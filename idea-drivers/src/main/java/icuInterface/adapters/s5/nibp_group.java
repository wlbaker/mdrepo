package icuInterface.adapters.s5;

import jakarta.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class nibp_group {
	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(nibp_group.class);;

	@Transient
	int hdr;

	@Metric(loc = "sys", code = "sys", unit = "mmHg",precision=2)
	Integer sys;
	@Metric(loc = "dia", code = "dia", unit = "mmHg", precision=2)
	Integer dia;
	@Metric(loc = "mean", code = "mean", unit = "mmHg", precision=2)
	Integer mean;
	@Metric(loc = "hr", code = "hr", unit = "mmHg", precision=2)
	Integer hr;
};
