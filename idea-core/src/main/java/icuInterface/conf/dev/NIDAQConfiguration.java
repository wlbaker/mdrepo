package icuInterface.conf.dev;

import idea.conf.DeviceConfiguration;

//note: might wrap up all the device configurations with a single "setConnectionValue()"


public class NIDAQConfiguration extends DeviceConfiguration {

	/**
	 * 
	 */
	private static final long serialVersionUID = -7290251905189813467L;
	private int sampleRate = 500;
	private double premultiplier;
	private String terminalConfig;
	
	public NIDAQConfiguration(Class<?> cl) {
		super(cl);
	}

	public void setRate(Integer sampleRate) {
		this.sampleRate = sampleRate;
	}

	public int getRate() {
		return sampleRate;
	}
	
	public double getPremultiplier() {
		return premultiplier;
	}
	
	public void setPremultiplier( Double v ) {
		this.premultiplier = v;
	}
	
	public void setTerminalConfig( String terminalConfig ) {
		this.terminalConfig = terminalConfig;
	}
	public String getTerminalConfig( ) {
		// return terminalConfig;
		return "NRSE";
	}
}
