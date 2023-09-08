package icuInterface.adapters;

/*
 * Mettler Toledo Standard Interface Command Set -- MT-SICS
 */

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.dev.MTSICSMeasurement;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class MTSICSDriver extends SerialAdapter implements AdapterInterface {
	private static final String driverName = "misc/MTSICS Mettler Toledo Scale";

	private final static byte CR = 0x0d;
	private final static byte LF = 0x0a;

	/*
	 * Commands
	 */

	protected static DeviceCapabilities cap;

	int mb_offset = 0;
	byte[] mb_buffer = new byte[256];

	private int tick;

	static {
		cap = new DeviceCapabilities(MTSICSDriver.class);

		cap.addStream(StreamID.MEASUREMENT, MTSICSMeasurement.class);
		cap.setModels(new String[] { "SICS0" });

		cap.addConnection(
				new SerialConnection(9600, 7, 1, 2));
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(MTSICSDriver.class);
	}

	public MTSICSDriver(DeviceConfiguration conf) {
		super(conf);

	}

	@Override
	public void connect() throws IOException {

		setStatus(ConnectionStatus.NEGOTIATING);
		tick = 99;

		String portName = RpUtil.getParam(conf, "port");
		connect(portName, 9600, 7, 1, 2);

		inquireSICS();
	}

	public void zero() throws IOException {
		sendPacket("Z");
	}

	public void zeroImmediate() throws IOException {
		sendPacket("ZI");
	}

	public void resetBalance() throws IOException {
		sendPacket("@");
	}

	public void inquireSICS() throws IOException {
		sendPacket("I0");
	}

	public void inquireBalanceData() throws IOException {
		sendPacket("I2");
	}

	public void inquireImmediateWeight() throws IOException {
		sendPacket("SI");
	}

	public void inquireImmediateWeightWithRepeat() throws IOException {
		sendPacket("SIR");
	}

	public void inquireStableWeightWithRepeat() throws IOException {
		sendPacket("SIR");
	}

	@Override
	public void reset() {
		mb_offset = 0;
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
					log.error("FIXME: ignoring interrupt", e);
				}
				continue;
			}

			if (mb_offset >= mb_buffer.length) {
				mb_offset = 0;
				continue;
			}

			mb_buffer[mb_offset++] = (byte) byt;
			if (byt == LF) {
				processMessage();
				mb_offset = 0;
			}

		}

	}

	private void processMessage() {

		tick = 0;

		String s = new String(mb_buffer, 0, mb_offset);
		// log.debug("process: {}", s);

		if (mb_offset > 2) {
			String[] ar = s.split("[ \r\n\"]+");
			String cmd0 = ar[0];
			String cmd1 = ar[2];

			if (cmd0.startsWith("Z")) { // Z or ZI -- a zero response
				fireAlarmEvent(this, new Alarm(cmd0, Alarm.INFO, 'Z', "" + cmd1, true));
			} else if (cmd0.equals("I4")) { // got a reset response
				fireAlarmEvent(this, new Alarm(cmd0, Alarm.INFO, '@', "" + cmd1, true));
			} else if (cmd0.equals("I0")) { // ignore inquiry of implemented
											// commands
			} else if (cmd0.equals("I1")) { // ignore inquiry of implemented
											// commands
			} else if (cmd0.equals("I2")) { // inquiry of balance data
				System.out.print(s);
			} else if (cmd0.startsWith("S")) { // inquiry of immediate weight
				int l = ar.length - 1;
				String unit = null;
				Integer wt = null;
				String code = null;
				String desc = null;
				if (l ==3) {
					unit = ar[l];
					l--;
				}
				if (l ==2) {
					double d = Double.parseDouble(ar[l]);
					wt = (int) d;
					l--;
				}
//				if (l > 2) {
//					desc = ar[l];
//					l--;
//				}
//				if (l > 2) {
//					code = ar[l];
//					l--;
//				}
				String status = ar[1];
				fireNumerics(status, code, desc, wt);
			} else {
				log.error("UNKNOWN RESPONSE: {}", s);
			}

		} else {
			log.warn("INVALID DATA: {}", s);
		}
	}

	private void fireNumerics(String status, String code, String desc, Integer weight) {

		MTSICSMeasurement block = new MTSICSMeasurement();
		block.setDriver(this);

		block.setStatus(status);
		block.setCode(code);
		block.setDesc(desc);
		block.setWeight(weight);

		fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
		tick = 0;
	}

	private void sendPacket(String payload) throws IOException {

		OutputStream out = getOutputStream();

		if (out == null) {
			log.error("OUTPUT PORT NOT INITIALIZED");
			return;
		}

		synchronized (out) {
			out.write(payload.getBytes());
			out.write(CR);
			out.write(LF);
		}

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

		log.error("FIXME: subbed out sendPacket(ESC, CONFIG_DATA, {});", configReq);
	}

	@Override
	public int tick() {

		tick++;

		try {
			inquireImmediateWeight();
		} catch (IOException e) {
			log.error("tick", e);
		}

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
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
