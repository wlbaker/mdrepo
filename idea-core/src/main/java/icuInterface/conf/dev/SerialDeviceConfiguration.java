package icuInterface.conf.dev;

import idea.conf.DeviceConfiguration;

//note: might wrap up all the device configurations with a single "setConnectionValue()"

public class SerialDeviceConfiguration extends DeviceConfiguration {

	private static final long serialVersionUID = 1L;
	
	public SerialDeviceConfiguration(Class<?> cl) {
		super(cl);
	}

	
	public String getPort() {
		return getConnectionValue();
	}

	public void setPort(String portName ) {
		setConnectionValue(portName);
	}
	
}
