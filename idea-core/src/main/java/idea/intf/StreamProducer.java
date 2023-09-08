package idea.intf;

import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;

import java.io.IOException;

import icuInterface.ConnectionStatus;

/**
 * The primary class for asynchronous signal producers.
 *  
 * @author william.l.baker2
 *
 */
public interface StreamProducer {

	public void addStreamListener(StreamID sid, StreamConsumer l);
	public void removeStreamListener(StreamConsumer l);
	public void removeAllStreamListeners();
	
	public PersistentItem getEvent(StreamID sid);

	public void requestCapabilities() throws IOException;
	
	public RpDevice getStaticCapabilities();
	public RpDevice getConfiguration();
	
	public ConnectionStatus getStatus();

}
