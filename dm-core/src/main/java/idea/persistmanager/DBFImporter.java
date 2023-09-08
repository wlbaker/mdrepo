/**
 * This package supports the HSE software: Harvard Apparatus inspiratory measurement system.
 * 
 */

package idea.persistmanager;
 

import java.io.File;
import java.io.IOException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;

import icuInterface.PlatformUtil;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistence.PiDatastreamImporter;
import idea.persistmanager.dbf.DBFTableReader;
import idea.persistmanager.dbf.RAWReader;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DBFImporter extends AbstractStreamProducer implements PiSubjectImporter {

	private PersistentItem[] arNext = null;

	private LinkedList<PiDatastreamImporter> importers;

	private RpSubject header;

	boolean readOnly;

	private ArchiveMetaData meta;

	private File file;

	private boolean isConnected;

	private DeviceConfiguration filter;

	public DBFImporter(File file) {
		this(file, true);
	}

	public DBFImporter(File file, boolean readOnly) {
		assert (file.isDirectory() == true) : "HSE uses a directory as its base.";
		this.file = file;
		this.readOnly = readOnly;
	}

	public File getFile() {
		return file;
	}

	@Override
	public void connect() throws IOException {

		if (isConnected) {
			disconnect();
		}
		isConnected = true;
		arNext = null;

		importers = new LinkedList<PiDatastreamImporter>();
		for (File f : file.listFiles()) {
			String name = f.getName();
			if (name.endsWith("DBF")) {
				DBFTableReader importer = new DBFTableReader(f);
				importers.add(importer);
			}
			if (name.equals("TRACK_1.RAW")) {
				RAWReader importer = new RAWReader(f, "HARDWARE.INI", "CALIB.DAT");
				importers.add(importer);
			} else {
				log.debug("Ignoring file: {}", f);
			}
		}

		Iterator<PiDatastreamImporter> ii = importers.iterator();
		while (ii.hasNext()) {
			PiDatastreamImporter importer = ii.next();
			try {
				importer.connect();
			} catch (Exception e) {
				log.error("Error connecting importer: {}", importer, e);

				ii.remove();
			}
		}
		
		

		PiDatastreamImporter logfile = getDatastreamImporter("LOGFILE", null);
		if (logfile != null) {
			try {
				Date start = parseMetaLogfile(logfile);
				meta = new ArchiveMetaData();
				meta.setStartTime( start );
				
				
				
				for( PiDatastreamImporter importer : importers) {
					if( importer instanceof DBFTableReader ) {
						DBFTableReader dbf = (DBFTableReader) importer;
						dbf.setStartTime( start );
					} else if (importer instanceof RAWReader ) {
						RAWReader raw = (RAWReader) importer;
						raw.setStartTime( start );
					}
				}

			} catch( Exception e ) {
				// ignore
				log.error("Could not parse logfile for meta info.", e);
			}
		}
		
		readHeader();  // depends on the log file already having been parsed
	}

	private Date parseMetaLogfile(PiDatastreamImporter logfile) throws IOException, ParseException {
		
		Date startDate = null;
		Date startTime = null;
		
		DateFormat dt = new SimpleDateFormat("MM/dd/yyyy");
		DateFormat tm = new SimpleDateFormat("hh:mm:ss a");
		
		Date zero = tm.parse("00:00:00 AM");  // used for timezone adjustment
		
		do {
			PersistentItem item = logfile.next();
			if (item == null)
				break;

			String val = (String)IntfUtil.getRawValueByLoc(item, "Desc");
			System.out.println("SET METADATA: " + val );
			if( val != null ) {
				int idx = val.indexOf(':');
				if(idx < 0 ) {
					log.error("Unexpect LOGFILE data: {}", val);
					continue;  // don't know how to handle this record
				}
				String k = val.substring(0,idx).trim();
				String v = val.substring(idx+1).trim();
				
				if( "Startdate".equalsIgnoreCase(k)) {
					startDate = dt.parse(v);
				} else if( "Starttime".equalsIgnoreCase(k)) {
					startTime = tm.parse(v);
				} else {
					log.error("Unexpect LOGFILE data: {}", val);
				}
			}

		} while (true);
		
		if( startDate != null && startTime != null ) {
			System.out.println("FIXME META START: " + startDate + " tm=" + startTime );
		}
		
		// must subtract TZ offset...otherwise we will add it in twice
		Date metaStart = new Date( startDate.getTime() + startTime.getTime() - zero.getTime() );
		
		System.out.println("meta start=" + metaStart);
		return metaStart;
	}

	private void readHeader() throws IOException {
		// this is in a file called STUDYPAR.DBF,
		// but I don't need it and it's not particularly useful
		header = new RpSubject();
		header.setNotes("HSE");
		if( meta != null ) {
			header.setSurgeryDate( meta.getStartTime() );
		}
		
		return;

	}

	@Override
	public void disconnect() {

		if (importers != null) {
			for (PiDatastreamImporter dev : importers) {
				try {
					dev.disconnect();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}

		isConnected = false;
	}

	@Override
	public long getTimeInMillis() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public PersistentItem next() throws IOException {
		PersistentItem block;

		synchronized (importers) {
			block = _next();
		}

		return block;
	}

	public PersistentItem _next() throws IOException {

		if (arNext == null) {
			arNext = new PersistentItem[importers.size()];

			for (int idx = 0; idx < importers.size(); idx++) {
				PiDatastreamImporter importer = importers.get(idx);

				if (filter != null && checkFilter(importer) == false) {
					continue; // skip this device
				}
				try {
					arNext[idx] = importer.next();
				} catch (IOException e) {
					throw e;
				} catch (Exception e) {
					throw new IOException(e);
				}
			}
		}

		PersistentItem ret = null;
		long nextTime = Long.MAX_VALUE;
		int nextPos = 0;
		for (int idx = 0; idx < arNext.length; idx++) {
			PersistentItem m = arNext[idx];
			if (m != null && m.getTime() < nextTime) {
				nextPos = idx;
				nextTime = m.getTime();
				ret = m;
			}
		}

		try {
			if (ret != null) { // if ret is null, then all the importers are out
				// of messages
				PiDatastreamImporter importer = importers.get(nextPos);
				if (importer != null) {
					try {
						arNext[nextPos] = importer.next();
					} catch (NullPointerException nex) {
						nex.printStackTrace();
					}
				}
			}
		} catch (IOException e) {
			throw e;
		} catch (Exception e) {
			throw new IOException(e);
		}

		return ret;
	}

	private boolean checkFilter(PiDatastreamImporter importer) {

		String name = importer.getName();
		String fname = filter.getName();
		if (name == null || fname == null) {
			log.error("FILTER NAME/FNAME IS NULL: {}/{}", name, fname);
			return false;
		}

		// BETA2: this is not the way to do this!!!! FIXME: Do it a different way!
		if (name.equals(fname) || name.startsWith(fname) || fname.startsWith(name)) {
			log.debug("accepting: {} filter={}", name, fname);
			return true;
		}
		log.debug("skipping: {} filter={}", name, fname);
		return false;
	}

	@Override
	public RpSubject getSubjectInfo() {
		return header;
	}

	public PiDatastreamImporter getImporter(int deviceIdx) {
		PiDatastreamImporter device = importers.get(deviceIdx);

		return device;
	}

	public PiDatastreamImporter[] getDevices() {
		if (importers == null || importers.size() == 0) {
			return null;
		}

		PiDatastreamImporter[] devices;
		synchronized (importers) {
			devices = new PiDatastreamImporter[importers.size()];

			devices = importers.toArray(devices);
		}
		return devices;
	}

	/**
	 * H5 specific routine to get a device, consisting of one importer/stream.
	 * Can also get a top-level dataset importer, such as annotations.
	 */
	public PiDatastreamImporter getDevice(String name) {
		PiDatastreamImporter found = null;
		for (PiDatastreamImporter importer : importers) {
			if (name.equals(importer.getName())) {
				found = (PiDatastreamImporter) importer;
				break;
			}
		}
		return found;
	}

	@Override
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid) {
		PiDatastreamImporter found = null;
		if (importers == null || importers.size() == 0) {
			return null;
		}

		for (PiDatastreamImporter importer : importers) {
			if (name.equals(importer.getName())) {
				found = importer;
				break;
			}
		}

		if (found == null && sid != null) {
			for (PiDatastreamImporter importer : importers) {
				for (StreamID sss : importer.getStreams()) {
					if (sid.equals(sss)) {
						found = importer;
						break;
					}
				}
			}
		}

		return found;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArchiveMetaData getMetaData() throws IOException {

		return meta;
	}

	private void merge(ArchiveMetaData meta, ArchiveMetaData metaDev) {

		if (meta.getStartTime() == null)
			meta.setStartTime(metaDev.getStartTime());
		if (meta.getStopTime() == null)
			meta.setStopTime(metaDev.getStopTime());

		if (metaDev.getStartTime() != null) {
			if (meta.getStartTime().getTime() > metaDev.getStartTime().getTime()) {
				meta.setStartTime(metaDev.getStartTime());
			}
		}

		if (metaDev.getStopTime() != null) {
			if (meta.getStopTime().getTime() < metaDev.getStopTime().getTime()) {
				meta.setStopTime(metaDev.getStopTime());
			}
		}

	}

	@Override
	public void rewind() throws IOException {
		synchronized (importers) {
			for (PiDatastreamImporter dev : getDevices()) {
				dev.rewind();
			}
		}

	}

	/*
	 * filters should be applied (or removed) before calling seek to reduce seek overhead
	 */

	@Override
	public void seek(long startTime) throws IOException {

		synchronized (importers) {

			long start = 0;
			if (log.isDebugEnabled()) {
				start = PlatformUtil.currentTimeMillis();
			}
			for (PiDatastreamImporter dev : importers) {

				if (filter != null && checkFilter(dev) == false) {
					// skip this importer
				} else {
					dev.seek(startTime);
					if (log.isDebugEnabled()) {
						long dt = PlatformUtil.currentTimeMillis() - start;
						log.debug("SEEK D-TIME: {} for {}", dt, dev.getName());
					}
				}
			}

			arNext = null;
		}
	}

	public PiDatastreamImporter getDatasetImporter(String name) {
		PiDatastreamImporter found = null;
		for (PiDatastreamImporter importer : importers) {
			if (name.equals(importer.getName())) {
				found = importer;
				break;
			}
		}

		return found;
	}

	public void setFilter(DeviceConfiguration conf) {

		/*
		 * filters should be applied or removed before calling seek to reduce seek overhead
		 */
		this.filter = conf;
	}

	public void skip(int count) {
		for (int idx = 0; idx < importers.size(); idx++) {
			PiDatastreamImporter importer = importers.get(idx);

			if (filter != null && checkFilter(importer) == false) {
				continue; // skip this device
			}

			log.error("SKIP disabled 03-24-2014");
		}

	}

	public static void main(String[] argv) throws IOException {

		System.out.println("CURRTIME=" + System.currentTimeMillis());
		//		File f = new File("/opt/study/hse/checked MSC/Pig_3061/EXP_DATA_Pig_3061_BL_PV/DATA.DBF");
		//		File f = new File("/opt/study/hse/checked MSC/Pig_3144/EXP_DATA_Pig_3144_BL_PV");
		File dir = new File("/opt/study/data-HSE/HSE/DATA/MSC/Pig_3486/EXP_DATA_Pig_3486_BL");
		DBFImporter importer = new DBFImporter(dir);
		importer.connect();
		PiDatastreamImporter cursor = importer.getDatasetImporter("CURSOR");
		do {

			PersistentItem item = cursor.next();
			if (item == null)
				break;
			System.out.println("got cursor: " + item);
		} while (true);

		PiDatastreamImporter raw = importer.getDatasetImporter("TRACK_1");
		do {

			PersistentItem item = raw.next();
			if (item == null)
				break;
			System.out.println("got track record: " + item);
		} while (true);

		importer.disconnect();
	}

}
