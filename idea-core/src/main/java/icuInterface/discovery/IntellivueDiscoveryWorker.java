package icuInterface.discovery;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.driver.IntellivueUDPDriver;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.model.dev.Intellivue_Demographics;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.LinkedList;
import java.util.List;

import javax.sql.ConnectionEvent;

import lombok.Getter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class IntellivueDiscoveryWorker extends DiscoveryProvider implements StreamConsumer {
	static IntellivueUDPDriver driver;

	static int discover_port = 24005;

	private static boolean running;
	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();

	/*
	 * DiscoveryWorkers listen for their device signature.
	 * 
	 * Since the DiscoveryWorker opens a driver, it needs to configure the
	 * driver. It configures the connection using the "ref" configuration.
	 * 
	 * All this is a problem for intellivue, since it can only handle ONE
	 * connection!
	 * 
	 */
	public IntellivueDiscoveryWorker() {
	}

	private void startDiscovery() {
		running = true;

		Runnable r = new Runnable() {

			@Override
			public void run() {

				DatagramSocket s = null;
				try {
					s = new DatagramSocket(discover_port);
					// s = new DatagramSocket(discover_port, addr );
					while (running) {
						waitForData(s);
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				s.close();

			}

		};

		Thread th = new Thread(r);
		th.start();
	}

	private void waitForData(DatagramSocket s) throws IOException {
		// Create a DatagramPacket and do a receive
		byte buf[] = new byte[1024];
		DatagramPacket pack = new DatagramPacket(buf, buf.length);

		s.receive(pack);

		if (log.isDebugEnabled()) {
			dumpDiscoverPacket(pack);
		}

		byte[] data = pack.getData();
		driver.parsePacket(data, 0, data.length);
	}

	private void dumpDiscoverPacket(DatagramPacket pack) {
		System.out.println("(" + pack.getAddress() + ") :");
		int idx = 0;
		for (byte b : pack.getData()) {
			if (idx == 0) {
				System.out.print("      ");
			}
			int ch = b;
			if (ch < 0) {
				ch += 256;
			}
			System.out.print(" ");
			if (ch < 16) {
				System.out.print("0");
			}
			System.out.print(Integer.toHexString(ch));
			idx++;
			if (idx > 40) {
				System.out.println();
				idx = 0;
			}
		}
		System.out.println();
	}

	@Override
	public void start() {
		driver = new IntellivueUDPDriver(null);
		driver.addStreamListener(StreamID.CAPABILITIES, this);
		driver.addStreamListener(StreamID.CONNECTION, this);

		startDiscovery();

	}

	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (sid == StreamID.CAPABILITIES) {
			CapabilitiesEvent e = (CapabilitiesEvent) item;
			DeviceConfiguration caps = e.getCapabilities();

			DeviceRecord rec = getDevice(caps.getConnectionValue());
			if (rec == null) {
				capabilitiesEvent(caps);
			} else {
				log.error("ignoring duplicate device: " + rec);
			}
		} else if (sid == StreamID.CONNECTION) {
			ConnectionItem it = (ConnectionItem) item;
			DeviceRecord rec = getDeviceFromDriver(source);
			if (rec == null) {
				log.error("did not find device for connection: {}", source);
			}
			connectionEvent(rec, it);
		} else if (sid == StreamID.DDDEMOGRAPHICS) {
			Intellivue_Demographics demog = (Intellivue_Demographics) item;
			DeviceRecord rec = getDeviceFromDriver(source);
			if (rec == null) {
				log.error("did not find device for demographics update: {}", source);
			} else {
				rec.setFullName( demog.getName() );
				fireDiscoverEvent(DiscoveryAction.UPDATE, rec);
			}
		} else {
			log.error("DISCOVERY: Unexpected event: " + sid);
		}
	}

	public void connectionEvent(DeviceRecord rec, ConnectionItem item) {
		System.out.println("got connevent: " + item);
		if (item.getStatus() == ConnectionStatus.NOT_CONNECTED) {
			remove(rec);
		}
	}

	public void capabilitiesEvent(DeviceConfiguration caps) {
		System.out.println("got discovery event from discovery driver: " + caps.getConnectionValue());

		// SocketDeviceConfiguration conf = default_conf;  IntellivueUDPDriver.createConfigInstance();
		RpDevice conf = new RpDevice();
		conf.setDeviceClass(caps.getDeviceClass());
		conf.setName(caps.getName());
		conf.setConnectionType(caps.getConnectionType());
		conf.setConnectionValue(caps.getConnectionValue());
		
		RpDevice ref = (RpDevice) getDefaultConfig();
		if (ref != null) {
			StreamID[] sids = new StreamID[] { StreamID.WAVEFORM, StreamID.MEASUREMENT, StreamID.DDDEMOGRAPHICS };
			for (StreamID sid : sids) {
				
				RpStream s = RpUtil.getStream(ref, sid);
				if (s != null) {
					conf.getStreams().add(s);
				}
			}
		}

		IntellivueUDPDriver d = new IntellivueUDPDriver(conf);
		d.addStreamListener(StreamID.CONNECTION, this);
		d.addStreamListener(StreamID.DDDEMOGRAPHICS, this);

		try {
			d.connect();
			System.out.println("connected!");

			DeviceRecord rec = new DeviceRecord();
			rec.setFullName(caps.getName());
			rec.setDriver(d);

			addDevice(rec); // fires discovery event automatically
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	@Override
	public void stop() {
		// TODO Auto-generated method stub

	}

	@Override
	public StreamProducer addDevice(RpDevice rpdev) throws IOException {
		log.error("FIXME: found device...build driver? " + rpdev);
		return null;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		return super.getDefaultConfig();
	}

}
