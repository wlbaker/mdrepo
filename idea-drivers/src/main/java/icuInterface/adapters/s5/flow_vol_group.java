package icuInterface.adapters.s5;

import jakarta.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;


@Data
public class flow_vol_group {
	@Transient
	private static RpMetric[] metrics;
	static {
		metrics = IntfUtil.getMetrics(flow_vol_group.class);		
	}
	
	@Transient
	int hdr;
	
	@Metric(loc = "rr", code = "RR", unit = "?" )
	Integer rr;
	@Metric(loc = "ppeak", code = "", unit = "?" )
	Integer ppeak;
	@Metric(loc = "peep", code = "", unit = "?" )
	Integer peep;
	@Metric(loc = "pplat", code = "", unit = "?" )
	Integer pplat;
	@Metric(loc = "tv_insp", code = "", unit = "?" )
	Integer tv_insp;
	@Metric(loc = "tv_exp", code = "", unit = "?" )
	Integer tv_exp;
	@Metric(loc = "compliance", code = "", unit = "?" )
	Integer compliance;
	@Metric(loc = "mv_exp", code = "", unit = "?" )
	Integer mv_exp;
};

