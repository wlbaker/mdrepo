package icuInterface.discovery;

import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.PortInUseException;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortEvent;
import com.fazecast.jSerialComm.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
//import icuInterface.adapters.BardUrimeter;
//import icuInterface.adapters.EvitaDriver;
//import icuInterface.adapters.IFMoutDriver;
//import icuInterface.adapters.KangarooDriver;
//import icuInterface.adapters.PlumADataportDriver;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.intf.StreamProducer;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.util.Collection;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.TooManyListenersException;

import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;

@Slf4j
public class RxtxDiscoveryWorker extends DiscoveryProvider implements SerialPortEventListener {

	private static RxtxDiscoveryWorker service;
	private static final long TICK_TIMER_INTERVAL = 2000;

	private static final int TIMEOUT = 6;
	private static final int MAX_VISIBLE_PORTS = 6;
	private String[] serial_dev;
	private SerialPort[] serial_ports;
	private SerialAdapter[] dev_inst;
	private String[] status_message;
	private int[] countdown_ticker;
	private int[] status_flags;
	private ByteBuffer[] serial_buf;

	List<AdapterInterface> probes = new LinkedList<AdapterInterface>();

	private static Map<String, RpDevice> conf_map = new HashMap<String, RpDevice>();

	int probeSetup_idx = 0;
	int found_counter = 0;
	int tick_counter = 0;

	private static Timer tickTimer;

	private int probe_count;
	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();

	public RxtxDiscoveryWorker() {
		service = this;
	}

	@Deprecated
	public int loadConfig(RpStudy study) {
		log.error("DEPRECATED loadConfig, should go through master discovery");
		if (study == null) {
			return -1;
		}

		int cnt = 0;
		List<RpHardware> hw = study.getHardware();
		RpHardware hw0 = hw.get(0);
		List<RpDevice> devs = hw0.getDevices();
		for (RpDevice dev : devs) {

			//
			// this conf is only used to determine if the device is a
			// serial device. we recreate the confs as needed so that
			// we can reassign the name...cant have two devices with the
			// same conf ... would mean they had the same name too
			//
			DeviceConfiguration conf = RpUtil.createDeviceConfiguration(dev, true);
			cnt++;

			if (conf instanceof SerialDeviceConfiguration) {
				conf_map.put(dev.getDeviceClass(), dev);
			} else {
				log.warn("unknown configuration class: {}", conf);
			}
		}

		return cnt;
	}

	/**
	 * Handle serial events. Dispatches the event to event-specific methods.
	 * 
	 * @param event
	 *            The serial event
	 */
	@Override
	public void serialEvent(SerialPortEvent event) {

		try {
			_serialEvent(event);
		} catch (Exception e) {
			log.error("unexpected exception in serialEvent", e);
		} catch (Throwable e2) {
			log.error("unexpected throwable in serialEvent", e2);
		}
	}

