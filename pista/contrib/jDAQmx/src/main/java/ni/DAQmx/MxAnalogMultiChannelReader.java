package ni.DAQmx;

import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.IAsyncResult;

public class MxAnalogMultiChannelReader extends AnalogMultiChannelReader {
 
	private int unused = 123;
	
    public MxAnalogMultiChannelReader(DaqStream stream) {
    	super( stream );
    }
    
    /*
    public virtual bool SynchronizeCallbacks { get; set; }

    public IAsyncResult BeginMemoryOptimizedReadWaveform(int samplesPerChannel, AsyncCallback callback, object state, AnalogWaveform<double>[] data);
    */
    // public native IAsyncResult beginReadMultiSample(int samplesPerChannel, AsyncCallback callback, Object state);
    public native IAsyncResult beginReadWaveform(int samplesPerChannel, AsyncCallback callback, Object state);
    public native AnalogWaveform[] endReadWaveform(IAsyncResult asyncResult) throws DaqException;
    public native double[] readSingleSample() throws DaqException;
    
    public native AnalogWaveform[] readWaveform(int samplesPerChannel);
    
    /*
    public IAsyncResult BeginReadSingleSample(AsyncCallback callback, object state);
    public double[,] EndReadMultiSample(IAsyncResult asyncResult);
    public double[] EndReadSingleSample(IAsyncResult asyncResult);
    public AnalogWaveform<double>[] MemoryOptimizedReadWaveform(int samplesPerChannel, AnalogWaveform<double>[] data);
    public double[,] ReadMultiSample(int samplesPerChannel);

    */
}
