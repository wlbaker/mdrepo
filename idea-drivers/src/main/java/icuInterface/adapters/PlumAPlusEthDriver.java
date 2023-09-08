package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.ERROR;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.ByteArrayInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.SequenceInputStream;
import java.util.Enumeration;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Vector;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPFile;
import org.xml.sax.SAXException;

import icuInterface.ConnectionStatus;
import icuInterface.adapters.plumA.PlumASaxParser;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.PlumAPlusMeasurement;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PlumAPlusEthDriver extends AbstractStreamProducer implements AdapterInterface {

	private static final String driverName="pump/Hospira Plum-A+ Ethernet";
	
	int verbose = 1;

	private SocketDeviceConfiguration conf;

	private static DeviceCapabilities cap;

	private int tick;

	private String host;
	int port = 0;

	private String username = "ftp";
	private String password = "ftp";

	private Timer connTimer;

	private static final String ROOT_DIR = "/ram/mnt/jffs2/plumLog/:PUMPID/0/:SERNO"; // 15908081
	protected static long CONN_TIMER_INTERVAL = 5000L;

	static {
		cap = new DeviceCapabilities(PlumAPlusEthDriver.class);


		cap.addStream( StreamID.MEASUREMENT, PlumAPlusMeasurement.class );

		cap.setModels( new String [] {"Plum-A+"});
	}

	public static SocketDeviceConfiguration createConfigInstance() {
		SocketDeviceConfiguration conf = new SocketDeviceConfiguration(PlumAPlusEthDriver.class);
		conf.setDriverName("PlumAPlusDriver");
		conf.setModelName("PlumAPlus");
		return conf;
	}

	/**
	 * 
	 */
	public PlumAPlusEthDriver(DeviceConfiguration conf) {
		this.conf = (SocketDeviceConfiguration) conf;

		AdapterUtil.fix_config(cap, conf);
	}

	public void processMessage(String message) {
		// ignore it if it is not a complete message
		if (message.length() > 7) {
			String identifier = message.substring(0, 3);

			if (identifier.equals("D01")) {
				PlumAPlusMeasurement block = new PlumAPlusMeasurement();

				String[] ar = message.split(",");

				for (RpMetric m : block.getMetrics() ) {
					int loc = Integer.parseInt(m.getLocation());
					Number value = Integer.parseInt(ar[loc]);
					IntfUtil.setValue(block, m, value);
				}
				fireStreamEvent(0,this,StreamID.MEASUREMENT, block);
				tick = 0;
			} else if (identifier.equals("D96")) {
				// patient setup info
			} else if (identifier.equals("D97")) {
				// calibration
			}
		}
	}

	@Override
	public void connect() throws IOException {

		host = conf.getHost();
		if (host == null) {
			host = "192.168.1.2"; // TODO: fix wizard to save IP address
		}

		if (verbose > 0) {
			System.out.println(" --> pluma " + host + "/" + port);
		}

		setStatus(NEGOTIATING);

		initTimers();

	}

	/**
	 * Initializes the icuInterface(s).
	 */
	protected void initTimers() {

		// create a timer that will monitor the connection, if no data has been
		// received in the last X seconds attempt to send a ping,if still no
		// result, then fire a disconnected event.
		connTimer = new Timer();
		connTimer.schedule(new TimerTask() {

			@Override
			public void run() {
				try {
					getEventLog();

				} catch (Exception ee) {
					setStatus(ConnectionStatus.NOT_CONNECTED);
					// do nothing
					System.err.println("[PlumAPlusDriver] " + ee.getMessage());
				}

			}

		}, 5000L, CONN_TIMER_INTERVAL);

	}

	private void getEventLog() throws IOException {
		FTPClient f = new FTPClient();
		f.connect(host);
		f.login(username, password);

		String directory = ROOT_DIR.replace(":PUMPID", "0");
		directory = directory.replace(":SERNO", "");

		FTPFile[] files = f.listFiles(directory);

		if (files == null || files.length == 0) {
			return; // no event log yet
		}
		String serNo = files[0].getName();

		for (int i = 0; i < 3; i++) {
			directory = ROOT_DIR.replace(":PUMPID", "0");
			directory = directory.replace(":SERNO", serNo);

			f.changeWorkingDirectory(directory);
			files = f.listFiles();
			for (FTPFile file : files) {
				String fileName = file.getName();
				if (fileName.endsWith("idx")) {
					// ignore index files
					continue;
				}

				System.out.println("retrieving file: " + fileName);
				InputStream istream = f.retrieveFileStream(fileName);

				if (istream == null) {
					System.err.println("error retrieving file: " + fileName);
				} else {
					try {
						parseStream(istream);
					} catch (ParserConfigurationException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (SAXException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					istream.read();
					istream.close();
				}
			}
		}

		f.disconnect();

		if (getStatus() == NOT_CONNECTED) {
			setStatus(CONNECTED);
		}
	}

	private void parseStream(InputStream istream) throws ParserConfigurationException, SAXException, IOException {

		String prefix = "<?xml version=\"1.0\"?><wrapper>";
		String suffix = "</wrapper>";

		Vector<InputStream> v = new Vector<InputStream>();

		v.add(new ByteArrayInputStream(prefix.getBytes()));
		v.add(istream);
		v.add(new ByteArrayInputStream(suffix.getBytes()));

		Enumeration<InputStream> ins = v.elements();

		SequenceInputStream sins = new SequenceInputStream(ins);
		SAXParserFactory factory = SAXParserFactory.newInstance();
		SAXParser saxParser = factory.newSAXParser();

		PlumASaxParser handler = new PlumASaxParser();

		saxParser.parse(sins, handler);

		System.out.println("parse complete!");
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
	public void disconnect() throws IOException {
		if (connTimer != null) {
			try {
				connTimer.cancel();
				connTimer = null;
			} catch (Exception e) {
			}
		}

		setStatus(NOT_CONNECTED);
		host = null;
		port = 0;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (deviceState == ERROR) {
			return -1;
		}
		if (tick > 80) {
			if (deviceState != NOT_CONNECTED) {
				deviceState = NOT_CONNECTED;
				setStatus(NOT_CONNECTED);
			}
		} else {
			if (deviceState == NEGOTIATING) {
				// ??
			} else if (deviceState != CONNECTED) {
				deviceState = CONNECTED;
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

	public static void main(String[] args) throws Exception {
		String fileName = "c:/cygwin/home/bbaker/plumA/0000000108";

		InputStream ins = new FileInputStream(fileName);

		PlumAPlusEthDriver plum = new PlumAPlusEthDriver(null);
		plum.parseStream(ins);

		ins.close();
	}
}
