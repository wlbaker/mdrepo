package icuInterface.adapters;

/*
 * TODO: Turn on extra variables: see command 0x58 section 4.3.2.4
 * TODO: CH3 and CH4 untested
 * TODO: Pediatric?
 * TODO: Is this VISTA mode? some things require it.
 * 
 * NOTE: BURST may be -3276.8 if mode or sensor not selected correctly.
 *       See Serial Port Technical Specification
 */
import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import static idea.model.dev.BISSensors.SAMPLE_RATE;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.adapters.bis.be_trend_variables_extra_info;
import icuInterface.adapters.bis.be_trend_variables_info;
import icuInterface.adapters.bis.processed_vars_msg;
import icuInterface.adapters.bis.processed_vars_with_extra_vars_msg;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.model.dev.BISMeasurement;
import idea.model.dev.BISSensors;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class BISBinaryDriver extends SerialAdapter implements AdapterInterface {
	@SuppressWarnings("unused")
	private static final String driverName = "anesthesia/Aspect BIS [binary]";

	private static final int MAX_MSG = 512;

	private static final short START_OF_PACKET = (short) 0xabba;
	int pkt_seq_id;
	private static final short L1_DATA_PACKET = 1;
	private static final short L1_ACK_PACKET = 2;
	private static final short L1_NAK_PACKET = 3;

	/*
	 * host to device
	 */
	private final static short SEND_RAW_EEG = 111;
	private final static short STOP_RAW_EEG = 112;
	private final static short SEND_PROCESSED_VARS = 115;
	private final static short STOP_PROCESSED_VARS = 116;
	private final static short TURN_ON_IMPED_MSG = 1000;
	private final static short TURN_OFF_IMPED_MSG = 1001;
	private final static short TURN_ON_ERROR_MSG = 1002;
	private final static short TURN_OFF_ERROR_MSG = 1003;
	private final static int SEND_REVISION_INFO = 1004;
	private final static short SEND_PROCESSED_VARS_LABELS = 133;
	private final static short SEND_EEG_SNIPPET = 1006;
	private final static short SEND_NEXT_EEG_SNIPPET_PKT = 1007;
	private final static short SEND_BIS_HISTORY = 1009;
	private final static short SEND_NEXT_HISTORY_PKT = 1010;
	private final static short SEND_NEXT_BIG_HISTORY_PKT = 1011;
	private final static short TURN_ON_SEND_EVENT = 1014;
	private final static short TURN_OFF_SEND_EVENT = 1015;
	private final static short SEND_EXTRA_VARIABLES = 1019;
	private final static short STOP_EXTRA_VARIABLES = 1020;
	private final static short SEND_PROCESSED_VARS_4B = 1025;
	private final static short SEND_PROCESSED_VARS_LABELS_4B = 1026;

	private static final short PESC = (byte) 0xa9;

	/*
	 * device to host
	 */

	// Raw EEG data, 8 packets per second
	// If VISTA Legacy Binary Mode is selected and a
	// bilateral sensor is connected, VISTA will send a
	// 2 channel EEG message but the data will be
	// invalid. To get raw EEG data for a Bilateral
	// Sensor, use the VISTA Binary Mode

	private final static short M_DATA_RAW = 50;
	private final static short M_PROCESSED_VARS = 52; // Processed Variables
														// once per second
	private final static short M_PROCESSED_VARS_AND_SPECTRA = 53; // Processed
																	// Variables
																	// and
																	// Spectra
																	// once per
																	// second
	private final static short SER_IMPED_MSG = 1100; // Impedance values from
														// Sensor Check or
														// Continuous Ground
														// Check
	private final static short SER_ERROR_MSG = 1101; // Error Messages
	private final static short SER_REVISION_INFO = 1102; // Software / System
															// Revision Info
	private final static short M_PROCESSED_VARS_LABELS = 63; // Labels
	private final static short SER_EEG_SNIPPET_HEADER = 1104; // EEG Snippet
																// Header
																// (A-2000 Only)
	private final static short SER_EEG_SNIPPET_RAW_DATA = 1105; // EEG Snippet
																// Data (A-2000
																// Only)
	private final static short SER_EEG_SNIPPET_PROCESSED_DATA = 1106; // EEG
																		// Snippet
																		// Processed
																		// Variables
																		// (A-2000
																		// Only)
	private final static short SER_NO_SNIPPET = 1107; // No EEG Snippet Present
														// (A-2000 Only)
	private final static short SER_SNIPPET_CORRUPTED = 1108; // EEG Snippet
																// Error (A-2000
																// Only)
	private final static short SER_BIS_HISTORY_HEADER = 1109; // BIS History
																// Header
																// (A-2000 Only,
																// Protocol Rev.
																// 1.06 and
																// higher)
	private final static short SER_BIS_HISTORY_DATA = 1110; // BIS History Data
															// (A-2000 Only,
															// Protocol Rev.
															// 1.06 and higher)
	private final static short SER_NO_HISTORY = 1111; // No BIS History (A-2000
														// Only, Protocol Rev.
														// 1.06 and higher)
	private final static short SER_EVENT_MSG = 1115; // Indicates that an event
														// was marked on the
														// A-2000 or VISTA at
														// the time specified
														// (Protocol Rev. 1.07
														// and higher)
	private final static short M_PROCESSED_VARS_WITH_EXTRA_VARS = 1120; // Processed
																		// Variables
																		// with
																		// Burst
																		// (Protocol
																		// Rev.1.08
																		// and
																		// higher)
	private final static short M_PROCESSED_VARS_AND_SPECTRA_WITH_EXTRA_VARS = 1121; // Processed
																					// Variables
																					// with
																					// Burst
																					// and
																					// Spectra

	private final static short M_PROCESSED_VARS_4B = 1122; // Bilateral
															// Processed
															// Variables
															// (Protocol Rev.
															// 1.09 � �VISTA
															// Binary�)
	private final static short M_PROCESSED_VARS_4B_AND_SPECTRA = 1123; // Bilateral
																		// Processed
																		// Variables
																		// and
																		// Spectra
																		// (Protocol
																		// Rev.
																		// 1.09
																		// �
																		// �VISTA
																		// Binary�)
	private final static short M_PROCESSED_VARS_LABELS_4B = 1124; // Bilateral
																	// Labels
																	// (Protocol
																	// Rev. 1.09
																	// � �VISTA
																	// Binary�)
	/*
	 * Commands
	 */

	private static final int HEADER_SIZE = 8;
	private int[] wave1;
	private int[] wave2;
	private int[] wave3;
	private int[] wave4;
	private int seq_no = 0;

	protected static DeviceCapabilities cap;

	int mb_offset = 0;
	byte[] mb_buffer = new byte[MAX_MSG];

	private int tick_params;
	private int tick_wf;

	private int mb_trigger_len;

	private int verbose = 1;

	private boolean need_eeg;

	static {
		cap = new DeviceCapabilities(BISBinaryDriver.class);

		cap.addStream(StreamID.MEASUREMENT, BISMeasurement.class);
		cap.addStream(StreamID.WAVEFORM, BISSensors.class);

		cap.setModels(new String[] { "IPX2" });

		cap.addConnection(new SerialConnection(57600, 8, 1, 0));
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(BISBinaryDriver.class);
	}

	public BISBinaryDriver(RpDevice conf) {
		super(conf);
		this.conf = conf;

		// String[] hdr0 = { "TIME", "DSC", "PIC", "Filters", "Alarm",
		// "Lo-Limit", "Hi-Limit", "Silence" };
		// String[] perChannel = { "SR12", "SEF07", "BITSBIT00", "BIS",
		// "TOTPOW07", "EMGLOW01", "SQI10", "IMPEDNCE",
		// "ARTF2" };
		// String[] channels = { "CH1", "CH2", "CH12" };

	}

	@Override
	public void connect() throws IOException {
		String portName = RpUtil.getParam(conf, "port");
		tick_params = 6;
		setStatus(ConnectionStatus.NEGOTIATING);

		super.connect(portName, 57600, 8, 1, 0);

		log.debug("opened port {}", portName);

		seq_no = 0;
		reqRevisionInfo();
	}

	private void reqRevisionInfo() throws IOException {
		log.debug("requesting revision");

		ByteBuffer bb = ByteBuffer.allocate(12);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.putInt(6); // routing id
		bb.putInt(SEND_REVISION_INFO);
		bb.putShort((short) seq_no++); // seq_no
		bb.putShort((short) 0); // length
		sendPacket(bb.array());
	}

	private void reqProcessedVarLabels() throws IOException {

		log.debug("requesting processed var LABELS");
		ByteBuffer bb = ByteBuffer.allocate(12);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.putInt(4); // routing id
		bb.putInt(SEND_PROCESSED_VARS_LABELS);
		bb.putShort((short) seq_no++); // seq_no
		bb.putShort((short) 0); // length
		sendPacket(bb.array());
	}

	private void reqProcessedVars(byte w_spectra) throws IOException {

		log.debug("requesting processed vars");
		ByteBuffer bb = ByteBuffer.allocate(13);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.putInt(4); // routing id..check...4
		bb.putInt(SEND_PROCESSED_VARS); // 115...check
		bb.putShort((short) seq_no++); // seq_no
		bb.putShort((short) 1); // length...check
		bb.put(w_spectra); // with spectra
		sendPacket(bb.array());
	}

	private void reqExtraVariables() throws IOException {

		log.debug("requesting extra vars");
		ByteBuffer bb = ByteBuffer.allocate(12);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.putInt(5); // routing id
		bb.putInt(SEND_EXTRA_VARIABLES);
		bb.putShort((short) seq_no++); // seq_no
		bb.putShort((short) 0); // length
		sendPacket(bb.array());
	}

	private void reqProcessedVars4B(byte w_spectra) throws IOException {

		log.error("requesting processed vars 4B");

		ByteBuffer bb = ByteBuffer.allocate(13);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.putInt(4); // routing id
		bb.putInt(SEND_PROCESSED_VARS_4B);
		bb.putShort((short) seq_no++); // seq_no
		bb.putShort((short) 0); // length
		bb.put(w_spectra); // with spectra
		sendPacket(bb.array());

	}

	private void reqRawEEG() throws IOException {
		log.debug("requesting EEG");
		ByteBuffer bb = ByteBuffer.allocate(14);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.putInt(4); // routing id
		bb.putInt(SEND_RAW_EEG);
		bb.putShort((short) seq_no++); // seq_no
		bb.putShort((short) 2); // length
		bb.putShort(SAMPLE_RATE); // rate
		sendPacket(bb.array());
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		while (in.available() > 0) {

			int byt = in.read();

			if (byt == -1) {
				System.out.print(".");
				try {
					Thread.sleep(200);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				continue;
			}

			if (mb_offset >= MAX_MSG) {
				mb_offset = 0;
				mb_trigger_len = 0;
				continue;
			}

			if (mb_offset == 0 && byt != 0xba) {
				// log.error("IGNORING BAD DATA-0: 0x{} pos={}",
				// Integer.toHexString(byt), mb_offset);
				mb_offset = 0;
				continue;
			}

			if (mb_offset == 1 && byt != 0xab) {
				// log.error("IGNORING BAD DATA-1: 0x{} pos={}",
				// Integer.toHexString(byt), mb_offset);
				mb_offset = 0;
				continue;
			}

			mb_buffer[mb_offset++] = (byte) byt;
			if (mb_offset == 6) {
				int opt_len = unsigned_byte(mb_buffer[4]);
				opt_len += 256 * unsigned_byte(mb_buffer[5]);

				mb_trigger_len = 10 + opt_len;
			}

			if (mb_offset == mb_trigger_len && mb_trigger_len > 0) {
				process();
				mb_trigger_len = 0;
				mb_offset = 0;
			}

		}

	}

	private void process() throws IOException {

		tick_params = 0;

		if (log.isDebugEnabled()) {
			dump(System.out, mb_buffer, mb_offset);
		}
		if (mb_offset < 4) {
			log.warn("message underflow");
			return; // invalid message!
		}

		ByteBuffer bb = ByteBuffer.wrap(mb_buffer, 0, mb_offset);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		int start_ind = unsigned_short(bb);
		int seq_id = unsigned_short(bb);
		int opt_len = unsigned_short(bb);
		int directive = unsigned_short(bb);

		byte[] pkt = null;
		if (opt_len > 0) {
			pkt = new byte[opt_len];
			bb.get(pkt);
		}
		int chksum = unsigned_short(bb);
		int new_checksum = calculate_checksum(mb_buffer, 2, mb_offset - 2);

		if (verbose > 1) {
			System.out.println();
			System.out.print("From device: ");
			dump(System.out, mb_buffer, mb_offset);
			System.out.println();
		}

		// calc checksum and compare
		if (new_checksum != chksum) {
			log.error("Checksum failure: expected=0x{}", Integer.toHexString(new_checksum));

			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			PrintStream out = new PrintStream(baos);
			dump(out, mb_buffer, mb_offset);
			out.close();
			log.error(baos.toString());
			sendNAK();
		} else {
			switch (directive) {
			case L1_NAK_PACKET:
				log.error("got NAK PKT: {}", seq_id);
				break;
			case L1_ACK_PACKET:
				log.error("got ACK PKT: {}", seq_id);
				break;
			case L1_DATA_PACKET:
				processDataPacket(pkt);
				break;
			default:
				log.error("got BAD PAKT TYPE: {}", directive);
			}

		}
	}

	private void processDataPacket(byte[] pkt) throws IOException {
		sendACK();
		ByteBuffer bb = ByteBuffer.wrap(pkt);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		int routing_id = bb.getInt();
		int message_id = bb.getInt();
		int seq_no = unsigned_short(bb);
		int len = unsigned_short(bb);

		if (need_eeg == true) {
			reqRawEEG();
			need_eeg = false;
			return;
		}
		switch (message_id) {
		case SER_REVISION_INFO:
			log.debug("revinfo pkt: {}", message_id);
			processRevisionInfo(bb, seq_no, len);
			// reqProcessedVars4B( (byte) 0 );
			// reqExtraVariables();
			reqProcessedVars((byte) 1);
			need_eeg = true;
			break;
		case M_PROCESSED_VARS:
			log.debug("processed vars pkt: {}", message_id);
			processProcessedVars(bb, seq_no, len);
			break;
		case M_PROCESSED_VARS_AND_SPECTRA:
			log.debug("vars w spectra: {}", message_id);
			processProcessedVars(bb, seq_no, len);
			log.debug("vars w spectra: pos/remaining = {} / {}", bb.position(), bb.remaining());
			break;
		case M_PROCESSED_VARS_WITH_EXTRA_VARS:
			log.debug("vars w extra pkt: {}", message_id);
			processProcessedVarsWithExtraVars(bb, seq_no, len);
			break;
		case M_PROCESSED_VARS_AND_SPECTRA_WITH_EXTRA_VARS:
			log.debug("vars and spectra w extra pkt: {}", message_id);
			processProcessedVarsWithExtraVars(bb, seq_no, len);
			break;
		case M_DATA_RAW:
			processDataRaw(bb, seq_no, len);
			break;
		default:
			log.error("No support for message received id={}", message_id);
			break;
		}

	}

	private void processDataRaw(ByteBuffer bb, int seq_no, int len) {

		BISSensors wf = new BISSensors();
		int num_channels = bb.getShort();
		int num_samples = SAMPLE_RATE / 8;
		if (wave1 == null) {
			wave1 = new int[num_samples];
			wave2 = new int[num_samples];
			wave3 = new int[num_samples];
			wave4 = new int[num_samples];
		}

		for (int i = 0; i < num_samples; i++) {
			wave1[i] = bb.getShort();
			wave2[i] = bb.getShort();
			if (num_channels == 4) {
				wave3[i] = bb.getShort();
				wave4[i] = bb.getShort();
			}
		}

		wf.setEeg1(wave1);
		wf.setEeg2(wave2);

		tick_wf = 0;
		fireStreamEvent(0, this, StreamID.WAVEFORM, wf);
	}

	private void fireProcessedVars(be_trend_variables_info[] vars) {
		be_trend_variables_info var = vars[0];
		String ch = "CH12.";
		PersistentItem block = buildBlockFromVariable(ch, var);
		if (block != null) {
			tick_params = 0;
			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
		}
	}

	private void fireProcessedVarsWithExtra(be_trend_variables_extra_info[] vars) {
		be_trend_variables_extra_info var = vars[0];
		String ch = "CH12.";
		PersistentItem block = buildBlockFromVariable(ch, var);
		if (block != null) {
			IntfUtil.setScaledValue(block, ch + "BURST", var.getBurst_per_min());
			tick_params = 0;
			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
		}
	}

	private PersistentItem buildBlockFromVariable(String ch, be_trend_variables_info var) {
		if (conf == null) {
			return null;
		}

		BISMeasurement block = new BISMeasurement();

		if (var.getBispectral_index() > -1) {
			IntfUtil.setScaledValue(block, ch + "BIS", var.getBispectral_index());
		}
		if (var.getBispectral_alternate_index() > -1) {
			IntfUtil.setScaledValue(block, ch + "BISALT", var.getBispectral_alternate_index());
		}
		if (var.getBispectral_alternate2_index() > -1) {
			IntfUtil.setScaledValue(block, ch + "BISAL2", var.getBispectral_alternate2_index());
		}
		IntfUtil.setScaledValue(block, ch + "SQI", (int) var.getBis_signal_quality());
		if (var.getBurst_suppress_ratio() > -1) {
			IntfUtil.setScaledValue(block, ch + "SR", var.getBurst_suppress_ratio());
		}
		IntfUtil.setScaledValue(block, ch + "EMGLOW", var.getEmg_low());
		IntfUtil.setScaledValue(block, ch + "TOTPOW", var.getTotal_power());
		IntfUtil.setScaledValue(block, ch + "BISBIT", var.getBis_bits());
		IntfUtil.setScaledValue(block, ch + "ARTF2", (int) var.getSecond_artifact());
		IntfUtil.setScaledValue(block, ch + "SEF", var.getSpectral_edge_95());

		return block;
	}

	private void processProcessedVars(ByteBuffer bb, int seq_no, int len) {
		processed_vars_msg p = new processed_vars_msg(bb);
		log.debug("processed vars");
		fireProcessedVars(p.getTrend_variables());
	}

	private void processProcessedVarsWithExtraVars(ByteBuffer bb, int seq_no, int len) {
		processed_vars_with_extra_vars_msg p = new processed_vars_with_extra_vars_msg(bb);
		log.debug("processed vars with extra");

		fireProcessedVarsWithExtra(p.getTrend_variables_extra());
	}

	private void processRevisionInfo(ByteBuffer bb, int seq_no, int len) {
		log.error("Process revision info!");
	}

	private void sendACK() {
		// document says ACK/NAK not necessary since no retrasmit anyway
		// log.error("send ack");
		tick_params = 0;
	}

	private void sendNAK() {
		// document says NAK not necessary since no retransmit anyway
		log.error("send NAK");
	}

	private int unsigned_short(ByteBuffer bb) {
		int v = bb.getShort();
		if (v < 0) {
			v += 65536;
		}
		return v;
	}

	private int unsigned_byte(int v) {
		if (v < 0) {
			v += 256;
		}
		return v;
	}

	private void sendPacket(byte[] payload) throws IOException {

		{
			int m_id = unsigned_byte(payload[4]) + 256 * payload[5];
			int seq = unsigned_byte(payload[8]) + 256 * payload[9];
			log.error("send pkt id: {} seq: {}", m_id, seq);
		}
		if (seq_no > 64) {
			seq_no = 0;
		}

		OutputStream out = getOutputStream();

		if (out == null) {
			log.error("OUTPUT PORT NOT INITIALIZED");
			return;
		}

		short optionalLength = 0;
		short layer_directive = L1_DATA_PACKET;

		if (payload != null) {
			optionalLength += payload.length;
		}

		ByteBuffer header = ByteBuffer.allocate(HEADER_SIZE);
		header.order(ByteOrder.LITTLE_ENDIAN);
		//
		header.putShort(START_OF_PACKET);
		header.putShort((short) pkt_seq_id++);
		header.putShort(optionalLength);
		header.putShort(layer_directive);

		int check1 = calculate_checksum(header.array(), 2, HEADER_SIZE);
		int check2 = calculate_checksum(payload, 0, payload.length);
		int checksum = check1 + check2;

		synchronized (out) {
			out.write(header.array());
			out.write(payload);
			int low_b = (byte) (checksum & 0xff);
			int hi_b = (byte) (checksum >> 8);
			if (low_b < 0) {
				low_b += 256;
			}
			if (hi_b < 0) {
				hi_b += 256;
			}

			out.write(low_b);
			out.write(hi_b);

			if (verbose > 1) {
				System.out.println("[BISDriver] to device");
				System.out.print("> ");
				dump(System.out, header.array(), header.position());
				System.out.print("+ ");
				dump(System.out, payload, payload.length);
				System.out.println("+ CHK=" + Integer.toHexString(low_b) + Integer.toHexString(hi_b));
			}
		}

	}

	private int calculate_checksum(byte[] header, int offset, int len) {
		int checksum = 0;
		for (int i = offset; i < len; i++) {
			int b = unsigned_byte(header[i]);
			checksum += b;
			// System.out.println("chk += " +
			// Integer.toHexString(unsigned_byte(header[i])) + " = " +
			// Integer.toHexString(checksum) );
		}
		return checksum & 0xffff;
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

	@Override
	public int tick() {

		tick_params++;
		tick_wf++;

		if (tick_wf > 6) {
			need_eeg = true;
			tick_wf = 0;
		}
		// // System.out.print("t");
		// try {
		// // reqProcessedVars();
		// reqExtraVariables();
		// } catch (IOException e1) {
		// // TODO Auto-generated catch block
		// e1.printStackTrace();
		// }

		ConnectionStatus deviceState = getStatus();
		if (tick_params >= 5) {
			if (tick_params > 100) {
				tick_params = 11;
			}
			try {
				if (tick_params % 5 == 0) {
					seq_no = 0;
					reqRevisionInfo();
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if (tick_params > 10 && deviceState != NOT_CONNECTED) {
				fireNoData(conf);
				setStatus(NOT_CONNECTED);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		return 0;
	}

}
