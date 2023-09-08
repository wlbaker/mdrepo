package icuInterface.adapters.s5;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import idea.schema.rp.RpMetric;
import lombok.Data;

@Data
public class wf_group extends PersistentItem {

	private static RpMetric[] metrics;
	static {
		metrics = IntfUtil.getMetrics(wf_group.class);
	}

	public wf_group(StreamProducer driver) {
		super(driver, StreamID.WAVEFORM.getCode());
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	// private static final int VARLEN=-1;
	private static final int VARLEN=-1;
	private static final int SPP_300HZ = 150;
	private static final int SPP_100HZ = 50;
	private static final int SPP_25HZ = 15;
	
	private static final String mmHg = "mmHg";
	private static final String ohm = "\u03A9";

	private final static String microV = "\u03BCV";
	private final static String tenthmicroV = "\u03BCV";

	@Waveform(loc = "wf.ecg1", code = "ECG1", freq = 300, spp = SPP_300HZ, unit = "mV")
	int[] ecg1;
	@Waveform(loc = "wf.ecg2", code = "ECG2", freq = 300, spp = SPP_300HZ, unit = "mV")
	int[] ecg2;
	@Waveform(loc = "wf.ecg3", code = "ECG3", freq = 300, spp = SPP_300HZ, unit = "mV")
	int[] ecg3;

	@Waveform(loc = "wf.invp1", code = "INVP1", freq = 100, spp = SPP_100HZ, precision=2, unit = mmHg)
	int[] invp1;
	@Waveform(loc = "wf.invp2", code = "INVP2", freq = 100, spp = SPP_100HZ, precision=2, unit = mmHg)
	int[] invp2;
	@Waveform(loc = "wf.invp3", code = "INVP3", freq = 100, spp = SPP_100HZ, precision=2, unit = mmHg)
	int[] invp3;
	@Waveform(loc = "wf.invp4", code = "INVP4", freq = 100, spp = SPP_100HZ, precision=2, unit = mmHg)
	int[] invp4;

	@Waveform(loc = "wf.invp5", code = "INVP5", freq = 100, spp = SPP_100HZ, precision=2, unit = mmHg)
	int[] invp5;
	@Waveform(loc = "wf.invp6", code = "INVP6", freq = 100, spp = SPP_100HZ, precision=2, unit = mmHg)
	int[] invp6;

	@Waveform(loc = "wf.pleth", code = "PLETH", freq = 100, spp = SPP_100HZ, unit = "%")
	int[] pleth;

	@Waveform(loc = "wf.co2", code = "wfCO2", freq = 25, spp = SPP_25HZ, unit = "%")
	int[] co2;
	@Waveform(loc = "wf.o2", code = "wfO2", freq = 25, spp = SPP_25HZ, unit = "%")
	int[] o2;
	@Waveform(loc = "wf.n2o", code = "wfN2O", freq = 25, spp = SPP_25HZ, unit = "%")
	int[] n2o;
	@Waveform(loc = "wf.aa", code = "wfAA", freq = 25, spp = SPP_25HZ, unit = "%")
	int[] aa;
	@Waveform(loc = "wf.awp", code = "wfAWP", freq = 25, spp = SPP_25HZ, unit = "cmH2O")
	int[] awp;
	@Waveform(loc = "wf.flow", code = "Flow", freq = 25, spp = SPP_25HZ, unit = "l@min")
	int[] flow;

	@Waveform(loc = "wf.vol", code = "wfVol", freq = 25, spp = SPP_25HZ, unit = "??")
	int[] vol;
	@Waveform(loc = "wf.resp", code = "RESP", freq = 25, spp = SPP_25HZ, precision=2, unit = ohm)
	int[] resp;

	@Waveform(loc = "wf.eeg1", code = "EEG1", freq = 100, spp = SPP_100HZ, precision=1, unit = tenthmicroV)
	int[] eeg1;
	@Waveform(loc = "wf.eeg2", code = "EEG2", freq = 100, spp = SPP_100HZ, precision=1, unit = tenthmicroV)
	int[] eeg2;
	@Waveform(loc = "wf.eeg3", code = "EEG3", freq = 100, spp = SPP_100HZ, precision=1, unit = tenthmicroV)
	int[] eeg3;
	@Waveform(loc = "wf.eeg4", code = "EEG4", freq = 100, spp = SPP_100HZ, precision=1, unit = tenthmicroV)
	int[] eeg4;

	@Waveform(loc = "wf.eegbis", code = "EEG_BIS", freq = 300, spp = SPP_300HZ, unit = microV)
	int[] eegbis;
	@Waveform(loc = "wf.tono", code = "TONO-PRESS", freq = 25, spp = SPP_25HZ, unit = mmHg)
	int[] tono;
	@Waveform(loc = "wf.spiloop", code = "SPI_STATUS", freq = 25, spp = SPP_25HZ, unit = "??")
	int[] spiloop;
	@Waveform(loc = "wf.ent100", code = "ENT100", freq = 100, spp = SPP_100HZ, precision=1, unit = tenthmicroV)
	int[] ent100;

}
