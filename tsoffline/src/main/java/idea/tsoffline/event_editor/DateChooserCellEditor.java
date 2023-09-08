package idea.tsoffline.event_editor;

import java.awt.Component;
import java.util.Date;

import javax.swing.AbstractCellEditor;
import javax.swing.JTable;
import javax.swing.table.TableCellEditor;

import com.toedter.calendar.JDateChooser;

/**
 * A CellEditor for tables, using a JDateChooser.
 * 
 * @author Kai Toedter
 * @version $LastChangedRevision: 100 $
 * @version $LastChangedDate: 2006-06-04 14:36:06 +0200 (So, 04 Jun 2006) $
 */
@SuppressWarnings("serial")
public class DateChooserCellEditor extends AbstractCellEditor implements TableCellEditor {

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

