package ni.DAQmx;

import ni.DAQcommon.DaqStream;
import ni.DAQcommon.Task;

public class MxDaqStream extends DaqStream {

	MxDaqStream( Task task ) {
		super(task);
	}
	
    public native void configureInputBuffer(long bufferSize);
    public native void configureOutputBuffer(long bufferSize);
}
