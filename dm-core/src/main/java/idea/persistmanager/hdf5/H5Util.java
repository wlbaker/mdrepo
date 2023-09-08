package idea.persistmanager.hdf5;

import static idea.persistmanager.hdf5.DatatypeConstants.BYTESIZE;
import static idea.persistmanager.hdf5.DatatypeConstants.DOUBLESIZE;
import static idea.persistmanager.hdf5.DatatypeConstants.FLOATSIZE;
import static idea.persistmanager.hdf5.DatatypeConstants.INTEGERSIZE;
import static idea.persistmanager.hdf5.DatatypeConstants.LONGSIZE;

import java.io.IOException;
import java.lang.reflect.Field;
import java.nio.ByteBuffer;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.callbacks.H5A_iterate_cb;
import hdf.hdf5lib.callbacks.H5A_iterate_t;
import hdf.hdf5lib.callbacks.H5L_iterate_cb;
import hdf.hdf5lib.callbacks.H5L_iterate_t;
import hdf.hdf5lib.exceptions.HDF5AttributeException;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5FunctionArgumentException;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import hdf.hdf5lib.structs.H5A_info_t;
import hdf.hdf5lib.structs.H5L_info_t;
import hdf.hdf5lib.structs.H5O_info_t;
import icuInterface.RpUtil;
import icuInterface.UnitUtil;
import idea.conf.CompositeDescription;
import idea.conf.DeviceConfiguration;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.persistence.PiDatastreamImporter;
import idea.persistmanager.PiConstants;
import idea.persistmanager.PiHdf5Exporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

class opdata_Lt implements H5L_iterate_t {
	public LinkedList<PiDatastreamImporter> importers = new LinkedList<PiDatastreamImporter>();
	int recurs;
	opdata_Lt prev;
	long addr;
	public long file_id;
	public int file_version;
	public RpDevice conf;
	public String parent;
}

class opdata_At implements H5A_iterate_t {
	int recurs;
	opdata_Lt prev;
	long addr;
	public long file_id;
	public int file_version;
	public RpDevice conf;
	public String parent;
}

enum H5O_type {
	H5O_TYPE_UNKNOWN(-1), // Unknown object type
	H5O_TYPE_GROUP(0), // Object is a group
	H5O_TYPE_DATASET(1), // Object is a dataset
	H5O_TYPE_NAMED_DATATYPE(2), // Object is a named data type
	H5O_TYPE_NTYPES(3); // Number of different object types
	private static final Map<Integer, H5O_type> lookup = new HashMap<Integer, H5O_type>();

	static {
		for (H5O_type s : EnumSet.allOf(H5O_type.class))
			lookup.put(s.getCode(), s);
	}

	private int code;

	H5O_type(int layout_type) {
		this.code = layout_type;
	}

	public int getCode() {
		return this.code;
	}

	public static H5O_type get(int code) {
		return lookup.get(code);
	}
}

@Slf4j
public class H5Util {
	private final static String[] known_units = { "mmHg", "%", "ms", "bpm", "??", "C", "?ms", "1/min", "mL", "mbar",
			"oz", "hhmm", "oz/hr", "null", "ml/min", "kcal/24hr", "br/min", "L/min", "cmH2O" };

	private static final int RANK1 = 1;
	private static H5DatasetCODEC meta_codec;

	private static H5L_iter_callbackT iter_cb = new H5L_iter_callbackT();
	private static H5L_iterate_cb iter_cb2 = new H5L_iter_callbackT();

	// @Slf4j
	static class H5L_iter_callbackT implements H5L_iterate_cb {

		@Override
		public int callback(long group_id, String name, H5L_info_t info, H5L_iterate_t op) {
			opdata_Lt opdata = (opdata_Lt) op;

			H5O_info_t infobuf; // the input info does not have the type field populated (correctly)
			try {
				infobuf = H5.H5Oget_info_by_name(group_id, name, HDF5Constants.H5P_DEFAULT);
				switch (H5O_type.get(infobuf.type)) {
				case H5O_TYPE_GROUP:
					log.info("  Group: {}", name);
					H5GroupImporter importDevice;
					try {
						importDevice = new H5GroupImporter(group_id, opdata.file_version, name);
						// H5GroupImporter calls this function recursively
						opdata.importers.add(importDevice);
					} catch (NullPointerException | HDF5Exception | IOException e) {
						log.error("Cannot open group : " + group_id, e);
					}
					break;
				case H5O_TYPE_DATASET:
					log.info("  Dataset: {}", name);
					log.error("FIXME: update to hdf5-1.10 broke some usage");
					DatasetImporter ds = new DatasetImporter(opdata.file_id, opdata.parent, name);

					/*
					 * this is only important for backward compatibility...some unspecified version
					 */
					if (opdata.conf != null) {
						StreamID sid = StreamID.fromName(name);
						if (sid != null) {
							RpStream s = RpUtil.getStream(opdata.conf, sid);
							ds.setStreamHint(s);
						}
					}
					opdata.importers.add(ds);
					break;

				case H5O_TYPE_NAMED_DATATYPE:
				case H5O_TYPE_NTYPES:
				default:
					break;
				}
			} catch (HDF5LibraryException | NullPointerException e1) {
				// TODO Auto-generated catch block
				log.error("Failed to get H5 data type", e1);
			}

			return 0;
		}

	};