	public void _serialEvent(SerialPortEvent event) throws IOException {

		int port_idx = -1;
		Object src = event.getSource();
		if (serial_ports == null) {
			// log.error("serial ports not prepared");
			return;
		}
		for (int i = 0; i < serial_ports.length; i++) {
			if (src == serial_ports[i]) {
				port_idx = i;
				break;
			}
		}

		if (port_idx < 0) {
			log.error("Messages from invalid port: {}" + src);
			return;
		}

		AdapterInterface driver;
		//
		// Dispatch event to individual methods. This keeps this ugly
		// switch/case statement as short as possible.
		//
		switch (event.getEventType()) {
		case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
			log.debug("outputBufferEmpty(event)");
			break;

		case SerialPortEvent.DATA_AVAILABLE:
			SerialPort port = (SerialPort) src;
			InputStream in = port.getInputStream();
			if (log.isDebugEnabled()) {

				// FIXME: log broken? log.debug("(P{} - {}) ", port_idx,
				// in.available());
			}

			driver = dev_inst[port_idx];

			ByteBuffer bb = serial_buf[port_idx];

			// Of course these are serial adapters!
			if (driver != null && driver instanceof SerialAdapter) {
				driver.process(in, port.getOutputStream());
			} else {
				while (in.available() > 0) {
					int ch = in.read();
					if (bb.position() < bb.limit()) {
						bb.put((byte) ch);
					}
				}
				if (countdown_ticker[port_idx] == 0) {

					log.warn("HARDCODED IMP731 below...discovery-testing probe data");
					dev_inst[port_idx] = testDeviceData(bb);
					if (dev_inst[port_idx] != null) {

						// FOUND VIA PROBE
						countdown_ticker[port_idx] = TIMEOUT;
						addDevice(dev_inst[port_idx], port.getName());

					}
				}

			}
			break;

		case SerialPortEvent.DSR:
			log.debug("got dsr");
			break;

		case SerialPortEvent.BI:
			log.debug("got break event");
			break;

		case SerialPortEvent.CD:
			log.debug("got CD");
			break;

		case SerialPortEvent.CTS:
			log.debug("got CTS");
			break;

		case SerialPortEvent.FE:
			log.debug("got FE");
			break;

		case SerialPortEvent.OE:
			log.debug("overrunError(event);");
			break;

		case SerialPortEvent.PE:
			log.debug("parityError(event);");
			break;
		case SerialPortEvent.RI:
			log.debug("ringIndicator(event);");
			break;

		default:
			log.warn("UNKNOWN EVENT: {}", event);
			break;

		}

	}

	private SerialAdapter testDeviceData(ByteBuffer bb) {

		SerialAdapter driver = null;

		if (bb.position() < 5) {
			return null; // wait for more data
		}

		byte[] arr = bb.array();

		for (AdapterInterface d : probes) {
			AdapterInterface probe_driver = d;
			if (probe_driver.verify(arr, bb.position())) {

				RpDevice conf = probe_driver.getConfiguration();
				driver = (SerialAdapter) DeviceFactory.createDriver(conf);

				break;
			}
		}

		return driver;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		DeviceConfiguration conf = new DeviceConfiguration("discovery");

		for (RpDevice device : conf_map.values()) {
			DeviceConfiguration sub = RpUtil.createDeviceConfiguration(device, false);
			conf.addDevice(sub);
		}
		return conf;
	}

	private DeviceConfiguration getConfiguration(String canonicalName, SerialPort port) {
		DeviceConfiguration conf = null;
		RpDevice dev = conf_map.get(canonicalName);
		if (dev == null) {
			log.error("NO CONFIG FOR DEV: {} port: {}", canonicalName, port);
		} else {
			conf = RpUtil.createDeviceConfiguration(dev, true);

			conf.setConnectionType(RpConnType.RS_232);
			conf.setConnectionValue(port.getName());
			// CHECK FOR DUPLICATES AND RENAME
			if (conf.getName() == null) {
				conf.setName(canonicalName);
			}
			String baseName = conf.getName();

			int idx = 0;
			boolean exists;
			do {
				exists = false;
				idx++;
				String name = conf.getName();

				for (SerialAdapter s : dev_inst) {
					if (s == null) {
						// ignore
					} else {
						String existing_name = s.getConfiguration().getName();
						if (name.equals(existing_name)) {
							exists = true;
							conf.setName(baseName + idx);
							break;
						}
					}
				}
			} while (exists == true);

		}
		return conf;
	}

	public void probe_all_ports(AdapterInterface probe_dev) throws IOException {

		log.info("polling dev: {} {}", probeSetup_idx, probe_dev.getClass().getName());

		for (int i = 0; i < serial_ports.length; i++) {

			SerialPort port = serial_ports[i];
			AdapterInterface driver = dev_inst[i];

			// RXTX does not handle a USB port-s which will come and go
			// if (port.isOpen() && driver == null) {
			serial_buf[i].clear();
			probe_one_port(probe_dev, port);
			// }

		}
	}

