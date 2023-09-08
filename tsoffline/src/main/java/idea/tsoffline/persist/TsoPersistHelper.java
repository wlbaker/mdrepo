package idea.tsoffline.persist;

import java.io.IOException;
import java.util.Collection;
import java.util.Date;
import java.util.List;
import java.util.ListIterator;

import org.piccolo2d.PNode;

import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistmanager.PiHdf5Exporter;
import idea.schema.rp.RpMetric;
import idea.GuiUtil;
import idea.tsoffline.model.OfflineDevice;
import idea.tsoffline.model.OfflineSignal;

public class TsoPersistHelper {
	public static void _saveEvents(PiHdf5Exporter exporter, List<OfflineSignal> infos) throws Exception {
		for (OfflineSignal info : infos) {
			ListIterator<PNode> it = info.getLayer().getChildrenIterator();
			while( it.hasNext() ) {
				PNode node = it.next();
				PersistentItem item = (PersistentItem) node.getAttribute("item");
				exporter.put(null, StreamID.ANNOTATION, item);
			}
		}
	}

	public static void _saveSession(PiHdf5Exporter exporter, List<OfflineSignal> infos, List<OfflineDevice> odevs ) throws Exception {

		//exporter.writeAttribute("dataFile", dataFile.getAbsolutePath());
		exporter.writeAttribute("fileType", "session");
		_saveFrames(exporter);
		_saveEvents(exporter, infos);

	}

	public static void _saveFrames(PiHdf5Exporter exporter) throws Exception {

		// H5DatastreamExporter dataset = exporter.addDataset("_frames", metrics, false, false);

		FrameItem block = new FrameItem();

		//		for (JInternalFrame jframe : frames) {
		//			if (jframe instanceof TsInternalFrame) {
		//				frame = (TsInternalFrame) jframe;
		//
		//				TimeseriesControl ctl = frame.getTimeseriesControl();
		//				OfflineSignal[] sigs = ctl.getSignals();
		//				long tmViewStart = ctl.getSelectionStartTime();
		//				long tmViewEnd = ctl.getSelectionEndTime();
		//
		//				viewStart.setValue(tmViewStart);
		//				viewEnd.setValue(tmViewEnd);
		//
		//				for (OfflineSignal sig : sigs) {
		//
		//					ImportDeviceInterface dev = sig.getImportDevice();
		//					tiDev.setValue(dev.getName());
		//					MetricDescription metric = sig.getDescription();
		//					tiLoc.setValue("" + metric.getLocation());
		//					tiName.setValue(metric.getName());
		//
		//					Date dtStart = ctl.getStartDate();
		//					Date dtEnd = ctl.getEndDate();
		//
		//					tsStart.setValue(dtStart.getTime());
		//					tsEnd.setValue(dtEnd.getTime());
		//
		//					niPos.setValue(1);
		//
		//					dataset.put(block);
		//				}
		//			}
		//		}

	}


	public static void _saveSignal(Date startTime, PiHdf5Exporter exporter, String pathName, OfflineSignal osig) throws IOException {

		String osig_name = pathName + "$" + osig.getLocation();

		if (osig.isDerived()) {
			RpMetric[] metrics = new RpMetric[] { osig };

			//H5DatastreamExporter ds = exporter.addDataset(md.getName(), metrics, true, false);
			//ds.writeAttribute("parent", osig_name);

			PersistentItem block = null;
			Collection<PNode> nodes = osig.getNodes();

			long ts = startTime.getTime();
			for (PNode node : nodes) {

				double sec_tm = node.getX();
				long ms_time = (long) (1000.0 * sec_tm);
				GuiUtil.showMessage("FIXME: block.setTm( new Date(ms_time + ts) );");
				exporter.put(null, StreamID.MEASUREMENT, block);
			}
		}

		GuiUtil.showMessage("Offline signals should be part of the device");
//		List<OfflineSignal> children = osig.getChildSignals();
//		if (children != null && children.size() > 0) {
//			for (OfflineSignal child : children) {
//				_saveSignal(exporter, osig_name, child); // recurse
//			}
//		}

	}

}
