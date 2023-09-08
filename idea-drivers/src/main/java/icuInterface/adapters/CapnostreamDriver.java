package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import static idea.model.dev.CapnostreamMeasurement.L_CO2_ALARMS;
import static idea.model.dev.CapnostreamMeasurement.L_CO2_STATUS;
import static idea.model.dev.CapnostreamMeasurement.L_EtCO2;
import static idea.model.dev.CapnostreamMeasurement.L_FiCO2;
import static idea.model.dev.CapnostreamMeasurement.L_NORESP_PERIOD;
import static idea.model.dev.CapnostreamMeasurement.L_PR;
import static idea.model.dev.CapnostreamMeasurement.L_RR;
import static idea.model.dev.CapnostreamMeasurement.L_SLOW_STATUS;
import static idea.model.dev.CapnostreamMeasurement.L_SPO2;
import static idea.model.dev.CapnostreamMeasurement.L_SPO2_ALARMS;
import static idea.model.dev.CapnostreamWaveform.WF_PKT_SIZE;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;

import icuInterface.ConnectionStatus;
import icuInterface.DriftRectifier;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.dev.CapnostreamMeasurement;
import idea.model.dev.CapnostreamWaveform;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class CapnostreamDriver extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "capnography/Oridion Capnostream";

	private final static int[] wave_data = new int[WF_PKT_SIZE];
	private int sample_count = 0;
	private int tick = 0;

	private final static byte ENABLE_COMM_CMD = (byte) 1;
	private final static byte DISABLE_COMM_CMD = (byte) 2;
	private final static byte INQUIRE_NUMERIC_CMD = (byte) 3;
	private final static byte START_REALTIME_CMD = (byte) 4;
	private final static byte STOP_REALTIME_CMD = (byte) 5;
	private final static byte INQUIRE_PROTOCOL_CMD = (byte) 9;
	private final static byte SET_HOST_CMD = (byte) 18;
	private final static byte SET_HOST_UNICODE_CMD = (byte) 35;
	private final static byte CONFIG_PERIODIC_CMD = (byte) 10;
	private final static byte INQUIRE_PATIENT_ID_CMD = (byte) 11;
	private final static byte INQUIRE_EVENTS_CMD = (byte) 21;
	private final static byte START_TREND_DOWNLOAD_CMD = (byte) 54;
	private final static byte STOP_TREND_DOWNLOAD_CMD = (byte) 55;
	private final static byte START_TREND_CFG_DOWNLOAD_CMD = (byte) 56;
	private final static byte CFG_SETUP_CMD = (byte) 60;

	private final static byte SET_PATIENT_ID_CMD = (byte) 61;
	private final static byte SET_PATIENT_ID_UNICODE_CMD = (byte) 62;

	private final static byte REALTIME_REPLY = (byte) 0;
	private final static byte NUMERIC_REPLY = (byte) 1;
	private final static byte CONFIGURED_NUMERIC_REPLY = (byte) 10;
	private final static byte PATIENT_ID_REPLY = (byte) 2;
	private final static byte PATIENT_ID_UNICODE_REPLY = (byte) 12;
	private final static byte EVENTLIST_REPLY = (byte) 21;
	private final static byte EVENTLIST_UNICODE_REPLY = (byte) 22;
	private final static byte NUMERIC_ITEM_REPLY = (byte) 3;
	private final static byte MESSAGE_HEADER = (byte) 0x85;

	private DriftRectifier drifter;

	private byte[] mb_buffer = new byte[1024];
	private int mb_offset = 0;

	private boolean escaped;
	private int etco2;
	private int fico2;
	private int rr;
	private int spo2;
	private int pr;
	private int slow_stat;
	private int co2_alarms;
	private int spo2_alarms;
	private int co2_units;
	private int co2_stat;
	private int noresp_period;
	private static DeviceCapabilities cap;

	static {
		cap = new DeviceCapabilities(CapnostreamDriver.class);

		cap.addStream(StreamID.MEASUREMENT, CapnostreamMeasurement.class);
		cap.addStream(StreamID.WAVEFORM, CapnostreamWaveform.class);

		cap.setModels(new String[] { "Capnostream" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(CapnostreamDriver.class);
	}

	public CapnostreamDriver(DeviceConfiguration conf) {
		super(conf);

		AdapterUtil.fix_config(cap, conf);
	}

	@Override
	public void connect() throws IOException {
		drifter = new DriftRectifier(500, 250, 10);

		String portName = RpUtil.getParam(conf, "port");
		connect(portName, 9600, 8, 1, 0);

		try {
			log.error("FIXME: handle timing with ticks or a timer!");
			initDataFlow();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	private void initDataFlow() throws InterruptedException, IOException {
		if (getOutputStream() == null) {
			// not connected
			return;
		}
		Thread.sleep(500);
		System.out.println("**req comm enable");
		requestCommEnable();

		Thread.sleep(500);
		System.out.println("**req config-periodic-message");
		requestConfigPeriodicMessage();

		Thread.sleep(500);
		System.out.println("**req realtime");
		requestRealTime();
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		while (in.available() > 0) {
			int byt = in.read();

			if (byt == -1) {
				break;
			}

			if (byt == 0x85) {
				mb_offset = 0;
			}

			if (byt == 0x80) {
				escaped = true;
				continue;
			}

			if (escaped) {
				byt += 0x80;
				escaped = false;
			}

			mb_buffer[mb_offset++] = (byte) byt;

			if (mb_offset > 2 && mb_buffer[0] == MESSAGE_HEADER) {

				int pkt_len = mb_buffer[1];
				if (pkt_len != mb_offset - 3) {
					// System.out.println("len mismatch: " + pkt_len +
					// "!=" + mb_offset + 2);
				} else {
					int xor = byt;

					processResponse(mb_buffer, mb_offset);

					mb_offset = 0;
				}
			}

			if (mb_offset > mb_buffer.length - 10) {
				mb_offset = 0;
			}
		}

	}

	private void send(byte[] req) throws IOException {

		OutputStream out = getOutputStream();
		int chk = 0x0;
		byte len = (byte) req.length;

		ByteBuffer bb = ByteBuffer.allocate(2 * len + 4);
		synchronized (out) {

			bb.put(MESSAGE_HEADER);
			bb.put(len); // assert: len != 0x85 || 0x80....must be escaped
			chk ^= len;

			for (int ch : req) {
				if (ch < 0)
					ch += 256;
				chk ^= ch;

				if (ch == 0x80 || ch == 0x85) {
					bb.put((byte) 0x80);
					ch -= 0x80;
				}
				bb.put((byte) ch);

			}
			chk &= 0xff; // don't know if this is necessary or not.

			if (chk == 0x80 || chk == 0x85) {
				bb.put((byte) 0x80);
				chk -= 0x80;
			}
			bb.put((byte) chk); // bb.array());
			out.write(bb.array(), 0, bb.position());
		}

	}

	private void dump(PrintStream out, byte[] array, int len) {
		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 20 == 0)) {
				out.println();
			}

			int byt = array[i];
			if (byt < 0)
				byt += 256;
			out.print(Integer.toHexString(byt));
			if (byt > 0x20 && byt < 0x80) {
				out.print("(");
				out.print((char) byt);
				out.print(")");
			}
			out.print(" ");
		}

	}

	private void processResponse(byte[] message, int len) throws IOException {

		byte cmd = message[2];
		if (cmd == REALTIME_REPLY) {

			if (len != 8) {
				log.error("invalid REALTIME packet len={}", len);
			}

			byte msg_num = message[3];
			int co2_high = message[4];
			int co2_low = message[5];
			if (co2_low < 0) {
				co2_low += 256;
			}
			if (co2_high < 0) {
				co2_high += 256;
			}
			int co2 = co2_low + 256 * co2_high;
			wave_data[sample_count++] = co2;

			if (sample_count == WF_PKT_SIZE) {

				long tm = drifter.getRectifiedTime(PlatformUtil.currentTimeMillis());

				CapnostreamWaveform block = new CapnostreamWaveform();
				block.setTime(tm);

				int msPerPacket = 1000;
				drifter.setNextExpectedTime(tm + msPerPacket);

				block.setCO2(wave_data);

				fireStreamEvent(0, this, StreamID.WAVEFORM, block);
				sample_count = 0;
				tick = 0;
			}
		} else if (cmd == NUMERIC_REPLY) {

			if (len != 31) {
				log.error("Invalid NUMERIC_REPLY: {}", len);
			}

			etco2 = fix(message[7]);
			fico2 = fix(message[8]);
			rr = fix(message[9]);
			spo2 = fix(message[10]);
			pr = fix(message[11]);
			slow_stat = fix(message[12]);
			co2_alarms = fix(message[16]);
			spo2_alarms = fix(message[17]);
			co2_units = fix(message[28]);

			co2_stat = fix(message[29]);
			noresp_period = fix(message[18]);

			sendNumerics();
			tick = 0;

		} else if (cmd == CONFIGURED_NUMERIC_REPLY) { // some kind of

			if (len != 31) {
				log.error("Invalid CONFIGURED_NUMERIC_REPLY: {}", len);
			}
		} else {
			log.warn("UNKNOWN COMMAND:    >>> CMD=[0x{}] LEN={}", Integer.toHexString(cmd), len);
		}
	}

	private int fix(byte b) {
		int val = b;
		if (val < 0) {
			val += 256;
		}
		return val;
	}

	private void sendNumerics() {
		// long time = PlatformUtil.currentTimeMillis();

		CapnostreamMeasurement item = new CapnostreamMeasurement();
		for (RpMetric metric : item.getMetrics()) {
			String loc = metric.getLocation();
			int fid = Integer.parseInt(loc);

			switch (fid) {
			case L_EtCO2:
				item.setETCO2(etco2);
				break;
			case L_FiCO2:
				item.setFiCO2(fico2);
				break;
			case L_RR:
				item.setRR(rr);
				break;
			case L_SPO2:
				item.setSpO2(spo2);
				break;
			case L_PR:
				item.setPR(pr);
				break;
			case L_SLOW_STATUS:
				item.setSSTAT(slow_stat);
				break;
			case L_CO2_ALARMS:
				item.setCO2ALM(co2_alarms);
				break;
			case L_SPO2_ALARMS:
				item.setSPO2ALM(spo2_alarms);
				break;
			case L_NORESP_PERIOD:
				item.setNOBr(noresp_period);
				break;
			case L_CO2_STATUS:
				item.setCO2STAT(co2_stat);
				break;
			}

			// if (item.getValue().intValue() == 255) {
			// item.setValue(null);
			// }
		}

		fireStreamEvent(0, this, StreamID.MEASUREMENT, item);
	}

	private void requestConfigSetup() throws IOException {
		byte[] req = { CFG_SETUP_CMD, 1, 1 }; // enable temporary alarm silence

		send(req);
	}

	private void requestData(byte param) throws IOException {
		byte[] req = { START_REALTIME_CMD, 0x02, param };

		send(req);
	}

	private void requestCommEnable() throws IOException {

		byte[] req = { ENABLE_COMM_CMD };

		send(req);

	}

	private void requestConfigPeriodicMessage() throws IOException {
		byte[] req = { //
				CONFIG_PERIODIC_CMD, // command
				0x1, // ipi
				0x1 // enable
		};

		send(req);
	}

	private void requestRealTime() throws IOException {

		byte[] req = { START_REALTIME_CMD };

		send(req);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 20) {
			tick = 4;
			if (getOutputStream() != null) {
				try {
					initDataFlow();
				} catch (Exception e) {
					// this should not happen...but the user already knows there
					// is
					// a comm error
					// USB-RS232 replicator disconnected?
					e.printStackTrace();
				}
			}
		} else if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
				sendNumerics(); // empty set of numerics for display, but also
				// resets tick

				setStatus(ConnectionStatus.NOT_CONNECTED);

				etco2 = 255;
				fico2 = 255;
				rr = 255;
				spo2 = 255;
				pr = 255;
				slow_stat = 255;
				co2_alarms = 255;
				spo2_alarms = 255;
				co2_units = 255;
				co2_stat = 255;
				noresp_period = 255;

				sendNumerics();
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(ConnectionStatus.CONNECTED);
			}
		}
		return 0;
	}

}
