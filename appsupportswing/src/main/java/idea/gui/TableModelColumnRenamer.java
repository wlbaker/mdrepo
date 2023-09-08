package idea.gui;

import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;

public class TableModelColumnRenamer implements TableModel {

	TableModel ref;
	String[]   columnName;
	
	public TableModelColumnRenamer(TableModel ref, String[] columnName) {
		this.ref = ref;
		this.columnName = columnName;
	}

	public void addTableModelListener(TableModelListener l) {
		ref.addTableModelListener(l);
	}

	public Class<?> getColumnClass(int columnIndex) {
		return ref.getColumnClass(columnIndex);
	}

	public int getColumnCount() {
		return ref.getColumnCount();
	}

	public String getColumnName(int columnIndex) {
		return columnName[columnIndex];
	}

	public int getRowCount() {
		return ref.getRowCount();
	}

	public Object getValueAt(int rowIndex, int columnIndex) {
		return ref.getValueAt( rowIndex, columnIndex);
	}

	public boolean isCellEditable(int rowIndex, int columnIndex) {
		return ref.isCellEditable(rowIndex, columnIndex);
	}

	public void removeTableModelListener(TableModelListener l) {
		ref.removeTableModelListener(l);
	}

	public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
		ref.setValueAt(aValue, rowIndex, columnIndex);
	}

}
