package idea.analysis.event;

import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@SuppressWarnings("serial")
@Data
public class AutocorrelationBlock extends PersistentItem {

	public final static String SDRR_LOC = "sdrr";
	public final static String SDSD_LOC = "sdsd";
	public final static String SOD_LOC  = "sod";

	@Metric( loc=SDSD_LOC, code="sdsd", desc="Standard Deviation of RRI Diffs")
	private double SDSD;
	@Metric( loc=SDRR_LOC, code="sdrr", desc="Standard Deviation of RRIs")
	private double SDRR;
	@Metric( loc=SOD_LOC, code="sod", desc="Autocorrelation of RRI Histograms")
	private double SOD;
	
	@Transient
	protected static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(AutocorrelationBlock.class);
	}	

	
	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}
	

}
