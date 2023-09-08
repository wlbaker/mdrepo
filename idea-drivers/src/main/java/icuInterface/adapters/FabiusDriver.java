package icuInterface.adapters;

import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.message.StreamID;
import idea.model.dev.Fabius_Measurements;
import idea.model.dev.Fabius_Sensors;
import idea.model.dev.Fabius_Settings;
import idea.schema.rp.RpDevice;

/*
 --> 0x05 = null : [1/0x05: Breathing Pressure]
  --> 0x73 = 4.0 : [1/0x73: Mean Breathing Pressure]
  --> 0x78 = 0.0 : [1/0x78: PEEP Breathing Pressure]
  --> 0x7D = 18.0 : [1/0x7D: Peak Breathing Pressure]
  --> 0x88 = 628.0 : [1/0x88: Tidal Volume]
  --> 0x82 = 0.62 : [1/0x82: Tidal Volume (L/OBS)]
  --> 0xB9 = 7.5 : [1/0xB9: Respiratory Minute Volume]
  --> 0xD7 = 12.0 : [1/0xD7: Respiratory Rate]
  --> 0xDE = 5226.0 : [1/0xDE: Air Flow]
  --> 0xE2 = 0.0 : [1/0xE2: O2 Flow]
  --> 0xDD = 0.0 : [1/0xDD: N2O Flow]
  --> 0x74 = 18.0 : [1/0x74: Plateau Pressure]
  --> 0xF0 = 20.0 : [1/0xF0: Insp. O2]
  --> 0xD5 = 0.0 : [1/0xD5: Frequency CO2]
 */
public class FabiusDriver extends MedibusDriver {

	@SuppressWarnings("unused")
	private static final String driverName="anesthesia/Drager Fabuis";
	private static DeviceCapabilities fabius_caps;

	static {
		String two_subscript = "2"; // + (char)0xE2 (char)0x82 "\u2082";
		fabius_caps = new DeviceCapabilities(FabiusDriver.class);

		fabius_caps.addStream( StreamID.SETTINGS, Fabius_Settings.class );
		fabius_caps.addStream(StreamID.MEASUREMENT, Fabius_Measurements.class);
		fabius_caps.addStream(StreamID.WAVEFORM, Fabius_Sensors.class);
		
		
		fabius_caps.setModels(new String[] { "Fabius" });
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(FabiusDriver.class);
	}

	public FabiusDriver(RpDevice conf) {
		super(fabius_caps, conf, 38400, true);
	}

}
