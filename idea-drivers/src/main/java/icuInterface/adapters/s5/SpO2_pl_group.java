package icuInterface.adapters.s5;

import jakarta.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;


@Data
public class SpO2_pl_group {
	@Transient
	private static RpMetric[] metrics = IntfUtil.getMetrics(SpO2_pl_group.class);;

	@Transient
	int hdr;
	
	@Metric(loc = "spo2", code = "", unit = "%", precision=2)
	Integer SpO2;
	@Metric(loc = "pr", code = "", unit = "bpm")
	Integer pr;
	@Metric(loc = "ir_amp", code = "", unit = "?")
	Integer ir_amp;
	@Metric(loc = "svo2", code = "", unit = "?")
	Integer SvO2;
};
