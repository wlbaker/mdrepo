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
@Table(name = "HT70_status")
@SuppressWarnings("serial")
@Data
public class HT70_status extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(HT70_status.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public HT70_status() {
		super(StreamID.SETTINGS);
	}

	@Metric( loc="mode")
	int mode;

	@Metric( loc="mvolprhi")
	int mvolprhi;

	@Metric( loc="mvolprlo")
	int mvolprlo;

	@Metric( loc="ppawprhi")
	int ppawprhi;

	@Metric( loc="ppawprlo")
	int ppawprlo;

	@Metric( loc="rateprhi")
	int rateprhi;

	@Metric( loc="apintvl")
	int apintvl;

	@Metric( loc="fio2prhi")
	int fio2prhi;

	@Metric( loc="fio2prlo")
	int fio2prlo;

	@Metric( loc="alvol")
	int alvol;

	@Metric( loc="tvolprcn")
	int tvolprcn;

	@Metric( loc="ppawprcn")
	int ppawprcn;

	@Metric( loc="ti")
	int ti;

	@Metric( loc="rateprcn")
	int rateprcn;

	@Metric( loc="trig")
	int trig;

	@Metric( loc="psprcn")
	int psprcn;

	@Metric( loc="peepprcn")
	int peepprcn;

	@Metric( loc="pflow")
	int pflow;

	@Metric( loc="flowtrig")
	int flowtrig;

	@Metric( loc="slope")
	int slope;

	@Metric( loc="psethresh")
	int psethresh;

	@Metric( loc="psmaxti")
	int psmaxti;

	@Metric( loc="wave")
	int wave;

	@Metric( loc="biasflow")
	int biasflow;

	@Metric( loc="niv")
	int niv;

	@Metric( loc="nmpr")
	int nmpr;

	@Metric( loc="pcvmode")
	int pcvmode;
}
