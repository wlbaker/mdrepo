package idea.model.dev;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@SuppressWarnings("serial")
@Data
public class AS50_Measurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(AS50_Measurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	@Metric(loc = "BOLRAT", desc = "Bolus Rate", unit = "ml/hr", precision = 2)
	private int bolRate;
	@Metric(loc = "BOLSIZ", desc = "Bolus Size", unit = "ml/hr", precision = 2)
	private int bolSize;
	@Metric(loc = "MAXDOSE", desc = "Maximum Dose", unit = "mL", precision = 2)
	private int maxDose;
	@Metric(loc = "MAXRATE", desc = "Maximum Rate", unit = "mL", precision = 2)
	private int maxRate;
	@Metric(loc = "MINDOSE", desc = "Minimum Dose", unit = "mL", precision = 2)
	private int minDose;
	@Metric(loc = "MINRATE", desc = "Minimum Rate", unit = "mL", precision = 2)
	private int minRate;
	@Metric(loc = "PRIRATE", desc = "Primary Rate", unit = "ml/hr", precision = 2)
	private int priRate;
	@Metric(loc = "PRIVTBI", desc = "Primary Volume to be Infused", unit = "mL", precision = 2)
	private int vtbi;
	@Text(loc = "PROTOCOL", desc = "Protocol Name", length = 10)
	private String protocol;
	@Text(loc = "STATUS", desc = "Status", length = 10)
	private String status;
	@Metric(loc = "TVI", desc = "Total Volume Infused", unit = "mL", precision = 2)
	private int vinf;

}
