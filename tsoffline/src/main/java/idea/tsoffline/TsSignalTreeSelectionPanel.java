/*
 * Created by JFormDesigner on Sun Jul 20 14:34:16 CDT 2014
 */

package idea.tsoffline;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTree;
import javax.swing.JViewport;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import idea.persistence.PiDatastreamImporter;
import idea.persistmanager.hdf5.H5GroupImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.gui.tree.checkbox.CheckTreeManager;
import idea.gui.tree.checkbox.CheckTreeSelectionModel;
import idea.gui.tree.checkbox.IconCellRenderer;
import idea.gui.tree.checkbox.IconData;
import idea.ts.TsoDeviceType;
import idea.ts.TsoSession;
import idea.ts.TsoSignalLayerType;
import idea.tsoffline.export.DeviceNode;
import idea.tsoffline.export.MetricNode;

/**
 * @author User #1
 */

@SuppressWarnings("serial")
@Slf4j
public class TsSignalTreeSelectionPanel extends JPanel implements WizardPanelInterface {
	private IconCellRenderer icon_cell_renderer;
	private WizardMasterInterface wiz;
	private PiDatastreamImporter[] devs;
	// private PiSubjectImporter importer;
	// private PiDatastreamImporter[] devs;
	public static final ImageIcon ICON_COMPUTER = new ImageIcon("");
	public static final ImageIcon ICON_DISK = new ImageIcon("defaults1.png");
	public static final ImageIcon ICON_FOLDER = new ImageIcon("fol_orig.png");
	public static final ImageIcon ICON_EXPANDEDFOLDER = new ImageIcon("folder_open.png");

	public TsSignalTreeSelectionPanel(WizardMasterInterface wiz) {
		initComponents();

		this.wiz = wiz;
		clear();

		showButtons(false);
		if (wiz != null) {
			wiz.enableFinish(true);
			wiz.enableNext(true);
		}
	}

	private void showButtons(boolean b) {
		optionsPanel.setVisible(!b);
	}

	private void initTree(JTree tree1) {
		tree1.setRowHeight(15); // WARNING: I should really take some concern
								// about font size

		/*
		 * old model
		 */

		tree1.setRootVisible(false);
		tree1.setShowsRootHandles(true);

		/*
		 * migrating to new model
		 */

		tree1.putClientProperty("JTree.lineStyle", "Angled");

		icon_cell_renderer = new IconCellRenderer();
		tree1.setCellRenderer(icon_cell_renderer);

		// FIXME: signalTree.addTreeExpansionListener(new
		// DirExpansionListener());
		log.error("signalTree.addTreeExpansionListener(new DirExpansionListener());");

		TreeSelectionModel sel_model = tree1.getSelectionModel();
		sel_model.setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
		tree1.addTreeSelectionListener(new TreeSelectionListener() {

			@Override
			public void valueChanged(TreeSelectionEvent e) {

				if (!e.isAddedPath()) {
					// ignore path removed
				}

				JTree t = (JTree) e.getSource();

				// PART1: notify currently selected signal
				TreePath path = e.getNewLeadSelectionPath();
				if (path == null) {
					return; // no path selected, ignore
				}
				MetricNode metric = null;
				RpMetric selected_signal = null;
				int count = path.getPathCount();
				if (count == 1) {
				} else if (count == 2) {
				} else if (count == 3) {
					DefaultMutableTreeNode m_node = (DefaultMutableTreeNode) path.getPathComponent(2);
					IconData m_icon = (IconData) m_node.getUserObject();
					metric = (MetricNode) m_icon.getObject();
					selected_signal = metric.getSig();
				}
				putClientProperty("selected_signal", selected_signal);

				syncIconColors(t);
				t.repaint();

			}
		});
		tree1.setEditable(false);

		CheckTreeManager checkTreeManager = new CheckTreeManager(tree1, null);

		tree1.putClientProperty("manager", checkTreeManager);
//		checkTreeManager.getSelectionModel().addTreeSelectionListener(new TreeSelectionListener() {
//
//			@Override
//			public void valueChanged(TreeSelectionEvent arg0) {
//				updateLoadHideButtons(arg0);
//			}
//		});
	}

