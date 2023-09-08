package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Timer;
import java.util.TimerTask;

import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.DriftRectifier;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.adapters.propaq.PropaqID;
import icuInterface.adapters.propaq.PropaqPacket;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.dev.Propaq_Measurement;
import idea.model.dev.Propaq_Waveform;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PropaqDriver extends SerialAdapter implements AdapterInterface {

	private static final String driverName = "monitor/Welch Allen Propaq 20x Series";

	private final static int zeroOffset = 2000;

	int[][] waveform_packet = new int[8][]; // packets are of varying

	// lengths...maybe

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(PropaqDriver.class);
	}

	private DeviceCapabilities cap;
	private byte[] mb_buffer = new byte[2048];
	private int mb_offset = 0;

	RpMetric hr_desc;

	private Timer restartTimer;

	private int commTimeout;

	private Propaq_Waveform waveform_block;
	private DriftRectifier drifter;
	byte channelRequest = 0;

	private int tick;

	public PropaqDriver(RpDevice conf) {

		super(conf);

		RpUnit mmHg = new RpLinearUnit(1.0, 0, "mmHg");
		cap = new DeviceCapabilities(PropaqDriver.class);

		cap.addStream(StreamID.WAVEFORM, Propaq_Waveform.class);
		cap.addStream(StreamID.MEASUREMENT, Propaq_Measurement.class);

		cap.setModels(new String[] { "Propaq CS" });

		waveform_block = new Propaq_Waveform();

	}

	@Override
	public void connect() throws IOException {

		drifter = new DriftRectifier(500, 100, 30);

		String portName = RpUtil.getParam(conf, "port");
		connect(portName, 19200, 8, 1, 0);

		setStatus(NOT_CONNECTED);
		initRequestFlags();
		initDataFlow();

	}

	private void initRequestFlags() {
		channelRequest = 0;

		log.error("FIXME: init request flags");
		/*
		 * if (conf != null) { WaveformDescription[] wfs = conf.getWaveforms();
		 * for (WaveformDescription d : wfs) { String loc = d.getLocation();
		 * String hex = loc.substring(2); int mask = Integer.parseInt(hex, 16);
		 * channelRequest |= mask; // ECG lead 1 + ECG lead 2? } }
		 * 
		 * int mask = 1; for (int idx = 0; idx < 8; idx++) {
		 * 
		 * if ((mask & channelRequest) != 0) {
		 * wf.setValues(waveform_packet[idx]); waveform_block.add(wf); } mask
		 * <<= 1; }
		 */

	}

	@Override
	public void disconnect() throws IOException {
		restartTimer.cancel();
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
	public void process(InputStream in, OutputStream out) throws IOException {
		// If we get here then data has been received
		try {

			System.out.print(" recv: ");
			while (in.available() > 0) {
				int byt = in.read();

				if (mb_offset < 8) {
					System.out.print(" ");
					char ch = (char) byt;
					if (ch >= 32 && ch < 127) {
						System.out.print(ch);
					}
					System.out.print("[");
					System.out.print(Integer.toHexString(byt));
					System.out.print("]");
				} else if (mb_offset == 8) {
					System.out.println(" ...");
				}

				if (byt == -1) {
					break;
				}

				mb_buffer[mb_offset++] = (byte) byt;

				int len = mb_buffer[0];
				if (mb_offset == 2) {
					int len_inv = mb_buffer[1];
					if (len_inv < 0)
						len_inv += 256; // there is no unsigned type in
					// java...hm

					if ((len + len_inv) != 0xff) {
						// invalid packet
						System.err.println(
								"invalid packet! " + len + " not complemented by " + len_inv + " dropping byte");

						mb_buffer[0] = mb_buffer[1];
						mb_offset = 1;
					}
				}

				if (mb_offset > 3 && mb_offset >= len + 4 && processPacket(mb_buffer, mb_offset)) {
					for (int i = 0; i < mb_buffer.length; i++) {
						mb_buffer[i] = -1;
					}
					mb_offset = 0;
					System.out.println("   processed");
				}

				if (mb_offset > mb_buffer.length - 10) {
					mb_offset = 0;
					System.out.println("   overflow");
				}
			}

		} catch (Exception e) {
			// No more lines
			dumpPacket(mb_buffer, mb_offset);
			e.printStackTrace();
			System.out.println("Exception in serial reader???");
		}

	}

	private boolean processPacket(byte[] valuesRead, int l) {
		// PropaqPacket pkt 3 = new PropaqPacket(valuesRead);
		int len = valuesRead[0];
		valuesRead[l] = (byte) 0xff;
		valuesRead[l + 1] = (byte) 0xff;

		// last two bytes are CRC...if you include the CRC in the calculation
		// itself, your resulting CRC
		// will always be 0. Curious property of the CRC.

		int crc = CRCUtil.getCRC16(valuesRead, 2, len + 4);
		if (crc != 0) {
			int crc1 = valuesRead[len + 2]; // checksum is after the last data
			// byte
			int crc2 = valuesRead[len + 3]; // checksum is after the last data
			// byte

			if (crc1 < 0)
				crc1 += 256;
			if (crc2 < 0)
				crc2 += 256;

			System.err.println("CRC=" + Integer.toHexString(crc) + " crc=" + Integer.toHexString(crc1) + "."
					+ Integer.toHexString(crc2));

			return true; // data error...discard packet
		}

		int cmdId = valuesRead[2];

		commTimeout = 5;

		switch (cmdId) {
		case PropaqPacket.ControlResponse:
			if (getStatus() == NOT_CONNECTED) {
				setStatus(NEGOTIATING); // transition from connecting to ONLINE
				// commTimeout = 0;
			}
			break;
		case PropaqPacket.WaveformResponse:

			Alarm alarm = new Alarm("propq", Alarm.WARNING, 99, "Waveform request exceeds bandwidth", true);
			fireStreamEvent(0, this, StreamID.ALARM, alarm);
			// state = PropaqState.READY;
			break;

		case PropaqPacket.SystemResponse:
			// systemResponse = true;
			break;
		case PropaqPacket.AlarmLimitResponse:
			break;
		case PropaqPacket.SensorResponse:
			break;
		case PropaqPacket.NumericResponse:
			break;
		case PropaqPacket.AutoNumeric:

			processAutoNumericPacket(valuesRead, // data read
					4, // start pos
					len - 2 // packet type, seq_no
			);

			commTimeout = 5;

			break;
		case PropaqPacket.AutoWaveform:

			// can be used to detect missing packets...
			// but I wouldn't know what to do if I did detect a missed packet.
			//
			// well...for one thing...that would invalidate the RRI interval
			// calculations
			//
			byte seqNo = valuesRead[3];

			try {
				synchronized (waveform_block) {
					processWaveformPacket(valuesRead, // data read
							4, // start pos
							len - 2 // packet type, seq_no
					);
				}
			} catch (Exception e) {
				e.printStackTrace();
				System.err.println("how dis be here?");
			}

			commTimeout = 5;
			break;
		case PropaqPacket.TrendResponse:
			break;
		case PropaqPacket.ChannelResponse:
			break;
		case PropaqPacket.AutoAlarmLimit:
			//
			// I am getting these messages and ignoring them
			//
			// System.out.println("<got autoAlarmLimit>");
			break;
		case PropaqPacket.AutoSensor:
			//
			// I am getting these messages and ignoring them
			//
			// System.out.println("<got autoSensor>");
			break;
		case PropaqPacket.AutoSystem:
			//
			// I am getting these messages and ignoring them
			//
			// System.out.println("<got autoSystem>");
			break;
		case PropaqPacket.AutoTrend:
			System.out.println("<got autoTrend>");
			break;
		case PropaqPacket.AutoChannel:
			//
			// I am getting these messages and ignoring them
			//
			// System.out.println("<got autoChannel>");
			break;
		default:

			System.out.println("unknown command: " + cmdId);

			dumpPacket(valuesRead, l);

			break;
		}
		return true;
	}

	private void processAutoNumericPacket(byte[] valuesRead, int i, int dataLen) {
		int hr = ((valuesRead[7] << 8) & 0x000000ff) | (valuesRead[6] & 0x000000ff);
		int sbp = ((valuesRead[11] << 8) & 0x000000ff) | (valuesRead[10] & 0x000000ff);
		int dbp = ((valuesRead[15] << 8) & 0x000000ff) | (valuesRead[14] & 0x000000ff);
		int map = ((valuesRead[19] << 8) & 0x000000ff) | (valuesRead[18] & 0x000000ff);
		int pp = sbp - dbp;

		double si = 0;
		if (sbp != 0) {
			si = ((double) hr) / sbp;
		}

		Propaq_Measurement block = new Propaq_Measurement();

		block.setHr(hr);

		fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
		tick = 0;
	}

	private void processWaveformPacket(byte[] valuesRead, int start, int len) {

		boolean invalid = false;

		int wave_id = -1;

		// dumpPacket(valuesRead, len + 4);

		for (int src_idx = start; src_idx < start + len; src_idx++) {
			int h = valuesRead[src_idx];
			if (h < 0) {
				h += 256;
			}
			invalid = (0x80 & h) == 0x80;

			if (invalid) {
				continue;
			}

			wave_id = (h & 0x0f) - 1; // lower nibble has the wave id

			int dest_idx = 0;

			switch (wave_id) {
			case 0:
			case 1:
				if ((h & 0x40) != 0) {
					dest_idx = 8;
				}
				read_words(valuesRead, src_idx + 1, waveform_packet[wave_id], dest_idx, 8);
				src_idx += 16;
				break;
			case 2:
			case 3:
				if ((h & 0x40) != 0) {
					dest_idx = 4;
				}
				read_compressed_words(valuesRead, src_idx + 1, waveform_packet[wave_id], dest_idx, 4);
				src_idx += 6;
				break;
			case 4:
				if ((h & 0x40) != 0) {
					dest_idx = 3;
				}
				read_bytes(valuesRead, src_idx + 1, waveform_packet[wave_id], dest_idx, 3);
				src_idx += 3;
				break;
			case 5:
				if ((h & 0x40) != 0) {
					dest_idx = 4;
				}
				read_compressed_words(valuesRead, src_idx + 1, waveform_packet[wave_id], dest_idx, 4);
				src_idx += 8; // skip two bytes of amplitude data
				break;
			default:
				System.err.println("dont know how to handle waveform: " + wave_id);
				break;
			}

			// System.out.println(" wv header=0x" + Integer.toHexString(h) +
			// " invalid=" + invalid + " wave_id=" + wave_id
			// + " (i)=" + src_idx ) ;
		}

		long tm = drifter.getRectifiedTime(PlatformUtil.currentTimeMillis());
		drifter.setNextExpectedTime(tm + 90);

		waveform_block.setTime(tm);

		fireStreamEvent(0, this, StreamID.WAVEFORM, waveform_block);
		tick = 0;

	}

	private void read_bytes(byte[] valuesRead, int src_idx, int[] dest, int dest_idx, int count) {

		while (count > 0) {
			int v = valuesRead[src_idx++];
			if (v < 0) {
				v += 256;
			}

			dest[dest_idx++] = v;
			count--;
		}
	}

	private void read_compressed_words(byte[] valuesRead, int src_idx, int[] dest, int dest_idx, int count) {
		while (count > 0) {
			int lsb1 = valuesRead[src_idx++];
			int msb = valuesRead[src_idx++];
			int lsb2 = valuesRead[src_idx++];

			if (lsb1 < 0) {
				lsb1 += 256;
			}
			if (msb < 0) {
				msb += 256;
			}
			if (lsb2 < 0) {
				lsb2 += 256;
			}

			int v1 = (256 * (msb >> 4)) + lsb1;
			int v2 = (256 * (msb & 0x0f)) + lsb2;

			dest[dest_idx++] = 0x7f & v1; // clip off the pulse detect
			dest[dest_idx++] = 0x7f & v2; // clip off the pulse detect

			count -= 2; // count must be even
		}

	}

	private void read_words(byte[] valuesRead, int src_idx, int[] dest, int dest_idx, int count) {
		while (count > 0) {
			int b1 = valuesRead[src_idx++];
			if (b1 < 0) {
				b1 += 256;
			}

			int v = b1;
			int b2 = valuesRead[src_idx++];

			if (b2 < 0) {
				b2 += 256;
			}
			b2 &= 0x0f;
			v = (b2 << 8) | b1;
			v = v - zeroOffset;

			dest[dest_idx++] = v;

			count--;
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

					dumpPacket(mb_buffer, mb_offset);
					setStatus(NOT_CONNECTED);
					e.printStackTrace();
				}
			}

		};

		restartTimer.schedule(task, 500, 500);
	}

	public void timerPulse() throws IOException {

		ConnectionStatus state = getStatus();
		
		OutputStream out = getOutputStream();
		// System.out.println(" state=" + state + " cto=" + commTimeout);
		if (state == NOT_CONNECTED && commTimeout == 0) {
			out.write(PropaqPacket.initPacket, 0, PropaqPacket.initPacket.length);
			commTimeout = 5;
			System.out.println("[PropaqDriver] sent init request");
		} else if (state == NOT_CONNECTED) {
			commTimeout--;
			if (commTimeout <= 0) {
				setStatus(NOT_CONNECTED);
				commTimeout = 0;
			}
		} else if (state == NEGOTIATING) {

			// ECG

			byte[] autoTransferWaveform = { PropaqPacket.WaveformCommand, PropaqID.WaveformTransfer1, channelRequest };
			byte[] autoStream = PropaqPacket.packetStream(autoTransferWaveform);
			out.write(autoStream, 0, autoStream.length);

			// this command starts numerics and alarms auto-transfer
			// byte[] autoStream =
			// PropaqPacket.packetStream(PropaqPacket.autoTransferOn);

			setStatus(CONNECTED);
			System.out.println("<sent autostream request>");

			commTimeout = 5;
		} else if (state == CONNECTED) {

			if (commTimeout == 0) {
				setStatus(NOT_CONNECTED);
			} else {
				byte[] keepAliveAuto = PropaqPacket.packetStream(PropaqPacket.keepAliveAuto);

				out.write(keepAliveAuto, 0, keepAliveAuto.length);
				commTimeout--;
			}
		} else {
			// assert( false ) : "Invalid state, not handled!";
		}

	}

	private void dumpPacket(byte[] buf, int len) {

		for (int i = 0; i < len; ++i) {
			int v = buf[i];
			if (v < 0) {
				v += 256;
			}

			System.out.format(" [%2.2s]", Integer.toHexString(v));
			if (i % 10 == 0) {
				System.out.println();
			}
		}
		System.out.println();

		if (len > 100) {
			System.err.println("how dis be?");
		}
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(ConnectionStatus.CONNECTED);
			}
		}
		return 0;
	}

}
