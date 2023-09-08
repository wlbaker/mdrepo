package icuInterface.discovery;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import idea.intf.AdapterInterface;
import idea.intf.StreamProducer;
import idea.schema.rp.RpDevice;
import lombok.Getter;

public class IDEADiscoveryWorker extends DiscoveryProvider {

	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();

	@Override
	public DeviceRecord[] getDevices() {
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
	public DeviceRecord getDevice(String devId) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public StreamProducer addDevice(RpDevice rpdev) throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

}
