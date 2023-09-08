/*
 * Created by JFormDesigner on Tue Jan 11 14:36:21 CST 2011
 */

package idea.tsoffline.derivsigwiz;

import java.util.HashSet;
import java.util.Set;

import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.persistence.PiDatastreamImporter;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppModel;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.canvas.PLayerStream;
import idea.tsoffline.model.OfflineDevice;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class SourceSignalSelection extends JPanel implements WizardPanelInterface, TreeSelectionListener {

	private HPSplitableLayer selectedSig;

	public SourceSignalSelection(HPSplitableLayer selectedSig) {
		initComponents();
		this.selectedSig = selectedSig;

		DerivedSigWizard wiz = DerivedSigWizard.getInstance();
		wiz.enableNext(false);
		wiz.enableFinish(false);

		initTree();
	}

	private void initTree() {

		tree.getSelectionModel().addTreeSelectionListener(this);
		refresh();

	}

	private void expandSelected(JTree t) {
		if (selectedSig == null) {
			return; // no selected signal
		}

		TreeNode[] selectedPath = null;

		TreeModel model = t.getModel();
		Object root = model.getRoot();

		
		PiDatastreamImporter selectedDev = new PLayerStream( selectedSig,  AppModel.getStartTime(), 'W');
		String devName = selectedDev.getName();

		outer_loop: for (int i = 0; i < model.getChildCount(root); i++) {
			DefaultMutableTreeNode dev_node = (DefaultMutableTreeNode) model.getChild(root, i);
			OfflineDevice dev = (OfflineDevice) dev_node.getUserObject();
			if (devName.equals(dev.getName())) {
				for (int j = 0; j < dev_node.getChildCount(); j++) {
					DefaultMutableTreeNode sig_node = (DefaultMutableTreeNode) dev_node.getChildAt(j);
					HPSplitableLayer sig = (HPSplitableLayer) sig_node.getUserObject();
					if (selectedSig.equals(sig)) {
						selectedPath = sig_node.getPath();
						break outer_loop;
					}
				}
			}
		}
		if (selectedPath != null) {
			TreePath tp = new TreePath(selectedPath);
			t.expandPath(tp);
			t.setSelectionPath(tp);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Source Signal");
		scrollPane2 = new JScrollPane();
		tree = new JTree();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("[350dlu,default]:grow", "default, $lgap, fill:default:grow"));
		add(separator1, cc.xy(1, 1));

		// ======== scrollPane2 ========
		{

			// ---- tree ----
			tree.setRootVisible(false);
			scrollPane2.setViewportView(tree);
		}
		add(scrollPane2, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JScrollPane scrollPane2;
	private JTree tree;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {

		TreePath path = tree.getSelectionPath();

		DerivedSigWizard wiz = DerivedSigWizard.getInstance();
		DefaultMutableTreeNode lastNode = (DefaultMutableTreeNode) path.getLastPathComponent();
		wiz.setSourceSignal((HPSplitableLayer) lastNode.getUserObject());

		DerivedSignalSelection panel = new DerivedSignalSelection();
		panel.setName("Derived Signal");
		wiz.pushPage(panel);

		return true;
	}

	@Override
	public void refresh() {
		Set<String> cached = new HashSet<String>();
		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		for (OfflineDevice dev : AppModel.getDevices()) {
			if (dev == null || dev.getName() == null) {
				log.error("SKIPPING....annotations...alarms?");
			} else {
				String devName = dev.getName();
				if (cached.contains(devName)) {
					// already added...skip
				} else {
					DefaultMutableTreeNode deviceNode = new DefaultMutableTreeNode(dev);
					GuiUtil.showMessage("FIXME: );addSignals(deviceNode, dev.getStreams());");

					root.add(deviceNode);
					cached.add(devName);
				}
			}
		}

		tree.setModel(new DefaultTreeModel(root));
		expandSelected(tree);

	}

	@Override
	public void valueChanged(TreeSelectionEvent e) {
		TreePath path = e.getPath();
		DerivedSigWizard wiz = DerivedSigWizard.getInstance();
		wiz.enableNext(path != null);

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}
}
