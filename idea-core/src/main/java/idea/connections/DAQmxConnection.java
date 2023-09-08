package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;



public class DAQmxConnection extends RpConnection {

	public DAQmxConnection() {
		setTyp( RpConnType.DA_QMX );
	}


	@Override
	public String toString() {
		return typ.toString();
	}


}
