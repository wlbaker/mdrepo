package icuInterface.discovery;

import java.net.InetAddress;

import lombok.Data;

@Data
public class DiscoveryIntf {
	public DiscoveryIntf( String name ) {
		this.name = name;
	}
	
	public DiscoveryIntf(String name, InetAddress addr, short port, short typ, short protocol) {
		this.addr = addr;
		this.name = name;
		this.port = port;
		this.typ = typ;
		this.protocol = protocol;
	}
	
	private InetAddress addr;
	private String name;
	private short port;
	private short typ;
	private short protocol;


}
