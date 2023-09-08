package idea.gui;

import java.awt.Component;

import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

import idea.schema.rp.RpMetric;

@SuppressWarnings("serial")
public class RpMetricTableCellRenderer extends DefaultTableCellRenderer {
	public Component getTableCellRendererComponent(JTable table, Object obj, boolean isSelected, boolean hasFocus,
			int row, int column) {

		String t = toString( (RpMetric)obj);
		Component cell = super.getTableCellRendererComponent(table, t, isSelected, hasFocus, row, column);

		if (isSelected) {
			// cell.setBackground(Color.green);
		}

		return cell;
	}

	public static String toString(RpMetric obj) {
		String t = null;
		
		RpMetric metric = (RpMetric) obj;
		if (metric != null) {
			t = metric.getCode();
			if (t == null || t.length() == 0) {
				t = metric.getName();
			}
			if (t == null || t.length() == 0) {
				t = metric.getLocation();
			}
		}
		
		if( t == null ) {
			t = "[??]";
		}
		return t;
	}
}