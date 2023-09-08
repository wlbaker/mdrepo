package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class ABPBlock extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;
	
	public final static String SYSTOLIC_LOC = "sys";
	public final static String DIASTOLIC_LOC = "dia";
	public final static String MEAN_LOC = "mean";
	
	static {
		metrics = IntfUtil.getMetrics(ABPBlock.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public ABPBlock() {
		super( StreamID.MEASUREMENT );
	}
	
	
	@Metric(loc = SYSTOLIC_LOC, code = SYSTOLIC_LOC, unit="mmHg")
	private Integer systolic;
	@Metric(loc = DIASTOLIC_LOC, code = DIASTOLIC_LOC, unit="mmHg")
	private Integer diastolic;
	@Metric(loc = MEAN_LOC, code = MEAN_LOC, unit = "mmHg")
	private Integer mean;

}
