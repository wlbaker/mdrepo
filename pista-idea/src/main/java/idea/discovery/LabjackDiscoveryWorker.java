package idea.discovery;

import java.io.IOException;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.DiscoveryProvider;
import icuInterface.events.CapabilitiesEvent;
import idea.conf.DeviceConfiguration;
import idea.driver.IntellivueUDPDriver;
import idea.driver.LabJackDriver;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpDevice;

@Slf4j
public class LabjackDiscoveryWorker extends DiscoveryProvider implements StreamConsumer {
	static LabJackDriver device;
	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();

	private void startDiscovery() {
		// running = true;
		//
		// Runnable r = new Runnable() {
		//
		// @Override
		// public void run() {
		//
		// DatagramSocket s = null;
		// try {
		// s = new DatagramSocket(discover_port);
		// // s = new DatagramSocket(discover_port, addr );
		// while (running) {
		// waitForData(s);
		// }
		// } catch (IOException e) {
		// // TODO Auto-generated catch block
		// e.printStackTrace();
		// }
		// s.close();
		//
		// }
		//
		// };
		//
		// Thread th = new Thread(r);
		// th.start();
	}

	@Override
	public void start() {
		device = new LabJackDriver(null);
		device.addStreamListener(StreamID.CAPABILITIES, this);

		startDiscovery();

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		CapabilitiesEvent e = (CapabilitiesEvent) item;
		DeviceConfiguration caps = e.getCapabilities();
		String ip = caps.getParam("ip");
		String port = caps.getParam("port");
		System.out.println("got discovery event: " + ip + "/" + port);

		SocketDeviceConfiguration conf = IntellivueUDPDriver.createConfigInstance();
		conf.setHost(ip);
		conf.setPort(Integer.parseInt(port));
		IntellivueUDPDriver d = new IntellivueUDPDriver(conf);
		try {
			d.connect();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		System.out.println("connected!");
	}

	@Override
	public DeviceRecord getDevice(String devId) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public DeviceRecord[] getDevices() {
		return LabJackDriver.getDevices();
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
		log.error("FIXME: getStaticCapabilites() stub");
		return null;
	}

	public static void main(String[] args) throws InterruptedException {

		System.out.println("waiting for discovery device");
		LabjackDiscoveryWorker service = new LabjackDiscoveryWorker();
		service.start();

		for (int i = 0; i < 20; i++) {
			Thread.sleep(1000);
			Date now = new Date();
			DeviceRecord[] devs = service.getDevices();
			if( devs == null ) {
				System.out.println(now + " NONE");
				continue;
			}
			System.out.println(now + " " + devs.length);
			for( DeviceRecord dev : devs ) {
				System.out.print("* ");
				System.out.print( dev.getFullName() );
				System.out.print(" ");
				System.out.print( dev.getUniqueID() );
				System.out.println();
			}
		}
		
		System.exit(0);

	}

}
