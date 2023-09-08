package idea.tsoffline;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JProgressBar;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;
import javax.swing.SwingWorker.StateValue;

import idea.message.StreamID;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.tsoffline.canvas.TsPSwingCanvas;

@Slf4j
class LoadWorker extends SwingWorker<Integer, Void> {

	private PiDatastreamImporter dev;
	String devName;
	StreamID sid;
	private List<RpMetric> sigs;
	private TsPSwingCanvas canvas;
	private SignalImporter simp;
	private static long canvasStartTime;
	private static long canvasStopTime;

	public LoadWorker(SignalImporter simp, TsPSwingCanvas canvas, PiDatastreamImporter dev, String devName,
			StreamID sid, List<RpMetric> sigs) {

		canvasStartTime = canvas.getStartTime(); // for the initial canvas, this
													// is 0
		canvasStopTime = canvas.getStopTime(); // for the initial canvas, this
												// is 0

		this.simp = simp;
		this.canvas = canvas;
		this.dev = dev;
		this.devName = devName;
		this.sid = sid;
		this.sigs = sigs;

	}

	@Override
	protected Integer doInBackground() throws Exception {
		dev.addStreamListener(StreamID.MANAGEMENT, simp);
		try {

			HPSplitableLayer[] layers = simp.loadSignal(dev, devName, sid, sigs, canvasStartTime, canvasStopTime);

			if (layers != null) {
				long tm = simp.getStartTime();
				TimelineModel tmod = AppModel.getTimelineModel();
				tmod.setStartTime(new Date(tm));

				long endTime = simp.getEndTime();
				tmod.setEndTime(new Date(endTime));

				if (canvasStartTime == 0) {
					canvas.setStartTime(tm);
				}
				for( HPSplitableLayer layer : layers ) {
					int band_id = layer.getBandId();
					canvas.addDataLayer( band_id, layer );
				}
			}

		} catch (Exception e) {
			e.printStackTrace();
			GuiUtil.showErrorInGuiThread("Loading device data:", e);
		} catch (Error r) {
			r.printStackTrace();
		} catch (Throwable t) {
			t.printStackTrace();
		} finally {
			dev.removeStreamListener(simp);
			System.out.println("ENDING JOB: " + devName + "/" + sid);
			JobManager.running--;
		}
		return null;
	}

	@Override
	public void done() {
	}

	public long getStartTime() {
		return canvasStartTime;
	}

	public long getStopTime() {
		return canvasStopTime;
	}

	public TsPSwingCanvas getCanvas() {
		return canvas;
	}
};

@Slf4j
public class JobManager {

	private static JButton cancel;
	public static JProgressBar progressBar;
	private static JLabel message;
	private static long progressStartTime;
	private static long progressRange;
	private static PropertyChangeListener progressUpdateListener = new LoadProgressListener();
	static boolean stop = false;

	static List<SwingWorker<Integer, Void>> jobs = new LinkedList<SwingWorker<Integer, Void>>();
	private static boolean finished;
	static int running = 0;

