package icuInterface.events;

import icuInterface.ConnectionStatus;

import java.util.EventObject;

public class ConnectionEventObsolete extends EventObject {

	private static final long serialVersionUID = 1519789946653270221L;
	
	String connectInfo;

	
	private ConnectionStatus status;

	public ConnectionEventObsolete(Object source, ConnectionStatus newStatus) {
		this(source, newStatus, "<????>" ); 
	}

	public ConnectionEventObsolete(Object source, ConnectionStatus newStatus, String connectInfo) {
		super(source);
		this.setStatus(newStatus);
		this.connectInfo = connectInfo;
	}

	public void setStatus(ConnectionStatus status) {
		this.status = status;
	}

	public ConnectionStatus getStatus() {
		return status;
	}

	public String getConnectInfo() {
		return connectInfo;
	}


	@Override
	public String toString() {
		String val = "???";
		
		if( status != null ) {
			val = status.toString();
		}
		
		return val;
	}
	

}