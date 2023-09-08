package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "Intellivue$Measurements")
@Data
@EqualsAndHashCode(callSuper=false)
public class Intellivue_Measurements extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( Intellivue_Measurements.class );
	}
	
	public Intellivue_Measurements() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Metric(loc ="spo2.hr", code="SpO2.HR", unit = "bpm")
	private Integer spo2$hr;

	@Metric(loc ="cvp.mean", code="CVP.MEAN", unit = "bpm")
	private Integer cvp$mean;
	

}
