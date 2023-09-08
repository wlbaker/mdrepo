package idea.persistmanager.daq;

import java.awt.Color;

public class STP {
	float[] signal = new float[16];
	float[] unitHigh = new float[16];
	float[] unitLow = new float[16];
	float[] vHigh = new float[16];
	float[] vLow = new float[16];
	float[] precision = new float[16];
	float[] channel = new float[16];
	
	float[] fdevinfo = new float[9];
//	System.out.printf("* DEVICE ID: %f\n", stp.fdevinfo[0]);
//	System.out.printf("* Sample Rate: %f\n", stp.fdevinfo[1]);
//	System.out.printf("* ?Source Data: %f\n", stp.fdevinfo[2]);
//	System.out.printf("* ?Accessory: %f\n", stp.fdevinfo[3]);
//	System.out.printf("* ?Config/NRSE: %f\n", stp.fdevinfo[4]);
//	System.out.printf("* Seq No: %f\n", stp.fdevinfo[5]);
//	System.out.printf("* Data Set Size(sec): %f\n", stp.fdevinfo[6]);
//	System.out.printf("* Timed Save (sec): %f\n", stp.fdevinfo[7]);
//	System.out.printf("* Auto Save (sec): %f\n", stp.fdevinfo[8]);

	Color[] colorTable = new Color[16];
	float[] colorAssign = new float[19];
	float[] b1 = new float[32];
	float[] b2 = new float[32];
	float[] b3 = new float[32];
	float[] b4 = new float[32];
	float[] b5 = new float[32];
	float[] b6 = new float[32];
	float[] b7 = new float[32];
	float[] b8 = new float[16];

	public String[] labels = new String[49];
	public String[] config = new String[27];
	public String [] label_graph = new String[124];

	byte[] binaryAA;
	byte[] comsAA;
	
	float[] other_102 = new float[120 - 16 - 3];
	public int h4_102;
	public int h3;
	public int h5;
	public int h6;
	public byte skip;
	public byte[] ascii0;
	public byte[] ascii1;
	public byte[] ascii2;
}
