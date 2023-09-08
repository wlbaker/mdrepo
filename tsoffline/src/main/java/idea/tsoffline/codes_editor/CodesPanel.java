/*
 * Created by JFormDesigner on Fri Jan 14 08:21:46 CST 2011
 */

package idea.tsoffline.codes_editor;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import javax.swing.AbstractCellEditor;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

import idea.intf.StreamProducer;
import idea.model.Annotation;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;
import idea.GuiUtil;
import idea.gui.ColorTableCellRenderer;
import idea.gui.ExcelAdapter;
import idea.gui.TableSorter;
import idea.ts.TsCode;
import idea.tsoffline.AppFrame;
import idea.tsoffline.AppModel;
import idea.tsoffline.ColorManager;
import idea.tsoffline.model.OfflineDevice;

/**
 * A CellEditor for tables, using a JDateChooser.
 * 
 * @author Kai Toedter
 * @version $LastChangedRevision: 100 $
 * @version $LastChangedDate: 2006-06-04 14:36:06 +0200 (So, 04 Jun 2006) $
 */
@SuppressWarnings("serial")
class DateChooserCellEditor extends AbstractCellEditor implements TableCellEditor {

	private JDateChooser dateChooser = new JDateChooser();

	@Override
	public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected, int row, int column) {

		Date date = null;
		if (value instanceof Date)
			date = (Date) value;

		dateChooser.setDate(date);

		return dateChooser;
	}

	@Override
	public Object getCellEditorValue() {
		return dateChooser.getDate();
	}

	public void setDateFormatString(String fmt) {
		dateChooser.setDateFormatString(fmt);
	}
}

@SuppressWarnings("serial")
class DateCellRenderer extends DefaultTableCellRenderer {
	SimpleDateFormat f;

	public DateCellRenderer(String fmt) {
		f = new SimpleDateFormat(fmt);
	}

