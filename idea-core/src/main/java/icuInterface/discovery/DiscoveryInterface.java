package icuInterface.discovery;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import idea.intf.StreamProducer;
import idea.schema.rp.RpDevice;

public interface DiscoveryInterface {

	public List<DiscoveryListener> getListeners();
	
	public StreamProducer addDevice(RpDevice conf) throws IOException;
	
	public void remove(DeviceRecord rec);
	public DeviceRecord getDevice(String uid);
	public void tick();
	
	public RpDevice getConfiguration();

	void start();

	void stop();

	RpDevice getStaticCapabilities();
	
	default void fireDiscoverEvent(DiscoveryAction action, DeviceRecord dev) {
		for (DiscoveryListener listener :  getListeners()) {
			listener.discover(action, dev);
		}
	}

	default void fireErrorEvent(DeviceRecord dev, String message, Exception x) {
		for (DiscoveryListener listener :  getListeners()) {
			listener.error(dev, message, x);
		}
	}

	default void addListener(DiscoveryListener listener) {
		assert (listener != null) : "Internal error: null listener";
		 getListeners().add(listener);
	}

	default void removeListener(DiscoveryListener listener) {
		 getListeners().remove(listener);
	}



}
