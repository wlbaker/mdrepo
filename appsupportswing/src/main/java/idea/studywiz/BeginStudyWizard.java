/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.studywiz;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
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
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.gui.wizard.DefaultStudyHeaderPanel;
import idea.gui.wizard.SiteInfo;
import idea.meddaq.AppSetup;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

// import static WizDeviceID.*;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
@Slf4j
public class BeginStudyWizard extends JPanel implements WizardMasterInterface {

	private static final String STUDY_SELECTION = "Study Selection";
	private static final String STUDY_INFO = "Study Info";
	private static final String HARDWARE_SETUP = "Hardware Setup";
	private static final String MULTIMEDIA_SETUP = "Multimedia Setup";
	private static final String SERIALCONF_SETUP = "Serial Autoconfig";

	private CardLayout card;

	// private RpSubject header;
	private boolean execute = false;
	private String curr;

	LinkedList<Component> stack = new LinkedList<Component>();
	private StudySelectionPanel studySelection;
	private DeviceConnectionPanel deviceConnection;
	private MultimediaPanel multimediaPanel;
	private DefaultStudyHeaderPanel subjectInfo;
	private SerialConfigurationPanel serialConfig;

	public BeginStudyWizard(String studyName) {
		initComponents();
		card = (CardLayout) filler.getLayout();

		enableNext(false);
		enableFinish(false);
		enablePrevious(false);

		RepositoryInterface local = RepositoryFactory.getLocalRepository();
		List<RpStudy> studies = null;

		try {
			studies = local.getStudyList(null);
		} catch (Exception e) {
			GuiUtil.showError("Error loading studies.", e);
		}

		if (studies == null || studies.size() == 0) {
			JPanel page;
			page = new StudyErrorPanel(
					"<html>No available studies.<br><br>Create a local study or retrieve a collaboration study with <i>Setup</i>.</html>");
			safeAdd(page, "Study Error");
		} else if (studyName == null) {
			safeAdd(studySelection = new StudySelectionPanel(this, true, false, false), STUDY_SELECTION);
			safeAdd(subjectInfo = new DefaultStudyHeaderPanel(this), STUDY_INFO);
			safeAdd(deviceConnection = new DeviceConnectionPanel(this), HARDWARE_SETUP);
			safeAdd(multimediaPanel = new MultimediaPanel(this), MULTIMEDIA_SETUP);
			try {
				safeAdd(serialConfig = new SerialConfigurationPanel(this), SERIALCONF_SETUP);
			} catch (Throwable t) {
				log.warn("Could not init serial dialog", t);
			}

			curr = STUDY_SELECTION;
			buildWizardNavigationTree();
			tree.setSelectionInterval(0, 0);
		} else {
			JPanel page = new StudyErrorPanel("<html>Could not load the indicate study: " + studyName
					+ "<br><br>Create study with <i>Setup</i></html>");
			safeAdd(page, "Study Load Error");
		}

		pushPage(studySelection);
	}

	private void safeAdd(JPanel p, String tag) {
		try {
			p.setName(tag);
			filler.add(p, tag);
		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(null, "Internal Error: " + e.getMessage());
		}
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode studySelection = new DefaultMutableTreeNode(STUDY_SELECTION);
		DefaultMutableTreeNode studyInfo = new DefaultMutableTreeNode(STUDY_INFO);
		DefaultMutableTreeNode hardwareSetup = new DefaultMutableTreeNode(HARDWARE_SETUP);
		DefaultMutableTreeNode multimediaSetup = new DefaultMutableTreeNode(MULTIMEDIA_SETUP);
		DefaultMutableTreeNode autoconf = new DefaultMutableTreeNode(SERIALCONF_SETUP);

		root.add(studySelection);
		root.add(studyInfo);
		root.add(hardwareSetup);
		root.add(multimediaSetup);
		root.add(autoconf);

		tree.setModel(new DefaultTreeModel(root));
		expandAll(tree);
	}

	private void expandAll(JTree tree2) {
		for (int i = 0; i < tree.getRowCount(); i++) {
			tree.expandRow(i);
		}
	}

	private void nextActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				_next(ri);

