package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class ROapdus {

	public static ByteBuffer encode(ByteBuffer pkt, short roivApdu,
			ByteBuffer payload ) {
		
		if( pkt == null ) {
			pkt = ByteBuffer.allocate( payload.remaining() + 4 );
		}
		
		pkt.putShort( C.ROIV_APDU );
		pkt.putShort( (short)payload.remaining() );
		pkt.put( payload );
		
		return pkt;
	}

}
