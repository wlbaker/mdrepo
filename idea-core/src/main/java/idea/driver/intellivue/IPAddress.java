package idea.driver.intellivue;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;

public class IPAddress {

	public static InetAddress parse(ByteBuffer bb) {
		byte[] ip4 = new byte[4];
		for (int i = 0; i < 4; i++) {
			ip4[i] = bb.get();
		}

		InetAddress addr = null;
		try {
			addr = InetAddress.getByAddress(ip4);
		} catch (UnknownHostException e) {
			e.printStackTrace();  // should not happen...but report and ignore if it does
		}
		return addr;
	}

}
