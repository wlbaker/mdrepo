/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.meddaq.entry;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedList;

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

import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.gui.wizard.DeviceSelectionPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

// import static WizDeviceID.*;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ConnectionWizard extends JPanel implements WizardMasterInterface {

	private final static String DEVICE_SELECTION = "Device Selection";
	private static final String SOURCE_DETAIL = "Source Detail";

	private CardLayout card;

	LinkedList<Component> stack = new LinkedList<Component>();

	private String curr;

	private boolean finished = false;
	private DeviceSelectionPanel devicePanel;

	public ConnectionWizard() {
		initComponents();
		card = (CardLayout) filler.getLayout();

		// pushPage(new SourceSelectionPanel());
		safeAdd(devicePanel = new DeviceSelectionPanel(), DEVICE_SELECTION);
		// safeAdd(analPanel = new AnReview( profile ), REVIEW_ANAL_PANEL);

		buildWizardNavigationTree();
		tree.setSelectionInterval(0, 0);

		// ? progressBar1.setVisible( false );
	}

	private void safeAdd(JPanel p, String tag) {
		try {
			if( curr == null ) {
				curr = tag;
			}
			filler.add(p, tag);
		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(null, "Internal Error: " + e.getMessage());
		}
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode srcsel = new DefaultMutableTreeNode(DEVICE_SELECTION);
		// DefaultMutableTreeNode signals = new DefaultMutableTreeNode(SAVE_SETUP, true);

		root.add(srcsel);
		// root.add(signals);

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

		if (curr.equals(DEVICE_SELECTION)) {
			nextPage = SOURCE_DETAIL;
//		} else if (curr.equals(SOURCE_DETAIL)) {
//			nextPage = ANALYSIS_SETUP;
//		} else if (curr.equals(ANALYSIS_SETUP)) {
//			nextPage = OUTPUT_SETUP;
//		} else if (curr.equals(OUTPUT_SETUP)) {
//			nextPage = SAVE_SETUP;
//
//			SimulatorOutputPanel lastPanel = new SimulatorOutputPanel(this, getAnalysis("simulator"));
//			pushPage(lastPanel);
			finishActionPerformed( null );
		} else {
			System.err.println( "ConnectionWizard: page not identifed");
		}

		if (nextPage != null) {

			setCurrentPanel(nextPage);
		}

	}

	private void setCurrentPanel(String nextPage) {
		card.show(filler, nextPage);

		curr = nextPage;
	}

	private void finishActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.finish();
				break;
			}
		}
		// hmm...no chance to quit?
		setExecute(true);
		GuiUtil.closeDialog(this);
	}

	private void previousActionPerformed(ActionEvent e) {
		popPage();
		refresh();
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
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
			} else {
				curr = p_name;
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

	public void setExecute(boolean b) {
		finished = b;
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
			panel1.setLayout(new FormLayout("default, $lcgap, default:grow, 5*($lcgap, default), $ugap, default",
					"default"));

			// ---- previous ----
			previous.setText("< Previous");
			previous.setEnabled(false);
			previous.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					previousActionPerformed(e);
				}
			});
			panel1.add(previous, cc.xy(9, 1));

			// ---- next ----
			next.setText("Next >");
			next.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					nextActionPerformed(e);
				}
			});
			panel1.add(next, cc.xy(11, 1));

			// ---- finish ----
			finish.setText("Finish");
			finish.setEnabled(false);
			finish.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					finishActionPerformed(e);
				}
			});
			panel1.add(finish, cc.xy(13, 1));

			// ---- cancel ----
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

	public String getConnection() {
		return devicePanel.getConnection();		
	}

	@Override
	public void setFinished(boolean b) {
		// TODO Auto-generated method stub
		
	}

}
