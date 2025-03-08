package org.pistax.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import lombok.Data;
import idea.schema.rp.RpMetric;

@Entity
@Table(name = "BMP180_measurement")
@SuppressWarnings("serial")
@Data
public class BMP180_measurement extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(BMP180_measurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public BMP180_measurement() {
		super(StreamID.WAVEFORM);
	}

	@Metric(loc = "T")  // temperature
	float t;
	@Metric(loc = "P")  // pressure
	float p;
}
