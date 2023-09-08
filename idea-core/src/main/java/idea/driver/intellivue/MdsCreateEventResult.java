package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class MdsCreateEventResult {

	public static ByteBuffer build(ByteBuffer pkt , ManagedObjectID mo, int event_time, short event_typ ) {
		if( pkt == null ) {
			pkt = ByteBuffer.allocate(  ManagedObjectID.size() + 8);
		}
		mo.encode( pkt );
		pkt.putInt( event_time );
		pkt.putShort( event_typ );
		pkt.putShort( (short) 0 );  // length...no attributes
		pkt.rewind();
		
		return pkt;
	}

}
