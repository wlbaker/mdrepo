package idea.datamanager.unused.devel;

import icuInterface.ConnectionStatus;
import icuInterface.message.AbstractBlock;
import icuInterface.message.AbstractItem;
import icuInterface.message.NumericBlock;
import icuInterface.message.NumericItem;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
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
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpSubject;

class ASCIIImportDevice extends AbstractStreamProducer implements PiSubjectImporter {

	FileReader strm;
	BufferedReader reader;

	private DeviceConfiguration conf;
	private LinkedList<RpMetric> waves;
	private RpMetric [] metrics;
	private File file;
	
	private long t0; // initial time

	ASCIIImportDevice(File file) throws IOException {
		this.file = file;

		rewind();

		conf = new DeviceConfiguration( H5Util.getClassFromDeviceName(file.getName()));
		conf.setName(file.getName());

		t0 = 0;
	}

	@Override
	public PersistentItem next() throws IOException {

		return getMetricBlock();
	}

	private PersistentItem getMetricBlock() throws IOException {

		return null;
	}

	@Override
	public void connect() throws IOException {
		rewind(); // this opens and reads the header
	}

	@Override
	public void disconnect() {
		// TODO Auto-generated method stub

	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	@Override
	public void rewind() throws IOException {

		close();

		strm = new FileReader(file);
		reader = new BufferedReader(strm);

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

	@Override
	public void seek(long startTime) throws IOException {
		rewind();

	}


	public void setStartTime(long timeInMillis) {
		t0 = timeInMillis;
	}

	@Override
	public RpDevice getStaticCapabilities() {
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
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid) {
		// TODO Auto-generated method stub
		return null;
	}

}
