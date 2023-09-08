package idea.intf;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.message.StreamID;
import idea.model.PersistentItem;

import java.io.IOException;

/**
 * The primary class for asynchronous signal producers.
 *  
 * @author william.l.baker2
 *
 */
public interface StreamProducerz {

	public void addStreamListener(StreamID sid, StreamConsumer l);
	public void removeStreamListener(StreamConsumer l);
	
	public PersistentItem getEvent(StreamID sid);

	public void requestCapabilities() throws IOException;
	
	public DeviceCapabilities getStaticCapabilities();
	public DeviceConfiguration getConfiguration();

}
