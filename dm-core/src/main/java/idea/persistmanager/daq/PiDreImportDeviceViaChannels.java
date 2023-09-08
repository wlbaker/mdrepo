package idea.persistmanager.daq;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.driver.NullDevice;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import idea.repository.DaqUtil;

@Slf4j
public class PiDreImportDeviceViaChannels extends AbstractStreamProducer implements PiDatastreamImporter, AdapterInterface {

	private static final int BINARY_FLAG = 0x10;
	private static final int VITALS_TYPE = 0x01;
	private static final int WAVEFORM_TYPE = 0x02;

	// BufferedReader char_reader;
	// RandomAccessFile binary_reader;
	private SeekableByteChannel chan_reader;
	ByteBuffer bb;

	RpSubject header;

	private static DateFormat time_format = new SimpleDateFormat("HH:mm:ss");
	private DeviceCapabilities conf;
	private List<String> fieldNames;

	private File file;
	// float[] colMult;

	long start_tm;
	long pos;
	private int DEFAULT_PACKET_SIZE = 40; // not really a constant for everyone

	private int sampleRate;

	/*
	 * set to true to handle some ECG data...multiply by 1000
	 */

	private boolean isAnalog = true;
	private Class<? extends PersistentItem> metricsClass;
	private ConnectionStatus conn_stat;
	private String devName;
	private STP stp;
	private int end_of_header;
	private static int model_idx = 1;

	public PiDreImportDeviceViaChannels(File file, String devName) {
		this.file = file;
		if (devName == null) {
			devName = file.getName();
			// int idx = devName.indexOf('.');
			// if( idx > 5 ) {
			// idx = 5;
			// }
			// if( idx > 0 ) {
			// int len = devName.length();
			// devName = devName.substring( len - idx, len - 1);
			// }
			int idx = devName.lastIndexOf('.');
			if (idx > 1) {
				devName = devName.substring(0, idx);
			}
		}
		this.devName = devName;
	}

	@Override
	public PersistentItem next() throws IOException {
		PersistentItem block;

		int data_typ = header.getDataType();
		if (data_typ == VITALS_TYPE) {
			block = next_vitals_block();
		} else if (data_typ == WAVEFORM_TYPE) {
			block = next_waveform_block();
		} else if ((data_typ & BINARY_FLAG) > 0) {
			block = next_binary_block();
		} else {
			log.error("unrecognized data type: {}", data_typ);
			block = null;
		}

		return block;
	}

	private PersistentItem next_vitals_block() throws IOException {

		PersistentItem nb = ModelUtil.getModelFromDataClass(metricsClass);
		nb.setDriver(this);

		nb.setTm(new Date(0));

		String line = DaqUtil.readLine(chan_reader, bb);
		pos++;
		if (line == null) {
			return null;
		}

		if (line.length() == 0) {
			return null;
		}

		StringTokenizer tokens = new StringTokenizer(line);

		for (int col = 0; col < fieldNames.size() + 1; col++) {
			if (tokens.hasMoreTokens()) {
				String token = tokens.nextToken();

				if (col == 0) {

					try {

						// Unless you are already in GMT, you have to subtract
						// off
						// the time zone offset of CST from GMT.
						if (token.indexOf(':') > 0) {
							Date headerDate = header.getSurgeryDate();
							Date dt = time_format.parse(token);
							dt.setYear(headerDate.getYear());
							dt.setMonth(headerDate.getMonth());
							dt.setDate(headerDate.getDate());
							nb.setTm(dt);
						} else {
							nb.setTm(new Date(Long.parseLong(token)));
						}
						// nb.setTime( dt.getTime() - dt0.getTime() );
					} catch (ParseException pe) {
						throw new IOException(pe);
					}

				} else {
					float val = Float.parseFloat(token);

					RpMetric m = nb.getMetricFromCode(fieldNames.get(col - 1));
					IntfUtil.setValue(nb, m, val);
				}
			}

		}

		return nb;
	}

