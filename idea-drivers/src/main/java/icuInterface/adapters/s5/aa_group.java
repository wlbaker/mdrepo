package icuInterface.adapters.s5;

import javax.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class aa_group {
	@Transient
	private static RpMetric[] metrics= IntfUtil.getMetrics(aa_group.class);;

	@Transient
	int hdr;
	@Metric(loc = "et", code = "et", unit = "mmHg", precision=2)
	Integer et;
	@Metric(loc = "fi", code = "fi", unit = "mmHg", precision=2)
	Integer fi;
	Integer mac_sum;
};

