package ni.DAQcommon;

import java.util.LinkedList;
import java.util.List;


import org.apache.commons.collections.list.*;

@SuppressWarnings("serial")
public abstract class AOChannelCollection {

	private LinkedList<AIChannel> ll;
	protected long _taskHandle;
	
	public AOChannelCollection( long taskHandle ) {
		this._taskHandle = taskHandle;
		ll = new LinkedList<AIChannel>();
	}
	
    public int getCount() { return ll.size(); };
	
    public abstract AOChannel createVoltageChannel(String physicalChannelName, String nameToAssignChannel, AOTerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AOVoltageUnits units) throws DaqException;

	/*
    public virtual AOChannel All { get; }
    public virtual bool IsSynchronized { get; }
    public virtual object SyncRoot { get; }
    public AOChannel CreateCurrentChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AOCurrentUnits units);
    public AOChannel CreateCurrentChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, string customScaleName);
    public AOChannel CreateFunctionGenerationChannel(string physicalChannelName, string nameToAssignChannel, AOFunctionGenerationType waveformType, double frequency, double amplitude);
    public AOChannel CreateFunctionGenerationChannel(string physicalChannelName, string nameToAssignChannel, AOFunctionGenerationType waveformType, double frequency, double amplitude, double offset);
    public AOChannel CreateVoltageChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, AOVoltageUnits units);
    public AOChannel CreateVoltageChannel(string physicalChannelName, string nameToAssignChannel, double minimumValue, double maximumValue, string customScaleName);
	*/

}
