package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.DriftRectifier;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterUtil;
import idea.intf.DataTyp;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

class WaveDetails {
	protected final static int WF_PACKET_SIZE = 128;

	int param_id;
	int unit_id;
	int pkt_pts;
	int[] wave_dat = new int[WF_PACKET_SIZE];
	int wave_pt = 0;

	String loc;
	public RpMetric w;
}

class ParamDetails {
	// byte o1 = bb.get();
	byte seq;
	int param_group;
	int param_id;
	int unit_id;
	int unk_trq; // NBP=05 or else=01
	int unk_ffff; // all entries were ffff
	int unk_b; // // hex values 01, 21, 31, 51
	int val_count; // number of values returned

	String loc;
	public RpMetric m;
	public byte unk_c;
	public byte mult;
}

@Slf4j
public class VueLinkDriver extends SerialAdapter {
	@SuppressWarnings("unused")
	private static final String driverName = "misc/Philips VueLink*";
	/*
	 * Commands
	 */

	private final static byte TT_SPEC_REQUEST = 0x01;
	private final static byte TT_DATA_REQUEST = 0x02; // code-page 1...see also
	private final static byte TT_DEBUGGING = 0x03;
	private final static byte TT_SPEC_RESP = (byte) 0x81;
	private final static byte TT_DATA_RESP = (byte) 0x82;

	private boolean fastProtocol = false;
	private int req_ct = 0; // modulo 64 packet sequence count

	// caps cannot be static, since it is used by various drivers.
	private DeviceCapabilities cap;

	private DriftRectifier drifter = new DriftRectifier(2000, 1000, 11);

	private static final byte[] VUELINK_ID = "HP-VueLink-1".getBytes();
	private byte[] status_req = new byte[] { 0 };
	private int req_index;
	private byte[] poll_req = new byte[] { 0 };

	private int tick;

	int mb_offset = 0;
	byte[] mb_buffer = new byte[4096];
	private HashMap<Integer, RpLinearUnit> unit_hm;
	private HashMap<String, String> code_hm;
	private HashMap<String, RpMetric> pp_hm;
	private boolean with_waves;
	private ParamDetails[] details;
	private WaveDetails[] wave_details;
	private PersistentItem block;
	private int vvvv;
	int pkt_len = 0;
	int data_start = 2;
	int data_len = 0;
	private Class<?> measClass;
	private Class<?> wfClass;

