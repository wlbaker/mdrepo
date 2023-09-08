package idea.model.dev;

import idea.intf.AdapterInterface;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class BodyguardSettings extends PersistentItem {

	public static final String ID_NO = "01";
	public static final String RATE1 = "04";
	public static final String VTBD1 = "05";
	public static final String VTOT1 = "06";
	public static final String STAT1 = "07";
	
	public static final String RATE2 = "14";
	public static final String VTBD2 = "15";
	public static final String VTOT2 = "16";
	public static final String STAT2 = "17";

	private static RpMetric [] metrics;

	static {
		metrics = IntfUtil.getMetrics(BodyguardSettings.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}
	
	public BodyguardSettings(AdapterInterface driver) {
		this.setDriver(driver);

	}


	@Metric(loc=ID_NO, code="id", desc="Hard ID")
	private int idNo;
	
	@Metric(loc=RATE1, code="dv1", desc="Rate-1", unit="ml/hr", precision=1)
	private int rate1;
	@Metric(loc=VTBD1, code="vt1", desc="Volume-1 VTBD", unit="ml", precision=1)
	private int vtbd1;

	@Metric(loc=RATE2, code="dv1", desc="Rate-2", unit="ml/hr", precision=1)
	private int rate2;
	@Metric(loc=VTBD2, code="vt1", desc="Volume-2 VTBD", unit="ml", precision=1)
	private int vtbd2;
}
