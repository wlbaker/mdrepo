package idea.test;

import icuInterface.ConnectionStatus;
import icuInterface.LoggingUtil;
import icuInterface.PlatformUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.driver.IntellivueSerialDriver;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

import java.io.IOException;

public class TestIntellivueSerialCaps extends IntellivueSerialDriver implements StreamConsumer {

	public TestIntellivueSerialCaps(DeviceConfiguration conf) {
		super(conf);
	}

	@Override
	public void streamEvent(int jobId, StreamProducer src, StreamID sid, PersistentItem item) {
		
		System.out.println("event: " + item);

		if( sid == StreamID.CONNECTION ) {
			ConnectionItem ce = (ConnectionItem)item;
			if( ce.getStatus() == ConnectionStatus.CONNECTED ) {
				try {
					requestCapabilities();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		} else if (sid == StreamID.CAPABILITIES) {
			DeviceConfiguration caps = ((CapabilitiesEvent)item).getCapabilities();
			LoggingUtil.dumpCapabilities(System.out, 0, (DeviceCapabilities) caps);
				// dev.setConfiguration( caps );
		} else if ( sid == StreamID.MEASUREMENT) {
			// NumericsEvent ne = (NumericsEvent)event;
			LoggingUtil.dumpEvent(System.out, 0, jobId, src, sid, item);
		} else {
			System.out.println("...[ignored]" );
		}
		
	}

	public static void main(String[] args) throws IOException, InterruptedException {

		PlatformUtil.loadLibrary("rxtxSerial");
		
		SerialDeviceConfiguration conf = IntellivueSerialDriver.createConfigInstance();
		conf.setPort("COM1");

		TestIntellivueSerialCaps t = new TestIntellivueSerialCaps( conf );

		t.addStreamListener(null, t);
		t.connect();

		for (int idx = 1;;idx++) {
			Thread.sleep(1000);
			t.tick();

			System.out.print(".");
			
			if( idx % 10 == 0 ) {
				t.requestCapabilities();
			}
		}
	}

}
