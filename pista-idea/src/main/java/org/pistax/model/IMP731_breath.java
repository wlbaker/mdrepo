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
@Table(name = "IMP731_breath")
@SuppressWarnings("serial")
@Data
public class IMP731_breath extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(IMP731_breath.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public IMP731_breath() {
		super(StreamID.WAVEFORM);
	}

	@Metric(loc = "tv")
	int tv;
	@Metric(loc = "i_ie")
	int i_ie;
	@Metric(loc = "e_ie")
	int e_ie;
	@Metric(loc = "peep")
	int peep;
	@Metric(loc = "pip")
	int pip;
	@Metric(loc = "bpm")
	int bpm;
	@Metric(loc = "mv")
	int mv;
	@Metric(loc = "rpm")
	int rpm;
	@Metric(loc = "pend")
	int Pend;
	@Metric(loc = "pmean")
	int Pmean;
	@Metric(loc = "ppeak")
	int Ppeak;
	@Metric(loc = "mgmPO2")
	int mgmPO2;
	@Metric(loc = "mgmPO2min")
	int mgmPO2Min;
	@Metric(loc = "mgmPO2flow")
	int mgmPO2Flow;
	@Metric(loc = "mgmCompFlow")
	int mgmCompFlow;
	@Metric(loc = "leak")
	int leak;
	@Metric(loc = "airway_baseline")
	int airway_baseline;
	@Metric(loc = "failed_autocal")
	int failed_autocal;
	@Metric(loc = "failed_cycles")
	int failed_cycles;
	@Metric(loc = "baseline_noise")
	int baseline_noise;
	@Metric(loc = "pga_paw_offset")
	int pga_paw_offset;
	@Metric(loc = "pga_o2_offset")
	int pga_o2_offset;
	@Metric(loc = "pga_flow_offset")
	int pga_flow_offset;
	@Metric(loc = "o2_mv")
	int o2_mv;
	@Metric(loc = "plat")
	int plat;

}
