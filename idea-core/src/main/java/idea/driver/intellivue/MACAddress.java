package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class MACAddress {

	public static byte[] parse(ByteBuffer bb) {
		byte [] mac = new byte[6];
		for( int i = 0; i < 6; i++ ) {
			mac[i] = bb.get();
		}
		return mac;
	}
	
	public static String toString( byte [] mac ) {
		StringBuffer s = new StringBuffer();
		
		boolean first = true;
		for( byte b : mac ) {
			if( first ) {
				first = false;
			} else {
				s.append(":");
			}
			int ch = b;
			if( ch < 0) {
				ch += 256;
			}
			if( ch < 16 ) {
				s.append("0");
			}
			s.append( Integer.toHexString(ch));
		}
		
		return s.toString();
	}

}