	public static long createTypes(int dataSize, int[] memberDims, String[] memberNames, long[] memberFileTypes,
			int[] memberStorage) throws HDF5LibraryException {

		log.debug("H5.H5Tcreate( HDF5Constants.H5T_COMPOUND, {} );", dataSize);

		long type_id = H5.H5Tcreate(HDF5Constants.H5T_COMPOUND, dataSize);

		int member_offset = 0;
		int numberMembers = memberNames.length;
		for (int indx = 0; indx < numberMembers; indx++) {
			String memberName = memberNames[indx];
			int memberDim = memberDims[indx];
			boolean derived = false;

			long fftype_id = memberFileTypes[indx];
			if (fftype_id == HDF5Constants.H5T_C_S1) {

				long strtype_id = H5.H5Tcopy(HDF5Constants.H5T_C_S1);
				H5.H5Tset_size(strtype_id, memberStorage[indx]);

				fftype_id = strtype_id;
				derived = true;
			}

			if (memberDim > 1) {
				long[] array_dim = { memberDim };
				long array_tid = H5.H5Tarray_create(fftype_id, 1, array_dim);

				fftype_id = array_tid;
				derived = true;
			}

			log.debug("H5.H5Tinsert( filetype_id, {}, offset={} );", memberName, member_offset);

			// make sure it is a legal member name
			if (memberName.indexOf(':') > 0) {
				log.error("illegal member name: {} removing ':'", memberName);
				memberName = memberName.replace(":", "");
			}
			if (memberName.indexOf('/') > 0) {
				log.error("illegal member name: {} removing '/'", memberName);
				memberName = memberName.replace("/", "");
			}

			// this is useful for finding duplicate members in the @Metric attribute names 
			log.debug("attempting to insert type: {} {} {} {}", type_id, memberName, member_offset, fftype_id );
			H5.H5Tinsert(type_id, memberName, member_offset, fftype_id);
			member_offset += memberStorage[indx] * memberDims[indx];
			if (derived) {
				H5.H5Tclose(fftype_id);
			}

		}

		return type_id;
	}

	public static boolean hasNullInd(int dataset_id) throws HDF5LibraryException, NullPointerException {

		long h5tid = H5.H5Dget_type(dataset_id);
		int n = 0;
		boolean nullind = false;

		if (h5tid >= 0) {
			n = H5.H5Tget_nmembers(h5tid);
		}

		if (n > 1) {
			String name = H5.H5Tget_member_name(h5tid, 1);
			// int typ = H5.H5Tget_member_type(h5tid, i);
			nullind = name.equals("nullind");

		}

		if (h5tid >= 0) {
			H5.H5Tclose(h5tid);
		}

		return nullind;
	}

	public static int readIntAttribute(long fileId, String attrName) throws HDF5LibraryException, NullPointerException {

		boolean exists = H5.H5Aexists(fileId, attrName);
		int value = 0;
		if (!exists) {
			log.error("could not file attribute: {}", attrName);
		} else {
			try {
				long attr_id = H5.H5Aopen_by_name(fileId, ".", attrName, HDF5Constants.H5P_DEFAULT,
						HDF5Constants.H5P_DEFAULT);
				// int attr_id = H5.H5Aopen_name(fileId, attrName);
				long aspace = H5.H5Aget_space(attr_id);

				byte[] buf = new byte[4];

				int ret = H5.H5Aread(attr_id, HDF5Constants.H5T_STD_B32BE, buf);
				if (ret < 0) {
					// no such attribute...or not right kind
					value = 0;
				} else {
					ByteBuffer bb = ByteBuffer.wrap(buf);
					value = bb.getInt();
				}

				H5.H5Aclose(attr_id);
				H5.H5Sclose(aspace);
			} catch (Exception ex) {
				// no such attribute
				value = 0;
			}
		}

		return value;
	}

	public static void writeStringAttribute(long parent_id, String attrName, String attrValue)
			throws NullPointerException, HDF5Exception {
		String val = null;

		byte[] buf = attrValue.getBytes();
		long[] dims = { 1 };
		long[] maxdims = { 1 };
		long aspace = H5.H5Screate_simple(RANK1, dims, maxdims);

		long s256 = H5.H5Tcopy(HDF5Constants.H5T_C_S1);
		H5.H5Tset_size(s256, buf.length);

		long attr = H5.H5Acreate(parent_id, attrName, s256, aspace, HDF5Constants.H5P_DEFAULT,
				HDF5Constants.H5P_DEFAULT);

		int ret = H5.H5Awrite(attr, s256, buf);
		H5.H5Aclose(attr);
		H5.H5Sclose(aspace);

		return;
	}

