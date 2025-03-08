package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class StatAvBlock extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;


	static {
		metrics = IntfUtil.getMetrics(StatAvBlock.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public final static String SDRR_LOC = "sdrr";
	public final static String SDSD_LOC = "sdsd";
	public final static String SDAV_LOC = "sdav";
	public final static String STATAV_LOC = "statav";
	
	public StatAvBlock() {
		super(StreamID.MEASUREMENT);
	}
	
	 @Metric( loc=SDRR_LOC, code="sdrr", desc="Standard Deviation of RRIs")
	private double sdrr;
	 @Metric( loc=SDSD_LOC, code="sdsd", desc="Standard Deviation of RRI Diffs")
	private double sdsd;
	 @Metric( loc=SDAV_LOC, code="sdav", desc="Standard Deviation of RRI Epochs")
	private double sdav;
	 @Metric( loc=STATAV_LOC, code="statav", desc="Index of Nonstationarity")
	private double statav;
	
	
	

}
