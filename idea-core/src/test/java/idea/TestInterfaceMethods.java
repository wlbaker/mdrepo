package idea;

interface Base {
	void one();
	
	default void two() {
		System.out.println("base-two");
	}
	
//	public static String name() {
//		return "Base";
//	}
}

class A implements Base {

	@Override
	public void one() {
		System.out.println("a=1");
	}

	public void two() {
		System.out.println("a-two");
	}
	
	public static String name() {
		return "I-am-A";
	}
	
}

class B implements Base {

	@Override
	public void one() {
		System.out.println("b=1");
	}
	
	public static String name() {
		return "I-am-B";
	}
	
}

public class TestInterfaceMethods {
	static public void main( String [] args ) {
		Base x = new A();
		Base y = new B();
		
		x.one();
		x.two();
		
		y.one();
		y.two();
		
		
		System.out.println("x.name()=" + A.name() );
		
	}
}
