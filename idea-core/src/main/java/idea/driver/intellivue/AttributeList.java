package idea.driver.intellivue;

import static idea.driver.intellivue.C.NOM_ATTR_COLOR;
import static idea.driver.intellivue.C.NOM_ATTR_DEV_AL_COND;
import static idea.driver.intellivue.C.NOM_ATTR_DISP_RES;
import static idea.driver.intellivue.C.NOM_ATTR_ID_BED_LABEL;
import static idea.driver.intellivue.C.NOM_ATTR_ID_HANDLE;
import static idea.driver.intellivue.C.NOM_ATTR_ID_LABEL;
import static idea.driver.intellivue.C.NOM_ATTR_ID_LABEL_STRING;
import static idea.driver.intellivue.C.NOM_ATTR_ID_MODEL;
import static idea.driver.intellivue.C.NOM_ATTR_ID_TYPE;
import static idea.driver.intellivue.C.NOM_ATTR_MDS_GEN_INFO;
import static idea.driver.intellivue.C.NOM_ATTR_METRIC_SPECN;
import static idea.driver.intellivue.C.NOM_ATTR_NET_ADDR_INFO;
import static idea.driver.intellivue.C.NOM_ATTR_NU_CMPD_VAL_OBS;
import static idea.driver.intellivue.C.NOM_ATTR_NU_VAL_OBS;
import static idea.driver.intellivue.C.NOM_ATTR_PCOL_SUPPORT;
import static idea.driver.intellivue.C.NOM_ATTR_POLL_NU_PRIO_LIST;
import static idea.driver.intellivue.C.NOM_ATTR_POLL_RTSA_PRIO_LIST;
import static idea.driver.intellivue.C.NOM_ATTR_SA_CALIB_I16;
import static idea.driver.intellivue.C.NOM_ATTR_SA_CMPD_VAL_OBS;
import static idea.driver.intellivue.C.NOM_ATTR_SA_SPECN;
import static idea.driver.intellivue.C.NOM_ATTR_SA_VAL_OBS;
import static idea.driver.intellivue.C.NOM_ATTR_SYS_SPECN;

