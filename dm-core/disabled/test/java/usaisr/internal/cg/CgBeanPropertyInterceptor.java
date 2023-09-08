/*
 * Created on May 16, 2006
 *
 * This is a pure CGLIB method of doing something which is mostly AOP.
 *  
 */
package idea.internal.cg;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

import net.sf.cglib.proxy.Enhancer;
import net.sf.cglib.proxy.MethodInterceptor;
import net.sf.cglib.proxy.MethodProxy;

public class CgBeanPropertyInterceptor implements MethodInterceptor {
    private PropertyChangeSupport propertySupport;

    public void addPropertyChangeListener(PropertyChangeListener listener) {

        propertySupport.addPropertyChangeListener(listener);

    }

    public void removePropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.removePropertyChangeListener(listener);
    }

    public Object newInstance(Class clazz ) {
        try {
            // BeanPropertyInterceptor interceptor = new BeanPropertyInterceptor();
            Enhancer e = new Enhancer();
            e.setSuperclass(clazz);
            e.setCallback(this);
            Object bean = e.create();
            propertySupport = new PropertyChangeSupport(bean);
            // interceptor.addPropertyChangeListener( listener );
            return bean;
        } catch (Throwable e) {
            e.printStackTrace();
            throw new Error(e.getMessage());
        }

    }

//    static final Class C[] = new Class[0];
//    static final Object emptyArgs[] = new Object[0];

    public Object intercept(Object obj, Method method, Object[] args, MethodProxy proxy) throws Throwable {
        Object retValFromSuper = null;
        String propertyName = null;
        
        String methodName = method.getName();
        
        if (methodName.startsWith("set") && args.length == 1 && method.getReturnType() == Void.TYPE) {
            char propName[] = methodName.substring("set".length()).toCharArray();
            propName[0] = Character.toLowerCase(propName[0]);
            propertyName = new String(propName);
        }
        
        if( propertyName != null ) {
            Object o = proxy;
            System.out.println( "need to call getter for: " + o );
        }

        if (!Modifier.isAbstract(method.getModifiers())) {
            // retValFromSuper = invocation.proceed();
            retValFromSuper = proxy.invokeSuper(obj, args);
        }

        if (propertyName != null) {
            System.out.println("***??  firing property change ***");
            propertySupport.firePropertyChange(propertyName, null, args[0]);
        }

        return retValFromSuper;
    }

}