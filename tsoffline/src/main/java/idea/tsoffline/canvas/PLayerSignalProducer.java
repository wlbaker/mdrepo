package idea.tsoffline.canvas;

import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.piccolo2d.PCamera;

import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.HPSplitableLayer;

@Slf4j
public class PLayerSignalProducer extends AbstractStreamProducer implements PiSubjectImporter {

	private PersistentItem[] arNext;
	private String[] arKey;
	private Map<String, PLayerStream> importers = new HashMap<>();
	private TsPSwingCanvas canvas;
	private long startTime;
	

	public PLayerSignalProducer(TsPSwingCanvas canvas ) {
		this.canvas = canvas;
		startTime = canvas.getStartTime();
		List<PCamera> cams = canvas.getBandCameras();
		for( PCamera cam : cams ) {
			List<HPSplitableLayer> layers = cam.getLayersReference();
			addSignals( layers );
		}
	}

	private void addSignals(List<HPSplitableLayer> layers) {

		for( HPSplitableLayer layer : layers) {

			int sid_code = 0;
			Object sid = layer.getAttribute("sid");
			if (sid != null) {
				String s_sid = (String) sid;
				if (s_sid.length() > 0) {
					sid_code = s_sid.getBytes()[0];
				}
			}

			String key = "" + (char) sid_code;
			PLayerStream importer = importers.get(key);
			if (importer == null) {
				importer = new PLayerStream(layer, startTime, sid_code);
				importers.put(key, importer);
			}
		}
	}

	@Override
	public RpDevice getConfiguration() {
		
		log.error("MORE TO DO HERE -- working on HDF5 exporter.");
		RpDevice conf = new RpDevice();
		for (Object key : importers.keySet() ) {
			PLayerStream pLayerStream = importers.get(key);
			RpStream str = new RpStream();
			str.setName( pLayerStream.getName() );
			str.getMetric( ).addAll( pLayerStream.getMetrics() );
			// str.setModel( importer.getModel(sid));
			conf.getStreams().add( str );
		}
		conf.setName("CanvasExporter");
		conf.setDriverName( PLayerSignalProducer.class.getCanonicalName() );
		return conf;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void connect() throws IOException {
		int i = 0;
		arNext = new PersistentItem[importers.size()];
		arKey = new String[importers.size()];

		for (String key : importers.keySet()) {
			PLayerStream dev = importers.get(key);
			dev.connect();
			arNext[i] = dev.next();
			arKey[i] = key;
			i++;
		}
	}

	@Override
	public void disconnect() {
		for (String key : importers.keySet()) {
			PLayerStream dev = importers.get(key);
			dev.disconnect();
		}
		arNext = null;
	}

	@Override
	public long getTimeInMillis() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public PersistentItem next() throws IOException {

		if( arNext == null ) {
			log.error("importer not connected");
			return null;
		}
		PersistentItem ret = null;
		long nextTime = Long.MAX_VALUE;
		int nextPos = 0;
		for (int idx = 0; idx < arNext.length; idx++) {
			PersistentItem m = arNext[idx];
			if (m != null && m.getTime() < nextTime) {
				nextPos = idx;
				nextTime = m.getTime();
				ret = m;
			}
		}

		try {
			if (ret != null) { // if ret is null, then all the importers are out
				// of messages
				String key = arKey[nextPos];
				PiDatastreamImporter importer = importers.get(key);
				if (importer != null) {
					try {
						arNext[nextPos] = importer.next();
					} catch (NullPointerException nex) {
						nex.printStackTrace();
					}
				}
			}
		} catch (IOException e) {
			throw e;
		} catch (Exception e) {
			throw new IOException(e);
		}

		// ret.setTime( initialTime + ret.getTime() );
		return ret;
	}

	@Override
	public RpSubject getSubjectInfo() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PiDatastreamImporter[] getDevices() {
		PiDatastreamImporter[] tableIntfs = new PiDatastreamImporter[importers.size()];

		int i = 0;
		Iterator<String> itter = importers.keySet().iterator();
		while (itter.hasNext()) {
			String key = itter.next();
			tableIntfs[i++] = importers.get(key);
		}
		return tableIntfs;
	}

	@Override
	public ArchiveMetaData getMetaData() throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void rewind() throws IOException {
		int idx = 0;
		for (String key : importers.keySet()) {
			PLayerStream dev = importers.get(key);
			dev.rewind();
			arNext[idx++] = dev.next();
		}

	}

	@Override
	public void seek(long tm) throws IOException {
		int idx = 0;
		for (String key : importers.keySet()) {
			PLayerStream dev = importers.get(key);
			dev.seek(tm);
			arNext[idx++] = dev.next();
		}

	}

	@Override
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid) {
		// TODO Auto-generated method stub
		return null;
	}

}
