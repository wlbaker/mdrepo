package icuInterface.events;

import idea.conf.DeviceCapabilities;

import java.util.EventObject;

public class CapabilitiesEventObsolete extends EventObject {

	private static final long serialVersionUID = 1519789946653270221L;

	private DeviceCapabilities cap;

	public CapabilitiesEventObsolete(Object source, DeviceCapabilities cap) {
		super(source);
		this.setCapabilities(cap);

	}

	public void setCapabilities(DeviceCapabilities cap) {
		this.cap = cap;
	}

	public DeviceCapabilities getCapabilities() {
		return cap;
	}

	@Override
	public String toString() {
		String val = "???";
		
		if( cap != null ) {
			val = cap.toString();
		}
		
		return val;
	}
	

}