/*
 * Created by JFormDesigner on Thu Dec 31 13:07:09 CST 2009
 */

package idea.tsoffline.explorer;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.io.IOException;
import java.util.Date;
import java.util.LinkedList;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTree;
import javax.swing.border.EmptyBorder;
import javax.swing.text.Position.Bias;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.ts.TsoSession;
import idea.tsoffline.TsSignalTreeSelectionPanel;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class DatasetExplorerWizard extends JPanel  implements WizardMasterInterface {
	private static final String STUDY_HEADER = "Study";
	private static final String SIGNAL_SELECTION = "Selection";
	
	private InfoAndRangeSelection headerPanel;
	private TsSignalTreeSelectionPanel signalSelection;

	private CardLayout card;
	private boolean finished = false;
	LinkedList<Component> stack = new LinkedList<Component>();

	public DatasetExplorerWizard() {
		initComponents();
		card = (CardLayout) filler.getLayout();

		enableNext(true);
		enableFinish(false);
		enablePrevious(false);

		safeAdd(headerPanel = new InfoAndRangeSelection(this), STUDY_HEADER );
		safeAdd(signalSelection = new TsSignalTreeSelectionPanel( this ), SIGNAL_SELECTION);
		
		buildWizardNavigationTree();
		tree.setSelectionInterval(0, 0);

		pushPage(headerPanel);
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

	public void setImporter(PiSubjectImporter importer) throws IOException {

		headerPanel.setImporter( importer );

		signalSelection.setSignalsInfo(importer.getDevices());
		signalSelection.selectAll();
		

	}


	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode studyInfo = new DefaultMutableTreeNode(STUDY_HEADER);
		DefaultMutableTreeNode signalSelection = new DefaultMutableTreeNode(SIGNAL_SELECTION);

		root.add(studyInfo);
		root.add(signalSelection);

		tree.setModel(new DefaultTreeModel(root));
		expandAll();
	}

	private void expandAll() {
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
//		
		if ( ri == headerPanel ) {
			pushPage( signalSelection);
			
			enableNext(false);
			enableFinish( true );
		} else if (ri == signalSelection) {
			finishActionPerformed(null);
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


	@Override
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
			
			refresh();
		} catch (Exception e) {
			GuiUtil.showError("Internal Error", e);
		}

	}

	@Override
	public void enableNext(boolean b) {
		next.setEnabled(b);
	}

	@Override
	public void enablePrevious(boolean b) {
		previous.setEnabled(b);
	}

	@Override
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


	@Override
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

	private void previousActionPerformed(ActionEvent e) {
		popPage();
		enableNext(true);  // default...can be changed in the refresh method

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
		panel4 = new JPanel();
		previous = new JButton();
		next = new JButton();
		finish = new JButton();
		cancel = new JButton();

		//======== this ========
		setBorder(Borders.DLU2);
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, $lgap, 10dlu, $lgap, default"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"[70dlu,default], $lcgap, default:grow",
				"fill:default:grow"));

			//======== scrollPane1 ========
			{

				//---- tree ----
				tree.setBackground(null);
				tree.setRootVisible(false);
				tree.setEnabled(false);
				tree.setModel(null);
				scrollPane1.setViewportView(tree);
			}
			panel2.add(scrollPane1, CC.xy(1, 1));

			//======== filler ========
			{
				filler.setBorder(new EmptyBorder(5, 5, 5, 5));
				filler.setLayout(new CardLayout());
			}
			panel2.add(filler, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 1));
		add(separator1, CC.xy(1, 3));

		//======== panel4 ========
		{
			panel4.setLayout(new FormLayout(
				"default, $lcgap, default:grow, 3*($lcgap, [50dlu,default]), $ugap, [50dlu,default]",
				"default"));

			//---- previous ----
			previous.setText("< Previous");
			previous.addActionListener(e -> previousActionPerformed(e));
			panel4.add(previous, CC.xy(5, 1));

			//---- next ----
			next.setText("Next >");
			next.addActionListener(e -> nextActionPerformed(e));
			panel4.add(next, CC.xy(7, 1));

			//---- finish ----
			finish.setText("Finish");
			finish.addActionListener(e -> finishActionPerformed(e));
			panel4.add(finish, CC.xy(9, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.setMinimumSize(new Dimension(70, 21));
			cancel.setPreferredSize(new Dimension(70, 21));
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel4.add(cancel, CC.xy(11, 1));
		}
		add(panel4, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTree tree;
	private JPanel filler;
	private JSeparator separator1;
	private JPanel panel4;
	private JButton previous;
	private JButton next;
	private JButton finish;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables


	public boolean isFinished() {
		return finished;
	}

	@Override
	public void setFinished(boolean b) {
		this.finished = b;
	}

	public Date getStartDate() {
		return headerPanel.getStartDate();
	}

	public Date getEndDate() {
		return headerPanel.getEndDate();
	}

	public void setSignalInfo(PiDatastreamImporter[] piDatastreamImporters) {
		signalSelection.setSignalsInfo( piDatastreamImporters );
	}

	public TsoSession getSession() {
		return signalSelection.getSession();
	}

}
