package idea.model.dev;

import idea.intf.AdapterInterface;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;

import lombok.Data;

@Entity
@Data
public class C2Measurement extends PersistentItem {

	private static RpMetric[] metrics = IntfUtil.getMetrics(C2Measurement.class);

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public C2Measurement(AdapterInterface driver) {
		setDriver(driver);
	}

	@Metric(loc = "ARATE", desc = "Channel A Rate", unit = "ml/hr", precision = 1)
	private int rate1;
	@Metric(loc = "AVTBI", desc = "Channel A VTBI", unit = "ml", precision = 1)
	private int vtbd1;
	@Metric(loc = "AVINF", desc = "Total Volume CH-A", unit = "ml", precision = 1)
	private int vtot1;
	@Text(loc = "A*MDEV", desc = "Device Stat-A", length = 8)
	private int stat1;
	@Text(loc = "A*MCON", desc = "Control Stat-A", length = 8)
	private int control1;
	@Text(loc = "A*MINF", desc = "Infusion Stat-A", length = 8)
	private int infstat1;
	@Text(loc = "A*ACT", desc = "Action Stat-A", length = 8)
	private int actstat1;
	@Metric(loc = "BRATE", desc = "Channel B Rate", unit = "ml/hr", precision = 1)
	private int rate2;
	@Metric(loc = "BVTBI", desc = "Channel B VTBI", unit = "ml", precision = 1)
	private int vtbd2;
	@Metric(loc = "BVINF", desc = "Total Volume CH-B", unit = "ml", precision = 1)
	private int vtot2;
	@Text(loc = "B*MDEV", desc = "Device Stat-B", length = 8)
	private int stat2;
	@Text(loc = "B*MCON", desc = "Control Stat-B", length = 8)
	private int control2;
	@Text(loc = "B*MINF", desc = "Infusion Stat-B", length = 8)
	private int infstat2;
	@Text(loc = "B*ACT", desc = "Action Stat-B", length = 8)
	private int actstat2;

}
