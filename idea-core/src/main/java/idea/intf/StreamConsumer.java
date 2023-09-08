package idea.intf;

import idea.message.StreamID;
import idea.model.PersistentItem;

import java.util.EventListener;

/**
 * SignalConsumer is a simple interface which consists of a single method that is called 
 * for any registered event.
 * 
 * @author william.l.baker2
 *
 */
public interface StreamConsumer extends EventListener {
	
	public void streamEvent( int jobID, StreamProducer source, StreamID sid, PersistentItem item );
}
