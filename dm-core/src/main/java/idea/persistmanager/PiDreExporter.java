package idea.persistmanager;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import idea.conf.CompositeDescription;
import idea.intf.DataTyp;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PiDreExporter implements PiSubjectExporter {

	int did_warning = 0;
	private final static String endl = "\r\n";

	private Map<Object, FileWriter> writers;

	// private long firstTime;
	// private Date startTime;

	private RpSubject header;

	private File archiveDir;
	private File archiveFile;

	SimpleDateFormat df1 = new SimpleDateFormat("EEEEEEEE, MMMMMMMMM dd, yyyy");
	SimpleDateFormat tf1 = new SimpleDateFormat("HH:mm:ss.SSS");
	SimpleDateFormat dfstd = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
	DecimalFormat ms = new DecimalFormat("0.000");

	File fqName;
	String seqNo = null;

	HashMap<String, RpMetric[]> metricMap = new HashMap<String, RpMetric[]>();
	private long clipStartMs;
	private long clipEndMs;
	private Date clipStart;

	// HashMap<String, DeviceConfiguration> confMap = new HashMap<String,
	// DeviceConfiguration>();

	public PiDreExporter() {
		this(null, null);
	}

	public PiDreExporter(RpSubject header, File archiveFile) {
		this.header = header;

		this.archiveFile = archiveFile;
		if( archiveFile != null ) {
			archiveDir = archiveFile.getParentFile();
		}
	}

	public void setStartAndStopTimes(long start_time, long stop_time) {
		this.clipStartMs = start_time;
		this.clipEndMs = stop_time;
		this.clipStart = new Date(clipStartMs);
	}

	@Override
	public void connect() throws IOException {

		writers = new HashMap<Object, FileWriter>();

		createDreWriter("_index_");
	}

	@Override
	public void disconnect() throws IOException {

		if (writers != null) {
			synchronized (writers) {
				for (Object key : writers.keySet()) {
					FileWriter w = writers.get(key);
					w.close();
				}
				writers.clear();
			}
			writers = null;
		}
	}

	private FileWriter createWaveformHeader0(FileWriter writer, Date now, String devName, RpMetric[] cols, Integer sampleRate ) throws IOException {

		if (header != null) {
			writer.write("Dynamic Research Evaluation Workstation\nAnalog Waveform Recording: ");
			writer.write("v" + PiConstants.DRE_VERSION + endl);
			writer.write("Subset Format : Scaled ASCII (TXT)\n");
			writer.write(df1.format(now) + "    :   " + tf1.format(now) + endl + endl);
			writer.write("Company Name: " + header.getCompany() + endl);
			writer.write("Organization: " + header.getOrganization() + endl);
			writer.write("Study Title: " + header.getStudyTitle() + endl);
			writer.write("Sugery Date: " + df1.format(now) + endl);
			writer.write("Subject Number: HRV" + endl);
			writer.write("Medical ID: " + header.getMedicalId() + endl);
			writer.write("DAQ Operator(s): " + header.getOperator() + endl);
			writer.write("Base File Name: " + devName + endl);
			writer.write("Sequence Number: " + seqNo + endl);
			writer.write("Sample Rate: " + sampleRate + endl);
			writer.write("Notes: Subset File" + endl);
			writer.write(endl);
		}
		write_cols(writer, exportTimestamp, cols);

		return writer;
	}

	private void write_cols(FileWriter writer, boolean tstamp, RpMetric[] rpMetrics) throws IOException {
		boolean first = true;

		if (tstamp) {
			writer.write("tstamp");
			first = false;
		}
		for (RpMetric metric : rpMetrics) {
			String col = metric.getCode();

			if (col == null) {
				col = metric.getLocation();
			}
			if (metric instanceof CompositeDescription) {
				CompositeDescription cd = (CompositeDescription) metric;
				col = col + "[" + cd.getCount() + "]";
			}

			if (!first) {
				writer.write("\t");
			} else {
				first = false;
			}

			writer.write(col);
		}
		writer.write(endl);
		writer.flush();
	}

	private void buildFQName(String devname, String id) {

		if (devname == null) {
			log.error("devname null for: {}", archiveFile);
			devname = "unknown";
		}
		String x = devname.toLowerCase();
		if (x.endsWith(".dat")) {
			devname = devname.substring(0, devname.length() - 4);
		}

		int l = devname.length();
		if (l > 4) {
			String suffix = devname.substring(l - 4);
			if (suffix.matches("[\\._]\\d\\d\\d")) {
				devname = devname.substring(0, l - 3); // leave _ or .
			}
		}
		// devname = devname.replaceAll("\\", "_");
		// devname = devname.replaceAll("/", "_");
		// devname = devname.replaceAll(" ", "_");
		// devname = devname.replaceAll(":", "_");
		// devname = devname.replaceAll(">", "_");
		// devname = devname.replaceAll("<", "_");
		for (int i = 0; i < 100; i++) {
			seqNo = "" + i;
			if (seqNo.length() < 3)
				seqNo = "0" + seqNo;
			if (seqNo.length() < 3)
				seqNo = "0" + seqNo;
			fqName = new File(archiveDir, devname + id + seqNo + ".dat");
			if (!fqName.exists()) {
				break;
			}
		}
		return;
	}

	private FileWriter createDreWriter(String desc) throws IOException {
		buildFQName( "dre", desc);

		FileWriter writer = new FileWriter(fqName);
		writers.put(desc, writer);

		return writer;
	}

	private FileWriter createVitalsHeader0( FileWriter writer, String devname, RpMetric[] cols) throws IOException {

		if (header != null) {
			if( clipStart == null ) {
				clipStart = new Date();  // now
				log.error("No clipStart time for PiDreExport, assuming NOW");
			}
			writer.write("Dynamic Research Evaluation Workstation" + endl);
			writer.write("Vitals Report" + endl);
			writer.write(df1.format(clipStart) + endl);
			writer.write(endl);
		}

		write_cols(writer, true, cols);

		// return fqName;
		return writer;
	}

	private boolean exportTimestamp;

	public void putWaveform(StreamProducer source, PersistentItem wfb) throws IOException {

		if (wfb == null) {
			// this could be a big problem if it is the first record!
			// header is derived from the first record that gets past this point
			return;
		}
		FileWriter writer = writers.get(StreamID.WAVEFORM);

		if (writer == null) {
			String outName = archiveFile.getName();
			writer = createWriter( outName, StreamID.WAVEFORM );
			writers.put(StreamID.WAVEFORM, writer);
			
			RpMetric[] cols = wfb.getMetrics();
			createWaveformHeader0(writer, wfb.getTm(), outName, cols, cols[0].getSampleRate());
			log.warn("FIXME: cols should come from conf, not wfb");
		}

		RpMetric[] waves = IntfUtil.getMetrics(wfb);
		if (waves.length == 0) {
			return;
		}

		// if (firstTime < 0) {
		// long tm = wfb.getTm();
		// firstTime = tm;
		// double rel_tm = tm - firstTime;
		// }

		writer.write("# ");
		writer.write(dfstd.format(wfb.getTm()));
		writer.write(endl);

		int tot_rows = 0;

		int[][] data_is = new int[waves.length][];
		float[][] data_ff = new float[waves.length][];
		double[][] data_fs = new double[waves.length][];
		int cols = waves.length;
		for (int i = 0; i < cols; i++) {
			RpMetric wave = waves[i];
			Integer typ = wave.getSubtyp();
			int len = 0;
			if (typ == DataTyp.INT_ARR_TYP) {
				int[] data = (int[]) IntfUtil.getRawValue(wfb, waves[i]);
				data_is[i] = data;
				if (data != null) {
					len = data.length;
				}
			} else if (typ == DataTyp.FLOAT_ARR_TYP) {
				float[] data = (float[]) IntfUtil.getRawValue(wfb, waves[i]);
				data_ff[i] = data;
				if (data != null) {
					len = data.length;
				}
			} else if (typ == DataTyp.DOUBLE_ARR_TYP) {
				double[] data = (double[]) IntfUtil.getRawValue(wfb, waves[i]);
				data_fs[i] = data;
				if (data != null) {
					len = data.length;
				}
			} else {
				log.error("UNKNOWN DATA TYPE: {}", typ);
			}
			if (len > tot_rows) {
				tot_rows = len;
			}
		}

		for (int row = 0; row < tot_rows; row++) {
			int idx = 0;
			// if (exportTimestamp) {
			// rel_tm += dt;
			// writer.write(ms.format(rel_tm / 1000.0));
			// writer.write("\t");
			// }
			for (int i = 0; i < cols; i++) {
				// RpMetric wave = waves[i];
				int[] data_i = data_is[i];
				float[] data_f = data_ff[i];
				double[] data_d = data_fs[i];
				if (idx > 0) {
					writer.write("\t");
				}

				if (data_i != null) {
					if (row < data_i.length) {
						int d = data_i[row];
						writer.write(Integer.toString(d));
					}
				}
				if (data_f != null) {
					if (row < data_f.length) {
						float f = data_f[row];
						writer.write(Float.toString(f));
					}
				}
				if (data_d != null) {
					if (row < data_d.length) {
						double d = data_d[row];
						writer.write(Double.toString(d));
					}
				}
				idx++;
			}
			writer.write(endl);

			writer.flush();
		}

	}

	private FileWriter createWriter(String datName, StreamID sid) throws IOException {
		int dot = datName.lastIndexOf('.');
		if (dot > 0) {
			datName = datName.substring(0, dot);
		}

		File datFile = null;


		String ext = null;
		if (sid == StreamID.WAVEFORM)
			ext = "_w_%03d.dat";
		else if (sid == StreamID.MEASUREMENT)
			ext = "_v_%03d.vtl";

//		boolean append = false;
		if (ext == null) {
			sid = StreamID.ANNOTATION;
			datFile = new File(datName + " (notes).txt");
//			append = !firstNotesFile;
//			firstNotesFile = false;
		} else {

			int idx = 1;
			String suffix = "";
			do {
				suffix = String.format(ext, idx);
				datFile = new File(datName + suffix);
				idx++;
			} while (datFile.exists());
		}
		FileWriter writer = new FileWriter( new File( archiveDir, datFile.getName() ));
		
		return writer;
	}

	public void putMeasurement(StreamProducer source, StreamID sid, PersistentItem mb) throws IOException {

		// assert( false ) :
		// "only measurement blocks! NEEDS REWORK AT INTF LEVEL";
		RpMetric[] metrics = mb.getMetrics();
		
		//metricMap.put(source_name, metrics);


		synchronized (writers) {

			FileWriter writer = writers.get(sid);

			if (writer == null) {
				String outName = archiveFile.getName();
				writer = createWriter( outName, sid);
				writers.put( sid, writer);
				
//				RpMetric[] metrics = metricMap.get(devName);
//				if (metrics == null) {
//					log.error("No metrics configured for device: {}", devName);
//					return;
//				}
				createVitalsHeader0(writer, "dev", metrics );
			}
				
//			putDatedString(writers.get("_index_"), mb.getTm(), fqName.getPath());


			if (writer != null && metrics != null) {

				boolean hasData = false;
				
				StringBuffer sb = new StringBuffer();
				sb.append(dfstd.format(mb.getTm())); // "" + mb.getTime());

				for (RpMetric metric : metrics) {
					Object value = IntfUtil.getRawValueByLoc(mb, metric.getLocation());

					sb.append('\t');
					if (value == null) {
						// nothing...just blank
					} else if (value instanceof int[]) {
						sb.append("[");
						int[] arr = (int[]) value;
						for (int i = 0; i < arr.length; i++) {
							if (i > 0) {
								sb.append(",");
							}
							sb.append(arr.toString());
						}
						sb.append("]");
						hasData = true;
					} else {
						sb.append(value.toString());
						hasData = true;
					}

				}
				if( hasData ) {
					sb.append("\n");
					writer.write(sb.toString());
					writer.flush();
				}
			}
		}
	}

	public void putAnnotation(PersistentItem item) throws IOException {

		RpMetric[] metrics = item.getMetrics();
		
		String devName = "_anno_";
		FileWriter writer = writers.get(devName);
		if (writer == null) {
			writer = createDreWriter(devName);
			writeNotesHeader(writer, "n", IntfUtil.getMetrics(item));
		}
		putDatedString(writer, item.getTm() );
		for( RpMetric metric : metrics ) {
			Object val = IntfUtil.getRawValue(item, metric);
			if( val != null ) {
				writer.write("\t");
				writer.write( "" + val);
			}
		}
		writer.write(endl);

	}

	public void putAlarm(StreamProducer source, StreamID sid, PersistentItem item) throws IOException {
		String fileName = _getOutputName(source, sid, item);

		RpMetric[] metrics = IntfUtil.getMetrics(item);
		FileWriter writer = writers.get(fileName);
		if (writer == null) {
			writer = createDreWriter(fileName);
			writeNotesHeader(writer, "alarms", metrics);
		}
		writer.write(dfstd.format(item.getTm()));
		writer.write("\t");
		writer.write(fileName);
		for( RpMetric metric : metrics ) {
			writer.write("\t");
			writer.write( "" + IntfUtil.getRawValue(item, metric));
		}
		writer.write(endl);
		writer.flush();
	}

	private void writeNotesHeader(FileWriter writer, String name, RpMetric[] rpMetrics) throws IOException {

		if (header != null) {
			if( clipStart == null ) {
				clipStart = new Date();  // now
				log.error("No clipStart time for PiDreExport, assuming NOW");
			}
			writer.write("Dynamic Research Evaluation Workstation" + endl);
			writer.write("Notes and Comments" + endl);
			writer.write(df1.format(clipStart) + endl);
			writer.write(endl);
		}

		if (rpMetrics != null) {
			write_cols(writer, true, rpMetrics);
		}
	}

	public void rotate() throws IOException {

		log.error("FIXME: rotate not ready");
		// writer = createWaveformHeader0(tm, archiveFile, source_name,
		// IntfUtil.getMetricsField(wfb));
		// writers.put(source_name, writer);
		//
		// putDatedString(writers.get("_index_"), new Date(wfb.getTime()),
		// fqName.getPath());

	}

	private void putDatedString(FileWriter writer, Date now, String... strs) throws IOException {

		writer.write(dfstd.format(now));
		for (String str : strs) {
			writer.write("\t");
			if (str != null) {
				writer.write(str);
			}
		}
		//writer.write(endl);
		//writer.flush();
	}

	@Override
	public void addDevice(RpDevice conf) {
		String source_name = _getSourceName(conf.getName());

		if (source_name == null) {
			log.error("unexpected null source name for conf={}", conf);
			return;
		}

		// confMap.put(source_name, conf);
		for (RpStream stream : (List<? extends RpStream>)conf.getStreams()) {
			List<RpMetric> list = stream.getMetric();
			if (list == null || list.size() == 0) {
				System.err.println("PiDreExporter ignoring empty list for: " + conf.getName());
				continue;
			}
			RpMetric[] metrics = new RpMetric[list.size()];
			list.toArray(metrics);
			metricMap.put(source_name, metrics);
		}
	}

	private String _getOutputName(StreamProducer source, StreamID sid, PersistentItem mb) {
		String outputName = null;

		RpDevice conf = (source == null) ? null : source.getConfiguration();

		if (conf != null) {
			outputName = conf.getName() + "_" + sid.getName();
			outputName = outputName.replace("/", "_");
		}

		if (outputName == null) {
			outputName = mb.getClass().getSimpleName();
		}

		return outputName;
	}

	private String _getSourceName(String source_name) {
		if (source_name != null && source_name.indexOf("/") > 0) {
			String[] ar = source_name.split("/");
			source_name = ar[0];
		}

		return source_name;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (writers == null) {
			return; // NOT CONNECTED
		}
		try {
			if (sid == StreamID.WAVEFORM) {
				putWaveform(source, item);
			} else if (sid == StreamID.ALARM) {
				putAlarm(source, sid, item);
			} else if (sid == StreamID.ANNOTATION) {
				putAnnotation(item);
			} else if (sid == StreamID.MEASUREMENT) {
				putMeasurement(source, sid, item);
			}
		} catch (IOException e1) {
			// BLIND: notify someone that data is being lost!
		}
	}

	@Override
	public void setHeader(RpSubject header) {
		this.header = header;
	}

	@Override
	public void setDestination(File archiveDir) {
		this.archiveDir = archiveDir;
	}

	public void exportTimestamp(boolean exportWaveTimestamp) {
		this.exportTimestamp = exportWaveTimestamp;
	}

}