	private PersistentItem next_waveform_block() throws IOException {
		PersistentItem wb = ModelUtil.getModelFromDataClass(metricsClass);
		wb.setStreamID(StreamID.WAVEFORM.getCode());
		wb.setDriver(this);
		wb.setTm(new Date(getTimeInMillis()));

		int samplesPerPacket = DEFAULT_PACKET_SIZE;
		for (String name : fieldNames) {
			RpMetric desc = wb.getMetricFromCode(name);
			if (desc.getSamplesPerPacket() > 0) {
				samplesPerPacket = desc.getSamplesPerPacket();
			}
			if (desc.getSubtyp() == DataTyp.FLOAT_ARR_TYP) {
				float[] data = new float[samplesPerPacket];
				IntfUtil.setValue(wb, desc, data);
			} else if (desc.getSubtyp() == DataTyp.DOUBLE_ARR_TYP) {
				double[] data = new double[samplesPerPacket];
				IntfUtil.setValue(wb, desc, data);
			} else {
				log.error("unkown datatype -- cannot allocate: " + desc.getSubtyp());
			}
		}

		if (readWaveformData(wb) == false) {
			wb = null;
		}
		return wb;
	}

	private PersistentItem next_binary_block() throws IOException {
		PersistentItem wb = ModelUtil.getModelFromDataClass(metricsClass);
		wb.setStreamID(
				(header.getDataType() == VITALS_TYPE) ? StreamID.MEASUREMENT.getCode() : StreamID.WAVEFORM.getCode());
		wb.setDriver(this);
		wb.setTm(new Date(getTimeInMillis()));

		int samplesPerPacket = DEFAULT_PACKET_SIZE;
		for (String name : fieldNames) {
			RpMetric desc = wb.getMetricFromCode(name);
			if (desc.getSamplesPerPacket() > 0) {
				samplesPerPacket = desc.getSamplesPerPacket();
			}
			if (desc.getSubtyp() == DataTyp.FLOAT_ARR_TYP) {
				float[] data = new float[samplesPerPacket];
				IntfUtil.setValue(wb, desc, data);
			} else if (desc.getSubtyp() == DataTyp.DOUBLE_ARR_TYP) {
				double[] data = new double[samplesPerPacket];
				IntfUtil.setValue(wb, desc, data);
			} else {
				log.error("unkown datatype -- cannot allocate: " + desc.getSubtyp());
			}
		}

		if (readBinaryData(wb) == false) {
			wb = null;
		}
		return wb;
	}

	@Override
	public void connect() throws IOException {
		rewind(); // this opens and reads the header

		conf = new DeviceCapabilities(NullDevice.class);

		String importName = file.getName();
		conf.setName(devName);
		conf.setDriverName(importName);

		if (metricsClass == null && fieldNames != null) {
			try {
				RpMetric[] fields = namesToFields();
				metricsClass = ModelUtil.findCachedModel(Arrays.asList(fields));

				if (metricsClass == null) {

					String modelName = importName.replace("/", "");
					modelName = "idea.model.auto.Auto" + modelName + model_idx;
					model_idx++;

					try {
						metricsClass = ModelUtil.createDynamicModel("idea.auto.dre." + importName,
								Arrays.asList(fields));
					} catch (Exception e) {
						log.error("could not creating dynamic model", e);
					}
				}

			} catch (Exception e) {
				throw (new IOException("could not build data model", e)); // wrap
																			// and
																			// throw
			}
			if (header.getDataType() == 1)
				conf.addStream(StreamID.MEASUREMENT, metricsClass);
			else
				conf.addStream(StreamID.WAVEFORM, metricsClass);
		}

		conn_stat = ConnectionStatus.CONNECTED;

	}

