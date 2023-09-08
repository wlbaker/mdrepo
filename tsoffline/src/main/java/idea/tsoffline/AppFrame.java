/*
 * William Baker
 * 
 * TODO: Classic WF selection
 * TODO: /Play/ and audio
 */

package idea.tsoffline;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Cursor;
import java.awt.Desktop;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.geom.AffineTransform;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URLEncoder;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.prefs.BackingStoreException;

import javax.swing.AbstractAction;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.KeyStroke;
import javax.swing.SwingWorker;
import javax.swing.SwingWorker.StateValue;
import javax.swing.WindowConstants;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.activities.PActivity;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectExporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiDreExporter;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.PiHdf5Importer;
import idea.persistmanager.PiImporterUtil;
import idea.persistmanager.hdf5.H5GroupImporter;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import oracle.help.Help;
import oracle.help.library.helpset.HelpSet;
import oracle.help.library.helpset.HelpSetParseException;
import uk.me.berndporr.api.FilterInterface;
import idea.GlobalHotkeyManager;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.devwizard.SetupWizard;
import idea.gui.RecentFiles;
import idea.r.RCue;
import idea.ts.TsBand;
import idea.ts.TsCode;
import idea.ts.TsFilter;
import idea.ts.TsoAnnotationEntryType;
import idea.ts.TsoAnnotationInfoType;
import idea.ts.TsoAttributeType;
import idea.ts.TsoCalibration;
import idea.ts.TsoDeviceType;
import idea.ts.TsoPhase;
import idea.ts.TsoPrefs;
import idea.ts.TsoSession;
import idea.ts.TsoSignalLayerType;
import idea.tsoffline.canvas.DisplayLayout;
import idea.tsoffline.canvas.PLayerSignalProducer;
import idea.tsoffline.canvas.TsControlPanel;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.disp_manager.DisplayManager;
import idea.tsoffline.event_editor.AnnotationExplorer;
import idea.tsoffline.event_editor.B2BAnnotationExplorer;
import idea.tsoffline.event_editor.PhaseExplorer;
import idea.tsoffline.explorer.DatasetExplorerWizard;
import idea.tsoffline.export.ExportWizard;
import idea.tsoffline.filter.FilterUtil;
import idea.tsoffline.model.FormulaSignal;
import idea.tsoffline.openwiz.OpenStudyWizard;
import idea.tsoffline.persist.TsoSessionSTPUtil;
import idea.tsoffline.persist.TsoSessionXMLUtil;
import idea.tsoffline.persist.TsoSetupXMLUtil;
import idea.tsoffline.prefs.PreferencesPanel;
import idea.tsoffline.script.ConsolePanel;
import idea.tsoffline.script.ScriptPanel;
import idea.tsoffline.setup.TsoSetupWizard;
import idea.tsoffline.video.TsPhaseControlPanel;
import idea.tsoffline.vizwiz.RPlotterPanel;
import idea.tsoffline.vizwiz.VizWizard;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
@Slf4j
public class AppFrame extends JFrame  {
	public static final String APP_NAME = "\u03C3PAD";
	public static final String APP_VERSION = "0.6.4";
	public static final String APP_RELEASE = "June 3, 2019";

	protected String subject_name;

	protected File sessionFile;
	private static AppFrame instance;
	private static PiSubjectImporter study_importer;

	private TsoPrefs prefs;
	private File prefsFile;

	private ConsolePanel console = null;
	private JMenuItem[] recent = new JMenuItem[10];

	DisplayManager manager;
	TsControlPanel tpanel;
	TsoSession session = null;

	private HPPathLayer vol_layer;

	private RpSubject subject;
	private Help h;

	public static AppFrame getInstance() {
		return instance;
	}

