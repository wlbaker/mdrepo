/*
 * Created by JFormDesigner on Tue Sep 29 08:46:30 CDT 2009
 */

package idea.meddaq;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.plaf.ProgressBarUI;
import javax.swing.plaf.synth.SynthContext;
import javax.swing.plaf.synth.SynthProgressBarUI;
import javax.swing.plaf.synth.SynthStyle;
import javax.swing.tree.DefaultMutableTreeNode;

import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;
import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryAction;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.DiscoveryService;
import idea.conf.DeviceConfiguration;
import idea.display.ChartRefresher;
import idea.display.InstrumentDisplayInterface;
import idea.display.editor.BandEditorPanel;
import idea.display.editor.DisplayEditorManager;
import idea.display.elegant.ElegantDisplayForm;
import idea.display.simple.SingleDeviceForm;
import idea.driver.InfinityDriver;
import idea.driver.NullStreamProducer;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.Annotation;
import idea.model.DisplayConfig;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Field;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.pistax.PistaUtil;

import lombok.extern.slf4j.Slf4j;
import idea.AdapterGui;
import idea.GlobalHotkeyManager;
import idea.GuiUtil;
import idea.ToneUtil;
import idea.analysis.AnalysisFactory;
import idea.analysis.AnalysisPanelInterface;
import idea.studywiz.BeginStudyWizard;
import idea.devwizard.SetupWizard;
import idea.devwizard.WizDeviceDetectionPanel;
import idea.gui.DialogActionListener;
import idea.meddaq.AppSetup;
import idea.simulator.SimulatorWizard;
import idea.studywiz.BeginStudyWizard;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;
import com.jtattoo.plaf.BaseProgressBarUI;
import com.sun.speech.freetts.Voice;
import com.sun.speech.freetts.VoiceManager;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
@Slf4j
public class MedDAQFrame extends JFrame
		implements StreamConsumer, ActionListener, DiscoveryListener, PropertyChangeListener {

	public static final String APP_RELEASE = "September 4, 2023";
	public static final String APP_VERSION = "0.9.9";
	public static final String APP_NAME = "MgDAQ";

	private static int NOT_CAPTURING_TIMEOUT_SEC = 600;
	
	MedDAQPanel mp;
	private RunMode runMode = null;
	int armed = 1;
	private RpSubject header;

	private static MedDAQFrame instance = null;
	boolean vid_recording = false;
	long vid_start = 0;
	int has_beeped = 0;
	boolean recordingAudio = false;
	boolean recordingVideo = false;
	private String appName;

	File annotationDir;

	RpStudy study;
	RpHardware hardware;
	long startTime;

	JMenuItem startCaptureButton;
	JMenuItem stopCaptureButton;

	DiscoveryService discovery = DiscoveryService.getInstance();

	public static MedDAQFrame getInstance() {
		return instance;
	}

	DateFormat dateFormat = new SimpleDateFormat("dd-MMM-yyyy");

	// private CaptureFfmpegUtil ffmpeg = new CaptureFfmpegUtil();

	public MedDAQFrame(String title) {
		super(title);
		initComponents();

		log.info("starup");

		MedDAQFrame.instance = this;
		this.appName = title;

		manageDevices.setEnabled(false);

		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE); // let me take
		// care of it
		// myself

		addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent e) {

				// super.windowClosing(e);
				exitItemActionPerformed(null);
			}

		});

		getContentPane().add(menuBar, BorderLayout.NORTH);
		mp = new MedDAQPanel();

		getContentPane().add(mp, BorderLayout.CENTER);

		mp.addPropertyChangeListener(MedDAQPanel.EDITABLE_DISPLAY, this);
		autoScale.setEnabled(false);
		penMenu.setEnabled(false);
		scaleMenu.setEnabled(false);

		// menuBar.setHelpMenu( helpMenu );
		// menuBar.add
		menuBar.add(helpMenu);
		createTitlebarComponents();

		enableActionButtons(false);
		startTimeoutTicker(); // always runs
		initEnterOnAnnoText();

		Timer swingTimer = new Timer(500, this);
		swingTimer.start();

		setRunMode(RunMode.STOP); // must call after creating xmetricsPanel

		discovery.addListener(this);

		log.error("SKIPPING INIT SERIAL PORTS");
		// initSerialPorts();

		manageDevices.setEnabled(true);

		this.addComponentListener(new ComponentAdapter() {

			@Override
			public void componentResized(ComponentEvent e) {
				int w = getWidth();
				// if substanceLAF
				//startCaptureButton.setBounds(w - 300, 2, 90, 16);
				//stopCaptureButton.setBounds(w - 200, 2, 90, 16);
			}

		});
		
		if( title.indexOf("DEBUG") > 0 ) {
			NOT_CAPTURING_TIMEOUT_SEC = 10;
		}
	}


	/*
	 * Substance support
	 */
	/*
	private void createTitlebarComponents() {
		startCaptureButton = new JButton("Capture");
		startCaptureButton.setFocusable(false);
		// startCaptureButton.setBounds(100, 3, 90, 22);
		startCaptureButton.setBackground(Color.GREEN);
		startCaptureButton.setEnabled(false);
		startCaptureButton.addActionListener(e -> startCaptureActionPerformed(e));
		startCaptureButton.setBorder( new EmptyBorder(1,1,1,1));

		stopCaptureButton = new JButton("Stop Capture");
		stopCaptureButton.setFocusable(false);
		// stopCaptureButton.setBounds(200, 3, 90, 32);
		stopCaptureButton.setBackground(Color.RED);
		stopCaptureButton.setEnabled(false);
		stopCaptureButton.addActionListener(e -> stopCaptureActionPerformed(e));
		stopCaptureButton.setBorder(null);
		// JComponent gp = (JComponent) getGlassPane();
		// gp.setLayout(null);

		 * it takes a little twiddling to put an item in the title bar -1- the
		 * title bar must be rendered by swing, not the OS -2- methods are L&F
		 * specific -3- items must have a specific property set the value of
		 * which... -4- is no a class scope protected enum called
		 * ExtraComponentKind
		
		String EXTRA_COMPONENT_KIND_CLASS_NAME = "org.pushingpixels.substance.internal.utils.SubstanceTitlePane$ExtraComponentKind";
		JComponent titlePanel = SubstanceLookAndFeel.getTitlePaneComponent(this);
		Object kind = null;
		try {
			Class<?>[] clazzs = SubstanceTitlePane.class.getDeclaredClasses();
			for (Class<?> cl : clazzs) {
				if (cl.getName().equals(EXTRA_COMPONENT_KIND_CLASS_NAME)) {
					Object[] consts = cl.getEnumConstants();

					kind = consts[2]; // MIDDLING
					break;
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		startCaptureButton.putClientProperty("substancelaf.internal.titlePane.extraComponentKind", kind);
		stopCaptureButton.putClientProperty("substancelaf.internal.titlePane.extraComponentKind", kind);

		titlePanel.add(startCaptureButton);
		titlePanel.add(stopCaptureButton);
	}
    */

	private void createTitlebarComponents() {
		startCaptureButton = new JMenuItem("Capture");
		startCaptureButton.setFocusable(false);
		// startCaptureButton.setBounds(100, 3, 90, 22);
		startCaptureButton.setBackground(Color.GREEN);
		startCaptureButton.setEnabled(false);
		startCaptureButton.addActionListener(e -> startCaptureActionPerformed(e));
		startCaptureButton.setBorder( new EmptyBorder(1,1,1,1));

		stopCaptureButton = new JMenuItem("Stop Capture");
		stopCaptureButton.setFocusable(false);
		// stopCaptureButton.setBounds(200, 3, 90, 32);
		stopCaptureButton.setBackground(Color.RED);
		stopCaptureButton.setEnabled(false);
		stopCaptureButton.addActionListener(e -> stopCaptureActionPerformed(e));
		stopCaptureButton.setBorder(null);
		//		JComponent gp = (JComponent) getGlassPane();
//		gp.setLayout(null);
//		gp.add(startCaptureButton);
//		gp.add(stopCaptureButton);
//		gp.setVisible(true);
		// menuBar.add(new JMenu("|"));
		JSeparator sep = new JSeparator();
		sep.setOpaque(true);
		menuBar.add( sep  );
		menuBar.add( startCaptureButton );
		menuBar.add( stopCaptureButton );
		
		Dimension sz = new Dimension(100,20);
		startCaptureButton.setPreferredSize(sz);
		startCaptureButton.setMaximumSize(sz);
		startCaptureButton.setMinimumSize(sz);
		
		stopCaptureButton.setPreferredSize(sz);
		stopCaptureButton.setMaximumSize(sz);
		stopCaptureButton.setMinimumSize(sz);
		
		// LAF
		elapsedTime.setBackground(Color.DARK_GRAY);
		clockLabel.setBackground(Color.DARK_GRAY);
		diskProgressBar.setStringPainted(true);
		diskProgressBar.setString("Disk");
		diskProgressBar.setForeground(Color.GREEN);
		diskProgressBar.setBackground(Color.DARK_GRAY);
		ProgressBarUI ui = diskProgressBar.getUI();
		// SynthProgressBarUI sui = (SynthProgressBarUI) ui;
		com.jtattoo.plaf.BaseProgressBarUI tui = (BaseProgressBarUI) ui;
		// SynthContext ctx = sui.getContext(diskProgressBar);
		// SynthStyle styl = ctx.getStyle();
		System.out.println("ui=" + tui);
	}
	
	public void setHeader(RpSubject header) {
		this.header = header;
	}

	public RunMode getRunMode() {
		return runMode;
	}

	public void setRunMode(RunMode runMode) {
		if (runMode == this.runMode) {
			return;
		}

		this.runMode = runMode;

		mp.setRunMode(runMode);

		// statusBar.setRunMode( runMode );

		if (runMode == RunMode.STOP) {
			mark.setEnabled(false);
			annoText.setEnabled(false);

		} else if (runMode == RunMode.RUN) {
			dateFormat = new SimpleDateFormat("dd-MMM-yyyy");
			mark.setEnabled(true);
			annoText.setEnabled(true);

			startCaptureButton.setVisible(true);
			stopCaptureButton.setVisible(true);

			armOverlayMessage();
		} else if (runMode == RunMode.SIMULATION) {
			dateFormat = new SimpleDateFormat("dd-MMM-yyyy  HH:mm:ss");
			mark.setEnabled(false);
			annoText.setEnabled(false);
		}
		updateIcons();
	}

	private void startTimeoutTicker() {
		Runnable r = new Runnable() {

			@Override
			public void run() {

				for (;;) {
					try {
						Thread.sleep(1000);
						if (getRunMode() == RunMode.RUN) {
							try {
								// done by time in serial discovery

								// ... serial_discovery.tick_probes(), really
								// through tick_all()

								discovery.tick();
							} catch (Exception e) {
								e.printStackTrace();
							}
							AppModel.tick(); // analysis modules
						}
						if (vid_recording) {
							Calendar cal = Calendar.getInstance();
							long diff = vid_start - cal.getTimeInMillis();
							int beeps = (int) (diff / 10000);
							if (beeps > has_beeped) {
								has_beeped = beeps;
								ToneUtil.playTone(250, 6000, 10);
							}
						}
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}

			}
		};

		Thread t = new Thread(r);
		t.start();
	}

	private void initEnterOnAnnoText() {

		annoText.putClientProperty(GlobalHotkeyManager.IGNORE_HOTKEY, true);
		annoText.addKeyListener(new KeyListener() {

			@Override
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					annotationActionPerformed(null);
				}
			}

			@Override
			public void keyReleased(KeyEvent e) {
			}

			@Override
			public void keyTyped(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					annotationActionPerformed(null);
				}
			}

		});
	}

	private void exitItemActionPerformed(ActionEvent evt) {

		// SimulatorControlSubpanel simu = mp.getSimulatorPanel();
		// if (simu != null) {
		// simu.disconnect();
		// }
		//
		String message = // "You have edits in progress in: " + tabName
				"\n\nContinue closing?";
		int ok = JOptionPane.showConfirmDialog(null, message, "Confirm Shutdown", JOptionPane.OK_CANCEL_OPTION);
		if (ok != JOptionPane.OK_OPTION) {
			return; // don't shut down if any edits in progress that are not OK
		}
		_endStudyActionPerformed(null);

		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		this.dispose();
		System.exit(0);
	}

	private void setupMenuActionPerformed(ActionEvent e) {

		// final WizParentPanel panel = new WizParentPanel();
		SetupWizard panel = new DataCollectionWizard();


		GuiUtil.doDialog("Application Setup", this, panel, null);
	}

	private void autoScaleActionPerformed(ActionEvent e) {
		mp.autoScale(null);
	}

	private void simulationActionPerformed(ActionEvent e) {
		final SimulatorWizard wiz = new SimulatorWizard();

		try {
			GuiUtil.doDialog("Begin Simulation", this, wiz, null);

			if (wiz.isExecute()) {

				study = wiz.getStudy();

				RpSubject header = null;
				startStudyAction(study, study.getHardware().get(0), header, true);
				mp.setRunMode(RunMode.SIMULATION);
				StreamProducer simu = null; // mp.getSimulatorPanel();

				 PiSubjectImporter importer = wiz.getConnectedImporter();
				mp.loadAnnotations(importer.getDatastreamImporter("Annotations", StreamID.ANNOTATION));

				importer.rewind();

				mp.clear();

				String method = wiz.getSimulationMethod();
				if ("repository".equals(method)) {
					String repository = wiz.getSimulationRepository();

					if (repository == null || repository.equals("file")) {

						// WHAT IS THIS?
					}
				} else if ("file".equals(method)) {

					// } else if ("device".equals(method)) {
					// String ip = wiz.getConnection();
					//
					// SocketDeviceConfiguration conf =
					// IDEADriver.createConfigInstance();
					// conf.setHost(ip);
					// conf.setPort(IDEADriver.DEFAULT_IDEA_UDP_PORT);
					//
					// IDEADriver driver = new IDEADriver(conf);
					// ImporterInterface importer = wiz.getConnectedImporter();
					//
					// // driver.addEventListener(type, l);
					// driver.connect();
					//
					// int jobId = 4444;
					//
					// Date dtStart = wiz.getMetaStartTime();
					// Date dtStop = wiz.getMetaEndTime();
					// Calendar cal = Calendar.getInstance();
					// cal.setTime(dtStop);
					// cal.add(Calendar.HOUR, -2);
					// IDEATransferRequest req =
					// driver.createTransferRequest(jobId, dtStart, dtStop,
					// null, 0);
					// req.addEventListener(null, MgDaqFrame.this);
					// req.startTransfer();
					// GuiUtil.showMessage("createTransferRequest...Probably
					// wrong listener!");

				}

				GuiUtil.showMessage("FIXME: simulation driver not available");
				// //DeviceConfiguration conf =
				// SimulationDriver.createConfigInstance();
				// //SimulationDriver sim = new SimulationDriver(conf,
				// importer);
				//
				// //simu.runSimulator(sim, importer); // AppModel.driverList);
				//
				// PiDatastreamImporter[] devs = new PiDatastreamImporter[] {}; //
				// sim.getDevices();
				// for (int idx = 0; idx < devs.length; idx++) {
				// PiDatastreamImporter dev = devs[idx];
				// String name = dev.getName();
				// if (dev instanceof StreamProducer) {
				// discovery.addDevice(name, (StreamProducer) dev);
				// } else {
				// log.warn("ignoring non-producer: {}", name);
				// }
				// }

				ChartRefresher refresher = ChartRefresher.getInstance();
				refresher.start();
			}
		} catch (Exception e1) {
			GuiUtil.showError("Starting Study: ", e1);
		}
	}

	public void beginStudyActionPerformed(ActionEvent e) {
		beginStudyActionPerformed(e, null);
	}

	public void beginStudyActionPerformed(ActionEvent e, String study) {
		final BeginStudyWizard panel = new BeginStudyWizard(study);

		GuiUtil.doDialog("Begin Study", this, panel, null);

		try {

			if (panel.isExecute()) {
				discovery.addSerialDiscovery(panel.getPorts());
				discovery.addManualDiscovery();

				mp.setRunMode(RunMode.RUN);
				startStudyAction(panel.getStudy(), panel.getHardware(), panel.getSubjectInfo(), false);
			}
		} catch (Exception e1) {
			GuiUtil.showError("Starting Study: ", e1);
		}
	}

	public void startStudyAction(RpStudy study, RpHardware hd, RpSubject h, boolean simulation)
			throws IOException, InterruptedException {

		this.study = study;
		this.hardware = hd;

		mp.reset();

		AppSetup.setRpSubject(h);
		if (hd == null) {
			return;
		}

		List<RpDevice> devConfs = hd.getDevices();

		String title = appName;
		if (h != null) {
			String studyTitle = h.getStudyTitle();
			String studySubject = h.getMedicalId();

			title += " - " + studyTitle + "/" + studySubject;

		}
		title = title.replace("[SERVER]", "");

		if (simulation) {
			title += " [SIMULATION]";
		}
		setTitle(title);

		showMessage("Starting devices...");
		enableActionButtons(true);

		try {
			startDevices(devConfs);
			// discovery.setDevices(devConfs);
			// discovery.start();

			autoScale.setEnabled(true);
			penMenu.setEnabled(true);
			scaleMenu.setEnabled(true);

		} catch (Exception e) {
			// AlarmItem item = new AlarmItem("frame-xx", AlarmItem.FATAL, 0,
			// e.toString(), true);
			//
			// AlarmEvent ae = new AlarmEvent(this, item);
			// mp.signalAlarmEvent(ae);
			GuiUtil.showError("Starting Devices", e);
		}

		showMessage("Preparing analysis");

		Thread.sleep(3000);
		startAnalysis(study.getAnalysis());

		AppModel.startGlobalPanel(mp);

		setHeader(h);

		if (simulation) {
			showMessage("Simulation");
			setRunMode(RunMode.SIMULATION);
		} else {
			showMessage("Running");
			setRunMode(RunMode.RUN);
		}

		mp.doLayout();
		doLayout();

		// pack();
	}

	private void startDevices(List<RpDevice> devConfs) throws IOException {

		// add all the expected devices to create the data structures
		for (RpDevice rpdev : devConfs) {

			String connectionName = rpdev.getConnectionValue();
			if (rpdev.getConnectionType() == RpConnType.ETHERNET) {
				connectionName = "socket";
			}

			if ("[DISCONNECTED]".equals(connectionName)) {
				log.warn("DEVICE DISCONNECTED: {}", rpdev.getName());
			} else {
				try {
					StreamProducer driver = (StreamProducer) discovery.addDevice(rpdev);
					log.error("FIXME: calling connect out of sequence");
					if (driver instanceof InfinityDriver) {
						InfinityDriver inf = (InfinityDriver) driver;
						inf.connect();  // FIXME: this is needed because other driver connections are handled by the discovery service!
					}
					
				} catch (IOException io) {
					GuiUtil.showError("Error starting device: " + rpdev.getName(), io);
					mp.addMessage(new Date(), "SYSTEM", Alarm.FATAL, io.getMessage());
				}

			}

		}
	}

	public void showMessage(String msg) {
		message.setText(msg);

	}

	// private void startDevices(List<RpDevice> devConfs, boolean simulation) {
	//
	// autoScale.setEnabled(true);
	// penMenu.setEnabled(true);
	// scaleMenu.setEnabled(true);
	//
	// return;
	// }

	private void startAnalysis(List<RpAnalysis> subanals) {

		for (RpAnalysis anal : subanals) {
			AnalysisPanelInterface one = addOneAnalysis(anal);
			AppModel.addAnalysis(one);

		}

	}

	private void _addAll(LinkedList<StreamProducer> ll, StreamProducer[] producers) {
		if (producers != null) {
			for (StreamProducer p : producers) {
				ll.add(p);
			}
		}
	}

	private AnalysisPanelInterface addOneAnalysis(RpAnalysis anal) {
		LinkedList<StreamProducer> ll = new LinkedList<StreamProducer>();
		_addAll(ll, discovery.getDeviceDrivers());
		_addAll(ll, AppModel.getAnalysisDrivers());

		StreamProducer[] drivers = new StreamProducer[ll.size()];
		ll.toArray(drivers);

		AnalysisPanelInterface api = null;
		try {
			api = AnalysisFactory.buildAnalysisPanel(ExportManager.getDerivedExporter(), anal, drivers);
			if (api != null && api instanceof JPanel ) {
				JPanel panel = (JPanel) api;
				mp.addPanel(panel.getName(), new JScrollPane(panel), ConnectionStatus.DATA_AVAILABLE );
			}
		} catch (UnsatisfiedLinkError e) {
			log.error("Error starting analysis", e);
			GuiUtil.showError("Analysis Link Error: " + anal.getName() + "/" + anal.getAnalysisClass(), e);
		} catch (Exception e) {
			log.error("Error starting analysis: " + anal.getName() + "/" + anal.getAnalysisClass(), e);
			GuiUtil.showError("Analysis Error: " + anal.getName() + "/" + anal.getAnalysisClass(), e);
		}
		
		return api;
	}

	protected void enableActionButtons(boolean b) {
		beginStudy.setEnabled(!b);
		startCaptureButton.setEnabled(b && !AppModel.isCapturing());
		stopCaptureButton.setEnabled(b && AppModel.isCapturing());

		endStudy.setEnabled(b);
		studyDetail.setEnabled(b);

		startCapture.setEnabled(b && !AppModel.isCapturing());
		stopCapture.setEnabled(b && AppModel.isCapturing());
	}

	private void endStudyActionPerformed(ActionEvent e) {

		int ok = GuiUtil.showConfirmDialog("Are you sure you want to end this study?", "End Study",
				JOptionPane.YES_NO_CANCEL_OPTION);
		if (ok != JOptionPane.YES_OPTION) {
			return;
		}
		_endStudyActionPerformed(e);
	}

	private void _endStudyActionPerformed(ActionEvent e) {
		// first, terminate capture, if applicable
		stopCaptureActionPerformed(null);

		discovery.stop(); // this should remove all panels
		ChartRefresher.getInstance().reset();

		try {
			PistaUtil.stop();
		} catch (UnsatisfiedLinkError le) {
			log.error("Pista stop failed: {}", le.getMessage());
		}
		// now change enabled flags
		enableActionButtons(false);

		// and clear the mp screen
		mp.setRunMode(RunMode.STOP);
		try {
			mp.reset();
		} catch (Exception xx) {
			// ignore
			log.warn("Could not clear MP", xx);
		}

		this.setTitle(appName);
	}

	private void syncRepoActionPerformed(ActionEvent e) {
		GuiUtil.showMessage("This option is not enabled.");
	}

	private void aboutActionPerformed(ActionEvent e) {
		JPanel panel = new AboutPanel();
		GuiUtil.doDialog("About", this, panel, null);
	}
	
	private void studyDetailActionPerformed(ActionEvent e) {
	}
