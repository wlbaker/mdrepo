package idea.model.dev;


import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@Data
public class AesculonMeasurement extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;
	
	static {
		metrics = IntfUtil.getMetrics(AesculonMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public AesculonMeasurement() {
		super(StreamID.MEASUREMENT);
	}
	/*
	 * 
	 */

			@Metric(loc="1010", code="SQI", desc="Signal Quality Indicator")
			private int sqi;
			
			@Metric(loc="2000", code="HR", desc="Heart Rate")
			private int hr;
			@Metric(loc="2010", code="SV", desc="Stroke Volume", unit="?", precision=1)
			private int sv;

			@Metric(loc="2011", code="SI BSA", desc="Stroke Index (by BSA)")
			private int si$bsa;
			@Metric(loc="2012", code="SI WT", desc="Stroke Index (by Weight)")
			private int si$wt;
			@Metric(loc="2020", code="CO l/min", desc="Cardiac Output", unit="l/min", precision=2)
			private int co;
			
			@Metric(loc="2021", code="CI BSA", desc="Cardiac Index (by BSA)", unit="?", precision=2)
			private int ci$bsa;
			@Metric(loc="2022", code="CI WT", desc="Cardiac Index (by Weight)", unit="?", precision=2)
			private int ci$wt;
			@Metric(loc="2030", code="ICON", desc="Index of Contractility (ICON)", unit="?", precision=1)
			private int icon;
			
			@Metric(loc="2040", code="TFC", desc="Thoracic Fluid Content")
			private int tfc;
			
			@Metric(loc="2050", code="FTC", desc="Corrected Flow Time")
			private int cft;
			
			@Metric(loc="2060", code="STR", desc="Systolic Time Ratio", unit="?", precision=2)
			private int str;
			
			@Metric(loc="2070", code="LVET", desc="Left-Ventricular Ejection Time", unit="ms")
			private int lvet;
			
			@Metric(loc="2080", code="PEP", desc="Pre-Ejection Period", unit="ms")
			private int pep;
			
			@Metric(loc="2090", code="SVV", desc="Stroke Volume Variation", unit="%")
			private int svv;
			
			@Metric(loc="20A0", code="VIC", desc="Variation of ICON (VIC)", unit="%")
			private int vic;
			@Metric(loc="3000", code="SBP", desc="Systolic Blood Pressure", unit="mmHg")
			private int sbp;
			@Metric(loc="3001", code="DBP", desc="Diastolic Blood Pressure", unit="mmHg")
			private int dbp;
			@Metric(loc="3002", code="MAP", desc="Mean Blood Pressure", unit="mmHg")
			private int map;
			@Metric(loc="3010", code="SVR", desc="Systemic Vascular Resistance", unit ="dyn-s/cm5")
			private int svr;
			@Metric(loc="3011", code="SVRI BSA", desc="Systemic Vascular Resistance Index (by BSA)")
			private int svri$bsa;
			@Metric(loc="3012", code="SVRI WT", desc="Systemic Vascular Resistance Index (by Weight)")
			private int svri$wt;
			
			@Metric(loc="3020", code="LCW", desc="Left Cardiac Work", unit="kg-m", precision=2)
			private int lcw;
			@Metric(loc="3021", code="LCWI BSA", desc="Left Cardiac Work Index (by BSA)", precision=2)
			private int lcwi$bsa;
			@Metric(loc="3022", code="LCWI WT", desc="Left Cardiac Work Index (by Weight)", precision=2)
			private int lcwi$wt;
			@Metric(loc="3030", code="SSVR", desc="Stroke Systemic Vascular Resistance")
			private int ssvr;
			@Metric(loc="3031", code="SSVRI BSA", desc="Stroke Systemic Vascular Resistance Index (by BSA)"
					)
			private int ssvri$bsa;

			@Metric(loc="3032", code="SSVRI WT", desc="Stroke Systemic Vascular Resistance Index (by Weight)"
					)
			private int ssvri$wt;
			@Metric(loc="3040", code="LCSW", desc="Left Cardiac Stroke Work")
			private int lcsw;
			@Metric(loc="3041", code="LCSWI BSA", desc="Left Cardiac Stroke Work Index (by BSA)")
			private int lcswi$bsa;
			@Metric(loc="3042", code="LCSWI WT", desc="Left Cardiac Stroke Work Index (by Weight)")
			private int lcswi$wt;
			@Metric(loc="3051", code="CPI BSA", desc="Cardiac Power Index (by BSA)")
			private int cpi$bsa;
			@Metric(loc="3052", code="CPI WT", desc="Cardiac Power Index (by Weight)")
			private int cpi$wt;
			@Metric(loc="4000", code="SpO2", desc="Oxygen Saturation", unit="%")
			private int spo2;
			@Metric(loc="4010", code="PR", desc="Pulse Rate", unit="bpm")
			private int pr;
			@Metric(loc="4020", code="SpHb", desc="Hemoglobin Concentration", unit="g/dL")
			private int sphb;
			@Metric(loc="4030", code="SpMet", desc="Methemoglobin Concentration", unit="%")
			private int spmet;
			@Metric(loc="4040", code="SpCO", desc="Carbon Monoxide Concentration", unit="%")
			private int spco;
			@Metric(loc="4050", code="PI", desc="Perfusion Index", unit="%")
			private int pi;
			@Metric(loc="4051", code="PI Change", desc="PI Percent Change", unit="%")
			private int pi_change;
			@Metric(loc="4060", code="PVI", desc="Pleth Variability Index", unit="%")
			private int pvi;
			@Metric(loc="4070", code="Desat Idx", desc="Desaturation Index")
			private int desatIdx;
			@Metric(loc="4080", code="CaO2", desc="Arterial Oxygen Content", unit="ml/dL")
			private int cao2;
			@Metric(loc="4090", code="DO2 ", desc="Oxygen Delivery", unit="ml / min")
			private int do2;
			@Metric(loc="4091", code="DO2I BSA", desc="Oxygen Delivery Index (by BSA)")
			private int do2i$bsa;
			@Metric(loc="4092", code="DO2I WT", desc="Oxygen Delivery Index (by Weight)")
			private int do2i$wt;
			@Metric(loc="5000", code="HRV", desc="Heart Rate Variability", unit="ms")
			private int hrv;
			@Metric(loc="5010", code="HRC", desc="Heart Rate Complexity", precision=2)
			private int hrc;
			@Metric(loc="5020", code="MSE", desc="Multiscale Entropy", precision=2)
			private int mse;
			@Metric(loc="5030", code="PNN", desc="pNNx", precision=2)
			private int pnn;
			@Metric(loc="5040", code="STAT", desc="StatAv", precision=2)
			private int stat;
}