	private RpMetric[] namesToFields() {
		int dt = header.getDataType();
		RpMetric[] fields = new RpMetric[fieldNames.size()];

		RpLinearUnit linear = new RpLinearUnit();
		linear.setM(1);
		linear.setB(0);
		linear.setUnitName("");

		int idx = 0;
		for (String name : fieldNames) {
			// FIXME: NORMALIZED LOC 
			// String loc2 = ModelUtil.normalizeFieldName(val);
			String loc = name; // ModelUtil.normalizeFieldName(name);
			RpMetric md;
			if ((dt & VITALS_TYPE) > 0) {
				// md = RpUtil.createRpMetric(name, name, null, linear,
				// DataTyp.INT_TYP);
				// md = RpUtil.createRpMetric(loc, name, null, linear,
				// DataTyp.FLOAT_TYP);
				md = RpUtil.createRpMetric(loc, name, null, linear, DataTyp.DOUBLE_TYP);
			} else if ((dt & WAVEFORM_TYPE) > 0) {
				md = RpUtil.createRpMetric(loc, name, null, 0, 0, linear);
				// md.setSubtyp(DataTyp.INT_ARR_TYP);
				// md.setSubtyp(DataTyp.FLOAT_ARR_TYP);
				md.setSubtyp(DataTyp.DOUBLE_ARR_TYP);
				md.setSamplesPerPacket(DEFAULT_PACKET_SIZE);
				md.setSampleRate(sampleRate);
			} else {
				log.error("unknown data type: {}", dt);
				md = null;
			}
			fields[idx++] = md;
		}
		return fields;
	}

