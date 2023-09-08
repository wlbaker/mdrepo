package idea.tsoffline.event_editor;

import java.awt.Component;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

@SuppressWarnings("serial")
class DateCellRenderer extends DefaultTableCellRenderer {
	SimpleDateFormat f;

	public DateCellRenderer(String fmt) {
		f = new SimpleDateFormat(fmt);
	}

	@Override
	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
		if (value instanceof Date) {
			value = f.format(value);
		}
		return super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
	}
};
