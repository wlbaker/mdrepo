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
@Table(name = "DragerDelta_SensorsAna")
@Data
public class DragerDelta_SensorsAnaesthesia extends PersistentItem {

	private final static String ECG_UNIT="MICROVOLT";
	@Transient
	private static RpMetric[] metrics;

	static {
		metrics = IntfUtil.getMetrics(DragerDelta_SensorsAnaesthesia.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public DragerDelta_SensorsAnaesthesia() {
		super(StreamID.WAVEFORM);
	}

	/*
	 * 
	 */


	// sample rate unknown!!!
	@Waveform(loc = "mgm_agent iso", code = "MGM_Agent", freq = 50, spp = 10, unit = "mmHg", m=0.16666, b=0)
	int[] agent_iso;
	@Waveform(loc = "mgm_o2", code = "MGM_O2", freq = 50, spp = 10, unit = "%", precision=1)
	int[] o2;
	@Waveform(loc = "mgm_co2", code = "MGM_CO2", freq = 50, spp = 10, unit = "mmHg", m=0.16666, b=0)
	int[] co2;

	// newest
	@Waveform(loc = "cnap", code = "CNAP", freq = 100, spp = 20, unit = "mmHg", m=0.16666, b=0)
	int[] cnap;

	@Waveform(loc = "mib_vent press", code = "PAW", desc = "MIB Ventilator Pressure", freq = 50, spp = 10, unit = "L/min")
	int[] paw;

	@Waveform(loc = "mib_vent flow", code = "Flow", desc = "MIB Ventilator Flow", freq = 50, spp = 10, unit = "L/min", precision=1)
	int[] flow;

}
