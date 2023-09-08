package idea.tsoffline.event_editor;

import java.awt.Component;
import java.text.DecimalFormat;

import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

@SuppressWarnings("serial")
class DoubleCellRenderer extends DefaultTableCellRenderer {
	DecimalFormat df3 = new DecimalFormat("0.000");

	@Override
	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
		if (value instanceof Double) {
			value = df3.format(value);
		}
		return super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
	}
};

