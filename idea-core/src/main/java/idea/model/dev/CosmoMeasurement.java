package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

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

@Table(name = "Cosmo"
// , uniqueConstraints = { @UniqueConstraint( columnNames = { "ORDER_DATE",
// "TYPE", "RECNUM" } ),
// @UniqueConstraint( columnNames = { "TYPE", "ORDER_DATE", "ORDER_NO", "RECNUM"
// } ),
// @UniqueConstraint( columnNames = { "TYPE", "`DIV`", "ORDER_NO" } ),
// @UniqueConstraint( columnNames = { "`DIV`", "ORDER_NO" } ) }
)
@Data
public class CosmoMeasurement extends PersistentItem {
	public static final int L_HR = 10; // Pulse Rate
	public static final int L_O2SAT = 11; // O2 Saturation

	public static final int L_BREATH_TYPE = 12; // 0 --> spontaneous / 1 --> Mechanical
	public static final int L_PIF = 13; // Peak Inspiratory Flow
	public static final int L_PEF = 14; // Peak Expiratory Flow
	public static final int L_TVinS = 18; // Inspired Tidal Volumn (Spontaneous breaths
	// only)
	public static final int L_TVinM = 19; // Inspired Tidal Volume (Mechanical breaths
	// only)
	public static final int L_VTi = 20; // Inspiratory Volume, breath-by-breath
	public static final int L_VTe = 21; // Expiratory Volume, breath-by-breath
	public static final int L_MVexpT = 23; // Expired Minute Volume, Total
	public static final int L_TVexT = 25; // Expired Tidal Volume, Total
	public static final int L_TVexS = 26; // Expired Tidal Volume, Spontaneous breaths
	// only
	public static final int L_TVexM = 27; // Expired Tidal Volume, Mechanical breaths
	// only
	public static final int L_MVexS = 28; // Expired Minute Volume, Spontaneous breaths
	// only
	public static final int L_MVexM = 29; // Expired Minute Volume, Mechanical breaths
	// only
	public static final int L_PIP = 30; // Peak Inspiratory Pressure
	public static final int L_PAW_MEAN = 31; // Mean Airway Pressure
	public static final int L_P0_1 = 32; // Pressure @ 100 msec
	public static final int L_PEEP = 33; // Positive End Expiratory Pressure
	public static final int L_PEEPi = 34; // Intrinsic Positive End-Expiratory Pressure
	public static final int L_PPLAT = 35; // Plateau Pressure
	public static final int L_NIP = 36; // Negative Inspiratory Pressure
	public static final int L_FREQ_S = 38; // Respiratory Rate, Spontaneous Breaths
	// only
	public static final int L_FREQ_M = 39; // Respiratory Rate, Mechanical Breaths only
	public static final int L_RR = 40; // Respiratory Rate
	public static final int L_IE_RATIO = 41; // Inspiratory to Expiratory Volume Ratio.
	public static final int L_TI = 42; // Inspired Time
	public static final int L_TE = 43; // Expired Time.....BUGFIX??? was 42!!!!
	public static final int L_RAWstI = 48; // Inspiratory Airway Resistance, static
	// measurement
	public static final int L_RAWstE = 49; // Expiratory Airway Resistance, static
	// measurement
	public static final int L_C_DYN = 51; // Lung Compliance, dynamic measurement
	public static final int L_C_STA = 52; // Lung Compliance, static measurement
	public static final int L_RSBI = 54; // Rapid Shallow Breathing Index
	public static final int L_C2O_C = 55; // C2O Ratio
	public static final int L_C_TOT = 60; // Total Lung Compliance, Dynamic measurement
	public static final int L_RAWiDYN = 61; // Inspiratory Airway Resistance, Dynamic
	// measurement
	public static final int L_RAWeDYN = 62; // Expiratory Airway Resistance, Dynamic
	// measurement
	public static final int L_WOBvt = 70; // Ventilator work of breathing
	public static final int L_WOBimp = 71; // Imposed work of breathing
	// available only when patient's weight is entered
	public static final int L_TV_kg = 78; // Expired Tidal Volume per Kilogram
	// measurement
	public static final int L_VCO2_kg = 79; // Volume CO2 Expired per Kilogram
	// measurement

	public static final int L_ETCO2 = 80; // End-Tidal CO2
	public static final int L_INSP_CO2 = 81; // Inspired CO2
	public static final int L_VCO2b = 82; // Volume CO2 Expired, per breath measurement
	public static final int L_VCO2 = 83; // Volume CO2 Expired, per minute average

	public static final int L_VTalvS = 84; // Alveolar Tidal Volume, Spontaneous
	public static final int L_VTalvM = 85; // Alveolar Tidal Volume, Mechanical
	public static final int L_VTalvT = 86; // Alveolar Tidal Volume, Total

