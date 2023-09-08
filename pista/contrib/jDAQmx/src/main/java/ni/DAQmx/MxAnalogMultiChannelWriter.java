package ni.DAQmx;

import ni.DAQcommon.AnalogMultiChannelReader;
import ni.DAQcommon.AnalogMultiChannelWriter;
import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.DaqException;
import ni.DAQcommon.DaqStream;
import ni.DAQcommon.IAsyncResult;

public class MxAnalogMultiChannelWriter extends AnalogMultiChannelWriter {
 
	private int unused = 123;
	
    public MxAnalogMultiChannelWriter(DaqStream stream) {
    	super( stream );
    }
    
    @Override
    public void writeSingleSample( boolean flag, float[] data ) throws DaqException {
		// fixme: writing support not implemented
    }

    @Override
    public void waitUntilComplete( ) throws DaqException {
		// fixme: writing support not implemented
    }
    
}
