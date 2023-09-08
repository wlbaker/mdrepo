package idea.persistmanager.dbf;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class RAWReader extends AbstractStreamProducer implements PiDatastreamImporter {

	private File f;
	private String ini;
	private String calib;

	private int sampleRate;
	private int bufferSize;
	private int evalBlocks; // This appears to be the number of signals in the file
	private RpMetric signal;
	private List<RpMetric> sigs;
	private Class<? extends PersistentItem> model;
	private int model_idx;
	private FileInputStream fis;
	private String name;
	private StreamID[] streams = { StreamID.WAVEFORM };
	private DeviceCapabilities caps = null;
	private long row_num;
	private long start;

	public RAWReader(File f, String ini, String calib) {
		this.f = f;
		this.ini = ini;
		this.calib = calib;

		name = f.getName();
		int idx = name.indexOf('.');
		if (idx > 0) {
			name = name.substring(0, idx);
		}

	}

	@Override
	public RpDevice getStaticCapabilities() {
		return caps ;
	}

	@Override
	public PersistentItem next() throws IOException {
		byte[] block = new byte[bufferSize * 2]; // two bytes per sample
		PersistentItem item = ModelUtil.getModelFromDataClass(model);
		item.setTime(start + row_num * 1000 /  this.sampleRate);
		item.setStreamID( StreamID.WAVEFORM.getCode() );
		RpMetric[] model_sigs = IntfUtil.getMetrics(model);
		for ( int sig_idx = 0; sig_idx < evalBlocks; sig_idx++) {
			RpMetric sig = null;
			if( sig_idx < model_sigs.length ) {
				sig = model_sigs[sig_idx];
			}
		
			int[] buf = new int[bufferSize];
			int n = fis.read(block);
			if( n != block.length ) {
				item = null;
				break;
			}
			ByteBuffer bb = ByteBuffer.wrap(block);
			bb.order(ByteOrder.LITTLE_ENDIAN);
			for (int i = 0; i < bufferSize; i++) {
				int val = bb.getShort();
				buf[i] = val;
			}
			if( sig != null ) {
				IntfUtil.setValue(item, sig, buf);
			}
		}
		
		row_num += bufferSize;
		return item;
	}

	@Override
	public void rewind() throws IOException {
		log.error("rewind() unimplemented");
		// fis.
	}

	@Override
	public ArchiveMetaData getMeta() throws IOException {
		log.error("getMeta() unimplemented");
		return null;
	}

	@Override
	public void seek(long startTime) throws IOException {
		log.error("seek() unimplemented");
	}

	@Override
	public void connect() throws IOException {
		sigs = new LinkedList<RpMetric>();
		readINI();
		readCalib();
		
//		int bogus = 0;
		if (evalBlocks > sigs.size()) {

			log.error("IGNORING {} BOGUS SIGNAL(S) IN RAW FILE", evalBlocks-sigs.size() );
//			signal = new RpMetric();
//			signal.setSubtyp(DataTyp.INT_ARR_TYP);
//			signal.setLocation("BOGUS" + bogus);
//			signal.setSampleRate(sampleRate);
//			signal.setSamplesPerPacket(bufferSize);
//			sigs.add( signal );
//			bogus++;
		}

		model = ModelUtil.findCachedModel(sigs);
		if (model == null) {
			model_idx++;
			try {
				model = ModelUtil.createDynamicModel("idea.model.auto.RAW" + name + model_idx, sigs);
			} catch (Exception e) {
				throw new IOException(e);
			}
		}

		row_num = 0;
		fis = new FileInputStream(f);
		
		
		caps = new DeviceCapabilities( RAWReader.class );
		caps.setName( name );
		caps.addStream( StreamID.WAVEFORM, model );

	}

	private void readCalib() throws IOException {
		int lowADC = 0;
		int highADC = 0;
		double lowMetric = 0;
		double highMetric = 0;

		File dir = f.getParentFile();
		File in = new File(dir, calib);
		BufferedReader r = new BufferedReader(new FileReader(in));

		String section = "NONE"; // section should not be null
		do {
			String line = r.readLine();
			if (line == null)
				break;
			line = line.trim(); // just in case
			if (line.length() == 0) {
				// empty lines are ok
			} else if (line.startsWith(";")) {
				// comment, ingore
			} else if (line.startsWith("[")) {
				line = line.trim();
				section = line.replace("[", "");
				section = section.replace("]", "");
				lowADC = 0;
				highADC = 0;
				lowMetric = 0;
				highMetric = 0;
			} else {
				String val = "";
				String[] args = line.split("\\=");
				if (args == null) {
					log.error("CALIB FORMAT ERROR in section: {}", section);
					continue;
				}
				String key = args[0];
				if (args.length > 1) {
					val = args[1];
				}

				val = val.replace(",", "");
				val = val.replace("_", "");
				val = val.trim();
				if ("LowADC".equals(key)) {
					lowADC = Integer.parseInt(val);
				} else if ("HighADC".equals(key)) {
					highADC = Integer.parseInt(val);
				} else if ("LowMetric".equals(key)) {
					lowMetric = Double.parseDouble(val);
				} else if ("HighMetric".equals(key)) {
					highMetric = Double.parseDouble(val);

					RpMetric sig = findSignal(section);
					if (sig != null) {
						RpLinearUnit unit = (RpLinearUnit) sig.getUnit();
						double m = ((double) (highMetric - lowMetric)) / (highADC - lowADC);
						double b = lowMetric - m * lowADC;
						unit.setM(m);
						unit.setB(b);
					}

				}
			}
		} while (true);

		r.close();
	}

	private RpMetric findSignal(String section) {

		for (RpMetric sig : sigs) {
			String code = sig.getCode();
			if (section.equals(code)) {
				return sig;
			}
		}
		return null;
	}

	private void readINI() throws IOException {
		File dir = f.getParentFile();
		File in = new File(dir, ini);
		BufferedReader r = new BufferedReader(new FileReader(in));

		String section = "NONE"; // section should not be null
		do {
			String line = r.readLine();
			if (line == null)
				break;
			line = line.trim(); // just in case
			if (line.length() == 0) {
				// empty lines are ok
			} else if (line.startsWith(";")) {
				// comment, ingore
			} else if (line.startsWith("[")) {
				section = line;
				if (line.startsWith("[AIN_SIGNAL")) {
					signal = new RpMetric();
					signal.setSubtyp(DataTyp.INT_ARR_TYP);
					signal.setLocation(line);
					signal.setSampleRate(sampleRate);
					signal.setSamplesPerPacket(bufferSize);
					sigs.add(signal);
				}
			} else {
				String val = "";
				String[] args = line.split("\\=");
				if (args == null) {
					log.error("INI FORMAT ERROR in section: {}", section);
					continue;
				}
				String key = args[0];
				if (args.length > 1) {
					val = args[1];
				}

				if (section.startsWith("[INPUT_BOARD")) {
					processInputBoardParam(key, val);
				} else if (section.startsWith("[AIN_SIGNAL")) {
					processInputSignal(key, val);
				}
			}
		} while (true);

		r.close();
	}

	private void processInputSignal(String key, String val) {
		if ("Name".equals(key)) {
			signal.setCode(val);
		} else if ("Fullname".equals(key)) {
			signal.setName(val);
			if (val.indexOf("Not used") > 0) {
				sigs.remove(signal); // my bad...not used
			}
		} else if ("Dimension".equals(key)) {
			RpLinearUnit unit = new RpLinearUnit();
			unit.setUnitName(val);
			signal.setUnit(unit);
		}
	}

	private void processInputBoardParam(String key, String val) {
		if ("DTSamplerate".equals(key)) {
			sampleRate = Integer.parseInt(val);
		} else if ("DTBuffer_Size".equals(key)) {
			bufferSize = Integer.parseInt(val);
		} else if ("NumberOfEvalBlocks".equals(key)) {
			evalBlocks = Integer.parseInt(val);
		}

	}

	@Override
	public void disconnect() throws IOException {
		fis.close();
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {
		return model;
	}

	@Override
	public StreamID[] getStreams() {
		return streams;
	}

	public void setStartTime(Date start) {
		this.start = start.getTime();
	}

}
