

package idea.internal.cg;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.lang.reflect.Method;


public class BeanTestCase implements PropertyChangeListener {

    
    public void propertyChange(PropertyChangeEvent evt) {
        System.out.println( "property [" + evt.getPropertyName() + "] changed.");
        
        // initials = (String)evt.getNewValue();
    }

    private void printInterfaceNames(Object o) {
        Class c = o.getClass();
        Class[] theInterfaces = c.getInterfaces();
        for (int i = 0; i < theInterfaces.length; i++) {
           String interfaceName = theInterfaces[i].getName();
           System.out.println(interfaceName);
        }
     }
  
    private void printMethods(Object o) {
        Class c = o.getClass();
        Method[] m = c.getMethods();
        for (int i = 0; i < m.length; i++) {
           System.out.println(m[i].getName());
        }
     }
    
    private static final Class[] PCL_PARAMS = new Class[] {PropertyChangeListener.class}; 

    /*
    public void testSpringPropertyListener() {
        
        Logger.getRootLogger().setLevel( Level.ALL );
        
        Bean b = new Bean();
        ProxyFactory pf = new ProxyFactory();
        IntroductionAdvisor advisor = new PropertyListenerAdvisor();
        pf.setTarget( b );
        pf.addAdvisor( advisor );
        pf.setOptimize( true );
        
        Bean proxy = (Bean)pf.getProxy();
        // b.addPropertyChangeListener( "name", this );
        b.setName( "foobar is my name");
        proxy.setName( "one two three");

        System.out.println( "******** primary interface ---- ");
        printInterfaceNames( b );
        System.out.println( "** methods ");
        printMethods(b);
        System.out.println( "******** proxy interface ---- ");
        printInterfaceNames( proxy );
        System.out.println( "** methods ");
        printMethods( proxy );
        System.out.println( "bean pass?: " + b.getName() );
       
        System.out.flush();
        try {
            Class cl = proxy.getClass();
            System.out.println( "class name=" + cl.getName() );
            cl.getMethod("addPropertyChangeListener", PCL_PARAMS);
        } catch (SecurityException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
        Solines ln = new Solines();
        
        System.out.println("-----------------------");
        // ln.addPropertyChangeListener( "initials", this);
        ln.setInitials( "zzz" );
        
        System.out.println( "solines pass?: " + ln.getInitials());
    }
    */
    
    public static void main(String[] args) {
        
        PropertyChangeListener listener = new PropertyChangeListener() {

            public void propertyChange(PropertyChangeEvent evt) {
                System.out.println("you got it: " + evt.getPropertyName() + " was " + evt.getOldValue() + " now " + evt.getNewValue() );

            }
        };
        
        CgBeanPropertyInterceptor interceptor = new CgBeanPropertyInterceptor();
        BeanB bean = (BeanB) interceptor.newInstance( BeanB.class );
        interceptor.addPropertyChangeListener( listener );
        // Bean bean = (Bean) newInstance(Bean.class, listener);

        // bean.addPropertyChangeListener(listener);

        bean.setSampleProperty("TEST");
        bean.setSampleProperty("Tossed");
        bean.setSampleProperty("Turse");
        System.out.println(" value: " + bean.getSampleProperty() );
    }

}

