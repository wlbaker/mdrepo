package icuInterface.adapters.s5;

import javax.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class tono_group {
	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(tono_group.class);;
	
	@Transient
	int hdr;
	
	@Metric(loc = "prco2", code ="", unit = "?")
	Integer prco2;
	
	@Metric(loc = "et", code = "", unit = "?" )
	Integer pr_et;
	Integer pr_pa;
	Integer pa_delay;
	Integer phi;
	Integer phi_delay;
	Integer amb_press;
	Integer cpma;
}

