package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;

public class NoConnection extends RpConnection {
	
	public NoConnection() {
		this.setTyp(RpConnType.NONE );
	}
	
	@Override
	public String toString() {
		return typ.toString();
	}

}
