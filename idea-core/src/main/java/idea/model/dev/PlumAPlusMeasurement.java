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
@SuppressWarnings("serial")
@Data
public class PlumAPlusMeasurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(PlumAPlusMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}
	
	public PlumAPlusMeasurement() {
		super( StreamID.MEASUREMENT );
	}

	@Metric( loc="RATE1", code="RATE1", desc="Channel 1 Rate", unit="ml/hr", precision=1)
	 private int rate1;
	@Metric( loc="RATE2", code="RATE2", desc="Channel 2 Rate", unit="ml/hr", precision=1)
	 private int rate2;
	@Metric( loc="RATE3", code="RATE3", desc="Channel 3 Rate", unit="ml/hr", precision=1)
	 private int rate3;
	@Metric( loc="VTBI1", code="VTBI1", desc="Channel 1 VTBI", unit="ml", precision=1)
	 private int vtbi1;
	@Metric( loc="VTBI2", code="VTBI2", desc="Channel 2 VTBI", unit="ml", precision=1)
	 private int vtbi2;
	@Metric( loc="VTBI3", code="VTBI3", desc="Channel 3 VTBI", unit="ml", precision=1)
	 private int vtbi3;
	@Metric( loc="INF1", code="INF1", desc="Channel 1 Infused", unit="ml", precision=1)
	 private int inf1;
	@Metric( loc="INF2", code="INF2", desc="Channel 2 Infused", unit="ml", precision=1)
	 private int inf2;
	@Metric( loc="INF3", code="INF3", desc="Channel 3 Infused", unit="ml", precision=1)
	 private int inf3;
	@Metric( loc="STATE1", code="STATE1", desc="Channel 1 State")
	 private int state1;
	@Metric( loc="STATE2", code="STATE2", desc="Channel 2 State")
	 private int state2;
	 @Metric( loc="STATE3", code="STATE3", desc="Channel 3 State")
	 private int state3;

}
