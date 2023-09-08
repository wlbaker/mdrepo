package icuInterface.adapters;

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
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.HemolungMeasurement;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class HemolungDriver extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "ecmo/A-Lung Hemolung";

	private byte[] mb_buffer = new byte[1024];
	private int mb_offset = 0;

	private static DeviceCapabilities cap;

	// Integer[] numeric = new Integer[127];
	// int[] numerics_req;
	HemolungMeasurement block = null;

	int sample_count = 0;
	int last_idx = -1;
	private int tick;

	private long last_tm = 0;
	private static final int MIN_RESEND_DT = 3000;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(HemolungDriver.class);
	}

	static {
		cap = new DeviceCapabilities(HemolungDriver.class);

		cap.addStream(StreamID.MEASUREMENT, HemolungMeasurement.class);

		cap.setModels(new String[] { "Hemolung" });
	}

	public HemolungDriver(DeviceConfiguration conf) {
		super(conf);

		fix_config();

	}

	// WARNING: overriding samplesPerPacket and SampleRate...these
	// values are not configurable

	private void fix_config() {
		if (conf == null) {
			return;
		}

	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		connect(portName, 115200, 8, 1, 0);

		initDataFlow();

	}

	/*
	 * The AnalysisPlus software uses all these commands, pretty much in the
	 * order indicated below. Some of them do not appear to be necessary and
	 * have been removed. Those commands remain in comments for reference or
	 * future use.
	 */

	private void initDataFlow() throws IOException {
		OutputStream out = getOutputStream();
		if (out != null) {
			out.write("\r\n".getBytes());
		}
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		while (in.available() > 0) {
			int byt = in.read();

			if (byt == -1) {
				break;
			}

			if (byt == '<') {
				mb_offset = 0;
			} else if (byt == '>') {
				processResponse(mb_buffer, mb_offset);
				mb_offset = 0;
			} else {
				mb_buffer[mb_offset++] = (byte) byt;
				if (mb_offset > mb_buffer.length - 10) {
					mb_offset = 0;
				}
			}

		}

	}

	private boolean processResponse(byte[] message, int len) throws IOException {
		boolean processed = false;

		if (len > 9) {
			String m = new String(message);
			String chksum = m.substring(0, 2);
			String id = m.substring(2, 5);
			String val = m.substring(6, len);

			RpMetric desc = RpUtil.getMetricFromStreamID(conf, StreamID.MEASUREMENT, id);
			if (desc == null) {
				// ignore
			} else {
				addMetric(desc, val);
			}
			processed = true;
		}

		return processed;
	}

	private void addMetric(RpMetric desc, String val) {
		if (block == null) {
			block = new HemolungMeasurement();
		}

		try {

			int ival = Integer.parseInt(val, 16);
			IntfUtil.setValue(block, desc, ival);
		} catch (NumberFormatException nfe) {
			log.error("DESC PARSING: " + desc, nfe);
		}

		long tm = System.currentTimeMillis();
		if (tm - last_tm > MIN_RESEND_DT) {
			last_tm = tm;
			block.setTime(tm);
			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
			block = null;
			tick = 0;
		}
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
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 20) {
			tick = 10;
			try {
				initDataFlow();
			} catch (Exception e) {
				log.error("init data flow", e);
			}
		} else if (tick > 10) {
			if (deviceState != NOT_CONNECTED) {
				int prev_tick = tick;
				fireStreamEvent(0, this, StreamID.MEASUREMENT, null); // send an
																		// empty
				// block
				// resets tick
				tick = prev_tick;

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
