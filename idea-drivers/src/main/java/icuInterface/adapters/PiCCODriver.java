package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.model.dev.PICCOV3_Vitals;
import idea.model.dev.PICCO_ART;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PiCCODriver extends SerialAdapter implements AdapterInterface {

	@SuppressWarnings("unused")
	private static final String driverName = "misc/Pulsion PiCCO";

	private final static byte HDR = 0x71;

	private byte[] mb_buffer = new byte[20];
	private int mb_offset = 0;

	private static DeviceCapabilities cap;

	private int tick;

	private PICCOV3_Vitals curr_primary;

	private PICCO_ART curr_art;

	private SerialDeviceConfiguration conf;

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(PiCCODriver.class);
		conf.addStream(cap.getStream(StreamID.MEASUREMENT));

		return conf;
	}

	static {
		cap = new DeviceCapabilities(PiCCODriver.class);

		cap.addStream(StreamID.MEASUREMENT, PICCOV3_Vitals.class);
		cap.addStream(StreamID.WAVEFORM, PICCO_ART.class);
		cap.setModels(new String[] { "PiCCOv3" });

		cap.addConnection(new SerialConnection(19200, 8, 1, 2));
	}

	public PiCCODriver(RpDevice conf) {
		super(conf);
		this.conf = (SerialDeviceConfiguration) conf;

		AdapterUtil.fix_config(cap, conf);
	}

	@Override
	public void connect() throws IOException {

		curr_primary = new PICCOV3_Vitals();
		curr_art = new PICCO_ART();

		String portName = RpUtil.getParam(conf, "port");

		log.info(" --> connect {}", portName);

		connect(portName, 19200, 8, 1, 2);

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	@Override
	public void reset() {
		mb_offset = 0;
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {

		while (in.available() > 0) {

			int byt = in.read();
			if (byt == -1) {
				break;
			}

			if (mb_offset == 0) {
				if (byt != HDR)
					continue;
			}
			if (mb_offset > 18) {
				mb_offset = 0;
				return;
			}

			mb_buffer[mb_offset++] = (byte) byt;

			if (mb_offset == 18) {
				processResponse(mb_buffer);
				mb_offset = 0;
			}

		}

	}

	private boolean processResponse(byte[] buf) {

		if (curr_primary == null) {
			curr_primary = new PICCOV3_Vitals();
		}
		if (curr_art == null) {
			curr_art = new PICCO_ART();
		}

		// dump(System.out, buf, buf.length);

		ByteBuffer bb = ByteBuffer.wrap(buf);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int start = bb.get();
		int slot = bb.get();
		int n = bb.getShort();
		int ap = bb.getShort();
		int cell3 = bb.getShort();
		int cell4 = bb.getShort();
		int cell5 = bb.getShort();
		int cell6 = bb.getShort();
		int cell7 = bb.getShort();
		int cell8 = bb.getShort();

		if (slot > 19 || slot < 0) {
			log.error("Invalid slot in PICCOV3: {}", slot);
			return false;
		}

		curr_art.getArt()[slot] = ap;

		// System.out.print( " " + n);
		switch (slot) {
		case 0:
			curr_primary.setMAP(cell4 >= 0 ? cell4 : null);
			curr_primary.setSYS(cell5 >= 0 ? cell5 : null);
			curr_primary.setDIA(cell6 >= 0 ? cell6 : null);
			curr_primary.setCO(cell7 >= 0 ? cell7 : null);
			break;
		case 1:
			curr_primary.setGEDV(cell7 >= 0 ? cell7 : null);
			break;
		case 3:
			curr_primary.setHR(cell4 >= 0 ? cell4 : null);
			curr_primary.setEVLW(cell7);
			break;
		case 4:
			if (cell7 >= 0) {
				int upper = cell7 >> 8;
				int lower = cell7 & 0xff;
				curr_primary.setCFI(lower);
				curr_primary.setGEF(upper);
			} else {
				curr_primary.setCFI(null);
				curr_primary.setGEF(null);
			}
			break;
		case 8:
			curr_primary.setSVV(cell5 >= 0 ? cell5 : null);
			break;
		case 10:
			curr_primary.setCI(cell7 >= 0 ? cell7 : null);
			break;
		case 11:
			curr_primary.setGEDI(cell7 >= 0 ? cell7 : null);
			break;
		case 13:
			curr_primary.setELWI(cell7 >= 0 ? cell7 : null);
			break;
		case 14:
			curr_primary.setPCCI(cell4 >= 0 ? cell4 : null);
			break;
		case 17:
			curr_primary.setSCVO2(cell4 >= 0 ? cell4 : null);
			break;
		case 18:
			curr_primary.setSVRI(cell4 >= 0 ? cell4 : null);
			break;
		case 19:
			curr_primary.setPDR(cell4 >= 0 ? cell4 : null);
			fireStreamEvent(0, this, StreamID.MEASUREMENT, curr_primary);
			fireStreamEvent(0, this, StreamID.WAVEFORM, curr_art);
			tick = 0;
			break;
		}
		return true;
	}

	private void fireStreamEvent(int id, PiCCODriver piCCODriver, StreamID sid, PersistentItem item) {
		switch (sid) {
		case MEASUREMENT:
			fireStreamEvent(0, this, StreamID.MEASUREMENT, item);
			break;
		case WAVEFORM:

			fireStreamEvent(0, this, StreamID.WAVEFORM, item);
			break;

		default:
			log.error("could not translate stream event");
		}
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 6) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
				fireNoData(conf);
			}

			tick = 6;
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		return 0;
	}

}
