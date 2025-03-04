package idea.driver;

import static icuInterface.ConnectionStatus.CONNECTED;
import static icuInterface.ConnectionStatus.NOT_CONNECTED;

import java.io.IOException;

import com.phidgets.BridgePhidget;
import com.phidgets.PhidgetException;
import com.phidgets.event.AttachEvent;
import com.phidgets.event.AttachListener;
import com.phidgets.event.BridgeDataEvent;
import com.phidgets.event.BridgeDataListener;
import com.phidgets.event.DetachEvent;
import com.phidgets.event.DetachListener;
import com.phidgets.event.ErrorEvent;
import com.phidgets.event.ErrorListener;

import icuInterface.ConnectionStatus;
import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import icuInterface.conf.dev.PhidgetDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.connections.PhidgetsConnection;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.AdapterUtil;
import idea.message.StreamID;
import idea.model.dev.PhidgetMeasurement;
import idea.model.dev.PhidgetSettings;
import idea.schema.rp.RpDevice;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class PhidgetBridgeDriver extends AbstractStreamProducer //
		implements AdapterInterface, //
		AttachListener, DetachListener, ErrorListener, BridgeDataListener {

	@SuppressWarnings("unused")
	private static final String driverName = "a2d/Phidget Bridge USB Sensing and Control";

	private RpDevice conf;
	private int tick;
	protected static DeviceCapabilities caps;

	private BridgePhidget bridge;
	private int tot_enabled;
	private double[] val = new double[4];

	public static DeviceConfiguration createConfigInstance() {
		return new PhidgetDeviceConfiguration(PhidgetBridgeDriver.class);
	}

	static {

		caps = new DeviceCapabilities(PhidgetBridgeDriver.class);

		caps.addStream(StreamID.SETTINGS, PhidgetSettings.class);
		caps.addStream(StreamID.MEASUREMENT, PhidgetMeasurement.class);

		caps.addConnection(new PhidgetsConnection());
	}

	public PhidgetBridgeDriver(RpDevice conf) {
		this.conf = conf;

		AdapterUtil.fix_config(caps, conf);

	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}

	@Override
	public void connect() throws IOException {

		try {

			String serNo = RpUtil.getParam(conf, "ser_no");

			bridge = new BridgePhidget();
			bridge.addAttachListener(this);
			bridge.addDetachListener(this);
			bridge.addErrorListener(this);
			bridge.addBridgeDataListener(this);

			if (serNo != null) {
				bridge.open(Integer.parseInt(serNo));
			} else {
				bridge.openAny();
			}

		} catch (Exception e) {
			e.printStackTrace();
			throw new IOException(e);
		}

	}

	@Override
	public void disconnect() throws IOException {
		if (bridge != null) {
			try {
				bridge.removeAttachListener(this);
				bridge.removeBridgeDataListener(this);
				bridge.removeDetachListener(this);
				bridge.removeErrorListener(this);
				bridge.close();

			} catch (PhidgetException e) {
				throw new IOException(e);
			}
		}
		setStatus(ConnectionStatus.NOT_CONNECTED);
	}

	@Override
	public void requestCapabilities() throws IOException {
		fireCapabilitiesEvent(this, caps);
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	public int tick() {
		tick++;

		ConnectionStatus deviceState = getStatus();
		if (tick > 4) {
			if (deviceState != NOT_CONNECTED) {
				setStatus(NOT_CONNECTED);
			}
		} else {
			if (deviceState != CONNECTED) {
				setStatus(CONNECTED);
			}
		}
		
		return 0;
	}

	@Override
	public void attached(AttachEvent an) {
		try {
			_attached(an);
		} catch (PhidgetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void _attached(AttachEvent an) throws PhidgetException {
		BridgePhidget attached = (BridgePhidget) an.getSource();

		log.info("phidget-attach: {}", attached.getSerialNumber());
		tick = 0;

		int gain = BridgePhidget.PHIDGET_BRIDGE_GAIN_128;
		StringStringMap params = conf.getParam();

		String s_gain = params.get("gain");
		if (s_gain != null) {
			gain = Integer.parseInt(s_gain);
		}
		int rate = 1000;

		String s_rate = params.get("rate");
		if (s_rate != null) {
			rate = Integer.parseInt(s_rate);
			if (rate < 40) {
				rate = 1000;
			}
		}
		tot_enabled = 0;

		for (int i = 0; i < 4; i++) {

			bridge.setEnabled(i, true);
			log.info("AI{} setting gain: {}", i, gain);
			bridge.setGain(i, gain);
			tot_enabled++;
		}
		if (tot_enabled > 0) {
			log.info("phidget datarate: {}", rate);
			bridge.setDataRate(rate); // data rate is set for all channels
		} else {
			log.error("NO CHANNELS CONFIGURED FOR PHIDGET???");
		}
	}

	@Override
	public void detached(DetachEvent arg0) {
		log.warn("detach: {}", arg0);
	}

	@Override
	public void error(ErrorEvent arg0) {
		log.warn("error: {}", arg0);
	}

	@Override
	public void bridgeData(BridgeDataEvent bde) {
		tick = 0;
		int idx = bde.getIndex();
		if (idx > 3 || idx < 0) {
			log.error("UNEXPECTED IDX: {}", idx);
			return;
		}

		BridgePhidget fc = (BridgePhidget) bde.getSource();

		val[idx] = bde.getValue() * 1000.0;

		if (idx == 3) {

			PhidgetMeasurement block = new PhidgetMeasurement();
			block.setTime( PlatformUtil.currentTimeMillis() );
			block.setA0((int) val[0]);
			block.setA1((int) val[1]);
			block.setA2((int) val[2]);
			block.setA3((int) val[3]);

			fireStreamEvent(0, this, StreamID.MEASUREMENT, block);

			for (int i = 0; i < val.length; i++) {
				val[i] = Double.NaN;
			}
		}

	}

}
