package icuInterface.adapters;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import ca.uhn.hl7v2.HL7Exception;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortEvent;
import icuInterface.adapters.HL7.HL7AbstractDriver;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.SerialConnection;
import idea.connections.TcpServerConnection;
import idea.message.StreamID;
import idea.model.dev.ICONResult;
import idea.model.dev.MindrayMeasurement;
import idea.model.dev.MindraySettings;
import idea.model.dev.OntonixMeasurement;
import idea.schema.rp.RpConnection;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ICON2SerialDriver extends HL7AbstractDriver  {
	private static final String driverName="cardiac/ICON Portable Monitor HL7";

	private static DeviceCapabilities caps;
	private final static byte SB = 0x0b;
	private final static byte EB = 0x1c;
	private final static byte CR = 0x0d;

	int mb_offset = 0;
	byte[] mb_buffer = new byte[8096];

	SerialDeviceConfiguration conf;

	SerialPort hw_port;

	static {
		caps = new DeviceCapabilities(ICON2SerialDriver.class);
		// caps.addStream(StreamID.SETTINGS, MindraySettings.class);
		caps.addStream(StreamID.MEASUREMENT, ICONResult.class);
		
		caps.setModels( new String[] { "ICON2" } );
		RpConnection [] conns = new RpConnection[] { 
				new SerialConnection(115200, 8, 1, 0),
				new SerialConnection(57600, 8, 1, 0)
				};
		
		caps.setConnections( conns );
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(ICON2SerialDriver.class);
		conf.setName("ICON2Serial");
		return conf;
	}

	public ICON2SerialDriver(DeviceConfiguration conf) {
		super(caps, conf);
		this.conf = (SerialDeviceConfiguration) conf;
	}

	@Override
	public void connect() throws IOException {
			String portName = conf.getPort();
			connect(portName, 115200, 8, 1, 0);

	}

	@Override
	public void disconnect() throws IOException {
		if (hw_port != null) {
		}

	}

	@Override
	public void serialEvent(SerialPortEvent event) {

		try {
			switch (event.getEventType()) {
			case SerialPort.LISTENING_EVENT_DATA_AVAILABLE: {
				SerialPort pp = (SerialPort) event.getSource();
				process(pp.getInputStream(), pp.getOutputStream());
			}
				break;
			default:
				log.warn("serialEvent unrecognized event: {}", event);
			}
		} catch (Exception e) {
			log.error("serialEvent", e);
		}

	}

	public void process(InputStream in, OutputStream out) throws IOException {

		while (in.available() > 0) {
			int byt = in.read();
			if (mb_offset >= mb_buffer.length) {
				mb_offset = 0;
			}

			if (byt == -1) {
				// should not happen!
				log.error("BUFFER UNDERFLOW");
				try {
					Thread.sleep(200);
				} catch (InterruptedException e) {
				}
				continue;
			}

			if (byt == SB) {
				// start of message
				mb_buffer[0] = (byte) byt;
				mb_offset = 1;
			} else if (byt == EB) {
				if (mb_offset > 10) { // should be MUCH MUCH greater than 10
					checkCRC();
					try {
						// strip SB + 4-char-CRC (and EB)
						parsePacket(mb_buffer, 1, mb_offset - 5);
					} catch (HL7Exception e) {
						log.error("Message parsing error", e);
					}
				} else {
					log.warn("SKIPPING INVALID DATA: len={}", mb_offset);
				}
				mb_offset = 0;

			} else {
				mb_buffer[mb_offset++] = (byte) byt;
			}

		}

	}

	private void checkCRC() {
		System.err.println("FIXME: check CRC");
	}


	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

}
