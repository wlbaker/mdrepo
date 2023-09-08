package idea.gui;

import java.awt.Color;
import java.awt.Component;

import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

@SuppressWarnings("serial")
public class ColorTableCellRenderer extends DefaultTableCellRenderer {
	public Component getTableCellRendererComponent(JTable table, Object obj, boolean isSelected, boolean hasFocus,
			int row, int column) {

		Component cell = super.getTableCellRendererComponent(table, "", isSelected, hasFocus, row, column);

		if (isSelected) {
			//cell.setBackground(Color.green);
		}

		cell.setBackground((Color) obj);
		return cell;
	}
}