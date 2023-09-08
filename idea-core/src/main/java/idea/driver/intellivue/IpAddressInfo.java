package idea.driver.intellivue;

import java.net.InetAddress;
import java.nio.ByteBuffer;

public class IpAddressInfo {
	byte[] mac;
	InetAddress addr;
	InetAddress subnet_mask;
	

	public static IpAddressInfo parse(ByteBuffer bb) {
		IpAddressInfo info = new IpAddressInfo();
		info.mac = MACAddress.parse(bb);
		info.addr = IPAddress.parse(bb);
		info.subnet_mask = IPAddress.parse( bb );
		
		return info;
	}


	public InetAddress getAddress() {
		return addr;
	}

}
