/*
 * Created by JFormDesigner on Wed Oct 02 14:06:18 CDT 2013
 */

package idea.analysis;

import icuInterface.RpUtil;
import idea.message.StreamID;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import idea.GuiUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
public class ReboaPressureSetupPanel extends JPanel implements
		ListSelectionListener, TableModelListener {
	private static final int LOC_SELECTION_COL = 1;
	
	private RpAnalysis anal;
	private RpDevice currentDev;

	public ReboaPressureSetupPanel(RpStudy study, RpAnalysis anal) {
		initComponents();

		this.anal = anal;

		loadSourceTable(study, anal);
		ListSelectionModel selection = devTable.getSelectionModel();
		selection.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		selection.addListSelectionListener(this);

		loadLocTable(null);
	}

	private void loadSourceTable(RpStudy study, RpAnalysis anal) {
		List<RpHardware> hw = study.getHardware();
		DefaultTableModel model = (DefaultTableModel) devTable.getModel();
		model.setRowCount(0);

		if (hw == null || hw.size() == 0) {
			return;
		}

		RpHardware hw0 = hw.get(0);
		List<RpDevice> devs = hw0.getDevices();

		for (RpDevice dev : devs) {
			model.addRow(new Object[] { dev, dev.getName() });
		}
	}

	/**
	 * (non-Javadoc)
	 * 
	 * @see javax.swing.event.ListSelectionListener#valueChanged(javax.swing.event.ListSelectionEvent)
	 * 
	 *      Action taken when a new device is selected.
	 * 
	 */
	@Override
	public void valueChanged(ListSelectionEvent e) {
		int row = devTable.getSelectedRow();
		RpDevice dev = (RpDevice) devTable.getValueAt(row, 0);
		if( e.getValueIsAdjusting() ) {
			// ignore
		} else {
			loadLocTable(dev);
		}
	}

	private void loadLocTable(RpDevice dev) {

		this.currentDev = dev;

		DefaultTableModel model = (DefaultTableModel) locTable.getModel();

		model.removeTableModelListener(this);
		model.setRowCount(0);
		if (dev == null) {
			return;
		}

		StringStringMap params = anal.getParam();
		if( params == null ) {
			params = new StringStringMap();
			anal.setParam(params);
		}
		String value = params.get(currentDev.getName()); 
		if( value == null ) {
			value = "";
		}
		System.out.println("loading loc table: " + currentDev + " value: " + value );
		for (RpMetric metric : RpUtil.getMetrics(dev, StreamID.MEASUREMENT) ) {
			boolean selected = false;
			String loc = metric.getLocation();
			if( value.indexOf( ":" + loc + ":") >= 0 ) {
				selected = true;
			}
			model.addRow(new Object[] { metric, selected, metric.getAlias() });
		}
		model.addTableModelListener(this);
	}

	/**
	 * 
	 * @param e
	 * 
	 *            Action taken when a the check mark is added or removed to a
	 *            data point in the "loc" table.
	 * 
	 */

	@Override
	public void tableChanged(TableModelEvent e) {

		int row = e.getFirstRow();
		System.out.println("row changed: " + row);

		saveRowInfo();
	}

	private void saveRowInfo() {
		assert (currentDev != null);

		StringStringMap params = anal.getParam();
		StringBuilder value = new StringBuilder();
		value.append(":");
		DefaultTableModel model = (DefaultTableModel) locTable.getModel();
		for( int row = 0; row < model.getRowCount(); row++ ) {
			Boolean b = (Boolean) model.getValueAt( row, LOC_SELECTION_COL );
			if( b != null && b == true ) {
				RpMetric metric = (RpMetric) model.getValueAt( row, 0);
				if( value.length() > 0 ) {
					value.append(":");
				}
				value.append( metric.getLocation() );
			}
		}
		value.append(":");
		
		params.put( currentDev.getName(), value.toString() );
		
		System.out.println("save row info: " + currentDev + " value: " + value );

	}


	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void okActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		devTable = new JTable();
		scrollPane2 = new JScrollPane();
		locTable = new JTable();
		panel3 = new JPanel();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "default, $lgap, default"));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("150dlu, $lcgap, default:grow",
					"fill:default:grow"));

			// ======== scrollPane1 ========
			{

				// ---- devTable ----
				devTable.setModel(new DefaultTableModel(new Object[][] {
						{ null, null }, { null, null }, }, new String[] {
						"loc", "Device" }) {
					Class<?>[] columnTypes = new Class<?>[] { Object.class,
							String.class };
					boolean[] columnEditable = new boolean[] { false, false };

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
					TableColumnModel cm = devTable.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(200);
				}
				scrollPane1.setViewportView(devTable);
			}
			panel2.add(scrollPane1, cc.xy(1, 1));

			// ======== scrollPane2 ========
			{

				// ---- locTable ----
				locTable.setModel(new DefaultTableModel(new Object[][] {
						{ null, true, null }, { null, true, null }, },
						new String[] { "loc", "Selected", "Name" }) {
					Class<?>[] columnTypes = new Class<?>[] { Object.class,
							Boolean.class, String.class };
					boolean[] columnEditable = new boolean[] { false, true,
							false };

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
					TableColumnModel cm = locTable.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(20);
					cm.getColumn(2).setPreferredWidth(200);
				}
				locTable.setPreferredScrollableViewportSize(new Dimension(250,
						100));
				scrollPane2.setViewportView(locTable);
			}
			panel2.add(scrollPane2, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 1));

		// ======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
					"default, $lcgap, default:grow, $lcgap, default, 2*($lcgap, [50dlu,default])",
					"default"));

			// ---- ok ----
			ok.setText("OK");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel3.add(ok, cc.xy(7, 1));

			// ---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel3.add(cancel, cc.xy(9, 1));
		}
		add(panel3, cc.xy(1, 3));
		// JFormDesigner - End of component initialization
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTable devTable;
	private JScrollPane scrollPane2;
	private JTable locTable;
	private JPanel panel3;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
