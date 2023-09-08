/*
 * Created by JFormDesigner on Wed Apr 21 16:21:08 CDT 2010
 */

package experiment;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.intf.AdapterInterface;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.GuiUtil;
import idea.gui.ComboCellEditor;
import idea.gui.ComboCellRenderer;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.importwiz.ImportWizard;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class DeviceConnectionPanel extends JPanel implements WizardPanelInterface {
	private static final int COL_PORT = 2;

	private List<TableCellEditor> editors;
	private List<TableCellRenderer> renderers;
	String[] commPorts; // = new Object [] {"COM1", "COM2"};

	private LinkedList<String> availablePorts;

	public DeviceConnectionPanel() {
		initComponents();
		setName("Hardware Setup");

		ImportWizard wizard = ImportWizard.getInstance();

		initPorts();

		wizard.enableNext(false);

		initTable(table);

		checkFinishable(wizard);
	}

	private void checkFinishable(ImportWizard wizard) {
		boolean canFinish = true;

		TableModel model = table.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			String port = (String) table.getValueAt(row, COL_PORT);
			System.out.println(" row: " + row + " = " + port);
			if ("Auto".equals(port)) {
				canFinish = false;
			}
		}

		wizard.enableFinish(canFinish);
		probe.setEnabled(!canFinish);
	}

	private void initPorts() {
//		Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();
//
//		availablePorts = new LinkedList<String>();
//		LinkedList<String> ll = new LinkedList<String>();
//		while (portList.hasMoreElements()) {
//			CommPortIdentifier portID = (CommPortIdentifier) portList.nextElement();
//
//			if (portID.getPortType() == CommPortIdentifier.PORT_SERIAL) {
//				ll.add(portID.getName());
//				availablePorts.add(portID.getName());
//			}
//
//		}
//		ll.add("Auto");
//
//		commPorts = new String[ll.size()];
//
//		commPorts = ll.toArray(commPorts);
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
	}

	private void setStudy(RpStudy study) {
		DefaultComboBoxModel model = new DefaultComboBoxModel();
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
			if (ct == null) {
				model.addRow(new Object[] { dev, dev.getName(), "<unspecified>" });
			} else if (ct.equals(RpConnType.ETHERNET)) {
				if (portName == null) {
					portName = "192.168.1.140";
				}
				model.addRow(new Object[] { dev, dev.getName(), portName });
			} else if (ct.equals(RpConnType.DA_QMX)) {
				model.addRow(new Object[] { dev, dev.getName(), "DAQMX" });
			} else if (ct.equals(RpConnType.RS_232)) {
				if (commIdx >= commPorts.length) {
					commIdx = commPorts.length - 1;
				}
				if (portName == null) {
					portName = commPorts[commIdx++];
				}
				portName = checkPortName(portName, commPorts);
				model.addRow(new Object[] { dev, dev.getName(), portName });
				dev.setConnectionValue(portName);
				editor = new ComboCellEditor(commPorts);
				renderer = new ComboCellRenderer(commPorts);
			} else {
				model.addRow(new Object[] { dev, dev.getName(), "<unknown>" });
			}

			editors.add(editor);
			renderers.add(renderer);
		}
	}

	private String checkPortName(String portName, String[] commPorts) throws IOException {
		String value = null;
		for (String name : commPorts) {
			if (portName.equals(name)) {
				value = portName;
				break;
			}
		}

		if (commPorts == null || commPorts.length == 0) {
			throw new IOException("No communication ports available.");
		}

		if (value == null) {
			value = commPorts[0];
		}
		return value;
	}

	private void configsActionPerformed(ActionEvent e) {
		String conf_name = (String) configs.getSelectedItem();

		ImportWizard wizard = ImportWizard.getInstance();
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
				} finally {
					probe.setEnabled(true);
					table.setEnabled(true);
				}

			}
		};

		Thread th = new Thread(r);
		th.start();
		probe.setEnabled(false);
		table.setEnabled(false);
	}

	private void _probeActionPerformed() {

		initPorts(); // don't know if this is a good idea or not

		// find available (unassigned) ports
		TableModel model = table.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			String port = (String) table.getValueAt(row, COL_PORT);
			System.out.println("checking ports: " + row + " = " + port);
			if ("Auto".equals(port)) {
				// probable
			} else {
				availablePorts.remove(port);
			}
		}

		RpHardware hw_config = null;
		String hw_name = (String) configs.getSelectedItem();
		ImportWizard wizard = ImportWizard.getInstance();

		assert (hw_config != null) : "Internal error: hardware config not found.";

		List<RpDevice> devices = hw_config.getDevices();
		for (int row = 0; row < devices.size(); row++) {
			RpDevice dev = devices.get(row);

			String port = (String) table.getValueAt(row, COL_PORT);
			System.out.println("testing device: " + row + " = " + port);
			if ("Auto".equals(port)) {
				// test each device on each available port
				String comm = testDeviceOnAvailablePorts(dev);
				if (comm != null) {
					availablePorts.remove(comm);
					table.setValueAt(comm, row, COL_PORT);
				}
			} else {
				availablePorts.remove(port);
			}
		}
	}

	private String testDeviceOnAvailablePorts(RpDevice dev) {
		class InvokedMessage implements Runnable {

			String message;

			public InvokedMessage(String message) {
				this.message = message;

			}

			@Override
			public void run() {
				probeText.setText(message);

			}

		}
		String rv = null;
		for (String port : availablePorts) {

			dev.setConnectionValue(port);

			AdapterInterface driver = null;

			DeviceConfiguration conf = RpUtil.createDeviceConfiguration(dev, true);
			driver = DeviceFactory.createDriver(conf);

			InvokedMessage message = new InvokedMessage("Probing " + port + " for " + dev.getName());
			SwingUtilities.invokeLater(message);

			try {
				driver.connect();
				int timeout = 6;
				while (timeout >= 0 && driver.getStatus() == NEGOTIATING) {
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					timeout--;
				}
				ConnectionStatus state = driver.getStatus();
				driver.disconnect();

				if (state == CONNECTED) {
					// we found the port
					rv = port;
					break;
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		}

		return rv;
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
		probeText = new JLabel();
		probe = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "3*(default, $ugap), fill:default:grow, $lgap, default"));
		add(separator2, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("20dlu, $lcgap, default, $lcgap, [80dlu,default], 2*($lcgap, default)",
					"default"));

			//---- label1 ----
			label1.setText("Configuration:");
			panel1.add(label1, cc.xy(3, 1));

			//---- configs ----
			configs.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					configsActionPerformed(e);
				}
			});
			panel1.add(configs, cc.xy(5, 1));
		}
		add(panel1, cc.xy(1, 3));
		add(separator1, cc.xy(1, 5));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout("20dlu, $ugap, default:grow", "fill:default:grow"));

			//======== scrollPane1 ========
			{
				scrollPane1.setPreferredSize(new Dimension(154, 223));

				//---- table ----
				table.setModel(new DefaultTableModel(new Object[][] { { null, null, null }, }, new String[] { "O",
						"Device", "Port" }) {
					boolean[] columnEditable = new boolean[] { false, false, true };

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
				}
				scrollPane1.setViewportView(table);
			}
			panel2.add(scrollPane1, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 7));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout("default:grow, $lcgap, [50dlu,default]", "default"));

			//---- probeText ----
			probeText.setText(" ");
			panel3.add(probeText, cc.xy(1, 1));

			//---- probe ----
			probe.setText("Probe");
			probe.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					probeActionPerformed(e);
				}
			});
			panel3.add(probe, cc.xy(3, 1));
		}
		add(panel3, cc.xy(1, 9));
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
	private JLabel probeText;
	private JButton probe;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public boolean next() {
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

}
