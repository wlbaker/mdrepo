package icuInterface.adapters;

import icuInterface.adapters.novamet3.NovaCom3AbstractDriver;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.message.StreamID;
import idea.model.dev.NM3Measurement;
import idea.model.dev.NM3Trend;
import idea.model.dev.NM3Waveform;
import idea.schema.rp.RpDevice;

public class PhilipsNM3Driver extends NovaCom3AbstractDriver {
	@SuppressWarnings("unused")
	private static final String driverName="capnography/Philips NM3";
	
	private static DeviceCapabilities cap;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(PhilipsNM3Driver.class);
	}

	public PhilipsNM3Driver(RpDevice conf) {
		super(2, cap, conf);
	}


	static {
		cap = new DeviceCapabilities(PhilipsNM3Driver.class);


		cap.addStream(StreamID.MEASUREMENT, NM3Measurement.class );
		cap.addStream(StreamID.MEASUREMENT_2, NM3Trend.class );
		cap.addStream(StreamID.WAVEFORM, NM3Waveform.class );

		cap.setModels(new String [] {"NM3"} );
	}


}
