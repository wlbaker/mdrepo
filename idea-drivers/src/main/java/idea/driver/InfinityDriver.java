package idea.driver;

/**
 * TODO: Autoconfig should remove unused values also....search for removeExtras, which is disabled.
 */
import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NEGOTIATING;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import static icuInterface.LoggingUtil.dumpConfiguration;
import static icuInterface.LoggingUtil.dumpEvent;
import static icuInterface.LoggingUtil.getLoggingOutputStream;
import static idea.driver.infinity.Constants.BED_LABEL_SIZE;
import static idea.driver.infinity.Constants.CURR_MSG_SIZE;
import static idea.driver.infinity.Constants.NDO_PDS_BED_CONFIG;
import static idea.driver.infinity.Constants.NDO_PDS_CURRENT_MSG_DISPLAYED;
import static idea.driver.infinity.Constants.NDO_PDS_DISPLAY_SETUP;
import static idea.driver.infinity.Constants.NDO_PDS_PARAMETER_AND_ALARM;
import static idea.driver.infinity.Constants.NDO_PDS_PARAMETER_BOX_SETUP;
import static idea.driver.infinity.Constants.NDO_PDS_SIGNAL_GROUP_INTERVAL_MEASUREMENT;
import static idea.driver.infinity.Constants.NDO_PDS_SUMMARY_ALARM_INFO;
import static idea.driver.infinity.Constants.NDO_PDS_VENT_CURRENT_MSG;
import static idea.driver.infinity.Constants.NDO_PDS_VENT_PARAM_LIST;
import static idea.driver.infinity.Constants.NDO_PDS_VENT_VOL_WV_DESC;
import static idea.driver.infinity.Constants.NDO_PDS_VENT_WV_DESC;
import static idea.driver.infinity.Constants.NDO_PDS_WAVEFORM;
import static idea.driver.infinity.Constants.NDO_PDS_WAVEFORM_SETUP;
import static idea.driver.infinity.Constants.PATIENT_INITIALS_SIZE;
import static idea.driver.infinity.Constants.PATIENT_NAME_SIZE;
import static idea.driver.infinity.Constants.UNKNOWN_NDO_34;
import static idea.driver.infinity.Constants.UNKNOWN_NDO_35;
import static idea.driver.infinity.Constants.UNKNOWN_NDO_PDS_28;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import icuInterface.ConnectionStatus;
import icuInterface.LoggingUtil;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.InfinityConnection;
import idea.display.BandLayout;
import idea.display.FieldData;
import idea.display.ParameterLayout;
import idea.display.WaveformData;
import idea.driver.infinity.NetUnitsOfMeasure;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.intf.DataTyp;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.DisplayConfig;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.model.dev.DragerDelta_Demographics;
import idea.model.dev.DragerDelta_Measurements;
import idea.model.dev.DragerDelta_MibBIS;
import idea.model.dev.DragerDelta_MibMGM;
import idea.model.dev.DragerDelta_MibSVO2;
import idea.model.dev.DragerDelta_MibVent;
import idea.model.dev.DragerDelta_Sensors;
import idea.model.dev.DragerDelta_SensorsAnaesthesia;
import idea.model.dev.DragerDelta_SensorsEKG12;
import idea.model.dev.DragerDelta_SensorsEKG5;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpUnit;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;

class DataPair {
	DataPair(RpMetric m, Class<? extends PersistentItem> cl) {
		this.metric = m;
		this.cl = cl;
	}

	RpMetric metric;
	Class<? extends PersistentItem> cl;
}

@Slf4j
public class InfinityDriver extends AbstractStreamProducer implements AdapterInterface {
	private static final String driverName = "monitor/Drager Infinity Network";

	public static final short INTF_TYPE_DATA = 4;
	public static final short INTF_TYPE_ALARM = 2;
	public final static int port = 2050;

	@Getter
	@Setter
	private long vitalsSkipCount = 10;
	public static int PARAMLOG_EVERY_N = 120; // come at the rate of 2/sec
	private boolean send_initial_caps = true;

	String group = null;

	DateFormat fmt = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");

	public static SocketDeviceConfiguration createConfigInstance() {
		SocketDeviceConfiguration conf = new SocketDeviceConfiguration(InfinityDriver.class);
		conf.setPort(port);
		conf.setName("Infinity");
		return conf;
	}

	private MulticastSocket s;
	private RpDevice sconf;
	private DeviceCapabilities caps;

	// private BandData[] bands;

	// private MetricDescription[] metric_descs;

	private static DeviceCapabilities static_cap;

	private static Map<String, DataPair> hm_mea = new HashMap<String, DataPair>();
	static RpMetric[] demographics_descs;

	DragerDelta_Sensors sensors = new DragerDelta_Sensors();

	private long ts;

	private long numeric_idx;

	DisplayConfig display = new DisplayConfig();

	private boolean initial_config = true;
	private boolean autoConfig = true;
	private int tick;
	private List<Alarm> lastAlarms = new LinkedList<Alarm>();
	int rev_no = 0;

	private InetAddress addr;
	private PrintStream dout;

	private boolean request_display_refresh;

	private boolean config_changed;

	private boolean continuousAlarms = false;

	private int firstSignalGroup;

	private int firstParamId;

	@Getter
	private byte opmode;

	private byte horiz_pboxes;
	private long julian0;
	private int ts_high0;
	private int ts_low0;
	@Setter
	@Getter
	private boolean useDeviceTime = false;
	private final static DateFormat debug_df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
	DragerDelta_Measurements measures = new DragerDelta_Measurements();

	@Getter
	private boolean discharged;
	
	static {

		static_cap = new DeviceCapabilities(InfinityDriver.class);

		/*
		 * MAJOR GROUP: patient data service
		 */

		// bed configuration

		// display setup

		// waveform data

		addOneStream(StreamID.WAVEFORM, DragerDelta_Sensors.class);
		addOneStream(null, DragerDelta_SensorsEKG12.class);
		addOneStream(null, DragerDelta_SensorsAnaesthesia.class);
		addOneStream(null, DragerDelta_SensorsEKG5.class);
		addOneStream(StreamID.DDDEMOGRAPHICS, DragerDelta_Demographics.class);
		addOneStream(StreamID.MEASUREMENT, DragerDelta_Measurements.class);
		addOneStream(null, DragerDelta_MibBIS.class);
		addOneStream(null, DragerDelta_MibMGM.class);
		addOneStream(null, DragerDelta_MibSVO2.class);
		addOneStream(null, DragerDelta_MibVent.class);

		static_cap.addConnection(new InfinityConnection());
		static_cap.setModels(new String[] { "Delta" });
	}

	private static void addOneStream(StreamID sid, Class<? extends PersistentItem> cl) {
		if (sid != null) {
			static_cap.addStream(sid, cl);
		}
		RpMetric[] metrics = IntfUtil.getMetrics(cl);
		for (RpMetric metric : metrics) {
			DataPair pair = new DataPair(metric, cl);
			hm_mea.put(metric.getLocation(), pair);
		}

	}

