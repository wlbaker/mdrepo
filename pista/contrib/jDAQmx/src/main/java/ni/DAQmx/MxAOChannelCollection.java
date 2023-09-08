package ni.DAQmx;

import ni.DAQcommon.AIChannel;
import ni.DAQcommon.AIChannelCollection;
import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.AOChannel;
import ni.DAQcommon.AOChannelCollection;
import ni.DAQcommon.AOTerminalConfiguration;
import ni.DAQcommon.AOVoltageUnits;
import ni.DAQcommon.DaqException;

public class MxAOChannelCollection extends AOChannelCollection {

	MxAOChannelCollection(long taskHandle) {
		super(taskHandle);
	}

	@Override
    public AOChannel createVoltageChannel(String physicalChannelName, String nameToAssignChannel, AOTerminalConfiguration terminalConfiguration, double minimumValue, double maximumValue, AOVoltageUnits units) throws DaqException {
    	return new MxAOChannel( _taskHandle, physicalChannelName, nameToAssignChannel, terminalConfiguration, minimumValue, maximumValue, units );
    }

}
