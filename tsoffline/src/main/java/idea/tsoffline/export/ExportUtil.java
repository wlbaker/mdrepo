package idea.tsoffline.export;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.sound.sampled.AudioFileFormat;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;

import org.piccolo2d.PLayer;

import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectExporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiCompositeImporter;
import idea.persistmanager.PiDreExporter;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.sql.SQLExporter;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpSubject;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.datamanager.ExcelExporter;

@Slf4j
public class ExportUtil {
	private final PropertyChangeSupport pcs = new PropertyChangeSupport(this);

	public final static String PNAME_CURRENT_DEVICE = "CURRENT_DEVICE";
	public final static String PNAME_CURRENT_PROGRESS = "CURRENT_PROGRESS";
	public final static String PNAME_MAX_PROGRESS = "MAX_PROGRESS";

	protected static final int RESAMPLE_NONE = 0;
	protected static final int RESAMPLE_HOLD = 1;
	protected static final int RESAMPLE_INTERPOLATE = 2;

	private String method;
	private String spec;

	@Setter
	private long dataStartMs;

	@Setter
	private Date clipStart;
	@Setter
	private Date clipEnd;
	@Setter
	private File audioInputFile;
	@Setter
	private File audioOutputFile;

	private PiSubjectImporter importer;
	boolean merge = false;
	int mssInterval;
	int resampleMethod;
	boolean showTimestamp = true;

	boolean stop_export;

	long clipStartMs = 0;
	long clipEndMs = Long.MAX_VALUE;

	Map<String, List> dev_signals;

	/*
	 * status values for clients
	 */
	private String currentDevice;
	private int currentProgress;

	private int maxProgress;

	private PiSubjectExporter exporter;
	boolean is_connected = false;

	private RpSubject header;

	public ExportUtil() {

	}

	public void setOutput(String method, String spec) {
		this.method = method;
		this.spec = spec;
	}

	public void setImporter(PiSubjectImporter importer) {
		this.importer = importer;
	}

	public void setInterval(int msecs) {
		mssInterval = msecs;
	}

	private PiSubjectExporter prepareExporter(long clipStartMs, long clipEndMs) throws IOException {
		if (importer instanceof PiCompositeImporter) {
			PiCompositeImporter ci = (PiCompositeImporter) importer;
			subjectChange(ci.getSubject());
		}
		PiSubjectExporter exporter = null;

		switch (method) {
		case "XLS":
		case "XLSX":
			ExcelExporter xls_exporter = new ExcelExporter(new File(spec), null, false);
			if (merge == true) {
				xls_exporter.setSheetMode(ExcelExporter.SINGLE_SHEET);
			} else {
				xls_exporter.setSheetMode(ExcelExporter.MULTIPLE_SHEET);
			}
			xls_exporter.setStartAndStopTimes(clipStartMs, clipEndMs);
			exporter = xls_exporter;
			break;
		case "DRE":
		case "DAT":
			PiDreExporter dre_exporter = new PiDreExporter(header, new File(spec));
			dre_exporter.setStartAndStopTimes(clipStartMs, clipEndMs);
			exporter = dre_exporter;
			break;
		case "H5":
		case "HDF5":
			exporter = new PiHdf5Exporter(header, spec, true);
			break;
		case "ASCII":
			exporter = new PiDreExporter(null, new File(spec));
			break;
		case "JDBC":
			exporter = new SQLExporter("exporterSQLite", spec);
			break;
		default:
			log.error("Unknown identify export method: {}", method);
		}

		if (exporter instanceof ExcelExporter) {
			log.error("FIXME: remove xls exporter specific features...make them general or git rid of them");
			ExcelExporter xx = (ExcelExporter) exporter;
			xx.setInterval(mssInterval);

			switch (resampleMethod) {
			case RESAMPLE_NONE:
				// nothing to do
				break;
			case RESAMPLE_HOLD:
			case RESAMPLE_INTERPOLATE:
				throw (new IOException("Interpolate resampling not ready: " + resampleMethod));
			default:
				throw (new IOException("Sample Method Unknown: " + resampleMethod));
			}

		} else {
			log.error("FIXME: implement features used by XLS exporter via manager...obsolete...however");
		}

		return exporter;
	}

	public void init() {
		if (clipStart != null) {
			clipStartMs = clipStart.getTime();
		}
		if (clipEnd != null) {
			clipEndMs = clipEnd.getTime();
		}

		if (clipStart == null || clipEnd == null) {
			setClientMaxProgress(-1);
		} else {
			setClientMaxProgress((int) ((clipEndMs - clipStartMs) / 1000));
		}
	}

