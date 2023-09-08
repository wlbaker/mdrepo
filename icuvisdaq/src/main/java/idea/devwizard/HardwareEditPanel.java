/*
 * Created by JFormDesigner on Wed Oct 07 12:27:36 CDT 2009
 */

package idea.devwizard;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeCellRenderer;
import javax.swing.tree.TreeModel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

class MetricWrapper {

	private RpMetric m;
	private StreamID sid;

	public MetricWrapper(StreamID sid, RpMetric m) {
		this.sid = sid;
		this.m = m;
	}

	public RpMetric getMetric() {
		return m;
	}

	public StreamID getSID() {
		return sid;
	}

	@Override
	public String toString() {
		String name = m.getName();
		if (name == null) {
			name = m.getCode();
		}
		if (name == null) {
			name = m.getLocation();
		}
		return name;
	}
}

class DevWrapper {

	private RpDevice dev;

	public DevWrapper(RpDevice dev) {
		this.dev = dev;
	}

	@Override
	public String toString() {
		return dev.getName();
	}

	public RpDevice getDev() {
		return dev;
	}

}

@Slf4j
class DeviceTreeRenderer implements TreeCellRenderer {

	TreeCellRenderer r;

	private static ImageIcon wave_icon;
	private static ImageIcon measurement_icon;

	static {
		try {
			InputStream stream = DeviceTreeRenderer.class.getResourceAsStream("/idea/image/wave.png");
			wave_icon = new ImageIcon(ImageIO.read(stream));
			stream.close();

			stream = DeviceTreeRenderer.class.getResourceAsStream("/idea/image/measurement.png");
			measurement_icon = new ImageIcon(ImageIO.read(stream));
			stream.close();
		} catch (IOException e) {
			log.error("Could not load resource: {}", e.getMessage());
		}
	}

	DeviceTreeRenderer(TreeCellRenderer r) {
		this.r = r;
	}

