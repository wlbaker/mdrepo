package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;

import lombok.Data;

@Entity
@SuppressWarnings("serial")
@Data
public class PICCO_ART extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String ART_LOC = "art";

	static {
		metrics = IntfUtil.getMetrics(PICCO_ART.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public PICCO_ART() {
		super(StreamID.WAVEFORM);
	}


	@Waveform(loc = ART_LOC, code = ART_LOC, unit = "mmHg", freq = 50, spp = 20)
	private int[] art = new int[20];
}

