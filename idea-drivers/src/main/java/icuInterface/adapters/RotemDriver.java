package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class RotemDriver extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "lab/Rotem Delta";

	private int mb_offset = 0;
	private byte[] mb_buffer = new byte[256];

	private int tick;
	private boolean connected = false;

	private static DeviceCapabilities caps;

	static {
		caps = new DeviceCapabilities(RotemDriver.class);

		// RpUnit sec = new LinearUnit(1.0, 0, "sec");
		// RpUnit mm = new LinearUnit(1.0, 0, "mm");
		//
		// RpMetric[] metrics = new RpMetric[] { //
		//
		// RpUtil.createMetric("Par_CT", "CT", "Clotting Time", sec),
		// RpUtil.createMetric("Par_CFT", "CFT", "Clot Formation Time", sec),
		// RpUtil.createMetric("Par_MCF", "MCF", "Maximum Clot Firmness", mm),
		// };
		//
		// caps.setMetrics(metrics);

		caps.setModels(new String[] { "Rotem" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(RotemDriver.class);
		conf.setModelName("Rotem");

		// conf.setMetrics(caps.getMetrics());

		return conf;
	}

	/**
	 * 
	 */
	public RotemDriver(RpDevice conf) {
		super(conf);
	}

	public void sendPacket(byte[] bytes) throws IOException {
		OutputStream outputStream = getOutputStream();
		outputStream.write(bytes);
	}

	public void processMessage(byte[] buf) {
		// ignore it if it is not a complete message
		if (mb_offset < 7) {
			return;
		}

		String line = new String(buf, 0, mb_offset);
		String identifier = line.substring(0, 5);
		if (identifier.equals("roTEG")) {

			connected = true;

			PersistentItem block = null;

			String[] dataArray = line.split("\\|");
			if (dataArray != null && dataArray.length > 11) {
				// setIntItem( block, "Par_CT", dataArray, 7 );
				// setIntItem( block, "Par_CFT", dataArray, 8 );
				// setIntItem( block, "Par_MCF", dataArray, 9 );
				fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
			} else {
				log.warn("short line: {}", line);
			}

		} else {
			log.warn("Invalid data: {}", line);
		}

		tick = 0;
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		setStatus(ConnectionStatus.NEGOTIATING);

		connect(portName, 115200, 8, 1, 0);

	}

	private void sendStartupCommands() throws IOException {
		sendPacket("Start".getBytes());
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	/**
	 * Called when a serial port event occurs
	 */
	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		// Check the event type
		try {

			while (in.available() > 0) {
				int byt = in.read();
				if (mb_offset >= mb_buffer.length) {
					mb_offset = 0; // dump anything received so far
				}

				if (byt < 0)
					break;

				if (byt == '\r' || byt == '\n') {
					processMessage(mb_buffer);
					mb_offset = 0;
				} else {
					mb_buffer[mb_offset++] = (byte) byt;
				}
			}
		} catch (Exception e) {
			// No more lines
			setStatus(NOT_CONNECTED);
			log.error("Exception in serial reader???", e);
		}
	}

	@Override
	public int tick() {
		tick++;
		int max_tick = (connected == true) ? 60 : 4;

		ConnectionStatus deviceState = getStatus();
		if (tick > max_tick) {
			if (deviceState != NOT_CONNECTED) {
				connected = false;
				setStatus(ConnectionStatus.NOT_CONNECTED);
				fireNoData(conf);
			}
		} else {
			if (!connected) {
				if (deviceState != NEGOTIATING) {
					setStatus(ConnectionStatus.NEGOTIATING);
				}
			} else if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}

		return 0;
	}

}
