package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import jakarta.persistence.Entity;

import lombok.Data;

@Entity
@SuppressWarnings("serial")
@Data
public class CapnostreamWaveform extends PersistentItem {

	public final static int WF_PKT_SIZE = 20;
	
	protected static RpMetric[] metrics;

	public static final String CO2_LOC = "CO2";

	static {
		metrics = IntfUtil.getMetrics(CapnostreamWaveform.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public CapnostreamWaveform() {
		super(StreamID.WAVEFORM);
	}


	// LinearUnit mmHg256 = new LinearUnit(1.0 / 256, 0, "mmHg");
	// so 256 is not the same as precision=2.  Hmm.  Need a divisor or multiplier
	@Waveform(loc = CO2_LOC, code = CO2_LOC, freq = (20 + 2), spp = WF_PKT_SIZE, unit = "mmHg256", precision=2)

	private int[] CO2 = new int[WF_PKT_SIZE];
}

