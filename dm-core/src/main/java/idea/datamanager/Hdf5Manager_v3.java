package idea.datamanager;

import java.io.File;
import java.io.IOException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import icuInterface.PlatformUtil;
import icuInterface.message.AbstractItem;
import icuInterface.message.NumericBlock;
import idea.conf.DeviceConfiguration;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectExporter;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.PiHdf5Importer;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class Hdf5Manager_v3 implements PiSubjectExporter {
	Calendar cal = Calendar.getInstance();
	Calendar trend_cal = Calendar.getInstance();
	HashMap<String, Integer> trend_minhash = new HashMap<String, Integer>();
	HashMap<String, String> trend_lochash = new HashMap<String, String>();

	List<PiHdf5Importer> importers = new LinkedList<PiHdf5Importer>();
	PiHdf5Exporter exporter;

	// PiHdf5Exporter rt_importer;
	private File dir;

	private long curr_tm = -1;
	private long end_tm = -1;

	private int tick = TICK_MODULUS;

	public static int MAX_DATA_AGE_DAYS = 14; // default of two weeks

	public final static int TICK_MODULUS = 10;
	public final static DateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	public static long MIN_FREE_MB = 100;

	int verbose = 1;
	File h5_export_file = null;

	public Hdf5Manager_v3(File dir) {

		this.dir = dir;
		this.exporter = new PiHdf5Exporter();

		File[] files = dir.listFiles();
		for (File file : files) {
			String name = file.getName();
			if (name.endsWith("h5")) {
				addImporter(file);
			}
		}

		// BETA2: order the importers in chronological order...maybe this works?
		Collections.sort(importers, new Comparator<PiHdf5Importer>() {

			@Override
			public int compare(PiHdf5Importer o1, PiHdf5Importer o2) {
				int comp = 0;
				try {
					ArchiveMetaData meta1 = o1.getMetaData();
					ArchiveMetaData meta2 = o2.getMetaData();
					if (meta1 != null && meta2 != null) {
						Date start1 = meta1.getStartTime();
						Date start2 = meta1.getStartTime();
						if (start1 != null && start2 != null) {
							comp = start1.compareTo(start2);
						}
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				return comp;
			}
		});

		if (log.isDebugEnabled()) {
			for (PiHdf5Importer importer : importers) {
				log.debug(" importer file={}", importer.getFile());
			}

		}

	}

	private void addImporter(File file) {
		PiHdf5Importer importer = new PiHdf5Importer(file);
		try {
			importer.connect();
			importers.add(importer);
		} catch (Exception e) {
			log.error("REMOVING FILE/COULD NOT OPEN: " + file);
			file.delete();
		}
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		System.out.print("*");
		synchronized (exporter) {
			exporter.streamEvent(jobID, source, sid, item);
		}
	}

	@Override
	public void setHeader(RpSubject header) {
		synchronized (exporter) {
			exporter.setHeader(header);
		}
	}

	@Override
	public void setDestination(File archiveDir) {
		synchronized (exporter) {
			exporter.setDestination(archiveDir);
		}
	}

	@Override
	public void connect() throws IOException {
		log.debug("manager connecting: TM={}", curr_tm);

		if (curr_tm < 0) {
			// allows time to be set externally...used for reprocessing
			// existing data and breaking datafile into chunks
			Calendar cal = Calendar.getInstance();
			curr_tm = cal.getTimeInMillis();

			log.debug("manager curr TM={}", curr_tm);
		} else {
			// this might cause a problem for JAMVM
			cal.setTimeInMillis(curr_tm);
		}

		String suffix = ".h5";
		int idx = 0;
		while (true) {
			String fname = sdf.format(cal.getTime());
			fname = fname.split(" ")[0]; // THIS IS A JAMVM WORKAROUND
			fname += suffix;

			h5_export_file = new File(dir, fname);
			if (h5_export_file.exists()) {
				idx++;
				suffix = "-" + idx + ".h5";
				log.info("h5 exists: {}", h5_export_file);
				continue;
			}
			break;
		}
		log.debug("creating file: {}", h5_export_file);
		exporter.setFile(h5_export_file);
		exporter.connect();

		log.debug("connected: {} exporter={}", h5_export_file, exporter);

		//rt_importer = new PiHdf5Exporter( exporter.getHdf5FileId() );
		//importers.add( rt_importer );

		if (PlatformUtil.isJAMVM()) {
			String s;
			// DateFormat df = new SimpleDateFormat("yyyy-MM-dd");

			// log.debug( "JAMVM TIME: {}", sdf.format( new Date(cal.getTimeInMillis() )));
			cal.add(Calendar.DAY_OF_YEAR, 1);
			end_tm = cal.getTimeInMillis();
			s = sdf.format(new Date(end_tm));
			// log.debug( "JAMVM LONG TOMORROW: {} TM={}", s, end_tm );
			s = s.split(" ")[0];
			s += " 00:00:01";
			// BUG JAMVM is rounding DOWN????
			// s = df.format( new Date( end_tm ));
			// log.debug( "JAMVM SHORT TOMORROW: {}", s );

			try {
				end_tm = sdf.parse(s).getTime();
				log.debug("JAMVM DUE: {} FOR TM={}", sdf.format(new Date(end_tm)), end_tm);
			} catch (ParseException e) {
				// THIS CANNOT FAIL!!!!
				e.printStackTrace();
				log.error("INTERNAL DATE PARSE ERROR???", e);
			}
		} else {
			log.debug("JAMVM = {}", PlatformUtil.isJAMVM());
			cal.set(Calendar.MILLISECOND, 0);
			cal.set(Calendar.HOUR_OF_DAY, 0);
			cal.set(Calendar.MINUTE, 0);
			cal.set(Calendar.SECOND, 0);
			cal.add(Calendar.DATE, 1);
			end_tm = cal.getTimeInMillis();

			log.debug("END_TM not JAMVM");
		}

		if (log.isDebugEnabled()) {
			log.debug("ROTATE due: {}", sdf.format(new Date(end_tm)));
		}
	}

	public void addTrendLoc(String cl, String loc) {
		// trend_lochash.put( cl, loc );
	}

	private boolean check_trend(DeviceConfiguration conf, boolean isSettings, NumericBlock block) {
		boolean ok = false;

		String cl = conf.getDeviceClass();
		String loc = trend_lochash.get(cl);

		String trend_key = conf.getName();
		if (isSettings) {
			trend_key += ".S";
		}

		if (loc != null) {
			Object val = null;
			AbstractItem item = block.getItem(loc);
			if (item != null) {
				val = item.getValue();
			}
			trend_key = trend_key + "." + val;
		}

		trend_cal.setTimeInMillis(block.getTime());
		int min = trend_cal.get(Calendar.MINUTE);

		Integer last_min = trend_minhash.get(trend_key);
		if (last_min == null || last_min != min) {
			trend_minhash.put(trend_key, min);
			ok = true;
		}

		return ok;
	}

	void rotate(long tm) throws IOException {

		if (log.isDebugEnabled()) {
			log.debug("Checking ROTATE: now={}  due={}", sdf.format(new Date(tm)), sdf.format(new Date(end_tm)));
		}

		synchronized (exporter) {
			curr_tm = tm;
			if (tm > end_tm) {
				cal.setTimeInMillis(curr_tm);
				if (exporter != null) {
					disconnect();
					addImporter(h5_export_file); // must do this before connecting to new file
				}
				connect();
				log.info("ROTATE complete.  fid={} exporter={}", exporter.getHdf5FileId(), exporter);
			}
		}
	}


	@Override
	public void disconnect() throws IOException {
		log.warn("Manager is DISCONNECTING");
		exporter.disconnect();
	}

	@Override
	public void addDevice(RpDevice conf) throws IOException {
		synchronized (exporter) {
			exporter.addDevice(conf);
		}
	}

	public void tick() {
		tick++;
		if (tick > TICK_MODULUS) {
			checkFreeSpace();
			checkDataAge();
			try {
				Calendar cal = Calendar.getInstance();
				rotate(cal.getTimeInMillis()); // aka rollover
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			tick = 0;
			if (verbose > 0) {
				verbose--;
			}

		}
	}

	private void checkDataAge() {

		long curr_ms = PlatformUtil.currentTimeMillis();
		if (log.isDebugEnabled()) {
			log.debug("CHECK DATA AGE: {} MAX={}", sdf.format(new Date(curr_ms)), MAX_DATA_AGE_DAYS);
		}

		// for JAMVM, we need to avoid Calendar.add(), tz confused?
		long delta = MAX_DATA_AGE_DAYS * 24 * 60 * 60 * 1000;
		long oldest_ms = curr_ms - delta;

		java.util.Iterator<PiHdf5Importer> ii = importers.iterator();
		while (ii.hasNext()) {
			PiHdf5Importer importer = ii.next();
			ArchiveMetaData meta = null;

			// log.debug("Checking importer: {}", importer.getFile() );

			try {
				if ((importer == null) // bad importer
						|| ((meta = importer.getMetaData()) == null) // no meta
						|| meta.getStartTime() == null // no start time
				) {
					log.warn("INVALID IMPORTER HAS NO DATES: ", importer.getFile());
					ii.remove();
					if (importer != null) {
						try {
							importer.disconnect();
						} catch (Exception ignore) {

						} finally {
							File f = importer.getFile();
							if (f == null) {
								// file is null if this is the importer tied to the exporter.
							} else {
								try {
									log.error("REMOVING UNREADABLE: {}", f);
									f.delete();
								} catch (Exception e) {
									log.error("COULD NOT REMOVE FILE: " + f, e);
								}
							}
						}
					}
					continue;
				}

				long file_ms = meta.getStartTime().getTime();
				delta = file_ms - oldest_ms;
				int delta_sec = (int) (delta / 1000);

				if (log.isDebugEnabled()) {
					int delta_hr = delta_sec / 3600;
					log.debug("Checking: {} delta: {} hr startdt=" + //
							sdf.format(meta.getStartTime()), //
							importer.getFile().getName(), //
							delta_hr);
				}

				if (delta_sec < 0) { // file_ms < oldest_ms ) {
					importer.disconnect();
					ii.remove();

					File file = importer.getFile();

					log.warn("removing old file: {}", file);
					if (file != null) {
						file.delete();
					}
				}

			} catch (IOException e) {
				log.error("Parsing importers: ", e);
			}

		}
	}

	private void checkFreeSpace() {
		
		File ref_file = dir;
		if( ref_file == null ) {
			ref_file = new File("/var/sda");
		}
		long freeSpace = ref_file.getFreeSpace(); //unallocated / free disk space in bytes.

		freeSpace /= (1024 * 1024); // in megabytes

		log.debug("free space: {}M", freeSpace);
		if (freeSpace < MIN_FREE_MB) {
			PiHdf5Importer oldest;
			try {
				log.warn("getting oldest file");
				oldest = findOldestFile();
				if (oldest != null) {
					oldest.disconnect();
					importers.remove(oldest);
					File f = oldest.getFile();
					f.delete();
					log.warn("deleting oldest file: {}", f);
				}
			} catch (Exception e) {
				log.warn("ERR GETTING OLDEST FILE", e);
			}
		}

	}

	private PiHdf5Importer findOldestFile() throws IOException {
		Date totStart = null;
		PiHdf5Importer found = null;
		for (PiHdf5Importer importer : importers) {
			ArchiveMetaData meta = importer.getMetaData();
			Date oneStart = meta.getStartTime();
			if (totStart == null || oneStart.getTime() < totStart.getTime()) {
				totStart = oneStart;
				found = importer;
			}
		}

		return found;
	}

	public List<PiHdf5Importer> getImporters() {

		return importers;
	}

	public void purge() throws IOException {
		synchronized (importers) {
			Iterator<PiHdf5Importer> ii = importers.iterator();
			while (ii.hasNext()) {
				PiHdf5Importer importer = ii.next();
				File f = importer.getFile();
				importer.disconnect();
				if (f != null) {
					f.delete();
				}
				ii.remove();
			}
		}

		synchronized (exporter) {
			try {
				exporter.disconnect();

				File f = exporter.getFile();
				f.delete();

				// reconnect
				curr_tm = -1;
				connect();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

	public PiHdf5Exporter getExporter() {
		return exporter;
	}

	public PiHdf5Importer getImporter(long tsStart) throws IOException {
		PiHdf5Importer found = null;
		long best_diff = -1;

		if (log.isDebugEnabled()) {
			log.debug("looking for importer: {}", new Date(tsStart));
		}

		synchronized (importers) {
			Iterator<PiHdf5Importer> ii = importers.iterator();
			while (ii.hasNext()) {
				PiHdf5Importer importer = ii.next();
				ArchiveMetaData meta;
				try {
					meta = importer.getMetaData();
					long metaStart = meta.getStartTime().getTime();
					long metaEnd = meta.getStopTime().getTime();

					if (metaEnd < metaStart) {
						log.error(" invalid metaend?");
					}

					long diff = tsStart - metaStart;
					log.debug("checking date: {} to {} diff=" + diff, meta.getStartTime(), meta.getStopTime());

					if (metaEnd < tsStart || diff < 0) {
						// ignore...ended before point of interest
					} else {

						if (best_diff == -1 || diff < best_diff) {
							best_diff = diff;
							found = importer;
						}

					}
				} catch (Exception e) {
					log.error("interrupt while looking for metadata in " + importer.getFile(), e);
				}
			}
		}

		log.info("found=" + found);
		if (found != null) {
			found.seek(tsStart);
		}
		return found;
	}

	public PiHdf5Importer[] getImporters(long tsStart, long tsEnd, DeviceConfiguration conf) throws IOException {
		List<PiHdf5Importer> found = new LinkedList<PiHdf5Importer>();

		if (tsEnd <= 0) {
			Calendar cal = Calendar.getInstance();
			tsEnd = cal.getTimeInMillis();
		}

		if (log.isDebugEnabled()) {
			log.debug("GET importers: {} to {}", new Date(tsStart), new Date(tsEnd));
		}

		synchronized (importers) {
			Iterator<PiHdf5Importer> ii = importers.iterator();
			while (ii.hasNext()) {
				PiHdf5Importer importer = ii.next();
				ArchiveMetaData meta;
				try {
					meta = importer.getMetaData();
					long metaStart = meta.getStartTime().getTime();
					long metaEnd = meta.getStopTime().getTime();

					if (metaEnd < metaStart) {
						log.error(" invalid metaend?");
					}

					// long diff = tsStart - metaStart;

					if (metaEnd < tsStart || metaStart > tsEnd) {
						// ends before our point of interest, or starts after our last point of interest
						// ignore
						// log.debug("skipping importer: {} to {}", meta.getStartTime(), meta.getStopTime());
					} else {
						importer.setFilter(conf);
						importer.seek(tsStart);
						found.add(importer);
						log.debug("inserting importer: {} to {}", meta.getStartTime(), meta.getStopTime());
					}
				} catch (Exception e) {
					log.error("interrupt while looking for metadata in " + importer.getFile(), e);
				}
			}
		}

		if (log.isDebugEnabled()) {
			log.debug("GOT importer count: {}", found.size());
		}
		
		// log.info("found size=" + found.size() );
		if (found.size() == 0) {
			return null;
		}

		PiHdf5Importer[] ar = new PiHdf5Importer[found.size()];
		found.toArray(ar);

		return ar;
	}

//	@Override
//	public void monitorEvent(MonitorEvent event) {
//		ConnectionStatus stat = event.getStat();
//		AdapterInterface driver = event.getDriver();
//		if (stat == ConnectionStatus.CONNECTED || stat == ConnectionStatus.CONNECTING) {
//			driver.addEventListener(null, exporter);
//		} else if (stat == ConnectionStatus.NOT_CONNECTED) {
//			driver.removeEventListener(exporter);
//		} else {
//			log.error("unknown monitor event: {} for {}", stat, driver);
//		}
//	}

//	public void setCurrentTime(long curr_tm) {
//		// this is used for rebuilding datafiles
//		this.curr_tm = curr_tm;
//	}

//	public boolean contains_exporter(String name) {
//		return exporter.contains_exporter(name);
//	}

}
