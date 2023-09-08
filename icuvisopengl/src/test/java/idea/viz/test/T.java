package idea.viz.test;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import idea.driver.intellivue.IntellivueUtil;

public class T {

	public static void main(String args[]) {

		long l1 = 4278185984L;
		long l2 = 4244676603L;
		short s1 = 0;
		short s2 = 16383;
		
		int i00 = (int)l1;
		int i01 = (int)l2;

		System.out.println("i00=" + i00);
		System.out.println("i01=" + i01);
		
		ByteOrder[] ords = new ByteOrder[] { ByteOrder.LITTLE_ENDIAN, ByteOrder.BIG_ENDIAN };
		for (ByteOrder ord : ords) {
			ByteBuffer bb = ByteBuffer.allocate(20);
			bb.order(ord);
			bb.putInt(i00);
			bb.putInt(i01);
			bb.putShort(s1);
			bb.putShort(s2);

			byte[] arr = bb.array();

			System.out.print(ord);
			System.out.print(": ");
			for (byte b : arr) {
				int ibyt = b;
				if (ibyt < 0) {
					ibyt += 256;
				}
				String hex = Integer.toHexString(ibyt);
				if (hex.length() < 2) {
					hex = "0" + hex;
				}
				System.out.print(hex);
				System.out.print(" ");
			}
			System.out.println();

			if (ord == ByteOrder.LITTLE_ENDIAN) {

				// reread as big endian
				ByteBuffer bb2 = ByteBuffer.wrap(arr);
				float lower_absolute_value = IntellivueUtil.parsePhilipsFloat(bb2);
				float upper_absolute_value = IntellivueUtil.parsePhilipsFloat(bb2);
				short lower_scaled_value = bb2.getShort();
				short upper_scaled_value = bb2.getShort();

				System.out.println("  lower_absolute_value: " + lower_absolute_value);
				System.out.println("  upper_absolute_value: " + upper_absolute_value);
				System.out.println("    lower_scaled_value: " + lower_scaled_value);
				System.out.println("    upper_scaled_value: " + upper_scaled_value);
			} else if (ord == ByteOrder.BIG_ENDIAN) {
				// reread as big endian
				ByteBuffer bb2 = ByteBuffer.wrap(arr);
				float lower_absolute_value = IntellivueUtil.parsePhilipsFloat(bb2);
				float upper_absolute_value = IntellivueUtil.parsePhilipsFloat(bb2);
				short lower_scaled_value = bb2.getShort();
				short upper_scaled_value = bb2.getShort();

				System.out.println("  lower_absolute_value: " + lower_absolute_value);
				System.out.println("  upper_absolute_value: " + upper_absolute_value);
				System.out.println("    lower_scaled_value: " + lower_scaled_value);
				System.out.println("    upper_scaled_value: " + upper_scaled_value);
			}

		}

	}
}