	@Override
	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus,
			int row, int column) {
		if (value instanceof Date) {
			value = f.format(value);
		}
		return super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
	}
};

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class CodesPanel extends JPanel {
	private static final int OBJECT1_COL = 0; // original object...not changed until OK
	private static final int OBJECT2_COL = 1; // working object...edited
	private static final int CODE_COL = 2;
	private static final int DESC_COL = 3;
	private static final int COLOR_COL = 4;

	public CodesPanel() {
		initComponents();
		initTable();


		populate();

	}

//	public void initColorColumn( TableColumn col, Color[] colors) {
//
//	}

	private void initTable() {
		TableColumn col = table.getColumnModel().getColumn(COLOR_COL);

		col.setCellRenderer(new ColorTableCellRenderer());

		TableSorter sorter = new TableSorter(table.getModel()) {

			@Override
			public Class getColumnClass(int column) {
				if (column == COLOR_COL) {
					return Color.class;
				}
				// else
				return super.getColumnClass(column);
			}
			

		};
		table.setAutoCreateColumnsFromModel(false);
		table.setModel(sorter);
		sorter.setTableHeader(table.getTableHeader());

		new ExcelAdapter(table);
		
		GuiUtil.initColorColumn(col, ColorManager.getColors());
	}

	private void populate() {
		TableSorter sorter = (TableSorter) table.getModel();
		DefaultTableModel model = (DefaultTableModel) sorter.getTableModel();
		model.setRowCount(0);

		List<TsCode> codes = AppFrame.getInstance().getCodeModel();
		if (codes != null) {
			for (TsCode code : codes) {
				addOneRowToModel(model, code, null);
			}
		}
	}

	private void addOneRowToModel(DefaultTableModel model, TsCode tsCodeOri, TsCode tsCodeNew) {
		String code = "?";
		String description = "";
		if (tsCodeOri != null) {
			code = tsCodeOri.getCode();
			description = tsCodeOri.getDescription();
		} else {
			code = tsCodeNew.getCode();
			description = tsCodeNew.getDescription();
		}
		model.addRow(new Object[] { tsCodeOri, tsCodeNew, code, description, Color.RED });
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
			ee.setCode((String) model.getValueAt(row, CODE_COL));
			ee.setDescription((String) model.getValueAt(row, DESC_COL));

			codes.add(ee); // add events...one per row
		}

	}

	private void insertActionPerformed(ActionEvent e) {
		TableSorter sorter = (TableSorter) table.getModel();
		DefaultTableModel model = (DefaultTableModel) sorter.getTableModel();

		TsCode tsCode = new TsCode();
		addOneRowToModel(model, null, tsCode);

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

		event.setCode((String) table.getValueAt(row, CODE_COL));
		event.setDescription((String) table.getValueAt(row, DESC_COL));
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

	private void importAnnotationsActionPerformed(ActionEvent e) {
		try {
			_importAnnotationsActionPerformed();
		} catch (IOException e1) {
			GuiUtil.showError("Importing Annotations", e1);
		}
	}

	private void _importAnnotationsActionPerformed() throws IOException {

		GuiUtil.showMessage("FIXME unused?: );AppFrame.getImporter();");
		OfflineDevice dev = AppModel.getDevice("Annotations");

		PiDatastreamImporter anno = null;
		if (anno == null) {
			return; // no annotations
		}

		anno.rewind();

		Annotation item;
		TableSorter sorter = (TableSorter) table.getModel();
		DefaultTableModel model = (DefaultTableModel) sorter.getTableModel();
		while ((item = (Annotation) anno.next()) != null) {
			String message = item.getMessage();
			StreamProducer driver = (StreamProducer) anno;
			String src = null;
			if (driver != null) {
				RpDevice conf = driver.getConfiguration();
				if (conf != null) {
					src = conf.getName();
				}
			}

			if (src == null) {
				src = "manual";
			}

			TsCode sevt = new TsCode();
			sevt.setDescription(src + ": " + message);
			sevt.setCode(message);
			addOneRowToModel(model, null, sevt);
		}

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel3 = new JPanel();
		scrollPane1 = new JScrollPane();
		table = new JTable();
		panel2 = new JPanel();
		insert = new JButton();
		edit = new JButton();
		delete = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "fill:default:grow"));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout("default:grow, $lcgap, default", "default, $lgap, fill:default:grow"));

			//======== scrollPane1 ========
			{

				//---- table ----
				table.setModel(new DefaultTableModel(new Object[][] { { null, null, null, "200", null },
						{ null, null, null, null, null }, }, new String[] { null, "O", "Code", "Description", "Color" }) {
					Class<?>[] columnTypes = new Class<?>[] { Object.class, Object.class, Object.class, Object.class,
							Integer.class };
					boolean[] columnEditable = new boolean[] { false, false, true, true, true };

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
					cm.getColumn(1).setResizable(false);
					cm.getColumn(1).setMinWidth(1);
					cm.getColumn(1).setMaxWidth(1);
					cm.getColumn(1).setPreferredWidth(1);
					cm.getColumn(2).setPreferredWidth(100);
					cm.getColumn(3).setPreferredWidth(140);
				}
				scrollPane1.setViewportView(table);
			}
			panel3.add(scrollPane1, cc.xy(1, 3));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout("[50dlu,default]", "5*(default, $lgap), fill:default:grow"));

				//---- insert ----
				insert.setText("Insert");
				insert.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						insertActionPerformed(e);
					}
				});
				panel2.add(insert, cc.xy(1, 1));

				//---- edit ----
				edit.setText("Edit");
				edit.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						editActionPerformed(e);
					}
				});
				panel2.add(edit, cc.xy(1, 3));

				//---- delete ----
				delete.setText("Delete");
				delete.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						deleteActionPerformed(e);
					}
				});
				panel2.add(delete, cc.xy(1, 5));
			}
			panel3.add(panel2, cc.xy(3, 3));
		}
		add(panel3, cc.xy(1, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel3;
	private JScrollPane scrollPane1;
	private JTable table;
	private JPanel panel2;
	private JButton insert;
	private JButton edit;
	private JButton delete;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
