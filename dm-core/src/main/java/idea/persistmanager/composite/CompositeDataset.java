package idea.persistmanager.composite;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import icuInterface.events.ManagementEvent;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class CompositeDataset extends AbstractStreamProducer implements PiDatastreamImporter {
	int curr_idx = 0;
	PiDatastreamImporter curr;
	List<PiDatastreamImporter> datasets = new LinkedList<PiDatastreamImporter>();

	@Override
	public PersistentItem getEvent(StreamID sid) {
		return curr.getEvent(sid);
	}

	@Override
	public void requestCapabilities() throws IOException {
		curr.requestCapabilities();
	}

	@Override
	public RpDevice getStaticCapabilities() {
		return curr.getStaticCapabilities();
	}

	@Override
	public RpDevice getConfiguration() {
		return curr.getConfiguration();
	}

	@Override
	public PersistentItem next() throws IOException {
		PersistentItem item = curr.next();
		while( item == null ) {
			_chrono_next_file();
			if( curr == null ) {
				break;
			}
			item = curr.next();
		}
		return item;
	}

	private void _chrono_next_file() {
		curr_idx++;
		if( curr_idx < datasets.size() ) {
			curr = datasets.get(curr_idx);
		} else {
			curr_idx = datasets.size();
			curr = null;
		}
		if( curr != null ) {
			RpDevice dev = curr.getConfiguration();
			fireManagementEvent(this, ManagementEvent.DEV_CHANGE, 0, dev);
		}
	}

	@Override
	public void rewind() throws IOException {
		for( PiDatastreamImporter ds : datasets ) {
			ds.rewind();
		}
		curr_idx = 0;
		curr = datasets.get(0);
	}

	@Override
	public ArchiveMetaData getMeta() throws IOException {
		ArchiveMetaData meta = null;
		for( PiDatastreamImporter dataset : datasets ) {
			ArchiveMetaData rev = dataset.getMeta();
			if( meta == null ) {
				meta = rev;
			} else {
				meta.add(rev);
			}
			
		}
		return meta;
	}

	@Override
	public void seek(long startTime) throws IOException {
		for( PiDatastreamImporter ds : datasets ) {
			ds.seek(startTime);
		}
	}

	@Override
	public void connect() throws IOException {
		log.error("connect: should not be called here");
	}

	@Override
	public void disconnect() throws IOException {
		log.error("disconnect: should not be called here");
	}

	@Override
	public String getName() {
		return curr.getName();
	}

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {
		log.error("getModel...no reason to use the composite function, and return value is unreliable");
		return curr.getModel(sid);
	}

	@Override
	public StreamID[] getStreams() {
		log.error("getStreams...no reason to use the composite function, and return value is unreliable");
		return curr.getStreams();
	}
	
	public void addDataset(PiDatastreamImporter ds) {
		// WARNING: assuming datasets are added in chronological order
		datasets.add(ds);
		if( curr == null ) {
			curr = ds;
		}
	}
}
