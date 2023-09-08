package icuInterface.adapters;

import com.fazecast.jSerialComm.SerialPort;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.connections.SerialConnection;
import idea.message.StreamID;
import idea.model.dev.DragerEvita_Measurements;
import idea.model.dev.DragerEvita_Sensors;
import idea.model.dev.DragerEvita_Settings;
import idea.schema.rp.RpDevice;

public class EvitaDriver extends MedibusDriver {
	@SuppressWarnings("unused")
	private static final String driverName="ventilator/Drager Evita";

	private static DeviceCapabilities evita_cap;

	static {
		evita_cap = new DeviceCapabilities(EvitaDriver.class);

		evita_cap.addStream( StreamID.SETTINGS, DragerEvita_Settings.class );
		evita_cap.addStream( StreamID.MEASUREMENT, DragerEvita_Measurements.class );
		evita_cap.addStream( StreamID.WAVEFORM, DragerEvita_Sensors.class );
		
		evita_cap.setModels( new String[] { "Evita 4", "Evita 2 dura", "Evita XL" });
		
		evita_cap.addConnection( new SerialConnection(19200, 8, 1, SerialPort.EVEN_PARITY ));
	}

	public static SerialDeviceConfiguration createConfigInstance() {
		SerialDeviceConfiguration conf = new SerialDeviceConfiguration(EvitaDriver.class);
		conf.addStream(evita_cap.getStream(StreamID.SETTINGS));
		return conf;
	}

	public EvitaDriver(RpDevice conf) {
		super(evita_cap, conf, 19200, false);

	}
}
