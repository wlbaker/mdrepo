package idea.driver.intellivue;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;
import static idea.driver.intellivue.C.CMD_CONFIRMED_ACTION;
import static idea.driver.intellivue.C.CMD_CONFIRMED_EVENT_REPORT;
import static idea.driver.intellivue.C.CMD_CONFIRMED_SET;
import static idea.driver.intellivue.C.CMD_EVENT_REPORT;
import static idea.driver.intellivue.C.CMD_GET;
import static idea.driver.intellivue.C.CMD_SET;
import static idea.driver.intellivue.C.NOM_ATTR_ID_LABEL;
import static idea.driver.intellivue.C.NOM_ATTR_NET_ADDR_INFO;
import static idea.driver.intellivue.C.NOM_ATTR_NU_VAL_OBS;
import static idea.driver.intellivue.C.NOM_ATTR_PCOL_SUPPORT;
import static idea.driver.intellivue.C.NOM_MOC_VMS_MDS;
import static idea.driver.intellivue.C.NOM_MOC_VMS_MDS_COMPOS_SINGLE_BED;
import static idea.driver.intellivue.C.ROER_APDU;
import static idea.driver.intellivue.C.ROIV_APDU;
import static idea.driver.intellivue.C.ROLRS_APDU;
import static idea.driver.intellivue.C.RORLS_FIRST;
import static idea.driver.intellivue.C.RORLS_LAST;
import static idea.driver.intellivue.C.RORLS_NOT_FIRST_NOT_LAST;
import static idea.driver.intellivue.C.RORS_APDU;
import icuInterface.ConnectionStatus;
import icuInterface.DriftRectifier;
import icuInterface.LoggingUtil;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import idea.conf.CompositeDescription;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.model.dev.Intellivue_Demographics;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class IntellivueDriver extends AbstractStreamProducer implements AdapterInterface {

	@Override
	public void connect() throws IOException {
		init_blocks();
	}

	private static final short NUMERIC_INVOKE_ID = 1;
	private static final short WAVEFORM_INVOKE_ID = 8;
	private static final short ALERTS_INVOKE_ID = 3;
	private static final short DEMOG_INVOKE_ID = 4;
	private static final short MDS_INVOKE_ID = 5;
	private static final short GET_PRIORITY_LIST_INVOKE_ID = 6;
	public static final int RESERVED_SCOPE = 0;
	private static final short SINGLEPOLL_FLAG = 0; // not used anymore

	private long lastExtendedRequestTM = 0;

	private int ttick;

	protected short session_id = (short) 0xe100;
	protected short p_context_id = 2;
	private static short poll_no = 1;

	DeviceCapabilities default_cap = new DeviceCapabilities(this.getClass());
	DeviceCapabilities caps;

	Intellivue_Demographics demog = new Intellivue_Demographics();
	PersistentItem num_block = null;
	PersistentItem wav_block = null;

	DisplayConfig display = new DisplayConfig();

	protected RpDevice conf;

	private boolean connected;

	private HashMap<Integer, SimpleArraySpecn> cachedArraySpec = new HashMap<Integer, SimpleArraySpecn>();
	//	private HashMap<Integer, SampleArrayFixedValueSpecn> cachedFixedValueSpec = new HashMap<Integer, SampleArrayFixedValueSpecn>();

	DriftRectifier drifter;
	private Class<? extends PersistentItem> measureModel;
	private Class<? extends PersistentItem> sensorModel;

	public IntellivueDriver(RpDevice conf) {

		// other data
		this.conf = conf;
		drifter = new DriftRectifier(2500, 2500, 2);

		caps = new DeviceCapabilities(IntellivueDriver.class);

		/*
		 * MAJOR GROUP: Alarm Group Service
		 */
		// AdapterUtil.fix_config(caps, conf);

		ttick = 1; // initial state
		setStatus(ConnectionStatus.NEGOTIATING);

	}

	protected void init_blocks() {
		log.info("init_blocks for conf={}", conf);
		Calendar cal = Calendar.getInstance();
		DateFormat df = new SimpleDateFormat("yyyyMMddHHmmssSSS");
		String tm = df.format(cal.getTime());

		RpStream stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
		if (stream != null) {
			List<RpMetric> metrics = stream.getMetric();
			try {
				measureModel = ModelUtil.createDynamicModel("Intellivue_Measure" + tm, metrics);
				num_block = ModelUtil.getModelFromDataClass(measureModel);
			} catch (Exception e) {
				log.error("Could not create measure model.", e);
			}
		}
		stream = RpUtil.getStream(conf, StreamID.WAVEFORM);
		if (stream != null) {
			List<RpMetric> metrics = stream.getMetric();
			try {
				sensorModel = ModelUtil.createDynamicModel("Intellivue_Sensor" + tm, metrics);
				wav_block = ModelUtil.getModelFromDataClass(sensorModel);
			} catch (Exception e) {
				log.error("Could not create sensor model.", e);
			}
		}
	}

	public void parsePacket(byte[] data, int off, int len) throws IOException {
		ttick = 0;

		ByteBuffer bb = ByteBuffer.wrap(data, off, len);

		int pos = bb.position();
		byte pkt_type = bb.get();
		bb.position(pos);

		if (pkt_type == C.CN_SPDU_SI) {
			log.error("NOT EXPECTING CONNECTION REQUEST");
		} else if (pkt_type == C.AC_SPDU_SI) {
			AssociationResponse resp = AssociationResponse.parse(bb);

			// resp.dump();
			// resp is ignored...other than the fact that we didnt get an error

			log.warn("FIXME: ASSUMING no error in association response");
			// resp.dump();
			refreshPolls();

		} else if (pkt_type == C.SESS_UNDOC_12) {
			log.warn("ANOTHER SESSION ALREADY OPEN");
			disconnect();
		} else if (pkt_type == C.AB_SPDU_SI) {
			log.warn("HANDLE ABORT CLEANLY!!!!");
			disconnect();
		} else if (pkt_type == C.SESS_DATA_EXPORT) { // DATA EXPORT COMMAND
			parseDataExportCommand(bb);

		} else if (pkt_type == 0x0c) {
			log.warn("UNDOC: resulted of malformed association request?");
			LoggingUtil.dump(bb);
		} else if (pkt_type == 0x0) { // Connect Indication Event
			int nomenclature = bb.getInt();
			if (nomenclature != 0x100) {
				log.error("unexpected nomenclature ver={}", nomenclature);
			}

			short ro_type = bb.getShort();
			short length = bb.getShort();
			switch (ro_type) {
			case ROIV_APDU:
				parseRemoteOperationInvoke(bb);
				break;
			default:
				log.error("Unknown ro_type: {} [connect indication]", ro_type);
				LoggingUtil.dump(bb, 0, bb.limit());
			}

		} else {
			// other?
			log.error("NOT EXPECTING pkt_type: {}  pktlen={}", pkt_type, len);
			LoggingUtil.dump(bb, off, len);
		}

	}

	@Override
	public void disconnect() throws IOException {
		connected = false;
	}

	protected void parseDataExportCommand(ByteBuffer bb) throws IOException {
		// SPpdu -- Session/Presentation Header
		ttick = 0; // if we are receiving data export data...then everything is running.

		short session_id = bb.getShort();
		short p_context_id = bb.getShort();

		// ROapdus -- Remote Operation Header
		short ro_type = bb
				.getShort(); /*
								 * ID for operation: ROIV_APDU, RORS_APDU, ...
								 */
		short cmd_length = bb.getShort(); /*
											 * bytes to follow...WARNING: not a
											 * LI variable 2-3 char length???
											 */

		int start_pos = bb.position();

		short state = RORLS_LAST;

		switch (ro_type) {
		case ROIV_APDU:
			parseRemoteOperationInvoke(bb);
			break;
		case ROLRS_APDU:
			state = bb.get();
			short count = bb.get();

			log.debug("ROLRS_APDU");
			if (log.isDebugEnabled()) {
				LoggingUtil.dump(bb);
			}

			switch (state) {
			case RORLS_FIRST:
				break;
			case RORLS_NOT_FIRST_NOT_LAST:
				break;
			case RORLS_LAST:
				// even though this is the last...we will still get an
				// RORS_APDU, probably without data

				break;
			default:
				log.error("UNKNOWN PARSE REMOTE OPERATION STATE: {}", state);
			}
			// yes, fall through to RORS_APDU
		case RORS_APDU:
			short invoke_id = bb.getShort();
			short command_type = bb.getShort();
			short rs_length = bb.getShort();

			int buf_end_pos = bb.position() + rs_length;

			ActionResult res = parseActionResult(bb, invoke_id, command_type);

			if (log.isDebugEnabled()) {
				log.debug("RORS_APDU  invoke_id={} command_type={} type=" + res.getActionType() + " objid="
						+ res.getObjectID(), invoke_id, command_type);
				LoggingUtil.dump(bb);
			}

			SingleContextPoll[] polls = res.getPolls();
			if (polls == null) {
				// this happens one RORS_APDU when all the data has been
				// delivered
				// through the ROLRS_APDU
			} else if (invoke_id == WAVEFORM_INVOKE_ID) {
				int tot = updateCapabilities(StreamID.WAVEFORM, polls);
				if (tot > 0) {
					caps.setRevNo(caps.getRevNo() + 1);
					fireCapabilitiesEvent(this, caps);
				}
				packWavePolls(polls);
			} else if (invoke_id == NUMERIC_INVOKE_ID) {
				int tot = updateCapabilities(StreamID.MEASUREMENT, polls);
				if (tot > 0) {
					caps.setRevNo(caps.getRevNo() + 1);
					fireCapabilitiesEvent(this, caps);
				}
				packNumericPolls(polls);
			} else if (invoke_id == ALERTS_INVOKE_ID) {
				// System.out.print("a");
				packAlerts(polls);
			} else if (invoke_id == DEMOG_INVOKE_ID) {
				packDemographics(demog, polls);
				fireStreamEvent(0, this, StreamID.DDDEMOGRAPHICS, demog);
			} else {
				log.error("not expecting result invoke_id: {} {}", invoke_id, res);
			}

			if (ro_type == RORS_APDU && state == RORLS_LAST) {

				if (invoke_id == WAVEFORM_INVOKE_ID) {

					long tm = drifter.getRectifiedTime(PlatformUtil.currentTimeMillis());
					drifter.setNextExpectedTime(tm + 250);
					if (wav_block != null) {
						wav_block.setTime(tm);
						fireStreamEvent(0, this, StreamID.WAVEFORM, wav_block);
						IntfUtil.clear(wav_block);
					}

				} else if (invoke_id == NUMERIC_INVOKE_ID) {
					if (num_block != null) {
						num_block.setTime(PlatformUtil.currentTimeMillis());
						fireStreamEvent(0, this, StreamID.MEASUREMENT, num_block);
						IntfUtil.clear(num_block);
					}
				}
			}

			bb.position(buf_end_pos);

			break;

		case ROER_APDU:
			parseError(bb);
			break;
		default:
			log.error("Unknown ro_type: {} session=0x", ro_type, Integer.toHexString(session_id));
			LoggingUtil.dump(bb, 0, bb.limit());
		}
		if (bb.position() - start_pos < cmd_length) {
			log.error("RO_TYPE=" + ro_type + " MUST BE MORE DATA -- BUT IM IGNORING LEN={} < {}",
					(bb.position() - start_pos), cmd_length);
			LoggingUtil.dump(bb);
		}
	}

	private int updateCapabilities(StreamID sid, SingleContextPoll[] polls) {
		int count = 0;

		log.debug("updating polls count: {}", polls.length);
		for (SingleContextPoll poll : polls) {
			log.debug("poll: context={}", poll.getContext_id());
			ObservationPoll[] obs = poll.getObservations();
			if (obs == null) {
				log.warn("No poll data for caps!");
				continue;
			}
			log.debug("updating polls-observation obs count: {}", obs.length);
			for (ObservationPoll ob : obs) {
				log.debug("obs: obj_handle={}", ob.getObj_handle());

				AttributeList attr = ob.getAttributes();
				if (attr == null) {
					log.error("Attr list is null? for poll: {} attr={}", ob, attr);
					continue;
				}

				boolean added = updateOneCap(sid, attr);
				if (added)
					count++;
			}
		}
		return count;
	}

	private boolean updateOneCap(StreamID sid, AttributeList attr) {
		Integer label = (Integer) attr.get(C.NOM_ATTR_ID_LABEL);

		if (label == null) {
			log.debug("NO LABEL break here for {} {}", sid, attr);
			// attr.dump();
			return false;
		}
		String loc = "" + label;

		RpStream stream = caps.getStream(sid);
		if (stream == null) {
			stream = new RpStream();
			stream.setName(sid.getName());
			caps.addStream(stream);
		}

		if (stream != null) {
			RpMetric desc = IntfUtil.getMetricByLoc(stream, loc);
			if (desc != null) {
				log.debug("CAPS found existing desc: {}/{}", sid, desc);
				return false;
			}
		}

		RpStream static_stream = default_cap.getStream(sid);
		if (static_stream == null) {
			static_stream = new RpStream();
			static_stream.setName(sid.getName());
			default_cap.addStream(static_stream);
		}
		RpMetric ref = IntfUtil.getMetricByLoc(static_stream, loc);
		if (ref == null) {
			String code = (String) attr.get(C.NOM_ATTR_ID_LABEL_STRING);
			MetricSpecn mspec = (MetricSpecn) attr.get(C.NOM_ATTR_METRIC_SPECN);
			if (mspec == null) {
				log.error("MSPEC IS NULL");
			} else {

				int struc = mspec.getStructure();
				int composite_indicator = (struc & 0xf00) >> 8;
				int num_elements = (struc & 0xff); // ignored
				SimpleArraySpecn aspec = (SimpleArraySpecn) attr.get(C.NOM_ATTR_SA_SPECN);

				if (composite_indicator == 1) {
					CompositeDescription cd = new CompositeDescription(loc, code, "Composite " + code, null);
					SaObsValue[] sas = (SaObsValue[]) attr.get(C.NOM_ATTR_SA_CMPD_VAL_OBS);
					if (sas == null) {
						log.error("FIXME: DELAYED ADDING METRICS FOR: {}", cd);
						int[] physio_ids = getPhysioIDsFromLabel(label, num_elements);
						// this works for numberic ST, where no sas's are sent...at least initially
						addPhysioIDs(cd, physio_ids);
						ref = cd;
					} else {
						// this works for wave==ECG...where it's not clear what ECG signals will be sent
						addPhysioIDs(cd, sas);
						ref = cd;
					}
				} else if (composite_indicator == 0) {
					if (sid == StreamID.WAVEFORM) {
						if (aspec == null) {
							log.error("NEED ARRAY SPEC FOR WAVE_INVOKE_CAPS_ID");
						} else {
							Integer timePd = (Integer) attr.get(C.NOM_ATTR_TIME_PD_SAMP);
							int spp = aspec.getArraySize(); // this is a MAX size...not the ACTUAL packet size
							if (spp > 64) {
								spp = spp / 2; // empirical observation!!!
							}
							ref = RpUtil.createRpMetric(loc, code, null, 4096 / timePd, spp, RpLinearUnit.unit);
							log.error("[" + timePd + "] ADDING WF code={}, hz={} spp={}", ref.getCode(),
									ref.getSampleRate(), ref.getSamplesPerPacket());
							aspec.dump();
						}
					} else {
						ref = RpUtil.createRpMetric(loc, code, null, RpLinearUnit.unit, DataTyp.INT_TYP);
						log.error("ADDING METRIC loc={} code={}", ref.getLocation(), ref.getCode());
					}
				} else {
					log.error("cannot determine simple/composite type: {}/{}", composite_indicator, attr);
					ref = RpUtil.createRpMetric(loc, code, null, RpLinearUnit.unit, DataTyp.INT_TYP);
					log.error("ADDING METRIC UNKNOWN SIMPLE COMPOSITE loc={} code={}", ref.getLocation(),
							ref.getCode());
				}
			}

			static_stream.getMetric().add(ref);
		}
		stream.getMetric().add(ref);

		if (ref == null) {
			log.error(sid + " err updating cap: {} / {}", //
					loc + " == 0x" + Integer.toHexString(label), //
					attr.get(C.NOM_ATTR_ID_LABEL_STRING));
			attr.dump();
		}

		return (ref != null);
	}

	private int[] getPhysioIDsFromLabel(int label, int expected_count) {
		log.error("remedial routine...needs to be removed");

		int[] ids = null;

		if (label == Numerics.NLS_NOM_PRESS_BLD_NONINV) {
			// ids = new int[] {C.NOM_PRESS_BLD_NONINV_SYS, C.NOM_PRESS_BLD_NONINV_DIA, C.NOM_PRESS_BLD_NONINV_MEAN};
		}

		if (ids == null) {
			ids = new int[expected_count];
			for (int i = 0; i < expected_count; i++) {
				ids[i] = i;
			}
		}

		return ids;
	}

	private void addPhysioIDs(CompositeDescription cd, SaObsValue[] sas) {
		if (sas == null) {
			log.error("no physio id's to add to composite: {}", cd);
			return;
		}

		for (SaObsValue sa : sas) {
			String loc = "0x" + Integer.toHexString(sa.getPhysioID());
			RpMetric d = RpUtil.createRpMetric(loc, loc, null, RpLinearUnit.unit, DataTyp.INT_TYP);
			cd.add(d);
		}

	}

	private void addPhysioIDs(CompositeDescription cd, int[] physio_ids) {
		if (physio_ids == null) {
			log.error("no physio id's to add to composite: {}", cd);
			return;
		}

		for (int physio_id : physio_ids) {
			String loc = "0x" + Integer.toHexString(physio_id);
			RpMetric d = RpUtil.createRpMetric(loc, loc, null, RpLinearUnit.unit, DataTyp.INT_TYP);
			cd.add(d);
		}

	}

	protected void fireDisplayEvent() {

		// DisplayConfig dconf = new DisplayConfig();
		// dconf.setNumBands(numBands);

		// DisplayEvent d = new DisplayEvent( this, dconf );
		// fireEvent(d);
	}

	protected void packAlerts(SingleContextPoll[] polls) {
		for (SingleContextPoll poll : polls) {
			ObservationPoll[] obs = poll.getObservations();
			if (obs == null) {
				log.warn("No poll data for alerts!");
			} else {
				for (ObservationPoll ob : obs) {
					AttributeList attr = ob.getAttributes();
					Object p_al_list = attr.get(C.NOM_ATTR_AL_MON_P_AL_LIST);
					Object t_al_list = attr.get(C.NOM_ATTR_AL_MON_T_AL_LIST);
					if (log.isDebugEnabled()) {
						log.debug("alert p_list={} t_list={} attr=" + attr, p_al_list, t_al_list);
					}
				}
			}
		}
	}

	protected void packDemographics(Intellivue_Demographics demog, SingleContextPoll[] polls) {
		for (SingleContextPoll poll : polls) {
			ObservationPoll[] obs = poll.getObservations();
			if (obs == null) {
				log.warn("No poll data for demographics!");
			} else {
				for (ObservationPoll ob : obs) {
					AttributeList attr = ob.getAttributes();

					Object family = attr.get(C11073.MDC_ATTR_PT_NAME_FAMILY);
					Object given = attr.get(C11073.MDC_ATTR_PT_NAME_GIVEN);
					Object birth = attr.get(C11073.MDC_ATTR_PT_NAME_BIRTH); // same as _MAIDEN
					Object middle = attr.get(C11073.MDC_ATTR_PT_NAME_MIDDLE);
					StringBuffer name = new StringBuffer();
					if( family != null ) name.append( family );
					if( given != null ) name.append(", ").append( given );
					if( given != null ) name.append(" ").append( middle );

					demog.setName(name.toString());
				}
			}
		}
	}

	protected void packNumericPolls(SingleContextPoll[] polls) {
		for (SingleContextPoll poll : polls) {
			ObservationPoll[] obs = poll.getObservations();
			if (obs == null) {
				log.debug("[nu] No poll data!");
			} else {
				for (ObservationPoll ob : obs) {
					AttributeList attr = ob.getAttributes();
					if (attr == null) {
						log.error("Attr list is null? for poll: {} nu_attr={}", ob, attr);
					} else {
						packNumeric(attr);
					}
				}
			}
		}

	}

	protected void packWavePolls(SingleContextPoll[] polls) {
		for (SingleContextPoll poll : polls) {
			ObservationPoll[] obs = poll.getObservations();
			if (obs == null) {
				log.debug("[wave] No poll data!");
				continue;
			}

			for (ObservationPoll ob : obs) {
				AttributeList attr = ob.getAttributes();
				if (attr == null) {
					log.error("Attr list is null? for poll: {} wave={}", ob, attr);
				} else {
					SaObsValue[] sas = (SaObsValue[]) attr.get(C.NOM_ATTR_SA_CMPD_VAL_OBS);
					SaObsValue sa = (SaObsValue) attr.get(C.NOM_ATTR_SA_VAL_OBS);

					if (sas != null) {
						log.debug("***** COMPOUND saobs");
						for (SaObsValue so : sas) {
							packWaves(attr, so);
						}
					} else if (sa != null) {
						log.debug("***** SIMPLE saobs physio_id={}", sa.getPhysioID());
						packWaves(attr, sa);
					} else {
						// caps are updated in a different routine
						Object label = attr.get(C.NOM_ATTR_ID_LABEL);
						Object code = attr.get(C.NOM_ATTR_ID_LABEL_STRING);
						log.warn("PUSH METADATA?? {} {}", label, code);
						// packWaves(attr, null);
					}
				}
			}

		}

	}

	protected void packWaves(AttributeList attr, SaObsValue sa) {
		if (wav_block == null) {
			return; // nothing to pack into
		}

		int physio_id = sa.getPhysioID();

		// FIXME: label/physio_id relation comes from WAVES table...end of chapter 7
		String label = "" + (0x00020000 + physio_id);
		RpMetric m = wav_block.getMetric(label);
		if (m == null) {
			log.info("wf physio_id not found: 0x{} label={}", Integer.toHexString(physio_id), label);
			return;
		} else {
			log.debug("wf found 0x{} {}", Integer.toHexString(physio_id), m.getCode());
		}
		int[] data = (int[]) IntfUtil.getRawValue(wav_block, m);

		if (data == null) {
			data = new int[m.getSamplesPerPacket()];
			IntfUtil.setValue(wav_block, m, data);
			log.info("allocated wf data");
		}

		SimpleArraySpecn aspec = (SimpleArraySpecn) attr.get(C.NOM_ATTR_SA_SPECN);
		SampleArrayFixedValueSpecn fvspec = (SampleArrayFixedValueSpecn) attr.get(C.NOM_ATTR_SA_FIXED_VAL_SPECN);
		if (aspec == null) {
			aspec = cachedArraySpec.get(physio_id);
		} else {
			cachedArraySpec.put(physio_id, aspec);

			if (log.isDebugEnabled()) {
				log.debug("caching SA SPEC for physio_id=0x{}", Integer.toHexString(physio_id));
				aspec.dump();
			}
		}
		//		if (fvspec == null) {
		//			fvspec = cachedFixedValueSpec.get(physio_id);
		//		} else {
		//			cachedFixedValueSpec.put(physio_id, fvspec);
		//			if (log.isDebugEnabled()) {
		//				log.debug("caching FV SPEC for physio_id=0x" + Integer.toHexString(physio_id));
		//				fvspec.dump();
		//			}
		//		}

		if (aspec == null) {
			// can't proceed, dont have specs yet
			String code = (String) attr.get(C.NOM_ATTR_ID_LABEL_STRING);
			log.error("missing wave aspec for: {} physio_id=0x{}", code, Integer.toHexString(physio_id));
		}

		packOneWave(m, data, aspec, fvspec, sa);
		// System.out.println(label + " = " + item );

	}

	protected void packNumeric(AttributeList attr) {

		if (num_block == null) {
			return; // nothing to pack into
		}

		Integer ava_label = (Integer) attr.get(C.NOM_ATTR_ID_LABEL);
		if (ava_label == null) {
			// this happens!
			if (log.isDebugEnabled()) {
				log.debug("pack numeric attr is null");
				attr.dump();
			}
			return;
		}
		String code = (String) attr.get(C.NOM_ATTR_ID_LABEL_STRING);

		String s_label = "" + ava_label;

		RpMetric desc = IntfUtil.getMetricByLoc(num_block, s_label);
		// RpMetric desc = hm_metric.get(s_label);
		if (desc != null) {
			if (desc instanceof CompositeDescription) {
				log.debug("composite found: {} {}", s_label, code);

				float[] fs = (float[]) attr.get(C.NOM_ATTR_NU_CMPD_VAL_OBS);
				if (fs == null) {
					log.error("null value...caps reply?");
				} else {
					IntfUtil.setValue(num_block, desc, fs);
				}
			} else {
				log.debug("item found: {} {}", s_label, code);
				Float f = (Float) attr.get(C.NOM_ATTR_NU_VAL_OBS);
				float[] fs = (float[]) attr.get(C.NOM_ATTR_NU_CMPD_VAL_OBS);
				if (f != null) {
					IntfUtil.setValue(num_block, desc, (int) (float) f);
				} else if (fs != null) {
					log.error("expecting numeric got composite type for " + s_label + ": {} {} ", desc, code);
					attr.dump();
					IntfUtil.setValue(num_block, desc, (int) fs[0]);
					//					ni.setValue((int) (fs[0]));
					//					CompositeDescription cd = new CompositeDescription(s_label, code, null, null);
					//					int[] physio_ids = getPhysioIDsFromLabel(ava_label, fs.length);
					//					addPhysioIDs(cd, physio_ids);
					log.error("CANNOT CURRENTLY REPLACE conf.replace_desc(StreamID.MEASUREMENT, desc, cd);");
				}
			}
		}

		log.debug("pack: {}  code={}", ava_label, code);
	}

	protected void packOneWave(RpMetric m, int[] item, SimpleArraySpecn aspec, SampleArrayFixedValueSpecn ffvspec,
			SaObsValue sa) {

		if (aspec != null && ffvspec != null) {
			sa.fixSpecMask(aspec, ffvspec);
		}
		int[] vals = sa.getValues();
		if (vals != null && vals.length > 0 && vals[0] > 6000) {
			int prev = 0;
			// THIS IS A REAL HACK TO FIX THE ECG SIGNAL!!!!
			for (int i = 0; i < vals.length; i++) {

				int curr = vals[i] - 8100;
				if (curr > 300) {
					curr = prev;
				}
				vals[i] = curr;

				prev = curr;
			}
		}
		IntfUtil.setValue(wav_block, m, vals);
	}

	protected void parseError(ByteBuffer bb) {
		if (log.isDebugEnabled()) {
			log.debug("dumping error from ROER_APDU");
			LoggingUtil.dump(bb);
		}

		RemoteOperationError roer = RemoteOperationError.parse(bb);
		// System.err.println(" invoke_id=" + roer.invoke_id);

		String txt = "<UNKNOWN>";
		switch (roer.error_value) {
		case C.NO_SUCH_OBJECT_CLASS:
			txt = "NO SUCH OBJECT CLASS";
			break;
		case C.NO_SUCH_OBJECT_INSTANCE:
			txt = "NO SUCH OBJECT INSTANCE";
			break;
		case C.ACCESS_DENIED:
			txt = "ACCESS DENIED";
			break;
		case C.GET_LIST_ERROR:
			txt = "GET_LIST_ERROR";
			break;
		case C.SET_LIST_ERROR:
			txt = "SET_LIST_ERROR";
			break;
		case C.NO_SUCH_ACTION:
			txt = "NO_SUCH_ACTION";
			break;
		case C.PROCESSING_FAILURE:
			txt = "PROCESSING_FAILURE";
			break;
		case C.INVALID_ARGUMENT_VALUE:
			txt = "INVALID_ARGUMENT_VALUE";
			break;
		case C.INVALID_OBJECT_INSTANCE:
			txt = "INVALID_OBJECT_INSTANCE";
			break;
		case C.INVALID_SCOPE:
			txt = "INVALID_SCOPE";
			break;

		}
		log.warn("error message={} error_no={}", txt, roer.error_value);

	}

	// typedef u_16 CMDType;
	private ActionResult parseActionResult(ByteBuffer bb, short invoke_id, short command_type) {
		// RORSapdu

		ActionResult res = null;

		switch (command_type) {
		case C.CMD_CONFIRMED_ACTION:
			res = ActionResult.parse(bb, invoke_id);
			break;
		case C.CMD_GET:
			parseCommandGetPriorityListResult(bb);
			break;

		default:
			log.error(" UNKNOWN REMOTE OPERATION RESULT CMD_TYPE={}", command_type);
		}

		return res;
	}

	protected void parseCommandGetPriorityListResult(ByteBuffer bb) {
		ManagedObjectID mo = ManagedObjectID.parse(bb);
		AttributeList list = AttributeList.parse(bb);
		log.debug("GET count={} expecting 1", list.getCount());
		Object txtidlist = list.get(C.NOM_ATTR_POLL_RTSA_PRIO_LIST);

		log.debug("txts={}", txtidlist);
	}

	protected void parseRemoteOperationInvoke(ByteBuffer bb) throws IOException {
		short invoke_id = bb.getShort();
		short command_type = bb.getShort();
		short length = bb.getShort();

		log.debug("      invoke_id:{}   command_type:{}", invoke_id, command_type);
		if (log.isDebugEnabled()) {
			LoggingUtil.dump(bb);
		}

		switch (command_type) {
		case CMD_EVENT_REPORT:
			AttributeList attrs = parseCmdEventReport(bb, length);
			if (attrs == null) {
				break;
			}
			IpAddressInfo addr = (IpAddressInfo) attrs.get(NOM_ATTR_NET_ADDR_INFO);
			ProtoSupport proto = (ProtoSupport) attrs.get(NOM_ATTR_PCOL_SUPPORT);
			SystemModel model = (SystemModel) attrs.get(C.NOM_ATTR_ID_MODEL);

			if (addr != null && proto != null) {
				DeviceCapabilities cap = new DeviceCapabilities(IntellivueDriver.class);
				cap.putParam("name", (model == null) ? "Philips" : model.getManufacturer());
				cap.putParam("port", "" + proto.getPort());
				String ip = "" + addr.getAddress().getHostAddress();
				cap.putParam("ip", ip);

				RpConnection conn = new RpConnection();
				conn.setTyp(RpConnType.INTELLIVUE);
				conn.setValue("intellivue://" + ip + ":" + proto.getPort());
				cap.addConnection(conn);

				cap.setConnectionValue(conn.getValue());
				cap.setModelName((model == null) ? "?" : model.getModel_number());
				fireCapabilitiesEvent(this, cap);
			}

			break;
		case CMD_CONFIRMED_EVENT_REPORT:
			EventReportArgument evt = EventReportArgument.parse(bb);
			if (evt.event_type == C.NOM_NOTI_MDS_CREAT) {
				MdsCreateInfo info = MdsCreateInfo.parse(bb);
			}

			assert (evt.event_type == C.NOM_NOTI_MDS_CREAT) : "Not expected event typ! " + evt.event_type + " != "
					+ C.NOM_NOTI_MDS_CREAT;

			ByteBuffer eventResult = MdsCreateEventResult.build(null, evt.getManagedObject(), evt.current_time,
					evt.event_type);
			ByteBuffer apdus = RORSapdus.build(null, invoke_id, C.CMD_CONFIRMED_EVENT_REPORT, eventResult);
			ByteBuffer pkt = SPpdu.build(null, session_id, p_context_id, apdus);

			send(pkt);
			if (log.isDebugEnabled()) {
				log.debug("dumping confirmed event report");
				LoggingUtil.dump(pkt);
			}

			connected = true;

			break;
		case CMD_GET:
		case CMD_SET:
		case CMD_CONFIRMED_SET:
		case CMD_CONFIRMED_ACTION:
		default:
			log.error("parseRemoteOperationInvoke not prepared for command_type=0x{}",
					Integer.toHexString(command_type));
		}
	}

	protected void sendGetPriorityList(short oidType) throws IOException {
		log.debug("get priority list request:");

		ByteBuffer get_arg = ByteBuffer.allocate(32);
		ManagedObjectID.encode(get_arg, NOM_MOC_VMS_MDS, // m_obj_class, //
				(short) 0, // context
				(short) 0 // handle
		);
		get_arg.putInt(RESERVED_SCOPE); // scope
		get_arg.putShort((short) 1); // attrib count
		get_arg.putShort((short) 2); // attrib length
		get_arg.putShort(oidType);
		get_arg.limit(get_arg.position());
		get_arg.rewind();

		ByteBuffer roiv = ROIVapdus.encode(null, GET_PRIORITY_LIST_INVOKE_ID, C.CMD_GET, get_arg);
		roiv.rewind();

		ByteBuffer ro_apdus = ROapdus.encode(null, C.ROIV_APDU, roiv);
		ro_apdus.rewind();

		ByteBuffer pkt = SPpdu.build(null, session_id, p_context_id, ro_apdus);

		send(pkt);
	}

	protected void sendExtendedPollDataRequest(short invoke_id, short m_obj_class, short code, int rel_tm)
			throws IOException {

		AttributeList tmout = new AttributeList();
		tmout.add(new AVAType(C.NOM_ATTR_TIME_PD_POLL, rel_tm));

		ByteBuffer mdib = PollMdibDataReq.encode(null, poll_no, C.NOM_PART_OBJ, code, (short) 0, tmout);
		mdib.rewind();

		// System.out.println("PollMdibDataReq");
		// dump(mdib);

		ByteBuffer actionarg = ExtendedPollDataRequest.encode(null, m_obj_class, mdib);
		actionarg.rewind();

		// System.out.println("ExtendedPollDataRequest");
		// dump(actionarg);

		ByteBuffer roiv = ROIVapdus.encode(null, invoke_id, C.CMD_CONFIRMED_ACTION, actionarg);
		roiv.rewind();

		ByteBuffer ro_apdus = ROapdus.encode(null, C.ROIV_APDU, roiv);
		ro_apdus.rewind();

		ByteBuffer pkt = SPpdu.build(null, session_id, p_context_id, ro_apdus);

		if (log.isDebugEnabled()) {
			log.debug("sendExtendedPollDataRequest:");
			LoggingUtil.dump(pkt);
		}
		send(pkt);

	}

	protected void sendSinglePollDataRequest(short invoke_id, short m_obj_class, short code) throws IOException {

		// log.debug("sendSinglePollDataRequest ");
		ByteBuffer mdib = PollMdibDataReq.encode(null, poll_no, C.NOM_PART_OBJ, code, (short) 0, null);
		mdib.rewind();

		// System.out.println("PollMdibDataReq");
		// dump(mdib);

		ByteBuffer actionarg = SinglePollDataRequest.encode(null, m_obj_class, mdib);
		actionarg.rewind();

		// System.out.println("SinglePollDataRequest ActionArg");
		// dump(actionarg);

		ByteBuffer roiv = ROIVapdus.encode(null, (short) (SINGLEPOLL_FLAG + invoke_id), C.CMD_CONFIRMED_ACTION,
				actionarg);
		roiv.rewind();

		ByteBuffer ro_apdus = ROapdus.encode(null, C.ROIV_APDU, roiv);
		ro_apdus.rewind();

		ByteBuffer pkt = SPpdu.build(null, session_id, p_context_id, ro_apdus);
		pkt.rewind();

		// System.out.println("sendSinglePollDataRequest my request:");
		// dump(pkt);
		send(pkt);

	}

	protected AttributeList parseCmdEventReport(ByteBuffer bb, short length) {
		// int endPos = bb.position() + length;

		// while( bb.position() < endPos ) {
		short m_obj_class = bb.getShort();

		short context_id = bb.getShort();
		short handle = bb.getShort();

		int event_time = bb.getInt(); // RelativeTime u_32
		short event_type = bb.getShort(); // OIDType u_16
		short pktlen = bb.getShort();

		AttributeList attr = parseAttributeList(bb);

		switch (m_obj_class) {
		case NOM_MOC_VMS_MDS_COMPOS_SINGLE_BED:

			break;
		default:
			log.error("parseCmdEventReport unknown obj_class=" + m_obj_class);

			break;
		}

		return attr;
	}

	private AttributeList parseAttributeList(ByteBuffer bb) {
		AttributeList attrs = AttributeList.parse(bb);

		String label_string = (String) attrs.get(C.NOM_ATTR_ID_LABEL_STRING);
		Integer id_label = (Integer) attrs.get(NOM_ATTR_ID_LABEL);

		if (num_block != null) {
			Object val = attrs.get(NOM_ATTR_NU_VAL_OBS);
			if (val != null) {
				// FIXME: is id_label the same as label_string???
				log.error("XIXME: duplicate of pack-numeric code?");
				log.error("XIXME: IntfUtil.setValue(num_block, \"\" + id_label, (Number) val);");
				log.debug("{} metric_descs  val= {}", label_string, val);
			}

		}

		return attrs;
	}

	public static void dump(SingleContextPoll[] polls) {
		log.debug("dumping polls");
		if (polls != null) {
			log.debug("poll count={}", polls.length);
			for (SingleContextPoll poll : polls) {
				poll.dump();
			}
		}
	}

	@Override
	public void requestCapabilities() throws IOException {
		if (caps == null) {
			fireCapabilitiesEvent(this, default_cap);
		} else {
			fireCapabilitiesEvent(this, caps);
		}
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return default_cap;
	}

	public void requestAssociation() throws IOException {
		log.info("requesting association");
		ByteBuffer req = ByteBuffer.allocate(512);
		AssociationRequest.build(req);
		send(req);
		if (log.isDebugEnabled()) {
			log.debug("association packet:");
			LoggingUtil.dump(req);
		}
	}

	protected abstract void send(ByteBuffer req) throws IOException;

	@Override
	public int tick() {

		if (connected) {
			try {
				refreshPolls();
			} catch (IOException e) {
				log.error("could not refresh polls", e);
			}
		}

		ttick++;
		if (ttick > 20) {
			ttick = 10;
			try {
				requestAssociation();
			} catch (Exception e) {
				// this should not happen...but the user already knows there is
				// a comm error USB-RS232 device disconnected?
				log.error("could not request association", e);
			}
		}

		ConnectionStatus deviceState = getStatus();
		if (ttick > 6) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(ConnectionStatus.NOT_CONNECTED);
				fireNoData(conf);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

	protected void refreshPolls() throws IOException {

		long currTM = PlatformUtil.currentTimeMillis();
		long deltaMS = currTM - lastExtendedRequestTM;

		if (deltaMS > 15000) {
			log.debug("refreshing polls");

			sendExtendedPollDataRequest(NUMERIC_INVOKE_ID, C.NOM_MOC_VMS_MDS, C.NOM_MOC_VMO_METRIC_NU,
					C.RELTIME_1SEC * 60);

			sendExtendedPollDataRequest(WAVEFORM_INVOKE_ID, C.NOM_MOC_VMS_MDS, C.NOM_MOC_VMO_METRIC_SA_RT,
					C.RELTIME_1SEC * 60);

			sendExtendedPollDataRequest(ALERTS_INVOKE_ID, C.NOM_MOC_VMS_MDS, C11073.MDC_MOC_VMO_AL_MON,
					C.RELTIME_1SEC * 60);
			sendSinglePollDataRequest(DEMOG_INVOKE_ID, C.NOM_MOC_VMS_MDS, C.NOM_MOC_PT_DEMOG);

			lastExtendedRequestTM = currTM;
		}

	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	public void setConfiguration(DeviceConfiguration new_conf) throws IOException {
		log.warn("FIXME: this does not work across the net. -- should it??");
		// System.out.println("before count=" + new_conf.getMetrics().length);
		// AdapterUtil.fix_config(caps, new_conf);
		conf = new_conf;

		init_blocks();

		refreshPolls();
	}
}
