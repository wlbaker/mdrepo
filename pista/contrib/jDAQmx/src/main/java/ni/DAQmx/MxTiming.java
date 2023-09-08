package ni.DAQmx;

import ni.DAQcommon.SampleClockActiveEdge;
import ni.DAQcommon.SampleQuantityMode;
import ni.DAQcommon.Timing;

public class MxTiming extends Timing {

	MxTiming(long taskHandle) {
		super(taskHandle);
		// TODO Auto-generated constructor stub
	}

	@Override
	public native void configureSampleClock(String signalSource, double rate,
			SampleClockActiveEdge activeEdge, SampleQuantityMode sampleMode,
			int samplesPerChannel);

	// DAQmxCfgOutputBuffer
	public native void configureOutputBuffer( int numSampsPerChannel );
	
	/*
	DAQmx_Val_Poll 12524: Repeatedly check for available buffer space as fast as possible.
	DAQmx_Val_Yield 12525: Yield control to other threads, but check frequently.
	DAQmx_Val_Sleep 12547: Check for available buffer space once per amount of time specified by SleepTime
	 */
	public native int getWriteWaitMode(); // DAQmxGetWriteWaitMode
	public native int setWriteWaitMode(int val); // DAQmxSetWriteWaitMode
	public native int resetWriteWaitMode(); // DAQmxResetWriteWaitMode
	
	public native int getWriteSleepTime();
	public native int setWriteSleepTime();
	public native int resetWriteSleepTime();

}
