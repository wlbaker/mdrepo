package idea.intf;

import java.io.IOException;
import java.util.Date;

import icuInterface.ConnectionStatus;
import idea.schema.rp.RpDevice;

public interface IDEAClient extends StreamProducer {

	/*
	 * local control
	 */
	void setAddress(String text);
	String getAddress();
	
	void start()  throws IOException;
	void shutdown();
	
	/*
	 * messages to remote machine
	 */
	public void requestPurge( int act )  throws IOException;  // purge all existing data
	public boolean requestLogin(int req_id, String user, String pwd)  throws IOException;
	@Override
	void requestCapabilities() throws IOException;
	public void requestStartup() throws IOException;
	public void requestStatus() throws IOException;
	public void requestEcho() throws IOException;
	public void requestPing() throws IOException;
	public void requestShutdown()  throws IOException;

	/*
	 * Management interface
	 */
	public void requestMgmtAddDevice(RpDevice dev)  throws IOException;
	public void requestMgmtRemoveDevice(String name)  throws IOException;

	/*
	 * Data requests
	 */
	public void subscribe(String key);
	public void unsubscribe(String key);
	/*
	 * local information management
	 */
	//StreamProducer getProxy(String name);
	StreamProducer [] getProxies();
	IDEATransferInterface createTransferRequest(int jobId, Date dtStart, Date dtEnd, RpDevice dev, int i);

}
