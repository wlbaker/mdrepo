package icuInterface.adapters.HL7;

//
// TODO: This device can send RealtimeConfigurationChanged messages if gas
//       is changed during the run 
//
// TODO: C6h (p29) can be sent at start of ventilator inspiratory cycle, 
//       and should be logged as an event
//
// TODO: There are hardcoded values in the syncEnableTraces call to start RT 
//       on two channels.  0x03.
//
// TODO: this thing should extend abstractsignalproducer, not serialadapter.
//

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import ca.uhn.hl7v2.DefaultHapiContext;
import ca.uhn.hl7v2.HL7Exception;
import ca.uhn.hl7v2.HapiContext;
import ca.uhn.hl7v2.model.Message;
import ca.uhn.hl7v2.model.Structure;
import ca.uhn.hl7v2.model.Varies;
import ca.uhn.hl7v2.model.v26.datatype.CWE;
import ca.uhn.hl7v2.model.v26.datatype.ID;
import ca.uhn.hl7v2.model.v26.datatype.NM;
import ca.uhn.hl7v2.model.v26.datatype.ST;
import ca.uhn.hl7v2.model.v26.group.ORU_R01_OBSERVATION;
import ca.uhn.hl7v2.model.v26.group.ORU_R01_ORDER_OBSERVATION;
import ca.uhn.hl7v2.model.v26.group.ORU_R01_PATIENT_RESULT;
import ca.uhn.hl7v2.model.v26.message.ORU_R01;
import ca.uhn.hl7v2.model.v26.segment.OBX;
import ca.uhn.hl7v2.parser.GenericParser;
import ca.uhn.hl7v2.parser.ModelClassFactory;
import ca.uhn.hl7v2.util.ReflectionUtil;
import icuInterface.ConnectionStatus;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class HL7AbstractDriver extends SerialAdapter implements AdapterInterface {

	private static final int DISCONNECTED_TICK_COUNT = 8;

	private int tick = DISCONNECTED_TICK_COUNT;
	DeviceConfiguration conf;

	HapiContext context = new DefaultHapiContext();
	private GenericParser p;

	private DeviceCapabilities caps;

	// private DeviceCapabilities caps;

	private static final int MDC_DIM_DIMLESS = 262656;
	private static final int MDC_DIM_MILLI_L = 263762;
	private static final int MDC_DIM_RESP_PER_MIN = 264928;
	private static final int MDC_DIM_PERCENT = 262688;
	private static final int MDC_DIM_CM_H2O = 266048;
	private static final int MDC_DIM_L_PER_MIN = 265216;
	private static final int MDC_DIM_CM_H2O_PER_L_PER_SEC = 268064;
	private static final int MDC_DIM_MILLI_L_PER_CM_H2O = 268050;
	private static final int MDC_DIM_KILO_G = 263875;

	private static final int MDC_DIM_MMHG = 266016;

	private static final Map<String, String> unitMap = new HashMap<String, String>();

	static {
		unitMap.put("" + MDC_DIM_DIMLESS, "");
		unitMap.put("" + MDC_DIM_MILLI_L, "mL");
		unitMap.put("" + MDC_DIM_RESP_PER_MIN, "/min");
		unitMap.put("" + MDC_DIM_PERCENT, "%");
		unitMap.put("" + MDC_DIM_CM_H2O, "cmH2O");
		unitMap.put("" + MDC_DIM_L_PER_MIN, "L/min");
		unitMap.put("" + MDC_DIM_CM_H2O_PER_L_PER_SEC, "cmH2O/L/s");
		unitMap.put("" + MDC_DIM_MILLI_L_PER_CM_H2O, "mL/cmH2O");
		unitMap.put("" + MDC_DIM_KILO_G, "kg");
		unitMap.put("" + MDC_DIM_MMHG, "mmHg");
	}

	public HL7AbstractDriver(DeviceCapabilities caps, DeviceConfiguration conf) {
		super(conf);
		this.caps = caps;
		this.conf = conf;
		p = context.getGenericParser();
	}

	public void parsePacket(byte[] data, int off, int len) throws IOException, HL7Exception {
		String s = new String(data, off, len);
		//String s = s1.replace("\r\n", "\r");

		Message hapiMsg = null;

		// hapiMsg = p.parse( s );
		hapiMsg = instantiateMessage("ORU_R01", "2.6", true);
		ORU_R01 oru = (ORU_R01) hapiMsg;
		oru.setParser(p);
		p.parse(oru, s);

		Structure[] obxs = null;
		try {
			obxs = oru.getAll("OBX");
		} catch (HL7Exception hex) {
			// i do NOT like this method of trying to determine the structure
		}
		PersistentItem settings = ModelUtil.getModelFromDataClass(caps.getStream(StreamID.SETTINGS).getPIClass());
		PersistentItem measurements = ModelUtil.getModelFromDataClass(caps.getStream(StreamID.MEASUREMENT).getPIClass());
		if (obxs == null) {
			ORU_R01_PATIENT_RESULT patientResult = oru.getPATIENT_RESULT();
			ORU_R01_ORDER_OBSERVATION o_obs = patientResult.getORDER_OBSERVATION();
			List<ORU_R01_OBSERVATION> obs = o_obs.getOBSERVATIONAll();
			for (ORU_R01_OBSERVATION obv : obs) {
				OBX obx = obv.getOBX();
				saveOneObx(measurements, settings, obx);
			}
			fireStreamEvent(0,this,StreamID.SETTINGS, settings);
			fireStreamEvent(0,this,StreamID.MEASUREMENT, measurements);
		}
		if (obxs != null) {
			for (Structure struc : obxs) {
				OBX obx = (OBX) struc;
				saveOneObx(measurements, settings, obx);
			}
			fireStreamEvent(0,this,StreamID.SETTINGS, settings);
			fireStreamEvent(0,this,StreamID.MEASUREMENT, measurements);
		}
		tick = 0;
	}

	private void saveOneObx(PersistentItem measurements, PersistentItem settings, OBX obx) {
		CWE cwe = obx.getObservationIdentifier();
		ST ihe_id = cwe.getCwe1_Identifier();
		ST ihe_name = cwe.getCwe2_Text();
		ID ihe_coding = cwe.getCwe3_NameOfCodingSystem();
		RpMetric metric = settings.getMetric(ihe_id.getValue());
		if (metric != null) {
			addElement(settings, metric, obx.getValueType(), obx.getObservationValue(), obx.getUnits());
		} else {
			metric = settings.getMetric(ihe_id.getValue());
			if (metric != null) {
				addElement(measurements, metric, obx.getValueType(), obx.getObservationValue(), obx.getUnits());
			} else {
				String code = "" + ihe_name;
				String[] arr = code.split("_");
				int l = arr.length;
				if (l > 3) {
					code = arr[l - 3] + "_" + arr[l - 2] + "_" + arr[l - 1];
				}

				System.out.println("// add");
				System.out.println("\tprivate static final String " + ihe_name + " = \"" + ihe_id + "\";");
				System.out.println("\t@Column(name=\"" + code + "\")");
				System.out.print("\t@Metric(loc=" + ihe_name);
				System.out.print(", code = \"" + code + "\"");
				System.out.println(", unit = \"" + translateUnit(obx.getUnits()) + "\")");
				System.out.println("	private final Integer x;");
				System.out.println();
			}
		}
	}

	private String translateUnit(CWE u) {
		ST id = u.getCwe1_Identifier();
		ST txt = u.getCwe2_Text();

		String num = id.getValue();
		String unitName = unitMap.get( num );
		if( unitName == null ) {
			unitName = txt.getValue();
		}
		if( unitName == null ) {
			unitName = num;
		}

		return unitName;
	}

	private void addElement(PersistentItem item, RpMetric m, ID typ, Varies[] values, CWE units) {
		Varies val = values[0];
		String name = val.getName();
		if( "CWE".equals(name) ) {
			CWE data = (CWE)val.getData();
			ST id = data.getCwe1_Identifier();
			ST txt = data.getCwe2_Text();
			if( "MDC_EVT_STAT_RUNNING".equals(txt.getValue()) ) {
				IntfUtil.setValue(item, m, 1);
			// } else if( "MNDRY_EVT_STAT_MODE_NORMAL".equals(txt.getValue()) ) {
			} else {
				IntfUtil.setValue(item, m, Integer.parseInt(id.getValue()));
				// System.out.println("unknown code: " + data);
			}
		} else if ("NM".equals(name)) {
			NM data = (NM) val.getData();
			String v = data.getValue();
			IntfUtil.setValue(item, m, v);
		}
	}

	protected Message instantiateMessage(String theName, String theVersion, boolean isExplicit) throws HL7Exception {
		ModelClassFactory factory = context.getModelClassFactory();
		Class<? extends Message> messageClass = factory.getMessageClass(theName, theVersion, isExplicit);
		if (messageClass == null)
			throw new HL7Exception("Can't find message class in current package list: " + theName);
		return ReflectionUtil.instantiateMessage(messageClass, factory);
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (deviceState == ConnectionStatus.NEGOTIATING) {
			// do nothing
		} else if (tick > DISCONNECTED_TICK_COUNT) {
			if (deviceState != NOT_CONNECTED) {
				log.info("tick taking driver offline: {}", tick);
				setStatus(NOT_CONNECTED);
				fireNoData(conf);
			}
		} else {
			if (tick == 1 && deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		return 0;
	}

}
