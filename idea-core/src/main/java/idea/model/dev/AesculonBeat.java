package idea.model.dev;


import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@Data
public class AesculonBeat extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;
	
	public final static String POS_LOC = "pos";
	public final static String SAMPLE_INTERVAL_LOC = "ivl";
	public final static String MS_INTERVAL_LOC = "ms";

	static {
		metrics = IntfUtil.getMetrics(AesculonBeat.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public AesculonBeat() {
		super(StreamID.MEASUREMENT);
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

}

