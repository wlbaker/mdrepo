package ni.DAQmx;

import ni.DAQcommon.AIChannel;
import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.DaqException;

public class MxAIChannel extends AIChannel {

	protected MxAIChannel(long taskHandle, String channelName,
			String assignName, AITerminalConfiguration terminalConfiguration,
			double minimumValue, double maximumValue, AIVoltageUnits units)
			throws DaqException {
		super(taskHandle, channelName, assignName, terminalConfiguration, minimumValue,
				maximumValue, units);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected native long createVoltageChannel(long taskHandle,
			String physicalChannelName, String nameToAssignChannel,
			AITerminalConfiguration terminalConfiguration, double minimumValue,
			double maximumValue, AIVoltageUnits units) throws DaqException;

}