	private void probe_one_port(AdapterInterface probe_dev, SerialPort port) throws IOException {

		InputStream in = port.getInputStream();
		while (in.available() > 0) {
			in.read(); // read and discard
		}

		int baud = 115200;
		log.debug("FIXME: SET PORT PARAMS probing PORT: {} baud={}", port, baud);
		try {
			port.setSerialPortParams(baud, 8, 1, 0);
		} catch (UnsupportedCommOperationException e) {
			log.error("unsupported comm exception setting serial params");
		}
		// PARITY_NONE);
		OutputStream out = port.getOutputStream();

		probe_dev.probe(out);
	}

	@Override
	public void tick() { // sends ticks to the drivers
		if (serial_ports == null) {
			log.debug("no serial ports to probe.");
			return;
		}
		for (int i = 0; i < serial_ports.length; i++) {
			SerialAdapter driver = dev_inst[i];
			if (driver != null && (countdown_ticker[i] > 1)) {
				driver.tick();
			}
		}

	}

	public void tick_probes() throws IOException {
		if (probes.size() == 0) {
			// nothing to do...yet
			return;
		}

		tick_counter++;
		tick_counter = tick_counter % 10;

		if (tick_counter == 3) {
			connectPorts(); // try to reconnect serial ports every 10 secs
		}

		probeSetup_idx = (probeSetup_idx + 1) % probes.size();

		AdapterInterface probe_dev = probes.get(probeSetup_idx);
		if (probe_dev == null) {
			// nulls can be used intentionally to manage timing
			return;
		}

		probe_all_ports(probe_dev);
	}

	public void setPorts(CommPortIdentifier[] portList) {

		String[] portDevs = new String[portList.length];

		int i = 0;
		for (CommPortIdentifier portId : portList) {
			portDevs[i++] = portId.getName();
		}

		setPorts(portDevs);
	}

	public void setPorts(String[] portList) {

		int count = portList.length;
		serial_dev = new String[count];
		serial_ports = new SerialPort[count];
		dev_inst = new SerialAdapter[count];
		countdown_ticker = new int[count];
		status_flags = new int[count];
		status_message = new String[count];
		serial_buf = new ByteBuffer[count];

		for (int i = 0; i < portList.length; i++) {
			countdown_ticker[i] = TIMEOUT;
			dev_inst[i] = null;
			serial_ports[i] = null;
			status_message[i] = "Initializing...";
			serial_dev[i] = portList[i];
			serial_buf[i] = ByteBuffer.allocate(100); // each device defaults to

		}

		connectPorts();
	}

