package idea.model.dev;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;

import javax.persistence.Transient;

import lombok.Data;

@Data
public class Intellivue_Sensors extends PersistentItem {

	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(Intellivue_Sensors.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public Intellivue_Sensors() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */

	@Waveform(loc = "ecg lead_I", code = "EKG0", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_I;

	@Waveform(loc = "ecg lead_II", code = "EKG1", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_II;
	@Waveform(loc = "ecg lead_III", code = "EKG2", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_III;
	@Waveform(loc = "ecg lead_V", code = "EKG3", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_V;

	@Waveform(loc = "ecg lead_V2", code = "V2", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_V2;
	@Waveform(loc = "ecg lead_V5", code = "V5", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_V5;
	@Waveform(loc = "ecg lead_v_prime", code = "v_prime", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_v_prime;
	@Waveform(loc = "ecg lead_DV1", code = "DV1", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_DV1;
	@Waveform(loc = "ecg lead_DV3", code = "DV3", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_DV3;
	@Waveform(loc = "ecg lead_DV4", code = "DV4", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_DV4;
	@Waveform(loc = "ecg lead_DV5", code = "DV5", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_DV5;
	@Waveform(loc = "ecg lead_DV6", code = "DV6", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_DV6;
	@Waveform(loc = "ecg lead_AVR", code = "AVR", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_AVR;
	@Waveform(loc = "ecg lead_AVF", code = "AVF", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_AVF;
	@Waveform(loc = "ecg lead_AVL", code = "AVL", freq = 200, spp = 40, unit = "mV", precision=2)
	int[] ecg_lead_AVL;
	@Waveform(loc = "a2co2", code = "a2co2", freq = 50, spp = 10, unit = "mV", precision=2)
	int[] a2co2;

	// cap.addWaveform( loc="q1", code="Paw???",  50, 10, "mV");
	// cap.addWaveform( loc="q2", code="q2",  freq=50, spp=10, "mV");
	// cap.addWaveform( loc="q3", code="EtCO2",  freq=50, spp=10, "mV");

	@Waveform(loc = "art", code = "ABP", freq = 100, spp = 20, unit = "mmHg", m = 0.02)
	int[] art;
	@Waveform(loc = "spo2 pulse", code = "SPO2", freq = 100, spp = 20, unit = "%", precision=125)
	int[] spo2_pulse;
	@Waveform(loc = "pa", code = "PA", freq = 100, spp = 20, unit = "mmHg", m = 0.02)
	int[] pa;
	@Waveform(loc = "cvp", code = "CVP", freq = 100, spp = 20, unit = "mmHg", m = 0.02)
	int[] cvp;
	@Waveform(loc = "n2", code = "SpO2", freq = 100, spp = 20)
	int[] n2;
	@Waveform(loc = "n3", code = "ART/PA?", freq = 100, spp = 20, unit = "mmHg", precision=1)
	int[] n3;
	@Waveform(loc = "n4", code = "PA/ART?", freq = 100, spp = 20, unit = "mmHg", precision=1)
	int[] n4;
	@Waveform(loc = "ra", code = "RA", freq = 100, spp = 20, unit = "mmHg", m = 0.025)
	int[] ra;
	@Waveform(loc = "rv", code = "RV", freq = 100, spp = 20, unit = "mmHg", m = 0.025)
	int[] rv;
	@Waveform(loc = "la", code = "LA", freq = 100, spp = 20, unit = "mmHg", m = 0.025)
	int[] la;
	@Waveform(loc = "lv", code = "LV", freq = 100, spp = 20, unit = "mmHg", m = 0.025)
	int[] lv;
	@Waveform(loc = "gp1", code = "GP1", freq = 100, spp = 20, unit = "mmHg", m = 0.025)
	int[] gp1;
	@Waveform(loc = "gp2", code = "GP2", freq = 100, spp = 20, unit = "mmHg", m = 0.025)
	int[] gp2;
	@Waveform(loc = "icp", code = "ICP", freq = 100, spp = 20, unit = "mmHg", precision=2)
	int[] icp;
	@Waveform(loc = "resp", code = "RESP", freq = 50, spp = 10, unit = "ohm")
	int[] resp;

	// sample rate unknown!!!
	@Waveform(loc = "mgm_agent iso", code = "MGM_Agent", freq = 50, spp = 10, unit = "mmHg", m = 0.02)
	int[] agent_iso;
	@Waveform(loc = "mgm_o2", code = "MGM_O2", freq = 50, spp = 10, unit = "mmHg", m = 0.02)
	int[] o2;
	@Waveform(loc = "mgm_co2", code = "MGM_CO2", freq = 50, spp = 10, unit = "mmHg", m = 0.02)
	int[] co2;

	// newest
	@Waveform(loc = "cnap", code = "CNAP", freq = 100, spp = 20, unit = "mmHg", m = 0.02)
	int[] cnap;

	@Waveform(loc = "mib_vent press", code = "PAW", desc = "MIB Ventilator Pressure", freq = 50, spp = 10, unit = "mV")
	int[] paw;

	@Waveform(loc = "mib_vent flow", code = "Flow", desc = "MIB Ventilator Flow", freq = 50, spp = 10, unit = "mV")
	int[] flow;

}
