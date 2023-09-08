package idea.persistmanager.hdf5;

import java.io.IOException;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class H5GroupImporter extends AbstractStreamProducer implements PiDatastreamImporter {

	@Override
	public String toString() {
		return "H5GroupImporter [" + conf.getName() + "]";
	}

	ArchiveMetaData meta;

	long grp_id;

	private String _groupName;
	private LinkedList<PiDatastreamImporter> intfs;

	private PersistentItem[] blocks;
	private RpDevice conf;

	public H5GroupImporter(long file_id, int file_version, String groupName)
			throws NullPointerException, HDF5Exception, IOException {

		// this.file_version = file_version;
		this._groupName = groupName;
		grp_id = H5.H5Gopen(file_id, groupName, HDF5Constants.H5P_DEFAULT);

		/*
		 * if file version <=2, then the meta information is saved in the group.
		 * for version > 2, the meta information is saved in the dataset under the attribute "meta"
		 */
		if (file_version <= 2) {
			log.info("reading meta");
			conf = H5Util.readMetaAttribute(grp_id, null);
		} else {
			conf = new RpDevice();
		}
//		

		String name = java.net.URLDecoder.decode(_groupName, "ISO-8859-1");
		if ("Cosmo_8100".equals(name)) {
			name = "Cosmo 8100";
		} else if ("Evita_4".equals(name)) {
			name = "Evita 4";
		}

		conf.setName(name);

		intfs = H5Util.readDatasetsFromGroup(grp_id, file_version, groupName, conf);

	}

	@Override
	public void connect() throws IOException {

		List streams = conf.getStreams();
		/*
		 * remove the known streams...they are allocated in this connect
		 */
		while( streams.size() > 0 ) {
			streams.remove(0);
		}
		
		for (PiDatastreamImporter intf : intfs) {
			intf.connect();
			
			RpDevice substream = intf.getConfiguration();
			streams.add( substream );
		}

	}

	@Override
	public void disconnect() throws IOException {

		for (PiDatastreamImporter intf : intfs) {
			intf.disconnect();
		}

		try {
			if (grp_id >= 0)
				H5.H5Gclose(grp_id);
		} catch (Exception ex) {
			throw new IOException(ex);
		}

	}

	public void rewind() {
		blocks = null;
		try {
			for (PiDatastreamImporter intf : intfs) {
				intf.rewind();
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public PersistentItem next() throws IOException {
		try {
			return _next(); // a shim
		} catch (Exception e) {
			throw new IOException(e);
		}
	}

	public PersistentItem _next() throws NullPointerException, HDF5Exception, IOException {

		PersistentItem curr = null;
		if (blocks == null) {
			blocks = new PersistentItem[intfs.size()];
			for (int i = 0; i < intfs.size(); i++) {
				PiDatastreamImporter intf = intfs.get(i);
				try {
					blocks[i] = intf.next();
				} catch (Exception e) {
					log.warn("Error importing alarm: {}", intf.getName());
					blocks[i] = null;
				}
			}
		}

		curr = findFirst();

		if (curr != null) {
			// the GROUP is the data source producer for datasets that belong to the group
			curr.setSource(this);
		}

		return curr;
	}

	private PersistentItem findFirst() {
		PersistentItem ret = null;
		int found = -1;
		int idx = -1;
		for (PersistentItem curr : blocks) {
			idx++;
			if (curr == null) {
				continue;
			}
			if (ret == null) {
				ret = curr;
				found = idx;
			}
			if (ret.getTime() > curr.getTime()) {
				ret = curr;
				found = idx;
			}
		}

		if (found >= 0) {
			try {
				blocks[found] = intfs.get(found).next();
			} catch (IOException e) {
				blocks[found] = null;
				log.error("exception in finding best time");
			}
		}
		return ret;
	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	@Override
	public void requestCapabilities() throws IOException {
		return;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return null;
	}

	@Override
	public ArchiveMetaData getMeta() throws IOException {
		if (meta != null) {
			return meta;
		}
		meta = new ArchiveMetaData();

		try {
			for (PiDatastreamImporter intf : intfs) {
				ArchiveMetaData m2 = intf.getMeta();
				meta.add(m2);
			}
		} catch (Exception e) {
			log.error("Could not retrieve meta data: {}", _groupName, e);
			return null;
		}

		return meta;
	}

	@Override
	public void seek(long startTime) throws IOException {

		try {
			for (PiDatastreamImporter intf : intfs) {
				intf.seek(startTime);
			}

			blocks = null;
		} catch (Exception e) {
			throw new IOException(e);
		}
	}

	@Override
	public String getName() {
		return conf.getName();
	}

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {
		for (int idx = 0; idx < intfs.size(); idx++) {
			PiDatastreamImporter intf = intfs.get(idx);
			Class<? extends PersistentItem> cl = intf.getModel(sid);
			if (cl != null) {
				return cl;
			}

		}
		return null;
	}

	@Override
	public StreamID[] getStreams() {
		List<StreamID> ids = new LinkedList<StreamID>();
		for (int idx = 0; idx < intfs.size(); idx++) {
			ids.addAll(Arrays.asList(intfs.get(idx).getStreams()));
		}
		StreamID[] arr = new StreamID[ids.size()];
		return ids.toArray(arr);
	}

	public PiDatastreamImporter getDatasetImporter(StreamID sid) {
		for (PiDatastreamImporter intf : intfs) {

			if (intf.getStreams()[0] == sid) {
				return intf;
			}
		}
		return null;
	}

	public long getGroupID() {
		return grp_id;
	}

	public LinkedList<PiDatastreamImporter> getImporters() {
		return intfs;
	}
}
