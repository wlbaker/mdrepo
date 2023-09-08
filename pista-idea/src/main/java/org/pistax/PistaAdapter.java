package org.pistax;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import org.pistax.pista_dev_status;
import org.pistax.pista_error_code;
import org.pistax.pista_packettype;
import org.pistax.model.BMP180_measurement;
import org.pistax.model.HT70_breath;
import org.pistax.model.HT70_pressures;
import org.pistax.model.HT70_status;
import org.pistax.model.IMP731_breath;
import org.pistax.model.IMP731_sensors;
import org.pistax.model.IMP731_status;
import org.pistax.model.MCCUL_fsensor;
import org.pistax.model.MEDSYS3_measurement;
import org.pistax.model.MEDSYS3_sigevent;
import org.pistax.model.MEDSYS3_status;
import org.pistax.model.PROPAQM_sensors;
import org.pistax.model.PROPAQM_vitals;
import org.pistax.model.SIMU_measure;
import org.pistax.model.SIMU_sensor;

import icuInterface.ConnectionStatus;
import icuInterface.LoggingUtil;
import icuInterface.events.ConnectionItem;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.DtConnection;
import idea.connections.I2CConnection;
import idea.connections.LabJackConnection;
import idea.connections.McculConnection;
import idea.connections.NoConnection;
import idea.connections.SerialConnection;
import idea.connections.TcpServerConnection;
import idea.intf.AdapterInterface;
import idea.intf.SerialAdapter;
import idea.message.StreamID;
import idea.model.PersistentItem;
import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpConnType;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.StringStringMap;

enum ALLOCMETHOD {
	FIXEDBUF, // same buf is used over-and-over
	SINGLEUSE, // buf is used once, then reallocated for next data block
	POOL //
}

enum THREADMETHOD {
	POLLED, // same buf is used over-and-over
	INTERNAL // buf is used once, then reallocated for next data block
}

// public class PistaAdapter extends AbstractStreamProducer implements
// AdapterInterface
@Slf4j
public class PistaAdapter extends SerialAdapter implements AdapterInterface {

	private static final int PARITY_NONE = 0;
	private static final int PARITY_ODD = 1;
	private static final int PARITY_EVEN = 2;

	private DeviceCapabilities caps;
	private RpDevice conf;
	private PistaDev d;

	PersistentItem s;
	PersistentItem m;
	PersistentItem m2;
	PersistentItem w;
	PersistentItem a; // alarm

	Class<? extends PersistentItem> cl_conf = null;
	// private OutputStream out;

	PistaEventHandler h = new PistaEventHandler() {
		@Override
		public int event(PistaDev dev, PistaDataPacket pkt) {
			if (pkt.getStreamID() == pista_packettype.PISTA_DF_MEASUREMENT) {
				if (m != null) {
					PistaUtil.decodePistaPacket(m, pkt);
					fireStreamEvent(0, PistaAdapter.this, StreamID.MEASUREMENT, m);
				} else {
					log.error("could not decode measurement");
				}
			} else if (pkt.getStreamID() == pista_packettype.PISTA_DF_WAVEFORM) {
				if (w != null) {
					PistaUtil.decodePistaPacket(w, pkt);
					fireStreamEvent(0, PistaAdapter.this, StreamID.WAVEFORM, w);
				} else {
					log.error("could not decode wf-stream");
				}
			} else if (pkt.getStreamID() == pista_packettype.PISTA_DF_SETTINGS) {
				if (s != null) {
					PistaUtil.decodePistaPacket(s, pkt);
					fireStreamEvent(0, PistaAdapter.this, StreamID.SETTINGS, s);
				} else {
					log.warn("could not decode settings");
				}
			} else if (pkt.getStreamID() == pista_packettype.PISTA_DF_M2) {
				if (m2 != null) {
					PistaUtil.decodePistaPacket(m2, pkt);
					fireStreamEvent(0, PistaAdapter.this, StreamID.MEASUREMENT_2, m2);
				} else {
					log.warn("could not decode meaurement2");
				}
			} else if (pkt.getStreamID() == pista_packettype.PISTA_DF_ALARM) {
				if (a != null) {
					PistaUtil.decodePistaPacket(a, pkt);
					fireStreamEvent(0, PistaAdapter.this, StreamID.ALARM, a);
				} else {
					log.warn("could not decode alarm");
				}
			} else if (pkt.getStreamID() == pista_packettype.PISTA_DF_CAPABILITIES) {
				log.error("pista capabilities: not implemented");
			} else if (pkt.getStreamID() == pista_packettype.PISTA_DF_CONNECTION) {
				ConnectionStatus stat = ConnectionStatus.ERROR;

				int stat_val = dev.getStatus();
				if (stat_val == pista_dev_status.PISTA_ST_CONNECTED) {
					stat = ConnectionStatus.CONNECTED;
				} else if (stat_val == pista_dev_status.PISTA_ST_NOT_CONNECTED) {
					stat = ConnectionStatus.NOT_CONNECTED;
				} else if (stat_val == pista_dev_status.PISTA_ST_ERROR) {
					stat = ConnectionStatus.ERROR;
				} else if (stat_val == pista_dev_status.PISTA_ST_NEGOTIATING) {
					stat = ConnectionStatus.NEGOTIATING;
				} else if (stat_val == pista_dev_status.PISTA_ST_STANDBY) {
					stat = ConnectionStatus.STANDBY;
				}

				setStatus(stat, "tm @" + pkt.getTm() );
			} else {
				log.error("unknown packet type: {}", pkt.getStreamID());
			}

			return 0;
		}
	};

