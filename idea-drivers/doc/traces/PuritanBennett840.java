package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import gnu.io.CommPortIdentifier;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortEvent;
import com.fazecast.jSerialComm.SerialPortEventListener;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import icuInterface.message.WaveformBlock;
import icuInterface.message.WaveformItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.conf.WaveformDescription;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.message.StreamID;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.nio.IntBuffer;

import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;

public class PuritanBennett840 extends AbstractStreamProducer implements
		AdapterInterface, SerialPortEventListener {

	@SuppressWarnings("unused")
	private static final String driverName="ventilator/Puritan Bennett 840";
	
	SerialPort port = null;
	InputStream inputStream;
	BufferedReader buffer;

	private DeviceCapabilities cap;

	private SerialDeviceConfiguration conf;

	private RpMetric[] md;

	IntBuffer[] wf_data;
	private int tick;
	protected final static int WF_PACKET_SIZE = 64;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(PuritanBennett840.class);
	}

	/**
	 * 
	 */
	public PuritanBennett840(DeviceConfiguration conf) {
		this.conf = (SerialDeviceConfiguration) conf;
		cap = new DeviceCapabilities( PuritanBennett840.class );

		RpLinearUnit mv = new RpLinearUnit( 1.0, 0, "mV");
		md = new RpMetric[97];
		md[0] = RpUtil.createMetric("01", "vtm", "Ventilator Time",
				"hh:mm");
		md[1] = null; // unused, 18 char
		md[2] = null; // unused, 6 char
		md[3] = RpUtil.createMetric("04", "vdt", "Ventilator Date",
				"mmmddyyyy");
		md[4] = RpUtil.createMetric("05", "mode", "Mode CMV/SIMV/CPAP",
				"a6");

		cap.addWaveform("W0", "Wave0", "Wave0name", 100,
				WF_PACKET_SIZE, mv);
		cap.addWaveform("W1", "Wave1", "Wave1name", 100,
				WF_PACKET_SIZE, mv);

		cap.setModels( new String [] { "PB840" }  );
		wf_data = new IntBuffer[2];

		wf_data[0] = IntBuffer.allocate(WF_PACKET_SIZE);
		wf_data[1] = IntBuffer.allocate(WF_PACKET_SIZE);

		if (conf != null) {
			WaveformDescription[] waves = cap.getWaveforms();
			for (WaveformDescription wave : waves) {
				conf.addWaveform(wave);
			}
		}
	}

	public void sendPacket(byte[] bytes) throws IOException {
		OutputStream outputStream = port.getOutputStream();
		outputStream.write(bytes);
	}

	public void processMessage(String message) {
		// ignore it if it is not a complete message
		if (message.length() > 3) {

			if (message.startsWith("B")) {
				// breath mark, ignore

				// Numerics get sent on another serial channel
				// NumericsBlock block = new NumericsBlock();
				//
				// String[] dataArray = message.split(" ");
				// if (dataArray != null && dataArray.length > 11) {
				//
				// for (int i = 0; i < 6; i++) {
				// NumericsItem item = new NumericsItem(md[i]);
				// item.setValue(dataArray[i + 5]); // 5
				// block.add(item);
				// }
				//
				// }
				//
				// NumericsEvent nevent = new NumericsEvent(this, block);
				// this.fireEvent(NumericsEvent.class, nevent);
			} else {
				String[] vals = message.split("[ ,\r\n\t]+");
				if (vals.length == 2) {
					System.out.println("parsing: " + vals[0] + "*" + vals[1]
							+ " from: " + message);
					wf_data[0].put((int) (Double.parseDouble(vals[0]) * 100.0));
					wf_data[1].put((int) (Double.parseDouble(vals[1]) * 100.0));
				}

				sendWaveforms();

			}
		}
	}

	private void sendWaveforms() {
		WaveformBlock block = null;
		WaveformDescription[] wfd = conf.getWaveforms();
		for (int idx = 0; idx < wf_data.length; idx++) {
			IntBuffer bb = wf_data[idx];
			if (bb.position() == WF_PACKET_SIZE) {
				WaveformDescription desc = wfd[idx];
				WaveformItem wf = new WaveformItem(desc);
				wf.setValues(bb.array());

				if (block == null) {
					block = new WaveformBlock();
				}
				block.add(wf);

				bb.clear();
			}
		}

		if (block != null) {
			// WARNING: If these don't match, you will end up with overlapping
			// graphs.
			// if( block.getWaveforms().length == conf.getWaveforms().length ) {
			// System.err.println("GOT AN ERR!");
			// }
			fireStreamEvent(0,this,StreamID.WAVEFORM, block);
		}
		tick = 0;
	}

	@Override
	public void connect() throws IOException {

		String portName = conf.getPort();
		try {

			System.out.println(" --> PB840 on " + portName);
			CommPortIdentifier portId = CommPortIdentifier
					.getPortIdentifier(portName);
			port = (SerialPort) portId.open("PB840", 2000);

			// int baud = 9600;
			int baud = 38400;

			port.setSerialPortParams(baud, 8,
					1, SerialPort.NO_PARITY);

			port.setDTR();
			port.setRTS();
			// port.setRTS( true );

			port.notifyOnDataAvailable(true);
			port.addEventListener(this);

			sendStartupCommands();

			inputStream = port.getInputStream();
			InputStreamReader reader = new InputStreamReader(inputStream);
			buffer = new BufferedReader(reader);

		} catch (Exception e) {
			e.printStackTrace();
			throw new IOException(e);
		}

	}

	public void sendStartupCommands() throws IOException {
		// nothing to send to start comm
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this,cap);
	}
	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	/**
	 * Called when a serial port event occurs
	 */
	@Override
	public void serialEvent(SerialPortEvent event) {
		// Should never happen, but it could ...
		assert (event != null) : "Null event in serial event.";

		SerialPort port = (SerialPort) event.getSource();

		// Check the event type
		switch (event.getEventType()) {
		case SerialPort.LISTENING_EVENT_DATA_AVAILABLE:

			// If we get here then data has been received
			try {

				String line = null;
				while ((inputStream.available() > 0)
						&& (line = buffer.readLine()) != null) {
					processMessage(line);
				}

			} catch (Exception e) {
				// No more lines
				setStatus( NOT_CONNECTED);
				System.out.println("Exception in serial reader???");
				e.printStackTrace();
			}
			break;

		default:
			System.out.println("unknown event: " + event.getEventType());
			break;

		}
	}

	@Override
	public void disconnect() throws IOException {
		if (port != null) {
			port.close();
			port = null;
		}
	}

	@Override
	public void tick() {
		tick++;
		ConnectionStatus deviceState = getState();
		if( tick > 4 ) {
			if( deviceState != NOT_CONNECTED ) {
				setStatus( ConnectionStatus.NOT_CONNECTED);
			}
		} else {
			if( deviceState != CONNECTED ) {
				setStatus( CONNECTED);
			}
		}
	}

}
