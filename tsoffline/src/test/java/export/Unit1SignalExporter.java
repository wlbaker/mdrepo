package export;

import static org.junit.jupiter.api.Assertions.assertNotNull;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;

import org.piccolo2d.PLayer;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.SignalImporter;
import idea.tsoffline.canvas.PLayerSignalProducer;
import idea.tsoffline.canvas.TsPSwingCanvas;

@Slf4j
public class Unit1SignalExporter {
	public static void main(String[] args) throws IOException {
		// wow...don't know how to this easily!

		// File parentDir = new File("V:\\HiFi Research\\5. ISR - (Baker &
		// Salinas)\\BAMC 485 (Normal) R-Ex");
		File parentDir = new File("U:\\ISR_PROTOCOL_A_17_01_RUBAL\\Data\\Normal (Active Duty)\\.BAMC 4685-(35yo M)");
		// File sessionFile = new File(parentDir, "4685(rest)_160830_1556_s_001.xml");
		File sessionFile = new File(parentDir, "4685_190517_1604_w_001.dat");

		PiSubjectImporter importer = PiImporterUtil.getImporterFromFile(sessionFile);
		assertNotNull(importer, "Could not open file.");

		importer.connect();

		TsPSwingCanvas canvas = new TsPSwingCanvas();

		PiDatastreamImporter dev = importer.getDevices()[0];
		Class<? extends PersistentItem> stream_cl = dev.getModel(StreamID.WAVEFORM);

		RpMetric[] metrics = IntfUtil.getMetrics(stream_cl);
		List<RpMetric> sigs = Arrays.asList(metrics);

		SignalImporter simp = new SignalImporter();

		HPSplitableLayer[] layers = simp.loadSignal(dev, dev.getName(), StreamID.WAVEFORM, sigs, 0, 0);

		for (HPSplitableLayer layer : layers) {
			canvas.addDataLayer(0, layer);
		}

		PLayerSignalProducer canv_importer = new PLayerSignalProducer(canvas);
		// canv_importer.addOfflineDevices(0, Arrays.asList(devs) );
		// canv_importer.addOfflineSignals(canvas.getStartTime(), null);
		canv_importer.connect();
		canv_importer.rewind();
		PersistentItem block;
		while ((block = canv_importer.next()) != null) {
			System.out.println("# time: " + block.getTime() + "\t" + block.getStreamID() + "\t");
			metrics = block.getMetrics();
			Object[] arr = new Object[metrics.length];

			int max_size = 0;
			for (int idx = 0; idx < metrics.length; idx++) {
				Object v = IntfUtil.getRawValue(block, metrics[idx]);
				arr[idx] = v;
				if (v instanceof float[]) {
					float[] ff = (float[]) v;
					max_size = Math.max(max_size, ff.length);
				} else if (v instanceof double[]) {
					double[] dd = (double[]) v;
					max_size = Math.max(max_size, dd.length);
				} else if (v instanceof int[]) {
					int[] ii = (int[]) v;
					max_size = Math.max(max_size, ii.length);
				} else {
					max_size = Math.max(max_size, 1);
				}
			}
			for (int i = 0; i < max_size; i++) {
				for (Object v : arr) {
					System.out.print("\t");
					if (v instanceof float[]) {
						float[] ff = (float[]) v;
						System.out.print((ff.length > i) ? ff[i] : "");
					} else if (v instanceof double[]) {
						double[] dd = (double[]) v;
						System.out.print((dd.length > i) ? dd[i] : "");
					} else if (v instanceof int[]) {
						int[] ii = (int[]) v;
						System.out.print((ii.length > i) ? ii[i] : "");
					} else {
						if (i == 0) {
							System.out.print(v);
						}
					}
				}
				System.out.println();
			}
		}
	}

}