	protected void syncIconColors(JTree tree) {
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		TreeNode root = (TreeNode) model.getRoot();
		for (int iroot = 0; iroot < root.getChildCount(); iroot++) {
			DefaultMutableTreeNode devnode = (DefaultMutableTreeNode) root.getChildAt(iroot);
			IconData dev_icondata = (IconData) devnode.getUserObject();
			DeviceNode dev_devdata = (DeviceNode) dev_icondata.getObject();
			for (int idev = 0; idev < devnode.getChildCount(); idev++) {
				DefaultMutableTreeNode signode = (DefaultMutableTreeNode) devnode.getChildAt(idev);
				IconData icondata = (IconData) signode.getUserObject();
				MetricNode sig_sigdata = (MetricNode) icondata.getObject();
				Color color = Color.black; // 071219 sig_sigdata.getSig().getColor();

				icondata.setColor(color);
			}
		}
	}

	public void setSignalsInfo(PiDatastreamImporter[] devs) {
		this.devs = devs;
		refresh();
	}

	protected void addStreamDevices(DefaultMutableTreeNode top, PiDatastreamImporter[] devs2, StreamID sid) {

		if (devs2 == null) {
			return;
		}

		List<String> listed = new LinkedList<String>(); // a cache list so
														// devices are not
														// duplicated

		for (PiDatastreamImporter dev : devs2) {

			if( dev instanceof H5GroupImporter ) {
				H5GroupImporter grp = (H5GroupImporter) dev;
				dev = grp.getDatasetImporter( sid );
				if( dev == null ) {
					continue;
				}
			}
			

			RpDevice conf = dev.getConfiguration();
			if (conf == null) {
				log.warn("device configuration is null: {}", dev.getName());
				continue;
			}
			List<? extends RpStream> streams = conf.getStreams();
//
			String devName = dev.getName();
			if (listed.contains(devName)) {
				continue;
			}

			List<RpMetric> signals = null;
			for (RpStream s : streams) {
				if (s.getName().equalsIgnoreCase(sid.getName())) {
					signals = s.getMetric();
					break;
				}
			}

			if (signals == null || signals.size() == 0) {
				// empty dataset
				continue;
			}
			listed.add(devName);
			
			DefaultMutableTreeNode node = new DefaultMutableTreeNode( new IconData(ICON_DISK, null, new DeviceNode(devName)));
			top.add(node);
			for (RpMetric sig : signals) {
				String name = sig.getName();

				IconData iconData = new IconData(ICON_DISK, null, new MetricNode(name, sig), Color.black); // sig.getColor());
				DefaultMutableTreeNode sub = new DefaultMutableTreeNode(iconData);
				node.add(sub);
			}

		}

		return;
	}

	static private void expandAll(JTree tree) {
		for (int i = 0; i < tree.getRowCount(); i++) {
			tree.expandRow(i);
		}
	}

	public TsoSession getSession() {
		TsoSession session = new TsoSession();

		// hide tabs that have no data
		List<TsoDeviceType> tsodevs = session.getTsoDevices();
		for (int i = 0; i < tabber.getTabCount(); i++) {
			JTree tree = getTreeAt(i);
			TsoDeviceType dev = createSessionDevFromTreeSelection(tree);
			if (dev != null) {
				tsodevs.add(dev);
			}
		}

		return session;
	}

	private TsoDeviceType createSessionDevFromTreeSelection(JTree tree) {
		TsoDeviceType tsodev = null;

		Map<String, List<RpMetric>> map = new HashMap<String, List<RpMetric>>();
		System.out.println("creatingSession from tree");
		getSelectedSignals(tree, map);

		StreamID sid = (StreamID) tree.getClientProperty("sid");
		for (String dev : map.keySet()) {
			List<RpMetric> sigs = map.get(dev);
			if (sigs == null || sigs.size() == 0) {
				continue;
			}
			if (tsodev == null) {
				tsodev = new TsoDeviceType();
				tsodev.setDeviceName(dev);
			}
			List<TsoSignalLayerType> layers = tsodev.getSignalLayer();
			for (RpMetric m : sigs) {
				TsoSignalLayerType layer = new TsoSignalLayerType();
				layer.setLoc(m.getLocation());
				layer.setName(m.getName());
				layer.setSidName(sid.getName());
				layer.setVisible(true); // show all selected signals by default
				layers.add(layer);
			}
		}
		return tsodev;

	}

