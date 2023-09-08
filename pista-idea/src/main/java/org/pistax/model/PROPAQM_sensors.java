package org.pistax.model;

import javax.persistence.Entity;
import javax.persistence.Table;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import lombok.Data;
import idea.schema.rp.RpMetric;

@Entity
@Table(name = "PROPAQM_sensors")
@SuppressWarnings("serial")
@Data
public class PROPAQM_sensors extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String CH1_LOC = "ecg";
	public static final String CH2_LOC = "co2";

	static {
		metrics = IntfUtil.getMetrics(PROPAQM_sensors.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public PROPAQM_sensors() {
		super(StreamID.WAVEFORM);
	}


	@Waveform(loc = CH1_LOC, code = CH1_LOC, unit = "u0", freq = 250, spp = 30, m=100.0)
	private int[] ecg;
	@Waveform(loc = CH2_LOC, code = CH2_LOC, unit = "u1", freq = 125, spp = 30, m=100.0)
	private int[] co2;
}

