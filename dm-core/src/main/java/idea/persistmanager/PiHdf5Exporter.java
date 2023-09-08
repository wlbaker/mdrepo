package idea.persistmanager;

import java.io.File;
import java.io.IOException;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import hdf.hdf5lib.structs.H5G_info_t;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.persistmanager.hdf5.H5DatastreamExporter;
import idea.persistmanager.hdf5.ExportHeader;
import idea.persistmanager.hdf5.H5GroupExporter;
import idea.persistmanager.hdf5.H5Util;
import idea.persistmanager.hdf5.TranBlock;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PiHdf5Exporter implements PiSubjectExporter {

	public static final int VERSION = 4;
	H5DatastreamExporter tranLog;

	private RpSubject header;
	long file_id = -1;

	long[] chunk_m_dims = { 1, 1 };
	private String fileName;

	long rotateSize = 0;

	LinkedList<H5GroupExporter> deviceList = new LinkedList<H5GroupExporter>();
	private boolean tranlog_ind;
	TranBlock tranlog_block = new TranBlock();

	int error_messages = 20;
	private static int name_idx = 1;

	public PiHdf5Exporter() {
		this(null, null, true);
	}

	public PiHdf5Exporter(RpSubject header, String fileName, boolean tranlog_ind) {
		this.header = header;
		this.fileName = fileName;
		this.tranlog_ind = tranlog_ind;
	}

	public PiHdf5Exporter(RpSubject header, long fid) {
		this.header = header;
		this.file_id = fid;
	}

	@Override
	public synchronized void connect() throws IOException {
		try {

			if (rotateSize != 0) {
				rotate(fileName, 0);
			}

			if (fileName != null) {
				File f = new File(fileName);
				if (f.isDirectory()) {
					f = new File(f, "0000.h5");
					fileName = f.getPath();
				}
				if (f.exists()) {
					int accMode = HDF5Constants.H5F_ACC_RDWR;
					log.debug("H5.H5Fopen({},{},HDF5Constants.H5P_DEFAULT)", fileName, accMode);
					try {
						file_id = H5.H5Fopen(fileName, accMode, HDF5Constants.H5P_DEFAULT);
					} catch (Exception e) {
						file_id = -1;
					}
				}
			}

			if (file_id < 0) {
				log.debug(
						"H5.H5Fcreate({}, HDF5Constants.H5F_ACC_TRUNC, HDF5Constants.H5P_DEFAULT, HDF5Constants.H5P_DEFAULT)",
						fileName);
				file_id = H5.H5Fcreate(fileName, HDF5Constants.H5F_ACC_TRUNC, HDF5Constants.H5P_DEFAULT,
						HDF5Constants.H5P_DEFAULT);

				if (header != null) {
					ExportHeader exhd = new ExportHeader();
					exhd.connectNew(file_id);
					exhd.putStudyHeader(header);
					exhd.disconnect();
				}

				H5Util.writeFileVersion(file_id, VERSION);
			} else {
				log.debug("OPEN OR CREATE THE ANNO INTERFACE HERE!");

				scanGroupsAndAdd();

			}

		} catch (Exception e) {
			throw new IOException("HDF v2a Error creating file: " + fileName, e);
		}

	}

	private void scanGroupsAndAdd() throws Exception {
		H5G_info_t info = null;

		long gid = H5.H5Gopen(file_id, "/", HDF5Constants.H5P_DEFAULT);
		info = H5.H5Gget_info(gid);
		H5.H5Gclose(gid);

		if (info == null || info.nlinks == 0) {
			log.error("Error: no groups to add?");
			return;
		}

		String objNames[] = new String[(int) info.nlinks];
		int objTypes[] = new int[(int) info.nlinks];
		int lnkTypes[] = new int[(int) info.nlinks];
		long objRefs[] = new long[(int) info.nlinks];

		int names_found = H5.H5Gget_obj_info_all(file_id, "/", objNames, objTypes, lnkTypes, objRefs,
				HDF5Constants.H5_INDEX_NAME);

		for (int i = 0; i < objNames.length; i++) {
			if (objNames[i] == null) {
				log.error("?? name #" + i + " does not exist");
				continue;
			}
			if (objTypes[i] == HDF5Constants.H5O_TYPE_GROUP) {
				String groupName = objNames[i];

				log.info("?? Group found at index: " + i + "/" + groupName);
				long grp_id = H5.H5Gopen(file_id, groupName, HDF5Constants.H5P_DEFAULT);

				H5GroupExporter dev = new H5GroupExporter(file_id, grp_id, groupName);
				synchronized (deviceList) {
					deviceList.add(dev);
				}
				log.error(
						"cannot tell if OPEN is called again later with connect, but closing now causes an error at disconnect");
				// H5.H5Gclose(grp_id); // OPEN is called again later with
				// CONNECT???
			} else if (objTypes[i] == HDF5Constants.H5O_TYPE_DATASET) {
				log.error("?? Dataset found at index: " + i + " OPENED BY CALLER");
			} else if (objTypes[i] == HDF5Constants.H5O_TYPE_NAMED_DATATYPE) {
				log.error("?? Datatype at index: " + i);
			} else {
				log.error("?? Unknown at index: " + i + " " + objNames[i]);
			}
		}
	}

	private void rotate(String baseName, int incr) {
		String name = baseName;
		if (incr > 0) {
			name += ".";
			name += incr;
		}
		File f = new File(name);

		if (f.exists()) {
			incr++;
			rotate(baseName, incr);
			File dest = new File(baseName + "." + incr);
			f.renameTo(dest);
		}

		log.warn("ROTATION Could close devices and create a new list?");
		// deviceList = new LinkedList<ExportDevice>();
	}

	public synchronized H5DatastreamExporter addDataset(String datasetName, int sid, RpMetric[] metrics, boolean ts_ind,
			boolean null_ind) throws NullPointerException, HDF5Exception {
		H5DatastreamExporter exporter = new H5DatastreamExporter(file_id, datasetName, sid, metrics, ts_ind, null_ind);
		// deviceList.add( exporter );
		exporter.connect(file_id);
		return exporter;
	}

	@Override
	public synchronized void addDevice(RpDevice conf) throws IOException {

		_addDevice(conf);
	}

	private H5GroupExporter _addDevice(RpDevice devConfig) throws IOException {
		H5GroupExporter dev = null;

		List<RpDevice> subconfs = devConfig.getDevices();
		if (subconfs != null && subconfs.size() > 0) {
			for (RpDevice subconf : subconfs) {
				_addDevice(subconf);
			}
		}

		try {
			log.info("creating device: {}", devConfig);
			H5GroupExporter pre_dev = new H5GroupExporter(file_id, devConfig);
			deviceList.add(pre_dev);
			dev = pre_dev; // only if no exception is thrown!

			if (file_id > 0) { // isConnected() ) {
				pre_dev.connect();
			}

		} catch (Exception ex) {
			throw new IOException(ex);
		}

		return dev;
	}

	@Override
	public synchronized void disconnect() throws IOException {
		if (file_id == -1 || file_id == 0) {
			return; // already disconnected
		}

		try {

			if (tranLog != null) {
				tranLog.disconnect();
			}

			for (H5GroupExporter dev : deviceList) {
				dev.disconnect();
			}

		} catch (Exception e) {
			e.printStackTrace();
			throw new IOException("HDF v2b Error", e);
		} finally {

			try {
				log.warn("disconnect flush");
				H5.H5Fflush(file_id, HDF5Constants.H5F_SCOPE_GLOBAL);
				H5.H5Fclose(file_id);
				// H5.H5close(); // this is a strong close...closes all
				// resources.
			} catch (HDF5LibraryException e) {
				throw new IOException(e);
			} finally {
				file_id = -1;
				deviceList.clear();
			}
		}
	}

	public synchronized void put(StreamProducer source, StreamID sid, PersistentItem wfb) throws IOException {

		if (wfb == null) {
			return; // probably a connection event?
		}

		try {
			if (rotateSize > 0) {
				long size;
				size = H5.H5Fget_filesize(file_id);

				if (size > rotateSize) {
					disconnect();
					rotate(fileName, 0);
					connect();
				}
			}

			H5GroupExporter dev = findGroupExporter(source);
			if (dev != null) {
				long pos = dev.putPersistentItem(sid, wfb);

				if (tranlog_ind) {
					put_tranLog(wfb.getTime(), pos, (char) sid.getCode(), dev.getConf().getName());
				}
			}

		} catch (NullPointerException | HDF5Exception e) {
			throw new IOException(e);
		}
	}

	private void put_tranLog(long time, long pos, char c, String configName)
			throws NullPointerException, HDF5Exception {
		checkTranLog();
		tranlog_block.setTm(new Date(time));
		tranlog_block.setFpos(pos);
		tranlog_block.setFtyp((byte) c);
		tranlog_block.setName(configName);
		// tranLog.put(tranlog_block);
	}

	private void checkTranLog() throws NullPointerException, HDF5Exception {
		if (tranLog == null) {
			tranLog = new H5DatastreamExporter(file_id, "/tranlog", //
					StreamID.TRANLOG.getCode(), //
					IntfUtil.getMetrics(TranBlock.class), //
					true, false);
			tranLog.connect(file_id);
		}

	}

	private H5GroupExporter findGroupExporter(StreamProducer source) throws IOException {

		String name = null;

		RpDevice conf = null;
		if (source != null) {
			conf = source.getConfiguration();
		}
		if (conf != null) {
			name = conf.getName();
		}
		if (name == null) {
			name = source.getClass().getName();
		}

		H5GroupExporter dev = null;
		synchronized (deviceList) {
			for (H5GroupExporter ed : deviceList) {
				RpDevice edConf = ed.getConf();
				if (edConf == null) {
					log.error("INTERNAL ERROR: NULL CONF IN DEVICE LIST");
					continue;
				}
				if (name.equals(edConf.getName())) {
					dev = ed;
					break;
				}

			}

			if (dev == null) {
				
				if( conf == null ) {
					conf = source.getStaticCapabilities();
					conf.setName( name );
				}

				dev = _addDevice(conf);
			}
			assert (dev != null) : "Could not find/create device!";
		}
		return dev;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (file_id < 0) {
			return; // NOT CONNECTED
		}

		try {
			put(source, sid, item);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void setRotation(long maxSize) {

		rotateSize = maxSize;

		// H5.H5Fget_filesize( file_id );
	}

	@Override
	public void setHeader(RpSubject header) {
		this.header = header;
	}

	public synchronized void flush() throws HDF5LibraryException {

		if (file_id == 0 || file_id == -1) {
			return;
		}

		H5.H5Fflush(file_id, HDF5Constants.H5F_SCOPE_GLOBAL);
	}

	public long getHdf5FileId() {
		return file_id;
	}

	@Override
	public void setDestination(File archiveDir) {
		if (archiveDir.getPath().toLowerCase().endsWith(".h5")) {
			// no change
		} else {
			archiveDir = new File(archiveDir, "0000.h5");
		}

		this.fileName = archiveDir.getPath();
	}

	public void writeAttribute(String name, String value) throws IOException {
		try {
			H5Util.writeStringAttribute(file_id, name, value);
		} catch (NullPointerException | HDF5Exception e) {
			throw new IOException(e);
		}
	}

	public void remove(String ds_name) throws HDF5LibraryException {
		Iterator<H5GroupExporter> ii = deviceList.iterator();
		while (ii.hasNext()) {
			H5GroupExporter ed = ii.next();
			assert (ed != null) : "[Hdf5Exporter] ExportDevice CANNOT BE NULL";

			if (ed.getConf().getName().equals(ds_name)) {
				ed.disconnect();
				H5Util.remove(file_id, ds_name);
				ii.remove();
				break;
			}
		}
	}

	public File getFile() {
		return new File(fileName);
	}

	public void setFile(File h5_export_file) {
		log.error("FIXME: maybe this should be the full getPath()???");
		fileName = h5_export_file.getName();
	}

}
