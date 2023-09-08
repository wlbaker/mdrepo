package idea.discovery;

import java.util.ArrayList;
import java.util.List;

import idea.conf.DeviceFactory;
import idea.intf.SerialAdapter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class TestProbeData {
	private static final int DATABITS_8 = 8;
	private static final int STOPBITS_1 = 1;
	private static final int PARITY_NONE = 0;

	SerialAdapter driver;
	int baud;
	int datab;
	int stopb;
	int parity;

	private final static byte[] medibus_probe_bytes = new byte[] { 0x1b, 0x30, 0x34, 0x42, 0x0d };
	private final static byte[] medibus_resp_bytes = new byte[] { 0x1b, '1', '?', '6' };

	private final static byte[] pluma_probe_bytes = "\rT@{IDX3};ISTA;2FAD\r".getBytes();
	private final static byte[] pluma_resp_bytes = "zzST".getBytes();

	private final static byte[] ifmout_resp_bytes = new byte[] { 'F', '?', ';' };

	private final static byte[] evita_resp_bytes = new byte[] { 0x02, 'N' };
	// kangaroo: "x".getBytes(), "ePumpST".getBytes()
	// bard: "\n".getBytes(), ":CCORE:".getBytes(),

	public TestProbeData(SerialAdapter driver, int baud, int datab, int stopb, int parity) {
		this.driver = driver;
		this.baud = baud;
		this.datab = datab;
		this.stopb = stopb;
		this.parity = parity;
	}

	public static ArrayList<SerialAdapter> probeData;

	public static void init(RpStudy study) {

		probeData = new ArrayList<SerialAdapter>();

		List<RpHardware> hws = study.getHardware();
		List<RpDevice> devs = hws.get(0).getDevices();
		for (RpDevice dev : devs) {
			String cl = dev.getDeviceClass();
			Class<?> xcl;
			try {
				xcl = Class.forName(cl);
				if (SerialAdapter.class.isAssignableFrom(xcl)) {
					// DeviceConfiguration conf =
					// RpUtil.createDeviceConfiguration(dev, false);
					SerialAdapter d = (SerialAdapter) DeviceFactory.createDriver(cl, dev);
					probeData.add(d);
				}
			} catch (ClassNotFoundException e) {
				log.error("config error: {}", e.getMessage() );
			}
			// new ProbeData("PlumA", 1200, DATABITS_8, STOPBITS_1, PARITY_NONE)
			// null, // give pluma more time to respond
			// new ProbeData("Kangaroo", 9600, DATABITS_8, STOPBITS_1,
			// PARITY_NONE),
			// new ProbeData("Bard", 9600, DATABITS_8, STOPBITS_1, PARITY_NONE),
			// new ProbeData("medibus", 19200, DATABITS_8, STOPBITS_1,
			// PARITY_NONE)
		}
	}

}
