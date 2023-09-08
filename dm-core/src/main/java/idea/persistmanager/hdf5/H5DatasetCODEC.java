package idea.persistmanager.hdf5;

import static idea.persistmanager.hdf5.DatatypeConstants.BYTESIZE;
import static idea.persistmanager.hdf5.DatatypeConstants.DOUBLESIZE;
import static idea.persistmanager.hdf5.DatatypeConstants.FLOATSIZE;
import static idea.persistmanager.hdf5.DatatypeConstants.INTEGERSIZE;
import static idea.persistmanager.hdf5.DatatypeConstants.LONGSIZE;

import java.nio.ByteBuffer;
import java.util.Date;

import hdf.hdf5lib.H5;
import hdf.hdf5lib.HDF5Constants;
import hdf.hdf5lib.exceptions.HDF5Exception;
import hdf.hdf5lib.exceptions.HDF5LibraryException;
import icuInterface.ConnectionStatus;
import idea.conf.CompositeDescription;
import idea.intf.DataTyp;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.model.Triplet;
import idea.persistmanager.PiCODEC;
import idea.persistmanager.PiConstants;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class H5DatasetCODEC implements PiCODEC {

	// Using Java Externalization will add a two-byte object header in
	// the stream, which needs to be called out in the datatypes.
	public int numberMembers = 0;
	public int[] memberDims = null;

	public String[] memberNames = null;
	public String[] memberLocs = null;
	public long[] memberFileTypes = null;
	public long[] memberMemTypes = null;
	public int[] memberStorage = null;
	private H5DatasetCODEC[] memberCodec = null;

	public byte[] null_flags;

	private RpMetric[] md;
	private int file_version;
	private boolean ts_ind;
	private boolean null_ind;
	private long file_tid;
	private long memory_tid;

	boolean verbose = true;
	private String[] memberH5FieldName;

	public H5DatasetCODEC(Class<? extends PersistentItem> cl) {
		try {
			init(PiConstants.HDF5_EX_VERSION, IntfUtil.getMetrics(cl), true, true);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public H5DatasetCODEC(PersistentItem item) {
		try {
			init(PiConstants.HDF5_EX_VERSION, item.getMetrics(), true, true);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public H5DatasetCODEC(int file_version, RpMetric[] metrics, boolean ts_ind, boolean null_ind) throws HDF5Exception {

		init(file_version, metrics, ts_ind, null_ind);

	}

	public void init(int file_version, RpMetric[] metrics, boolean ts_ind, boolean null_ind) throws HDF5Exception {
		this.md = metrics;
		this.file_version = file_version;
		this.ts_ind = ts_ind;
		this.null_ind = null_ind;

		int null_bytecount = 1 + ((metrics.length - 1) / 8);
		numberMembers = metrics.length;

		if (ts_ind) {
			numberMembers++; // null indicator
		}
		if (null_ind) {
			numberMembers++; // null indicator
			null_flags = new byte[null_bytecount];
		}

		memberDims = new int[numberMembers];
		memberLocs = new String[numberMembers];
		memberNames = new String[numberMembers];
		memberH5FieldName = new String[numberMembers];
		memberFileTypes = new long[numberMembers];
		memberStorage = new int[numberMembers];
		memberCodec = new H5DatasetCODEC[numberMembers];

		memberMemTypes = memberFileTypes;

		int idx = 0;
		if (ts_ind) {
			memberDims[0] = 1;
			memberNames[0] = "tstamp";
			memberH5FieldName[0] = "tstamp";
			memberLocs[0] = "tstamp";
			memberFileTypes[0] = HDF5Constants.H5T_STD_I64BE;
			memberStorage[0] = LONGSIZE;
			idx++;
		}

		if (null_ind) {

			memberNames[idx] = "nullind";
			memberH5FieldName[idx] = "nullind";
			memberLocs[idx] = "nullind";
			memberDims[idx] = null_bytecount;
			memberFileTypes[idx] = HDF5Constants.H5T_STD_I8BE;
			memberStorage[idx] = BYTESIZE;

			idx++;
		}

		for (RpMetric desc : metrics) {

			memberDims[idx] = getMemberDims(desc);
			memberNames[idx] = getMemberName(desc);
			memberH5FieldName[idx] = getMemberH5FieldName(desc);
			memberLocs[idx] = desc.getLocation();

			if (desc instanceof CompositeDescription) {
				CompositeDescription comp = (CompositeDescription) desc;

				memberDims[idx] = comp.getSamplesPerPacket();
				if (comp.getSubtyp() == DataTyp.INT_ARR_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_STD_I32BE;
					memberStorage[idx] = INTEGERSIZE;
				} else {
					// expecting subtyp to be either Object or Object[]
					RpMetric[] sub_metrics = IntfUtil.getMetrics(comp.getModel());
					H5DatasetCODEC sub_codec = new H5DatasetCODEC(file_version, sub_metrics, false, false);
					long sub_tid = sub_codec.getFileTID();
					memberFileTypes[idx] = sub_tid;
					memberStorage[idx] = sub_codec.getDataSize();
					memberCodec[idx] = sub_codec;
					// an array of ints
				}

			} else if (desc instanceof RpMetric) {
				Integer subtyp = desc.getSubtyp();
				if (subtyp == null) {
					subtyp = DataTyp.INT_TYP;
				}

				if (subtyp == DataTyp.INT_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_STD_I32BE;
					memberStorage[idx] = INTEGERSIZE;
				} else if (subtyp == DataTyp.LONG_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_STD_I64BE;
					memberStorage[idx] = LONGSIZE;
				} else if (subtyp == DataTyp.FLOAT_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_IEEE_F32BE;
					memberStorage[idx] = FLOATSIZE;
				} else if (subtyp == DataTyp.DOUBLE_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_IEEE_F64BE;
					memberStorage[idx] = DOUBLESIZE;
				} else if (subtyp == DataTyp.BYTE_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_STD_I8BE;
					memberStorage[idx] = BYTESIZE;
				} else if (subtyp == DataTyp.BOOLEAN_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_STD_I8BE;
					memberStorage[idx] = BYTESIZE;
				} else if (subtyp == DataTyp.STRING_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_C_S1;
					int spp = 64;
					if (desc.getSamplesPerPacket() == null) {
						log.error("unexpected NULL int length in H5T_C_S1");
					} else {
						spp = desc.getSamplesPerPacket();
					}
					if( spp > 1 ) {
						log.warn("FIXME: Small problem here...probably memory leak");
						memberFileTypes[idx] = H5.H5Tcopy(HDF5Constants.H5T_C_S1);
						H5.H5Tset_size(memberFileTypes[idx], spp);
					}
					memberStorage[idx] = spp;  //This is the storage size...not 1
					memberDims[idx] = 1;
				} else if (subtyp == DataTyp.INT_ARR_TYP) {
					int spp = desc.getSamplesPerPacket();
					if (spp > 0) {
						memberFileTypes[idx] = HDF5Constants.H5T_STD_I32BE;
					} else {
						memberFileTypes[idx] = H5.H5Tvlen_create(HDF5Constants.H5T_STD_I32BE);
					}
					memberStorage[idx] = INTEGERSIZE;
					memberDims[idx] = spp;
				} else if (subtyp == DataTyp.FLOAT_ARR_TYP) {
					int spp = desc.getSamplesPerPacket();
					if (spp > 0) {
						memberFileTypes[idx] = HDF5Constants.H5T_IEEE_F32BE;
					} else {
						memberFileTypes[idx] = H5.H5Tvlen_create(HDF5Constants.H5T_IEEE_F32BE);
					}
					memberStorage[idx] = FLOATSIZE;
					memberDims[idx] = spp;
				} else if (subtyp == DataTyp.DOUBLE_ARR_TYP) {
					int spp = desc.getSamplesPerPacket();
					if (spp > 0) {
						memberFileTypes[idx] = HDF5Constants.H5T_IEEE_F64BE;
					} else {
						memberFileTypes[idx] = H5.H5Tvlen_create(HDF5Constants.H5T_IEEE_F64BE);
					}
					memberStorage[idx] = DOUBLESIZE;
					memberDims[idx] = spp;
				} else if (subtyp == DataTyp.OBJ_TYP) {
					memberFileTypes[idx] = HDF5Constants.H5T_STD_I32BE;
					memberStorage[idx] = INTEGERSIZE;
				} else {
					log.warn("UNKNOWN DESCRIPTION SUBTYPE: {}/{} SUBTYP=" + subtyp, desc.getLocation(), desc.getName());
					memberFileTypes[idx] = HDF5Constants.H5T_STD_I32BE;
					memberStorage[idx] = INTEGERSIZE;
				}
			} else {
				log.error("UNKNOWN DESCRIPTION TYPE: {}", desc);
				memberFileTypes[idx] = HDF5Constants.H5T_STD_I32BE;
				memberStorage[idx] = INTEGERSIZE;
			}

//			if (log.isDebugEnabled()) {
//				System.out.print(memberNames[idx]);
//				System.out.print(" loc=" + memberLocs[idx]);
//				System.out.print(" dim=" + memberDims[idx]);
//				System.out.print(" typ=" + memberFileTypes[idx]);
//				System.out.print(" storage=" + memberStorage[idx]);
//				System.out.println(); // memberCodec[idx]
//			}

			idx++;
		}
	}

	/*
	 * The H5 field name should be present when opening files to ensure that the
	 * name is a legal and meaningful name, however, on creating the file, the name
	 * might not be assigned yet.
	 * 
	 * This routine should never return null.
	 */
	private String getMemberH5FieldName(RpMetric desc) {
		String h5FieldName = desc.getH5FieldName();
		if (h5FieldName == null) {
			h5FieldName = desc.getCode();

			if (h5FieldName == null) {
				h5FieldName = desc.getLocation();
			}
			// fix any unacceptable characters
			desc.setH5FieldName( h5FieldName);
		}
		return h5FieldName;
	}

	private int getMemberDims(RpMetric desc) {
		int dims = 0;
		if (desc.getSubtyp() == DataTyp.STRING_TYP) {
			dims = 1;
		} else {
			Integer val = desc.getSamplesPerPacket();
			dims = (val == null) ? 0 : val;
		}
		if (dims == 0) {
			dims = 1;
		}

		return dims;
	}

	private String getMemberName(RpMetric desc) {
		String memberName;

		String code = desc.getCode();
		if (code == null) {
			code = desc.getLocation(); // LOC cannot be null
		}
		memberName = code;

		// BUT: code might not be unique.

		// 28May15 WLB removed file rev=4
		// RpUnit unit = desc.getUnit();
		// if( memberName == null || memberName.length() == 0 ) {
		// String loc = "" + desc.getLocation();
		// memberName += "!";
		// if (loc != null) {
		// memberName += loc;
		// }
		// }
		//
		// if (unit != null) {
		// memberName += "!";
		// memberName += unit.toString();
		// }

		return memberName;
	}

	// Each data member field must be shown how to be written and read.
	// Strings need to be handled by bytes.
	public PersistentItem decode(PersistentItem block, ByteBuffer bb) {

		if (log.isDebugEnabled()) {
			log.debug("codec decode start ts_ind={} null_flags={} remaining=" + bb.remaining(), ts_ind, null_flags);
			int start = bb.position();
			StringBuffer s = new StringBuffer();
			while (bb.hasRemaining()) {
				int byt = bb.get();
				if (byt < 0) {
					byt += 256;
				}
				s.append(" ");
				s.append(Integer.toHexString(byt));
			}
			log.debug("bytes start={} buf={}", start, s);
			bb.position(start);
		}

		int header_length = 0;
		if (ts_ind) {
			long time = bb.getLong();
			block.setTm(new Date(time));
			header_length++;
		}

		if (null_flags != null) {
			bb.get(null_flags);
			header_length++;
		}

		boolean null_flag = false;
		for (int i = 0; i < md.length; i++) {
			RpMetric metric = md[i];
			if (null_flags != null) {
				int byte_pos = i / 8;
				int bit_pos = i % 8;
				byte val = null_flags[byte_pos];
				int mask = 1 << bit_pos;
				null_flag = ((val & mask) == mask);
			}

			String loc = metric.getLocation();
			RpMetric item_metric = block.getMetric(loc);
			if (item_metric == null) {

				if (verbose) {

					log.error("no such element: {} ", loc);

					System.out.print("@Column(name = \"" + loc + "\", nullable = true");
					System.out.println(")");
					String data_typ = "int";
					String data_alloc = "";

					System.out.println("@Metric(loc = \"" + loc + "\", code = \"" + metric.getCode() + "\", unit = \""
							+ metric.getUnit().getUnitName() + "\")");
					System.out.println("private " + data_typ + " " + loc + data_alloc + ";");
				}
				continue;
			}

			if (metric.getSubtyp() == DataTyp.STRING_TYP) {

				StringBuffer sb = new StringBuffer();

				boolean append = true;
				for (int ii = 0; ii < metric.getSamplesPerPacket(); ii++) {
					byte ch = bb.get();
					// we have to iterate through all the bytes to correctly
					// position the buffer
					if (ch == 0) {
						append = false;
					}
					if (append)
						sb.append((char) ch);
				}
				if (!null_flag) {
					IntfUtil.setValue(block, item_metric, sb.toString());
				}
			} else if (metric.getSubtyp() == DataTyp.INT_ARR_TYP) {
				int[] values = (int[]) IntfUtil.getRawValueByLoc(block, item_metric.getLocation());

				if (values == null) {
					// WARNING: allocation probably doesn't go here
					values = new int[memberDims[i + header_length]];
					// item_metric.setValue(block, values);
					IntfUtil.setValue(block, item_metric, values);
				}

				for (int ii = 0; ii < values.length; ii++) {
					values[ii] = bb.getInt();
				}
			} else if (metric.getSubtyp() == DataTyp.FLOAT_ARR_TYP) {
				float[] values = (float[]) IntfUtil.getRawValueByLoc(block, item_metric.getLocation());

				if (values == null) {
					// WARNING: allocation probably doesn't go here
					values = new float[memberDims[i + header_length]];
					// item_metric.setValue(block, values);
					IntfUtil.setValue(block, item_metric, values);
				}

				for (int ii = 0; ii < values.length; ii++) {
					values[ii] = bb.getFloat();
				}
			} else if (metric.getSubtyp() == DataTyp.DOUBLE_ARR_TYP) {
				double[] values = (double[]) IntfUtil.getRawValueByLoc(block, item_metric.getLocation());

				if (values == null) {
					// WARNING: allocation probably doesn't go here
					values = new double[memberDims[i + header_length]];
					// item_metric.setValue(block, values);
					IntfUtil.setValue(block, item_metric, values);
				}

				for (int ii = 0; ii < values.length; ii++) {
					values[ii] = bb.getDouble();
				}
			} else {
				Object val;
				int startpos = bb.position();
				if (metric.getSubtyp() == DataTyp.INT_TYP) {
					val = bb.getInt();

				} else if (metric.getSubtyp() == DataTyp.LONG_TYP) {
					val = bb.getLong();
				} else if (metric.getSubtyp() == DataTyp.FLOAT_TYP) {
					val = bb.getFloat();
				} else if (metric.getSubtyp() == DataTyp.DOUBLE_TYP) {
					val = bb.getDouble();
				} else if (metric.getSubtyp() == DataTyp.BYTE_TYP) {
					val = bb.get();
				} else if (metric.getSubtyp() == DataTyp.BOOLEAN_TYP) {
					byte b = bb.get();
					val = (b == 0) ? false : true;
				} else if (metric.getSubtyp() == DataTyp.INT_ARR_TYP) {
					// CURRENTLY CANNOT HAPPEN!!!
					int count = memberDims[i + header_length];
					if (count != 3) {
						log.error("Expecting INT_ARR_TYP to be triplet");
						System.exit(0);
					}
					Triplet triplet = new Triplet();
					triplet.setP_SYS(bb.getInt());
					triplet.setP_DIA(bb.getInt());
					triplet.setP_MAP(bb.getInt());

					val = triplet;

					log.error("FIXME: remove next two lines...development only");
					IntfUtil.setValue(block, item_metric, triplet);
					val = null; // TEMPORARY fix for null indicator
				} else {
					log.error("UNKNOWN METRIC SUBTYPE: {} for M={}", metric.getSubtyp(), metric.getName());
					val = null;
				}
				if (!null_flag) {
					if (file_version < 2 && val instanceof Integer && ((Integer) val).intValue() == -1) {
						// if importing old formatted data,
					} else {
						IntfUtil.setValue(block, item_metric, val);
					}
				}
				// if (log.isDebugEnabled()) {
				// log.debug("decode metric start={} end=" + bb.position() + " typ={} null=" +
				// null_flag + " value="
				// + val, startpos, metric.getSubtyp());
				// }
			}
		}

		return block;
	}

	private int getMemberIndex(RpMetric desc) { // TAKES INTO ACCOUNT
												// tstamp and
												// optionally
												// nullind
		int idx = -1;
		String loc = desc.getLocation();
		for (int i = 0; i < numberMembers; i++) {
			if (loc.equals(memberLocs[i])) {
				idx = i;
				break;
			}
		}
		return idx;
	}

	public int getDataSize() {
		int data_size = 0;
		for (int indx = 0; indx < numberMembers; indx++)
			data_size += memberStorage[indx] * memberDims[indx];
		return data_size;
	}

	public int getTotalDataSize(int qty, PersistentItem item) {
		int data_size = 0;

		int md_offset = 0;

		if (ts_ind)
			md_offset++;
		if (null_ind)
			md_offset++;

		for (int indx = 0; indx < numberMembers; indx++) {
			int memberSize = memberStorage[indx];
			int dims = memberDims[indx];

			if (dims <= 0) {

				Object raw = IntfUtil.getRawValue(item, md[indx - md_offset]);
				if (raw == null) {
					dims = 0;
				} else if (raw instanceof int[]) {
					int[] arr = (int[]) raw;
					dims = arr.length;
				} else {
					log.error("UNKNOWN ITEM LENGTH: " + raw);
					dims = 0;
				}

			}
			data_size += memberSize * dims;
		}
		return qty * data_size;
	}

	public RpMetric[] getMetrics() {
		return md;
	}

	public long getFileTID() throws HDF5LibraryException {
		if (file_tid == 0) {
			return getMemoryTID();
			// file_tid = H5Util.createTypes(getDataSize(), memberDims, memberNames,
			// memberFileTypes, memberStorage);
		}
		return file_tid;
	}

	public long getMemoryTID() throws HDF5LibraryException {
		if (memory_tid == 0) {
			memory_tid = H5Util.createTypes(getDataSize(), memberDims, memberH5FieldName, memberFileTypes,
					memberStorage);
		}
		return memory_tid;
	}

	public void setFileTID(long filetype_id) {
		file_tid = filetype_id;
	}

	public void encode(PersistentItem block, ByteBuffer bb) {
		if (ts_ind) {
			long l = 0;
			Date tm = block.getTm();
			if (tm != null) {
				l = tm.getTime();
			}
			bb.putLong(l);
		}

		if (null_flags != null) {
			for (int i = 0; i < null_flags.length; i++) {
				null_flags[i] = 0;
			}
			for (int i = 0; i < md.length; i++) {
				RpMetric metric = md[i];
				String loc = metric.getLocation();
				Object vval = IntfUtil.getRawValue(block, metric);
				if (vval == null) {
					int null_byt = i / 8;
					int null_bit = i % 8;
					null_flags[null_byt] |= 1 << null_bit;
				}
			}

			bb.put(null_flags);
		}

		for (RpMetric metric : md) {
			Object val = IntfUtil.getRawValue(block, metric);
			int idx = getMemberIndex(metric); // takes into account tstamp and
												// optionally nullind
			if (idx < 0) {
				log.error("mmetric not found: {}", metric);
			}
			int count = memberDims[idx];

			H5DatasetCODEC codec = memberCodec[idx];
			int bytes = count * memberStorage[idx];
			if (val == null) {

				// while (bytes > 0) {
				// bb.put((byte) 0);
				// bytes--;
				// }
				bb.position(bb.position() + bytes);

			} else if (codec != null) {
				if (metric.getSubtyp() == DataTyp.OBJ_ARR_TYP) {
					Object[] arr = (Object[]) val;
					for (Object o : arr) {
						log.warn("NOT SURE ABOUT THIS OBJECT-ARRAY ENCODING!!!");
						codec.encodeOneValue(bb, count, bytes, val, metric.getSubtyp());
					}
				} else {
					// codec.encode(val, bb); // simply encode 1 value
					codec.encodeOneValue(bb, count, bytes, val, metric.getSubtyp());
				}
			} else {

				encodeOneValue(bb, count, bytes, val, metric.getSubtyp());
			}

		}

		return;
	}

	private void encodeOneValue(ByteBuffer bb, int count, int tot_bytes, Object val, Integer subtyp) {
		switch (subtyp) {
		case DataTyp.INT_TYP:
			bb.putInt((Integer) val);
			break;
		case DataTyp.INT_ARR_TYP: {
			int[] vals = (int[]) val;
			for (int v : vals) {
				count--;
				if (count < 0) {
					log.error("too many values: {} != {}", vals.length, count);
					break;
				}
				bb.putInt(v);
			}
			if (count > 0) {
				log.error("not enough values, padding with -1's: {} != {}", vals.length, count);
				while (count-- > 0) {
					bb.putInt(-1);
				}
			}
		}
			break;
		case DataTyp.FLOAT_ARR_TYP: {
			float[] vals = (float[]) val;
			for (float v : vals) {
				count--;
				if (count < 0) {
					log.error("too many values: {} != {}", vals.length, count);
					break;
				}
				bb.putFloat(v);
			}
			if (count > 0) {
				log.error("not enough values, padding with -1's: {} != {}", vals.length, count);
				while (count-- > 0) {
					bb.putFloat(-1);
				}
			}
		}
			break;
		case DataTyp.DOUBLE_ARR_TYP: {
			double[] vals = (double[]) val;
			for (double v : vals) {
				count--;
				if (count < 0) {
					log.error("too many values: {} != {}", vals.length, count);
					break;
				}
				bb.putDouble(v);
			}
			if (count > 0) {
				log.error("not enough values, padding with -1's: {} != {}", vals.length, count);
				while (count-- > 0) {
					bb.putDouble(-1);
				}
			}
		}
			break;
		case DataTyp.LONG_TYP:
			bb.putLong((Long) val);
			break;
		case DataTyp.DOUBLE_TYP:
			bb.putDouble((Double) val);
			break;
		case DataTyp.BYTE_TYP:
			bb.put((Byte) val);
			break;
		case DataTyp.BOOLEAN_TYP:
			bb.put(((Boolean) val) ? (byte) 1 : 0);
			break;
		case DataTyp.FLOAT_TYP:
			bb.putFloat((Float) val);
			break;
		case DataTyp.STRING_TYP:
			String sval = (String) val;
			byte[] src = null;
			if (val != null && sval.length() > 0) {
				src = sval.getBytes();
			}

			for (int i = 0; i < tot_bytes; i++) {
				if (src != null && i < src.length) {
					bb.put(src[i]);
				} else {
					bb.put((byte) 0);
				}
			}
			break;
		case DataTyp.OBJ_TYP:
			//log.error("Save the PI child!!! then store oid");
			if (val instanceof PersistentItem) {
				PersistentItem it = (PersistentItem) val;
				bb.putInt((int) it.getOid());
			} else if (val instanceof ConnectionStatus) {
				ConnectionStatus cs = (ConnectionStatus) val;
				bb.putInt(cs.getCode());
			} else {
				log.error("unidentified item/expecting child persistentitem: {}", val);
				bb.putInt(-1);
			}
			break;
		default:
			log.error("UNKOWN encode SUBTYP: {}", subtyp);
			bb.putInt((Integer) val);
		}
	}

	public void destroy() throws HDF5LibraryException {
		if (file_tid != 0) {
			H5.H5Tclose(file_tid);
			file_tid = 0;
		}
		if (memory_tid != 0) {
			H5.H5Tclose(memory_tid);
			memory_tid = 0;
		}
	}

}