	public static String readStringAttribute(long fileId, String attrName)
			throws HDF5LibraryException, NullPointerException {

		String value = null;

		boolean exists = H5.H5Aexists(fileId, attrName);
		if (!exists) {
			log.error("Could not find attribute: {}", attrName);
		} else {

			try {
				long attr_id = H5.H5Aopen_by_name(fileId, ".", attrName, HDF5Constants.H5P_DEFAULT,
						HDF5Constants.H5P_DEFAULT);
				long aspace = H5.H5Aget_space(attr_id);
				long typ = H5.H5Aget_type(attr_id);

				// System.out.println("typ=" + typ + " == " +
				// HDF5Constants.H5T_C_S1);

				byte[] buf = new byte[(int) H5.H5Tget_size(typ)];

				int ret = H5.H5Aread(attr_id, typ, buf);
				if (ret < 0) {
					// no such attribute...or not right kind
				} else {
					value = new String(buf).trim();
				}

				H5.H5Tclose(typ);
				H5.H5Aclose(attr_id);
				H5.H5Sclose(aspace);
			} catch (Exception ex) {
				// no such attribute
			}
		}
		return value;
	}

	public static String getClassFromDeviceName(String devName) {
		String cl = null;

		if (devName == null) {
			devName = "icuInterface.adapters.NullDevice";
		} else if (devName.startsWith("Bard")) {
			devName = "icuInterface.adapters.BardUrimeter";
		} else if (devName.startsWith("Evita")) {
			devName = "icuInterface.adapters.EvitaDriver";
		} else if (devName.startsWith("Drager")) {
			devName = "icuInterface.adapters.InfinityDriver";
		} else if (devName.startsWith("Cosmo")) {
			devName = "icuInterface.adapters.Cosmo8100Driver";
		} else if (devName.startsWith("Capnostream")) {
			devName = "icuInterface.adapters.CapnostreamDriver";
		} else if (devName.startsWith("Vigil")) {
			devName = "icuInterface.adapters.IFMoutDriver";
		} else if (devName.startsWith("Deltatrac")) {
			devName = "icuInterface.adapters.Deltatrac2";
		} else if (devName.startsWith("Sentec")) {
			devName = "icuInterface.adapters.SentecSerDriver";
		} else if (devName.equals("alarms")) {
			// ignore
		} else if (devName.equals("tranlog")) {
			// ignore
		} else {
			log.debug("Could not identify driver: {}", devName);
		}

		return devName;
	}

	/*
	 * while you could get the basic type descriptions from the dataset itself,
	 */
	public static RpStudy readStudy(String fileName) throws HDF5LibraryException, NullPointerException {

		int accMode = HDF5Constants.H5F_ACC_RDONLY;
		RpStudy study = new RpStudy();

		List<RpHardware> hws = study.getHardware();
		RpHardware hw = new RpHardware();
		hw.setName("active");
		List<RpDevice> devs = hw.getDevices();
		long file_id = H5.H5Fopen(fileName, accMode, HDF5Constants.H5P_DEFAULT);

		if (file_id >= 0) {
			long count = H5.H5Gn_members(file_id, "/");

			log.info("count={}: members for data file: {}", count, fileName);
			if (count > 0) {
				String[] oname = new String[(int) count];
				int[] otype = new int[(int) count];
				long[] orefs = new long[(int) count];
				int n = H5.H5Gget_obj_info_all(file_id, "/", oname, otype, orefs);
				// Get type of the object and display its name and type.
				log.debug("H5.H5Gget_obj_info_all() returned: {}", n);

				for (int indx = 0; indx < count; indx++) {

					if (otype[indx] == HDF5Constants.H5O_TYPE_GROUP) {
						log.info("  Group: {}", oname[indx]);
						long grp_id = H5.H5Gopen(file_id, oname[indx], HDF5Constants.H5P_DEFAULT);

						DeviceConfiguration conf = readMetaAttribute(grp_id, oname[indx]);
						H5.H5Gclose(grp_id);

						devs.add(conf);
					} else if (otype[indx] == HDF5Constants.H5O_TYPE_DATASET) {
						log.info("  Dataset: {}", oname[indx]);
					} else if (otype[indx] == HDF5Constants.H5O_TYPE_NAMED_DATATYPE) {
					} else if (otype[indx] == HDF5Constants.H5O_TYPE_NTYPES) {
						// System.out.println(" Datatype:" + oname[indx]);
					} else {
						log.error("Unknown HDF5 type.  field={}", oname[indx]);
					}
				}
			}
			H5.H5Fclose(file_id);
		}

		return study;

	}

	/*
	 * while you could get the basic type descriptions from the dataset itself,
	 * 
	 * This routine is used both for groups (old) and for individual streams (newer)
	 */
	public static DeviceConfiguration readMetaAttribute(long grp_id, String conf_name)
			throws HDF5LibraryException, NullPointerException {

		DeviceConfiguration conf = readDescriptionsFromAttribute("meta", grp_id, conf_name);
		if (conf == null) {
			conf = readDescriptionsFromAttribute("signals", grp_id, conf_name);
		}

		return conf;
	}

