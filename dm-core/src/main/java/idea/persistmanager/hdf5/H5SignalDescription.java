package idea.persistmanager.hdf5;

import static idea.persistmanager.hdf5.DatatypeConstants.INTEGERSIZE;

import java.nio.ByteBuffer;
import java.util.LinkedList;

import hdf.hdf5lib.HDF5Constants;
import icuInterface.RpUtil;
import idea.conf.CompositeDescription;
import idea.intf.DataTyp;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class H5SignalDescription {

	// Using Java Externalization will add a two-byte object header in
	// the stream, which needs to be called out in the datatypes.

	public static final int NAMESTRINGSIZE = 20;
	public static final int CODESTRINGSIZE = 20;
	public static final int UNITSTRINGSIZE = 10;
	public static final int LOCATIONSTRINGSIZE = 80;

	public static int numberMembers = 8;
	public static int[] memberDims = { 1, 1, 1, 1, 1, 1, 1, 1 };

	public static String[] memberNames = { "ftyp", "name", "code", "unit", "sigtyp", "rate", "spp", "location" };
	public static long[] memberFileTypes = { // 
	HDF5Constants.H5T_STD_I32BE, // ftyp
			HDF5Constants.H5T_C_S1, // name
			HDF5Constants.H5T_C_S1, HDF5Constants.H5T_C_S1, // code,unit
			HDF5Constants.H5T_STD_I32BE, // typ
			HDF5Constants.H5T_STD_I32BE, // rate
			HDF5Constants.H5T_STD_I32BE, // spp
			HDF5Constants.H5T_C_S1 // location
	};
	public static int[] memberStorage = { INTEGERSIZE, // ftype
			NAMESTRINGSIZE, // name
			CODESTRINGSIZE, UNITSTRINGSIZE, // code,unit
			INTEGERSIZE, // typ
			INTEGERSIZE, // rate
			INTEGERSIZE, // spp
			LOCATIONSTRINGSIZE // location
	};

	// Data size is the storage size for the members not the object.
	// Java Externalization also adds a 4-byte "Magic Number" to the
	// beginning
	// of the data stream
	public static int getTotalDataSize(int qty) {
		int data_size = 0;
		for (int indx = 0; indx < numberMembers; indx++) {
			data_size += memberStorage[indx] * memberDims[indx];
		}
		return qty * data_size;
	}

	public static int getDataSize() {
		int data_size = 0;
		for (int indx = 0; indx < numberMembers; indx++)
			data_size += memberStorage[indx] * memberDims[indx];
		return data_size;
	}

	public static int getOffset(int memberItem) {
		int data_offset = 0;
		for (int indx = 0; indx < memberItem; indx++)
			data_offset += memberStorage[indx];
		return data_offset;
	}

	// Each data member field must be shown how to be written and read.
	// Strings need to be handled by bytes.
	public static RpMetric[] decode(byte[] dat, int subsett) {

		LinkedList<RpMetric> ll = new LinkedList<RpMetric>();

		CompositeDescription comp = null;

		ByteBuffer bb = ByteBuffer.wrap(dat);
		while (bb.position() < dat.length) {
			RpMetric ent = null;
			int typ = bb.getInt();

			String name = decodeString(bb, NAMESTRINGSIZE);
			String code = decodeString(bb, CODESTRINGSIZE);
			String unitName = decodeString(bb, UNITSTRINGSIZE);
			int codetype = bb.getInt();
			int rate = bb.getInt();
			int spp = bb.getInt();
			String loc = decodeString(bb, LOCATIONSTRINGSIZE);

			RpLinearUnit unit = new RpLinearUnit(1.0, 0.0, unitName);
			if (subsett == 0) {
				// decode all metrics
				ent = RpUtil.createRpMetric(loc, code, name, unit, subsett);
				ent.setSampleRate(rate);
				ent.setSamplesPerPacket(spp);
			} else if (subsett == 1) {
				if (typ == 1) {
					ent = RpUtil.createRpMetric(loc, code, name, unit, subsett);
				} else if (typ == 2) {
					// waveform....ignore
				} else if (typ == 3) {
					ent = new RpMetric( loc, code, name, null, DataTyp.STRING_TYP);
					ent.setSamplesPerPacket(spp);
				} else if (typ == 4) {
					comp = new CompositeDescription(loc, code, name);
					ent = comp;
				} else if (typ == 5) {
					RpMetric comp_item = RpUtil.createRpMetric(loc, code, name, unit, subsett);
					if (comp == null) {
						log.error("subitem found before composite item");
					} else {
						comp.add(comp_item);
					}
				} else if (typ == 0x11) {
					// ignore, this is a metric setting
				} else if (typ == 0x13) {
					// ignore, this is a text setting
				} else {
					log.error("Invalid comp item typ={} name{}", typ, name);
				}

				if (ent != null) {
					ent.setSampleRate(rate);
					ent.setSamplesPerPacket(spp);
				}
			} else if (subsett == 2) {
				if (typ == 2) {
					ent = RpUtil.createRpMetric(loc, code, name, rate, spp, unit);
				}
			} else if (subsett == 3) {
				if (typ == 0x11) {
					ent = RpUtil.createRpMetric(loc, code, name, unit, subsett);
				}
			}

			if (ent != null) {
				ll.add(ent);
			}
		}

		RpMetric[] ar = new RpMetric[ll.size()];
		return ll.toArray(ar);
	}

	private static String decodeString(ByteBuffer bb, int len) {
		StringBuffer b = new StringBuffer(len);
		for (int idx = 0; idx < len; idx++) {
			char ch = (char) bb.get();
			if (ch != 0) {
				b.append(ch);
			}
		}
		return b.toString();
	}

	public static byte[] encode(ByteBuffer bb, RpMetric[] metrics) {
		byte[] ret = encode(bb, metrics, 0);
		return ret;
	}

	public static byte[] encode(ByteBuffer bb, RpMetric[] metrics, int offset) {

		int idx = 0;
		if (metrics != null) {
			for (RpMetric metric : metrics) {
				int descType = 1 + offset;
				Integer rate = metric.getSampleRate();
				Integer spp = metric.getSamplesPerPacket();
				RpUnit unit = metric.getUnit();
				String unitName = null;
				if (unit != null) {
					unitName = unit.getUnitName();
				}
				if (spp == null) {
					spp = 0;
				}
				if (rate == null) {
					rate = 0;
				}
				if (metric.getSubtyp() == DataTyp.STRING_TYP ) {
					descType = 3 + offset;  // ?? Why the exception?
				}
				if (metric instanceof CompositeDescription) {
					// CompositeDescription comp = (CompositeDescription) metric;
					descType = 4 + offset;
				}
				bb.putInt(descType);
				String name = metric.getName();
				if (name == null || name.length() == 0) {
					name = metric.getCode();
				}
				if (name == null) {
					name = "V" + (++idx);
				}
				bb.put(encodeString(name, NAMESTRINGSIZE));
				bb.put(encodeString(metric.getCode(), CODESTRINGSIZE));
				bb.put(encodeString(unitName, UNITSTRINGSIZE));
				bb.putInt(0); // metric.getSignalType().getCode());
				bb.putInt(rate);
				bb.putInt(spp);
				bb.put(encodeString(metric.getLocation(), LOCATIONSTRINGSIZE));
			}
		}

		return bb.array();
	}

	private static byte[] encodeString(String text, int len) {

		byte[] buf = new byte[len];

		for (int idx = 0; idx < len; idx++) {
			if (text != null && idx < text.length())
				buf[idx] = (byte) text.charAt(idx);
			else
				buf[idx] = 0;
		}
		return buf;
	}

}
