package idea.datamanager.unused.devel;

import icuInterface.ConnectionStatus;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistence.PiDatastreamImporter;
import idea.persistmanager.hdf5.H5Util;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.EventObject;
import java.util.LinkedList;
import java.util.StringTokenizer;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;

class WFDBImportDevice  extends AbstractStreamProducer implements PiSubjectImporter {

	
	FileReader strm;
	BufferedReader reader;

	private RpDevice conf;
	private File file;
	
	private long t0; // initial time

	WFDBImportDevice(File file) throws IOException {
		this.file = file;

		rewind();

		conf = new RpDevice( );
		conf.setName(file.getName());
		conf.setDeviceClass( H5Util.getClassFromDeviceName(file.getName()) );

		t0 = 0;
	}


	@Override
	public void rewind()  {

		try {
			close();
			strm = new FileReader(file);
			reader = new BufferedReader(strm);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


	}

	void close() throws IOException {
		if (reader != null) {
			reader.close();
		}

		if (strm != null) {
			strm.close();
		}

	}

	public long getTimeInMillis() {
		long val = 0;

		return val;
	}

	public void setStartTime(long timeInMillis) {
		t0 = timeInMillis;
	}

	public File getFile() {
		return file;
	}

	public void addStream(String encoding) {
		// TODO Auto-generated method stub
		
	}


	@Override
	public RpDevice getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}


	@Override
	public void connect() throws IOException {
		// TODO Auto-generated method stub
		
	}


	@Override
	public void disconnect() {
		// TODO Auto-generated method stub
		
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

}
