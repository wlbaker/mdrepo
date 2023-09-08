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
import idea.model.dev.CardiohelpMeasurement;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class CardiohelpDriver extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "ecmo/CardioHelp";

	private byte[] mb_buffer = new byte[1024];
	private int mb_offset = 0;

	private static DeviceCapabilities cap;

	Integer[] numeric = new Integer[127];
	int[] numerics_req;

	int sample_count = 0;
	int last_idx = -1;
	private int tick;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(CardiohelpDriver.class);
	}

	static {
		cap = new DeviceCapabilities(CardiohelpDriver.class);

		cap.addStream(StreamID.MEASUREMENT, CardiohelpMeasurement.class);
	}

	public CardiohelpDriver(DeviceConfiguration conf) {
		super(conf);
	}

	@Override
	public void connect() throws IOException {

			String portName = RpUtil.getParam(conf, "port");

			connect(portName, 9600, 8, 1, 0);

	}

	/*
	 * The AnalysisPlus software uses all these commands, pretty much in the
	 * order indicated below. Some of them do not appear to be necessary and
	 * have been removed. Those commands remain in comments for reference or
	 * future use.
	 */

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		while (in.available() > 0) {
			int byt = in.read();

			if (byt == -1) {
				break;
			}

			mb_buffer[mb_offset++] = (byte) byt;

			if (processResponse(mb_buffer, mb_offset)) {
				for (int i = 0; i < mb_buffer.length; i++) {
					mb_buffer[i] = -1;
				}
				mb_offset = 0;
			}

			if (mb_offset > mb_buffer.length - 10) {
				mb_offset = 0;
			}
		}

	}

	private boolean processResponse(byte[] message, int len) throws IOException {
		boolean processed = false;

		if (len > 2) {

			processed = true;
		}

		return processed;
	}

	private void sendNumerics() {
		// long time = PlatformUtil.currentTimeMillis();

		CardiohelpMeasurement block = new CardiohelpMeasurement();
		RpMetric[] metrics = IntfUtil.getMetrics(block);

		for (RpMetric metric : metrics) {
			log.error("should be a better way than parsing the int");
			int fid = Integer.parseInt(metric.getLocation());
			IntfUtil.setValue(block, metric, fid);
		}

		fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
		tick = 0;

		for (int i = 0; i < numeric.length; i++) {
			numeric[i] = null; // Integer.MIN_VALUE;
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
			tick = 4;
			// ?? initDataFlow();
		} else if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
				int prev_tick = tick;
				sendNumerics(); // empty set of numerics for display, but also
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
