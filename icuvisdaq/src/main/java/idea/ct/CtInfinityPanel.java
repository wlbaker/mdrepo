/*
 * Created by JFormDesigner on Mon Oct 05 13:52:41 CDT 2009
 */

package idea.ct;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.ConnectionStatus;
import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryAction;
import icuInterface.discovery.DiscoveryIntf;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.DiscoveryService;
import icuInterface.discovery.InfinityDiscoveryWorker;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceConfiguration;
import idea.driver.InfinityDriver;
import idea.intf.AdapterInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;
import idea.gui.DevRecordListCellRenderer;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CtInfinityPanel extends JPanel implements CtInterface, StreamConsumer, DiscoveryListener {

	InfinityDiscoveryWorker infinity;

	public CtInfinityPanel() {
		initComponents();

		DiscoveryService ds = DiscoveryService.getInstance();

		ds.addInfinityDiscovery();

		devices.setRenderer(new DevRecordListCellRenderer());
		infinity = (InfinityDiscoveryWorker) ds.getWorker(RpConnType.INFINITY);

		test.setEnabled(false);

		devices.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				Object o = devices.getSelectedItem();
				test.setEnabled(o != null);
			}
		});

	}

	public void hideCommSetup() {
		portLabel.setVisible(false);
		devices.setVisible(false);
	}

	public void panelToModel(RpDevice dc) {

		dc.setConnectionType(RpConnType.INFINITY);

		DeviceRecord rec = (DeviceRecord) devices.getSelectedItem();
		String id = "";
		String group = "";
		if (rec != null) {
			id = rec.getUniqueID();
			IntfUtil.setParam(dc, "id", id);

			for (DiscoveryIntf intf : rec.getIntfs()) {
				if (intf.getTyp() == InfinityDriver.INTF_TYPE_DATA && intf.getProtocol() == 1) {
					group = "" + intf.getAddr();
				}
				System.out.println("intf=" + intf);
			}
		}
		IntfUtil.setParam(dc, "group", group);
		dc.setConnectionValue("infinity:/" + group + id);
	}

	private void scanActionPerformed(ActionEvent e) {
		String s_units = unitID.getText();

		if (s_units.equals("")) {
			s_units = "1";
			unitID.setText(s_units);
		}
		//FIXME- wlb - 2023 infinity.setUnits(s_units);
		infinity.stop();
		infinity.start();

		scan.setEnabled(false);
		unitID.setEnabled(false);

	}

	/*
	 * Utility functions that are no longer found in the DeviceConfiguration
	 * class...now RpDevice
	 */

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Discovery");
		panel3 = new JPanel();
		label1 = new JLabel();
		unitID = new JTextField();
		portLabel = new JLabel();
		devices = new JComboBox<>();
		panel4 = new JPanel();
		scan = new JButton();
		test = new JButton();

		// ======== this ========
		setLayout(new FormLayout("default:grow",
				"default, $lgap, 12dlu, $lgap, default, $lgap, 12dlu, 2*($lgap, default)"));
		add(separator1, CC.xy(1, 1));

		// ======== panel3 ========
		{
			panel3.setLayout(new FormLayout("right:[30dlu,default], $lcgap, 50dlu:grow", "default, $rgap, default"));

			// ---- label1 ----
			label1.setText("Unit ID:");
			panel3.add(label1, CC.xy(1, 1));
			panel3.add(unitID, CC.xy(3, 1));

			// ---- portLabel ----
			portLabel.setText("Device:");
			panel3.add(portLabel, CC.xy(1, 3));
			panel3.add(devices, CC.xy(3, 3));
		}
		add(panel3, CC.xy(1, 5));

		// ======== panel4 ========
		{
			panel4.setLayout(new FormLayout("default:grow, $lcgap, default:grow", "2*(default)"));

			// ---- scan ----
			scan.setText("Scan");
			scan.addActionListener(e -> scanActionPerformed(e));
			panel4.add(scan, CC.xy(1, 1));

			// ---- test ----
			test.setText("Test");
			panel4.add(test, CC.xy(3, 1));
		}
		add(panel4, CC.xy(1, 9));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel3;
	private JLabel label1;
	private JTextField unitID;
	private JLabel portLabel;
	private JComboBox<DeviceRecord> devices;
	private JPanel panel4;
	private JButton scan;
	private JButton test;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.CAPABILITIES) {
			// 24 June 2014: Intellivue devices send multiple CAPS messages
			DeviceConfiguration caps = ((CapabilitiesEvent) item).getCapabilities();
			log.error("FIXME: refresh( caps); // put refresh on the GUI thread");
		}
		if (sid == StreamID.CONNECTION) {
			ConnectionItem e = (ConnectionItem) item;
			ConnectionStatus status = e.getStatus();
			log.error("FIXME: probably need something here");
		}
	}

	@Override
	public void init(RpDevice dc) {

		DefaultComboBoxModel<DeviceRecord> cbmodel = (DefaultComboBoxModel) devices.getModel();
		cbmodel.removeAllElements();

		DeviceRecord[] devs = infinity.getDevices();
		log.error("ADDING DEVS: {}", devs);
		for (DeviceRecord dev : devs) {
			cbmodel.addElement(dev);
		}

		infinity.addListener(this);

	}

	@Override
	public void release() {
		infinity.removeListener(this);
	}

	@Override
	public void discover(DiscoveryAction action, DeviceRecord dev) {
		DefaultComboBoxModel cbmodel = (DefaultComboBoxModel) devices.getModel();
		cbmodel.addElement(dev);
		log.error("FOUND DEVICE: " + dev);
	}

	@Override
	public void error(DeviceRecord dev, String message, Exception x) {
		this.putClientProperty("CLIENT_MESSAGE", message);
		log.error("UNHANDLED DISCOVERY ERROR: " + message);
	}

	@Override
	public void handleConnectionEvent(RpDevice conf, AdapterInterface driver, ConnectionStatus status) {
		log.error("UNHANDLED CONNECTION EVENT: " + status);
	}

}
