package ni.DAQmx;

import ni.DAQcommon.Local;
import ni.DAQmxBase.BaseLocal;

public class MxLocal extends Local {

    public String[] getTasks() { return null; }
    public native String[] getPhysicalChannels( ); // PhysicalChannelTypes physicalChannelTypes, PhysicalChannelAccess physicalChannelAccess);

	private static MxLocal local;
	
	public static Local getInstance() {
		if( local == null ) {
			local = new MxLocal();
		}
		return local;
	}
	    	
}
