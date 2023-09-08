package icuInterface.adapters;

/*
 * this package specifically written to support abbott's Central Data Station, used for iStat
 * 
 * this might be the ASTM protocol
 */
import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.math.BigDecimal;

import com.fazecast.jSerialComm.SerialPort;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.CharValues;
import idea.intf.SerialAdapter;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ASTMDriver extends SerialAdapter {

	@SuppressWarnings("unused")
	private static final String driverName = "lab/ASTM E 1381-91/1394-91 (CLSI LIS1-A/LIS2-A2)";

	private int mb_offset = 0;
	private byte[] mb_buffer = new byte[256];

	private int tick;

	private static DeviceCapabilities caps;

	final static byte[] ack = { CharValues.ACK.get() };
	final static byte[] enq = { CharValues.ENQ.get() };
	final static byte[] nak = { CharValues.NAK.get() };

	private static final String FIELD_DELIMITER = "[|]";

	int checksum;
	int end_of_frame = 0;

	StringBuffer record;

	enum Mode {
		SENDER, RECEIVER, NEUTRAL
	};

	Mode mode = Mode.NEUTRAL;

	private int cs1;

	private int cs2;
	private int frame_no;

	private int frame_terminator;

	private int frame_term_pos;

	static {
		caps = new DeviceCapabilities(ASTMDriver.class);

		caps.addConnection(
				new SerialConnection(9600, 8, 1, SerialPort.NO_PARITY));
		caps.setModels(new String[] { "Abbott CDS" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(ASTMDriver.class);
	}

	/**
	 * 
	 */
	public ASTMDriver(RpDevice conf) {
		super(conf);
	}

	public void sendPacket(byte[] bytes) throws IOException {
		OutputStream outputStream = getOutputStream();
		if (outputStream != null) {
			outputStream.write(bytes);
		}
	}

	public void processFrame() {
		tick = 0;

		String dat = new String(mb_buffer, 3, frame_term_pos);
		record.append(dat);

		if (frame_terminator == CharValues.ETX.getValue()) {
		}

		String rec = record.toString();
		char typ = record.charAt(0);
		log.error("Parsing Record: {}", typ);
		if (typ == 'H') {
			parseH(rec);
		} else if (typ == 'P') {
			parseP(rec);
		} else if (typ == 'Q') {
			parseQ(rec);
		} else if (typ == 'O') {
			parseO(rec);
		} else if (typ == 'R') {
			parseR(rec);
		} else if (typ == 'C') {
			parseC(rec);
		} else if (typ == 'M') {
			parseM(rec);
		} else if (typ == 'S') {
			parseS(rec);
		} else if (typ == 'L') {
			parseL(rec);
		} else {
			log.error("UNKNOWN RECORD CODE: {}", typ);
		}
		// if( block != null ) {
		// this.fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
		// }

	}

	private void parseH(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("HEADER", ar);
	}

	private void parseP(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("PATIENT", ar);
	}

	private void parseQ(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("Q", ar);
	}

	private void parseO(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("O", ar);
	}

	private void parseR(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("R", ar);
	}

	private void parseC(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("C", ar);
	}

	private void parseM(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("M", ar);
	}

	private void parseS(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("S", ar);
	}

	private void parseL(String rec) {
		String[] ar = rec.split(FIELD_DELIMITER);
		dump("L", ar);
	}

	private void dump(String pfx, String[] ar) {
		System.out.print(pfx);
		System.out.println(": ");
		int idx = 0;
		for (String s : ar) {
			System.out.print(++idx);
			System.out.print(" --> ");
			System.out.println(s);
		}
	}

	private Number safeParse(String string) {
		Number val = null;
		try {
			// value of --- is considered a null
			if (!string.startsWith("--")) {
				val = new BigDecimal(string);
			}
		} catch (Exception e) {
			// not a number
			System.err.println("not a number: *" + string + "*");
		}
		return val;
	}

	@Override
	public void connect() throws IOException {

		setStatus(ConnectionStatus.NEGOTIATING);

		String portName = RpUtil.getParam(conf, "port");
		connect(portName, 38400, 8, 1, 0);

		// ASTM host does not initiate communication. The sending device
		// initiates the communication.
		// sendENQ();

	}

	public void sendENQ() throws IOException {
		frame_no = 0;
		sendPacket(enq);
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, caps);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	/**
	 * Called when a serial port event occurs
	 */

	@Override
	public void process(InputStream in, OutputStream os) throws IOException {
		while (in.available() > 0) {
			int byt = in.read();
			if (byt == -1) {
				break;
			}
			process(byt);
		}
	}

	public void process(int byt) throws IOException {

		if (mb_offset >= mb_buffer.length) {
			mb_offset = 0; // dump anything received so far
		}
		if (byt > 32 && byt < 120) {
			System.out.print((char) byt);
		} else {
			System.out.print("<" + byt + ">");
		}

		if (byt == CharValues.ENQ.getValue()) {
			if (mode == Mode.NEUTRAL) {
				getOutputStream().write(ack);
				mode = Mode.RECEIVER;
			} else {
				log.error("Not expecting ENQ for mode: {}", mode);
			}
		} else if (byt == CharValues.NAK.getValue()) {
			System.out.println("-- got NAK");
		} else if (byt == CharValues.ACK.getValue()) {
			// ??
		} else if (byt == CharValues.EOT.getValue()) {
			// ??
			mode = Mode.NEUTRAL;
		} else if (mode == Mode.RECEIVER) {

			if (mb_offset > 248 || byt == CharValues.STX.getValue()) {
				// ? log.error("Overflow");
				mb_offset = 0;
				checksum = 0;
				end_of_frame = 0;
			} else {
				if (end_of_frame == 0) {
					checksum += byt; // ETX/EOT is included in
										// calculation
				} else if (end_of_frame == 1) {
					cs1 = byt - '0';
					end_of_frame++;
				} else if (end_of_frame == 2) {
					cs2 = byt - '0';
					end_of_frame++;
				} else if (end_of_frame == 3) {
					// must be CR
				} else if (end_of_frame == 4) {
					// must be LF
					// verify checksum
					checksum %= 256;
					int cs = cs1 << 4 + cs2;
					if (checksum == cs) {
						System.out.println("GOOD PACKET");
						if (frame_no == mb_buffer[1]) {
							log.error("DUPLICATE PKT");
						} else {
							processFrame();
							frame_no = mb_buffer[1];
						}
						sendPacket(ack);
					} else {
						log.error("BAD PKT: {} != {}", checksum, cs);
						sendPacket(nak);
					}
				}

			}
			mb_buffer[mb_offset++] = (byte) byt;

			if (end_of_frame == 0) {
				if (byt == CharValues.ETB.getValue() || byt == CharValues.ETX.getValue()) {
					end_of_frame++;
					frame_terminator = byt;
					frame_term_pos = mb_offset - 1;
				}
			}
		}
	}

	@Override
	public int tick() {
		tick++;

		boolean connected = this.getStatus() == ConnectionStatus.CONNECTED;
		int max_tick = (connected == true) ? 60 : 4;

		ConnectionStatus deviceState = getStatus();
		if (tick > max_tick) {
			if (deviceState != NOT_CONNECTED) {
				connected = false;
				setStatus(NOT_CONNECTED);
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

}