	@Override
	public Component getTreeCellRendererComponent(JTree tree, Object value, boolean selected, boolean expanded,
			boolean leaf, int row, boolean hasFocus) {
		JLabel c = (JLabel) r.getTreeCellRendererComponent(tree, value, selected, expanded, leaf, row, hasFocus);
		DefaultMutableTreeNode nodo = (DefaultMutableTreeNode) value;
		// if (tree.getModel().getRoot().equals(nodo)) {
		// setIcon(root);
		// } else
		Object uu = nodo.getUserObject();

		if (uu instanceof MetricWrapper) {
			MetricWrapper m = (MetricWrapper) uu;
			if (m.getSID() == StreamID.WAVEFORM) {
				c.setIcon(wave_icon);
			} else if (m.getSID() == StreamID.MEASUREMENT) {
				c.setIcon(measurement_icon);
			}
			c.setText(m.toString());
		} else {
			// c.setIcon(leaf);
		}
		return c;
	}

}

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class HardwareEditPanel extends JPanel implements WizardPanelInterface, TreeSelectionListener {
	private SetupWizardInterface wizard;
	RpHardware hw;

	public HardwareEditPanel(SetupWizardInterface wizard, RpStudy study) {
		initComponents();
		this.wizard = wizard;
		setName("Hardware Setup");

		TreeCellRenderer r = tree.getCellRenderer();
		tree.setCellRenderer(new DeviceTreeRenderer(r));
		tree.addTreeSelectionListener(this);

		List<RpHardware> hw_list = study.getHardware();
		if (hw_list.isEmpty()) {
			hw = new RpHardware();
			hw.setName("Default Configuration");
			hw_list.add(hw);
		} else {
			hw = hw_list.get(0);
		}

		refresh();
	}

	private void expandAll(JTree tree) {
		int row = 0;
		while (row < tree.getRowCount()) {
			tree.expandRow(row);
			row++;
		}
	}

	public String getProfileName() {
		return profileNameField.getText();
	}

	private void addDeviceActionPerformed(ActionEvent e) {

		saveProfileName();

		WizDevicePanel panel = new WizDevicePanel(wizard, hw);
		wizard.pushPage(panel);
	}

	private void editSignalsActionPerformed(ActionEvent e) {
		saveProfileName();

		String clazzName = getDeviceWizardClass();
		Class<?> wiz_clazz = SetupData.getWizardForDevice(clazzName);
		if( wiz_clazz == null ) {
			log.error("Could not find wizard class: {}", clazzName);
			GuiUtil.showMessage("Could not find class: " + clazzName );
			return;
		}

		RpDevice dev_conf = getSelectedDevice();

		// LOOK FOR ANOTHER COPY OF THIS AS PUSH_SELECTION
		try {
			Constructor<?> mid = wiz_clazz.getConstructor(WizardMasterInterface.class, RpDevice.class);
			Object[] args = new Object[] { wizard, dev_conf };
			// args[0] = null;
			JPanel panel = (JPanel) mid.newInstance(args);
			panel.setName("Signal Selection");

			wizard.pushPage(panel);
		} catch (Exception ex) {
			throw new RuntimeException("Could not construct: " + wiz_clazz, ex);
		}
	}

	private String getDeviceWizardClass() {
		String clazzName = null;
		DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();

		Object nodeInfo = node.getUserObject();
		if (nodeInfo instanceof DevWrapper) {
			DevWrapper wrapper = (DevWrapper) nodeInfo;
			nodeInfo = wrapper.getDev();
		}
		if (nodeInfo instanceof RpDevice) {
			RpDevice dev = (RpDevice) nodeInfo;
			clazzName = dev.getDeviceClass();
		}

		return clazzName;
	}

	private void removeDeviceActionPerformed(ActionEvent e) {
		RpDevice dev = getSelectedDevice();

		assert (dev != null) : "should not get this far with a null device";

		if (dev != null) {
			int ok = GuiUtil.showConfirmDialog("<html>Remove device....<br><br>Are you sure?", "Confirm Remove",
					JOptionPane.YES_NO_OPTION);
			if (ok == JOptionPane.YES_OPTION) {
				saveProfileName();
				RpUtil.removeDevice(hw.getDevices(), dev);

				refresh();
			}
		}
	}

	private RpDevice getSelectedDevice() {
		RpDevice dev = null;
		DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();

		Object nodeInfo = node.getUserObject();
		if (nodeInfo instanceof DevWrapper) {
			DevWrapper wrapper = (DevWrapper) nodeInfo;
			nodeInfo = wrapper.getDev();
		}
		if (nodeInfo instanceof RpDevice) {
			dev = (RpDevice) nodeInfo;
		}
		return dev;
	}

	private void detectDevicesActionPerformed(ActionEvent e) {

		RpStudy default_study = null;
		WizDeviceDetectionPanel panel = new WizDeviceDetectionPanel(default_study, wizard);
		panel.setName("Device Detection");
		wizard.pushPage(panel);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label2 = new JLabel();
		profileNameField = new JTextField();
		scrollPane1 = new JScrollPane();
		tree = new JTree();
		panel2 = new JPanel();
		addDevice = new JButton();
		detectDevices = new JButton();
		removeDevice = new JButton();
		editSignals = new JButton();

		// ======== this ========
		setLayout(new FormLayout("[150dlu,default]:grow, $lcgap, default", "default, $lgap, fill:default:grow"));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default, $lcgap, [150dlu,default], 2*($lcgap, default)",
					"2*(default, $lgap), default"));

			// ---- label2 ----
			label2.setText("Configuration Name:");
			panel1.add(label2, CC.xy(1, 3));
			panel1.add(profileNameField, CC.xy(3, 3));
		}
		add(panel1, CC.xy(1, 1));

		// ======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(76, 124));
			scrollPane1.setViewportView(tree);
		}
		add(scrollPane1, CC.xy(1, 3));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default:grow", "default:grow, 4*($lgap, default)"));

			// ---- addDevice ----
			addDevice.setText("Add Device");
			addDevice.addActionListener(e -> addDeviceActionPerformed(e));
			panel2.add(addDevice, CC.xy(1, 3));

			// ---- detectDevices ----
			detectDevices.setText("Detect Devices");
			detectDevices.addActionListener(e -> detectDevicesActionPerformed(e));
			panel2.add(detectDevices, CC.xy(1, 5));

			// ---- removeDevice ----
			removeDevice.setText("Remove Device");
			removeDevice.addActionListener(e -> removeDeviceActionPerformed(e));
			panel2.add(removeDevice, CC.xy(1, 7));

			// ---- editSignals ----
			editSignals.setText("Edit Signals");
			editSignals.addActionListener(e -> editSignalsActionPerformed(e));
			panel2.add(editSignals, CC.xy(1, 9));
		}
		add(panel2, CC.xy(3, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label2;
	private JTextField profileNameField;
	private JScrollPane scrollPane1;
	private JTree tree;
	private JPanel panel2;
	private JButton addDevice;
	private JButton detectDevices;
	private JButton removeDevice;
	private JButton editSignals;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void valueChanged(TreeSelectionEvent e) {

		boolean isDev = false;

		DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
		if (node != null) {
			Object nodeInfo = node.getUserObject();
			if (nodeInfo instanceof DevWrapper) {
				// RpDevice dev = (RpDevice)nodeInfo;
				isDev = true;
			}
		}

		editSignals.setEnabled(isDev);
		removeDevice.setEnabled(isDev);
	}

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {

		saveProfileName();

		return true;

	}

	private void saveProfileName() {
		String profileName = profileNameField.getText().trim();
		if (profileName.length() > 0) {
			hw.setName(profileName);
		}
	}

	@Override
	public void refresh() {

		String profileName = hw.getName();
		if (profileName != null) {
			profileName = profileName.trim();
		}
		if (profileName == null || profileName.length() == 0) {
			profileName = "Untitled";
			hw.setName(profileName);
		}
		profileNameField.setText(profileName);

		DefaultMutableTreeNode root = new DefaultMutableTreeNode("Add device...");

		List<RpDevice> devs = hw.getDevices();

		int n_devs = 0;
		for (RpDevice dev : devs) {
			DefaultMutableTreeNode tnDev0 = new DefaultMutableTreeNode(new DevWrapper(dev));
			root.add(tnDev0);
			n_devs++;

			StreamID[] sids = new StreamID[] { StreamID.MEASUREMENT, StreamID.WAVEFORM };
			for (StreamID sid : sids) {
				List<? extends RpMetric> metrics = RpUtil.getMetrics(dev, sid);
				if (metrics != null) {
					for (RpMetric metric : metrics) {
						tnDev0.add(new DefaultMutableTreeNode(new MetricWrapper(sid, metric)));
					}
				}
			}

		}

		tree.setRootVisible(n_devs == 0);

		TreeModel tm = new DefaultTreeModel(root);
		tree.setModel(tm);

		expandAll(tree);
		valueChanged(null);
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

}
