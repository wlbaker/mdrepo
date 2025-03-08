package icuInterface.adapters.s5;

import jakarta.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class nmt_group {
	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(nmt_group.class);;

	@Transient
	int hdr;
	@Metric(loc = "t1", code = "t1", unit = "?")
	Integer t1;
	Integer tration;
	Integer ptc;
};