	public InfinityDriver(RpDevice conf) {

		this.sconf = conf;
		this.caps = new DeviceCapabilities(conf);

		// AdapterUtil.fix_config(cap, conf);
		// set the isActive() flag and copy the getter/setter

		this.dout = getLoggingOutputStream(this.getClass());
		if (dout != null) {
			dumpConfiguration(dout, this);
		}
		ts = now();
		// other data

		/*
		 * MAJOR GROUP: Alarm Group Service
		 */

		if (conf == null) {
			setAutoConfig(true);
		} else {
			String ac_text = RpUtil.getParam(conf, "autoConfig");
			if (ac_text != null) {
				this.setAutoConfig("true".equalsIgnoreCase(ac_text));
			}

			setConfiguration(conf);
		}

	}

	private long now() {
		if (useDeviceTime) {
			return julian0 * 1000 + ts_low0;
		}

		return PlatformUtil.currentTimeMillis();
	}

	@Override
	public void connect() throws IOException {

		setStatus(NEGOTIATING);
		group = null;

		String ip = RpUtil.getParam(sconf, "host");
		if (ip == null) {
			ip = sconf.getConnectionValue();
		}
		int monitoring_unit = 1;
		if (ip.startsWith("infinity://")) {
			String ref = ip;
			group = ip.substring(12);
			int pos = group.indexOf('/', 4);
			if (pos > 2) {
				ip = group.substring(pos + 1); // ignored
				group = group.substring(1, pos);
			}
		} else if (ip.startsWith("udp://")) {
			String ref = ip;
			group = ip.substring(6);
			int pos = group.indexOf('/', 4);
			if (pos > 2) {
				ip = group.substring(pos + 1); // ignored
			} else {
				setStatus(ConnectionStatus.ERROR);
				log.error("Invalid ID/No monitoring unit: {}", ref);
				return;
			}
			group = group.substring(1, pos);
		} else if (ip.startsWith("/")) {
			ip = ip.substring(1);
			int pos = ip.indexOf(':');
			if (pos > 2) {
				String ag_s = ip.substring(pos + 1);
				ip = ip.substring(0, pos);
				monitoring_unit = Integer.parseInt(ag_s);
			}
			addr = InetAddress.getByName(ip);

		} else {
			addr = InetAddress.getByName(ip);
			byte[] ar = addr.getAddress();

			int last8 = ar[3];
			if (last8 < 0) {
				last8 += 256;
			}
			group = "224.0." + monitoring_unit + "." + last8;
		}

		if (group != null) {
			log.info("group: {}", group);
			s = new MulticastSocket(port);

			try {
				// join the multicast group
				// byte [] tmp = new byte[4];
				InetAddress group_inet = InetAddress.getByName(group);
				s.joinGroup(group_inet);
				// Now the socket is set up and we are ready to receive packets
			} catch (UnknownHostException skipme) {
				throw (skipme); // rethrow
			} catch (Exception skipme) {
				log.error("WARNING: might not get multicast for address: {}", group, skipme);
			}
		}
		// Now the socket is set up and we are ready to receive packets

		incrementFileRevision(); // set the name before the first packet is even
									// sent.

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

		Thread th = new Thread(r, "INFINITY_DRV");
		th.start();
	}

	@Override
	public void disconnect() throws IOException {

		// And when we have finished receiving data leave the multicast group
		// and
		// close the socket

		if (s != null) {
			try {
				s.leaveGroup(InetAddress.getByName(group));
			} finally {
				s.close();
			}

			setStatus(ConnectionStatus.NOT_CONNECTED);
		}

	}

	private void waitForData() throws IOException {

		// Create a DatagramPacket and do a receive
		byte buf[] = new byte[2048];
		DatagramPacket pack = new DatagramPacket(buf, buf.length);
		s.receive(pack);

		// this can happen if the monitor is in standby...is that connected or
		// not?
		// setStatus(CONNECTED); // if we got a packet, must be connected!

		parsePacket(pack.getData(), pack.getLength());
	}

	@Override
	public void process(InputStream is, OutputStream os) throws IOException {

		byte[] data = is.readAllBytes(); // VERY HACKY
		parsePacket(data, data.length);
		return;
	}

	public void parsePacket(byte[] data, int len) {
		if (dout != null) {
			dout.flush();
			LoggingUtil.dumpSocketData(dout, now() - ts, data, len);
		}
		ByteBuffer bb = ByteBuffer.wrap(data);
		short ndoId = bb.getShort();
		short pad = bb.getShort();
		int msgSeq = bb.getInt();
		long julian = bb.getInt();
		int deviceIp = bb.getInt();

		bb.getShort(); // connect id

		int ts_low = bb.getShort(); // timestamp
		int ts_high = bb.getInt();
		if (ts_low < 0)
			ts += 0x10000;

		julian0 = julian;
		ts_high0 = ts_high;
		ts_low0 = ts_low;

		short majorVer = bb.getShort();
		short minorVer = bb.getShort();

		short n_bytes = bb.get(); // yes, byte in this context
		byte n_ndo = bb.get();
		short spare = bb.getShort();

//		if (opmode == 0) {
//			System.out.println(spare + " ver: " + //
//					majorVer + "." + minorVer + " seq: " + msgSeq + " pad:" + pad);
//		}
		for (int i = 1; i <= n_ndo; i++) { // should be n_ndo - 1???
			// System.out.println("i=" + i + " of:" + n_ndo);
			if (!bb.hasRemaining()) {
				// System.out.println("x-out " + i + " of " + n_ndo);
				break;
			}
			ndoId = bb.getShort();
			n_bytes = bb.getShort();

			int pos = bb.position();

			if (n_bytes == 0)
				break;

			ByteBuffer ndoBuffer = ByteBuffer.wrap(data, pos, n_bytes - 4);
			// debugFindString(ndoBuffer);

			switch (ndoId) {
			case NDO_PDS_BED_CONFIG:
				if (opmode == 0)
					parseBedConfig(ndoBuffer);
				break;
			case NDO_PDS_DISPLAY_SETUP:
				/*
				 * we must parse this message to set opmode
				 */
				tick = 0; // we call this connected, even if NO DATA is
							// sent...standby
				parseDisplaySetup(ndoBuffer);
				break;
			case NDO_PDS_WAVEFORM:
				if (opmode == 0)
					parseWaveform(ndoBuffer);
				break;
			case NDO_PDS_WAVEFORM_SETUP:
				if (opmode == 0)
					parseWaveformSetup(ndoBuffer);
				break;
			case NDO_PDS_PARAMETER_AND_ALARM:
				if (opmode == 0)
					parseParameterAndAlarm(ndoBuffer);
				break;
			case NDO_PDS_PARAMETER_BOX_SETUP:
				if (opmode == 0)
					parseParameterBoxSetup(ndoBuffer);
				break;
			case NDO_PDS_CURRENT_MSG_DISPLAYED:
				if (opmode == 0)
					parseCurrentMsgDisplayed(ndoBuffer);
				break;
			case NDO_PDS_SUMMARY_ALARM_INFO:
				if (opmode == 0)
					parseSummaryAlarmInfo(ndoBuffer);
				break;

			case NDO_PDS_VENT_CURRENT_MSG:
				if (opmode == 0)
					parseVentCurrentMsg(ndoBuffer);
				break;

			case NDO_PDS_VENT_WV_DESC:
				if (opmode == 0)
					parseVentWaveformDescription(ndoBuffer);
				break;

			case NDO_PDS_VENT_PARAM_LIST:
				if (opmode == 0)
					parseVentParamList(ndoBuffer);
				break;

			case NDO_PDS_VENT_VOL_WV_DESC:
				if (opmode == 0)
					parseVentVolWaveformDescription(ndoBuffer);
				break;

			case UNKNOWN_NDO_PDS_28:
				// intentionally ignoring this value...occurs!
				log.info(" UNKNOWN_NDO_PDS_28 unknown ndoId");
				break;
			case UNKNOWN_NDO_34:
				// intentionally ignoring this value...occurs!
				log.debug(" UNKNOWN_NDO_34 unknown ndoId");
				break;
			case UNKNOWN_NDO_35:
				// intentionally ignoring this value...occurs!
				log.debug(" UNKNOWN_NDO_35 unknown ndoId");
				break;
			case NDO_PDS_SIGNAL_GROUP_INTERVAL_MEASUREMENT:
				if (opmode == 0)
					parseSignalGroupIntervalMeasurement(ndoBuffer, n_bytes - 4);
				break;
			default:
				log.warn(" unknown ndoId: {}", ndoId);

			}
			bb.position(pos + n_bytes - 4);
		}

	}

