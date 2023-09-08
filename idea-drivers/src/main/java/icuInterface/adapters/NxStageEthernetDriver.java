package icuInterface.adapters;

/*
 * 
 * device serial number for tech support: PA0516
 * 
 */

import static icuInterface.ConnectionStatus.CONNECTED;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.HashMap;
import java.util.Map;

import com.sun.jna.Native;
import com.sun.jna.NativeLong;
import com.sun.jna.win32.StdCallLibrary;

import icuInterface.ConnectionStatus;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.message.StreamID;
import idea.model.dev.NxStageMeasurement;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;



@Slf4j
public class NxStageEthernetDriver extends AbstractStreamProducer implements AdapterInterface {
	private static final String driverName="renal/NxStage Ethernet";

	public interface NxCrypto extends StdCallLibrary {
	    NxCrypto INSTANCE = (NxCrypto) Native.loadLibrary("NxCrypto", NxCrypto.class);
	    // void EncryptTextWithCrc(String format, Object... args);
	    int NxDecryptWithCRC(byte []  encryptIn, byte [] pbPlainTextOut, NativeLong[] plLength);
	    int NxEncryptWithCRC(byte []  plainTextIn, byte [] pbEncryptedOut, NativeLong[] plLength);
	}
	
	private SocketDeviceConfiguration conf;

	Map<String, String> settings = new HashMap<String, String>();

	/*
	 * Commands
	 */

	public final static int DEFAULT_NXSTAGE_UDP_PORT = 14042;

	byte[] receiveData = new byte[4 * 1024];


	// private int idNo;
	// private int deviceName;
	// private int deviceRev;
	// private int medibusRev;

	protected static DeviceCapabilities cap;

	public final static int STATE_UNK = 0;
	public final static int STATE_RUN = 1;
	public final static int STATE_STOP = 2;
	public final static int STATE_OFF = 3;
	public final static int STATE_PROMPT = 4;
	public final static int STATE_ERROR = 5;

	private int[] state = new int[2];

	private int[] rate = new int[2];
	private int[] vtbi = new int[2];
	private int[] infused = new int[2];

	private DatagramSocket s;

	NxStageMeasurement just_here_to_link_till_complete;
	
	static {
		cap = new DeviceCapabilities(NxStageEthernetDriver.class);

		cap.addStream(StreamID.MEASUREMENT, NxStageMeasurement.class );
	}

	public static SocketDeviceConfiguration createConfigInstance() {
		SocketDeviceConfiguration conf = new SocketDeviceConfiguration(NxStageEthernetDriver.class);
		conf.setName("NxStageDriver");
		conf.setHost("127.0.0.1");
		conf.setPort(DEFAULT_NXSTAGE_UDP_PORT);
		return conf;
	}

	public NxStageEthernetDriver(DeviceConfiguration conf) {
		this.conf = (SocketDeviceConfiguration) conf;

	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	@Override
	public void connect() throws IOException {
		//
		// you either have to open the socket here or wait in for notification
		// from the
		// child thread
		//
		// this allows client applications to send commands immediately...like
		// login!
		//

		InetAddress ipAddress = InetAddress.getByName(conf.getHost()); // create an
		int port = conf.getPort();
		
		System.out.println("listening on port: " + port );
		s = new DatagramSocket( port );

		setStatus(ConnectionStatus.NEGOTIATING);
		Runnable r = new Runnable() {

			@Override
			public void run() {

				try {
					for (;;) {
						waitForData();
					}
				} catch (SocketException se) {
					if (s.isClosed()) {
						// normal exit
					} else {
						se.printStackTrace();
					}
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}

		};

		Thread th = new Thread(r);
		th.start();

	}


	private void waitForData() throws IOException {

		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		s.receive(receivePacket);

		if (getStatus() != CONNECTED) {
			setStatus(CONNECTED);
		}

		parseServerData(receivePacket); //

	}

	private void parseServerData(DatagramPacket receivePacket) {
		System.out.println("NXSTAGE: " + receivePacket );
		byte [] plainTextOut = new byte[1024];
		NativeLong [] length = new NativeLong[1]; 
		length[0] = new NativeLong( receivePacket.getLength() );
		System.out.println("ENCRYP len=" + receivePacket.getLength() );
		int err = NxCrypto.INSTANCE.NxDecryptWithCRC( receivePacket.getData(), plainTextOut, length);
		
		NxStageMeasurement block = new NxStageMeasurement();
		long len = length[0].longValue();
		System.out.println("err=0x" + Integer.toHexString(err) + " decryp len=" + len );
		for( int i = 0; i < len; i++ ) {
			System.out.print( (char)plainTextOut[i]);
		}
		// System.out.println();
		fireStreamEvent(0,this,StreamID.MEASUREMENT, block);
	}

	@Override
	public void disconnect() throws IOException {

		setStatus(ConnectionStatus.NOT_CONNECTED);

	}



	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	@Override
	public int tick() {
		return 0;
	}

}
