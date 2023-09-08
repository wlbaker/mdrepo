package idea.model.dev;


import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class AesculonWaveform extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;
	
	// determined by burst length in waveform configuration
	private static final int WF_PACKET_SIZE = 50; 

	private static final String ECG_LOC = "0001";
	private static final String IMPEDENCE_LOC = "0002";

	static {
		metrics = IntfUtil.getMetrics(AesculonWaveform.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public AesculonWaveform() {
		super(StreamID.WAVEFORM);
	}
	/*
	 * 
	 */

	@Waveform(loc = ECG_LOC, code = "ECG", desc="Electrocardiogram", freq=300, spp=WF_PACKET_SIZE)
	private int [] ecg;
	@Waveform(loc = IMPEDENCE_LOC, code = "dZ", desc="Impedance", freq=300, spp=WF_PACKET_SIZE)
	private int [] dZ;

}