	private void getSelectedSignals(JTree tree, Map<String, List<RpMetric>> map) {
		CheckTreeManager checkTreeManager = (CheckTreeManager) tree.getClientProperty("manager");
		TreePath[] paths = checkTreeManager.getSelectionModel().getSelectionPaths();
		getSelectedSignals(paths, map);
	}

	private void getSelectedSignals(TreePath[] paths, Map<String, List<RpMetric>> map) {
		for (TreePath path : paths) {
			int count = path.getPathCount();
			if (count == 1) {
				// this happens in particular when there is only one item in the
				// checklist,
				// and that one item is selected
				DefaultMutableTreeNode node = (DefaultMutableTreeNode) path.getPathComponent(0);
				getAllDeviceMaps(map, node);
			} else if (count == 2) {
				DefaultMutableTreeNode d_node = (DefaultMutableTreeNode) path.getPathComponent(1);
				getOneDeviceMap(map, d_node);
			} else if (count == 3) {
				DefaultMutableTreeNode d_node = (DefaultMutableTreeNode) path.getPathComponent(1);
				DefaultMutableTreeNode m_node = (DefaultMutableTreeNode) path.getPathComponent(2);
				addOneSignalToMap(map, d_node, m_node);
			}
		}
	}

	private void getAllDeviceMaps(Map<String, List<RpMetric>> map, DefaultMutableTreeNode node) {
		Enumeration<TreeNode> childs = node.children();

		while (childs.hasMoreElements()) {
			getOneDeviceMap(map, childs.nextElement());
		}
	}

	private static void addOneSignalToMap(Map<String, List<RpMetric>> map, DefaultMutableTreeNode d_node, TreeNode tn) {
		DefaultMutableTreeNode treeNode = (DefaultMutableTreeNode) tn;
		IconData d_icon = (IconData) d_node.getUserObject();
		DeviceNode dev = (DeviceNode) d_icon.getObject();
		IconData m_icon = (IconData) treeNode.getUserObject();
		MetricNode metric = (MetricNode) m_icon.getObject();

		List<RpMetric> list = map.get(dev.getName());

		if (list == null) {
			list = new LinkedList<RpMetric>();
			map.put(dev.getName(), list);
		}
		list.add(metric.getSig());
	}

	private void getOneDeviceMap(Map<String, List<RpMetric>> map, TreeNode tn) {

		DefaultMutableTreeNode treeNode = (DefaultMutableTreeNode) tn;
		Enumeration<TreeNode> childs = treeNode.children();
		while (childs.hasMoreElements()) {
			addOneSignalToMap(map, treeNode, childs.nextElement());
		}
	}

	public void clear() {

		tabber.removeAll();

	}

	public void refresh() {

		Object ss = getClientProperty("selected_signal");
		putClientProperty("selected_signal", null);

		/*
		 * Recycle the trees...which preserves the selection model
		 */
		Map<StreamID, JTree> trees = new HashMap<StreamID, JTree>();

//		int count = tabber.getTabCount();
//		for (int i = 0; i < count; i++) {
//			JTree tree = getTreeAt(i);
//			StreamID sid = (StreamID) tree.getClientProperty("sid");
//			trees.put(sid, tree);
//		}
		tabber.removeAll();

		StreamID[] ids = new StreamID[] { StreamID.ANNOTATION, StreamID.MEASUREMENT, StreamID.MEASUREMENT_2,
				StreamID.MEASUREMENT_3, StreamID.SETTINGS, StreamID.WAVEFORM };
		ids = new StreamID[] {  StreamID.WAVEFORM };
		log.error("FIXME: debugging for WAVEFORMS only");

		for (StreamID sid : ids) {
			DefaultMutableTreeNode top = new DefaultMutableTreeNode(new IconData(ICON_COMPUTER, null, "Study"));
			addStreamDevices(top, devs, sid);
			DefaultTreeModel model = new DefaultTreeModel( top );
			if (model != null && model.getRoot() != null) {
				JTree tree = null; // trees.get(sid);
				if (tree == null) {
					tree = new JTree(model);
					initTree(tree);
					tree.putClientProperty("sid", sid);
					trees.put(sid, tree);
				}

				expandAll(tree);

				JScrollPane sp = new JScrollPane(tree);
				tabber.addTab(sid.getName(), sp);
			}

		}

		// well...it sorta is checked still. Need to tell listeners
		if (ss != null) {
			putClientProperty("selected_signal", ss);
		}

		//
		// Enable the NEXT option...maybe only if some datapoints are selected
		//
		if (wiz != null) {
			wiz.enableNext(true);
		}

		selectAll();
	}

