package icuInterface.adapters;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import com.fazecast.jSerialComm.SerialPort;

import icuInterface.CRCUtil;
import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.AesculonBeat;
import idea.model.dev.AesculonMeasurement;
import idea.model.dev.AesculonWaveform;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

// 5306+AKPYSO
//

@Slf4j
public class AesculonDriver extends SerialAdapter implements AdapterInterface {

	@SuppressWarnings("unused")
	private static final String driverName = "monitor/Osypka Aesculon - Serial";

	private long last_lm_ms;

	public static final short MSG_SET_PARAM_CONFIG = 0x7000;
	private static final short MSG_PARAM_EXPORT_JOB = 0x7004;
	private static final short MSG_PARAM_VALUES = 0x7010;
	private static final short MSG_PARAM_RANGE_REQ = 0x7020;
	private static final short MSG_PARAM_RANGES = 0x7021;

	private static final short MSG_SET_WAVEFORM_CONFIG = 0x7080;
	private static final short MSG_WAVEFORM_EXPORT_JOB = 0x7084;
	private static final short MSG_WAVEFORM_VALUES = 0x7090;
	private static final short MSG_HC_LANDMARK_VALUES = 0x7100;

	private static final short MSG_PATIENT_DATA_REQ = (short) 0x8001;
	private static final short MSG_PATIENT_DATA_RESULT = (short) 0x8002;
	public static final short MSG_PROTOCOL_VER_REQ = (short) 0x9000;
	private static final short MSG_PROTOCOL_VER_RESULT = (short) 0x9001;

	private static final short PARAM_HR = 0x2000;
	private static final short PARAM_SBP = 0x3000;
	private static final short PARAM_DBP = 0x3001;
	private static final short PARAM_MAP = 0x3002;

	private static final short PD_SBP = 0x0001; // SBP mmHg 4 bytes float
												// Systolic Blood Pressure
	private static final short PD_DBP = 0x0002; // DBP mmHg 4 bytes float
												// Diastolic Blood Pressure
	private static final short PD_MBP = 0x0003; // MBP mmHg 4 bytes float Mean
												// Blood Pressure
	private static final short PD_SPO2 = 0x0010; // SpO2 % 4 bytes float Oxygen
													// Saturation
	private static final short PD_Hb = 0x0020; // Hb g/dL 4 bytes float
												// Hemoglobin Concentration

	private final static byte STX = (byte) 0xff;
	private final static byte MTX = (byte) 0xfd;
	private final static byte ETX = (byte) 0xfe;

	private static final int CRC_SEED = 0;
	private static final short PARAM_JOB_ID = 21;
	private static final short WAVEFORM_JOB_ID = 22;
	private static final short PATIENT_DATA_JOB_ID = 3;

	private byte[] mb_buffer = new byte[2048]; // 1024 worked for a long
												// time...then I got an oob
												// exception !?!
	private int mb_offset = 0;

	private static DeviceCapabilities cap;

	private int tick_vitals;
	private int tick_sensors;

	List<? extends RpMetric> req_metrics;
	List<? extends RpMetric> req_waves;

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(AesculonDriver.class);
		// conf.setMetrics(cap.getMetrics());

