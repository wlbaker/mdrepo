package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.Map;

import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.dev.PlumA3Measurement;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PlumADataportDriver extends SerialAdapter {

	private static final String driverName = "pump/Hospira Plum-A+ Dataport";

	private int mb_offset = 0;
	private byte[] mb_buffer = new byte[256];

	private int tick = 99;
	private int connecting;
	private int curr_id;
	private int curr_pass;

	private static final byte CR = '\r';

	private String[] pump_sta = new String[4];
	private String[] last_alarm = new String[4];

	private static final Map<String, String> messageMap = new HashMap<String, String>();

	static {
		messageMap.put("AD1", "Air in line, Distal");
		messageMap.put("ADB", "Air in line, Distal (Bolus)");
		messageMap.put("ADC", "Air in line, Distal (Cumulative)");
		messageMap.put("AP1", "Air in line, Proximal");
		messageMap.put("APA", "Air in line, Proximal line A");
		messageMap.put("APB", "Air in line, Proximal line B");
		messageMap.put("APT", "Air in line, Proximal Total");
		messageMap.put("BDP", "Battery Depleted");
		messageMap.put("BPR", "BackPriming");
		messageMap.put("CHK", "Check settings, rate or VTBI not set.");
		messageMap.put("CS1", "Cassette Failure, Valve Failure");
		messageMap.put("DCO1", "Door, Cassette, Open, Door-Open");
		messageMap.put("DE1", "Dose End, Line 1");
		messageMap.put("DE2", "Dose End, Line 2");
		messageMap.put("DTL", "Control Dial turned when lockout switch is on.");
		messageMap.put("FDF", "Flow Detector, False (unplugged while pumping)");
		messageMap.put("FDT", "Flow Detector, True (plugged in while pumping)");
		messageMap.put("FLF", "Flow, False");
		messageMap.put("LCK", "LockOut Enabled");

		messageMap.put("LOV", "LockOut Violation");
		messageMap.put("MALxxx", "Malfunction");

		messageMap.put("NAA", "No Action Alarm");
		messageMap.put("NC1", "Nurse Call Back, line 1");
		messageMap.put("NC2", "Nurse Call Back, line 2");
		messageMap.put("OBP", "Proximal Occlusion on secondary");

		messageMap.put("OCP", "Proximal Occlusion");
		messageMap.put("OD1", "Occlusion, Distal");
		messageMap.put("OK", "No alarms");
		messageMap.put("OP1", "Occlusion, Proximal, line 1");
		messageMap.put("OP2", "Occlusion, Proximal, line 2");
		messageMap.put("PR1", "Pressure out of range");
		messageMap.put("RL", "Reset too Long or system Idle");

		messageMap.put("URC", "Unrecognizable Cassette");
		messageMap.put("VTB1", "Programmed VTBI completed in line 1.");
		messageMap.put("VTB2", "Programmed VTBI completed in line 2.");

	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(PlumADataportDriver.class);
	}

	/**
	 * 
	 */
	public PlumADataportDriver(DeviceConfiguration conf) {
		super(conf);
	}

	public void sendPacket(byte[] s) throws IOException {
		OutputStream outputStream = getOutputStream();
		outputStream.write(s);

		if (s.length > 22) {
			log.error("SEND PKT TOO LONG: " + new String(s));
		}

		int crc = CRCUtil.getCRC16X(0, s, 0, s.length);
		String s_crc = Integer.toHexString(crc).toUpperCase();
		while (s_crc.length() < 4) {
			s_crc = "0" + s_crc;
		}
		outputStream.write(s_crc.getBytes());
		outputStream.write(CR);

	}

	public void processMessage(byte[] buf) {
		// ignore it if it is not a complete message

		String line = new String(buf, 0, mb_offset);
		if (line.length() > 10) {
			String fromid = line.substring(0, 3);

			int pump_id = -1;
			if ("F1;".equals(fromid)) {
				pump_id = 1;
			} else if ("F2;".equals(fromid)) {
				pump_id = 2;
			} else if ("F3;".equals(fromid)) {
				pump_id = 3;
			}

			if (pump_id > 0 && pump_id <= 3) {

				PlumA3Measurement block = new PlumA3Measurement(this);

				String[] dataArray = line.split("[;]");
				IntfUtil.setValue(block, PlumA3Measurement.ID_NO, pump_id);
				if (dataArray == null) {
					// ignore
				} else if (dataArray.length == 5 || dataArray.length == 6) {
					// alarm info
					String alarm = dataArray[2];
					if (alarm == null) {
						if (last_alarm[pump_id] != null) {
							// alarm ending
							Alarm alr;
							alr = new Alarm("ALR", Alarm.CLEAR, 1, "[" + pump_id + "] ", true);
							fireAlarmEvent(this, alr);
						}

					} else if (!alarm.equals(last_alarm[pump_id])) {
						// alarm starting

						String alarmText = translateAlarm(alarm);
						Alarm alr;
						alr = new Alarm("ALR", Alarm.WARNING, 1, "[" + pump_id + "] " + alarmText, true);
						fireStreamEvent(0, this, StreamID.ALARM, alr);
					} else {
						// alarm and last_alarm are the same...ignore
					}

					tick = 0;
					last_alarm[pump_id] = alarm;

					log.debug("[{}] alarm: {}", fromid, alarm);
					String sta = dataArray[3];
					sta = sta.split(" ")[0];
					pump_sta[pump_id] = sta;
					// FIXME set_text_item(block, PlumA3DataBlock.STA, sta );
				} else if (dataArray.length == 7) {
					String rate = dataArray[2];
					if (rate.startsWith("R")) {
						rate = rate.substring(1);
					}
					set_numeric_item(block, PlumA3Measurement.RATE1aA, rate);
					set_numeric_item(block, PlumA3Measurement.VTBD1A, dataArray[3]);
					set_numeric_item(block, PlumA3Measurement.VTOT1A, dataArray[4]);
					if (pump_sta[pump_id] != null) {
						// text value
						IntfUtil.setValue(block, PlumA3Measurement.STA, pump_sta[pump_id]);
					}
					// text value
					IntfUtil.setValue(block, PlumA3Measurement.DRUGNAME, dataArray[5]);

					pump_sta[pump_id] = null;
					tick = 0;
					if (log.isDebugEnabled()) {
						String name = "BAD";
						if (conf != null) {
							name = conf.getName();
						}
						log.debug(name + " [{}] numerics: {}", fromid, block);
					}

					fireStreamEvent(0, this, StreamID.MEASUREMENT, block);

				} else {
					log.error("?? unknown message: {}", line);
				}
			} else {
				log.error("unknown pump id: {} line: {}", fromid, line);
			}
		} else {
			log.error("short pump message: {}", line);
		}
	}

	private String translateAlarm(String alarm) {

		if (alarm.startsWith("r") || alarm.startsWith("R")) {
			alarm = alarm.substring(1);
		}

		String val = messageMap.get(alarm);

		if (val == null) {
			val = alarm;
		}
		return val;
	}

	private void set_numeric_item(PlumA3Measurement block, String loc, String val) {

		// log.debug("parse: {} == {}", loc, val);

		if (val.startsWith("r")) {
			// device is sounding alarm
			val = val.substring(1);
		}

		try {
			double d = Double.parseDouble(val);
			int i_val = (int) d;
			IntfUtil.setValue(block, loc, i_val);
		} catch (NumberFormatException e) {
			log.warn("NF Exception: val={} for loc={}", val, loc);
			// e.printStackTrace();
		}
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");
		try {

			log.info(" --> plumA on {}", portName);
			curr_id = 1;
			tick = 99;
			setStatus(NEGOTIATING);

			connect(portName, 1200, 8, 1, 0);

			System.err.println("port.setDTR();");
			System.err.println("port.setRTS();");

		} catch (Exception e) {
			e.printStackTrace();
			throw new IOException(e);
		}

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		DeviceCapabilities caps = new DeviceCapabilities(PlumADataportDriver.class);
		caps.addStream(StreamID.MEASUREMENT, PlumA3Measurement.class);
		caps.setModels(new String[] { "Plum-A+" });
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
				if (mb_offset > 4) {
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

		if (out != null) {
			try {

				if (curr_pass == 0) {
					curr_id++;
					if (curr_id > 3) {
						curr_id = 1;
					}

					String m1 = "T@" + curr_id + ";IDV1;VT1;TV1;DN1;";
					// log.debug(m1);
					sendPacket(m1.getBytes());
					curr_pass = 1;
				} else {
					String m2 = "T@" + curr_id + ";IALR;STA;";
					// log.debug(m2);
					sendPacket(m2.getBytes());
					curr_pass = 0;

				}
			} catch (IOException e) {
				// failure here is unexpected, but ok due to thread races and
				// unsynchronized access
			}
		}

		ConnectionStatus deviceState = getStatus();
		if (tick > max_tick) {
			if (deviceState == NOT_CONNECTED) {
				// ignore
			} else if (deviceState == NEGOTIATING && connecting < max_tick) {
				// give it a chance before declaring not connected
				connecting++;
			} else if (deviceState != NOT_CONNECTED) {
				log.debug("firing disconnect event: {}", tick);
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

	private final static byte[] pluma_probe_bytes = "\rT@{IDX3};ISTA;2FAD\r".getBytes();
	
	// test the byte array to see if the data is recognized
	@Override
	public void probe(OutputStream out) throws IOException {
		out.write( pluma_probe_bytes );
		return;
	}
	
	public boolean test(byte[] arr) {
		return false;
	}


}
