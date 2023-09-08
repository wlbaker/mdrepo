package ni.DAQmx;

import ni.DAQcommon.IAsyncResult;

class InternalAsyncResult implements IAsyncResult {

	long _callbackHandle;
	
	InternalAsyncResult( long callbackHandle ) {
		this._callbackHandle = callbackHandle;		
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
