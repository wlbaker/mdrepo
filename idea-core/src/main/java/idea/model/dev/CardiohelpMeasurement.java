package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Metric;
import idea.schema.rp.RpMetric;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;

@Entity
@Table(name = "Cardiohelp")
@Data
public class CardiohelpMeasurement extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(CardiohelpMeasurement.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public CardiohelpMeasurement() {
		super(StreamID.MEASUREMENT);
	}

	private final static int PVen_measurement = 1;
	private final static int PVen_limits = 2;
	private final static int PInt_measurement = 6;
	private final static int PInt_limits = 7;
	private final static int PArt_measurement = 11;
	private final static int PArt_limits = 12;
	private final static int PAux_measurement = 16;
	private final static int PAux_limits = 17;
	private final static int deltaP_measurement = 21;
	private final static int deltaP_limits = 22;
	private final static int Flow_measurement = 24;
	private final static int Flow_limits = 25;
	private final static int Speed_measurement = 27; // Speed rpm 0 � 5025 -32000*
	private final static int Speed_limits = 28; // Warning low rpm 0 � 5000 5001
	private final static int SvO2_measurement = 30; // SvO2 % 40.0 � 99.9 -32000*
	private final static int SvO2_limits = 31; // Low limit % 40.0 � 99.9 100.0
	private final static int Hb_measurement = 33; // Hb g/dl 5.0 � 15.0 -32000*
	private final static int Hb_limits = 34; // Low limit g/dl 5.0 � 15.0 15.1
	private final static int Hct_measurement = 36; // Hct % 15.0 � 50.0 -32000*
	private final static int Hct_limits = 37; // Low limit % 15.0 � 50.0 50.1
	private final static int TVen_measurement = 39; // TVen �C 10.0 � 45.0 -32000*
	private final static int TVen_limits = 40; // Low limit �C 10.0 � 45.0 45.1
	private final static int TArt_measurement = 42; // TArt �C 10.0 � 45.0 -32000*
	private final static int TArt_limits = 43; // Low limit �C 10.0 � 45.0 45.1
	private final static int Bubble_measurement = 45; // Bubble -- 0 � 1 -32000*
	private final static int Level_measurement = 46; // Level -- 0 � 1 -32000*
	private final static int Requested_flow = 47; // Requested flow l/min 0 � +9.99 -32000*
	private final static int Requested_speed = 48; // Requested speed rpm 0 � 5000 -32000*
	private final static int Requested_pump_mode = 49; // Requested pump	mode (RPM / LPM)
	private final static int Active_pump_mode = 50; //(RPM / LPM)
	//		private final static int TVen_measurement = 39; // TVen �C 10.0 � 45.0 -32000*
	//		private final static int TArt_measurement = 42; // TArt �C 10.0 � 45.0 -32000*
	//		private final static int Bubble_measurement = 45; // Bubble -- 0 � 1 -32000*
	//		private final static int Level_measurement = 46; // Level -- 0 � 1 -32000*
	//		private final static int Requested_flow = 47; // Requested flow l/min 0 � +9.99 -32000*
	//		private final static int Requested_speed = 48; // Requested speed rpm 0 � 5000 -32000*
	//		private final static int Requested_pump_mode	=	49; // Requested pump	mode (RPM / LPM)
	//		private final static int Active_pump_mode = 50; //(RPM / LPM)

	@Column(name = "PVen", nullable = true)
	@Metric( loc="" + PVen_measurement, code="PVen", unit="mmHg", precision=1)
	private Integer PVen;
	
	@Column(name = "SpO2", nullable = true)
	@Metric( loc="" +PInt_measurement, code="SpO2", unit="mmHg", precision=1)
	private Integer SpO2;

	@Column(name = "PART", nullable = true)
	@Metric( loc="" +PArt_measurement, code="PArt", unit="mmHg", precision=1)
	private Integer PArt;
	
	@Column(name = "PAUX", nullable = true)
	@Metric( loc="" +PAux_measurement, code="PAux", unit="mmHg", precision=1)
	private Integer PAux;
	
	@Column(name = "DELTA_P", nullable = true)
	@Metric( loc="" +deltaP_measurement, code="deltaP", unit="mmHg")
	private Integer deltaP;

	@Column(name = "FLOW", nullable = true)
	@Metric( loc="" +Flow_measurement, code="Flow", unit="L/min", precision=2)
	private Integer flow;

	@Column(name = "SPEED", nullable = true)
	@Metric( loc="" +Speed_measurement, code="Speed", unit="rpm")
	private Integer speed;

	@Column(name = "SvO2", nullable = true)
	@Metric( loc="" +SvO2_measurement, code="SvO2", unit="L/min", precision=2)
	private Integer SvO2;

	@Column(name = "Hb", nullable = true)
	@Metric( loc="" +Hb_measurement, code="Hb", unit="g/dl")
	private Integer Hb;

	@Column(name = "Hct", nullable = true)
	@Metric( loc="" +Hct_measurement, code="Hct", unit="L/min", precision=2) 
	private Integer Hct;

}
