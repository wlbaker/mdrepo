package idea.discovery;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.UnknownHostException;

import idea.driver.InfinityDriver;

public class ZZTestDragerListener {

	public final static int disc_port = 2150;
	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {

		byte buf[] = new byte[2048];

		// String group = "224.0.1.105";
		String group = "224.127.1.255";

		System.out.println("created socket");
		// InetAddress me = InetAddress.getByName("192.168.50.105");
		// InetAddress me = InetAddress.getByName("192.168.50.10");
		
		// MulticastSocket s = new MulticastSocket(InfinityDriver.port);
		MulticastSocket s = new MulticastSocket(disc_port);

		System.out.println("creatin packet");
		DatagramPacket pack = new DatagramPacket(buf, buf.length);

		try {
			// join the multicast group
			// byte [] tmp = new byte[4];
			InetAddress group_inet = InetAddress.getByName(group);
			s.joinGroup(group_inet);
			// Now the socket is set up and we are ready to receive packets
		} catch (UnknownHostException skipme) {
			throw (skipme); // rethrow
		} catch (Exception skipme) {
			System.err.println("WARNING: might not get multicast for address: " + group);
		}

		for (;;) {
			System.out.println("receiving packet");
			s.receive(pack);

			System.out.println("checking address");
			InetAddress addr = pack.getAddress();

			System.out.println("addr: " + addr);
		}
	}

}
