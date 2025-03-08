package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import jakarta.persistence.Entity;

import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.model.dev.BodyguardMeasurement;
import idea.model.dev.BodyguardSettings;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Entity
@Slf4j
public class BodyGuardDriver extends SerialAdapter {
	@SuppressWarnings("unused")
	private static final String driverName = "pump/CME Bodyguard";

	private static final int MIN_DELTA_TM = 5000; // only send on numerics
													// message every 5 secs
	private long[] last_tm_time = new long[2];

	private final static int START = 0xa8;
	private final static int END = 0xa8;
	private final static byte CR = 0x0d;
	private final static byte LF = 0x0a;
	private final static byte ESC = 0x1b;

	private static final int PESC = (byte) 0xa9;

	List<String> message_q = new LinkedList<String>();
	Map<String, String> settings = new HashMap<String, String>();

	/*
	 * Commands
	 */

	protected static DeviceCapabilities cap;

	private byte[] pumpID;
	private byte[] anyPumpID = new byte[] { ESC, '*', '*', '*', '*', '*', '*', '*' };

	int mb_offset = 0;
	byte[] mb_buffer = new byte[128];

	int loc_offset = 0;
	byte[] loc_buffer = new byte[128];

	private boolean localMessage = true;
	boolean isEscaped = false;

	private int[] lastKnownEvent = new int[2];

	private int tick;
	private int request_timeout = 0;

	public final static int STATE_UNK = 0;
	public final static int STATE_RUN = 1;
	public final static int STATE_STOP = 2;
	public final static int STATE_OFF = 3;
	public final static int STATE_PROMPT = 4;
	public final static int STATE_ERROR = 5;

	private int[] state = new int[2];

	private int[] rate = new int[2];
	private int[] vtbi = new int[2];
	private int[] infused = new int[2];

	private static int verbose = 0;

	private boolean request_in_progress;

	private String last_req;

