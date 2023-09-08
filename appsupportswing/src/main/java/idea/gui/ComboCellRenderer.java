/*
 * Created on Aug 10, 2006
 *
 */
package idea.gui;

import java.awt.Color;
import java.awt.Component;

import javax.swing.ComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JTable;
import javax.swing.table.TableCellRenderer;

@SuppressWarnings("serial")
public class ComboCellRenderer extends JComboBox implements TableCellRenderer {

	Color foreground;
	Color highlight;
	Color background;
	
    public ComboCellRenderer(Object[] items) {
        super( items );
    }

    public ComboCellRenderer(ComboBoxModel model) {
		super( model );
	}
    
    @Override
    public void setForeground( Color color ) {  //yes, this overrides
    	this.foreground = color;
    }

    public void setHilight( Color color ) {  //yes, this overrides
    	this.highlight = color;
    }

    @Override
    public void setBackground( Color color ) {  //yes, this overrides
    	this.background = color;
    }

	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected,
            boolean hasFocus, int row, int column) {
		
        if (isSelected) {
            super.setForeground( (foreground != null) ? foreground : table.getSelectionForeground());
            super.setBackground( (highlight != null ) ? highlight : table.getSelectionForeground());
        } else {
            super.setForeground( (foreground != null) ? foreground : table.getForeground());
            super.setBackground( (background != null) ? background : table.getBackground());
        }

        return this;
    }

}