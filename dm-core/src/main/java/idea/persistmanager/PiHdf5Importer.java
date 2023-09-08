package idea.persistmanager;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;

import static hdf.hdf5lib.HDF5Constants.*;
import hdf.hdf5lib.callbacks.H5A_iterate_cb;
import hdf.hdf5lib.callbacks.H5A_iterate_t;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import hdf.hdf5lib.structs.H5A_info_t;
import hdf.hdf5lib.structs.H5O_info_t;
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
import idea.persistmanager.hdf5.DatasetImporter;
import idea.persistmanager.hdf5.H5GroupImporter;
import idea.persistmanager.hdf5.H5Util;
import idea.persistmanager.hdf5.ImportHeader;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

// BETA2: FIXME: allow_simultaneous_importers

@Slf4j
public class PiHdf5Importer extends AbstractStreamProducer implements PiSubjectImporter {

	private static final boolean ALLOW_SIMULTANEOUS_IMPORTERS = false;

	// private String fileName;

	// private WaveformBlock nextWave;
	// private NumericsBlock nextNumerics;
	private PersistentItem[] arNext = null;

	PiDatastreamImporter tranlog;

	private LinkedList<PiDatastreamImporter> importers;

	private RpSubject header;

	long file_id = -1;
	boolean readOnly;
	private static int verbose = 3;

	// H5WithMeta curr;

	private boolean ownFID;

	private ArchiveMetaData meta;

	private File file;

	private boolean isConnected;

	private DeviceConfiguration filter;

	private int file_version;

	public PiHdf5Importer(File f) {
		this(f, true);
	}

	public PiHdf5Importer(File file, boolean readOnly) {
		assert (file.isDirectory() == false) : "Composite imports handled by Hdf5CompositeImport class!";
		this.file = file;
		this.readOnly = readOnly;
		ownFID = true;
	}

	public PiHdf5Importer(long hdf5FileId) {
		this.file_id = hdf5FileId;
		this.readOnly = false;
		ownFID = false;
	}

	@Override
	public void connect() throws IOException {

		if (isConnected) {
			disconnect();
		}
		isConnected = true;
		try {
			arNext = null;

			_connect(file, readOnly);

		} catch (IOException e) {
			throw e;
		} catch (Exception e) {
			throw (new IOException(e));
		}

	}

	public File getFile() {
		return file;
	}

//	class H5A_iter_callbackT implements H5A_iterate_cb {
//
//		@Override
//		public int callback(long group_id, String name, H5A_info_t info, H5A_iterate_t op) {
//			opdata_At opdata = (opdata_At) op;
//
//			H5O_info_t infobuf; // the input info does not have the type field populated (correctly)
//			try {
//				infobuf = H5.H5Oget_info_by_name(group_id, name, H5P_DEFAULT);
//					log.info("  Group: {}", infobuf.hdr.);
//					log.info("  Dataset: {}", name);
//			} catch (HDF5LibraryException | NullPointerException e1) {
//				// TODO Auto-generated catch block
//				log.error("Failed to get H5 data type", e1);
//			}
//
//			return 0;
//		}
//
//	}
//

	private void _connect(File f, boolean readOnly) throws NullPointerException, HDF5Exception, IOException {

		if (ownFID) {
			file_id = open(f, readOnly);
		} else {
			// file already open, perhaps by exporter
		}


		file_version = H5Util.readIntAttribute(file_id, "fileVersion");
		readHeader();

		importers = H5Util.readDatasetsFromGroup(file_id, file_version, null, null);
		tranlog = H5Util.getDatasetFromName(importers, "tranlog");

		Iterator<PiDatastreamImporter> ii = importers.iterator();
		while (ii.hasNext()) {
			PiDatastreamImporter importer = ii.next();
			try {
				importer.connect();
			} catch (Exception e) {
				log.error("HDF5 removing importer: {}", importer, e);

				ii.remove();
			}
		}

	}

	private void readHeader() throws NullPointerException, HDF5Exception, IOException {
		ImportHeader reader = null;
		try {
			reader = new ImportHeader(file_id);
			reader.connect();
			this.header = reader.next();
			reader.disconnect();
		} catch (Exception notfound) {
			// not an error
		}

		return;

	}

	private static long open(File f, boolean readOnly) throws HDF5LibraryException, NullPointerException {

		int accMode = (readOnly) ? HDF5Constants.H5F_ACC_RDONLY : HDF5Constants.H5F_ACC_RDWR;

		String fileName = f.getAbsolutePath();

		return H5.H5Fopen(fileName, accMode, HDF5Constants.H5P_DEFAULT);

	}

