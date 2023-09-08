package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class DragerApollo_Sensors extends PersistentItem {

	protected final static int WF_PACKET_SIZE = 64;
	protected final static String two_subscript = "2"; // + (char)0xE2 (char)0x82 "\u2082";

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(DragerApollo_Sensors.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public DragerApollo_Sensors() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */

	@Waveform(loc="0x00", code="PAW", desc="Airway Pressure", freq=200, spp=WF_PACKET_SIZE, unit="mbar") private int [] PAW;
	@Waveform(loc="0x01",  code="Flow", desc="Flow (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="Lmin") private int [] FLOW;
	@Waveform(loc="0x02",  code="Pleth", desc="Pleth", freq=200, spp=WF_PACKET_SIZE, unit="%") private int [] PLETH;
	@Waveform(loc="0x05",  code="O2", desc="O2 (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="%") private int [] O2;
	@Waveform(loc="0x06",  code="etCO2", desc="Exp CO" + two_subscript, freq=200, spp=WF_PACKET_SIZE, unit="mmHg") private int [] EtCO2;
	@Waveform(loc="0x07",  code="etCO2", desc="Exp CO" + two_subscript, freq=200, spp=WF_PACKET_SIZE, unit="kPa") private int [] EtCO2kpa;
	@Waveform(loc="0x08",  code="etCO2", desc="Exp CO" + two_subscript, freq=200, spp=WF_PACKET_SIZE, unit="%" ) private int [] EtCO2pct; // Vol%

	@Waveform(loc="0x0A", desc="Agent (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="%") private int [] AGENT;
	@Waveform(loc="0x0B", desc="Halothane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="%") private int [] HALO;
	@Waveform(loc="0x0C", desc="Enflurane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="%") private int [] ENFL;
	@Waveform(loc="0x0D", desc="Isoflurane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="%") private int [] ISO;
	@Waveform(loc="0x0E", desc="Desflurane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="%") private int [] DES;
	@Waveform(loc="0x0F", desc="Sevoflurane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="%") private int [] SEVO;

	// new since device version 1.05
	@Waveform(loc="0x2A", desc="Agent (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="kPa") private int [] AGENT2A;
	@Waveform(loc="0x2B", desc="Halothane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="kPa") private int [] AGENT2B;
	@Waveform(loc="0x2C", desc="Enflurane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="kPa") private int [] ENFL2C;
	@Waveform(loc="0x2D", desc="Isoflurane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="kPa") private int [] ISO2D;
	@Waveform(loc="0x2E", desc="Desflurane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="kPa") private int [] DES2E;
	@Waveform(loc="0x2F", desc="Sevoflurane (insp./exp.)", freq=200, spp=WF_PACKET_SIZE, unit="kPa") private int [] SEVO2F;
	

}
