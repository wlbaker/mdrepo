package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.persistence.Text;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@Table(name = "SentecEth")
@Data
public class SentecEthMeasurement extends PersistentItem {
	@Transient
	private static RpMetric[] metrics;
	
	public static final String PACO2_LOC = "PACO2";
	public static final String SPO2_LOC = "SPO2";
	public static final String HR_LOC = "HR";
	public static final String PI_LOC = "PI"; // wrong!
	public static final String RHP_LOC = "RHP"; // wrong!

	static {
		metrics = IntfUtil.getMetrics(SentecEthMeasurement.class);
	}

	public SentecEthMeasurement() {
		super( StreamID.MEASUREMENT );
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}
	
	// @Text( loc="Pco2PartAttr", 8), // u
	// @Text( loc="PoxSpO2Attr", 8), //
	// @Text( loc="PoxPRAttr", 8), //
	// @Text( loc="AppMonitoringStatus", 8), // 100%
	// @Text( loc="DisplayStatusText", 32), // PCO2 stabilizing
	// @Text( loc="WUTempStatus", 16), // protected
	// @Text( loc="WUPowerStatus"), // -
	// @Text( loc="SmbDateTime", 22), // 2011-04-96 14:26:52
	// @Text( loc="AppMonitoringTimeVal", 8), // 8.0h
	// @Text( loc="WuStatus", 4), // SP
	// @Text( loc="SmbSerialNb", 8), // 302848
	// @Text( loc="SmbPower", 8), // BAT
	// new MetricDescription("SmbBatteryCharge"), // 78
	// @Text( loc="SmbBatteryStatus", 8), // 100%
	// @Text( loc="MpbBarometerStatus", 8), // -
	// new MetricDescription("MpbBarometerVal"), // 741.2
	// @Text( loc="DsGas"), // 0%|30
	// @Text( loc="DsGasStatus", ""), // -
	@Text( loc="&f7", code="f7", length=16) // 192.168.1.3
	private String addr;
	@Text( loc="&64", code="64", length=8) // VS-A/P
	private String id;
	@Text( loc="&83", code="83", length=2) // CE
	private String ce;
	@Metric( loc="&4e", code="4e", precision=1) // 0.0
	private int zeroptzero;
	@Text( loc="&4a", code="4a", length=8) // 17.0|20
	private String unk_ratio;
	@Metric( loc="&b4", code="b4", desc="*B4") // 45
	private int unk1;
	@Metric( loc="&b5", code="b5", desc="*B5") // 30
	private int unk2;
	@Text( loc="&35", code="35", length=8) // 94|0
	private String unk_ratio2;
	@Metric( loc="&a2", code="a2", desc="*spo2", unit="%") // 100
	private int SpO;
	@Metric( loc="&a3", code="a3", desc="*hr", unit="bpm") // 85
	private int HR;
	@Text( loc="&36", code="36", length=8) // 85|0
	private String unk_ratio3;
	@Metric( loc="&a5", code="a5") // 140
	private int a5;
	@Metric( loc="&a6", code="a6") // 60
	private int a6;
	@Text( loc="&37", code="37", length=8) // 0.9|0
	private String unk_ratio4;
	@Text( loc="&17", code="17", length=8) // adult
	private String model;
	@Text( loc="&87", code="87", length=8) // info
	private String info;
	@Text( loc="&24", code="24", length=8) // 42.0|10
	private String unk_ratio5;
	@idea.persistence.Text( loc="&26", code="26", length=8) // 0|40
	private String s26;
	@Metric( loc="&23", code="23", desc="* tPCO2", unit="mmHg", precision=1) // 42.0
	private int PCO2;
	@Metric( loc="&2a", code="2a", desc="tPCO2", unit="mmHg") // 42.0
	private int tPCO2_b;
	@Metric( loc="&93", code="93") // 0
	private int n93;
	@Metric( loc="&91", code="91") // 0
	private int n91;
	@Metric( loc="&27", code="27", precision=1) // 8.0
	private int n27;
	@Metric( loc="&29", code="29", precision=1) // 12.0
	private int n29;
	@Metric( loc="&65", code="65") // [blank]
	private int blank1;
	@Metric( loc="&66", code="66") // [blank]
	private int blank2;
	@Metric( loc="&45", code="45") // 480
	private int n45;
	@Metric( loc="&43", code="43", precision=1) // 8.9
	private int n43;
	@Text( loc="&61", code="61", desc="Serial No", length=8) // 305680
	private String serialNo;
	@Text( loc="&62", code="62", desc="HWVersion?", length=8) // SV2D 01E A01
	private String hwVersion;
	@Text( loc="&63", code="63", desc="SWVersion", length=8) // V02.05
	private String swVersion;
	@Metric( loc="&33", code="33") // 6
	private int n33;
	@Text( loc="&1b", code="1b", length=8) // basic
	private String basic;
	@Text( loc="&8d", code="8d", length=8) // -
	private String dash;
	@Text( loc="&53", code="53", desc="VersionX?", length=8) // V05.00.10
	private String versionX;
	@Text( loc="&fb", code="fb", desc="VersionY?", length=8) // V07.00.4
	private String versionY;
	@Text( loc="&e1", code="e1", length=8) // normal
	private String mode;
	@Metric( loc="&e4", code="e4") // 4
	private String num4;
	@Text( loc="&e7", code="e7", length=8) // on
	private String p_on;


}
