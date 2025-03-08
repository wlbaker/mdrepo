package idea.tsoffline.vizwiz;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "ASTM_Measurement")
@Data
@EqualsAndHashCode(callSuper = false)
public class PlotData extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics(PlotData.class);
	}

	public PlotData() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	@Metric(loc = "subject")
	private String subject;
	
	
	@Metric(loc = "caption")
	private String caption;
	
	
	@Metric(loc = "name1")
	private String name1;
	
	@Metric(loc = "arg1")
	private double[] arg1;
	
	@Metric(loc = "name2")
	private String name2;
	
	@Metric(loc = "arg2")
	private double[] arg2;

	@Metric(loc = "name3")
	private String name3;
	
	@Metric(loc = "arg3")
	private double[] arg3;
}
