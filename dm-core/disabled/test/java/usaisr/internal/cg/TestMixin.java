package idea.internal.cg;

import java.lang.reflect.Method;

import net.sf.cglib.proxy.Mixin;

class Class1 {
	public int method1() {
		return 1;
	}

}

class Class2 {
	public int method2() {
		return 2;
	}

}

public class TestMixin {
	public static void main(String [] args) {
		Mixin mixin = Mixin.createBean(new Object[] { new Class1(), new Class2() });
		Object o = mixin;
		
		System.out.println( "mixin is c1 ?= " + (o instanceof Class1) );
		System.out.println( "mixin is c2 ?= " + (o instanceof Class2) );
		System.out.println( "o class= " + o.getClass().getCanonicalName() );
		
		Method[] methods = o.getClass().getMethods();
		for( Method method : methods ) {
			System.out.println("method=" + method.getName());
		}

	}

}
