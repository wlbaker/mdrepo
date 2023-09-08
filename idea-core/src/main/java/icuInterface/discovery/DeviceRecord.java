package icuInterface.discovery;

import idea.intf.StreamProducer;

import java.net.InetAddress;
import java.util.LinkedList;
import java.util.List;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

@Data
@Slf4j
public class DeviceRecord {

	private StreamProducer driver;
	private String uniqueID;
	private String fullName;

	private long discoveryTime;  // used for infinity (and possibly other network...) timeouts
	
	private List<DiscoveryIntf> intfs = new LinkedList<DiscoveryIntf>();
	
	public void addInterface( String name ) {
		DiscoveryIntf di = new DiscoveryIntf( name );
		intfs.add( di );		
	}
	
	public void addInterface(String name, InetAddress addr, short port, short typ, short protocol) {
		DiscoveryIntf di = new DiscoveryIntf( name, addr, port, typ, protocol );
		intfs.add( di );		
	}
	
	public String getIntfName( int idx ) {
		return intfs.get(idx).getName();
	}

}
