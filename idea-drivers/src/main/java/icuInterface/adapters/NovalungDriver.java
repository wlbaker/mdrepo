package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.HashMap;
import java.util.Map;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.Novalung_Measurement;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class NovalungDriver extends SerialAdapter implements AdapterInterface {
	@SuppressWarnings("unused")
	private static final String driverName = "ecmo/Novalung";

	private final static int baudd = 19200;

	private static final int PROTOCOL_REQ = 0xa1;
	private static final int PROTOCOL_RESP = 0xb1;
	private static final int DATA_REQ = 0xa2;
	private static final int DATA_RESP = 0xb2;

	private byte[] protocol_req = { (byte) PROTOCOL_REQ, 0x00, 0x00, 0x5e };
	private byte[] data_req = { (byte) DATA_REQ, 0x00, 0x00, 0x5d };
	private byte[] mb_buffer = new byte[256];
	private int mb_offset = 0;

	private static DeviceCapabilities cap;
	private boolean have_version = false;

	private int tick;

	private static Map<String, RpMetric> map = new HashMap<String, RpMetric>();

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(NovalungDriver.class);
		// conf.setMetrics(cap.getMetrics());

		return conf;
	}

	static {
		cap = new DeviceCapabilities(NovalungDriver.class);

		cap.addStream(StreamID.MEASUREMENT, Novalung_Measurement.class);
		cap.setModels(new String[] { "Novalung" });

		for (RpMetric d : IntfUtil.getMetrics(Novalung_Measurement.class)) {
			map.put(d.getLocation(), d);
		}
		cap.addConnection(new SerialConnection(baudd, 8, 1, 0));

	}

	public NovalungDriver(RpDevice conf) {
		super(conf);

		AdapterUtil.fix_config(cap, conf);
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		log.info(" --> connect {}", portName);

		setStatus(ConnectionStatus.NEGOTIATING);
		connect(portName, baudd, 8, 1, 0);

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	@Override
	public void reset() {
		mb_offset = 0;
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {

		// System.out.print(" recv: ");
		while (in.available() > 0) {
			int byt = in.read();

			// if (verbose > 1) {
			// System.out.print(" ");
			// System.out.print(Integer.toHexString(byt));
			// }
			if (byt == -1) {
				break;
			}

			if (mb_offset == 0) {
				if (byt == PROTOCOL_RESP || byt == DATA_RESP) {
					// ok
				} else {
					// ignore
					System.out.print(" " + Integer.toHexString(byt));
					continue;
				}

			} else if (mb_offset >= mb_buffer.length) {
				mb_offset = 0;
				// error...buffer overrun
				continue;
			}

			mb_buffer[mb_offset++] = (byte) byt;

			if (mb_offset > 3) {
				int len = mb_buffer[1] * 256 + mb_buffer[2];
				if (mb_offset == len + 4) { // id[1], len[2], data[n], crc[1]
					processResponse(mb_buffer, mb_offset);
					mb_offset = 0;
				}
			}

		}

	}

	private int calcChecksum(byte[] array, int len) {
		int sum = 0;
		for (int i = 0; i < len; i++) {
			// byte b = array[i];
			// sum += b;
			int b = array[i];
			if (b < 0) {
				b += 256;
			}
			sum += b;
		}
		sum = 255 - (sum & 0xff);
		return sum;
	}

	private boolean processResponse(byte[] buf, int len) {
		// dump(System.out, buf, len);

		int checksum = calcChecksum(buf, len - 1);
		int ref = buf[len - 1];
		if (ref < 0) {
			ref += 256;
		}
		if (ref != checksum) {
			log.warn("checksum mismatch: {} != {}", Integer.toHexString(ref), Integer.toHexString(checksum));
			return true;
		}

		int msg_id = 256 + buf[0]; // this value is negative
		if (msg_id == PROTOCOL_RESP) {
			have_version = true;
			log.error("GOT PROTOCOL VERSION: {} {}", buf[3], buf[4]);
		} else if (msg_id == DATA_RESP) {
			System.out.println("NOVALUNG: got numerics");
			sendNumerics(buf, len);
		} else {
			log.error("BAD MESSAGE ID: {}", msg_id);
		}
		return true;
	}

	private void sendNumerics(byte[] buf, int len) {

		Novalung_Measurement bbblock = new Novalung_Measurement();

		int id = 0; // ignore msg_id
		ByteBuffer bb = ByteBuffer.wrap(buf, 1 + 2, len - 2);
		bb.order(ByteOrder.BIG_ENDIAN);

		while (bb.hasRemaining()) {
			id++;

			if (id >= 30) {
				// not processing more
				break;
			}
			String loc = "" + id;
			RpMetric m = map.get(loc);

			if (m == null) {
				if (log.isDebugEnabled()) {
					log.debug("FIXME: Unknown field:  {}", loc);
				}
				continue;
			}

			int val;
			switch (id) {
			case 6:
			case 7:
			case 30:
			case 31:
			case 32:
				val = bb.get();
				if (val < 0) {
					val += 256;
				}
				break;
			case 33:
			case 34:
				val = bb.get();
				break;
			default:
				val = bb.getShort();
			}

			RpMetric item = bbblock.getMetric(loc);
			IntfUtil.setValue(bbblock, item, val);
		}

		log.debug("Sending numeric event.");

		fireStreamEvent(0, this, StreamID.MEASUREMENT, bbblock);
		tick = 0;
	}

	@Override
	public int tick() {
		tick++;

		OutputStream out = getOutputStream();
		if (out == null) {
			log.error("device not connected.");
			return -1;
		}

		byte[] req = null;

		if (have_version == false) {
			req = protocol_req;
		}

		ConnectionStatus deviceState = getStatus();
		if (tick > 6) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
				fireNoData(conf);
			}

			tick = 6;
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}

			if (have_version == false) {
				req = protocol_req;
			} else {
				req = data_req;
			}

		}

		if (req != null) {
			try {
				out.write(req);
			} catch (IOException e) {
				log.error("output req fail");
			}
		}
		
		return 0;
	}

}