	public AppFrame() {

		AppFrame.instance = this;
		initComponents();

		consoleMenuItem.setEnabled(true);

		// Make the big window be indented 50 pixels from each edge
		// of the screen.
		int inset = 50;
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		setBounds(inset, inset, screenSize.width - inset * 2, screenSize.height - inset * 2);

		setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

		addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent e) {

				// super.windowClosing(e);
				exitMenuItemActionPerformed(null);
			}

		});

		JMenu help = new JMenu("Help");
		JMenuItem contents;
		help.add(contents = new JMenuItem("Contents"));
		contents.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				if (h == null) {
					h = new Help();

					File f = new File("doc/ohj/auth02.hs");
					HelpSet hs;
					try {
						hs = new HelpSet(f.toURL());
						h.addBook(hs);
					} catch (MalformedURLException | HelpSetParseException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
				h.showNavigatorWindow();
				// GuiUtil.doDialog("Help", AppFrame.this, h, null);
			}
		});

		JMenuItem training;
		help.add(training = new JMenuItem("Training"));
		training.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				JPanel panel = new TrainingPanel();
				GuiUtil.doDialog("Training", AppFrame.this, panel, null);
			}
		});
		JMenuItem feedback;
		help.add(feedback = new JMenuItem("Feedback"));
		feedback.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// JPanel panel = new TrainingPanel();
				// GuiUtil.doDialog("Training", AppFrame.this, panel, null);
				try {
					submitMessage();
				} catch (IOException | URISyntaxException e1) {
					GuiUtil.showError("Could not create feedback.", e1);
				}
			}
		});
		JMenuItem about;
		help.add(about = new JMenuItem("About"));
		about.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				JPanel panel = new AboutPanel();
				GuiUtil.doDialog("About", AppFrame.this, panel, null);
			}
		});

		menuBar.add(help);
		// getContentPane().add(menuBar, BorderLayout.NORTH);

		initRecentFiles();

		Container contentPane = getContentPane();

		// 160331 add the display form
		// 06MAR17 WLB TsDataPanel dpanel = new TsDataPanel(null);
		manager = new DisplayManager(tpanel = new TsControlPanel(), null); // 06MAR17
																			// WLB
																			// dpanel);
		tpanel.getCanvas1().setName("primary");
		// 06MAR17 WLB dpanel.addPropertyChangeListener("selected_signal",
		// tpanel);
		// 06MAR17 WLB dpanel.addPropertyChangeListener("removed_signal",
		// tpanel);
		// 06MAR17 WLB dpanel.addPropertyChangeListener("selected_signal",
		// this);
		contentPane.add(manager, BorderLayout.CENTER);
		// contentPane.add(tpanel, BorderLayout.CENTER);

		// 160331 contentPane.add(tpanel = new TsControlPanel(),
		// BorderLayout.CENTER);
		// 160331 contentPane.add(dpanel = new TsDevicePanel(),
		// BorderLayout.WEST);
		setMessage(" ");
		try {
			// RUtil.getREngine(); // try to init the R engine
			consoleMenuItem.setEnabled(true);
		} catch (Throwable e) {
			setMessage("R unavailable: " + e.getMessage());
			log.error("Could not init R: {}", e.getMessage());
		}

		// 160331 tpanel.setVisible(false);
		// 160331 dpanel.setVisible(false);

		cboxNavigationActionPerformed(null);
		initHotkeys();

		close(); // set default items...disabled and/or not visible

	}

	protected void submitMessage() throws IOException, URISyntaxException {

		String to = "william.l.baker2.civ@mail.mil";
		String cc = "bbaker@softhorizons.com";
		String subject = "SigmaPAD%20Application%20Feedback";

		// this encoding uses + insedad of %20...and maybe other issues
		String body = URLEncoder.encode("", "UTF-8");

		// poor man's encoding
		body = body.replaceAll("\\+", "%20").replaceAll("\\%21", "!").replaceAll("\\%27", "'").replaceAll("\\%28", "(")
				.replaceAll("\\%29", ")").replaceAll("\\%7E", "~");

		final String mailURIStr = String.format("mailto:%s?subject=%s&cc=%s&body=%s", to, subject, cc, body);

		URI uriMailTo = new URI(mailURIStr);

		Desktop desktop;
		if (Desktop.isDesktopSupported() && (desktop = Desktop.getDesktop()).isSupported(Desktop.Action.MAIL)) {
			desktop.mail(uriMailTo);
		} else {
			throw new RuntimeException("desktop doesn't support mailto; mail is dead anyway ;)");
		}

	}

	private void setMessage(String txt) {
		manager.setMessage(txt);
	}

	public void showErrorMessage(String msg) {
		if (msg == null) {
			setMessage("");
		} else {
			Toolkit.getDefaultToolkit().beep();
			setMessage(msg);
		}
	}

	private void initHotkeys() {
		KeyStroke f12 = KeyStroke.getKeyStroke(KeyEvent.VK_F12, 0);

		AbstractAction navAction = new AbstractAction() {

			@Override
			public void actionPerformed(ActionEvent e) {
				cboxNavigation.setSelected(!cboxNavigation.isSelected());
				cboxNavigationActionPerformed(null);
			}
		};

		GlobalHotkeyManager hotkeyManager = GlobalHotkeyManager.getInstance();

		hotkeyManager.getInputMap().put(f12, "nav");
		hotkeyManager.getActionMap().put("nav", navAction);

	}

	private void initRecentFiles() {
		recent[0] = r0;
		recent[1] = r1;
		recent[2] = r2;
		recent[3] = r3;
		recent[4] = r4;
		recent[5] = r5;
		recent[6] = r6;
		recent[7] = r7;
		recent[8] = r8;
		recent[9] = r9;
		RecentFiles.load(TsOfflineSetup.getInstance(), recent);

		ActionListener recentListener = new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				JMenuItem item = (JMenuItem) e.getSource();
				File file = (File) item.getClientProperty("file");
				try {
					// OpenStudyWizard.openDataImporter(file); // the
					session = getSessionInfoStep1(file);
					openSessionFiles(null, session, file.getParentFile());
				} catch (Exception e1) {
					GuiUtil.showError("Could not open session file", e1);
				}
			}
		};

		for (JMenuItem item : recent) {
			item.addActionListener(recentListener);
		}
	}

	public TsoSession getSessionInfoStep1(File f) throws Exception {
		String name = f.getName().toLowerCase();
		if (name.endsWith("xml") || name.endsWith("spad")) {
			session = TsoSessionXMLUtil.readSessionFile(f);
			sessionFile = f;

			String dataFileName = session.getDataFile();
			File df = new File(dataFileName);

			// if files have been moved, the session data file is still an
			// absolute path that
			// points to the previous location
			if (!df.exists()) {
				// look for the same data file name in the directory of the
				// session file
				df = new File(sessionFile.getParent(), df.getName());

				if (!df.exists()) {
					dataFileName = dataFileName.replaceAll("\\\\", "/");

					df = new File(dataFileName);
					if (!df.exists()) {
						df = new File(sessionFile.getParent(), df.getName());
					}
				}

				if (df.exists()) {
					// reset the datafile to an existin one
					session.setDataFile(df.getName());
				}
			}

		} else if (name.endsWith("stp")) {

			TsoSessionSTPUtil stpUtil = new TsoSessionSTPUtil();

			session = stpUtil.readSessionFile(f);
			sessionFile = f;
			// String datName = fileName.substring(0, dot_pos + 1) + "dat";
			// datName = datName.replace("_s_", "_w_");
			// f = new File( f.getParentFile(), datName );
			// session must set start time!

		} else {
			sessionFile = null;
			session = new TsoSession();
			session.setDataFile(f.getPath());
			File audioFile = getAudioFile(f);
			if (audioFile != null) {
				session.setAudioFile(audioFile.getPath());
			}

		}

		return session;
	}

	public void importFromFile(String file) throws IOException {
		// doImport( new File(file) );
		PiHdf5Exporter dest = new PiHdf5Exporter(null, ((PiHdf5Importer) study_importer).getH5FileId());
		dest.connect();

		_doImportDAT(dest, new File(file));

		log.error("AppFrame ERROR: I really need to indicate to which file to import, then disconnect.");
	}

	public void openMenuItemActionPerformed(ActionEvent e) {
		final OpenStudyWizard panel = new OpenStudyWizard();

		GuiUtil.doDialog("Open Study", this, panel, null);

		if (panel.isFinished()) {
			// RpStudy study = panel.getStudy();
			study_importer = panel.getImporter();
			session = panel.getSession();
			File sessionDir = panel.getSessionDir();
			
			/*
			 * This is used when picking the menu item "Save Session"
			 */
			session.setDataFile( sessionDir.getPath() );

			study_importer = openSessionFiles(study_importer, session, sessionDir );
			subject = (study_importer == null) ? null : study_importer.getSubjectInfo();
			
		}

	}

	/*
	 * ************************************************************************* **
	 * 
	 * menu item handler functions
	 */
	public SwingWorker<Integer, Void> createLoadJob(String devName, StreamID sid, List<RpMetric> sigs) {
		PiDatastreamImporter importer = study_importer.getDatastreamImporter(devName, sid);
		if (importer == null) {
			return null;
		}

		if (importer instanceof H5GroupImporter) {
			importer = ((H5GroupImporter) importer).getDatasetImporter(sid);
			if (importer == null) {
				log.error("ERROR: could not find stream exporter {} in device {}", sid, devName);
				return null;
			}
		}

		if (sigs == null) {
			return null;
		}

		// don't load sigs that are already loaded
		GuiUtil.showMessage("FIXME: dont load signals that are already loaded 071219");
//		Iterator<RpMetric> ii = sigs.iterator();
//		while (ii.hasNext()) {
//			RpMetric sig = ii.next();
//			if (sig.isLoaded()) {
//				ii.remove();
//			}
//		}

		// nothing to do if no sigs need loading
		if (sigs.size() == 0) {
			return null;
		}

		final TsPSwingCanvas canv = tpanel.getCanvas1();
		SwingWorker<Integer, Void> worker = JobManager.createImporterJob(canv, importer, devName, sid, sigs);
		worker.addPropertyChangeListener(new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {

				Object src = evt.getSource();
				if ("state".equals(evt.getPropertyName())) {
					SwingWorker.StateValue state = (StateValue) evt.getNewValue();
					if (state == StateValue.STARTED) {
						enableAllMenuItems(false);
						// start-load-job does this...but it probably shouldnt
						canv.setDisplayLayout(DisplayLayout.GD_ONE);
						canv.reset();
					} else if (state == StateValue.DONE) {
						if (!JobManager.isFinished()) {
							return; // more data coming
						}
						enableAllMenuItems(true);
						manager.setAudiofile(session.getAudioFile());
						// if (session == null) {
						// } else {
						canv.applyDefaults();

						// will get redrawn with session view
						applySessionView(session);
						applySessionFormulas(canv, session);
						addSessionSignals();
						applySessionAnnotations(session);
						applySessionPhases(session);
						applySessionTransform(session);

						/*
						 * create and apply formulas to signals, but that just handles the meta-info.
						 * Run "updateFormulas to actually perform the computations.
						 */
						canv.updateFormulas();

						/*
						 * signals the thread that may have started the load and is "wait"ing on the
						 * frame instance, see AppUtil.open()
						 */
						synchronized (AppFrame.this) {
							AppFrame.this.notifyAll();
						}

					}
				}

			}

		});

		return worker;
	}

	PiSubjectImporter openSessionFiles( PiSubjectImporter importer, TsoSession session, File sessionDir ) {

		try {
			if( importer == null ) {
				File dataFile = new File( session.getDataFile() );
				if( dataFile.exists() == false ) {
					dataFile = new File( sessionDir, session.getDataFile() );
				}
				if( dataFile.exists() == false ) {
					GuiUtil.showMessage("Cannot open data file: " + session.getDataFile() );
					return null;
				}
				study_importer = PiImporterUtil.getImporterFromFile( dataFile );
				study_importer.connect();
				importer = study_importer;
			}
			_startDataLoadJob( importer, session);

//			if (dataFile == null) {
//				this.setTitle(APP_NAME);
//				PrefUtil.setAppFile(null);
//				subject_name = "";
//			} else {
			// updateTitleAndPrefs(session.getDataFile() );
//			}
		} catch (Exception e) {
			GuiUtil.showError("Error opening file: " + session.getDataFile(), e);
		}

		return importer;
	}

	private void _startDataLoadJob(PiSubjectImporter importer, TsoSession sess) throws Exception {

		subject = importer.getSubjectInfo(); // WARNING...subject is

		TimelineModel tl_model = AppModel.getTimelineModel();
		tl_model.setStartTime(sess.getDataStart());
		tl_model.setEndTime(sess.getDataEnd());
		tl_model.publish();

//		List<TsBand> bands = sess.getTsoBands();
//		if (bands == null || bands.size() == 0) {
//			tpanel.getCanvas1().setDisplayLayout(DisplayLayout.GD_ONE);
//		} else {
//			tpanel.getCanvas1().setDisplayLayout(bands);
//		}

		loadDataJob(sess);

		/*
		 * Apply the frame width-and-height values found in the session file, if any
		 */
		if (sess != null) {
			if (sess.getFrameWidth() > 100 && sess.getFrameHeight() > 100) {
				setSize(sess.getFrameWidth(), sess.getFrameHeight());
				setLocation(sess.getFrameX(), sess.getFrameY());
				if (sess.getFrameState() > 0) {
					setExtendedState(sess.getFrameState());
				}
			}
		}
	}

	private void updateTitleAndPrefs(File f, File dataFile) {
		this.setTitle(APP_NAME + ": " + dataFile.getAbsolutePath());
		PrefUtil.setAppFile("" + dataFile.getAbsoluteFile());
		subject_name = null;

		if (subject != null) {
			subject_name = subject.getSubject();
			if (subject_name == null || subject_name.length() == 0) {
				subject_name = subject.getMedicalId();
			}
		}
		if (subject_name == null || subject_name.length() == 0) {
			subject_name = dataFile.getName();

			String[] tests = { "_w_", "_s_", "." };
			for (String test : tests) {
				int dot = subject_name.indexOf(test);
				if (dot > 0) {
					subject_name = subject_name.substring(0, dot);
				}
			}
		}

		try {
			RecentFiles.addFile(TsOfflineSetup.getInstance(), recent, f);
			TsOfflineSetup.setArchiveFile(dataFile.getAbsolutePath());
		} catch (BackingStoreException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	private void resetActionPerformed(ActionEvent e) {
		applySessionView(session);
	}

	/*
	 * WARNING: this is too similar to applySessionNames, but this must be done
	 * AFTER creating the derived signals
	 */
	private void applySessionView(TsoSession session) {

		final TsPSwingCanvas canv = tpanel.getCanvas1();
		HPSplitableLayer[] layers = canv.getSigs();

		for (HPSplitableLayer sig : layers) {
			TsoSignalLayerType layer_info = null;
			PLayer layer = sig;
			String devName = (String) layer.getAttribute("dev_name");
			String sigName = (String) layer.getAttribute("sig_name");
			String sigLoc = (String) layer.getAttribute("sig_loc");

			dev_loop: for (TsoDeviceType dev : session.getTsoDevices()) {
				if (!dev.getDeviceName().equals(devName)) {
					continue;
				}
				for (TsoSignalLayerType tso_sig : dev.getSignalLayer()) {
					if (!tso_sig.getLoc().equals(sigLoc)) {
						continue;
					}
					layer_info = tso_sig;
					break dev_loop;
				}
			}

			if (layer_info == null) {
				log.error("could not find signal: {}/{}", devName, sigName);
			} else {
				if( layer_info.getName() != null ) {
					sig.setName( layer_info.getName() );
				}
				applyTsoSignalInfo(sig, layer_info);
				applyCalibrationInfo(sig, layer_info);
			}
			// session.get layer.getName();
		}
	}

	private void applyCalibrationInfo(HPSplitableLayer sig, TsoSignalLayerType layerinfo) {
		List<TsoCalibration> calibInfo = layerinfo.getCalibration();
		log.debug("applyCalibrationInfo: {} {}", sig, calibInfo);
		if (calibInfo == null || calibInfo.isEmpty()) {
			return;
		}

		PLayer layer = sig;
		for (TsoCalibration cal : calibInfo) {
			if (cal.getStartTime() > 0) {
				// create layer if necessary
				layer = tpanel.splitLayerForCalibration( //
						sig, // can change in first call
						cal.getStartTime() / 1000.0 // convert ms to sec
				);
			}

			AffineTransform tran = new AffineTransform(1, 0, 0, cal.getGain(), cal.getShift(), cal.getOffset());
			layer.setTransform(tran);

		}
	}

	private void applySessionCalibration(TsoSession session) {
		TsPSwingCanvas canvas = tpanel.getCanvas1();

		canvas.terminateAnimation(PActivity.TERMINATE_AND_FINISH);

		List<TsoDeviceType> devs = session.getTsoDevices();
		if (devs == null) {
			return;
		}
		for (TsoDeviceType dev : devs) {
			List<TsoSignalLayerType> tso_sigs = dev.getSignalLayer();

			if (tso_sigs == null) {
				continue;
			}
			for (TsoSignalLayerType tso_sig : tso_sigs) {
				List<TsoCalibration> calibs = tso_sig.getCalibration();
				if (calibs == null || calibs.size() == 0) {
					continue;
				}
				TsoCalibration cal = calibs.get(0);

				HPSplitableLayer sig = canvas.findSignal(tso_sig.getLoc());
				if (sig == null) {
					log.error("Could not find signal to apply calibration: {}", tso_sig.getLoc());
					continue;
				}
				AffineTransform tran = new AffineTransform(1, 0, 0, cal.getGain(), cal.getShift(), cal.getOffset());
				sig.setTransform(tran);
			}
		}
		canvas.redrawAxisLayer(0);
	}

	private void applyTsoSignalInfo(HPSplitableLayer sig, TsoSignalLayerType layer_info) {
		AffineTransform t = new AffineTransform(1, 0, 0, 1, 0, 0);
		if( sig.getChildrenCount() == 0 ) {
			log.error("no children for signal: {}", sig.getName() );
			return;
		}
		HPPathLayer layer = (HPPathLayer) sig.getChild(0);
		if (layer == null) {
			log.error("null layer for signal: {}", sig);
			return;
		}
		layer.setTransform(t);
		layer.setVisible(layer_info.isVisible());
		String name = layer_info.getName();
		if (name != null && name.length() > 0) {
			sig.setName(layer_info.getName());
			layer.addAttribute("sig_name", layer_info.getName());
		}

		byte[] rgb = layer_info.getColor();
		if (rgb != null) {

			Color color = ColorManager.asColor(rgb);
			sig.setDefaultColor(color);
			sig.setPaint(color);

			layer.setPaint(color);
		}

		List<TsoAttributeType> attribs = layer_info.getAttributes();
		if (attribs != null && attribs.size() > 0) {
			/*
			 * check and fix filter/@filterName
			 */
			Iterator<TsoAttributeType> it = attribs.iterator();
			while (it.hasNext()) {
				TsoAttributeType attr = it.next();
				String key = attr.getKey();
				String val = attr.getValue();
				if ("filter".equals(key)) {

				}
				if ("@filterName".equals(key)) {

				}
			}

			/*
			 * now apply all attributes
			 */
			it = attribs.iterator(); // reset the iterator
			while (it.hasNext()) {
				TsoAttributeType attr = it.next();
				String key = attr.getKey();
				String val = attr.getValue();
				if (key == null) {
					log.error("null key for attribute: {}/{}", name, val);
					continue;
				}
				if ("filter".equals(key)) {
					// correct approach: iterate through attributes twice...first fixing filter and
					// @filterName
					log.warn("ignoring filter description, waiting for @filterName: {}/{}", name, val);
					continue;
				}
				layer.addAttribute(key, val);

				// if ("filter".equals(key)) {
				// TsFilter filter = FilterUtil.findFilterFromName( val );
				// }
				if ("@filterName".equals(key)) {
					TsFilter filter = FilterUtil.findFilterFromName(val);
					if (filter == null) {
						log.error("missing filter definition: {}/{}", key, val);
					} else {
						FilterInterface cascade = FilterUtil.createFilterFromJSON(filter.getDescription());
						layer.applyFilter(filter, cascade);
					}
				}
			}
		}

		int bandId = layer_info.getBandId();
		sig.setBandId(bandId);

	}

	private void addSessionSignals() {
		TsPSwingCanvas canvas = tpanel.getCanvas1();

		/*
		 * The layers have already been added to the canvas, but
		 * the band may have been re-assigned by the session info. 
		 * 
		 * It is safe to add layers multiple times.  Duplicate information
		 * will not be created.
		 */
		for (HPSplitableLayer layer : canvas.getSigs() ) {
			
			if (layer.isLoaded()) {
				// band_id will be -1 if no band assigned
				int band_id = layer.getBandId();
				if (band_id >= 0) {
					canvas.addDataLayer(band_id, (HPSplitableLayer)layer );
				}
			}
		}

	}

	private void applySessionTransform(TsoSession session) {
		TsPSwingCanvas canvas = tpanel.getCanvas1();

		canvas.terminateAnimation(PActivity.TERMINATE_AND_FINISH);

		for (PCamera cam : canvas.getBandCameras()) {

			double sy = -1;
			double ty = 0;
			TsBand tsBand = (TsBand) cam.getAttribute("tsBand");
			if (tsBand != null && tsBand.getYScale() != 0) {
				sy = tsBand.getYScale();
				ty = tsBand.getYTranslate();
			}
			AffineTransform vt = new AffineTransform(session.getXScale(), 0, 0, sy, session.getXTranslate(), ty);
			try {
				// test the transform to see if it us usable
				AffineTransform r = new AffineTransform(vt);
				r.invert();
			} catch (Exception e) {
				log.error("COULD NOT INVERT TRANS: {}", vt);
				vt = new AffineTransform(); // use the identity matrix
			}

			cam.setViewTransform(vt);
		}
		canvas.redrawAxisLayer(0);
	}

	private void applySessionAnnotations(TsoSession session) {

		TsPSwingCanvas canv = tpanel.getCanvas1();
		
		List<TsoAnnotationInfoType> infos = session.getTsoAnnotations();
		for (TsoAnnotationInfoType info : infos) {
			String layerName = info.getLayerName();
			PLayer layer = canv.getAnnotationLayer(layerName);

			Color layerColor = Color.DARK_GRAY;
			byte[] rgb = info.getColor();
			if (rgb != null && rgb.length == 3) {
				layerColor = ColorManager.asColor(rgb);
			}

			if (layer == null) {
				layer = canv.addAnnotationLayer(layerName, layerColor, info.getSource());
			} else {
				layer.setPaint(layerColor);
			}

			layer.setVisible(info.isVisible());

			List<TsoAnnotationEntryType> entries = info.getAnnotationEntry();
			for (TsoAnnotationEntryType entry : entries) {
				String code = entry.getCode();
				double val = entry.getValue();
				double offset = entry.getOffset();
				PNode node = LayerUtil.addFiducialPoint(layer, offset, val, code);
				node.addAttribute("item", entry);
				node.addAttribute("txt", code);
				applyPNodeAttributes(node, entry.getAttributes());

			}

			List<TsoAttributeType> attrs = info.getAttributes();
			applyPNodeAttributes(layer, attrs);
		}

	}

	private void applySessionPhases(TsoSession session) {

		PLayer phaseLayer = tpanel.getCanvas1().getPhaseLayer();

		List<TsoPhase> phases = session.getTsoPhases();
		for (TsoPhase phase : phases) {
			String phaseName = phase.getName();
			if (phaseName == null) {
				phase.setName("BUBBA!");

			}

			AppModel.addAnnotation(phaseLayer, phase, true);

			// List<TsoAttributeType> attrs = phase.getAttributes();
			// applyPNodeAttributes(phase, attrs);
		}

	}

	private void applyPNodeAttributes(PNode node, List<TsoAttributeType> attrs) {
		if (attrs == null) {
			return;
		}
		for (TsoAttributeType entry : attrs) {
			String key = entry.getKey();
			if ("txt".equals(key)) {
				continue; // ignore...already handled
			} else if ("item".equals(key)) {
				continue; // ignore...already handled
			}
			Object val = entry.getValue();
			String typ = entry.getTyp();
			if ("OfflineSignal".equals(typ)) {
				val = getCanvas().findSignal((String) val);
				if (val == null) {
					log.error("Could not restore signal: {} attribute of: {}", val, node.getName());
				}
			} else if ("Double".equals(typ)) {
				val = Double.parseDouble((String) val);
			} else if ("Map".equals(typ)) {
				Map<String, Double> map = new HashMap<>();
				for (TsoAttributeType subentry : entry.getAttribute()) {
					double subval = Double.parseDouble(subentry.getValue());
					map.put(subentry.getKey(), subval);
				}
				val = map;
			} else if (typ == null) {
				// treat key and val as string...
			} else {
				log.error("Unknown attribute typ: {} key={} val={}", typ, key, val);
			}

			node.addAttribute(key, val);
		}
	}

	private void applySessionFormulas(TsPSwingCanvas canvas, TsoSession session) {

		List<TsoDeviceType> devs = session.getTsoDevices();
		for (TsoDeviceType dev : devs) {

			String dev_name = dev.getDeviceName();
			if (dev_name == null || !dev_name.equals("@Formula")) {
				continue;
			}

			List<TsoSignalLayerType> tsosigs = dev.getSignalLayer();
			if (tsosigs == null) {
				continue;
			}
			for (TsoSignalLayerType tsosig : tsosigs) {
				String formula = tsosig.getLoc();
				String layerName = tsosig.getName();

				// updated color will be applied
				FormulaSignal sig = AppModel.addFormula(layerName, Color.CYAN, formula);

				if (sig == null) {
					log.error("Could not process formula: {}", formula);
					GuiUtil.showMessage("Could not process formula: " + formula);
					continue;
				}

				applyTsoSignalInfo(sig, tsosig);
			}

			canvas.updateFormulas();
		}
	}

	/*
	 * Returns a file just which may be the file passed in, or may be a file derived
	 * from a session.
	 */
	public PiSubjectImporter openDataImporter(File f) throws IOException {

		File importerFile = null;

		if (study_importer != null) {
			try {
				study_importer.disconnect();
			} catch (Exception e) {
				log.error("disconnect error...unexpected?", e);
			}
		}

		PiSubjectImporter importer = PiImporterUtil.getImporterFromFile(f);
		if (importer == null) {
			throw new IOException("Could not open file.");
		}

		Cursor prev = AppFrame.this.getCursor();
		AppFrame.this.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

		PiHdf5Importer h5 = null;
		try {
			importer.connect();

			String fileType = "not_session";
			if (importer instanceof PiHdf5Importer) {
				h5 = (PiHdf5Importer) importer;
				fileType = h5.readStringAttribute("fileType");
			}

			if ("session".equals(fileType)) {
				String dataFileName = h5.readStringAttribute("dataFile");
				importerFile = new File(dataFileName);
				if (!importerFile.exists()) {
					String title = "Could not find datafile: " + dataFileName;
					GuiUtil.showMessage(title);
					importerFile = GuiUtil.doOpenFileChooser(JFileChooser.FILES_ONLY, title, this, null, null);
				}
				study_importer = PiImporterUtil.getImporterFromFile(importerFile);
				study_importer.connect();
			} else {
				importerFile = f;
				study_importer = importer;
			}
			// read twice!!!!

			// 071619 OfflineDevice[] devs = OfflineUtil.loadOfflineDevices(study_importer);
			// 071619 AppModel.addModel(devs);

		} catch (Exception ee) {
			GuiUtil.showError(f.toString(), ee);
		} finally {
			AppFrame.this.setCursor(prev);
			if (h5 != null && h5 != study_importer) {
				h5.disconnect();
			}
		}

		return study_importer;
	}

	/*
	 * Returns the audio file associated with the data file.
	 */
	private File getAudioFile(File dataFile) throws IOException {
		if (dataFile == null) {
			log.error("Attempting to derive audio file name, but DAT file is null");
			// this should not happen
			return null;
		}
		File audioFile = null;
		String fileName = dataFile.getName();

		if (fileName != null) {
			fileName = fileName.replace("_w_", "_a_");
			fileName = fileName.replace("_s_", "_a_");
			int dot = fileName.lastIndexOf('.');
			if (dot > 0) {
				fileName = fileName.substring(0, dot);
			}
			fileName += ".aud";
			audioFile = new File(dataFile.getParentFile(), fileName);
			if (!audioFile.exists()) {
				audioFile = null;
			}
		}

		return audioFile;
	}

	protected void enableAllMenuItems(boolean b) {
		setupMenuItem.setEnabled(true);
		newMenuItem.setEnabled(true);
		openMenuItem.setEnabled(true);
		analysisMenuItem.setEnabled(b);
		// consoleMenuItem.setEnabled(b);

		exportMenuItem.setEnabled(b);
		closeMenuItem.setEnabled(b);
		saveMenuItem.setEnabled(b);
		if (b == false) {
			manager.disableReplay();
		}

		cboxNavigation.setEnabled(b);
		cboxShowGraphTimeline.setEnabled(b);
		cboxShowLegend.setEnabled(b);
		cboxCursorValue.setEnabled(b);
		studyMenuItem.setEnabled(b);
		analysisMenuItem.setEnabled(true); // even when no sessions are open,
											// you can still run some scripts
		annotationsMenuItem.setEnabled(b);
		phasesMenuItem.setEnabled(b);

		b2bAnnotations.setEnabled(b);

		tpanel.setVisible(b);

		b = true;
		r0.setEnabled(b);
		r1.setEnabled(b);
		r2.setEnabled(b);
		r3.setEnabled(b);
		r4.setEnabled(b);
		r5.setEnabled(b);
		r6.setEnabled(b);
		r7.setEnabled(b);
		r8.setEnabled(b);
		r9.setEnabled(b);
	}

	private void exitMenuItemActionPerformed(ActionEvent e) {

		if (checkDataLoss("Exit Application") != JOptionPane.OK_OPTION) {
			return;
		}

		this.dispose();
		System.exit(0);
	}

	/*
	 * SCRIPT INTERFACE ROUTINE, must be public
	 */

	public void close() {
		// close the importer(s)
		try {
			if (study_importer != null) {
				study_importer.disconnect();
			}
		} catch (Exception ex) {
			// this is ok
		}

		study_importer = null;

		session = null;

		TsPSwingCanvas canv = tpanel.getCanvas1();
		canv.resetAll();

		// log.error( "3 disable menu items");

		enableAllMenuItems(false);

		setTitle(APP_NAME);
		manager.clear();

		System.gc();
	}

	private void closeMenuItemActionPerformed(ActionEvent e) {

		if (checkDataLoss("Confirm Shutdown") != JOptionPane.OK_OPTION) {
			return;
		}

		close();
	}

	private int checkDataLoss(String title) {
		if (AppModel.isDirty() == false) {
			return JOptionPane.OK_OPTION;
		}
		String message = "";

		message = "You have unsaved edits. Data will be lost.";
		message += "\n\nContinue closing?";

		int ok = JOptionPane.showConfirmDialog(null, message, title, JOptionPane.OK_CANCEL_OPTION);

		return ok;
	}

	private void saveMenuItemActionPerformed(ActionEvent e) {

		if (sessionFile == null) {
			File dataFile = new File(session.getDataFile());
			String parent = dataFile.getParent();
			String fileName = dataFile.getName();
			String sessionFileName = fileName;
			int dot = fileName.lastIndexOf('.');
			if (dot > 0) {
				sessionFileName = fileName.substring(0, dot);
			}
			// sessionFileName += ".xml";
			sessionFileName += ".spad";

			sessionFile = new File(parent, sessionFileName);

		}

		sessionFile = GuiUtil.doSaveFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "Save", this, sessionFile, null);

		if (sessionFile != null) {
			if (sessionFile.isDirectory()) {
				GuiUtil.showMessage("Cannot save session to a directory: " + sessionFile.getAbsolutePath());
				return;
			}

			// File hdf5SessionFile = appendExtension(sessionFile, "ses");
			// _saveHDF5Session(hdf5SessionFile);

			// File xmlSessionFile = appendExtension(sessionFile, "xml");
			File sigmapadSessionFile = appendExtension(sessionFile, "spad");

			try {
				TsoSessionXMLUtil.saveXMLSession(sigmapadSessionFile, this, tpanel.getCanvas1(), session.getDataFile());
				RecentFiles.addFile(TsOfflineSetup.getInstance(), recent, sigmapadSessionFile);

				AppModel.setDirty(false);
			} catch (Exception e1) {
				GuiUtil.showError("Error saving session", e1);
			}
		}
	}

	private File appendExtension(File f_session, String ext) {
		String fname = f_session.getName();
		if (fname.indexOf('.') < 0) {
			fname = fname + "." + ext;

			File parent = f_session.getParentFile();
			f_session = new File(parent, fname);
		}
		return f_session;
	}

	private void exportMenuItemActionPerformed(ActionEvent e) {
		PLayerSignalProducer importer;
		importer = new PLayerSignalProducer(tpanel.getCanvas1());
		GuiUtil.showMessage("FIXME: need start time for importer");
		// 071619 importer.addOfflineDevices(AppModel.getStartTime(),
		// AppModel.getDevices());

		ExportWizard wiz = new ExportWizard(tpanel.getCanvas1(), false);
		wiz.setImporter(importer);
		wiz.setSession(session);

		GuiUtil.doDialog("Export Current", this, wiz, null);

	}

	private void _doImportDAT(PiHdf5Exporter dest, File file) throws IOException {
		PiSubjectImporter importer2 = PiImporterUtil.getImporterFromFile(file);

		importer2.connect();

		long tm_offset = 0;
		if (importer2.getTimeInMillis() <= 0) {
			ArchiveMetaData meta = study_importer.getMetaData();
			Date start = meta.getStartTime();
			if (start != null) {
				tm_offset = start.getTime();
			}
		}

		PersistentItem block;

		GuiUtil.showMessage("IMPORT DAT NOT READY");

		importer2.addStreamListener(null, dest);
		while ((block = importer2.next()) != null) {
			if (tm_offset != 0) {
				long tm = block.getTime();
				tm += tm_offset;
				block.setTm(new Date(tm));
			}
			log.error("dest.put(null, StreamID.MEASUREMENT, block);");
		}
		importer2.removeStreamListener(dest);
		dest.disconnect();
	}

	private void studyMenuItemActionPerformed(ActionEvent e) {
		showDataExplorer(false);
	}

	private void showDataExplorer(boolean doLoad) {

		DatasetExplorerWizard explorer = new DatasetExplorerWizard();
//		try {
		;
		GuiUtil.showMessage("Should be calling setSignalInfo()?");
		explorer.setSignalInfo(study_importer.getDevices());
//		} catch (IOException e1) {
//			// TODO Auto-generated catch block
//			e1.printStackTrace();
//		}

		// GuiUtil.doDialog("Setup and Configuration", this, explorer, null);

		if (doLoad) {
			if (explorer.isFinished()) {

				TimelineModel tl_model = AppModel.getTimelineModel();
				tl_model.setStartTime(explorer.getStartDate());
				tl_model.setEndTime(explorer.getEndDate());
				tl_model.publish();

				session = explorer.getSession();
			} else {
				close();
			}
		} else {
			// load not indicated...so don't close the existing
			// dataset...happens when View/Study menu selected
		}
	}

	private boolean isSigInSession(TsoSession session, RpMetric sig) {
//		List<TsoDeviceType> devs = session.getTsoDevices();
//		String loc = sig.getLocation();
//
//		for (TsoDeviceType dev : devs) {
//			String dev_name = dev.getDeviceName(); // Drager_1
//			if (dev_name.equals(sig.getSource())) {
//				List<TsoSignalLayerType> tso_layers = dev.getSignalLayer();
//				for (TsoSignalLayerType tso_layer : tso_layers) {
//					if (loc.equals(tso_layer.getLoc())) {
//						return true;
//					}
//				}
//			}
//		}
		log.error("FIXME: isSigInSession 071219");
		// FIXME: 071219
		return false;
	}

	private void loadDataJob(TsoSession session) {

		for (TsoDeviceType d : session.getTsoDevices()) {
			String devName = d.getDeviceName();
			Map<String, List<RpMetric>> smap = new HashMap<String, List<RpMetric>>();

			List<TsoSignalLayerType> layers = d.getSignalLayer();
			for (TsoSignalLayerType layer : layers) {
				String sid = layer.getSidName();
				if (sid == null) {
					sid = "Waveform";
				}
				List<RpMetric> sigs = smap.get(sid);
				if (sigs == null) {
					sigs = new LinkedList<RpMetric>();
					smap.put(sid, sigs);
				}
				RpMetric metric = new RpMetric();
				metric.setLocation(layer.getLoc());
				sigs.add(metric);
			}

			for (String s : smap.keySet()) {
				List<RpMetric> sigs = smap.get(s);
				StreamID sid = StreamID.fromName(s);
				createLoadJob(devName, sid, sigs);
			}
		}

		JobManager.executeOneJob();
	}

	private void annotationsMenuItemActionPerformed(ActionEvent e) {
		AnnotationExplorer panel = new AnnotationExplorer( tpanel.getCanvas1() );
		GuiUtil.doDialog("Annotations", this, panel, null);

		Date dt = panel.getSelectedTime();
		if (dt != null) {
			TsPSwingCanvas canvas = tpanel.getCanvas1();

			Date startTime = AppModel.getTimelineModel().getStartTime();
			long ms = dt.getTime() - startTime.getTime();
			double rtm_sec = (ms / 1000.0);

			canvas.zoomToDataPosition(null, rtm_sec, 0, 2, 0);
		}

		tpanel.redraw();
	}

	private void phasesMenuItemActionPerformed(ActionEvent e) {
		PhaseExplorer panel = new PhaseExplorer(tpanel.getCanvas1());
		GuiUtil.doDialog("Phases", this, panel, null);

		if (panel.isOk()) {
			// save?
			// Date startTime = AppModel.getTimelineModel().getStartTime();
		}

		tpanel.redraw();
	}

	private void b2bAnnotationsActionPerformed(ActionEvent e) {
		B2BAnnotationExplorer panel = new B2BAnnotationExplorer( getCanvas() );
		GuiUtil.doDialog("B2B Annotations", this, panel, null);
	}

	private void consoleMenuItemActionPerformed(ActionEvent e) {
		try {
			_consoleMenuItemActionPerformed(e);

		} catch (UnsatisfiedLinkError ee) {
			GuiUtil.showError("Could not load R console", ee);
		}
	}

	private void _consoleMenuItemActionPerformed(ActionEvent e) {
		JFrame frame = new JFrame("Script Console");

		frame.getContentPane().add(console);
		frame.setSize(900, 400);

		frame.setVisible(true);

	}

	private void newMenuItemActionPerformed(ActionEvent e) {
		try {

			File parent = null;
			String lastDir = TsOfflineSetup.getArchiveFile();
			if (lastDir != null) {
				parent = new File(lastDir);
			}
			GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "New Study Master File", this, parent,
					new ActionListener() {

						@Override
						public void actionPerformed(ActionEvent e) {
							int ok = JOptionPane.OK_OPTION;
							File file = (File) e.getSource();
							if (file.exists()) {
								ok = GuiUtil.showConfirmDialog("Replace file: " + file, "New File",
										JOptionPane.OK_CANCEL_OPTION);
								if (ok != JOptionPane.OK_OPTION) {
									return;
								}
								file.delete();
							}

							if (file.exists() == false) {

								// FIXME: replace with PiUtility.getExporter(file);
								String extension = null;
								String fileName = file.getName();

								int i = fileName.lastIndexOf('.');
								if (i > 0) {
									extension = fileName.substring(i + 1);
								}
								if (extension == null || extension.length() == 0) {
									extension = "h5";
								}
								extension = extension.toLowerCase();

								PiSubjectExporter exporter;
								if (extension.equals("dat")) {
									exporter = new PiDreExporter(null, file);
								} else { // assume h5
									exporter = new PiHdf5Exporter(null, file.getPath(), false);
								}
								try {
									exporter.connect();
									exporter.disconnect();
								} catch (IOException e1) {
									// TODO Auto-generated catch block
									e1.printStackTrace();
								}
							}
							updateTitleAndPrefs(file, file);
							enableAllMenuItems(true);
							TsPSwingCanvas canv = tpanel.getCanvas1();
							canv.setDisplayLayout(DisplayLayout.GD_ONE);
							canv.reset();
						}
					});

		} catch (Exception e1) {
			GuiUtil.showError("New", e1);
		}

	}

	private void analysisMenuItemActionPerformed(ActionEvent e) {

		RpStudy study = AppModel.getModelAsStudy();
		VizWizard wiz = new VizWizard(tpanel, study);

		GuiUtil.doDialog("Analysis", this, wiz, null);

		if (wiz.isFinished()) {
			if (wiz.isRealtime()) {
				RpAnalysis anal = wiz.getSelectedAnalysis();
				String env = wiz.getREnvName();
				embedPlots(env);
			} else {
				showPlots();
			}
		} else {
			discardPlots();
		}

		tpanel.redraw(); // there might have been some changes...like adding ECG
							// segmentation
	}

	public void discardPlots() {
		List<? extends JPanel> pending_plots = AppUtil.getPendingPlots();
		Iterator<? extends JPanel> ii = pending_plots.iterator();
		while (ii.hasNext()) {
			JPanel plot = ii.next();
			ii.remove();
		}
	}

	public void embedPlots(String envName) {
		List<? extends JPanel> pending_plots = AppUtil.getPendingPlots();
		Iterator<? extends JPanel> ii = pending_plots.iterator();
		while (ii.hasNext()) {
			JComponent plot = ii.next();
			if (plot instanceof TsPhaseControlPanel) {
				TsPhaseControlPanel pcp = (TsPhaseControlPanel) plot;
				plot = pcp.getCanvas();
			}
			Dimension sz = new Dimension(300, 260);
			plot.setMaximumSize(sz);
			plot.setMinimumSize(sz);
			plot.setPreferredSize(sz);
			tpanel.addOptionPanel(plot);
			plot.putClientProperty("env_name", envName);
			// if (plot instanceof RPlotterPanel) {
			// RCue cue = ((RPlotterPanel) plot).getRCue();
			// cue.setFrame(f2);
			// }
			// plot visibility gets reset when it is removed from the wizard
			// container
			plot.setVisible(true);
			ii.remove(); // once added to a frame...remove from stack
		}
	}

	public void showPlots() {
		List<? extends JPanel> pending_plots = AppUtil.getPendingPlots();
		Iterator<? extends JPanel> ii = pending_plots.iterator();
		while (ii.hasNext()) {
			JPanel plot = ii.next();
			JFrame f2 = new JFrame((String) plot.getClientProperty("title"));
			f2.addWindowListener(new WindowAdapter() {

				@Override
				public void windowClosing(WindowEvent e) {
					Container content = f2.getContentPane();
					Component[] comps = content.getComponents();
					for (Component comp : comps) {
						if (comp instanceof RPlotterPanel) {
							RPlotterPanel plotter = (RPlotterPanel) comp;
							RCue cue = plotter.getRCue();

							if (cue != null) {
								cue.executeDevOff();
							}
						}
					}
					super.windowClosing(e);
				}

			});
			Container content = f2.getContentPane();
			content.setLayout(new BorderLayout());
			content.add(plot, BorderLayout.CENTER);
			if (plot instanceof RPlotterPanel) {
				RCue cue = ((RPlotterPanel) plot).getRCue();
				cue.setFrame(f2);
			}
			// plot visibility gets reset when it is removed from the wizard
			// container
			plot.setVisible(true);
			f2.pack();
			f2.setVisible(true);

			ii.remove(); // once added to a frame...remove from stack
		}
	}

	private void preferencesMenuItemActionPerformed(ActionEvent e) {
		PreferencesPanel panel = new PreferencesPanel(prefs);
		GuiUtil.doDialog("Preferences", this, panel, null);
		if (panel.isOk()) {
			try {
				TsoSetupXMLUtil.saveSetup(prefsFile, prefs);
				tpanel.refresh(prefs);
			} catch (Exception e1) {
				GuiUtil.showError("Error saving setup", e1);
			}
		}
	}

	private void javaScriptMenuItemActionPerformed(ActionEvent e) {
		ScriptPanel panel = new ScriptPanel();
		GuiUtil.doNonModalDialog("Script", this, panel, null);
	}

	private void setupActionPerformed(ActionEvent e) {

		// final WizParentPanel panel = new WizParentPanel();
		// HERE I NEED TO CREATE A TEMPORARY COPY OF PREFS
		// or load them again from the file
		final SetupWizard panel = new TsoSetupWizard(prefs);

		GuiUtil.doDialog("Application Setup", this, panel, null);
		if (panel.isFinished()) {
			try {
				TsoSetupXMLUtil.saveSetup(prefsFile, prefs);
				tpanel.refresh(prefs);
			} catch (Exception e1) {
				GuiUtil.showError("Error saving setup", e1);
			}
		}

	}

	private void cboxNavigationActionPerformed(ActionEvent e) {
		if (cboxNavigation.isSelected()) {
			tpanel.showOptions();
		} else {
			tpanel.hideOptions();
		}
	}

	private void cboxCursorValueActionPerformed(ActionEvent e) {
		tpanel.showCursorValue(cboxCursorValue.isSelected());
	}

	private void cboxShowGraphTimelineActionPerformed(ActionEvent e) {
		tpanel.showGraphTimeline(cboxShowGraphTimeline.isSelected());
	}

	private void cboxShowLegendActionPerformed(ActionEvent e) {
		tpanel.showLegend(cboxShowLegend.isSelected());
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		panel4 = new JPanel();
		menuBar = new JMenuBar();
		menu1 = new JMenu();
		setupMenuItem = new JMenuItem();
		newMenuItem = new JMenuItem();
		openMenuItem = new JMenuItem();
		saveMenuItem = new JMenuItem();
		closeMenuItem = new JMenuItem();
		exportMenuItem = new JMenuItem();
		r0 = new JMenuItem();
		r1 = new JMenuItem();
		r2 = new JMenuItem();
		r3 = new JMenuItem();
		r4 = new JMenuItem();
		r5 = new JMenuItem();
		r6 = new JMenuItem();
		r7 = new JMenuItem();
		r8 = new JMenuItem();
		r9 = new JMenuItem();
		exitMenuItem = new JMenuItem();
		menu2 = new JMenu();
		studyMenuItem = new JMenuItem();
		annotationsMenuItem = new JMenuItem();
		phasesMenuItem = new JMenuItem();
		b2bAnnotations = new JMenuItem();
		cboxShowGraphTimeline = new JCheckBoxMenuItem();
		cboxShowLegend = new JCheckBoxMenuItem();
		cboxCursorValue = new JCheckBoxMenuItem();
		cboxNavigation = new JCheckBoxMenuItem();
		reset = new JMenuItem();
		preferencesMenuItem = new JMenuItem();
		menu3 = new JMenu();
		consoleMenuItem = new JMenuItem();
		rScriptMenuItem = new JMenuItem();
		javaScriptMenuItem = new JMenuItem();
		analysisMenuItem = new JMenuItem();

		//======== this ========
		setTitle("tsOffline");
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		//======== panel1 ========
		{
			panel1.setBorder(null);
			panel1.setLayout(new FormLayout(
				"[101dlu,default], $lcgap, default:grow",
				""));
		}
		contentPane.add(panel1, BorderLayout.PAGE_END);

		//======== panel4 ========
		{
			panel4.setLayout(new FormLayout(
				"default:grow",
				"default, 1px"));

			//======== menuBar ========
			{

				//======== menu1 ========
				{
					menu1.setText("File");
					menu1.setMnemonic('F');

					//---- setupMenuItem ----
					setupMenuItem.setText("Setup");
					setupMenuItem.addActionListener(e -> setupActionPerformed(e));
					menu1.add(setupMenuItem);
					menu1.addSeparator();

					//---- newMenuItem ----
					newMenuItem.setText("New");
					newMenuItem.addActionListener(e -> newMenuItemActionPerformed(e));
					menu1.add(newMenuItem);

					//---- openMenuItem ----
					openMenuItem.setText("Open");
					openMenuItem.setMnemonic('O');
					openMenuItem.addActionListener(e -> openMenuItemActionPerformed(e));
					menu1.add(openMenuItem);

					//---- saveMenuItem ----
					saveMenuItem.setText("Save Session");
					saveMenuItem.setMnemonic('S');
					saveMenuItem.setEnabled(false);
					saveMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, KeyEvent.CTRL_MASK));
					saveMenuItem.addActionListener(e -> saveMenuItemActionPerformed(e));
					menu1.add(saveMenuItem);

					//---- closeMenuItem ----
					closeMenuItem.setText("Close");
					closeMenuItem.setEnabled(false);
					closeMenuItem.addActionListener(e -> closeMenuItemActionPerformed(e));
					menu1.add(closeMenuItem);
					menu1.addSeparator();

					//---- exportMenuItem ----
					exportMenuItem.setText("Export");
					exportMenuItem.setMnemonic('E');
					exportMenuItem.setEnabled(false);
					exportMenuItem.addActionListener(e -> exportMenuItemActionPerformed(e));
					menu1.add(exportMenuItem);
					menu1.addSeparator();

					//---- r0 ----
					r0.setText("text");
					menu1.add(r0);

					//---- r1 ----
					r1.setText("text");
					menu1.add(r1);

					//---- r2 ----
					r2.setText("text");
					menu1.add(r2);

					//---- r3 ----
					r3.setText("text");
					menu1.add(r3);

					//---- r4 ----
					r4.setText("text");
					menu1.add(r4);

					//---- r5 ----
					r5.setText("text");
					menu1.add(r5);

					//---- r6 ----
					r6.setText("text");
					menu1.add(r6);

					//---- r7 ----
					r7.setText("text");
					menu1.add(r7);

					//---- r8 ----
					r8.setText("text");
					menu1.add(r8);

					//---- r9 ----
					r9.setText("text");
					menu1.add(r9);
					menu1.addSeparator();

					//---- exitMenuItem ----
					exitMenuItem.setText("Exit");
					exitMenuItem.setMnemonic('X');
					exitMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X, KeyEvent.CTRL_MASK));
					exitMenuItem.addActionListener(e -> exitMenuItemActionPerformed(e));
					menu1.add(exitMenuItem);
				}
				menuBar.add(menu1);

				//======== menu2 ========
				{
					menu2.setText("View");
					menu2.setIcon(null);
					menu2.setMnemonic('V');

					//---- studyMenuItem ----
					studyMenuItem.setText("Study");
					studyMenuItem.setEnabled(false);
					studyMenuItem.addActionListener(e -> studyMenuItemActionPerformed(e));
					menu2.add(studyMenuItem);

					//---- annotationsMenuItem ----
					annotationsMenuItem.setText("Annotations");
					annotationsMenuItem.setEnabled(false);
					annotationsMenuItem.addActionListener(e -> annotationsMenuItemActionPerformed(e));
					menu2.add(annotationsMenuItem);

					//---- phasesMenuItem ----
					phasesMenuItem.setText("Phases");
					phasesMenuItem.addActionListener(e -> phasesMenuItemActionPerformed(e));
					menu2.add(phasesMenuItem);

					//---- b2bAnnotations ----
					b2bAnnotations.setText("B2B Annotations");
					b2bAnnotations.addActionListener(e -> b2bAnnotationsActionPerformed(e));
					menu2.add(b2bAnnotations);
					menu2.addSeparator();

					//---- cboxShowGraphTimeline ----
					cboxShowGraphTimeline.setText("Graph Timeline");
					cboxShowGraphTimeline.setEnabled(false);
					cboxShowGraphTimeline.addActionListener(e -> cboxShowGraphTimelineActionPerformed(e));
					menu2.add(cboxShowGraphTimeline);

					//---- cboxShowLegend ----
					cboxShowLegend.setText("Graph Legend");
					cboxShowLegend.setEnabled(false);
					cboxShowLegend.addActionListener(e -> cboxShowLegendActionPerformed(e));
					menu2.add(cboxShowLegend);

					//---- cboxCursorValue ----
					cboxCursorValue.setText("Cursor Value");
					cboxCursorValue.setEnabled(false);
					cboxCursorValue.addActionListener(e -> cboxCursorValueActionPerformed(e));
					menu2.add(cboxCursorValue);

					//---- cboxNavigation ----
					cboxNavigation.setText("Navigation Assistance");
					cboxNavigation.setEnabled(false);
					cboxNavigation.addActionListener(e -> cboxNavigationActionPerformed(e));
					menu2.add(cboxNavigation);
					menu2.addSeparator();

					//---- reset ----
					reset.setText("Reset");
					reset.addActionListener(e -> resetActionPerformed(e));
					menu2.add(reset);

					//---- preferencesMenuItem ----
					preferencesMenuItem.setText("Preferences");
					preferencesMenuItem.addActionListener(e -> preferencesMenuItemActionPerformed(e));
					menu2.add(preferencesMenuItem);
				}
				menuBar.add(menu2);

				//======== menu3 ========
				{
					menu3.setText("Run");
					menu3.setMnemonic('R');

					//---- consoleMenuItem ----
					consoleMenuItem.setText("Console");
					consoleMenuItem.setMnemonic('C');
					consoleMenuItem.addActionListener(e -> consoleMenuItemActionPerformed(e));
					menu3.add(consoleMenuItem);

					//---- rScriptMenuItem ----
					rScriptMenuItem.setText("R Script");
					rScriptMenuItem.setEnabled(false);
					menu3.add(rScriptMenuItem);

					//---- javaScriptMenuItem ----
					javaScriptMenuItem.setText("Java Script");
					javaScriptMenuItem.setEnabled(false);
					javaScriptMenuItem.addActionListener(e -> javaScriptMenuItemActionPerformed(e));
					menu3.add(javaScriptMenuItem);
					menu3.addSeparator();

					//---- analysisMenuItem ----
					analysisMenuItem.setText("Analysis");
					analysisMenuItem.setEnabled(false);
					analysisMenuItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, KeyEvent.CTRL_MASK));
					analysisMenuItem.addActionListener(e -> analysisMenuItemActionPerformed(e));
					menu3.add(analysisMenuItem);
				}
				menuBar.add(menu3);
			}
			panel4.add(menuBar, CC.xy(1, 1));
		}
		contentPane.add(panel4, BorderLayout.PAGE_START);
		pack();
		setLocationRelativeTo(getOwner());
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JPanel panel4;
	private JMenuBar menuBar;
	private JMenu menu1;
	private JMenuItem setupMenuItem;
	private JMenuItem newMenuItem;
	private JMenuItem openMenuItem;
	private JMenuItem saveMenuItem;
	private JMenuItem closeMenuItem;
	private JMenuItem exportMenuItem;
	private JMenuItem r0;
	private JMenuItem r1;
	private JMenuItem r2;
	private JMenuItem r3;
	private JMenuItem r4;
	private JMenuItem r5;
	private JMenuItem r6;
	private JMenuItem r7;
	private JMenuItem r8;
	private JMenuItem r9;
	private JMenuItem exitMenuItem;
	private JMenu menu2;
	private JMenuItem studyMenuItem;
	private JMenuItem annotationsMenuItem;
	private JMenuItem phasesMenuItem;
	private JMenuItem b2bAnnotations;
	private JCheckBoxMenuItem cboxShowGraphTimeline;
	private JCheckBoxMenuItem cboxShowLegend;
	private JCheckBoxMenuItem cboxCursorValue;
	private JCheckBoxMenuItem cboxNavigation;
	private JMenuItem reset;
	private JMenuItem preferencesMenuItem;
	private JMenu menu3;
	private JMenuItem consoleMenuItem;
	private JMenuItem rScriptMenuItem;
	private JMenuItem javaScriptMenuItem;
	private JMenuItem analysisMenuItem;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public List<TsCode> getCodeModel() {
		if (prefs == null) {
			return null;
		}
		return prefs.getCodes();
	}

	public void setPrefsFile(File prefsFile) {
		this.prefsFile = prefsFile;
		try {
			prefs = TsoSetupXMLUtil.getSetup(prefsFile);
		} catch (Exception e) {
			log.warn("Could not load prefs file: {}", prefsFile);
		}
		if (prefs == null) {
			prefs = TsoSetupXMLUtil.getDefaultSetup();
		}
		tpanel.refresh(prefs);
	}

	public TsoPrefs getPrefs() {
		return prefs;
	}

	public static PiSubjectImporter getImporter() {
		return study_importer;
	}

	public String getSubject() {
		return subject_name;
	}

	public void setConsole(ConsolePanel console) {
		this.console = console;
	}

	public TsPSwingCanvas getCanvas() {
		return tpanel.getCanvas1();
	}

}
