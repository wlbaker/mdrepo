package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.ERROR;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.math.BigDecimal;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortEvent;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.Deltatrac2_Measurements;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class Deltatrac2 extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "capnography/Deltatrac2";

	int verbose = 1;

	private static DeviceCapabilities cap;

	private int tick;
	StringBuffer line;

	static {
		cap = new DeviceCapabilities(Deltatrac2.class);

		// Deltatrac-2

		cap.addStream(StreamID.MEASUREMENT, Deltatrac2_Measurements.class);
		cap.setModels(new String[] { "Deltatrac" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(Deltatrac2.class);
	}

	/**
	 * 
	 */
	public Deltatrac2(RpDevice conf) {
		super(conf);

		AdapterUtil.fix_config(cap, conf);
	}

	public void sendPacket(byte[] bytes) throws IOException {
		OutputStream outputStream = getOutputStream();
		outputStream.write(bytes);
	}

	public void processMessage(String message) {
		// ignore it if it is not a complete message
		if (message.length() > 7) {
			String identifier = message.substring(0, 3);

			if (identifier.equals("D01")) {
				Deltatrac2_Measurements block = new Deltatrac2_Measurements();

				String[] ar = message.split(",");

				for (RpMetric m : block.getMetrics()) {
					int loc = Integer.parseInt(m.getLocation());
					int value = Integer.parseInt(ar[loc]);
					IntfUtil.setValue(block, m, value);
				}
				fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
				tick = 0;
			} else if (identifier.equals("D96")) {
				// patient setup info
			} else if (identifier.equals("D97")) {
				// calibration
			}
		}
	}

	private Number safeParse(String string) {
		Number val = null;
		try {
			val = new BigDecimal(string);
		} catch (Exception e) {
			// not a number
			System.err.println("not a number: *" + string + "*");
		}
		return val;
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		line = new StringBuffer();

		connect(portName, 1200, 8, 1, 0);

	}

	@Override
	public void requestCapabilities() {
		fireCapabilitiesEvent(this, cap);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	/**
	 * Called when a serial port event occurs
	 */
	@Override
	public void serialEvent(SerialPortEvent event) {
		// Should never happen, but it could ...
		assert (event != null) : "Null event in serial event.";

		SerialPort port = (SerialPort) event.getSource();

		// Check the event type
		switch (event.getEventType()) {
		case SerialPort.LISTENING_EVENT_DATA_AVAILABLE:

			// If we get here then data has been received
			try {
				InputStream inputStream = port.getInputStream();

				int avail = inputStream.available();
				while (avail > 0) {
					int ch = inputStream.read();
					line.append((char) ch);
					if (ch == 10) {
						processMessage(line.toString());
						line.setLength(0);
					}
					avail = inputStream.available();
				}

			} catch (Exception e) {
				// No more lines
				setStatus(ConnectionStatus.ERROR);
				e.printStackTrace();
			}
			break;

		default:
			System.out.println("unknown event: " + event.getEventType());
			break;

		}
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (deviceState == ERROR) {
			return -1;
		}
		if (tick > 80) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(ConnectionStatus.NOT_CONNECTED);
			}
		} else {
			if (deviceState == NEGOTIATING) {
				// ??
			} else if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

}
