package icuInterface.events;

import idea.model.DisplayConfig;

import java.util.EventObject;

public class DisplayEvent extends EventObject {

	private static final long serialVersionUID = 1519789946653270221L;

	private DisplayConfig conf;

	public DisplayEvent(Object source, DisplayConfig conf) {
		super(source);
		this.setConfig(conf);

	}

	public void setConfig(DisplayConfig conf) {
		this.conf = conf;
	}

	public DisplayConfig getConfig() {
		return conf;
	}

	@Override
	public String toString() {
		String val = "???";
		
		if( conf != null ) {
			val = conf.toString();
		}
		
		return val;
	}
	

}