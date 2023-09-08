package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;
import lombok.Data;

@SuppressWarnings("serial")
@Data
public class PICCOV3_Vitals extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String PCCI_LOC = "14.4";
	public static final String SVV_LOC = "8.5";
	public static final String SVRI_LOC = "18.4";
	public static final String CFI_LOC = "4.7a";
	public static final String GEF_LOC = "4.7b";
	public static final String GEDV_LOC = "1.7";
	public static final String GEDI_LOC = "11.7";
	public static final String ELWI_LOC = "13.7";
	public static final String EVLW_LOC = "3.7";
	public static final String SCVO2_LOC = "17.4";
	public static final String PDR_LOC = "19.4";
	public static final String CI_LOC = "10.7";
	public static final String CO_LOC = "0.7";

	private static final String SYS_LOC = "0.5";
	private static final String DIA_LOC = "0.6";
	private static final String MAP_LOC = "0.4";
	private static final String HR_LOC = "3.4";

	static {
		metrics = IntfUtil.getMetrics(PICCOV3_Vitals.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public PICCOV3_Vitals() {
		super(StreamID.MEASUREMENT);
	}

	/*
	 * 
	 */

	@Metric(loc = PCCI_LOC, code = "PCCI", desc="Pulse contour cardiac index", unit = "l/min/m2",precision=2)
	private Integer PCCI;
	@Metric(loc = SVV_LOC, code = "SVV", desc="Stroke volume variation", unit = "%")
	private Integer SVV;
	@Metric(loc = SVRI_LOC, code = "SVRI", desc="Systemic vascular resistance index", unit = "dyn*s*cm-5*m2")
	private Integer SVRI;
	@Metric(loc = GEF_LOC, code = "GEF", desc="Global ejection fraction", unit = "%")
	private Integer GEF;
	@Metric(loc = CFI_LOC, code = "CFI", desc="Cardiac function index", unit = "l/min", precision=1)
	private Integer CFI;
	@Metric(loc = GEDI_LOC, code = "GEDI", desc="Global end-diastolic volume index", unit = "ml/m2")
	private Integer GEDI;
	@Metric(loc = GEDV_LOC, code = "GEDV", desc="Global end-diastolic volume", unit = "ml")
	private Integer GEDV;
	@Metric(loc = ELWI_LOC, code = "ELWI", unit = "ml/kg")
	private Integer ELWI;
	@Metric(loc = SCVO2_LOC, code = "SCVO2", unit = "%",precision=2)
	private Integer SCVO2;
	@Metric(loc = PDR_LOC, code = "PDR", desc="Plasma disappearance rate", unit = "%/min", precision=1)
	private Integer PDR;
	@Metric(loc = CI_LOC, code = "CI", unit = "l/min/m2",precision=2)
	private Integer CI;
	@Metric(loc = CO_LOC, code = "CO", unit = "m/min",precision=2)
	private Integer CO;
	@Metric(loc = EVLW_LOC, code = "EVLW", unit = "ml")
	private Integer EVLW;

	@Metric(loc = SYS_LOC, code = "SYS", unit = "mmHg", precision=1)
	private Integer SYS;
	@Metric(loc = DIA_LOC, code = "DIA", unit = "mmHg", precision=1)
	private Integer DIA;
	@Metric(loc = MAP_LOC, code = "MAP", unit = "mmHg", precision=1)
	private Integer MAP;
	@Metric(loc = HR_LOC, code = "HR", unit = "bpm")
	private Integer HR;
}
