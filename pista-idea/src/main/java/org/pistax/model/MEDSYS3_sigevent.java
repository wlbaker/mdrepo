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
public class MEDSYS3_sigevent extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(MEDSYS3_sigevent.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public MEDSYS3_sigevent() {
		super(StreamID.MEASUREMENT_2);
	}

	@Metric(loc = "code")
	int code;
	@Metric(loc = "pump")
	int pump;
	@Metric(loc = "aaf_type")
	int aaf_type;
	@Metric(loc = "aaf_index")
	int aaf_index;
	
}
