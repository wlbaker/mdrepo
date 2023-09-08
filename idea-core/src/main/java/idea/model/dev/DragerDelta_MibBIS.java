package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;

@Entity
@Table(name = "DragerDelta_MibBIS")
@Data
public class DragerDelta_MibBIS extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( DragerDelta_MibBIS.class );
	}
	
	public DragerDelta_MibBIS() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Column(name = "power", nullable = true)
	@Metric(loc = "bis.power", code = "bis.power", unit = "??")
	private int power;

	@Column(name = "sef", nullable = true)
	@Metric(loc = "bis.sef", code = "bis.sef", unit = "??")
	private int sef;

	@Column(name = "bct", nullable = true)
	@Metric(loc = "bis.bct", code = "bis.bct", unit = "??")
	private int bct;

	@Column(name = "emg", nullable = true)
	@Metric(loc = "bis.emg", code = "bis.emg", unit = "??")
	private int emg;

	@Column(name = "bis", nullable = true)
	@Metric(loc = "bis.bis", code = "bis.bis", unit = "??")
	private int bis;

	@Column(name = "sr", nullable = true)
	@Metric(loc = "bis.sr", code = "bis.sr", unit = "??")
	private int sr;

	@Column(name = "sqi", nullable = true)
	@Metric(loc = "bis.sqi", code = "bis.sqi", unit = "??")
	private Integer sqi;

}
