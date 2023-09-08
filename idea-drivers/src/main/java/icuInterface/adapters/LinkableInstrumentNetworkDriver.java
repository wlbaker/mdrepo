package icuInterface.adapters;

//
// Driver for MasterFlex pumps using their protocol: LinkableInstrumentNetwork
//

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.text.DecimalFormat;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.model.dev.LinkableInstrumentsMeasurement;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class LinkableInstrumentNetworkDriver extends SerialAdapter {

	private static final String driverName = "pump/Linkable Instruments - MasterFlex";

	private final static byte ESC = 0x1b;
	private final static byte CR = 0x0d;

	private final static byte STX = 0x02;
	private final static byte[] ENQ = { 0x05 };

	private final static byte NAK = 0x15;
	private final static byte ACK = 0x06;
	private static final int MAX_RETRIES = 3;

	private static DeviceCapabilities cap;

	private int tick;

	int mb_offset = 0;
	byte[] mb_buffer = new byte[128];
	private byte[] last_command;
	private int next_id = 1;
	private int nak_count;
	// @Getter
	private byte[] assigned_id;

	private String model;

	static {
		cap = new DeviceCapabilities(LinkableInstrumentNetworkDriver.class);

		cap.addStream(StreamID.SETTINGS, LinkableInstrumentsMeasurement.class);
		cap.addStream(StreamID.MEASUREMENT, LinkableInstrumentsMeasurement.class);

		cap.addConnection(new SerialConnection(4800, 7, 1, 1));
	}

	public byte[] getAssignedId() {
		return assigned_id;
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(EvitaDriver.class);
		conf.addStream(StreamID.SETTINGS, LinkableInstrumentsMeasurement.class);
		conf.addStream(StreamID.MEASUREMENT, LinkableInstrumentsMeasurement.class);
		return conf;
	}

	public LinkableInstrumentNetworkDriver(RpDevice conf) {
		super(conf);

		AdapterUtil.fix_config(cap, conf);
	}

	@Override
	public void connect() throws IOException {
		String portName = RpUtil.getParam(conf, "port");

		mb_offset = 0;
		next_id = 1;
		tick = 99;

		connect(portName, 4800, 7, 1, 1);
	}

	@Override
	public void disconnect() throws IOException {

		super.disconnect();
	}

	
	public void sendInquiry() throws IOException {

		OutputStream out = getOutputStream();
		if (out == null) {
			return;
		}

		synchronized (out) {
			out.write(ENQ);
		}
	}

	public void sendHalt() throws IOException {

		OutputStream out = getOutputStream();
		if (out == null) {
			return;
		}

		String cmd = "H";
		sendRequest(out, (byte) 'P', assigned_id, cmd );
	}

	public void sendRequest(OutputStream out, byte command, byte[] id, String arg) throws IOException {

		if (out == null) {
			log.error("no output stream available.  early tick?");
			return; // probably tick called before we are ready
		}

		int capacity = 5;
		if (arg != null)
			capacity += arg.length();
		ByteBuffer bb = ByteBuffer.allocate(capacity);
		// bb.order( ByteOrder.BIG_ENDIAN );

		bb.put(STX);
		bb.put(command);
		bb.put(id);

		if (arg != null) {
			bb.put(arg.getBytes());
		}

		bb.put(CR);
		last_command = bb.array();

		synchronized (out) {
			out.write(bb.array());
		}

		if (log.isDebugEnabled()) {
			// log.debug("to device: ");
			dump("send: ", System.out, bb.array(), bb.position());
		}
	}

	public void setSpeedAndRevolutions( double rpm, double revs, boolean forward ) throws IOException {	
		OutputStream out = hw_port.getOutputStream();
		
		if( rpm < 0) {
			forward = !forward;
			rpm = -rpm;
		}
		
		String ind = (forward) ? "+" : "-";
		String cmd = String.format("S%s%05.1fV%06.2fG", ind, rpm, revs);
		sendRequest(out, (byte) 'P', assigned_id, cmd );
	}
	
	private static void dump(String pfx, PrintStream out, byte[] array, int len) {

		out.print(pfx);

		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 20 == 0)) {
				out.println();
			}

			int byt = array[i];
			if (byt < 0)
				byt += 256;
			out.print(Integer.toHexString(byt));
			if (byt > 0x20 && byt < 0x80) {
				out.print("("); // b
				out.print((char) byt);
				out.print(")");
			}
			out.print(" ");
		}
		out.println();
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {

		while (in.available() > 0) {
			int byt = in.read();

			// System.out.print(" " + Integer.toHexString(byt) + "[" + (char) byt + "]");

			if (mb_offset >= mb_buffer.length || byt == STX) {
				mb_offset = 0; // no overflows
			}

			if (byt == NAK) {
				resend();
				nak_count++;
				if (nak_count > MAX_RETRIES) {
					log.error("TOO MANY NAKS");
					last_command = null;
				}
			} else if (byt == CR) {
				if (mb_buffer[0] == STX) {
					processResponse(out, mb_buffer, mb_offset);
				} else {
					log.error("unexpected CR...invalid message");
				}
				mb_offset = 0;

			} else if (byt < 0) {
				log.error("7-bit ASCII only?");
			} else {
				mb_buffer[mb_offset++] = (byte) byt;
			}

		}
	}

	private void resend() throws IOException {
		if (last_command != null) {
			OutputStream out = getOutputStream();

			synchronized (out) {
				out.write(last_command);
			}
		}
	}

	private void processResponse(OutputStream out, byte[] message, int len) throws IOException {

		if (len < 4) {
			return; // NO DATA!
		}
		// dump("process: ", System.out, message, len);

		ByteBuffer bb = ByteBuffer.wrap(message, 0, len);
		byte byt = bb.get(); // stx or ack
		if (byt == ACK) {
			System.out.println("ACK[" + len + "]");

			last_command = null;
			nak_count = 0;
			return;
		} else if (byt == STX) {
			// proceed
		} else {
			log.error("UNKNOWN MESSAGE TYPE: {}", byt);
		}
		byte command = bb.get();
		// System.out.println( "CMD[" + (char)command + "]");

		switch (command) {
		case 'P':
			byte id0 = bb.get();
			byte id1 = bb.get();
			// System.out.println( "LINSTR P--" + (char) id0 + (char)id1);
			if (id0 == '?' && (id1 == '0' | id1 == '2')) {
				// this is the initial pump id string
				
				// -- P?0 for 600 RPM 7550-30
				// -- P?2 for 100 RPM 7550-50
				model = "UNKNOWN";
				if( id1 == '0') model = "600 RPM 7550-30"; 
				if( id1 == '2') model = "100 RPM 7550-50"; 
				
				assigned_id = String.format("%02d", next_id).getBytes();
				sendRequest(out, (byte) 'P', assigned_id, null);
				next_id++;
			} else {
				processPumpMessage(out, bb);
			}
			break;
		case 'C': // max revolutions
			break;
		case 'E': // revolutions to go
			break;
		case 'A': // open/close
			break;
		case 'K': // ?
			break;

		case 'S': // speed
			bb = ByteBuffer.wrap(message, 2, len - 2);
			parseAndFire(bb, StreamID.MEASUREMENT);
			break;
		default:
			log.warn("Unrecognized response: command=0x{}", Integer.toHexString(command));

		}
	}

	private void processPumpMessage(OutputStream out, ByteBuffer bb) {

		int n = bb.remaining();
		byte code = bb.get();

		//System.out.println(
		//"PROCESS: " + code + "==" + ((char) code) 
		//+ " lim=" + bb.limit() + " r=" + n + " pos=" + bb.position());

		switch (code) {
		case 'I':
			byte opstat = bb.get();
			byte aux_output = bb.get();
			byte aux_input = bb.get();
			byte pump_stat = bb.get();
			byte comm_stat = bb.get();
			// System.out.println("pump stat: " + pump_stat);
			
			// this may be the result of a poll while in an un-connected state
			if( assigned_id == null ) {
				assigned_id = String.format("%02d", next_id).getBytes();
				setStatus(ConnectionStatus.CONNECTED);
			}
			break;
		case 'P':
			byte id0 = bb.get();
			byte id1 = bb.get();
			if (id0 == '?' && id1 == '0') {
				assigned_id = String.format("%02d", next_id).getBytes();
				try {
					System.out.println("assigning id: " + new String(assigned_id));
					sendRequest(out, (byte) 'P', assigned_id, null);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				next_id++;
			} else {
				System.out.println("GOT A P"); // processPumpMessage(id1, bb);
			}
			break;
		case 'C': // max revolutions
			break;
		case 'E': // revolutions to go
			break;
		case 'A': // open/close
			break;
		case 'K': // ?
			break;

		case 'S': // speed
			System.out.println("FIXME: Handle speed"); // : bb = ByteBuffer.wrap(message, 2, len - 2);
			parseAndFire(bb, StreamID.MEASUREMENT);
			break;
		default:
			log.error("unknown pump message: 0x{}=={}", Integer.toHexString(code), (char) code);
		}
	}

	private void parseAndFire(ByteBuffer bb, StreamID subset) {

		LinkableInstrumentsMeasurement block = new LinkableInstrumentsMeasurement();
		block.setStreamID(subset.getCode());

		String s = "";
		while (bb.remaining() > 0) {

			s += (char) bb.get();
		}

		double rpm = Double.parseDouble(s);
		block.setRpm(rpm);

		fireStreamEvent(0, this, subset, block);
		tick = 0;
		this.setStatus(ConnectionStatus.CONNECTED);
	}

	private double getKeyValue(ByteBuffer bb) {
		StringBuffer ret = new StringBuffer();
		while (bb.hasRemaining()) {
			char v = (char) bb.get();
			if (v == CR || Character.isLetter(v)) {
				bb.position(bb.position() - 1);
				break;
			}
			ret.append(v);
		}
		double d = 0;
		if (ret.length() > 0) {
			d = Double.parseDouble(ret.toString());
		}
		return d;
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, cap);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	@Override
	public int tick() {
		tick++;

		try {
			ConnectionStatus deviceState = getStatus();
			// System.out.println(" " + deviceState + " tick=" + tick);
			if( hw_port == null || hw_port.isOpen() == false ) {
				setStatus(ConnectionStatus.NOT_CONNECTED);
			} else if ( assigned_id == null) {
				if (hw_port.getCTS()) { // hw_port.getCTS()) {
					sendInquiry();
				} else {
					OutputStream out = getOutputStream();
					if (out != null) {
						byte[] test_id = String.format("%02d", next_id).getBytes();						
						sendRequest(out, (byte) 'P', test_id, "I");
					}
				}

			} else {
				inquireStatus();  // connected or not...try
			}

			if (tick > 8) {
				if (deviceState != NOT_CONNECTED) {
					log.info("tick taking MASTERFLEX offline: {}", tick);
					setStatus(NOT_CONNECTED);
					fireNoData(conf);
				}
			}
		} catch (IOException e) {
			log.error("tick", e);
		}
		return 0;
	}

	public void inquireStatus() throws IOException {
		OutputStream out = getOutputStream();
		sendRequest(out, (byte) 'P', assigned_id, "I");
		sendRequest(out, (byte) 'P', assigned_id, "S");
	}

	public void requestSettingsUpdate(OutputStream out, PersistentItem settings) throws IOException {
		StringBuffer val = new StringBuffer();
		for (RpMetric metric : settings.getMetrics()) {
			String loc = metric.getLocation();
			val.append(loc);
			Double d = (Double) IntfUtil.getScaledValue(settings, metric);
			if (d != null) {
				DecimalFormat f = null;
				if ("S".equals(loc)) {
					if (d.doubleValue() >= 0) {
						val.append("+");
					}
					DecimalFormat df = new DecimalFormat("0000.0");
					val.append(df.format(d.doubleValue()));
				} else if ("V".equals(loc)) {
					DecimalFormat df = new DecimalFormat("00000.00");
					val.append(df.format(d.doubleValue()));
				}

			}
		}
		if (assigned_id == null) {
			log.error("device not indicated");
		} else if (val.length() > 0) {
			val.append("G");
			System.out.println("settings: " + val.toString());
			sendRequest(out, (byte) 'P', assigned_id, val.toString());
		}
	}

}
