package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "HEMOLUNG")
@Data
@EqualsAndHashCode(callSuper = false)
public class HemolungMeasurement extends PersistentItem {
	// private final static int ACTIVE_SCREEN = 0x0;
	// private final static int POST_RESULT = 0x1;
	// private final static int AC_DETECTED = 0x4;
	private final static String CO2_EXCHANGE_RATE = "005";
	private final static String CO2_CONCENTRATION = "006";
	private final static String O2_CONCENTRATION = "007";
	private final static String SWEEP_GAS_FLOW = "008";
	private final static String SWEEP_GAS_PRESSURE = "009";
	// private final static int PM_STATUS = 0xA;
	private final static String BLOOD_FLOW = "00B";
	private final static String BLOOD_FLOW_VALID = "00C";
	private final static String MOTOR_RPM = "00D";
	// private final static int MOTOR_CURRENT = 0xE;
	private final static String VACUUM_PUMP_RPM = "00F";
	// private final static int DC_BUS_VOLTAGE = 0x10;
	// private final static int BATTERY_VOLTAGE = 0x11;
	private final static String CABINET_O2_CONCEN = "012";
	// private final static int ACTIVE_ALARM_MASK = 0x13;
	// private final static int CASE_TEMPERATURE = 0x14;
	// private final static int EMBEDDED_SW_VERSION = 0x15;
	// private final static int HELP_VISIBLE = 0x18;
	// private final static int LEFT_SOFTKEY_INDEX = 0x19;
	// private final static int LEFT_CTR_SOFTKEY_INDEX = 0x1a;
	// private final static int RIGHT_CTR_SOFTKEY_INDEX = 0x1B;
	// private final static int RIGHT_SOFTKEY_INDEX = 0x1C;
	// private final static int SWEEP_GAS_FLOW_SETPOINT = 0x1D;
	// private final static int PRIMING_SCREEN_NUM = 0x1F;
	private final static String RUNNING_ON_O2 = "020";
	// private final static int ALARM_AUDIO_STATE = 0x22;
	private final static String MOTOR_RPM_SETPOINT = "023";
	// private final static int HUMAN_USE = 0x25;
	// private final static int BATTERY_CHARGING = 0x27;
	// private final static int SERIAL_NUMBER = 0x28;
	private final static String RECIRC_SUBSTATE = "02B";
	private final static String SWEEP_GAS_SELECTION = "02C";
	// private final static int SWEEP_GAS_WARNING = 0x2D;
	// private final static int STATUS_MESSAGE = 0x2E;
	// private final static int PUMP_STOPPED_TIMER = 0x2F;
	// private final static int ALL_ALARMS = 0x30;
	// private final static int CURRENT_LANGUAGE = 0x31;
	// private final static int SHOW_SG_SETPOINT = 0x32;
	// private final static int SHOW_CO2_REMOVAL = 0x33;
	// private final static int RECIRC_AIR_STATUS = 0x34;
	// private final static int RUN_GRAPH = 0x35;
	// private final static int SHOW_PRIME_SCREEN_NUM = 0x36;
	// private final static int TREND_RESOLUTION = 0x37;
	// private final static int RINSE_BACK_SCREEN_NUM = 0x38;

	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(HemolungMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public HemolungMeasurement() {
		super(StreamID.MEASUREMENT);
	}

	@Metric(loc = CO2_EXCHANGE_RATE, code = "rCO2", desc = "CO2 Exchange Rate", unit = "mL/min")
	private int rCO2;
	@Metric(loc = CO2_CONCENTRATION, code = "%CO2", desc = "CO2 Concentration", unit = "%", precision = 2)
	private int pctCO2;
	@Metric(loc = O2_CONCENTRATION, code = "%O2", desc = "O2 Cooncentration", unit = "%", precision = 2)
	private int pctO2;
	@Metric(loc = SWEEP_GAS_FLOW, code = "gF", desc = "Sweep gas flow", unit = "mmHg")
	private int gF;
	@Metric(loc = SWEEP_GAS_PRESSURE, code = "gP", desc = "Sweep gas manifold pressure", unit = "mmHg")
	private int gP;
	@Metric(loc = BLOOD_FLOW, code = "BF", desc = "Blood Flow", unit = "mL/min")
	private int BF;
	@Metric(loc = BLOOD_FLOW_VALID, code = "BFv", desc = "Blood Flow Valid Indicator")
	private int BFv;
	@Metric(loc = MOTOR_RPM, code = "MTR", desc = "Motor", unit = "rpm")
	private int MTR;
	@Metric(loc = VACUUM_PUMP_RPM, code = "VAC", desc = "Blood Flow Valid Indicator")
	private int VAC;
	@Metric(loc = CABINET_O2_CONCEN, code = "cabO2", desc = "Blood Flow Valid Indicator")
	private int cabO2;
	@Metric(loc = RUNNING_ON_O2, code = "flagO2", desc = "Denotes if Oxygen pressure switch is detecting oxygen")
	private int O2flag;
	@Metric(loc = MOTOR_RPM_SETPOINT, code = "MTRrpm", desc = "Motor RPM Setpoint", unit = "rpm")
	private int MTRsetting;

	@Metric(loc = RECIRC_SUBSTATE, code = "RECIRC", desc = "Enumerated type denoting substrate withing recirculation")
	private int RECIRC;
	@Metric(loc = SWEEP_GAS_SELECTION, code = "idSWEEP", desc = "Enumerated sweep gas config setting")
	private int idSWEEP;

}
