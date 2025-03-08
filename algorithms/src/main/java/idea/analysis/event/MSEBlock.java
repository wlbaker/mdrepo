package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Column;
import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class MSEBlock extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;


	static {
		metrics = IntfUtil.getMetrics(MSEBlock.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public final static String MSE1_LOC = "MSE1";
	public final static String MSE2_LOC = "MSE2";
	public final static String MSE3_LOC = "MSE3";
	public final static String MSE4_LOC = "MSE4";
	public final static String MSE5_LOC = "MSE5";
	public final static String MSECOMPLEXITY_LOC = "MSE";

	public MSEBlock() {
		super(StreamID.MEASUREMENT);
	}

	@Column(name = MSE1_LOC, nullable = true)
	@Metric(loc = MSE1_LOC, code = "mse1", desc = "MSE scale 1", unit = "", precision = 2)
	private int MSE1;
	@Column(name = MSE2_LOC, nullable = true)
	@Metric(loc = MSE2_LOC, code = "mse2", desc = "MSE scale 2", unit = "", precision = 2)
	private int MSE2;
	@Column(name = MSE3_LOC, nullable = true)
	@Metric(loc = MSE3_LOC, code = "mse3", desc = "MSE scale 3", unit = "", precision = 2)
	private int MSE3;
	@Column(name = MSE4_LOC, nullable = true)
	@Metric(loc = MSE4_LOC, code = "mse4", desc = "MSE scale 4", unit = "", precision = 2)
	private int MSE4;

	@Column(name = MSE5_LOC, nullable = true)
	@Metric(loc = MSE5_LOC, code = "mse5", desc = "MSE scale 5", unit = "", precision = 2)
	private int MSE5;

	@Column(name = MSECOMPLEXITY_LOC, nullable = true)
	@Metric(loc = MSECOMPLEXITY_LOC, code = "mseC", desc = "Multiscale Entropy", unit = "", precision = 2)
	private int MSE;

}
