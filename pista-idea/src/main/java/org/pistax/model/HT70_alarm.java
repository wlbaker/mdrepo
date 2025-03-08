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
@Table(name = "HT70_alarm")
@SuppressWarnings("serial")
@Data
public class HT70_alarm extends PersistentItem {

	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(HT70_alarm.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public HT70_alarm() {
		super(StreamID.ALARM);
	}

	@Metric( loc="sysfault")
	int sysfault;

	@Metric( loc="battfail")
	int battfail;

	@Metric( loc="pwrfail")
	int pwrfail;

	@Metric( loc="occlusionsust")
	int occlusionsust;

	@Metric( loc="prox")
	int prox;

	@Metric( loc="ppawlo")
	int ppawlo;

	@Metric( loc="occlusion")
	int occlusion;

	@Metric( loc="apnea")
	int apnea;

	@Metric( loc="mvollo")
	int mvollo;

	@Metric( loc="mvolhi")
	int mvolhi;

	@Metric( loc="pcvnr")
	int pcvnr;

	@Metric( loc="fio2lo")
	int fio2lo;

	@Metric( loc="peeplo")
	int peeplo;

	@Metric( loc="ppawhi")
	int ppawhi;

	@Metric( loc="battlo")
	int battlo;

	@Metric( loc="extbattlo")
	int extbattlo;

	@Metric( loc="vtehi")
	int vtehi;

	@Metric( loc="fio2hi")
	int fio2hi;

	@Metric( loc="peephi")
	int peephi;

	@Metric( loc="batton")
	int batton;

	@Metric( loc="battery")
	int battery;

	@Metric( loc="ratehi")
	int ratehi;

	@Metric( loc="fio2sensor")
	int fio2sensor;

	@Metric( loc="backup")
	int backup;

	@Metric( loc="nopwr")
	int nopwr;


}
