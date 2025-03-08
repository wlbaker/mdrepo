package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.OneToOne;
import jakarta.persistence.Table;
import jakarta.persistence.Transient;

import lombok.Data;

@Entity
@Table(name = "DragerDelta_SensorsEKG12")
@Data
public class DragerDelta_SensorsEKG12 extends PersistentItem {

	private final static String ECG_UNIT="MICROVOLT";
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(DragerDelta_SensorsEKG12.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public DragerDelta_SensorsEKG12() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */


	@Waveform(loc = "ecg lead_V2", code = "V2", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_V2;
	@Waveform(loc = "ecg lead_V5", code = "V5", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_V5;
	@Waveform(loc = "ecg lead_v_prime", code = "v_prime", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_v_prime;
	@Waveform(loc = "ecg lead_DV1", code = "DV1", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_DV1;
	@Waveform(loc = "ecg lead_DV3", code = "DV3", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_DV3;
	@Waveform(loc = "ecg lead_DV4", code = "DV4", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_DV4;
	@Waveform(loc = "ecg lead_DV5", code = "DV5", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_DV5;
	@Waveform(loc = "ecg lead_DV6", code = "DV6", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_DV6;
	@Waveform(loc = "ecg lead_AVR", code = "AVR", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_AVR;
	@Waveform(loc = "ecg lead_AVF", code = "AVF", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_AVF;
	@Waveform(loc = "ecg lead_AVL", code = "AVL", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_AVL;

}
