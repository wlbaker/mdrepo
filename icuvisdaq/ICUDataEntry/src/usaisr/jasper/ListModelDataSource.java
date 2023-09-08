/*
 * Created on Jul 13, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package idea.jasper;

import java.lang.reflect.Field;

import javax.swing.ListModel;

import net.sf.jasperreports.engine.JRDataSource;
import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRField;

/**
 * @author bbaker
 *
 */
public class ListModelDataSource implements JRDataSource {

    ListModel model;
    Object    oCurrent;
    Class     clCurrent;
    Class     clFilter;
    
    int idx = 0;
    
    /* (non-Javadoc)
     * @see net.sf.jasperreports.engine.JRDataSource#next()
     */
    public boolean next() throws JRException {
        
        boolean success = false;
        
        do {
            success = ( idx < model.getSize() );
	        if( success ) {
	            oCurrent = model.getElementAt( idx );
	            clCurrent  = oCurrent.getClass(); 
	            idx++;
	        }
        } while( success && clFilter != null && !(clCurrent.equals(clFilter)) );

        return success;
    }

    /* (non-Javadoc)
     * @see net.sf.jasperreports.engine.JRDataSource#getFieldValue(net.sf.jasperreports.engine.JRField)
     */
    public Object getFieldValue(JRField jrField) throws JRException {
        
		Field f;
		Object oValue = null;
		
        try {
            f = clCurrent.getDeclaredField( jrField.getName() );
            oValue = f.get( oCurrent );
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return oValue;
    }
    
    public ListModelDataSource( ListModel model ) {
        this.model = model;
    }

    public ListModelDataSource( ListModel model, Class clFilter ) {
        this.model = model;
        this.clFilter = clFilter;
    }

}
