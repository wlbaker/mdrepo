package ni.DAQmxBase;

import ni.DAQcommon.DaqStream;
import ni.DAQcommon.Task;

public class BaseDaqStream extends DaqStream {

	BaseDaqStream( Task task ) {
		super(task);
	}
	
    public native void configureInputBuffer(long bufferSize);
    public native void configureOutputBuffer(long bufferSize);
    
 	
}
