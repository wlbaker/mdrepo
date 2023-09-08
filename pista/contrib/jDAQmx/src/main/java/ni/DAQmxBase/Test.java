package ni.DAQmxBase;

import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.IAsyncResult;
import ni.DAQcommon.SampleClockActiveEdge;
import ni.DAQcommon.SampleQuantityMode;
import ni.DAQcommon.TaskAction;
import ni.DAQcommon.AsyncCallback;

public class Test {

	private native long test0();
	private native long test1();
	private native long test2();

	public void test3() {
		BaseTask myTask;
		AnalogMultiChannelReader reader;
		AnalogWaveform[] data;
		
		String channel = "Dev1/ai0";
		float minValue = -10.0f;
		float maxValue = 10.0f;
	
		int sampleRate = 500;
		
		try {
			// Create the task
			myTask = new BaseTask("");

			// Create channels
			myTask.getAIChannels().createVoltageChannel(channel, "",
					AITerminalConfiguration.DEFAULT, minValue, maxValue,
					AIVoltageUnits.Volts);

			// Set up timing
			myTask.getTiming().configureSampleClock("", sampleRate,
					SampleClockActiveEdge.Rising,
					SampleQuantityMode.ContinuousSamples, 1000);

			System.out.println( "verify");
			// Verify the task
			myTask.control(TaskAction.Verify);

			// Prepare pretrigger samples

			// data = new double[myTask.getAIChannels().getCount()][samples];

			System.out.println( "get stream");
			DaqStream stream = myTask.getStream();
			stream.configureInputBuffer( 200000 );
			
			System.out.println( "create reader");
			reader = myTask.createAnalogMultiChannelReader( );

			System.out.println( "starting task");
			myTask.start();
			
			for( int i = 0; i < 3; i++ ) {
			
				AnalogWaveform[] wf = reader.readWaveform(100);
				double[] dat = wf[0].getRawData();
				for( int j=0; j < 4 ; j++ ) {
					System.out.print( dat[j] );
					System.out.print( "  " );
				}
				System.out.println();
			}
		} catch (DaqException ex) {
			System.err.println(ex.getMessage());
			ex.printStackTrace();
			
			myTask = null;
		}

	}
	
	public void test4() {
		BaseTask myTask;
		AnalogWaveform[] data;
		
		String channel = "Dev1/ai0";
		float minValue = -10.0f;
		float maxValue = 10.0f;
	
		int sampleRate = 500;
		
		try {
			// Create the task
			myTask = new BaseTask("");

			// Create channels
			myTask.getAIChannels().createVoltageChannel(channel, "",
					AITerminalConfiguration.DEFAULT, minValue, maxValue,
					AIVoltageUnits.Volts);

			// Set up timing
			myTask.getTiming().configureSampleClock("", sampleRate,
					SampleClockActiveEdge.Rising,
					SampleQuantityMode.ContinuousSamples, 1000);

			System.out.println( "verify");
			// Verify the task
			myTask.control(TaskAction.Verify);

			// Prepare pretrigger samples

			// data = new double[myTask.getAIChannels().getCount()][samples];

			System.out.println( "get stream");
			DaqStream stream = myTask.getStream();
			stream.configureInputBuffer( 200000 );
			
			System.out.println( "create reader");
			final AnalogMultiChannelReader reader = myTask.createAnalogMultiChannelReader( );

			System.out.println( "starting task");
			myTask.start();

			reader.beginReadWaveform( 100 , new AsyncCallback() {

				@Override
				public void asyncCallback(IAsyncResult result) {
					
					try {
						reader.endReadWaveform( result );
						AnalogWaveform[] wf = reader.readWaveform(100);
						double[] dat = wf[0].getRawData();
						for( int j=0; j < 4 ; j++ ) {
							System.out.print( dat[j] );
							System.out.print( "  " );
						}
						System.out.println();
					} catch (DaqException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
				} } , null);
			
		} catch (DaqException ex) {
			System.err.println(ex.getMessage());
			ex.printStackTrace();
			
			myTask = null;
		}

	}
	public static void main(String[] args) {
		System.out.println( "library: " + System.getProperty("java.library.path"));
		System.loadLibrary("jDAQmxBase");
		System.out.println( "t0 loadlibrary done");
		if( args.length == 0 ) {
			System.out.println( "Indicate test number to run.");
			System.exit(0);
		}
		
		Test t = new Test();
		
		for( String arg : args ) {
			if( arg.equals("1")) {
				t.test1();
				System.out.println("complete TEST1.");
			} else if ( arg.equals("3")) {
				t.test3();
				System.out.println("complete TEST3.");
			} else if ( arg.equals("4")) {
				t.test4();
				System.out.println("complete TEST4.");
			} else {
				System.out.println( "UNKNOWN TEST: " + arg );
			}
		}
	}

}
