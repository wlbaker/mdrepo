package idea.analysis.event;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class BeatBlock extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	public final static String POS_LOC = "pos";
	public final static String SAMPLE_INTERVAL_LOC = "ivl";
	public final static String MS_INTERVAL_LOC = "ms";
	public final static String AMPLITUDE_LOC = "ampl";
	public final static String PENDING_LOC = "pend";
	public final static String LEAD_ID_LOC = "lead";
	public final static String DET_ID_LOC = "det";
	public final static String QUALITY_IDX_LOC = "qi";

	static {
		metrics = IntfUtil.getMetrics(BeatBlock.class);
	}

	public BeatBlock(StreamProducer src) {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}
	
	/*
	 * 
	 */

	@Metric(loc = POS_LOC, code = "pos")
	private Integer pos;
	@Metric(loc = SAMPLE_INTERVAL_LOC, code = "interval")
	private Integer samp_interval;
	@Metric(loc = MS_INTERVAL_LOC, code = "ms_interval", unit = "ms")
	private Integer ms_interval;
	@Metric(loc = AMPLITUDE_LOC, code = "amplitude")
	private Integer amplitude;
	@Metric(loc = PENDING_LOC, code = "pending")
	private Integer pending;
	@Metric(loc = LEAD_ID_LOC, code = "id")
	private Integer lead_id;
	@Metric(loc = DET_ID_LOC, code = "detector_id")
	private Integer detector_id;
	@Metric(loc = QUALITY_IDX_LOC, code = "quality_idx")
	private Integer quality_idx;

}
