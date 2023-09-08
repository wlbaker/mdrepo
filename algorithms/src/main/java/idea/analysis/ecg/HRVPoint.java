package idea.analysis.ecg;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Column;
import javax.persistence.Transient;

import lombok.Data;
import idea.analysis.HRVProcessor;

@Data
public class HRVPoint extends PersistentItem {
	public final static String HF_LOC = "HF";
	public final static String LF_LOC = "LF";
	public final static String HFLF_LOC = "HF_LF";
	public final static String LFHF_LOC = "LF_HF";

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(HRVPoint.class);
	}
	
	public HRVPoint(HRVProcessor src) {
		super(src, StreamID.MEASUREMENT.getCode());
	}

	@Column(name = HF_LOC, nullable = true)
	@Metric(loc = HF_LOC, code = "HF", desc = "HF", unit = "")
    private double HF;
	
	@Column(name = LF_LOC, nullable = true)
	@Metric(loc = LF_LOC, code = "LF", desc = "LF", unit = "")
    private double LF;

	@Column(name = HFLF_LOC, nullable = true)
	@Metric(loc = HFLF_LOC, code = "HF_LF", desc = "HF_LF", unit = "")
	private double HF_LF;

	@Column(name = LFHF_LOC, nullable = true)
	@Metric(loc = LFHF_LOC, code = "LF_HF", desc = "LF_HF", unit = "")
	private double LF_HF;

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

}