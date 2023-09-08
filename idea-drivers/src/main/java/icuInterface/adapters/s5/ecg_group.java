package icuInterface.adapters.s5;

import javax.persistence.Transient;

import idea.model.IntfUtil;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class ecg_group {
	private static RpMetric metrics [];
	
	static {
		metrics = IntfUtil.getMetrics( ecg_group.class );
	}
	
	@Transient
	int hdr;
	
	@Metric(loc = "ecg.hr", code = "ECG_HR", unit = "bpm_100", precision=2 )
	Integer hr;
	@Metric(loc = "ecg.st1", code="ECG_ST1", precision=2)
	Integer st1;
	@Metric(loc = "ecg.st2", code="ECG_ST2", precision=2)
	Integer st2;
	@Metric(loc = "ecg.st3", code="ECG_ST3", precision=2)
	Integer st3;
	@Metric(loc = "ecg.imp_rr", code="ECG_IMP_RR", precision=2)
	Integer imp_rr;
	
};

