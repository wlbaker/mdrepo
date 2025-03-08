package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "VIT")
@Data
@EqualsAndHashCode(callSuper = false)
public class VITMeasurement extends PersistentItem {
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(VITMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public VITMeasurement() {
		super(StreamID.MEASUREMENT);
	}

	@Metric(loc="ra_p1", unit="mmHg")
	private int ra_p1;
	@Metric(loc="rv_p2", unit="mmHg")
	private int rv_p1;
	@Metric(loc="la_p3", unit="mmHg")
	private int la_p1;
	@Metric(loc="lv_p4", unit="mmHg")
	private int lv_p1;
	@Metric(loc="gp1_p5",unit="mmHg")
	private int gp2_p5;
	@Metric(loc="gp2_p6", unit="mmHg")
	private int gp2_p6;
	


}
