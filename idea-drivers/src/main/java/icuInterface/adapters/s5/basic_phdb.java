package icuInterface.adapters.s5;

import jakarta.persistence.Transient;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.CompositeMetric;
import idea.schema.rp.RpMetric;
import lombok.Data;


@Data
public class basic_phdb extends PersistentItem {

	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(basic_phdb.class);


	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public basic_phdb(StreamProducer driver) {
		super( driver, StreamID.MEASUREMENT.getCode() );
		
		for (int i = 0; i < 4; i++) {
			p[i] = new p_group();
			t[i] = new t_group();
		}
		for (int i = 0; i < 2; i++) {
			p56[i] = new p_group();
		}
	}

	@CompositeMetric(loc = "test_ar", max_count=3)
	int[] test_ar = new int[3];
	
	@CompositeMetric(loc = "ecg")
	ecg_group ecg = new ecg_group();

	@CompositeMetric(loc = "p", max_count=4)
	p_group[] p = new p_group[4]; // invasive pressure measurements

	@CompositeMetric(loc = "nibp")
	nibp_group nibp = new nibp_group();

	@CompositeMetric(loc = "t", max_count=4)
	t_group[] t = new t_group[4];

	@CompositeMetric(loc = "spo2")
	SpO2_pl_group SpO2 = new SpO2_pl_group();

	@CompositeMetric(loc = "co2")
	co2_group co2 = new co2_group();

	@CompositeMetric(loc = "o2")
	o2_group o2 = new o2_group();

	@CompositeMetric(loc = "no2")
	n2o_group n2o = new n2o_group();

	@CompositeMetric(loc = "aa")
	aa_group aa = new aa_group();

	@CompositeMetric(loc = "flow_vol")
	flow_vol_group flow_vol = new flow_vol_group();

	@CompositeMetric(loc = "co_wedge")
	co_wedge_group co_wedge = new co_wedge_group();

	@CompositeMetric(loc = "nmt")
	nmt_group nmt = new nmt_group();

	@CompositeMetric(loc = "ecgx")
	ecg_extra_group ecgx = new ecg_extra_group();

	@CompositeMetric(loc = "svo2")
	svo2_group svo2 = new svo2_group();

	@CompositeMetric(loc = "p56", max_count=2)
	p_group[] p56 = new p_group[2];

	@Transient
	byte[] reserved = new byte[2];

};
