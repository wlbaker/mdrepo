package org.pistax.model;

import javax.persistence.Entity;
import javax.persistence.Table;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Waveform;
import lombok.Data;
import idea.schema.rp.RpMetric;

@Entity
@Table(name = "HT70_pressures")
@SuppressWarnings("serial")
@Data
public class HT70_pressures extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(HT70_pressures.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public HT70_pressures() {
		super(StreamID.WAVEFORM);
	}

	@Waveform(loc = "PAW", code = "PAW", unit = "", freq = 50, spp = 50, m=100.0)
	private int[] paw;
	@Waveform(loc = "FLOW", code = "FLOW", unit = "", freq = 50, spp = 50, m=100.0)
	private int[] flow;
}