	private static DeviceConfiguration readDescriptionsFromAttribute(String attributeName, long grp_id,
			String conf_name) throws HDF5LibraryException, NullPointerException {

		// this is used at the signal level, not the group level.
		StreamID signal_sid = null;
		int streamID = H5Util.readIntAttribute(grp_id, "streamID");
		if (streamID != 0) {
			signal_sid = StreamID.fromCode(streamID);
		}

		String s = H5Util.readStringAttribute(grp_id, "driverClass");
		if (s == null) {
			s = H5Util.getClassFromDeviceName(conf_name);
		}

		DeviceConfiguration conf = new DeviceConfiguration(s);
		conf.setName(conf_name);

		conf.setDriverName(conf_name);

		boolean exists = H5.H5Aexists(grp_id, attributeName);
		if (exists) {
			long attr_id;
			try {
				attr_id = H5.H5Aopen_by_name(grp_id, ".", attributeName, HDF5Constants.H5P_DEFAULT,
						HDF5Constants.H5P_DEFAULT);
				log.debug("Opened attribute: {} on group: {} --> {}", attributeName, grp_id, attr_id);
			} catch (HDF5FunctionArgumentException xx) {
				log.debug("FAE \"{}\" not found for group: {}", attributeName, conf_name);
				return null;
			} catch (HDF5AttributeException xx) {
				log.debug("Attribute \"{}\" not found for group: {}", attributeName, conf_name);
				return null;
			}

			long aspace = H5.H5Aget_space(attr_id);

			long[] min_d = new long[1];
			long[] max_d = new long[1];
			int ndims = H5.H5Sget_simple_extent_dims(aspace, min_d, max_d);

			int nrecs = (int) min_d[0];

			long filetype_id = H5.H5Aget_type(attr_id);

			int sz = (int) H5.H5Aget_storage_size(attr_id);
			byte[] read_data = new byte[sz];

			H5.H5Aread(attr_id, filetype_id, read_data);

			StreamID[] sidSet = null;
			int[] decode_keys = null;
			if (streamID != 0) {
				sidSet = new StreamID[] { signal_sid };
				decode_keys = new int[] { 0 };
			} else {
				// support for original format...quite dated now
				sidSet = new StreamID[] { StreamID.MEASUREMENT, StreamID.WAVEFORM, StreamID.SETTINGS };
				decode_keys = new int[] { 1, 2, 3 };
			}

			for (int i = 0; i < sidSet.length; i++) {
				StreamID sid = sidSet[i];
				int decode_key = decode_keys[i];

				RpMetric[] metrics = null;
				if ("signals".equals(attributeName)) {
					metrics = H5SignalDescription.decode(read_data, decode_key);
				} else {
					List<RpMetric> list = new LinkedList<RpMetric>();
					decodeTypeData(list, filetype_id, read_data, decode_key);
					metrics = new RpMetric[list.size()];
					list.toArray(metrics);
				}

				if (metrics == null) {
					continue;
				}

				RpStream stream = conf.getStream(sid);
				if (stream == null) {
					stream = new RpStream();
					stream.setName(sid.getName());
					conf.addStream(stream);
				}

				for (RpMetric desc : metrics) {

					RpMetric duplicate = RpUtil.getMetricFromStream(stream, desc.getLocation());
					if (duplicate != null) {
						log.error("duplicate metric signal being renamed: {}", desc.getLocation());
						desc.setLocation(desc.getLocation() + "_dup");
					}
					stream.getMetric().add(desc);
				}
			}
			if (aspace >= 0) {
				H5.H5Sclose(aspace);
			}
			if (attr_id >= 0) {
				H5.H5Aclose(attr_id);
			}
			if (filetype_id >= 0) {
				H5.H5Tclose(filetype_id);
			}
		}

		return conf;
	}

