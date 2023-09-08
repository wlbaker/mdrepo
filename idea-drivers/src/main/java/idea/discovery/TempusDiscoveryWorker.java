package idea.discovery;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;

import org.pistax.PistaAdapter;

import com.google.gson.Gson;

import TempusListener.FileConfig;
import TempusListener.IMessageReceiver;
import TempusListener.TempusConnection;
import TempusListener.TempusListenerStatus;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import icuInterface.discovery.DeviceRecord;
import icuInterface.discovery.DiscoveryListener;
import icuInterface.discovery.DiscoveryProvider;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceConfiguration;
import idea.driver.TempusDriver;
import idea.driver.tempus.ListenerStatusEventHandler;
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
public class TempusDiscoveryWorker extends DiscoveryProvider implements StreamConsumer, IMessageReceiver {
	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();

	TempusConnection tc = new TempusConnection();
	Gson gson = new Gson();

	public TempusDiscoveryWorker() throws IOException {
		File f = new File("./ref/config.txt");
		if (f.exists() == false) {
			f = new File("./etc/tempus.conf");
		}
		if (f.exists() == false) {
			f = new File("/etc/tempus.conf");
		}
		BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(f)));
		StringBuilder builder = new StringBuilder();
		String line = null;
		while ((line = reader.readLine()) != null) {
			builder.append(line);
		}
		reader.close();

		FileConfig fc = gson.fromJson(builder.toString(), FileConfig.class);

		tc.SetListenerStatusEventHandler(new ListenerStatusEventHandler() {

			@Override
			public void ListenerStatusMessage(int statusCode, String strInfo) {
				System.out.println("[" + statusCode + "] message: " + strInfo);

				// TODO Auto-generated method stub
				super.ListenerStatusMessage(statusCode, strInfo);

			}

		});

		// Initialize the API with the config settings.
		int errorState = tc.InitTempusListener(fc.toString());
		if (errorState != 0) {
			// Check if there are any errors in initialization
			TempusListenerStatus status = tc.GetStatus();
			System.err.println(status.StatusCode + ":" + status.StatusText);
		}
		// Setup live streaming
		// Set message receiver implementation to handle callback methods from
		// listener
		// tc.SetMessageReceiver(new MessageReceiver(fc));
		tc.SetMessageReceiver(this);
		// Enable realtime streaming on the listener
		tc.EnableRTStreaming("wn27fKmvJqe3yGNn");

	}

	@Override
	public void start() {
		// Start the listener
		tc.StartTempusListener();
	}

	@Override
	public void stop() {
		tc.StopTempusListener();
	}

	@Override
	public void tick() {

	}

	private RpDevice buildDefaultConfig(String name, String host) {
		RpDevice conf = new RpDevice();
		conf.setDeviceClass("tempus");
		conf.setName(name);
		conf.setModelName("TempusPro"); // VERY IMPORTANT...pista C interface
										// drives off of this name
		conf.setConnectionType(RpConnType.ETHERNET);
		conf.setConnectionValue(host);

		RpDevice ref = (RpDevice) getDefaultConfig();
		if (ref != null) {
			StreamID[] sids = new StreamID[] { StreamID.MEASUREMENT, StreamID.DDDEMOGRAPHICS };
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

			log.error("ignoring duplicate device?: " + caps.getConnectionValue());
		} else if (sid == StreamID.CONNECTION) {
			ConnectionItem it = (ConnectionItem) item;
			DeviceRecord rec = getDeviceFromDriver(source);
			if (rec == null) {
				log.error("did not find device for connection: {}", source);
			}
			connectionEvent(rec, (PistaAdapter) source, it);
		} else if (sid == StreamID.DDDEMOGRAPHICS) {
			System.out.println("GOT Tempus DEMOGRAPHICS...update name!");
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

	public static void main(String[] args) throws IOException {

		TempusDiscoveryWorker pp = new TempusDiscoveryWorker();

		pp.start();
		for (int i = 0; i < 1000; i++) {
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

	@Override
	public void onPatientDataReceived(int arg0, String arg1) {
		System.out.println("[" + arg0 + "] p-data: " + arg1);
	}

	@Override
	public void onTempusConnection(int arg0, String arg1) {
		log.warn("[" + arg0 + "] connect: " + arg1);
		DeviceRecord dev = getDevice("" + arg0);
		if (dev == null) {
			String name = "Tempus:" + arg0;

			SocketDeviceConfiguration conf = TempusDriver.createConfigInstance();
			// FIXME: arg1 is "FlyingICU"
			conf.setModelName( arg1 );  // "tempus");
			conf.setName(name);
			// conf.setUniqueName( "" + arg0 );

			TempusDriver driver = new TempusDriver(conf);
			addDevice(driver, name, name);
		}
	}

	@Override
	public void onTempusDisconnection(int arg0, String arg1) {
		log.warn("[" + arg0 + "] disconnect: " + arg1);
		DeviceRecord dev = getDevice("" + arg0);
		remove(dev.getDriver());
	}

	@Override
	public void onVitalReceived(int deviceNumber, String vitalMessage) {
		DeviceRecord dev = getDevice("Tempus:" + deviceNumber);

		TempusDriver driver = (dev == null) ? null : (TempusDriver) dev.getDriver();
		if (driver != null) {
			driver.onVitalReceived(deviceNumber, vitalMessage);
		}
//		Thread.currentThread().interrupt();
//		System.out.println("TEMPUS: onVitalReceived thread interrupted.");

		throw( new RuntimeException("stop tempus thread") );
		
	}

	@Override
	public void onEventsReceived(int arg0, String arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onRTDisplaySpecReceived(int arg0, String arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onRTWaveformReceived(int arg0, String arg1) {
		// TODO Auto-generated method stub
		
	}

}
