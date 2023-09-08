package ni.DAQmxBase;

import java.util.TimerTask;

import ni.DAQcommon.AsyncCallback;
import ni.DAQcommon.IAsyncResult;

public class BBTimerTask extends TimerTask {

	private AsyncCallback callback;
	private Object state;
	private long   _taskHandle;

	public BBTimerTask(long _taskHandle, AsyncCallback callback, Object state) {
		this.callback = callback;
		this.state = state;
		this._taskHandle = _taskHandle;
	}

	@Override
	public void run() {
		IAsyncResult result = new InternalAsyncResult( _taskHandle );
		callback.asyncCallback( result );
		
	}

}