/* WLB 2023
	private void studyDetailActionPerformed(ActionEvent e) {
		File detailFile = AppSetup.getStudyDetailFileName();
		try {
			Map<String, String> map = QuestionAnswerUtils.readNamedPairs(detailFile);

			JPanel p = AppSetup.getStudyQuestionaire(detailFile.getParent());
			QuestionAnswerUtils.populateNamedPairs(p, map);

			int ok = JOptionPane.showConfirmDialog(this, p, "Study Questionaire", JOptionPane.OK_CANCEL_OPTION);
			if (ok == JOptionPane.OK_OPTION) {
				// p.saveKvPairs();
				QuestionAnswerUtils.getNamedPairs(p, map);
				QuestionAnswerUtils.writeNamedPairs(detailFile, map);

			}
			// }
		} catch (Exception e1) {
			GuiUtil.showError("Error in questionaire data", e1);
		}
	}
*/
	
	private void newFrameActionPerformed(ActionEvent e) {
		JOptionPane.showMessageDialog(this, "This feature is disabled.");
	}

	private void pen1ActionPerformed(ActionEvent e) {
		BasicStroke stroke = new BasicStroke(1.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL);
		mp.setStroke(stroke);
	}

	private void pen2ActionPerformed(ActionEvent e) {
		BasicStroke stroke = new BasicStroke(20.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL);
		mp.setStroke(stroke);
	}

	private void pen3ActionPerformed(ActionEvent e) {
		BasicStroke stroke = new BasicStroke(30.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL);
		mp.setStroke(stroke);
	}

	private void annotationActionPerformed(ActionEvent e) {

		String message = annoText.getText();
		putAnnotation(message);
	}

	private void putAnnotation(String message) {
		PiSubjectExporter exporter = ExportManager.getDataExporter();
		if (exporter == null) {
			return;
		}

		Calendar cal = Calendar.getInstance();
		ToneUtil.playTone(250, 4000, 10);
		Annotation anno = new Annotation(cal.getTimeInMillis(), message);

		exporter.streamEvent(0, null, StreamID.ANNOTATION, anno);
		mp.addMessage(cal.getTime(), "daq", Alarm.INFO, message);

		annoText.setText("");
	}

	public void startCaptureActionPerformed(ActionEvent e) {
		try {
			Calendar cal = Calendar.getInstance();
			int yr = cal.get(Calendar.YEAR);
			int mon = cal.get(Calendar.MONTH) + 1;
			int day = cal.get(Calendar.DAY_OF_MONTH);
			int hr = cal.get(Calendar.HOUR_OF_DAY);
			int min = cal.get(Calendar.MINUTE);
			int sec = cal.get(Calendar.SECOND);
			String dateAndTime = String.format("%d_%02d_%02d_%02d.%02d.%02d", yr, mon, day, hr, min, sec);

			File baseFile = new File(header.getMedicalId());
			baseFile = new File(baseFile, dateAndTime);

			System.setProperty("SUBJECT", header.getMedicalId());
			System.setProperty("DATETIME", dateAndTime);

			ExportManager.initDB(study, header);

			ExportManager.startDeviceCapture(study, discovery.getDeviceDrivers(), header, baseFile.getPath());
			ExportManager.startDerivedCapture(study, AppModel.getAnalysisDrivers(), header, baseFile.getPath());

			AppModel.setCapturing(true);

			enableActionButtons(true);
			updateIcons();

		} catch (Exception e1) {
			GuiUtil.showError("Start Capture:", e1);
		}
	}

	public void stopCaptureActionPerformed(ActionEvent e) {
		try {
			ExportManager.disconnect();

			AppModel.setCapturing(false);
			enableActionButtons(runMode == RunMode.RUN);
			updateIcons();

		} catch (Exception e1) {
			GuiUtil.showError("Stop Capture", e1);
		}

	}

	private void captureOptionsActionPerformed(ActionEvent e) {

		CaptureOptions panel = new CaptureOptions();
		GuiUtil.doDialog("Capture Options", this, panel, null);
	}

	private void recordAudioActionPerformed(ActionEvent e) {
		try {
			_recordAudioActionPerformed(e);
		} catch (Throwable ex) {
			GuiUtil.showError("Could not start audio recording", ex);
		}
	}

	private void recordVideoActionPerformed(ActionEvent e) {
		try {
			_recordVideoActionPerformed(e);
		} catch (Throwable ex) {
			GuiUtil.showError("Could not start video recording", ex);
		}
	}

	private void _recordVideoActionPerformed(ActionEvent e) {
		recordingVideo = !recordingVideo;
		updateIcons();
		
		
//		if (recordingAudio) {
//			File f = getNewAnnotationFile("audio", "mp3");
//			ffmpeg .beginVideoCapture(f);
//			putAnnotation("START FFMPEG VIDEO: " + f.getPath());
//		} else {
//			ffmpeg.endVideoCapture();
//			putAnnotation("END FFMPEG VIDEO");
//		}
	}
	
	private void _recordAudioActionPerformed(ActionEvent e) {
		recordingAudio = !recordingAudio;
		updateIcons();

		if (recordingAudio) {
			File f = getNewAnnotationFile("audio", "mp3");
			CaptureXugglerUtil.beginAudioCapture(f);
			putAnnotation("START AUDIO: " + f.getPath());
		} else {
			CaptureXugglerUtil.endAudioCapture();
			putAnnotation("END AUDIO");
		}
	}

	private void screenCaptureActionPerformed(ActionEvent e) {

		File f = getNewAnnotationFile("screenshot", "jpg");
		try {
			CaptureXugglerUtil.captureScreenShot(f, mp);
			putAnnotation("SCREENCAP: " + f.getPath());
		} catch (Exception e1) {
			GuiUtil.showError("Screen Capture", e1);
		}
	}

	private File getNewAnnotationFile(String prefix, String extension) {
		Calendar cal = Calendar.getInstance();

		DateFormat fmt = new SimpleDateFormat("yyyy-MM-dd_hhmmss");

		if (annotationDir == null) {
			annotationDir = ExportManager.getArchiveDir();
		}
		if (annotationDir == null) {
			annotationDir = GuiUtil.doOpenFileChooser(JFileChooser.DIRECTORIES_ONLY, "Select screenshot directory",
					this, null, null);
		}

		String fileName = prefix + "-" + fmt.format(cal.getTime()) + "." + extension;
		return new File(annotationDir, fileName);
	}

	private void updateIcons() {
		boolean anno_ena = false;

		if (AppModel.isCapturing()) {
			recordAudio.setEnabled(true);
			anno_ena = true;
			if (recordingAudio == false) {
				// green...you can start capture
				recordAudio.setIcon(new ImageIcon(getClass().getResource("/idea/image/MicrophoneNormal.png")));
			} else {
				recordAudio.setIcon(new ImageIcon(getClass().getResource("/idea/image/MicrophoneNormalRed.png")));
			}
		} else {
			// disabled...not capturing
			recordAudio.setIcon(new ImageIcon(getClass().getResource("/idea/image/MicrophoneDisabled.png")));
			recordAudio.setEnabled(false);
		}
		mark.setEnabled(anno_ena);
		annoText.setEnabled(anno_ena);

		screenCapture.setEnabled(runMode == RunMode.RUN || runMode == RunMode.SIMULATION);

	}

	private void manageDeviceActionPerformed(ActionEvent e) {

		WizDeviceDetectionPanel discoveryPanel = new WizDeviceDetectionPanel();
		String[] options = {};

		// manual_discovery.addListener( panel );
		discoveryPanel.initDiscovery(discovery);
		discovery.addListener(discoveryPanel);

		JOptionPane p = new JOptionPane(discoveryPanel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options,
				null);
		JDialog d = p.createDialog(this, "Device Management");
		GuiUtil.initModalDialog(d, p); // makes the escape key work
		d.setResizable(true);
		d.pack();
		d.setVisible(true);

		discovery.removeListener(discoveryPanel);
	}

	private void fullScreenActionPerformed(ActionEvent e) {
		if (fullScreen.isSelected()) {
			GuiUtil.initScreen(null, this, true);
		} else {
			GuiUtil.initScreen(null, this, false);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		statusBar = new JPanel();
		message = new JLabel();
		mark = new JButton();
		annoText = new JTextField();
		recordAudio = new JButton();
		elapsedTime = new JTextField();
		clockLabel = new JTextField();
		screenCapture = new JButton();
		diskProgressBar = new JProgressBar();
		menuBar = new JMenuBar();
		menu1 = new JMenu();
		newFrame = new JMenuItem();
		setupMenu = new JMenuItem();
		simulation = new JMenuItem();
		fullScreen = new JCheckBoxMenuItem();
		exitItem = new JMenuItem();
		menu2 = new JMenu();
		scaleMenu = new JMenu();
		menuItem3 = new JMenuItem();
		menuItem4 = new JMenuItem();
		menuItem5 = new JMenuItem();
		penMenu = new JMenu();
		pen1 = new JMenuItem();
		pen2 = new JMenuItem();
		pen3 = new JMenuItem();
		studyDetail = new JMenuItem();
		autoScale = new JMenuItem();
		menu4 = new JMenu();
		beginStudy = new JMenuItem();
		endStudy = new JMenuItem();
		manageDevices = new JMenuItem();
		startCapture = new JMenuItem();
		stopCapture = new JMenuItem();
		menu6 = new JMenu();
		displayEditor = new JMenuItem();
		syncRepo = new JMenuItem();
		captureOptions = new JMenuItem();
		helpMenu = new JMenu();
		about = new JMenuItem();

		// ======== this ========
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		// ======== statusBar ========
		{
			statusBar.setBorder(null);
			statusBar.setLayout(new FormLayout(
					"$lcgap, 50dlu, $lcgap, default, $lcgap, [132dlu,default]:grow, $lcgap, default, 2*($lcgap, [50dlu,default]), 2*($lcgap, default), $lcgap",
					"default, $lgap"));

			// ---- message ----
			message.setText("Ready");
			message.setMaximumSize(new Dimension(21, 14));
			message.setMinimumSize(new Dimension(21, 14));
			message.setPreferredSize(new Dimension(21, 14));
			statusBar.add(message, CC.xy(2, 1));

			// ---- mark ----
			mark.setText("Mark");
			mark.addActionListener(e -> annotationActionPerformed(e));
			statusBar.add(mark, CC.xy(4, 1));
			statusBar.add(annoText, CC.xy(6, 1));

			// ---- recordAudio ----
			recordAudio.setMinimumSize(new Dimension(23, 23));
			recordAudio.setPreferredSize(new Dimension(23, 23));
			// recordAudio.setIcon(new ImageIcon(getClass().getResource("/idea/image/MicrophoneDisabled.png")));
			recordAudio.setToolTipText("Audio Annotation");
			recordAudio.addActionListener(e -> recordAudioActionPerformed(e));
			statusBar.add(recordAudio, CC.xy(8, 1));

			// ---- elapsedTime ----
			elapsedTime.setEditable(false);
			elapsedTime.setEnabled(false);
			elapsedTime.setHorizontalAlignment(SwingConstants.TRAILING);
			elapsedTime.setBackground(Color.red);
			statusBar.add(elapsedTime, CC.xy(10, 1));

			// ---- clockLabel ----
			clockLabel.setEditable(false);
			clockLabel.setEnabled(false);
			clockLabel.setHorizontalAlignment(SwingConstants.TRAILING);
			statusBar.add(clockLabel, CC.xy(12, 1));

			// ---- screenCapture ----
			screenCapture.setText("S");
			screenCapture.setPreferredSize(new Dimension(23, 23));
			screenCapture.setMinimumSize(new Dimension(23, 23));
			screenCapture.setToolTipText("Screen Capture");
			screenCapture.addActionListener(e -> screenCaptureActionPerformed(e));
			statusBar.add(screenCapture, CC.xy(14, 1));

			// ---- diskProgressBar ----
			diskProgressBar.setStringPainted(true);
			statusBar.add(diskProgressBar, CC.xy(16, 1));
		}
		contentPane.add(statusBar, BorderLayout.SOUTH);
		pack();
		setLocationRelativeTo(getOwner());

		// ======== menuBar ========
		{

			// ======== menu1 ========
			{
				menu1.setText("File");
				menu1.setMnemonic('F');

				// ---- newFrame ----
				newFrame.setText("New Frame");
				newFrame.addActionListener(e -> newFrameActionPerformed(e));
				menu1.add(newFrame);
				menu1.addSeparator();

				// ---- setupMenu ----
				setupMenu.setText("Setup");
				setupMenu.setMnemonic('S');
				setupMenu.addActionListener(e -> setupMenuActionPerformed(e));
				menu1.add(setupMenu);

				// ---- simulation ----
				simulation.setText("Simulation");
				simulation.setMnemonic('I');
				simulation.addActionListener(e -> simulationActionPerformed(e));
				menu1.add(simulation);
				menu1.addSeparator();

				// ---- fullScreen ----
				fullScreen.setText("Full Screen");
				fullScreen.addActionListener(e -> fullScreenActionPerformed(e));
				menu1.add(fullScreen);
				menu1.addSeparator();

				// ---- exitItem ----
				exitItem.setText("Exit");
				exitItem.setMnemonic('X');
				exitItem.addActionListener(e -> exitItemActionPerformed(e));
				menu1.add(exitItem);
			}
			menuBar.add(menu1);

			// ======== menu2 ========
			{
				menu2.setText("View");
				menu2.setMnemonic('V');

				// ======== scaleMenu ========
				{
					scaleMenu.setText("Scale");

					// ---- menuItem3 ----
					menuItem3.setText("5 sec");
					scaleMenu.add(menuItem3);

					// ---- menuItem4 ----
					menuItem4.setText("10 sec");
					scaleMenu.add(menuItem4);

					// ---- menuItem5 ----
					menuItem5.setText("15 sec");
					scaleMenu.add(menuItem5);
				}
				menu2.add(scaleMenu);

				// ======== penMenu ========
				{
					penMenu.setText("Pen Size");

					// ---- pen1 ----
					pen1.setText("1 pt");
					pen1.addActionListener(e -> pen1ActionPerformed(e));
					penMenu.add(pen1);

					// ---- pen2 ----
					pen2.setText("2 pt");
					pen2.addActionListener(e -> pen2ActionPerformed(e));
					penMenu.add(pen2);

					// ---- pen3 ----
					pen3.setText("3 pt");
					pen3.addActionListener(e -> pen3ActionPerformed(e));
					penMenu.add(pen3);
				}
				menu2.add(penMenu);

				// ---- studyDetail ----
				studyDetail.setText("Study Detail");
				studyDetail.addActionListener(e -> studyDetailActionPerformed(e));
				menu2.add(studyDetail);

				// ---- autoScale ----
				autoScale.setText("AutoScale");
				autoScale.setMnemonic('A');
				autoScale.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, KeyEvent.CTRL_MASK));
				autoScale.addActionListener(e -> autoScaleActionPerformed(e));
				menu2.add(autoScale);
			}
			menuBar.add(menu2);

			// ======== menu4 ========
			{
				menu4.setText("Action");
				menu4.setMnemonic('A');

				// ---- beginStudy ----
				beginStudy.setText("Begin Study");
				beginStudy.setMnemonic('B');
				beginStudy.addActionListener(e -> beginStudyActionPerformed(e));
				menu4.add(beginStudy);

				// ---- endStudy ----
				endStudy.setText("End Study");
				endStudy.setMnemonic('E');
				endStudy.addActionListener(e -> endStudyActionPerformed(e));
				menu4.add(endStudy);
				menu4.addSeparator();

				// ---- manageDevices ----
				manageDevices.setText("Manage Devices");
				manageDevices.addActionListener(e -> manageDeviceActionPerformed(e));
				menu4.add(manageDevices);
				menu4.addSeparator();

				// ---- startCapture ----
				startCapture.setText("Start Data Capture");
				startCapture.setMnemonic('C');
				startCapture.addActionListener(e -> startCaptureActionPerformed(e));
				menu4.add(startCapture);

				// ---- stopCapture ----
				stopCapture.setText("Stop Data Capture");
				stopCapture.setMnemonic('P');
				stopCapture.addActionListener(e -> stopCaptureActionPerformed(e));
				menu4.add(stopCapture);
			}
			menuBar.add(menu4);

			// ======== menu6 ========
			{
				menu6.setText("Tools");
				menu6.setMnemonic('T');

				// ---- displayEditor ----
				displayEditor.setText("Display Editor");
				displayEditor.setEnabled(false);
				displayEditor.addActionListener(e -> displayEditorActionPerformed(e));
				menu6.add(displayEditor);

				// ---- syncRepo ----
				syncRepo.setText("Synchronize Repository");
				syncRepo.setMnemonic('S');
				syncRepo.addActionListener(e -> syncRepoActionPerformed(e));
				menu6.add(syncRepo);
				menu6.addSeparator();

				// ---- captureOptions ----
				captureOptions.setText("Capture Options");
				captureOptions.addActionListener(e -> captureOptionsActionPerformed(e));
				menu6.add(captureOptions);
			}
			menuBar.add(menu6);
		}

		// ======== helpMenu ========
		{
			helpMenu.setText("Help");
			helpMenu.setMnemonic('H');

			// ---- about ----
			about.setText("About");
			about.setMnemonic('A');
			about.addActionListener(e -> aboutActionPerformed(e));
			helpMenu.add(about);
		}
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel statusBar;
	private JLabel message;
	private JButton mark;
	private JTextField annoText;
	private JButton recordAudio;
	private JTextField elapsedTime;
	private JTextField clockLabel;
	private JButton screenCapture;
	private JProgressBar diskProgressBar;
	private JMenuBar menuBar;
	private JMenu menu1;
	private JMenuItem newFrame;
	private JMenuItem setupMenu;
	private JMenuItem simulation;
	private JCheckBoxMenuItem fullScreen;
	private JMenuItem exitItem;
	private JMenu menu2;
	private JMenu scaleMenu;
	private JMenuItem menuItem3;
	private JMenuItem menuItem4;
	private JMenuItem menuItem5;
	private JMenu penMenu;
	private JMenuItem pen1;
	private JMenuItem pen2;
	private JMenuItem pen3;
	private JMenuItem studyDetail;
	private JMenuItem autoScale;
	private JMenu menu4;
	private JMenuItem beginStudy;
	private JMenuItem endStudy;
	private JMenuItem manageDevices;
	private JMenuItem startCapture;
	private JMenuItem stopCapture;
	private JMenu menu6;
	private JMenuItem displayEditor;
	private JMenuItem syncRepo;
	private JMenuItem captureOptions;
	private JMenu helpMenu;
	private JMenuItem about;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		// we can get alarm events

		if (sid == StreamID.ALARM) {
			final Alarm ai = (Alarm) item;

			if (ai.getCode() == Alarm.FATAL) {
				SwingUtilities.invokeLater(new Runnable() {

					@Override
					public void run() {
						GuiUtil.showMessage("Fatal Error: " + ai.getMessage());
					}
				});
			}
		}

	}

	/*
	 * (non-Javadoc)
	 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
	 * 
	 * SwingTimer notices are sent to this routine.
	 * 
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		/*
		 * determine free space
		 */
		updateFreeSpace();
		/*
		 * set the clock
		 */
		Calendar cal = Calendar.getInstance();
		Date dt;
		if (runMode == RunMode.SIMULATION) {
			log.error("FIXME: stub SimulatorControlSubpanel simu = mp.getSimulatorPanel();");
			dt = new Date();
			// long dataTime = simu.getSimulationTime(); // THIS IS WRONG!
			// dt = new Date(dataTime);
		} else {
			dt = cal.getTime();
		}
		clockLabel.setText(dateFormat.format(dt));

		mp.updateSubPanel(dt);

		if (runMode == RunMode.RUN && !AppModel.isCapturing()) {
			long tm = (System.currentTimeMillis() - startTime) / (1000);

			// System.out.println("tm=" + tm);
			if (tm % NOT_CAPTURING_TIMEOUT_SEC == (NOT_CAPTURING_TIMEOUT_SEC -1) ) { // verbal alarm every 10 minutes
				if (armed > 0) {
					JPanel panel = new DataCaptureWarningPanel();
					GuiUtil.doDialog("", this, panel, p -> armOverlayMessage(), true);

					armed = 0;
					say("Warning. Data capture is not active.");

					System.out.println("added glass pane to thread: " + Thread.currentThread().getName());

				}

			}

		}
	}

	private void armOverlayMessage() {
		startTime = System.currentTimeMillis();
		armed = 1;

		return;
	}

	private void updateFreeSpace() {
		File archiveDir = ExportManager.getArchiveDir();

		if (archiveDir == null) {
			archiveDir = new File(System.getProperty("user.dir"));
		}
		if (archiveDir == null || archiveDir.exists() == false) {
			diskProgressBar.setIndeterminate(true);
		} else {
			diskProgressBar.setIndeterminate(false);
			long freeSpace = archiveDir.getFreeSpace();
			long totSpace = archiveDir.getTotalSpace();
			int percent = 100 - (int) ((100 * freeSpace) / totSpace);
			if (percent < 85) {
				diskProgressBar.setForeground(Color.GREEN);
			} else if (percent < 92) {
				diskProgressBar.setForeground(Color.ORANGE);
			} else {
				diskProgressBar.setForeground(Color.RED);
			}
			diskProgressBar.setValue(percent);
			diskProgressBar.setString("Disk");
		}
	}

	private static void say(final String msg) {
		Runnable r = new Runnable() {

			@Override
			public void run() {

				try {
					String voiceName = "kevin16";
					VoiceManager voiceManager = VoiceManager.getInstance();
					Voice helloVoice = voiceManager.getVoice(voiceName);

					if (helloVoice == null) {
						log.error("Cannot find a voice named " + voiceName + ".  Please specify a different voice.");
						return;
					}

					helloVoice.allocate();
					helloVoice.speak(msg);
					helloVoice.deallocate();
				} catch (Throwable e) {
					log.warn("Could not say message: {}", msg, e);
				}

			}
		};

		Thread t = new Thread(r);
		t.start();
	}

	public void clear() {
		mp.clear();
	}

	private void _addDevice(StreamProducer driver) {
		if( driver == null ) {
			log.error("cannot add null device driver");
			return;
		}
		RpDevice conf = driver.getConfiguration();
		if (conf == null) {
			log.error("device has no configuration: {}", driver);
			return;
		}

		List<RpDevice> subConfs = conf.getDevices();
		if (subConfs != null && subConfs.size() > 0) {
			for (RpDevice sub_conf : subConfs) {
				NullStreamProducer sub_driver = new NullStreamProducer((DeviceConfiguration) sub_conf);
				_addDevice(sub_driver);
			}
		} else {

			String tabName = conf.getName();
			if (tabName == null || tabName.length() == 0) {
				tabName = conf.getDriverName();
			}

			Component form = null;
			try {
				log.info("adding {} class={}", driver, driver.getClass());
				form = AdapterGui.buildDevicePanel(driver, conf);

				if (form != null) {
					ConnectionStatus stat = driver.getStatus();
					mp.addPanel(tabName, form, stat );

					if (form instanceof DisplayEditorManager) {
						DisplayEditorManager layered = (DisplayEditorManager) form;
						form = layered.getForm();
					}

					// if (form instanceof GLCanvas) {
					// GLCanvas view = (GLCanvas) form;
					// FPSAnimator animator = new FPSAnimator(60);
					// animator.add(view);
					// animator.start();
					// }
					if (form instanceof StreamConsumer) {
						driver.addStreamListener(StreamID.WAVEFORM, (StreamConsumer) form);
						driver.addStreamListener(StreamID.MEASUREMENT, (StreamConsumer) form);
						driver.addStreamListener(StreamID.DISPLAY, (StreamConsumer) form);
						driver.addStreamListener(StreamID.CONNECTION, (StreamConsumer) form);
					}
				}
			} catch (Exception e) {
				log.error("buildDevicePanel", e);
			}

		}

		PiSubjectExporter exporter = ExportManager.getDataExporter();
		if (exporter != null) {
			driver.addStreamListener(null, ExportManager.getDataExporter());
		}

		driver.addStreamListener(StreamID.CONNECTION, mp);
		driver.addStreamListener(StreamID.ANNOTATION, mp);
		driver.addStreamListener(StreamID.ALARM, mp);

		// listen to alarms whether or not the server is active
		driver.addStreamListener(StreamID.ALARM, this);

	}

	public void removeDevice(AdapterInterface dev) {
		RpDevice conf = dev.getConfiguration();
		String name = null;
		if (conf != null) {
			name = conf.getName();

			if (name == null) {
				name = conf.getDriverName();
			}
		}
		if (name != null) {
			mp.removePanel(name);
		}
	}

	@Override
	public void discover(DiscoveryAction action, DeviceRecord dev) {
		if (action != DiscoveryAction.DISCOVER) {
			// ignore discovery event
			return;
		}
		log.info("Discovered device: {}", dev);
		final StreamProducer driver = dev.getDriver();
		Runnable r = new Runnable() {

			@Override
			public void run() {
				_addDevice(driver);

			}

		};
		if (SwingUtilities.isEventDispatchThread()) {
			r.run();
		} else {
			SwingUtilities.invokeLater(r); // move request to the GUI thread
		}
		return;
	}

	public StreamProducer getSignalProducer(String name) {
		DeviceRecord dev = discovery.getDevice(name);
		if (dev == null) {
			log.error("Could not find requested device: {}", name);
			return null;
		}
		return dev.getDriver();
	}

	@Override
	public void error(DeviceRecord dev, String message, Exception x) {
		GuiUtil.showError(message + dev, x);
	}

	/*
	 * Used by the MgDAQPanel to send state changes
	 */
	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		String key = evt.getPropertyName();
		if (MedDAQPanel.EDITABLE_DISPLAY.equals(key)) {
			Boolean editable = (Boolean) evt.getNewValue();
			displayEditor.setEnabled(editable);
		}
	}

	private void displayEditorActionPerformed(ActionEvent e) {
		Component panel = mp.getSelectedPanel();
		DisplayConfig display = null;
//		if (panel instanceof ElegantDisplayForm) {
//			ElegantDisplayForm form = (ElegantDisplayForm) panel;
//			display = form.getDisplay();
//		} else if (panel instanceof SingleDeviceForm) {
//			SingleDeviceForm form = (SingleDeviceForm) panel;
//			display = form.getDisplay();
//		} else 
		if (panel instanceof InstrumentDisplayInterface) {
			InstrumentDisplayInterface form = (InstrumentDisplayInterface) panel;

			String[] options = {};
			BandEditorPanel editorPanel = new BandEditorPanel( form);

			JOptionPane p = new JOptionPane(editorPanel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null,
					options, null);
			JDialog d = p.createDialog(this, "Display Editor");
			GuiUtil.initModalDialog(d, p); // makes the escape key work
			d.setResizable(true);
			d.pack();
			d.setVisible(true);

		}
	}

	public void setNotCapturingTimeout(int timeout) {
		NOT_CAPTURING_TIMEOUT_SEC = timeout;
	}
}
