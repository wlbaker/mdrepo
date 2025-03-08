package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@Data
public class PulseTransitTimeBlock extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;


	static {
		metrics = IntfUtil.getMetrics(PulseTransitTimeBlock.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}
	
	public final static String PTT_LOC = "PTT";
	
	
	public PulseTransitTimeBlock() {
		super(StreamID.MEASUREMENT);
	}
	
	@Metric(loc = PTT_LOC, unit = "ms", precision=0)
	private double PTT;
	

}
