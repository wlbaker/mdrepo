/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.simulator;

import icuInterface.RpUtil;
import idea.intf.IDEAClient;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTree;
import javax.swing.text.Position.Bias;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.devwizard.SetupWizardInterface;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.gui.wizard.DeviceSelectionPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

// import static WizDeviceID.*;

/**
 * @author User #2
 */

@Slf4j
@SuppressWarnings("serial")
public class SimulatorWizard extends JPanel implements SetupWizardInterface {

	private final static String SOURCE_SELECTION = "Source Selection";
	private static final String SOURCE_DETAIL = "Source Detail";
	private static final String ANALYSIS_SETUP = "Analysis";
	private static final String OUTPUT_SETUP = "Simulation";
	private static final String SAVE_SETUP = "Save";
	private static final String LAST_PAGE = "Last";
	private static final String TIME_SELECTION = "Time Selection";

	protected static final int RESAMPLE_NONE = 0;
	protected static final int RESAMPLE_HOLD = 1;
	protected static final int RESAMPLE_INTERPOLATE = 2;

	private CardLayout card;
	private static WizardMasterInterface instance;
	private String studyID;
	private RpStudy study;

	LinkedList<JPanel> stack = new LinkedList<JPanel>();

	private Date startTime;
	private Date endTime;

	long tmStart; // same values as dates above, but more convenient and used
	// between threads
	long tmEnd;

	private String repository;

	private boolean finished = false;
	private String subjectID;
	private RpAnalysis analGroup;
	private SourceSelectionPanel sourcePanel;
	private DeviceSelectionPanel deviceSelectionPanel;
	private TimeSelectionPanel timeSelection;

	IDEAClient driver;
	private String method;
	private SimulatorFilePanel simulatorFilePanel;

	public SimulatorWizard() {
		initComponents();
		card = (CardLayout) filler.getLayout();
		instance = this; // must be set before any sub-panels added

		// pushPage(new SourceSelectionPanel());
		pushPage(sourcePanel = new SourceSelectionPanel(this), SOURCE_SELECTION);
		// safeAdd(analPanel = new AnReview( profile ), REVIEW_ANAL_PANEL);

		buildWizardNavigationTree();
		tree.setSelectionInterval(0, 0);

		// ? progressBar1.setVisible( false );
	}

	private void pushPage(JPanel p, String tag) {
		System.out.println("adding panel: " + tag);
		if( tag != null ) {
			p.setName( tag );
		}
		pushPage( p );
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode srcsel = new DefaultMutableTreeNode(SOURCE_SELECTION);
		DefaultMutableTreeNode repository_or_file = new DefaultMutableTreeNode(SOURCE_DETAIL);
		DefaultMutableTreeNode analsel = new DefaultMutableTreeNode(ANALYSIS_SETUP, true);
		DefaultMutableTreeNode outsel = new DefaultMutableTreeNode(OUTPUT_SETUP, true);
		DefaultMutableTreeNode signals = new DefaultMutableTreeNode(SAVE_SETUP, true);

		root.add(srcsel);
		root.add(repository_or_file);
		root.add(analsel);
		root.add(outsel);
		root.add(signals);

		tree.setModel(new DefaultTreeModel(root));
		expandAll(tree);
	}

	private void expandAll(JTree tree2) {
		for (int i = 0; i < tree.getRowCount(); i++) {
			tree.expandRow(i);
		}
	}

