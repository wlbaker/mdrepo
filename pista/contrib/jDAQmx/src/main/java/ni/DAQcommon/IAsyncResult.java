package ni.DAQcommon;

public interface IAsyncResult {
    Object getAsyncState();
    //wlb WaitHandle getAsyncWaitHandle();
    boolean getCompletedSynchronously();
    boolean getIsCompleted();
}
