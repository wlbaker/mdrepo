package idea.model.dev;

import javax.persistence.Entity;
import javax.persistence.Table;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Entity
@Table(name = "SIMUSIN_W")
@SuppressWarnings("serial")
@Data
public class SimuSine_Waveform extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String WF0_LOC = "waveform0";
	public static final String WF1_LOC = "waveform1";
	public static final String WF2_LOC = "waveform2";

	static {
		metrics = IntfUtil.getMetrics(SimuSine_Waveform.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public SimuSine_Waveform() {
		super(StreamID.WAVEFORM);
	}


	@Waveform(loc = WF0_LOC, code = WF0_LOC, unit = "mmHg", freq = 50, spp = 50, m=0.01)
	private int[] wf0;
	@Waveform(loc = WF1_LOC, code = WF1_LOC, unit = "inH2O", freq = 50, spp = 50, m=1)
	private int[] wf1;
	@Waveform(loc = WF2_LOC, code = WF1_LOC, unit = "inH2O", freq = 50, spp = 50, m=1)
	private float[] wf2;
}