import java.nio.ByteBuffer;
import java.util.HashSet;
import java.util.Iterator;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class AttributeList {
	int verbose = 2;

	HashSet<AVAType> hm = new HashSet<AVAType>();

	public AttributeList() {

	}

	private void add(short attribute_id, Object value) {
		AVAType ava = new AVAType(attribute_id, value);
		hm.add(ava);
	}

	public Object get(int attrib_id) {
		Iterator<AVAType> it = hm.iterator();
		while (it.hasNext()) {
			AVAType ava = it.next();
			if (attrib_id == ava.getAttributeId()) {
				return ava.getValue();
			}
		}
		return null;
	}

	public ByteBuffer encode(ByteBuffer bb) {
		short avasize = 0;

		for (AVAType ava : hm) {
			avasize += ava.sizeof();
		}

		if (bb == null) {
			bb = ByteBuffer.allocate(avasize + 4);
		}

		short count = (short) hm.size();
		bb.putShort(count);
		bb.putShort(avasize);
		if (count != 0) {
			for (AVAType ava : hm) {
				ava.encode(bb);
			}
		}

		bb.limit(bb.position());
		return bb;
	}

	public void add(AVAType typ) {

		hm.add(typ);
	}

	public static int parse(AttributeList al, ByteBuffer bb) {

		short count = bb.getShort();
		short length = bb.getShort();

		int pos1 = bb.position();

		return count;
	}

	public static AttributeList parse(ByteBuffer bb) {

		AttributeList al = new AttributeList();

		int pos0 = bb.position();

		short count = bb.getShort();
		short length = bb.getShort();

		int pos1 = bb.position();

		assert (count >= 0) : "[parseAttributeList] attribute count < 0";
		if (count < 0) {
			log.error("NEGATIVE ATTRIBUTE COUNT: pos=" + bb.position());
			return null;
		}

		// System.out.println( " parsing attribute-list count=" + count +
		// " length=" + length + " pos1=" + pos1);
		attrib_processing: for (int i = 0; i < count; i++) {
			short attribute_id = bb.getShort(); // OIDType u_16
			short attr_length = bb.getShort(); // length

			// System.out.println( "pos2:" + bb.position() +
			// " attrib parsing: 0x" + Integer.toHexString(attribute_id) +
			// " attr_length: " + attr_length );

			switch (attribute_id) {
			case C.NOM_ATTR_PT_NOTES1: //
			case C.NOM_ATTR_PT_NOTES2: //
			case C.NOM_ATTR_PT_BSA: // = 0x0956; // Patient BSA
			case C.NOM_ATTR_PT_DEMOG_ST: // = 0x0957; // Pat Demo State
			case C.NOM_ATTR_PT_DOB: // = 0x0958; // Patient Date of Birth
			case C.NOM_ATTR_PT_ID: // = 0x095A; // Patient ID
			case C.NOM_ATTR_PT_SEX: // = 0x0961; // Patient Sex
			case C.NOM_ATTR_PT_TYPE: // = 0x0962; // Patient Type
			case C.NOM_ATTR_PT_AGE:
			case C.NOM_ATTR_PT_HEIGHT:
			case C.NOM_ATTR_PT_WEIGHT:
				// case C.NOM_ATTR_PT_ID_INT: ... duplicate ID, see below
			case C11073.MDC_ATTR_PT_PACED_MODE:
				bb.position(bb.position() + attr_length);
				break;
			case C.NOM_ATTR_PT_NAME_FAMILY: // = 0x095C; // Family Name
			case C11073.MDC_ATTR_PT_NAME_MIDDLE:
			case C.NOM_ATTR_PT_NAME_GIVEN: // = 0x095D; // Given Name
				String name = parseStringAttribute(bb);
				al.add(attribute_id, name);
				break;

			case C.NOM_POLL_PROFILE_SUPPORT:
				al.add(attribute_id, PollProfileSupport.parse(bb));
				break;
			case C.NOM_ATTR_POLL_PROFILE_EXT:
				log.debug("C.NOM_ATTR_PT_ID_INT/C.NOM_ATTR_POLL_PROFILE_EXT -- duplicate attr number");
				if (attr_length == 10) {
					bb.getShort();
					bb.getInt();
					bb.getInt();
					al.add(attribute_id, "PT_ID_INT");
				} else {
					al.add(attribute_id, PollProfileExt.parse(bb));
				}
				break;

			case NOM_ATTR_DEV_AL_COND:
				log.debug("nom_attr_dev_al_cond");
				DeviceAlertCondition cond = DeviceAlertCondition.parse(bb);
				al.add(attribute_id, cond);
				break;
			case NOM_ATTR_DISP_RES:
			case NOM_ATTR_COLOR:
			case NOM_ATTR_ID_HANDLE:
				assert (attr_length == 2) : "[IntellivueDriver] : wrong attr length for " + attribute_id;
				al.add(attribute_id, bb.getShort());
				break;

			case NOM_ATTR_ID_TYPE:
			case NOM_ATTR_ID_LABEL:
			case C.NOM_ATTR_TIME_PD_SAMP:
				assert (attr_length == 4) : "[IntellivueDriver] : wrong attr length (!4) for attrib: " + attribute_id;
				al.add(attribute_id, bb.getInt());
				break;

			case NOM_ATTR_NU_VAL_OBS:
				al.add(attribute_id, parseObservedValAttribute(bb, attr_length));
				break;

			case NOM_ATTR_NU_CMPD_VAL_OBS: // compound observed value
				al.add(attribute_id, parseCompoundObservedValAttribute(bb, attr_length));
				break;

			case NOM_ATTR_SA_VAL_OBS:
				al.add(attribute_id, SaObsValue.parse(bb));
				break;

			case NOM_ATTR_SA_CMPD_VAL_OBS:
				short cmpd_count = bb.getShort();
				short cmpd_length = bb.getShort();
				SaObsValue[] arr = new SaObsValue[cmpd_count];
				for (int idx = 0; idx < cmpd_count; idx++) {
					arr[idx] = SaObsValue.parse(bb);
				}
				al.add(attribute_id, arr);
				break;

			case NOM_ATTR_SA_SPECN: {
				SimpleArraySpecn specn;
				al.add(attribute_id, specn = SimpleArraySpecn.parse(bb));
				// specn.dump();
			}
				break;

			// connection events
			case NOM_ATTR_NET_ADDR_INFO:

				IpAddressInfo addr = IpAddressInfo.parse(bb);
				System.err.println(" list.add(NOM_ATTR_NET_ADDR_INFO, addr );");

				al.add(attribute_id, addr);
				break;
			case NOM_ATTR_PCOL_SUPPORT:
				ProtoSupport proto = ProtoSupport.parse(bb);
				System.err.println("list.add(NOM_ATTR_PCOL_SUPPORT, proto );");

				al.add(attribute_id, proto);
				break;

			case NOM_ATTR_MDS_GEN_INFO:
				MdsGenSystemInfoEntry[] info = MdsGenSystemInfoEntry.parseArray(bb);
				al.add(attribute_id, info);
				break;

			case NOM_ATTR_SYS_SPECN:
				SystemSpecEntry[] system = SystemSpecEntry.parseArray(bb);
				al.add(attribute_id, system);
				break;

			case NOM_ATTR_ID_MODEL:
				SystemModel model = SystemModel.parse(bb);
				al.add(attribute_id, model);
				break;

			case NOM_ATTR_POLL_NU_PRIO_LIST:
			case NOM_ATTR_POLL_RTSA_PRIO_LIST:
				int attr_end = bb.position() + attr_length;
				Object textIdList = parseTextIdList(bb);
				al.add(attribute_id, textIdList);

				if (attr_end != bb.position()) {
					// bet there should be a count field as well as a length
					// field?
					System.err.println("Philips has a protocol/doc err in attr: " + attribute_id);
					bb.position(attr_end); //
				}

				break;

			case NOM_ATTR_ID_BED_LABEL:
			case NOM_ATTR_ID_LABEL_STRING:
				String label_string = parseStringAttribute(bb);
				al.add(attribute_id, label_string);
				break;

			// known, but ignored
			case NOM_ATTR_SA_CALIB_I16:
				parseSimpleArrayCalData(bb); // ignored
				break;

			case NOM_ATTR_METRIC_SPECN:
				al.add(attribute_id, MetricSpecn.parse(bb));
				break;

			// intentionally ignored
			case C.NOM_ATTR_SA_FIXED_VAL_SPECN: // fixed val specn...has pacer
												// and defib masks
				al.add(attribute_id, SampleArrayFixedValueSpecn.parse(bb));
				break;
			case C.NOM_ATTR_SCALE_SPECN_I16: // scaled range
												// specification....min and
												// maximum values
				al.add(attribute_id, ScaleRangeSpec16.parse(bb));
				break;
			case C11073.MDC_ATTR_SYS_ADT_ST:
				Short s = bb.getShort();
				al.add(attribute_id, s);
				break;
			case C.NOM_ATTR_NOM_VERS: // int length
			case C.NOM_ATTR_LOCALIZN: // localization...long or two ints
			case C.NOM_ATTR_MODE_OP: // length short operating mode...value 8192
			case C.NOM_ATTR_AREA_APPL: // length 2...value 2
			case C.NOM_ATTR_LINE_FREQ: // length 2...value 2
			case C.NOM_ATTR_STD_SAFETY: // length 2...value 2
			case C.NOM_ATTR_ALTITUDE: // length 2...value 0
			case C.NOM_ATTR_VMS_MDS_STAT: // length 2...value 6
			case C.NOM_ATTR_TIME_ABS: // length 8...some kind of time stamp
			case C.NOM_ATTR_TIME_REL: // length 4...a relative offset? timezon offset?
			case C.NOM_ATTR_TIME_STAMP_ABS:
			case C.NOM_SAT_O2_TONE_FREQ:
			case C.NOM_ATTR_UNDOC_F237:
			case C.NOM_ATTR_SYS_ID:
			case C.NOM_ATTR_ID_ASSOC_NO:
			case C.NOM_NOTI_MDS_CONNECT_INDIC: // during connect indication
												// message
			case C.NOM_ATTR_UNIT_CODE: // two byte...see UnitCodes.java
			case C.NOM_ATTR_METRIC_STAT: // two byte bit field ...METRIC_OFF or
											// 0
			case C.NOM_ATTR_GRID_VIS_I16:
			case C.NOM_ATTR_MODE_MSMT:
			case C.NOM_ATTR_SA_RANGE_PHYS_I16:
				log.debug("skipping known attr {} length: {}", attribute_id, attr_length);
				bb.position(bb.position() + attr_length);
				break;

			case C11073.MDC_ATTR_AL_MON_P_AL_LIST:
			case C11073.MDC_ATTR_AL_MON_T_AL_LIST:
				while (attr_length > 0) {
					byte byt = bb.get();
					if (log.isDebugEnabled()) {
						log.debug("skipping attr_al_mon list + {}", Integer.toHexString((byt >= 0) ? byt : (byt + 256)));
					}
					attr_length--;
				}
				break;
			case C.UNK_F2E1: // label_id??
			case C.UNK_F2E2:
			case C.UNK_F2E3:
			case C.UNK_F1EC: // num_vals
				String val = "";
				if (attr_length == 2) {
					short s1 = bb.getShort(); // probably a short
					val = "" + s1;
				} else if (attr_length == 4) {
					int i1 = bb.getInt(); // probably a int
					val = i1 + "==0x" + Integer.toHexString(i1);
				} else {
					bb.position(bb.position() + attr_length);
				}
				if (log.isDebugEnabled()) {
					log.warn(i + " semi-known attribute: " + attribute_id + " == 0x"
							+ Integer.toHexString(attribute_id) + " length: " + attr_length + " probable val=" + val);
				}
				break;
			default:
				if (log.isDebugEnabled()) {
					log.warn(i + " unknown attribute: " + attribute_id + " == 0x" + Integer.toHexString(attribute_id)
							+ " length: " + attr_length);
				}
				if (attr_length == 2) {
					short s1 = bb.getShort(); // probably a short
					//log.warn("{} probable attribute val: {}", i, s1);
				} else if (attr_length == 4) {
					int i1 = bb.getInt(); // probably a int
					//log.warn("{} probable attribute val: {}", i, i1);
				} else {
					bb.position(bb.position() + attr_length);
				}
				if (attr_length > 1000) {
					log.error("INVALID LENGTH...BREAK HERE: pos={}", bb.position());
					break attrib_processing;
				}
			}

		}

		int pos2 = bb.position();

		if (length != pos2 - pos1) {
			log.error("wrong end position -- break");
		}
		assert (length == pos2 - pos1) : "[parseAttributeList] length mismatch " + length + " != " + (pos2 - pos1)
				+ " pos=" + pos2;

		return al;
	}

	private static Object parseTextIdList(ByteBuffer bb) {
		short count = bb.getShort();
		short len = bb.getShort();
		int[] ids = null;
		if (count > 0) {
			ids = new int[count];
			for (int i = 0; i < count; i++) {
				ids[i] = bb.getInt();
			}
		}
		return ids;
	}

	private static float parseObservedValAttribute(ByteBuffer bb, short attr_length) {
		// NuObsValue;

		short physio_id = bb.getShort();
		int state = bb.getShort(); // measurementState
		if (state < 0)
			state += 65536;

		short unit_code = bb.getShort();
		float value = IntellivueUtil.parsePhilipsFloat(bb);

		return value;
	}

	private static float[] parseCompoundObservedValAttribute(ByteBuffer bb, short attr_length) {
		// NuObsValueCmp;

		short count = bb.getShort();
		short length = bb.getShort();
		int pos1 = bb.position();

		if (count <= 0) {
			log.error("[parseCompoundObservedValAttribute] invalid count: {}", count);
		}

		float[] value = null;
		if (count > 0) {
			value = new float[count];
		}
		for (int i = 0; i < count; i++) {
			// parseObservedValAttribute( bb );

			short physio_id = bb.getShort();
			int state = bb.getShort(); // measurementState
			if (state < 0)
				state += 65536;

			short unit_code = bb.getShort();
			value[i] = IntellivueUtil.parsePhilipsFloat(bb);

			log.debug("parseCompoundObs state={} physio_id={}", state, physio_id);

		}

		int pos2 = bb.position();
		assert (length == (pos2 - pos1)) : "[parseCompoundObservedValAttribute] data length disagreement " + length
				+ " != " + (pos2 - pos1);

		return value;
	}

	private static void parseSimpleArrayCalData(ByteBuffer bb) {
		// typedef struct {
		// FLOATType lower_absolute_value;
		// FLOATType upper_absolute_value;
		// u_16 lower_scaled_value;
		// u_16 upper_scaled_value;
		// u_16 increment;
		// u_16 cal_type;
		// #define BAR 0
		// #define STAIR 1
		// } SaCalData16;

		float lower_absolute_value = bb.getFloat();
		float upper_absolute_value = bb.getFloat();

		short lower_scaled_value = bb.getShort();
		short upper_scaled_value = bb.getShort();
		short increment = bb.getShort();
		short cal_type = bb.getShort();

		// System.out.println("   cal_data: [" + lower_absolute_value + "," +
		// upper_absolute_value + "] --> " + "["
		// + lower_scaled_value + "," + upper_scaled_value + "] incr=" +
		// increment + " cal_typ=" + cal_type);

	}

	private static String parseStringAttribute(ByteBuffer bb) {

		StringBuffer val = new StringBuffer();
		short length = bb.getShort(); // length in bytes

		boolean appending = true;

		for (short idx = 0; idx < length; idx += 2) { // reading 2 bytes at a
														// time
			char c = (char) bb.getShort(); // read a 16-bit unicode char
			int u = c;
			if (c == 0)
				appending = false;

			if (appending) {
				switch (c) {
				case 0xe145:
					val.append("subE");
					break;
				case 0xe14c:
					val.append("supL");
					break;
				case 0xE400:
					val.append("Lper");
					break;
				case 0xE401:
					val.append("hyd");
					break;
				case 0xE40D:
					val.append("*");
					break;
				case 0xE425:
					val.append("vdot");
					break;
				default:
					val.append(c);
				}
			}
		}

		return val.toString().trim();
	}

	public int getCount() {
		return hm.size();
	}

	public void dump() {
		System.out.println("Attribute List");
		System.out.println("         count : " + hm.size());
		Iterator<AVAType> it = hm.iterator();
		while (it.hasNext()) {
			AVAType ava = it.next();
			Object value = ava.getValue();
			System.out.print("  ava [0x" + Integer.toHexString(ava.getAttributeId()) + "] ");
			if (value instanceof Reportable) {
				Reportable dumpable = (Reportable) value;
				dumpable.dump();
			} else if (value instanceof float[]) {
				float[] farr = (float[]) value;
				for (float f : farr) {
					System.out.print(f);
					System.out.print(",");
				}
				System.out.println();
			} else if (value instanceof SaObsValue[]) {
				SaObsValue[] arr = (SaObsValue[]) value;
				System.out.println("SaObsValue [] count=" + arr.length);
				for (SaObsValue obs : arr) {
					obs.dump();
				}
			} else {
				String label;
				switch (ava.getAttributeId()) {
				case C11073.MDC_ATTR_DISP_RES:
					label = "display-res";
					break;
				case C11073.MDC_ATTR_ID_LABEL:
					label = "label";
					break;
				case C11073.MDC_ATTR_ID_LABEL_STRING:
					label = "label-string";
					break;
				case C11073.MDC_ATTR_COLOR:
					label = "color";
					break;
				case C11073.MDC_ATTR_ID_TYPE:
					label = "type attribute";
					break;
				case C11073.MDC_ATTR_ID_HANDLE:
					label = "handle";
					break;
				case C11073.MDC_ATTR_NU_VAL_OBS:
					label = "observ";
					break;
				case C11073.MDC_ATTR_TIME_PD_SAMP:
					label = "samp_per";
					break;
				case C11073.MDC_ATTR_PT_NAME_FAMILY:
					label = "family_name";
					break;
				case C11073.MDC_ATTR_PT_NAME_GIVEN:
					label = "given_name";
					break;
				case C11073.MDC_ATTR_PT_NAME_BIRTH:  // same as _MAIDEN
					label = "birth/maiden_name";
					break;
				case C11073.MDC_ATTR_PT_NAME_MIDDLE:
					label = "middle_name";
					break;

				default:
					label = "unk";
				}
				System.out.print("[");
				System.out.print(label);
				System.out.print("] ");
				System.out.println(value); // + " " + value.getClass());

			}
		}
	}

	// private String _getParamNameFromAttribute(short attributeId) {
	// String name = null;
	// switch( attributeId ) {
	// case C.NOM_ATTR_ID_LABEL:
	// name = "NOM_ATTR_ID_LABEL";
	// break;
	// case C.NOM_ATTR_ID_LABEL_STRING:
	// name = "NOM_ATTR_ID_LABEL_STRING";
	// break;
	// }
	// return name;
	// }

	@Override
	public String toString() {
		StringBuffer b = new StringBuffer(64);
		b.append("[AttributeList]");
		Iterator<AVAType> ii = hm.iterator();
		while (ii.hasNext()) {
			AVAType ava = ii.next();
			b.append("  0x");
			b.append(Integer.toHexString(ava.getAttributeId()));
			b.append("=");
			b.append(ava.getValue());
		}
		return b.toString();
	}

	public Iterator<AVAType> iterator() {
		return hm.iterator();
	}

}
