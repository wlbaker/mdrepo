package idea.datamanager.unused.devel;

/*
 * NOTE: Performance of RandomAccessFile is PITIFUL.  Avoid it.
 */

import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;

public class WFDBImporter  extends AbstractStreamProducer implements PiSubjectImporter {

	private LinkedList<WFDBImportDevice> devs;
	private File headerFile;

	public WFDBImporter( File headerFile ) {
		this.headerFile = headerFile;
	}

	@Override
	public void disconnect() {
		for (WFDBImportDevice dev : devs) {
			try {
				dev.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	@Override
	public long getTimeInMillis() {
		return devs.get(0).getTimeInMillis();
	}

	/*
	*/

	// public DeviceConfiguration[] getDeviceConfiguration() {
	// DeviceConfiguration[] ar = new DeviceConfiguration[1];
	// ar[0] = dev.getConfiguration();
	//
	// return ar;
	// }

	@Override
	public void connect() throws IOException {

		devs = new LinkedList<WFDBImportDevice>();

		FileReader strm = new FileReader( headerFile );
		BufferedReader reader = new BufferedReader( strm );
		
		boolean header = true;
		String line;
		int    datCount;
		int    freq;
		
		while( (line = reader.readLine()) != null ) {
			if( line.startsWith("#") ) {
				// ignore this line...comment
			} else if( header == true ) {
				String[] ar = line.split("[ \t]+");
				header = false;
				datCount = Integer.parseInt(ar[1]);
				freq = Integer.parseInt(ar[2]);
				
			} else {
				String[] ar = line.split("[ \t]+");
				File devFile = new File(ar[0]);
				String encoding = ar[1];
				
				WFDBImportDevice dev = getDevice( devFile );
				if( dev == null ) {
					dev = new WFDBImportDevice( devFile );
				}
				
				dev.addStream( encoding );
			}
		}
		
		for (WFDBImportDevice dev : devs) {
			dev.connect(); // ?? doesn't do anything now
		}
	}

	private WFDBImportDevice getDevice( File file ) {
		WFDBImportDevice found = null;
		for( WFDBImportDevice dev : devs ) {
			if( dev.getFile().equals(file)) {
				found = dev;
				break;
			}
		}
		
		return found;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
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
		// TODO Auto-generated method stub
		
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
