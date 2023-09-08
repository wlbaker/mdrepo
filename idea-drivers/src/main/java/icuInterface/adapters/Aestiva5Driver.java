package icuInterface.adapters;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Date;
import java.util.List;

import com.fazecast.jSerialComm.SerialPort;
import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.DriftRectifier;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.dev.AestivaMeasurement;
import idea.model.dev.AestivaWaveform;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class Aestiva5Driver extends SerialAdapter implements AdapterInterface {
	private static final String driverName = "anesthesia/Datex Ohmeda Aestiva 5*";

	public final static byte ESC = 0x1b;

	private final static byte[] disableChecksum = { 'V', 'T', 'D' };
	private final static byte[] enableChecksum = { 'V', 'T', 'E' };
	private final static byte[] enableCompression = { 'V', 'T', 'Q' };
	private final static byte[] slaveMode = { 'V', 'T', 'S' };
	private final static byte[] autoMode = { 'V', 'T', 'X' };
	private final static byte[] sendSetupData = { 'V', 'T', '$' };
	private final static byte[] sendAllData = { 'V', 'T', '?' };
	private final static byte[] enableWaveformData = { 'V', 'T', 'W' };

	private final static byte[] measuredDataResponse = { 'V', 'T', 'D' };
	private final static byte[] setupDataResponse = { 'V', 'T', 'M' };
	private final static byte[] NACK = { 'V', 'T', 'N' };
	private final static byte[] statusDataResponse = { 'V', 'T', 'Q' };
	private final static byte[] waveformDataResponse = { 'V', 'T', 'W' };
	private final static byte[] alarmSilenceResponse = { 'V', 'T', 'R' };
	private final static byte[] ACK = { 'V', 'T', 'Y' };

	private static byte[] initPacket;

	static {
		initPacket = new byte[16];
		buildPacket(initPacket, autoMode);
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(Aestiva5Driver.class);
	}

	private static void buildPacket(byte[] initPacket2, byte[] automode2) {
		// TODO Auto-generated method stub

	}

	int[][] waveform_packet = new int[3][]; // packets are of varying

	private static DeviceCapabilities cap;
	private byte[] mb_buffer = new byte[2048];
	private int mb_offset = 0;

	private static RpMetric[] wave_desc; // ecg_desc;
	RpMetric hr_desc;

	private AestivaWaveform waveform_block;
	private DriftRectifier drifter;
	byte channelRequest = 0;

	private int tick;

	static {

		cap = new DeviceCapabilities(Aestiva5Driver.class);

		wave_desc = new RpMetric[3];

		cap.addStream(StreamID.WAVEFORM, AestivaWaveform.class);
		cap.addStream(StreamID.MEASUREMENT, AestivaMeasurement.class);

		cap.addConnection(
				new SerialConnection(19200, 8, 1, SerialPort.NO_PARITY));
	}

	public Aestiva5Driver(RpDevice conf) {
		super(conf);

		this.conf = conf;

		waveform_packet[0] = new int[AestivaWaveform.WF_PKT_SIZE];
		waveform_packet[1] = new int[AestivaWaveform.WF_PKT_SIZE];
		waveform_packet[2] = new int[AestivaWaveform.WF_PKT_SIZE];

		waveform_block = new AestivaWaveform();

		channelRequest = 0;

		if (conf != null) {
			List<? extends RpMetric> wfs = RpUtil.getMetrics(conf, StreamID.WAVEFORM);
			if (wfs != null) {
				for (RpMetric d : wfs) {
					String loc = d.getLocation();
					String hex = loc.substring(2);
					int mask = Integer.parseInt(hex, 16);
					channelRequest |= mask; // ECG lead 1 + ECG lead 2?

				}
			}
		}

	}

	@Override
	public void connect() throws IOException {

		drifter = new DriftRectifier(500, 100, 30);

		String portName = RpUtil.getParam(conf, "port");

		setStatus(ConnectionStatus.NEGOTIATING);

		connect(portName, 19200, 8, 1, 0);

		sendPacket(initPacket, 0, initPacket.length);

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
			process(byt);
		}
	}

	public void process(int byt) {

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

		mb_buffer[mb_offset++] = (byte) byt;

		int len = mb_buffer[0];
		if (mb_offset == 2) {
			int len_inv = mb_buffer[1];
			if (len_inv < 0)
				len_inv += 256; // there is no unsigned type in
			// java...hm

			if ((len + len_inv) != 0xff) {
				// invalid packet
				System.err.println("invalid packet! " + len + " not complemented by " + len_inv + " dropping byte");

				mb_buffer[0] = mb_buffer[1];
				mb_offset = 1;
			}
		}

		if (mb_offset > 3 && mb_offset >= len + 4 && processPacket(mb_buffer, mb_offset)) {
			for (int i = 0; i < mb_buffer.length; i++) {
				mb_buffer[i] = -1;
			}
			mb_offset = 0;
		}

		if (mb_offset > mb_buffer.length - 10) {
			mb_offset = 0;
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

		switch (cmdId) {
		default:

			System.out.println("unknown command: " + cmdId);

			dumpPacket(valuesRead, l);

			break;
		}
		return true;
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
				break;
			case 2:
			case 3:
				break;
			case 4:
				break;
			case 5:
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

		waveform_block.setTm(new Date(tm));

		this.fireStreamEvent(0, this, StreamID.WAVEFORM, waveform_block);

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

	private void sendPacket(byte[] message, int off, int len) throws IOException {
		OutputStream out = getOutputStream();

		if (out == null) {
			log.error("OUTPUT PORT NOT INITIALIZED");
			return;
		}
		out.write(message, off, len);
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (tick > 6) {
				try {
					sendPacket(initPacket, 0, initPacket.length);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				tick = 4;
			}
			if (deviceState != ConnectionStatus.NOT_CONNECTED) {
				setStatus(ConnectionStatus.NOT_CONNECTED);
			}
		} else {
			if (deviceState != ConnectionStatus.CONNECTED) {
				setStatus(ConnectionStatus.CONNECTED);
			}
		}

		return 0;
	}

}
