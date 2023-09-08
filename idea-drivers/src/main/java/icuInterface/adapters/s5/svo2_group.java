package icuInterface.adapters.s5;

import javax.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class svo2_group {
	@Transient
	private static RpMetric[] metrics= IntfUtil.getMetrics(svo2_group.class);;

	@Transient
	int hdr;

	@Metric(loc = "svo2", code = "svo2", unit = "%")
	Integer svo2;
};

