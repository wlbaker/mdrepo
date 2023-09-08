package ni.user;

import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqSystem;
import ni.DAQcommon.IAsyncResult;
import ni.DAQcommon.Task;
import ni.DAQcommon.SampleClockActiveEdge;
import ni.DAQcommon.SampleQuantityMode;
import ni.DAQcommon.TaskAction;
import ni.DAQmx.MxAnalogMultiChannelReader;
import ni.DAQmx.MxTask;

public class ContAcqVoltage implements AsyncCallback {
	private Task myTask;
	private MxAnalogMultiChannelReader reader;
	private AnalogWaveform[] data;

	@Override
	public void asyncCallback(IAsyncResult result) {

		try {
			// wlb if (runningTask == result.AsyncState) {
			// Read the available data from the channels
			data = reader.endReadWaveform(result);

			// Plot your data here
			System.out.println("data[0] = " + data[0]);

			// wlb reader.beginMemoryOptimizedReadWaveform(samplesPerChannel,
			// wlb		analogCallback, myTask, data);
			// wlb }
		} catch (DaqException exception) {
			// Display Errors
			exception.printStackTrace();

			// wlb runningTask = null;
			myTask.dispose();
		}

	}

	private void init(String channel, double minValue, double maxValue,
			double sampleRate, int samples, int pretriggerSamples) {

		try {
			// Create the task
			myTask = new MxTask( "" );

			// Create channels
			myTask.getAIChannels().createVoltageChannel(channel, "",
					AITerminalConfiguration.DEFAULT, minValue, maxValue,
					AIVoltageUnits.Volts);

			// Set up timing
			myTask.getTiming().configureSampleClock("", sampleRate,
					SampleClockActiveEdge.Rising,
					SampleQuantityMode.ContinuousSamples, 1000);

			// Verify the task
			myTask.control(TaskAction.Verify);

			reader = new MxAnalogMultiChannelReader(myTask.getStream());

			AsyncCallback acb = new AsyncCallback( ) {

				@Override
				public void asyncCallback(IAsyncResult result) {
					System.err.println( "DING");
				}
				
			};

			reader.beginReadWaveform(samples, this, myTask);
			
		} catch (DaqException ex) {
			System.err.println(ex.getMessage());
			ex.printStackTrace();

			myTask.dispose();
			myTask = null;
		}

	}

	public static void main(String... args) {

		System.loadLibrary("jDAQmx");

		String[] channels = DaqSystem.getMxLocal().getPhysicalChannels();

		if( channels.length == 0 ) {
			System.out.println("No devices available.");
			System.exit(0);
		}
		
		System.out.println("Channel count: " + channels.length);
		for (String s : channels) {
			System.out.println(" channel=" + s);
		}

		ContAcqVoltage acq = new ContAcqVoltage();

		String channel = channels[0];

		acq.init(channel, -10.0, 10.0, 500, 200, 100);

		try {
			Thread.sleep(6000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return;
	}

}
