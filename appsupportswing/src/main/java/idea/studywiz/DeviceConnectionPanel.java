/*
 * Created by JFormDesigner on Wed Apr 21 16:21:08 CDT 2010
 */

package idea.studywiz;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.fazecast.jSerialComm.SerialPort;
import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;
import com.phidgets.Manager;
import com.phidgets.Phidget;
import com.phidgets.PhidgetException;
import com.phidgets.event.AttachEvent;
import com.phidgets.event.AttachListener;
import com.phidgets.event.DetachEvent;
import com.phidgets.event.DetachListener;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryAction;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.DiscoveryService;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceFactory;
import idea.intf.AdapterInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.ComboCellEditor;
import idea.gui.ComboCellRenderer;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class DeviceConnectionPanel extends JPanel
		implements WizardPanelInterface, StreamConsumer, AttachListener, DetachListener, DiscoveryListener {

	Manager phidgetManager = null;

	class InvokedMessage implements Runnable {

		String message;

		public InvokedMessage(String message) {
			this.message = message;

		}

		@Override
		public void run() {
			System.out.println("dev conn status message: " + message);
			statusMessage.setText(message);

		}

	}

	private static final int COL_OBJECT = 0;
	private static final int COL_PORT = 2;

	private static final String AUTO_NAME = "[AUTO]";
	private static final String DISCONNECTED_NAME = "[DISCONNECTED]";
	private static final String NOPHIDGETS_NAME = "[NO PHIDGETS]";

	private List<TableCellEditor> editors;
	private List<TableCellRenderer> renderers;
	String[] commPorts; // = new Object [] {"COM1", "COM2"};
	String[] enableDisable = new String[] { "Enable", "Disable" };

	private LinkedList<String> availablePorts;
	private LinkedList<String> untriedPorts;
	private String probe_port;
	private int probe_idx;
	List<RpDevice> probe_devices;
	AdapterInterface probe_driver = null;

	private SerialDeviceConfiguration probe_conf;

	private boolean is_probing;

	private boolean needPhidgets;
	private boolean needInfinity;

	private WizardMasterInterface wizard;
	private RpHardware hardware;
	private RpStudy study;

	public DeviceConnectionPanel(WizardMasterInterface wizard) {
		initComponents();
		setName("Hardware Setup");
		this.wizard = wizard;

		initPorts();

		initTable(table);

	}

	private void checkFinishable() {
		boolean canFinish = true;

		TableModel model = table.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			String port = (String) table.getValueAt(row, COL_PORT);
			System.out.println(" row: " + row + " = " + port);
			if (AUTO_NAME.equals(port)) {
				canFinish = false;
			}
		}

		wizard.enableFinish(canFinish);
		probe.setEnabled(!canFinish);
	}

	private void initPorts() {

		availablePorts = new LinkedList<String>();
		untriedPorts = new LinkedList<String>();
		LinkedList<String> ll = new LinkedList<String>();
//		Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();
//		while (portList.hasMoreElements()) {
//			CommPortIdentifier portID = (CommPortIdentifier) portList.nextElement();
//
//			if (portID.getPortType() == CommPortIdentifier.PORT_SERIAL) {
//				ll.add(portID.getName());
//				availablePorts.add(portID.getName());
//			}
//
//		}
		for( SerialPort port : SerialPort.getCommPorts() ) {
			ll.add(port.getDescriptivePortName());
			availablePorts.add(port.getDescriptivePortName());
		}
		untriedPorts.addAll(availablePorts);
		ll.add(AUTO_NAME);
		ll.add(DISCONNECTED_NAME);

		commPorts = new String[ll.size()];

		commPorts = ll.toArray(commPorts);
	}

	private void initTable(JTable table) {
		// table.getCellEditor(row, column);

		// signalTable.setAutoCreateColumnsFromModel(false);
		// signalTable.setModel( new_model );

		// TableColumnModel tcm = table.getColumnModel();
		// tcm.getColumn(COL_SIGTYPE)
		// .setCellRenderer(new ComboCellRenderer(types));
		// tcm.getColumn(COL_CONNECTION).setCellEditor(new
		// ComboCellEditor(types));

		table.getModel().addTableModelListener(new TableModelListener() {

			@Override
			public void tableChanged(TableModelEvent e) {

				checkFinishable();
			}
		});
		// table.addPropertyChangeListener( new PropertyChan)
	}

	private void refreshStudy(RpStudy study) {
		DefaultComboBoxModel<String> model = new DefaultComboBoxModel<>();
		List<RpHardware> hw_confs = study.getHardware();
		for (RpHardware hw_conf : hw_confs) {
			model.addElement(hw_conf.getName());
		}

		configs.setModel(model);
	}

	private void setHardwareConfig(RpHardware hw_conf) throws IOException {
		editors = new LinkedList<TableCellEditor>();
		renderers = new LinkedList<TableCellRenderer>();

		List<RpDevice> devs = hw_conf.getDevices();

		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount(0);

		int commIdx = 0;
		for (RpDevice dev : devs) {

			RpConnType ct = dev.getConnectionType();

			TableCellEditor editor = null;
			TableCellRenderer renderer = null;

			String portName = dev.getConnectionValue();
			if (ct == null || ct.equals(RpConnType.NONE)) {

				editor = new ComboCellEditor(enableDisable);
				renderer = new ComboCellRenderer(enableDisable);
				model.addRow(new Object[] { dev, dev.getName(), "Enable" });

			} else if (ct.equals(RpConnType.ETHERNET)) {
				model.addRow(new Object[] { dev, dev.getName(), portName });
			} else if (ct.equals(RpConnType.DA_QMX)) {
				log.error("RpConnType.DAQ_MX not ready");
				model.addRow(new Object[] { dev, dev.getName(), portName });
			} else if (ct.equals(RpConnType.PHIDGET)) {
				log.error("RpConnType.PHIDGET not ready");
				model.addRow(new Object[] { dev, dev.getName(), portName });
			} else if (ct.equals(RpConnType.RS_232)) {
				if (commIdx >= commPorts.length) {
					commIdx = commPorts.length - 1;
				}
				if (portName == null) {
					portName = DISCONNECTED_NAME; // commPorts[commIdx++];
				}
				portName = checkPortName(portName, commPorts);
				model.addRow(new Object[] { dev, dev.getName(), portName });
				dev.setConnectionValue(portName);
				editor = new ComboCellEditor(commPorts);
				renderer = new ComboCellRenderer(commPorts);
			} else if (ct.equals(RpConnType.PHIDGET)) {
				needPhidgets = true;
				model.addRow(new Object[] { dev, dev.getName(), NOPHIDGETS_NAME });
			} else if (ct.equals(RpConnType.INFINITY)) {
				needInfinity = true;
				model.addRow(new Object[] { dev, dev.getName(), portName });

			} else {
				model.addRow(new Object[] { dev, dev.getName(), portName });
			}

			editors.add(editor);
			renderers.add(renderer);
		}

		DiscoveryService ds = DiscoveryService.getInstance();
		if (needPhidgets) {
			try {
				log.error("NEED ds.addPhidgetDiscovery()");
				initPhidgetDevs();
			} catch (PhidgetException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		if (needInfinity) {
			ds.addInfinityDiscovery();
		}
	}

	private void initPhidgetDevs() throws PhidgetException {

		phidgetManager = new Manager();
		phidgetManager.addAttachListener(this);
		phidgetManager.addDetachListener(this);
		phidgetManager.open();
	}

	private String checkPortName(String portName, String[] commPorts) throws IOException {
		String value = null;
		for (String name : commPorts) {
			if (portName.equals(name)) {
				value = portName;
				break;
			}
		}

		if (value == null) {
			value = DISCONNECTED_NAME; // commPorts[0];
		}
		return value;
	}

	private void configsActionPerformed(ActionEvent e) {
		String conf_name = (String) configs.getSelectedItem();

		try {
			List<RpHardware> hws = study.getHardware();
			for (RpHardware hw : hws) {
				if (conf_name.equals(hw.getName())) {
					setHardwareConfig(hw);
					break;
				}
			}
		} catch (Exception exc) {
			GuiUtil.showError("Configuration Error", exc);
		}

	}

	protected TableCellEditor tableGetCellEditor(TableCellEditor defaultEditor, int row, int column) {
		if (column == COL_PORT) {
			TableCellEditor editor = editors.get(row);
			if (editor != null) {
				// editor.
				return editor;
			}
		}
		return defaultEditor;
	}

	private TableCellRenderer tableGetCellRenderer(TableCellRenderer defaultRenderer, int row, int column) {

		if (renderers != null && column == COL_PORT) {
			Object pp = table.getValueAt(row, COL_PORT);
			if (pp instanceof JComboBox) {
				JComboBox combo = (JComboBox) pp;
				pp = combo.getSelectedItem();
			}

			TableCellRenderer renderer = renderers.get(row);
			if (renderer != null) {
				if (renderer instanceof ComboCellRenderer) {
					ComboCellRenderer ccr = (ComboCellRenderer) renderer;

					ccr.setSelectedItem(pp);
				}
				return renderer;
			}

		}
		return defaultRenderer;
	}

	private void probeActionPerformed(ActionEvent e) {
		Runnable r = new Runnable() {

			@Override
			public void run() {
				try {
					_probeActionPerformed();
				} catch (Exception ex) {

					GuiUtil.showError("Device Connection", ex);
					probe.setEnabled(true);
					table.setEnabled(true);
				}

			}
		};

		probe.setEnabled(false);
		table.setEnabled(false);

		Thread th = new Thread(r);
		th.start();
	}

	private void _probeActionPerformed() throws IOException {

		table.setEnabled(false);
		probe.setEnabled(false);
		initPorts(); // don't know if this is a good idea or not

		// find available (unassigned) ports
		TableModel model = table.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			String port = (String) table.getValueAt(row, COL_PORT);
			System.out.println("checking ports: " + row + " = " + port);
			if (AUTO_NAME.equals(port)) {
				// probable
			} else {
				availablePorts.remove(port);

			}
		}

		RpHardware hw_config = null;
		String hw_name = (String) configs.getSelectedItem();

		List<RpHardware> hws = study.getHardware();
		for (RpHardware hw : hws) {
			if (hw_name.equals(hw.getName())) {
				hw_config = hw;
				break;
			}
		}

		assert (hw_config != null) : "Internal error: hardware config not found.";
		probe_devices = hw_config.getDevices();
		startNextDeviceProbe();

		is_probing = true;

		Runnable r = new Runnable() {

			@Override
			public void run() {

				int probe_count = 30;
				while (is_probing && probe_count > 0) {
					try {
						probe_count--;
						Thread.sleep(1000);
						probe_driver.tick();
						System.out.println("tick: " + probe_driver);
					} catch (Exception e) {
						System.err.println("probing error: " + probe_driver);
						e.printStackTrace();
					}
				}

			}
		};

		Thread th = new Thread(r);
		th.start();

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Hardware");
		panel1 = new JPanel();
		label1 = new JLabel();
		configs = new JComboBox();
		separator1 = compFactory.createSeparator("Connections");
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		table = new JTable() {
			@Override
			public TableCellEditor getCellEditor(int row, int column) {
				return tableGetCellEditor(super.getCellEditor(row, column), row, column);
			}

			@Override
			public TableCellRenderer getCellRenderer(int row, int column) {
				return tableGetCellRenderer(super.getCellRenderer(row, column), row, column);
			}
		};
		panel3 = new JPanel();
		statusMessage = new JLabel();
		probe = new JButton();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "3*(default, $ugap), fill:default:grow, $lgap, default"));
		add(separator2, CC.xy(1, 1));

		// ======== panel1 ========
		{
			panel1.setLayout(
					new FormLayout("20dlu, $lcgap, default, $lcgap, [80dlu,default], 2*($lcgap, default)", "default"));

			// ---- label1 ----
			label1.setText("Configuration:");
			panel1.add(label1, CC.xy(3, 1));

			// ---- configs ----
			configs.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					configsActionPerformed(e);
				}
			});
			panel1.add(configs, CC.xy(5, 1));
		}
		add(panel1, CC.xy(1, 3));
		add(separator1, CC.xy(1, 5));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("20dlu, $ugap, default:grow", "fill:default:grow"));

			// ======== scrollPane1 ========
			{
				scrollPane1.setPreferredSize(new Dimension(154, 223));

				// ---- table ----
				table.setModel(new DefaultTableModel(new Object[][] { { null, null, null, null }, },
						new String[] { "O", "Device", "Port", "Status" }) {
					boolean[] columnEditable = new boolean[] { false, false, true, false };

					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = table.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(200);
					cm.getColumn(2).setPreferredWidth(100);
					cm.getColumn(3).setPreferredWidth(60);
				}
				scrollPane1.setViewportView(table);
			}
			panel2.add(scrollPane1, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 7));

		// ======== panel3 ========
		{
			panel3.setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, [50dlu,default]", "default"));

			// ---- statusMessage ----
			statusMessage.setText(" ");
			panel3.add(statusMessage, CC.xy(1, 1));

			// ---- probe ----
			probe.setText("Probe");
			probe.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					probeActionPerformed(e);
				}
			});
			panel3.add(probe, CC.xy(5, 1));
		}
		add(panel3, CC.xy(1, 9));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator2;
	private JPanel panel1;
	private JLabel label1;
	private JComboBox configs;
	private JComponent separator1;
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable table;
	private JPanel panel3;
	private JLabel statusMessage;
	private JButton probe;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	private boolean signalevent_recursing;

	@Override
	public boolean finish() {
		closeResources();
		savePanel();
		return true;
	}

	private void closeResources() {
		if (phidgetManager != null) {
			try {
				phidgetManager.close();
			} catch (PhidgetException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		}

	}

	public void savePanel() {
		RpHardware hw_config = null;
		String hw_name = (String) configs.getSelectedItem();

		List<RpHardware> hws = study.getHardware();
		for (RpHardware hw : hws) {
			if (hw_name.equals(hw.getName())) {
				hw_config = hw;
				break;
			}
		}

		// stop any pending cell editing before retrieving COL_PORT
		if (table.getCellEditor() != null) {
			table.getCellEditor().stopCellEditing();
		}

		if (hw_config == null) {
			log.error("no hardware configuration: name={}", hw_name);
			return;
		}
		
		List<RpDevice> devices = hw_config.getDevices();
		for (int idx = 0; idx < devices.size(); idx++) {
			RpDevice dev = devices.get(idx);
			String connValue = (String) table.getValueAt(idx, COL_PORT);

			dev.setConnectionValue(connValue);
		}

	}

	@Override
	public boolean next() {
		
		closeResources();
		savePanel();
		
		return true;
	}

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (signalevent_recursing) {
			return;
		}

		if (sid == StreamID.CONNECTION) {
			ConnectionItem e = (ConnectionItem) item;
			ConnectionStatus status = e.getStatus();
			try {
				handleConnectionEvent(status);
			} catch (Exception ex) {
				ex.printStackTrace();
				System.out.println("don't know how to handle exceptions here");
			}
		}
	}

	private void handleConnectionEvent(ConnectionStatus status) throws IOException {
		System.out.println(probe_port + " " + status.toString());
		String probe_name = probe_driver.getConfiguration().getName();

		if (status == NOT_CONNECTED || status == CONNECTED) {
			try {
				signalevent_recursing = true;
				probe_driver.disconnect();
				signalevent_recursing = false;
			} catch (IOException e1) {
				// can probably ignore this
				e1.printStackTrace();
			}
		}

		if (status == ConnectionStatus.NOT_CONNECTED) {
			if (untriedPorts != null && untriedPorts.size() > 0) {
				probe_port = untriedPorts.removeFirst();
				statusMessage.setText("Checking " + probe_name + " on " + probe_port);
				probe_conf.setPort(probe_port);
				try {
					probe_driver.connect();
				} catch (IOException e1) {
					// WARNING: cannot ignore this!!!
					e1.printStackTrace();
				}
			} else {
				statusMessage.setText("<html>" + probe_name + " not found.  Check power/cables and try again.");
				is_probing = false;
				probe.setEnabled(true);
				table.setEnabled(true);
			}
		} else if (status == CONNECTED) {
			statusMessage.setText("Found " + probe_name + " on " + probe_port);
			availablePorts.remove(probe_port);
			table.setValueAt(probe_port, probe_idx, COL_PORT);

			startNextDeviceProbe();
		} else if (status == ConnectionStatus.NEGOTIATING) {
			statusMessage.setText("Looking for " + probe_name + " on " + probe_port);
		} else {
			statusMessage.setText(probe_name + " on " + probe_port + ": " + status.toString());
		}
	}

	private void startNextDeviceProbe() throws IOException {

		boolean more_probing = false;
		untriedPorts = new LinkedList<String>();
		for (probe_idx = 0; probe_idx < probe_devices.size(); probe_idx++) {
			RpDevice dev = probe_devices.get(probe_idx);

			String port = (String) table.getValueAt(probe_idx, COL_PORT);
			if (AUTO_NAME.equals(port)) {
				System.out.println("need probe for dev: " + dev.getName());
				// test each device oneach available port
				startProbeOnAvailablePorts(dev);
				more_probing = true;
				break;
			} else {
				System.out.println("skip device: " + port + " dev: " + dev.getName());

				availablePorts.remove(port);
			}
		}
		is_probing = more_probing;

		if (!is_probing) {
			statusMessage.setText("Probing complete.");
			checkFinishable();
			table.setEnabled(true);
		}

	}

	private void startProbeOnAvailablePorts(RpDevice dev) throws IOException {
		if (availablePorts.size() < 1) {
			String message = "Cannot probe: no ports available.";
			throw new IOException(message);
		}
		untriedPorts.addAll(availablePorts);

		probe_port = untriedPorts.remove();
		dev.setConnectionValue(probe_port);

		probe_conf = (SerialDeviceConfiguration) RpUtil.createDeviceConfiguration(dev, true);
		probe_driver = DeviceFactory.createDriver(probe_conf);

		InvokedMessage message = new InvokedMessage("Probing " + probe_port + " for " + dev.getName());
		SwingUtilities.invokeLater(message);

		probe_driver.addStreamListener(StreamID.CONNECTION, this);

		try {
			probe_driver.connect();
		} catch (final Exception e) {
			Runnable r = new Runnable() {

				@Override
				public void run() {
					GuiUtil.showError("Probing port: " + probe_port, e);
				}
			};

			if (SwingUtilities.isEventDispatchThread()) {
				r.run();
			} else {
				try {
					SwingUtilities.invokeAndWait(r);
				} catch (Exception e2) {
					System.err.println("Could not invoke and wait: " + e2);
				}
			}
			return;
		}

	}

	/*
	 * *************************************************************************
	 * *
	 * 
	 * methods for handling phidgets
	 */

	@Override
	public void attached(AttachEvent arg0) {
		System.out.println("got attach for phidget: " + arg0);

		updatePhidgetsList();
	}

	@Override
	public void detached(DetachEvent arg0) {
		System.out.println("got detach for phidget: " + arg0);
		updatePhidgetsList();
	}

	private void updatePhidgetsList() {
		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				try {
					_updatePhidgetsList();
				} catch (PhidgetException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		});
	}

	private void _updatePhidgetsList() throws PhidgetException {
		DefaultTableModel model = (DefaultTableModel) table.getModel();

		Vector<Phidget> phidgets;
		phidgets = phidgetManager.getPhidgets();

		String[] phidgetDevs = null;

		if (phidgets != null && phidgets.size() > 0) {
			phidgetDevs = new String[phidgets.size()];
			int idx = 0;
			for (Phidget phid : phidgets) {
				phidgetDevs[idx++] = phid.getSerialNumber() + "";
			}
		} else {
			System.err.println("WARNING: " + NOPHIDGETS_NAME);
		}

		for (int row = 0; row < model.getRowCount(); row++) {
			RpDevice dev = (RpDevice) model.getValueAt(row, COL_OBJECT);
			RpConnType ct = dev.getConnectionType();

			if (ct != RpConnType.PHIDGET) {
				continue;
			}
			if (phidgetDevs != null && phidgetDevs.length > 0) {
				ComboCellEditor editor = new ComboCellEditor(phidgetDevs);
				ComboCellRenderer renderer = new ComboCellRenderer(phidgetDevs);
				// model.setValueAt(NOPHIDGETS_NAME, row, COL_PORT );

				renderer.setForeground(UIManager.getColor("ComboBox.foreground"));
				renderer.setHilight(UIManager.getColor("ComboBox.background"));
				renderer.setBackground(UIManager.getColor("ComboBox.background"));

				editors.set(row, editor);
				renderers.set(row, renderer);
				model.setValueAt(phidgetDevs[0], row, COL_PORT);
				// model.fireTableDataChanged();
			} else {
				model.setValueAt(NOPHIDGETS_NAME, row, COL_PORT);
			}
		}
	}

	public RpHardware getHardware() {
		return hardware;
	}

	public void setHardware(RpHardware hardware) {
		this.hardware = hardware;
	}

	public void setStudy(RpStudy study) {
		this.study = study;
		refreshStudy(study);

		if (hardware == null) {
			List<RpHardware> hws = study.getHardware();
			if (hws.size() > 0) {
				hardware = hws.get(0);
			}
		}

		try {
			if (hardware != null) {
				configs.setSelectedItem(hardware.getName());
				setHardwareConfig(hardware);
			}
		} catch (Exception exc) {
			GuiUtil.showError("Configuration Error", exc);
		}

	}

	@Override
	public void discover(DiscoveryAction action, DeviceRecord dev) {
		log.error("UPDATE DISCOVERY COMPONENTS");
	}

	@Override
	public void error(DeviceRecord dev, String message, Exception x) {
		// TODO Auto-generated method stub

	}
}
