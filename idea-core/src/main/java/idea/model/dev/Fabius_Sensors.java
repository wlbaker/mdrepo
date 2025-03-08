package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class Fabius_Sensors extends PersistentItem {

	protected final static int WF_PACKET_SIZE = 64;
	protected final static String two_subscript = "2"; // + (char)0xE2 (char)0x82 "\u2082";

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(Fabius_Sensors.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public Fabius_Sensors() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */

	@Waveform(loc="0x00", code="PAW", desc="Airway Pressure", freq=96, spp=WF_PACKET_SIZE, unit="mbar") private int [] PAW;
	@Waveform(loc="0x01",  code="Flow", desc="Flow (insp./exp.)", freq=96, spp=WF_PACKET_SIZE, unit="Lmin") private int [] FLOW;
	@Waveform(loc="0x21",  code="eFlow", desc="Expiratory Flow", freq=96, spp=WF_PACKET_SIZE, unit="Lmin") private int [] EFLOW;

}
