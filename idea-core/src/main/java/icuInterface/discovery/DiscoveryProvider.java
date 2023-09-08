package icuInterface.discovery;

import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.StreamProducer;
import idea.schema.rp.RpDevice;

import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class DiscoveryProvider extends AbstractStreamProducer implements DiscoveryInterface {

	protected List<DeviceRecord> devs = new LinkedList<DeviceRecord>();
	private RpDevice default_dev;

	public void addDevice(StreamProducer driver, String portName) {
		String fullname = driver.getConfiguration().getName();
		addDevice(driver, portName, fullname);
	}

	public void addDevice(StreamProducer driver, String portName, String fullName) {

		DeviceRecord dev = new DeviceRecord();
		dev.setDriver(driver);
		dev.setFullName(fullName);
		dev.setUniqueID(portName);
		dev.addInterface(portName);

		addDevice(dev);
	}

	public void addDevice(DeviceRecord dev) {
		synchronized (devs) {
			devs.add(dev);
			fireDiscoverEvent(DiscoveryAction.DISCOVER, dev);
		}
	}

	protected Iterator<DeviceRecord> getDevIterator() {
		return devs.iterator();
	}

	public DeviceRecord getDevice(String devId) {
		for (DeviceRecord d : devs) {
			String id = d.getUniqueID();
			if (id == null) {
				id = d.getFullName();
			}
			log.debug("getDevice {} == {}", devId, id);
			if (id == null) {
				log.error("Internal Error: no ID for {}", d);
			} else if (id.equals(devId)) {
				return d;
			}
		}

		log.warn("getDevice {}: NOT FOUND", devId);
		return null;
	}

	public void reset() {
		Iterator<DeviceRecord> it = devs.iterator();
		while (it.hasNext()) {
			DeviceRecord d = it.next();
			d.getDriver().removeStreamListener(null);
			fireDiscoverEvent(DiscoveryAction.LOSE, d);
			it.remove();
		}
	}

	public DeviceRecord getDeviceFromDriver(StreamProducer source) {
		Iterator<DeviceRecord> it = devs.iterator();
		while (it.hasNext()) {
			DeviceRecord d = it.next();
			if (d.getDriver() == source) {
				return d;
			}
		}
		return null;
	}

	public void remove(StreamProducer driver) {

		if (devs != null) {
			for (DeviceRecord rec : devs) {
				if (rec.getDriver() == driver) {
					remove(rec);
				}
			}
		}
	}

	public void remove(DeviceRecord rec) {

		log.error("FIXME: Ignoring automated remove for the moment...consider manually added serial devices!");
		String uid = rec.getUniqueID();
//		if (devs != null) {
//			synchronized (devs) {
//				Iterator<DeviceRecord> it = devs.iterator();
//
//				if (uid == null) {
//					uid = rec.getFullName();
//				}
//
//				while (it.hasNext()) {
//					DeviceRecord d = it.next();
//
//					if (uid.equals(d.getUniqueID())) {
//						fireDiscoverEvent(DiscoveryAction.LOSE, d);
//						d.getDriver().removeStreamListener(null);
//						log.error("Removing device {}", uid);
//						it.remove();
//						return;
//					}
//				}
//			}
//		}
		log.error("FIXME: did not find device to remove: {}", uid);
	}

	public DeviceRecord[] getDevices() {
		DeviceRecord[] arr = new DeviceRecord[devs.size()];
		devs.toArray(arr);

		return arr;
	}

	public StreamProducer[] getDeviceDrivers() {
		StreamProducer[] arr = new StreamProducer[devs.size()];
		int idx = 0; // ok...not thread safe.
		for (DeviceRecord d : devs) {
			arr[idx++] = d.getDriver(); // yes, could be null
		}
		return arr;
	}

	public abstract void start();

	public abstract void stop();

	public abstract StreamProducer addDevice(RpDevice rpdev) throws IOException;

	public void tick() {
		if (devs != null) {
			for (DeviceRecord d : devs) {
				StreamProducer driver = d.getDriver(); // yes, could be null
				if (driver instanceof AdapterInterface) {
					AdapterInterface ai = (AdapterInterface) driver;
					ai.tick();
				}
			}
		}
	}

	public void setDefaultConfig(RpDevice dev) {
		default_dev = dev;
	}

	public RpDevice getDefaultConfig() {
		return default_dev;
	}
}
