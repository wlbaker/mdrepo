package idea;

import icuInterface.ConnectionStatus;
import icuInterface.LoggingUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceConfiguration;
import idea.driver.IntellivueUDPDriver;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;

import java.io.IOException;

public class TestIntellivue implements StreamConsumer {

	IntellivueUDPDriver driver;
	boolean configured = false;
	private SocketDeviceConfiguration conf;
	
	@Override
	public void streamEvent(int jobId, StreamProducer source, StreamID sid, PersistentItem item) {
		System.out.println("event: " + item);

		if( sid == StreamID.CONNECTION ) {
			ConnectionItem ce = (ConnectionItem)item;
			if( ce.getStatus() == ConnectionStatus.CONNECTED ) {
				try {
					driver.requestCapabilities();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		} else if (sid == StreamID.CAPABILITIES) {
			DeviceConfiguration caps = ((CapabilitiesEvent)item).getCapabilities();
			
			// LoggingUtil.dumpCapabilities(System.out, 0, caps);
			RpStream s = caps.getStream(StreamID.MEASUREMENT);
			if( s != null && !configured ) {
				LoggingUtil.dumpCapabilities(System.out, 0, caps);
				
				RpMetric hr = RpUtil.getMetricFromStream(s, "147842");  // HR
				RpMetric rr = RpUtil.getMetricFromStream(s, "151562");  // RR
				if( hr != null && rr != null ) {
					
					try {
						// driver.disconnect();
						driver.setConfiguration( caps );
						// driver.connect();
						configured = true;
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		} else if ( sid == StreamID.MEASUREMENT) {
			LoggingUtil.dumpEvent(System.out, item.getTime(), jobId, source, sid,item);
		} else {
			System.out.println("ignoring message: " + sid );
		}
		
	}
	
	private void run() throws IOException, InterruptedException {
		conf = IntellivueUDPDriver.createConfigInstance();
		conf.setHost("192.168.50.51");		
		driver = new IntellivueUDPDriver( conf );
		
		// driver.addStreamListener(StreamID.MEASUREMENT, prog);
		driver.addStreamListener(null, this);
		
		driver.connect();
		
		for( ;; ) {
			Thread.sleep(1000);
			driver.tick();

			if( driver.getStatus() == ConnectionStatus.NOT_CONNECTED ) {
				break;
			}
		}
		
		driver.disconnect();
	}
	
	public static void main(String[] args) throws InterruptedException, IOException {
		
		TestIntellivue prog = new TestIntellivue();
		
		prog.run();
		
	}



}
