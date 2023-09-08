package ni.DAQcommon;

import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.IAsyncResult;

public abstract class AnalogMultiChannelReader {
 
	protected DaqStream stream;
	
    public AnalogMultiChannelReader(DaqStream stream) {
    	this.stream = stream;
    }
    
    /*
    public virtual bool SynchronizeCallbacks { get; set; }

    public IAsyncResult BeginMemoryOptimizedReadWaveform(int samplesPerChannel, AsyncCallback callback, object state, AnalogWaveform<double>[] data);
    */
    // public native IAsyncResult beginReadMultiSample(int samplesPerChannel, AsyncCallback callback, Object state);
    public abstract IAsyncResult beginReadWaveform(int samplesPerChannel, AsyncCallback callback, Object state);
    public abstract AnalogWaveform[] endReadWaveform(IAsyncResult asyncResult) throws DaqException;
    public abstract double[] readSingleSample() throws DaqException;

	public abstract AnalogWaveform[] readWaveform(int samplesPerChannel ) throws DaqException;
    
    // public native AnalogWaveform<Double>[] readWaveform(int samplesPerChannel);
    /*
    public IAsyncResult BeginReadSingleSample(AsyncCallback callback, object state);
    public double[,] EndReadMultiSample(IAsyncResult asyncResult);
    public double[] EndReadSingleSample(IAsyncResult asyncResult);
    public AnalogWaveform<double>[] MemoryOptimizedReadWaveform(int samplesPerChannel, AnalogWaveform<double>[] data);
    public double[,] ReadMultiSample(int samplesPerChannel);

    */
}
