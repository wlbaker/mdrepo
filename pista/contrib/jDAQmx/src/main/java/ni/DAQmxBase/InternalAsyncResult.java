package ni.DAQmxBase;

import ni.DAQcommon.IAsyncResult;

class InternalAsyncResult implements IAsyncResult {


	long _taskHandle;
	
	InternalAsyncResult( long _taskHandle ) {
		this._taskHandle = _taskHandle;		
	}

	@Override
	public Object getAsyncState() {
		// dunno
		return null;
	}

	@Override
	public boolean getCompletedSynchronously() {
		// I suspect this is used for the threads flag
		return false;
	}

	@Override
	public boolean getIsCompleted() {
		return true;
	}

}
