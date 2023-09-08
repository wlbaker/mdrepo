package idea.gui;


import java.awt.Component;
import java.math.BigDecimal;

import javax.swing.AbstractCellEditor;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.table.TableCellEditor;
import javax.swing.text.Document;

import lombok.extern.slf4j.Slf4j;

@SuppressWarnings("serial")
@Slf4j
public class NumericCellEditor<T extends Number> extends AbstractCellEditor implements TableCellEditor {
    // This is the component that will handle the editing of the cell value
    JTextField component = new JTextField();
    
    Class[] argTypes = new Class[]{String.class};
    java.lang.reflect.Constructor constructor;
    
	//
    // difficult to explain why the generic class must be inserted here
    // either trust me or google "get type name for generic parameter of generic class"
    //
    public NumericCellEditor(Class<T> clazz) {  
    	this( clazz, null );
    }
    
    public NumericCellEditor(Class<T> clazz, Document doc ) {
    	if( doc == null ) {
        	CustomizedDocument cdoc = new CustomizedDocument();
        	cdoc.setNumeric( true );
        	cdoc.setMaxChars( 16 );
        	
        	doc = cdoc;
    	}
    	component.setDocument( doc );
    	component.setHorizontalAlignment( SwingConstants.TRAILING );
    	
        try {
            // Class<?> type = T.getClass();
            // Since our obligation is to produce a value which is
            // assignable for the required type it is OK to use the
            // String constructor for columns which are declared
            // to contain Objects. A String is an Object.
            constructor = clazz.getConstructor(argTypes);
        }
        catch (Exception e) {
            log.error("no string constructor", e);
        }
    }
    
    // This method is called when a cell value is edited by the user.
    public Component getTableCellEditorComponent(JTable table, Object value,
            boolean isSelected, int rowIndex, int vColIndex) {
        // 'value' is value contained in the cell located at (rowIndex, vColIndex)

        // Configure the component with the specified value
    	if( value == null ) {
    		component.setText("");
    	} else if( value instanceof String ) {
    		// this really should not happen, I think
            component.setText((String)value);    		
    	} else if( value instanceof BigDecimal ) {
            component.setText( ((BigDecimal)value).toPlainString());    		
    	} else {
    		T bd = (T)value;
    		component.setText( bd.toString() );
    	}

        // Return the configured component
        return component;
    }

    // This method is called when editing is completed.
    // It must return the new value to be stored in the cell.
    public Object getCellEditorValue() {
    	
    	T value = null;
    	
    	String val = component.getText();
    	if( val.length() > 0 ) {
    		// bd = (T)new Double( val );
    		try {
				value = (T) constructor.newInstance(new Object[]{val});
			} catch (Exception e) {
				e.printStackTrace();
			}
    	}
        return value;
    }
}