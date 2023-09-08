package ni.DAQmx;

import ni.DAQcommon.AIChannel;
import ni.DAQcommon.AITerminalConfiguration;
import ni.DAQcommon.AIVoltageUnits;
import ni.DAQcommon.AOChannel;
import ni.DAQcommon.AOTerminalConfiguration;
import ni.DAQcommon.AOVoltageUnits;
import ni.DAQcommon.DaqException;

public class MxAOChannel extends AOChannel {

	protected MxAOChannel(long taskHandle, String channelName,
			String assignName, AOTerminalConfiguration terminalConfiguration,
			double minimumValue, double maximumValue, AOVoltageUnits units)
			throws DaqException {
		super(taskHandle, channelName, assignName, terminalConfiguration, minimumValue,
				maximumValue, units);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected native long createVoltageChannel(long taskHandle,
			String physicalChannelName, String nameToAssignChannel,
			AOTerminalConfiguration terminalConfiguration, double minimumValue,
			double maximumValue, AOVoltageUnits units) throws DaqException;

}
