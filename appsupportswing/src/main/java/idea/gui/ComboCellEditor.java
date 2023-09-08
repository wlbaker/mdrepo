/*
 * Created on Aug 10, 2006
 *
 */
package idea.gui;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultCellEditor;
import javax.swing.JComboBox;

@SuppressWarnings("serial")
public class ComboCellEditor extends DefaultCellEditor {
    public ComboCellEditor(Object[] items) {
        super(new JComboBox(items));
    }

	public ComboCellEditor(ComboBoxModel model) {
		super( new JComboBox(model));
	}
    
    
}