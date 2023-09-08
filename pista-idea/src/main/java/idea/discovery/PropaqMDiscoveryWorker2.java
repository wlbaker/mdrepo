package idea.discovery;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import org.pistax.PistaAdapter;
import org.pistax.PistaCl;
import org.pistax.PistaDiscoveryHandler;
import org.pistax.PistaService;

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
public class PropaqMDiscoveryWorker2 extends DiscoveryProvider implements StreamConsumer
	// IClientCallback, IServiceBrowserCallback, IServiceResolverCallback,  
{
	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();


	PistaService pp_disc;
	PistaDiscoveryHandler handler = new PistaDiscoveryHandler() {
		@Override
		public void discovery(long tm, int event_type, String name, String url) {
			System.out.println("JAVA " + event_type + " DEVICE: " + name + " at " + url);
			int idx = name.indexOf(' ');
			if( idx > 0 ) {
				name = name.substring(0, idx);
			}
			
			String host = url.replace("propaq://", "");
			idx = host.indexOf(':');
			if( idx > 0 ) {
				host = host.substring(0, idx);
			}
			
			RpDevice conf = buildDefaultConfig(name, host);
			PistaAdapter x = new PistaAdapter(conf);
			
			addDevice(x, name); // fires discovery event automatically

			/*
			x.addStreamListener(StreamID.CAPABILITIES, this);
			x.addStreamListener(StreamID.CONNECTION, this);
			x.addStreamListener(StreamID.DDDEMOGRAPHICS, this);
			*/
			x.addStreamListener(StreamID.CONNECTION, PropaqMDiscoveryWorker2.this);
			
			try {
				x.connect();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	};

	public PropaqMDiscoveryWorker2() {
		int count = PistaCl.getInstance().service_count();
		
		PistaCl.getInstance().service_count();
		System.out.println("service count: " + count );
		
		count = PistaCl.getInstance().driver_count();
		System.out.println("driver count: " + count );
		
		pp_disc = PistaCl.getInstance().service(0);
		System.out.println("got a service: " + pp_disc );
		
		// pp_disc = new PistaService();
		pp_disc.attach(handler);
	}

	@Override
	public void start() {
		pp_disc.start();
	}

	@Override
	public void stop() {
		pp_disc.stop();
	}

	@Override
	public void tick() {
		pp_disc.tick();
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

			log.error("ignoring duplicate device?: " + caps.getConnectionValue() );
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
		} else if (sid == StreamID.MEASUREMENT) {
			System.out.println("m");
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

	public static void main(String[] args) {
		System.load("/home/bbaker/git/pista/libx-support.so");
		System.load("/home/bbaker/git/pista/libpista-core.so");
		System.load("/home/bbaker/git/pista/pista-bindings/libpista-java.so");
		
		PropaqMDiscoveryWorker2 pp = new PropaqMDiscoveryWorker2();

		
		pp.start();
		for( int i = 0; i < 1000; i++) {
			pp.tick();
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		pp.stop();
	}

}
