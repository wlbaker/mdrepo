package idea.ct;

import icuInterface.ConnectionStatus;
import idea.intf.AdapterInterface;
import idea.schema.rp.RpDevice;

public interface CtInterface {

	public void init(RpDevice dev) throws Exception ;
	// public void refresh() throws Exception ;
	public void release();
	
	public void panelToModel(RpDevice dev);

	public void handleConnectionEvent(RpDevice conf, AdapterInterface driver, ConnectionStatus status);
	
}
