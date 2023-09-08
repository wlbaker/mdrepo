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
public class MEDSYS3_measurement extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(MEDSYS3_measurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public MEDSYS3_measurement() {
		super(StreamID.MEASUREMENT);
	}

	@Metric(loc = "ins_status")
	int ins_status;
	
	@Metric(loc = "pa_dev_status")
	int pa_dev_status;
	@Metric(loc = "pb_dev_status")
	int pb_dev_status;
	@Metric(loc = "pc_dev_status")
	int pc_dev_status;
	
	@Metric(loc = "pa_inf_status")
	int pa_inf_status;
	@Metric(loc = "pb_inf_status")
	int pb_inf_status;
	@Metric(loc = "pc_inf_status")
	int pc_inf_status;
	
	@Metric(loc = "pa_rate")
	int pa_rate;
	@Metric(loc = "pb_rate")
	int pb_rate;
	@Metric(loc = "pc_rate")
	int pc_rate;
	
	@Metric(loc = "pa_infused")
	int pa_infused;
	@Metric(loc = "pb_infused")
	int pb_infused;
	@Metric(loc = "pc_infused")
	int pc_infused;
	
	@Metric(loc = "pa_sec_infused")
	int pa_sec_infused;
	@Metric(loc = "pb_sec_infused")
	int pb_sec_infused;
	@Metric(loc = "pc_sec_infused")
	int pc_sec_infused;
}
