package idea.gui;

import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;

@SuppressWarnings("serial")
public class TableModelFixer implements TableModel {

	private TableModel tm;

	public TableModelFixer( TableModel tm ) {
		this.tm = tm;
	}
	
	@Override
	public void addTableModelListener(TableModelListener l) {
		tm.addTableModelListener(l);
	}

	@Override
	public Class<?> getColumnClass(int columnIndex) {
		return tm.getColumnClass(columnIndex);
	}

	@Override
	public String getColumnName(int column) {
		return tm.getColumnName(column);
	}

	@Override
	public boolean isCellEditable(int rowIndex, int columnIndex) {
		return tm.isCellEditable(rowIndex, columnIndex);
	}

	@Override
	public void removeTableModelListener(TableModelListener l) {
		tm.removeTableModelListener(l);
	}

	@Override
	public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
		tm.setValueAt(aValue, rowIndex, columnIndex);
	}

	@Override
	public int getColumnCount() {
		return tm.getColumnCount();
	}

	@Override
	public int getRowCount() {
		return tm.getRowCount();
	}

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		return tm.getValueAt(rowIndex, columnIndex);
	}

	public TableModel getShadowedModel() {
		return tm;
	}
	
	
}
