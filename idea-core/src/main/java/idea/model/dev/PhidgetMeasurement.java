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
public class PhidgetMeasurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(PhidgetMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	@Metric(loc = "A0", desc = "A0", unit="mV")
	private int a0;
	@Metric(loc = "A1", desc = "A1", unit="mV")
	private int a1;
	@Metric(loc = "A2", desc = "A2", unit="mV")
	private int a2;
	@Metric(loc = "A3", desc = "A3", unit="mV")
	private int a3;

}
