package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "IFMOUT")
@Data
@EqualsAndHashCode(callSuper = false)
public class IFMoutMeasurement extends PersistentItem {
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(IFMoutMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public IFMoutMeasurement() {
		super(StreamID.MEASUREMENT);
	}

	@Metric(loc = "Annn", code = "SaO2", desc = "Arterial Oxygen Saturation", unit = "%")
	private int SaO2;

	@Metric(loc = "a+nn.n", code = "SNR", desc = "Signal to Noise Ration (CCO mode)", unit = "dB", precision = 1)
	private int SNR;
	@Metric( loc="Bnn.n", code="BT", desc="Blood Temperature (non Bolus mode)", unit="C", precision=1) //
	private int BT;
	@Metric( loc="bnn.n", code="SVV", desc="Stroke Volume Variation", unit="%", precision=1) //
	private int SVV;
	@Metric( loc="Cnn.n", code="CO", desc="Continuous Cardiac Output", unit="L/min", precision=1) //
	private int CO;
	@Metric( loc="cnn.n", code="COi", desc="Continuous Cardiac Output Index", unit="L/min/m**2", precision=1) //
	private int COi;
	@Metric( loc="Dnnnn", code="DO2", desc="Oxygen Deliver (CCO mode)", unit="ml/min") //
	private int DO2;
	@Metric( loc="Ennn", code="RVEF", desc="Right Ventricular Ejection Fraction (CCO/EDV)", unit="%") //
	private int RVEF;
	@Metric( loc="ennn", code="RVEF_st", desc="Right Ventricular Ejection Fraction STAT (CCO/EDV)", unit="%") //
	private int RVEF_st;
	@Metric( loc="Fnn",code= "CO_Fault", desc="CO Fault code") //
	private int CO_Fault;
	@Metric( loc="fnn", code="O_Fault", desc="Oximetry Fault code") //
	private int O_Fault;
	@Metric( loc="Hnnn", code="HRavg", desc="Average Heart Rate", unit="bpm") //
	private int HRavg;
	@Metric( loc="Imnn.n", code="ICO", desc="Bolus Cardiac Output - (1-6)", unit="L/min", precision=1) //
	private int ICO;
	@Metric( loc="imnn.n", code="ICPi", desc="Bolus Cardiac Output Index - (1-6)", unit="L/min", precision=1) //
	private int ICPi;
	@Metric( loc="Jnnn", code="EDV", desc="End Diastolic Volume (CCO/EDV)", unit="ml") //
	private int EDV;
	@Metric( loc="jnnn", code="EDVi", desc="End Diastolic Volume Index (CCO/EDV)", unit="ml/m**2") //
	private int EDVi;

	@Metric( loc="Knnn", code="ESV", desc="End Systolic Volume (CCO/EDV)", unit="ml") //
	private int ESV;
	@Metric( loc="knnn", code="ESVi", desc="End Systolic Volume Index (CCO/EDV)", unit="ml/m**2") //
	private int ESVi;
	@Metric( loc="Lnn", code="CO_Alert", desc="CO Alert code") //
	private int COAlert;
	@Metric( loc="lnn", code="Oximetry_Alert", desc="Oximetry Alert code") //
	private int OximetryAlert;
	@Metric( loc="Mnnm", code="CO_Alarm", desc="CO Alert and Alarm code") //
	private int COAlarm;

	@Metric( loc="mnnm", code="Oximetry Alarm", desc="Oximetry Alarm code") //
	private int OximetryAlarm;
	@Metric( loc="Nnnnn-nnnn-nn", code="ID", desc="IFMout ID") //
	private String ID;
	@Metric( loc="Onnnn", code="VO2", desc="Oxygen Consumption (CCO)", unit="ml/min") //
	private int VO2;
	@Metric( loc="Pnnn", code="MAP", desc="Mean Arterial Pressure", unit="mmHg") //
	private int MAP;
	@Metric( loc="pnnn", code="CVP", desc="Central Veneous Pressure", unit="mmHg") //
	private int CVP;
	@Metric( loc="Qn", code="SQI", desc="Oximetry Signal Quality Indicator", unit="ml/min") //
	private int SQI;
	
	@Metric( loc="Rnnnn", code="SVR", desc="Systemic Vascular Resistance (CCO)", unit="dn-s/cm**5") //
	private int SVR;
	@Metric( loc="rnnnn", code="SVRi", desc="Systemic Vascular Resistance Index (CCO)", unit="dn-s-m**2/cm**5") //
	private int SVRi;
	@Metric( loc="Snnn", code="SV", desc="Stroke Volume (CCO)", unit="ml/beat") //
	private int SV;
	@Metric( loc="snnn", code="SVi", desc="Stroke Volume Index (CCO)", unit="ml/beat/m**2", precision=1) //
	private int SVi;
	@Metric( loc="Tnn.n", code="CO_st", desc="Cardiac Output STAT (CCO)", unit="L/min", precision=1) //
	private int CO_st;
	
	@Metric( loc="tnn.n", code="COi_st", desc="Cardiac Output Index STAT (CCO)", unit="L/min/m**2", precision=1) //
	private int COi_st;
	@Metric( loc="Unnn", code="EDV_st", desc="End Diastolic Volume STAT (CCO/EDV)", unit="ml") //
	private int EDV_st;
	@Metric( loc="unnn", code="EDVi_st", desc="End Diastolic Volume Index STAT (CCO/EDV)", unit="ml/m**2", precision=1) //
	private int EDVi_st;
	@Metric( loc="Vnnn", code="SvO2", desc="Mixed Venous Oxygen Saturation", unit="%") //
	private int SvO2;
	@Metric( loc="vnnn", code="ScvO2", desc="Continuous Venous Oxygen Saturation", unit="%") //
	private int ScvO2;
	@Metric( loc="Wnnn", code="SV_st", desc="Stroke Volume STAT (CCO)", unit="ml/beat") //
	private int SV_st;
	@Metric( loc="wnnn", code="SVi_st", desc="Stroke Volume Index STAT (CCO)", unit="ml/beat/m**2", precision=1) //
	private int SVi_st;
	@Metric( loc="Xnn.n", code="O2Ei", desc="Oxygen Extraction Index", unit="%", precision=1) //
	private int O2Ei;
	@Metric( loc="Ynnnnn", code="Y", desc="EV1000-y") //
	private String Y;

}