	public void run() throws IOException {

		stop_export = false;

		exporter = prepareExporter(clipStartMs, clipEndMs);
		exporter.connect();
		exporter.setHeader(header);
		is_connected = true;

		// exportMetrics();

		// importer.rewind();
		// importer.seek(tmStart);
		long t0 = System.currentTimeMillis();
		// if (merge) {
		exportMerged();
		// } else {
		// exportAllDevices(exporter);
		// }
		System.out.println("export time: " + (System.currentTimeMillis() - t0));

		setClientCurrentProgress(-1);
		try {
			exporter.disconnect();
		} catch (Exception e) {
			// speculative debugging
			log.error("could not disconnect", e);
		}
		System.out.println("write time: " + (System.currentTimeMillis() - t0));
		if (audioOutputFile != null) {
			exportAudio(audioInputFile, audioOutputFile, "WAV", dataStartMs, clipStartMs, clipEndMs);
		}
		is_connected = false;
		setClientCurrentProgress(-2);
	}

	// basics of audio file formats in java:
	//
	// https://docs.oracle.com/javase/tutorial/sound/converters.html
	//

	public static void exportAudio(File audioInputFile, File audioOutputFile, String typ, long dataStartMs,
			long clipStartMs, long clipEndMs) throws IOException {

		long clipStartRel = clipStartMs - dataStartMs;
		long clipEndRel = clipEndMs - dataStartMs;

		int start_sample = (int) (11025 * clipStartRel / 1000);
		if (start_sample < 0) {
			start_sample = 0;
		}

		int last_sample = (int) (11025 * clipEndRel / 1000);
		if (last_sample < 0) {
			last_sample = 0;
		}

		/*
		 * a special class to lie about the length of the input file stream, since the
		 * re-coder doesn't really have a way to say when to stop...it just recodes the
		 * whole input stream!
		 */
		class CutLengthFileInputStream extends FileInputStream {

			private int tot;
			private int clip;

			int pos = 0;
			private int mark_pos;

			public CutLengthFileInputStream(File file, int tot) throws FileNotFoundException {
				super(file);
				this.clip = (int) (file.length() - tot);
				this.tot = tot;
			}

			@Override
			public int available() throws IOException {
				return super.available() - clip;
			}

			@Override
			public int read() throws IOException {
				if (pos < tot) {
					pos += 1;
					return super.read();
				}
				return -1;
			}

			@Override
			public int read(byte[] b) throws IOException {
				if (pos < tot) {
					int n = super.read(b);
					pos += n;
					return n;
				}
				return -1;
			}

			@Override
			public int read(byte[] b, int off, int len) throws IOException {
				int n = -1;
				if (pos < tot) {
					n = super.read(b, off, len);
					pos += n;
				}
				return n;
			}

			@Override
			public long skip(long n) throws IOException {

				long m = -1;
				if (pos < tot) {
					m = super.skip(n);
					if (m > 0) {
						pos += m;
					}
				}

				return m;
			}

			@Override
			public synchronized void mark(int readlimit) {
				mark_pos = pos;
				super.mark(readlimit);
			}

			@Override
			public synchronized void reset() throws IOException {
				pos = mark_pos;
				super.reset();
			}

		}

		InputStream in = new CutLengthFileInputStream(audioInputFile, last_sample * 2 + 71);

		byte[] header = new byte[71];
		in.read(header, 0, 71);
		in.mark(0);

		AudioFormat f = new AudioFormat(11025, 16, 1, true, true);
		// create an audiostream from the inputstream
		AudioInputStream ais = new AudioInputStream(in, f, AudioSystem.NOT_SPECIFIED);

		// ais.reset(); ... not supported by this stream
		// ? ais.skip(samples * 2); // two bytes per sample...not supported for
		// variable length streams!
		byte[] b = new byte[1000];
		int skip = (int) start_sample * 2;
		while (skip > 0) {
			int len = skip;
			if (len > b.length) {
				len = b.length;
			}
			skip -= len;
			ais.read(b, 0, len);
		}

		if ("RAW".equals(typ)) {
			int len;
			OutputStream writer = new FileOutputStream(audioOutputFile);
			byte[] audio_header = "Dynamic Research Evaluation Workstation Audio Recording".getBytes();
			ByteBuffer bb = ByteBuffer.allocate(71);
			bb.putInt(audio_header.length);
			bb.put(audio_header);
			bb.put((byte) 0);
			bb.put((byte) 0);
			bb.put((byte) 0);
			bb.put((byte) 0);
			bb.putInt(1);
			bb.putInt(256 + 124); // something to do with file length
			byte[] arr = bb.array();
			for (int i = 0; i < 71; i++) {
				if (i % 16 == 0) {
					System.out.println();
				}
				System.out.print(" " + arr[i]);
			}
			writer.write(bb.array(), 0, 71);
			while ((len = ais.read(b, 0, b.length)) > 0) {
				writer.write(b, 0, len);
			}
			writer.close();
		} else {
			AudioSystem.write(ais, AudioFileFormat.Type.WAVE, audioOutputFile);
		}

		ais.close();

	}

