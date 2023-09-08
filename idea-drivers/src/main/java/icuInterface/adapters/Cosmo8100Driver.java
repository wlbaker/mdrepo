package icuInterface.adapters;

import icuInterface.adapters.novamet3.NovaCom3AbstractDriver;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.message.StreamID;
import idea.model.dev.CosmoMeasurement;
import idea.model.dev.CosmoWaveform;

public class Cosmo8100Driver extends NovaCom3AbstractDriver {

	private static final String driverName="capnography/CO2SMO 8100 Capnographer";
	
	private static DeviceCapabilities cap;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(Cosmo8100Driver.class);
	}

	public Cosmo8100Driver(DeviceConfiguration conf) {
		super(1, cap, conf);
	}

	static {
		cap = new DeviceCapabilities(Cosmo8100Driver.class);

		cap.addStream(StreamID.WAVEFORM, CosmoWaveform.class );
		cap.addStream(StreamID.MEASUREMENT, CosmoMeasurement.class );
		
		cap.setModels( new String [] {"Cosmo 8100"} );
	}

}
