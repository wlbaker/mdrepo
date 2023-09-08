package ni.DAQmxBase;

import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.IAsyncResult;
import ni.DAQcommon.Task;

public class BaseAnalogMultiChannelReader  extends AnalogMultiChannelReader {

	Task _task;

	class ZZReader implements Runnable {

		int samplesPerChannel;
		AsyncCallback callback;
		Object state;
		
		ZZReader( int samplesPerChannel, AsyncCallback callback, Object state ) {
			this.samplesPerChannel = samplesPerChannel;
			this.callback = callback;
			this.state = state;
		}
		
		@Override

		public void run() {
			try {
				while( true ) {
					_run();
					
				}
			} catch (DaqException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		public void _run() throws DaqException {
			BaseAsyncResult result = new BaseAsyncResult();
			System.out.println( "java asking to read waveform at samples=" + samplesPerChannel );
			result.setWaveform( readWaveform( samplesPerChannel ) );
			callback.asyncCallback(result );
		}
		
	}
	
	BaseAnalogMultiChannelReader( Task task ) {
    	super( task.getStream() );
    	this._task = task;
	}

	private native AnalogWaveform[] readWaveform(int samplesPerChannel, int channels)
	throws DaqException;
	
	public AnalogWaveform[] readWaveform(int samplesPerChannel) throws DaqException {
		return readWaveform(samplesPerChannel, stream.getNumberOfInputChannels() );
	}

	public native double[][] readMultiSample(int samplesPerChannel)
			throws DaqException;

	public native double[] readSingleSample() throws DaqException;

	public IAsyncResult beginReadWaveform(int samplesPerChannel,
			AsyncCallback callback, Object state) {
		
		System.out.println( "task=" + _task );
		_task.start();
		
		ZZReader zrt = new ZZReader(samplesPerChannel, callback, state);
		
		Thread t = new Thread(zrt);
		t.start();
		
		return null;

	}

	public AnalogWaveform[] endReadWaveform(IAsyncResult asyncResult)
			throws DaqException {
		
		BaseAsyncResult r = (BaseAsyncResult) asyncResult;
		
		return r.getWaveform();
	}

	/*
	 * ?? public virtual bool [is|set]SynchronizeCallbacks
	 * 
	 * public IAsyncResult beginMemoryOptimizedReadWaveform(int
	 * samplesPerChannel, AsyncCallback callback, object state,
	 * AnalogWaveform<double>[] data);
	 */
	// public native IAsyncResult beginReadMultiSample(int samplesPerChannel,
	// AsyncCallback callback, Object state);
	/*
	 * public IAsyncResult beginReadSingleSample(AsyncCallback callback, object
	 * state); public double[][] endReadMultiSample(IAsyncResult asyncResult);
	 * public double[] endReadSingleSample(IAsyncResult asyncResult); public
	 * AnalogWaveform<double>[] memoryOptimizedReadWaveform(int
	 * samplesPerChannel, AnalogWaveform<double>[] data);
	 */

}
