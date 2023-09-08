package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;

public class PhidgetsConnection extends RpConnection {

	// SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE
	public PhidgetsConnection() {
		this.setTyp( RpConnType.PHIDGET );
	}

	@Override
	public String toString() {
		return typ.toString();
	}


}
