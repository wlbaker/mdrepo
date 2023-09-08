package idea.persistmanager.hdf5;

import java.io.UnsupportedEncodingException;
import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class H5GroupExporter {

	private Map<String, H5DatastreamExporter> exportMap = new HashMap<String, H5DatastreamExporter>();

	long file_id;
	long grp_id;
	private RpDevice conf;

	private int error_messages = 100;

	public H5GroupExporter(long file_id, long grp_id, String groupName) throws Exception {

		this.file_id = file_id;
		this.grp_id = grp_id;

		conf = H5Util.readMetaAttribute(grp_id, groupName);
		createStreamDatasets(file_id);
	}

	public H5GroupExporter(long file_id, RpDevice conf) throws NullPointerException, HDF5Exception {
		this.setConf(conf);
		this.file_id = file_id;

	}

	private void setConf(RpDevice subconf2) {
		this.conf = subconf2;
	}

	public RpDevice getConf() {
		return conf;
	}

	private void createStreamDatasets(long file_id)
			throws NullPointerException, HDF5Exception, NoSuchFieldException, SecurityException {

		if (conf == null) {
			log.error("COULD NOT CREATE SUBGROUPS, NO CONF");
			return;
		}
		List<RpStream> streams = conf.getStreams();
		if (streams != null && streams.size() > 0) {
			// the new way...ignore, creation done automatically further down
			for (RpStream stream : streams) {
				StreamID sid = StreamID.fromName(stream.getName());
				// List<RpMetric> list = stream.getMetric();
				// RpMetric[] metrics = new RpMetric[list.size()];
				// list.toArray(metrics);
				RpMetric[] metrics = IntfUtil.getMetrics(stream.getPIClass());
				String ds_name = stream.getPIClass().getSimpleName();
				if (metrics.length == 0) {
					log.error("no metrics in dataset: {}", ds_name);
					continue;
				}
				H5DatastreamExporter ds = createDatastreamExporter(//
						(sid == null) ? 0 : sid.getCode(), //
						ds_name, //
						metrics); //
				ds.connect(grp_id);
				for (RpMetric m : metrics) {
					if (m.getSubtyp() == DataTyp.OBJ_TYP) {
						String fieldName = m.getLocation(); // this must be the real field name as stored in
														// IntfUtil.buildMetrics()
						Class<?> subitem_class = getSubitemClass(stream.getPIClass(), fieldName);
						H5DatastreamExporter dss = createDatastreamExporter(0, subitem_class.getSimpleName(),
								IntfUtil.getMetrics(subitem_class));
						dss.connect(grp_id);
					}
				}

			}
		}
	}

	private Class<?> getSubitemClass(Class<?> piClass, String name) throws NoSuchFieldException, SecurityException {
		Field field = piClass.getDeclaredField(name);
		return field.getType();
	}

	private void createGroup(RpDevice subconf2, long file_id, String devName)
			throws NullPointerException, HDF5Exception {

		if (file_id <= 0) {
			log.error("Must create file before creating group: {}", devName);
			return;
		}

		try {
			if (devName.startsWith("/")) {
				// ok
			} else {
				// make sure path names are absolute
				devName = "/" + devName;
			}

			try {
				grp_id = H5.H5Gcreate(file_id, devName, HDF5Constants.H5P_DEFAULT, HDF5Constants.H5P_DEFAULT,
						HDF5Constants.H5P_DEFAULT);
				log.debug("H5.H5Gcreate( file_id={}, devName={},0) ", file_id, devName);

				/*
				 * write driver class
				 */
				String driverClass = subconf2.getDeviceClass();
				if (driverClass != null) {
					H5Util.writeStringAttribute(grp_id, "driverClass", driverClass);
				}

			} catch (HDF5Exception ex) {
				grp_id = H5.H5Gopen(file_id, devName, HDF5Constants.H5P_DEFAULT);
			}
		} catch (Exception e) {
			log.error("create group", e);
		}

		log.debug("group flush: {}", devName);
		H5.H5Fflush(file_id, HDF5Constants.H5F_SCOPE_GLOBAL);
	}

	private String createValidGroupName(String devName) {
		String name = devName;

		if (devName != null) {
			try {
				name = java.net.URLEncoder.encode(devName, "ISO-8859-1");
			} catch (UnsupportedEncodingException e) {
				name = "UnsupportedEncodingException";
			}
		}

		if (name == null || name.length() == 0) {
			name = "UNKNOWN";
		}

		return name;
	}

	public synchronized void connect() throws Exception {
		// createStreamDatasets(file_id);
		String name = conf.getName();
		String devName = createValidGroupName(name);

		createGroup(conf, file_id, devName);

		createStreamDatasets(file_id);

	}

	public synchronized void disconnect() throws HDF5LibraryException {

		for (H5DatastreamExporter ds : exportMap.values()) {
			log.error("exportMap disconnecting {}", ds);
			if (ds != null) {
				ds.disconnect();
			}
		}

		if (grp_id >= 0) {
			H5.H5Gclose(grp_id);
		}

	}

	public long putPersistentItem(StreamID sid, PersistentItem item) throws NullPointerException, HDF5Exception {
		RpMetric[] metrics = item.getMetrics();
		if (metrics == null) {
			log.error("no metrics in item: {}", item);
		} else {
			for (RpMetric m : metrics) {
				if (m.getSubtyp() == DataTyp.OBJ_TYP) {
					Object o = IntfUtil.getRawValue(item, m);
					if (o == null) {
						// ignore
					} else if (o instanceof PersistentItem) {
						PersistentItem subitem = (PersistentItem) o;
						if (subitem != null) {
							H5DatastreamExporter ds = exportMap.get(subitem.getClass().getSimpleName());

							// VERY SUBTILE that this PUT updates the OID which is then saved by
							// encodeOneValue in H5DatasetCODEC
							ds.put(subitem);

						}
					} else {
						log.warn("EXPECTING PI value, got: {} FROM (fk?) {}", o, m.getLocation());
					}
				}
			}
		}
		
		long rc = 0;
		H5DatastreamExporter ds = exportMap.get(item.getClass().getSimpleName());
		if( ds == null ) {
			log.error("Could not find exporter: {}", item.getClass().getSimpleName());
		} else {
			rc = ds.put(item);
		}

		return rc;
	}

	public H5DatastreamExporter createDatastreamExporter(int sid_code, String ds_name, RpMetric[] metrics)
			throws HDF5Exception {
		H5DatastreamExporter ds = exportMap.get(ds_name);

		if (ds == null) {
			String h5ds_name = "/" + conf.getName() + "/" + ds_name;
			ds = new H5DatastreamExporter(file_id, h5ds_name, sid_code, metrics, true, true);
			exportMap.put(ds_name, ds);
			log.warn("exporter created: {} with dataset: {} + count={}", ds_name, h5ds_name, exportMap.size());
		} else {
			log.warn("exporter ALREADY for {}/*{}* == *{}* is {}", grp_id, ds_name, ds_name, ds);
		}
		return ds;
	}

	public ArchiveMetaData getMetaData() {
		// TODO Auto-generated method stub
		return null;
	}

}
