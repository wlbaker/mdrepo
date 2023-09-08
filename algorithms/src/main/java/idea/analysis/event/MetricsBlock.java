package idea.analysis.event;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class MetricsBlock extends PersistentItem {


	@Transient
	private static RpMetric[] metrics;

	// Location values
	public final static String DATE_LOC	= "0x000";

	public final static String SAMPEN_LOC 	= "0x001";
	public final static String QSE_LOC 	= "0x002";
	public final static String MSE_LOC 	= "0x003";

	public final static String SD1_LOC 	= "0x004";
	public final static String SD2_LOC 	= "0x005";
	public final static String SDRATIO_LOC = "0x006";

	public final static String STATAV_LOC 	= "0x007";

	public final static String ALPHA_LOC 	= "0x008";
	public final static String ALPHA1_LOC 	= "0x008";
	public final static String ALPHA2_LOC 	= "0x010";

	public final static String SOD_LOC 	= "0x011"; 

	public final static String SDRR_LOC 	= "0x012";
	public final static String SDSD_LOC 	= "0x013";

	public final static String HR_LOC 		= "0x014";

	static {
		metrics = IntfUtil.getMetrics(MetricsBlock.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public MetricsBlock() {
		super(StreamID.MEASUREMENT);
	}

	// Individual time values
	@Metric( loc= SAMPEN_LOC, code="sampEn",  desc="Sample Entropy")
	private double sampEn;
	@Metric( loc= QSE_LOC, code="qse", desc="Quadratic Sample Entropy")
	private double qse;
	@Metric( loc= MSE_LOC, code="mse",  desc="Multi-Scale Entropy")
	private double mse;

	// Individual Poincare plot values
	@Metric( loc= SD1_LOC, code="sd2",  desc="Short-Term Variability")
	private double sd1;
	@Metric( loc= SD2_LOC, code="sd1",  desc="Long-Term Variability")
	private double sd2;
	@Metric( loc= SDRATIO_LOC, code="sdRatio",  desc="Variability Ratio")
	private double sdRatio;

	@Metric( loc= STATAV_LOC, code="statAV",  desc="Degree of Nonstationarity")
	private double statAv;


	// Individual detrended fluctuation analysis values
	@Metric( loc= ALPHA_LOC, code="alpha",  desc="Alpha")
	private double alpha;
	@Metric( loc= ALPHA1_LOC, code="alpha1",  desc="Alpha1")
	private double alpha1;
	@Metric( loc= ALPHA2_LOC, code="alpha2",  desc="Alpha2")
	private double alpha2;


	// Individual distribution values
	@Metric( loc= SOD_LOC, code="sod",  desc="Similarity of Distributions")
	private double sod;


	// Individual standard deviation (Poincare plot) values
	@Metric( loc= SDRR_LOC, code="sdrr",  desc="Standard Deviation of RRIs")
	private double sdrr;
	@Metric( loc= SDSD_LOC, code="sdsd",  desc="Standard Deviation of RRI Diffs")
	private double sdsd;

	// Individual heart rate values
	@Metric( loc= HR_LOC, code="hr",  desc="Estimated Heart Rate", unit="bpm")
	protected double hr;


}
