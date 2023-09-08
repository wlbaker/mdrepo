package icuInterface.adapters;

import java.io.IOException;
import java.util.List;

import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.SecurityEvent;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class AATest implements StreamConsumer {

	private ASTMDriver idea;

	private final static int JOB_ID = 1;

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid,
			PersistentItem item) {
		System.out.println("Got event: " + item);

		if (sid == StreamID.SECURITY) {
			SecurityEvent sec_event = (SecurityEvent) item;
			if (sec_event.isAccept()) {
				System.out.println("LOGIN SUCCESSFUL");
				try {
					idea.requestCapabilities();
				} catch (IOException e) {
					log.error("request caps failed", e);
				}
			} else {
				System.out.println("FAILURE TO LOGIN");
			}
		}
		if (sid == StreamID.WAVEFORM) {

			System.out.println("got waveforms: " + item);
		} else if (sid == StreamID.CAPABILITIES) {
			CapabilitiesEvent cevent = (CapabilitiesEvent) item;
			DeviceConfiguration caps = cevent.getCapabilities();

			List<RpDevice> devs = caps.getDevices();
			for (RpDevice dev : devs) {
				System.out.println("found device: " + dev.getName()
						+ " of type " + dev.getDriverName());

			}

			/*
			 * used for updating pump rate
			 * 
			 * AbstractItem[] settings; idea.requestSettingsUpdate(settings);
			 */
		}

	}

	/**
	 * @param args
	 * @throws IOException
	 * @throws InterruptedException
	 */
	public static void main(String[] args) throws IOException,
			InterruptedException {
		
		PlatformUtil.init();
		PlatformUtil.loadLibrary("rxtxSerial");
		

		String clientTyp = "icuInterface.adapters.ASTMDriver";
		AATest me = new AATest();

		RpDevice conf = ASTMDriver.createConfigInstance();
		RpUtil.setParam(conf, "port", "/dev/ttyUSB0");
		
		ASTMDriver idea = (ASTMDriver) DeviceFactory.createDriver(conf);
		me.idea = idea;

		idea.addStreamListener(null, me);
		// idea.addStreamListener(StreamID.WAVEFORM, me);
		//idea.addStreamListener(StreamID.CAPABILITIES, me);
		// idea.addStreamListener(StreamID.MEASUREMENT, me);
		// idea.addStreamListener(StreamID.SECURITY, me);

		idea.connect();

		for (;;) {
			Thread.sleep(1000);
			System.out.println("ping");

			idea.tick();
			/*
			 * keep telling the server that we are here...send data for any open
			 * jobs.
			 */
			log.error("tick();");
		}
	}

}
