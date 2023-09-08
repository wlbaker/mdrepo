/*
 * Created on Oct 27, 2006
 *
 */
package idea.datamanager.unused.devel;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.lang.reflect.Method;

import javax.persistence.Column;
import javax.swing.JTextField;
import javax.swing.text.Document;
import javax.swing.text.JTextComponent;

import com.jgoodies.binding.adapter.Bindings;
import com.jgoodies.binding.beans.BeanUtils;
import com.jgoodies.binding.value.ValueModel;

public class BindingSupplement {
    
    public static Document getDocFromAnnotations(Class beanClass, String attrib) {
        // access the method annotation
        Column anno = null;
        //FIXME: CustomizedDocument doc = null;

        try {
            Method method = beanClass.getMethod(attrib);
            anno = method.getAnnotation(Column.class);

        } catch (Exception e) {
            e.printStackTrace();
        }

        if (anno == null) {
            // access the field annotation
            // Field field = clazz.getField( attrib );
            // anno = field.getAnnotation(Column.class);
        }

        /*
         * process method level annotations
         */

        // FIXME: Removed because things not in path
//        doc = new CustomizedDocument();
//        doc.setUpperCase(true);
//        if (anno != null) {
//            if( anno.length() > 0 ) doc.setMaxChars(anno.length());
//        }
        Document doc = null;
        
        return doc;
    }


    /**
     * Listens to changes of all bean properties. Fires property changes
     * if the associated property or an arbitrary set of properties has changed.
     */
    private final class PropertyChangeHandler implements PropertyChangeListener {
        
        String field;
        String subfield;
        
        public PropertyChangeHandler(String field, String subfield) {
            this.field = field;
            this.subfield = subfield;
        }

        public void propertyChange(PropertyChangeEvent evt) {
            String propertyName = evt.getPropertyName();
            if (propertyName == null) {
                //forwardAllAdaptedValuesChanged();
                System.out.println("global property change" );
            } else if( field.equals(propertyName)) {
                System.out.println("property change: " + propertyName );
                System.out.println( "source: " + evt.getSource() );
            } else {
                // ignore field we are not interested in
            }
        }
    }

    public static void bind(JTextField rep, Object bean, String field, String subfield) {
        BindingSupplement bs = new BindingSupplement();
        PropertyChangeHandler propertyChangeHandler = bs.new PropertyChangeHandler( field, subfield );
        BeanUtils.addPropertyChangeListener(bean, bean.getClass(), propertyChangeHandler);
        
    }

    public static void bind(JTextField c, ValueModel valueModel, Class beanClass, String getterName) {
        setDocFromAnnotations( c, beanClass, getterName );  // set the doc before the binding to not loose data
        Bindings.bind(c, valueModel, false );
        
    }

	public static void setDocFromAnnotations(JTextComponent c, Class beanClass, String getterName) {
        Document doc = getDocFromAnnotations(beanClass, getterName);
        c.setDocument(doc);
	}


}
