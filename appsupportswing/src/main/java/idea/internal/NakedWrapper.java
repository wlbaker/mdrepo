package idea.internal;

/*
 * Now, you may be wondering, why have a wrapper here at all?  Well, getNakedWrapper() is invoked through a CGLIB
 * altered object.  If this function were to return the target object directly, the invoke interceptor would
 * recognize it and deliberately return the proxy instead.  You can imagine that this would be necessary
 * sometimes for the aspect code to work correctly, but the getTarget() method is not public, so there is no
 * clear way to get the target out of the CGLIB generated code.  The simple workaround is to use a wrapper, so
 * the CGLIB code won't try to substitute the proxy object for the target object when it is actually desired
 * to get the target object.
 * 
 * In my openion, getTarget() should be publically accessible.
 * 
 * All this wrapper stuff could probably be hidden in a static function.
 * 
 */
public class NakedWrapper {

	private Object o;
	
	public NakedWrapper( Object o ) {
		this.o = o;
	}
	
	public Object getObject() {
		return o;
	}
}
