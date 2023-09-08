package idea.persistence;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpSubject;

import java.io.IOException;


/*
 * FIXME: Merge with IDEATransferInterface
 */
public interface PiSubjectImporter extends StreamProducer {

	void connect() throws IOException ;
	void disconnect();

	long getTimeInMillis();

	PersistentItem next() throws IOException;

	RpSubject getSubjectInfo();

	PiDatastreamImporter[] getDevices();
	ArchiveMetaData getMetaData() throws IOException;
	
	public void rewind() throws IOException;
	public void seek(long tm) throws IOException;

	PiDatastreamImporter getDatastreamImporter( String name, StreamID sid );

	

}