		return conf;
	}

	static {
		cap = new DeviceCapabilities(AesculonDriver.class);

		cap.addStream(StreamID.MEASUREMENT, AesculonMeasurement.class);
		cap.addStream(StreamID.WAVEFORM, AesculonWaveform.class);

		cap.setModels(new String[] { "Aesculon" });

		cap.addConnection(new SerialConnection(115200, 8, 1, 0));

	}

	public AesculonDriver(RpDevice conf) {
		super(conf);

		if (conf != null) {
			AdapterUtil.fix_config(cap, conf);

			// FIXME: this gets all waves and metrics...maybe ok
			req_metrics = RpUtil.getMetrics(conf, StreamID.MEASUREMENT);
			req_waves = RpUtil.getMetrics(conf, StreamID.WAVEFORM);
		}

		setStatus(ConnectionStatus.NOT_CONNECTED);
	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		log.info(" --> Aesculon {}", portName);

		setStatus(NEGOTIATING);
		connect(portName, 115200, 8, 1, 0);

	}

	// communication resets..due to comm errors
	public void reset() {
		mb_offset = 0;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return cap;
	}

	@Override
	public void process(InputStream in, OutputStream os) throws IOException {
		while (in.available() > 0) {
			int byt = in.read();
			if (byt == -1) {
				break;
			}
			process(byt);
		}
	}

	public void process(int byt) {

		if (byt == STX || mb_offset > mb_buffer.length - 10) {
			mb_offset = 0;
		}

		mb_buffer[mb_offset++] = (byte) byt;

		if ((byte) byt == ETX) {
			processResponse(mb_buffer, mb_offset);
			mb_offset = 0;
		}

	}

	private void processResponse(byte[] buf, int len) {
		if (log.isDebugEnabled()) {
			System.out.println("\nRESP:");
			dump(System.out, buf, len);
		}
		/*
		 * reconstruct the most significant bit
		 */
		int mtx_pos = 0;
		for (int i = 0; i < len; i++) {
			if (buf[i] == MTX)
				mtx_pos = i;
		}
		if (mtx_pos == 0) {
			log.error("EXPECTING MTX");
			dump(System.out, buf, len);
			return;
		}

		int bit7_byte = mtx_pos + 1;
		int bit7_bit = 6;
		for (int i = 1; i < mtx_pos; i++) {
			byte bit7 = buf[bit7_byte];
			int mask = 1 << bit7_bit;
			int flag = bit7 & mask;
			if (flag != 0) {
				buf[i] += 128;
			}
			if (bit7_bit == 0) {
				bit7_bit = 6;
				bit7_byte++;
			} else {
				bit7_bit--;
			}
		}

		ByteBuffer bb = ByteBuffer.wrap(buf, 0, mtx_pos);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		byte stx = bb.get(); // stx
		if (stx != STX) {
			log.warn("ignoring message / no STX");
			return;
		}
		short mc = bb.getShort();

		switch (mc) {
		case MSG_PARAM_VALUES:
			processParams(bb);
			break;
		case MSG_PROTOCOL_VER_RESULT:
			processProtocolVerResult(bb);
			break;
		case MSG_PATIENT_DATA_RESULT:
			processPatientDataResult(bb);
			break;
		case MSG_PARAM_RANGES:
		case MSG_WAVEFORM_VALUES:
			processWaveformValues(bb);
			break;
		case MSG_HC_LANDMARK_VALUES:
			processLandmark(bb);
			break;
		case MSG_PATIENT_DATA_REQ:
		default:
			log.error("Unknown message code: {}", mc);
			break;
		}

		return;
	}

	private void processLandmark(ByteBuffer bb) {
		int len = bb.getShort();
		int msgcnt = bb.getShort();
		int wjobid = bb.getShort();
		int lm_dt = bb.getInt();
		int lm_tm = bb.getInt();
		short step_cd = bb.getShort();
		int unk = bb.getShort();
		int resvd1 = bb.getInt();
		int resvd2 = bb.getInt();
		int r_splcnt = bb.getInt();
		int q_splncnt = bb.getInt();
		int c_splcnt = bb.getInt();
		int b_splcnt = bb.getInt();
		int x_splcnt = bb.getInt();
		int xp_splcnt = bb.getInt();
		// WARNING: CRC causes buffer underflow....where is CRC?
		// int crc = bb.getShort();

		if (r_splcnt != -1) {
			long lm_ms = decodeDateTime(lm_dt, lm_tm);

			long ms_ivl = lm_ms - last_lm_ms;
			last_lm_ms = lm_ms;
			if (ms_ivl < 100000) {
				AesculonBeat ab = new AesculonBeat();
				ab.setTm(new Date(lm_ms));
				ab.setMs_interval((int) ms_ivl);
				// fireStreamEvent(0,this,StreamID.MEASUREMENT, 0, StreamID.RRI,
				// ab);
			}
		}

	}

	private void processPatientDataResult(ByteBuffer bb) {
		int len = bb.getShort();
		int pdid = bb.getShort();
		int rescd = bb.getShort();
		int resvd1 = bb.getInt();
		int resvd2 = bb.getInt();
		int crc = bb.getShort();

		String message = "[UNKNOWN CODE]";
		switch (rescd) {
		case 0x0000:
			message = "success";
			break;
		case 0x1000:
			message = "Unknown Error";
			break;
		case 0x2000:
			message = "Too many incoming messages";
			break;
		case 0x2010:
			message = "Update rate too high";
			break;
		case 0x2020:
			message = "Not ready to receive data of the patient data";
			break;
		case 0x2021:
			message = "Not ready / not running";
			break;
		}
		log.debug("processPatientDataResult : {}", message);
	}

	private void processProtocolVerResult(ByteBuffer bb) {
		int len = bb.getShort();
		int major = bb.getShort();
		int minor = bb.getShort();
		int build = bb.getShort();
		int devcd = bb.getShort();
		int resvd1 = bb.getInt();
		int resvd2 = bb.getInt();
		int crc = bb.getShort();

		System.out.print("  --> protocol verison: " + major);
		System.out.print("." + minor);
		System.out.print("." + build);
		System.out.print(" dev: " + devcd);
		System.out.print(" rsv1 = " + Integer.toHexString(resvd1));
		System.out.print(" rsv2 = " + Integer.toHexString(resvd2));
		System.out.print(" crc = " + Integer.toHexString(crc));
		System.out.println();

	}

	private void processParams(ByteBuffer bb) {

		if (req_metrics == null) {
			return;
		}

		AesculonMeasurement block = new AesculonMeasurement();

		int len = bb.getShort();
		int msgcnt = bb.getShort();
		int pjobid = bb.getShort();
		int resvd1 = bb.getInt();
		int resvd2 = bb.getInt();

		int mfsiz = bb.getShort();
		int mfcnt = bb.getShort();

		for (RpMetric m : req_metrics) {
			mfcnt--;
			if (mfcnt < 0)
				break;

			float raw = bb.getFloat();

			RpUnit unit = m.getUnit();

			int v = (int) unit.inverse(raw + 0.5);
			IntfUtil.setValue(block, m, v);
		}

		int crc = bb.getShort();

		// log.debug("Sending numeric event.");\
		tick_vitals = 0;
		fireStreamEvent(0, this, StreamID.MEASUREMENT, block);

	}

	private void processWaveformValues(ByteBuffer bb) {

		if (req_waves == null) {
			return;
		}

		AesculonWaveform block = new AesculonWaveform();

		int len = bb.getShort();
		short jobID = bb.getShort();
		int dt = bb.getInt();
		int tm = bb.getInt();
		short step_cd = bb.getShort();
		int spl_counter = bb.getShort(); // sample counter
		int unk = bb.getShort();
		int resvd1 = bb.getInt();
		int resvd2 = bb.getInt();

		if (req_waves == null) {
			log.error("Aesculon: unsolicited waveform");
			return;
		}

		for (RpMetric m : req_waves) {
			if (bb.remaining() < 4) {
				log.error("no wave values?");
				break;
			}
			String loc = m.getLocation();

			// int offset = bb.position();
			int mfsiz = bb.getShort();
			int mfcnt = bb.getShort();

			int[] wave_data = (int[]) IntfUtil.getRawValueByLoc(block, loc);
			if (wave_data == null) {
				wave_data = new int[mfcnt];
				IntfUtil.setValue(block, loc, wave_data);
			}
			if (mfcnt > bb.remaining() / 2) {
				log.error("buffer does not have enough wf values: {} != {}", mfcnt, bb.remaining() / 2);
				mfcnt = bb.remaining() / 2;
			}
			for (int idx = 0; idx < mfcnt; idx++) {
				int w = bb.getShort();
				wave_data[idx] = w;
			}
		}

		if (bb.remaining() < 2) {
			log.error("missing CRC");
		} else {
			int crc = bb.getShort();
		}
		// this.dump(System.out, bb.array(), bb.limit());
		fireStreamEvent(0, this, StreamID.WAVEFORM, block);

		tick_sensors = 0;
	}

	public static void dump(PrintStream out, byte[] array, int len) {
		out.print("  ");
		for (int i = 0; i < len; i++) {
			if ((i > 0) && (i % 16 == 0)) {
				out.println();
				out.print("  ");
			}

			// if ((i > 0) && (i % 32 == 0)) {
			// out.println();
			// out.print(" ");
			// }

			int byt = array[i];
			if (byt < 0)
				byt += 256;
			if (byt < 16) {
				out.print("0");
			}
			out.print(Integer.toHexString(byt));
			out.print(" ");
		}

		out.println();

	}

	public void sendProtocolVersionRequest() throws IOException {
		short len = 8;
		ByteBuffer bb = ByteBuffer.allocate(len + 6);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		bb.putShort(MSG_PROTOCOL_VER_REQ);
		bb.putShort(len);
		bb.putInt(-1); // RESVD1
		bb.putInt(-1); // RESVD2

		int crc = CRCUtil.getCRC16Aesculon(bb.array(), bb.position(), CRC_SEED);
		bb.putShort((short) crc);

		sendPacket(bb.array());
	}

	// make calling easier from script
	public void sendPatientData(Date date, double sbp, double dbp, double mbp) throws IOException {
		sendPatientData(date, (float) sbp, (float) dbp, (float) mbp);
	}

	public void sendPatientData(Date date, Integer sbp, Integer dbp, Integer mbp) throws IOException {
		sendPatientData(date, (float) sbp, (float) dbp, (float) mbp);
	}

	public void sendPatientData(Date date, float sbp, float dbp, float mbp) throws IOException {
		short mfsiz = 0;
		short mfcnt = 0;
		short vdsiz = 0;

		short mtype = 0x0001;
		short pdid = PATIENT_DATA_JOB_ID; // patient data ID

		vdsiz = 4;

		mfcnt = 3;
		mfsiz = (short) (mfcnt * (2 + 2 + vdsiz));

		short len = (short) (24 + mfsiz);
		ByteBuffer bb = ByteBuffer.allocate(len + 4 + 2);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		bb.putShort(MSG_PATIENT_DATA_REQ);
		bb.putShort(len);
		bb.putShort(mtype);
		bb.putShort(pdid);

		encodeDate(bb, date);
		encodeTime(bb, date);
		// bb.putInt(-1); // DATE
		// bb.putInt(-1); // TIME

		bb.putInt(-1); // RESVD1
		bb.putInt(-1); // RESVD2

		bb.putShort(mfsiz);
		bb.putShort(mfcnt);

		bb.putShort(vdsiz);
		bb.putShort(PD_SBP);
		bb.putFloat(sbp);

		bb.putShort(vdsiz);
		bb.putShort(PD_DBP);
		bb.putFloat(dbp);

		bb.putShort(vdsiz);
		bb.putShort(PD_MBP);
		bb.putFloat(mbp);

		int crc = CRCUtil.getCRC16Aesculon(bb.array(), bb.position(), CRC_SEED);
		bb.putShort((short) crc);

		System.out.println("sending blood pressure: " + sbp + "/" + mbp + "/" + dbp);
		sendPacket(bb.array());
	}

	private void encodeTime(ByteBuffer bb, Date date) {
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		bb.put((byte) cal.get(Calendar.HOUR_OF_DAY));
		bb.put((byte) cal.get(Calendar.MINUTE));
		bb.put((byte) cal.get(Calendar.SECOND));
		bb.put((byte) 0);
	}

	private void encodeDate(ByteBuffer bb, Date date) {
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		bb.putShort((short) cal.get(Calendar.YEAR));
		bb.put((byte) cal.get(Calendar.MONTH));
		bb.put((byte) cal.get(Calendar.DAY_OF_MONTH));
	}

	private long decodeDateTime(int aesculonDt, int aesculonTm) {
		Calendar cal = Calendar.getInstance();
		cal.set(Calendar.YEAR, 0xffff & aesculonDt);
		cal.set(Calendar.MONTH, ((aesculonDt & 0xff0000) >> 16) - 1);
		cal.set(Calendar.DAY_OF_MONTH, (aesculonDt >> 24));
		int sec = (aesculonTm >> 16) & 0xff;
		int milli = (aesculonTm >> 24);

		if (sec >= 60) {
			log.error("BAD SECOND: " + sec);
		}
		if (milli >= 100) {
			log.error("BAD MILLI: " + milli);
		}
		cal.set(Calendar.SECOND, sec);
		cal.set(Calendar.MINUTE, ((aesculonTm & 0xff00) >> 8));
		cal.set(Calendar.HOUR_OF_DAY, (aesculonTm & 0xff) + 1);
		cal.set(Calendar.MILLISECOND, 10 * milli);

		return cal.getTimeInMillis();
	}

	public void sendClinicalParameterConfiguration() throws IOException {
		log.debug("sending clinical config");
		short mfsiz = 0;
		short mfcnt = 0;

		mfcnt = 0;
		if (req_metrics != null) {
			mfcnt = (short) req_metrics.size();
		}
		mfsiz = (short) (mfcnt * 2);

		ByteBuffer bb = ByteBuffer.allocate(5 + 12 + mfsiz + 2 - 1);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		bb.putShort(MSG_SET_PARAM_CONFIG);
		bb.putShort((short) (12 + mfsiz));
		bb.putInt(-1); // RESVD1
		bb.putInt(-1); // RESVD2
		bb.putShort(mfsiz); // Multiple Field Block Size
		bb.putShort(mfcnt); // PRMCD

		if (req_metrics != null) {
			for (RpMetric m : req_metrics) {
				String loc = m.getLocation();
				short sloc = (short) Integer.parseInt(loc, 16);
				bb.putShort(sloc);
			}
		}

		int crc = CRCUtil.getCRC16Aesculon(bb.array(), bb.position(), CRC_SEED);
		bb.putShort((short) crc);

		sendPacket(bb.array());

	}

	public void sendWaveformConfiguration() throws IOException {
		if (req_waves == null) {
			return;
		}
		log.debug("sending waveform configuration: {}", req_waves);
		short mfsiz = 0;
		short mfcnt = 0;

		mfcnt = (short) req_waves.size();
		mfsiz = (short) (mfcnt * 2);

		ByteBuffer bb = ByteBuffer.allocate(4 + 18 + mfsiz + 2);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		bb.putShort(MSG_SET_WAVEFORM_CONFIG);
		bb.putShort((short) (18 + mfsiz));
		bb.putShort((short) 0x0001); // send the RRI landmarks
		bb.putFloat(0.25f); // send a burst every 0.25 second, must be in range
							// 0.05 to 0.25
		bb.putInt(-1); // RESVD1
		bb.putInt(-1); // RESVD2
		bb.putShort(mfsiz); // Multiple Field Block Size
		bb.putShort(mfcnt); // PRMCD

		for (RpMetric m : req_waves) {
			String loc = m.getLocation();
			short sloc = (short) Integer.parseInt(loc, 16);
			bb.putShort(sloc);
		}

		int crc = CRCUtil.getCRC16Aesculon(bb.array(), bb.position(), CRC_SEED);
		bb.putShort((short) crc);

		sendPacket(bb.array());
	}

	public void sendClinicalParameterExportJob() throws IOException {
		sendClinicalParameterExportJob((short) 0x0080, (short) 1, (short) 0);
	}

	public void sendWaveformExportJob() throws IOException {

		if (req_waves == null) {
			return;
		}
		log.debug("sending waveform export job id={}", WAVEFORM_JOB_ID);
		ByteBuffer bb = ByteBuffer.allocate(4 + 12 + 2);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		short TMCD = (short) 0x0001;

		bb.putShort(MSG_WAVEFORM_EXPORT_JOB);
		bb.putShort((short) 12); // length
		bb.putShort(WAVEFORM_JOB_ID);
		// bb.putShort( (short) 0x0001 ); // TMCD...send one immediate
		bb.putShort(TMCD); // TMCD...send periodic
		bb.putInt(-1); // RESVD1
		bb.putInt(-1); // RESVD2

		int crc = CRCUtil.getCRC16Aesculon(bb.array(), bb.position(), CRC_SEED);
		bb.putShort((short) crc);

		sendPacket(bb.array());
	}

	public void sendClinicalParameterExportJob(short TMCD, float ARG1, float ARG2) throws IOException {
		log.debug("sending clinical export job request: TMCD {} ARG1={}", TMCD, ARG1);
		ByteBuffer bb = ByteBuffer.allocate(4 + 20 + 2);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		bb.putShort(MSG_PARAM_EXPORT_JOB);
		bb.putShort((short) 20); // length
		bb.putShort(PARAM_JOB_ID);
		// bb.putShort( (short) 0x0001 ); // TMCD...send one immediate
		bb.putShort(TMCD); // TMCD...send periodic
		bb.putFloat(ARG1); // once/second
		bb.putFloat(ARG2);
		bb.putInt(-1); // RESVD1
		bb.putInt(-1); // RESVD2

		int crc = CRCUtil.getCRC16Aesculon(bb.array(), bb.position(), CRC_SEED);
		bb.putShort((short) crc);

		sendPacket(bb.array());
	}

	private void sendPacket(byte[] data) throws IOException {

		OutputStream out = getOutputStream();
		// port = hw_port;
		if (out == null) {
			return; // probably tick called before we are ready
		}

		if (log.isDebugEnabled()) {
			int len = data.length;
			ByteArrayOutputStream bout = new ByteArrayOutputStream(len);
			dump(System.out, data, len);
		}

		ByteArrayOutputStream bout = new ByteArrayOutputStream(256);
		byte[] bytes;
		synchronized (out) {
			int n = AesculonDriver.encode(bout, data, data.length);
			// encode(out, data);
			bytes = bout.toByteArray();
			out.write(bytes, 0, n);

			// if (log.isTraceEnabled()) {
			// System.out.println("encoded[" + bout.size() + "]:");
			// dump(System.out, bout.toByteArray(), n);
			// System.out.println();
			// }
		}

	}

	public static int encode(OutputStream out, byte[] data, int len) throws IOException {
		byte[] upperBits = new byte[(len + 6) / 7];
		int bitpos = 7;
		int bitbyte = 0;

		int n = 0;

		out.write(STX);
		n++;
		for (int i = 0; i < len; i++) {
			bitpos--;

			byte ch = data[i];
			if (ch < 0) {
				ch += 128;
				upperBits[bitbyte] |= 1 << bitpos;
			}
			out.write(ch);
			n++;

			if (bitpos == 0) {
				bitbyte++;
				bitpos = 7;
			}

		}
		out.write(MTX);
		n++;
		out.write(upperBits);
		n += upperBits.length;
		out.write(ETX);
		n++;

		return n;
	}

	@Override
	public void setPort(SerialPort port) {
		super.setPort(port);
		tick_vitals = 10;

	}

	@Override
	public int tick() {
		tick_vitals++;
		tick_sensors++;

		OutputStream out = getOutputStream();
		if (out == null) {
			log.error("device not connected");
			return -1;
		}

		/*
		 * handle config and request for vitals data
		 */
		ConnectionStatus deviceState = getStatus();
		if (tick_vitals > 10) {

			// form 10 to 19, deviceState can be NEGOCIATING
			if (tick_vitals >= 20) {
				ConnectionStatus req_state = (tick_sensors < 5) ? ConnectionStatus.NEGOTIATING : NOT_CONNECTED;
				if (deviceState != req_state) {
					setStatus(req_state);
					fireNoData(conf);
				}
				tick_vitals = 10;
			}

			if (tick_vitals == 12) {
				try {
					sendClinicalParameterConfiguration();
				} catch (IOException e) {
					log.error("tick", e);
				}
			}
			if (tick_vitals == 13) {
				try {
					sendClinicalParameterExportJob();
				} catch (IOException e) {
					log.error("tick", e);
				}
			}

		} else {
			if (deviceState != CONNECTED && (tick_vitals < 10)) {
				setStatus(CONNECTED);
			}
		}

		/*
		 * handle config and request for sensor data
		 */
		if (tick_sensors > 10) {
			if (tick_sensors >= 20) {
				tick_sensors = 10;
			}

			if (tick_sensors == 12) {
				try {
					sendWaveformConfiguration();
					sendWaveformExportJob();
				} catch (IOException e) {
					log.error("tick", e);
				}
			}
		}
		return 0;
	}

}
