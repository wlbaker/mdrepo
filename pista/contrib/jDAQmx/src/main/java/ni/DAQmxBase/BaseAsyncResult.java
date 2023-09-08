package ni.DAQmxBase;

import ni.DAQcommon.AnalogWaveform;
import ni.DAQcommon.IAsyncResult;

class BaseAsyncResult implements IAsyncResult {

	private AnalogWaveform[] wf;

	@Override
	public Object getAsyncState() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean getCompletedSynchronously() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean getIsCompleted() {
		// TODO Auto-generated method stub
		return false;
	}

	void setWaveform(AnalogWaveform[] wf) {
		this.wf = wf;
	}

	AnalogWaveform[] getWaveform() {
		return wf;
	}
	
}

