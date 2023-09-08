package icuInterface.adapters.s5;

import javax.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class co_wedge_group {
	@Transient
	private static RpMetric[] metrics= IntfUtil.getMetrics(co_wedge_group.class);;

	@Transient
	int hdr;

	@Metric(loc = "co", code = "co", unit = "ml")
	Integer co;
	@Metric(loc = "blood_temp", code = "", unit = "?")
	Integer blood_temp;
	Integer ref;
	Integer pcwp;
};

