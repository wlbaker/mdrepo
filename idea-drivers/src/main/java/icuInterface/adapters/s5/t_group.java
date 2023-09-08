package icuInterface.adapters.s5;

import javax.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class t_group {
	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(t_group.class);;

	@Transient
	int hdr;
	@Metric(loc = "temp", code = "temp", unit = "C", precision=2)
	Integer temp;
};
