package idea.persistence;

import idea.intf.StreamConsumer;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

import java.io.File;
import java.io.IOException;

public interface PiSubjectExporter extends StreamConsumer  {
	
	void setHeader(RpSubject header);
	void setDestination(File archiveDir);

	void connect( ) throws IOException;
	void disconnect( ) throws IOException;
	
	void addDevice(RpDevice conf) throws IOException;
}
