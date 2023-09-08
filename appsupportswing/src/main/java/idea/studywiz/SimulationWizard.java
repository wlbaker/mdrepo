/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.studywiz;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTree;
import javax.swing.text.Position.Bias;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.ObjectFactory;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

// import static WizDeviceID.*;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SimulationWizard extends JPanel implements WizardMasterInterface {

	private CardLayout card;

	private RpStudy study;
	private RpHardware hw_config;
	private RpSubject header;
	private static SimulationWizard instance;

	LinkedList<Component> stack = new LinkedList<Component>();

	public SimulationWizard() {
		this(null);
	}

	public SimulationWizard(String studyName) {
		initComponents();
		card = (CardLayout) filler.getLayout();
		instance = this; // must be set before any sub-panels added

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

		JPanel page;
		if (studies == null || studies.size() == 0) {
			page = new StudyErrorPanel("<html>No available studies.<br><br>Create a local study or retrieve a collaboration study with <i>Setup</i>.</html>");
		} else if (studyName == null) {
			page = new StudySelectionPanel( this, true, false, false );

			buildWizardNavigationTree();
			tree.setSelectionInterval(0, 0);
		} else {
			page = new StudyErrorPanel("<html>Could not load the indicate study: " + studyName
					+ "<br><br>Create study with <i>Setup</i></html>");
		}

		pushPage(page);

	}

	public static SimulationWizard getInstance() {
		return instance;
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode studySelection = new DefaultMutableTreeNode("Study Selection");
		DefaultMutableTreeNode studyInfo = new DefaultMutableTreeNode("Study Info");
		DefaultMutableTreeNode hardwareSetup = new DefaultMutableTreeNode("Hardware Setup");

		root.add(studySelection);
		root.add(studyInfo);
		root.add(hardwareSetup);

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
				ri.next();
				break;
			}
		}
	}

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

	private static WizardPanelInterface buildPanel(Class<?> clazz) {
		WizardPanelInterface panel = null;

		try {
			Constructor<?> mid = clazz.getConstructor(); // DeviceConfiguration.class
			// );
			Object[] args = new Object[0];
			// args[0] = null;
			panel = (WizardPanelInterface) mid.newInstance(args);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return panel;
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
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("[250dlu,default]:grow", "fill:default:grow, 2*($lgap, default)"));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("80dlu, $lcgap, default:grow", "fill:default:grow"));

			// ======== scrollPane1 ========
			{

				// ---- tree ----
				tree.setBackground(null);
				tree.setRootVisible(false);
				tree.setEnabled(false);
				tree.setModel(null);
				scrollPane1.setViewportView(tree);
			}
			panel2.add(scrollPane1, cc.xy(1, 1));

			// ======== filler ========
			{
				filler.setLayout(new CardLayout());
			}
			panel2.add(filler, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 1));
		add(separator1, cc.xy(1, 3));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default:grow, 6*($lcgap, default), $ugap, default", "default"));

			// ---- previous ----
			previous.setText("< Previous");
			previous.setEnabled(false);
			previous.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					previousActionPerformed(e);
				}
			});
			panel1.add(previous, cc.xy(9, 1));

			// ---- next ----
			next.setText("Next >");
			next.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					nextActionPerformed(e);
				}
			});
			panel1.add(next, cc.xy(11, 1));

			// ---- finish ----
			finish.setText("Finish");
			finish.setEnabled(false);
			finish.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					finishActionPerformed(e);
				}
			});
			panel1.add(finish, cc.xy(13, 1));

			// ---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
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
			String tag = panel.getName();

			filler.add(panel, tag);
			card.show(filler, tag);
			stack.addFirst(panel);

			TreeModel model = tree.getModel();
			if (model != null) {
				TreePath path = tree.getNextMatch(tag, 0, Bias.Forward);
				tree.setSelectionPath(path);

				previous.setEnabled(stack.size() > 1);
			}
		} catch (Exception e) {
			GuiUtil.showError("Internal Error", e);
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

	public RpStudy getStudy() {
		return study;
	}

	public void setStudy(RpStudy study) {
		this.study = study;
		this.hw_config = null;
	}

	public RpHardware getHardware() {
		return hw_config;
	}

	public void setHardware(RpHardware hw_config) {
		this.hw_config = hw_config;
	}

	public void pushSignalSelectionPage(Class<?> clazz) {
		try {
			_pushSignalSelectionPage(clazz);
		} catch (Exception e) {
			GuiUtil.showError("Signal Selection Panel: ", e);
		}
	}

	public void _pushSignalSelectionPage(Class<?> clazz) throws SecurityException, NoSuchMethodException,
			IllegalArgumentException, InstantiationException, IllegalAccessException, InvocationTargetException {
		ObjectFactory of = new ObjectFactory();
		RpDevice dev_conf = of.createRpDevice();

		RpHardware hw_conf = getHardware();
		List<RpDevice> devs = hw_conf.getDevices();
		devs.add(dev_conf);

		Constructor<?> mid = clazz.getConstructor(RpDevice.class);
		Object[] args = new Object[] { dev_conf };
		// args[0] = null;
		JPanel panel = (JPanel) mid.newInstance(args);
		panel.setName("Signal Selection");

		pushPage(panel);
	}

	public RpSubject getSubjectInfo() {
		// TODO Auto-generated method stub
		return header;
	}

	public void setStudyHeader(RpSubject header) {
		this.header = header;
	}

	@Override
	public void setFinished(boolean b) {
		// TODO Auto-generated method stub
		
	}

}
