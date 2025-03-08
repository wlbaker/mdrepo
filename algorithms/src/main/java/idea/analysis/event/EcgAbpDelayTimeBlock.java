package idea.analysis.event;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class EcgAbpDelayTimeBlock extends PersistentItem {

	public final static String DT_LOC = "dt";
	
	@Metric( loc=DT_LOC, code="dt", desc="ECG-ABP Delay Time")
	private int dt;
	
	@Transient
	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(EcgAbpDelayTimeBlock.class);
	}	

	
	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

}