	private static void decodeTypeData(List<RpMetric> metric, long filetype_id, byte[] read_data, int decode_key)
			throws HDF5LibraryException {
		log.debug("filetype nmembers: {}  size: {}", H5.H5Tget_nmembers(filetype_id), H5.H5Tget_size(filetype_id));

		int n = H5.H5Tget_nmembers(filetype_id);
		int[] clz = new int[n];
		int[] siz = new int[n];
		long[] offset = new long[n];
		String[] name = new String[n];
		for (int i = 0; i < n; i++) {
			name[i] = H5.H5Tget_member_name(filetype_id, i);

			offset[i] = H5.H5Tget_member_offset(filetype_id, i);
			long typ = H5.H5Tget_member_type(filetype_id, i);
			clz[i] = H5.H5Tget_class(typ);
			siz[i] = (int) H5.H5Tget_size(typ);
			log.debug("  field: {} offset: {}", name, offset);
		}

		// System.out.println("**NEW ATTRIBUTE");
		ByteBuffer bb = ByteBuffer.wrap(read_data);

		while (bb.remaining() > 2) {
			RpMetric m = new RpMetric();
			String unitName = null;
			float lu_m = 0;
			float lu_b = 0;
			int pu_p = 0;

			// System.out.println("**NEXT FIELD: " + bb.position());
			int end = bb.position();
			for (int i = 0; i < n; i++) {
				int t = clz[i];
				String nm = name[i];
				// System.out.print("    " + nm + " at: " + (bb.position() - end) + " ");

				if (t == HDF5Constants.H5T_INTEGER) {
					int val = bb.getInt();
					//System.out.print("        I=" + val);
					if ("sigtyp".equals(nm)) {
						if (decode_key != 0 && val != decode_key) {
							continue;
						}
					} else if ("rate".equals(nm)) {
						m.setSampleRate(val);
					} else if ("spp".equals(nm)) {
						m.setSamplesPerPacket(val);
					} else if ("pu_p".equals(nm)) {
						pu_p = val;
					} else if ("subtyp".equals(nm)) {
						m.setSubtyp(val);
					} else {
						log.error("CANT APPLY UNKNOWN INT FIELD TO METRIC DEF: {}", nm);
					}
				} else if (t == HDF5Constants.H5T_FLOAT) {

					double val;
					if (siz[i] == 4) {
						val = bb.getFloat();
					} else if (siz[i] == 8) {
						val = bb.getDouble();
					} else {
						log.error("Unknown float size");
						val = -1;
					}
					// System.out.print("        F=" + val);
					if ("lu_m".equals(nm)) {
						lu_m = (float) val;
					} else if ("lu_b".equals(nm)) {
						lu_b = (float) val;
					} else {
						log.error("CANT APPLY UNKNOWN FLOAT FIELD TO METRIC DEF: {}", nm);
					}
				} else {
					// read and discard
					byte[] dst = new byte[siz[i]];
					bb.get(dst);
					String val = new String(dst).trim();

					// System.out.print("        s=");
					for (int ii = 0; ii < dst.length; ii++) {
						// System.out.print(" ");
						int ch = dst[ii];
						if (ch < 0) {
							ch += 256;
						}
						//if (ch < 16) {
						//	System.out.print("0");
						//}
						//System.out.print(Integer.toHexString(ch));
						//if (ch > 32 && ch < 'z') {
						//	System.out.print(" [" + ch + "]");
						//}
					}

					if ("loc".equals(nm)) {
						m.setLocation(val);
					} else if ("code".equals(nm)) {
						m.setCode(val);
					} else if ("desc".equals(nm)) {
						m.setName(val);
					} else if ("unit".equals(nm)) {
						unitName = val;
					} else {
						log.error("CANT APPLY UNKNOWN STRING(?) FIELD TO METRIC DEF: {}", nm);
					}
				}
				// System.out.println();
			}

			if (pu_p == 0) {
				RpLinearUnit lu = new RpLinearUnit();
				lu.setUnitName(unitName);
				lu.setM(lu_m);
				lu.setB(lu_b);
				m.setUnit(lu);
			} else if (pu_p == 0) {
				RpPrecisionUnit pu = new RpPrecisionUnit();
				pu.setUnitName(unitName);
				pu.setPrecision(pu_p);
				m.setUnit(pu);
			}
			//System.out.println("DEBUG: adding m=" + m.getName() + " " + m.getLocation() + " " + m.getUnitName());
			metric.add(m);
		}

		return;
	}

