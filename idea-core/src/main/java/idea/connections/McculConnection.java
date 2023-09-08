package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;



public class McculConnection extends RpConnection {

	public McculConnection() {
		setTyp( RpConnType.MCCUL );
	}


	@Override
	public String toString() {
		return typ.toString();
	}


}
