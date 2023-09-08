package ni.DAQmx;

import ni.DAQcommon.AIChannelCollection;
import ni.DAQcommon.AOChannelCollection;
import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQcommon.AnalogMultiChannelWriter;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.Task;
import ni.DAQcommon.Timing;
import ni.DAQmxBase.BaseDaqStream;

public class MxTask extends Task {
	
	public MxTask(String name) {
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
		return new MxTiming( taskHandle );
	}

	@Override
	protected AIChannelCollection createAIChannelCollection(long taskHandle) {
		return new MxAIChannelCollection( taskHandle );
	}

	@Override
	protected AOChannelCollection createAOChannelCollection(long taskHandle) {
		return new MxAOChannelCollection( taskHandle );
	}

	public AnalogMultiChannelReader createAnalogMultiChannelReader() {
		return new MxAnalogMultiChannelReader( getStream() );
	}

	@Override
	protected DaqStream createDaqStream() {
		return new MxDaqStream( this );
	}

	@Override
	public AnalogMultiChannelWriter createAnalogMultiChannelWriter() {
		// TODO Auto-generated method stub
		return null;
	}



}
