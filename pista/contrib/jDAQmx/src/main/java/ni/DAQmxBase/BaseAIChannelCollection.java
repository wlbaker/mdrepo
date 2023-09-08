package ni.DAQmxBase;

import ni.DAQcommon.AIChannel;
import ni.DAQcommon.AIChannelCollection;
import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.DaqException;

public class BaseAIChannelCollection extends AIChannelCollection {

	public BaseAIChannelCollection(long taskHandle) {
		super(taskHandle);
	}

	@Override
	public AIChannel createVoltageChannel(String physicalChannelName,
			String nameToAssignChannel,
			AITerminalConfiguration terminalConfiguration, double minimumValue,
			double maximumValue, AIVoltageUnits units) throws DaqException {
		
		
		BaseAIChannel ch = new BaseAIChannel(this._taskHandle,  // task 
				physicalChannelName,   // physical ch
				nameToAssignChannel,   // ch name
				terminalConfiguration, // terminal
				minimumValue,          // min
				maximumValue,          // max
				units);                // units
		addChannel(ch);
		
		return ch;
	}

}
