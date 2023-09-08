package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "DragerDelta_MibSVO2")
@Data
@EqualsAndHashCode(callSuper=false)
public class DragerDelta_MibSVO2 extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( DragerDelta_MibSVO2.class );
	}
	
	public DragerDelta_MibSVO2() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


	@Metric(loc = "mib_svo2.svo2", code = "svo2", unit = "??")
	private int svo2;

	@Metric(loc = "mib_svo2.sao2", code = "sao2", unit = "??")
	private int sao2;

	@Metric(loc = "mib_svo2.tb", code = "tb", unit = "??")
	private int tb;

	@Metric(loc = "mib_svo2.cco", code = "cco", unit = "??")
	private int cco;

	@Metric(loc = "mib_svo2.cci", code = "cci", unit = "??")
	private int cci;

	@Metric(loc = "mib_svo2.ico", code = "ico", unit = "??")
	private int ico;

	@Metric(loc = "mib_svo2.ici", code = "ici", unit = "??")
	private int ici;

	@Metric(loc = "mib_svo2.svr", code = "svr", unit = "??")
	private int svr;

	@Metric(loc = "mib_svo2.svri", code = "svri", unit = "??")
	private int svri;

	@Metric(loc = "mib_svo2.do2", code = "do2", unit = "??")
	private int do2;

	@Metric(loc = "mib_svo2.vo2", code = "vo2", unit = "??")
	private int vo2;

	@Metric(loc = "mib_svo2.sv", code = "sv", unit = "??")
	private int sv;

	@Metric(loc = "mib_svo2.sqi", code = "sqi", unit = "??")
	private int sqi;

	@Metric(loc = "mib_svo2.ref", code = "ref", unit = "??")
	private int ref;

	@Metric(loc = "mib_svo2.svi", code = "svi", unit = "??")
	private int svi;

	@Metric(loc = "mib_svo2.edv", code = "edv", unit = "??")
	private int edv;

	@Metric(loc = "mib_svo2.esv", code = "esv", unit = "??")
	private int esv;

}
