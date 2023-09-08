package icuInterface.conf.dev;

import idea.conf.DeviceConfiguration;

// note: might wrap up all the device configurations with a single "setConnectionValue()"

public class PhidgetDeviceConfiguration extends DeviceConfiguration {

	private static final long serialVersionUID = 1L;
	private int serNo;
	
	// might be able to fudge these values into "settings", maybe.
	
	private int gain;
	private int rate;
	
	public PhidgetDeviceConfiguration(Class<?> cl) {
		super(cl);		
	}
	
	public PhidgetDeviceConfiguration(Class<?> cl, int serNo) {
		super(cl);
		setSerNo(serNo);
	}
	
	public void setSerNo( Integer serNo) {
		this.serNo = serNo;
	}

	public int getSerNo() {
		return serNo;
	}

	public void setGain(Integer gain) {
		this.gain = gain;
	}

	public int getGain() {
		return gain;
	}

	public void setRate(Integer rate) {
		this.rate = rate;
	}

	public int getRate() {
		return rate;
	}


}
