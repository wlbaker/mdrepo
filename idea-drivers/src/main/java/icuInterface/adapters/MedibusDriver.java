package icuInterface.adapters;

//
// TODO: This device can send RealtimeConfigurationChanged messages if gas
//       is changed during the run 
//
// TODO: C6h (p29) can be sent at start of ventilator inspiratory cycle, 
//       and should be logged as an event
//
// TODO: There are hardcoded values in the syncEnableTraces call to start RT 
//       on two channels.  0x03.
//

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.text.DateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import com.fazecast.jSerialComm.SerialPort;
import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.DriftRectifier;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class MedibusDriver extends SerialAdapter {

	private static final String driverName = "ventilator/Drager Medibus";

	private boolean isMetricConfigured = false;
	private boolean isCalibrationConfigured = false;
	private boolean isWaveConfigured = false;
	private boolean isTraceConfigured = false;
	boolean skip = false;

	private final static byte SOH = 0x01;
	private final static byte ESC = 0x1b;
	private final static byte CR = 0x0d;

	private final static byte DC1 = 0x11;
	private final static byte DC3 = 0x13;
	private final static byte NAK = 0x15;
	private final static byte CAN = 0x18;

	/*
	 * Ext RT commands
	 */

	private final static int SYNC_START = 0xd0; // first 4 bits
	private final static int SYNC_END = 0xc0; // full byte
	private final static int SYNC_CMD_MASK = 0xc0; // first 4 bits
	// ? private final static int SYNC_COMMAND = 0xc0; // first 4 bits

	/*
	 * Commands
	 */

	private final static byte MEASURED_DATA = 0x24;
	// ? private final static byte LOW_ALARM = 0x25;
	// ? private final static byte HIGH_ALARM = 0x26;
	private final static byte CURRENT_ALARMS = 0x27; // code-page 1...see also
	// 2D, current alarms
	// cp=2
	// ? private final static byte DATE_TIME = 0x28;
	private final static byte CURRENT_SETTINGS = 0x29;
	private final static byte TEXT_MESSAGES = 0x2A;
	// ? private final static byte CURRENT_ALARMS_CP2 = 0x2E; // same as 0x27,
	// different code page
	private final static byte NOP = 0x30;
	private final static byte CONFIG_DATA = 0x4a;
	private final static byte ICC = 0x51;
	private final static byte DEVICE_ID = 0x52;
	private final static byte REALTIME_CONFIG = 0x53;
	private final static byte REALTIME_TRANSMISSION = 0x54;
	private final static byte STOP = 0x55;

	/*
	 * data types
	 */

	private final static byte DT_DATA = 0x24;
	// private final static byte DT_ALARMS = 0x27;
	// private final static byte DT_DEVICE_SETTINGS = 0x29;
	// private final static byte DT_TEXT_MESSAGES = 0x2A;
	// private final static byte DT_DATA_CP2 = 0x2B;
	// private final static byte DT_ALARMS_CP2 = 0x2E;

	// caps cannot be static, since it is used by various drivers.
	private DeviceCapabilities cap;

	IntBuffer[] wf_data;

	private int baud;

	private DriftRectifier drifter = new DriftRectifier(2000, 1000, 11);

	protected final static int WF_PACKET_SIZE = 64;

	private static byte[] hex = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	private int tick;
	private int tick_measurement;

	public static int verbose = 0;

	private int noop_cycle = 0;

	private List<Alarm> lastAlarms = new LinkedList<Alarm>();

	int mb_offset = 0;
	int rt_offset = 0;
	int rt_expected = 0;
	byte[] mb_buffer = new byte[128];
	int[] rt_buffer = new int[128];

	int[] textCodes = new int[6];
	private boolean requiresNOOP;
	private boolean gotICC = false;
	private boolean hasSettings;
	Class<? extends PersistentItem> dataClass;
	Class<? extends PersistentItem> settingsClass;
	Class<? extends PersistentItem> waveformClass;

	public MedibusDriver(DeviceCapabilities caps, RpDevice conf, int baud, boolean requiresNOOP) {
		super(conf);

		tick = 99; // initially disconnected
		setStatus(NOT_CONNECTED);

		this.cap = caps;
		this.dataClass = (Class<? extends PersistentItem>) caps.getStream(StreamID.MEASUREMENT).getPIClass();
		this.settingsClass = (Class<? extends PersistentItem>) caps.getStream(StreamID.SETTINGS).getPIClass();
		this.waveformClass = (Class<? extends PersistentItem>) caps.getStream(StreamID.WAVEFORM).getPIClass();

		wf_data = new IntBuffer[4];

		wf_data[0] = IntBuffer.allocate(WF_PACKET_SIZE);
		wf_data[1] = IntBuffer.allocate(WF_PACKET_SIZE);
		wf_data[2] = IntBuffer.allocate(WF_PACKET_SIZE);
		wf_data[3] = IntBuffer.allocate(WF_PACKET_SIZE);

		this.baud = baud;
		this.requiresNOOP = requiresNOOP;
		System.out.println("requires noop: " + requiresNOOP);
		this.requiresNOOP = false;

		if (conf != null) {
			AdapterUtil.fix_config(cap, conf);

			List<? extends RpMetric> settings = RpUtil.getMetrics(conf, StreamID.SETTINGS);
			hasSettings = (settings != null && settings.size() > 0);
		}

		hasSettings = false; // FIXME: V500 override!

	}

	@Override
	public void connect() throws IOException {
		String portName = RpUtil.getParam(conf, "port"); // old method
		if (portName == null) {
			portName = conf.getConnectionValue(); // new method
		}
		if (portName == null) {
			throw new IOException("Port name not specified.");
		}

		mb_offset = 0;
		rt_offset = 0;
		rt_expected = 0;

		setStatus(ConnectionStatus.NEGOTIATING);
		connect(portName, baud, 8, 1, 0);

		System.err.println("hw_port.setDTR(); // added while testing Fabius");
		System.err.println("hw_port.setRTS();");

		sendRequest(ICC);
		isCalibrationConfigured = false;
		isMetricConfigured = false;
		isWaveConfigured = false;
		isTraceConfigured = false;

		tick = 4; // this is the negotiating start

	}

	@Override
	public void disconnect() throws IOException {
		sendRequest(STOP);

		super.disconnect();
	}

	private void sendResponse(byte commandCode) throws IOException {
		sendPacket(SOH, commandCode, null);
	}

	private void sendRequest(byte commandCode) throws IOException {
		sendPacket(ESC, commandCode, null);
	}

	private void sendRequest(byte commandCode, String arg) throws IOException {
		sendPacket(ESC, commandCode, arg);
	}

	private void sendPacket(byte pfx, byte commandCode, String arg) throws IOException {
		OutputStream out = getOutputStream();

		if (out == null) {
			return; // probably tick called before we are ready
		}

		// System.out.println("S: " + (int)commandCode );
		int capacity = 5;
		if (arg != null)
			capacity += arg.length();
		ByteBuffer bb = ByteBuffer.allocate(capacity);
		// bb.order( ByteOrder.BIG_ENDIAN );

		bb.put(pfx);
		bb.put(commandCode);

		if (arg != null) {
			bb.put(arg.getBytes());
		}

		int checksum = CRCUtil.getChecksum(bb.array(), 0, bb.capacity() - 3);
		checksum %= 256;
		bb.put(hex[checksum / 16]);
		bb.put(hex[checksum % 16]);
		bb.put(CR);

		synchronized (out) {
			out.write(bb.array());
		}

		if (verbose > 1 || log.isDebugEnabled()) {

			System.out.print("    to: ");
			dump(System.out, bb.array(), bb.position());
		}
	}

	private void sendByte(byte b) throws IOException {
		OutputStream out = getOutputStream();
		if (out != null) {
			synchronized (out) {
				out.write(b);
			}
		}
	}

	private static void dump(PrintStream out, byte[] array, int len) {
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

	public void process(InputStream in, OutputStream out) throws IOException {

		while (in.available() > 0) {
			int byt = in.read();
			if (mb_offset >= 128) {
				mb_offset = 0;
			}

			if (byt == -1) {
				try {
					Thread.sleep(200);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				continue;
			}

			if (byt >= 0x80) {
				if (rt_offset >= rt_buffer.length) {
					rt_offset = 0;
					rt_expected = 0;
					log.warn("[overflow]");
				}

				if ((byt & 0xf0) == SYNC_START) {
					int b = byt & 0x0f;
					rt_offset = 0;
					rt_expected = 0;
					if ((b & 0x08) != 0)
						rt_expected += 2;
					if ((b & 0x04) != 0)
						rt_expected += 2;
					if ((b & 0x02) != 0)
						rt_expected += 2;
					if ((b & 0x01) != 0)
						rt_expected += 2;

				}
				if ((byt & 0xf0) == SYNC_CMD_MASK) {
					rt_expected++;
				}

				rt_buffer[rt_offset++] = byt;

				if (rt_offset > rt_expected) {
					processRtMessage(rt_buffer, rt_offset);
				}

			} else if (byt == ESC || byt == SOH) {
				// start of message
				mb_buffer[0] = (byte) byt;
				mb_offset = 1;
			} else if (byt == CR) {
				if (mb_buffer[0] == ESC) {
					processRequest(out, mb_buffer, mb_offset);
				} else if (mb_buffer[0] == SOH) {
					processResponse(mb_buffer, mb_offset);
				}
				mb_offset = 0;

			} else {
				mb_buffer[mb_offset++] = (byte) byt;
			}

		}
	}

	private void processRtMessage(int[] rtBuffer, int len) {
		if (log.isDebugEnabled()) {
			System.out.print("+");
		}

		int idx = 0;
		int rt_curve = -1;
		int sync_command = 0;
		int sync_arg = 0;

		assert (rtBuffer[0] == 0xd7 || rtBuffer[0] == 0xd3) : "medibus rt assert d7 here";
		assert (len == 5 || len == 7 || len == 9) : "medibus rt len invalid: " + len;

		while (idx < len) {
			int byt = rtBuffer[idx++];
			if ((byt & 0xf0) == SYNC_START) {
				rt_curve = byt & 0x0f;
			} else if ((byt & 0xf0) == SYNC_CMD_MASK) {
				// beginning of sync command seq
				sync_command = byt & 0x0f;
				sync_arg = 0x0f & rtBuffer[idx++];

				switch (sync_command) {
				case 0x06:
					// beginning or end of vent cycle...check sync_arg
					break;
				case 0x0f:
					// corrupte data-record received
					break;
				}
			} else {
				int low = (0x3f & byt);
				byt = rtBuffer[idx++];
				int high = (0x3f & byt);

				int val = (high << 6) + low;
				for (int curve = 0; curve < 4; curve++) {
					int mask = (1 << curve);
					if ((rt_curve & mask) != 0) {
						wf_data[curve].put(val);

						rt_curve = rt_curve - mask;

						break;
					}
				}
			}
		}

		// int n0 = wf_data[0].position();
		// int n1 = wf_data[1].position();
		// int n2 = wf_data[2].position();
		// if (n0 != n1 || n0 != n2) {
		// log.warn("outta sync!");
		// wf_data[0].clear();
		// wf_data[1].clear();
		// wf_data[2].clear();
		// } else {
		sendWaveforms();
		// }
	}

	private void sendWaveforms() {
		PersistentItem block = null;
		List<? extends RpMetric> wfd = RpUtil.getMetrics(conf, StreamID.WAVEFORM);
		if (wfd == null) {
			// waveforms not configured.... should never get this far
			return;
		}
		for (int idx = 0; idx < wf_data.length; idx++) {
			if (idx >= wfd.size()) {
				// ERROR HERE!
				continue;
			}
			IntBuffer bb = wf_data[idx];
			if (bb.position() == WF_PACKET_SIZE) {
				RpMetric desc = wfd.get(idx);

				if (block == null) {
					long tm = PlatformUtil.currentTimeMillis();
					// System.out.print("block: " +
					// PlatformUtil.currentTimeMillis());
					// System.out.print(" expected: " +
					// drifter.getNextExpectedTime());
					// long delta = tm - drifter.getNextExpectedTime();
					// System.out.println(" delta: " + delta);
					tm = drifter.getRectifiedTime(tm);

					block = ModelUtil.getModelFromDataClass(waveformClass);

					// int msPerPacket = WF_PACKET_SIZE * 1000 /
					// desc.getSampleRate();
					int msPerPacket = 500;
					drifter.setNextExpectedTime(tm + msPerPacket);
				}
				IntfUtil.setValue(block, desc, bb.array());

				bb.clear();
			}
		}

		if (block != null) {
			fireStreamEvent(0, this, StreamID.WAVEFORM, block);
		}

		// don't reset the tick on waveform, as I need to send NOOP to Fabius
		// whether or not we get RT waveforms
		// tick = 0;
	}

	private void processRequest(OutputStream out, byte[] message, int len) throws IOException {

		if (log.isDebugEnabled()) {
			System.out.print(" qfrom: ");
			dump(System.out, message, len);
		}
		int checksum = CRCUtil.getChecksum(message, 0, len - 2);

		checksum %= 256;

		byte ch0 = hex[checksum / 16];
		byte ch1 = hex[checksum % 16];

		if (message[len - 2] == ch0 && message[len - 1] == ch1) {
			// this message passes the checksum
		} else {
			log.warn("CHK error: " + message[len - 2] + "." + message[len - 1] + " <> " + ch0 + "." + ch1);
			dump(System.err, message, len);

			sendResponse(NAK);
			return;
		}

		switch (message[1]) {
		case DEVICE_ID:
			sendResponse(DEVICE_ID);

			break;
		case ICC:
			gotICC = true;
			sendResponse(ICC);
			isCalibrationConfigured = false;
			isMetricConfigured = false;
			isWaveConfigured = false;
			isTraceConfigured = false;

			tick = 0;
			break;
		// fall through for ICC request...required by Fabius?
		// not tested on evita?
		case NOP:
			if (message[1] == NOP) {
				sendResponse(NOP);
			}

			processNOOP(out);
			tick = 0;
			break;
		case TEXT_MESSAGES:
		case MEASURED_DATA:
			// fabius sends these messages, not sure why
			sendResponse(message[1]); // send an empty response
			tick = 0;
			tick_measurement = 0;
			break;
		default:
			log.warn("Unrecognized request: ");
			dump(System.err, message, len);
			sendResponse(message[1]); // send an empty response, recommended in
										// the FAQ
		}
	}

	private void processNOOP(OutputStream out) throws IOException {
		if (isMetricConfigured == false) {
			log.info("medibus ** configuring metrics");
			tick_measurement = 1;
			List<? extends RpMetric> metrics = RpUtil.getMetrics(conf, StreamID.MEASUREMENT);
			configureMetrics(metrics);

			isMetricConfigured = true;
		} else if (isCalibrationConfigured == false) {

			requestRealtimeConfig();

			isCalibrationConfigured = true;
		} else if (isWaveConfigured == false) {
			List<? extends RpMetric> waves = RpUtil.getMetrics(conf, StreamID.WAVEFORM);
			if (waves != null && waves.size() > 0) {
				configRealtime(waves);
			}

			isWaveConfigured = true;
		} else if (isTraceConfigured == false) {

			List<? extends RpMetric> waves = RpUtil.getMetrics(conf, StreamID.WAVEFORM);

			if (waves != null && waves.size() > 0) {
				int ena = 0;
				if (waves.size() == 1) {
					ena = 0x01;
				} else if (waves.size() == 2) {
					ena = 0x03;
				} else if (waves.size() == 3) {
					ena = 0x07;
				} else if (waves.size() == 4) {
					ena = 0x0f;
				}
				syncEnableTraces(out, 0, ena); // channels 1&2
			}
			isTraceConfigured = true;
		} else {
			noop_cycle %= 4;

			switch (noop_cycle) {
			case 0:
				requestMetrics();
				break;
			case 1:
				if (hasSettings) {
					requestSettings();
				}
				break;
			case 2:
				requestAlarms();
				break;
			case 3:
				requestTextMessages();
				break;
			}
			noop_cycle++;
		}
	}

	private void processResponse(byte[] message, int len) throws IOException {

		if (len < 3) {
			return; // NO DATA!
		}

		// System.out.println("resp: " + len);

		if (log.isDebugEnabled()) {
			System.out.print(" efrom: ");
			dump(System.out, message, len);
		}

		int checksum = CRCUtil.getChecksum(message, 0, len - 2);
		checksum %= 256;

		byte ch0 = hex[checksum / 16];
		byte ch1 = hex[checksum % 16];

		if (message[len - 2] == ch0 && message[len - 1] == ch1) {
			// this message passes the checksum
		} else {
			log.warn("CHK error: " + message[len - 2] + "." + message[len - 1] + " <> " + ch0 + "." + ch1);
			dump(System.err, message, len);
			return;
		}

		ByteBuffer bb;
		switch (message[1]) {
		case ICC:
			gotICC = true;
			log.info("ICC: got device response");
			tick = 0;
			isCalibrationConfigured = false;
			isMetricConfigured = false;
			isWaveConfigured = false;
			isTraceConfigured = false;

			break;
		case DEVICE_ID:
			// idNo = 123;
			tick = 0;
			log.info("DEVICE_ID: got response...ignoring");
			break;
		case REALTIME_CONFIG:
			bb = ByteBuffer.wrap(message, 2, len - 3);
			while (bb.remaining() >= 23) {
				String code = getByteBufferString(bb, 2);
				String interval = getByteBufferString(bb, 8);
				int minVal = getByteBufferInt(bb, 5);
				int maxVal = getByteBufferInt(bb, 5);
				int maxBin = getByteBufferInt(bb, 3);

				log.debug("code=" + code //
						+ " interval=" + interval //
						+ " minVal=" + minVal //
						+ " maxVal=" + maxVal //
						+ " bin=" + maxBin);
			}
			log.debug("realtime config complete");
			tick = 0;

			break;
		case REALTIME_TRANSMISSION:
			log.debug("<ack of RT transmission>");
			tick = 0;

			break;
		case CONFIG_DATA:
			log.debug("<ack of configured data>");
			tick = 0;

			break;
		case NAK:
			log.warn("NAK NAK NAK...maybe disconnected or no session established?");
			break;
		case MEASURED_DATA:
			bb = ByteBuffer.wrap(message, 2, len - 2);
			parseAndFire(bb, StreamID.MEASUREMENT);
			break;
		case CURRENT_SETTINGS:
			bb = ByteBuffer.wrap(message, 2, len - 2);
			parseAndFire(bb, StreamID.SETTINGS);
			break;
		case CURRENT_ALARMS:
			bb = ByteBuffer.wrap(message, 2, len - 2);

			DateFormat df2 = DateFormat.getDateTimeInstance();
			long now = PlatformUtil.currentTimeMillis();
			// System.out.println("date: " + df2.format(new Date()));
			List<Alarm> currAlarms = new LinkedList<Alarm>();
			while (bb.remaining() >= 4) {

				int priority = bb.get();
				String code = getByteBufferString(bb, 2);
				String phrase = getByteBufferString(bb, 12);

				String paramName = code;
				String pdc_code = phrase;
				int cond = priority;

				log.info("alarm {} = {}", code, phrase);

				Alarm ai = findAndRemoveAlarm(lastAlarms, cond, paramName);
				if (ai == null) {
					ai = new Alarm(paramName, Alarm.WARNING, cond, pdc_code, true);
					ai.setTm(new Date(now));
					fireAlarmEvent(this, ai);
					if (verbose > 0) {
						log.info(" alarm: {} code={}", ai, pdc_code);
					}
				}
				currAlarms.add(ai);
			}

			for (Alarm ai : lastAlarms) {
				ai.setActive(false);
				fireStreamEvent(0, this, StreamID.ALARM, ai);
			}
			lastAlarms = currAlarms;

			tick = 0;

			break;
		case TEXT_MESSAGES:
			bb = ByteBuffer.wrap(message, 2, len - 2);

			int idx = 0;
			while (bb.hasRemaining()) {
				String code = getByteBufferString(bb, 2);
				if ("9F".equals(code) || bb.remaining() < 2) {
					// end of messages
					break;
				}
				int tlen = bb.get() - '0';
				if (tlen > 32 || tlen < 0) {
					log.warn("INVALID TEXT MESSAGE");
					break;
				}
				String msg = getByteBufferString(bb, tlen);
				byte etx = bb.get();
				// assert( etx == ETX );
				log.debug("txt msg: {} / {}", code, msg);
				textCodes[idx++] = Integer.parseInt(code, 16);
				if (idx == textCodes.length) {
					break;
				}
			}
			break;
		case NOP:
			tick = 0;
			processNOOP(getOutputStream());

			break;
		default:
			log.warn("Unrecognized response: ");
			dump(System.err, message, len);
		}
	}

	private void parseAndFire(ByteBuffer bb, StreamID sid) {

		PersistentItem block;
		int fieldLen;
		String pfx;
		if (sid == StreamID.MEASUREMENT) {
			block = ModelUtil.getModelFromDataClass(dataClass);
			pfx = "0x";
			fieldLen = 4;
		} else if (sid == StreamID.SETTINGS) {
			// YES...THIS IS cap.getSettings() not conf.getSettings()!!!
			// ALWAYS send all the settings
			block = ModelUtil.getModelFromDataClass(settingsClass);
			pfx = "1x";
			fieldLen = 5;
		} else {
			log.warn("parseAndFire: invalid subset!");
			return;
		}
		while (bb.remaining() >= 6) {

			String code = pfx + getByteBufferString(bb, 2);
			String value = getByteBufferString(bb, fieldLen);

			// strip spaces
			value = value.replace(" ", "");
			value = value.trim();

			RpMetric desc = RpUtil.getMetricFromStreamID(conf, sid, code);

			if (desc == null) {
				log.warn("UNKNOWN : {} = {}", sid + " " + code, value);
				if (verbose > 0) {
					dump(System.out, bb.array(), bb.limit());
				}
			} else {

				Integer v = null;
				try {
					RpPrecisionUnit lu = (RpPrecisionUnit) desc.getUnit();
					v = lu.inverse(Double.parseDouble(value));
				} catch (Exception e) {
					// number format exception
					log.error("fixme medbus: {} expected double: {}", code, value);
				}
				IntfUtil.setValue(block, desc, v);
			}
		}

		if (sid == StreamID.SETTINGS)

		{

			String debugString = null;
			if (log.isDebugEnabled()) {
				debugString = "textCodes[] = {";
			}

			for (int i = 0; i < textCodes.length; i++) {
				RpMetric m = block.getMetric("TXT" + i);
				IntfUtil.setValue(block, m, "" + textCodes[i]);
				textCodes[i] = 0;
			}

			if (log.isDebugEnabled()) {
				debugString += "}";
				log.debug(debugString);
			}
		}

		fireStreamEvent(0, this, sid, block);
		tick = 0;

	}

	private Alarm findAndRemoveAlarm(List<Alarm> list, int code, String paramName) {
		Iterator<Alarm> it = list.iterator();
		while (it.hasNext()) {
			Alarm item = it.next();

			if (item.getCode() == code && paramName.equals(item.getDevParam())) {
				it.remove();
				return item;
			}
		}
		return null;
	}

	private String getByteBufferString(ByteBuffer bb, int len) {
		StringBuffer ret = new StringBuffer();
		while (len > 0) {
			ret.append((char) bb.get());
			len--;
		}
		return ret.toString();
	}

	private int getByteBufferInt(ByteBuffer bb, int len) {

		StringBuffer ret = new StringBuffer();
		while (len > 0) {
			byte b = bb.get();
			if (b == ' ') {
				// skip
			} else {
				ret.append(b);
			}
			len--;
		}

		String s = ret.toString();
		return Integer.parseInt(s);
	}

	protected void requestRealtimeConfig() throws IOException {
		sendRequest(REALTIME_CONFIG);
	}

	protected void configRealtime(List<? extends RpMetric> waves) throws IOException {
		if (waves == null) {
			return;
		}
		String req = new String();

		for (RpMetric d : waves) {
			String code = d.getLocation().toString();
			String mult = "01";

			req += code.substring(2);
			req += mult;
		}
		sendRequest(REALTIME_TRANSMISSION, req);
	}

	public void requestStop() throws IOException {
		sendRequest(STOP);
	}

	public void sendPause() throws IOException {
		sendByte(DC1);
	}

	public void sendResume() throws IOException {
		sendByte(DC3);
	}

	public void sendAbort() throws IOException {
		sendByte(CAN);
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, cap);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	public void syncEnableTraces(OutputStream out, int traceGroup, int bitmap) throws IOException {
		byte syncCommand = 0x00;
		if (traceGroup == 0) {
			syncCommand = (byte) 0xc1;
		} else if (traceGroup == 1) {
			syncCommand = (byte) 0xc2;
		} else if (traceGroup == 2) {
			syncCommand = (byte) 0xc3;
		}
		sendSyncPacket(out, syncCommand, (byte) bitmap);
	}

	private void sendSyncPacket(OutputStream out, byte syncCommand, byte b) throws IOException {

		ByteBuffer bb = ByteBuffer.allocate(5);

		bb.put((byte) SYNC_START);
		bb.put(syncCommand);
		bb.put((byte) (0xc0 | b));
		bb.put((byte) SYNC_END);
		bb.put((byte) SYNC_END);

		synchronized (out) {
			out.write(bb.array());
			if (verbose > 0) {
				dump(System.out, bb.array(), 5);
			}
		}
	}

	public void configureMetrics(List<? extends RpMetric> metrics) throws IOException {
		if (metrics == null) {
			log.info("no metrics requested!");
			return;
		}
		String configReq = "";
		configReq += (char) DT_DATA; // if you don't convert to char, it is
		// added as an int.
		for (RpMetric metric : metrics) {
			String metricCode = metric.getLocation();
			if (metricCode.startsWith("0x") && metricCode.length() == 4) {
				// keep going
				configReq += metricCode.substring(2);
			} else {
				log.warn("NO SUCH METRIC ?setting?: \"{}\" {}", metricCode, metric);
			}
		}

		// log.error("configureMetrics: {}", configReq);
		sendPacket(ESC, CONFIG_DATA, configReq);
	}

	public void requestMetrics() throws IOException {
		log.info("requestMetrics()");
		sendPacket(ESC, MEASURED_DATA, null);
	}

	public void requestAlarms() throws IOException {
		sendPacket(ESC, CURRENT_ALARMS, null);
	}

	public void requestSettings() throws IOException {
		log.debug("requestSettings()");
		sendPacket(ESC, CURRENT_SETTINGS, null);
	}

	public void requestTextMessages() throws IOException {
		sendPacket(ESC, TEXT_MESSAGES, null);
	}

	@Override
	public void setPort(SerialPort port) {
		super.setPort(port);

		try {
			port.setBaudRate(baud);
			port.setNumDataBits(8);
			port.setNumStopBits(1);
			port.setParity( SerialPort.NO_PARITY);
		} catch (Exception e) {
			log.error("could not set port baud: ", e);
		}
	}

	@Override
	public int tick() {
		tick++;
		tick_measurement++;
		if (tick_measurement > 6) {
			isMetricConfigured = false;
			tick_measurement = 1;
		}

		if (gotICC == false) {
			// wait

			try {
				if (tick == 6) {
					sendRequest(ICC);
					isCalibrationConfigured = false;
					isMetricConfigured = false;
					isWaveConfigured = false;
					isTraceConfigured = false;

				} else if (tick == 8) {
					sendRequest(DEVICE_ID);
				} else if (tick == 12) {
					tick = 5;
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		// only send noops if completely configured
		if (requiresNOOP && isTraceConfigured) {
			if (!skip) {
				try {
					// fabius and maybe apollo requires NOOP
					sendPacket(ESC, NOP, null);
				} catch (IOException e) {
					log.error("tick", e);
				}
			}
			skip = !skip;
		}

		ConnectionStatus deviceState = getStatus();
		if (tick > 10) {
			if (deviceState != NOT_CONNECTED) {
				log.info("tick taking MedibusDriver offline: {} verbosity: {}", tick, verbose);
				setStatus(NOT_CONNECTED);
				fireNoData(conf);
			}
		} else if (tick > 4) {
			if (deviceState != NEGOTIATING) {
				setStatus(NEGOTIATING);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

	private final static byte[] medibus_probe_bytes = new byte[] { 0x1b, 0x30, 0x34, 0x42, 0x0d };

	// test the byte array to see if the data is recognized
	@Override
	public void probe(OutputStream out) throws IOException {
		out.write(medibus_probe_bytes);
		return;
	}

	public boolean test(byte[] arr) {
		return false;
	}

}
