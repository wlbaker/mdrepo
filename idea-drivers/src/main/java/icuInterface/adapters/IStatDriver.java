package icuInterface.adapters;

/*
 * TODO: Temperature...probably only one...maybe Celsius is right? 
 * TODO: Temperature...Farenheit field?
 * TODO: b1/b2 are unknown values that fluctuate wildly
 * TODO: Strange date format...since 1950?
 * TODO: Try a wide date range
 * TODO: Any use for RSC?
 * TODO: Make it actually talk to the device and fire numerics
 * TODO: Determine database storage format
 */

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;

import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.intf.SerialAdapter;
import idea.model.dev.IstatMeasurement;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

enum STATE {
	SESSION, DSQ

}

@Slf4j
public class IStatDriver extends SerialAdapter {

	@SuppressWarnings("unused")
	private static final String driverName = "lab/Abbott ISTAT";

	private static final byte STX = 2;
	private static final byte ACK = 6;
	private static final byte EOT = 4;
	private static final byte NAK = 21;
	private static final byte ENQ = 5;
	private static final int HEADER_SIZE = 112;

	private int mb_offset = 0;
	private byte[] mb_buffer = new byte[1024 + 64];

	private int tick;
	private boolean connected = false;
	private static DeviceCapabilities caps;

	int remaining = 0;
	int seq_no = 0;
	int data_seq_no = 0;

	STATE state = null;
	private byte[] last_data = null;
	private boolean in_message;

	private static final Map<String, String> colCodes = new HashMap<String, String>();

	private IstatMeasurement isb = new IstatMeasurement(); // FIXME: not
															// currently used

	static {
		// FIXME: these codes have been moved into the IstatResult() structure
		colCodes.put("5", "pH");
		colCodes.put("6", "pCO2");
		colCodes.put("15", "pO2");
		colCodes.put("11", "BE");
		colCodes.put("9", "HCO3");
		colCodes.put("19", "SO2pct");
		colCodes.put("24", "Lac");

		colCodes.put("0", "Na");
		colCodes.put("1", "K");
		colCodes.put("2", "Cl");
		colCodes.put("4", "iCa");
		colCodes.put("8", "TCO2");
		colCodes.put("7", "Glu");
		colCodes.put("3", "BUN");
		colCodes.put("25", "Crea");
		colCodes.put("13", "Hct");
		colCodes.put("14", "Hb");
		colCodes.put("10", "AnGap");

	}

