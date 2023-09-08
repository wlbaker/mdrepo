/*
 * Created by JFormDesigner on Wed Apr 21 16:21:08 CDT 2010
 */

package idea.studywiz;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumnModel;

import com.fazecast.jSerialComm.SerialPort;
import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.gui.ColorRenderer;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class SerialConfigurationPanel extends JPanel implements WizardPanelInterface {

	private static final int COL_OBJECT = 0;
	private static final int COL_EDITABLE = 1;
	private static final int COL_ENABLED = 2;
	private static final int COL_PORT = 3;
	private static final int COL_DEV = 4;


	private RpHardware hardware;
	private ColorRenderer colorRenderer;

	public SerialConfigurationPanel(WizardMasterInterface wizard) {
		initComponents();
		setName("Hardware Setup");
		//this.wizard = wizard;

		// RpHardware hardware = wizard.getHardware();
		// RpStudy study = wizard.getStudy();

		initPorts();

		initTable(table);

	}
	
	public void setStudy( RpStudy study, RpHardware hw) {
		//this.study = study;
		this.hardware = hw;
		
		refreshHardware( hardware );
	}

	private void initPorts() {
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount(0);
		
		SerialPort[] ports = SerialPort.getCommPorts();
		//rxtx Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();


//rxtx		while (portList.hasMoreElements()) {
//rxtx			CommPortIdentifier portID = (CommPortIdentifier) portList.nextElement();
//rxtx			if (portID.getPortType() == CommPortIdentifier.PORT_SERIAL) {
//rxtx				model.addRow( new Object[] { portID, true, true, portID.getName(), ""} );
//rxtx			}
//rxtx		}
		for( SerialPort port : ports ) {
			model.addRow( new Object[] { port.getSystemPortName(), true, true, port.getDescriptivePortName() } );
		}

	}

	private void initTable(JTable table) {
		colorRenderer = new ColorRenderer(table, table.getDefaultRenderer(Object.class));
		colorRenderer.addRenderer(Boolean.class, table.getDefaultRenderer(Boolean.class));
		// signalTable.setDefaultRenderer(Object.class, colorRenderer);
		table.setDefaultRenderer(Boolean.class, colorRenderer);


		table.getModel().addTableModelListener(new TableModelListener() {

			@Override
			public void tableChanged(TableModelEvent e) {

				// checkFinishable();
			}
		});
		// table.addPropertyChangeListener( new PropertyChan)
	}

	private void refreshHardware(RpHardware hw_conf) {

		List<RpDevice> devs = hw_conf.getDevices();

		DefaultTableModel model = (DefaultTableModel) table.getModel();

		// clear all the dev rows regarding port and enabled fields
		colorRenderer.clear();
		for( int row = 0; row < model.getRowCount(); row++ ) {
			model.setValueAt("", row, COL_DEV);
			model.setValueAt(false, row, COL_ENABLED);
			model.setValueAt(true, row, COL_EDITABLE);
			
		}
		
		// re-populate
		for (RpDevice dev : devs) {

			RpConnType ct = dev.getConnectionType();

			if (RpConnType.RS_232.equals(ct)) {
				String portName = dev.getConnectionValue();
				int row = findPort(model, portName);
				if( row >= 0 ) {
					model.setValueAt(true, row, COL_ENABLED);
					model.setValueAt(false, row, COL_EDITABLE);
					model.setValueAt( dev.getName(), row, COL_DEV );
					
					colorRenderer.setRowColor(row, Color.RED);
				}
			} else {
				// ignore
			}

		}

	}

	private int findPort(DefaultTableModel model, String portName)  {
		int idx = -1;
		for (int row = 0; row < model.getRowCount(); row++) {
			if (portName.equals(model.getValueAt(row, COL_PORT))) {
				idx = row;
				break;
			}
		}

		return idx;
	}

	protected TableCellRenderer tableGetCellRenderer(TableCellRenderer cellRenderer, int row, int column) {
		return cellRenderer;
	}

	protected TableCellEditor tableGetCellEditor(TableCellEditor cellEditor, int row, int column) {
		return cellEditor;
	}

	private void enableAllActionPerformed(ActionEvent e) {
		enableAll(true);
	}

	private void disableAllActionPerformed(ActionEvent e) {
		enableAll(false);
	}
	
	private void enableAll( boolean t ) {
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			model.setValueAt((Boolean)t, row, COL_ENABLED );
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Autoconfig Connections");
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		table = new JTable() {
			@Override
		    public TableCellEditor getCellEditor(int row, int column) {
				return tableGetCellEditor(super.getCellEditor(row, column), row, column );
		    }
			@Override
		    public TableCellRenderer getCellRenderer(int row, int column) {
				return tableGetCellRenderer(super.getCellRenderer(row, column), row, column );
		    }
		    @Override
			public boolean isCellEditable(int row, int column) {
				boolean editable = super.isCellEditable(row, column);
				if( editable ) editable = (boolean) this.getValueAt(row, COL_EDITABLE);
				return editable;
			}

		};
		panel3 = new JPanel();
		enableAll = new JButton();
		disableAll = new JButton();
		statusMessage = new JLabel();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $ugap, fill:default:grow, $lgap, default"));
		add(separator1, CC.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"10dlu, $ugap, default:grow",
				"fill:default:grow"));

			//======== scrollPane1 ========
			{
				scrollPane1.setPreferredSize(new Dimension(154, 223));

				//---- table ----
				table.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null, true, null, null},
					},
					new String[] {
						"O", null, "Enable", "Port", "Device"
					}
				) {
					Class<?>[] columnTypes = new Class<?>[] {
						Object.class, Boolean.class, Boolean.class, Object.class, Object.class
					};
					boolean[] columnEditable = new boolean[] {
						false, true, true, false, false
					};
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
					TableColumnModel cm = table.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setMinWidth(1);
					cm.getColumn(1).setMaxWidth(1);
					cm.getColumn(1).setPreferredWidth(1);
					cm.getColumn(2).setPreferredWidth(60);
					cm.getColumn(3).setPreferredWidth(100);
					cm.getColumn(4).setPreferredWidth(200);
				}
				scrollPane1.setViewportView(table);
			}
			panel2.add(scrollPane1, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 3));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"2*(default, $lcgap), default:grow, $lcgap, default, $lcgap, [50dlu,default]",
				"default"));

			//---- enableAll ----
			enableAll.setText("Enable All");
			enableAll.addActionListener(e -> enableAllActionPerformed(e));
			panel3.add(enableAll, CC.xy(1, 1));

			//---- disableAll ----
			disableAll.setText("Disable All");
			disableAll.addActionListener(e -> disableAllActionPerformed(e));
			panel3.add(disableAll, CC.xy(3, 1));

			//---- statusMessage ----
			statusMessage.setText(" ");
			panel3.add(statusMessage, CC.xy(5, 1));
		}
		add(panel3, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable table;
	private JPanel panel3;
	private JButton enableAll;
	private JButton disableAll;
	private JLabel statusMessage;
	// JFormDesigner - End of variables declaration //GEN-END:variables


	@Override
	public boolean finish() {


		// stop any pending cell editing before retrieving COL_PORT
		if (table.getCellEditor() != null) {
			table.getCellEditor().stopCellEditing();
		}

//		List<RpDevice> devices = hardware.getDevices();
//		for (int idx = 0; idx < devices.size(); idx++) {
//			RpDevice dev = devices.get(idx);
//			String connValue = (String) table.getValueAt(idx, COL_PORT);
//
//			dev.setConnectionValue(connValue);
//
//		}

		return true;
	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public void refresh() {
		refreshHardware( hardware );
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	public String[] getPorts() {
		List<String> ports = new LinkedList<String>();
		
		DefaultTableModel model = (DefaultTableModel) table.getModel();

		for(int row = 0; row < model.getRowCount(); row++ ) {
			boolean enabled = (Boolean)model.getValueAt(row, COL_ENABLED );

			if (enabled) {
				ports.add( (String)model.getValueAt(row,  COL_OBJECT));
			} 

		}

		String [] arr = new String[ports.size()];
		ports.toArray( arr );
		return arr;
	}

}
