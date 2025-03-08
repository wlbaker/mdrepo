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
@Table(name = "MindRaySettings")
@Data
public class MindraySettings extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(MindraySettings.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public MindraySettings() {
		super( StreamID.SETTINGS);
	}

	public final static String MR_VENT_PRESS_LIMIT = "20013";
	public final static String MR_FLOW_O2_FG = "113";
	public final static String MR_FLOW_N2O_FG = "114";
	public final static String MR_FLOW_AIR_FG = "115";
	public final static String MR_VENT_PRESS_MAX = "151957";
	public final static String MR_PRESS_AWAY_INSP_MEAN = "151819";

	@Column(name = "PLIM", nullable = true)
	@Metric(loc = MR_VENT_PRESS_LIMIT, code = "PLIM", unit = "cmH2O")
	private Integer pressLimit;

	@Column(name = "FLOW_O2", nullable = true)
	@Metric(loc = MR_FLOW_O2_FG, code = "FLOW_O2", unit = "ml/min")
	private Integer flowO2;

	@Column(name = "FLOW_NO2", nullable = true)
	@Metric(loc = MR_FLOW_N2O_FG, code = "FLOW_N2O", unit = "ml/min")
	private Integer flowN2O;

	@Column(name = "FLOW_AIR", nullable = true)
	@Metric(loc = MR_FLOW_AIR_FG, code = "FLOW_AIR", unit = "ml/min")
	private Integer flowAir;

	@Column(name = "PMAX", nullable = true)
	@Metric(loc = MR_VENT_PRESS_MAX, code = "PMAX", unit = "cmH2O")
	private Integer pressMax;

	@Column(name = "PMEAN", nullable = true)
	@Metric(loc = MR_PRESS_AWAY_INSP_MEAN, code = "PMEAN", unit = "cmH2O")
	private Integer pressureInspMean;

	
	
	// add
		private static final String MDC_EVT_STAT_DEV = "268422";
		@Column(name="EVT_STAT_DEV")
		@Metric(loc=MDC_EVT_STAT_DEV, code = "EVT_STAT_DEV", unit = "")
		private Integer devStat;

	// add
		private static final String MNDRY_EVT_STAT_MODE_DEV = "30002";
		@Column(name="STAT_MODE_DEV")
		@Metric(loc=MNDRY_EVT_STAT_MODE_DEV, code = "STAT_MODE_DEV", unit = "")
		private Integer devMode;

	// add
		private static final String MNDRY_EVT_PATIENT_TYPE = "30005";
		@Column(name="EVT_PATIENT_TYPE")
		@Metric(loc=MNDRY_EVT_PATIENT_TYPE, code = "EVT_PATIENT_TYPE", unit = "")
		private Integer patientType;

	// add
		private static final String MNDRY_EVT_STAT_WARMER_ON_BOOL = "30007";
		@Column(name="WARMER_ON_BOOL")
		@Metric(loc=MNDRY_EVT_STAT_WARMER_ON_BOOL, code = "WARMER_ON_BOOL", unit = "")
		private Integer warmerOn;

	// add
		private static final String MDC_VENT_MODE = "184352";
		@Column(name="MDC_VENT_MODE")
		@Metric(loc=MDC_VENT_MODE, code = "MDC_VENT_MODE", unit = "")
		private Integer ventMode;

	// add
		private static final String MDC_VOL_AWAY_TIDAL_SETTING = "151868";
		@Column(name="AWAY_TIDAL_SETTING")
		@Metric(loc=MDC_VOL_AWAY_TIDAL_SETTING, code = "AWAY_TIDAL_SETTING", unit = "mL")
		private Integer tidalVolume;

	// add
		private static final String MDC_VENT_RESP_RATE_SETTING = "151586";
		@Column(name="RESP_RATE_SETTING")
		@Metric(loc=MDC_VENT_RESP_RATE_SETTING, code = "RESP_RATE_SETTING", unit = "/min")
		private Integer respRate;

	// add
		private static final String MDC_RATIO_IE_SETTING = "20000";
		@Column(name="RATIO_IE_SETTING")
		@Metric(loc=MDC_RATIO_IE_SETTING, code = "RATIO_IE_SETTING", unit = "")
		private Integer i2e;

	// add
		private static final String MNDRY_VENT_PAUSE_TIME_PERCENT_SETTING = "20007";
		@Column(name="TIME_PERCENT_SETTING")
		@Metric(loc=MNDRY_VENT_PAUSE_TIME_PERCENT_SETTING, code = "TIME_PERCENT_SETTING", unit = "%")
		private Integer timePercent;

	// add
		private static final String MDC_PRESS_AWAY_END_EXP_POS_SETTING = "151976";
		@Column(name="EXP_POS_SETTING")
		@Metric(loc=MDC_PRESS_AWAY_END_EXP_POS_SETTING, code = "EXP_POS_SETTING", unit = "cmH2O")
		private Integer peepSetting;


}
