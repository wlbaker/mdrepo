package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "DragerApollo_Measurement")
@Data
@EqualsAndHashCode(callSuper = false)
public class Fabius_Measurements extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(Fabius_Measurements.class);
	}

	public Fabius_Measurements() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

//	@Metric(loc = "0x1B", desc = "Consumption Halothane (Liquid)", unit = "mL")
//	private int USAGE_HALO; //
//	@Metric(loc = "0x1C", desc = "Consumption Enflurane (Liquid)", unit = "mL")
//	private int USAGE_ENFLURANE; //
//	@Metric(loc = "0x1D", desc = "Consumption Isoflurane (Liquid)", unit = "mL")
//	private int USAGE_ISO; //
//	@Metric(loc = "0x1E", desc = "Consumption Desflurane (Liquid)", unit = "mL")
//	private int USAGE_DES; //
//	@Metric(loc = "0x1F", desc = "Consumption Sevoflurane (Liquid)", unit = "mL")
//	private int USAGE_SEVO; //
//	@Metric(loc = "0x07", desc = "Compliance (Alt)", unit = "L/bar")
//	private int C_ALT; //
//
//	@Metric(loc = "0x50", desc = "Insp. Halothane", unit = "kPa")
//	private int INSP_HALO; //
//	@Metric(loc = "0x51", desc = "Exp. Halothane", unit = "kPa")
//	private int EXP_HALO; //
//	@Metric(loc = "0x52", desc = "Insp. Enflurane", unit = "kPa")
//	private int INSP_ENFL; //
//	@Metric(loc = "0x53", desc = "Exp. Enflurane", unit = "kPa")
//	private int EXP_ENFL; //
//	@Metric(loc = "0x54", desc = "Insp. Isoflurane", unit = "kPa")
//	private int INSP_ISO; //
//	@Metric(loc = "0x55", desc = "Exp. Isoflurane", unit = "kPa")
//	private int EXP_ISO; //
//	@Metric(loc = "0x56", desc = "Insp. Desflurane", unit = "kPa")
//	private int INSP_DES; //
//	@Metric(loc = "0x57", desc = "Exp. Desflurane", unit = "kPa")
//	private int EXP_DES; //
//	@Metric(loc = "0x58", desc = "Insp. Sevoflurane", unit = "kPa")
//	private int INSP_SEVO; //
//	@Metric(loc = "0x59", desc = "Exp. Sevoflurane", unit = "kPa")
//	private int EXP_SEVO; //
//
//	@Metric(loc = "0x5A", desc = "Insp. Agent", unit = "kPa")
//	private int INSP_AGENT; //
//	@Metric(loc = "0x5B", desc = "Exp. Agent", unit = "kPa")
//	private int EXP_AGEN2; //
//	@Metric(loc = "0x5C", desc = "2nd Insp. Agent", unit = "kPa")
//	private int INSP_2AGENT; //
//	@Metric(loc = "0x5D", desc = "2nd Exp. Agent", unit = "kPa")
//	private int EXP_2AGENT; //
//	@Metric(loc = "0xAC", desc = "Insp. MAC")
//	private int INSP_MAC; //
//	@Metric(loc = "0xAD", desc = "Exp. MAC")
//	private int EXP_MAC; //

//	// O2 related
//	@Metric(loc = "0xC4", desc = "Delta O2 (Insp. O2 - Exp. O2)", unit = "%")
//	private int DELTA_O2; //
//	@Metric(loc = "0xEF", desc = "Exp. O2", unit = "%")
//	private int EXP_O2; //
//	@Metric(loc = "0x64", desc = "O2 Uptake", unit = "10mL/min")
//	private int O2UPTAKE; //
//	// SpO2
//	@Metric(loc = "0xE1", desc = "Pulse Rate (OXIMETER)", unit = "1/min")
//	private int PR_OXI; //
//	@Metric(loc = "0xEB", desc = "Oxygen Saturation", unit = "%")
//	private int SAT; //
//	@Metric(loc = "0xDF", desc = "Pulse Rate (derived)", unit = "1/min")
//	private int PR_DERIV; //
//	// Ventilator Data
//	@Metric(loc = "0xB2", desc = "Ventilator Leakage", unit = "mL/min")
//	private int LEAK; //
	
	@Metric(loc = "0xAE", desc = "Insp. Desflurane", unit = "%")
	private int INSP_M_DES; //
	@Metric(loc = "0xAF", desc = "Exp. Desflurane", unit = "%")
	private int EXP_M_DES; //
	@Metric(loc = "0xB0", desc = "Insp. Sevoflurane", unit = "%")
	private int INSP_M_SEVO; //
	@Metric(loc = "0xB1", desc = "Exp. Sevoflurane", unit = "%")
	private int EXP_M_SEVO; //
	@Metric(loc = "0xE9", desc = "Insp. Agent", unit = "%")
	private int INSP_M_AGENT; //
	@Metric(loc = "0xEA", desc = "Exp. Agent", unit = "%")
	private int EXP_M_AGENT; //
