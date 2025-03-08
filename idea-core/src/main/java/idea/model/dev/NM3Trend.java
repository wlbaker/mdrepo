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
@Table(name = "NMT_TREND")
@Data
@EqualsAndHashCode(callSuper = false)
public class NM3Trend extends PersistentItem {
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(NM3Trend.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public NM3Trend() {
		super(StreamID.MEASUREMENT_2);
	}

	@Metric( loc="4", code="RSBI", desc="Rapid Shallow Breathing Index")
	private int RSBI;
	@Metric( loc="10", code="HR", desc="HR", unit="bpm")
	private int HR;
	@Metric( loc="20", code="FREQ_S", desc="Respiratory Rate, Spontaneous only", unit="br/min")
	private int fS;
	@Metric( loc="21", code="FREQ_M", desc="Respiratory Rate, Mechanical Breaths only", unit="br/min")
	private int fM;
	@Metric( loc="22", code="RR", desc="Respiratory Rate, Total", unit="br/min")
	private int RR;
	@Metric( loc="23", code="PIF", desc="Peak Inspiratory Flow", unit="LPM", precision=1)
	private int PIF;
	@Metric( loc="24", code="PEF", desc="Peak Expiratory Flow", unit="LPM", precision=1)
	private int PEF;
	@Metric( loc="32", code="TVins", desc="Inspired Tidal Volumn (Spontaneous only)")
	private int TVis;
	@Metric( loc="33", code="TVinM", desc="Inspired Tidal Volume (Mechanical only)")
	private int TVim;
	@Metric( loc="35", code="TVexS", desc="Expired Tidal Volume, Spontaneous only", unit="ml")
	private int TVxs;
	@Metric( loc="36", code="TVexM", desc="Expired Tidal Volume, Mechanical only", unit="ml")
	private int TVxm;
	@Metric( loc="37", code="TVexT", desc="Expired Tidal Volume, Total", unit="ml")
	private int TVt;
	@Metric( loc="41", code="MVexS", desc="Expired Minute Volume, Spontaneous only", unit="L", precision=2)
	private int MVxs;
	@Metric( loc="42", code="MVexM", desc="Expired Minute Volume, Mechanical only", unit="L", precision=2)
	private int MVxm;
	@Metric( loc="43", code="MvexpT", desc="Expired Minute Volume, Total")
	private int MVxt;
	@Metric( loc="50", code="PIP", desc="Peak Inspiratory Pressure", unit="cmH2O", precision=1)
	private int PIP;
	@Metric( loc="52", code="PAW_MEAN", desc="Mean Airway Pressure", unit="cmH2O", precision=1)
	private int PMEAN;
	@Metric( loc="53", code="PEEP", desc="Positive End Expiratory Pressure", unit="cmH2O", precision=1)
	private int PEEP;
	@Metric( loc="60", code="RAWiDYN", desc="Inspiratory Airway Resistance, Dynamic")
	private int RAWidyn;
	@Metric( loc="61", code="RAWxDYN", desc="Expiratory Airway Resistance, Dynamic")
	private int RAWxdyn;
	@Metric( loc="62", code="C_DYN", desc="Lung Compliance, dynamic measurement")
	private int Cdyn;

	@Metric( loc="70", code="EtCO2", desc="End-Tidal CO2", unit="mmHg?")
	private int EtCO2;
	@Metric( loc="75", code="InspCO2", desc="Inspired CO2", unit="mmHg")
	private int iCO2;
	@Metric( loc="76", code="PeCO2", desc="Mixed-Expired CO2")
	private int PeCO2;
	@Metric( loc="81", code="VCO2", desc="Volume CO2 Expired (averaged - current setting)", unit="mL/min")
	private int VCO2;
	@Metric( loc="90", code="VTalvS", desc="Alveolar Tidal Volume, Spontaneous")
	private int VTalvs;
	@Metric( loc="91", code="VTalvM", desc="Alveolar Tidal Volume, Mechanical")
	private int VTalvm;
	@Metric( loc="92", code="VTalvT", desc="Alveolar Tidal Volume, Total")
	private int VTalvt;

	@Metric( loc="93", code="MValvS", desc="Alveolar Minute Volume, Spontaneous")
	private int MValvs;
	@Metric( loc="94", code="MValvM", desc="Alveolar Minute Volume, Mechanical")
	private int MValvm;
	@Metric( loc="95", code="MValvT", desc="Alveolar Minute Volume, Total")
	private int MValvt;
	@Metric( loc="96", code="VdExp", desc="Airway Deadspace (Expired)")
	private int Vdx;
	@Metric( loc="97", code="VdVt", desc="Vd/Vt Airway")
	private int VdVt_aw;
	@Metric( loc="98", code="VtVd", desc="Vt/Vd Physiologic")
	private int VdVt_phy;
	@Metric( loc="99", code="VdAW", desc="Airway Deadspace (Total)")
	private int Vd_aw;

}
