package ni.DAQmxBase;

import ni.DAQcommon.SampleClockActiveEdge;
import ni.DAQcommon.SampleQuantityMode;
import ni.DAQcommon.Timing;

public class BaseTiming extends Timing {

	BaseTiming(long taskHandle) {
		super(taskHandle);
		// TODO Auto-generated constructor stub
	}

	@Override
	public native void configureSampleClock(String signalSource, double rate,
			SampleClockActiveEdge activeEdge, SampleQuantityMode sampleMode,
			int samplesPerChannel);

}
