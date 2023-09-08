package idea.driver;

import static icuInterface.LoggingUtil.dumpConfiguration;
import static icuInterface.LoggingUtil.dumpSocketData;
import static icuInterface.LoggingUtil.getLoggingOutputStream;
import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.IntellivueConnection;
import idea.connections.NoConnection;
import idea.driver.intellivue.IntellivueDriver;
import idea.schema.rp.RpDevice;

import java.io.IOException;
import java.io.PrintStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class IntellivueUDPDriver extends IntellivueDriver {
	private static final String driverName = "monitor/Philips Intellivue Network";

	private DatagramSocket assoc_socket;

	private int dest_port;

	private InetAddress dest_addr;

	private Thread th;
	private long ts;

	private PrintStream dout;
	
	public static SocketDeviceConfiguration createConfigInstance() {
		SocketDeviceConfiguration conf = new SocketDeviceConfiguration(IntellivueUDPDriver.class);
		conf.setPort(24105);
		conf.setName(driverName);
		return conf;
	}

	public IntellivueUDPDriver(RpDevice conf) {
		super(conf);

		this.dout = getLoggingOutputStream(this.getClass());
		if (dout != null) {
			dumpConfiguration(dout, this);
		}

		ts = PlatformUtil.currentTimeMillis();

		initCaps();
	}

	private void initCaps() {
		DeviceCapabilities caps = getStaticCapabilities();
		caps.addConnection( new IntellivueConnection() );
		caps.setModels( new String [] { "MP5", "MP70"} );
	}

	@Override
	public void connect() throws IOException {

		if (th != null) {
			disconnect();
		}
		super.connect();
		
		String ip = conf.getConnectionValue();
		if( ip.startsWith("intellivue://")) {
			ip = ip.substring(13);
		}
		int colon = ip.indexOf(':');
		if( colon > 0 ) {
			ip = ip.substring(0, colon);
		}
		
		dest_port = 24105; // sconf.getPort();
		dest_addr = InetAddress.getByName(ip);
		assoc_socket = new DatagramSocket(); //

		Runnable r = new Runnable() {

			@Override
			public void run() {

				try {

					requestAssociation();
					for (;;) {
						waitForData2();
					}
				} catch (InterruptedException ex) {
					System.out.println("IntellivueUDPDriver: disconnecting");
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}

		};

		th = new Thread(r);
		th.start();
	}

	@Override
	public void disconnect() throws IOException {

		super.disconnect();
		if (assoc_socket != null) {

			log.error("requesting synch of disconnect");
			
			if (assoc_socket != null) {
				assoc_socket.close();
			}
			try {
				th.interrupt();
				// th.join();
			} catch (Exception e) {
				log.error("disconnecting", e);
			} finally {
				th = null;
			}
			log.error("got sync of disconnect");

			assoc_socket = null;
			setStatus( ConnectionStatus.NOT_CONNECTED);
		}

	}

	private void waitForData2() throws InterruptedException, IOException {

		// Create a DatagramPacket and do a receive
		byte buf[] = new byte[2048];
		DatagramPacket pack = new DatagramPacket(buf, buf.length);
		if (assoc_socket == null) {
			throw new InterruptedException();
		}
		assoc_socket.receive(pack);

		ByteBuffer bb = ByteBuffer.wrap(buf, pack.getOffset(), pack.getLength());
		if (dout != null) {
			dout.flush();
			dumpSocketData(dout, PlatformUtil.currentTimeMillis() - ts, bb.array(), pack.getLength());
		}

		parsePacket(bb.array(), bb.position(), bb.remaining());
	}


	@Override
	protected
	void send(ByteBuffer req) throws IOException {
		byte[] arr = req.array();
		DatagramPacket packet = new DatagramPacket(arr, req.position(), req.remaining());

		packet.setAddress(dest_addr);
		packet.setPort(dest_port);

		if (log.isDebugEnabled()) {
			log.debug("sending to: " + dest_addr + "/" + dest_port + " nbytes=" + req.remaining() + " from_local="
					+ assoc_socket.getLocalPort() + " starting POS=" + req.position());
		}
		assoc_socket.send(packet);

	}

}