	private void parseSignalGroupIntervalMeasurement(ByteBuffer ndoBuffer, int n_bytes) {
		if (n_bytes != 12) {
			log.warn("expecting 12 bytes, got {}", n_bytes);
		}

		// if it is signal group...then it is past the end of my known signal
		// groups
		// ? int signalGroup = ndoBuffer.get();
		// ? int paramId = ndoBuffer.get();

		// signalGroupIntervalMeasurement count=12
		// 52 78 ca 3b 1e 0 0 0 14 6 0 0
		// only coming from Anesthesia machine?
		// seems to be signal group+ID followed by two ints

		// System.out.println("signalGroupIntervalMeasurement count=" + n_bytes
		// );
		// for( int i = 0; i < n_bytes ; i++ ) {
		// int b = ndoBuffer.get();
		// if( b < 0 ) {
		// b += 256;
		// }
		// System.out.print( Integer.toHexString(b ));
		// System.out.print(" " );
		// }
		// System.out.println();

	}

	private void parseVentWaveformDescription(ByteBuffer ndoBuffer) {
		byte num_vent_desc = ndoBuffer.get();
		byte spare = ndoBuffer.get();
	}

	private void parseVentVolWaveformDescription(ByteBuffer ndoBuffer) {
		// unknown number of NdoWaveformDescStruct's
	}

	private void parseVentParamList(ByteBuffer ndoBuffer) {
		byte num_params = ndoBuffer.get();
		byte pad = ndoBuffer.get();

		for (int i = 0; i < num_params; i++) {
			byte signal = ndoBuffer.get();
			byte param_id = ndoBuffer.get();
		}
	}

	private void parseVentCurrentMsg(ByteBuffer ndoBuffer) {
		// WARNING: this may be the same as parseCurrentMsgDisplayed(ByteBuffer
		// ndoBuffer)

		StringBuffer message = new StringBuffer();
		for (int i = 0; i < CURR_MSG_SIZE; i++) {
			char ch = ndoBuffer.getChar();
			if (ch == 0) {
				break;
			}
			message.append(ch);
		}
		String msg_string = message.toString().trim();
		byte msg_chars_plus_null = ndoBuffer.get();
		byte foreground_color = ndoBuffer.get();
		byte background_color = ndoBuffer.get();
		byte audio_tone = ndoBuffer.get();

		// ServerMessage msg = new ServerMessage();
		// msg.addOrUpdateParameter("message", msg_string);

		if (msg_string.length() > 0) {
			log.warn("FIXME: Fire drager vent message: {}", msg_string);
		}
	}

	private void parseParameterBoxSetup(ByteBuffer ndoBuffer) {

		int n_pboxes = ndoBuffer.get(); // NdoPboxSetupStruct
		int pad1 = ndoBuffer.get();

		if (display.getNumPBoxes() != n_pboxes) {
			config_changed = true;
			display.clearPBoxes(); // add them back as needed
		}

		for (int i = 0; i < n_pboxes; i++) {
			ParameterLayout pbox = display.getPBox(i);

			byte pbox_id = ndoBuffer.get(); // NdoWaveformBandStruct
			byte pbox_format = ndoBuffer.get(); // ...enum BAND_ATTRIBUTE
			byte num_params = ndoBuffer.get();
			byte foreground = ndoBuffer.get();

			byte background = ndoBuffer.get();
			byte is_flashing = ndoBuffer.get();

			if (pbox == null) {
				pbox = new ParameterLayout(pbox_id, pbox_format, foreground, null);
				display.addParamBox(pbox);
				config_changed = true;
			}
			if (pbox.getBackground() != background || pbox.getForeground() != foreground) {
				pbox.setForeground(foreground);
				pbox.setBackground(background);
				config_changed = true;
			}

			if (pbox.fields == null || pbox.fields.length != num_params) {
				pbox.fields = new FieldData[num_params];
				config_changed = true;
			}

			for (int j = 0; j < num_params; j++) {
				byte signalGroup = ndoBuffer.get();
				short paramId = ndoBuffer.get();
				byte uom = ndoBuffer.get();
				byte pad = ndoBuffer.get();

				DataPair pair = findMetric(signalGroup, paramId);

				// WARNING: may need to set UOM

				FieldData setup = null;
				if (pair != null) {
					setup = new FieldData(pair.metric.getLocation(), uom);
				}

				pbox.fields[j] = setup;

				if (pair == null) {
					log.error("FIXME? PARAM NOT FOUND code={}.{}", getSignalGroup(signalGroup), getParamCode(paramId));
				}
			}
		}

		// if bands is null, we haven't received the band config yet
		if ((initial_config || config_changed) && display.getBands() != null) {
			fireDisplayEvent(this, display);
			initial_config = false;
			config_changed = false;
		}

	}

	@Override
	public void fireStreamEvent(int jobId, StreamProducer src, StreamID sid, PersistentItem block) {
		if (dout != null) {
			dumpEvent(dout, now() - ts, jobId, src, sid, block);
		}
		super.fireStreamEvent(jobId, src, sid, block);
	}