	static {
		cap = new DeviceCapabilities(BodyGuardDriver.class);

		cap.addStream(StreamID.MEASUREMENT, BodyguardMeasurement.class);
		cap.addStream(StreamID.SETTINGS, BodyguardSettings.class);
		cap.addConnection(new SerialConnection(9600, 8, 1, 0));
		cap.setModels(new String[] { "BodyGuard" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(BodyGuardDriver.class);
	}

	public BodyGuardDriver(RpDevice conf) {
		super(conf);

		pumpID = new byte[8];
		pumpID[0] = ESC;
		pumpID[1] = 'T';
		pumpID[2] = ' ';
		pumpID[3] = '3';
		pumpID[4] = '2';
		pumpID[5] = '5';
		pumpID[6] = '7';
		pumpID[7] = '1';

	}

	public void sendKey(String key) throws IOException {
		for (int i = 0; i < key.length(); i++) {
			char ch = key.charAt(i);
			String command = "K" + ch;
			queueCommand(command);
		}
	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	@Override
	public void connect() throws IOException {
		setStatus(ConnectionStatus.NEGOTIATING);

		request_in_progress = false;
		request_timeout = 0;
		String portName = RpUtil.getParam(conf, "port");
		connect(portName, 9600, 8, 1, 0);

		log.info("opened port {} baud={}", portName, 9600);
		sendQueryDevice();

	}

	public void sendQueryDevice() throws IOException {

		sendPacket(anyPumpID, "");
	}

	public void sendQuerySetup() {
		queueCommand("S");
	}

	public void sendQueryCalibration() throws IOException {
		queueCommand("C");
	}

	public void sendQueryLastEvent(int channel) {
		String cmd = "L";
		cmd += channel;

		message_q.add(cmd);
	}

	public void queueCommand(String message) {
		synchronized (message_q) {
			message_q.add(message);
		}
	}

	public void sendQueryEvent(int channel, int eventOffset) {

		if (eventOffset <= 0) {
			eventOffset = lastKnownEvent[channel] + eventOffset;
		}

		if (eventOffset < 0) {
			log.error("Need to wrap around the buffer");
			eventOffset = 0; // OVERIDE
		}
		String s_eventNo = Integer.toString(eventOffset);

		while (s_eventNo.length() < 4) {
			s_eventNo = "0" + s_eventNo; // poor man's Integer.format()
		}

		String cmd = "E";
		cmd += (channel + 1);
		cmd += " ";
		cmd += s_eventNo;

		message_q.add(cmd);
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		while (in.available() > 0) {

			int byt = in.read();

			if (byt == -1) {
				log.warn("?no data?");
				try {
					Thread.sleep(200);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				continue;
			}

			if (byt == START) {
				localMessage = false;
			}

			if (localMessage) {
				if (loc_offset >= 128) {
					loc_offset = 0;
				}

				if (byt == LF || byt == CR) {
					if (loc_offset > 1) {
						processLocalMessage();
					}
					loc_offset = 0;
				} else {
					loc_buffer[loc_offset++] = (byte) byt;
				}

			} else {

				if (mb_offset >= 128) {
					mb_offset = 0;
					localMessage = true;
					continue;
				}

				if (byt == PESC) {
					log.error("GOT UNEXPECTED ESCAPE!");
					isEscaped = true;
					continue;
				}

				if (isEscaped) {
					if (byt == 0x88)
						byt = START;
					else if (byt == 0x89)
						byt = PESC;
					else {
						assert (false) : "invalid escape sequence...ignore escape";
					}
					isEscaped = false;
				}

				if (byt == START && mb_offset == 1) {
					// ignore duplicate start chars
				} else if (byt == END && mb_offset > 2) {
					boolean process = true;
					if (mb_offset > 12) {
						int cmd0 = mb_buffer[11];
						if (cmd0 == 'E') { // binary command with a
											// fixed length
							if (mb_offset < 40) {
								process = false;
							}
						}
					}

					if (process) {
						processExtendedMessage();

						mb_buffer[0] = (byte) byt;
						mb_offset = 1;

						localMessage = true;

						sendNextQueuedCommand();
					}
				} else {
					mb_buffer[mb_offset++] = (byte) byt;
				}
			}

		}

	}

	private void sendNextQueuedCommand() throws IOException {
		if (request_in_progress) {
			return;
		}

		synchronized (message_q) {
			if (message_q.size() > 0) {
				String command = message_q.remove(0);
				sendPacket(pumpID, command);
				last_req = command;
				request_in_progress = true;
				request_timeout = 0;
			}
		}
	}

	private void processExtendedMessage() {

		request_timeout = 0;
		tick = 0;

		if (verbose > 2) {
			dump(System.out, mb_buffer, mb_offset);
		}

		int ch0 = mb_buffer[0];
		if (ch0 < 0) {
			ch0 += 256;
		}

		if (ch0 == 0xa8 && mb_buffer[1] == ESC) {
			int cmd0 = mb_buffer[11];
			int cmd1 = mb_buffer[12];

			if (verbose > 1) {
				System.out.print((char) cmd0);
				System.out.flush();
			}

			if (cmd0 == CR || cmd0 == '0') {
				for (int i = 0; i < 8; i++) {
					pumpID[i] = mb_buffer[i + 1];
				}
				request_in_progress = false;
			} else if (cmd0 == 'C') {
				request_in_progress = false;
			} else if (cmd0 == 'E') {
				parseEventLogEntry();
				request_in_progress = false;
			} else if (cmd0 == 'S' && cmd1 == 'H') {
				String s = new String(mb_buffer, 11, mb_offset).trim();
				String[] arr = s.split("[ =\"\r\n]+");
				if (arr.length < 3) {
					log.warn("IGNORING SHORT SHOW COMMAND!");
				} else {
					String var = arr[1].replace("\"", "");
					settings.put(var, arr[2]);
				}
			} else if (cmd0 == 'S') {
				request_in_progress = false;
			} else if (cmd0 == 'L') {
				request_in_progress = false;

				int chan = mb_buffer[12] - '1';
				int event = 0;

				int idx = 13;
				while (mb_buffer[idx] != CR && idx < 22) {
					event = 10 * event + (mb_buffer[idx] - '0');
					idx++;
				}

				if (lastKnownEvent[chan] != event) {
					lastKnownEvent[chan] = event;
					// System.out.println("SET LAST KNOWN EVENT: " + event);
					sendQueryEvent(chan, 0);
				}

			} else if (cmd0 == 'A') {
				// keystroke acknowledge, actually ACC
				request_in_progress = false;

			} else {
				log.error("*******UNKNOWN COMMAND: {}", cmd0);
			}

			if (verbose > 1) {
				if (request_in_progress == false) {
					log.warn("!");
				}
			}
		} else {
			log.error("INVALID CMD FORMAT");
		}
	}

	private void parseEventLogEntry() {
		int pumpId = mb_buffer[12] - '1';
		if (pumpId < 0 || pumpId > 1) {
			log.error("INVALID PUMP ID: {}", pumpId);
			return;
		}

		String sEventNo = ""; // don't need this for anything right now
		for (int idx = 0; idx < 4; idx++) {
			sEventNo += (char) mb_buffer[14 + idx];
		}

		int idx = 19;
		int ev0 = unsigned_byte(mb_buffer[idx++]);
		int ev1 = unsigned_byte(mb_buffer[idx++]);
		int yr = unsigned_byte(mb_buffer[idx++]);
		int mon = unsigned_byte(mb_buffer[idx++]);
		int day = unsigned_byte(mb_buffer[idx++]);
		int hr = unsigned_byte(mb_buffer[idx++]);
		int min = unsigned_byte(mb_buffer[idx++]);
		int code = unsigned_byte(mb_buffer[idx++]);
		int rate_b0 = unsigned_byte(mb_buffer[idx++]);
		int rate_b1 = unsigned_byte(mb_buffer[idx++]);
		int rate = 256 * rate_b0 + rate_b1;
		int vtbi_b0 = unsigned_byte(mb_buffer[idx++]);
		int vtbi_b1 = unsigned_byte(mb_buffer[idx++]);
		int vtbi_b2 = unsigned_byte(mb_buffer[idx++]);

		int vtbi = vtbi_b0;
		vtbi = 256 * vtbi + vtbi_b1;
		vtbi = 256 * vtbi + vtbi_b2;

		int inf_b0 = unsigned_byte(mb_buffer[idx++]);
		int inf_b1 = unsigned_byte(mb_buffer[idx++]);
		int inf_b2 = unsigned_byte(mb_buffer[idx++]);

		int inf = inf_b0;
		inf = 256 * inf + inf_b1;
		inf = 256 * inf + inf_b2;

		System.out.println("pumpid=" + pumpId);
		System.out.println("code=" + code);
		System.out.println("rate=" + rate_b0 + "." + rate_b1 + " --> " + rate);
		System.out.println("vtbi=" + vtbi_b0 + "." + vtbi_b1 + "." + vtbi_b2 + " --> " + vtbi);
		System.out.println("infu=" + inf_b0 + "." + inf_b1 + "." + inf_b2 + " --> " + inf);

		if (code == 43 || code == 50) {
			this.rate[pumpId] = rate;
			this.vtbi[pumpId] = vtbi;
			this.infused[pumpId] = inf;

			fireNumerics(pumpId);
		}
	}

	private int unsigned_byte(byte b) {
		int val = b;
		if (val < 0) {
			val += 256;
		}
		return val;
	}

	private int debug_local = 0;

	private void processLocalMessage() {
		debug_local++;
		if (debug_local < 20) {
			return;
		}
		debug_local = 0;
		tick = 0;

		// I DONT LIKE THIS...but messages seem to run together sometimes
		for (int i = 3; i < loc_offset; i++) {
			if (loc_buffer[i] == '*') {
				loc_offset = i;
				break;
			}
		}

		String s = new String(loc_buffer, 0, loc_offset);
		s = s.trim();

		if (verbose > 0) {
			System.out.print("local: ");
			System.out.println(s);
		}

		int pumpId = loc_buffer[1] - '1';
		if (pumpId < 0 || pumpId > 1) {
			log.error("process local message INVALID PUMP ID: {}", s);
			return;
		}

		// System.out.println( "split: " + s + " len=" + loc_offset);
		String[] ar = s.split("[ \r\n]+");
		String cmd = "???";
		if (ar.length >= 2) {
			cmd = ar[1];
		}
		if (ar.length > 3 && "RUN".equals(cmd)) {
			state[pumpId] = STATE_RUN;
			String t = ar[2];
			String r = ar[3];
			if (t.equals("RATE")) {
				try {
					rate[pumpId] = (int) (10.0 * Double.parseDouble(r));
				} catch (Exception e) {
					e.printStackTrace();
					return;
				}

				log.debug("firing message for pump: {}", pumpId);
				fireNumerics(pumpId);
			} else if (t.equals("VTBI")) {
				// ignore...this happens when the INFO key is pressed
			} else {
				log.error("[1] UNKNOWN LOCAL MESSAGE: " + s + " T=" + t + " R=" + r);
			}
		} else if ("PUT".equals(cmd)) {
			if (ar.length == 2) {
				// empty put...safe to ignore
			} else {
				String t = ar[2];
				if ("STOP".equals(t)) {
					state[pumpId] = STATE_STOP;
				} else if ("AIR".equals(t)) {
					state[pumpId] = STATE_ERROR;
				} else if ("OFF".equals(t)) {
					state[pumpId] = STATE_OFF;
				} else if ("CH-1".equals(t)) {
					state[pumpId] = STATE_PROMPT;
				} else if ("CH-2".equals(t)) {
					state[pumpId] = STATE_PROMPT;
				} else if ("RATE".equals(t)) {
					state[pumpId] = STATE_PROMPT;
				} else if ("VTBI".equals(t) && ar.length < 4) {
					state[pumpId] = STATE_PROMPT;
				} else if ("VTBI".equals(t)) {

					String r = ar[3];
					try {
						vtbi[pumpId] = (int) (10.0 * Double.parseDouble(r));
						;
					} catch (Exception ee) {
						ee.printStackTrace();
					}
				} else if ("OK".equals(t) || "PRES".equals(t)) {
					// ? state[pumpId] = STATE_PROMPT;
					// ? System.out.println( "BG STATE PRESS OK?");
				} else if (ar.length > 2) {
					log.error("[2] UNKNOWN LOCAL MESSAGE: " + s);
				}
			}
		} else if ("GET".equals(cmd)) {
			if (ar.length == 2) {
				// empty put...safe to ignore
			} else {
				String t = ar[2];
				if ("RATE".equals(t)) {
					state[pumpId] = STATE_PROMPT;
				} else if ("VTBI".equals(t)) {
					state[pumpId] = STATE_PROMPT;
				} else if (ar.length > 2) {
					log.error("[4] UNKNOWN LOCAL MESSAGE: " + s);
				}
			}
		} else {
			log.error("[3] UNKNOWN LOCAL MESSAGE: " + s);
		}
	}

	private void fireNumerics(int pumpId) {
		assert (pumpId < 2) : "BODYGUARD only knows about two pumps!";
		if (pumpId > 1) {
			return;
		}

		long curr_tm = PlatformUtil.currentTimeMillis();
		if (curr_tm - last_tm_time[pumpId] > MIN_DELTA_TM) {

			BodyguardMeasurement block = new BodyguardMeasurement(this);

			block.setRate1(rate[0]);
			block.setRate2(rate[2]);

			block.setVtot1(infused[0]);
			block.setVtot2(infused[1]);

			block.setVtbd1(vtbi[0]);
			block.setVtbd2(vtbi[1]);

			block.setStat1(state[0]);
			block.setStat2(state[1]);

			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
			last_tm_time[pumpId] = curr_tm;
		}
		tick = 0;

	}

	private void sendPacket(byte[] pumpID, String payload) throws IOException {

		OutputStream out = getOutputStream();

		if (out == null) {
			log.error("OUTPUT PORT NOT INITIALIZED");
			return;
		}

		int capacity = 13;
		if (payload != null)
			capacity += payload.length();

		ByteBuffer bb = ByteBuffer.allocate(capacity);
		// bb.order( ByteOrder.BIG_ENDIAN );

		bb.put((byte) START);
		bb.put(pumpID);
		bb.put(CR);
		bb.put(LF);
		bb.put(payload.getBytes());
		bb.put(CR);
		bb.put(LF);

		int crc = CRCUtil.getCRC16X(0xffff, bb.array(), 1, bb.capacity());
		crc &= 0xffff;

		synchronized (out) {
			out.write(bb.array());
			writeEscapedByte(out, (crc % 256)); // low byte
			writeEscapedByte(out, (crc / 256)); // high byte
			out.write((byte) END);

		}

		if (verbose > 1) {
			log.debug(" to device: ");
			dump(System.out, bb.array(), bb.position());
		}
	}

	private void writeEscapedByte(OutputStream out, int b) throws IOException {
		if (b == START) {
			out.write((byte) PESC);
			out.write((byte) 0x88);
		} else if (b == PESC) {
			out.write((byte) PESC);
			out.write((byte) 0x89);
		} else {
			out.write(b);
		}
	}

	private void dump(PrintStream out, byte[] array, int len) {
		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 40 == 0)) {
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
			out.print(" ");
		}
		out.println();

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	public void configureMetrics(RpMetric[] metrics) throws IOException {
		if (metrics == null) {
			return;
		}
		String configReq = "";

		for (RpMetric metric : metrics) {
			String metricCode = metric.getLocation();
			if (metricCode.startsWith("0x") && metricCode.length() == 4) {
				// keep going
				configReq += metricCode.substring(2);
			} else {
				log.error("NO SUCH METRIC: {}", metricCode);
				return; // bad value!
			}
		}

		// sendPacket(ESC, CONFIG_DATA, configReq);
	}

	@Override
	public void requestSettingsUpdate(PersistentItem settings) throws IOException {

		int channel = 1;
		String switch_channel_key = "";

		for (RpMetric setting : IntfUtil.getMetrics(settings)) {
			Object nm = setting.getLocation();
			Number val = (Number) IntfUtil.getRawValue(settings, setting);
			if ("RATE1".equals(nm)) {
				if (channel == 2) {
					sendKey(switch_channel_key);
					channel = 1;
				}
				sendKey(val.intValue() + "RR");
			} else if ("RATE2".equals(nm)) {
				if (channel == 1) {
					sendKey(switch_channel_key);
					channel = 2;
				}
				sendKey(val.intValue() + "RR");
			} else {
				log.error("CANNOT CONFIG VARIABLE: {} EXPECTING RATE1/RATE2.", nm);
			}
		}
	}

	public Object getMeta(Object key) {
		Object o = settings.get(key);
		log.info(" key: {} meta: {}", key, o);
		return o;
	}

	@Override
	public int tick() {

		if (request_in_progress) {
			request_timeout++;
			if (request_timeout > 2) {
				log.info("LAST REQUEST TIMEOUT: {}", last_req);
				request_in_progress = false;
			}
		}

		if (!request_in_progress) {
			if (message_q.size() == 0) {
				sendQuerySetup();
				sendQueryLastEvent(1);
				sendQueryLastEvent(2);
			}
			try {
				sendNextQueuedCommand();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			request_in_progress = false;
			if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
				try {
					sendQueryDevice();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

}
