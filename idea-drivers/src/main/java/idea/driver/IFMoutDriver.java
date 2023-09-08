package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.DataTyp;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.IFMoutMeasurement;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class IFMoutDriver extends SerialAdapter implements AdapterInterface {
	private static final String driverName = "cardiac/Edwards Vigilance, Vigilance II, Vigileo, EV1000";

	private int next_baudd = 19200;

	private final static byte STX = 0x02;
	private final static byte ETX = 0x03;

	private byte[] mb_buffer = new byte[1024];
	private int mb_offset = 0;

	private static DeviceCapabilities cap;

	private int verbose = 0;
	private int tick;

	static {
		cap = new DeviceCapabilities(IFMoutDriver.class);
		cap.addStream(StreamID.MEASUREMENT, IFMoutMeasurement.class);

		cap.setModels(new String[] { "Vigilance", "Vigilance II", "Vigileo", "EV1000" });

		cap.addConnection(new SerialConnection(19200, 8, 1, 0));

	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(IFMoutDriver.class);
		conf.setName("IFMOUT");
		conf.addStream(cap.getStream(StreamID.MEASUREMENT));

		return conf;
	}

	public IFMoutDriver(RpDevice conf) {
		super(conf);

		AdapterUtil.fix_config(cap, conf);
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port"); // old method
		if (portName == null) {
			portName = conf.getConnectionValue(); // new method
		}

		log.info(" --> connect {}", portName);

		connect(portName, next_baudd, 8, 1, 0);

	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
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

			if (byt == STX || mb_offset > mb_buffer.length - 10) {
				// String mb = new String( mb_buffer );
				// System.out.println( "mb=" + mb );
				mb_offset = 0;

				if (mb_offset > mb_buffer.length - 10) {

				}
			}

			mb_buffer[mb_offset++] = (byte) byt;

			if (mb_offset > 1 && mb_buffer[mb_offset - 2] == ETX) {

				processResponse(mb_buffer, mb_offset);
				for (int i = 0; i < mb_buffer.length; i++) {
					mb_buffer[i] = -1;
				}
				mb_offset = 0;
			}

		}

	}

	private int calcChecksum(byte[] array, int len) {
		int sum = 0;
		for (int i = 0; i < len; i++) {
			byte b = array[i];
			assert (!(i == 0 && b == STX)) : "Message must start with STX";
			assert (b > 0) : "Unexpected value in IFMout message";
			sum += b;
			if (b == ETX)
				break;
		}
		sum = 255 - (sum & 0xff);
		return 0;
	}

	private boolean processResponse(byte[] buf, int len) {
		if (verbose > 1) {
			dump(System.out, buf, len);
		}

		sendNumerics(buf, len);
		return true;
	}

	private void sendNumerics(byte[] buf, int len) {

		if (len < 4) {
			return; // simply invalid
		}
		IFMoutMeasurement bbblock = new IFMoutMeasurement();

		if (log.isDebugEnabled()) {
			String s = new String(buf);
			s = s.substring(1, len - 2);
			log.error("data: {}", s);
		}

		RpMetric[] desc = IntfUtil.getMetrics(bbblock.getClass());

		int offset = 1; // ignore STX
		len -= 2; // ignore checksum
		while (offset < len) {

			int ch = buf[offset];
			if (ch < ' ' || ch > 120) {
				offset++; // ignore STX, ETX, etc
				continue;
			}

			RpMetric m = findMetric(desc, buf, offset);

			if (m == null) {
				if (log.isDebugEnabled()) {
					String field = new String(buf, offset, len);
					log.debug("FIXME: Unknown field:  {}", field);
					String full_buf = new String(buf);
					log.debug("FIXME: full buff={}", full_buf);
				}
				break;
			}

			String s = m.getLocation();

			int data_len = s.length();

			String val = new String(buf, offset + 1, data_len - 1);
			offset += data_len;

			if (m.getSubtyp() == DataTyp.STRING_TYP) {
				IntfUtil.setValue(bbblock, m, val);
			} else {

				try {
					RpUnit unit = m.getUnit();
					double raw = unit.inverse_d(Double.parseDouble(val));
					IntfUtil.setValue(bbblock, m, (int) (raw + 0.5));
					if (log.isDebugEnabled()) {
						log.debug("raw=" + raw + " item={} txt={}", m, val);
					}
				} catch (NumberFormatException e) {
					// this is expected to occur in our string field
					log.warn("format err in IFMoutDriver field={} value={} ", m.getCode(), e.getMessage());

				}
			}
		}

		log.debug("Sending numeric event.");

		fireStreamEvent(0, this, StreamID.MEASUREMENT, bbblock);
		tick = 0;
	}

	private RpMetric findMetric(RpMetric[] desc, byte[] buf, int offset) {

		RpMetric m = null;

		byte ch = buf[offset];
		for (int i = 0; i < desc.length; i++) {
			String s = desc[i].getLocation();
			byte[] bytes = s.getBytes();
			if (bytes[0] == ch) {
				m = desc[i];
				break;
			}
		}

		return m;
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

		int chk = calcChecksum(array, len);
		out.print("(");
		out.print(Integer.toHexString(chk));
		out.print(")");
		out.println();

	}

	@Override
	public int tick() {
		tick++;

		OutputStream out = getOutputStream();
		if (out == null) {
			log.error("device not connected.");
			return -1;
		}
		// try {
		// // System.out.println("PINGING IFMOUT");
		// OutputStream out = port.getOutputStream();
		// out.write("\r\n".getBytes());
		// } catch (IOException e) {
		// // it is ok to fail here
		// // e.printStackTrace();
		// }
		// log.debug( "tick: {}", tick );

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
		}
		return 0;
	}

}
