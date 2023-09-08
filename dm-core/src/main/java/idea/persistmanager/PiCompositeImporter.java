package idea.persistmanager;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.LinkedList;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistence.PiDatastreamImporter;
import idea.persistmanager.composite.CompositeDataset;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PiCompositeImporter extends AbstractStreamProducer implements PiSubjectImporter {

	public static final String SUBJECT_NAME = "Subject";

	int file_idx = 0;
	private PersistentItem[] arNext = null;
	private PropertyChangeSupport propertySupport = new PropertyChangeSupport(this);

	private LinkedList<H5CompositeWithMeta> files = new LinkedList<H5CompositeWithMeta>();

	private int flags;

	public PiCompositeImporter(File file) {
		this(file, PiImporterUtil.ANY_FLAG);
	}

	public PiCompositeImporter(File file, int flags) {
		this.flags = flags;
		addFile(file);
	}

	public void addFile(File file) {
		this.addFile(file.getName(), file);
	}

	public void addFile(String subject, File file) {
		if (file.isDirectory()) {
			File[] children = file.listFiles();
			for (File child : children) {
				addFile(subject, child);
			}
		} else {

			String suffix = file.getPath().toLowerCase();
			try {
				PiSubjectImporter importer = null;
				if (suffix.endsWith("dat") && ((flags & PiImporterUtil.DAT_FLAG) > 0)) {
					importer = new PiDreImporter(file, "DAT");
				} else if (suffix.endsWith("vtl") && ((flags & PiImporterUtil.VTL_FLAG) > 0)) {
					importer = new PiDreImporter(file, "VTL");
				} else if (suffix.endsWith("h5") && ((flags & PiImporterUtil.HDF5_FLAG) > 0)) {
					importer = new PiHdf5Importer(file, true);
				}

				if (importer != null) {
					H5CompositeWithMeta hmeta = new H5CompositeWithMeta(file, null);
					hmeta.setSubject(subject);
					importer.connect(); // hmeta, true);
					PiDatastreamImporter[] devs = importer.getDevices();
					ArchiveMetaData meta = importer.getMetaData(); // createMetaData();
					importer.disconnect();

					System.err.println("DID I HAVE AN EXTRA CONNECTION OPEN???");
					hmeta.setImporter(importer);
					hmeta.setMeta(meta);
					if (meta.getStartTime() == null) {
						log.warn("Could not get start time: {}", file);
					} else {
						log.debug("adding file: {}", file);
						log.debug(" * start time: {}  stop time:" + meta.getStartTime(), meta.getStopTime());
						files.addLast(hmeta);
					}
				}
			} catch (Exception ex) {
				log.error("error loading child: {}", file, ex);
			}

		}

	}

	@Override
	public void connect() throws IOException {

		arNext = null;
		for (H5CompositeWithMeta f : files) {
			try {
				PiSubjectImporter importer = f.getImporter();
				// if (importer == null) {
				// importer = new PiHdf5Importer(f.getFile(), true);
				// f.setImporter(importer);
				// }
				importer.connect();

			} catch (Exception e) {
				e.printStackTrace();
				throw (new IOException(e));
			}
		}

	}

	@Override
	public void disconnect() {

		for (H5CompositeWithMeta f : files) {
			PiSubjectImporter importer = f.getImporter();
			if (importer != null) {
				importer.disconnect();
			}
		}

	}

	@Override
	public long getTimeInMillis() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public PersistentItem next() throws IOException {
		PersistentItem block = _chrono_next_item();

		return block;
	}

	public PersistentItem _chrono_next_item() throws IOException {

		if (arNext == null) {
			arNext = new PersistentItem[files.size()];

			for (int idx = 0; idx < files.size(); idx++) {

				PiSubjectImporter importer = files.get(idx).getImporter();
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
				PiSubjectImporter importer = files.get(nextPos).getImporter();
				if (importer != null) {
					arNext[nextPos] = importer.next();
				}
			}
		} catch (IOException e) {
			throw e;
		} catch (Exception e) {
			throw new IOException(e);
		}

		return ret;
	}

	@Override
	public RpSubject getSubjectInfo() {
		RpSubject header = null;

		if (files.size() > 0) {
			H5CompositeWithMeta f = files.get(0);
			PiSubjectImporter importer = f.getImporter();
			if (importer != null) {
				header = importer.getSubjectInfo();
			}
		}
		return header;
	}

	public PiDatastreamImporter[] getDevices() { // only for the current subject
		LinkedList<PiDatastreamImporter> list = new LinkedList<PiDatastreamImporter>();

		String subject = getSubject();
		for (H5CompositeWithMeta f : files) {
			if (subject.equals(f.getSubject())) {
				PiSubjectImporter importer = f.getImporter();
				PiDatastreamImporter[] sub_devices = importer.getDevices();

				if (sub_devices != null) {
					list.addAll(Arrays.asList(sub_devices));
				}
			}
		}
		PiDatastreamImporter[] devices = new PiDatastreamImporter[list.size()];
		devices = list.toArray(devices);
		return devices;
	}

	public PiDatastreamImporter[] getAllDevices() {
		LinkedList<PiDatastreamImporter> list = new LinkedList<PiDatastreamImporter>();

		for (H5CompositeWithMeta f : files) {
			PiSubjectImporter importer = f.getImporter();
			PiDatastreamImporter[] sub_devices = importer.getDevices();

			if (sub_devices != null) {
				list.addAll(Arrays.asList(sub_devices));
			}
		}
		PiDatastreamImporter[] devices = new PiDatastreamImporter[list.size()];
		devices = list.toArray(devices);
		return devices;
	}

	@Override
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid) {

		CompositeDataset composite = null;
		for (H5CompositeWithMeta f : files) {
			PiSubjectImporter importer = f.getImporter();
			PiDatastreamImporter ds = importer.getDatastreamImporter(name, sid);
			if (ds != null) {
				if (composite == null) {
					composite = new CompositeDataset();
				}
				composite.addDataset(ds);
			}
		}
		return composite;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		log.error("getStaticCapabilities: STUB NOT IMPLEMENTED");
		return null;
	}

	@Override
	public ArchiveMetaData getMetaData() throws IOException {
		ArchiveMetaData meta_tot = new ArchiveMetaData();
		for (H5CompositeWithMeta file : files) {

			ArchiveMetaData meta = file.getMeta();
			if (meta_tot.getStartTime() == null) {
				meta_tot.setStartTime(meta.getStartTime());
			}
			if (meta_tot.getStopTime() == null) {
				meta_tot.setStopTime(meta.getStopTime());
			}

			if (meta.getStartTime() != null && meta.getStartTime().getTime() < meta_tot.getStartTime().getTime()) {
				meta_tot.setStartTime(meta.getStartTime());
			}
			if (meta.getStopTime() != null && meta.getStopTime().getTime() > meta_tot.getStopTime().getTime()) {
				meta_tot.setStopTime(meta.getStopTime());
			}
		}
		return meta_tot;
	}

	@Override
	public void rewind() throws IOException {
		for (H5CompositeWithMeta f : files) {
			PiSubjectImporter importer = f.getImporter();
			if (importer != null) {
				importer.rewind();
			}
		}

		String old_subject = getSubject();
		file_idx = 0;
		String subject = getSubject();
		if (!old_subject.equals(subject)) {
			propertySupport.firePropertyChange(SUBJECT_NAME, old_subject, subject);
		}

	}

	@Override
	public void seek(long startTime) throws IOException {

		for (H5CompositeWithMeta f : files) {
			PiSubjectImporter importer = f.getImporter();
			if (importer != null) {
				try {
					importer.seek(startTime);
				} catch (Exception e) {
					log.error("Could not seek: {}", f.getFile(), e);
				}
			}

		}
	}

	public boolean nextFile() throws IOException {
		boolean ok = false;
		String old_subject = getSubject();
		if ((file_idx + 1) < files.size()) {
			arNext = null;
			file_idx++;
			H5CompositeWithMeta f = files.get(file_idx);
			PiSubjectImporter importer = f.getImporter();
			importer.rewind();
			ok = true;

			if (!old_subject.equals(f.getSubject())) {
				propertySupport.firePropertyChange(SUBJECT_NAME, old_subject, f.getSubject());
			}
		}
		return ok;
	}

	public File getFile() {
		H5CompositeWithMeta f = files.get(file_idx);
		return f.getFile();
	}

	public H5CompositeWithMeta getCurrentMetaData() {
		H5CompositeWithMeta f = files.get(file_idx);
		return f;
	}

	public String getSubject() {
		H5CompositeWithMeta f = files.get(file_idx);
		return f.getSubject();
	}

	public void addSubjectChangeListener(PropertyChangeListener listener) {
		propertySupport.addPropertyChangeListener(SUBJECT_NAME, listener);
	}

	public boolean nextSubject() throws IOException {
		String old_subject = getSubject();
		boolean ok = false;
		do {
			ok = nextFile();
		} while( ok && old_subject.equals(getSubject()));
		
		return ok;
	}
}
