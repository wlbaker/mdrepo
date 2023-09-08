package icuInterface.discovery;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import idea.conf.DeviceFactory;
import idea.intf.AdapterInterface;
import idea.intf.StreamProducer;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import lombok.Getter;

public class ManualDiscoveryWorker extends DiscoveryProvider implements DiscoveryInterface {

	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();

	@Override
	public RpDevice getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void start() {
		// TODO Auto-generated method stub

	}

	@Override
	public void stop() {
		// TODO Auto-generated method stub

	}

	@Override
	public StreamProducer addDevice(RpDevice conf) throws IOException {
		AdapterInterface driver = DeviceFactory.createDriver(conf);
		if( driver != null) {
			driver.connect(); // connect after notifying clients
		
			// add to linked list and fire discovery event
			super.addDevice( driver, conf.getConnectionValue() );
		}
		return driver;
	}

	@Override
	public void remove(DeviceRecord rec) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public DeviceRecord getDevice(String uid) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void tick() {
		super.tick();  // step through ticks for all manual devices
		
	}

	@Override
	public RpDevice getConfiguration() {
		RpDevice pconf;
			if (devs != null && devs.size() > 0 ) {
				pconf = new RpDevice(); // super.getConfiguration();
				pconf.setConnectionType(RpConnType.NONE); // manual
				pconf.setName("manual discovery");
				pconf.setDeviceClass( this.getClass().getCanonicalName() );
				for (DeviceRecord rec : devs) {
					RpDevice one_conf = rec.getDriver().getConfiguration();
					pconf.getDevices().add(one_conf);
				}
			} else {
				pconf = null;
			}
		return pconf;
	}

	
}
