/*
 * Created by JFormDesigner on Thu Oct 10 13:10:38 CDT 2013
 */

package idea.devwizard;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.fazecast.jSerialComm.SerialPort;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryAction;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.DiscoveryService;
import icuInterface.discovery.JSerialCommDiscoveryWorker;
import idea.intf.StreamProducer;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class WizDeviceDetectionPanel extends JPanel implements DiscoveryListener {
	private static final int NAME_COL = 2;
	private static final int PROBE_COL = 1;
	private static final int OBJECT_COL = 0;
	private static final int TYP_COL = 3;
	private static final int STATUS_COL = 4;

	private SetupWizardInterface wizard;
	private RpStudy default_study;
	private SerialPortRenderer serialport_renderer;
	private DiscoveryService discovery;

	public WizDeviceDetectionPanel() {
		initComponents();

		probe.setEnabled(false);
		stop.setEnabled(false);

		DefaultTableModel model = (DefaultTableModel) deviceTable.getModel();
		model.setRowCount(0);

		serialport_renderer = new SerialPortRenderer(deviceTable.getDefaultRenderer(String.class));
	}

	public void initDiscovery(DiscoveryService discovery) {

		if (discovery != null) {
			this.discovery = discovery;
		}

		showDiscoveredDevices();
		showAutoDevices();

	}

	private void showAutoDevices() {
		DefaultTableModel model = (DefaultTableModel) autoTable.getModel();
		model.setRowCount(0);

		if (discovery == null) {
			return;
		}
		 StreamProducer[] devs = discovery.getDeviceDrivers();
		if (devs != null) {
			for (StreamProducer sub : devs) {

				RpDevice conf = sub.getConfiguration();
				model.addRow(new Object[] { conf.getName(), "?sub.getConnectionType() +  sub.getPortName()",
						"?sub.getDeviceClass()" });
			}
		}

	}

	private void showDiscoveredDevices() {
		DefaultTableModel model = (DefaultTableModel) deviceTable.getModel();
		model.setRowCount(0);

		if (discovery == null) {
			return;
		}

		GuiUtil.showMessage("FIXME: -- get discovered devices");
		//		int count = discovery.getPortCount();
		//
		//		for (int i = 0; i < count; i++) {
		//			SerialPort port = discovery.getPort(i);
		//			DeviceConfiguration conf = discovery.getPortConfig(i);
		//			String typ = null;
		//			if (conf != null) {
		//				typ = conf.getConnectionName();
		//				if (typ == null || "Auto".equals(typ)) {
		//					typ = "Auto";
		//				}
		//			}
		//			model.addRow(new Object[] { port, true, port.getName(), typ, port });
		//		}

	}

	public WizDeviceDetectionPanel(RpStudy study, SetupWizardInterface wizard) {
		super();
		initComponents();

		probe.setEnabled(false);
		stop.setEnabled(false);

		this.default_study = study;
		this.wizard = wizard;

	}

	private TableCellRenderer tableGetCellRenderer(TableCellRenderer defaultRenderer, int row, int column) {

		if (column == STATUS_COL) {
			return serialport_renderer;
		}
		return defaultRenderer;
	}

	private void probeActionPerformed(ActionEvent e) {
		probe.setEnabled(false);
		stop.setEnabled(true);
		if (wizard != null) {
			wizard.enableNext(false);
		}

		// try {
		// default_study = loadDefaultStudy();
		GuiUtil.showMessage("Probe not ready...discovery and port setup goes in the caller!");
		// } catch (JAXBException e1) {
		// GuiUtil.showError("Error loading study file", e1);
		// }
		JSerialCommDiscoveryWorker discovery = new JSerialCommDiscoveryWorker();
		discovery.resetConfiguration(default_study);

		//rxtx Collection<CommPortIdentifier> portList = new LinkedList<CommPortIdentifier>();
		List<String> portList = new LinkedList<String>();

		SerialPort [] ports = SerialPort.getCommPorts();
		for( SerialPort p : ports ) { portList.add( p.getDescriptivePortName() ); }

		TableModel model = deviceTable.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			//rxtx CommPortIdentifier comm = (CommPortIdentifier) model.getValueAt(row, OBJECT_COL);
			String comm = (String) model.getValueAt(row, OBJECT_COL);
			Boolean ok = (Boolean) model.getValueAt(row, PROBE_COL);
			if (ok) {
				portList.add(comm);
			}
		}

		String [] arr = new String[ portList.size() ];
		portList.toArray( arr );
		discovery.setPorts(arr);

		discovery.addListener(this);
		discovery.start();
	}

	private void stopActionPerformed(ActionEvent e) {
		probe.setEnabled(true);
		stop.setEnabled(false);
		if (wizard != null) {
			wizard.enableNext(true);
		}

	}

	private void refreshActionPerformed(ActionEvent e) {
		initDiscovery(null); // refresh
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		label1 = compFactory.createLabel("Autodiscover Devices");
		scrollPane2 = new JScrollPane();
		autoTable = new JTable();
		separator1 = compFactory.createSeparator("Discovered Devices");
		scrollPane1 = new JScrollPane();
		deviceTable = new JTable() {
			@Override
			public TableCellRenderer getCellRenderer(int row, int column) {
				return tableGetCellRenderer(super.getCellRenderer(row, column), row, column);
			}
		};
		panel1 = new JPanel();
		probe = new JButton();
		stop = new JButton();
		refresh = new JButton();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("default:grow, $lcgap, [80dlu,default]",
				"3*(default, $lgap), fill:default:grow, $lgap, default"));
		add(label1, cc.xy(1, 1));

		// ======== scrollPane2 ========
		{

			// ---- autoTable ----
			autoTable.setPreferredScrollableViewportSize(new Dimension(550, 100));
			autoTable.setModel(new DefaultTableModel(new Object[][] {},
					new String[] { "Device", "Code", "Description" }) {
				boolean[] columnEditable = new boolean[] { false, false, false };

				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = autoTable.getColumnModel();
				cm.getColumn(0).setPreferredWidth(80);
				cm.getColumn(1).setPreferredWidth(80);
				cm.getColumn(2).setPreferredWidth(200);
			}
			scrollPane2.setViewportView(autoTable);
		}
		add(scrollPane2, cc.xy(1, 3));
		add(separator1, cc.xy(1, 5));

		// ======== scrollPane1 ========
		{

			// ---- deviceTable ----
			deviceTable.setModel(new DefaultTableModel(new Object[][] {}, new String[] { "O", "Probe", "Port", "Typ",
					"Device" }) {
				Class<?>[] columnTypes = new Class<?>[] { Object.class, Boolean.class, Object.class, Object.class,
						Object.class };
				boolean[] columnEditable = new boolean[] { false, true, false, false, false };

				@Override
				public Class<?> getColumnClass(int columnIndex) {
					return columnTypes[columnIndex];
				}

				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = deviceTable.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(50);
				cm.getColumn(2).setPreferredWidth(50);
				cm.getColumn(3).setPreferredWidth(50);
				cm.getColumn(4).setPreferredWidth(200);
			}
			deviceTable.setPreferredScrollableViewportSize(new Dimension(550, 200));
			scrollPane1.setViewportView(deviceTable);
		}
		add(scrollPane1, cc.xy(1, 7));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default:grow", "fill:default:grow, 3*($lgap, default)"));

			// ---- probe ----
			probe.setText("Start Probe");
			probe.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					probeActionPerformed(e);
				}
			});
			panel1.add(probe, cc.xy(1, 3));

			// ---- stop ----
			stop.setText("Stop Probe");
			stop.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					stopActionPerformed(e);
				}
			});
			panel1.add(stop, cc.xy(1, 5));

			// ---- refresh ----
			refresh.setText("Refresh");
			refresh.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					refreshActionPerformed(e);
				}
			});
			panel1.add(refresh, cc.xy(1, 7));
		}
		add(panel1, cc.xy(3, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel label1;
	private JScrollPane scrollPane2;
	private JTable autoTable;
	private JComponent separator1;
	private JScrollPane scrollPane1;
	private JTable deviceTable;
	private JPanel panel1;
	private JButton probe;
	private JButton stop;
	private JButton refresh;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void discover(DeviceRecord dev) {
		DefaultTableModel model = (DefaultTableModel) deviceTable.getModel();

		boolean found = false;
		for (int row = 0; row < model.getRowCount(); row++) {
			String port = (String) model.getValueAt(row, OBJECT_COL);
			String name = (String) model.getValueAt(row, NAME_COL);
			if (name.equals(dev.getIntfName(0))) {
				model.setValueAt("Ready: " + dev.getUniqueID(), row, STATUS_COL);
				found = true;
				break;
			}
		}

		if (found == false) {
			model.addRow(new Object[] { dev, true, dev.getIntfName(0), dev.getUniqueID() });
		}
	}

	public int findDeviceRow(DeviceRecord dev) {
		DefaultTableModel model = (DefaultTableModel) deviceTable.getModel();

		int found = -1;
		for (int row = 0; row < model.getRowCount(); row++) {
			// DeviceRecord row_dev = (DeviceRecord) model.getValueAt(row,
			// OBJECT_COL);
			String name = (String) model.getValueAt(row, NAME_COL);
			if (name.equals(dev.getIntfName(0))) {
				found = row;
				break;
			}
		}

		return found;
	}

	public void lose(DeviceRecord dev) {
		int row = findDeviceRow(dev);
		if (row < 0) {
			log.error("Device lost...but never found!");
			return;
		}
		DefaultTableModel model = (DefaultTableModel) deviceTable.getModel();
		model.setValueAt("Disconnect: " + dev.getUniqueID(), row, STATUS_COL);
	}

	public void update(DeviceRecord dev) {
		int row = findDeviceRow(dev);
		// if (row < 0 ) {
		// log.error("Device update...but never found!");
		// return;
		// }
		// deviceTable.valueChanged(e);

		System.out.println("update: " + row);
		// just repaint the whole table
		deviceTable.repaint();
	}

	@Override
	public void discover(DiscoveryAction action, DeviceRecord dev) {
		switch (action) {
		case DISCOVER:
			discover(dev);
			break;
		case LOSE:
			lose(dev);
			break;
		case UPDATE:
			update(dev);
			break;
		default:
			log.error("Unhandled discovery action: {}", action);
		}

	}

	@Override
	public void error(DeviceRecord dev, String message, Exception x) {
		GuiUtil.showMessage(dev.getFullName() + message); 		
	}
}