	private void parseParameterAndAlarm(ByteBuffer ndoBuffer) {
		Map<Class<?>, PersistentItem> hm_item = new HashMap<Class<?>, PersistentItem>();
		hm_item.put(DragerDelta_Measurements.class, measures);

		byte num_params = ndoBuffer.get();
		byte bytes_per_param = ndoBuffer.get();

		for (int i = 0; i < num_params; i++) {
			short param_val = ndoBuffer.getShort();
			short param_upper_limit = ndoBuffer.getShort();
			short param_lower_limit = ndoBuffer.getShort();
			short alarm_limit = ndoBuffer.getShort();
			getTimestamp(ndoBuffer); // paramTimestamp
			getTimestamp(ndoBuffer); // alarmTimestamp
			byte signal_group = ndoBuffer.get();
			byte param_id = ndoBuffer.get();
			byte param_val_id = ndoBuffer.get();
			byte alarm_attrib = ndoBuffer.get();
			byte unit_of_measure = ndoBuffer.get();
			byte units_exp = ndoBuffer.get();
			byte show_units = ndoBuffer.get();
			byte alarm_condition = ndoBuffer.get();
			byte alarm_state = ndoBuffer.get();
			byte alarm_grade = ndoBuffer.get();
			byte curr_param_color = ndoBuffer.get();
			byte default_param_color = ndoBuffer.get();
			byte limits_type = ndoBuffer.get();
			byte background_color = ndoBuffer.get();
			byte is_flashing = ndoBuffer.get();
			byte num_decimals_to_display = ndoBuffer.get();

			DataPair pair = findMetric(signal_group, param_id);

			if (pair == null) {
				String loc = getSignalGroup(signal_group) + "." + getParamCode(param_id);

				RpUnit u = new RpPrecisionUnit(-units_exp, NetUnitsOfMeasure.toText(unit_of_measure));
				RpMetric metric = new RpMetric(loc, loc, null, u, DataTyp.INT_TYP);
				pair = new DataPair(metric, null);

				hm_mea.put(loc, pair);
			} else {
				String uom_text = NetUnitsOfMeasure.toText(unit_of_measure);
				RpPrecisionUnit u = (RpPrecisionUnit) pair.metric.getUnit();

				// FIXME: 21APR16 wlb
				if (uom_text == null) {
					log.warn("Unknown UOM measure: {}", unit_of_measure);
				} else if (uom_text.equals(u.getUnitName())) {
					// match
				} else {
					log.error(pair.metric.getLocation() + "FIXING UOM MISMATCH: {} != {}", u.getUnitName(), uom_text);
					u.setUnitName(uom_text);
				}

				// FIXME: 21APR16 wlb -- fix precision
				if (-units_exp != u.getPrecision()) {
					log.error(pair.metric.getLocation() + "FIXING PRECISION {} != {}", (int) -units_exp,
							u.getPrecision());
					u.setPrecision(-units_exp);
				}

			}

			RpMetric metric = pair.metric;
			if (autoConfig || metric.isActive()) {
				PersistentItem item = hm_item.get(pair.cl);
				if (item == null && pair.cl != null) {
					item = ModelUtil.getModelFromDataClass(pair.cl);
					if (item != null) {
						item.setTime( now() );
						if (item instanceof DragerDelta_MibBIS) {
							measures.setBis((DragerDelta_MibBIS) item);
						} else if (item instanceof DragerDelta_MibBIS) {
							measures.setMgm((DragerDelta_MibMGM) item);
						} else if (item instanceof DragerDelta_MibSVO2) {
							measures.setSvo2((DragerDelta_MibSVO2) item);
						} else if (item instanceof DragerDelta_MibVent) {
							measures.setVent((DragerDelta_MibVent) item);
						}
						hm_item.put(pair.cl, item);
					}
				}

				if (item == null) {
					log.debug("ALARM could not save item: {}/{}", metric, pair.cl);
				} else {
					IntfUtil.setValue(item, metric, param_val);
				}
			}

		}

		// TODO: 1- remove extra metrics
		// TODO: 2- indicate config/caps should be resent

		if (vitalsSkipCount > 1) {
			numeric_idx++;
			numeric_idx %= vitalsSkipCount;
			if (numeric_idx == 0) {
				measures.setTime(now());
				this.fireStreamEvent(0, this, StreamID.MEASUREMENT, measures);
				measures = new DragerDelta_Measurements();
			}
		} else {
			this.fireStreamEvent(0, this, StreamID.MEASUREMENT, measures);
		}
		tick = 0;
	}

//	private void clearNumerics() {
//		if (measures != null) {
//			IntfUtil.clear(measures);
//		}
//	}

	private final static String[] sig_gr_codes = { //
			"invalid", //
			"ecg", "resp", "art", "pa", "icp", "cvp", "la", "ra", "lv", "rv", // 10
			"gp1", "gp2", //
			"p1a", "p1b", "p1c", "p1d", //
			"p2a", "p2b", "p2c", "p2d", //
			"p3a", "p3b", "p3c", "p3d", //
			"spo2", // 25
			"tbasic", //
			"temp1", "temp2", "temp3", //
			"nibp", // 30
			"a2co2", "co", "ibp", "alarm", //
			"mib_svo2", "mib_vent", //
			"mgm_co2", //
			"mgm_o2", "mgm_n2o", "mgm_agent", // 40
			"svo2", "eeg", "vent", "crg", "gas", //
			"tcpo2", "o2p", "n2op", "airp", "mib_pao2", // 50
			"vcalc", "p1", "p2", "nco", "tcp", "tcp2", "fio2", "trend", "eeg1", "eeg2", "eeg3", "eeg4", // 62
			"awco2", "icp2", "bis", "labdat", "ventset", "spo2athena", "nmt", "fasttemp", // 70
			"cncco", "cnap", "pic", "74", "75", "76", "77", "78", "79", "80", // 80
			"81", "82", "83", "84", "85", "86", "87", "88", "89", "90", //
			"91", "92", "93", "94", "95", "96", "97", "98", "99", "100", //
			"101", "102", "103", "104", "105", "106", "107", "108", "109", "110", //
			"111", "112", "113", "114", "115", "116", "117", "118", "119", "120", //
			"121", "122", "123", "124", "125", "126", "127", "128", "129", "130", //
	};

	private final static String[] sensor_codes = { //
			"invalid", //
			null, // only one in group...don't add extension
			"lead_I", "lead_II", "lead_III", "lead_AVR", "lead_AVF", "lead_AVL", "lead_V1", "lead_MCL1", "lead_MCL6", //
			"lead_RA", "lead_LA", "lead_LL", "lead_RL", "lead_VL", //
			"temp_a", "temp_b", //
			"co_blood", "co_inj", //
			"ir", "red", "pulse", // spo2
			"cascade", // ecg
			"raw_cuff", "lp_cuff", "pulse_ext", // nibp
			"press", "flow", "hal", "iso", "enf", "sev", "des", // agent...anestesia?
			"lead_v_prime", // ecg
			"dr", // nco
			"lead_V", "lead_V2", "lead_V3", "lead_V4", "lead_V5", "lead_V6", // ecg
			"vol", //
			"lead_DV1", "lead_DV2", "lead_DV3", "lead_DV4", "lead_DV5", "lead_DV6", // ecg
			// derived
			"eeg1", "eeg2", // eeg
			"lead_avr_imv", // ecg
			"last" };

