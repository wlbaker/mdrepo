package idea.model.dev;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Transient;

import lombok.Data;

@Entity
@SuppressWarnings("serial")
@Data
public class AS50_Settings extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(AS50_Settings.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	@Metric(loc = "PRIST", desc = "Primary Start")
	private int infuse;
	@Metric(loc = "BOLSIZ", desc = "Bolus Size", unit = "ml/hr", precision = 2)
	private int bolSize;
	@Metric(loc = "PRIRATE", desc = "Primary Rate", unit = "ml/hr", precision = 2)
	private int priRate;
	@Metric(loc = "PRIVTBI", desc = "Primary Volume to be Infused", unit = "mL", precision = 2)
	private int vtbi;
	@Metric(loc = "TVI", desc = "Total Volume Infused", unit = "mL", precision = 2)
	private int vinf;
	@Metric(loc = "CLRTVI", desc = "Clear Total Volume Infused")
	private int ctvi;

}
