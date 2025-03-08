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
@Table(name = "PROPAQM_vitals")
@SuppressWarnings("serial")
@Data
public class PROPAQM_vitals extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(PROPAQM_vitals.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public PROPAQM_vitals() {
		super(StreamID.WAVEFORM);
	}

	@Metric(loc = "monitor")
	int monitored_bits;
	@Metric(loc = "alarm")
	int alarm_bits;
	@Metric(loc = "state")
	int datastate_bits;
	@Metric(loc = "temp0", precision=1)
	int temp0;
	@Metric(loc = "temp1", precision=1)
	int temp1;
	@Metric(loc = "temp2", precision=1)
	int temp2;
	@Metric(loc = "hr", precision=1)
	int hr;
	@Metric(loc = "fico2", precision=1, unit="%")
	int fico2;
	@Metric(loc = "spo2_spco")
	int spo2_spco;
	@Metric(loc = "spo2_spmet")
	int spo2_spmet;
	@Metric(loc = "spo2_pvi")
	int spo2_pvi;
	@Metric(loc = "spo2_pi")
	int spo2_pi;
	@Metric(loc = "spo2_spoc")
	int spo2_spoc;
	@Metric(loc = "spo2_sphb")
	int spo2_sphb;
	@Metric(loc = "spo2_pct")
	int spo2_pct;
	@Metric(loc = "nibp_sys")
	int nibp_sys;
	@Metric(loc = "nibp_dia")
	int nibp_dia;
	@Metric(loc = "nibp_map")
	int nibp_map;
	@Metric(loc = "ibp0_sys")
	int ibp0_sys;
	@Metric(loc = "ibp0_dia")
	int ibp0_dia;
	@Metric(loc = "ibp0_map")
	int ibp0_map;
	@Metric(loc = "ibp1_sys")
	int ibp1_sys;
	@Metric(loc = "ibp1_dia")
	int ibp1_dia;
	@Metric(loc = "ibp1_map")
	int ibp1_map;
	@Metric(loc = "ibp2_sys")
	int ibp2_sys;
	@Metric(loc = "ibp2_dia")
	int ibp2_dia;
	@Metric(loc = "ibp2_map")
	int ibp2_map;

}
