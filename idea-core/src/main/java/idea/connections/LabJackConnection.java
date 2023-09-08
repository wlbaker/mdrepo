package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;



public class LabJackConnection extends RpConnection {

	public LabJackConnection() {
		setTyp( RpConnType.LAB_JACK );
	}


	@Override
	public String toString() {
		return typ.toString();
	}


}
