package icuInterface.discovery;

import idea.conf.DeviceCapabilities;
import idea.conf.DeviceFactory;
import idea.intf.AdapterInterface;
import idea.intf.StreamProducer;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;

import java.io.IOException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import lombok.Getter;
import lombok.NonNull;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DiscoveryService implements DiscoveryInterface {

	private static DiscoveryService instance = null;
	Map<RpConnType, DiscoveryProvider> providers = new HashMap<RpConnType, DiscoveryProvider>();

	class ListenerProxy implements DiscoveryListener {
		@Override
		public void discover(DiscoveryAction action, DeviceRecord dev) {
			System.out.println("proxy discover is firing!!!");
			fireDiscoverEvent(action, dev);
		}

		@Override
		public void error(DeviceRecord dev, String message, Exception s) {
			System.out.println("proxy error is firing!!!");
			fireErrorEvent(dev, message, s);
		}
	};

	private ListenerProxy proxy = new ListenerProxy();

	private boolean recursing = false;
	private List<RpDevice> devConfs;

	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();


	static {
		instance = new DiscoveryService();
	}

	public static DiscoveryService getInstance() {
		return instance;
	}

	private DiscoveryService() {
		addManualDiscovery();
	}

	public void setDevices(List<RpDevice> devConfs) {
		this.devConfs = devConfs;
	}

	public void start() {

		if (recursing) {
			return;
		}
		recursing = true;

		if (devConfs == null) {
			log.warn("NO DEVICES CONFIGURED FOR DISCOVERY");
		} else {
			for (RpDevice rpdev : devConfs) {

				String connectionName = rpdev.getConnectionValue();
				if ("[DISCONNECTED]".equals(connectionName)) {
					log.warn("DEVICE DISCONNECTED: {}", rpdev);
					continue;
				}

				RpConnType typ = rpdev.getConnectionType();
				DiscoveryProvider provider = providers.get(typ);
				if (provider == null) {
					// anytime the provider is not found, treat as a manual device
					log.info("No provider for connection type: {}, using manual", typ);
					provider = providers.get(RpConnType.NONE);
				}

				try {
					provider.addDevice(rpdev);
				} catch (IOException io) {
					log.error("Error starting device: {} {}", rpdev.getName(), io);
					fireErrorEvent(null, "Error starting device", io);
				}
			}
		}

		for (DiscoveryProvider d : providers.values()) {
			System.out.println("starting: " + d);
			d.start();
		}
		System.out.println("done.");
		recursing = false;
		return;
	}

	public void stop() {
		if (recursing) {
			return;
		}
		recursing = true;
		for (DiscoveryProvider d : providers.values()) {
			// if (d == this) {
			d.stop();
			d.reset();
		}
		recursing = false;
	}

	public StreamProducer[] getDeviceDrivers() {
		LinkedList<StreamProducer> ll = new LinkedList<StreamProducer>();
		for (DiscoveryProvider d : providers.values()) {
			_addAll(ll, d.getDeviceDrivers());
		}

		StreamProducer[] arr = new StreamProducer[ll.size()];
		return ll.toArray(arr);
	}

	private void _addAll(LinkedList<StreamProducer> ll, StreamProducer[] producers) {
		if (producers != null) {
			for (StreamProducer p : producers) {
				ll.add(p);
			}
		}
	}

	@Override
	public void remove(DeviceRecord rec) {
		for (RpConnType key : providers.keySet()) {
			DiscoveryProvider provider = providers.get(key);
			provider.remove(rec);
		}
	}

	@Override
	public DeviceRecord getDevice(String uid) {
		DeviceRecord dev = null;
		for (DiscoveryProvider p : providers.values()) {
			dev = p.getDevice(uid);
			if (dev != null) {
				break;
			}
		}
		return dev;
	}

	@Override
	public void tick() {
		for (DiscoveryProvider p : providers.values()) {
			p.tick();
		}
	}

	@Override
	public StreamProducer addDevice(@NonNull RpDevice conf) throws IOException {

		RpConnType ct = conf.getConnectionType();
		if (ct == null) {
			ct = RpConnType.NONE;
			conf.setConnectionType(ct);
		}
		DiscoveryProvider provider = providers.get(ct);
		// if no provider is registered, use the manual provider
		if( provider == null ) provider = providers.get(RpConnType.NONE);
		
		StreamProducer driver = null;

		driver = provider.addDevice(conf);
		addDevice(ct, conf.getName(), driver);

		return driver;
	}

	@Override
	public RpDevice getConfiguration() {
		RpDevice master = new RpDevice();
		master.setName("discovery-master");
		for (RpConnType ct : providers.keySet()) {
			DiscoveryProvider provider = providers.get(ct);
			RpDevice pconf = provider.getConfiguration();

			log.info("adding pconf: {}", pconf);
			if (pconf != null) {
				master.getDevices().add(pconf);
			}
		}
		return master;
	}

	private void addDevice(RpConnType ct, String name, StreamProducer producer) {

		if (ct == null) {
			ct = RpConnType.NONE;
		}

		DiscoveryProvider provider = providers.get(ct);
		if (provider == null) {
			log.error("Unknown discovery provider class: {}", ct);
			provider = providers.get(RpConnType.NONE); // try to add as a manual panel
		}

		if (provider != null) { // this should never be null, as we should always have a manual provider
			provider.addDevice(producer, name);
		}
	}

	@Override
	public RpDevice getStaticCapabilities() {
		log.error("FIXME: stub for getStaticCapabilities()");
		return null;
	}

	public DiscoveryProvider getWorker(RpConnType typ) {
		return providers.get(typ);
	}

	public DiscoveryProvider addManualDiscovery() {
		DiscoveryProvider provider = providers.get( RpConnType.NONE);
		if( provider == null ) {
			provider = new ManualDiscoveryWorker();
			provider.addListener(proxy);
			providers.put(RpConnType.NONE, provider );
		}

		return provider;
	}

	/*
	 * Create a discovery provider that polls the requested serial ports. All ports
	 * must exist. The alternate method is to supply a list of device names that may
	 * not exist initially, such as USB devices which may come and go.
	 */

	/*
	 * Deprecated...and removed with conversion to jSerialComm
	 *
	@Deprecated
	public DiscoveryProvider addSerialDiscovery(CommPortIdentifier[] usable_ports) {
		if (usable_ports == null || usable_ports.length == 0) {
			return null;
		}
		DiscoveryProvider serial_discovery = getWorker(RpConnType.RS_232);
		if (serial_discovery == null) {
			RxtxDiscoveryWorker d = new RxtxDiscoveryWorker();
			d.setPorts(usable_ports);
			d.addListener(proxy);

			providers.put(RpConnType.RS_232, d);

			serial_discovery = d;
		}

		return serial_discovery;
	}
	*/

	/*
	 * Create a provider that will poll the requested serial devices. The ports do
	 * not have to exist and may appear or disappear, ie, USB serial devices.
	 */

	public DiscoveryProvider addSerialDiscovery(String[] requested_ports) {
		if (requested_ports == null || requested_ports.length == 0) {
			return null;
		}
		DiscoveryProvider provider = getWorker(RpConnType.RS_232);
		if (provider == null) {
			JSerialCommDiscoveryWorker d = new JSerialCommDiscoveryWorker();
			d.setPorts(requested_ports);
			provider = d;
			
			provider.addListener(proxy);
			providers.put(RpConnType.RS_232, provider);

		}

		return provider;
	}

	public DiscoveryProvider addInfinityDiscovery() {
		DiscoveryProvider infinity = getWorker(RpConnType.INFINITY);
		if (infinity == null) {
			infinity = new InfinityDiscoveryWorker();
			infinity.addListener(proxy);
			providers.put(RpConnType.INFINITY, infinity);
		}
		return infinity;
	}

	public void addDiscoveryProvider(RpConnType typ, DiscoveryProvider provider) {
		DiscoveryProvider ref = getWorker(typ);
		if (ref != null) {
			ref.stop(); // stop, then replace
		}

		provider.addListener(proxy);
		providers.put(typ, provider);
	}

	public DiscoveryProvider addIntellivueDiscovery() {
		DiscoveryProvider intellivue = getWorker(RpConnType.INTELLIVUE);
		if (intellivue == null) {
			intellivue = new IntellivueDiscoveryWorker();
			intellivue.addListener(proxy);
			providers.put(RpConnType.INTELLIVUE, intellivue);
		}
		return intellivue;
	}

	public void refreshListener(DiscoveryListener l) {
		for (RpConnType key : providers.keySet()) {
			DiscoveryProvider provider = providers.get(key);
			DeviceRecord[] ddevs = provider.getDevices();
			if (ddevs == null) {
				continue;
			}
			for (DeviceRecord dev : ddevs) {
				provider.fireDiscoverEvent(DiscoveryAction.UPDATE, dev);
			}
		}

	}

}