	private final static String[] param_codes = { //
			"invalid", //
			"hr", "pp", "arr", "pvc", "pr", "rr", "dia", "sys", "mean", "cpp", // 10
			"a", "b", "delta", "satu", "etco2", "ico2", "co", "co_avg", "ti", "tb", // 20
			"pwp", "sa1", "svo2", "sao2", "cco", "cci", "ico", "ici", "svr", "svri", // 30
			"do2", "vo2", "sv", "sqi", "ref", "pap", "peep", "map", "mv", "tv", // 40
			"pause", "ieratio", "eto2", "io2", "etn2o", "in2o", "ethal", "ihal", "etiso", "iiso", // 50
			"etenf", "ienf", "etsev", "isev", "etdes", "ides", "st1", // ECG
																		// starts
																		// here
																		// -- 57
			"st2", "st3", "stavr", // 60
			"stavf", "stavl", "stv1", "mcl1", "mcl6", "st", "mvi", "tvi", "wallp", "tankp", // 70
			"pvr", "pvri", "svi", "tvr", "tpr", "lvsw", "lvswi", "rvsw", "rvswi", "lhcpp", // 80
			"rpi", "pao2", "pvo2", "paco2", //
			"vco2", //
			"cao2", "cvo2", "avdo2", "do2i", "vo2i", // vent calcs
			"o2er", "aado2", "qsqt", "cdyn", //
			"cs", "ri", "re", "eef", "vd", "vtp_ration", "vta_ratio", "alvent", "wob", // end
			// vent
			// calcs
			"st_vprime", "nco", "nsv", "stv2", "stv3", "stv4", "stv5", "stv6", "stv", "stvm", "stcvm", "stx", "sty",
			"stz", "o2", "co2", "htrpwr", "stlead", "nosubscript", "trendmarker", "median", "sef", "bsr", "tot_pwr",
			"beta_pwr", "alpha_pwr", "theta_pwr", "delta_pwr", "pip", "tvi_mech", "tvi_spon", "tva", "tot_mv", "mva",
			"mv_spon", "vd_aw", "c_dyn", "c_stat", "c2o_dyn", "eraw", "iraw", "wo_bimp", "vd_vt", "vd_phy", "vol_delta",
			"pleth", "pplat", "bis", "emg", "sr", "power", "ipeep", "pif", "pef", "tve_mech", "tve_spon", "mve_mech",
			"mve_spon", "rr_mech", "rr_spon", "c_total", "rsbi", "wob_mech", "tv_ratio", "mvco2", "tvco2", "tva_spon",
			"tva_mech", "mva_spon", "mva_mech", "peco2", "dilut_ratio_aw", "insp_time", "exp_time", "insp_time_pct",
			"tv_leak", "mv_pct", "ph", "hco3", "hct", "hgb", "raw", //
			"deriv_v1", "deriv_v2", "deriv_v3", "deriv_v4", "deriv_v5", "deriv_v6", "current", "twitch", //
			"tof_ratio", "tof_count", "pct_count", "temp", "bct", "mac", "bat", "pco", //
			"gedv", "gedvi", "evlw", "evlwi", "gef", "pbt", "pvpi", "pcco", "pcci", "psvi", "svv", //
			"psvr", "psvri", "dpmax", "edv", "esv", "esvi", "ef", "tair", "t1skin", "t2skin", "wt", //
			"rh", "pcto2", "tmatt", "pwrhtr", "tair_set", "tskin_set", "rh_set", "o2_set", "tmatt_set", "etvi", "234",
			"235", "236", "237", "238", "239", //
			"240", "241", "242", "243", "244", "245", "246", "247", "248", "249", //
			"250", "251", "252", "253", "254", "255" //
	};

	public static String getSignalGroup(int idx) {
		if (idx < 0) {
			idx += 256;
		}
		if (idx > sig_gr_codes.length) {
			return "" + idx;
		}
		return sig_gr_codes[idx];
	}

	public static String getParamCode(int idx) {
		if (idx < 0) {
			idx += 256;
		}
		if (idx > param_codes.length) {
			return "" + idx;
		}
		return param_codes[idx];
	}

	public void setAutoConfig(boolean autoConfig) {
		this.autoConfig = autoConfig;
	}

	public boolean getAutoConfig() {
		return autoConfig;
	}

	// should not be public
	public DataPair findMetric(int signalGroup, int paramId) {
		DataPair pair = null;

		if (signalGroup < 0) {
			signalGroup += 256;
		}
		if (paramId < 0) {
			paramId += 256;
		}

		String sig_group = null;
		if (signalGroup < sig_gr_codes.length) {
			sig_group = sig_gr_codes[signalGroup];
		}

		String p_name = null;
		if (paramId < param_codes.length) {
			p_name = param_codes[paramId];
		}

		if (sig_group != null && p_name != null) {
			String m_name = sig_group + "." + p_name;
			pair = hm_mea.get(m_name);
		}

		if (pair == null) {
			if (sig_group == null)
				sig_group = "(" + signalGroup + ")";
			if (p_name == null)
				p_name = "(" + paramId + ")";

			log.debug("unknown metric: {}.{}", sig_group, p_name);
		}

		return pair;
	}

	/**
	 * Find the waveform description.
	 * 
	 * This uses a different code table than findMetric()
	 */
	protected DataPair findWaveform(int signalGroup, int signalId) {
		String key = sig_gr_codes[signalGroup];
		String xtension = sensor_codes[signalId];
		if (xtension != null) {
			key = key + " " + xtension;
		}
		DataPair desc = hm_mea.get(key);
		if (desc == null) {
			log.error("WV NOT FOUND: {}", key);
		}
		// System.out.println( "found wf: " + desc );
		return desc;
	}

	private void getTimestamp(ByteBuffer ndoBuffer) {
		for (int i = 0; i < 6; i++) {
			ndoBuffer.get();
		}

		return; // ts
	}

	private void parseCurrentMsgDisplayed(ByteBuffer ndoBuffer) {

		String msg_string = getFixedLengthString(ndoBuffer, CURR_MSG_SIZE);

		byte msg_chars_plus_null = ndoBuffer.get();
		byte foreground_color = ndoBuffer.get();
		byte background_color = ndoBuffer.get();
		byte audio_tone = ndoBuffer.get();

	}

	private String getFixedLengthString(ByteBuffer ndoBuffer, int sz) {
		StringBuffer message = new StringBuffer();
		boolean more = true;
		for (int i = 0; i < sz; i++) {
			char ch = ndoBuffer.getChar();
			if (ch == 0) {
				more = false;
			}
			if (more) {
				message.append(ch);
			}
		}
		return message.toString().trim();
	}