	@Override
	public void disconnect() {

		if (file_id < 0) {
			log.error("attempting to close already closed file?");
			return;
		}

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

		// Close the file.
		try {

			int post_count = (int) H5.H5Fget_obj_count(file_id, HDF5Constants.H5F_OBJ_ALL);

			if (file_id > 0 && ownFID) {
				if (!readOnly) {
					log.warn("importer disconnect flush");
					H5.H5Fflush(file_id, HDF5Constants.H5F_SCOPE_GLOBAL);
				}
				int err = H5.H5Fclose(file_id);
				if (err != 0) {
					log.error("Hdf5Importer H5Fclose err: {}", err);
				}
				file_id = -1;
			}

			if (post_count > 1) {
				int file_count = (int) H5.H5Fget_obj_count(file_id, HDF5Constants.H5F_OBJ_FILE);
				int dt_count = (int) H5.H5Fget_obj_count(file_id, HDF5Constants.H5F_OBJ_DATATYPE);
				int attr_count = (int) H5.H5Fget_obj_count(file_id, HDF5Constants.H5F_OBJ_ATTR);
				log.error("H5 DETECTED RESOURCE LEAK: " + post_count + "," + dt_count + "," + attr_count + ","
						+ file_count);
			}
			file_id = -1;
		} catch (HDF5LibraryException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
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

	public long getH5FileId() {
		return file_id;
	}

	public PiDatastreamImporter getImporter(int deviceIdx) {
		PiDatastreamImporter device = importers.get(deviceIdx);

		return device;
	}

	public PiDatastreamImporter[] getDevices() {
		if (importers == null) {
			return null;
		}

		PiDatastreamImporter[] devices = null;
		synchronized (importers) {
			int count = 0;
			for (PiDatastreamImporter dev : importers) {
				if (dev == null || dev == tranlog) {
					// ignore
				} else {
					count++;
				}
			}

			if (count > 0) {
				devices = new PiDatastreamImporter[count];

				int idx = 0;
				for (PiDatastreamImporter dev : importers) {
					if (dev == null || dev == tranlog) {
						// ignore
					} else {
						devices[idx++] = dev;
					}
				}
			}
		}
		return devices;
	}

	/**
	 * H5 specific routine to get a device, consisting of one importer/stream. Can
	 * also get a top-level dataset importer, such as annotations.
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

		log.debug("looking for importer: {}", name);
		
		found = findImporter( importers, name, sid );

		if (sid != null) {
			if (found instanceof H5GroupImporter) {
				H5GroupImporter group = (H5GroupImporter) found;
				found = group.getDatasetImporter(sid);
			} else if (found instanceof DatasetImporter) {
				DatasetImporter ds = (DatasetImporter) found;
				if (ds.getStreamID() != sid) {
					log.error("Dataset importer SID {} != {}", sid, ds.getStreamID());
					found = null;
				}
			}
		}

		return found;
	}

	private static PiDatastreamImporter findImporter(LinkedList<PiDatastreamImporter> importers, String name, StreamID sid) {
		
		String [] arr = name.split("/");
		int idx = 0;
		if( arr[idx].isEmpty() ) {
			idx++;
		}

		outer:
	    while(idx < arr.length ) {
	    	String seg = arr[idx++];
	        for(PiDatastreamImporter importer : importers ){
	        	if( name.equals(importer.getName() )) {
	        		return importer;
	        	}
				if (seg.equals(importer.getName()) ) {
					if( idx == arr.length ) {
						return importer;
					}
					// more segments to search...and yes, this could throw error
					H5GroupImporter grp = (H5GroupImporter)importer;
					
					// drill down another level
					importers = grp.getImporters();
					break;
				}
	        }
	    }
		return null;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArchiveMetaData getMetaData() throws IOException {

		if (meta == null) {
			meta = createMetaData();
		}
		return meta;
	}

	private ArchiveMetaData createMetaData() throws IOException {
		ArchiveMetaData meta_tot = new ArchiveMetaData();

		if (importers == null) {
			meta_tot.setStartTime(new Date()); // now, but no end time
			return meta_tot;
		}

		synchronized (importers) {
			for (PiDatastreamImporter importer : importers) {
				ArchiveMetaData meta = importer.getMeta();

				// meta will be null for header
				if (meta != null) {
					log.debug("hdf5Importer meta: {} end: ", meta.getStartTime(), meta.getStopTime());
					merge(meta_tot, meta);
				}

			}
		}

		return meta_tot;
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
	 * filters should be applied (or removed) before calling seek to reduce seek
	 * overhead
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

	public String readStringAttribute(String name) {
		String value = null;
		try {
			value = H5Util.readStringAttribute(file_id, name);
		} catch (Exception e) {
			// not found
		}
		return value;
	}

	public void setFilter(DeviceConfiguration conf) {

		/*
		 * filters should be applied or removed before calling seek to reduce seek
		 * overhead
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
			// if (importer instanceof H5GroupImporter) {
			// DatasetImporter metric_importer = ((H5GroupImporter)
			// importer).getMetricImporter();
			// if (metric_importer != null) {
			// metric_importer.skip(count);
			// }
			// }
		}

	}

	public int getFileVersion() {
		return file_version;
	}

}
