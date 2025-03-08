package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "SIMUSIN_M")
@Data
@EqualsAndHashCode(callSuper=false)
public class SimuSine_Measurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( SimuSine_Measurement.class );
	}
	
	public SimuSine_Measurement() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


	// @Column(name = "HR", nullable = true)
	@Metric(loc = "m0", code = "m0", unit = "L/bar")
	private int m0;
	@Metric(loc = "m1", code = "m1", unit = "L/bar", m = 0.1, b = 2)
	private int m1;
	@Metric(loc = "m2", code = "m2", unit = "mbar/L/s", m = 0.01)
	private int m2;
	@Metric(loc = "m3", code = "m3", unit = "mbar/L/s")
	private double m3;
	@Metric(loc = "m4", code = "m4", unit = "mbar")
	private double m4;
}