	public static final int L_MValvS = 87; // Alveolar Minute Volume, Spontaneous
	public static final int L_MValvM = 88; // Alveolar Minute Volume, Mechanical
	public static final int L_MValvT = 89; // Alveolar Minute Volume, Total

	public static final int L_VdAW = 90; // Airway Deadspace
	public static final int L_VdVtAW = 91; // Vd / Vt Airway

	// internal calculated values involving linear regression on the CO2/volume
	// expirogram
	public static final int L_P2Slp = 93; // Phase 2 Slope
	public static final int L_P2YI = 94; // Phase 2 Intercept

	// internal calculated values involving linear regression on the CO2/volume
	// expirogram, used internally by the Flow/CO2 module in calculating airway
	// deadspace
	public static final int L_P3Slp = 95; // Phase 3 Slope
	public static final int L_P3YI = 96; // Phase 3 Intercept

	public static final int L_PeCO2 = 100; // Mixed-Expired CO2

	@Transient
	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(CosmoMeasurement.class);
	}

	public CosmoMeasurement() {
		super( StreamID.MEASUREMENT );
	}
	
	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Column(name = "HR", nullable = true)
	@Metric(loc = "10", code = "HR", desc = "HR", unit = "bpm")
	private int HR;
	@Column(name = "SPO2", nullable = true)
	@Metric(loc = "11", code = "spO2", desc = "spO2", unit = "unk")
	private int spO2;
	@Column(name = "RR", nullable = true)
	@Metric(loc = "40", code = "RR", desc = "Respiratory Rate", unit = "br/min")
	private int RR;
	@Column(name = "ETCO2", nullable = true)
	@Metric(loc = "80", code = "EtCO2", desc = "End-Tidal CO2", unit = "mmHg?")
	private int etCO2;
	@Column(name = "INSSP_CO2", nullable = true)
	@Metric(loc = "81", code = "InspCO2", desc = "Inspired CO2", unit = "mmHg")
	private int inspCO2;
	@Column(name = "BR_TYPE", nullable = true)
	@Metric(loc = "12", code = "Btype", desc = "Breath Type")
	private int breathType;
	@Column(name = "PIF", nullable = true)
	@Metric(loc = "13", code = "PIF", desc = "Peak Inspiratory Flow")
	private int PIF;
	@Column(name = "PEF", nullable = true)
	@Metric(loc = "14", code = "PEF", desc = "Peak Expiratory Flow")
	private int PEF;
	@Column(name = "TVinS", nullable = true)
	@Metric(loc = "18", code = "TVinS", desc = "Inspired Tidal Volumn (Spontaneous only)")
	private int tv_in_s;
	@Column(name = "TVinM", nullable = true)
	@Metric(loc = "19", code = "TVinM", desc = "Inspired Tidal Volume (Mechanical only)")
	private int tv_in_m;
	@Column(name = "VTi", nullable = true)
	@Metric(loc = "20", code = "VTi", desc = "Inspiratory Volume, breath-by-breath")
	private int vt_i;
	@Column(name = "VTe", nullable = true)
	@Metric(loc = "21", code = "VTe", desc = "Expiratory Volume, breath-by-breath")
	private int vt_e;
	@Column(name = "MvexpT", nullable = true)
	@Metric(loc = "23", code = "MvexpT", desc = "Expired Minute Volume, Total")
	private int mv_exp_t;
	@Column(name = "TVexT", nullable = true)
	@Metric(loc = "25", code = "TVexT", desc = "Expired Tidal Volume, Total", unit = "mL")
	private int tv_ex_t;
	@Column(name = "TVexS", nullable = true)
	@Metric(loc = "26", code = "TVexS", desc = "Expired Tidal Volume, Spontaneous only", unit = "mL")
	private int tv_ex_s;
	@Metric(loc = "27", code = "TVexM", desc = "Expired Tidal Volume, Mechanical only", unit = "mL")
	private int tv_ex_m;
	@Metric(loc = "28", code = "MVexS", desc = "Expired Minute Volume, Spontaneous only", unit = "L", precision=2)
	private int mv_ex_s;
	@Metric(loc = "29", code = "MVexM", desc = "Expired Minute Volume, Mechanical only", unit = "L", precision=2)
	private int mv_ex_m;
	@Metric(loc = "30", code = "PIP", desc = "Peak Inspiratory Pressure", unit = "cmH2O", precision=1)
	private int PIP;
	@Metric(loc = "31", code = "PAW_MEAN", desc = "Mean Airway Pressure", unit = "cmH2O", precision=1)
	private int paw_mean;
	@Metric(loc = "32", code = "P0_1", desc = "Pressure @ 100 msec", unit = "cmH2O", precision=1)
	private int p0_1;
	@Column(name = "PEEP", nullable = true)
	@Metric(loc = "33", code = "PEEP", desc = "Positive End Expiratory Pressure", unit = "cmH2O", precision=1)
	private int PEEP;
	@Metric(loc = "34", code = "PEEPi", desc = "Intrinsic Positive End-Expiratory Pressure", unit = "cmH2O", precision=1)
	private int peep_i;
	@Metric(loc = "35", code = "PPLAT", desc = "Plateau Pressure", unit = "cmH2O", precision=1)
	private int pplat;
	@Metric(loc = "36", code = "NIP", desc = "Negative Inspiratory Pressure", unit = "cmH2O", precision=1)
	private int nip;
	@Metric(loc = "38", code = "FREQ_S", desc = "Respiratory Rate, Spontaneous only", unit = "/min")
	private int freq_s;
	@Metric(loc = "39", code = "FREQ_M", desc = "Respiratory Rate, Mechanical Breaths only", unit = "/min")
	private int freq_m;
	@Metric(loc = "41", code = "IE_RATIO", desc = "Inspiratory to Expiratory Volume Ratio.")
	private int i2e;
	@Metric(loc = "42", code = "TI", desc = "Inspired Time", unit = "s", precision=2)
	private int ti;
	@Metric(loc = "43", code = "TE", desc = "Expired Time", unit = "s", precision=2)
	private int te;
	@Metric(loc = "48", code = "RAWstI", desc = "Inspiratory Airway Resistance, static", unit = "cmH2O/L/sec")
	private int raw_st_i;
	@Metric(loc = "49", code = "RAWstE", desc = "Expiratory Airway Resistance, static", unit = "cmH2O/L/sec")
	private int raw_st_e;
	@Metric(loc = "51", code = "C_DYN", desc = "Lung Compliance, dynamic measurement")
	private int c_dyn;
	@Metric(loc = "52", code = "C_STA", desc = "Lung Compliance, static measurement")
	private int c_sta;
	@Metric(loc = "54", code = "RSBI", desc = "Rapid Shallow Breathing Index")
	private int rsbi;
	@Metric(loc = "55", code = "C2O_C", desc = "C2O Ratio")
	private int c2o_c;
	@Metric(loc = "60", code = "C_TOT", desc = "Total Lung Compliance, Dynamic measurement")
	private int c_tot;
	@Metric(loc = "61", code = "RAWiDYN", desc = "Inspiratory Airway Resistance, Dynamic")
	private int raw_i_dyn;
	@Metric(loc = "62", code = "RAWeDYN", desc = "Expiratory Airway Resistance, Dynamic")
	private int raw_e_dyn;
	@Metric(loc = "70", code = "WOBvt", desc = "Ventilator work of breathing")
	private int wob_vt;
	@Metric(loc = "71", code = "WOBimp", desc = "Imposed work of breathing")
	private int wob_imp;
	@Metric(loc = "78", code = "TV_kg", desc = "Expired Tidal Volume per Kilogram")
	private int tv_kg;
	@Metric(loc = "79", code = "VCO2_kg", desc = "Volume CO2 Expired per Kilogram")
	private int vco2_kg;

	@Metric(loc = "82", code = "VCO2b", desc = "Volume CO2 Expired, per breath measurement", unit = "mmHg", precision=1)
	private int vco2b;
	@Metric(loc = "83", code = "VCO2", desc = "Volume CO2 Expired, per minute average", unit = "mmHg")
	private int vco2;

	@Metric(loc = "84", code = "VTalvS", desc = "Alveolar Tidal Volume, Spontaneous")
	private int vt_alv_s;
	@Metric(loc = "85", code = "VTalvM", desc = "Alveolar Tidal Volume, Mechanical")
	private int vt_alv_m;
	@Metric(loc = "86", code = "VTalvT", desc = "Alveolar Tidal Volume, Total")
	private int vt_alv_t;

	@Metric(loc = "87", code = "MValvS", desc = "Alveolar Minute Volume, Spontaneous")
	private int mv_alv_s;
	@Metric(loc = "88", code = "MValvM", desc = "Alveolar Minute Volume, Mechanical")
	private int mv_alv_m;
	@Metric(loc = "89", code = "MValvT", desc = "Alveolar Minute Volume, Total")
	private int mv_alv_t;

	@Metric(loc = "90", code = "VdAW", desc = "Airway Deadspace")
	private int vd_aw;
	@Metric(loc = "91", code = "VdVtAW", desc = "Vd / Vt Airway")
	private int vd_vt_aw;

	@Metric(loc = "93", code = "P2Slp", desc = "Phase 2 Slope")
	private int p2slp;
	@Metric(loc = "94", code = "P2YI", desc = "Phase 2 Intercept")
	private int p2yi;
	@Metric(loc = "95", code = "P3Slp", desc = "Phase 3 Slope")
	private int p3slp;
	@Metric(loc = "96", code = "P3YI", desc = "Phase 3 Intercept")
	private int p3yi;

	@Metric(loc = "100", code = "PeCO2", desc = "Mixed-Expired CO2")
	private int peCO2;

}
