package ni.user;

import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.SampleClockActiveEdge;
import ni.DAQcommon.SampleQuantityMode;
import ni.DAQcommon.TaskAction;
import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQmxBase.BaseTask;

public class AcqMultVoltageSamples_SWTimed {
	private BaseTask myTask;
	private AnalogMultiChannelReader reader;

	public double [] readOneSample() {
		double[] data = null;

		try {
			data = reader.readSingleSample();


		} catch (DaqException exception) {
			// Display Errors
			exception.printStackTrace();

			// wlb runningTask = null;
			myTask.dispose();
		}

		return data;
	}

	private void init(String channel, double minValue, double maxValue,
			double sampleRate, int samples, int pretriggerSamples) {

		try {
			// Create the task
			myTask = new BaseTask( "" );

			// Create channels
			myTask.getAIChannels().createVoltageChannel(channel, "",
					AITerminalConfiguration.DEFAULT, minValue, maxValue,
					AIVoltageUnits.Volts);

			myTask.getTiming().configureSampleClock("OnboardClock", 
					500.0, 
					SampleClockActiveEdge.Rising, 
					SampleQuantityMode.FiniteSamples, 
					250
					);
			
			// Verify the task
			myTask.control(TaskAction.Verify);

			myTask.start();
			
			reader = myTask.createAnalogMultiChannelReader();

		} catch (DaqException ex) {
			System.err.println(ex.getMessage());
			ex.printStackTrace();

			myTask.dispose();
			myTask = null;
		}

	}

	public static void main(String... args) {

		// System.load("/usr/lib/libstdc++.so.6");
		System.loadLibrary("jDAQmxBase");

		String[] channels = ni.DAQcommon.DaqSystem.getBaseLocal().getPhysicalChannels();

		AcqMultVoltageSamples_SWTimed acq = new AcqMultVoltageSamples_SWTimed();

		String channel = channels[0] + ", " + channels[1];

		System.out.println( "selecting data on channels: " + channels );
		
		acq.init(channel, -10.0, 10.0, 500, 200, 100);

		for (int i = 0; i < 100; i++) {
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			double[] data = acq.readOneSample();
			if( data == null ) {
				System.err.println( "DATA NOT AVAILABLE");
				break;
			}
			
			for( int ii=0; ii < data.length ; ii++ ) {
				System.out.println("data[" + ii + "] = " + data[ii]);
			}
			System.out.println();

		}

		return;
	}

}
