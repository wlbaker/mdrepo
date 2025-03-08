package icuInterface.adapters.s5;

import jakarta.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class flow_vol_group2 {
	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(flow_vol_group2.class);		
	
	@Transient
	int hdr;
	
	@Metric(loc = "ipeep", code = "ipeep", unit = "?" )
	Integer ipeep;
	
	@Metric(loc = "pmean", code = "pmean", unit = "?" )	
	Integer pmean;
	Integer raw;
	@Metric(loc = "mv_insp", code = "mv_insp", unit = "?" )	
	Integer mv_insp;
	@Metric(loc = "epeep", code = "epeep", unit = "?" )	
	Integer epeep;
	@Metric(loc = "mv_spont", code = "mv_spont", unit = "?" )	
	Integer mv_spont;
	@Metric(loc = "ie_ratio", code = "ie_ratio", unit = "?" )	
	Integer ie_ratio;
	@Metric(loc = "insp_time", code = "insp_time", unit = "?" )	
	Integer insp_time;
	@Metric(loc = "exp_time", code = "exp_time", unit = "?" )	
	Integer exp_time;
	
	@Metric(loc = "static_compliance", code = "static_compliance", unit = "?" )	
	Integer static_compliance;
	@Metric(loc = "static_pplat", code = "static_pplat", unit = "?" )	
	Integer static_pplat;
	@Metric(loc = "static_peepe", code = "static_peepe", unit = "?" )	
	Integer static_peepe;
	@Metric(loc = "static_peepi", code = "static_peepi", unit = "?" )	
	Integer static_peepi;
	
	@Transient
	short[] reserved;
}

