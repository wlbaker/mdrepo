package idea.discovery;

import gnu.io.CommPortIdentifier;
import com.fazecast.jSerialComm.SerialPort;
import icuInterface.PlatformUtil;
import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryAction;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.DiscoveryProvider;
import icuInterface.discovery.InfinityDiscoveryWorker;
import icuInterface.discovery.RxtxDiscoveryWorker;

import java.util.Arrays;
import java.util.Enumeration;
import java.util.LinkedList;
import java.util.List;

import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpDevice;

@Slf4j
public class TestRxtxDiscovery implements DiscoveryListener {

	public static void initSerialPorts(RxtxDiscoveryWorker discovery) {
		String[] requested_ports = null;
		String alphaPort = null;

		List<CommPortIdentifier> usable_ports = new LinkedList<CommPortIdentifier>();
		Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();
		while (portList.hasMoreElements()) {
			CommPortIdentifier portId = (CommPortIdentifier) portList.nextElement();
			if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				if (requested_ports != null) {
					int idx = Arrays.binarySearch(requested_ports, portId.getName());
					if (idx >= 0) {
						log.info("ADDING REQUEST SERIAL: ", portId.getName());
						usable_ports.add(portId);
					}
				} else if ("/dev/ttyS0".equals(portId.getName())) {
					log.info("SKIP SERIAL [console]: {}", portId.getName());
				} else if (alphaPort != null && alphaPort.equals(portId.getName())) {
					log.info("SKIP SERIAL [alpha]: {}", portId.getName());
				} else {
					log.info("ADDING SERIAL: {}", portId.getName());
					usable_ports.add(portId);
				}
			} else {
				log.warn("Skipping port: {}", portId);
			}
		}

		CommPortIdentifier [] arr = new CommPortIdentifier[ usable_ports.size() ];
		usable_ports.toArray( arr );
		discovery.setPorts(arr);
	}

	/**
	 * @param args
	 * @throws InterruptedException
	 */
	public static void main(String[] args) throws InterruptedException {

		try {
			String os = System.getProperty("os.name");
			if ("Linux".equals(os)) {
				// auto-loading
				log.info("no autoload of rxtx, but you may need: -Djava.library.path=/usr/lib64/rxtx");
			} else {
				PlatformUtil.loadLibrary("rxtxSerial");
			}
			log.info("---serial library loaded.");
		} catch (UnsatisfiedLinkError e) {
			log.error("Could not load rxtx module", e);
		}

		TestRxtxDiscovery tester = new TestRxtxDiscovery();

		InfinityDiscoveryWorker inf_worker = new InfinityDiscoveryWorker();
		RpDevice conf = null;
		inf_worker.setCreateDriverOnDiscover(true, conf  );
		DiscoveryProvider discovery = inf_worker;
		// discovery = new SerialDiscoveryWorker( );
		// discovery = new IntellivueDiscoveryWorker();


		discovery.addListener(tester);

		// initSerialPorts( discovery );
		// System.out.println( "adding a single device");
		// SerialDeviceConfiguration conf = AlphaDisplay.createConfigInstance();
		// conf.setPort("COM1");
		// try {
		// discovery.addDevice( conf );
		// } catch (IOException e) {
		// // TODO Auto-generated catch block
		// e.printStackTrace();
		// }

		System.out.println("discovery startup");
		discovery.start();

		Thread.sleep(1200000);

		System.out.println("discovery shutdown");
		discovery.stop();
	}

	@Override
	public void discover(DiscoveryAction action, DeviceRecord dev) {
		switch( action ) {
		case UPDATE:
			/*
				SerialPort port = dev.getSerialPort();

				int stat = 0;
				if (port.isCD())
					stat += 4;
				if (port.isCTS())
					stat += 2;
				if (port.isDSR())
					stat += 1;

				System.out.println("update DEVICE: " + port + " stat=" + stat);

			break;
			*/
			default:
				System.out.println(action + " DEVICE: " + dev);
		}
		
	}

	@Override
	public void error(DeviceRecord dev, String message, Exception s) {
		// TODO Auto-generated method stub
		System.err.println(dev + ": " + message + ": " + s );
	}

}
