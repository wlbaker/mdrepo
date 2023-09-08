package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;



public class InfinityConnection extends RpConnection {

	public InfinityConnection() {
		setTyp( RpConnType.INFINITY );
	}


	@Override
	public String toString() {
		return typ.toString();
	}


}
