package idea.driver;

import static icuInterface.LoggingUtil.dumpConfiguration;
import static icuInterface.LoggingUtil.getLoggingOutputStream;
import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.LoggingUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.IntellivueConnection;
import idea.connections.SerialConnection;
import idea.driver.intellivue.IntellivueDriver;
import idea.intf.SerialAdapter;
import idea.intf.StreamConsumer;
import idea.message.StreamID;
import idea.schema.rp.RpDevice;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;

import com.fazecast.jSerialComm.SerialPort;

import lombok.extern.slf4j.Slf4j;

@Slf4j
class IntellivueSerialProxy extends IntellivueDriver {
	private static final String driverName="monitor/Philips Intellivue Serial";

	private static final int BOF = 0xc0;
	private static final int EOF = 0xc1;
	private static final int PHILIPS_ESCAPE_CHAR = 0x7d;
	private static final byte PROTOCOL_ID = 0x11;
	private static final byte MESSAGE_TYPE = 0x01;

	private final static int MAX_SERIAL_MTU = 1364;
	private final static int MIN_MPLX_WAVE_MTU = 700;
	private int mtu = MAX_SERIAL_MTU; // this value is [potentially?] negociated

	int pos = 0;
	byte[] user_data = new byte[2 * mtu]; // packet
	boolean escaping = false;
	private SerialPort port;

	public IntellivueSerialProxy(RpDevice conf) {
		super(conf);
		initCaps();
	}

	private void initCaps() {
		DeviceCapabilities caps = getStaticCapabilities();
		caps.addConnection( new SerialConnection(19200, 8, 1, 0 ) );  // 24-feb-16: not sure about this config
		caps.setModels( new String [] { "MP5", "MP70"} );
	}
	

	@Override
	protected void send(ByteBuffer req) throws IOException {
		ByteBuffer sendable = ByteBuffer.wrap(user_data);

		ByteBuffer header = ByteBuffer.allocate(4);
		header.put(PROTOCOL_ID);
		header.put(MESSAGE_TYPE);
		header.putShort((short) req.remaining());
		header.rewind();

		// log.info("remaining=", Integer.toHexString(req.remaining()));

		int crc = 0xffff;
		crc = CRCUtil.getCRC16(header.array(), 0, header.remaining());
		crc = CRCUtil.getCRC16X(crc, req.array(), req.position(), req.remaining());

		sendable.put((byte) BOF);
		append(sendable, header);
		append(sendable, req);
		crc = finalizeCrc(crc);
		ByteBuffer bb_crc = ByteBuffer.allocate(2);
		bb_crc.putShort((short) crc);
		bb_crc.rewind();

		append(sendable, bb_crc);
		sendable.put((byte) EOF);
		sendable.limit(sendable.position());
		sendable.rewind();

		OutputStream out = port.getOutputStream();
		out.write(sendable.array(), sendable.position(), sendable.remaining());
	}

	private void append(ByteBuffer sendable, ByteBuffer req) {
		while (req.remaining() > 0) {
			int b = req.get();
			if (b < 0) {
				b += 256;
			}
			if (b == PHILIPS_ESCAPE_CHAR || b == BOF || b == EOF) {
				sendable.put((byte) PHILIPS_ESCAPE_CHAR);
				b = b ^ 0x20;
			}
			sendable.put((byte) b);
		}

	}

	private static int finalizeCrc(int crc) {
		int onescomp = 0xffff - crc;
		int b1 = onescomp & 0x00ff;
		int b2 = (onescomp & 0xff00) >> 8;

		return (b1 << 8) | b2;
	}

	private static int getShort(byte[] user_data, int pos) {
		int b1 = user_data[pos];
		int b2 = user_data[pos + 1];
		if (b1 < 0) {
			b1 += 256;
		}
		if (b2 < 0) {
			b2 += 256;
		}
		int val = b1 << 8 | b2;
		return val;
	}

