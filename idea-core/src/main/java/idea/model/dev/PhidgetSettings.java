package idea.model.dev;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Transient;

import lombok.Data;

@Entity
@SuppressWarnings("serial")
@Data
public class PhidgetSettings extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(PhidgetSettings.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	@Metric(loc = "F", desc = "Sample Rate", unit="hz")
	private int f;
	@Metric(loc = "GAIN", desc = "Gain", unit = "m", precision = 2)
	private int gain;
	@Metric(loc = "M", desc = "Slope", unit = "", precision = 2)
	private int m;
	@Metric(loc = "OFFSET", desc = "Offset", unit = "", precision = 2)
	private int offset;

}
