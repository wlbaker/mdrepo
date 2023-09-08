package icuInterface.events;

import icuInterface.ConnectionStatus;
import idea.intf.AdapterInterface;

import java.util.EventObject;

import lombok.Data;

@SuppressWarnings("serial")
@Data
public class MonitorEvent extends EventObject {
	private String devName;
	private AdapterInterface driver;
	private ConnectionStatus stat;
	private String portName;
	
	public MonitorEvent( Object src, String devName, AdapterInterface driver, ConnectionStatus stat, String portName ) {
		super(src);
		this.devName = devName;
		this.driver = driver;
		this.stat = stat;
		this.portName = portName;
	}
}
