package icuInterface.adapters.novamet3;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import static idea.model.dev.CosmoWaveform.WF_PKT_SIZE;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.nio.ByteBuffer;

import com.fazecast.jSerialComm.SerialPort;

import icuInterface.ConnectionStatus;
import icuInterface.DriftRectifier;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.dev.CosmoMeasurement;
import idea.model.dev.CosmoWaveform;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class NovaCom3AbstractDriver extends SerialAdapter implements AdapterInterface {

	private final static int BAUD = 19200;

	private final static int MAX_V2_WAVES = 5;

	private final static int[][] wave_data = new int[5][WF_PKT_SIZE];

	// data is always sent in the same order: flow pressure co2 volume spo2
	private final static int WF_FLOW = 0;
	private final static int WF_PRESSURE = 1;
	private final static int WF_CO2 = 2;
	private final static int WF_VOLUME = 3;
	private final static int WF_SPO2 = 4;

	private final static byte STARTWAVEFORM_DATAMODE_CMD_VER1 = (byte) 0xb0;
	private final static byte MULTIWAVEFORM_PARAMETERMODE_CMD = (byte) 0xb1;
	private final static byte GET_DPI_PARAMETER_CMD = (byte) 0xb3;
	private final static byte STARTWAVEFORM_DATAMODE_CMD_VER2 = (byte) 0xb4;
	private final static byte GET_SOFTWARE_REV_CMD = (byte) 0xca;

	private final static byte UNDOC_C0_ENDTREND_TRANSFER_CMD = (byte) 0xc0;
	private final static byte UNDOC_C3_CMD = (byte) 0xc3;
	private final static byte UNDOC_D9_CMD = (byte) 0xd9;

	private final static byte MINUTE_AVG_PKT = (byte) 0xc2;
	private static final byte STARTTREND_TRANSFER_CMD_VER1 = (byte) 0xc4;
	private static final byte STARTTREND_TRANSFER_CMD_VER2 = (byte) 0x9a;
	private static final byte TRENDDATA_CMD_VER2 = (byte) 0x9c;
	private final static byte STREAM_PKT_VER1 = (byte) 0xc5;
	private final static byte WAVEFORM_PKT_VER2 = (byte) 0xb5;
	private final static byte STOP_CONT_MODE_CMD = (byte) 0xc9;
	private byte[] mb_buffer = new byte[1024];
	private int mb_offset = 0;
	// private InputStream in;

	private DeviceCapabilities cap;

	protected static int SHORTFLOW_STATUS_ERR = 1;
	protected static int EXTENDED_FLOW_STATUS_ERR = 2;
	protected static int BAROMETRIC_PRESSURE = 3;
	protected static int START_OF_INSP_MARK = 4;
	protected static int START_OF_EXP_MARK = 5;
	protected static int END_OF_PARAMETERS_FLAG = 126;
	/*
	 * SpO2 Pulseox Addendum
	 */

	Integer[] numeric = new Integer[127];
	int[] numerics_req;

	private DriftRectifier drifter;
	private int version;
	byte waves_requested = 0x0f; // indicated by the b4 command and confirmed by
									// b4 response
	public NovaCom3AbstractDriver(int version, DeviceCapabilities caps, RpDevice conf) {
		super(conf);

		this.version = version;
		this.cap = caps;

		AdapterUtil.fix_config(caps, conf);
		drifter = new DriftRectifier(500, 250, 11);

	}

	@Override
	public void connect() throws IOException {

		tick = 0;
		String portName = RpUtil.getParam(conf, "port"); // old method?
		if (portName == null) {
			portName = conf.getConnectionValue();
		}

		log.debug(" --> NovaCom3 {} at {}", portName, BAUD);
		connect(portName, BAUD, 8, 1, 0);

		try {
			log.error("FIXME: initDataFlow should not have sleep()");
			initDataFlow();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	/*
	 * The AnalysisPlus software uses all these commands, pretty much in the
	 * order indicated below. Some of them do not appear to be necessary and
	 * have been removed. Those commands remain in comments for reference or
	 * future use.
	 */

	@Override
	public void setPort(SerialPort port) {
		tick = 0;
		super.setPort(port);

		try {
			InputStream in = port.getInputStream();
			int avail = in.available();
			log.debug(" --> baud={} skipping available={}", port.getBaudRate(), avail);
			// if (avail > 0) {
			// in.skip(avail);
			// }
			log.debug(" --> NovaCom3 setPort request baud {} at {}", port, BAUD);
			port.setBaudRate(BAUD);
			port.setNumDataBits(8);
			port.setNumStopBits(1);
			port.setParity(SerialPort.NO_PARITY);
			port.setFlowControl(SerialPort.FLOW_CONTROL_DISABLED);
			initDataFlow();

			log.debug("setPort ready to: {}", port);
			port.setRTS();
			port.setDTR();

		} catch (Exception e) {
			log.error("could not set port baud: ", e);
		}
	}

	private void initDataFlow() throws InterruptedException, IOException {
		Thread.sleep(500);

		log.debug("**req init");

		requestStopContinuousMode();

		Thread.sleep(500);
		requestID();

		// Thread.sleep(500);
		// System.out.println("**req d9");
		// requestData((byte) 0x02);

		// Thread.sleep(500);
		// System.out.println("**req c3");
		// requestUndoc1( (byte) 0x01 );

		// Thread.sleep(500);
		// System.out.println("**req d9");
		// requestData((byte) 0x01); // ???

		Thread.sleep(500);

		log.debug("**sending numerics req 1");

		if (version == 1) {
			requestIndicatedMetricsVer1();
		} else if (version == 2) {
			// requestIndicatedMetricsVer2();
			requestWaveformDataModeV2();
		} else {
			log.error("Unrecognized version: {}", version);
			assert (false) : "NovaCom3AbstractDriver: Unrecognized version: " + version;
		}
	}

	@Override
	public void reset() {
		mb_offset = 0;
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {

		while (in.available() > 0) {
			// System.out.print("[" + in.available() + "]");
			int byt = in.read();

			if (byt == -1) {
				break;
			}

			// System.out.print(Integer.toHexString(byt));
			// System.out.print(" ");
			mb_buffer[mb_offset++] = (byte) byt;

			if (processResponse(mb_buffer, mb_offset)) {
				for (int i = 0; i < mb_buffer.length; i++) {
					mb_buffer[i] = -1;
				}
				mb_offset = 0;
			}

			if (mb_offset > mb_buffer.length - 10) {
				mb_offset = 0;
			}
		}
		// System.out.println("***");
		// System.out.println("DONE");

	}

	private void send(byte[] req, int len) throws IOException {

		OutputStream out = getOutputStream();
		int chk = 0x0;
		synchronized (out) {
			for (int i = 0; i < len; i++) {
				int ch = req[i];
				chk += ch;
			}
			chk %= 0x80;
			chk = 0x80 - chk;
			out.write(req, 0, len); // bb.array());
			out.write((byte) chk); // bb.array());
		}

		if (log.isDebugEnabled()) {
			System.out.print(" to device: ");
			dump(System.out, req, len);
			System.out.println("chk=" + Integer.toHexString(chk));
		}
	}

	private static void dump(PrintStream out, byte[] user_data, int len) {
		for (int i = 0; i < len; i++) {
			int ch = user_data[i];
			if (ch < 0)
				ch += 256;
			if (ch < 0x10) {
				System.out.print("0");
			}
			System.out.print(Integer.toHexString(ch));
			System.out.print(" ");

			String xtra = null;
			if (i == 0) {
				if (ch == 0xc9) {
					xtra = "STOP";
				} else if (ch == 0x89) {
					xtra = "CONT: HW DIAG MODE";
				} else if (ch == 0x8a) {
					xtra = "CONT: CO2 DIAG MODE";
				} else if (ch == 0xa0) {
					xtra = "SR: ZERO CAPNO";
				} else if (ch == 0xb0) {
					xtra = "CONT: START WF";
				} else if (ch == 0xb1) {
					xtra = "CONT: PARAM MODE";
				} else if (ch == 0xb3) {
					xtra = "SR: GET DPI";
				} else if (ch == 0xb4) {
					xtra = "CR: START WF/P";
				} else if (ch == 0xb5) {
					xtra = "CR: WF/P";
				} else if (ch == 0xc8) {
					xtra = "NAK";
				} else if (ch == 0xca) {
					xtra = "SR: GET REV";
				} else if (ch == 0xcb) {
					xtra = "SR: GET/SET NORESP TMOUT";
				} else if (ch == 0xcd) {
					xtra = "SR: MANUAL PURGE-0";
				} else if (ch == 0xd0) {
					xtra = "SR: GET/SET COMP";
				} else if (ch == 0xd4) {
					xtra = "SR: GET/SET SETTINGS";
				} else if (ch == 0xd8) {
					xtra = "SR: GET SNSR TYPE";
				} else if (ch == 0xdb) {
					xtra = "SR: GET MECH THRSH";
				} else if (ch == 0xf8) {
					xtra = "SR: RESET";
				}
			}
			if (i == 1) {
				xtra = "NBF";
			}

			if (xtra != null) {
				System.out.print("[");
				System.out.print(xtra);
				System.out.print("] ");
			}
		}
	}

	int sample_count = 0;
	int last_idx = -1;
	private int tick;

	private boolean processResponse(byte[] message, int len) throws IOException {
		boolean processed = false;

		if (len + 2 >= mb_buffer.length) {
			System.out.println("overflow");
			return true; // ignore and wipe the buffer
		}
		if (len == 1) {
			byte cmd = message[0];
			if (cmd >= 0) {
				log.debug("ignoring: {}", Integer.toHexString(cmd));
				return true; // reset buffer
			} else {
				// log.debug("got cmd: {}", Integer.toHexString(cmd + 256));
			}
			return false;
		}

		if (len > 2) {

			byte cmd = message[0];
			int pkt_len = message[1];
			if (len == pkt_len + 2) {

				if (sample_count >= WF_PKT_SIZE) {
					log.error("sample count err: {}", sample_count);
					sample_count = 0;
				}
				if (cmd == MULTIWAVEFORM_PARAMETERMODE_CMD) { // version 1

					int idx = 2;
					for (int i = 0; i < 4; i++) {
						int h = message[idx++] - 0x40;
						int l = message[idx++];
						int val = h * 0x80 + l;

						wave_data[i][sample_count] = val;
					}

					if (pkt_len > 10) {
						int fid = message[idx++];
						int h = message[idx++];
						int l = message[idx++];
						int val = h * 0x80 + l;

						numeric[fid] = val;

						if (fid == 0x66) {
							sendNumerics();
						}
					}

					sample_count++;
					if (sample_count == WF_PKT_SIZE) {
						fireWaveformComplete();
					}
				} else if (cmd == WAVEFORM_PKT_VER2) { // the version 2
														// continuous waveform
					// eeek
					int nbf = message[1];
					if (nbf < 0) {
						nbf += 256;
					}
					nbf--; // drop checksum
					int idx = 2;
					for (int i = 0; i < MAX_V2_WAVES; i++) {
						int flag = 1 << i;
						if ((waves_requested & flag) != 0) {
							if (i == WF_SPO2) {
								nbf -= 1; // SPO2 waves are single byte
								int val = message[idx++];
								wave_data[i][sample_count] = val;
							} else {
								nbf -= 2;
								if (nbf < 0) {
									log.warn("bad WAVEFORM_PKT_VER2 packet");
									break;
								}
								int h = message[idx++] - 0x40;
								int l = message[idx++];
								int val = h * 0x80 + l;

								wave_data[i][sample_count] = val;
							}
						}
					}

					if (nbf > 1) {
						int fid = message[idx++];
						int h = message[idx++];
						int l = 0;
						int val = h;
						int dp3 = 0;
						if (nbf > 2) {
							l = message[idx++];
							val = h * 0x80 + l;
						}
						if (nbf > 3) {
							dp3 = message[idx++];
							// log.warn("PARAM={} DP3={}", fid, dp3);
						}

						if (nbf > 4) {
							int dp4 = message[idx++];
							if (fid == 2 || fid == 18) { // flow status=2, alarm
															// status =18
								val = h << 24 + l << 16 + dp3 << 8 + dp4;
								// } else if (fid == 7) { // NM3....maybe a
								// check adapter or standby?
								// val = h << 24 + l << 16 + dp3 << 8 + dp4;
								// } else {
								// log.warn("UNIT NOT HANDLED PARAM=" + fid);
							}
						}
						if (fid >= 0 && fid < numeric.length) {
							numeric[fid] = val;
						} else {
							log.warn("FID[{}] NOT HANDLED PARAM={}", fid, val);
						}
						// if (log.isDebugEnabled() ) {
						// log.debug(nbf + " fid={} byte_h={} byte_l=" + l
						// + " val=" + val, fid, h);
						// }
						if (fid == 0x63) {
							sendNumerics();
						}
					} else if (nbf > 0) {
						nbf--;
						log.debug("nums? nbf: {}", nbf);
					}

					sample_count++;
					if (sample_count == WF_PKT_SIZE) {
						log.debug("firing waveform");
						fireWaveformComplete();
					}

				} else if (cmd == STREAM_PKT_VER1) { // some kind of setup or
														// trend
					// stream? ends when WF starts

					int idx = message[2];
					if (last_idx != idx) {
						last_idx = idx;

					}

					// for (int ii = 3; ii < pkt_len;) {
					// int field_id = message[ii++];
					// if (field_id == 1) {
					// for (int j = 0; j < 6; j++) {
					// int val = message[ii++];
					// log.debug(" {}", val);
					// }
					// } else {
					// int val = message[ii++];
					// val *= 128;
					// val += message[ii++];
					//
					// log.debug(" [" + field_id + "] " + val);
					//
					// }
					// }
				} else if (cmd == MINUTE_AVG_PKT) {
					byte var_id = message[3];

					int val = message[4]; // high byte
					val *= 0x80;
					val += message[5];

					if (log.isDebugEnabled()) {
						log.debug(" MINUTE_AVG: {}={}", var_id, val);
						if (var_id == 0x7e) {
							System.out.println();
						}
					}

				} else if (cmd == TRENDDATA_CMD_VER2) {
					if (pkt_len >= 7) {
						int idx = 3;
						int fid = message[idx++];
						int h = message[idx++];
						int l = message[idx++];
						int val = h * 0x80 + l;

						if (fid >= 0 && fid < numeric.length) {
							numeric[fid] = val;
						} else {
							log.warn("Unexpected fid={} val={}", fid, val);
						}

						if (fid == END_OF_PARAMETERS_FLAG) {
							sendNumerics();
						}
					} else {
						log.warn("SHORT TREND DATA PKT");
					}
				} else if (cmd == STARTTREND_TRANSFER_CMD_VER2) {
					// ?? send continuous mode request
					requestWaveformDataModeV2();
				} else if (cmd == UNDOC_C0_ENDTREND_TRANSFER_CMD) {
					requestWaveformDataModeV1();
				} else if (cmd == STOP_CONT_MODE_CMD) {

					// if( haveControl == false ) {
					log.debug("Unhandled: STOP_CONT_MODE_CMD");
					// // if the remote system has control, reply to his request
					// byte[] req = { PING_PKT, 0x01 };
					// send(req);
					// }

				} else {
					int icmd = cmd;
					if (icmd < 0) {
						icmd += 256;
					}

					log.warn("ignorning cmd: {}", icmd);
				}
				processed = true;
			}
		}

		return processed;
	}

	private void fireWaveformComplete() {
		long tm = drifter.getRectifiedTime(PlatformUtil.currentTimeMillis());
		int msPerPacket = 500;
		drifter.setNextExpectedTime(tm + msPerPacket);

		CosmoWaveform block = new CosmoWaveform();
		block.setTime(tm);
		RpMetric[] wfd = block.getMetrics();

		for (int ii = 0; ii < wfd.length; ii++) {
			// not exactly what we wanted...we allocated data when calling the
			// persistent item constructor. This replaces that data.
			IntfUtil.setValue(block, wfd[ii], wave_data[ii]);
		}

		fireStreamEvent(0, this, StreamID.WAVEFORM, block);
		sample_count = 0;
		tick = 0;
		setStatus(ConnectionStatus.CONNECTED);
	}

	private void sendNumerics() {
		// long time = PlatformUtil.currentTimeMillis();

		CosmoMeasurement block = new CosmoMeasurement();
		RpMetric[] metrics = block.getMetrics();

		boolean all_null = true;
		for (RpMetric metric : metrics) {
			String loc = metric.getLocation();
			int fid = Integer.parseInt(loc);
			Integer val = numeric[fid];
			if (val != null) {
				IntfUtil.setValue(block, metric, val);
				all_null = false;
			}
		}

		if (all_null == true) {
			// dont fire an event. continue waiting for timeout tick.
		} else {
			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);
			tick = 0;
			setStatus(CONNECTED);

			for (int i = 0; i < numeric.length; i++) {
				numeric[i] = null; // Integer.MIN_VALUE;
			}
		}

	}

	private void requestWaveformDataModeV1() throws IOException {
		byte[] reply = { STARTWAVEFORM_DATAMODE_CMD_VER1, 0x40, waves_requested, 0x04, 0x05, 0x0a, 0x0b, 0x0c, 0x0d,
				0x0e, 0x12, 0x13, 0x14, 0x15, 0x17, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24,
				0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x30, 0x31, 0x33, 0x34, 0x36, 0x37, 0x3c, 0x3d, 0x3e, 0x46, 0x47,
				0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x57, 0x59, 0x58, 0x5a, 0x5b, 0x5d, 0x5e, 0x5f, 0x60,
				0x61, 0x62, 0x64, 0x65, 0x66 };

		send(reply, reply.length);
	}

	private void requestWaveformDataModeV2() throws IOException {
		ByteBuffer tpv = ByteBuffer.allocate(128);

		tpv.put(STARTWAVEFORM_DATAMODE_CMD_VER2);
		tpv.put((byte) 0); // length placeholder
		tpv.put(waves_requested); // wmb...or'd list of waveforms
		// reply has one more byte...wmv...confirming waveform req...
		RpMetric[] metrics = IntfUtil.getMetrics(CosmoWaveform.class);
		if (metrics != null) {
			for (RpMetric metric : metrics) {
				String loc = metric.getLocation();
				int x_pos = loc.indexOf('x');
				String hex = loc.substring(x_pos + 1);

				int dpv = Integer.parseInt(hex);
				tpv.put((byte) dpv);
			}
		}
		byte[] req = tpv.array();
		req[1] = (byte) (tpv.position() - 1); // recalc length...we might remove

		send(req, tpv.position());
	}

	private void requestData(byte param) throws IOException {
		byte[] req = { UNDOC_D9_CMD, 0x02, param };

		send(req, req.length);
	}

	private void requestIndicatedMetricsVer1() throws IOException {

		byte[] req = { STARTTREND_TRANSFER_CMD_VER1, // command
				0x22, // len
				0x10, 0x0a, 0x0b, 0x0e, //
				0x12, 0x13, 0x14, 0x15, 0x17, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, //
				0x21, 0x26, 0x27, 0x28, //
				0x33, 0x3d, 0x3e, //
				0x50, 0x51, 0x53, 0x54, 0x55, 0x57, 0x59, 0x58, //
				0x64, 0x65, 0x66 }; //

		req[1] = (byte) (req.length - 1); // recalc length...we might remove
		// columns

		send(req, req.length);
	}

	private void requestIndicatedMetricsVer2() throws IOException {

		byte[] req = { STARTTREND_TRANSFER_CMD_VER2, // command
				0x22, // len
				0x10, 0x0a, 0x0b, 0x0e, //
				0x12, 0x13, 0x14, 0x15, 0x17, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, //
				0x21, 0x26, 0x27, 0x28, //
				0x33, 0x3d, 0x3e, //
				0x50, 0x51, 0x53, 0x54, 0x55, 0x57, 0x59, 0x58, //
				0x64, 0x65, 0x66 }; //

		req[1] = (byte) (req.length - 1); // recalc length...we might remove
		// columns

		send(req, req.length);
	}

	private void requestStopContinuousMode() throws IOException {

		byte[] req = { STOP_CONT_MODE_CMD, 0x01 };

		send(req, req.length);

	}

	private void requestID() throws IOException {
		byte[] req = { GET_SOFTWARE_REV_CMD, 0x02, 0x0 };

		send(req, req.length);
	}

	private void requestUndoc1(byte val) throws IOException {

		byte[] req = { UNDOC_C3_CMD, 0x02, val };

		send(req, req.length);
	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
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
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();

		if (tick > 10) {
			tick = 7;
			try {
				initDataFlow();
			} catch (Exception e) {
				// this should not happen...but the user already knows there is
				// a comm error USB-RS232 device disconnected?
				log.error("could not init data flow", e);
			}
		} else if (tick > 7) {
			if (deviceState != NOT_CONNECTED) {
				int prev_tick = tick;
				sendNumerics(); // empty set of numerics for display, but also
				// resets tick
				tick = prev_tick;

				setStatus(NOT_CONNECTED, "tick");
			}
		} else {
			// could be negotiating
			// if (deviceState != CONNECTED) {
			// setStatus(CONNECTED, "tick");
			// }
		}
		
		return 0;
	}

}
