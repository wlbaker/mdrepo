package idea.model.dev;

import idea.intf.AdapterInterface;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;

import lombok.Data;

@Entity
@Data
public class C2Settings extends PersistentItem {
	private static RpMetric[] metrics = IntfUtil.getMetrics(C2Settings.class);

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public C2Settings(AdapterInterface driver) {
		setDriver(driver);
	}

	@Metric(loc = "AINFUSE", desc = "CH-A Infusion ON/OFF", unit = "", precision = 0)
	private int inf1;
	@Metric(loc = "ARATE", desc = "Channel A Rate", unit = "ml/hr", precision = 1)
	private int rate1;
	@Metric(loc = "AVTBI", desc = "Channel A VTBI", unit = "ml", precision = 1)
	private int vtbd1;
	@Metric(loc = "AVINF", desc = "Total Volume CH-A", unit = "ml", precision = 1)
	private int vtot1;
	@Metric(loc = "AZERO", desc = "Zero Total Volume-A", unit = "")
	private int zero1;
	@Metric(loc = "BINFUSE", desc = "CH-B Infusion ON/OFF", unit = "", precision = 0)
	private int inf2;
	@Metric(loc = "BRATE", desc = "Channel B Rate", unit = "ml/hr", precision = 1)
	private int rate2;
	@Metric(loc = "BVTBI", desc = "Channel B VTBI", unit = "ml", precision = 1)
	private int vtbd2;
	@Metric(loc = "BVINF", desc = "Total Volume CH-B", unit = "ml", precision = 1)
	private int vtot2;
	@Metric(loc = "BZERO", desc = "Zero Total Volume-B", unit = "")
	private int zero2;

}
