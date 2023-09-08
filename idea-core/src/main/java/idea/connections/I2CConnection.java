package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;

public class I2CConnection extends RpConnection {
	public I2CConnection() {
		this.setTyp(RpConnType.I_2_C);
	}

	@Override
	public String toString() {
		return typ.toString();
	}


}
