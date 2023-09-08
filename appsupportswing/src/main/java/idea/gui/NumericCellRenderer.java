package idea.gui;

import java.awt.Component;
import java.text.NumberFormat;

import javax.swing.JLabel;
import javax.swing.JTable;
import javax.swing.SwingConstants;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableCellRenderer;

/*
 * 
 * NOTE: this cell renderer is backwards...it should really subclass DefaultCellRenderer
 * this class should be depricated and replaced with a slightly different one
 * 
 */
@SuppressWarnings("serial")
public class NumericCellRenderer extends DefaultTableCellRenderer {
	protected TableCellRenderer parent;
	protected NumberFormat f;
	JLabel label;

	public NumericCellRenderer( TableCellRenderer parent, NumberFormat f ) {
		this.parent = parent;
		this.f = f;
		label = new JLabel();
	}
	
	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
	
		JLabel l;
		if( parent == null ) {
			l = (JLabel)super.getTableCellRendererComponent( table, value, isSelected, hasFocus, row, column);
		} else {
			l = (JLabel)parent.getTableCellRendererComponent( table, value, isSelected, hasFocus, row, column);
		}

		label.setSize( l.getSize() );
		label.setBorder( l.getBorder() );
		label.setBackground( l.getBackground() );
		label.setForeground( l.getForeground() );
		label.setOpaque( l.isOpaque() );
		
		if( value == null ) {
			label.setText("");
		} else {
			// BigDecimal bd = (BigDecimal)value;
			try {
				label.setText( f.format( value ));
				label.setHorizontalAlignment( SwingConstants.TRAILING );
			} catch (Exception e) {
				// System.out.println( "cannot format: " + value);
				label.setText( "??" );
			}
		}
		return label;
	}

}
