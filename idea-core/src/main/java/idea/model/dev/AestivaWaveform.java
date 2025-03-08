package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Transient;

import lombok.Data;

@Data
public class AestivaWaveform extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	// determined by burst length in waveform configuration
	public static final int WF_PKT_SIZE = 15;

	private static final int WF_PRESSURE_ID = 0;
	private static final int WF_FLOW_ID = 1;
	private static final int WF_VOL_ID = 2;

	static {
		metrics = IntfUtil.getMetrics(AestivaWaveform.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public AestivaWaveform() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */

	// sample rate = 1/16ms...62.5 samples / sec
	@Waveform(loc = "0x" + WF_PRESSURE_ID, code = "PRES", desc = "Pressure", freq = 62, spp = WF_PKT_SIZE, unit = "cmH2O")
	private int[] press;
	@Waveform(loc = "0x" + WF_FLOW_ID, code = "Flow", desc = "Flow", freq = 62, spp = WF_PKT_SIZE, unit = "L/min")
	private int[] flow;
	@Waveform(loc = "0x" + WF_VOL_ID, code = "V", desc = "Volume", freq = 62, spp = WF_PKT_SIZE, unit = "L")
	private int[] vol;

}
