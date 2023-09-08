package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.ERROR;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.util.LinkedList;

import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import icuInterface.message.AbstractItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.C2Measurement;
import idea.model.dev.C2Settings;
import idea.schema.rp.RpMetric;

public class C2Driver extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "pump/Gemini(?) C2";
	private static int verbose = 0;

	private static final byte[] hex = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
			'F' };
	private LinkedList<AbstractItem> settings;

	private boolean connected = false;

	protected static DeviceCapabilities cap;
	protected int serialNo;
	private int crc = -1;

	public static DeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(C2Driver.class);
	}

	int mb_offset = 0;
	byte[] mb_buffer;
	int tick = 0;
	private Boolean enableInfuse;
	private final static String[] mode_fields = { "*MDEV", "*MCON", "*MPIG", "*MINF", "*MACT" };

	static {
		cap = new DeviceCapabilities(C2Driver.class);

		cap.addStream(StreamID.MEASUREMENT, C2Measurement.class);
		cap.addStream(StreamID.SETTINGS, C2Settings.class);

		cap.addConnection(new SerialConnection(9600, 8, 1, 0));

		cap.setModels(new String[] { "980", "PC-1", "PC-2", "PC-4", "PC-2TX" });
	}

	public C2Driver(DeviceConfiguration conf) {
		super(conf);

		mb_buffer = new byte[256];

		AdapterUtil.fix_config(cap, conf);
	}

	@Override
	public void connect() throws IOException {
		String portName = RpUtil.getParam(conf, "port");

		connected = false;
		tick = 0;
		setStatus(NEGOTIATING);

		super.connect(portName, 9600, 8, 1, 0);

		//hw_port.notifyOnDataAvailable(true);
		hw_port.setDTR();
		hw_port.setRTS(); // note, you must do this AFTER setting port
		// speed

	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		while (true) {
			int byt = in.read();

			if (verbose > 0) {
				System.out.print(Integer.toHexString(byt));
				System.out.print(".");
			}
			if (mb_offset >= mb_buffer.length) {
				mb_offset = 0; // dump anything received so far
			}

			if (byt < 0)
				break;

			if (byt == '<') {
				// start of message
				mb_offset = 0;
				crc = -1;
			} else if (byt == '>') {
				// System.out.print(" read: ");
				crc = 4;
			}

			mb_buffer[mb_offset++] = (byte) byt;
			if (crc == 0) {
				connected = true;
				processResponse(mb_buffer, mb_offset);
				processSettings();
				settings = null;
				mb_offset = 0;
				crc--;
			}

			if (crc > 0) {
				crc--;
			}
		}
	}

	private void processSettings() throws IOException {
		if (settings != null && settings.size() > 0) {
			String[] pumps = { "A", "B", "C", "D" };

			for (String pump : pumps) {
				byte pumpId = pump.getBytes()[0];

				enableInfuse = null;
				// sendPacket(pumpId,
				// "INFUSTYP?;MODEL?;REV?;ACCMODE?;MODE?;ECD?");
				// sendPacket(pumpId, "PCMODE=PUMP");

				String message = buildPumpSettingsString(pump);
				if (message.length() > 0) {
					sendPacket(pumpId, message.toString());
				}

				if (enableInfuse == null) {
					// ignore
				} else if (enableInfuse) {
					sendPacket(pumpId, "INFUSE=ON");
				} else {
					sendPacket(pumpId, "INFUSE=OFF");
				}
			}
		}

	}

	private String buildPumpSettingsString(String pump) throws IOException {
		StringBuffer message = new StringBuffer();
		boolean first = true;

		LinkedList<AbstractItem> sent = null;
		for (AbstractItem item : settings) {
			String key = item.getDescription().getLocation();
			if (!key.startsWith(pump)) {
				continue; // not this pump
			}

			if (sent == null) {
				sent = new LinkedList<AbstractItem>();
			}
			sent.add(item);

			key = key.substring(1);

			Number val = (Number) item.getValue();
			int ival = val.intValue();
			String sval = null;
			if (key.equals("INFUSE")) {
				if (ival == 0)
					enableInfuse = false;
				else if (ival == 1)
					enableInfuse = true;
				else {
					assert (false) : "Invalid INFUSION value: " + ival;
					sval = "" + ival;
				}
			} else if (key.equals("ZERO")) {
				key = "VINF";
				if (ival == 1) {
					sval = "0";
				}
			} else {
				sval = "" + ival;
			}

			if (sval != null) {
				if (first) {
					// nothing special
					first = false;
				} else {
					message.append(';');
				}
				message.append(key);
				message.append("=");
				message.append(sval);
			}

		}

		if (sent != null) {
			for (AbstractItem item : sent) {
				settings.remove(item);
			}
		}

		return message.toString();
	}

	private void processResponse(byte[] message, int len) throws IOException {

		//
		// System.out.println("received: " + new String(message, 0, len));
		//

		if (len < 13) {
			return; // invalid message
		}

		byte[] s_crc = new byte[4];
		byte[] s_rcv = new byte[4];

		int crc = CRCUtil.getCRC16forC2(message, len - 4);
		int crc0 = crc / 256;
		int crc1 = crc % 256;

		// <A1234A:RATE@129;VTBI@0>92A7

		s_crc[0] = hex[crc0 / 16];
		s_crc[1] = hex[crc0 % 16];
		s_crc[2] = hex[crc1 / 16];
		s_crc[3] = hex[crc1 % 16];

		s_rcv[0] = message[len - 4];
		s_rcv[1] = message[len - 3];
		s_rcv[2] = message[len - 2];
		s_rcv[3] = message[len - 1];

		String sc = new String(s_crc);
		String sr = new String(s_crc);
		if (sc.equals(sr)) {
			// this message passes the checksum
		} else {
			System.err.println("CHK error: " + sc + " <> " + sr);
			dump(System.err, message, len);
			return;
		}

		tick = 0;
		// s = "<A1234A:RATE@129;VTBI@0>92A7";

		String s = new String(message, 0, len);
		int idx = s.indexOf(':');
		String id = s.substring(1, idx);
		int lst = s.indexOf('>');
		s = s.substring(idx + 1, lst);

		String[] pairs = s.split(";");

		C2Measurement block = new C2Measurement(this);

		char ack_nak = id.charAt(0);
		char channel = id.charAt(5);

		if (ack_nak != 'A') {
			System.err.println("ack-nak=" + ack_nak);
		}

		for (String pair : pairs) {
			idx = pair.indexOf('@');
			if (idx < 0) {
				System.err.println("c2 could not parse: " + new String(message, 0, len));
				System.err.println("           data: " + s);
				System.err.println("           pair: " + pair);
				continue;
			}
			String key = pair.substring(0, idx);
			String val = pair.substring(idx + 1);

			if (key.equals("MODE") && val.length() > 6) {
				val = val.substring(1, val.length() - 1); // clip opening and
															// closing parenth
				String[] vals = val.split("[,]");

				assert (vals.length == mode_fields.length) : "C2Driver: incorrect number of values for mode field";
				int pos = 0;
				for (String sub_key : mode_fields) {
					addTextField(block, channel, sub_key, vals[pos++]);
				}
			} else {
				addNumericField(block, channel, key, val);
			}
		}
		fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
	}

	private void addTextField(C2Measurement block, char channel, String key, String val) {
		String loc = channel + key;

		IntfUtil.setValue(block, loc, val);
	}

	private void addNumericField(C2Measurement block, char channel, String key, String val) {
		String loc = channel + key;

		Number value = Double.parseDouble(val);
		IntfUtil.setValue(block, loc, 10 * value.doubleValue());
	}

	private void fireNoData() {
		fireNoData(conf);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	public void configureMetrics(RpMetric[] metrics) throws IOException {
		if (metrics == null) {
			return;
		}

		// sendPacket(ESC, CONFIG_DATA, configReq);
	}

	/*
	 * *************************************************************************
	 * Requests
	 * *************************************************************************
	 */

	public void requestSerialNo() throws IOException {
		serialNo = 0;
		sendPacket((byte) 'A', "RATE?;VTBI?");
		// sendPacket( null );
	}

	public void requestStatus(byte pumpId) throws IOException {
		serialNo = 0;
		sendPacket(pumpId, "RATE?;VTBI?;VINF?;MODE?");
	}

	public void requestAlarms() throws IOException {
	}

	private void sendPacket(byte pump, String message) throws IOException {

		int capacity = 2 + 4 + 2 + 1 + 4; // <A dddd A: <message> > xxxx
		if (message != null)
			capacity += message.length();

		String dest = "1234";

		ByteBuffer bb = ByteBuffer.allocate(capacity);
		bb.put((byte) '<');
		bb.put((byte) 'A');
		bb.put(dest.getBytes());
		bb.put(pump);
		bb.put((byte) ':');
		if (message != null) {
			bb.put(message.getBytes());
		}
		bb.put((byte) '>');

		int crc = CRCUtil.getCRC16forC2(bb.array(), bb.position());
		int crc0 = crc / 256;
		int crc1 = crc % 256;

		bb.put(hex[crc0 / 16]);
		bb.put(hex[crc0 % 16]);
		bb.put(hex[crc1 / 16]);
		bb.put(hex[crc1 % 16]);
		// bb.put(CR);

		OutputStream out = getOutputStream();
		synchronized (out) {
			out.write(bb.array(), 0, bb.position());
		}

		if (verbose > 0) {
			dump(System.out, bb.array(), bb.position());
		}
	}

	private void dump(PrintStream out, byte[] array, int len) {
		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 80 == 0)) {
				out.println();
			}

			int byt = array[i];
			if (byt < 0)
				byt += 256;

			if (byt > 0x20 && byt < 0x80) {
				out.print((char) byt);
			} else {
				out.print("[");
				out.print(Integer.toHexString(byt));
				out.print("]");
			}
		}
		out.println();

	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (deviceState == ERROR) {
			return -1;
		}
		int max_tick = (connected) ? 10 : 4;

		if (tick > max_tick) {
			if (deviceState != NOT_CONNECTED) {
				connected = false;
				setStatus(ConnectionStatus.NOT_CONNECTED);
				fireNoData();
			}
		} else {
			if (!connected) {
				if (deviceState != NEGOTIATING) {
					setStatus(ConnectionStatus.NEGOTIATING);
				}
			} else if (deviceState != CONNECTED) {
				setStatus(ConnectionStatus.CONNECTED);
			}
		}

		try {
			if (getOutputStream() == null) {
				if (verbose > 0) {
					System.err.println("C2: port not created for tick()");
				}
				// else ignore
			} else {
				requestStatus((byte) 'A');
				requestStatus((byte) 'B');
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return 0;
	}

}
