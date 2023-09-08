package icuInterface.adapters.s5;

import javax.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class ecg_extra_group { // THIS GROUP HAS NO HEADER according to the docs
	@Transient
	private static RpMetric[] metrics= IntfUtil.getMetrics(ecg_extra_group.class);;

	@Metric(loc = "hr_ecg", code = "hr_ecg", unit = "bpm")
	Integer hr_ecg;

	@Metric(loc = "hr_max", code = "hr_max", unit = "bpm")
	Integer hr_max;

	@Metric(loc = "hr_min", code = "hr_min", unit = "bpm")
	Integer hr_min;
};

