package ni.DAQcommon;

import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.IAsyncResult;

public abstract class AnalogMultiChannelWriter {
 
	protected DaqStream stream;
	
    public AnalogMultiChannelWriter(DaqStream stream) {
    	this.stream = stream;
    }
    
    // public abstract IAsyncResult writeMultiSample(int samplesPerChannel, AsyncCallback callback, Object state);
    // public abstract IAsyncResult beginWriteMultiSample(int samplesPerChannel, AsyncCallback callback, Object state);
    // public abstract AnalogWaveform[] endWriteMultiSample(IAsyncResult asyncResult) throws DaqException;

	public abstract void writeSingleSample( boolean flag, float[] data ) throws DaqException;
	public abstract void waitUntilComplete( ) throws DaqException;
	// public abstract void writeMultiSample( AnalogWaveform[] data ) throws DaqException;
    
}
