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
@Table(name = "DragerDelta_Sensors")
@Data
public class DragerDelta_Sensors extends PersistentItem {

	private final static String ECG_UNIT="MICROVOLT";
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(DragerDelta_Sensors.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public DragerDelta_Sensors() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */

	@OneToOne(cascade = CascadeType.ALL)
	@JoinColumn(name="ekg5_fk")
	private DragerDelta_SensorsEKG5 ekg5;
	
	@Waveform(loc = "ecg lead_I", code = "lead_i", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_I;
	@Waveform(loc = "ecg lead_II", code = "lead_ii", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_II;
	@Waveform(loc = "ecg lead_III", code = "lead_iii", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_III;
	@Waveform(loc = "ecg lead_V", code = "lead_v", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_V;
	@Waveform(loc = "ecg lead_v_prime", code = "lead_v_prime", freq = 200, spp = 40, unit = ECG_UNIT, precision=0)
	int[] ecg_lead_V_prime;

	@OneToOne(cascade = CascadeType.ALL)
	@JoinColumn(name="ekg12_fk")
	private DragerDelta_SensorsEKG12 ekg12;
	
	@Waveform(loc = "a2co2", code = "a2co2", freq = 50, spp = 10, unit = ECG_UNIT, precision=0)
	int[] a2co2;

	@Waveform(loc = "art", code = "ART", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] art;
	@Waveform(loc = "spo2 pulse", code = "SPO2", freq = 100, spp = 20, unit = "", precision=0)
	int[] spo2_pulse;
	@Waveform(loc = "pa", code = "PA", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] pa;
	@Waveform(loc = "cvp", code = "CVP", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] cvp;
	@Waveform(loc = "n2", code = "SpO2", freq = 100, spp = 20)
	int[] n2;
	@Waveform(loc = "n3", code = "n3", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)  // VERIFY CODE!  ART/PA?
	int[] n3;
	@Waveform(loc = "n4", code = "n4", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)  // VERIFY CODE! PA/ART?
	int[] n4;
	@Waveform(loc = "ra", code = "RA", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] ra;
	@Waveform(loc = "rv", code = "RV", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] rv;
	@Waveform(loc = "la", code = "LA", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] la;
	@Waveform(loc = "lv", code = "LV", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] lv;
	@Waveform(loc = "gp1", code = "GP1", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] gp1;
	@Waveform(loc = "gp2", code = "GP2", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] gp2;
	@Waveform(loc = "icp", code = "ICP", freq = 100, spp = 20, unit = "mmHg", precision=2)
	int[] icp;
	@Waveform(loc = "resp", code = "RESP", freq = 50, spp = 10, unit = "OHM", precision=3)
	int[] resp;

	@OneToOne(cascade = CascadeType.ALL)
	@JoinColumn(name="ana_fk")
	private DragerDelta_SensorsAnaesthesia ana;
	


}
