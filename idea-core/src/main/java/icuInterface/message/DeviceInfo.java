package icuInterface.message;

import icuInterface.ConnectionStatus;

// NOTE: this class might disappear.  The information I really want is in the configuration.
// I might be able to use one of the elements of that structure directly.

@Deprecated
public class DeviceInfo {

	private String name;
	private ConnectionStatus state;
	private String model;
	
	public DeviceInfo(String name, ConnectionStatus state, String model) {
		this.setName(name);
		this.setState(state);
		this.setModel( model );
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public void setState(ConnectionStatus state) {
		this.state = state;
	}

	public ConnectionStatus getState() {
		return state;
	}

	public void setModel(String model) {
		this.model = model;
	}

	public String getModel() {
		return model;
	}
	
}
