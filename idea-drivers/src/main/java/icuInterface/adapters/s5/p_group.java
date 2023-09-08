package icuInterface.adapters.s5;

import javax.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class p_group {
	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(p_group.class);;

	@Transient
	int hdr;

	@Metric(loc = "sys", code = "sys", unit = "mmHg", precision=2)
	Integer sys;
	@Metric(loc = "dia", code = "dia", unit = "mmHg", precision=2)
	Integer dia;
	@Metric(loc = "mean", code = "mean", unit = "mmHg", precision=2)
	Integer mean;
	@Metric(loc = "hr", code = "hr", unit = "mmHg", precision=2)
	Integer hr;
};

