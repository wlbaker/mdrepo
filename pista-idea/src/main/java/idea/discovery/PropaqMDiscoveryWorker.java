package idea.discovery;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.pistax.PistaAdapter;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.DiscoveryProvider;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceConfiguration;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;

@Slf4j
public class PropaqMDiscoveryWorker extends DiscoveryProvider implements StreamConsumer
	// IClientCallback, IServiceBrowserCallback, IServiceResolverCallback,  
{
	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();

	Map<String, StreamProducer> candidates = new HashMap<String, StreamProducer>();

	int seq = 0;

	public PropaqMDiscoveryWorker() {
	}

	@Override
	public void start() {
	}

	@Override
	public void stop() {
	}

	@Override
	public void tick() {
		seq %= 6;

		if (seq == 0) {
			try {
				processAvahiQuery();
			} catch (IOException e) {
				// not supposed to happen, but mostly ignored
				System.err.println(e.getMessage());
			}
		}

		seq++;

	}

	private void processAvahiQuery() throws IOException {
		// avahi-browse -c --domain=X-Series.device.ZOLL.local _workstation._tcp
		ProcessBuilder ps = new ProcessBuilder( //
				"/usr/bin/avahi-browse", // executable
				"-p", // parsable computer format
				"-c", // from cache
				"--no-db-lookup", // from cache
				"--domain=X-Series.device.ZOLL.local", // zoll devices
				"_workstation._tcp" // web server record
		);

		//From the DOC:  Initially, this property is false, meaning that the 
		//standard output and error output of a subprocess are sent to two 
		//separate streams
		ps.redirectErrorStream(true);

		Process pr = ps.start();

		BufferedReader in = new BufferedReader(new InputStreamReader(pr.getInputStream()));
		String line;
		while ((line = in.readLine()) != null) {
			String[] rec = line.split(";");
			String sign = rec[0];
			String intf = rec[1];
			String protocol = rec[2]; // expecting IPv4
			String workstation = rec[3]; // AP14E001105 [00:22:52:03:01:5d]
			String[] ws_args = workstation.split("[\\\\]"); // spaces are escaped in avahi encoding
			String name = ws_args[0] + ".X-Series.device.ZOLL.local";

			StreamProducer driver = candidates.get(name);
			if (driver == null) {
				System.out.println("found zoll: " + name);

				RpDevice conf = buildDefaultConfig(name, name);
				PistaAdapter x = new PistaAdapter(conf);
				
				addDevice(x, name); // fires discovery event automatically

				x.addStreamListener(StreamID.CAPABILITIES, this);
				x.addStreamListener(StreamID.CONNECTION, this);
				x.addStreamListener(StreamID.DDDEMOGRAPHICS, this);
				x.connect();

				candidates.put(name, x);
			}
		}

		try {
			pr.waitFor();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {

			in.close();
		}
	}

	private RpDevice buildDefaultConfig(String name, String host) {
		RpDevice conf = new RpDevice();
		conf.setDeviceClass("propaq");
		conf.setName(name);
		conf.setModelName("propaqm"); // VERY IMPORTANT...pista C interface drives off of this name
		conf.setConnectionType(RpConnType.PROPAQ_M);
		conf.setConnectionValue(host);

		RpDevice ref = (RpDevice) getDefaultConfig();
		if (ref != null) {
			StreamID[] sids = new StreamID[] { StreamID.WAVEFORM, StreamID.MEASUREMENT, StreamID.DDDEMOGRAPHICS };
			for (StreamID sid : sids) {

				RpStream s = RpUtil.getStream(ref, sid);
				if (s != null) {
					conf.getStreams().add(s);
				}
			}
		}

		return conf;
	}

	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.CAPABILITIES) {
			CapabilitiesEvent e = (CapabilitiesEvent) item;
			DeviceConfiguration caps = e.getCapabilities();

			StreamProducer driver = candidates.get(caps.getConnectionValue());
			if (driver == null) {
				capabilitiesEvent(driver, caps);
			} else {
				log.error("ignoring duplicate device: " + caps.getConnectionValue() );
			}
		} else if (sid == StreamID.CONNECTION) {
			ConnectionItem it = (ConnectionItem) item;
			DeviceRecord rec = getDeviceFromDriver(source);
			if (rec == null) {
				log.error("did not find device for connection: {}", source);
			}
			connectionEvent(rec, (PistaAdapter) source, it);
		} else if (sid == StreamID.DDDEMOGRAPHICS) {
			System.out.println("GOT PROPAQ DEMOGRAPHICS...update name!");
			// Intellivue_Demographics demog = (Intellivue_Demographics) item;
			//			DeviceRecord rec = getDeviceFromDriver(source);
			//			if (rec == null) {
			//				log.error("did not find device for demographics update: {}", source);
			//			} else {
			//				rec.setFullName( demog.getName() );
			//				fireDiscoverEvent(DiscoveryAction.UPDATE, rec);
			//			}
		} else {
			log.error("DISCOVERY: Unexpected event: " + sid);
		}
	}

	public void connectionEvent(DeviceRecord rec, PistaAdapter candidate, ConnectionItem item) {
		System.out.println("got connevent: " + item);
		if (item.getStatus() == ConnectionStatus.CONNECTED) {
		} else if (item.getStatus() == ConnectionStatus.NOT_CONNECTED) {
			// remove(rec);
		}
	}

	public void capabilitiesEvent(StreamProducer driver, DeviceConfiguration caps) {
		System.out.println("capabilities driver: " + caps.getConnectionValue());

		// update( rec );
	}

	@Override
	public StreamProducer addDevice(RpDevice rpdev) throws IOException {
		log.error("FIXME: this device should keep track of its contacts");
		return null;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		log.error("FIXME: this device should provide static capabilities?");
		return null;
	}

}