//	@Metric(loc = "0xED", desc = "2nd Insp. Agent", unit = "%")
//	private int INSP_M_2AGENT; //
//	@Metric(loc = "0xEE", desc = "2nd Exp. Agent", unit = "%")
//	private int EXP_M_2AGENT; //

	@Metric(loc = "0xF4", desc = "Insp. Halothane", unit = "%")
	private int INSP_M_HALO; //
	@Metric(loc = "0xF5", desc = "Exp. Halothane", unit = "%")
	private int EXP_M_HALO; //
	@Metric(loc = "0xF6", desc = "Insp. Enflurane", unit = "%")
	private int INSP_M_ENFL;//
	@Metric(loc = "0xF7", desc = "Exp. Enflurane", unit = "%")
	private int EXP_M_ENFL; //
	@Metric(loc = "0xF8", desc = "Insp. Isoflurane", unit = "%")
	private int INSP_M_ISO; //
	@Metric(loc = "0xF9", desc = "Exp. Isoflurane", unit = "%")
	private int EXP_M_ISO; //

	@Metric(loc = "0xFB", desc = "Insp. N2O")
	private int INSP_NO2; //
	@Metric(loc = "0xFC", desc = "Exp. N2O")
	private int EXP_NO2; //

	// airway related
	@Metric(loc = "0x05", desc = "Breathing Pressure", unit = "mbar")
	private int BR_P; //
	@Metric(loc = "0x06", desc = "Compliance", unit = "mL/mbar")
	private int C; //
	@Metric(loc = "0x6B", desc = "Ambient Pressure", unit = "mbar")
	private int AMB_P; //
	@Metric(loc = "0x73", desc = "Mean Breathing Pressure", unit = "mbar")
	private int MEAN; //
	@Metric(loc = "0x74", desc = "Plateau Pressure", unit = "mbar")
	private int PLATEAU; //
	@Metric(loc = "0x78", desc = "PEEP Breathing Pressure", unit = "mbar")
	private int PEEP; //
	@Metric(loc = "0x7D", desc = "Peak Breathing Pressure", unit = "mbar")
	private int PEAK; //
	// loc = 0x82: TV MLtoL...obsolete
	@Metric(loc = "0x88", desc = "Tidal Volume", unit = "mL")
	private int TV; //
	@Metric(loc = "0x8B", desc = "Insp. Tidal Volume", unit = "mL")
	private int InspTV; //
	
	@Metric(loc = "0xB9", desc = "Respiratory Minute Volume", unit = "L", precision = 3)
	private int MV; //
	@Metric(loc = "0xD7", desc = "Respiratory Rate", unit = "1/min")
	private int RRd7; //

	// CO2 related
	@Metric(loc = "0xD5", desc = "Respiratory Rate (CO2)", unit = "1/min")
	private int RRco2; //
	@Metric(loc = "0xDA", desc = "Insp. CO2", unit = "%")
	private int InspCO2pct; //
	@Metric(loc = "0xDB", desc = "Entidal CO2", unit = "%")
	private int EtCO2pct; //
	@Metric(loc = "0xE3", desc = "Entidal CO2", unit = "kPa")
	private int EtCO2kpa; //
	@Metric(loc = "0xE5", desc = "Insp. CO2", unit = "mmHg")
	private int InspCO2; //
	@Metric(loc = "0xE6", desc = "Entidal CO2", unit = "mmHg")
	private int EtCO2; //
	@Metric(loc = "0xFF", desc = "Insp. CO2", unit = "kPa")
	private int INSP_CO2; //

	// SpO2
	@Metric(loc = "0xF0", desc = "Insp. O2", unit = "%")
	private int INSP_O2; //
	@Metric(loc = "0xDD", desc = "N2O Flow", unit = "mL/min")
	private int N2O; //
	@Metric(loc = "0xDE", desc = "Air Flow", unit = "mL/min")
	private int AIR; //
	@Metric(loc = "0xE2", desc = "O2 Flow", unit = "mL/min")
	private int O2;

}
