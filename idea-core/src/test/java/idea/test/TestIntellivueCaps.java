package idea.test;

import icuInterface.ConnectionStatus;
import icuInterface.LoggingUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.driver.IntellivueUDPDriver;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.model.dev.Intellivue_Measurements;
import idea.schema.rp.RpMetric;

import java.io.IOException;

public class TestIntellivueCaps extends IntellivueUDPDriver implements StreamConsumer {

	public TestIntellivueCaps(DeviceConfiguration conf) {
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
			DeviceCapabilities caps = (DeviceCapabilities) ((CapabilitiesEvent)item).getCapabilities();
			LoggingUtil.dumpCapabilities(System.out, 0, caps);
				// dev.setConfiguration( caps );
		} else if ( sid == StreamID.MEASUREMENT) {
			// NumericsEvent ne = (NumericsEvent)event;
			LoggingUtil.dumpEvent(System.out, 0,jobId, src, sid, item);
		} else {
			System.out.println("...[ignored]" );
		}
		
	}

	public static void main(String[] args) throws IOException, InterruptedException {

		Intellivue_Measurements m = new Intellivue_Measurements();
		RpMetric[] mm1 = IntfUtil.getMetrics(Intellivue_Measurements.class);
		RpMetric[] mm2 = IntfUtil.getMetrics (m);
		if( mm1 == null || mm2 == null ) {
			System.err.println("could not get metrics fields: " + mm1 + " or " + mm2 );
			return;
		}
		SocketDeviceConfiguration conf = IntellivueUDPDriver.createConfigInstance();
		conf.setHost("192.168.50.51");

		TestIntellivueCaps t = new TestIntellivueCaps( conf );

		t.addStreamListener(null, t);
		t.connect();

		for (;;) {
			Thread.sleep(1000);
			t.tick();

			System.out.print(".");
		}
	}

}
