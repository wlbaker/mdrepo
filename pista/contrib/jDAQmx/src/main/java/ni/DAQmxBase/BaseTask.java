package ni.DAQmxBase;

import ni.DAQcommon.AIChannelCollection;
import ni.DAQcommon.AOChannelCollection;
import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQcommon.AnalogMultiChannelWriter;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.Task;
import ni.DAQcommon.TaskAction;
import ni.DAQcommon.Timing;
import ni.DAQmx.MxAnalogMultiChannelReader;

public class BaseTask extends Task {
	
	public BaseTask(String name) {
		super(name);
	}

	protected native long createTask( String name );

	public native void start();

	public native void stop();

	@Override
	public void dispose() {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected Timing createTiming(long taskHandle) {
		return new BaseTiming( taskHandle );
	}

	@Override
	protected AIChannelCollection createAIChannelCollection(long taskHandle) {
		return new BaseAIChannelCollection( _taskHandle );
	}

	@Override
	public AnalogMultiChannelReader createAnalogMultiChannelReader() {
		return new BaseAnalogMultiChannelReader( this );
	}

	@Override
	protected DaqStream createDaqStream() {
		return new BaseDaqStream( this );
	}

	@Override
	protected AOChannelCollection createAOChannelCollection(long taskHandle) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public AnalogMultiChannelWriter createAnalogMultiChannelWriter() {
		// TODO Auto-generated method stub
		return null;
	}


}
