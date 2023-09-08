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
@Table(name = "PSIMU_SENSOR")
@SuppressWarnings("serial")
@Data
public class SIMU_sensor extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String CH0_LOC = "waveform0";
	public static final String CH1_LOC = "waveform1";
	public static final String CH2_LOC = "waveform2";
	public static final String CH3_LOC = "waveform3";

	static {
		metrics = IntfUtil.getMetrics(SIMU_sensor.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public SIMU_sensor() {
		super(StreamID.WAVEFORM);
	}


	@Waveform(loc = CH0_LOC, code = CH0_LOC, freq = 50, spp = 50, m=1)
	private int[] ch0;
	@Waveform(loc = CH1_LOC, code = CH1_LOC, freq = 50, spp = 50, m=1)
	private int[] ch1;
	@Waveform(loc = CH2_LOC, code = CH2_LOC, freq = 50, spp = 50, m=1)
	private float[] ch2;
	@Waveform(loc = CH3_LOC, code = CH3_LOC, freq = 50, spp = 50, m=1)
	private float[] ch3;
}

