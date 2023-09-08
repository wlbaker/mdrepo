package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;

public class TcpServerConnection extends RpConnection {
	public TcpServerConnection() {
		this.setTyp(RpConnType.ETHERNET);
	}

	@Override
	public String toString() {
		return typ.toString();
	}


}
