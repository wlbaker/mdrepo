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
import java.util.List;

import com.fazecast.jSerialComm.SerialPort;
import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import icuInterface.message.AbstractItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.SerialConnection;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.AS50_Measurement;
import idea.model.dev.AS50_Settings;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class AS50Driver extends SerialAdapter {

	private static final String driverName = "pump/Baxter AS50";

	private static int verbose = 0;

	private LinkedList<AbstractItem> settings;

	private SerialDeviceConfiguration conf;

	protected static DeviceCapabilities cap;
	protected int serialNo;
	private int crc = -1;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(AS50Driver.class);
	}

	int mb_offset = 0;
	byte[] mb_buffer;
	int tick = 0;
	private Boolean enableInfuse;
	private AS50_Measurement block;

	private Object lastLoc;

	static {

		cap = new DeviceCapabilities(AS50Driver.class);

		cap.addStream(StreamID.MEASUREMENT, AS50_Measurement.class);
		cap.addStream(StreamID.SETTINGS, AS50_Settings.class);

		cap.addConnection(
				new SerialConnection(9600, 8, 1, SerialPort.NO_PARITY));

		cap.setModels(new String[] { "AS50" });
	}

	public AS50Driver(RpDevice conf) {
		super(conf);

		mb_buffer = new byte[256];

		AdapterUtil.fix_config(cap, conf);

	}

	@Override
	public void connect() throws IOException {

		connect(conf.getPort(), 9600, 8, 1, 0);

	}

	@Override
	public void disconnect() throws IOException {
		sendPacket("EXIT");
		super.disconnect();
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {

		while (true) {
			int byt = in.read();
			if (mb_offset >= mb_buffer.length) {
				mb_offset = 0; // dump anything received so far
			}

			if (byt < 0)
				break;

			if (byt == '[') {
				// start of message
				mb_offset = 0;
				crc = -1;
			} else if (byt == ']') {
				crc = 2;
			}

			mb_buffer[mb_offset++] = (byte) byt;
			if (crc == 0) {
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

			enableInfuse = null;
			// sendPacket(pumpId,
			// "INFUSTYP?;MODEL?;REV?;ACCMODE?;MODE?;ECD?");
			// sendPacket(pumpId, "PCMODE=PUMP");

			String message = buildPumpSettingsString();
			if (message.length() > 0) {
				sendPacket(message.toString());
			}

			if (enableInfuse == null) {
				// ignore
			} else if (enableInfuse) {
				sendPacket("INFUSE=ON");
			} else {
				sendPacket("INFUSE=OFF");
			}
		}

	}

	private String buildPumpSettingsString() throws IOException {
		StringBuffer message = new StringBuffer();
		boolean first = true;

		LinkedList<AbstractItem> sent = null;

		for (AbstractItem item : settings) {
			String key = item.getDescription().getLocation();

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

		if (verbose > 0) {
			String ss = new String(message, 0, len);
			System.out.println("received: " + ss);
		}

		if (len < 6) {
			return; // invalid message
		}

		int crc = CRCUtil.getCRC16forC2(message, len - 2);
		int crc0 = crc / 256;
		int crc1 = crc % 256;

		int rcrc0 = message[len - 2];
		int rcrc1 = message[len - 1];
		if (rcrc0 < 0) {
			rcrc0 += 256;
		}
		if (rcrc1 < 0) {
			rcrc1 += 256;
		}

		if (crc0 == rcrc0 && crc1 == rcrc1) {
			// ok
		} else {
			System.err.println("crc err");
		}

		tick = 0;

		String pair = new String(message, 0, len);
		int lst = pair.indexOf(']');
		pair = pair.substring(1, lst);

		int idx = pair.indexOf('=');

		if (idx < 0) {
			if (pair.startsWith("REJECT")) {
				// yeah, we know we're not handling this.
				// can result from PROTOCOL request in some modes
			} else if (pair.startsWith("RESEND")) {
				System.err.println("AS50 resend request: ??");
			} else {
				System.err.println("as50 could not parse: " + new String(message, 0, len));
				System.err.println("           pair: " + pair);
			}
		} else {
			String key = pair.substring(0, idx);
			String val = pair.substring(idx + 1);

			if (block == null) {
				block = new AS50_Measurement();
			}

			log.error("Must account for whether this is a TXT or a numeric field");
			IntfUtil.setValue(block, key, val);

			if (key.equals(lastLoc)) {
				fireStreamEvent(0, this, StreamID.MEASUREMENT, block);

				block = null;
			}
		}

	}

	private void fireNoData() {
		fireNoData(conf);
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, cap);
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

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	/*
	 * *************************************************************************
	 * Requests
	 * *************************************************************************
	 */

	public void requestSerialNo() throws IOException {
		serialNo = 0;
		sendPacket("DEVADDR?");
	}

	public void requestStatus() throws IOException {
		RpStream stream = null;
		if (conf != null) {
			stream = conf.getStream(StreamID.MEASUREMENT);
		}
		if (stream != null) {
			List<RpMetric> metrics = stream.getMetric();
			RpMetric last = null;
			for (RpMetric metric : metrics) {
				sendPacket(metric.getLocation() + "?");
				last = metric;
			}

			// used to trigger fire-numerics
			if (last != null) {
				lastLoc = last.getLocation();
			}

		}
	}

	public void requestAlarms() throws IOException {
	}

	private void sendPacket(String message) throws IOException {

		int capacity = 2 + 4 + 2 + 1 + 4; // <A dddd A: <message> > xxxx
		if (message != null)
			capacity += message.length();

		ByteBuffer bb = ByteBuffer.allocate(capacity);
		bb.put((byte) '[');
		if (message != null) {
			bb.put(message.getBytes());
		}
		bb.put((byte) ']');

		int crc = CRCUtil.getCRC16forC2(bb.array(), bb.position());
		int crc0 = crc / 256;
		int crc1 = crc % 256;

		bb.put((byte) crc0);
		bb.put((byte) crc1);

		OutputStream out = getOutputStream();
		synchronized (out) {
			out.write(bb.array(), 0, bb.position());
		}

		if (verbose > 0) {
			System.out.print("[AS50 Driver] to device: ");
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

		ConnectionStatus deviceState = this.getStatus();
		if (deviceState == ERROR) {
			return -1;
		}
		if (tick > 12) {

			if (deviceState != NOT_CONNECTED) {
				deviceState = NOT_CONNECTED;
				setStatus(ConnectionStatus.NOT_CONNECTED);
				fireNoData();
			}

		} else {
			if (deviceState == NEGOTIATING) {
				// ??
			} else if (deviceState != CONNECTED) {
				deviceState = CONNECTED;
				setStatus(CONNECTED);
			}
		}

		if (tick > 1 && (tick % 2 == 1)) {
			try {
				requestStatus();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return 0;
	}

}
