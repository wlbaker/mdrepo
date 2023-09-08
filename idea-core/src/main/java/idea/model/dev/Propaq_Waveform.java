package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;
import lombok.Data;

@SuppressWarnings("serial")
@Data
public class Propaq_Waveform extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String WF0_LOC = "wf0";
	public static final String WF1_LOC = "wf1";
	public final static byte ECG1_CHANNEL_IDX = 0;
	public final static byte ECG2_CHANNEL_IDX = 1;
	public final static byte INVP1_CHANNEL_IDX = 2;
	public final static byte INVP2_CHANNEL_IDX = 3;
	public final static byte NIBP_CHANNEL_IDX = 4;
	public final static byte SPO2_CHANNEL_IDX = 5;
	public final static byte CO2_CHANNEL_IDX = 6;

	private static final int WF_PKT_SIZE = 16;
	private static final int WF8_PKT_SIZE = 8;
	private static final int WF6_PKT_SIZE = 6;

	public final static byte ECG1_CHANNEL_MASK = 0x01;
	public final static byte ECG2_CHANNEL_MASK = 0x02;
	public final static byte INVP1_CHANNEL_MASK = 0x04;
	public final static byte INVP2_CHANNEL_MASK = 0x08;
	public final static byte NIBP_CHANNEL_MASK = 0x10;
	public final static byte SPO2_CHANNEL_MASK = 0x20;
	public final static byte CO2_CHANNEL_MASK = 0x40;

	static {
		metrics = IntfUtil.getMetrics(Propaq_Waveform.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public Propaq_Waveform() {
		super(StreamID.WAVEFORM);
	}

	@Waveform(loc = "0x" + ECG1_CHANNEL_MASK, code = "ECG", freq = 182, spp = WF_PKT_SIZE, unit = "mmHg")
	private int[] ecg1;

	@Waveform(loc = "0x" + ECG2_CHANNEL_MASK, code = "ECG2", freq = 182, spp = WF_PKT_SIZE, unit = "mmHg")
	private int[] ecg2;

	@Waveform(loc = "0x" + INVP1_CHANNEL_MASK, code = "INVP1", desc = "Invasive Pressure 1", freq = 92, spp = WF8_PKT_SIZE, unit = "mmHg")
	private int[] invp1;
	@Waveform(loc = "0x" + INVP2_CHANNEL_MASK, code = "INVP2", desc = "Invasive Pressure 2", freq = 92, spp = WF8_PKT_SIZE, unit = "mmHg")
	private int[] invp2;

	@Waveform(loc = "0x" + NIBP_CHANNEL_MASK, code = "NIBP", freq = 68, spp = WF6_PKT_SIZE, unit = "mmHg")
	private int[] nibp;
	@Waveform(loc = "0x" + SPO2_CHANNEL_MASK, code = "SPO2", freq = 68, spp = WF6_PKT_SIZE, unit = "mmHg")
	private int[] spo2;

	@Waveform(loc = "0x" + CO2_CHANNEL_MASK, code = "CO2", freq = 11, spp = 1, unit = "mmHg")
	private int[] co2;

}
