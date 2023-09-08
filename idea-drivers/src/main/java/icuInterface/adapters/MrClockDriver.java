package icuInterface.adapters;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

import icuInterface.ConnectionStatus;
import icuInterface.conf.dev.SocketDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.DisplayInterface;
import idea.schema.rp.RpDevice;

public class MrClockDriver extends AbstractStreamProducer implements AdapterInterface, DisplayInterface {

	private static final String driverName="z/MrClock Driver";
	private RpDevice conf;

	private int id = 0;

	private String host;

	public static DeviceConfiguration createConfigInstance() {
		return new SocketDeviceConfiguration(MrClockDriver.class);
	}

	/**
	 * 
	 */
	public MrClockDriver(RpDevice conf) {
		this.conf = conf;
	}

	/**
	 * Sets a display message on the LED with no special text modes (sends in
	 * "Hold" mode);
	 * 
	 * @param topLine
	 *            Top line String
	 * @param bottomLine
	 *            Bottom Line String
	 * @throws IOException
	 */
	@Override
	public void setDisplayMessage(String topLine, String bottomLine) throws IOException {

		topLine = (topLine.length() > 0) ? topLine.trim() : " ";
		bottomLine = (bottomLine.length() > 0) ? bottomLine : " ";
		postDisplayMessage(topLine, bottomLine);
	}

	private void postDisplayMessage(String topLine, String bottomLine) throws IOException {
		String urlParameters = "dev=" + id + "&line1=" + topLine + "&line2=" + bottomLine;
		String type = "application/x-www-form-urlencoded";
		// String encodedData = URLEncoder.encode( rawData );
		URL u = new URL("http://" + host + ":6342/updateClock");
		HttpURLConnection conn = (HttpURLConnection) u.openConnection();
		conn.setDoOutput(true);
		conn.setRequestMethod("POST");
		conn.setRequestProperty("Content-Type", type);
		conn.setRequestProperty("Content-Length", Integer.toString(urlParameters.getBytes().length));
		// conn.setRequestProperty( "Content-Length",
		// String.valueOf(encodedData.length()));

		DataOutputStream os = new DataOutputStream(conn.getOutputStream());
		os.writeBytes(urlParameters);
		// os.write( encodedData.getBytes() );
		os.flush();
		os.close();
		String resp = conn.getResponseMessage();
		conn.disconnect();
		

	}

	@Override
	public ConnectionStatus getStatus() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int tick() {
		return 0;
	}

	@Override
	public RpDevice getConfiguration() {
		return conf;
	}
	
	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return null;
	}

	@Override
	public void connect() throws IOException {
		this.host = conf.getConnectionValue();
		String[] arr = host.split("/");
		if( arr.length == 2 ) {
			this.host = arr[0];
			this.id = Integer.parseInt(arr[1]);
		}
	}

	@Override
	public void disconnect() throws IOException {
		// TODO Auto-generated method stub
		
	}

}
