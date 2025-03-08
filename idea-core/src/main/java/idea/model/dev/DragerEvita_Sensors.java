package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class DragerEvita_Sensors extends PersistentItem {

	protected final static int WF_PACKET_SIZE = 64;
	protected final static String two_subscript = "2"; // + (char)0xE2 (char)0x82 "\u2082";

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(DragerEvita_Sensors.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public DragerEvita_Sensors() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */

	@Waveform(loc="0x00", code="PAW", desc="Airway Pressure", freq=126, spp=WF_PACKET_SIZE, unit="mbar") private int [] PAW;
	@Waveform(loc="0x01",  code="Flow", desc="Flow (insp./exp.)", freq=126, spp=WF_PACKET_SIZE, unit="Lmin") private int [] FLOW;
	@Waveform(loc="0x02",  code="Pleth", desc="Pleth", freq=126, spp=WF_PACKET_SIZE, unit="%") private int [] PLETH;
	
	@Waveform(loc="0x03",  code="RVol", desc="Resp. Vol since insp began", freq=126, spp=WF_PACKET_SIZE, unit="ml") private int [] RVOL;
	@Waveform(loc="0x06",  code="expCO2", desc="Exp CO" + two_subscript, freq=126, spp=WF_PACKET_SIZE, unit="mbar", precision=1) private int [] EtCO2;
	@Waveform(loc="0x07",  code="expCO2", desc="Exp CO" + two_subscript, freq=126, spp=WF_PACKET_SIZE, unit="kPa") private int [] EtCO2kpa;
	@Waveform(loc="0x08",  code="expCO2", desc="Exp CO" + two_subscript, freq=126, spp=WF_PACKET_SIZE, unit="%" ) private int [] EtCO2pct; // Vol%

	@Waveform(loc="0x20",  code="inspF", desc="Inspiratory Flow", freq=126, spp=WF_PACKET_SIZE, unit="L/min") private int [] iFLOW;
	@Waveform(loc="0x21",  code="expF", desc="Expiratory Flow", freq=126, spp=WF_PACKET_SIZE, unit="L/min") private int [] eFLOW;
	@Waveform(loc="0x24",  code="expV", desc="Expiratory Vol", freq=126, spp=WF_PACKET_SIZE, unit="ml") private int [] eVOL;
}
