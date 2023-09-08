package idea.conf;


import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

import idea.schema.rp.RpConnection;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DeviceCapabilities extends DeviceConfiguration {
	/**
	 * 
	 */

	private long startTime;
	private long endTime;

	private String[] models;

	private List<RpConnection> connections = new LinkedList<RpConnection>();

	public DeviceCapabilities( String cl) {
		super(cl);
	}

	public DeviceCapabilities( Class<?> cl) {
		super(cl);
	}

	public DeviceCapabilities(RpDevice conf) {
		super(conf);
	}
	
	public DeviceCapabilities(DeviceCapabilities caps) {
		super(caps);
		connections = new LinkedList<RpConnection>(caps.connections);
	}

	public void setStartTime(long startTime) {
		this.startTime = startTime;
	}

	public long getStartTime() {
		return startTime;
	}

	public void setEndTime(long endTime) {
		this.endTime = endTime;
	}

	public long getEndTime() {
		return endTime;
	}

	public void setModels(String[] models) {
		this.models = models;
	}
	public String[] getModels() {
		return models;
	}

	public void setConnections(RpConnection[] RpConnections) {
		this.connections = Arrays.asList(RpConnections);
	}

	public RpConnection [] getConnections() {
		RpConnection [] intf = null;
		if( connections.size() > 0 ) {
			intf = new RpConnection[ connections.size() ];
			connections.toArray( intf );
		}
		
		return intf;
	}

	public void addConnection(RpConnection intf) {
		connections.add(intf);
	}


}
