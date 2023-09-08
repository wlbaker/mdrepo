package idea.analysis.event;


import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class SBCO2Block extends PersistentItem {

	public final static String VOLAIR_LOC = "10";
	public final static String VOLCO2_LOC = "11";
	public final static String FICO2_LOC = "12";
	public static final String IBI_LOC = "15";
	public static final String EXH_LOC = "16";
	public static final String PH2SLOPE_LOC = "20";
	public static final String PH3SLOPE_LOC = "21";
	public static final String PH2INTERCEPT_LOC = "30";
	public static final String PH3INTERCEPT_LOC = "31";
	public static final String DEADSPACE_LOC = "32";
	public static final String ETCO2_LOC = "33";
	public static final String COMPLIANCE_LOC = "34";
	public static final String RESISTANCE_LOC = "35";
	public static final String TV_LOC = "36";
	
	@Transient
	protected static RpMetric[] metrics;


	static {
		metrics = IntfUtil.getMetrics(SBCO2Block.class);
	}	

	
	
	@Waveform( loc=FICO2_LOC, code="FiCO2", desc="Percent CO2", unit="%", freq = 0, spp = 0 )
	private double[] flowData;
	private double[] histData;
	
	@Waveform( loc=VOLCO2_LOC, code="VolCO2", desc="Volume CO2",  unit="ml", freq = 0, spp = 0)
	private double[] vco2Data;
	
	@Waveform( loc=VOLAIR_LOC, code="VOL", desc="Volume Air",  unit="ml", freq = 0, spp = 0)
	private double[] volData;
	
	@Metric( loc=IBI_LOC, code="ibi", desc="IBI", unit="hundredths_sec")
	private int ibi;
	
	@Metric( loc=PH2SLOPE_LOC, code="mph2", desc="M-PH2")
	private double mph2;
	@Metric( loc=PH3SLOPE_LOC, code="mph3", desc="M-PH3" )
	private double mph3;
	
	@Metric( loc=PH2INTERCEPT_LOC, code="ph2int", desc="INT-PH2")
	private double ph2int;
	@Metric( loc=PH3INTERCEPT_LOC, code="ph3int", desc="INT-PH3")
	private double ph3int;
	@Metric( loc=EXH_LOC, code="exh", desc="EXH", unit="hundredths_sec")
	private int exh;
	@Metric( loc=DEADSPACE_LOC, code="ds", desc="DS")
	private int ds;
	@Metric( loc=ETCO2_LOC,code= "etco2", desc="EtCO2", unit="tenths")
	private double ETCO2;
	@Metric( loc=COMPLIANCE_LOC, code="C", desc="Compliance")
	private double compliance;
	@Metric( loc=RESISTANCE_LOC, code="R", desc="Resistance")
	private double resistance;
	@Metric( loc=TV_LOC, code="TV", desc="Tidal Volume", unit="ml")
	private double TV;
	private double relativeTime;
	private double vco2;
	private double vae;

	public SBCO2Block() {
		
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}


}
