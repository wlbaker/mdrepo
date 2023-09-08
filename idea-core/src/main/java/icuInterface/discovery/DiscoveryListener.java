package icuInterface.discovery;

public interface DiscoveryListener {

	void discover(DiscoveryAction action, DeviceRecord dev);
	void error( DeviceRecord dev, String message, Exception x );
}
