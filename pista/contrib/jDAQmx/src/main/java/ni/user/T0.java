package ni.user;

public class T0 {

	public static native void doT0();
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println( "library: " + System.getProperty("java.library.path"));
		System.loadLibrary("jDAQmx");
		System.out.println( "t0 done");
		// doT0();

	}

}
