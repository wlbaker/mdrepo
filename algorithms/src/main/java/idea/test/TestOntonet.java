package idea.test;

import idea.analysis.Ontonet;

import com.sun.jna.Native;

public class TestOntonet {

	private static String projectDir = "c:\\opt\\workspace\\chaktaw\\algorithms";
	private static String libraryFile = projectDir + "\\lib\\win32\\ontonet_dll";
	private static String licenseFile = "c:\\opt\\tools\\ontomed2\\license_2.dat";
	
	static String toOntonixFile = projectDir + "\\ref\\validation\\Libro1_.txt"; // csv";
	static String fromOntonixFile = "c:\\tmp\\ontonet_out.out";

	public static void main(String[] args) {
		Ontonet ontonet = (Ontonet) Native.loadLibrary(libraryFile, Ontonet.class);
		boolean tf = ontonet.initLicense(licenseFile);
		
		System.out.println("initLicense: " + tf);
		String labels = "";
//		for( int i =0; i < 20; i++ ) {
//			StringBuffer seg = new StringBuffer();
//			if( i != 0 ) {
//				seg.append(",");
//			}
//			seg.append((char)('A' + i));
//			labels = labels + seg;
//		}
		byte cal = ontonet.calculate(toOntonixFile, labels);
		tf = ontonet.writeTXT(toOntonixFile, labels, fromOntonixFile);
		
		System.out.println("RESULTS calc: " + cal + " writeObf: " + tf);

	}

}
