package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@SuppressWarnings("serial")
@Data
public class MF3X00Result extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String RATE_LOC = "RATE";
	public static final String VOL_LOC = "VOL";

	static {
		metrics = IntfUtil.getMetrics(PICCOV3_Vitals.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public MF3X00Result() {
		super(StreamID.MEASUREMENT);
	}

	/*
	 * 
	 */

	@Metric(loc = RATE_LOC, code = "Rate", unit = "l/min/m2", precision=2)
	private int rate;
	@Metric(loc = VOL_LOC, code = "Vol", unit = "ml")
	private int volume;
}