	private void parseWaveformSetup(ByteBuffer ndoBuffer) {
		boolean config_changed = request_display_refresh;
		boolean scale_changed = false;

		int n_bands = ndoBuffer.get(); // NdoWaveformSetupStruct
		int pad1 = ndoBuffer.get();

		List<BandLayout> bands = display.getBands();

		int reserved_bands = 0;
		if (horiz_pboxes > 0) {
			reserved_bands = 1;
		}
		if (bands == null || bands.size() != (n_bands - reserved_bands)) {
			if (n_bands <= reserved_bands) {
				log.error("Invalid number of bands: " + n_bands + " <= " + reserved_bands);
				return;
			}
			BandLayout[] arr = new BandLayout[n_bands - reserved_bands];
			bands = Arrays.asList(arr);
			config_changed = true;
			display.setBands(bands);
		}

		// System.out.print("INF n_bands=" + n_bands + " PARAM REFRESH=" +
		// config_changed);
		for (int i = 0; i < n_bands; i++) {
			byte band_number = ndoBuffer.get(); // NdoWaveformBandStruct
			byte band_attribute = ndoBuffer.get(); // ...enum BAND_ATTRIBUTE
			byte num_waveforms = ndoBuffer.get();
			byte spare = ndoBuffer.get();

			// When band_attribute is 1, the band is covered by an overlapping
			// band
			// System.out.print(" " + (int) band_attribute);

			BandLayout bband = null;

			if (i < bands.size()) {
				bband = bands.get(i);
				if (bband == null) { // just allocated above
					bband = new BandLayout(band_number, band_attribute);
					bands.set(i, bband);
				}
			}

			if (bband != null && bband.getNumWaves() != num_waveforms) {
				WaveformData[] waves = new WaveformData[num_waveforms];
				config_changed = true;
				bband.setWaves(new LinkedList<WaveformData>(Arrays.asList(waves)));
			}

			// List<WaveformSetupData> waves = band.getWaves();
			for (int j = 0; j < num_waveforms; j++) {
				WaveformData wf_setup = new WaveformData();
				wf_setup.setSweepSpeed(ndoBuffer.getShort());
				wf_setup.setWaveSampleRate(ndoBuffer.getShort());
				short scale1 = ndoBuffer.getShort();
				short scale2 = ndoBuffer.getShort();
				byte signal_group = ndoBuffer.get();
				byte param_id = ndoBuffer.get();
				wf_setup.setWaveColor(ndoBuffer.get());
				wf_setup.setScaleDescriptor(ndoBuffer.get());
				wf_setup.topOverlay = ndoBuffer.get();
				wf_setup.bottomOverlay = ndoBuffer.get();
				wf_setup.setUom(ndoBuffer.get());
				wf_setup.setUomExp((byte) -ndoBuffer.get());

				if (bband == null) {
					log.error("LAST BAND CAN BE NULL, BUT SHOULD NO HAVE WF'S!");
					continue;
				}

				if (wf_setup.bottomOverlay != 0 || wf_setup.topOverlay != 0) {
					System.err.println("GOT A BOTTOM/TOP OVERLAY ON J=" + j //
							+ " BO:" + (int) wf_setup.bottomOverlay //
							+ " TO:" + (int) wf_setup.topOverlay //
					);
				}

				DataPair pair = findWaveform(signal_group, param_id);
				if (pair == null) {
					continue;
				}
				RpMetric desc = pair.metric;
				if (desc == null) {
					wf_setup.setRangeMin(scale1);
					wf_setup.setRangeMax(scale2);

					log.error("ADD WF: " + getSignalGroup(signal_group) + "." + getParamCode(param_id));
				} else {
					RpUnit unit = desc.getUnit();

					String loc = desc.getLocation();
					String u_name = NetUnitsOfMeasure.toText(wf_setup.getUom());

					// FIXME: 21APR16 WLB da ist an error here
					// if (!u_name.equals(unit.getUnitName())) {
					// log.error(loc + " UOM= {} != {}", unit.getUnitName(),
					// u_name);
					// }
					//
					// if (unit instanceof RpPrecisionUnit) {
					// RpPrecisionUnit pu = (RpPrecisionUnit) unit;
					// if (wf_setup.getUomExp() != pu.getPrecision()) {
					// log.error(loc + " EXP {} != {}", wf_setup.getUomExp(),
					// pu.getPrecision());
					// }
					// }

					if (wf_setup.getScaleDescriptor() == 0) {
						// System.out.print( loc );
						// System.out.print(" PRE scale1,2=" + scale1 + "," +
						// scale2 );
						// System.out.println();
						// request_display_refresh = true;
						int delta = scale1 - scale2;
						int offset = (int) (1.7 * delta);
						int t = scale1;
						scale1 = (short) (2.5 * scale2 - offset);
						scale2 = (short) (2.5 * t - offset);

						// FIXME: this can be condensed to two linear
						// equations...but I didnt
						// int t = scale1;
						// scale1 = (short)(scale2 - 120);
						// scale2 = (short) (2.5 * t - 150);
					}
					// if (loc.startsWith("ecg ")) {
					// RpPrecisionUnit pu = (RpPrecisionUnit) unit;
					// System.out.print(loc);
					// System.out.print(" EXP_" + (int) wf_setup.getUomExp() +
					// "==?" + pu.getPrecision());
					// System.out.print(" scale1,2=" + scale1 + "," + scale2);
					// System.out.println(" unit=" + unit);
					//
					// System.out.print(" SD=" + (int)
					// wf_setup.getScaleDescriptor());
					// System.out.print(" TOP=" + (int) wf_setup.topOverlay);
					// System.out.print(" BOT=" + (int)
					// wf_setup.bottomOverlay);
					// System.out.println();
					// }
					wf_setup.setRangeMin(scale1);
					wf_setup.setRangeMax(scale2);
				}
				// config_changed = true;

				if (!config_changed && !scale_changed) {
					WaveformData ref = bband.getWave(j);
					scale_changed = ref.getRangeMin() != wf_setup.getRangeMin();
					scale_changed |= ref.getRangeMax() != wf_setup.getRangeMax();
					scale_changed |= ref.getSweepSpeed() != wf_setup.getSweepSpeed();
				}
				if (!config_changed) {
					WaveformData ref = bband.getWave(j);
					String loc0 = ref.getLoc();
					String loc1 = wf_setup.getLoc();
					if (loc0 == null) {
						config_changed = (loc1 != null);
					} else {
						config_changed = loc0.equals(loc1);
					}

					if (config_changed) {
						log.debug("CONFIG_CHANGED CFGCHANGE={} {} ", loc0, loc1);
					}

				}

				if (scale_changed || config_changed) {
					bband.setWaves(j, wf_setup);
				}

				if (desc == null) {
					log.error("WAVE NOT FOUND > {}/{}", signal_group, param_id);
				} else {
					wf_setup.setLoc(desc.getLocation());
					if (desc.getSampleRate() != wf_setup.getWaveSampleRate()) {
						log.warn("SAMPLE RATE: {} != {} FOR: " + desc.getCode(), desc.getSampleRate(),
								wf_setup.getWaveSampleRate());
					}
				}
			}

		}

		// System.out.println(" YOU GOT IT");

		if (config_changed && display.getParameterBoxs() != null) {
			log.warn("FIRED AT POSITION-0");
			fireDisplayEvent(this, display);
			request_display_refresh = false;
		}
	}

