package idea.internal.cg;

import java.lang.reflect.Method;
import java.util.Arrays;

import lombok.Data;
import net.sf.cglib.proxy.Enhancer;
import net.sf.cglib.proxy.MethodInterceptor;
import net.sf.cglib.proxy.MethodProxy;

@Data
class C1 {
	int d;
	int e;

}

interface Wrapper<T> {
	T getSource();
}

abstract class SimpleWrapper extends C1 implements Wrapper<C1> {
	String prophandler = "prophandler";
//	@Override
//	public int getD() {
//		System.out.println("wrapped [" + getSource().getD() + "]");
//		return d;
//	}
}


public class Test4Wrapper {
	public static <S, W> W createWrapper(final S source,
			final Class<W> wrapperClass) {
		Enhancer enhancer = new Enhancer();
		enhancer.setSuperclass(wrapperClass);
		enhancer.setInterfaces(wrapperClass.getInterfaces());
		enhancer.setCallback(new MethodInterceptor() {
			public Object intercept(Object proxy, Method method, Object[] args,
					MethodProxy methodProxy) throws Throwable {
				if (method.getName().startsWith("set") ) {
//						&& C1.class.equals(method.getDeclaringClass())) {
					System.out.println("setter: " + method.getName());
					// return source;
				}
				if (Arrays.asList(wrapperClass.getDeclaredMethods()).contains(
						method)) {
					Object o= methodProxy.invokeSuper(proxy, args);
					return o;

				}
				Object o = methodProxy.invoke(source, args);
				return o;
			}
		});
		return (W) enhancer.create();
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		C1 c1 = new C1();
		c1.setD( 99 );

		SimpleWrapper wrapper = createWrapper(c1, SimpleWrapper.class);

		System.out.println( "get0=" + wrapper.getD() );
		wrapper.setD(2);
		wrapper.getD();
		System.out.println( "get1=" + wrapper.getD() );
		System.out.println( "get1=" + c1.getD() );
	}
}
