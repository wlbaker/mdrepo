package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class DetrendedFluctuationBlock extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;
	
	public final static String ALPHA_LOC = "alpha";
	public final static String ALPHA1_LOC = "alpha1";
	public final static String ALPHA2_LOC = "alpha2";
	
	static {
		metrics = IntfUtil.getMetrics(DetrendedFluctuationBlock.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	
	public DetrendedFluctuationBlock() {
		super( StreamID.MEASUREMENT );
	}
	
	@Metric(  loc=ALPHA_LOC, code="alpha")
	private double alpha;
	@Metric(  loc=ALPHA1_LOC, code="alpha1")
	private double alpha1;
	@Metric(  loc=ALPHA2_LOC, code="alpha2")
	private double alpha2;


}
