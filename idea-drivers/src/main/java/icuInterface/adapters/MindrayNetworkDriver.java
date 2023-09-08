package icuInterface.adapters;

import static icuInterface.LoggingUtil.dumpConfiguration;
import static icuInterface.LoggingUtil.getLoggingOutputStream;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

import ca.uhn.hl7v2.HL7Exception;
import icuInterface.ConnectionStatus;
import icuInterface.adapters.HL7.HL7AbstractDriver;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.message.StreamID;
import idea.model.dev.MindrayMeasurement;
import idea.model.dev.MindraySettings;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class MindrayNetworkDriver extends HL7AbstractDriver {
	private static final String driverName="monitor/Mindray Network";

	private final static byte SB = 0x0B; // Start Block ( (VT))
	private final static byte EB = 0x1C; // End Block (0x1C (FS))
	// private final static byte CR = 0x0D; //  Carriage Return (0x0D (CR))
	private static final int DEFAULT_MINDRAY_PORT = 1550;

	private int port_no;

	private Thread th;

	private PrintStream dout;

	private static DeviceCapabilities caps;
	private SocketDeviceConfiguration conf;

	ServerSocket listener;

	static {
		caps = new DeviceCapabilities(MindrayNetworkDriver.class);
		caps.addStream(StreamID.SETTINGS, MindraySettings.class);
		caps.addStream(StreamID.MEASUREMENT, MindrayMeasurement.class);
		caps.setModels( new String [] {"A5"} );
	}

	public static SocketDeviceConfiguration createConfigInstance() {
		SocketDeviceConfiguration conf = new SocketDeviceConfiguration(MindrayNetworkDriver.class);
		conf.setName("Mindray");
		conf.setPort(DEFAULT_MINDRAY_PORT);
		return conf;
	}

	public MindrayNetworkDriver(DeviceConfiguration conf) {
		super(caps, null);

		this.dout = getLoggingOutputStream(this.getClass());
		if (dout != null) {
			dumpConfiguration(dout, this);
		}

		this.conf = (SocketDeviceConfiguration) conf;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;     // we are hiding this configuration from the lower layers
	}

	@Override
	public void connect() throws IOException {

		if (th != null) {
			disconnect();
		}

		Runnable r = new Runnable() {

			@Override
			public void run() {

				try {

					SocketDeviceConfiguration sconf = conf;
					// String ip = sconf.getHost();
					port_no = sconf.getPort();
					listener = new ServerSocket(port_no);

					MindrayNetworkDriver.this.setStatus(ConnectionStatus.NEGOTIATING);
					while (true) {
						new Handler(MindrayNetworkDriver.this, listener.accept()).start();
					}
				} catch (Exception e) {
					log.error("listener socket exception");
				}

			}

		};

		th = new Thread(r);
		th.start();
	}

	@Override
	public void disconnect() throws IOException {

		if (listener != null) {

			log.error("requesting synch of disconnect");

			listener.close();
			try {
				th.interrupt();
				th.join();
			} catch (Exception e) {
				log.error("disconnecting", e);
			} finally {
				th = null;
			}
			log.error("got sync of disconnect");

			listener = null;
			setStatus(ConnectionStatus.NOT_CONNECTED);
		}

	}



	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		// FIXME: remove this.

	}

	/**
	 * 
	 * A handler thread class. Handlers are spawned from the listening loop and
	 * are responsible for a dealing with a single client and broadcasting its
	 * messages.
	 */
	private static class Handler extends Thread {
		private Socket socket;
		
		int mb_offset = 0;
		byte[] mb_buffer = new byte[8096];
		private MindrayNetworkDriver parent;


		/**
		 * * Constructs a handler thread, squirreling away the socket. * All the
		 * interesting work is done in the run method.
		 * @param mindrayNetworkDriver 
		 */
		public Handler(MindrayNetworkDriver parent, Socket socket) {
			this.socket = socket;
			this.parent = parent;
		}

		/**
		 * * Services this thread's client by repeatedly requesting a * screen
		 * name until a unique one has been submitted, then * acknowledges the
		 * name and registers the output stream for * the client in a global
		 * set, then repeatedly gets inputs and * broadcasts them.
		 */
		@Override
		public void run() {
			try { // Create character streams for the socket. 
				InputStream in = socket.getInputStream();
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
							try {
								parent.parsePacket(mb_buffer, 1, mb_offset - 1);
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
			} catch (IOException e) {
				log.error("i/o error", e);
			} finally {
				try {
					socket.close();
				} catch (IOException e) {
				}
			}
		}
	}
}
