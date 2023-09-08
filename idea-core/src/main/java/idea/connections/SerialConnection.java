package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;
import lombok.Data;

@Data
public class SerialConnection extends RpConnection {
	private int baud;
	private int databits;
	private int stopbits;
	private int parity;

	public SerialConnection(int baud, int databits, int stopbits, int parity) {

		this.setTyp(RpConnType.RS_232 );
		this.baud = baud;
		this.databits = databits;
		this.stopbits = stopbits;
		this.parity = parity;
	}
	
	@Override
	public String toString() {
		return typ.toString();
	}


}