	private void exportMerged() throws IOException {

		boolean hasNext = false;
		do {
			doMergeExport(importer);

			if (importer instanceof PiCompositeImporter) {
				PiCompositeImporter ci = (PiCompositeImporter) importer;
				hasNext = ci.nextSubject();
			}
		} while (hasNext);
	}

	@Deprecated
	private void doSimpleExport(PiDatastreamImporter src) throws IOException {

		String name = src.getName();

		List<? extends RpMetric> ssigs = dev_signals.get(name);
		if (ssigs == null || ssigs.size() == 0) {
			log.debug("device not referenced: {}", name);
			return;
		}

		setClientCurrentDevice(name);
		setClientCurrentProgress(0);

		src.rewind();
		src.seek(clipStartMs);

		PersistentItem block;

		System.out.println("STARTING EXPORT : " + name);
		int idx = 0;
		while ((block = src.next()) != null && !stop_export) {
			long tm = block.getTime();
			if (idx > 100) {
				idx = 0;
			}
			idx++;

			if (tm < clipStartMs) {
				Date dtCurr = new Date(tm);
				Date dtStart = new Date(clipStartMs);
				log.error("unexpected packet before time range: {} < {}", dtCurr, dtStart);
				continue;
			}
			if (tm > clipEndMs) {
				break;
			}

			// if this is a group, send the parent dev as the data source. The
			// subdev has a name of "numerics"
			// and all the streams will lump together in one sheet.
			int sid_code = block.getStreamID();
			StreamID sid = StreamID.fromCode(sid_code);

			exporter.streamEvent(0, src, sid, block); // export simple

			setClientCurrentProgress((int) ((tm - clipStartMs) / 1000));
		}

		System.out.println("COMPLETE EXPORT~!!!!!");
	}

	private void doMergeExport(PiSubjectImporter importer) throws IOException {

		PersistentItem block;

		importer.connect(); // rewind is implicit
		importer.seek(clipStartMs);

		/*
		 * we need to deal with the special case where we are exporting a merged
		 * dataset, and one of the exports is a waveform. if so, space out the entries
		 * by the waveform sample size
		 */

		if (merge) {
			// set the rate before the first record...first record could be an
			// annotation
			// List waveSigs = new LinkedList<>();
			// List simpleSigs = new LinkedList<>();
			Integer max_rate = null;

			Set<String> keys = dev_signals.keySet();
			for (String key : keys) {
				List ss = dev_signals.get(key);
				for (Object o : ss) {
					PLayer layer = (PLayer)o;
					RpMetric sig = (RpMetric)layer.getAttribute("sig");
					Integer rate = sig.getSampleRate();
					if (rate == null || rate == 0) {
						// simpleSigs.add(sig);
					} else {
						// waveSigs.add(sig);
						max_rate = (max_rate == null) ? rate : Math.max(max_rate, rate);
					}
				}
			}

			if (max_rate != null && max_rate > 0) {
				int mss = 1000 / max_rate;
				if (exporter instanceof ExcelExporter) {
					ExcelExporter xls_exporter = (ExcelExporter) exporter;
					xls_exporter.setInterval(mss);
				} else if (exporter instanceof PiDreExporter) {
					PiDreExporter dre_exporter = (PiDreExporter) exporter;
					log.error("FIXME: ??dre_exporter.setInterval(mss);");
				} else {
					log.error("FIXME: set exporter tm interval?");
				}
			}
		}

		long tm0 = 0; // debug

		StreamID sid = null;
		while ((block = importer.next()) != null && !stop_export) {
			long tm = block.getTime();

			if (tm < tm0) {
				log.error("INTERNAL SEQ ERROR");
			}
			tm0 = tm;

			if (tm < clipStartMs) {
				Date dtCurr = new Date(tm);
				Date dtStart = new Date(clipStartMs);
				log.error("unexpected packet before time range: {} < {}", dtCurr, dtStart);
				// continue;
			}
			if (tm > clipEndMs) {
				break;
			}

			// stream-id does not matter for a merged export
			if (!merge) {
				int s_code = block.getStreamID();
				sid = StreamID.fromCode(s_code);
			}
			exporter.streamEvent(0, importer, sid, block);

			setClientCurrentProgress((int) ((tm - clipStartMs) / 1000));

		}

	}

