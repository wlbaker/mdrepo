package idea.internal.cg;

import net.sf.cglib.proxy.Enhancer;
import net.sf.cglib.proxy.NoOp;

public class Test6cgProxy {
	 public static Object createProxy(Class targetClass) {
	        Enhancer enhancer = new Enhancer();
	        enhancer.setSuperclass(targetClass);
	        enhancer.setCallback(NoOp.INSTANCE);
	        return enhancer.create();
	   }

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		Object c2 = createProxy( C1.class );
		System.out.println( "c2=" + c2.getClass() );
		System.out.println( "c2 is c1 ?= " + (c2 instanceof C1) );
	}

}
