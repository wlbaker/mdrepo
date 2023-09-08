package icuInterface.conf.dev;

import icuInterface.RpUtil;
import idea.conf.DeviceConfiguration;


public class LabJackConfiguration extends DeviceConfiguration {

	public static final String SPP = "spp";
	public static final String SAMPLE_RATE = "sampleRate";
	
	public LabJackConfiguration(Class<?> cl) {
		super(cl);
		
		RpUtil.setParam(this, SPP, "50");
		RpUtil.setParam(this, SAMPLE_RATE, "500");
	}

}