				break;
			}
		}
	}

	private void _next(WizardPanelInterface ri) {
		ri.next();

		JPanel nextPage = null;

		if (curr.equals(STUDY_SELECTION)) {
			nextPage = subjectInfo; // STUDY_INFO;
			enableNext(false);
			if (AppSetup.isClient()) {
				RpSubject header = subjectInfo.getHeader();
				AppSetup.setRpSubject(header);
				deviceConnection.setStudy(getStudy());

				nextPage = deviceConnection; // DEVICE_SETUP;
			} else {
				nextPage = subjectInfo; // STUDY_INFO;

				try {
					SiteInfo site = AppSetup.readSiteInfo(AppSetup.getLocalRepositoryDir() + "/site.xml");
					subjectInfo.setSiteInfo(site);
					subjectInfo.setStudyTitle(getStudy().getTitle());

				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		} else if (curr.equals(STUDY_INFO)) {

			nextPage = deviceConnection; // DEVICE_SETUP;
			enableFinish(true);
			enableNext(true); // ...maybe? refresh might change it, but there is
								// one more page

			deviceConnection.setStudy(getStudy());

			RpSubject header = subjectInfo.getHeader();
			AppSetup.setRpSubject(header);

		} else if (curr.equals(HARDWARE_SETUP)) {
			nextPage = multimediaPanel; // SERIALCONF_SETUP;

			enableNext(false); // this is the last page
			enableFinish(true);
		} else if (curr.equals(MULTIMEDIA_SETUP)) {
			if (serialConfig == null) {
				nextPage = null; // fall through to Finish
			} else {
				nextPage = serialConfig; // SERIALCONF_SETUP;

				enableNext(false); // this is the last page
				enableFinish(true);
				serialConfig.setStudy(getStudy(), getHardware());
			}
		}

		if (nextPage != null) {
			pushPage(nextPage);
			// setCurrentPanel(nextPage);
		} else {
			// walked past the end
			finishActionPerformed(null);
		}

		// ********* 1

		// ********* 2

	}

	// private void setCurrentPanel(String nextPage) {
	// card.show(filler, nextPage);
	//
	// curr = nextPage;
	//
	// updateTreeSelection();
	// }

	private void finishActionPerformed(ActionEvent e) {
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

	}

	private void previousActionPerformed(ActionEvent e) {
		popPage();
		refresh();
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
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

		// ======== this ========
		setLayout(new FormLayout("[350dlu,default]:grow", "fill:default:grow, 2*($lgap, default)"));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("80dlu, $lcgap, [280dlu,default]:grow", "fill:default:grow"));

			// ======== scrollPane1 ========
			{

				// ---- tree ----
				tree.setBackground(null);
				tree.setRootVisible(false);
				tree.setEnabled(false);
				tree.setModel(null);
				scrollPane1.setViewportView(tree);
			}
			panel2.add(scrollPane1, CC.xy(1, 1));

			// ======== filler ========
			{
				filler.setLayout(new CardLayout());
			}
			panel2.add(filler, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 1));
		add(separator1, CC.xy(1, 3));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
					"default:grow, 3*($lcgap, default), 3*($lcgap, [50dlu,default]), $ugap, [50dlu,default]",
					"default"));

			// ---- previous ----
			previous.setText("< Previous");
			previous.setEnabled(false);
			previous.addActionListener(e -> previousActionPerformed(e));
			panel1.add(previous, CC.xy(9, 1));

			// ---- next ----
			next.setText("Next >");
			next.addActionListener(e -> nextActionPerformed(e));
			panel1.add(next, CC.xy(11, 1));

			// ---- finish ----
			finish.setText("Finish");
			finish.setEnabled(false);
			finish.addActionListener(e -> finishActionPerformed(e));
			panel1.add(finish, CC.xy(13, 1));

			// ---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel1.add(cancel, CC.xy(15, 1));
		}
		add(panel1, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
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

	public void pushPage(JPanel panel) {
		try {
			curr = panel.getName();

			filler.add(panel, curr);
			card.show(filler, curr);
			stack.addFirst(panel);

			updateTreeSelection();

		} catch (Exception e) {
			GuiUtil.showError("Internal Error", e);
		}

	}

	private void updateTreeSelection() {
		TreeModel model = tree.getModel();
		if (model != null) {
			TreePath path = tree.getNextMatch(curr, 0, Bias.Forward);
			tree.setSelectionPath(path);

			previous.setEnabled(stack.size() > 1);
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

		card.show(filler, curr = page.getName());

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

	public RpStudy getStudy() {
		return studySelection.getSelectedStudy();
	}

	public RpHardware getHardware() {
		return deviceConnection.getHardware();
	}

	public String[] getPorts() {
		if (serialConfig == null) {
			return null;
		}
		return serialConfig.getPorts();
	}

	public RpSubject getSubjectInfo() {
		return subjectInfo.getHeader();
	}

	public void setFinished(boolean execute) {
		this.execute = execute;
	}

	public boolean isExecute() {
		return execute;
	}

}
