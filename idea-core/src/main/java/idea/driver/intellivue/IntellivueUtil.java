package idea.driver.intellivue;

import java.io.PrintStream;
import java.nio.ByteBuffer;

public class IntellivueUtil {
	
	public static long parseAbsTimeStamp(ByteBuffer bb) {
		byte century = bb.get();
		byte year = bb.get();
		byte month = bb.get();
		byte day = bb.get();
		byte hour = bb.get();
		byte minute = bb.get();
		byte second = bb.get();
		byte sec_fractions = bb.get();

//		if (verbose > 2) {
//			System.out.println("abstime= " + year + "/" + month + "/" + day + " " + hour + ":" + minute + ":" + second
//					+ "." + sec_fractions);
//		}
		return 0;
	}
	
	public static float parsePhilipsFloat(ByteBuffer bb) {
		int v = bb.getInt();
		int sign = v & 0x00800000;
		int exp = v & 0xFF000000;
		int mantisa = v & 0x007FFFFF;
		sign >>= 23;
		exp >>= 24;
		if (sign == 1) {
			mantisa = -mantisa;
		}
		float value = (float) (mantisa * Math.pow(10, exp));

		return value;
	}



	public static void dumpBlob(PrintStream out, byte[] array, int len) {
		out.println("dumping packet");
		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 20 == 0)) {
				out.println();
			}

			int byt = array[i];
			if (byt < 0)
				byt += 256;
			out.print(Integer.toHexString(byt));
			if (byt > 0x20 && byt < 0x80) {
				out.print("(");
				out.print((char) byt);
				out.print(")");
			}
			out.print(" ");
		}
		out.println();

	}

}