	PistaCommHandler c = new PistaCommHandler() {

		@Override
		public int write(byte[] data) throws IOException {

			OutputStream out = getOutputStream();
			int len = -1;
			if (out == null) {
				log.debug("no output stream: {}", conf.getName());
			} else {
				out.write(data);
				len = data.length;
			}
			return len;
		}

	};
	private PistaDriver driver;

	public PistaAdapter(RpDevice rp) {
		super(rp);
		this.conf = rp;

		PistaCl inst = PistaCl.getInstance();

		String name = rp.getModelName();
		driver = inst.driver(name);
        if( driver == null ) {
            log.error("Could no load driver from name: {}", name );
        }
		d = driver.allocate();
		
		RpConnType typ = rp.getConnectionType();
		if( typ != null ) {
			d.setOption("connection", typ.toString() );
		}
		
		if( rp.getConnectionType() == RpConnType.ETHERNET) {
			d.setOption("host", rp.getConnectionValue() );
		} else if ( rp.getConnectionType() == RpConnType.INFINITY) {
			d.setOption("host", rp.getConnectionValue() );
		} else {
			d.setOption("port", rp.getConnectionValue() );
		}
		
		StringStringMap params = rp.getParam();
        if( params != null ) {
		    for( String key : params.keySet() ) {
			    d.setOption( key,params.get(key));
		    }
        }

		
		prepareCapabilities(driver, name);
		
		d.attach(h);
		d.attach(c);
	}

	public PistaAdapter(PistaDev d) {
		super(null);
		this.d = d;
		System.err.println("getting pista dev from driver -- CANNOT POLL! NO CONF!: " + d);

		prepareCapabilities(null, "simu");

		d.attach(h);
		d.attach(c);
	}

	private void prepareCapabilities(PistaDriver driver, String name) {
		caps = new DeviceCapabilities(PistaAdapter.class);

		if (driver != null) {
			caps.setName(driver.longname());
			caps.setModels(new String[] { driver.name() });
		}

		if ("mccul".equalsIgnoreCase(name)) {
			caps.addConnection(new McculConnection());
			caps.addStream(StreamID.WAVEFORM, MCCUL_fsensor.class);
			w = new MCCUL_fsensor();
		} else if ("simu".equalsIgnoreCase(name)) {
			caps.addConnection(new NoConnection());
			caps.addStream(StreamID.WAVEFORM, SIMU_sensor.class);
			caps.addStream(StreamID.MEASUREMENT, SIMU_measure.class);
			w = new SIMU_sensor();
			m = new SIMU_measure();
		} else if ("u3".equalsIgnoreCase(name)) {
			caps.addConnection(new LabJackConnection());
			log.error("FIXME: need data structure for LabJack U3");
			caps.addStream(StreamID.WAVEFORM, MCCUL_fsensor.class);
			w = new MCCUL_fsensor();
		} else if ("dt".equalsIgnoreCase(name)) {
			caps.addConnection(new DtConnection());
			log.error("FIXME: need data structure for DT");
			caps.addStream(StreamID.WAVEFORM, MCCUL_fsensor.class);
			w = new MCCUL_fsensor();
		} else if ("imp731".equalsIgnoreCase(name)) {
			caps.addConnection(new SerialConnection(115200, 8, 1, PARITY_NONE));
			caps.addStream(StreamID.SETTINGS, IMP731_status.class);
			caps.addStream(StreamID.MEASUREMENT, IMP731_breath.class);
			caps.addStream(StreamID.WAVEFORM, IMP731_sensors.class);

			s = new IMP731_status();
			m = new IMP731_breath();
			w = new IMP731_sensors();
		} else if ("medsys3".equalsIgnoreCase(name)) {
			caps.addConnection(new SerialConnection(9600, 7, 1, PARITY_ODD));
			caps.addStream(StreamID.SETTINGS, MEDSYS3_status.class);
			caps.addStream(StreamID.MEASUREMENT, MEDSYS3_measurement.class);
			caps.addStream(StreamID.MEASUREMENT_2, MEDSYS3_sigevent.class);

			s = new MEDSYS3_status();
			m = new MEDSYS3_measurement();
			m2 = new MEDSYS3_sigevent();
		} else if ("ht70".equalsIgnoreCase(name)) {
			caps.addConnection(new SerialConnection(38400, 8, 1, PARITY_NONE ));
			caps.addStream(StreamID.SETTINGS, HT70_status.class);
			caps.addStream(StreamID.MEASUREMENT, HT70_breath.class);
			caps.addStream(StreamID.WAVEFORM, HT70_pressures.class);
			// caps.addStream(StreamID.ALARM, HT70_alarms.class);

			s = new HT70_status();
			m = new HT70_breath();
			w = new HT70_pressures();
			// a = new HT70_alarms();
		} else if ("propaqm".equalsIgnoreCase(name)) {
			caps.addConnection(new TcpServerConnection());
			caps.addStream(StreamID.MEASUREMENT, PROPAQM_vitals.class);
			caps.addStream(StreamID.WAVEFORM, PROPAQM_sensors.class);

			m = new PROPAQM_vitals();
			w = new PROPAQM_sensors();
		} else if ("bmp180".equalsIgnoreCase(name)) {
			caps.addConnection(new I2CConnection());
			caps.addStream(StreamID.MEASUREMENT, BMP180_measurement.class);

			m = new BMP180_measurement();
		} else {
			caps.addConnection(new NoConnection());
			log.error("NO METRICS FOUND -- currently must be hardcoded here!");
		}

	}

