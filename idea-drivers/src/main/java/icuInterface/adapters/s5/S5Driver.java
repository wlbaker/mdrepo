package icuInterface.adapters.s5;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Date;
import java.util.List;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.SerialConnection;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class S5Driver extends SerialAdapter implements StreamProducer, AdapterInterface {
	private static final String driverName = "monitor/GE S5";

	private wf_group wf;

	private final static byte PKT_START = 0x7e;
	private final static byte PKT_END = 0x7e;
	private static final byte ESCAPE_CODE = 0x7d;

	public static final int DATEX_HEADER_SIZE = 40;
	public static final int DATEX_PHDBREQ_SIZE = 9;
	public static final int DATEX_WAVEREQ_SIZE = 48;
	public static final int DATEX_ANY_SIZE = 512;
	public static final short DRI_PH_DISPL = 0xff;

	private static final int DRI_PHDB_SIZE = 278;

	public static final short DRI_MT_PHDB = 0;
	public static final short DRI_MT_WAVE = 1;
	public static final short DRI_MT_ALARM = 4; // network only
	public static final short DRI_MT_FO = 8; // network only

	public static final short WF_REQ_CONT_START = 0;
	public static final short WF_REQ_CONT_STOP = 1;

	private static final byte DRI_WF_CMD = 0;
	private static final byte DRI_WF_ECG1 = 1;
	private static final byte DRI_WF_ECG2 = 2;
	private static final byte DRI_WF_ECG3 = 3;
	private static final byte DRI_WF_INVP1 = 4;
	private static final byte DRI_WF_INVP2 = 5;
	private static final byte DRI_WF_INVP3 = 6;
	private static final byte DRI_WF_INVP4 = 7;
	private static final byte DRI_WF_PLETH = 8;
	private static final byte DRI_WF_CO2 = 9;
	private static final byte DRI_WF_O2 = 10;
	private static final byte DRI_WF_NO2 = 11;
	private static final byte DRI_WF_AA = 12;
	private static final byte DRI_WF_AWP = 13;
	private static final byte DRI_WF_FLOW = 14;
	private static final byte DRI_WF_RESP = 15;
	private static final byte DRI_WF_INVP5 = 16;
	private static final byte DRI_WF_INVP6 = 17;
	private static final byte DRI_WF_EEG1 = 18;
	private static final byte DRI_WF_EEG2 = 19;
	private static final byte DRI_WF_EEG3 = 20;
	private static final byte DRI_WF_EEG4 = 21;
	// no 22
	private static final byte DRI_WF_VOL = 23;
	private static final byte DRI_WF_TONO_PRESS = 24;
	// no 25,26,27,28
	private static final byte DRI_WF_SPI_LOOP_STATUS = 29;
	// no 30,31
	private static final byte DRI_WF_ENT_100 = 32;
	// no 33,34
	private static final byte DRI_WF_EEG_BIS = 35;

	// ...there are more
	private static final byte DRI_EOL_SUBR_LIST = (byte) 0xff;

	private static final byte DRI_PH_DSPL = 1;
	private static final byte DRI_PH_10S_TREND = 2;
	private static final byte DRI_PH_60S_TREND = 3;

	private static final int DRI_PHDBCL_REQ_BASIC_MASK = 0;
	private static final int DRI_PHDBCL_DENY_BASIC_MASK = 0x01;
	private static final int DRI_PHDBCL_REQ_EXT1_MASK = 0x02;
	private static final int DRI_PHDBCL_REQ_EXT2_MASK = 0x04;
	private static final int DRI_PHDBCL_REQ_EXT3_MASK = 0x08;

	private static final short DRI_PHDBCL_BASIC = 0;
	private static final short DRI_PHDBCL_EXT1 = 1;
	private static final short DRI_PHDBCL_EXT2 = 2;
	private static final short DRI_PHDBCL_EXT3 = 3;

	private static final byte DRI_LEVEL_00 = 6;
	private static final byte DRI_LEVEL_01 = 7;
	private static final byte DRI_LEVEL_02 = 8;

	private byte[] mb_buffer = new byte[1024];
	private int mb_offset = 0;

	private static DeviceCapabilities cap;

	ByteBuffer pkt;
	ByteBuffer bbHdr;

	boolean decode = false;
	private int verbose = 2;

	S5Unit unnamed_100unit = new S5Unit(0.01, 0, "");
	S5Unit mmHg_100unit = new S5Unit(0.01, 0, "mmHg");
	S5Unit bpm_100unit = new S5Unit(0.01, 0, "bpm");
	S5Unit ms_100unit = new S5Unit(0.01, 0, "ms");
	S5Unit mv_100unit = new S5Unit(0.01, 0, "mV");

	private int tick;

	static {
		cap = new DeviceCapabilities(S5Driver.class);
		cap.addStream(StreamID.MEASUREMENT, basic_phdb.class);
		cap.addStream(StreamID.MEASUREMENT_2, ext3_phdb.class);
		cap.addStream(StreamID.WAVEFORM, wf_group.class);

		cap.setModels(new String[] { //
				"02: S-STD95/96", "02: S-ARK95/96", //
				"03: S-STD97/98", "03: S-ARK97/98", "03: S-ICU97/98", "03: Light Monitor", //
				"04: Cardiocap/5", //
				"05: S-STD99(A)", "05: S-ARK99(A)", "05: S-ICU99(A)", "05: S-00A01/02/05/06",//
		});

		cap.addConnection(new SerialConnection(19200, 8, 1, 2));
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(S5Driver.class);
	}

	public S5Driver(DeviceConfiguration conf) {
		super(conf);

		this.wf = new wf_group(this);
		// this.conf = (SerialDeviceConfiguration) conf;

		pkt = ByteBuffer.allocate(DATEX_ANY_SIZE);
		pkt.order(ByteOrder.LITTLE_ENDIAN);

		bbHdr = ByteBuffer.allocate(DATEX_HEADER_SIZE);
		bbHdr.order(ByteOrder.LITTLE_ENDIAN);

	}

	@Override
	public void connect() throws IOException {

		String portName = RpUtil.getParam(conf, "port");

		connect(portName, 19200, 8, 1, 2);

		initDataFlow();

	}

	private void initDataFlow() {
		try {
			log.error("FIXME: don't sleep in connect/init!");
			requestStop();
			Thread.sleep(200);
			requestPHDB();
			Thread.sleep(200);
			requestWaveforms();
		} catch (Exception e) {
			log.error("initDataFlow", e);
		}

	}

	private void requestStop() throws IOException {
		ByteBuffer[] subrecs = new ByteBuffer[1];

		ByteBuffer subrec0 = ByteBuffer.allocate(DATEX_PHDBREQ_SIZE); // 1 for
																		// ESC,
																		// 2
		subrec0.order(ByteOrder.LITTLE_ENDIAN);

		buildPHDBReq(subrec0, DRI_PH_DSPL, 0, //
				DRI_PHDBCL_REQ_BASIC_MASK //
						| DRI_PHDBCL_REQ_EXT1_MASK //
						| DRI_PHDBCL_REQ_EXT2_MASK //
						| DRI_PHDBCL_REQ_EXT3_MASK //
		); // stop

		subrecs[0] = subrec0;
		send(DRI_MT_PHDB, subrecs);
	}

	private void requestPHDB() throws IOException {
		ByteBuffer[] subrecs = new ByteBuffer[1];

		ByteBuffer subrec0 = ByteBuffer.allocate(DATEX_PHDBREQ_SIZE); // 1 for
																		// ESC,
																		// 2
		subrec0.order(ByteOrder.LITTLE_ENDIAN);

		buildPHDBReq(subrec0, DRI_PH_DSPL, 10, //
				DRI_PHDBCL_REQ_BASIC_MASK //
						| DRI_PHDBCL_REQ_EXT1_MASK //
						| DRI_PHDBCL_REQ_EXT2_MASK //
						| DRI_PHDBCL_REQ_EXT3_MASK //
		); // stop

		subrecs[0] = subrec0;
		send(DRI_MT_PHDB, subrecs);
	}

	private void requestWaveforms() throws IOException {
		ByteBuffer[] subrecs = new ByteBuffer[1];

		ByteBuffer subrec0 = ByteBuffer.allocate(DATEX_WAVEREQ_SIZE); // 1 for
		// ESC,
		// 2
		subrec0.order(ByteOrder.LITTLE_ENDIAN);
		subrecs[0] = subrec0;

		byte[] stop_types = { DRI_WF_CMD, // means ALL in this context
				DRI_EOL_SUBR_LIST, 0, 0, 0, 0, 0, 0 };

		buildWaveReq(subrec0, WF_REQ_CONT_STOP, stop_types);
		send(DRI_MT_WAVE, subrecs); // send stop request

		subrec0.clear();

		byte[] start_types = { 0, 0, 0, 0, 0, 0, 0, 0 };
		RpStream stream = IntfUtil.getStream(conf, StreamID.WAVEFORM);
		if (stream != null) {
			List<RpMetric> waves = stream.getMetric();

			int idx = 0;
			for (RpMetric wave : waves) {
				if (idx < 8) {
					start_types[idx++] = get_waveid(wave.getLocation());
				}
			}
			if (idx < 8) {
				start_types[idx] = DRI_EOL_SUBR_LIST;
			}

			buildWaveReq(subrec0, WF_REQ_CONT_START, start_types);
			send(DRI_MT_WAVE, subrecs); // send start request
		}

	}

	private byte get_waveid(String loc) {
		int id = 0;
		if (loc.equals("wf.ecg1")) {
			id = DRI_WF_ECG1;
		} else if (loc.equals("wf.ecg2")) {
			id = DRI_WF_ECG2;
		} else if (loc.equals("wf.ecg3")) {
			id = DRI_WF_ECG3;
		} else if (loc.equals("wf.invp1")) {
			id = DRI_WF_INVP1;
		} else if (loc.equals("wf.invp2")) {
			id = DRI_WF_INVP2;
		} else if (loc.equals("wf.invp3")) {
			id = DRI_WF_INVP3;
		} else if (loc.equals("wf.invp4")) {
			id = DRI_WF_INVP4;
		} else if (loc.equals("wf.invp5")) {
			id = DRI_WF_INVP5;
		} else if (loc.equals("wf.invp6")) {
			id = DRI_WF_INVP6;
		} else if (loc.equals("wf.pleth")) {
			id = DRI_WF_PLETH;
		} else if (loc.equals("wf.co2")) {
			id = DRI_WF_CO2;
		} else if (loc.equals("wf.o2")) {
			id = DRI_WF_O2;
		} else if (loc.equals("wf.no2")) {
			id = DRI_WF_NO2;
		} else if (loc.equals("wf.aa")) {
			id = DRI_WF_AA;
		} else if (loc.equals("wf.awp")) {
			id = DRI_WF_AWP;
		} else if (loc.equals("wf.resp")) {
			id = DRI_WF_RESP;
		} else if (loc.equals("wf.eeg1")) {
			id = DRI_WF_EEG1;
		} else if (loc.equals("wf.eeg2")) {
			id = DRI_WF_EEG2;
		} else if (loc.equals("wf.eeg3")) {
			id = DRI_WF_EEG3;
		} else if (loc.equals("wf.eeg4")) {
			id = DRI_WF_EEG4;
		} else if (loc.equals("wf.vol")) {
			id = DRI_WF_VOL;
		} else if (loc.equals("wf.tono")) {
			id = DRI_WF_TONO_PRESS;
		} else if (loc.equals("wf.spiloop")) {
			id = DRI_WF_SPI_LOOP_STATUS;
		} else if (loc.equals("wf.ent100")) {
			id = DRI_WF_ENT_100;
		} else if (loc.equals("wf.eegbis")) {
			id = DRI_WF_EEG_BIS;
		}

		return (byte) id;
	}

	private void send(short maintype, ByteBuffer[] subrecs) throws IOException {

		bbHdr.clear();
		buildDatexHdr(bbHdr, (byte) 0, maintype, subrecs);

		int chk = calcCheck(bbHdr, 0);
		for (ByteBuffer subrec : subrecs) {
			chk += calcCheck(subrec, 0);
		}

		// FIXME: need to encode binary escape sequences
		pkt.clear();
		pkt.put(PKT_START);
		pkt.put(bbHdr.array());
		for (ByteBuffer subrec : subrecs) {
			pkt.put(subrec.array());
		}
		pkt.put((byte) chk);
		pkt.put(PKT_END);

		if (verbose > 9) {
			System.out.print("out:");
			dump(System.out, pkt.array(), pkt.position());
		}

		OutputStream out = getOutputStream();
		out.write(pkt.array(), 0, pkt.position());

		return;
	}

	private int calcCheck(ByteBuffer bb, int offset) {
		int chk = 0;

		byte[] dat = bb.array();
		for (int i = offset; i < bb.capacity(); i++) {
			int byt = dat[i];
			if (byt < 0)
				byt += 256;
			chk += byt;
			// System.out.println( " add: " + Integer.toHexString(byt) +
			// " chk=" + Integer.toHexString(chk) );
		}
		chk %= 256;

		// System.out.println( "chk=" + Integer.toHexString(chk) );

		return chk;
	}

	private void buildPHDBReq(ByteBuffer bb, byte phdb_rcrd_type, int tx_ival, int phdbClassBf) {

		bb.put(phdb_rcrd_type);
		bb.putShort((short) tx_ival);
		bb.putInt(phdbClassBf);

		bb.putShort((short) 0x00); // reserved
	}

	private void buildWaveReq(ByteBuffer bb, short reqType, byte[] type) {

		bb.putShort(reqType);

		bb.putShort((short) 0x05); // reserved!!!
		bb.put(type);

		for (int i = 0; i < 10; i++) {
			bb.putShort((short) 0x00); // reserved
		}
	}

	private void buildDatexHdr(ByteBuffer bb, byte r_nbr, short maintype, ByteBuffer[] subrecs) {
		byte dri_level = 0;
		short plug_id = (short) 0; // 0xfde8;

		Date now = new Date();
		int r_time = (int) (now.getTime() / 1000);

		dri_level = DRI_LEVEL_00; // debug
		r_time = 0; // debug value

		bb.putShort((short) 0x00); // holder for len
		bb.put(r_nbr);
		bb.put(dri_level);
		bb.putShort(plug_id);
		bb.putInt(r_time);
		bb.put((byte) 0); // reserved1
		bb.put((byte) 0); // reserved2
		bb.putShort((short) 0); // reserved3

		bb.putShort(maintype); // r_maintype

		// holders for submessage types...meaning depends on maintype

		int subrecs_len = 0;
		if (subrecs != null) {
			subrecs_len = subrecs.length;
		}
		short offset = 0;
		short rec_size = DATEX_HEADER_SIZE;
		for (int i = 0; i < 8; i++) {
			if (i < subrecs_len) {
				ByteBuffer subrec = subrecs[i];
				bb.putShort(offset); // sr_offset
				bb.put((byte) 0); // sr_type
				offset += subrec.capacity();
				rec_size += subrec.capacity();
			} else if (subrecs_len == i) {
				bb.putShort((short) 0); // offset); // sr_offset
				bb.put(DRI_EOL_SUBR_LIST); // sr_type
				offset = 0;
			} else {
				bb.putShort((short) 0); // sr_offset
				bb.put((byte) 0); // sr_type
			}
		}

		bb.position(0);
		bb.putShort(rec_size); // actual len

	}

	@Override
	public void disconnect() throws IOException {
		super.disconnect();
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
	public void process(InputStream in, OutputStream out) throws IOException {
		if (verbose > 9) {
			System.out.print("in [" + new Date() + "]:");
		}

		while (in.available() > 0) {
			int byt = in.read();

			if (byt == -1) {
				break;
			}

			if (verbose > 9) {
				System.out.print(" 0x" + Integer.toHexString(byt));
			}

			if (mb_offset > mb_buffer.length - 2) {
				mb_offset = 0;
				log.error("COMM PKT OVERFLOW");
				continue;
			}

			if (byt == PKT_START) {
				if (mb_offset > 0) {

					// System.out.println( "\n\nPACKET: ");
					// dump(System.out, mb_buffer, mb_offset);

					processResponse(mb_buffer, mb_offset);
					for (int i = 0; i < mb_buffer.length; i++) {
						mb_buffer[i] = -1;
					}
				}
				mb_offset = 0;
			} else {
				if (byt == ESCAPE_CODE) {
					decode = true;
				} else {
					if (decode) {
						if (byt == 0x5e) {
							byt = 0x7e;
						} else if (byt == 0x5d) {
							byt = 0x7d;
						} else {
							log.error("UNXPECTED ESCAPE CHAR: 0x{}", Integer.toHexString(byt));
						}
						decode = false;
					}
					mb_buffer[mb_offset++] = (byte) byt;
				}
			}
		}

		if (verbose > 0) {
			System.out.println();
		}
	}

	private boolean processResponse(byte[] buf, int buflen) {

		tick = 0;

		ByteBuffer pkt = ByteBuffer.wrap(buf);
		pkt.order(ByteOrder.LITTLE_ENDIAN);

		short rLen = pkt.getShort();
		byte rNbr = pkt.get();
		byte driLevel = pkt.get();
		short plugID = pkt.getShort();
		int rTime = pkt.getInt();
		pkt.get(); // reserved1
		pkt.get(); // reserved2
		pkt.getShort(); // reserved3
		short rMaintype = pkt.getShort();

		short[] srOffset = new short[8];
		byte[] srType = new byte[8];

		for (int i = 0; i < 8; i++) {
			srOffset[i] = pkt.getShort();
			srType[i] = pkt.get();
		}

		log.debug("Parsing main type: {}", rMaintype);

		// now process each type
		for (int i = 0; i < 8; i++) {

			log.debug("{} Parsing subtype: {}", i, srType[i]);
			if (srType[i] == DRI_EOL_SUBR_LIST) {
				break;
			}

			byte marker;
			byte r1;
			switch (rMaintype) {
			case DRI_MT_PHDB:
				if (verbose >= 1)
					dump(System.out, buf, buflen);
				pkt.mark();
				int clpos = pkt.position() + DRI_PHDB_SIZE - 2;
				pkt.position(clpos);
				short undoc = pkt.get(); // reserved
				// field...val=91...documentation
				// has a byte order inversion?
				short cl = pkt.get(); // docs indicate this is a two byte field,
				// but that is not reflected in the data
				cl &= 0x0f; // some bits in this field are reserved
				pkt.reset();

				if (cl == DRI_PHDBCL_BASIC) {
					log.info("got PHDBCL");
					basic_phdb phdb = new basic_phdb(this);

					parsePHDB(phdb, pkt, srType[i]);

					fireStreamEvent(0, this, StreamID.MEASUREMENT, phdb);
					tick = 0;
				} else if (cl == DRI_PHDBCL_EXT1) {
					System.err.println("EXT1 READING NOT IMPLEMENTED");
					parseEXT1(pkt, srType[i]);
				} else if (cl == DRI_PHDBCL_EXT2) {
					System.err.println("EXT2 READING NOT IMPLEMENTED");
					parseEXT2(pkt, srType[i]);
				} else if (cl == DRI_PHDBCL_EXT3) {
					ext3_phdb ext3 = new ext3_phdb();
					parseEXT3(ext3, pkt, srType[i]);

					fireStreamEvent(0, this, StreamID.MEASUREMENT_2, ext3);
					tick = 0;
				} else {
					log.error("INVALID CLASS NOT IMPLEMENTED");
					pkt.position(clpos);
					pkt.get(); // reserved field...91
					pkt.get();
				}
				marker = pkt.get(); // marker
				r1 = pkt.get();
				cl = pkt.getShort();
				break;

			case DRI_MT_WAVE:

				parseWave(pkt, srType[i]);
				Date now = new Date();
				wf.setTm(now);
				fireStreamEvent(0, this, StreamID.WAVEFORM, wf);

				tick = 0;

				break;
			case DRI_MT_ALARM:
			default:
				log.error("CANT HANDLE MAINTYPE: {} SUBTYPE: 0x{}", rMaintype, Integer.toHexString(srType[i]));
				dump(System.err, buf, buflen);
			}
		}

		return true;
	}

	private void parseWave(ByteBuffer pkt, byte srType) {

		short act_len = pkt.getShort(); // number of word-sized samples
		short status = pkt.getShort();
		pkt.getShort(); // reserved

		if (act_len <= 0) {
			log.error("zero-or-negative size for wave: {} size={}", srType, act_len);
			return;
		}

		int[] item = null;
		item = new int[act_len];

		for (int i = 0; i < act_len; i++) {
			short datum = pkt.getShort();
			item[i] = datum;
		}

		switch (srType) {
		case DRI_WF_ECG1:
			wf.ecg1 = item;
			break;
		case DRI_WF_ECG2:
			wf.ecg2 = item;
			break;
		case DRI_WF_ECG3:
			wf.ecg3 = item;
			break;
		case DRI_WF_INVP1:
			wf.invp1 = item;
			break;
		case DRI_WF_INVP2:
			wf.invp2 = item;
			break;
		case DRI_WF_INVP3:
			wf.invp3 = item;
			break;
		case DRI_WF_INVP4:
			wf.invp4 = item;
			break;
		case DRI_WF_PLETH:
			wf.pleth = item;
			break;
		case DRI_WF_INVP5:
			wf.invp5 = item;
			break;
		case DRI_WF_INVP6:
			wf.invp6 = item;
			break;
		case DRI_WF_RESP:
			wf.resp = item;
			break;
		case DRI_WF_CO2:
			wf.co2 = item;
			break;
		case DRI_WF_O2:
			wf.o2 = item;
			break;
		case DRI_WF_NO2:
			wf.n2o = item;
			break;
		case DRI_WF_AA:
			wf.aa = item;
			break;
		case DRI_WF_AWP:
			wf.awp = item;
			break;
		case DRI_WF_FLOW:
			wf.flow = item;
			break;
		case DRI_WF_VOL:
			wf.vol = item;
			break;
		case DRI_WF_EEG1:
			wf.eeg1 = item;
			break;
		case DRI_WF_EEG2:
			wf.eeg2 = item;
			break;
		case DRI_WF_EEG3:
			wf.eeg3 = item;
			break;
		case DRI_WF_EEG4:
			wf.eeg4 = item;
			break;
		case DRI_WF_TONO_PRESS:
			wf.tono = item;
			break;
		case DRI_WF_EEG_BIS:
			wf.eegbis = item;
			break;
		case DRI_WF_ENT_100:
			wf.ent100 = item;
			break;

		}
		log.debug("parsed wave: {} len={}", srType, act_len);
	}

	private void parsePHDB(basic_phdb phdb, ByteBuffer pkt, byte srType) {

		int rTime = pkt.getInt();

		phdb.ecg.hdr = pkt.getInt();
		pkt.getShort(); // FIXME: this does not agree with DOCS p19
		phdb.ecg.hr = (int) pkt.getShort();
		phdb.ecg.st1 = (int) pkt.getShort();
		phdb.ecg.st2 = (int) pkt.getShort();
		phdb.ecg.st3 = (int) pkt.getShort();
		phdb.ecg.imp_rr = (int) pkt.getShort();

		for (int i = 0; i < 4; i++) {
			phdb.p[i].hdr = pkt.getInt();
			pkt.getShort();
			phdb.p[i].sys = (int) pkt.getShort();
			phdb.p[i].dia = (int) pkt.getShort();
			phdb.p[i].mean = (int) pkt.getShort();
			phdb.p[i].hr = (int) pkt.getShort();
		}

		phdb.nibp.hdr = pkt.getInt();
		pkt.getShort();
		phdb.nibp.sys = (int) pkt.getShort();
		phdb.nibp.dia = (int) pkt.getShort();
		phdb.nibp.mean = (int) pkt.getShort();
		phdb.nibp.hr = (int) pkt.getShort();

		for (int i = 0; i < 4; i++) {
			phdb.t[i].hdr = pkt.getInt();
			pkt.getShort();
			phdb.t[i].temp = (int) pkt.getShort();
		}

		phdb.SpO2.hdr = pkt.getInt();
		pkt.getShort();
		phdb.SpO2.SpO2 = (int) pkt.getShort();
		phdb.SpO2.pr = (int) pkt.getShort();
		phdb.SpO2.ir_amp = (int) pkt.getShort();
		phdb.SpO2.SvO2 = (int) pkt.getShort();

		phdb.co2.hdr = pkt.getInt();
		pkt.getShort();
		phdb.co2.et = (int) pkt.getShort();
		phdb.co2.fi = (int) pkt.getShort();
		phdb.co2.rr = (int) pkt.getShort();
		phdb.co2.amb_press = (int) pkt.getShort();

		phdb.o2.hdr = pkt.getInt();
		pkt.getShort();
		phdb.o2.et = (int) pkt.getShort();
		phdb.o2.fi = (int) pkt.getShort();

		phdb.n2o.hdr = pkt.getInt();
		pkt.getShort();
		phdb.n2o.et = (int) pkt.getShort();
		phdb.n2o.fi = (int) pkt.getShort();

		phdb.aa.hdr = pkt.getInt();
		pkt.getShort();
		phdb.aa.et = (int) pkt.getShort();
		phdb.aa.fi = (int) pkt.getShort();
		phdb.aa.mac_sum = (int) pkt.getShort();

		phdb.flow_vol.hdr = pkt.getInt();
		pkt.getShort();
		phdb.flow_vol.rr = (int) pkt.getShort();
		phdb.flow_vol.ppeak = (int) pkt.getShort();
		phdb.flow_vol.peep = (int) pkt.getShort();
		phdb.flow_vol.pplat = (int) pkt.getShort();
		phdb.flow_vol.tv_insp = (int) pkt.getShort();
		phdb.flow_vol.tv_exp = (int) pkt.getShort();
		phdb.flow_vol.compliance = (int) pkt.getShort();
		phdb.flow_vol.mv_exp = (int) pkt.getShort();

		phdb.co_wedge.hdr = pkt.getInt();
		pkt.getShort();
		phdb.co_wedge.co = (int) pkt.getShort();
		phdb.co_wedge.blood_temp = (int) pkt.getShort();
		phdb.co_wedge.ref = (int) pkt.getShort();
		phdb.co_wedge.pcwp = (int) pkt.getShort();

		phdb.nmt.hdr = pkt.getInt();
		pkt.getShort();
		phdb.nmt.t1 = (int) pkt.getShort();
		phdb.nmt.tration = (int) pkt.getShort();
		phdb.nmt.ptc = (int) pkt.getShort();

		phdb.ecgx.hr_ecg = (int) pkt.getShort();
		phdb.ecgx.hr_max = (int) pkt.getShort();
		phdb.ecgx.hr_min = (int) pkt.getShort();

		phdb.svo2.hdr = pkt.getInt();
		pkt.getShort();
		phdb.svo2.svo2 = (int) pkt.getShort();

		for (int i = 0; i < 2; i++) {
			phdb.p56[i].hdr = pkt.getInt();
			pkt.getShort();
			phdb.p56[i].sys = (int) pkt.getShort();
			phdb.p56[i].dia = (int) pkt.getShort();
			phdb.p56[i].mean = (int) pkt.getShort();
			phdb.p56[i].hr = (int) pkt.getShort();
		}

		byte r0 = pkt.get(); // reserved
		byte r1 = pkt.get(); // reserved

		fireStreamEvent(0, this, StreamID.MEASUREMENT, phdb);
	}

	private void parseEXT2(ByteBuffer pkt, byte b) {
		for (int i = 0; i < 270; i++) {
			pkt.get();
		}
	}

	private void parseEXT1(ByteBuffer pkt, byte b) {
		for (int i = 0; i < 270; i++) {
			pkt.get();
		}
	}

	private void parseEXT3(ext3_phdb ext3, ByteBuffer pkt, byte b) {
		ext3.gasex.hdr = pkt.getInt();
		pkt.getShort();
		ext3.gasex.ee = (int) pkt.getShort();
		ext3.gasex.rq = (int) pkt.getShort(); // ? out of order???
		ext3.gasex.vo2 = (int) pkt.getShort();
		ext3.gasex.vco2 = (int) pkt.getShort();

		ext3.fvol2.hdr = pkt.getInt();
		pkt.getShort();
		ext3.fvol2.ipeep = (int) pkt.getShort();
		ext3.fvol2.pmean = (int) pkt.getShort();
		ext3.fvol2.raw = (int) pkt.getShort();
		ext3.fvol2.mv_insp = (int) pkt.getShort();
		ext3.fvol2.epeep = (int) pkt.getShort();
		ext3.fvol2.mv_spont = (int) pkt.getShort();
		ext3.fvol2.ie_ratio = (int) pkt.getShort();
		ext3.fvol2.insp_time = (int) pkt.getShort();
		ext3.fvol2.exp_time = (int) pkt.getShort();
		ext3.fvol2.static_compliance = (int) pkt.getShort();
		ext3.fvol2.static_pplat = (int) pkt.getShort();
		ext3.fvol2.static_peepe = (int) pkt.getShort();
		ext3.fvol2.static_peepi = (int) pkt.getShort();
		for (int i = 0; i < 7; i++) {
			pkt.getShort(); // reserved;
		}

		ext3.bal.hdr = pkt.getInt();
		pkt.getShort();
		ext3.bal.et = (int) pkt.getShort();
		ext3.bal.fi = (int) pkt.getShort();

		ext3.tono.hdr = pkt.getInt();
		pkt.getShort();
		ext3.tono.prco2 = (int) pkt.getShort();
		ext3.tono.pr_et = (int) pkt.getShort();
		ext3.tono.pr_pa = (int) pkt.getShort();
		ext3.tono.pa_delay = (int) pkt.getShort();
		ext3.tono.phi = (int) pkt.getShort();
		ext3.tono.phi_delay = (int) pkt.getShort();
		ext3.tono.amb_press = (int) pkt.getShort();
		ext3.tono.cpma = (int) pkt.getShort();

		ext3.aa2.hdr = pkt.getInt();
		pkt.getShort();
		ext3.aa2.mac_age_sum = (int) pkt.getShort();

		for (int i = 0; i < 16; i++) {
			pkt.get(); // reserved;
		}

		for (int i = 0; i < 154; i++) {
			pkt.get(); // reserved;
		}
	}

	private void sendNumerics(int rTime) {

		// NumericsBlock block = new NumericsBlock();
		// MetricDescription[] desc = cap.getMetricDescriptions();
		//
		// int offset = 1;
		// int len = -2;
		// while (offset < len) {
		//
		// byte [] buf = null;
		// MetricDescription m = findMetric(desc, buf, offset);
		//
		// String s = (String) m.getLocation();
		//
		// int data_len = s.length();
		//
		// String val = new String(buf, offset + 1, data_len - 1);
		// offset += data_len;
		//
		// NumericsItem item = new NumericsItem(m);
		// item.setValue(new Double(val)); // FIXME: maybe this should not be a
		// // double
		// item.setTime(rTime * 1000);
		//
		// System.out.println(" got numeric item: " + m.getCode() + "=" + val);
		// block.add(item);
		// }

		log.error("S5DRIVER: Sending numeric event.");
		// fireEvent(NumericsEvent.class, new NumericsEvent(this, block));

	}

	private RpMetric findMetric(RpMetric[] desc, byte[] buf, int offset) {

		RpMetric m = null;

		byte ch = buf[offset];
		for (int i = 0; i < desc.length; i++) {
			String s = desc[i].getLocation();
			byte[] bytes = s.getBytes();
			if (bytes[0] == ch) {
				m = desc[i];
				break;
			}
		}

		return m;
	}

	private void dump(PrintStream out, byte[] array, int len) {
		out.print("\n ->");
		int i;
		for (i = 0; i < len; i++) {
			if ((i > 0) && (i % 16 == 0)) {
				out.print("\n ->");
			}

			out.print(" ");

			int byt = array[i];
			if (byt < 0)
				byt += 256;

			if (byt < 16) {
				out.print("0");
			}
			out.print(Integer.toHexString(byt));
		}

		out.println(); // terminate the line
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
				deviceState = NOT_CONNECTED;
				setStatus(NOT_CONNECTED);
			}
			if (tick > 8) {
				tick = 4;
				initDataFlow();
			}
		} else {
			if (deviceState != CONNECTED) {
				deviceState = CONNECTED;
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

}