	@Override
	public void disconnect() throws IOException {
		conn_stat = ConnectionStatus.NOT_CONNECTED;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	private boolean readWaveformData(PersistentItem wb) throws IOException {

		String line;

		int samplesPerPacket = 0;

		// prepare output arrays for quick lookup
		float[][] out = new float[fieldNames.size()][];
		for (int col = 0; col < fieldNames.size(); col++) {
			RpMetric wf = wb.getMetricFromCode(fieldNames.get(col));
			out[col] = (float[]) IntfUtil.getRawValue(wb, wf);

			int wf_spp = wf.getSamplesPerPacket();
			if (wf_spp > samplesPerPacket) {
				samplesPerPacket = wf_spp;
			}

		}

		if (samplesPerPacket <= 0)
			samplesPerPacket = DEFAULT_PACKET_SIZE;

		for (int i = 0; i < samplesPerPacket; i++) { // for each row

			line = DaqUtil.readLine(chan_reader, bb);
			pos++;
			if (line == null) {
				return false;
			}

			if (line.length() == 0) {
				continue;
			}

			StringTokenizer tokens = new StringTokenizer(line);

			for (int col = 0; col < fieldNames.size(); col++) {
				if (tokens.hasMoreTokens()) {
					String token = tokens.nextToken();

					if (isAnalog) {
						float val = Float.parseFloat(token);
						out[col][i] = val;
					} else {

						// double parsing is slow...check to see if necessary
						// first
						if (token.indexOf(".") > 0) {
							float val = Float.parseFloat(token);
							out[col][i] = (int) val;
						} else {
							out[col][i] = Integer.parseInt(token);
						}
					}
				}

			}

		}
		return true;
	}

	private boolean readBinaryData(PersistentItem wb) throws IOException {

		int samplesPerPacket = 0;

		// prepare output arrays for quick lookup
		float[][] out = new float[fieldNames.size()][];
		for (int col = 0; col < fieldNames.size(); col++) {
			RpMetric wf = wb.getMetricFromCode(fieldNames.get(col));
			out[col] = (float[]) IntfUtil.getRawValue(wb, wf);
			if (out[col] == null) {

				int wf_spp = wf.getSamplesPerPacket();
				if (wf_spp > samplesPerPacket) {
					samplesPerPacket = wf_spp;
				}
			}

		}

		if (samplesPerPacket <= 0)
			samplesPerPacket = DEFAULT_PACKET_SIZE;

		int n = fieldNames.size();
		byte[] buf = new byte[4 * n * samplesPerPacket];
		ByteBuffer bb = ByteBuffer.wrap(buf);

		int tot = chan_reader.read(bb);
		if (tot < buf.length) {
			return false;
		}
		bb.flip();

		bb.order(ByteOrder.BIG_ENDIAN);

		for (int i = 0; i < samplesPerPacket; i++) { // for each row
			pos++;

			// read a predetermined number of bytes into the buffer
			for (int col = 0; col < n; col++) {

				float val = bb.getFloat();
				out[col][i] = val;

			}

		}
		return true;
	}

	@Override
	public void rewind() throws IOException {

		close();

		chan_reader = Files.newByteChannel(file.toPath(), StandardOpenOption.READ);

		bb = ByteBuffer.allocate(2048); // entire header must be in this block!
		chan_reader.read(bb); // has to succeed
		bb.flip();

		header = DaqUtil.readDaqHeader(chan_reader, bb);

		sampleRate = DaqUtil.getSampleRate(); // header.getSampleRate();
//		if (sampleRate > 5) {
//			DEFAULT_PACKET_SIZE = sampleRate / 5;
//			if (DEFAULT_PACKET_SIZE <= 0) {
				DEFAULT_PACKET_SIZE = 40;
//			}
//		}

		start_tm = header.getSurgeryDate().getTime();
		pos = 0;
		if (sampleRate <= 0 && header.getDataType() == 2) { // invalid sample
															// rate, or not
															// specified
			log.error("Sample rate not specified: assuming 200");
			sampleRate = 200; // assumption...invalid
		}

		fieldNames = new LinkedList<String>();
		readDescriptions(fieldNames);

		end_of_header = bb.position();
		chan_reader.position(end_of_header); // set next read position to start
												// of data
	}

	public void close() throws IOException {
		if (chan_reader != null) {
			chan_reader.close();
			chan_reader = null;
		}

	}

	public RpSubject getSubjectInfo() {
		return header;
	}

	protected void readDescriptions(List<String> metrics) throws IOException {
		String line = DaqUtil.readLine(chan_reader, bb);

		metrics.clear();

		String[] ar = line.split("\t");
		int idx = 0;
		for (String sigName : ar) {

			if (idx == 0 && header.getDataType() == VITALS_TYPE) {
				// skip...this is time
			} else {
				if (stp != null) {
					sigName = stp.labels[idx];
				}
				sigName = sigName.replace("\"", "");
				metrics.add(sigName);
			}

			idx++;
		}

	}

	public long getTimeInMillis() {
		long val = start_tm;

		val += (pos * 1000) / sampleRate;

		return val;
	}

	@Override
	public ArchiveMetaData getMeta() throws IOException {
		ArchiveMetaData meta = new ArchiveMetaData();
		meta.setStartTime(header.getSurgeryDate());
		return meta;
	}

	@Override
	public void seek(long seek_tm) throws IOException {

		log.error("FIXME: this is a relative time seek, not abs time, and its wrong anyway");
		long seek_pos = (seek_tm - start_tm) * sampleRate / 1000;

		if (pos > seek_pos) {
			rewind();
		}

		while (pos < seek_pos) {
			// char_reader.readLine();
			// FIXME: replaced by chan_reader anyway
			pos++;
		}

	}

	@Override
	public void requestCapabilities() throws IOException {
		// TODO Auto-generated method stub
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		log.error("FIXME: getStaticCapabilities incomplete");
		return null;
	}

	@Override
	public int tick() {
		log.error("FIXME: tick incomplete");
		return 0;
	}

	@Override
	public String getName() {
		return devName;
	}

	@Override
	public ConnectionStatus getStatus() {
		return conn_stat;
	}

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {
		if (sid == StreamID.MEASUREMENT) {
			if (header.getDataType() == VITALS_TYPE) {
				return metricsClass;
			}
		} else if (sid == StreamID.WAVEFORM) {
			if ((header.getDataType() & WAVEFORM_TYPE) > 0) {
				return metricsClass;
			}
		}
		return null;
	}

	@Override
	public StreamID[] getStreams() {
		StreamID[] sids = new StreamID[1];
		if (header.getDataType() == VITALS_TYPE) {
			sids[0] = StreamID.MEASUREMENT;
		} else {
			// could be binary or ascii
			sids[0] = StreamID.WAVEFORM;
		}
		return sids;
	}

	public void setSTP(STP sess) {
		this.stp = sess;
	}

}