	private void parseBedConfig(ByteBuffer ndoBuffer) {
		DragerDelta_Demographics demographics_block = new DragerDelta_Demographics();

		String pat_pname = getFixedLengthString(ndoBuffer, PATIENT_NAME_SIZE);
		String pat_initials = getFixedLengthString(ndoBuffer, PATIENT_INITIALS_SIZE);
		String bed_label = getFixedLengthString(ndoBuffer, BED_LABEL_SIZE);
		int loc_control = ndoBuffer.getShort();
		int rmt_control = ndoBuffer.getShort();
		int barometric_pressure = ndoBuffer.getShort();
		short pat_name_chars_plus_null = ndoBuffer.get();
		short pat_initials_chars_plus_null = ndoBuffer.get();
		short bed_label_chars_plus_null = ndoBuffer.get();
		short freq_response = ndoBuffer.get();
		short alarm_vol_percent = ndoBuffer.get();
		short language = ndoBuffer.get();
		short banners = ndoBuffer.get();
		short pat_category = ndoBuffer.get(); // 1==ADULT
		short alarm_tones_mode = ndoBuffer.get();
		short banners2 = ndoBuffer.get();

//		System.out.println("BED CoNFIG; " + sconf.getConnectionValue() + " b2=" + banners2 + //
//				" ctg=" + pat_category + " loc=" + loc_control + " remote=" + rmt_control + //
//				" baro=" + barometric_pressure + " freq=" + freq_response + " bed:" + bed_label + " atmode: "
//				+ alarm_tones_mode);
//		System.out.println("   name: " + pat_pname + " initials: " + pat_initials + " banner:" + banners );
		
		demographics_block.setName(pat_pname);
		demographics_block.setInitials(pat_initials);
		demographics_block.setBed(bed_label);

		fireStreamEvent(0, this, StreamID.DDDEMOGRAPHICS, demographics_block);
	}

	private final static String[] param_device_cond_codes = { //
			"invalid", "basic_pod_disc", "pod1_disc", "pod2_disc", "pod3_disc", "pod4_disc", "nibp_cart_disc",
			"airway_co2_cart_disc", "basic_pod_hw_failure", "pod1_hw_failure", "pod2_hw_failure", "pod3_hw_failure",
			"pod4_hw_failure", "nibp_cart_disc", "airway_co2_hw_failure", "upper_limit_viol", "lower_limit_viol",
			"persist_leads_invalid", "persist_artifact", "cuff_pressure", "zero_offset", // 20
			"all alarms off", "too_old", "param_too_high", "param_too_low", "apnea", "cannot_derive_param",
			"mon_disabled", "unplugged", "hw_failure", "transducer_failure", "leads_invalid", "artifact",
			"signal_too_high", "signal_too_low", "lead_unavailable", "measurement_timeout", "saturated", "please_zero",
			"zeroing", "zero_complete", // 40
			"zero_out_of_range", "zero_not_static", "zero_before_cal", "cal_in_progress", "cal_complete",
			"cal_out_of_range", "cal_not_static",
			// Event and Beat Classification (Drager Manual p9-3)
			"asy", // Asystole
			"vf", // Ventricular Fibrillation
			"vt", // Ventricular Tachycardia // 50
			"run", // Ventricular Run
			"ivr", // Idioventricular Rhythm
			"svt", // Supraventricular Rhythm
			"cpt", // Ventricular Couplet
			"bgm", // Ventricular Bigeminy
			"tach", // Sinus Tachycardia
			"brady", // Sinus Bradycardia
			"pnc", // Pacer Non-capture
			"paus", // Missed Beat // 60
			"ront", // // R on top of T Wave
			"btc_art", // Beat Classification Artifact
			"paced", // Paced Rhythm
			"irreg", // Irregular Rhythm
			"learning", "please_learn", "reg", "la_off", "ra_off", "ll_off", "rl_off", "chest_off", "static",
			"art static press", "opaque", "transparent", "weak_signal", "searching", "regulation", "unsupported_probe" // 80
			// ... TO BE CONTINUED
			, "80" //
			, "81", "82", "83", "84", "85", "86", "87", "88", "89", "90" //
			, "91", "92", "93", "94", "95", "96", "97", "98", "99", "100" //
			, "101", "102", "103", "104", "105", "106", "none: alarms active", "108", "109", "110" //
			, "111", "replace_sensor", "113", "114", "115", "116", "117", "118", "119", "120" //
			, "121", "122", "123", "124", "125", "126", "127", "128", "129", "130" //
			, "131", "132", "133", "134", "135", "136", "137", "138", "139", "140" //
			, "141", "142", "143", "144", "145", "146", "147", "148", "149", "150" //
			, "151", "152", "153", "154", "155", "156", "157", "158", "159", "160" //
			, "161", "162", "163", "artifact", "weak_signal", "166", "167", "168", "169", "170" //
	};

	private void parseSummaryAlarmInfo(ByteBuffer ndoBuffer) {
		long now = now();

		List<Alarm> currAlarms = new LinkedList<Alarm>();
		while (ndoBuffer.hasRemaining()) {
			short alarm_limit = ndoBuffer.getShort();
			getTimestamp(ndoBuffer); // alarmTimestamp
			byte current_alarm_tone_grade = ndoBuffer.get();
			byte alarm_group_id = ndoBuffer.get();
			byte signal_group = ndoBuffer.get();
			byte param_id = ndoBuffer.get();
			byte alarm_condition = ndoBuffer.get();
			byte alarm_state = ndoBuffer.get();
			byte alarm_grade = ndoBuffer.get();
			byte is_flashing = ndoBuffer.get();
			byte foreground_color = ndoBuffer.get();
			byte background_color = ndoBuffer.get();

			int cond = alarm_condition;
			if (cond < 0)
				cond += 256;

			String paramName = "??";
			// RpMetric metric = null;
			DataPair pair = findMetric(signal_group, param_id);
			if (pair == null) {
				paramName = signal_group + "/" + param_id;
			} else {

				paramName = pair.metric.getCode();
			}

			String pdc_code = "<unknown>";

			if (cond < param_device_cond_codes.length) {
				pdc_code = param_device_cond_codes[cond];
			}
			if (pdc_code != null && pdc_code.equals("all alarms off")) {
				// ignore
			} else {
				Alarm ai = findAndRemoveAlarm(lastAlarms, cond, paramName);
				if (ai == null) {
					ai = new Alarm(paramName, Alarm.WARNING, cond, paramName + ": " + pdc_code, true);
					ai.setTm(new Date(now));
					fireAlarmEvent(this, ai);
					log.debug(" alarm on: {}", ai);
				}

				if (continuousAlarms == false) {
					currAlarms.add(ai);
				}
			}
		}

		if (continuousAlarms == false) {
			for (Alarm ai : lastAlarms) {
				ai.setActive(false);
				ai.setTm(new Date(now));
				ai.setMessage(ai.getMessage() + " / OFF");
				fireAlarmEvent(this, ai);

				log.debug(" alarm off: {}", ai);
			}
		}
		lastAlarms = currAlarms;

	}

