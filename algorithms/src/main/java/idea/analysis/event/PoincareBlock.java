package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class PoincareBlock extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	public final static String SDRR_LOC = "sddr";
	public final static String SDSD_LOC = "sdsd";
	public final static String SD1_LOC = "sd1";
	public final static String SD2_LOC = "sd2";
	public final static String SDRATIO_LOC = "sdration";
	
	static {
		metrics = IntfUtil.getMetrics(PoincareBlock.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}


		
	
	public PoincareBlock() {
		super(StreamID.MEASUREMENT);
	}
	

	@Metric( loc=SDRR_LOC, code="sdrr", desc="Standard Deviation of RRIs")
	private double SDRR;
	@Metric( loc=SDSD_LOC, code="sdsd", desc="Standard Deviation of RRI Diffs")
	private double SDSD;
	@Metric( loc=SD1_LOC, code="sd2", desc="Short-Term Variability")
	private double SD1;
	@Metric( loc=SD2_LOC, code="sd1", desc="Long-Term Variability")
	private double SD2;
	@Metric( loc=SDRATIO_LOC, code="sdratio", desc="Variability Ratio")
	private double SDRatio;
	
}
