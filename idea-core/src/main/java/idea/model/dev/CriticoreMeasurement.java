package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@Table(name = "Criticore")
@Data
public class CriticoreMeasurement extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(CriticoreMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public CriticoreMeasurement() {
		super(StreamID.MEASUREMENT);
	}

	public final static String BARD_CURRENT_TIME = "00";
	public final static String BARD_UO = "01";
	public final static String BARD_RATE = "02";
	public final static String BARD_VOL = "03";
	public final static String BARD_PVOL = "04";
	public final static String BARD_PRIOR_TIME = "05";

	@Metric(loc = BARD_CURRENT_TIME, code = "time", desc = "Current Time", unit = "hhmm")
	private Integer currentTime;

	@Metric(loc = BARD_UO, code = "UO", desc = "Urine Output", unit = "ml")
	private Integer currentOutput;

	@Metric(loc = BARD_RATE, code = "rate", desc = "Urine Rate", unit = "ml/hr")
	private Integer ratePerHour;

	@Metric(loc = BARD_VOL, code = "vol", desc = "Total Volume", unit = "ml")
	private Integer totalVolume;

	@Metric(loc = BARD_PVOL, code = "pvol", desc = "Prior Output", unit = "ml")
	private Integer priorOutput;

	@Metric(loc = BARD_PRIOR_TIME, code = "ptm", desc = "Prior Time", unit = "ms")
	private Integer priorTime;

}
