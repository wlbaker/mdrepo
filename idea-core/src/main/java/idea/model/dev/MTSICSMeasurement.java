package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "MTSICS")
@Data
@EqualsAndHashCode(callSuper = false)
public class MTSICSMeasurement extends PersistentItem {
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(MTSICSMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public MTSICSMeasurement() {
		super(StreamID.MEASUREMENT);
	}

	@Text(loc = "status", code = "status", desc = "Status", length = 1)
	private String status;
	@Metric(loc = "wt", code = "wt", desc = "Weight", unit = "g", precision = 2)
	private int weight;
	@Text(loc = "code", desc = "Code", length = 10)
	private String code;
	@Text(loc = "desc", desc = "Description", length = 16)
	private String desc;

}