	public void selectSignal(String devName, StreamID reqSID, String loc) {
		for (int i = 0; i < tabber.getTabCount(); i++) {
			JTree tree = getTreeAt(i);
			StreamID sid = (StreamID) tree.getClientProperty("sid");
			if (reqSID != null && reqSID != sid) {
				continue;
			}
			selectSignal(tree, devName, loc);
		}

	}

	private void selectSignal(JTree tree, String devName, String loc) {

		CheckTreeManager manager = (CheckTreeManager) tree.getClientProperty("manager");
		CheckTreeSelectionModel selections = manager.getSelectionModel();
		if (selections.getSelectionCount() > 0) {
			return;
		}
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		TreeNode root = (TreeNode) model.getRoot();
		for (int iroot = 0; iroot < root.getChildCount(); iroot++) {
			DefaultMutableTreeNode devnode = (DefaultMutableTreeNode) root.getChildAt(iroot);
			IconData dev_icondata = (IconData) devnode.getUserObject();
			DeviceNode dev_devdata = (DeviceNode) dev_icondata.getObject();
			if (devName == null || devName.equals(dev_devdata.getName())) {
				for (int idev = 0; idev < devnode.getChildCount(); idev++) {
					DefaultMutableTreeNode signode = (DefaultMutableTreeNode) devnode.getChildAt(idev);
					IconData sig_icondata = (IconData) signode.getUserObject();
					MetricNode sig_sigdata = (MetricNode) sig_icondata.getObject();
					RpMetric desc = sig_sigdata.getSig();
					if (loc == null || loc.equals(desc.getLocation())) {
						TreePath path = new TreePath(signode.getPath());
						selections.addSelectionPath(path);
					}
				}
			}
		}
		manager.setSelectionModel(selections);
	}

	private JTree getTreeAt(int i) {
		Component comp = tabber.getComponentAt(i);
		JScrollPane sp = (JScrollPane) comp;
		JViewport vp = sp.getViewport();
		JTree tree = (JTree) vp.getView();

		return tree;
	}

	private void viewActionPerformed(ActionEvent e) {
		for (int i = 0; i < tabber.getTabCount(); i++) {
			Map<String, List<RpMetric>> map = new HashMap<String, List<RpMetric>>();
			JTree tree = getTreeAt(i);
			getSelectedSignals(tree, map);
			for (String dev : map.keySet()) {
				List<RpMetric> sigs = map.get(dev);
				log.error("FIXME 071219: rpmetric and visiblility");
				for (RpMetric sig : sigs) {
//					PLayer layer = sig.getLayer();
//					if (layer != null) {
//						boolean vis = layer.getVisible();
//						layer.setVisible(!vis);
//						layer.repaint();
//					}
				}
			}
		}

		refresh();

	}

