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

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.LinkedList;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.BISMeasurement;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class BISAsciiDriver extends SerialAdapter implements AdapterInterface {
	@SuppressWarnings("unused")
	private static final String driverName = "anesthesia/Aspect BIS [ascii]";

	private static final int MIN_DELTA_TM = 5000; // only send on numerics
													// message every 5 secs
	private static final int MAX_MSG = 512;
	private final static String[] short_names = { "SR", "SEF", "SQI", "TOTPOW", "BISBIT", "EMGLOW" };

	/*
	 * for the ASCII protocol
	 */
	private static final String HEADER_REQUEST = "D";
	private static final String CLEAR_ALL_OUTPUT = "C";
	// private static final String ERROR_RECORDS_ON = "E";
	// private static final String ERROR_RECORDS_OFF = "e";
	// private static final String VISTA_MODE_SELECT = "m"; // 0x6d
	// private static final String EVENT_RECORDS_ON = "N";
	// private static final String EVENT_RECORDS_OFF = "n";
	//
	// private static final String UPDATE_OUTPUT_ON = "U";
	private static final String VERSION_REQUEST = "V";
	//
	// private static final String EXTRA_VARIABLES_ON = "X"; // 0x58
	// private static final String EXTRA_VARIABLES_OFF = "x";
	//
	// private static final String IMPEDANCE_RECS_ON = "Z";
	// private static final String IMPEDANCE_RECS_OFF = "z";

	private final static byte CR = 0x0d;
	private final static byte LF = 0x0a;
	// private final static byte ESC = 0x1b;
	//
	// private static final int PESC = (byte) 0xa9;

	/*
	 * Commands
	 */

	protected static DeviceCapabilities cap;

	int mb_offset = 0;
	byte[] mb_buffer = new byte[MAX_MSG];

	private int tick;
	private String[] hdr_line0;
	private String[] fields;

	static {
		cap = new DeviceCapabilities(BISAsciiDriver.class);

		cap.addStream(StreamID.MEASUREMENT, BISMeasurement.class);
		cap.setModels(new String[] { "IPX2" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(BISAsciiDriver.class);
	}

	public BISAsciiDriver(RpDevice conf) {
		super(conf);
		this.conf = conf;

		String[] hdr0 = { "TIME", "DSC", "PIC", "Filters", "Alarm", "Lo-Limit", "Hi-Limit", "Silence" };
		String[] perChannel = { "SR12", "SEF07", "BITSBIT00", "BIS", "TOTPOW07", "EMGLOW01", "SQI10", "IMPEDNCE",
				"ARTF2" };
		String[] channels = { "CH1", "CH2", "CH12" };

		LinkedList<String> ll = new LinkedList<String>(Arrays.asList(hdr0));
		for (String channel : channels) {
			for (String field : perChannel) {
				ll.add(channel + "." + field);
			}
		}

		fields = new String[ll.size()];
		fields = ll.toArray(fields);
	}

	@Override
	public void connect() throws IOException {
		String portName = RpUtil.getParam(conf, "port");
		setStatus(ConnectionStatus.NEGOTIATING);
		super.connect(portName, 9600, 8, 1, 0);

		sendPacket(CLEAR_ALL_OUTPUT);
		sendPacket(VERSION_REQUEST);
		sendPacket(HEADER_REQUEST);

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
				continue;
			}

			if (byt == CR) {
				// LF should come next
			} else if (byt == LF) {
				process();

				mb_offset = 0;
			} else if (byt == 0) {
				mb_offset = 0;
			} else {
				mb_buffer[mb_offset++] = (byte) byt;
			}

		}

	}

	private void process() throws IOException {

		tick = 0;

		if (log.isDebugEnabled()) {
			dump(System.out, mb_buffer, mb_offset);
		}
		if (mb_offset < 4) {
			log.warn("message underflow");
			return; // invalid message!
		}

		String message = new String(mb_buffer, 0, mb_offset);
		if (message.startsWith("VERSION")) {
			log.error("IGNORING VERSION: {}", message);
			sendPacket(HEADER_REQUEST);
		} else if (message.startsWith("ERROR")) {
			log.warn("[BIS] throw alarm due to error");
		} else if (message.startsWith("IMPED")) {
			log.warn("[BIS] what do i do w impedence record");
		} else if (message.startsWith("S_HDR3")) {
			hdr3(message);
		} else if (message.startsWith("TIME")) {
			time(message);
		} else {
			// expecting data w date_time
			data(message);
		}
	}

	private void data(String message) {
		if (fields == null || fields.length == 0) {
			log.warn("NO HEADER FOUND: {}" + message);
			return; // header not received
		}

		boolean assigned = false;
		// RpStream stream = RpUtil.getStream( conf, StreamID.MEASUREMENT);
		// List<RpMetric> conf_metrics = stream.getMetric();
		BISMeasurement block = new BISMeasurement();
		// second header message
		// ignore
		String[] dats = message.split("\\|");
		if (dats.length < fields.length) {
			log.warn("bad bis fields or data");
			return;
		}
		for (int i = 0; i < fields.length; i++) {
			String dat = dats[i].trim();
			if (dat == null || i > dats.length - 1) {
				// ignore
			} else {
				// store
				RpMetric item = block.getMetric(fields[i]);
				if (item == null) {
					log.debug("field not found: {}", fields[i]);
				} else {
					String loc = item.getLocation();
					try {
						int val = -1;
						if (loc.indexOf("BIT") > 0) {
							val = Integer.parseInt("3ff", 16); // 1023
						}
						IntfUtil.setScaledValue(block, item, val);
					} catch (Exception e) {
						log.warn("could not format number: {} for LOC={}", dat, loc);
						e.printStackTrace();
					}
					assigned = true;
				}
			}
		}

		if (assigned) {
			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
			tick = 0;
		}
	}

	private void time(String message) {
		// second header message
		// ignore

		fields = message.split("\\|");
		String pfx = "";
		for (int i = 0; i < fields.length; i++) {
			if (i > 5 && hdr_line0[i] != null) {
				pfx = hdr_line0[i] + ".";
			}

			String field = fields[i].trim();
			for (String short_name : short_names) {
				if (field.startsWith(short_name)) {
					field = short_name;
					break;
				}
			}
			fields[i] = pfx + field;

		}
	}

	private void hdr3(String message) {
		hdr_line0 = message.split("\\|");
		String ver = hdr_line0[1];
		log.debug("VER: ", ver);

		for (int i = 0; i < hdr_line0.length; i++) {
			String pfx = hdr_line0[i].trim();
			if (pfx != null && pfx.length() == 0) {
				pfx = null;
			} else {
				if ("Ch. 1".equals(pfx)) {
					pfx = "CH1";
				} else if ("Ch. 2".equals(pfx)) {
					pfx = "CH2";
				} else if ("Ch. 3".equals(pfx)) {
					log.error("CH3 untested");
					pfx = "CH3";
				} else if ("Ch. 4".equals(pfx)) {
					log.error("CH4 untested");
					pfx = "CH4";
				} else if ("Ch. 12".equals(pfx)) {
					pfx = "CH12";
				}
			}
			hdr_line0[i] = pfx;
		}
	}

	private void sendPacket(String payload) throws IOException {
		OutputStream out = getOutputStream();

		if (out == null) {
			log.error("OUTPUT PORT NOT INITIALIZED");
			return;
		}

		// int capacity = 13;
		// if (payload != null)
		// capacity += payload.length();

		byte[] data_out = payload.getBytes();
		// ByteBuffer bb = ByteBuffer.allocate(capacity);
		// // bb.order( ByteOrder.BIG_ENDIAN );
		//
		// bb.put((byte) START);
		// bb.put(pumpID);
		// bb.put(CR);
		// bb.put(LF);
		// bb.put(payload.getBytes());
		// bb.put(CR);
		// bb.put(LF);
		// data_out = bb.array()

		synchronized (out) {
			out.write(data_out);
			// out.write((byte) END);

		}

		// if (verbose > 1) {
		// System.out.print("[BISDriver] to device: ");
		// dump(System.out, bb.array(), bb.position());
		// }
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

		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 10) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
				try {
					sendPacket(CLEAR_ALL_OUTPUT);
					sendPacket(VERSION_REQUEST);
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