	int data_indicator;
	int test_type;
	int cart_typ;
	int fail_code;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(IStatDriver.class);
	}

	/**
	 * 
	 */
	public IStatDriver(RpDevice conf) {
		super(conf);
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		connected = false;
		tick = 0;

		connect(portName, 38400, 8, 1, 0);

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	/**
	 * Called when a serial port event occurs
	 */

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {

		while (in.available() > 0) {
			int byt = in.read();

			// System.out.print( Integer.toHexString(byt) );
			// System.out.print( " ");

			if (mb_offset >= mb_buffer.length) {
				log.error("buf overflow");
				mb_offset = 0; // dump anything received so far
			}

			if (in_message) {
				mb_buffer[mb_offset++] = (byte) byt;
				if (mb_offset == 6) {
					int lo = unsigned_byte(mb_buffer[4]);
					int hi = unsigned_byte(mb_buffer[5]);
					remaining = 256 * hi + lo + 2; // 2 for crc

					if (remaining > 1024) {
						System.out.println("BAD PKT SIZE: " + remaining);
					}
				} else if (mb_offset > 6) { // add to buffer and continue
					remaining--;
					if (remaining == 0) {
						processRequest();
						mb_offset = 0;
						in_message = false;
					}
				}
				continue;
			}

			if (byt == ACK) {
				if (state == null) {
					log.info("ignoring ACK");
				} else if (state == STATE.SESSION) {
					sendDSQ();
					state = STATE.DSQ;
				} else {
					seq_no++;
				}
				mb_offset = 0;
				remaining = 0;
			} else if (byt == EOT) {
				mb_offset = 0;
				state = null;

			} else if (byt == ENQ) {
				processEnquire();
			} else if (byt == NAK) {
				log.error("got NAK -- untested!");
				sendPacket(last_data);
			} else if (byt == STX) {
				mb_offset = 0;
				mb_buffer[mb_offset++] = (byte) byt;
				in_message = true;
			} else {
				// System.out.print( "[" + Integer.toHexString(byt) + "]");
			}
		}
	}

	private static int unsigned_byte(byte b) {
		if (b < 0)
			return b + 256;
		return b;
	}

	private static int unsigned_byte(ByteBuffer bb) {
		int b = bb.get();
		if (b < 0)
			return b + 256;
		return b;
	}

	private void processRequest() throws IOException {
		if (mb_offset < 9) {
			log.error("incomplete data packet");
			return;
		}

		ByteBuffer bb = ByteBuffer.wrap(mb_buffer, 0, mb_offset);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		byte stx = bb.get();
		if (stx != 0x02) {
			log.error("no STX");
			return;
		}
		short seqNo = bb.getShort();
		byte pkts = bb.get();
		if (pkts != 1) {
			log.error("pkt count field {} != 1???", pkts);
		}
		short data_len = bb.getShort();
		int crc = bb.getShort();
		if (crc < 0) {
			crc += 0x10000;
		}
		int my_crc = CRCUtil.getCRC16g(mb_buffer, bb.position(), bb.remaining());
		if (crc == my_crc) {
			sendAck();
		} else {
			sendNAK();
			log.error("crc error: {} != {}", Integer.toHexString(crc), Integer.toHexString(my_crc));
			System.exit(0);
		}
		byte[] reply_b = new byte[3];
		bb.get(reply_b);
		String reply = new String(reply_b);

		if (reply.equals("DQN")) {
			sendRFI();
		} else if ("RSR".equals(reply)) {
			processRSR(bb);
			sendSDT();
		} else if ("STN".equals(reply)) {
			sendRSQ();
		} else if ("RSE".equals(reply)) {
			sendEOT();
		} else if ("RSD".equals(reply)) {
			byte recs = bb.get();
			System.out.println("RSD: [START] segs=" + recs);

			int segs = processRSD(bb, recs);
			if (segs != recs) {
				log.error("RSD: Expecting recs count: " + recs + " != " + segs);
			}

			System.out.println("RSD: [END]");

		} else if ("RSC".equals(reply)) {
			processRSC(bb);
		} else {
			log.error("unknown reply: {}", reply);
		}

	}

	private void processRSC(ByteBuffer bb) {
		log.error("RSC not implemented");
		System.out.print("ZZ: RSC=");
		dump(System.out, bb.array(), bb.limit());
	}

	private void processRSR(ByteBuffer bb) {
		int c03 = bb.get();
		int c04 = bb.get();

		int serial_no = bb.getInt();
		String jams_ver = fixed_string(bb, 9);

		if (c03 < 0) {
			c03 += 256;
		}
		if (c04 < 0) {
			c04 += 256;
		}
		System.out.println("RSR: skip=" //
				+ " 0x" + Integer.toHexString(c03) //
				+ " 0x" + Integer.toHexString(c04) //
		);

		System.out.println("RSR: serial_no=" + serial_no);
		System.out.println("RSR: jams_ver=" + jams_ver);
	}

	private int processRSD(ByteBuffer bb, int tot_segs) {

		int segs = 0;
		while (bb.remaining() > 0) { // int i = 0; i < n_recs; i++) {
			int pos0 = bb.position();

			int id = bb.getShort();
			if (id != 0x55aa) {
				log.error("unknown section id: {}", Integer.toHexString(id));
			}
			segs++;

			int b1 = unsigned_byte(bb);
			int b2 = unsigned_byte(bb);
			int seg_len = bb.getShort();
			int unk_code = bb.getShort(); // probably 0x79
			if (unk_code != 0x79) {
				log.error("RSD: unk_code not 0x79!");
			}

			// when has_results is 0, b3 is 7a...maybe b3+has_results is a short
			// field?

			System.out.println("RSD: processing " + segs + "/" + tot_segs + " b1/b2=" //
					+ " 0x" + Integer.toHexString(b1) //
					+ " 0x" + Integer.toHexString(b2) //
			);

			parse_header(bb);

			byte zero = bb.get();
			if (zero != 0) {
				System.out.println("RSD: expecting unknown zero !=" + zero); //
			}
			byte n_fields = bb.get();

			// log.debug("FIELDS COUNT={}", n_fields);
			for (int f = 0; f < n_fields; f++) {
				int ftyp = bb.get();
				int nextPos = 0;
				switch (ftyp) {
				case 0x01:
					int fid = bb.get();
					byte o1 = bb.get(); // this could actually be part of the
										// fid?
					// if (o1 != 0x01) {
					// log.error("expecting code 01");
					// }
					nextPos = bb.position() + 18;
					zero = bb.get();
					// if (zero != 0x00) {
					// log.error("expecting code 00");
					// }
					int sensor_val = bb.getInt();
					// String val = getNullTermString(bb);
					String val = fixed_string(bb, 9);
					int u3 = bb.getInt();
					if (u3 != -1) {
						log.error("expecting -1 for u3 but got: " + u3);
						log.error("bb.pos=" + bb.position());
					}

					String fieldDescription = colCodes.get("" + fid);
					log.info("01 FID: " + fid + " VALUE=" + val + "/" + fieldDescription //
							+ "  sensor_12bit=0x" + Integer.toHexString(sensor_val));
					break;
				case 0x02:
				case 0x04:
					nextPos = bb.position() + 20;
					val = fixed_string(bb, 20);
					log.info("0" + ftyp + " VALUE=" + val);
					break;
				case 0x03:
					nextPos = bb.position() + 20;
					System.out.print("ZZ [CALIB] 03 FID: "); //
					for (int i = 0; i < 20; i++) {
						int ch = unsigned_byte(bb);
						System.out.print(" ");
						if (ch < 16)
							System.out.print("0");
						System.out.print(Integer.toHexString(ch));
					}
					System.out.println();
					break;
				case 0x05:
					fid = bb.get();
					o1 = bb.get(); // this could actually be part of the fid?
					if (o1 != 0x01) {
						log.error("expecting code 01");
					}
					nextPos = bb.position() + 18;
					String v1 = getNullTermString(bb);
					String v2 = getNullTermString(bb);

					while (bb.position() < nextPos) {
						byte pad = bb.get();
						if (pad != -1) {
							log.error("expecting pad=0xff got={}", pad);
						}
					}
					log.info("05 FID: " + fid + " V1=" + v1 + " V2=" + v2);
					break;
				default:
					log.error("UNKNOWN FIELD TYPE: " + ftyp);
					break;
				}
				if (nextPos != bb.position()) {
					log.error("did not find correct end of 01 field: {} != {}", nextPos, bb.position());
				}
			}

			if (data_indicator == 0 || data_indicator == 0xff) {
				// ok
			} else {
				log.error("NOT EXPECTING DATA INDICATOR VALUE: 0x" + Integer.toHexString(data_indicator));
			}

			if (test_type == 0x0005 || test_type == 0x0101 || test_type == 0x0102) {
				// ok
			} else {
				log.error("test_typ: 0x" + Integer.toHexString(test_type));
			}

			if (cart_typ == 0x1c || cart_typ == 0x11 || cart_typ == 0x1f || cart_typ == 0x13) {
				// 1c == 228J 11=417Y 1f=calib/blank 13==419W
				// ...note: the code matches the second and 3rd digit!
			} else {
				log.error("UNKNOWN CARTRIDGE: 0x" + Integer.toHexString(cart_typ));
			}

			int pos1 = bb.position();
			int actual_len = (pos1 - pos0);

			if (actual_len != seg_len) {
				log.error("PACKET LENGTH DOES NOT MATCH EXPECTED POS! FIXME!!!");
				bb.position(pos0 + actual_len);
			}

			System.out.println("RSD: complete " + segs + "/" + tot_segs);
		}

		return segs;
	}

	private static void dump(PrintStream out, byte[] array, int len) {
		for (int i = 0; i < len; i++) {

			int byt = unsigned_byte(array[i]);
			if (byt < 0)
				byt += 256;
			if (byt < 16) {
				out.print("0");
			}
			out.print(Integer.toHexString(byt));
			// if (byt > 0x20 && byt < 0x80) {
			// out.print("("); // b
			// out.print((char) byt);
			// out.print(")");
			// }
			out.print(" ");
		}
		out.println();
	}

	private void parse_header(ByteBuffer bb) {
		int start_pos = bb.position();

		bb.get();
		String operator = fixed_string(bb, 17);
		String patient = fixed_string(bb, 17);
		String cartridge = fixed_string(bb, 14);

		data_indicator = unsigned_byte(bb); // blank cartridge is 0x00, patient
											// data is 0xff
		String empty = fixed_string(bb, 12);

		test_type = bb.getShort(); // 0x0005 is calibration, 0x0101 is cartridge
		cart_typ = bb.get();

		System.out.println("ZZ cartridge=" + cartridge + " pat: " + patient + " oper=" + operator + " data_indicator=0x"
				+ Integer.toHexString(data_indicator) + " test_typ=0x" + Integer.toHexString(test_type) + " cart_typ="
				+ cart_typ);
		if (empty.length() != 0) {
			log.error("expecting empty field but got {}", empty);
			System.exit(0);
		}

		System.out.print("ZZ skipping unknown:");
		for (int i = 0; i < 4; i++) {
			int tt = unsigned_byte(bb);
			System.out.print(" ");
			if (tt < 16)
				System.out.print("0");
			System.out.print(Integer.toHexString(tt));
		}
		System.out.println();

		// dump_header_fields( bb );

		System.out.print("ZZ");
		{
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			fail_code = bb.getInt(); // err code?
			if ((fail_code & 0xff) != 0) {
				log.error("INVALID FAIL CODE??? 0x" + Integer.toHexString(fail_code));
			} else {
				fail_code >>= 8;
			}
			int sensor_flag = bb.getShort(); // present if 01 fields have sensor
												// data
			int tempC = bb.getShort(); // temperature C
			int tempF = bb.getShort(); // temperature F
			int q = unsigned_byte(bb); // unknown

			long tm = bb.getInt();
			if (tm < 0) {
				tm += 0x100000000L;
			}
			// tm = 0x80000000L;

			tm -= 0x259E4900;
			java.util.Date time = new java.util.Date(tm * 1000);
			int devSeqNo = bb.getInt();
			System.out.print(" [ERR=" + fail_code + "]");
			System.out.print(" [sf=" + sensor_flag + "]");
			System.out.print(" [tC=" + (tempC / 10.0) + "]");
			System.out.print(" [tF=" + (tempF / 100.0) + "]");
			System.out.print(" [q=0x" + Integer.toHexString(q) + "]");
			System.out.print(" [dt=" + sdf.format(time) + "]");
			System.out.print(" [seq=" + devSeqNo + "]");

		}
		System.out.println();

		String clew = fixed_string(bb, 4);
		String slash0 = fixed_string(bb, 10);
		byte o2 = bb.get();
		String jams = fixed_string(bb, 9);

		System.out.println("   CLEW: " + clew + "   slash0=" + slash0 + " test_jams=" + jams);

		if (bb.position() != start_pos + HEADER_SIZE) {
			log.error("WRONG BUFFER POSITOIN");
			bb.position(start_pos + HEADER_SIZE);
		}
	}

	private void dump_header_fields(ByteBuffer bb) {
		int pos = bb.position();
		System.out.print("ZZ ");
		for (int i = 0; i < 13; i++) {
			int tt = unsigned_byte(bb);
			if (i == 0) {
				System.out.print("[ERR=");
			}
			if (i == 4) {
				System.out.print("] [sf=");
			}
			if (i == 6) {
				System.out.print("] [tC=");
			} else if (i == 8) {
				System.out.print("] [tF=");
			} else if (i == 10) {
				System.out.print("] [?=");
			} else if (i == 11) {
				System.out.print("] [dt=");
			} else if (i == 15) {
				System.out.print("] [seq=");
			} else {
				System.out.print(" ");
			}
			if (tt < 16)
				System.out.print("0");
			System.out.print(Integer.toHexString(tt));
		}
		System.out.println("]");
		bb.position(pos);
	}

	private void skip_pattern(ByteBuffer bb) {
		int start_pos = bb.position();

		byte[] pattern = "JAMS134A".getBytes();
		int pattern_pos = 0;
		while (pattern_pos < pattern.length) {
			byte ch = bb.get();
			if (ch == pattern[pattern_pos]) {
				pattern_pos++;
			} else {
				pattern_pos = 0;
			}
		}

		if (pattern_pos == pattern.length) {
			bb.get(); // null
			int end_pos = bb.position();
			int delta = (end_pos - start_pos);
			if (delta != 112) {
				log.error("unexpected header length: " + delta + " != " + 112);
				log.error("FIXME NOW");
				System.exit(0);
			}
			log.info("start/end = " + start_pos + "/" + end_pos + " len=" + delta);

		} else {

			log.error("Could not find PATTERN END");
		}
	}

	private String fixed_string(ByteBuffer bb, int count) {

		StringBuffer buf = new StringBuffer();
		do {
			byte byt = bb.get();
			count--;
			if (byt < 0) {
				log.error("unprintable char in string?");
			}
			if (byt == 0) {
				break;
			}
			buf.append((char) byt);
		} while (bb.hasRemaining() && count > 0);

		while (count > 0) {
			bb.get();
			count--;
		}
		return buf.toString();
	}

	private String getNullTermString(ByteBuffer bb) {
		StringBuffer buf = new StringBuffer();
		do {
			byte byt = bb.get();
			if (byt < 0) {
				log.error("unprintable char in string?");
			}
			if (byt == 0) {
				break;
			}
			buf.append((char) byt);
		} while (bb.hasRemaining());

		return buf.toString();
	}

	private void processEnquire() throws IOException {
		if (mb_offset > 16) {
			String m = new String(mb_buffer, 0, mb_offset);
			if (m.indexOf("COMMANDMODEcommandmode") > 0) {
				log.error("Maybe send some device init info?");
			} else {
				log.error("INIT session without COMMANDMODEcommandmode");
			}
		}
		sendAck();
		state = STATE.SESSION;
		seq_no = 0;
		data_seq_no = 0;
		mb_offset = 0;
	}

	private void sendNAK() throws IOException {
		log.error("-- NAK of data packet!");

		OutputStream outputStream = getOutputStream();
		outputStream.write(NAK);
	}

	private void sendAck() throws IOException {
		OutputStream outputStream = getOutputStream();
		outputStream.write(ACK);
	}

	private void sendEOT() throws IOException {
		OutputStream outputStream = getOutputStream();
		outputStream.write(EOT);
	}

	private void sendDSQ() throws IOException {
		byte[] dsq = "DSQ".getBytes();
		sendPacket(dsq);
	}

	private void sendSDT() throws IOException {
		Calendar cal = Calendar.getInstance();
		int yr = cal.get(Calendar.YEAR);
		int mon = cal.get(Calendar.MONTH);
		int day = cal.get(Calendar.DAY_OF_MONTH);
		int hr = cal.get(Calendar.HOUR_OF_DAY);
		int min = cal.get(Calendar.MINUTE);
		int sec = cal.get(Calendar.SECOND);

		ByteBuffer bb = ByteBuffer.allocate(11);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put("SDT".getBytes());
		bb.putShort((short) yr);
		bb.put((byte) day);
		bb.put((byte) mon);
		bb.put((byte) min);
		bb.put((byte) hr);
		bb.put((byte) 0);
		bb.put((byte) sec);

		sendPacket(bb.array());
	}

	/*
	 * request firmware info
	 */

	private void sendRFI() throws IOException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.put("RFI".getBytes());
		bb.put((byte) 4);

		sendPacket(bb.array());
	}

	/*
	 * request data
	 */
	private void sendRSQ() throws IOException {
		ByteBuffer bb = ByteBuffer.allocate(5);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		bb.put("RSQ".getBytes());
		bb.putShort((short) data_seq_no);

		sendPacket(bb.array());
	}

	private void sendPacket(byte[] data) throws IOException {
		if (data == null) {
			log.error("cannot send null data pkt");
			return;
		}
		OutputStream o = getOutputStream();
		int chk = CRCUtil.getChecksum(data, 0, data.length);

		o.write(STX);
		o.write(seq_no); // low 8 bits
		o.write(seq_no >> 8); // high 8 bits
		o.write(1); // unknown
		o.write(data.length); // lower 8 bits
		o.write(data.length >> 8); // high 8 bits
		o.write(chk); // lower 8 bits
		o.write(chk >> 8); // high 8 bits
		o.write(data);
		last_data = data;

	}

	@Override
	public int tick() {
		tick++;
		int max_tick = (connected == true) ? 60 : 4;

		ConnectionStatus deviceState = getStatus();
		if (tick > max_tick) {
			if (deviceState != NOT_CONNECTED) {
				connected = false;
				setStatus(ConnectionStatus.NOT_CONNECTED);
				fireNoData(conf);
			}
		} else {
			if (!connected) {
				if (deviceState != NEGOTIATING) {
					// don't repeat the message
					setStatus(ConnectionStatus.NEGOTIATING);
				}
			} else if (deviceState != CONNECTED) {
				setStatus(ConnectionStatus.CONNECTED);
			}
		}
		return 0;
	}

	public static void main(String[] args) {
		byte EOT = 4;
		String[] msgs = { "DSQ", "DQN", "RFI" + (char) EOT, "STN", "RSE" };
		int[] expects = { 0x55d0, 0xe955, 0x8ec0, 0xef6c, 0x2373 };

		for (int i = 0; i < msgs.length; i++) {
			String msg = msgs[i];
			int xpt = expects[i];
			byte[] b = msg.getBytes();
			System.out.println("msg=" + new String(b) + "  expect=" + Integer.toHexString(xpt) + " bits="
					+ Integer.toBinaryString(xpt));

			int vl = CRCUtil.getCRC16g(b, 0, b.length);
			System.out.println("  vl=" + Integer.toHexString(vl));
		}
	}

	private static void guess2(byte[] b, int xpt) {
		int hi = xpt >> 8;
		int lo = xpt & 0xff;

		int r_xpt = 256 * lo + hi;

		System.out.println("  lo-hi = " + Integer.toHexString(xpt) + " --> " + Integer.toHexString(r_xpt));

		for (int seed = 0; seed < 65536; seed++) {
			int crc = CRCUtil.getCRC16X(seed, b, 0, b.length);
			if (crc == xpt) {
				System.out.println("MATCH=" + seed);
			} else if (crc == r_xpt) {
				System.out.println("R_MATCH=" + seed);
			}
		}

	}

	private static void guess(byte[] s, int xpt) {
		int e = 0;
		int o = 0;
		boolean even = true;
		for (int i = 0; i < s.length; i++) {
			System.out.println(" adding --> " + s[i]);
			if (even)
				e = e + s[i];
			else
				o = o + s[i];
			even = !even;
		}
		System.out.println(" tot=" + e + " odd=" + o);
		System.out.println(" bits[0]=" + Integer.toBinaryString(e) + " odd=" + Integer.toBinaryString(o) + " chk0="
				+ Integer.toBinaryString(e + o));

		for (int a = 1; a < 5; a++) {
			for (int b = 1; b < 5; b++) {
				int chk = a * e + b * o;
				System.out.println("     --> =" + Integer.toBinaryString(chk) + "  (" + a + "," + b + ") "
						+ Integer.toBinaryString(chk ^ xpt));

				int low_byt = chk & 0xff;
				int hi_byt = chk >> 8 & 0xff;
				int out = 256 * low_byt + hi_byt;
				if (out == xpt) {
					System.out.println("ANSWER: a=" + a + " b=" + b);
				} else {
					out = 256 * hi_byt + low_byt;
					if (out == xpt) {
						System.out.println("ANSWER: HIGH-LOW a=" + a + " b=" + b);
					}

				}
			}
		}

	}

}
