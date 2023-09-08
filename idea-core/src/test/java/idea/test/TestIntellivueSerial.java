package idea.test;

import icuInterface.ConnectionStatus;
import icuInterface.LoggingUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceConfiguration;
import idea.driver.IntellivueUDPDriver;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

import java.io.IOException;

public class TestIntellivueSerial implements StreamConsumer {

	private static IntellivueUDPDriver dev;

	@Override
	public void streamEvent(int jobId, StreamProducer src, StreamID sid, PersistentItem item) {
		
		System.out.println("event: " + item);

		if( sid == StreamID.CONNECTION ) {
			ConnectionItem ce = (ConnectionItem)item;
			if( ce.getStatus() == ConnectionStatus.CONNECTED ) {
				try {
					dev.requestCapabilities();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		} else if (sid == StreamID.CAPABILITIES) {
			DeviceConfiguration caps = ((CapabilitiesEvent)item).getCapabilities();
			try {
				// dev.disconnect();
				dev.setConfiguration( caps );
				// dev.connect();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if ( sid == StreamID.MEASUREMENT) {
			// NumericsEvent ne = (NumericsEvent)event;
			LoggingUtil.dumpEvent(System.out, 0,jobId, src, sid, item);
		} else {
			System.out.println("...[ignored]" );
		}
		
	}

	public static void main(String[] args) throws IOException, InterruptedException {

		TestIntellivueSerial t = new TestIntellivueSerial();

		SocketDeviceConfiguration conf = IntellivueUDPDriver.createConfigInstance();
		conf.setHost("192.168.50.51");

		dev = new IntellivueUDPDriver(conf);
		dev.addStreamListener(null, t);
		dev.connect();
		dev.requestCapabilities();

		for (;;) {
			Thread.sleep(1000);
			dev.tick();

			System.out.print(".");
		}
	}

}
