package idea.datamanager;

import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class CompositeExporter implements PiSubjectExporter {

	boolean connected = false;
	List<PiSubjectExporter> exporters;

	public CompositeExporter() {

		reset();
	}

	public void addExporter(PiSubjectExporter exporter) {
		exporters.add(exporter);
	}

	@Override
	public void addDevice(RpDevice conf) throws IOException {
		for (PiSubjectExporter x : exporters) {
			x.addDevice(conf);
		}
	}

	@Override
	public void connect() throws IOException {
		for (PiSubjectExporter x : exporters) {
			x.connect();
		}
		connected = true;
	}

	@Override
	public void disconnect() throws IOException {
		if (connected) {
			connected = false;
			for (PiSubjectExporter x : exporters) {
				x.disconnect();
			}
		}
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (connected) {
			for (PiSubjectExporter x : exporters) {
				x.streamEvent(jobID, source, sid, item);
			}

		}
	}

	@Override
	public void setHeader(RpSubject header) {
		for (PiSubjectExporter x : exporters) {
			x.setHeader(header);
		}

	}

	@Override
	public void setDestination(File archiveDir) {

		// this code could fail if archiveDir exists but is not a directory here.
		if (archiveDir.exists() == false) {
			archiveDir.mkdirs();
		}

		for (PiSubjectExporter x : exporters) {
			x.setDestination(archiveDir);
		}

	}

	public void reset() {
		exporters = new LinkedList<PiSubjectExporter>();
	}

}
