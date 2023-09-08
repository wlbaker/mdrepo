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
import idea.conf.DeviceConfiguration;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.dev.KangarooResult;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class KangarooDriver extends SerialAdapter {

	@SuppressWarnings("unused")
	private static final String driverName = "misc/Covidien Kangaroo ePump";

	private static DeviceCapabilities caps;
	private int mb_offset = 0;
	private byte[] mb_buffer = new byte[256];

	private int tick;
	private int verbose = 0;
	private boolean alarming;

	static {
		caps = new DeviceCapabilities(KangarooDriver.class);

		caps.addStream(StreamID.MEASUREMENT, KangarooResult.class);
		caps.setModels(new String[] { "ePump" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(KangarooDriver.class);
		conf.addStream(StreamID.MEASUREMENT, KangarooResult.class);
		conf.setModelName("ePump");
		return conf;
	}

	/**
	 * 
	 */
	public KangarooDriver(DeviceConfiguration conf) {
		super(conf);

		fix_config(conf);
	}

	private void fix_config(DeviceConfiguration conf) {
		if (conf != null) {
			conf.setModelName("ePump");

			DeviceCapabilities caps = getStaticCapabilities();
			AdapterUtil.fix_config(caps, conf);
		}
	}

	public void sendPacket(byte[] bytes) throws IOException {
		OutputStream outputStream = getOutputStream();
		outputStream.write(bytes);
	}

	public void processMessage(byte[] buf) {
		// ignore it if it is not a complete message

		String line = new String(buf, 0, mb_offset);
		if (line.length() > 20) {
			String identifier = line.substring(0, 8);

			// Ensure it is kangaroo epump data
			log.debug("data={}", line);

			if (identifier.equals("ePumpSTS")) {

				String pumpStatus = "<UNKNOWN>";
				KangarooResult block = new KangarooResult(this);

				String[] dataArray = line.split("\\|");
				if (dataArray != null && dataArray.length > 12) {
					pumpStatus = dataArray[4];

					try {
						block.setSerNo(dataArray[1]);
						block.setPumpStatus(Integer.parseInt(dataArray[4]));
						block.setFlushTotal(Integer.parseInt(dataArray[5]));
						block.setFlushVTBD(Integer.parseInt(dataArray[6]));
						block.setFlushIVL(Integer.parseInt(dataArray[7]));
						block.setFeedTotal(Integer.parseInt(dataArray[8]));
						block.setFeedRate(Integer.parseInt(dataArray[9]));
						block.setFeedVTBD(Integer.parseInt(dataArray[10]));
						block.setFeedRemaining(Integer.parseInt(dataArray[11]));
						block.setNumBolus(Integer.parseInt(dataArray[12]));
					} catch (Exception e) {
						log.error("PARSE ERROR: {}", line);
					}
				}

				ConnectionStatus deviceState = this.getStatus();
				if (deviceState != CONNECTED) {
					setStatus(CONNECTED);
				}

				tick = 0;
				if (alarming) {
					alarming = false; // clear the alarm

					Alarm alarm = new Alarm(pumpStatus, Alarm.INFO, 0, "Clear", false);
					fireAlarmEvent(this, alarm);
				}
				fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
			} else if (identifier.equals("ePumpERR")) {
				// ePumpERR|00095FE2|0004|0008|0081|0096|00|53||0|0000|000002BB|0028|0000|0000|0000|2B||
				tick = 0;
				// log.warn("ePumpERR: {}", line);
				String[] dataArray = line.split("\\|");
				Alarm block;
				if (dataArray != null && dataArray.length > 6) {
					String pumpStatus = dataArray[4];
					String errorCode = dataArray[5];
					String sysCode = dataArray[6];
					int i_errorCode = 999;

					String errorMessage = line;
					try {
						i_errorCode = Integer.parseInt(errorCode, 16);
						int i_sysCode = Integer.parseInt(sysCode, 16);
						if (i_sysCode != 0) {
							i_errorCode = i_sysCode;
							errorMessage = "SYS CODE: " + i_sysCode;
						} else {
							switch (i_errorCode) {
							case 102:
								errorMessage = "System Error";
								break;
							case 106:
								errorMessage = "Pump Set Dislodged";
								break;
							case 150:
								errorMessage = "Battery Low";
								break;
							case 120:
								errorMessage = "Feed Error";
								break;
							case 121:
								errorMessage = "Flush Error";
								break;
							case 122:
								errorMessage = "Flow Error";
								break;
							case 101:
								errorMessage = "Hold Error";
								break;
							case 111:
								errorMessage = "Rotor Error";
								break;
							default:
								errorMessage = "Error CODE: " + i_errorCode;
								break;
							}

						}

					} catch (Exception e) {
						// parse exception
					}
					block = new Alarm(pumpStatus, Alarm.WARNING, i_errorCode, errorMessage, true);
				} else {
					block = new Alarm("??", Alarm.INFO, 0, line, true);
				}
				fireAlarmEvent(this, block);
				if (alarming == false) {
					alarming = true;
					fireNoData(conf);
				}

			}
		}
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");
		try {

			log.info(" --> kangaroo on {}", portName);

			tick = 0;
			setStatus(NEGOTIATING);

			connect(portName, 9600, 8, 1, 0);

			//?? port.setDTR();
			//?? port.setRTS();

			sendStartupCommands();
		} catch (Exception e) {
			e.printStackTrace();
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
		int max_tick = (out == null) ? 60 : 12;

		// String portName = "<??>";
		// if (conf != null) {
		// portName = conf.getPort();
		// }

		if (out != null) {
			try {
				out.write('x');
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

	// test the byte array to see if the data is recognized
	@Override
	public void probe(OutputStream out) throws IOException {
		out.write('x' );
		return;
	}
	
	public boolean test(byte[] arr) {
		return false;
	}

}
