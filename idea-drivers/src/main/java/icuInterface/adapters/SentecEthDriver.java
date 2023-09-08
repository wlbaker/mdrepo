package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.ERROR;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.ByteBuffer;
import java.util.Timer;
import java.util.TimerTask;

import icuInterface.ConnectionStatus;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.TcpServerConnection;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.message.StreamID;
import idea.model.dev.SentecEthMeasurement;
import idea.schema.rp.RpMetric;

public class SentecEthDriver extends AbstractStreamProducer implements AdapterInterface {

	private static final String driverName="misc/Sentec TransQ PCO2 [Ethernet]";
			
	private static final byte[] helloPacket = "/hello\r\n".getBytes();
	private static final byte[] onlinePacket = "/online=on\r\n".getBytes();
	private static final byte[] offlinePacket = "/online=off\r\n".getBytes();

	private final static int port = 62000;

	private SocketDeviceConfiguration conf;
	private DatagramSocket serverSocket;

	private static DeviceCapabilities cap;

	private static RpMetric[] metrics;
	private Timer restartTimer;

	private int commTimeout;
	private int tick;

	int poll_pos = 0;

	private boolean debug = true;

	static {
		cap = new DeviceCapabilities(SentecEthDriver.class);


		cap.addStream(StreamID.MEASUREMENT, SentecEthMeasurement.class );
		cap.setModels( new String [] { "SenTec"});

		cap.addConnection(new TcpServerConnection() );
	}

	public static SocketDeviceConfiguration createConfigInstance() {
		return new SocketDeviceConfiguration(SentecEthDriver.class);
	}

	public SentecEthDriver(DeviceConfiguration conf) {

		this.conf = (SocketDeviceConfiguration) conf;

		// waveform_block = new WaveformBlock();

	}

	@Override
	public void connect() throws IOException {

		int p = conf.getPort();
		serverSocket = new DatagramSocket(p);

		Runnable reader = new Runnable() {

			@Override
			public void run() {

				try {
					// Create a DatagramPacket and do a receive
					byte buf[] = new byte[2048];
					DatagramPacket pack = new DatagramPacket(buf, buf.length);

					for (;;) {
						serverSocket.receive(pack);

						parsePacket(pack.getData());
						commTimeout = 5;
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}

		};

		try {

			Thread th = new Thread(reader);
			th.start();
			setStatus(NOT_CONNECTED);
			initDataFlow();
		} catch (Exception e) {
			setStatus(ERROR);
			e.printStackTrace();
			throw new IOException(e);
		}

	}

	private void parsePacket(byte[] data) {
		ByteBuffer bb = ByteBuffer.wrap(data);

		byte[] line = new byte[128];
		int pos = 0;

		while (bb.remaining() < 0) {
			byte ch = bb.get();
			if (ch == '\n') {
				// ignore
				pos = 0;
			} else if (ch == '\r') {
				parseParameter(line, pos);
				pos = 0;
			} else {
				line[pos++] = ch;
				if (pos > 127) {
					System.err.println("Sentec packet overflow!");
					pos = 0;
					break;
				}
			}
		}
		byte[] id = new byte[16];
		System.err.println("got senetc packet...parse?");
		bb.get(id); // should be SenTec_SDM302848
	}

	private void parseParameter(byte[] line, int pos) {
		String s = new String(line, 0, pos);
		String[] ar = s.split("=");
		if (ar != null && ar.length == 2) {
			System.out.println(" param: " + ar[0] + " value: " + ar[1]);
			// possible values of param:
			// SenTec_SDM302848 = 192.168.1.3:62768
			// &f7 = 192.168.1.3
			// &64 = VS-A/P
			// &83 = CE
			// &4e = 0.0
			// &4a = 17.0|20
			// &b4 = 45
			// &b5 = 30
			// Pco2PartAttr=u
			// &35=94|0
			// &a2=100
			// &a3=85
			// PoxSpO2Attr=
			// &36=85|0
			// &a5=140
			// &a6=50
			// QPoxPRAttr=
			// &37=0.9|0
			// &17=adult
			// AppMonitoringStatus = 100%
			// vDisplayStatusText = PCO2 stabilizing
			// &87=info
			// &24=42.0|10
			// &26=0|40
			// WuTempStatus = protected
			// WuPowerStatus = -
			// SmbDateTime=20 11-04096 14:27:52
			// &23 = 42.0
			// &2a = 42.0
			// &93 = 0
			// &91 = 0
			// &27 = 8.0
			// &29 = 12.0
			// AppMonitoringTimeVal=8.0h
			// &65 =
			// &66 =
			// WuStatus = SP
			// &45=480
			// &43=8.9
			// &61=305680
			// &62=SV2D 01E A 01
			// &63=V02.05
			// &33 = 6
			// &1b = basic
			// &8d = -
			// SmbSerialNb=302848
			// &53=V05.00.10
			// &fb=V07.00.4
			// SmbPower=BAT
			// SmbBatteryCharge=78
			// SmbBatteryStatus=100%
			// MpbBarometerStatus=-
			// MbpBarometerVal=741.2
			// DsGas=0%|30
			// DsGasStatus=-
			// &e1=normal
			// &e4=4
			// &e7=on

		}

	}

	@Override
	public void disconnect() throws IOException {
		restartTimer.cancel();
		serverSocket.close();

		setStatus(NOT_CONNECTED);
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
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	private void processWaveformPacket(byte[] valuesRead, int start, int len) {

		// this.fireEvent(WaveformEvent.class, new WaveformEvent(this,
		// waveform_block));
		assert (false) : "Sentec Ethernet does not support waveforms currently.";
	}

	private void initDataFlow() {
		restartTimer = new Timer();

		TimerTask task = new TimerTask() {

			@Override
			public void run() {
				try {
					timerPulse();
				} catch (Exception e) {

					// dumpPacket(mb_buffer, mb_offset);
					setStatus(NOT_CONNECTED);
					e.printStackTrace();
				}
			}

		};

		restartTimer.schedule(task, 500, 500);
	}

	public void timerPulse() throws IOException {

		if (serverSocket == null) {
			return; // nothing to do right now.
		}

		if (debug) {
			return;
		}

		ConnectionStatus deviceState = getStatus();
		if (deviceState == NOT_CONNECTED && commTimeout == 0) {
			byte[] buf = new byte[] { '&', 'a', '2', '\r', '\n' };
			DatagramPacket p = new DatagramPacket(buf, buf.length);
			serverSocket.send(p);
			commTimeout = 5;
			System.out.println("[SentecEthDriver] sent init request");
		} else if (deviceState == NOT_CONNECTED) {
			commTimeout--;
			if (commTimeout <= 0) {
				setStatus(NOT_CONNECTED);
				commTimeout = 0;
			}
		} else if (deviceState == CONNECTED) {

			if (commTimeout == 0) {
				setStatus(NOT_CONNECTED);
			} else {
				if (poll_pos >= metrics.length) {
					poll_pos = 0;
				}
				RpMetric param = metrics[poll_pos++];
				String loc = param.getLocation();

				byte[] buf = new byte[5];
				byte[] bytes = loc.getBytes();
				buf[0] = bytes[0];
				buf[1] = bytes[1];
				buf[2] = bytes[2];
				buf[3] = '\r';
				buf[4] = '\n';

				DatagramPacket p = new DatagramPacket(buf, buf.length);
				serverSocket.send(p);

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
				setStatus(ConnectionStatus.NOT_CONNECTED);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(ConnectionStatus.CONNECTED);
			}
		}
		
		return 0;
	}

}
