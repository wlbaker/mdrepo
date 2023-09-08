package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;



public class DtConnection extends RpConnection {

	public DtConnection() {
		setTyp( RpConnType.DT );
	}


	@Override
	public String toString() {
		return typ.toString();
	}


}
