package ni.DAQmx;

import ni.DAQcommon.AIChannel;
import ni.DAQcommon.AIChannelCollection;
import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.DaqException;

public class MxAIChannelCollection extends AIChannelCollection {

	MxAIChannelCollection(long taskHandle) {
		super(taskHandle);
	}

	@Override
    public AIChannel createVoltageChannel(String physicalChannelName, String nameToAssignChannel, AITerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AIVoltageUnits units) throws DaqException {
    	return new MxAIChannel( _taskHandle, physicalChannelName, nameToAssignChannel, terminalConfiguration, minimumValue, maximumValue, units );
    }

}
