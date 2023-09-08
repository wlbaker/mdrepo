package icuInterface.discovery;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.util.LinkedList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

import lombok.Getter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class JSerialCommDiscoveryWorker extends DiscoveryProvider implements SerialPortDataListener {
	private static final int GENERAL_COMM_TIMEOUT = 15;  // FIXME: use tick error to find disconnects
	
	private static final long debugStartTime = System.currentTimeMillis();
	
	class TrackingConnectionListener implements StreamConsumer {

		int idx;

		TrackingConnectionListener(int idx) {
			this.idx = idx;
		}

		@Override
		public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
			ConnectionItem it = (ConnectionItem) item;
			if (it.getStatus() == ConnectionStatus.NOT_CONNECTED) {
				log.error("FIXME: sstarting lose");
				serial_buf[idx].clear();
				dev_inst[idx] = null;
				remove(source);
				log.error("FIXME: completed lose");
			} else {
				log.error("FIXME: handle connection info? {}", item);
			}

		}

	}

	private static JSerialCommDiscoveryWorker service;
	private static final long TICK_TIMER_INTERVAL = 2000;

	private SerialPort[] serial_ports;
	private AdapterInterface[] dev_inst;
	private String[] status_message;
	private ByteBuffer[] serial_buf;
	private int[] timeout;

	List<AdapterInterface> probes = new LinkedList<AdapterInterface>();

	int probeSetup_idx = 0;
	int found_counter = 0;
	int tick_counter = 0;

	private static Timer tickTimer;

	private int probe_count;
	private SerialConnection prev_conn;
	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();

	public JSerialCommDiscoveryWorker() {
		service = this;
	}

	public JSerialCommDiscoveryWorker(RpStudy study) {
		service = this;
		resetConfiguration(study);
	}

	public int resetConfiguration(RpStudy study) {

		int cnt = 0;
		List<RpHardware> hw = study.getHardware();
		RpHardware hw0 = hw.get(0);
		List<RpDevice> confs = hw0.getDevices();

		for (RpDevice conf : confs) {
			RpConnType typ = conf.getConnectionType();
			if (typ == RpConnType.RS_232) {
				AdapterInterface probe = DeviceFactory.createDriver(conf);
				probes.add(probe);

			} else {
				// JSerialComm ignoring dev of wrong type
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

		if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
			return;
		}

		int port_idx = -1;
		Object src = event.getSource();

		for (int i = 0; i < serial_ports.length; i++) {
			if (src == serial_ports[i]) {
				port_idx = i;
				break;
			}
		}

		assert (port_idx >= 0) : "Messages from invalid port";

		SerialPort port = (SerialPort) src;
		InputStream in = port.getInputStream();
		AdapterInterface driver = dev_inst[port_idx];
		
		if( in.available() < 0 ) {
				// this is our USB disconnect notification.
			if( driver != null ) {
				driver.disconnect();
				dev_inst[port_idx] = null;
			} else {
				port.closePort();
			}
			log.warn("closing port avail={}", in.available());
			return;
		}


		// Of course these are serial adapters!
		if (driver != null) {
				timeout[port_idx] = 0;
				driver.process(in, port.getOutputStream());
			
		} else {
			ByteBuffer bb = serial_buf[port_idx];
			log.debug("* SER-EVENT: {} bytes", in.available() );
			while (in.available() > 0) {
				int ch = in.read();
				// ignore bytes beyond the capacity
				if (bb.position() < bb.capacity()) {
					bb.put((byte) ch);
				}
			}

			driver = testDeviceData(bb);
			if (driver != null) { // NEW DRIVER FOUND VIA PROBE
				SerialAdapter serial = (SerialAdapter) driver;
				serial.setOutputStream(port.getOutputStream());

				timeout[port_idx] = 0;
				dev_inst[port_idx] = driver;
				log.info("jsc: assigning driver to idx={}", port_idx );
				addDevice(driver, port.getSystemPortName());

				driver.addStreamListener(StreamID.CONNECTION, new TrackingConnectionListener(port_idx));
			}
		}

	}

	private AdapterInterface testDeviceData(ByteBuffer bb) {

		AdapterInterface driver = null;

		if (bb.position() < 5) {
			return null; // wait for more data
		}

		byte[] arr = bb.array();

		System.out.print("jsc testing: ");
		for (int i = 0; i < bb.position(); i++) {
			char ch = (char)arr[i];
			if( ch < 0 ) {
				ch += 256;
			}
			if( ch >= ' ' && ch <= '}' ) {
				System.out.print(ch);
			} else {
				System.out.print("[");
				System.out.print(Integer.toHexString(ch));
				System.out.print("]");
			}
		}
		System.out.println();

		for (AdapterInterface d : probes) {
			AdapterInterface probe_driver = d;
			if (probe_driver.verify(arr, bb.position() )) {

				RpDevice conf = probe_driver.getConfiguration();
				driver = DeviceFactory.createDriver(conf);

				break;
			}
		}

		if (driver != null) {
			System.out.println("jsc identified driver:" + driver.getConfiguration().getName() + " AT " + driver.getConfiguration().getConnectionValue() );
		}

		return driver;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		DeviceConfiguration conf = new DeviceConfiguration("discovery");

		for (AdapterInterface probe : probes) {
			RpDevice device = probe.getConfiguration();
			DeviceConfiguration sub = RpUtil.createDeviceConfiguration(device, false);
			conf.addDevice(sub);
		}
		return conf;
	}

	private DeviceConfiguration getConfiguration(String canonicalName, SerialPort port) {
		for (AdapterInterface probe : probes) {
			RpDevice device = probe.getConfiguration();
			if (canonicalName.equals(device.getName())) {
				return RpUtil.createDeviceConfiguration(device, false);
			}
		}
		log.error("NO CONFIG FOR DEV: {} port: {}", canonicalName, port);

		// conf = RpUtil.createDeviceConfiguration(dev, true);
		//
		// conf.setConnectionType(RpConnType.RS_232);
		// conf.setConnectionValue(port.getSystemPortName());
		// // CHECK FOR DUPLICATES AND RENAME
		// if (conf.getName() == null) {
		// conf.setName(canonicalName);
		// }
		// String baseName = conf.getName();
		//
		// int idx = 0;
		// boolean exists;
		// do {
		// exists = false;
		// idx++;
		// String name = conf.getName();
		//
		// for (AdapterInterface s : serial_drivers) {
		// if (s == null) {
		// // ignore
		// } else {
		// String existing_name = s.getConfiguration().getName();
		// if (name.equals(existing_name)) {
		// exists = true;
		// conf.setName(baseName + idx);
		// break;
		// }
		// }
		// }
		// } while (exists == true);
		// return conf;

		return null;
	}

	@Override
	public void tick() { // sends ticks to the drivers

		System.out.println("tick: " + (System.currentTimeMillis() - debugStartTime) / 1000 );
		// no serial ports to probe.
		if (serial_ports == null) {
			return;
		}
		for (int i = 0; i < serial_ports.length; i++) {
			AdapterInterface driver = dev_inst[i];
			if (driver == null) {
				// ignore
			} else {
				timeout[i]++;

				if (timeout[i] > GENERAL_COMM_TIMEOUT) {
					try {
						driver.disconnect(); // this will send the disconnect
												// message
					} catch (IOException e) {
						log.error("Error in timeout/disconnect", e); // log and
																		// ignore
					}
					// lose() sends a discovery lost message...
					// but no reason this has to happen with disconnect
					remove(driver);
					dev_inst[i] = null;
				} else {
					driver.tick();
				}
			}
		}

	}

	public void tick_probes() throws IOException {
		if (probes.size() == 0) {
			// nothing to do...yet
			return;
		}

		if (serial_ports == null || serial_ports.length == 0) {
			// still nothing to do...yet
			return;
		}

		tick_counter++;
		tick_counter = tick_counter % serial_ports.length;

		connectPort(tick_counter); // try to reconnect one port / loop

		probeSetup_idx = (probeSetup_idx + 1) % probes.size();

		AdapterInterface probe_dev = probes.get(probeSetup_idx);
		if (probe_dev == null) {
			// nulls can be used intentionally to manage timing
			return;
		}

		probe_all_ports(probe_dev);
	}

	public void probe_all_ports(AdapterInterface probe_dev) throws IOException {

		log.info("polling dev: {} {}", probeSetup_idx, probe_dev.getClass().getName());

		for (int i = 0; i < serial_ports.length; i++) {

			SerialPort port = serial_ports[i];
			AdapterInterface driver = dev_inst[i];
			
			if (port.isOpen() && driver == null && prev_conn != null ) {
				// force a flush
				// log.error("FLUSH {} baud={} databits={}", port.getSystemPortName(), prev_conn.getBaud(), prev_conn.getDatabits());
				port.setComPortParameters(300, prev_conn.getDatabits(), prev_conn.getStopbits(), prev_conn.getParity());
				port.setComPortParameters(prev_conn.getBaud(), prev_conn.getDatabits(), prev_conn.getStopbits(), prev_conn.getParity());
			}
			driver = dev_inst[i];

			// port may be a USB port which will come and go.
			if (port.isOpen() && driver == null) {
				
				DeviceCapabilities caps = (DeviceCapabilities) probe_dev.getStaticCapabilities();
				RpConnection[] conns = caps.getConnections();
				SerialConnection conn = null;
				if (conns != null) {
					conn = (SerialConnection) conns[0];
					prev_conn = conn;
				}

				serial_buf[i].clear();
				probe_one_port(conn, probe_dev, port);
			}

		}
	}

	private void probe_one_port(SerialConnection conn, AdapterInterface probe_dev, SerialPort port) throws IOException {

		InputStream in = port.getInputStream();
		while (in.available() > 0) {
			in.read(); // read and discard
		}

		if (conn != null) {
			log.error("PROBE {} baud={} databits={}", port.getSystemPortName(), conn.getBaud(), conn.getDatabits());
			port.setComPortParameters(conn.getBaud(), conn.getDatabits(), conn.getStopbits(), conn.getParity());
		}

		OutputStream out = port.getOutputStream();

		probe_dev.probe(out);
	}

	public void setPorts(String[] portList) {

		int count = portList.length;

		serial_ports = new SerialPort[count];
		dev_inst = new AdapterInterface[count];
		status_message = new String[count];
		serial_buf = new ByteBuffer[count];
		timeout = new int[count];

		for (int i = 0; i < portList.length; i++) {
			dev_inst[i] = null;
			serial_ports[i] = SerialPort.getCommPort(portList[i]);
			serial_buf[i] = ByteBuffer.allocate(128); // each device defaults to
														// 128 bytes of data for
														// probe recognition
			status_message[i] = "Initializing...";
		}

	}

	private void connectPort(int i) {

		SerialPort port = serial_ports[i];
		if (!port.isOpen()) {

			boolean ok = port.openPort();
			if (ok == false) {
				log.warn("could not open port: {}", port.getSystemPortName());
			} else {
				port.addDataListener(this);
			}
		}
	}

	public SerialPort[] getPorts() {
		return serial_ports;
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
			if (rec.getDriver() != null) {
				log.error("FIXME: is this right?: DEVICE ALREADY CONNECTED: {}", req_name);
				return rec.getDriver();
			}
		}

		//
		// this is the serial discovery adapter...should be serial devices
		//
		AdapterInterface driver = DeviceFactory.createDriver(conf);
		if (driver == null) {
			log.error("Could not create driver: {}", conf.getDeviceClass());
			return null;
		}

		int port_idx = -1;
		String src = conf.getConnectionValue(); // COM1...
		for (int i = 0; i < serial_ports.length; i++) {
			SerialPort port = serial_ports[i];
			// Handles this inconsistent //./COM99
			System.out.println("checking: " + src + "?=" + port.getSystemPortName() + " ?=" + port.getDescriptivePortName() + " ?= " + port.toString());
			String systemName = port.getSystemPortName();
			String descName = port.getDescriptivePortName();
			String rawName = port.toString();
			
			
			if ( systemName != null && systemName.endsWith(src) ) {
				port_idx = i;
				break;
			}
			if ( descName != null && descName.endsWith(src) ) {
				port_idx = i;
				break;
			}
			if ( rawName != null && rawName.endsWith(src) ) {
				port_idx = i;
				break;
			}
			String targName = "(" + systemName + ")";
			
			if ( src.indexOf(targName) > 0 ) {
				port_idx = i;
				break;
			}
			if ( targName.indexOf(src) > 0 ) {
				port_idx = i;
				break;
			}
		}

		if (port_idx < 0) {
			log.error("Requested port not managed by discovery: {}", src);
			probes.add(driver);
		} else {

			log.error("discovery-assigning driver port {} assigned: {}", serial_ports[port_idx], driver);

			dev_inst[port_idx] = driver;

			SerialPort port = serial_ports[port_idx];
			log.error("FIXME: At this point, the port is not set for the right baud rate.");
			log.error("There may be a better way to do this...???  Just let the device be discovered???");
			log.error("Restrict probing on this port to the indicated device???");
			StringStringMap params = conf.getParam();
			String s_baud = params.get("baud");
			int baud = 9600;
			int databits = 8;
			int stopbits = 1;
			int parity = SerialPort.NO_PARITY;  // 0
			if( s_baud != null ) {
				baud = Integer.parseInt(s_baud);
			}
			port.setComPortParameters( baud, databits, stopbits, parity);

			log.error("FIXME: all providers must do the same thing! addDevice or not!");
			log.error("DUPLICATE!!! ...check with DiscoveryService line 182");
			// this.addDevice(driver, port.getSystemPortName());
		}

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
					tick();

				} catch (Exception ee) {
					ee.printStackTrace();
					log.warn("tick err!");
				}

			}

		}, 1000L, TICK_TIMER_INTERVAL);
	}

	public static JSerialCommDiscoveryWorker getInstance() {
		return service;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		log.error("FIXME: getStaticCapabilities() stub");
		return null;
	}

	/**
	 * getListeningEvents() is a jSerialComm method. See docs.
	 * 
	 * @see com.fazecast.jSerialComm.SerialPortDataListener#getListeningEvents()
	 */
	@Override
	public int getListeningEvents() {
		return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
	}

}