	public static void prepareProgressBar(JLabel message, JProgressBar progressBar, JButton cancel) {
		JobManager.message = message;
		JobManager.progressBar = progressBar;
		JobManager.cancel = cancel;
		cancel.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				SignalImporter.stop = true;
			}
		});
	}

	static class LoadProgressListener implements PropertyChangeListener {

		private int progressActual;
		private int progressLast = 0;

		@Override
		public void propertyChange(PropertyChangeEvent evt) {

			boolean edt = SwingUtilities.isEventDispatchThread();

			if (SignalImporter.IMPORTER_FILE_PROPERTY.equals(evt.getPropertyName())) {
				message.setText("Loading... " + evt.getNewValue());
				return;
			}

			if ("state".equals(evt.getPropertyName())) {
				LoadWorker worker = (LoadWorker) evt.getSource();
				StateValue s = (StateValue) evt.getNewValue();

				if (s == StateValue.STARTED) {
					prepareProgressIndicator(worker.getStartTime(), worker.getStopTime());

					progressLast = 0;
					progressActual = 0;
					// addDerivedSignal.setEnabled(false);
					// visualization.setEnabled(false);
					message.setText("Loading...");
					progressBar.setVisible(true);
					cancel.setVisible(true);
				} else if (s == StateValue.DONE) {
					progressLast = 0;
					if (jobs.size() > 0) {
						executeOneJob();
					} else {
						progressBar.setVisible(false);
						cancel.setVisible(false);
						message.setText("Complete");
					}
				} else {
					log.error("Unexpected state: {}", s);
				}
				return;
			} else if ("importerPosition".equals(evt.getPropertyName())) {
				// ? ignore
			} else {
				log.error("fixme: Unexpected property change: {}", evt.getPropertyName());
			}

			long newValue = (Long) evt.getNewValue();
			progressActual = (int) ((newValue - progressStartTime) / 1000);
			if (progressActual < progressLast) {
				log.error("fixme: progressLast not reset?");
				progressLast = progressActual; // not supposed to happen
			}

			// PERCENT COMPLETE is progressActual + " of " + progressRange
			if ((progressActual - progressLast) > (progressRange / 100)) {
				if (edt) {
					progressLast = progressActual;
					progressBar.setValue(progressActual);
					progressBar.repaint();
				} else {
					try {
						SwingUtilities.invokeAndWait(new Runnable() {

							@Override
							public void run() {
								progressLast = progressActual;
								progressBar.setValue(progressActual);
								progressBar.repaint();

							}
						});
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}
	}

	public static SwingWorker<Integer, Void> createImporterJob(TsPSwingCanvas canvas, PiDatastreamImporter dev,
			String devName, StreamID sid, List<RpMetric> sigs) {

		TimelineModel tl_model = AppModel.getTimelineModel();
		Date startTime = tl_model.getStartTime();
		Date stopTime = tl_model.getEndTime();
		if (startTime != null) {
			canvas.setStartTime(startTime.getTime());
			canvas.setStopTime(0);
		}

		if (stopTime != null) {
			canvas.setStopTime(stopTime.getTime());
		}

		final SignalImporter simp = new SignalImporter();
		simp.addPropertyChangeListener(SignalImporter.IMPORTER_POS_PROPERTY, progressUpdateListener);
		simp.addPropertyChangeListener(SignalImporter.IMPORTER_FILE_PROPERTY, progressUpdateListener);

		LoadWorker worker = new LoadWorker(simp, canvas, dev, devName, sid, sigs);
		worker.addPropertyChangeListener(progressUpdateListener);

		jobs.add(worker);
		return worker;
	}

	public static void prepareProgressIndicator(Long startTime, Long stopTime) {
		progressBar.setVisible(true);
		cancel.setVisible(false);
		if (startTime != null && stopTime != null && stopTime > startTime) {
			progressStartTime = startTime;
			progressRange = ((stopTime - progressStartTime) / 1000);

			log.warn("progress start: 0 progress end: {}", progressRange);

			progressBar.setMinimum(0);
			progressBar.setMaximum((int) progressRange);
		} else {
			progressBar.setIndeterminate(true);
		}
	}

	public static void executeOneJob() {

		SignalImporter.stop = false;

		if (running > 1) {
			System.out.println("Ignoring run request...job already in progress");
			return;
		}

		Iterator<SwingWorker<Integer, Void>> it = jobs.iterator();
		if (it.hasNext()) {
			SwingWorker<Integer, Void> worker = it.next();
			running++;
			System.out.println("STARTING JOB: " + ((LoadWorker) worker).devName + "/" + ((LoadWorker) worker).sid);
			worker.execute(); // creates a thread...no wait
			it.remove();
		}

	}

	public static boolean isFinished() {
		if (running == 0) {
			return jobs.size() == 0;
		}
		return false;
	}

}
