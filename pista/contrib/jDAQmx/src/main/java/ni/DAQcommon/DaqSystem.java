package ni.DAQcommon;

import ni.DAQmx.MxLocal;
import ni.DAQmxBase.BaseLocal;

public class DaqSystem {
	
	public static Local getBaseLocal() {
		return BaseLocal.getInstance();
	}
	
	public static Local getMxLocal() {
		return MxLocal.getInstance();
	}

	
	/*???
    public String[] getDevices();
    public long getDriverMajorVersion();
    public long getDriverMinorVersion();
    public long getDriverUpdateVersion();
    public String[] getGlobalChannels();
    public DaqWarningEventArgs getLastDaqWarning();
    public static DaqSystem getLocal(); ????
	*/
}
