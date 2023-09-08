package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.SerialConnection;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.dev.CriticoreMeasurement;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class BardUrimeter extends SerialAdapter {

	private static final String driverName = "urimeter/Bard Urimeter";

	private static final int MIN_DELTA_TM = 5000; // only send on numerics
													// message every 5 secs
	private long last_tm_time;

	private int mb_offset = 0;
	private byte[] mb_buffer = new byte[256];

	private int tick;
	private boolean connected = false;

	private static DeviceCapabilities caps;

	static {
		caps = new DeviceCapabilities(BardUrimeter.class);

		caps.setName("Criticore");
		caps.addStream(StreamID.MEASUREMENT, CriticoreMeasurement.class);
		caps.setModels(new String[] { "Criticore" });
		
		caps.addConnection(new SerialConnection(9600, 8, 1, 0));
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(BardUrimeter.class);
		conf.setModelName("Criticore");
		conf.addStream(caps.getStream(StreamID.MEASUREMENT));
		return conf;
	}

	/**
	 * 
	 */
	public BardUrimeter(DeviceConfiguration conf) {
		super(conf);
	}

	public void sendPacket(byte[] bytes) throws IOException {
		OutputStream outputStream = getOutputStream();
		if (outputStream != null) {
			outputStream.write(bytes);
		} else {
			log.warn("output stream is null");
		}
	}

	public void processMessage(byte[] buf) {
		// ignore it if it is not a complete message
		if (mb_offset < 7) {
			return;
		}

		String line = new String(buf, 0, mb_offset);
		if (line.length() > 7) {
			String identifier = line.substring(0, 7);

			// Ensure it is urimeter data
			if (identifier.equals(":CCORE:")) {

				connected = true;

				CriticoreMeasurement bdb = new CriticoreMeasurement();
				bdb.setDriver(this);

				String[] dataArray = line.split(" ");
				if (dataArray != null && dataArray.length > 11) {
					bdb.setCurrentTime(safeParse(dataArray[5]));
					bdb.setCurrentOutput(safeParse(dataArray[6]));
					bdb.setRatePerHour(safeParse(dataArray[7]));
					bdb.setTotalVolume(safeParse(dataArray[8]));
					bdb.setPriorOutput(safeParse(dataArray[9]));
					bdb.setPriorTime(safeParse(dataArray[10]));
				}

				long curr_tm = PlatformUtil.currentTimeMillis();
				if (curr_tm - last_tm_time >= MIN_DELTA_TM) {
					fireStreamEvent(0, this, StreamID.MEASUREMENT, bdb);
					last_tm_time = curr_tm;
				}

				tick = 0;
			}
		}
	}

	private Integer safeParse(String string) {
		Integer val = null;
		try {
			// value of --- is considered a null
			if (!string.startsWith("--")) {
				val = new Integer(string);
			}
		} catch (Exception e) {
			log.error("not a number: *{}*", string);
		}

		return val;
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		try {

			connected = false;
			tick = 0;

			connect(portName, 9600, 8, 1, 0);

			sendStartupCommands();
		} catch (Exception e) {
			log.error("connecting", e);
			throw new IOException(e);
		}

	}

	public void sendStartupCommands() throws IOException {
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
			try {
				sendPacket("\r\n".getBytes());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
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

	public void resetTime() {
		last_tm_time = 0;
	}

}
