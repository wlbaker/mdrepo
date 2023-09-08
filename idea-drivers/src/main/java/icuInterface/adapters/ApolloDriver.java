package icuInterface.adapters;

import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.message.StreamID;
import idea.model.dev.DragerApollo_Measurements;
import idea.model.dev.DragerApollo_Sensors;
import idea.schema.rp.RpDevice;

public class ApolloDriver extends MedibusDriver {

	private static final String driverName="anesthesia/Drager Apollo Anesthesia";
	private static DeviceCapabilities apollo_cap;

	static {
		apollo_cap = new DeviceCapabilities(ApolloDriver.class);

		apollo_cap.addStream( StreamID.MEASUREMENT, DragerApollo_Measurements.class );
		apollo_cap.addStream( StreamID.WAVEFORM, DragerApollo_Sensors.class );

		apollo_cap.setModels(  new String[] { "Apollo" } );
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(ApolloDriver.class);
	}

	public ApolloDriver(RpDevice conf) {
		super(apollo_cap, conf, 9600, true);
	}

}
