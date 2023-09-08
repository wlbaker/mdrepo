package idea.replay;

/*
 * Notes for Android:
 * <uses-permission android:name="android.permission.CHANGE_WIFI_MULTICAST_STATE" />
 * <uses-permission android:name="android.permission.INTERNET"/>
 * <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>
 * <uses-permission android:name="android.permission.ACCESS_WIFI_STATE"/>
 * 
 * See: http://stackoverflow.com/questions/15807733/udp-multicasting-from-mobile-to-pc
 */
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.zip.GZIPInputStream;

import icuInterface.LoggingUtil;

public class InfinityReplay {

	DatagramSocket socket;
	private InetAddress address;
	private int port;

	public void replay(String fileName) throws IOException, InterruptedException {
		File f = new File(fileName);

		FileInputStream fin = new FileInputStream(f);
		GZIPInputStream is = new GZIPInputStream(fin);

		BufferedReader stream = new BufferedReader(new InputStreamReader(is));

		// Start timing
		String line;
		long last_dt = 0;
		boolean trigger = false;
		while ((line = stream.readLine()) != null) {
			if (line.startsWith("# [socket]")) {
				int idx = line.indexOf("dt=");
				idx += 3;
				int end = line.indexOf(' ', idx);
				long dt = Long.parseLong(line.substring(idx, end));
				System.out.println("dt: " + dt + " from: " + line);
				long millis = dt - last_dt;
				Thread.sleep(millis);
				last_dt = dt;
				trigger = true;
			} else if (trigger) {
				System.out.println("decode: " + line);
				byte[] bb = LoggingUtil.parse(line);
				trigger = false;

				DatagramPacket out = new DatagramPacket(bb, bb.length, address, port);
				socket.send(out);

			}
		}

		stream.close();
		// bis.close();
		is.close();
		fin.close();
	}

	private void initServer(String host, int port) throws IOException {
		socket = new DatagramSocket();
		address = InetAddress.getByName(host);
		this.port = port;
	}
	
	private void close() {
		socket.close();
	}

	public static void main(String[] args) throws IOException, InterruptedException {
		String fileName = "doc/traces/idea.driver.InfinityDriver-2017-03-07.log.gz";

		InfinityReplay replayer = new InfinityReplay();

		replayer.initServer("224.0.1.140", 2050);
		replayer.replay(fileName);
		replayer.close();

	}


}
