package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper=false)
public class Propaq_Measurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( Propaq_Measurement.class );
	}
	
	public Propaq_Measurement() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


	// @Column(name = "HR", nullable = true)
	@Metric(loc = "hr", code = "HR", unit = "bpm")
	private int hr;
	
	@Metric(loc = "nibp", code = "NIBP", unit = "mmHg")
	private int NIBP;
	
	@Metric(loc = "spo2", code = "SpO2", unit = "%")
	private int SpO2;
	
	@Metric(loc = "resp", code = "Resp", unit = "br/m")
	private int resp;
	
	@Metric(loc = "etco2", code = "EtCO2", unit = "mmHg")
	private int EtCO2;

}

