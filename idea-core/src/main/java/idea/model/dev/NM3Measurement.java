package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "IFMOUT")
@Data
@EqualsAndHashCode(callSuper = false)
public class NM3Measurement extends PersistentItem {
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(NM3Measurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public NM3Measurement() {
		super(StreamID.MEASUREMENT);
	}


	@Metric( loc="1", /* sz="1", */ code="sfs", desc="short flow status")
	private Integer sfs;
	@Metric( loc="2", /* sz="4", */ code="efs", desc="extended flow status")
	private Integer efs;
	@Metric( loc="3", /* sz="2", */ code="Pb", desc="barometric pressure", unit="mmHg")
	private Integer Pb;
	@Metric( loc="4", /* sz="1", */ code="SPI", desc="start of inspiration mark")
	private Integer SPI;
	@Metric( loc="5", /* sz="1", */ code="SPE", desc="start of expiration mark")
	private Integer SPE;
	@Metric( loc="6", /* sz="1", */ code="SpO2err", desc="SpO2 Status")
	private Integer SpO2_Status;
	@Metric( loc="7", /* sz="4", */ code = "COerr", desc="Cardiac Output Status/Errors")
	private Integer CO_Status;
	@Metric( loc="8", /* sz="2", */ code="nBr", desc="Breath Counter")
	private Integer nBR;
	@Metric( loc="9", /* sz="2", */ code="COcyc", desc="Cardiac Output Complete Cycle Count")
	private Integer COCycle;
	@Metric( loc="10", /* sz="2", */ code="PR", desc="Pulse Rate", unit="bpm")
	private Integer PR;
	@Metric( loc="12", /* sz="2", */ code="COvp", desc="Cardiac Output Valve Pressure", unit="twentieths_cmH2O" )
	private Integer COvp;
	@Metric( loc="13", /* sz="2", */ desc="Breath Type: Spontaneous or Mechanical")
	private Integer BRtyp;
	@Metric( loc="15", /* sz="2", */ desc="Estimated Percent Rebreath", unit="%")
	private Integer estRebreath;
	@Metric( loc="16", /* sz="2", */ code="O2sat", desc="O2 Saturation", unit="%", precision=1)
	private Integer O2Sat;
	@Metric( loc="17", /* sz="1", */ code="Notify Cardiac Output Blood Gas Available")
	private Integer CO_BGNotify;
	@Metric( loc="18", /* sz="4", */ desc="Alarm Limit Status")
	private Integer ALARM_STAT;
	@Metric( loc="19", /* sz="2", */ code="FiO2", desc="Fraction Inspired Oxygen", unit="%")
	private Integer FiO2;
	@Metric( loc="20", /* sz="2", */ code="Freq s", desc="Respiratory Rate, Spontaneous breaths only (Freq s)", unit="br/min")
	private Integer fSpont;
	@Metric( loc="21", /* sz="2", */ code="Freq m", desc="Respiratory Rate, Mechanical breaths only (Freq m)", unit="br/min")
	private Integer fMech;
	@Metric( loc="22", /* sz="2", */ code="RR", desc="Respiratory Rate, Total (Freq t)", unit="br/min")
	private Integer RR;
	@Metric( loc="23", /* sz="2", */ code="PIF", desc="Peak Inspiratory Flow", unit="L/min", precision=1)
	private Integer PIF;
	@Metric( loc="24", /* sz="2", */ code="PEF", desc="Peak Expiratory Flow", unit="L/min", precision=1)
	private Integer PEF;
	// I:E should be a composite
	@Metric( loc="25", /* sz="2", */ code="I:E", desc="Inspiratory to Expiratory Volume Ratio")
	private Integer I2E;
	@Metric( loc="26", /* sz="2", */ code="TsubI", desc="Inspiratory Time", unit="s", precision=2)
	private Integer Ti;
	@Metric( loc="27", /* sz="2", */ code="TsubE", desc="Expiratory Time", unit="s", precision=2)
	private Integer Te;
	@Metric( loc="30", /* sz="2", */ code="Vsub(T)i", desc="Inspiratory Volume, breath-by-breath", unit="ml")
	private Integer Vti;
	@Metric( loc="31", /* sz="2", */ code="Vsub(T)e", desc="Expiratory Volume, breath-by-breath", unit="ml")
	private Integer Vte;
	@Metric( loc="32", /* sz="2", */ code="TVsub(IN)s", desc="Inspired Tidal Volume, Spontaneous breaths only", unit="ml")
	private Integer TVis;
	@Metric( loc="33", /* sz="2", */ code="TVsub(IN)m", desc="Inspired Tidal Volume, Mechanical breaths only", unit="ml")
	private Integer TVim;
	@Metric( loc="34", /* sz="2", */ code="TVinT", desc="Inspired Tidal Volume, Total", unit="ml")
	private Integer TVit;
	@Metric( loc="35", /* sz="2", */ code="TVsub(EX)s", desc="Expired Tidal Volume, Spontaneous breaths only", unit="ml")
	private Integer TVxs;
	@Metric( loc="36", /* sz="2", */ code="TVsub(EX)m", desc="Expired Tidal Volume, Mechanical breaths only", unit="ml")
	private Integer TVxm;
	@Metric( loc="37", /* sz="2", */ code="TVexT", desc="Expired Tidal Volume, Total", unit="ml")
	private Integer TVxt;
	// minute volumes
	@Metric( loc="38", /* sz="2", */ code="MVsub(IN)s", desc="Inspired Minute Volume, Spontaneous breaths only", unit="ml")
	private Integer MVs;
	@Metric( loc="39", /* sz="2", */ code="MVsub(IN)m", desc="Inspired Minute Volume, Mechanical breaths only", unit="ml")
	private Integer MVm;
	@Metric( loc="40", /* sz="2", */ code="MVsub(IN)t", desc="Inspired Minute Volume, Total", unit="ml")
	private Integer MVt;
	@Metric( loc="41", /* sz="2", */ code="MVsub(EX)s", desc="Expired Minute Volume, Spontaneous breaths only", unit="ml")
	private Integer MVxs;
	@Metric( loc="42", /* sz="2", */ code="MVsub(EX)m", desc="Expired Minute Volume, Mechanical breaths only", unit="ml")
	private Integer MVxm;
	@Metric( loc="43", /* sz="2", */ code="MVexpT", desc="Expired Minute Volume, Total", unit="ml")
	private Integer Mvxt;
	@Metric( loc="44", /* sz="1", */ desc="Notify breath type")
	private Integer BRtype;
	//
	@Metric( loc="50", /* sz="2", */ code="PIP", desc="Peak Inspiratory Pressure", unit="cmH2O", precision=1)
	private Integer PIP;
	@Metric( loc="51", /* sz="2", */ code="Psub(plat)", desc="Plateau Pressure", unit="cmH2O", precision=1)
	private Integer Pplat;
	@Metric( loc="52", /* sz="2", */ code="PAWsub(MEAN)", desc="Mean Airway Pressure", unit="cmH2O", precision=1)
	private Integer PMEAN;
	@Metric( loc="53", /* sz="2", */ code="PEEP", desc="Positive End-Expiratory Pressure", unit="cmH2O", precision=1)
	private Integer PEEP;
	@Metric( loc="54", /* sz="2", */ code="NIP", desc="Negative Inspired Pressure", unit="cmH2O", precision=1)
	private Integer NIP; 
	@Metric( loc="55", /* sz="2", */ code="P100", desc="Pressure 100ms", unit="cmH2O", precision=1/* , offset=-819.2 */)
	private Integer P100;
	//
	@Metric( loc="60", /* sz="2", */ code="RAWsub(I)dyn", desc="Inspiratory Airway Resistance, Dynamic measurement", unit="cmH2O", precision=1)
	private Integer RAWidyn;
	@Metric( loc="61", /* sz="2", */ code="RAWsub(E)dyn", desc="Expiratory Airway Resistance, Dynamic measurement", unit="cmH2O", precision=1)
	private Integer RAWxdyn;
	@Metric( loc="62", /* sz="2", */ code="Csub(TOT)", desc="Total Lung Compliance, Dynamic measurement", unit="cmH2O", precision=1)
	private Integer Ctot;
	@Metric( loc="63", /* sz="2", */ code="CStat", desc="Static Compliance", unit="cmH2O", precision=1)
	private Integer CStat;
	//
	@Metric( loc="70", /* sz="3", */ code="ETCO2", desc="End-Tidal CO2", unit="mmHg")
	private Integer ETCO2;
	@Metric( loc="71", /* sz="2", */ code="ETCO2/br", desc="End-Tidal CO2 per breath", unit="mmHg", precision=1)
	private Integer etCO2_br;
	@Metric( loc="75", /* sz="3", */ code="InspCO2", desc="Inspired CO2", unit="mmHg")
	private Integer iCO2;
	@Metric( loc="76", /* sz="3", */ code="PeCO2", desc="Mixed-Expired CO2", unit="mmHg")
	private Integer PeCO2; 
	//
	@Metric( loc="80", /* sz="2", */ code="VCO2b", desc="Volume CO2 Expired, per breath", unit="ml", precision=1)
	private Integer VCO2b;
	@Metric( loc="81", /* sz="2", */ code="VCO2", desc="Volume CO2 Expired, per minute average", unit="mL/min")
	private Integer VCO2;
	//
	@Metric( loc="83", /* sz="2", */ code="BTPS", desc="Volume CO2 per breath", unit="mL/min", precision=2/* , offset=-81.92 */)
	private Integer BTPS; 
	@Metric( loc="84", /* sz="2", */ code="BTPS", desc="Volume CO2 Inspired per breath", unit="mL/min", precision=2/* , offset=-81.92 */)
	private Integer BPTS84;
	@Metric( loc="85", /* sz="2", */ code="BTPS", desc="Volume CO2 per breath per minute", unit="mL/min", precision=1/* , offset=-819.2 */)
	private Integer BTPS85;
	//
	@Metric( loc="90", /* sz="2", */ code="VTsub(ALV)s", desc="Alveolar Tidal Volume, Spontaneous per breath", unit="ml")
	private Integer VTalvs;
	@Metric( loc="91", /* sz="2", */ code="VTsub(ALV)m", desc="Alveolar Tidal Volume, Mechanical per breath", unit="ml")
	private Integer VTalvm;
	@Metric( loc="92", /* sz="2", */ code="VTsub(ALV)", desc="Alveolar Tidal Volume, total", unit="ml")
	private Integer VTalv;
	@Metric( loc="93", /* sz="2", */ code="MVsub(ALV)s", desc="Alveolar Minute Volume, Spontaneous per breath", unit="L", precision=2)
	private Integer MValvs;
	@Metric( loc="94", /* sz="2", */ code="MVsub(ALV)m", desc="Alveolar Minute Volume, Mechanical per breath", unit="L", precision=2)
	private Integer MValvm;
	@Metric( loc="95", /* sz="2", */ code="MValvT", desc="Alveolar Minute Volume, total", unit="L", precision=2)
	private Integer MValvT;
	@Metric( loc="96", /* sz="2", */ code="Vsub(DE)aw", desc="Alveolar Deadspace Expired", unit="ml")
	private Integer Vdeaw;
	@Metric( loc="98", /* sz="2", */ code="Vsub(D)/Vsub(T)phys", desc="Vd/Vt Physiologic")
	private Integer VdVtphys;
	@Metric( loc="99", /* sz="2", */ code="Vsub(D)aw", desc="Alveolar Deadspace Total", unit="ml")
	private Integer Vdaw;
}