	private void connectPorts() {

		for (int i = 0; i < serial_dev.length; i++) {
			String devName = serial_dev[i];
			SerialPort port = serial_ports[i];
			if (port != null) {
				continue; // already connected
			}

			try {
				CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(devName);
				port = addOnePort(portId);

				if (port != null) {
					port.addEventListener(this);
				}
				serial_ports[i] = port;
			} catch (NoSuchPortException e) {
				log.warn("DEBUG: port does not exist: {}", devName);
			} catch (PortInUseException e) {
				log.warn("Port not available: {}", devName);
			} catch (UnsupportedCommOperationException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (TooManyListenersException e) {
				log.error("INTERNAL ERROR: Too many listeners on serial port: {}", devName);
			}
		}
	}

	public SerialPort[] getPorts() {
		return serial_ports;
	}

	private SerialPort addOnePort(CommPortIdentifier portId)
			throws PortInUseException, UnsupportedCommOperationException, TooManyListenersException {

		String name = portId.getName();

		SerialPort port = null;
		if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
			log.debug("Monitoring: {}", name);
			port = (SerialPort) portId.open("MONITOR_" + name, 2000);

			int baud = 115200;
			port.setSerialPortParams(baud, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
			log.error("FIXME: hard coded baud rate for port open for imp731 baud={}", baud);

			port.setDTR(true);
			port.setRTS(true);
			// port.setRTS( true );

			port.notifyOnDataAvailable(true);

		} else {
			log.debug("Skipping: {} {}", name, portId);
		}

		return port;
	}

	public String buildStatusString() {
		String s = " ";
		for (int i = 0; i < countdown_ticker.length && i < MAX_VISIBLE_PORTS; i++) {
			int counter = countdown_ticker[i];
			s += (i + 1) + ((counter > 0) ? "*" : " ");
		}
		return s;
	}

	@Override
	public void start() {
		log.debug("Starting probe and ticking");
		initTimer();
	}

	@Override
	public void stop() {
		if (tickTimer != null) {
			try {
				tickTimer.cancel();
			} catch (Exception e) {
			}
		}
	}

	@Override
	public StreamProducer addDevice(RpDevice conf) throws IOException {
		String req_name = conf.getName();

		DeviceRecord rec = getDevice(req_name);
		if (rec != null) {
			log.info("DEVICE CONFIG EXISTS: {}", req_name);
			// if (rec.getSerialPort() != null) {
			if (rec.getDriver() != null) {
				log.error("FIXME is it connected??: DEVICE ALREADY CONNECTED: {}", req_name);
				return rec.getDriver();
			}
		}

		//
		// this is the serial discovery adapter...should be serial devices
		//
		SerialAdapter driver = (SerialAdapter) DeviceFactory.createDriver(conf);
		if (driver == null) {
			throw new IOException("Could not find driver: " + conf.getDeviceClass());
		}

		int port_idx = -1;
		String src = conf.getConnectionValue(); // COM1...
		for (int i = 0; i < serial_ports.length; i++) {
			SerialPort port = serial_ports[i];
			if (port.getName().endsWith(src)) { // I hate this
												// inconsistent
												// //./.COM99
												// stuff
				port_idx = i;
				break;
			}
		}

		if (port_idx < 0) {
			log.error("Requested port not managed by discovery: {}", src);
			throw new IOException(
					"Requested port not managed: " + src + ".  Verify that no other applications are using this port.");
		}

		log.error("discovery-assigning driver port {} assigned: {}", serial_ports[port_idx], driver);

		dev_inst[port_idx] = driver;

		SerialPort port = serial_ports[port_idx];
		countdown_ticker[port_idx] = TIMEOUT;
		log.error("At this point, the port is not set for the right baud rate.");
		log.error("There may be a better way to do this...???  Just let the device be discovered???");
		log.error("Restrict probing on this port to the indicated device???");
		driver.setPort(port);

		assert(rec == null) : "Should be a null rec ";
		
		addDevice(driver, port.getName() );

		return driver;
	}

	private void initTimer() {
		// create a timer that will monitor the connection, if no data has been
		// received in the last X seconds attempt to send a ping,if still no
		// result, then fire a disconnected event.

		stop();
		tickTimer = new Timer("SerialDiscoveryService");
		tickTimer.schedule(new TimerTask() {

			@Override
			public void run() {
				try {
					tick_probes();
					// tick();

				} catch (Exception ee) {
					ee.printStackTrace();
					log.warn("tick err!");
				}

			}

		}, 1000L, TICK_TIMER_INTERVAL);
	}

	public int getPortCount() {
		if (serial_ports == null) {
			return -1;
		}
		return serial_ports.length;
	}

	public SerialPort getPort(int idx) {
		return serial_ports[idx];
	}

	public DeviceConfiguration getPortConfig(int idx) {
		RpDevice conf = null;
		SerialAdapter driver = dev_inst[idx];
		if (driver != null) {
			conf = driver.getConfiguration();
		}
		return (DeviceConfiguration) conf;
	}

	public static RxtxDiscoveryWorker getInstance() {
		return service;
	}

	public SerialPort getPort(String portName) {
		SerialPort port = null;
		if (serial_ports != null)
			for (SerialPort t : serial_ports) {
				if (t != null) {
					if (t.getName().endsWith(portName)) {
						port = t;
						break;
					}
				}
			}
		return port;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		log.error("FIXME: getStaticCapabilities() stub");
		return null;
	}

}
