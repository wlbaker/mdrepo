package idea.model.dev;

import idea.intf.AdapterInterface;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class PlumA3Measurement extends PersistentItem {

	public static final String ID_NO = "01";
	public static final String RATE1aA = "04";
	public static final String VTBD1A = "05";
	public static final String VTOT1A = "06";
	public static final String STA = "07";
	public static final String CFG = "08";
	public static final String DRUGNAME = "DN";

	private static RpMetric [] metrics;

	static {
		metrics = IntfUtil.getMetrics(PlumA3Measurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}
	
	public PlumA3Measurement(AdapterInterface driver) {
		this.setDriver(driver);

	}


	@Metric(loc=ID_NO, code="id", desc="Hard ID")
	private int idNo;
	
	@Metric(loc=RATE1aA, code="dv1", desc="Rate 1A", unit="ml")
	private int rate1A;
	@Metric(loc=VTBD1A, code="vt1", desc="Volume VTBD 1A", unit="ml")
	private int vtbd1a;
	@Metric(loc=VTOT1A, code="tv1", desc="Total Volume 1A", unit="hr")
	private int vtot1a;
	@Text(loc=STA, code="sta", desc="Status",  length=16)
	String sta;
	@Text(loc=CFG, code="cfg", desc="Config",  length=16)
	String cfg;
	@Text(loc=DRUGNAME, code="dn1", desc="Drug Name", length=16)
	String drugName;

}
