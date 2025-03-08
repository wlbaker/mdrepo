package idea.model.dev;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@SuppressWarnings("serial")
@Data
public class CapnostreamMeasurement extends PersistentItem {
	public static final int L_EtCO2 = 1;
	public static final int L_FiCO2 = 2;
	public static final int L_RR = 3; // respiration rate
	public static final int L_SPO2 = 4;
	public static final int L_PR = 5; // pulse rate
	public static final int L_SLOW_STATUS = 6;
	public static final int L_EVENT_IDX = 7;
	public static final int L_CO2_ALARMS = 8;
	public static final int L_SPO2_ALARMS = 9;
	public static final int L_NORESP_PERIOD = 10;
	public static final int L_ETCO2_HIGHLIMIT = 11;
	public static final int L_ETCO2_LOWLIMIT = 12;
	public static final int L_RR_HIGHLIMIT = 13;
	public static final int L_RR_LOWLIMIT = 14;
	public static final int L_FICO2_HIGHLIMIT = 15;
	public static final int L_SPO2_HIGHLIMIT = 16;
	public static final int L_SPO2_LOWLIMIT = 17;
	public static final int L_PR_HIGHLIMIT = 18;
	public static final int L_PR_LOWLIMIT = 19;
	public static final int L_CO2_UNITS = 20;
	public static final int L_CO2_STATUS = 21;

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(CapnostreamMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	// new MetricDescription( EVENT_IDX, "PIF", "Peak Inspiratory Flow", "" )
	@Metric( loc="" +L_EtCO2, code="EtCO2", desc="End-Tidal CO2", unit="mmHg?")
	private int ETCO2;
	@Metric( loc="" +L_FiCO2,  code="FiCO2", desc="Fi CO2", unit="mmHg?")
	private int FiCO2;
	@Metric( loc="" +L_RR,  code="RR", desc="Respiratory Rate", unit="br/m")
	private int RR;
	@Metric( loc="" +L_SPO2,  code="SpO2", desc="SpO2", unit="%")
	private int SpO2;
	@Metric( loc="" +L_PR,  code="InspCO2", desc="Inspired CO2", unit="mmHg")
	private int PR;
	@Metric( loc="" +L_SLOW_STATUS,  code="SStat", desc="Slow Status", unit="")
	private int SSTAT;
	@Metric( loc="" +L_CO2_ALARMS,  code="CO2Alm", desc="CO2 Alarms", unit="")
	private int CO2ALM;
	@Metric( loc="" +L_SPO2_ALARMS,  code="SPO2Alm", desc="SPO2 Alarms", unit="--")
	private int SPO2ALM;
	@Metric( loc="" +L_NORESP_PERIOD,  code="NOBr", desc="No Breath period", unit="s")
	private int NOBr;
	@Metric( loc="" +L_CO2_STATUS, code="CO2Stat", desc="CO2 Status", unit="--")
	private int CO2STAT;
	

}
