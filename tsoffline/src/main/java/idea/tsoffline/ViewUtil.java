package idea.tsoffline;

import java.awt.BorderLayout;
import java.awt.Color;

import javax.swing.JTabbedPane;

import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.analysis.AnalysisFactory;
import idea.analysis.AnalysisFrame;
import idea.analysis.AnalysisPanelInterface;
import idea.analysis.AttractorAnalysisPanel;
import idea.tsoffline.analysis.ComplexityAnalysisPanel;
import idea.tsoffline.analysis.FrequencyAnalysisPanel;
import idea.tsoffline.analysis.HRAsymmetryAnalysisPanel;
import idea.tsoffline.analysis.MSEAnalysisPanel;
import idea.tsoffline.canvas.PLayerStream;
import idea.tsoffline.canvas.TsBaseCanvas;
import idea.tsoffline.model.OfflineSignal;

@Slf4j
public class ViewUtil {


	public static void doAnalysis(TsBaseCanvas canvas, final long startTimeMs, RpStudy study, RpAnalysis anal, Color color) throws Error {
		try {
			_doAnalysis(canvas, startTimeMs, study, anal, color);
		} catch (Throwable e) {
			throw new Error(e);
		}
		
	}
	private static void _doAnalysis(TsBaseCanvas canvas, final long startTimeMs, RpStudy study, RpAnalysis anal, Color color) throws Exception {
		String name = anal.getName();


		if (true) {
			log.error("FIXME: this will fail...loc vs code vs name");
			canvas.removeAnnotationLayer(name);
			final HPSplitableLayer outputLayer = canvas.addAnnotationLayer(name, color, anal.getName() );

			StreamProducer dataSource = AnalysisFactory.buildAnalysisProducer(null, study, anal);
			if( dataSource == null ) {
				throw new RuntimeException("filter not found for analysis: " + anal);
			}
			StreamConsumer filter_in = (StreamConsumer) dataSource;
			StringStringMap params = anal.getParam();
			String sigLoc = params.get("loc");
			String sigName = params.get("code");
			HPSplitableLayer signal = canvas.findSignal(sigLoc);
			if( signal == null ) {
				log.error("Could not find signal: {}", sigLoc);
				return;
			}
			
			PLayerStream importer = new PLayerStream(signal, startTimeMs, 'W');

			importer.rewind();
			importer.seek(startTimeMs );
			PersistentItem item;

			dataSource.addStreamListener(null, new StreamConsumer() {

				@Override
				public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
					AppModel.addAnnotation(outputLayer, item, false);
				}
			});
			
			outputLayer.setVisible( false );
			while ((item = importer.next()) != null) {
				StreamID sid = StreamID.fromCode(item.getStreamID());
				filter_in.streamEvent(0, importer, sid, item);
			}
			outputLayer.setVisible(true);
			
			System.out.println("done w analysis");

		} else if (name.startsWith("HRC")) {
			GuiUtil.showMessage("[ViewUtil] HRC NO LONGER HERE, use doStandardAnalysis");
			// doStandardAnalysis( window );
		} else {
			// String cl = anal.getAnalysisClass();
			// JPanel panel = AnalysisFactory.buildAnalysisPanel( cl );
			if (anal == null) {
				// ignore
			} else {
				// if (sig.getSignalLayer() == null) {
				// GuiUtil.showMessage(sig.getDescription() + ": Signal has not
				// been loaded.");
				// return;
				// }
				String clazz = anal.getAnalysisClass();
				// JPanel panel = AnalysisFactory.buildAnalysisPanel(clazz);
				System.err.println("builder failing....hardcoding");
				final AttractorAnalysisPanel panel = new AttractorAnalysisPanel();

				AnalysisFrame frame = new AnalysisFrame("Standford Attractor Visualization");
				frame.getContentPane().add(panel, BorderLayout.CENTER);

				// Object[] options = new Object[] {};
				// JOptionPane op = new JOptionPane(panel,
				// JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null,
				// options);
				// JDialog dlg = op.createDialog(AppFrame.getInstance(),
				// anal.getName());
				// GuiUtil.initModalDialog(dlg, panel);
				// dlg.setResizable(true);

				if (panel instanceof AnalysisPanelInterface) {
					AnalysisPanelInterface f = (AnalysisPanelInterface) panel;
					log.error("FIXME: f.connect() --> this function no longer here!");
				}

				// dlg.setVisible(true);
				frame.pack();
				System.out.println("starting next frame visible");
				frame.setVisible(true);
				System.out.println("completing next frame visible");
			}

		}
	}

	public static void doStandardAnalysis(JTabbedPane tabber, long startTime, long endTime, OfflineSignal sig) {

		double[][] data = sig.getDataInRange(startTime, endTime);
		double[] dd = data[1];
		int[] ddii = new int[dd.length];
		for (int pos = 0; pos < dd.length; pos++) {
			ddii[pos] = (int) dd[pos];
			pos++;
		}

		ComplexityAnalysisPanel c = new ComplexityAnalysisPanel();
		tabber.addTab("HRC", c);

		c.process(startTime, endTime, dd);

		FrequencyAnalysisPanel f = new FrequencyAnalysisPanel();
		tabber.addTab("HRV", f);
		f.process(startTime, endTime, dd);

		MSEAnalysisPanel mse = new MSEAnalysisPanel();
		tabber.addTab("MSE", mse);
		mse.process(startTime, endTime, ddii);

		HRAsymmetryAnalysisPanel hra = new HRAsymmetryAnalysisPanel();
		tabber.addTab("HRA", hra);
		mse.process(startTime, endTime, ddii);

	}

}
