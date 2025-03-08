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
@Table(name = "HT70_breath")
@SuppressWarnings("serial")
@Data
public class HT70_breath extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(HT70_breath.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public HT70_breath() {
		super(StreamID.MEASUREMENT);
	}

	@Metric( loc="tvol")
	int tvol;

	@Metric( loc="mvol")
	int mvol;

	@Metric( loc="rate")
	int rate;

	@Metric( loc="ppaw")
	int ppaw;

	@Metric( loc="map")
	int map;

	@Metric( loc="peep")
	int peep;

	@Metric( loc="fio2")
	int fio2;

	@Metric( loc="pflow")
	int pflow;

	@Metric( loc="i2e")
	int i2e;

	@Metric( loc="o2cyltime")
	int o2cyltime;

	@Metric( loc="battime")
	int battime;

}
