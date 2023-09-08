package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.JoinColumn;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.persistence.Transient;

import lombok.Data;

@Entity
@Table(name = "DragerDelta_SensorsEKG5")
@Data
public class DragerDelta_SensorsEKG5 extends PersistentItem {

	private final static String ECG_UNIT="MICROVOLT";
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(DragerDelta_SensorsEKG5.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public DragerDelta_SensorsEKG5() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */


	@Waveform(loc = "ecg u", code = "u", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] u;

//	@Waveform(loc = "ecg lead_I", code = "lead_i", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
//	int[] ecg_lead_I;
//	@Waveform(loc = "ecg lead_II", code = "lead_ii", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
//	int[] ecg_lead_II;
//	@Waveform(loc = "ecg lead_III", code = "lead_iii", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
//	int[] ecg_lead_III;
//	@Waveform(loc = "ecg lead_V", code = "lead_v", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
//	int[] ecg_lead_V;
//	@Waveform(loc = "ecg lead_v_prime", code = "lead_v_prime", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
//	int[] ecg_lead_V_prime;


}
