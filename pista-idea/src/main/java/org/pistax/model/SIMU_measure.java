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
@Table(name = "PSIMU_MEASURE")
@SuppressWarnings("serial")
@Data
public class SIMU_measure extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String VITAL0_LOC = "vital0";
	public static final String VITAL1_LOC = "vital1";
	public static final String VITAL2_LOC = "vital2";
	public static final String VITAL3_LOC = "vital3";

	static {
		metrics = IntfUtil.getMetrics(SIMU_measure.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public SIMU_measure() {
		super(StreamID.WAVEFORM);
	}

	@Metric(loc = VITAL0_LOC, code = VITAL0_LOC, m = 1, unit="mmHg")
	private int v0;
	@Metric(loc = VITAL1_LOC, code = VITAL1_LOC, m = 10, unit="cmH2O")
	private int v1;
	@Metric(loc = VITAL2_LOC, code = VITAL2_LOC, m = 100, unit="V")
	private float v2;
	@Metric(loc = VITAL3_LOC, code = VITAL3_LOC, m = 0.1, unit="\u2126")   // ohm
	private float v3;
}
