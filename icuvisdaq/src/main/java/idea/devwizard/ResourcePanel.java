/*
 * Created by JFormDesigner on Wed Oct 07 12:27:36 CDT 2009
 */

package idea.devwizard;


import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpResource;
import idea.schema.rp.RpStudy;
import idea.GuiUtil;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ResourcePanel extends JPanel implements WizardPanelInterface, TreeSelectionListener {
	private SetupWizardInterface wizard;

	public ResourcePanel(SetupWizardInterface wizard ) {
		initComponents();
		this.wizard = wizard;
		setName("Edit Hardware");
		
		tree.addTreeSelectionListener(this);
		
		refresh();
	}

	public void setResources(List<RpStudy> rr) {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode("Configuration");

		for (RpStudy study : rr) {
			DefaultMutableTreeNode tnDev0 = new DefaultMutableTreeNode( study.getIdentifier() );
			root.add(tnDev0);

			 List<RpResource> sigs = study.getResources();
			if (sigs != null) {
				for (RpResource sig : sigs) {
					tnDev0.add(new DefaultMutableTreeNode( sig ));
				}
			}
		}

		TreeModel tm = new DefaultTreeModel(root);
		tree.setModel(tm);

		expandAll(tree);
		valueChanged(null);
	}

	private void expandAll(JTree tree) {
		int row = 0;
		while (row < tree.getRowCount()) {
			tree.expandRow(row);
			row++;
		}
	}

	private void uploadActionPerformed(ActionEvent e) {
		
		GuiUtil.showMessage("UPLOAD NOT READY" );
		// wizard.setDevice(null);

		WizDevicePanel panel = new WizDevicePanel( wizard, null );
		wizard.pushPage(panel);
	}

	private void removeDeviceActionPerformed(ActionEvent e) {
		RpDevice dev = getSelectedResource();

		assert (dev != null) : "should not get this far with a null device";

		if (dev != null) {
			int ok = GuiUtil.showConfirmDialog("<html>Remove device....<br><br>Are you sure?", "Confirm Remove",
					JOptionPane.YES_NO_OPTION);
			if (ok == JOptionPane.YES_OPTION) {
				GuiUtil.showMessage("NOT IMPLEMENTED");
				// RpUtil.removeDevice( wizard.getHardware().getDevices(), dev );
				
				refresh();
			}
		}
	}

	private RpDevice getSelectedResource() {
		RpDevice dev = null;
		DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();

//		Object nodeInfo = node.getUserObject();
//		if( nodeInfo instanceof DevWrapper ) {
//			DevWrapper wrapper = (DevWrapper)nodeInfo;
//			nodeInfo = wrapper.getDev();
//		}
//		if (nodeInfo instanceof RpDevice) {
//			dev = (RpDevice) nodeInfo;
//		}
		return dev;
	}

	private void detectDevicesActionPerformed(ActionEvent e) {
		
		RpStudy default_study = null;
		WizDeviceDetectionPanel panel = new WizDeviceDetectionPanel( default_study, wizard );
		panel.setName("Device Detection");
		wizard.pushPage(panel);
	}

	private void deleteActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void downloadActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		tree = new JTree();
		panel2 = new JPanel();
		upload = new JButton();
		download = new JButton();
		delete = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[200dlu,default]:grow, $lcgap, default:grow",
			"fill:default:grow"));

		//======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(76, 124));
			scrollPane1.setViewportView(tree);
		}
		add(scrollPane1, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow",
				"default:grow, 3*($lgap, default)"));

			//---- upload ----
			upload.setText("Upload / Store");
			upload.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					uploadActionPerformed(e);
				}
			});
			panel2.add(upload, cc.xy(1, 3));

			//---- download ----
			download.setText("Download / Retrieve");
			download.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					downloadActionPerformed(e);
				}
			});
			panel2.add(download, cc.xy(1, 5));

			//---- delete ----
			delete.setText("Delete");
			delete.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deleteActionPerformed(e);
				}
			});
			panel2.add(delete, cc.xy(1, 7));
		}
		add(panel2, cc.xy(3, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTree tree;
	private JPanel panel2;
	private JButton upload;
	private JButton download;
	private JButton delete;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void valueChanged(TreeSelectionEvent e) {

		boolean isDev = false;

		DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
		if (node != null) {
			Object nodeInfo = node.getUserObject();
			if (nodeInfo instanceof RpResource ) {
				// RpDevice dev = (RpDevice)nodeInfo;
				isDev = true;
			}
		}

	}

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

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

}