	private void resetLabelsActionPerformed(ActionEvent e) {

		JTree tree = getTreeAt(tabber.getSelectedIndex());

		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		TreeNode root = (TreeNode) model.getRoot();
		for (int iroot = 0; iroot < root.getChildCount(); iroot++) {
			DefaultMutableTreeNode devnode = (DefaultMutableTreeNode) root.getChildAt(iroot);
			IconData dev_icondata = (IconData) devnode.getUserObject();
			DeviceNode dev_devdata = (DeviceNode) dev_icondata.getObject();
			for (int idev = 0; idev < devnode.getChildCount(); idev++) {
				DefaultMutableTreeNode signode = (DefaultMutableTreeNode) devnode.getChildAt(idev);
				IconData icondata = (IconData) signode.getUserObject();
				MetricNode sig_sigdata = (MetricNode) icondata.getObject();
				Color color = Color.black; // 071219 sig_sigdata.getSig().getColor();

				icondata.setColor(color);

				String name = sig_sigdata.getSig().getName();
				if (name == null) {
					name = sig_sigdata.getSig().getLocation();
				}
				if (name == null) {
					name = sig_sigdata.getSig().getCode();
				}
				String[][] translation = AppModel.getSubstitutionsModel();
				for (int tr = 0; tr < translation.length; tr++) {
					if (translation[tr][0].equals(name)) {
						name = translation[tr][1];
						sig_sigdata.getSig().setName(name);
						break;
					}
				}

				// maybe...
			}
		}

		tree.repaint();
		tree.validate();
	}

	private void deselectActionPerformed(ActionEvent e) {
		setAllCheckboxes(false, null);

	}

	private void setAllCheckboxes(boolean isSelected, Set<String> signalList) {
		// for (int i = 0; i < tabber.getTabCount(); i++) {
		int tab_idx = tabber.getSelectedIndex();
		JTree tree = getTreeAt(tab_idx);

		CheckTreeManager checkTreeManager = (CheckTreeManager) tree.getClientProperty("manager");

		// mass_select = true;
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		Object root = model.getRoot();
		TreeNode node = (TreeNode) root;

		TreePath[] paths = checkTreeManager.getSelectionModel().getSelectionPaths();
//		for (TreePath path : paths) {
//			log.error("selected path=" + path);
//		}
		checkTreeManager.getSelectionModel().removeSelectionPaths(paths);
		// checkTreeManager.getSelectionModel().addSelectionPath(null);

		// mass_select = false;
		tree.repaint();

		for (int i = 0; i < tree.getRowCount(); i++) {
			if (isSelected) {
				tree.expandRow(i);
			} else {
				tree.collapseRow(i);
			}
		}
		// treeValueChanged(null);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		tabber = new JTabbedPane();
		scrollPane2 = new JScrollPane();
		v_tree = new JTree();
		scrollPane3 = new JScrollPane();
		wf_tree = new JTree();
		optionsPanel = new JPanel();
		deselect = new JButton();
		resetLabels = new JButton();

		// ======== this ========
		setBorder(Borders.DLU2);
		setLayout(new FormLayout("[150dlu,default]:grow", "fill:default:grow, $lgap, default"));

		// ======== tabber ========
		{

			// ======== scrollPane2 ========
			{
				scrollPane2.setViewportView(v_tree);
			}
			tabber.addTab("Vitals", scrollPane2);

			// ======== scrollPane3 ========
			{
				scrollPane3.setViewportView(wf_tree);
			}
			tabber.addTab("Waveforms", scrollPane3);
		}
		add(tabber, CC.xy(1, 1));

		// ======== optionsPanel ========
		{
			optionsPanel.setLayout(new FormLayout("[50dlu,default], 3*($lcgap, default)", "default"));

			// ---- deselect ----
			deselect.setText("Deselect All");
			deselect.addActionListener(e -> deselectActionPerformed(e));
			optionsPanel.add(deselect, CC.xy(1, 1));

			// ---- resetLabels ----
			resetLabels.setText("Reset Labels");
			resetLabels.addActionListener(e -> resetLabelsActionPerformed(e));
			optionsPanel.add(resetLabels, CC.xy(3, 1));
		}
		add(optionsPanel, CC.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JTabbedPane tabber;
	private JScrollPane scrollPane2;
	private JTree v_tree;
	private JScrollPane scrollPane3;
	private JTree wf_tree;
	private JPanel optionsPanel;
	private JButton deselect;
	private JButton resetLabels;
	// GEN-END:variables

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public boolean finish() {
		// TODO Auto-generated method stub
		return true;
	}

	public void selectAll() {
		String devName = null; // disambiguate which method is being called
		this.selectSignal(devName, null, null);
	}

}
