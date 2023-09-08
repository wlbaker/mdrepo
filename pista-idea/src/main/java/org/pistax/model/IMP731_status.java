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
@Table(name = "IMP731_status")
@SuppressWarnings("serial")
@Data
public class IMP731_status extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(IMP731_status.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public IMP731_status() {
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
	@Metric(loc = "phi")
	int Phi;
	@Metric(loc = "plow")
	int Plow;
	@Metric(loc = "br")
	int br;
	@Metric(loc = "fio2", m=0.1, unit="%")
	int fio2;
	@Metric(loc = "trigger")
	int trigger;
	@Metric(loc = "nonop_alarm")
	int nonop_alarm;
	@Metric(loc = "op_alarm")
	int op_alarm;
	@Metric(loc = "advisory_alarm")
	int advisory_alarm;
	@Metric(loc = "s_source")
	int s_source;
	@Metric(loc = "s_type")
	int s_type;
	@Metric(loc = "pga_temp")
	int pga_temp;
	@Metric(loc = "p_o2_tank")
	int p_o2_tank;
	@Metric(loc = "p_ambient")
	int p_ambient;
	@Metric(loc = "p_mode")
	int p_mode;
	@Metric(loc = "mode")
	int mode;
	@Metric(loc = "ie_ratio")
	int ie_ratio;
	@Metric(loc = "bpm_high")
	int bpm_high;
	@Metric(loc = "bpm_low")
	int bpm_low;
	@Metric(loc = "tv_high")
	int tv_high;
	@Metric(loc = "tv_low")
	int tv_low;
	@Metric(loc = "p_support")
	int p_support;
	@Metric(loc = "p_target")
	int p_target;
	@Metric(loc = "rise_tm")
	int rise_tm;
	@Metric(loc = "max_insp_tm")
	int max_insp_tm;
	@Metric(loc = "pct_peak_flow")
	int pct_peak_flow;

}
