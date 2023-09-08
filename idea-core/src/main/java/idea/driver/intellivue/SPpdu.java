package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class SPpdu {

	public static ByteBuffer build(ByteBuffer pkt, short session_id, short p_context_id, short len) {
		if( pkt == null ) {
			pkt = ByteBuffer.allocate(4 + len);
		}
		pkt.putShort( session_id );
		pkt.putShort( p_context_id );
		// pkt.putShort( len );
		
		return pkt;
	}

	public static ByteBuffer build(ByteBuffer pkt, short session_id, short p_context_id, ByteBuffer apdus) {
		pkt = build( pkt, session_id, p_context_id, (short)apdus.remaining() );
		pkt.put( apdus );
		
		pkt.rewind();
		return pkt;
	}

}
