package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class LyaBlock extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	public static final String LYA_ITEM = "lya";
	public static final String LYA2_ITEM = "lya2";
	public static final String DIVASM_ITEM = "asym";
	public static final String LYA_ERROR = "err";
	public static final String DIVLEN_ITEM = "divlen";


	
	static {
		metrics = IntfUtil.getMetrics(LyaBlock.class);
	}

	public LyaBlock() {
		super( StreamID.MEASUREMENT );
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}
	
	/*
	 * 
	 */

	@Metric(loc = LYA_ITEM, code =LYA_ITEM, desc= "Lyapunov", precision=3 )
	private double lya;
	@Metric(loc = LYA2_ITEM, code = LYA2_ITEM, desc = "Lyapunov Offset 2", precision=3 )
	private double lya2;
	@Metric(loc = DIVASM_ITEM, code = DIVASM_ITEM, desc ="Divergence Asymtope", precision=2)
	private double divergence;
	@Metric(loc = DIVLEN_ITEM, code = DIVLEN_ITEM, desc="Divergence Length", precision=2)
	private double divlen;
	@Metric(loc = LYA_ERROR, code = LYA_ERROR, desc="Lyapunov Error", precision=2)
	private double err;
	
}
