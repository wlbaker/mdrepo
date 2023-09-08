package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import java.util.Date;

import lombok.Data;

@Data
public class PICCOV3_Settings extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String PAT_LOC = "1.4l";
	public static final String HEIGHT_LOC = "6.6h";
	public static final String WEIGHT_LOC = "4.6";

	private static final String DATE_LOC = "9.5";

	static {
		metrics = IntfUtil.getMetrics(PICCOV3_Settings.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public PICCOV3_Settings() {
		super(StreamID.SETTINGS);
	}

	/*
	 * 
	 */

	@Metric(loc = PAT_LOC, code = "patID")
	private Integer patID;
	@Metric(loc = HEIGHT_LOC, code = "Height", unit = "in")
	private Integer height;
	@Metric(loc = WEIGHT_LOC, code = "Weight", unit = "kg")
	private Integer weight;
	@Metric(loc = DATE_LOC, code = "date")
	private Date dt;

}