	/**
	 * This routine cannot handle units. YES IT CAN...you have to parse the
	 * attribute name. Parsing used for older datasets.
	 * 
	 * @param dataset_id
	 * @return
	 * @throws HDF5LibraryException
	 * @throws NullPointerException
	 */
	public static H5DatasetCODEC readDescriptionsFromDataset(long dataset_id, RpStream stream_hint)
			throws HDF5LibraryException, NullPointerException {

		LinkedList<RpMetric> mlist = new LinkedList<RpMetric>();

		long file_tid = H5.H5Dget_type(dataset_id);
		int n = 0;

		if (file_tid >= 0) {
			n = H5.H5Tget_nmembers(file_tid);
		}

		boolean ts_ind = false;
		boolean null_ind = false;

		for (int i = 0; i < n; i++) {
			String h5_field_name = H5.H5Tget_member_name(file_tid, i);
			String name = h5_field_name;
			RpLinearUnit unit = null;
			String loc;

			if (log.isDebugEnabled()) {
				long offset = H5.H5Tget_member_offset(file_tid, i);
				log.debug("field: {} offset: {}", name, offset);
			}

			String[] arr = h5_field_name.split("!");
			if (arr.length > 1) {
				name = arr[0];
				loc = arr[1];
				if (arr.length > 2) {
					unit = UnitUtil.parseLinearUnit(arr[2]);
				}
			} else {
				String unit_name = getUnitName(h5_field_name);
				name = h5_field_name;
				if (unit_name != null) {
					name = name.substring(0, name.length() - unit_name.length());
				}
				loc = name;
			}

			if (name.equals("tstamp")) {
				ts_ind = true;
				continue;
			}
			if (name.equals("nullind")) {
				null_ind = true;
				continue;
			}

			long mtyp = H5.H5Tget_member_type(file_tid, i);
			int mclass = H5.H5Tget_class(mtyp);
			int len = (int) H5.H5Tget_size(mtyp);
			int subtyp;

			long array_len = len; // if it is an array
			long nest_id = 0;
			boolean isArray = false;
			if (mclass == HDF5Constants.H5T_ARRAY) {
				nest_id = H5.H5Tget_super(mtyp);
				mclass = H5.H5Tget_class(nest_id);
				len = (int) H5.H5Tget_size(nest_id);
				isArray = true;
				array_len /= len;
			}

			RpMetric metric = null;
			if (mclass == HDF5Constants.H5T_STRING) { // C_S1) {
				metric = new RpMetric(loc, name, name, null, DataTyp.STRING_TYP);
				metric.setSamplesPerPacket((int) len);
			} else if (mclass == HDF5Constants.H5T_INTEGER) {
				if (len == INTEGERSIZE) {
					subtyp = (isArray) ? DataTyp.INT_ARR_TYP : DataTyp.INT_TYP;
				} else if (len == LONGSIZE) {
					subtyp = (isArray) ? DataTyp.INVALID_ARR_TYP : DataTyp.LONG_TYP;
				} else if (len == BYTESIZE) {
					subtyp = (isArray) ? DataTyp.INVALID_ARR_TYP : DataTyp.BYTE_TYP;
				} else {
					log.error("UNEXPECTED data type: {}/ {}", mtyp, mclass);
					assert (false) : "UNEXPECTED data type";
					subtyp = DataTyp.INT_TYP;
				}
				metric = RpUtil.createRpMetric(loc, name, null, unit, subtyp);

				applyHints(metric, stream_hint, loc, isArray, array_len);
			} else if (mclass == HDF5Constants.H5T_FLOAT) {
				if (len == FLOATSIZE) {
					subtyp = (isArray) ? DataTyp.FLOAT_ARR_TYP : DataTyp.FLOAT_TYP;
				} else if (len == DOUBLESIZE) {
					subtyp = (isArray) ? DataTyp.DOUBLE_ARR_TYP : DataTyp.DOUBLE_TYP;
				} else {
					log.error("Unknown float type len/bytes={}", len);
					subtyp = -1;
				}
				metric = RpUtil.createRpMetric(loc, name, null, unit, subtyp);
				applyHints(metric, stream_hint, loc, isArray, array_len);
			} else if (mclass == HDF5Constants.H5T_BITFIELD) {
				metric = RpUtil.createRpMetric(loc, name, null, unit, DataTyp.BYTE_TYP);
			} else if (mclass == HDF5Constants.H5T_COMPOUND) {
				String strerr = "Unexpected compount type";
				log.error(strerr);
				assert (false) : strerr;
			} else {
				String strerr = "Unknown class: mclass=" + mclass;
				Field[] fields = HDF5Constants.class.getFields();
				HDF5Constants consts = new HDF5Constants();
				for (Field f : fields) {
					try {
						int val = f.getInt(consts);
						if (val == mclass) {
							log.info("field: " + f.getName() + "=" + f.getInt(consts));
						}
					} catch (IllegalArgumentException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IllegalAccessException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				log.error("?" + strerr);
				assert (false) : strerr;
			}

			if (metric != null) {
				metric.setH5FieldName(h5_field_name);
			}

			if (nest_id > 0) {
				H5.H5Tclose(nest_id);
			}

			if (metric != null) {
				mlist.add(metric);
			}
		}

		RpMetric[] metrics = new RpMetric[mlist.size()];
		mlist.toArray(metrics);

		H5DatasetCODEC codec = null;
		try {
			codec = new H5DatasetCODEC(PiConstants.HDF5_EX_VERSION, metrics, ts_ind, null_ind);
		} catch (HDF5Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		codec.setFileTID(file_tid);

		return codec;
	}

	private static void applyHints(RpMetric metric, RpStream stream_hint, String loc, boolean isArray, long array_len) {
		int FIXME_BAD_sample_rate = (int) array_len * 5; // FIXME: only works for
		// drager delta
		if (isArray) {
			Integer sample_rate = -1;
			if (stream_hint != null) {
				RpMetric ref_desc = IntfUtil.getMetricByCode(stream_hint, loc);
				if (ref_desc == null) {
					int pos = loc.indexOf('.');
					if (pos > 0) {
						ref_desc = IntfUtil.getMetricByCode(stream_hint, loc.substring(0, pos));
					}
				}
				if (ref_desc == null) {
					// this is not expected! Does this happen?
					ref_desc = IntfUtil.getMetricByLoc(stream_hint, loc);
				}
				if (ref_desc == null) {
					log.error("COULD NOT GET SAMPLE RATE FROM CONF FOR LOC={}", loc);
				} else {
					sample_rate = ref_desc.getSampleRate();
					metric.setLocation(ref_desc.getLocation());
					metric.setCode(ref_desc.getCode());
					metric.setName(ref_desc.getName());
					metric.setUnit(ref_desc.getUnit());
				}
			}
			if (sample_rate == null || sample_rate < 0) {
				sample_rate = FIXME_BAD_sample_rate;
				log.error("FIXME: bad sample rate probably not {}", FIXME_BAD_sample_rate);
			}
			metric.setSampleRate(sample_rate);
			metric.setSamplesPerPacket((int) array_len);
		}
	}

	private static String getUnitName(String s) {
		s = s.toLowerCase();
		for (String u : known_units) {
			u = "." + u.toLowerCase();
			if (s.endsWith(u)) {
				return u;
			}
		}
		return null;
	}

	public static void writeFileVersion(long file_id, int version) throws NullPointerException, HDF5Exception {
		/*
		 * write driver class
		 */
		writeIntAttribute(file_id, "fileVersion", version);
	}

	public static void writeTypesAndAttributes(long parent_id, RpMetric[] metrics) throws HDF5Exception {

		int tot = 0;
		if (metrics != null) {
			tot += metrics.length;
		}

		if (tot == 0) {
			// this is OK...metrics may jest be defined post-hoc...or alarms
			// only...or demographics only
			return;
		}

		if (metrics != null) {
			for (RpMetric m : metrics) {
				if (m instanceof CompositeDescription) {
					CompositeDescription c = (CompositeDescription) m;
					tot += ((CompositeDescription) m).getSamplesPerPacket();
				}
			}
		}

		if (PiHdf5Exporter.VERSION < 4) {
			// actually obsolete, but kept here for reference
			writeSignalDescriptions(parent_id, tot, metrics);
		} else {
			writeMetaDescriptions(parent_id, tot, metrics);
		}
	}

	private static void writeMetaDescriptions(long parent_id, int tot, RpMetric[] metrics)
			throws NullPointerException, HDF5Exception {
		long[] dims = { tot };
		long[] maxdims = { tot };

		if (meta_codec == null) {
			meta_codec = new H5DatasetCODEC(PiHdf5Exporter.VERSION, IntfUtil.getMetrics(MetaInfo.class), false, false);
		}
		long aspace = H5.H5Screate_simple(1, dims, maxdims);

		long attr = H5.H5Acreate(parent_id, "meta", meta_codec.getFileTID(), aspace, HDF5Constants.H5P_DEFAULT,
				HDF5Constants.H5P_DEFAULT);

		int idx = 0;
		MetaInfo[] metas = new MetaInfo[tot];
		for (RpMetric m : metrics) {

			MetaInfo meta = new MetaInfo();
			meta.setLoc(m.getLocation());
			meta.setCode(m.getCode());
			meta.setDesc(m.getName());
			RpUnit u = m.getUnit();
			if (u != null) {
				meta.setUnit(u.getUnitName());
				if (u instanceof RpLinearUnit) {
					RpLinearUnit lu = (RpLinearUnit) u;
					meta.setLu_b(lu.getB());
					meta.setLu_m(lu.getM());
				}
				if (u instanceof RpPrecisionUnit) {
					RpPrecisionUnit pu = (RpPrecisionUnit) u;
					meta.setPu_p(pu.getPrecision());
				}
			}
			Integer sr = m.getSampleRate();
			if (sr != null) {
				meta.setRate(sr);
			}
			Integer spp = m.getSamplesPerPacket();
			if (spp != null) {
				meta.setSpp(spp);
			}
			Integer subtyp = m.getSubtyp();
			if (subtyp != null) {
				meta.setSubtyp(subtyp);
			}
			metas[idx++] = meta;
		}

		if (idx != tot) {
			log.error("FIXME: composites not handled correctly.");
		}
		int sz = 0;
		for (MetaInfo meta : metas) {
			sz += meta_codec.getTotalDataSize(1, meta);
		}
		ByteBuffer bb = ByteBuffer.allocate(sz);

		for (MetaInfo meta : metas) {
			meta_codec.encode(meta, bb);
		}
		int ret = H5.H5Awrite(attr, meta_codec.getFileTID(), bb.array());
		H5.H5Aclose(attr);
		H5.H5Sclose(aspace);
	}

	@Deprecated
	private static void writeSignalDescriptions(long parent_id, int tot, RpMetric[] metrics)
			throws NullPointerException, HDF5Exception {
		long[] dims = { tot };
		long[] maxdims = { tot };
		long aspace = H5.H5Screate_simple(1, dims, maxdims);

		long filetype_id = H5Util.createTypes(H5SignalDescription.getDataSize(), H5SignalDescription.memberDims,
				H5SignalDescription.memberNames, H5SignalDescription.memberFileTypes,
				H5SignalDescription.memberStorage);

		long attr = H5.H5Acreate(parent_id, "signals", filetype_id, aspace, HDF5Constants.H5P_DEFAULT,
				HDF5Constants.H5P_DEFAULT);

		ByteBuffer bb = ByteBuffer.allocate(H5SignalDescription.getTotalDataSize(tot));

		byte[] write_data = H5SignalDescription.encode(bb, metrics);
		int ret = H5.H5Awrite(attr, filetype_id, write_data);
		H5.H5Aclose(attr);
		H5.H5Sclose(aspace);

	}

	public static void remove(long file_id, String grp_name) throws HDF5LibraryException, NullPointerException {
		H5.H5Ldelete(file_id, grp_name, HDF5Constants.H5P_DEFAULT); // HDF5Constants.H5F_ACC_DEFAULT);
	}

	public static long getRecordTime(long dataset_id, long fspace, long mspace, long tid, long pos)
			throws NullPointerException, IllegalArgumentException, HDF5Exception {
		long[] start = { pos };
		long[] count = { 1 };

		long size = H5.H5Tget_size(tid);

		H5.H5Sselect_hyperslab( //
				fspace, // file space
				HDF5Constants.H5S_SELECT_SET, // command
				start, // start
				null, // stride
				count, // count
				null); // set block to 1

		byte[] read_data = new byte[(int) size];
		H5.H5Dread(dataset_id, tid, mspace, fspace, HDF5Constants.H5P_DEFAULT, read_data);
		ByteBuffer bb = ByteBuffer.wrap(read_data);
		long ts = bb.getLong();

		return ts;
	}

	public static void setRecordTime(long dataset_id, long fspace, long mspace, long tid, long pos, long ts)
			throws NullPointerException, IllegalArgumentException, HDF5Exception {
		long[] start = { pos };
		long[] count = { 1 };

		long size = H5.H5Tget_size(tid);

		H5.H5Sselect_hyperslab( //
				fspace, // file space
				HDF5Constants.H5S_SELECT_SET, // command
				start, // start
				null, // stride
				count, // count
				null); // set block to 1

		byte[] read_data = new byte[(int) size];
		H5.H5Dread(dataset_id, tid, mspace, fspace, HDF5Constants.H5P_DEFAULT, read_data);
		ByteBuffer bb = ByteBuffer.wrap(read_data);
		bb.putLong(ts);

		H5.H5Sselect_hyperslab( //
				fspace, // file space
				HDF5Constants.H5S_SELECT_SET, // command
				start, // start
				null, // stride
				count, // count
				null); // set block to 1
		H5.H5Dwrite(dataset_id, tid, mspace, fspace, HDF5Constants.H5P_DEFAULT, read_data);

		return;
	}

	public static void dumpTypeInfo(String parent_name, long tid) throws HDF5LibraryException {
		log.debug("{} filetype nmembers: {}  size: {}", parent_name, H5.H5Tget_nmembers(tid), H5.H5Tget_size(tid));

		int n = H5.H5Tget_nmembers(tid);
		for (int i = 0; i < n; i++) {
			String field_name = H5.H5Tget_member_name(tid, i);
			long offset = H5.H5Tget_member_offset(tid, i);
			log.debug("  {} field: {} offset: {}", parent_name, field_name, offset);
		}

	}

	public static void writeIntAttribute(long dataset_id, String attrName, int val)
			throws NullPointerException, HDF5Exception {
		int RANK1 = 1;

		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.putInt(val);
		long[] dims = { 1 };
		long[] maxdims = { 1 };
		long aspace = H5.H5Screate_simple(RANK1, dims, maxdims);

		long attr = H5.H5Acreate(dataset_id, attrName, HDF5Constants.H5T_STD_B32BE, aspace, HDF5Constants.H5P_DEFAULT,
				HDF5Constants.H5P_DEFAULT);

		byte[] buf = bb.array();
		int ret = H5.H5Awrite(attr, HDF5Constants.H5T_STD_B32BE, buf);
		H5.H5Aclose(attr);
		H5.H5Sclose(aspace);
	}

	public static int[] getJNIVersion() {
		return H5.LIB_VERSION;
	}

	public static int[] getSOVersion() {
		int[] v2 = new int[3];
		try {
			H5.H5get_libversion(v2);
		} catch (HDF5LibraryException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return v2;
	}

	// FIXME: consolidate with getSOVersion()
	public static void getLoadedVersion(int[] v2) throws Exception {
		H5.H5get_libversion(v2);
	}

	public static LinkedList<PiDatastreamImporter> readDatasetsFromGroup(long file_id, int file_version, String _parent,
			RpDevice conf) throws NullPointerException, HDF5Exception, IOException {

		opdata_Lt od = new opdata_Lt();
		od.file_id = file_id;
		od.file_version = file_version;
		od.conf = conf;
		od.parent = _parent;

		log.info("Starting iteration: {}", _parent);
		if (_parent == null || _parent.equals("/")) {
			H5.H5Literate(file_id, //
					HDF5Constants.H5_INDEX_NAME, HDF5Constants.H5_ITER_NATIVE, //
					0L, // ??
					iter_cb, // callback
					od);
		} else {
			H5.H5Literate_by_name(file_id, "/" + _parent, //
					HDF5Constants.H5_INDEX_NAME, HDF5Constants.H5_ITER_NATIVE, //
					0L, iter_cb2, od, //
					HDF5Constants.H5P_DEFAULT);
		}

		log.info("Finishing iteration: {}", _parent);

		return od.importers;
	}

	public static PiDatastreamImporter getDatasetFromName(LinkedList<PiDatastreamImporter> importers, String name) {
		for (PiDatastreamImporter intf : importers) {
			if (name.equals(intf.getName())) {
				return intf;
			}
		}
		return null;
	}

}
