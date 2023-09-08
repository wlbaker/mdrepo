package icuInterface.adapters;

import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.message.StreamID;
import idea.model.dev.DragerV500_Measurements;
import idea.model.dev.DragerV500_Sensors;
import idea.model.dev.DragerV500_Settings;
import idea.schema.rp.RpDevice;

public class V500Driver extends MedibusDriver {
	@SuppressWarnings("unused")
	private static final String driverName="ventilator/Drager V500";

	private static DeviceCapabilities v500_cap;

	static {
		v500_cap = new DeviceCapabilities(V500Driver.class);

		v500_cap.addStream( StreamID.SETTINGS, DragerV500_Settings.class );
		v500_cap.addStream( StreamID.MEASUREMENT, DragerV500_Measurements.class );
		v500_cap.addStream( StreamID.WAVEFORM, DragerV500_Sensors.class );
		
		// dont know if this is the right 
		v500_cap.addConnection( new SerialConnection(19200, 8, 1, 0));
		v500_cap.setModels(new String[] { "V500" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(V500Driver.class);
	}

	public V500Driver(RpDevice conf) {
		super(v500_cap, conf, 19200, false);

	}
}
