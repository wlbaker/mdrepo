package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@Table(name = "MindRayMeasurement")
@Data
public class MindrayMeasurement extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(MindrayMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public MindrayMeasurement() {
		super( StreamID.MEASUREMENT );
	}

	public final static String MR_LUNG_COMPL = "151688";
	public final static String MR_CONC_O2_INSP = "152196";
	public final static String MR_CONC_CO2_ET = "151708";
	public final static String MR_CONC_CO2_INSP = "151716";
	public final static String MR_CONC_O2_ET = "152440";
	public final static String MR_CONC_N2O_ET = "152108";

	@Column(name = "C", nullable = true)
	@Metric(loc = MR_LUNG_COMPL, code = "C", unit = "ml/cmH2O")
	private Integer compliance;

	@Column(name = "iO2", nullable = true)
	@Metric(loc = MR_CONC_O2_INSP, code = "iO2", unit = "%")
	private Integer iO2;

	@Column(name = "etCO2", nullable = true)
	@Metric(loc = MR_CONC_CO2_ET, code = "etCO2", unit = "mmHg")
	private Integer etCO2;

	@Column(name = "iCO2", nullable = true)
	@Metric(loc = MR_CONC_CO2_INSP, code = "iCO2", unit = "mmHg")
	private Integer flowAir;

	@Column(name = "etO2", nullable = true)
	@Metric(loc = MR_CONC_O2_ET, code = "etO2", unit = "%")
	private Integer pressMax;

	@Column(name = "etNO2", nullable = true)
	@Metric(loc = MR_CONC_N2O_ET, code = "etNO2", unit = "%")
	private Integer pressureInspMean;

	
	// add
	private static final String MDC_PRESS_RESP_PLAT = "151784";
	@Column(name="PRESS_RESP_PLAT")
	@Metric(loc=MDC_PRESS_RESP_PLAT, code = "PRESS_RESP_PLAT", unit = "cmH2O")
	private Integer plat;

// add
	private static final String MDC_PRESS_AWAY_END_EXP_POS = "151976";
	@Column(name="END_EXP_POS")
	@Metric(loc=MDC_PRESS_AWAY_END_EXP_POS, code = "END_EXP_POS", unit = "cmH2O")
	private Integer expPos;

// add
	private static final String MDC_VOL_MINUTE_AWAY = "151880";
	@Column(name="VOL_MINUTE_AWAY")
	@Metric(loc=MDC_VOL_MINUTE_AWAY, code = "VOL_MINUTE_AWAY", unit = "L/min")
	private Integer minuteVol;

// add
	private static final String MDC_VOL_AWAY_TIDAL = "151868";
	@Column(name="VOL_AWAY_TIDAL")
	@Metric(loc=MDC_VOL_AWAY_TIDAL, code = "VOL_AWAY_TIDAL", unit = "mL")
	private Integer tidalVol;

// add
	private static final String MDC_VENT_RESP_RATE = "151586";
	@Column(name="VENT_RESP_RATE")
	@Metric(loc=MDC_VENT_RESP_RATE, code = "VENT_RESP_RATE", unit = "/min")
	private Integer rr;

// add
	private static final String MDC_RATIO_IE = "151832";
	@Column(name="MDC_RATIO_IE")
	@Metric(loc=MDC_RATIO_IE, code = "MDC_RATIO_IE", unit = "")
	private Integer i2e;

// add
	private static final String MDC_RES_AWAY = "151840";
	@Column(name="MDC_RES_AWAY")
	@Metric(loc=MDC_RES_AWAY, code = "MDC_RES_AWAY", unit = "cmH2O/L/s")
	private Integer res;

// add
	private static final String MDC_COMPL_LUNG = "151688";
	@Column(name="MDC_COMPL_LUNG")
	@Metric(loc=MDC_COMPL_LUNG, code = "MDC_COMPL_LUNG", unit = "mL/cmH2O")
	private Integer C;

// add
	private static final String MDC_CONC_AWAY_O2_INSP = "152196";
	@Column(name="AWAY_O2_INSP")
	@Metric(loc=MDC_CONC_AWAY_O2_INSP, code = "AWAY_O2_INSP", unit = "%")
	private Integer o2i;

// add
	private static final String MDC_MASS_BODY_ACTUAL = "188736";
	@Column(name="MASS_BODY_ACTUAL")
	@Metric(loc=MDC_MASS_BODY_ACTUAL, code = "MASS_BODY_ACTUAL", unit = "kg")
	private Integer massBody;

// add
	private static final String MDC_CONC_AWAY_CO2_ET = "151708";
	@Column(name="AWAY_CO2_ET")
	@Metric(loc=MDC_CONC_AWAY_CO2_ET, code = "AWAY_CO2_ET", unit = "mmHg")
	private Integer co2Et;

// add
	private static final String MDC_CONC_AWAY_CO2_INSP = "151716";
	@Column(name="AWAY_CO2_INSP")
	@Metric(loc=MDC_CONC_AWAY_CO2_INSP, code = "AWAY_CO2_INSP", unit = "mmHg")
	private Integer co2i;

// add
	private static final String MDC_CONC_AWAY_O2_ET = "152440";
	@Column(name="AWAY_O2_ET")
	@Metric(loc=MDC_CONC_AWAY_O2_ET, code = "AWAY_O2_ET", unit = "%")
	private Integer o2Et;

// add
	private static final String MDC_CONC_AWAY_N2O_ET = "152108";
	@Column(name="AWAY_N2O_ET")
	@Metric(loc=MDC_CONC_AWAY_N2O_ET, code = "AWAY_N2O_ET", unit = "%")
	private Integer no2Et;

// add
	private static final String MDC_CONC_AWAY_N2O_INSP = "152192";
	@Column(name="AWAY_N2O_INSP")
	@Metric(loc=MDC_CONC_AWAY_N2O_INSP, code = "AWAY_N2O_INSP", unit = "%")
	private Integer no2Insp;

// add
	private static final String MDC_CONC_MAC = "119";
	@Column(name="MDC_CONC_MAC")
	@Metric(loc=MDC_CONC_MAC, code = "MDC_CONC_MAC", unit = "")
	private Integer mac;

// add
	private static final String MDC_CONC_AWAY_ENFL_ET = "152088";
	@Column(name="AWAY_ENFL_ET")
	@Metric(loc=MDC_CONC_AWAY_ENFL_ET, code = "AWAY_ENFL_ET", unit = "%")
	private Integer enFlowEt;

// add
	private static final String MDC_CONC_AWAY_ENFL_INSP = "152172";
	@Column(name="AWAY_ENFL_INSP")
	@Metric(loc=MDC_CONC_AWAY_ENFL_INSP, code = "AWAY_ENFL_INSP", unit = "%")
	private Integer enFlowInsp;

// add
	private static final String MDC_CONC_AWAY_DESFL_ET = "152084";
	@Column(name="AWAY_DESFL_ET")
	@Metric(loc=MDC_CONC_AWAY_DESFL_ET, code = "AWAY_DESFL_ET", unit = "%")
	private Integer desFlowEt;

// add
	private static final String MDC_CONC_AWAY_DESFL_INSP = "152168";
	@Column(name="AWAY_DESFL_INSP")
	@Metric(loc=MDC_CONC_AWAY_DESFL_INSP, code = "AWAY_DESFL_INSP", unit = "%")
	private Integer desFlowInsp;

// add
	private static final String MDC_VOL_DELIV_HALOTH_LIQUID_CASE = "126";
	@Column(name="HALOTH_LIQUID_CASE")
	@Metric(loc=MDC_VOL_DELIV_HALOTH_LIQUID_CASE, code = "HALOTH_LIQUID_CASE", unit = "mL")
	private Integer haloth;

// add
	private static final String MDC_VOL_DELIV_ENFL_LIQUID_CASE = "127";
	@Column(name="ENFL_LIQUID_CASE")
	@Metric(loc=MDC_VOL_DELIV_ENFL_LIQUID_CASE, code = "ENFL_LIQUID_CASE", unit = "mL")
	private Integer enFlow;

// add
	private static final String MDC_VOL_DELIV_ISOFL_LIQUID_CASE = "128";
	@Column(name="ISOFL_LIQUID_CASE")
	@Metric(loc=MDC_VOL_DELIV_ISOFL_LIQUID_CASE, code = "ISOFL_LIQUID_CASE", unit = "mL")
	private Integer isoFlow;

// add
	private static final String MDC_VOL_DELIV_SEVOFL_LIQUID_CASE = "129";
	@Column(name="SEVOFL_LIQUID_CASE")
	@Metric(loc=MDC_VOL_DELIV_SEVOFL_LIQUID_CASE, code = "SEVOFL_LIQUID_CASE", unit = "mL")
	private Integer sevoFlow;

// add
	private static final String MDC_VOL_DELIV_DESFL_LIQUID_CASE = "130";
	@Column(name="DESFL_LIQUID_CASE")
	@Metric(loc=MDC_VOL_DELIV_DESFL_LIQUID_CASE, code = "DESFL_LIQUID_CASE", unit = "mL")
	private Integer desFlow;

}