	private void discover() {
		System.err.println("NOT READY");

	}

	@Override
	public void connect() throws IOException {

		if (conf != null) {
			StringStringMap params = conf.getParam();
			if (params != null) {
				for (String key : params.keySet()) {
					d.setOption(key, params.get(key));
				}
			}
			d.setOption("connection", conf.getConnectionValue());
		}
		sync_metadata(StreamID.WAVEFORM, w);

		d.attach(h);
		d.connect();

		return;
	}

	private void sync_metadata(StreamID sid, PersistentItem item) {

		if (item == null) {
			return; // no (waveform) metadata to sync
		}
		PistaStream str = d.getStream(sid.getCode()); // Code is 'W' for
														// waveform data
		for (int i = 0; i < str.getDescriptorCount(); i++) {
			PistaDescriptor pd = str.getDescriptorByIdx(i);
			String loc = pd.getLoc();

			RpMetric m = item.getMetric(loc);
			if (m != null) {
				System.out.println("sync metadata: " + loc + " hzz=" + pd.getFreq());
				m.setSampleRate(pd.getFreq());
				m.setSamplesPerPacket(pd.getSPP());
			}
		}

	}

	@Override
	public void disconnect() throws IOException {
		super.disconnect(); // fire a connection message

		d.disconnect(); // forward the disconnect notification to PISTA

		return;
	}

	@Override
	public int tick() {
		// don't do either of these in this call:
		//
		// 1) d.tick()  because ticks are done at the pista level
		// 
		// 2) PistaCl pista = PistaCl.getInstance();
		//    return pista.tick();
		//
		// -- nor (2) since there is one PistaAdapter per device, and this is a pista-level tick call.
		return 0;
	}

	public void setConfig(RpDevice dev) throws IOException {
		// FIXME: ignoring dev configuration
		log.error("FIXME: ignoring dev configuration for C++ driver");
		// d.getConfiguration();
		//
		// conf = new DeviceConfiguration(dev);
		// if (conf.getName() == null) {
		// conf.setName(caps.getName());
		// }
		// conf.addStream(StreamID.WAVEFORM, cl_conf);

	}

	@Override
	public RpDevice getConfiguration() {
		if (conf == null) {
			return super.getConfiguration();
		}
		return conf;
	}

	@Override
	public DeviceConfiguration getStaticCapabilities() {
		return caps;
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		int avail = in.available();
		byte[] buf = new byte[avail]; // we could use a fixed size buf

		in.read(buf);

		d.handle(buf);
	}

	@Override
	public void probe(OutputStream out) throws IOException {
		PistaCommHandler c = new PistaCommHandler() {
			@Override
			public int write(byte[] data) throws IOException {

				int len = -1;
				out.write(data);
				len = data.length;

				return len;
			}
		};
		driver.probe(c);
	}

	@Override
	public boolean verify(byte[] arr, int len) {

		return (driver.verify(arr, len) == pista_error_code.PISTA_OK);
	}

}
