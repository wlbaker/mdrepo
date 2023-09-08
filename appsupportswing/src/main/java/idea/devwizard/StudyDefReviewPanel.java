/*
 * Created by JFormDesigner on Wed Oct 07 12:27:36 CDT 2009
 */

package idea.devwizard;

import java.awt.Dimension;
import java.util.List;
import java.util.Map;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.GuiUtil;
import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class StudyDefReviewPanel extends JPanel implements WizardPanelInterface {
	private SetupWizardInterface wizard;

	public StudyDefReviewPanel(SetupWizardInterface wizard) {
		initComponents();
		this.wizard = wizard;
		setName("Review");

		refresh();
	}

	private void setStudy(RpStudy study) {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode("Configuration");

		List<RpHardware> hws = null;

		if (study != null) {
			hws = study.getHardware();
		}

		if (hws != null) {
			for (RpHardware hw : hws) {
				DefaultMutableTreeNode tnHW = new DefaultMutableTreeNode(hw.getName());
				root.add(tnHW);

				List<RpDevice> devs = hw.getDevices();
				showDevs(tnHW, devs);
			}
		}

		List<RpAnalysis> anals = study.getAnalysis();
		if (anals != null && anals.size() > 0 ) {
			DefaultMutableTreeNode tnHW = new DefaultMutableTreeNode("Analysis");
			root.add(tnHW);
			
			showAnalyses(tnHW, study.getAnalysis());
		}

		TreeModel tm = new DefaultTreeModel(root);
		profileTree.setModel(tm);

		expandAll(profileTree);
	}

	private void showAnalyses(DefaultMutableTreeNode parent, List<RpAnalysis> anals ) {
		if (anals == null) {
			return;
		}
		
		for (RpAnalysis anal : anals) {
			DefaultMutableTreeNode tnDev0 = new DefaultMutableTreeNode( anal.getName() );
			parent.add(tnDev0);
			
			Map<String,String> params = anal.getParam();
			if (params != null) {
				for (String key : params.keySet() ) {
					Object val = params.get(key);
					if( val == null ) {
						val = "?";
					} else {
						String s = val.toString();
						if( s.length() > 60 ) {
							s = s.substring(0, 58) + "...";
						}
						val = s;
					}
					tnDev0.add(new DefaultMutableTreeNode( key + ": " + val ));
				}
			}
		}
	}

	private void showDevs(DefaultMutableTreeNode parent, List<RpDevice> devs) {
		if (devs == null) {
			return;
		}

		for (RpDevice dev : devs) {
			DefaultMutableTreeNode tnDev0 = new DefaultMutableTreeNode(getDeviceName(dev));
			parent.add(tnDev0);

			List<? extends RpMetric> metrics = RpUtil.getMetrics(dev, StreamID.MEASUREMENT);
			if (metrics != null) {
				for (RpMetric metric : metrics) {
					tnDev0.add(new DefaultMutableTreeNode(getMetricName(metric)));
				}
			}

			metrics = RpUtil.getMetrics(dev, StreamID.SETTINGS);
			if (metrics != null) {
				for (RpMetric metric : metrics) {
					tnDev0.add(new DefaultMutableTreeNode(getMetricName(metric)));
				}
			}
			
			List<? extends RpMetric> sigs = RpUtil.getMetrics(dev, StreamID.WAVEFORM);
			if (sigs != null) {
				for (RpMetric sig : sigs) {
					tnDev0.add(new DefaultMutableTreeNode(getMetricName(sig)));
				}
			}

			showDevs(tnDev0, dev.getDevices());
		}
	}

	private String getMetricName(RpMetric sig) {
		String name = sig.getName();
		if (name == null || name.trim().length() == 0 ) {
			name = sig.getCode();
		}
		return name;
	}

	private String getDeviceName(RpDevice dev) {
		return dev.getName();
	}

	private void expandAll(JTree tree) {
		int row = 0;
		while (row < tree.getRowCount()) {
			tree.expandRow(row);
			row++;
		}
	}

	public void addTreeSelectionListener(TreeSelectionListener tsl) {
		profileTree.addTreeSelectionListener(tsl);

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		profileTree = new JTree();
		panel2 = new JPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[300dlu,default]:grow, $lcgap, default:grow",
			"fill:default:grow"));

		//======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(81, 60));
			scrollPane1.setViewportView(profileTree);
		}
		add(scrollPane1, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow",
				"default:grow, 3*($lgap, default)"));
		}
		add(panel2, cc.xy(3, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTree profileTree;
	private JPanel panel2;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean next() {
		return true;

	}

	@Override
	public void refresh() {
		RpStudy study = wizard.getStudy();
		setStudy(study);

		wizard.enableNext(false);
		wizard.enableFinish(true);
	}

	@Override
	public boolean finish() {
		RpStudy study = wizard.getStudy();

		RepositoryInterface local = RepositoryFactory.getLocalRepository();
		try {
			local.createStudy(study);
			return true;
		} catch (Exception e) {
			GuiUtil.showError("Saving Study: ", e);
		}

		return false;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

}