	private void nextActionPerformed(ActionEvent e) {

		String nextPage = null;

		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.next();
				break;
			}
		}
		JPanel page = stack.getFirst();
		String curr = page.getName();

		if (curr.equals(SOURCE_SELECTION)) {
			if (sourcePanel.isSignalFromFile()) {
				simulatorFilePanel = new SimulatorFilePanel(this);
				simulatorFilePanel.setName("File Selection");
				pushPage(simulatorFilePanel);
				method = "file";
			} else if (sourcePanel.isSignalFromDevice()) {
				deviceSelectionPanel = new DeviceSelectionPanel();
				deviceSelectionPanel.setName("Device Selection");
				pushPage(deviceSelectionPanel);
				method = "device";
			} else if (sourcePanel.isSignalFromRepository()) {
				page = new SimulatorRepositoryPanel(this);
				page.setName("Repository");
				pushPage(page);
				method = "repository";
			} else {
				assert (false) : "unexpected inport source";
			}

		} else if (curr.equals(SOURCE_DETAIL)) {

			System.out.println("do nothing?");
		} else if (curr.equals("Device Selection")) {
			log.error("FIXME: connect to IDEA server");
			GuiUtil.showMessage("FIXME: connect to IDEA server");
//			String connectionIP = deviceSelectionPanel.getConnection();
//			SocketDeviceConfiguration conf = IDEAClient.createConfigInstance();
//			conf.setHost(connectionIP);
//			conf.setPort(IDEAClient.DEFAULT_IDEA_UDP_PORT);
//
//			if (driver != null) {
//				driver.shutdown();
//			}
//			driver = new IDEAClient(conf);
//			if (timeSelection == null) {
//				pushPage(timeSelection = new TimeSelectionPanel(this), TIME_SELECTION);
//			}
//			try {
//				driver.start();
//				timeSelection.setDriver(driver);
//				timeSelection.requestMeta();
//			} catch (IOException e1) {
//				// TODO Auto-generated catch block
//				e1.printStackTrace();
//			}

			nextPage = TIME_SELECTION;
			System.out.println("don't create or push a page?");
		} else if (curr.equals(TIME_SELECTION)) {
			ArchiveMetaData meta = timeSelection.getMeta();
			startTime = meta.getStartTime();
			endTime = meta.getStopTime();
			finishActionPerformed(null);
		} else if (curr.equals(ANALYSIS_SETUP)) {
			nextPage = OUTPUT_SETUP;

			SimulatorOutputPanel lastPanel = new SimulatorOutputPanel(this, getAnalysis("simulator"));
			lastPanel.setName(nextPage);
			pushPage(lastPanel);
		} else if (curr.equals(OUTPUT_SETUP)) {
			// this is not quite the way it is supposed to work!!!!
			// this got set prematurely to SAVE_SETUP when ANALYSIS_SETUP was
			// called on pushPage
			nextPage = SAVE_SETUP;
			nextPage = LAST_PAGE;

			SimulatorSaveConfigPanel lastPanel = new SimulatorSaveConfigPanel(this, study, null);
			lastPanel.setName(nextPage);
			pushPage(lastPanel);
		}

		if (nextPage != null) {

			setCurrentPanel(nextPage);
		}

	}

	private RpAnalysis getAnalysis(String name) {

		RpAnalysis ret = null;

		List<RpAnalysis> list = study.getAnalysis();

		if (list != null) {
			for (RpAnalysis anal : list) {
				if (name.equals(anal.getName())) {
					ret = anal;
					break;
				}
			}
		}

		if (ret == null) {
			ret = new RpAnalysis();
			ret.setName(name);

			list.add(ret);
		}

		return ret;
	}

	private void setCurrentPanel(String nextPage) {
		card.show(filler, nextPage);
	}

	private void finishActionPerformed(ActionEvent ae) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.finish();
				if (ok) {
					setFinished(true);
					GuiUtil.closeDialog(this);
				}
				break;
			}
		}
		// hmm...no chance to quit?
		if (driver != null) {
			log.error("FIXME: driver.shutdown();");
		}
		setFinished(true);
		GuiUtil.closeDialog(this);
	}

	private void previousActionPerformed(ActionEvent e) {
		popPage();
		refresh();
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	public Date getMetaStartTime() {
		return startTime;
	}

	public Date getMetaEndTime() {
		return endTime;
	}

	@Override
	public void pushPage(JPanel panel) {
		try {
			String tag = panel.getName();

			filler.add(panel, tag);
			card.show(filler, tag);
			stack.addFirst(panel);

			TreePath path = tree.getNextMatch(tag, 0, Bias.Forward);
			tree.setSelectionPath(path);

			previous.setEnabled(true);

			String p_name = panel.getName();
			assert (p_name != null) : "bad wizard panel name!";
			if (p_name == null) {
				p_name = "unknown";
			}

		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(null, "Internal Error: " + e.getMessage());
		}

	}

	public void enableNext(boolean b) {
		next.setEnabled(b);
	}

	public void enablePrevious(boolean b) {
		previous.setEnabled(b);
	}

	public void enableFinish(boolean b) {
		finish.setEnabled(b);
	}

	private void popPage() {
		Component page = stack.removeFirst();
		filler.remove(page);

		// ? card.removeLayoutComponent( page );

		page = stack.getFirst();
		String tag = page.getName();
		TreePath path = tree.getNextMatch(tag, 0, Bias.Forward);
		tree.setSelectionPath(path);

		card.show(filler, page.getName());

		previous.setEnabled(stack.size() > 1);
	}

	public void popPageUntil(String key) {
		Component page = stack.getFirst();
		while (!key.equals(page.getName())) {
			System.out.println("POPPING PAGE: " + page.getName());
			popPage();
			page = stack.getFirst();
		}
		refresh();
	}

	public void refresh() {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.refresh();
				break;
			}
		}
	}

	public boolean isExecute() {
		return finished;
	}

	public void setFinished(boolean b) {
		finished = b;
	}

	public void setSimulationSource(String repositoryName, String studyID, String subjectID) throws IOException {
		this.repository = repositoryName;
		this.studyID = studyID;
		this.subjectID = subjectID;

		study = new RpStudy();
		RpAnalysis anal = getAnalysis();
		if (anal != null) {
			study.getAnalysis().add(anal);
		}

		try {
			PiSubjectImporter importer = getConnectedImporter();
			RpHardware hw = RpUtil.createHardware(importer.getDevices());
			study.getHardware().add(hw);
			importer.disconnect();
		} catch (IOException e) {
			study = null;
			throw (e);
		}

	}

	public PiSubjectImporter getConnectedImporter() throws IOException {
		File dataFile = new File(getSubjectID());
		PiSubjectImporter importer = PiImporterUtil.getImporterFromFile(dataFile);
		importer.connect();
		return importer;
	}

	public String getSimulationRepository() {
		return this.repository;
	}

	public String getStudyID() {
		return this.studyID;
	}

	public String getSubjectID() {
		return this.subjectID;
	}

	public RpAnalysis getAnalysis() {
		return analGroup;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		tree = new JTree();
		filler = new JPanel();
		separator1 = new JSeparator();
		panel1 = new JPanel();
		previous = new JButton();
		next = new JButton();
		finish = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("[250dlu,default]:grow", "fill:default:grow, 2*($lgap, default)"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout("80dlu, $lcgap, default:grow", "fill:default:grow"));

			//======== scrollPane1 ========
			{

				//---- tree ----
				tree.setBackground(null);
				tree.setRootVisible(false);
				tree.setEnabled(false);
				scrollPane1.setViewportView(tree);
			}
			panel2.add(scrollPane1, cc.xy(1, 1));

			//======== filler ========
			{
				filler.setLayout(new CardLayout());
			}
			panel2.add(filler, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 1));
		add(separator1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default, $lcgap, default:grow, 5*($lcgap, default), $ugap, default",
					"default"));

			//---- previous ----
			previous.setText("< Previous");
			previous.setEnabled(false);
			previous.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					previousActionPerformed(e);
				}
			});
			panel1.add(previous, cc.xy(9, 1));

			//---- next ----
			next.setText("Next >");
			next.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					nextActionPerformed(e);
				}
			});
			panel1.add(next, cc.xy(11, 1));

			//---- finish ----
			finish.setText("Finish");
			finish.setEnabled(false);
			finish.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					finishActionPerformed(e);
				}
			});
			panel1.add(finish, cc.xy(13, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel1.add(cancel, cc.xy(15, 1));
		}
		add(panel1, cc.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTree tree;
	private JPanel filler;
	private JSeparator separator1;
	private JPanel panel1;
	private JButton previous;
	private JButton next;
	private JButton finish;
	private JButton cancel;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	public RpStudy getStudy() {

		return study;
	}

	public String getSimulationMethod() {
		return method;
	}

	public String getConnection() {
		return deviceSelectionPanel.getConnection();
	}

	public void setStartTime(Date dt) {
		this.startTime = dt;
	}

	public void setEndTime(Date dt) {
		this.endTime = dt;
	}

}
