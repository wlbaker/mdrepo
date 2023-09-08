package idea.persistmanager.text;

import java.io.BufferedReader;
import java.io.IOException;

import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;
import idea.persistence.PiDatastreamImporter;

/**
 * This importer was specifically designed for copy-paste from excel, but it is a
 * general purpose importer supporting comma or text delimited text streams from
 * any source. 
 * 
 * @author william.l.baker2
 *
 */
public class TextStreamImporter extends AbstractStreamProducer implements PiSubjectImporter {

	private BufferedReader reader;
	private RpDevice dev;
	private long tm;

	public TextStreamImporter( RpDevice dev, BufferedReader reader ) {
		this.reader = reader;
		this.dev = dev;
	}
	
	@Override
	public RpDevice getStaticCapabilities() {
		return dev;
	}

	@Override
	public void connect() throws IOException {
		// do nothing...stream cannot be opened
	}

	@Override
	public void disconnect() {
		// do nothing...stream will not be closed
	}

	@Override
	public long getTimeInMillis() {
		return tm;
	}

	@Override
	public PersistentItem next() throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public RpSubject getSubjectInfo() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PiDatastreamImporter[] getDevices() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArchiveMetaData getMetaData() throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void rewind() throws IOException {
		// doesnt hurt to try...but might not succeed
		reader.reset();
		tm = 0;  // if successful, reset time to 0...which might not be right
	}

	@Override
	public void seek(long tm) throws IOException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid) {
		// TODO Auto-generated method stub
		return null;
	}

}
