package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Entity
@Table(name = "BIS_Sensor")
@Data
@EqualsAndHashCode(callSuper = false)
public class BISSensors extends PersistentItem {

	public static final short SAMPLE_RATE = 128;
	
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(BISSensors.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public BISSensors() {
		super(StreamID.WAVEFORM);
	}

	@Waveform(loc = "EEG1", code = "eeg1", freq = SAMPLE_RATE, spp = SAMPLE_RATE / 8, unit = "\u03BCV")  // microV
	int[] eeg1;
	@Waveform(loc = "EEG2", code = "eeg2", freq = SAMPLE_RATE, spp = SAMPLE_RATE / 8, unit = "\u03BCV")  // microV
	int[] eeg2;
}