	private Alarm findAndRemoveAlarm(List<Alarm> list, int code, String paramName) {
		Iterator<Alarm> it = list.iterator();
		while (it.hasNext()) {
			Alarm item = it.next();

			if (item.getCode() == code && paramName.equals(item.getDevParam())) {
				it.remove();
				return item;
			}
		}
		return null;
	}

	/*
	 * parse the waveform ndo
	 * 
	 * 00:05: # sent each time set of wvf types changes 05: # num waves 00: #
	 * channel id 00:00: # extern data hight / data low 00:00: # register_number /
	 * register_data
	 * 
	 * WF 1 -- NdoWaveform Data Header Struct 00:c8: # sample rate 00:5e: # block
	 * len 02:12: 21:95: bc:1f: 01:02: # timestamp 28: # num samples 00: # spare
	 * 00:01:00:01:00:01:00:01:00:01: 00:01:00:01:00:01:00:01:00:01:
	 */
	private void parseWaveform(ByteBuffer ndoBuffer) {
		Map<Class<?>, PersistentItem> hm_item = new HashMap<Class<?>, PersistentItem>();
		hm_item.put(DragerDelta_Sensors.class, sensors);

		short wvf = ndoBuffer.getShort();
		byte n_waves = ndoBuffer.get();
		byte channelId = ndoBuffer.get();
		short dhdl = ndoBuffer.getShort();
		short rnrd = ndoBuffer.getShort();

		boolean reconfig = false;

		sensors.setTime(now());

		int sig_count = 0;
		for (int i = 0; i < n_waves; i++) {

			int sampleRate = ndoBuffer.getShort();
			int blockLen = ndoBuffer.getShort();

			int tm = ndoBuffer.getInt(); // timestamp
			int tmb1 = ndoBuffer.getShort();

			int signal_group = ndoBuffer.get();
			int sensor_id = ndoBuffer.get();

			int n_samples = ndoBuffer.get();
			byte spare = ndoBuffer.get();

			DataPair pair = findWaveform(signal_group, sensor_id);
			RpMetric desc = null;
			if (pair == null || pair.metric == null) {
				log.warn("Could not find waveform: {}/{}", signal_group, sensor_id);
			} else {
				desc = pair.metric;
			}

			if (desc != null && !desc.isActive() && autoConfig) {
				reconfig = true;
				desc.setActive(true);
			}

			if (desc != null && desc.isActive()) {
				PersistentItem item = hm_item.get(pair.cl);
				if (item == null) {
					item = ModelUtil.getModelFromDataClass(pair.cl);
					
					if (item != null) {
						item.setTime( now() );
						if (item instanceof DragerDelta_SensorsAnaesthesia) {
							sensors.setAna((DragerDelta_SensorsAnaesthesia) item);
						} else if (item instanceof DragerDelta_SensorsEKG5) {
							sensors.setEkg5((DragerDelta_SensorsEKG5) item);
						} else if (item instanceof DragerDelta_SensorsEKG12) {
							sensors.setEkg12((DragerDelta_SensorsEKG12) item);
						}
						hm_item.put(pair.cl, item);
					}
				}

				int[] data = (int[]) IntfUtil.getRawValue(item, desc);
				if (data == null || data.length != n_samples) {
					data = new int[n_samples];
					IntfUtil.setValue(item, desc, data);
				}
				for (int j = 0; j < n_samples; j++) {
					short point = ndoBuffer.getShort();
					data[j] = point / 4;
				}

				sig_count++;
			} else {
				// throw it away
				for (int j = 0; j < n_samples; j++)
					ndoBuffer.getShort();
			}

		}

		if (reconfig || send_initial_caps) {
			incrementFileRevision();
			fireCapabilitiesEvent(this, caps);
			send_initial_caps = false;
		}

		if (sig_count > 0) {
			fireStreamEvent(0, this, StreamID.WAVEFORM, sensors);
		}

		tick = 0;
	}

	private void incrementFileRevision() {
		caps.setRevNo(rev_no);
		rev_no++;
	}

	private void parseDisplaySetup(ByteBuffer ndoBuffer) {
		short alarm_suspend_timeout = ndoBuffer.getShort(); // time remaining
															// for alarm suspend
		short num_bands = ndoBuffer.get();
		short num_pboxes = ndoBuffer.get();
		short pbox1_pos = ndoBuffer.get();
		short pbox_order = ndoBuffer.get();
		horiz_pboxes = ndoBuffer.get();
		short vert_pboxes = ndoBuffer.get();
		short alarm_limit_display = ndoBuffer.get();
		short pacer_detect = ndoBuffer.get();
		short pacer_spike_display = ndoBuffer.get();
		short resp_spike_display = ndoBuffer.get();
		byte opmode = ndoBuffer.get();
		short alarm_suspend = ndoBuffer.get(); // flag. mask 0x01 --> alarm
												// suspended
		short notes_counter = ndoBuffer.get();
		short pboxIconDisplay = ndoBuffer.get();

//		if (opmode == 0) {
//			System.out.print("INF OPMODE=" + opmode + " " + sconf.getConnectionValue());
//			System.out.println(" PBOX=" + pbox1_pos + " " + vert_pboxes + " " + num_pboxes + " num_bands: " + num_bands);
//		}
		// i can't find a clear way to see the "Discharged" mode, so i use this
		discharged = ((vert_pboxes <= 1) && (num_pboxes <= 1));
		if( discharged ) { 
			// opmode 1 == standby
			opmode = 3;  // you would think that this was the default behavior for Drager
		}
		
		this.opmode = opmode;  // write to the field

		boolean changed;

		changed = (display.getPbox1Pos() != pbox1_pos);
		changed |= (display.getVertPboxes() != vert_pboxes);
		changed |= (display.getOpmode() != opmode);

		if (changed) {

			// display.setNumBands(num_bands);
			// display.setNumPboxes(num_pboxes);
			display.setPbox1Pos(pbox1_pos);
			display.setVertPboxes(vert_pboxes);
			display.setOpmode(opmode);

			// DONT CALL DISPLAY HERE...set a refresh request to --> true
			config_changed = true;
		}

	}

	public void requestDisplayRefresh() {
		request_display_refresh = true;
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, static_cap);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return static_cap;
	}

	@Override
	public RpDevice getConfiguration() {
		return sconf;
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (getStatus() != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
				fireNoData(caps);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		return 0;
	}

	public void setConfiguration(RpDevice conf) {
		this.sconf = conf;
		this.caps = new DeviceCapabilities(sconf);

		AdapterUtil.fix_config(static_cap, conf);

		config_changed = true;
		initial_config = true;

		// measures.setDriver(this);
		// sensors.setDriver(this);
	}

	public void setContinuousAlarms(boolean b) {
		continuousAlarms = b;
	}

	public DisplayConfig getDisplay() {
		return display;
	}
}