	public void process(int ch) {
		if (ch == BOF) {
			pos = 0;
		} else if (ch == EOF) {
			if (escaping) {
				log.warn("GOT COMM ABORT");
				return;
			}
			int protocol_id = user_data[0];
			int msg_type = user_data[1];
			int frame_len = user_data[3];
			if (frame_len < 0) { // correct sign on lowest byte
				frame_len += 256;
			}
			frame_len = 256 * user_data[2] + frame_len; // high byte must be lt
														// 128

			log.debug("received: pos={} frame_len={}", pos, frame_len);
			ByteBuffer bb = ByteBuffer.wrap(user_data, 0, pos);
			if( log.isDebugEnabled() ) {
				LoggingUtil.dump(bb);
			}

			if (protocol_id != 0x11) {
				log.error("** CHECK PROTOCOL_ID 0x11 !={}", protocol_id);
			} else if (msg_type != 0x01) {
				log.error("** CHECK MSG_TYPE 0x01 !={}", msg_type);
			} else {

				int crcCalc = CRCUtil.getCRC16(user_data, 0, pos - 2);
				crcCalc = finalizeCrc(crcCalc);
				int crcRef = getShort(user_data, pos - 2);

				if (frame_len != (pos - 6)) {
					log.error("dropping packet: frame length err.");
				} else if (crcCalc != crcRef) {
					log.error("dropping packet: CRC error: calc CRC={} received={}", Integer.toHexString(crcCalc),
							Integer.toHexString(crcRef));
				} else {
					try {
						// dump(user_data, pos);
						parsePacket(user_data, 4, frame_len);
					} catch (Exception e) {
						log.error("parsePacket", e);
					}
				}
			}

		} else if (ch == PHILIPS_ESCAPE_CHAR) {
			escaping = true;
		} else {
			if (escaping) {
				ch = ch ^ 0x20;
				escaping = false;

				// System.out.println("escaping");
				// dump( user_data , pos);
			}

			user_data[pos] = (byte) ch;
			pos++;
		}

	}


	public void setPort(SerialPort port) {
		this.port = port;
	}


	@Override
	public void connect() throws IOException {
		super.connect();
	}
}

@Slf4j
public class IntellivueSerialDriver extends SerialAdapter {

	private static final String driverName = "monitor/Philips Intellivue Serial (2)";
	private SerialDeviceConfiguration conf;

	int baud;

	private PrintStream dout;
	private IntellivueSerialProxy proxy;

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(IntellivueSerialDriver.class);
		conf.setName( driverName );
		return conf;
	}

	public IntellivueSerialDriver(DeviceConfiguration conf) {
		super(conf);
		this.conf = (SerialDeviceConfiguration) conf;

		this.dout = getLoggingOutputStream(this.getClass());
		if (dout != null) {
			dumpConfiguration(dout, this);
		}

		proxy = new IntellivueSerialProxy( this.conf );
	}

	@Override
	public void connect() throws IOException {
		try {
			proxy.connect();
			SerialDeviceConfiguration conf = (SerialDeviceConfiguration) super.getConfiguration();
			String portName = conf.getPort();

			//rxtx portId = CommPortIdentifier.getPortIdentifier(portName);
			//rxtx SerialPort port = (SerialPort) portId.open("IntellivueSerial", 2000);

			//rxtx port.notifyOnDataAvailable(true);
			//rxtx port.addEventListener(this);
			SerialPort port = SerialPort.getCommPort(portName);
			port.openPort();
			port.addDataListener(this);

			// baud = 0; -- auto
			// baud = 19200;
			setPort( port );
		} catch (Exception e) {
			log.error("connect", e);
			throw new IOException(e);
		}
	}


	
	@Override
	public void process(InputStream in, OutputStream os) {
		try {
			while (in.available() > 0) {

				int byt = in.read();
				proxy.process(byt);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			reset();
		}

	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	@Override
	public int tick() {
		return proxy.tick();

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return proxy.getStaticCapabilities();
	}

	@Override
	public void setPort(SerialPort port) {
		super.setPort(port);  //...maybe?
		
		baud = 115200;
		try {
			//rxtx port.setSerialPortParams(baud, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
			port.setBaudRate(baud);
			port.setNumDataBits( 8 );
			port.setNumStopBits( 1);
			port.setParity( SerialPort.NO_PARITY );
			proxy.setPort( port );
			proxy.requestAssociation();
		} catch( Exception e) {
			e.printStackTrace();
		}

	}

	/*
	 * METHOD 1: handling events
	 */
	@Override
	public void addStreamListener(StreamID sid, StreamConsumer l) {
		proxy.addStreamListener(sid, l);
	}


	@Override
	public void removeStreamListener(StreamConsumer eventListener) {
		proxy.removeStreamListener(eventListener);
	}

	@Override
	public ConnectionStatus getStatus() {
		return proxy.getStatus();
	}

	@Override
	public void requestCapabilities() throws IOException {
		proxy.requestCapabilities();
	}

	@Override
	public int getListeningEvents() {
		System.err.println("New routine with change from rxtx to jSerialComm...whatis it for?");
		return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
	}
	

}
