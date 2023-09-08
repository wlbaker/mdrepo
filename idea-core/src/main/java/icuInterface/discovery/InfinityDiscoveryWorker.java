package icuInterface.discovery;

import java.io.IOException;
import java.io.PrintStream;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.MulticastSocket;
import java.net.SocketAddress;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import icuInterface.LoggingUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceFactory;
import idea.intf.AdapterInterface;
import idea.intf.StreamProducer;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class InfinityDiscoveryWorker extends DiscoveryProvider {

	/*
	 * the "1" here referes to the monitoring group...probably different in
	 * hospital!
	 */
	public final static int disc_port = 2150;
	public final static int ALARM_PORT = 2000; // UDP alarms sent
												// here...multicast...254
	public final static int DIAG_LOG_PORT = 7150; // you can telnet here and
													// press ENTER
	public final static int UNK_OPEN_PORT = 7100; // you can telnet here...dont
													// know what for...no
													// response
	public final static int ENQ_PORT = 1950; // you can telnet here...ENQ with
												// CRC...some session.

	private MulticastSocket s;
	byte buf[] = new byte[2048];
	DatagramPacket pack;
	InetAddress[] groups;

	int[] monitoringIDs = { 0, 1, 21, 59 };
	private boolean autoCreate;
	private RpDevice default_conf;

	String bind_interface = null; // "127.0.0.1";

	@Getter
	private List<DiscoveryListener> listeners = new LinkedList<DiscoveryListener>();
	private boolean networkLogging = false;

	@Getter
	@Setter
	private long timeout = 60000;

	public InfinityDiscoveryWorker() {
	}

	@Override
	public void start() {
		try {
			connect();
		} catch (IOException e) {
			log.error("connect", e);
		}

	}

	@Override
	public void stop() {
		try {
			disconnect();
		} catch (IOException e) {
			log.error("disconnect", e);
		}

	}

	public void setCreateDriverOnDiscover(boolean autoCreate, RpDevice default_conf) {
		this.autoCreate = autoCreate;
		this.default_conf = default_conf;
	}

	private void connect() throws IOException {

		s = null;

		if (bind_interface != null) {
			// for example, bind interface = "127.0.0.1"
			SocketAddress local = new InetSocketAddress(InetAddress.getByName(bind_interface), disc_port);
			s = new MulticastSocket(local);
		} else {
			s = new MulticastSocket(disc_port);
		}
		// s = new MulticastSocket(ALARM_PORT);

		// if this fails on linux, create /etc/sysctl.d/60-drager-wlb.conf
		// net/ipv4/igmp_max_memberships = 60

		// monitoring_unit_id is configured on the Drager network setup screen.

		groups = null;
		if (bind_interface == null) {
			groups = new InetAddress[monitoringIDs.length];
			int idx = 0;
			for (int monitoring_unit_id : monitoringIDs) {
				// String unitbdcast_ip = "224.127." + i + ".253"; // simple ip
				// address broadcast
				// String alarmbdcast_ip = "224.127." + i + ".254"; // active alarms
				String multicast_ip = "224.127." + monitoring_unit_id + ".255";
				InetAddress addr = InetAddress.getByName(multicast_ip);

				log.debug("joining: {}", multicast_ip);
				s.joinGroup(addr);

				groups[idx++] = addr;
			}
		}

		s.setSoTimeout(5000);

		// Now the socket is set up and we are ready to receive packets

		Runnable r = new Runnable() {

			@Override
			public void run() {

				try {
					pack = new DatagramPacket(buf, buf.length);

					for (;;) {
						log.debug("discovery waiting: {}", s.getPort());
						waitForData();
					}
				} catch (IOException e) {
					log.warn("InfinityDiscoveryWorker stopping: {}", e.getMessage());
				}

			}

		};

		Thread th = new Thread(r, "INFINITY_DISC");
		th.start();
	}

	private void disconnect() throws IOException {

		if (s != null) {
			if (groups != null) {
				for (InetAddress group : groups) {
					s.leaveGroup(group);
				}
			}
			s.close();

		}

	}

	private void waitForData() throws IOException {

		// Create a DatagramPacket and do a receive

		try {
			s.receive(pack);
			log.debug("got discovery pack: {}", pack.getAddress());
			DeviceRecord d2 = new DeviceRecord();
			boolean ok = parseDiscoveryPacket(d2, pack.getData(), pack.getLength());
			if (!ok)
				return;
			d2.setDiscoveryTime(System.currentTimeMillis());

			DeviceRecord rec = getDevice(d2.getUniqueID());
			if (rec == null) {
				if (autoCreate && default_conf != null) {

					for (DiscoveryIntf intf : d2.getIntfs()) {
						if (intf.getPort() == 2050) {
							RpDevice conf = default_conf;
//							// conf.setDeviceClass( "idea.driver.InfinityDriver");
							// String hostIp = ideviceIp[0] + "." + ideviceIp[1] + "." + ideviceIp[2] + "."
							// + ideviceIp[3];

							conf.setConnectionType(RpConnType.INFINITY);
							log.error("UNTESTED CODE in INFINITYDISCOVERYWORKER Device ADDR=" + intf.getAddr());
							// conf.setConnectionValue("infinity://224.0." + ideviceIp[2] + "." +
							// ideviceIp[3] + "/" + hostIp);
							conf.setConnectionValue("infinity://" + intf.getAddr());

							AdapterInterface driver = DeviceFactory.createDriver(conf);
							d2.setDriver(driver);
							break;
						}
					}
				}

				addDevice(d2);
			} else {
				log.debug("Refreshed device: {}", d2.getUniqueID());
			}

		} catch (SocketTimeoutException to) {
			// ok to timeout
		}

		remove_old();
	}

	private void remove_old() {
		Iterator<DeviceRecord> ii = getDevIterator();
		while (ii.hasNext()) {
			DeviceRecord d = ii.next();
			long tm = System.currentTimeMillis();
			if (tm - d.getDiscoveryTime() > timeout) {
				ii.remove();
				fireDiscoverEvent(DiscoveryAction.LOSE, d);
			}
		}

	}

	/*
	 * 
	 * Firmware VF8.3-W 2014-04-03 10:03:24,359 DEBUG
	 * [icuInterface.discovery.InfinityDiscoveryService] - DISCOVERED
	 * /192.168.192.168 2808 port=0 typ=7100 protocol=1 2014-04-03 10:03:24,359 INFO
	 * [idea.mpm.DiscoverySelectionPanel] - Discovered device:
	 * DeviceRecord(uniqueID=/192.168.28.110, fullName=2808, addressX=/28.110.0.0,
	 * portName=null, serialNo=6002591075, model=Delta, firmwareID=VF8.3-W, tm=0,
	 * intfs=[DiscoveryIntf(addr=/28.110.0.0, name=IDS2110, port=1, typ=0,
	 * protocol=0), DiscoveryIntf(addr=/192.168.192.168, name=2808, port=0,
	 * typ=7150, protocol=1), DiscoveryIntf(addr=/192.168.224.0, name=2808, port=0,
	 * typ=2050, protocol=4), DiscoveryIntf(addr=/192.168.224.127, name=2808,
	 * port=0, typ=2000, protocol=2), DiscoveryIntf(addr=/192.168.192.168,
	 * name=2808, port=0, typ=1950, protocol=2),
	 * DiscoveryIntf(addr=/192.168.192.168, name=2808, port=0, typ=7100,
	 * protocol=1)], driver=null, serialPort=null) intf:
	 * DiscoveryIntf(addr=/28.110.0.0, name=IDS2110, port=1, typ=0, protocol=0)
	 * intf: DiscoveryIntf(addr=/192.168.192.168, name=2808, port=0, typ=7150,
	 * protocol=1) intf: DiscoveryIntf(addr=/192.168.224.0, name=2808, port=0,
	 * typ=2050, protocol=4) intf: DiscoveryIntf(addr=/192.168.224.127, name=2808,
	 * port=0, typ=2000, protocol=2) intf: DiscoveryIntf(addr=/192.168.192.168,
	 * name=2808, port=0, typ=1950, protocol=2) intf:
	 * DiscoveryIntf(addr=/192.168.192.168, name=2808, port=0, typ=7100, protocol=1)
	 */

	public boolean parseDiscoveryPacket(DeviceRecord d, byte[] data, int len) throws UnknownHostException {

		if (networkLogging) {
			LoggingUtil.dumpSocketData(System.out, System.currentTimeMillis(), data, len);
		}

		byte[] deviceIp = new byte[4];
		ByteBuffer bb = ByteBuffer.wrap(data);
		bb.get(deviceIp); // source/device address
		int a1 = bb.getShort(); // connect id...0x0004
		int a2 = bb.getInt(); // 0x000001
		int msgSeq = bb.getInt();
		int a3 = bb.getInt(); // unk
		int a4 = bb.getShort();
		int monitorUnit = bb.get(); // timestamp ???
		int zero = bb.get();
		int a5 = bb.getShort();

		int pos = bb.position();
		while (pos < len) {
			short unknown_pfx = bb.getShort();

			int sep = bb.getShort();
			if (sep == 0) {
				break;
			}
			if (sep != '-') {
				log.error("UNEXPECTED SEP={}", sep);
			}
			int seglen = bb.getShort();
			int segcode = bb.get();
			byte[] seg = new byte[seglen - 7];
			bb.get(seg);
			ByteBuffer bb_seg = ByteBuffer.wrap(seg);

			log.debug("seglen ={} remaining={} segcode ={}", seglen, bb.remaining(), segcode);
			dump(System.out, segcode, seg, seg.length - 2);

			byte str_len = bb_seg.get();

			String segName = getSimpleString(bb_seg, str_len);

			switch (segcode) {
			case 1: {
				byte[] ip = new byte[4];
				bb_seg.get(ip);

				// this address is legit...I just dont need it
				//
				// InetAddress dev_addr = InetAddress.getByAddress(ip);
				// d.setAddressX(dev_addr);
				//
				// log.debug(" FQNAME: {}", dev_addr);
				//

				d.setFullName(segName);
			}
				break;
			case 13: {

				int unk_code = bb_seg.getShort(); // -89, 61
				int code1 = bb_seg.getShort(); // -65, -69
				int code2 = bb_seg.getShort(); // 00 00
				int code3 = bb_seg.getShort(); // 00 00

				if (unk_code < 0) {
					unk_code += 65536;
				}

				// unknown packet
				log.debug("  a73d CODE0: {}  CODE1: {} CODE2: {}", Integer.toHexString(unk_code), code1, code2);

				bb_seg.get(); // discard 3
				bb_seg.get(); // discard 1
				bb_seg.get(); // discard 9...or 0x02
				int fwid_len = bb_seg.get();
				int model_len = bb_seg.get();
				int serno_len = bb_seg.get();
				int unk_val_1 = bb_seg.get();
				int unk_val_0 = bb_seg.get();

				// WARNING: results when fwid_len or model_len are odd
				// is unknown.
				// Strings might be padded to an even number of chars
				String fw_id = getSimpleString(bb_seg, fwid_len);
				String model = getSimpleString(bb_seg, model_len);
				String serno = getSimpleString(bb_seg, serno_len);
				log.debug("  0301 SERNO PACKET: {} {} FIRMWARE: {}", model, serno, fw_id);

			}
				break;
			case 11: {
				byte[] ip = new byte[4];
				bb_seg.get(ip);

				InetAddress feature_addr = InetAddress.getByAddress(ip);
				short port = -1;
				short typ = -1;
				short protocol = -1;
				if (bb_seg.remaining() >= 2) {
					int zero_1 = bb_seg.getShort();
					log.debug("zero={}", zero_1);
					if (bb_seg.remaining() >= 12) {
						port = bb_seg.getShort();
						typ = bb_seg.getShort();
						protocol = bb_seg.getShort();
						short zero_2 = bb_seg.getShort();
						short f1 = bb_seg.getShort();
						short f2 = bb_seg.getShort();
						short f3 = bb_seg.getShort();
					}
				}
				log.debug("  DISCOVERED {} {} port={} typ={} protocol={}", feature_addr, segName, port, typ, protocol);
				d.addInterface(segName, feature_addr, port, typ, protocol);
			}
				break;
			case 5: {
				/*
				 * these features contain the host id, monitoring setup information, alarm
				 * group, etc
				 */
				byte[] mac = new byte[4];
				bb_seg.get(mac);
				byte[] ip = new byte[4];
				bb_seg.get(ip);
				int len1 = bb_seg.get();
				if (len1 != 1) {
					log.error("Unexpected len1={}", len1);
				}
				int len2 = bb_seg.get();
				int len3 = bb_seg.get();
				int len4 = bb_seg.get();

				String patName = getSimpleString(bb_seg, len2);
				String regNo = getSimpleString(bb_seg, len3);

				log.debug("patName: {}  regNo: {}", patName, regNo);
			}
				break;
			default:
				log.error("  UNKNOWN SEGMENT: {}", segcode);
				break;
			}

			pos += seglen;
		}

		d.setUniqueID(d.getFullName());

		return (d.getFullName() != null);
	}

	private String getSimpleString(ByteBuffer bb_seg, int len) {
		if (bb_seg.remaining() < 2 * len) {
			log.error("SAFE UNDERFLOW IN DISCOVER");
			return null;
		}
		char[] b = new char[len];
		for (int i = 0; i < len; i++) {
			b[i] = (char) bb_seg.getShort();
		}

		if ((len % 2) == 1) { // ID string is padded to an even length
			int discard0 = bb_seg.getShort();
			if (discard0 != 0) {
				log.error("NOT A TERMINATOR: " + len + " discard0=" + discard0);
			}
		}

		String s = new String(b);
		return s.trim();
	}

	private void dump(PrintStream out, int seg_code, byte[] array, int len) {
		if (log.isDebugEnabled()) {
			out.print(" seg " + seg_code + " [" + len + "]= ");
			out.print(" [l=" + (int) array[0] + "]");
			for (int i = 1; i < len; i++) {
				if ((i > 0) && (i % 160 == 0)) {
					out.println();
				}

				int hi_byt = array[i];
				if (hi_byt < 0)
					hi_byt += 256;
				i++;
				int lo_byt = array[i];
				if (lo_byt < 0)
					lo_byt += 256;

				int byt = 256 * hi_byt + lo_byt;

				if (byt > 0x20 && byt < 0x80) {
					out.print((char) byt);
				} else {
					if (byt == 0) {
						out.println();
						out.print("    ");
					}
					out.print("[");
					out.print(Integer.toHexString(byt));
					out.print("]");
				}
			}
			out.println();
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

		// int port_idx = -1;
		// String src = conf.getConnectionValue(); // COM1...
		// for (int i = 0; i < serial_ports.length; i++) {
		// SerialPort port = serial_ports[i];
		//// Handles this inconsistent //./COM99
		// if (port.getSystemPortName().endsWith(src)) {
		// port_idx = i;
		// break;
		// }
		// }

		log.error("FIXME: untested code");
		return driver;
	}

	@Override
	public RpDevice getStaticCapabilities() {
		log.error("FIXME: this device should provide static capabilities?");
		return null;
	}

	/**
	 * Set the interface to be bound. This value defaults to null. If the interface
	 * is specified, then there is no groupJoin. If the interface is not specified,
	 * then the operating system is assumed to route multicast packets to the
	 * desired interface.
	 * 
	 * @param bind_interface
	 */
	public void setBinding(String bind_interface) {
		this.bind_interface = bind_interface;
	}

	/**
	 * Monitoring units are specified in a comma-separated string.
	 * 
	 * @param s_units
	 */
	public void setMonitoringUnits(String s_units) {
		String[] arr = s_units.split("[ ,]+");
		int[] units = new int[arr.length];

		int idx = 0;
		for (String unit : arr) {
			units[idx++] = Integer.parseInt(unit);
		}

		monitoringIDs = units;
	}

}
