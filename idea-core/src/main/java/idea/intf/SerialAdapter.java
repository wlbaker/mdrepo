package idea.intf;

import static icuInterface.LoggingUtil.dumpEvent;
import static icuInterface.LoggingUtil.encode;
import static icuInterface.LoggingUtil.getLoggingOutputStream;
import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;

import idea.conf.DeviceCapabilities;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.schema.rp.RpConnection;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

import java.io.ByteArrayInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.TooManyListenersException;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

/*
 * 
 */
@Slf4j
public abstract class SerialAdapter //
		extends AbstractStreamProducer //
		implements AdapterInterface, //
		SerialPortDataListener // deprecated
{

	protected PrintStream logging_out = System.out;
	LoggingOutputStream lout = null;

	protected RpDevice conf;
	private long ts = -1;
	// private SimulatedSerialPort simuport;
	// private SerialPort port;
	protected SerialPort hw_port;
	private OutputStream outputStream;

	@Override
	public void fireStreamEvent(int jobId, StreamProducer src, StreamID sid, PersistentItem block) {
		super.fireStreamEvent(jobId, src, sid, block);

		if (logging_out != null) {
			dumpEvent(logging_out, (PlatformUtil.currentTimeMillis() - ts), jobId, src, sid, block);
		}

	}

	public SerialAdapter(RpDevice conf) {
		this.conf = conf;

		logging_out = getLoggingOutputStream(this.getClass());
	}

	public void setPort(SerialPort port) {
		this.hw_port = port;

		log.error("FIXME: probably didnt encapsulate logging output stream");

		this.outputStream = port.getOutputStream();

		DeviceCapabilities caps = (DeviceCapabilities) this.getStaticCapabilities();

		if (caps == null) {
			log.error("NO CAPS FOR DEVICE: {}", getClass());
		} else {
			RpConnection[] conns = caps.getConnections();
			if (conns == null || conns.length == 0) {
				log.error("no connection parameters: {}", getClass());
			} else if (conns.length == 1) {
				//rxtx	port.setSerialPortParams(9600, 8, 1, 0);
				port.setBaudRate( 9600 );
				port.setNumDataBits( 8 );
				port.setNumStopBits( 1 );
				port.setFlowControl( SerialPort.FLOW_CONTROL_DISABLED );
			} else {
				log.warn("Cannot determing which CONN to use: {}", getClass());
			}
		}

	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	private SerialPort createPort(String portName)
			throws IOException, TooManyListenersException {
		if (hw_port != null) {
			disconnect();
		}
		if (portName.startsWith("sealink")) {
			System.err.println("hw_port = new SealinkSerialPort(portName);");
			System.err.println("FIXME: SealLink support incomplete.");
		} else {
			//rxtx CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier(portName);
			//rxtx hw_port = (SerialPort) portId.open(getClass().getCanonicalName(), 2000);
			//rxtx hw_port.notifyOnDataAvailable(true);
			//rxtx hw_port.addEventListener(this);

			//rxtx hw_port.setDTR(true);
			//rxtx hw_port.setRTS(true);
			hw_port = SerialPort.getCommPort( portName );
			hw_port.addDataListener(this);
			hw_port.setDTR();
			hw_port.setRTS();

		}
		return hw_port;

	}

	protected void connect(String portName, int baud, int datab, int stopb, int parity) throws IOException {
		try {
			SerialPort hw_port = createPort(portName);

			//rxtx hw_port.setSerialPortParams(baud, datab, stopb, parity);
			hw_port.setBaudRate( baud );
			hw_port.setNumDataBits( datab );
			hw_port.setNumStopBits( stopb );
			hw_port.setParity( parity );
			hw_port.openPort();
			if (logging_out != null) {
				encapsulateOutputPort(hw_port);
			}

			this.outputStream = hw_port.getOutputStream();
		} catch (IOException e) {
			throw e; // just re-throw
		} catch (Exception e) {
			e.printStackTrace(); // encode as an io exception
			throw new IOException(e);
		}

	}

	@Override
	public void disconnect() throws IOException {
		if (hw_port != null) {
			OutputStream out = hw_port.getOutputStream();
			out.flush();
			hw_port.removeDataListener();

			hw_port.closePort();
			hw_port = null;
		}
		setStatus(ConnectionStatus.NOT_CONNECTED);

	}

	private InputStream dump(InputStream in) throws IOException {

		if (logging_out == null) {
			return in;
		}

		if (ts == -1) {
			ts = PlatformUtil.currentTimeMillis();
		}

		int avail = in.available();

		byte[] r = new byte[avail];
		in.read(r, 0, avail);

		String s = encode(r);
		logging_out.print("# t=");
		logging_out.print((PlatformUtil.currentTimeMillis() - ts));
		logging_out.println();
		logging_out.print("[in] ");
		logging_out.print(':');
		logging_out.println(s);

		in = new ByteArrayInputStream(r, 0, avail);

		return in;
	}

	private void encapsulateOutputPort(SerialPort port) throws FileNotFoundException, IOException {
		assert (logging_out != null) : "dont call! null checks done before this point";
		OutputStream ostream = null;
		if (port != null) {
			ostream = port.getOutputStream();
		}
		lout = new LoggingOutputStream(ostream, logging_out);
	}

	@Override
	public void serialEvent(SerialPortEvent event) {

		try {
			switch (event.getEventType()) {
			case SerialPort.LISTENING_EVENT_DATA_AVAILABLE: {
				SerialPort pp = (SerialPort) event.getSource();
				InputStream in = dump(pp.getInputStream());
				process(in, pp.getOutputStream());
			}
				break;
			default:
				log.warn("unrecognized seial event: {}", event);
			}

		} catch (Exception e) {
			log.error("serialEvent", e);
			reset();
		}

	}

	public void reset() {
		// override to handle communication resets
		setStatus(ConnectionStatus.NOT_CONNECTED);
	}

	public OutputStream getOutputStream() {
		return outputStream;
	}

	public void setOutputStream(OutputStream outputStream) {
		this.outputStream = outputStream;
	}

	@Override
	public int getListeningEvents() {
		return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
	}

}
