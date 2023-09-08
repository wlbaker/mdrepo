package idea.tsoffline.model;

import java.awt.Color;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.ColorManager;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;

@Slf4j
public class OfflineUtil {

	public static OfflineDevice[] loadOfflineDevices(PiSubjectImporter h5_study) throws IOException {

		int default_color_idx = 0;

		List<OfflineDevice> offline_devs = new LinkedList<OfflineDevice>();

		PiDatastreamImporter[] h5_devs = h5_study.getDevices();
		if (h5_devs == null) {
			return null;
		}

		for (PiDatastreamImporter h5_dev : h5_devs) {

			String name = h5_dev.getName();
			if (name == null) {
				name = "??null conf name";
			}

			OfflineDevice offline_dev = new OfflineDevice(name);
			offline_devs.add(offline_dev);

			h5_dev.rewind();
			h5_dev.getStreams(); // debug only
			for (StreamID sid : h5_dev.getStreams()) {
				Class<? extends PersistentItem> clazz = h5_dev.getModel(sid);
				if (clazz == null) {
					log.error("could not get class for stream: {}", sid);
					continue;
				}
				OfflineStream s = new OfflineStream(sid);
				offline_dev.addStream(s);
				RpMetric[] metrics = IntfUtil.getMetrics(clazz);
				int idx = 1;
				for (RpMetric metric : metrics) {
					System.err.println("h5_dev used to be second argument here...not needed?");
					HPSplitableLayer sig = new HPSplitableLayer(metric, TimeseriesType.TT_DATA);
					sig.setLayerSeq(100*idx);
					Color color = ColorManager.getDefaultColor(default_color_idx++);
					sig.setDefaultColor(color);
					sig.setPaint(color);
					sig.setSource( name );
					//s.addSignal(sig);
					idx++;
				}
			}
		}

		OfflineDevice[] devs = new OfflineDevice[offline_devs.size()];
		offline_devs.toArray(devs);

		return devs;
	}

}
