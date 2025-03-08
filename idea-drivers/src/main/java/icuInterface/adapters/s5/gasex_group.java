package icuInterface.adapters.s5;

import jakarta.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class gasex_group {
	@Transient
	private static RpMetric[] metrics= IntfUtil.getMetrics(gasex_group.class);;
	
	int hdr;
	@Metric(loc = "vo2", code = "vo2", unit = "mmHg",precision=2)
	Integer vo2;
	@Metric(loc = "vco2", code = "vco2", unit = "mmHg", precision=2)
	Integer vco2;
	@Metric(loc = "ee", code = "ee", unit = "mmHg", precision=2)
	Integer ee;
	@Metric(loc = "rq", code = "rq", unit = "mmHg", precision=2)
	Integer rq;
}

