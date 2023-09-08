/*
 * Created by JFormDesigner on Tue Sep 21 11:22:44 CDT 2010
 */

package idea.tsoffline.export;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Set;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeCellRenderer;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;
import idea.gui.WizardPanelInterface;
import idea.gui.tree.checkbox.CheckTreeManager;
import idea.gui.tree.checkbox.IconCellRenderer;
import idea.gui.tree.checkbox.IconData;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.model.OfflineSignal;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class ExpSignalSelectionPanel extends JPanel implements WizardPanelInterface {

	private boolean showMetrics;
	private boolean showWaveforms;
	private boolean mass_select;

	private ExportWizard wizard;

	private CheckTreeManager checkTreeManager;

	public static final ImageIcon ICON_COMPUTER = new ImageIcon("");
	public static final ImageIcon ICON_DISK = new ImageIcon("defaults1.png");
	public static final ImageIcon ICON_FOLDER = new ImageIcon("fol_orig.png");
	public static final ImageIcon ICON_EXPANDEDFOLDER = new ImageIcon("folder_open.png");

	DefaultMutableTreeNode top;

	public ExpSignalSelectionPanel(ExportWizard wiz, boolean showMetrics, boolean showWaveforms) {
		initComponents();
		setName("Signals");

		this.showMetrics = showMetrics;
		this.showWaveforms = showWaveforms;

		this.wizard = wiz;

		initDeviceList();
	}

	protected void initDeviceList() {

		top = new DefaultMutableTreeNode(new IconData(ICON_COMPUTER, null, "Study"));
		DefaultTreeModel m_model = new DefaultTreeModel(top);

		signalTree.putClientProperty("JTree.lineStyle", "Angled");
		signalTree.setRowHeight(15); // WARNING: I should really take some concern about font size

		TreeCellRenderer renderer = new IconCellRenderer();
		signalTree.setCellRenderer(renderer);

		signalTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
		signalTree.setShowsRootHandles(true);
		signalTree.setEditable(false);

		checkTreeManager = new CheckTreeManager(signalTree, null);
		checkTreeManager.getSelectionModel().addTreeSelectionListener(new TreeSelectionListener() {

			@Override
			public void valueChanged(TreeSelectionEvent arg0) {
				signalTreeValueChanged(null);
			}
		});

		signalTree.setModel(m_model);
	}

	private void signalTreeValueChanged(TreeSelectionEvent e) {

		if (mass_select) {
			return;
		}
		int selected_count = 0;
		DefaultTreeModel model = (DefaultTreeModel) signalTree.getModel();
		Object root = model.getRoot();
		TreeNode node = (TreeNode) root;
		for (int i = 0; i < node.getChildCount(); i++) {
			// FIXME: can we finish
			log.error("check: is anything selected??? can we finish???");
			TreePath[] paths = checkTreeManager.getSelectionModel().getSelectionPaths();
			for (TreePath path : paths) {
				log.error("selected path=" + path);
				selected_count++;
			}
		}

	}

	private void selectAllActionPerformed(ActionEvent e) {
		setAllCheckboxes(true, null);
	}

	private void deselectAllActionPerformed(ActionEvent e) {
		setAllCheckboxes(false, null);
	}

	private void setAllCheckboxes(boolean isSelected, Set<String> signalList) {
		mass_select = true;
		DefaultTreeModel model = (DefaultTreeModel) signalTree.getModel();
		Object root = model.getRoot();
		TreeNode node = (TreeNode) root;

		TreePath[] paths = checkTreeManager.getSelectionModel().getSelectionPaths();
		for (TreePath path : paths) {
			log.error("selected path=" + path);
		}
		checkTreeManager.getSelectionModel().addSelectionPath(null);

		mass_select = false;
		signalTree.repaint();

		signalTreeValueChanged(null);
	}

	private void deviceTreeValueChanged(TreeSelectionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		signalTree = new JTree();
		panel1 = new JPanel();
		selectAll = new JButton();
		deselectAll = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:default:grow, $lgap, default"));

		//======== scrollPane1 ========
		{

			//---- signalTree ----
			signalTree.addTreeSelectionListener(new TreeSelectionListener() {
				@Override
				public void valueChanged(TreeSelectionEvent e) {
					deviceTreeValueChanged(e);
				}
			});
			scrollPane1.setViewportView(signalTree);
		}
		add(scrollPane1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("2*(default, $lcgap), default", "default"));

			//---- selectAll ----
			selectAll.setText("Select All");
			selectAll.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					selectAllActionPerformed(e);
				}
			});
			panel1.add(selectAll, cc.xy(1, 1));

			//---- deselectAll ----
			deselectAll.setText("De-select All");
			deselectAll.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					deselectAllActionPerformed(e);
				}
			});
			panel1.add(deselectAll, cc.xy(3, 1));
		}
		add(panel1, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTree signalTree;
	private JPanel panel1;
	private JButton selectAll;
	private JButton deselectAll;

	// JFormDesigner - End of variables declaration  //GEN-END:variables

	@Override
	public boolean finish() {
		return true;
	}
	
	public Map<String, LinkedList<? extends RpMetric>> getSignals() {
		
		HashMap<String, LinkedList<? extends RpMetric>> signals = new HashMap<String, LinkedList<? extends RpMetric>>();

		DefaultTreeModel model = (DefaultTreeModel) signalTree.getModel();
		TreeNode root = (TreeNode) model.getRoot();
		TreePath[] paths = checkTreeManager.getSelectionModel().getSelectionPaths();
		for (TreePath path : paths) {
			log.info("path=" + path);
			int count = path.getPathCount();
			if (count == 1) {
				// selected everything
				for (int i = 0; i < root.getChildCount(); i++) {
					DefaultMutableTreeNode node = (DefaultMutableTreeNode) root.getChildAt(i);
					IconData icon = (IconData) node.getUserObject();
					DeviceNode dev = (DeviceNode) icon.getObject();
					addDeviceSignals(signals, root, dev.getName());
				}
			} else if (count == 2) {
				// selected full device
				DefaultMutableTreeNode node = (DefaultMutableTreeNode) path.getPathComponent(1);
				IconData icon = (IconData) node.getUserObject();
				DeviceNode dev = (DeviceNode) icon.getObject();
				addDeviceSignals(signals, root, dev.getName());
			} else if (count == 3) {
				DefaultMutableTreeNode d_node = (DefaultMutableTreeNode) path.getPathComponent(1);
				DefaultMutableTreeNode m_node = (DefaultMutableTreeNode) path.getPathComponent(2);
				IconData d_icon = (IconData) d_node.getUserObject();
				DeviceNode dev = (DeviceNode) d_icon.getObject();
				IconData m_icon = (IconData) m_node.getUserObject();
				MetricNode metric = (MetricNode) m_icon.getObject();
				addSignal(signals, dev.getName(), metric.getSig());
			} 
		}

		return signals;
	}

	private void addDeviceSignals(HashMap<String, LinkedList<? extends RpMetric>> signals, TreeNode root, String devName) {

		for (int i = 0; i < root.getChildCount(); i++) {
			DefaultMutableTreeNode d_node = (DefaultMutableTreeNode) root.getChildAt(i);
			IconData icon = (IconData) d_node.getUserObject();
			DeviceNode dev = (DeviceNode) icon.getObject();
			if (devName.equals(dev.getName())) {
				log.info("selecting signals for dev: {}", devName);
				for (int j = 0; j < d_node.getChildCount(); j++) {
					DefaultMutableTreeNode m_node = (DefaultMutableTreeNode) d_node.getChildAt(j);
					icon = (IconData) m_node.getUserObject();
					MetricNode mm = (MetricNode) icon.getObject();
					addSignal(signals, dev.getName(), mm.getSig() );
				}
				break;
			}
		}

	}
	private void addSignal(HashMap<String, LinkedList<? extends RpMetric>> devSignals, String devName, RpMetric sig) {
		LinkedList sigs = devSignals.get(devName);
		if (sigs == null) {
			sigs = new LinkedList<>();
			devSignals.put(devName, sigs);
		}

		sigs.add(sig);
	}


	@Override
	public boolean next() {
		finish();
		return true;
	}

	@Override
	public void refresh() {
		wizard.enableFinish(true);
		wizard.enableNext(false);
		wizard.enableFinish(false);
	}

	public void refresh(PiSubjectImporter importer) {
		PiDatastreamImporter[] devs = importer.getDevices();

		importDevices(devs);
	}

	protected void importDevices(PiDatastreamImporter[] devs) {

		if (devs == null) {
			devs = new PiDatastreamImporter[0];
		}

		next_dev: for (PiDatastreamImporter dev : devs) {

			String devName = dev.getName();

			// first, does root already have this device?  Devices can be repeated in devs
			for (int idx = 0; idx < top.getChildCount(); idx++) {
				DefaultMutableTreeNode child = (DefaultMutableTreeNode) top.getChildAt(idx);
				IconData iconData = (IconData) child.getUserObject();
				DeviceNode dnode = (DeviceNode) iconData.getObject();
				if (dnode.getName().equals(devName)) {
					log.info("duplicate device: {}", dnode.getName());
					continue next_dev;
				}
			}

			DefaultMutableTreeNode node = new DefaultMutableTreeNode(new IconData(ICON_DISK, null, new DeviceNode(
					devName)));
			top.add(node);
			// makes it expandable??? 
			// node.add(new DefaultMutableTreeNode(new Boolean(true)));

			if (showMetrics) {
				StreamID[] streams = dev.getStreams();
				if (streams == null) {
					log.error("no streams for device: {}", devName);
					continue;
				}
				for (StreamID sid : streams) {
					if (sid == StreamID.WAVEFORM) {
						// ignore waveforms
						continue;
					}
					Class<? extends PersistentItem> model = dev.getModel(sid);
					if (model != null) {
						for (RpMetric m : IntfUtil.getMetrics(model)) {
							String name = m.getName();
							if (name == null || name.length() == 0) {
								name = m.getCode();
							}
							name = "[" + m.getLocation() + "] " + name;

							log.warn("EXPORT NOT READY: CREADING OFFLINE SIG: {}", name);
							OfflineSignal offsig = new OfflineSignal( m, TimeseriesType.TT_DATA);
							log.error("FIXME: offsig.setDevice( (PiDatastreamImporter) dev );");
							IconData iconData = new IconData(ICON_DISK, null, new MetricNode(name, offsig));
							DefaultMutableTreeNode sub = new DefaultMutableTreeNode(iconData);
							node.add(sub);
						}
					}
				}
			}

			if (showWaveforms) {
				Class<? extends PersistentItem> model = dev.getModel(StreamID.WAVEFORM);
				if (model != null) {
					for (RpMetric m : IntfUtil.getMetrics(model)) {
						String name = m.getName();
						if (name == null || name.length() == 0) {
							name = m.getCode();
						}
						OfflineSignal offsig = new OfflineSignal(m, TimeseriesType.TT_DATA);
						log.error("FIXME: offsig.setDevice( (PiDatastreamImporter) dev );");
						IconData iconData = new IconData(ICON_DISK, null, new MetricNode(name, offsig));
						DefaultMutableTreeNode sub = new DefaultMutableTreeNode(iconData);
						node.add(sub);
					}
				}

			}
		}

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

}
