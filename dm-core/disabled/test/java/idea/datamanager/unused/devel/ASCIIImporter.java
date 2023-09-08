package idea.datamanager.unused.devel;

import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistence.PiDatastreamImporter;

/*
 * NOTE: Performance of RandomAccessFile is PITIFUL.  Avoid it.
 */

import idea.persistence.StudyDefinition;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

import java.io.File;
import java.io.IOException;
import java.util.LinkedList;

import idea.intf.AbstractStreamProducer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

public class ASCIIImporter  extends AbstractStreamProducer implements PiSubjectImporter  {

	private LinkedList<ASCIIImportDevice> devs = new LinkedList<ASCIIImportDevice>();

	public ASCIIImporter() {

	}

	public ASCIIImportDevice addDevice(File file) {
		ASCIIImportDevice dev = null;
		
		try {

			dev = new ASCIIImportDevice(file);
			devs.add(dev);

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return dev;
	}

	@Override
	public void disconnect() {
		for (ASCIIImportDevice dev : devs) {
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
		for (ASCIIImportDevice dev : devs) {

			dev.connect(); // ?? doesn't do anything now
		}
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
	public void seek(long tm) throws IOException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void rewind() throws IOException {
		// TODO Auto-generated method stub
		
	}

//	public AbstractBlock next() throws IOException {
//
//		AbstractBlock message = devs.get(0).next();
//
//		if (message instanceof NumericBlock) {
//			fireNumericsEvent(this, (NumericBlock) message);
//		}
//
//		return message;
//	}

}
