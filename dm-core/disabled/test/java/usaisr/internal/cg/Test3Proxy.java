package idea.internal.cg;

import lombok.Data;

import org.apache.commons.proxy.Interceptor;
import org.apache.commons.proxy.Invocation;
import org.apache.commons.proxy.ObjectProvider;
import org.apache.commons.proxy.ProxyFactory;

@Data
class CC1 {
	int d;
	
}

class MyIn implements Interceptor {

	@Override
	public Object intercept(Invocation arg0) throws Throwable {
		System.out.println("intercept: " + arg0 );
		return arg0;
	}
	
}



public class Test3Proxy {

	static CC1 c1;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		MyIn myIn = new MyIn();
		ProxyFactory f = new ProxyFactory();

		c1 = new CC1();
		c1.setD( 1 );
		
		ObjectProvider wrapper = new ObjectProvider( ) {

			@Override
			public Object getObject() {
				return c1;
			}
			
		};
		
		// f.createDelegatorProxy(c1, new Class [] { C1.class } );
		f.createDelegatorProxy( wrapper, new Class [] { C1.class }) ;
		c1.setD( 2 );
	}

}
