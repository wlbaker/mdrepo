package icuInterface.conf.dev;

import lombok.extern.slf4j.Slf4j;
import icuInterface.RpUtil;
import idea.conf.DeviceConfiguration;

//note: might wrap up all the device configurations with a single "setConnectionValue()"

@Slf4j
public class SocketDeviceConfiguration extends DeviceConfiguration {

	private static final long serialVersionUID = 1L;
	private String ip;
	private int port;
	
	public SocketDeviceConfiguration(Class<?> cl) {
		super(cl);		
	}
	
	public SocketDeviceConfiguration(Class<?> cl, String ip, int port) {
		super(cl);
		setHost(ip);
		setPort(port);
	}
	
	@Deprecated
	public void setHost(String ip) {
		this.ip = ip;
		
		log.warn("usage of deprecated call setHost()");
		RpUtil.setParam( this, "host", ip);

	}

	public String getHost() {
		return ip;
	}

	@Deprecated
	public void setPort(int port) {
		log.warn("usage of deprecated call setPort()");
		RpUtil.setParam( this, "port", "" + port);
		this.port = port;
	}

	public int getPort() {
		return port;
	}


}
