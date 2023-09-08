package idea.intf;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import icuInterface.ConnectionStatus;
import idea.conf.DeviceConfiguration;
import idea.schema.rp.RpDevice;

/**
 * 
 * @author william.l.baker2
 *
 */
public interface AdapterInterface extends StreamProducer {
	public void connect() throws IOException;
	public void disconnect() throws IOException;
	
	public ConnectionStatus getStatus();
	public RpDevice getConfiguration();
	public DeviceConfiguration getStaticCapabilities();
	// public void requestSettingsUpdate( AbstractItem [] settings);
	
	public int tick();
	
	/**
	 * Test the input data to see if it is valid for this device.  Used in discovery.
	 * @param arr
	 * @return
	 */
	
	default public boolean verify(byte[] arr, int len) {
		return false;
	}
	
	/**
	 * Send probe data to the output stream to see if a recognized response is returned.  Used by discovery.
	 * 
	 * @param arr
	 * @return
	 */
	
	default void probe(OutputStream s) throws IOException {
		return;
	}
	
	/**
	 * Some devices are capable of processing data delivered from an outside source, particularly serial
	 * devices -- which includes all SerialAdapter subclasses and some Pista devices.
	 * 
	 * @param is InputStream
	 * @param os OutputStream
	 * 
	 * @throws IOException
	 */
	default public void process( InputStream is, OutputStream os ) throws IOException {
		return;
	}

}
