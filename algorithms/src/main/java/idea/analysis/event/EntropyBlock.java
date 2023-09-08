package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Transient;

import lombok.Data;

@Entity
@Data
public class EntropyBlock  extends PersistentItem {

	@Transient
	protected static RpMetric[] metrics;


	static {
		metrics = IntfUtil.getMetrics(EntropyBlock.class);
	}	

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}
	
	private int [] A;
	private int [] B;
	
	public final static String TOLERANCE_LOC = "R";
	public final static String SAMPENT_LOC = "SAMPEN";
	public final static String STDDEV_LOC = "11";
	public final static String APPXENT_LOC = "12";
	public final static String MEAN_LOC = "13";
	public final static String Q_LOC = "QSE";
	
	
	public EntropyBlock() {
		super(StreamID.MEASUREMENT);
	}
	
	@Column(name = SAMPENT_LOC, nullable = true)
	@Metric(loc = SAMPENT_LOC, code = "sampEn", desc = "Sample Entropy",  precision=2 )
	private int sampEnt;
	
	@Column(name = Q_LOC, nullable = true)
	@Metric(loc = Q_LOC, code = "qse", desc = "QSE",  precision=2 )
	private int qse;

	@Metric( loc=APPXENT_LOC, code="appxEn", desc="Approximate Entropy", precision=2 )
	private int appxent;
	
	@Metric(  loc=STDDEV_LOC, code="stddev", desc="Standard Deviation", precision=2)
	private int stddev;
	
	@Metric(  loc=MEAN_LOC, code="mean", desc="Mean", precision=2)
	private int mean;
	
	@Metric(  loc=TOLERANCE_LOC, code="q", desc="Quadratic Entropy", precision=2)
	private int tolerance;
	

}
