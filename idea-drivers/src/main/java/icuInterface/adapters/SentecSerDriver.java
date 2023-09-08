package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import static idea.model.dev.SentecSerMeasurement.HR_LOC;
import static idea.model.dev.SentecSerMeasurement.PACO2_LOC;
import static idea.model.dev.SentecSerMeasurement.PI_LOC;
import static idea.model.dev.SentecSerMeasurement.RHP_LOC;
import static idea.model.dev.SentecSerMeasurement.SPO2_LOC;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Timer;
import java.util.TimerTask;

import com.fazecast.jSerialComm.SerialPort;
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
import idea.model.dev.SentecSerMeasurement;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

//
// PROBLEM #1: saving data...died after first save
// PROBLEM #2: output to Excel file off by x10 for 
//

@Slf4j
public class SentecSerDriver extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "misc/Sentec TransQ PCO2 [Serial]";

	private static final byte[] helloPacket = "/hello\r\n".getBytes();
	private static final byte[] onlinePacket = "/online=on\r\n".getBytes();
	private static final byte[] offlinePacket = "/online=off\r\n".getBytes();

	private static final byte[] crlf = "\r\n".getBytes();
	private static DeviceCapabilities cap;

	static {
		cap = new DeviceCapabilities(SentecSerDriver.class);

		cap.addStream(StreamID.MEASUREMENT, SentecSerMeasurement.class);

		cap.setModels(new String[] { "SenTec" });
		cap.addConnection(new SerialConnection(115200, 8, 1, 0));
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(SentecSerDriver.class);
		conf.addStream(StreamID.MEASUREMENT, SentecSerMeasurement.class);
		conf.setModelName("SenTec");
		return conf;
	}

	private byte[] mb_buffer = new byte[256];
	private int mb_offset = 0;

	private Timer restartTimer;

	private int commTimeout;

	private int tick;
	private int metric_idx;
	private SentecSerMeasurement numerics_block;
	private RpMetric[] metrics;

	public SentecSerDriver(RpDevice conf) {
		super(conf);

		AdapterUtil.fix_config(cap, conf);
		numerics_block = initNumericsBlock();
		metrics = IntfUtil.getMetrics(SentecSerMeasurement.class);
	}

	private SentecSerMeasurement initNumericsBlock() {
		SentecSerMeasurement numerics_block = new SentecSerMeasurement();
		numerics_block.setDriver(this);

		return numerics_block;
	}

	@Override
	public void connect() throws IOException {

		setStatus(ConnectionStatus.NEGOTIATING);
		String portName = RpUtil.getParam(conf, "port");
		connect(portName, 115200, 8, 1, SerialPort.NO_PARITY);

		initDataFlow();

	}


	@Override
	public void disconnect() throws IOException {
		if (restartTimer != null) {
			restartTimer.cancel();
		}
		super.disconnect();
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, cap);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	@Override
	public void process(InputStream in, OutputStream os) throws IOException {

		while (in.available() > 0) {
			int byt = in.read();

			if (byt == -1) {
				break;
			}

			mb_buffer[mb_offset++] = (byte) byt;

			if (byt == '\n') {
				processPacket(mb_buffer, mb_offset);

				// debug or redundant clear buffer
				for (int i = 0; i < mb_buffer.length; i++) {
					mb_buffer[i] = -1;
				}
				mb_offset = 0;
			}

			// catch overflow before it happens
			if (mb_offset > mb_buffer.length - 10) {
				mb_offset = 0;
			}
		}

	}

	private void processPacket(byte[] message, int l) throws IOException {

		String m = new String(message, 0, l - 1);

		commTimeout = 5;

		if (m.startsWith("/hello")) {
			// ignore
			return;
		} else if (m.startsWith("/online")) {
			// ignore
			return;
		}

		String[] ar = m.split("=");
		if (ar == null || ar.length != 2) {
			parse_ascii_message(m);

			fireStreamEvent(0, this, StreamID.MEASUREMENT, numerics_block);

			resetForNextFire();
		} else {

			String loc = ar[0];
			String val = ar[1];
			log.info("parsing: {} = {}", loc, val);

			setItem(loc, val);

			// don't know that I understood the last message...
			// increment the timer to wait for a response
			commTimeout = 5;
			get_next_metric();

			if (metric_idx == metrics.length) {
				fireStreamEvent(0, this, StreamID.MEASUREMENT, numerics_block);
				resetForNextFire();
			}
		}

		return;
	}

	private void resetForNextFire() {
		tick = 0;
		commTimeout = 5;
		numerics_block = initNumericsBlock();
	}

	private void get_next_metric() throws IOException {

		OutputStream out = getOutputStream();
		// synchronized (port) {
		metric_idx %= metrics.length;

		RpMetric metric = metrics[metric_idx];
		String loc = metric.getLocation();
		out.write(loc.getBytes());
		out.write(crlf);
		metric_idx++;
		// }
	}

	private void parse_ascii_message(String m) {
		if (m == null || m.length() < 10) {
			return; // no message
		}

		char ch0 = m.charAt(0);
		if (!Character.isDigit(ch0)) {
			// ***SENTEC DIGITAL MONITOR ON-LINE DATA***
			// may be serial number
			return;
		}

		// 2011-10-11 11:45:10 94 72.6 114 0.34 3

		// 2011-10-11 11:45:11 95 72.6 114 0.34 3
		// 2011-10-11 11:45:12 95 72.8 114 0.34 3
		// 2011-10-11 11:45:13 94 u 114 0.34 5
		// 2011-10-11 11:45:14 94? i 114? 0.28? 5 CE
		// 2011-10-11 11:45:15 --- --- --- --- -/- SO

		String[] ar = m.split("\t");
		if (ar == null || ar.length > 4) {

			setItem(SPO2_LOC, ar[1]);
			setItem(PACO2_LOC, ar[2]);
			setItem(HR_LOC, ar[3]);
			setItem(PI_LOC, ar[4]);
			setItem(RHP_LOC, ar[5]);

			// flags follow

		} else {
			log.error("cannot parse message: {}", m);
		}
	}

	private void setItem(String loc, String val) {

		if (val == null || val.length() == 0 || val.equals("i")) {
			return;
		}

		RpMetric item = IntfUtil.getMetricByLoc(numerics_block, loc);

		if (item.getSubtyp() == DataTyp.STRING_TYP) {
			IntfUtil.setValue(numerics_block, loc, val);
		} else {
			// assume integer...only other type supported by this driver

			int ival;
			// LinearUnit unit = (LinearUnit) item.getDescription().getUnit();
			if (val.indexOf('?') > 0) {
				// this can happen....unresolved how to deal with it permenantly
				val = val.replace("?", "");
			}

			// no value
			if ("---".equals(val)) {
				val = "-1.0";
			} else if ("-/-".equals(val)) {
				val = "-1.0";
			} else if (val.endsWith("-")) {
				System.out.print("replacing " + val);
				val = val.substring(0, val.length() - 2);
				System.out.println("  with " + val);
			} else if ("u".equals(val)) {
				val = "-1.0";
			}
			double dval = -1;
			try {
				dval = Double.parseDouble(val);
			} catch (NumberFormatException ee) {
				ee.printStackTrace(); // shouldn't happen
			}
			if (loc.equals(PACO2_LOC)) {
				dval *= 10;
			} else if (loc.equals(PI_LOC)) {
				dval *= 100;
			}
			ival = (int) dval;
			IntfUtil.setValue(numerics_block, loc, ival);
		}
	}

	private void initDataFlow() {
		restartTimer = new Timer();

		TimerTask task = new TimerTask() {

			@Override
			public void run() {
				try {
					timerPulse();
				} catch (Exception e) {

					// dumpPacket(mb_buffer, mb_offset);
					setStatus(NOT_CONNECTED);
					e.printStackTrace();
				}
			}

		};

		restartTimer.schedule(task, 500, 500);
	}

	public void timerPulse() throws IOException {

		OutputStream out = getOutputStream();
		if (out == null) {
			// not connected yet;
			return;
		}
		ConnectionStatus deviceState = getStatus();
		if (deviceState == NOT_CONNECTED && commTimeout == 0) {
			out.write(helloPacket, 0, helloPacket.length);
			commTimeout = 5;
			log.info("sent init request");
		} else if (deviceState == NOT_CONNECTED) {
			commTimeout--;
			if (commTimeout <= 0) {
				setStatus(NOT_CONNECTED);
				commTimeout = 0;
			}
		} else if (deviceState == NEGOTIATING) {

			setStatus(CONNECTED);
			log.debug("<sent autostream request>");

			commTimeout = 5;
		} else if (deviceState == CONNECTED) {

			if (commTimeout == 0) {
				setStatus(NOT_CONNECTED);
			} else {

				// out.write(keepAliveAuto, 0, keepAliveAuto.length);
				commTimeout--;
			}
		} else {
			// assert( false ) : "Invalid state, not handled!";
		}

	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(ConnectionStatus.NOT_CONNECTED);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

}
