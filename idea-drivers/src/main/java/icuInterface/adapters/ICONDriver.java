package icuInterface.adapters;

/*
 * To put ICON in DEMO mode, disconnect leads and press:
 * LEFT-RIGHT-CENTER-LEFT-RIGHT-CENTER from main screen.
 * 
 * Sample output:
 * [in] :5%0913:52:56%09male%0946y%0990.00%09187.0%09-
 *        %09100%0969.4%09106.19%097.37%0928%0971.4%09323
 *        %0949.21%091.18%093.41%090.08%093%097%09-%09-%09-
 *        %09-%09-%09-%09-%09-%09-%09-%09-%09-%09-%090.30%0990%09300%0D%0A
 */

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
import idea.conf.DeviceConfiguration;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.dev.ICONResult;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ICONDriver extends SerialAdapter {

	private static final String driverName = "cardiac/ICON Portable Monitor";

	private static DeviceCapabilities caps;
	private int mb_offset = 0;
	private byte[] mb_buffer = new byte[256];

	private int tick;
	private int verbose = 0;
	private boolean alarming;

	static {
		caps = new DeviceCapabilities(ICONDriver.class);

		caps.addStream(StreamID.MEASUREMENT, ICONResult.class);
		caps.setModels(new String[] { "ICON" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(ICONDriver.class);
		conf.addStream(StreamID.MEASUREMENT, ICONResult.class);
		conf.setModelName("ePump");
		return conf;
	}

	/**
	 * 
	 */
	public ICONDriver(DeviceConfiguration conf) {
		super(conf);

		AdapterUtil.fix_config(caps, conf);

	}

	public void sendPacket(byte[] bytes) throws IOException {
		OutputStream outputStream = getOutputStream();
		outputStream.write(bytes);
	}

	public void processMessage(byte[] buf) {
		// ignore it if it is not a complete message

		String line = new String(buf, 0, mb_offset);
		if (line.length() > 20) {
			String identifier = line.substring(0, 10);

			// Ensure it is icon data
			log.debug("data={}", line);

			if (identifier.matches("[0-9]+-[0-9]+-[0-9]+")) {

				ICONResult block = new ICONResult(this);

				String[] dataArray = line.split("\t");
				if (dataArray != null && dataArray.length == 36) {

					try {
						block.setGender(dataArray[2]);
						block.setAGE(parseAge(dataArray[3]));
						block.setSV(parseValue(dataArray[7], 10));
						block.setHR(parseValue(dataArray[8], 1));
						// block.setSV(parseValue(dataArray[9]));
						block.setCO(parseValue(dataArray[10], 10));
						block.setTFC(parseValue(dataArray[11], 10));
						block.setICON(parseValue(dataArray[12], 100));
						block.setSTR(parseValue(dataArray[13], 10));
						block.setP14(parseValue(dataArray[14], 100));

						System.out.println(block);
					} catch (Exception e) {
						log.error("PARSE ERROR: {}", line);
					}
				}

				ConnectionStatus deviceState = this.getStatus();
				if (deviceState != CONNECTED) {
					setStatus(CONNECTED);
				}

				tick = 0;
				fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
			} else {
				Alarm block = new Alarm("??", Alarm.INFO, 0, line, true);
				fireStreamEvent(0, this, StreamID.ALARM, block);
				if (alarming == false) {
					alarming = true;
					fireNoData(conf);
				}

			}
		}
	}

	private Integer parseAge(String v) {
		Integer age = null;
		v = v.replace("y", "");
		try {
			age = Integer.parseInt(v);
		} catch (Exception e) {
			// ignore
		}
		return age;
	}

	private Integer parseValue(String s, int m) {
		Integer v = null;
		if (s == null || s.length() == 0 || s.startsWith("-")) {
			// ignore
		} else {
			try {
				int vv = (int) (Double.parseDouble(s) * m);
				v = vv;
			} catch (Exception e) {
				// leave as null
			}
		}
		return v;
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		log.info(" --> ICON on {}", portName);

		tick = 0;
		setStatus(NEGOTIATING);

		connect(portName, 115200, 8, 1, 0);

		sendStartupCommands();

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
				if (mb_offset > 20) {
					processMessage(mb_buffer);
				}
				mb_offset = 0;
			} else {
				mb_buffer[mb_offset++] = (byte) byt;
			}
		}
	}

	@Override
	public int tick() {
		tick++;
		OutputStream out = getOutputStream();
		int max_tick = (out == null) ? 120 : 80;

		// String portName = "<??>";
		// if (conf != null) {
		// portName = conf.getPort();
		// }

		if (out != null && (tick % 10) == 0) {
			System.out.println("icon_tick");
			try {
				out.write('\r');
				out.write('\n');
			} catch (IOException e) {
				// failure here is unexpected, but ok due to thread races and
				// unsynchronized access
			}
		}

		ConnectionStatus deviceState = getStatus();
		if (tick > max_tick) {
			if (deviceState == NOT_CONNECTED) {
				// ignore
			} else if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
				fireNoData(conf);
			}
			tick = max_tick;
		} else {
			if (deviceState != CONNECTED) {
				setStatus(ConnectionStatus.CONNECTED);
			}
		}
		return 0;

	}

}
