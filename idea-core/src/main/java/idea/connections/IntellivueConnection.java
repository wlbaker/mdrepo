package idea.connections;

import idea.schema.rp.RpConnType;
import idea.schema.rp.RpConnection;



public class IntellivueConnection extends RpConnection {

	public IntellivueConnection() {
		setTyp( RpConnType.INTELLIVUE );
	}


	@Override
	public String toString() {
		return typ.toString();
	}


}
