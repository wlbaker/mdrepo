package idea.persistence;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

import java.io.IOException;

public interface PiDatastreamImporter extends StreamProducer {

	public PersistentItem next() throws 	IOException;

	public void rewind() throws IOException;

	public ArchiveMetaData getMeta() throws IOException;

	public void seek(long startTime) throws IOException;

	
	// subset of functions needed from AdapterInterface
	public void connect() throws IOException;
	public void disconnect() throws IOException;
	//public DeviceConfiguration getConfiguration();
	
	public String getName();

	public Class<? extends PersistentItem> getModel(StreamID sid);

	public StreamID [] getStreams();

}