	private void setClientMaxProgress(int maxProgress) {
		int oldValue = this.maxProgress;
		this.maxProgress = maxProgress;
		pcs.firePropertyChange(PNAME_MAX_PROGRESS, oldValue, this.maxProgress);
	}

	private void setClientCurrentProgress(int currentProgress) {
		int oldValue = this.currentProgress;
		this.currentProgress = currentProgress;
		pcs.firePropertyChange(PNAME_CURRENT_PROGRESS, oldValue, this.currentProgress);
	}

	private void setClientCurrentDevice(String name) {
		String oldValue = this.currentDevice;
		this.currentDevice = name;
		pcs.firePropertyChange(PNAME_CURRENT_DEVICE, oldValue, this.currentDevice);
	}

	@Deprecated
	private void exportAllDevices(PiSubjectExporter dest) throws IOException {

		PiDatastreamImporter[] devs = importer.getDevices();
		int dev_num = 0;

		for (PiDatastreamImporter dev : devs) {
			String fname = dev.getName();
			if (fname == null) {
				dev_num++;
				fname = "DevX" + dev_num;
			}

			List<? extends RpMetric> signals = dev_signals.get(fname);
			if (signals != null) {
				List waveSigs = new LinkedList<>();
				List simpleSigs = new LinkedList<>();

				for (RpMetric sig : signals) {
					Integer rate = sig.getSampleRate();
					if (rate == null || rate == 0) {
						simpleSigs.add(sig);
					} else {
						waveSigs.add(sig);
					}
				}

				exportOneDevice(dest, dev, waveSigs, simpleSigs);
			}
		}

	}

	@Deprecated
	private void exportOneDevice(PiSubjectExporter dest, PiDatastreamImporter src, List waveSigs, List simpleSigs)
			throws IOException {

		if (waveSigs.size() > 0) {

			if (dest instanceof ExcelExporter) {
				int max_frequency = 0;
				for (Object o : waveSigs) {
					RpMetric wave = (RpMetric) o;
					int sample_rate = wave.getSampleRate();
					if (sample_rate > max_frequency) {
						max_frequency = sample_rate;
					}
				}
				ExcelExporter xx = (ExcelExporter) dest;
				xx.setInterval(1000 / max_frequency);
			}

			src.seek(clipStartMs);
			exportWaves(dest, src, waveSigs);
		}

		if (simpleSigs.size() > 0) {
			if (dest instanceof ExcelExporter) {
				ExcelExporter xx = (ExcelExporter) dest;
				xx.setInterval(0);
			}
			src.seek(clipStartMs);
			doSimpleExport(src);
		}

	}

	@Deprecated
	private void exportWaves(PiSubjectExporter dest, PiDatastreamImporter src, List<? extends RpMetric> signals)
			throws IOException {

		PersistentItem block;

		// Is this supposed to work...??...is this a feature???
		// -- using alternate method: call dest.streameEvent() directly
		//
		// dev.addStreamListener(StreamID.WAVEFORM, dest);
		while ((block = src.next()) != null && !stop_export) {

			long tm = block.getTime();

			if (tm > clipEndMs) {
				break;
			}
			System.out.println("dt=" + block.getTm());

			dest.streamEvent(0, src, StreamID.WAVEFORM, block); // export
																// waveforms

			setClientCurrentProgress((int) ((tm - clipStartMs) / 1000));
		}

	}

	public void setSignals(Map dev_signals) {
		this.dev_signals = dev_signals;
	}

	/*
	 * boilerplate code
	 */
	public void addPropertyChangeListener(PropertyChangeListener listener) {
		this.pcs.addPropertyChangeListener(listener);
	}

	public void removePropertyChangeListener(PropertyChangeListener listener) {
		this.pcs.removePropertyChangeListener(listener);
	}

	/*
	 * If the importer is a COMPOSITE for multipe subjects, we probably still want
	 * the output to go into seperate files for each subject....with the subject id
	 * in the output file name.
	 */
	public void subjectChange(String newValue) {
		System.setProperty("SUBJECT", newValue);
		System.setProperty("Subject", newValue);

		if (is_connected) {
			try {
				exporter.disconnect();
				exporter.connect();
			} catch (IOException e) {
				log.error("subject change error");
			}
		}

	}

	public void setMergeOption(boolean mergeOption) {
		this.merge = mergeOption;
	}

	public void setHeader(RpSubject header) {
		this.header = header;
	}

}
