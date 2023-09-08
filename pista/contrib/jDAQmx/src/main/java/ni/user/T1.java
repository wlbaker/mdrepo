package ni.user;

public class T1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		try {
			System.out.println("hello world...loading lib");
			System.loadLibrary("jDAQmx");

//			System.load("/home/bbaker/workspace/nijava/jdaqmx-c/build/rhel/daqmxbase/libjDAQmxBase.so");
			// System.loadLibrary("jDAQmxBase");
			System.out.println("loaded....now contacqvoltagebase");

			ContAcqVoltageBase.main(args);

			System.out.println("done");
		} catch (Exception e) {
			e.printStackTrace();
			System.err.println( "std err");
		} catch (UnsatisfiedLinkError e) {
			e.printStackTrace();
			System.err.println( "link err");
		}
	}

}
