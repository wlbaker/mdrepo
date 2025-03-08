package org.pistax.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import lombok.Data;
import idea.schema.rp.RpMetric;

@Entity
@Table(name = "IMP731_S")
@SuppressWarnings("serial")
@Data
public class IMP731_sensors extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String CH0_LOC = "w0";
	public static final String CH1_LOC = "w1";
	public static final String CH2_LOC = "w2";
	public static final String CH3_LOC = "w3";

	static {
		metrics = IntfUtil.getMetrics(IMP731_sensors.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public IMP731_sensors() {
		super(StreamID.WAVEFORM);
	}


	@Waveform(loc = CH0_LOC, code = CH0_LOC, unit = "", freq = 100, spp = 100, m=1)
	private int[] w0;
	@Waveform(loc = CH1_LOC, code = CH1_LOC, unit = "", freq = 100, spp = 100, m=1)
	private int[] w1;
	@Waveform(loc = CH2_LOC, code = CH2_LOC, freq = 100, spp = 100, m=1)
	private int[] w2;
	@Waveform(loc = CH3_LOC, code = CH3_LOC, freq = 100, spp = 100, m=1)
	private int[] w3;
	
}

