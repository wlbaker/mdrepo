/*
 * Created by JFormDesigner on Tue Jan 11 14:36:21 CST 2011
 */

package idea.tsoffline.vizwiz;

import java.util.List;

import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppModel;
import idea.tsoffline.model.OfflineDevice;
import idea.tsoffline.model.OfflineSignal;
import idea.tsoffline.model.OfflineStream;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class VizSignalSelection extends JPanel implements WizardPanelInterface, TreeSelectionListener {

	private WizardMasterInterface wiz;

	public VizSignalSelection(WizardMasterInterface wiz) {
		initComponents();
		this.wiz = wiz;

		tree.getSelectionModel().addTreeSelectionListener(this);
		refresh();
	}

	private static void expandAll(JTree t) {
		for (int i = 0; i < t.getRowCount(); i++) {
			t.expandRow(i);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Source Signal");
		scrollPane1 = new JScrollPane();
		tree = new JTree();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("[350dlu,default]:grow", "default, $lgap, fill:default:grow"));
		add(separator2, cc.xy(1, 1));

		// ======== scrollPane1 ========
		{

			// ---- tree ----
			tree.setRootVisible(false);
			scrollPane1.setViewportView(tree);
		}
		add(scrollPane1, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator2;
	private JScrollPane scrollPane1;
	private JTree tree;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {

		return true;
	}

	@Override
	public void refresh() {
		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		for (OfflineDevice dev : AppModel.getDevices()) {
			if (dev == null || dev.getName() == null) {
				System.out.println("SKIPPING....annotations?");
			} else {
				DefaultMutableTreeNode deviceNode = new DefaultMutableTreeNode(dev);
				addStreams(deviceNode, dev.getStreams());

				root.add(deviceNode);
			}
		}

		tree.setModel(new DefaultTreeModel(root));
		expandAll(tree);

		valueChanged(null);
	}

	private void addStreams(DefaultMutableTreeNode parent, List<OfflineStream> streams) {
		if (streams == null) {
			return;
		}

		for (OfflineStream signal : streams) {

			DefaultMutableTreeNode child = new DefaultMutableTreeNode(signal);
			parent.add(child);
			GuiUtil.showMessage("addSignals(child, signal.getChildSignals()); // viz signal selection recursively add");
		}

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public void valueChanged(TreeSelectionEvent e) {
		TreePath path = tree.getSelectionPath();

		boolean hasNext = false;
		if (path != null) {
			DefaultMutableTreeNode node = (DefaultMutableTreeNode) path.getLastPathComponent();
			Object userobj = node.getUserObject();
			if (userobj instanceof OfflineSignal) {
				// wiz.setSelectedSignal((OfflineSignal) userobj);
				hasNext = true;
			}

		}

		wiz.enableNext(hasNext);
		wiz.enableFinish(false);
	}
}
