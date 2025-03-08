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
public class NM3Waveform extends PersistentItem {

	public final static int WF_PKT_SIZE = 50;

	protected static RpMetric[] metrics;

	public static final String FLOW_LOC = "0x00";
	public static final String PAW_LOC = "0x01";
	public static final String CO2_LOC = "0x02";
	public static final String VOL_LOC = "0x04";

	static {
		metrics = IntfUtil.getMetrics(NM3Waveform.class);
	}

	@Override
	public RpMetric[] getMetrics() {
		return metrics;
	}

	public NM3Waveform() {
		super(StreamID.WAVEFORM);
	}

	// adult sensor resolution 0.1 L/min [-180,180]
	// neonatal sensor resolutino 0.01 L/min range [-40,40]

	// airway pressure resolution 0.05 cmH2O range [-120, 120.0] cmH2O

	// adult sensor resolution 0.1 L/min [-180,180]
	// neonatal sensor resolutino 0.01 L/min range [-40,40]
	@Waveform(loc = FLOW_LOC, code = "Flow", freq = 100, spp = WF_PKT_SIZE, unit = "L/min", precision=1)
	private int[] flow = new int[WF_PKT_SIZE];

	// airway pressure resolution 0.05 cmH2O range [-10.0,99.9]
	@Waveform(loc = PAW_LOC, code = "Paw", desc = "Airway Pressure", freq = 100, spp = WF_PKT_SIZE, unit = "twentythscmH2O")
	private int[] paw = new int[WF_PKT_SIZE];
	
	// CO2 0.1mmHg range [-10,99.9]
	@Waveform(loc = CO2_LOC, code = "CO2", desc = "CO2", freq = 100, spp = WF_PKT_SIZE, unit = "mmHg", precision = 1)
	private int[] co2 = new int[WF_PKT_SIZE];
	
	@Waveform(loc = VOL_LOC, code = "Vol", desc = "Volume", freq = 100, spp = WF_PKT_SIZE, unit = "L")
	private int[] vol = new int[WF_PKT_SIZE];

}
