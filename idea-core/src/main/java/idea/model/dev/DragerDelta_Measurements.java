package idea.model.dev;

// Generated May 17, 2007 10:53:35 AM by Hibernate Tools 3.2.0.b9

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.OneToOne;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "DragerDelta_Measurement")
@Data
@EqualsAndHashCode(callSuper=false)
public class DragerDelta_Measurements extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.buildMetrics( DragerDelta_Measurements.class );
	}
	
	public DragerDelta_Measurements() {
		super(StreamID.MEASUREMENT);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	@Metric(loc ="nibp.sys", code="NIBP-SYS", unit = "mmHg")
	private Integer nibp$sys;
	
	@Metric(loc ="nibp.dia", code="NIBP-DIA", unit = "mmHg")
	private Integer nibp$dia;
	
	@Metric(loc ="nibp.mean", code="NIBP-MEAN", unit = "mmHg")
	private Integer nibp$mean;
	
	@Metric(loc ="spo2.hr", code="SpO2.HR", unit = "bpm")
	private Integer spo2$hr;

	@Metric(loc ="cvp.mean", code="CVP.MEAN", unit = "mmHg")
	private Integer cvp$mean;
	
	@Metric(loc ="pic.gedv", code="GEDV", unit = "ml")
	private Integer pic$gedv;
	
	@Metric(loc ="pic.gedvi", code="GEDVI", unit = "ml/m_SQUARED")
	private Integer pic$gedvi;
	
	@Metric(loc ="pic.evlw", code="EVLW", unit="ml")
	private Integer pic$evlw;
	
	@Metric(loc ="pic.evlwi", code="EVLWI", unit="ml/kg")
	private Integer pic$evlwi;
	
	@Metric(loc ="pic.pcci", code="PCCI", precision=2, unit="l/min/m_SQUARED")
	private Integer pic$pcci;
	
	@Metric(loc ="pic.psvri", code="p-SVRI", unit = "mmHg·min/l")
	private Integer pic$psvri;
	
	@Metric(loc ="pic.svv", code="SVV", unit = "%")
	private Integer pic$svv;
	
	@Metric(loc ="cnap.sys", code="CNAP-SYS", unit = "mmHg")
	private Integer cnap$sys;
	
	@Metric(loc ="cnap.dia", code="CNAP-DIA", unit = "mmHg")
	private Integer cnap$dia;
	
	@Metric(loc ="cnap.mean", code="CNAP-MEAN", unit = "mmHg")
	private Integer cnap$mean;
	
	@Metric(loc ="pa.pwp", code="PA.PWP", unit="mmHg")
	private Integer pa$pwp;
	
	@Metric(loc ="pa.mean", code="PA.MEAN", unit="mmHg")
	private Integer pa$mean;
	
	@Metric(loc ="pa.sys", code="PA.SYS", unit="mmHg")
	private Integer pa$sys;
	
	@Metric(loc ="pa.dia", code="PA.DIA", unit="mmHg")
	private Integer pa$dia;
	
	@Metric(loc ="art.pwp", code="ART.PWP", unit="mmHg")
	private Integer art$pwp;
	
	@Metric(loc ="art.mean", code="ART.MEAN", unit="mmHg")
	private Integer art$mean;
	
	@Metric(loc ="art.sys", code="ART.SYS", unit="mmHg")
	private Integer art$sys;
	
	@Metric(loc ="art.dia", code="ART.DIA", unit="mmHg")
	private Integer art$dia;
	
	@Metric(loc ="art.hr", code="ART.HR", unit = "bpm")
	private Integer art$hr;

	@Metric(loc ="ecg.pp", code="ECG.PP", desc="ECG P-P Interval", unit = "%")
	private Integer ecg$pp;
	
	@Metric(loc ="ecg.arr", code="ECG.ARR", desc="ECG Arrhythmia", unit = "bpm")
	private Integer ecg$arr;
	
	@Metric(loc ="ecg.pvc", code="ECG.PVC", desc="ECG Pre-ventricular contraction", unit = "bpm")
	private Integer ecg$pvc;
	
	@Metric(loc ="ecg.hr", code="ECG.HR", desc="ECG HR", unit = "bpm")
	private Integer ecg$hr;
	
	@Metric(loc ="ecg.deriv_v2", code="ECG.DV2", desc="ECG Derived V2", precision=1, unit = "mm")
	private Integer ecg$deriv_v2;
	
	@Metric(loc ="ecg.deriv_v5", code="ECG.DV5", desc="ECG Derived V5", precision=1, unit = "mm")
	private Integer ecg$deriv_v5;
	
	@Metric(loc ="spo2.satu", code="SPO2_SATU", desc="SpO2 Saturation", unit = "%")
	private Integer spo2$satu;
	
	@Metric(loc ="spo2.pr", code="SPO2_PR", desc="SpO2 PR", unit = "bpm")
	private Integer spo2$pr;

	@Metric(loc ="art.pr", code="ART.PR", desc="Arterial PR", unit = "mmHg")
	private Integer art$pr;
	
	@Metric(loc ="tbasic.a", code="Ta", desc="Tempurature A", unit = "C", precision=1)
	private Integer tbasic$a;
	
	@Metric(loc ="tbasic.b", code="Tb", desc="Tempurature B", unit = "C", precision=1)
	private Integer tbasic$b;
	
	@Metric(loc ="tbasic.delta", code="Tdelta", desc="Tempurature Delta", unit = "DELTA_C", precision=1)
	private Integer tbasic$delta;
	
	@Metric(loc ="temp1.a", code="TEMP1.A", desc="TEMP1 A", unit = "C", precision=1)
	private Integer t1$a;
	
	@Metric(loc ="temp1.b", code="TEMP1.B", desc="TEMP1 B", unit = "C", precision=1)
	private Integer t1$b;
	


	@Metric(loc ="lv.sys", code="LV.SYS", unit="mmHg")
	private Integer lv$sys;

	@Metric(loc ="lv.dia", code="LV.DIA", unit="mmHg")
	private Integer lv$dia;

	@Metric(loc ="lv.mean", code="LV.MEAN", unit="mmHg")
	private Integer lv$mean;

	@Metric(loc ="ra.mean", code="RA.MEAN", unit="mmHg")
	private Integer ra$mean;

	@Metric(loc="a2co2.etco2", code= "A2CO2.ETCO2",  unit="mmHg", precision=1)
	private Integer a2co2$etco2;
	
	@Metric(loc="a2co2.ico2", code= "A2CO2.ICO2", unit="mmHg", precision=1)
	private Integer a2co2$ico2;
	
	@Metric(loc="a2co2.rr", code= "A2CO2.RR", unit="", precision=1)
	private Integer a2co2$rr;
	

	@Metric(loc="icp.icp", code= "ICP.ICP",  unit="mmHg")
	private Integer icp$icp;
	
	@Metric(loc="icp.cpp", code= "ICP.CPP", unit="mmHg")
	private Integer icp$cpp;
	
	@Metric(loc="icp.mean", code= "ICP.MEAN", unit="mmHg")
	private Integer icp$mean;
	
	@Metric(loc="resp.rr", code= "RESP.RR", desc= "Respiratory Rate", unit="bpm")
	private Integer resp$rr;
	
	@Metric(loc="gp1.sys", code= "GP1.SYS", unit="mmHg")
	private Integer gp1$sys;
	
	@Metric(loc="gp1.dia", code= "GP1.DIA", unit="mmHg")
	private Integer gp1$dia;
	
	@Metric(loc="gp1.mean", code= "GP1.MEAN", unit="mmHg")
	private Integer gp1$mean;
	
	@Metric(loc="gp2.sys", code= "GP2.SYS", unit="mmHg")
	private Integer gp2$sys;
	
	@Metric(loc="gp2.dia", code= "GP2.DIA", unit="mmHg")
	private Integer gp2$dia;
	
	@Metric(loc="gp2.mean", code= "GP2.MEAN", unit="mmHg")
	private Integer gp2$mean;
	
	@Metric(loc="rv.sys", code= "RV.ICP", unit="mmHg")
	private Integer rv$sys;
	
	@Metric(loc="rv.dia", code= "RV.CPP", unit="mmHg")
	private Integer rv$dia;
	
	@Metric(loc="rv.mean", code= "RV.MEAN", unit="mmHg")
	private Integer rv$mean;
	
	@Metric(loc="la.mean", code= "LA.MEAN", unit="mmHg")
	private Integer la$mean;

	
	@OneToOne(cascade = CascadeType.ALL)
	@JoinColumn(name="bis_fk")
	private DragerDelta_MibBIS bis;
	
	@OneToOne(cascade = CascadeType.ALL)
	@JoinColumn(name="mgm_fk")
	private DragerDelta_MibMGM mgm;
	
	@OneToOne(cascade = CascadeType.ALL)
	@JoinColumn(name="svo2_fk")
	private DragerDelta_MibSVO2 svo2;
	
	@OneToOne(cascade = CascadeType.ALL)
	@JoinColumn(name="vent_fk")
	private DragerDelta_MibVent vent;
}
