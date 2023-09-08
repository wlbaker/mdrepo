/*
 * Created by JFormDesigner on Sat Jul 09 13:30:43 CDT 2011
 */

package idea.meddaq.entry;

import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.events.CapabilitiesEvent;
import idea.conf.DeviceConfiguration;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;
import javax.swing.WindowConstants;
import javax.swing.border.BevelBorder;

import idea.GuiUtil;
import idea.schema.rp.RpDevice;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class MedDAQEntryFrame extends JFrame implements StreamConsumer, ActionListener {
	StudypointReviewPanel review;

	private DeviceConfiguration entry_caps;
	private SocketDeviceConfiguration primary_conf;
	private SocketDeviceConfiguration entry_conf;

	// private LinkedList<EntrySheet> entrySheets;
	private Date startDate;
	private EntryModel entryModel;
	private String curr_tpName;
	private EntryTimePoint curr_tp;
	// these are the actions that have been completed on the curr tp
	private LinkedList<TimepointAction> curr_actions;

	public MedDAQEntryFrame(String title) {
		initComponents();

		add(review = new StudypointReviewPanel(this), BorderLayout.CENTER);

		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE); // let me take

		addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent e) {

				// super.windowClosing(e);
				exitActionPerformed(null);
			}

		});

		connect.setEnabled(true);
		disconnect.setEnabled(false);

		newStudy.setEnabled(false);
		review.clear();

		Timer timer = new Timer(5000, this);
		// timer.setInitialDelay(pause);
		timer.start();
	}

	private void exitActionPerformed(ActionEvent evt) {
		String message = // "You have edits in progress in: " + tabName
		"\n\nContinue closing?";
		int ok = JOptionPane.showConfirmDialog(null, message, "IDEA Data Entry", JOptionPane.OK_CANCEL_OPTION);
		if (ok != JOptionPane.OK_OPTION) {
			return; // don't shut down if any edits in progress that are not OK
		}
		// endStudyActionPerformed(null);

		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		this.dispose();
		System.exit(0);
	}

	private void connectActionPerformed(ActionEvent ae) {
		try {
			ConnectionWizard cwiz = new ConnectionWizard();

			String[] options = {};
			JOptionPane p = new JOptionPane(cwiz, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options, null);
			JDialog d = p.createDialog(this, "Signal Selection");
			GuiUtil.initModalDialog(d, p); // makes the escape key work
			// d.setName("$Id: ParameterManager.java,v 1.6 2008/02/19 17:23:24 bbaker Exp $");
			d.setResizable(true);
			d.pack();
			d.setVisible(true);

			if (cwiz.isExecute()) {

				String host = cwiz.getConnection();
				_connectActionPerformed(host);

				connect.setEnabled(false);

				disconnect.setEnabled(true);
				newStudy.setEnabled(true);
				newMenu.setEnabled(true);

			}
		} catch (Exception e) {
			setMessage("Connection error");
			GuiUtil.showError("Connection Error", e);
		}
	}

	private void _connectActionPerformed(String host) throws IOException {

		GuiUtil.showMessage("FIXME: connect not implemented.");
//		if (driver_primary != null) {
//			driver_primary.disconnect();
//		}
//
//		primary_conf = IDEADriver.createConfigInstance();
//		primary_conf.setHost(host);
//		driver_primary = new IDEADriver(primary_conf);
//		driver_primary.addEventListener(CapabilitiesEvent.class, this);
//		driver_primary.addStreamListener(StreamID.MEASUREMENT, this);
//
//		setMessage("Connecting...");
//		driver_primary.connect();
//		driver_primary.requestCapabilities();

		setTitle("MedDAQ-Entry [" + primary_conf.getHost() + "]");
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		try {
			_streamEvent(jobID, source, sid, item);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void _streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) throws IOException {
		if (StreamID.CAPABILITIES.equals(sid)) {

			CapabilitiesEvent cap_ev = (CapabilitiesEvent) item;
			entry_caps = cap_ev.getCapabilities();
			setMessage("[MgEntryFrame] GOT capabilites: " + entry_caps);
			EntryUtil.checkCapabilities();

			List<RpDevice> subdevs = entry_caps.getDevices();
			for (RpDevice dev : subdevs) {
				dump_dev("   [MgEntryFrame subdev]", dev);

				if ("remote_entry".equals(dev.getName()) || "GUIEntry".equals(dev.getName())) {
					processRemoteEntryCaps(primary_conf);
				}

			}

		} else if (StreamID.MEASUREMENT.equals(sid)) {

			review.addNumericsBlock(source, item);
		}
	}

	private void processRemoteEntryCaps(SocketDeviceConfiguration primary_conf) throws IOException {
		GuiUtil.showMessage("FIXME: processRemoteCaps not implemented");
//		entry_conf = IDEADriver.createConfigInstance();
//		entry_conf.setHost(primary_conf.getHost());
//		entry_conf.setPort(primary_conf.getPort() + 1);
//
//		driver_dataentry = new IDEADriver(entry_conf);
//		driver_dataentry.addEventListener(CapabilitiesEvent.class, new StreamConsumer() {
//
//			@Override
//			public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
//				if (event instanceof CapabilitiesEvent) {
//					System.out.println("GOT ENTRY CAPS");
//				}
//				CapabilitiesEvent caps_evt = (CapabilitiesEvent) event;
//				DeviceConfiguration sub_caps = caps_evt.getCapabilities();
//				dump_dev("SUBDEV", sub_caps);
//
//				GuiUtil.showMessage("EXCEL FILE NOT SPECIFIED IN REMOTE ENTRY DUE TO SUBCAPS CHANGE");
//				//				DeviceConfiguration re_cap = sub_caps.getDevice("remote_entry");
//				//				if (re_cap == null) {
//				//					re_cap = sub_caps;
//				//				}
//				//! String excelFile = re_cap.getParam("excelFile");
//				String excelFile = null;
//
//				refresh(startDate, excelFile);
//
//			}
//
//		});
//
//		driver_dataentry.connect();
//
//		// BLIND: this capabilities request is ignored by the client
//		// for the moment
//		driver_dataentry.requestCapabilities();

	}

	public void refresh(Date startDate, String excelFile) {
		if (excelFile != null) {
			File file = new File(excelFile);
			try {
				entryModel = EntryUtil.loadEntrySheets(file);
				this.startDate = startDate;

				message.setText("Load: " + file.getPath());
				review.refresh(entryModel.getSheets());

			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();

				GuiUtil.showMessage("Could not load data file: " + file.getPath());
			}

		}

	}

	public void showEntryPanel() {

		StudypointEntryPanel entry = new StudypointEntryPanel( entry_caps);
		entry.refresh(startDate, entryModel);
		GuiUtil.doDialog("entry panel", MedDAQEntryFrame.this, entry, null);

	}

	public static void dump_dev(String title, RpDevice dev) {
		int verbose = 0;

		if (verbose > 0) {
			System.out.println("TITLE   : " + title);
			System.out.println("dev name: " + dev.getName());
			System.out.println("   class: " + dev.getClass());
			System.out.println("   model: " + dev.getModelName());
			//			for (MetricDescription setting : dev.getSettings()) {
			//				System.out.println("   setting: " + setting.getName());
			//			}

			List<RpDevice> subcaps = dev.getDevices();
			if (subcaps != null) {
				for (RpDevice subcap : subcaps) {
					dump_dev("*" + title, subcap);
				}
			}
		}
	}

	private void setMessage(String txt) {
		message.setText(txt);
	}

	private void entryActionPerformed(ActionEvent e) {
		if (entryModel == null) {
			GuiUtil.showMessage("Prompt entries have not been loaded.  Load prompts and connect to server to proceed.");
			return;
		}
		showEntryPanel();
	}

	private void loadActionPerformed(ActionEvent e) {
		final LoadWizard wiz = new LoadWizard();

		try {
			Calendar cal = Calendar.getInstance();

			wiz.setStartTime(cal.getTime());
			GuiUtil.doDialog("Load Wizard", this, wiz, null);

			if (wiz.isExecute()) {

				startDate = wiz.getStartTime();
				entryModel = wiz.getEntryModel();
				//				RpDevice def = wiz.getStudyDefinition();
				//				String excelFile = (String) RpUtil.getParam(def.getParam(), "excelFile");
				//				refresh(startDate, excelFile);
			}
		} catch (Exception e1) {
			GuiUtil.showError("Starting Study: ", e1);
		}

	}

	private void disconnectActionPerformed(ActionEvent e) {

		GuiUtil.showMessage("FIXME: disconnect not implemented");
//		try {
//			if (driver_primary != null) {
//				driver_primary.disconnect();
//			}
//
//		} catch (Exception ex) {
//			ex.printStackTrace();
//		}
//		driver_primary = null;
//
//		try {
//			if (driver_dataentry != null) {
//				driver_dataentry.disconnect();
//			}
//		} catch (Exception ex) {
//			ex.printStackTrace();
//		}
//		driver_dataentry = null;

		connect.setEnabled(true);
		disconnect.setEnabled(false);
		newStudy.setEnabled(false);

		review.clear();
	}

	private void newStudyActionPerformed(ActionEvent e) {
		final StudyWizard wiz = new StudyWizard();

		try {
			Calendar cal = Calendar.getInstance();

			wiz.setStartTime(cal.getTime());
			GuiUtil.doDialog("Study Wizard", this, wiz, null);

			if (wiz.isExecute()) {

				RpDevice conf = new RpDevice();

				conf.setName("HARDCODED_A11010");
				conf.setDeviceClass("ENTRY");
				conf.setModelName("A11010");
				conf.setDriverName("STDYA11010");

				LinkedList<EntrySheet> sheets = entryModel.getSheets();
				for (EntrySheet sheet : sheets) {
					RpDevice dev = sheet.getDevice();
					conf.getDevices().add(dev);
				}

				//FIXME: driver_primary.mgmAddDevice(conf);
				// wiz.getH

				studyMenu.setEnabled(true);

				review.refresh(entryModel.getSheets());
				loadExistingData();

			} else {
				message.setText("New Study selection aborted.");
			}
		} catch (Exception e1) {
			GuiUtil.showError("Starting Study: ", e1);
		}
	}

	private void loadExistingData() throws IOException {

		int job_id = 22;
		System.err.println("! driver_primary.allocateJobId() ?? ");
		DeviceConfiguration conf = new DeviceConfiguration("");
		conf.setName("HARDCODED_A11010");
		GuiUtil.showMessage("FIXME: request Transfer in MgEntryFrame");
		// driver_primary.requestTransfer(job_id, IDEA.BEGINNING_TIME, IDEA.END_TIME, conf );

	}

	private void xShutdownActionPerformed(ActionEvent e) {
		try {
			GuiUtil.showMessage("FIXME: shutdown not implemented"); // driver_primary.mgmShutdown();
		} catch (Exception e1) {
			GuiUtil.showError("Shutdown Error: ", e1);
		}
	}

	private void setStartTimeActionPerformed(ActionEvent e) {
		StartTimePanel panel = new StartTimePanel();

		if (startDate != null) {
			panel.setStartTime(startDate);
		}

		boolean ok = GuiUtil.doOkDialog(this, "Study Start Time", panel);

		if (ok) {
			startDate = panel.getStartDate();

			DateFormat df = new SimpleDateFormat("MM/dd/yyyy HH:mm");
			startMessage.setText(df.format(startDate));

			getNextTP();
			updateTick();

			review.enableEntry(true);
			entry.setEnabled(true);

		}
	}

	private void getNextTP() {

		if (startDate == null) {
			return;
		}

		Date now = new Date();
		long msNow = now.getTime();
		long shortest = Long.MAX_VALUE;
		curr_tp = null;
		curr_actions = null;

		LinkedList<EntryTimePoint> timepoints = entryModel.getTimepoints();
		for (EntryTimePoint tp : timepoints) {
			if (tp.getActions() == null || tp.getActions().size() == 0) {
				System.out.println("Ignoring TP without actions: " + tp.getTpName());
				continue;
			}
			Date tpTime = tp.getTpTime(startDate);
			long msThen = tpTime.getTime();

			if (msNow > msThen) {
				// already passed
				System.out.println("skipping past TP: " + tp.getTpName());
			} else {
				if (msThen - msNow < shortest) {
					shortest = msThen - msNow;
					curr_tpName = tp.getTpName();
					curr_tp = tp;
					tickMessage.setText(" NEXT TP: " + curr_tpName + " at " + tpTime);
				}
			}
		}

		if (curr_tp != null) {
			curr_actions = new LinkedList<TimepointAction>(curr_tp.getActions());
		}
	}

	private void updateTick() {
		if (curr_actions == null || curr_actions.size() == 0) {
			// no remaining actions: find the next tp
			getNextTP();
		}
		if (startDate == null || curr_tp == null) {
			tickMessage.setText(" ");
		} else {
			Date now = new Date();
			Date tpTime = curr_tp.getTpTime(startDate);

			long tmtp = tpTime.getTime();
			long tmnow = now.getTime();

			List<TimepointAction> actions = curr_actions;
			List<TimepointAction> removables = null;
			;
			for (TimepointAction action : actions) {
				Date actionTime = action.getActionTime(tpTime);
				long tmaction = actionTime.getTime();
				if (tmnow > tmaction) {

					ExecutableAction[] exeActions = entryModel.getExecutableActions(action.getName());
					if (exeActions == null) {
						System.out.println("NO ACTION for NAME=" + action.getName());
					} else {
						for (ExecutableAction exe : exeActions) {
							EntryUtil.execute(exe);
						}
					}
					if (removables == null) {
						removables = new LinkedList<TimepointAction>();
					}
					removables.add(action);
				}
			}
			if (removables != null) {
				for (TimepointAction action : removables) {
					curr_actions.remove(action);
				}
			}

			if (tmnow > tmtp) {
				System.err.println("TIME: " + curr_tp.getTpName());
				System.err.println(" start= " + startDate);
				System.err.println(" now= " + now);
				System.err.println(" tp= " + tpTime);
			}
		}
	}

	private void xRunActionExeActionPerformed(ActionEvent e) {

		if (curr_tp == null || curr_tp.getActions() == null) {
			GuiUtil.showMessage("NO CURRENT ACTIONS");
			return;
		}

		List<TimepointAction> actions = curr_tp.getActions();
		for (TimepointAction action : actions) {
			if (curr_actions.contains(action)) {
				// already acted on this action
			} else {
				curr_actions.add(action);

				ExecutableAction[] exeActions = entryModel.getExecutableActions(action.getName());
				if (exeActions == null) {
					System.out.println("No action for name=" + action.getName());
				} else {
					for (ExecutableAction exe : exeActions) {
						EntryUtil.execute(exe);
					}
					break;
				}
			}
		}

		return;
	}

	private void xTranReqActionPerformed(ActionEvent e) {
		try {
			loadExistingData();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		menuBar1 = new JMenuBar();
		menu1 = new JMenu();
		newMenu = new JMenu();
		newStudy = new JMenuItem();
		entry = new JMenuItem();
		connect = new JMenuItem();
		disconnect = new JMenuItem();
		load = new JMenuItem();
		xShutdown = new JMenuItem();
		xRunActionExe = new JMenuItem();
		xTranReq = new JMenuItem();
		exit = new JMenuItem();
		studyMenu = new JMenu();
		setStartTime = new JMenuItem();
		studyExport = new JMenuItem();
		footerPanel = new JPanel();
		message = new JLabel();
		tickMessage = new JLabel();
		startMessage = new JLabel();
		label3 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		setTitle("C3E-Entry");
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		//======== menuBar1 ========
		{

			//======== menu1 ========
			{
				menu1.setText("File");
				menu1.setMnemonic('F');

				//======== newMenu ========
				{
					newMenu.setText("New");
					newMenu.setEnabled(false);

					//---- newStudy ----
					newStudy.setText("Study");
					newStudy.setEnabled(false);
					newStudy.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							newStudyActionPerformed(e);
						}
					});
					newMenu.add(newStudy);

					//---- entry ----
					entry.setText("Entry");
					entry.setEnabled(false);
					entry.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							entryActionPerformed(e);
						}
					});
					newMenu.add(entry);
				}
				menu1.add(newMenu);
				menu1.addSeparator();

				//---- connect ----
				connect.setText("Connect");
				connect.setMnemonic('C');
				connect.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						connectActionPerformed(e);
					}
				});
				menu1.add(connect);

				//---- disconnect ----
				disconnect.setText("Disconnect");
				disconnect.setMnemonic('D');
				disconnect.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						disconnectActionPerformed(e);
					}
				});
				menu1.add(disconnect);

				//---- load ----
				load.setText("Load");
				load.setMnemonic('L');
				load.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						loadActionPerformed(e);
					}
				});
				menu1.add(load);
				menu1.addSeparator();

				//---- xShutdown ----
				xShutdown.setText("X-Server Shutdown");
				xShutdown.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						xShutdownActionPerformed(e);
					}
				});
				menu1.add(xShutdown);

				//---- xRunActionExe ----
				xRunActionExe.setText("X-Run Action Exe");
				xRunActionExe.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						xRunActionExeActionPerformed(e);
					}
				});
				menu1.add(xRunActionExe);

				//---- xTranReq ----
				xTranReq.setText("X-Transfer Req");
				xTranReq.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						xTranReqActionPerformed(e);
					}
				});
				menu1.add(xTranReq);

				//---- exit ----
				exit.setText("Exit");
				exit.setMnemonic('X');
				exit.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						exitActionPerformed(e);
					}
				});
				menu1.add(exit);
			}
			menuBar1.add(menu1);

			//======== studyMenu ========
			{
				studyMenu.setText("Study");
				studyMenu.setMnemonic('S');
				studyMenu.setEnabled(false);

				//---- setStartTime ----
				setStartTime.setText("Start Time");
				setStartTime.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						setStartTimeActionPerformed(e);
					}
				});
				studyMenu.add(setStartTime);

				//---- studyExport ----
				studyExport.setText("Export");
				studyMenu.add(studyExport);
			}
			menuBar1.add(studyMenu);
		}
		setJMenuBar(menuBar1);

		//======== footerPanel ========
		{
			footerPanel.setLayout(new FormLayout("[150dlu,default], default:grow, [80dlu,default], default",
					"fill:[12dlu,default]"));

			//---- message ----
			message.setText("text");
			message.setBorder(new BevelBorder(BevelBorder.LOWERED));
			footerPanel.add(message, cc.xy(1, 1));

			//---- tickMessage ----
			tickMessage.setText("text");
			tickMessage.setBorder(new BevelBorder(BevelBorder.LOWERED));
			footerPanel.add(tickMessage, cc.xy(2, 1));

			//---- startMessage ----
			startMessage.setText("text");
			startMessage.setBorder(new BevelBorder(BevelBorder.LOWERED));
			footerPanel.add(startMessage, cc.xy(3, 1));

			//---- label3 ----
			label3.setText("text");
			label3.setBorder(new BevelBorder(BevelBorder.LOWERED));
			footerPanel.add(label3, cc.xy(4, 1));
		}
		contentPane.add(footerPanel, BorderLayout.SOUTH);
		pack();
		setLocationRelativeTo(getOwner());
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JMenuBar menuBar1;
	private JMenu menu1;
	private JMenu newMenu;
	private JMenuItem newStudy;
	private JMenuItem entry;
	private JMenuItem connect;
	private JMenuItem disconnect;
	private JMenuItem load;
	private JMenuItem xShutdown;
	private JMenuItem xRunActionExe;
	private JMenuItem xTranReq;
	private JMenuItem exit;
	private JMenu studyMenu;
	private JMenuItem setStartTime;
	private JMenuItem studyExport;
	private JPanel footerPanel;
	private JLabel message;
	private JLabel tickMessage;
	private JLabel startMessage;
	private JLabel label3;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void actionPerformed(ActionEvent e) {
		updateTick();
	}

}
