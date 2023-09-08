/*
 * Created by JFormDesigner on Fri Jan 14 08:21:46 CST 2011
 */

package idea.tsoffline.codes_editor;

import java.awt.event.ActionEvent;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.ExcelAdapter;
import idea.gui.TableSorter;
import idea.ts.TsCode;
import idea.tsoffline.AppFrame;
import idea.tsoffline.AppModel;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SubstitutionsPanel extends JPanel {
	private static final int OBJECT1_COL = 0; // original object...not changed until OK
	private static final int OBJECT2_COL = 1; // working object...edited
	private static final int NAME_COL = 2;
	private static final int SUBSTITUTION_COL = 3;

	public SubstitutionsPanel() {
		initComponents();
		initTable();


		populate();

	}

//	public void initColorColumn( TableColumn col, Color[] colors) {
//
//	}

	private void initTable() {

		TableSorter sorter = new TableSorter(table.getModel());
		
		table.setAutoCreateColumnsFromModel(false);
		table.setModel(sorter);
		sorter.setTableHeader(table.getTableHeader());

		new ExcelAdapter(table);
		
	}

	private void populate() {
		TableSorter sorter = (TableSorter) table.getModel();
		DefaultTableModel model = (DefaultTableModel) sorter.getTableModel();
		model.setRowCount(0);

		String[][] subs = AppModel.getSubstitutionsModel();
		if (subs != null) {
			for (String[] sub : subs) {
				model.addRow(new Object[] { sub, null, sub[0], sub[1]});
			}
		}
	}

	public void panelToModel(ActionEvent e) {
		if (table.isEditing()) {
			TableCellEditor editor = table.getCellEditor();
			editor.stopCellEditing(); // commit edited values
		}
		List<TsCode> codes = AppFrame.getInstance().getCodeModel();
		codes.clear();

		TableModel model = table.getModel();
		for (int row = 0; row < model.getRowCount(); row++) {
			TsCode ee = (TsCode) model.getValueAt(row, OBJECT2_COL);
			if (ee == null) {
				ee = (TsCode) model.getValueAt(row, OBJECT1_COL);
				// no change...but not deleted either.
			}
			ee.setCode((String) model.getValueAt(row, NAME_COL));
			ee.setDescription((String) model.getValueAt(row, SUBSTITUTION_COL));

			codes.add(ee); // add events...one per row
		}

	}

	private void insertActionPerformed(ActionEvent e) {
		TableSorter sorter = (TableSorter) table.getModel();
		DefaultTableModel model = (DefaultTableModel) sorter.getTableModel();

		TsCode tsCode = new TsCode();
		model.addRow(new Object[] { null, null, "", ""});
		

	}

	private void deleteActionPerformed(ActionEvent e) {
		int[] rows = table.getSelectedRows();
		if (rows != null && rows.length > 0) {
			TableSorter sorter = (TableSorter) table.getModel();
			DefaultTableModel model = (DefaultTableModel) sorter.getTableModel();

			// remove starting from the end, otherwise the row numbers change
			for (int idx = rows.length - 1; idx >= 0; idx--) {
				int row = sorter.modelIndex(rows[idx]);
				model.removeRow(row);
			}
		}
	}

	private void editActionPerformed(ActionEvent e) {
		int row = table.getSelectedRow();

		if (row < 0) {
			return;
		}

		TsCode event = (TsCode) table.getValueAt(row, OBJECT2_COL);
		if (event == null) {
			TsCode ori = (TsCode) table.getValueAt(row, OBJECT1_COL);
			event = new TsCode();
		}

		event.setCode((String) table.getValueAt(row, NAME_COL));
		event.setDescription((String) table.getValueAt(row, SUBSTITUTION_COL));
		// event.setColor( ori.getColor() );
		table.setValueAt(event, row, OBJECT2_COL);

		GuiUtil.showMessage("Single Code Editor not ready");
		//		SingleEventPanel panel = new SingleEventPanel(event);
		//		GuiUtil.doDialog("Single Event", AppFrame.getInstance(), panel, null);
		//		if (panel.isOk()) {
		//			table.setValueAt(event.getCode(), row, CODE_COL);
		//			table.setValueAt(event.getDesc(), row, DESC_COL);
		//		}

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel3 = new JPanel();
		scrollPane1 = new JScrollPane();
		table = new JTable();
		panel2 = new JPanel();
		insert = new JButton();
		delete = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow"));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"default:grow, $lcgap, default",
				"default, $lgap, fill:default:grow"));

			//======== scrollPane1 ========
			{

				//---- table ----
				table.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null, "", "200"},
						{null, null, null, null},
					},
					new String[] {
						null, "O", "Original", "Replacement"
					}
				) {
					boolean[] columnEditable = new boolean[] {
						false, false, true, true
					};
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
					cm.getColumn(1).setResizable(false);
					cm.getColumn(1).setMinWidth(1);
					cm.getColumn(1).setMaxWidth(1);
					cm.getColumn(1).setPreferredWidth(1);
					cm.getColumn(2).setPreferredWidth(100);
					cm.getColumn(3).setPreferredWidth(140);
				}
				scrollPane1.setViewportView(table);
			}
			panel3.add(scrollPane1, CC.xy(1, 3));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout(
					"[50dlu,default]",
					"4*(default, $lgap), fill:default:grow"));

				//---- insert ----
				insert.setText("Insert");
				insert.addActionListener(e -> insertActionPerformed(e));
				panel2.add(insert, CC.xy(1, 1));

				//---- delete ----
				delete.setText("Delete");
				delete.addActionListener(e -> deleteActionPerformed(e));
				panel2.add(delete, CC.xy(1, 3));
			}
			panel3.add(panel2, CC.xy(3, 3));
		}
		add(panel3, CC.xy(1, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel3;
	private JScrollPane scrollPane1;
	private JTable table;
	private JPanel panel2;
	private JButton insert;
	private JButton delete;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
