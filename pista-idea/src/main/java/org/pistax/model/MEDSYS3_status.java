package org.pistax.model;

import javax.persistence.Entity;
import javax.persistence.Table;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import lombok.Data;
import idea.schema.rp.RpMetric;

@Entity
@Table(name = "MEDSYS3_status")
@SuppressWarnings("serial")
@Data
public class MEDSYS3_status extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(MEDSYS3_status.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public MEDSYS3_status() {
		super(StreamID.SETTINGS);
	}

	@Metric(loc = "drug_a")
	String drug_a;
	@Metric(loc = "drug_b")
	String drug_b;
	@Metric(loc = "drug_c")
	String drug_c;
}
