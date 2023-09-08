package ni.user;

import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.DaqSystem;
import ni.DAQcommon.IAsyncResult;
import ni.DAQcommon.SampleClockActiveEdge;
import ni.DAQcommon.SampleQuantityMode;
import ni.DAQcommon.TaskAction;
import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQmx.MxTask;

public class ContAcqVoltageBase implements AsyncCallback {
	private MxTask myTask;
	private AnalogMultiChannelReader reader;
	private AnalogWaveform[] data;

	int samplesPerChannel = 500;  // WARNING: this number should come from somewhere else

	@Override
	public void asyncCallback(IAsyncResult result) {

		try {
			// wlb if (runningTask == result.AsyncState) {
			// Read the available data from the channels
			data = reader.endReadWaveform(result);

			// Plot your data here
			System.out.println("data[0] = " + data[0]);

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
			myTask.getAIChannels().createVoltageChannel( "Dev1/ai1", "zzai1",
					AITerminalConfiguration.DEFAULT, minValue, maxValue,
					AIVoltageUnits.Volts);

			myTask.getAIChannels().createVoltageChannel( "Dev1/ai2", "zzai2",
					AITerminalConfiguration.DEFAULT, minValue, maxValue,
					AIVoltageUnits.Volts);
			
			// Set up timing
			System.out.println("timing=" + myTask.getTiming() );
			myTask.getTiming().configureSampleClock("", sampleRate,
					SampleClockActiveEdge.Rising,
					SampleQuantityMode.ContinuousSamples, 1000);

			// Verify the task
			myTask.control(TaskAction.Verify);

			// Prepare pretrigger samples

			// data = new double[myTask.getAIChannels().getCount()][samples];

			DaqStream stream = myTask.getStream();
			
			stream.configureInputBuffer( 200000 );
			
			reader = myTask.createAnalogMultiChannelReader( );

			// System.out.println( "starting task");
			// myTask.start();
			
			System.out.println( "begin read waveform");
			reader.beginReadWaveform(samples, this, myTask);
			
		} catch (DaqException ex) {
			System.err.println(ex.getMessage());
			ex.printStackTrace();
			
			myTask.dispose();
			myTask = null;
		}

	}

//	private AnalogWaveform[] read(int samplesPerChannel ) throws DaqException {
//        data = reader.readWaveform(samplesPerChannel);
//		return data;
//	}

	public static void main(String... args) throws DaqException {

		System.out.println( "loading lib");
		System.loadLibrary("jDAQmx");
		// System.loadLibrary("jDAQmxBase");
		System.out.println( "loaded lib");

		String[] phy_channels = DaqSystem.getMxLocal().getPhysicalChannels(); // PhysicalChannelTypes.AI,
		// PhysicalChannelAccess.External);
		
		String [] channels = { phy_channels[0], phy_channels[1] };

		System.out.println("Channel count: " + channels.length);
		for (String s : channels) {
			System.out.println(" channel=" + s);
		}

		ContAcqVoltageBase acq = new ContAcqVoltageBase();

		String channel = channels[0];

		acq.init(channel, -10.0, 10.0, 500, 1100, 100);

		int totalRead = 0;
		int samplesPerChannel = 256;
		
//		//int timeout = 1000;
//		//int DAQmx_Val_GroupByChannel = 0;
//		//int DAQmx_Val_GroupByScanNumber = 1;
//		
//		for( int ii = 0; ii < 10 ; ii++ ) {
//
//			AnalogWaveform[] data = acq.read( samplesPerChannel );
//	        totalRead += samplesPerChannel;
//
//	        AnalogWaveform wave = data[0];
//	        double [] f = wave.getRawData();
//
//	        // Just print out the first 10 points of the last data read
//	        for (int i = 0; i < 10; ++i)
//	            System.out.format("data0[%d] = %f\tdata1[%d] = %f\n",i,f[2*i],i,f[2*i+1]);
//
//		}
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	    System.out.format("Acquired %d total samples.\n",totalRead);

		return;
	}


}
