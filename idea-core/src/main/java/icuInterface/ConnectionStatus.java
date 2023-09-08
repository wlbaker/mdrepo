package icuInterface;

import java.util.EnumSet;

public enum ConnectionStatus {

	NOT_CONNECTED(0x0001), //
	NEGOTIATING(0x0002), // both connected and not connected flags set
	STANDBY(0x0211), // needs to be applied to Infinity
	CONNECTED(0x0010), //
	AUTHENTICATED( 0x0011),
	//SERVER_CURRENTLY_FULL(0x1010), // connected and a particular error
	DATA_AVAILABLE(0x0110), //
	DATA_NOT_AVAIL(0x0210), // ??
	ERROR(0x2010); // connected and general error

	private int code;

	ConnectionStatus(int code) {
		this.code = code;
	}

	public int getCode() {
		return this.code;
	}
	
	public static ConnectionStatus lookup( int code ) {
		for (ConnectionStatus s : EnumSet.allOf(ConnectionStatus.class)) {
			if( s.getCode() == code ) {
				return s;
			}
		}
		
		return null;
	}

}
