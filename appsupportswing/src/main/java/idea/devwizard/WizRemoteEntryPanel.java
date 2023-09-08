/*
 * Created by JFormDesigner on Wed Oct 07 11:45:32 CDT 2009
 */

package idea.devwizard;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.StringStringMap;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class WizRemoteEntryPanel extends JPanel implements WizardPanelInterface {
	private static final int COL_KEY = 1;
	private static final int COL_PROMPT = 2;

	private RpDevice dc;
	private WizardMasterInterface wizard;
	private boolean debug = true;

	public WizRemoteEntryPanel(WizardMasterInterface wizard, RpDevice dev_conf) {
		this.dc = dev_conf;
		this.wizard = wizard;

		initComponents();

		if (dev_conf != null) {
			String name = dev_conf.getName();
			if (name != null) {
				devName.setText(name);
			}
		}

	}

	public void refresh() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);

		StringStringMap params = dc.getParam();

		//		for( RpKVPair pair : params ) {
		//			model.addRow( new Object [] { pair, pair.getKey(), pair.getValue() } );
		//		}

		if (params != null) {

			String val = params.get("excelFile");
			if (val != null) {
				File f = new File(val);
				refresh(f);
			}

		}

	}

	private void loadActionPerformed(ActionEvent e) {

		String lastOpen;
		try {
			lastOpen = PrefUtil.getUserPref("REMOTEENTRY_LOAD_FILE", null);

			File f = null;
			if (lastOpen != null) {
				f = new File(lastOpen);
			}
			GuiUtil.doOpenFileChooser(JFileChooser.FILES_ONLY, "Load", this, f, new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					File f = (File) e.getSource();
					refresh(f);

				}

			});
		} catch (Exception e1) {
			GuiUtil.showError("Could not open file: ", e1);
		}

	}

	private void refresh(File f) {
		System.err.println("ERROR: cardioStrip RemoteEntry needs rethought");
		//		try {
		//			excelName.setText( f.getPath());
		//			LinkedList<EntrySheet> sheets = EntryUtil.loadEntrySheets( f );
		//			refresh( sheets );
		//		PrefUtil.saveUserPref("REMOTEENTRY_LOAD_FILE", f.getCanonicalPath() );
		//		} catch (Exception e1) {
		//			GuiUtil.showError("Load", e1);
		//		}
	}

	//	private void refresh(LinkedList<EntrySheet> sheets) {
	//		while( tabber.getTabCount() > 1 ) {
	//			tabber.removeTabAt( 1 );
	//		}
	//		
	//		boolean first = true;
	//		for( EntrySheet sheet : sheets ) {
	//			if( first ) {
	//				refreshTimepoints( sheet );
	//				first = false;
	//			}
	//			
	//			JTable table = buildTableFromEntrySheet(sheet);
	//			fillTable( table, sheet.getItems() );
	//
	//			tabber.addTab(sheet.getName(), new JScrollPane(table) );
	//		}
	//	}

	//	private void refreshTimepoints(EntrySheet sheet) {
	//		DefaultTableModel model = (DefaultTableModel) timepointsTable.getModel();
	//		model.setRowCount( 0 );
	//		
	//		LinkedList<EntryTimePoint> timepoints = sheet.getTimepoints();
	//		for( EntryTimePoint timepoint : timepoints ) {
	//			model.addRow( new Object[] {timepoint, timepoint.getTpName(), timepoint.getTpTime(), timepoint.getTpTime() } );
	//		}
	//	}

	//	private void fillTable(JTable table, LinkedList<EntryItem> items) {
	//		DefaultTableModel model = (DefaultTableModel) table.getModel();
	//		model.setRowCount( 0 );
	//
	//		for( EntryItem item : items ) {
	//			model.addRow( new Object[] { item, item.getDevValue(), item.getPrompt(), item.getValidation() } );
	//		}
	//	}
	//
	//	private JTable buildTableFromEntrySheet(EntrySheet sheet) {
	//		JTable table = new JTable();
	//		
	//		//---- table1 ----
	//		table.setModel(new DefaultTableModel(
	//			new Object[][] {
	//				{null, "ART_SYS", "Systolic", "[50,220]"},
	//				{null, "ART_DIA", "Diastolic", null},
	//				{null, "ART_MAP", null, null},
	//			},
	//			new String[] {
	//				"O", "Key", "Prompt", "Validation"
	//			}
	//		) {
	//			boolean[] columnEditable = new boolean[] {
	//				false, true, true, true
	//			};
	//			@Override
	//			public boolean isCellEditable(int rowIndex, int columnIndex) {
	//				return columnEditable[columnIndex];
	//			}
	//		});
	//		{
	//			TableColumnModel cm = table.getColumnModel();
	//			cm.getColumn(0).setResizable(false);
	//			cm.getColumn(0).setMinWidth(10);
	//			cm.getColumn(0).setMaxWidth(10);
	//			cm.getColumn(0).setPreferredWidth(10);
	//			cm.getColumn(1).setPreferredWidth(100);
	//			cm.getColumn(2).setPreferredWidth(100);
	//			cm.getColumn(3).setPreferredWidth(300);
	//		}
	//
	//		
	//		return table;
	//	}
	//
	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		label1 = new JLabel();
		devName = new JTextField();
		tabber = new JTabbedPane();
		scrollPane2 = new JScrollPane();
		timepointsTable = new JTable();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		scrollPane4 = new JScrollPane();
		table4 = new JTable();
		panel2 = new JPanel();
		excelName = new JLabel();
		load = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("right:[50dlu,default], $lcgap, [150dlu,default], $lcgap, default",
					"default"));

			//---- label1 ----
			label1.setText("Name:");
			panel1.add(label1, cc.xy(1, 1));
			panel1.add(devName, cc.xy(3, 1));
		}
		add(panel1, cc.xy(1, 1));

		//======== tabber ========
		{

			//======== scrollPane2 ========
			{

				//---- timepointsTable ----
				timepointsTable.setModel(new DefaultTableModel(new Object[][] {
						{ null, "Baseline", "Day1 Baseline", "0", null },
						{ null, "Baseline", "Day2 Baseline", "0", null },
						{ null, "Procedure 1", null, "+10 min", null },
						{ null, "Procedure 1A", null, "+10 min", null }, { null, "Break", "End Day 1", "0", null },
						{ null, "Baseline", "Day 2 Baseline", "0", null },
						{ null, "Baseline ", "Day 2 Baseline", "0", null }, { null, "Procedure 1", null, null, null },
						{ null, "Procedure 1A", null, null, null }, }, new String[] { "O", "Procedure", "Description",
						"Time", "Require" }) {
					Class<?>[] columnTypes = new Class<?>[] { Object.class, Object.class, Object.class, Object.class,
							Boolean.class };
					boolean[] columnEditable = new boolean[] { false, true, true, true, true };

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
					TableColumnModel cm = timepointsTable.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(10);
					cm.getColumn(0).setMaxWidth(10);
					cm.getColumn(0).setPreferredWidth(10);
					cm.getColumn(1).setPreferredWidth(80);
					cm.getColumn(2).setPreferredWidth(200);
					cm.getColumn(3).setPreferredWidth(100);
				}
				scrollPane2.setViewportView(timepointsTable);
			}
			tabber.addTab("Timepoints", scrollPane2);

			//======== scrollPane1 ========
			{

				//---- table1 ----
				table1.setModel(new DefaultTableModel(new Object[][] { { null, "ART_SYS", "Systolic", "[50,220]" },
						{ null, "ART_DIA", "Diastolic", null }, { null, "ART_MAP", null, null }, }, new String[] { "O",
						"Key", "Prompt", "Validation" }) {
					boolean[] columnEditable = new boolean[] { false, true, true, true };

					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = table1.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(10);
					cm.getColumn(0).setMaxWidth(10);
					cm.getColumn(0).setPreferredWidth(10);
					cm.getColumn(1).setPreferredWidth(100);
					cm.getColumn(2).setPreferredWidth(100);
					cm.getColumn(3).setPreferredWidth(300);
				}
				scrollPane1.setViewportView(table1);
			}
			tabber.addTab("Procedure 1", scrollPane1);

			//======== scrollPane4 ========
			{

				//---- table4 ----
				table4.setModel(new DefaultTableModel(new Object[][] { { null, "ABG_LAB1", "Systolic", "[50,220]" },
						{ null, "ABG_LAB2", "Diastolic", null }, { null, "ABG_LAB3", null, null }, }, new String[] {
						"O", "Key", "Prompt", "Validation" }) {
					boolean[] columnEditable = new boolean[] { false, true, true, true };

					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = table4.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(10);
					cm.getColumn(0).setMaxWidth(10);
					cm.getColumn(0).setPreferredWidth(10);
					cm.getColumn(1).setPreferredWidth(100);
					cm.getColumn(2).setPreferredWidth(100);
					cm.getColumn(3).setPreferredWidth(300);
				}
				scrollPane4.setViewportView(table4);
			}
			tabber.addTab("Procedure 1A", scrollPane4);

		}
		add(tabber, cc.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default:grow, $lcgap, [50dlu,default]", "default"));

			//---- excelName ----
			excelName.setText("text");
			panel2.add(excelName, cc.xy(1, 1));

			//---- load ----
			load.setText("Load");
			load.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					loadActionPerformed(e);
				}
			});
			panel2.add(load, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JLabel label1;
	private JTextField devName;
	private JTabbedPane tabber;
	private JScrollPane scrollPane2;
	private JTable timepointsTable;
	private JScrollPane scrollPane1;
	private JTable table1;
	private JScrollPane scrollPane4;
	private JTable table4;
	private JPanel panel2;
	private JLabel excelName;
	private JButton load;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	protected void panelToModel() {
		if (dc == null) {
			dc = new RpDevice();
		} else {
			RpUtil.resetDC(dc);
		}

		// ? dc.setDeviceClass( driver.getClass().getCanonicalName() );
		dc.setConnectionType(RpConnType.NONE);

		dc.setConnectionValue("");
		dc.setName("remote_entry");
		dc.setDeviceClass("FIXME--IDEAProxyDevice.class.getCanonicalName()");

		DefaultTableModel model = (DefaultTableModel) table1.getModel();

		StringStringMap params = dc.getParam();
		params.clear();

		params.put("excelFile", excelName.getText());

		for (int row = 0; row < model.getRowCount(); row++) {
			String key = (String) model.getValueAt(row, COL_KEY);
			String prompt = (String) model.getValueAt(row, COL_PROMPT);

			params.put(key, prompt );
		}
	}

	@Override
	public boolean next() {
		panelToModel();

		return true;
	}

	@Override
	public boolean finish() {
		panelToModel();
		return true;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

}
