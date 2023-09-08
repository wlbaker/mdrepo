package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.dev.PolestarMeasurement;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

// INIT
//     \022
//     4\0\0\36\270?\205\353\205A\271
//     \365\303@\250\0\0
//     B4f\303=\200\234\340\300\267\0\5\0<\0?\0
//     0\0\0\0\0
// INIT  (line 320)
//
// The first handheld TransC02 Sensor is on its way back to you with version 3.4 software in it. It now sends out CO2 measurements on the serial port when it is in the RUN state. The particulars of the transfer are as follows:
//
// The command consists of 8 bytes:
//
// Cmd[0] = 'S'(0x53)
// Cmd[1] = 0x8F(indicates CO2 measurement)
// Cmd[2] = LSB of CO2(float)
// Cmd[3] = Mid of CO2(float)
// Cmd[4] = Mid of CO2(float)
// Cmd[5] = MSB of CO2(float)
// Cmd[6] = Exclusive Or of 
//
// Cmd[1] through Cmd[5] inclusive Cmd[7] = 'E'(0x45)
//
// This will not be the only command on the serial port.
//
// If you have any questions, please feel free to contact me.
//
// Al Votolato
//

@Slf4j
public class PoleStarDriver extends SerialAdapter {

	private static final String driverName = "misc/PoleStar TransQ";

	private static final int CMD_PACKET_LEN = 7;
	private static DeviceCapabilities caps;
	private int mb_offset = -1;
	private byte[] mb_buffer = new byte[64];

	private int tick = 5;

	static {
		caps = new DeviceCapabilities(PoleStarDriver.class);

		caps.addStream(StreamID.MEASUREMENT, PolestarMeasurement.class);

		caps.setModels(new String[] { "PT01" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(PoleStarDriver.class);
		conf.addStream(caps.getStream(StreamID.MEASUREMENT));
		conf.setModelName("PoleStar");
		return conf;
	}

	/**
	 * 
	 */
	public PoleStarDriver(RpDevice conf) {
		super(conf);

		AdapterUtil.fix_config(caps, conf);
	}

	public void sendPacket(byte[] bytes) throws IOException {
		OutputStream outputStream = getOutputStream();
		outputStream.write(bytes);
	}

	public void processMessage(byte[] buf) {
		// ignore it if it is not a complete message

		ByteBuffer bb = ByteBuffer.wrap(buf, 0, mb_offset);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		int s = bb.get();
		int cmd = bb.get();
		float co2 = bb.getFloat();
		int xor = bb.get();

		if (cmd < 0) {
			cmd += 256;
		}

		if (cmd == 0x8f) {
			PolestarMeasurement block = new PolestarMeasurement();

			block.setRed(0);
			block.setGreen(0);
			block.setBlue(0);
			block.setInfr(0);
			block.setTemp(0);
			block.setCo2((int) (100 * co2));

			System.out.println("co2=" + co2);

			ConnectionStatus deviceState = this.getStatus();
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}

			tick = 0;
			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
		}
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		log.info(" --> polestar on {}", portName);

		tick = 0;
		setStatus(NEGOTIATING);

		connect(portName, 9600, 8, 1, 0);

		System.err.println("port.setDTR();");
		System.err.println("port.setRTS();");

		initDataFlow();

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {

		while (in.available() > 0) {
			int byt = in.read();

			if (byt < 0)
				break;

			if (mb_offset == -1) {
				if (byt == 'S') {
					mb_offset = 0;
				}
			} else if (mb_offset == CMD_PACKET_LEN) {
				processMessage(mb_buffer);
				mb_offset = -1;
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

		ConnectionStatus deviceState = getStatus();
		if (tick > max_tick) {
			try {
				initDataFlow();
			} catch (IOException e) {
				e.printStackTrace();
			}

			if (deviceState == NOT_CONNECTED) {
				// ignore
			} else if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
				fireNoData(conf);
			}
			tick = max_tick - 5;
		} else {
			if (tick < 5 && deviceState != CONNECTED) {
				setStatus(ConnectionStatus.CONNECTED);
			}
		}

		return 0;
	}

	private void initDataFlow() throws IOException {
		OutputStream sout = getOutputStream();
		if (sout != null) {
			byte[] arr = new byte[] { 'S', (byte) 0xab, 0, 0, 0, 0, (byte) 0xab, 'E' };
			sout.write(arr);

			System.out.print(" --> start: ");
			dump(System.out, arr, arr.length);
		}

	}

	public static void dump(PrintStream out, byte[] array, int len) {
		out.print("  ");
		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 16 == 0)) {
				out.println();
				out.print("  ");
			}

			int byt = array[i];
			if (byt < 0)
				byt += 256;
			if (byt < 16) {
				out.print("0");
			}
			out.print(Integer.toHexString(byt));
			out.print(" ");
		}

		out.println();

	}

}