	private int model_idx;

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(VueLinkDriver.class);
		// conf.setSettings(cap.getSettings());
		conf.setName(driverName);
		return conf;
	}

	public VueLinkDriver(RpDevice conf) {
		super(conf);

	}

	@Override
	public void connect() throws IOException {
		mb_offset = 0;

		String portName = RpUtil.getConnectionPort(conf);

		connect(portName, 19200, 8, 1, 0);

		requestSpec();
	}

	@Override
	public void disconnect() throws IOException {
		super.disconnect();
	}

	private void sendTelegram(byte typ, byte[] data) throws IOException {

		OutputStream out = getOutputStream();
		if (out == null) {
			return; // probably tick called before we are ready
		}

		int capacity = 4;
		if (data != null) {
			if (data.length > 254)
				capacity += 2;
			capacity += data.length;
		}

		ByteBuffer bb = ByteBuffer.allocate(capacity);
		bb.order(ByteOrder.BIG_ENDIAN);

		bb.put(typ);

		if (data == null) {
			bb.put((byte) 0);
		} else if (data.length < 255) {
			bb.put((byte) data.length);
		} else {
			bb.put((byte) 0xff);
			bb.putShort((short) data.length);
		}

		if (data != null) {
			bb.put(data);
		}

		int crc = CRCUtil.getCRC16g(bb.array(), 0, bb.capacity() - 2);
		bb.put((byte) (crc >> 8));
		bb.put((byte) (crc & 0xff));

		synchronized (out) {
			out.write(bb.array());
		}

	}

	private static void dump(PrintStream out, byte[] array, int len) {
		StringBuffer hex_buf = new StringBuffer();
		StringBuffer txt_buf = new StringBuffer();
		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 16 == 0)) {
				out.print(hex_buf.toString());
				out.print("\t\t");
				out.println(txt_buf.toString());

				hex_buf = new StringBuffer();
				txt_buf = new StringBuffer();
			}

			int byt = array[i];
			if (byt < 0)
				byt += 256;

			if (byt < 16) {
				hex_buf.append("0");
			}

			hex_buf.append(Integer.toHexString(byt));
			hex_buf.append(" ");

			if (byt >= 0x20 && byt < 0x80) {
				txt_buf.append((char) byt);
			} else {
				txt_buf.append(".");
			}
		}

		out.print(hex_buf.toString());
		out.print("\t\t");
		out.println(txt_buf.toString());

		out.println();
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {

		while (in.available() > 0) {
			int byt = in.read();
			if (mb_offset >= mb_buffer.length) {
				mb_offset = 0;
			}

			if (mb_offset == 0) {
				byte signedb = (byte) byt;
				if (signedb == TT_DATA_RESP || signedb == TT_SPEC_RESP) {
					mb_buffer[0] = (byte) byt;
					mb_offset = 1;
				} else {
					// ignore
				}
			} else {
				mb_buffer[mb_offset++] = (byte) byt;

			}

			if (mb_offset == 6) {

				data_start = 2;
				data_len = unsigned_byt(mb_buffer[1]);
				if (data_len == 0xff) {
					int hi = unsigned_byt(mb_buffer[2]);
					int lo = unsigned_byt(mb_buffer[3]);
					data_len = 256 * hi + lo;
					data_start = 4;
				}

				pkt_len = data_start + data_len + 2;
			}

			// System.out.println(mb_offset + " [" + Integer.toHexString(byt)
			// + "] TRIGGER=" + pkt_len);

			if (mb_offset == pkt_len && mb_offset > 3) {
				// System.out.println(" data_start=" + data_start + " len="
				// + data_len);
				// dump(System.out, mb_buffer, mb_offset);
				parseResponse(out, mb_buffer, data_start, data_len);

				tick = 0;
				mb_offset = 0;
				pkt_len = 0;
			}

		}
	}

	private int unsigned_byt(byte b) {
		return (b < 0) ? b + 256 : b;
	}

	private void sendWaveforms() {
		PersistentItem block = null;
		RpMetric[] wfd = IntfUtil.getMetrics(wfClass);
		for (int idx = 0; idx < wave_details.length; idx++) {
			WaveDetails w = wave_details[idx];
			RpMetric desc = wfd[idx];

			IntfUtil.setValue(block, desc, w.wave_dat);
			desc.setSampleRate(256);

			if (block == null) {
				long tm = PlatformUtil.currentTimeMillis();
				// tm = drifter.getRectifiedTime(tm);

				block = ModelUtil.getModelFromDataClass(wfClass);

				// int msPerPacket = 500;
				// drifter.setNextExpectedTime(tm + msPerPacket);
			}

			w.wave_pt = 0;
		}

		if (block != null) {
			fireStreamEvent(0, this, StreamID.WAVEFORM, block);
		}

	}

	private void parseResponse(OutputStream out, byte[] message, int data_start, int data_len) throws IOException {

		int len = mb_offset;

		int crc = CRCUtil.getCRC16g(message, 0, len - 2);

		byte ch0 = (byte) (crc >> 8);
		byte ch1 = (byte) (crc & 0xff);

		if (message[len - 2] == ch0 && message[len - 1] == ch1) {
			// this message passes the checksum
		} else {
			log.warn("CHK error: " + message[len - 2] + "." + message[len - 1] + " <> " + ch0 + "." + ch1);
			dump(System.err, message, len);
			return;
		}

		ByteBuffer bb = ByteBuffer.wrap(message, data_start, data_len);
		bb.order(ByteOrder.BIG_ENDIAN);
		byte tt = message[0];
		if (tt == TT_DATA_RESP) {
			// log.debug("got tt_data_resp");
			// dump(System.out, message, len);
			tick = 0;

			parseDataResponse(bb);
			requestNext();
		} else if (tt == TT_SPEC_RESP) {
			log.debug("got tt_spec_resp");

			// dump(System.out, message, len);
			parseSpecResp(bb);

			try {
				buildCapabilities();
			} catch (Exception e) {
				log.error("Could not build capabilities", e);
			}
			AdapterUtil.fix_config(cap, conf);

			with_waves = false;
			poll_req = new byte[1]; // dont request waves until after one
									// sequence of numerics
			// buildTransferRequest();
			requestStatus();
			fireCapabilitiesEvent(this, cap);
			tick = 0;
		} else {
			log.warn("Unrecognized request: {}", tt);
			dump(System.err, message, len);
		}
	}

	private void parseDataResponse(ByteBuffer bb) {

		if (block == null) {
			block = ModelUtil.getModelFromDataClass(measClass);
		}
		// response is based on request...
		byte b = poll_req[0];
		ParamDetails p = findParam(b);

		if (p == null) {
			log.debug("PARAM NOT FOUND: " + b);
		} else {
			// waveforms data comes FIRST in any data reply
			if (bb.remaining() >= 18) {
				for (int i = 1; i < 3; i++) { // poll_req.length; i++) {
					// byte widx = poll_req[i];
					int widx = i - 1;
					WaveDetails w = wave_details[widx];
					for (int j = 0; j < w.pkt_pts; j++) {
						w.wave_dat[w.wave_pt++] = unsigned_short(bb);
					}

					// System.out.println("wave pos=" +
					// wave_details[widx].wave_pt + buff len = );
					// for (int ii = 0; ii < w.buff.length; ii++) {
					// w.wave_dat[w.wave_pt++] = w.buff[ii];
					// }
				}
			}

			if (wave_details[0].wave_pt == WaveDetails.WF_PACKET_SIZE) {
				sendWaveforms();
			}
			// if (bb.remaining() < 5) {
			// log.error("NO REMAINGING DATA FOR PARAM: " + p.loc);
			// int val = masked_short(bb);
			//
			// System.out.println(" val=" + val);
			//
			// System.out.println(" after=" + bb.remaining());
			// if (val != 32767) {
			// block.setNumericValue(p.loc, val);
			// }
			// } else {
			if (p.val_count == 3) {
				// NPB...not a measured value struct
			} else {
				for (int i = 0; i < p.val_count; i++) {
					if (bb.remaining() < 2) {
						log.error("UNDERFLOW in param: {} of {} loc=" + p.loc, i, p.val_count);
						break;
					}
					// dump(System.out, bb.array(), bb.limit());

					int val = masked_short(bb); // was measured_short!
					if (val != 32767) {
						log.debug("parsing: {}  polled: {}", p.loc, poll_req.length);
						IntfUtil.setValue(block, p.loc, val);
					}
				}
			}
			// }
		}

		if (vvvv >= 32) {
			vvvv = 0;

			block.setTime(System.currentTimeMillis());
			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
			block = ModelUtil.getModelFromDataClass(measClass);
		} else {
			vvvv++;
		}

	}

	private ParamDetails findParam(byte b) {

		if (b >= 0 && b < details.length) {
			return details[b];
		}
		return null;
	}

	private void buildCapabilities() throws Exception {
		cap = new DeviceCapabilities(this.getClass());

		RpMetric wfMetrics[] = new RpMetric[wave_details.length];

		int i = 0;
		for (WaveDetails d : wave_details) {
			// wfMetrics[i++] = fix_metric(d.w);
			log.error("Create WFDES from wave_details");
			wfMetrics[i++] = d.w;
		}
		wfClass = ModelUtil.createDynamicModel("VueLink" + model_idx, Arrays.asList(wfMetrics));
		model_idx++;

		// ?
		// for (RpMetric m : pp_hm.values()) {
		// fix_metric(m);
		// }
		measClass = ModelUtil.createDynamicModel("VueLink" + model_idx, pp_hm.values());
		model_idx++;

	}

	private void parseSpecResp(ByteBuffer bb) {

		while (bb.hasRemaining()) {
			int unk1 = bb.getShort();
			if (bb.remaining() == 0) {
				break;
			}
			int unk2 = bb.getShort();

			int start = bb.position();

			int len = unsigned_short(bb);
			int id = unsigned_short(bb);
			switch (id) {
			case 0:
				parseSection00(bb);
				break;
			case 0x11:
				parseWaveformInfoSection11(bb);
				break;
			case 0x12:
				parseSection12(bb);
				break;
			case 0x10:
				parseDisplaySection10(bb);
				break;
			case 0x14:
				parseMessageSection14(bb);
				break;
			case 0x15:
				parseUnitsSection15(bb);
				break;
			case 0x16:
				parseCodeSection16(bb);
				break;
			case 0x18:
				parseSection18(bb);
				break;
			case 0x19:
				parseIdentitySection19(bb);
				break;
			case 0x80:
				parseSection80(bb);
				break;
			default:
				log.error("unknown section: {}", id);
			}

			int end = start + len + 2;
			if (bb.position() != end) {
				log.error("INVALID POSITION section=" + Integer.toHexString(id) + " expected={} got={}", end,
						bb.position());
				bb.position(end);
			}
		}
	}

	private void parseSection00(ByteBuffer bb) {
		byte[] dst = new byte[20];
		bb.get(dst);

	}

	private void parseDisplaySection10(ByteBuffer bb) {
		pp_hm = new HashMap<String, RpMetric>();

		int count = unsigned_short(bb);
		details = new ParamDetails[count + 1];
		int idx = 0;
		details[idx++] = null; // this is the Status message
		while (count-- > 0) {
			ParamDetails detail = new ParamDetails();
			details[idx++] = detail;
			byte o1 = bb.get();
			detail.seq = bb.get();
			detail.param_group = unsigned_short(bb);
			detail.param_id = unsigned_short(bb);
			detail.unit_id = unsigned_short(bb);
			detail.unk_trq = unsigned_short(bb); // NBP=05 or else=01
			detail.unk_ffff = unsigned_short(bb); // all entries were ffff
			detail.unk_b = bb.get(); // // hex values 01, 21, 31, 51
			detail.val_count = bb.get(); // number of values returned

			for (int j = 0; j < 2; j++) {
				unsigned_short(bb);
			}

			detail.unk_c = bb.get();
			detail.mult = bb.get(); // unit multiplier

			for (int j = 0; j < 3; j++) {
				unsigned_short(bb);
			}

			RpPrecisionUnit su = new RpPrecisionUnit(detail.mult, "" + detail.unit_id);
			detail.loc = "0x" + Integer.toHexString(detail.param_id);

			detail.m = new RpMetric(detail.loc, null, null, su, DataTyp.INT_TYP);
			pp_hm.put(detail.loc, detail.m);

			log.debug("group={} param=0x{} unit=" + detail.unit_id, detail.param_group,
					Integer.toHexString(detail.param_id));
		}
	}

	private void parseWaveformInfoSection11(ByteBuffer bb) {
		int count = unsigned_short(bb);

		wave_details = new WaveDetails[count];
		int idx = 0;
		while (count-- > 0) {
			WaveDetails wd = new WaveDetails();
			wd.param_id = unsigned_short(bb);
			wd.pkt_pts = 4;
			wd.unit_id = unsigned_short(bb);

			byte[] dst = new byte[30];
			bb.get(dst);

			wd.loc = "0x" + Integer.toHexString(wd.param_id);
			RpPrecisionUnit u = new RpPrecisionUnit(0, "" + wd.unit_id);
			RpMetric wf = new RpMetric(wd.loc, null, null, u, DataTyp.INT_ARR_TYP);
			wd.w = wf;

			wave_details[idx++] = wd;

			log.debug("waveform: param={} unit={}", wd.loc, wd.unit_id);
		}
	}

	private void parseSection12(ByteBuffer bb) {
		int count = unsigned_short(bb);
		byte[] dst = new byte[38];
		while (count-- > 0) {
			bb.get(dst);
		}
	}

	private void parseMessageSection14(ByteBuffer bb) {
		int count = unsigned_short(bb);
		while (count-- > 0) {
			int message_id = unsigned_short(bb);
			String message = fixed_2byte_string(bb, 19);
			log.debug("message id={} message={}", message_id, message);
			bb.getShort();
			bb.getShort();
		}
	}

	private void parseUnitsSection15(ByteBuffer bb) {
		int count = unsigned_short(bb);

		unit_hm = new HashMap<Integer, RpLinearUnit>();
		while (count-- > 0) {
			int unit_id = unsigned_short(bb);
			String name = fixed_2byte_string(bb, 19).trim();

			RpLinearUnit unit = new RpLinearUnit(1.0, 0.0, name);
			unit_hm.put(unit_id, unit);

			log.debug("unit id={} name={}", unit_id, name);
		}
	}

	private void parseCodeSection16(ByteBuffer bb) {
		code_hm = new HashMap<String, String>();

		int count = unsigned_short(bb);
		while (count-- > 0) {
			int param_id = unsigned_short(bb);
			String name = fixed_2byte_string(bb, 7).trim();

			code_hm.put("0x" + Integer.toHexString(param_id), name);

			log.debug("id=0x{} name={}", Integer.toHexString(param_id), name);
		}
	}

	private void parseSection18(ByteBuffer bb) {
		int count = unsigned_short(bb);
		byte[] dst = new byte[4];
		while (count-- > 0) {
			bb.get(dst);
		}
	}

	private void parseIdentitySection19(ByteBuffer bb) {
		String deviceName = fixed_2byte_string(bb, 20).trim();
		String softkey_1 = fixed_2byte_string(bb, 9).trim();
		String softkey_2 = fixed_2byte_string(bb, 9).trim();
		String u1 = fixed_2byte_string(bb, 9);
		String u2 = fixed_2byte_string(bb, 9);
		String vuelinkType = fixed_2byte_string(bb, 25);
		String m99 = fixed_2byte_string(bb, 25);
		String u3 = fixed_2byte_string(bb, 21);

		short ushort = bb.getShort();

		log.info("Device Name\t:\t\"{}\"", deviceName);
		log.info("VueLink Type\t:\t\"{}\"", vuelinkType);
		log.info("Softkey Labels\t:\t\"{}\" / \"{}\"", softkey_1, softkey_2);
		log.info("m99: " + m99);
	}

	private void parseSection80(ByteBuffer bb) {
		int count = unsigned_short(bb);
		byte[] dst = new byte[2];
		while (count-- > 0) {
			bb.get(dst);
		}
	}

	private int unsigned_short(ByteBuffer bb) {
		int s = bb.getShort();
		if (s < 0) {
			s += 65536;
		}
		return s;
	}

	private int masked_short(ByteBuffer bb) {
		int s = bb.getShort();
		return s;
	}

	private int measured_short(ByteBuffer bb) {
		int pos = bb.position();
		int aper = unsigned_byt(bb.get());
		int inop = unsigned_byt(bb.get());
		int alarm = unsigned_byt(bb.get());

		int mantissa = bb.getShort();
		if (mantissa < 0) {
			mantissa += 65536;
		}
		// int v = 0x7ff & s;
		// int p = s >> 11;
		// System.out.print(" " + v + "/" + p);
		// while( p > 0 ) {
		// v *= 10;
		// p--;
		// }
		return mantissa;
	}

	private String fixed_2byte_string(ByteBuffer bb, int count) {

		StringBuffer buf = new StringBuffer();
		do {
			char byt = (char) bb.getShort();
			count--;
			if (byt < 0) {
				log.error("unprintable char in string?");
			}
			if (byt == 0) {
				break;
			}
			buf.append(byt);
		} while (bb.hasRemaining() && count > 0);

		while (count > 0) {
			bb.get();
			count--;
		}
		return buf.toString();
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, cap);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	public void requestSpec() throws IOException {
		sendTelegram(TT_SPEC_REQUEST, VUELINK_ID);
	}

	public void requestStatus() throws IOException {
		sendTelegram(TT_DATA_REQUEST, status_req);
	}

	private void requestNext() throws IOException {

		req_index++;
		if (req_index > 27) {
			req_index = 0;

			if (with_waves == false) {
				buildTransferRequest();
				with_waves = true;
			}
		}
		poll_req[0] = (byte) req_index;
		sendTelegram(TT_DATA_REQUEST, poll_req);
	}

	public void buildTransferRequest() throws IOException {
		if (conf == null) {
			return;
		}

		poll_req = null;

		// MetricDescription[] metrics = conf.getMetrics();
		RpStream s = IntfUtil.getStream(conf, StreamID.WAVEFORM);
		List<RpMetric> waves = s.getMetric();
		// waves = null; // WAVES DISABLED!!!

		int wave_count = 0;
		if (waves != null)
			wave_count += waves.size();

		poll_req = new byte[wave_count + 1];
		if (wave_count > 0) {
			int idx = 1;
			// if (metrics != null) {
			// for (MetricDescription m : metrics) {
			// cached_config[idx++] = (byte) Integer.parseInt(
			// m.getLocation(), 16);
			// }
			// }
			byte wave_id = 1;
			if (waves != null) {
				for (RpMetric m : waves) {
					poll_req[idx++] = wave_id++; // (byte)
													// Integer.parseInt(m.getLocation(),
													// 16);
				}
			}
		}

	}

	@Override
	public int tick() {
		try {
			return _tick();
		} catch (IOException e) {
			log.error("tick", e);
		}
		return -1;
	}

	public int _tick() throws IOException {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick >= 8) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
				fireNoData(conf);
			}
			if (tick % 8 == 0) {
				requestSpec();
			}
		} else if (tick > 5) {
			// requestDataTransfer();
			requestStatus();
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		return 0;
	}

	public void reset() {
		tick = 0;
		mb_offset = 0;
		pkt_len = 0;

		for (WaveDetails w : wave_details) {
			w.wave_pt = 0;
		}
	}

}
