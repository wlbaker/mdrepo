package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Data
@EqualsAndHashCode(callSuper = false)
public class Novalung_Measurement extends PersistentItem {
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(Novalung_Measurement.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public Novalung_Measurement() {
		super(StreamID.MEASUREMENT);
	}

			@Metric(loc="1", code="speed", desc="Drive Speed", unit="rpm")
			private int speed;
			@Metric(loc="2", code="setSpeed", desc="Set point Speed", unit="rpm")
			private int speedSetpoint;
			@Metric(loc="3", code="speedLimMin", desc="Speed min alarm limit", unit="rpm")
			private int minSpeed;
			@Metric(loc="4", code="speedLimMax", desc="Speed max alarm limit", unit="rpm")
			private int maxSpeed;
			@Metric(loc="5", code="dU", desc="Difference (pulsatile mode)", unit="rpm")
			private int dU;
			@Metric(loc="6", code="fPulse", desc="Frequency (pulsatile mode)", unit="bpm")
			private int fPulse;
			@Metric(loc="7", code="systole", desc="Systole (pulsatile mode)", unit="%")
			private int systole;
			@Metric(loc="8", code="Flow", desc="Blood Flow", unit="ml/min")
			private int flow;
			@Metric(loc="9", code="setFlow", desc="Set point Flow", unit="ml/min")
			private int flowSetpoint;
			@Metric(loc="10", code="flowLimMin", desc="Flow min alarm limit", unit="ml/min")
			private int minFlow;
			@Metric(loc="11", code="flowLimMax", desc="Flow max alarm limit", unit="ml/min")
			private int maxFlow;
			@Metric(loc="12", code="p1", desc="Pressure p1", unit="mmHg")
			private int P1;
			@Metric(loc="13", code="p2", desc="Pressure p2", unit="mmHg")
			private int P2;
			@Metric(loc="14", code="p3", desc="Pressure p3", unit="mmHg")
			private int P3;
			@Metric(loc="15", code="p4", desc="Pressure p4", unit="mmHg")
			private int P4;
			@Metric(loc="16", code="p1LimMin", desc="Pressure p1 min alarm limit", unit="mmHg")
			private int minP1;
			@Metric(loc="17", code="p2LimMin", desc="Pressure p2 min alarm limit", unit="mmHg")
			private int minP2;
			@Metric(loc="18", code="p3LimMin", desc="Pressure p3 min alarm limit", unit="mmHg")
			private int minP3;
			@Metric(loc="19", code="p4LimMin", desc="Pressure p4 min alarm limit", unit="mmHg")
			private int minP4;
			@Metric(loc="20", code="p1LimMax", desc="Pressure p1 max alarm limit", unit="mmHg")
			private int maxP1;
			@Metric(loc="21", code="p2LimMax", desc="Pressure p2 max alarm limit", unit="mmHg")
			private int maxP2;
			@Metric(loc="22", code="p3LimMax", desc="Pressure p3 max alarm limit", unit="mmHg")
			private int maxP3;
			@Metric(loc="23", code="p4LimMax", desc="Pressure p4 max alarm limit", unit="mmHg")
			private int maxP4;
			@Metric(loc="24", code="T1", desc="Temperature T1", unit="C", precision=1)
			private int T1;
			@Metric(loc="25", code="T2", desc="Temperature T2", unit="C", precision=1)
			private int T2;
			@Metric(loc="26", code="T1LimMin", desc="Temperature T1 min alarm limit", unit="C", precision=1)
			private int minT1;
			@Metric(loc="27", code="T2LimMin", desc="Temperature T2 min alarm limit", unit="C", precision=1)
			private int minT2;
			@Metric(loc="28", code="T1LimMax", desc="Temperature T1 max alarm limit", unit="C", precision=1)
			private int maxT1;
			@Metric(loc="29", code="T2LimMax", desc="Temperature T2 max alarm limit", unit="C", precision=1)
			private int maxT2;
	//new MetricDescription("30", code="guiLocked", desc="Locking state of GUI", LinearUnit.unit),
	//new MetricDescription("31", code="flowSensorType", desc="Type of Sensor", LinearUnit.unit),
	//new MetricDescription("32", code="pumpType", desc="Type of Pump", LinearUnit.unit),
	//new MetricDescription("33", code="bubbleState", desc="", LinearUnit.unit),
	//new MetricDescription("34", code="levelState", desc="", LinearUnit.unit),
	//new MetricDescription("35", code="driveState", code="", LinearUnit.unit),
	//new MetricDescription("36", code="sbState", desc="", LinearUnit.unit),
	//new MetricDescription("37", code="powerState", desc="", LinearUnit.unit),
	//new MetricDescription("38", code="PD_ERROR", desc="", LinearUnit.unit),
	//new MetricDescription("39", code="SB_ERROR", desc="", LinearUnit.unit),
	//new MetricDescription("40", code="PS_ERROR", desc="", LinearUnit.unit),
	//new MetricDescription("41", code="CP_ERROR", desc="", LinearUnit.unit),

}
