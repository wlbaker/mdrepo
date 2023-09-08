package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class RORSapdus {

	public static ByteBuffer build(ByteBuffer pkt, short invoke_id, short cmd, ByteBuffer eventResult) {
		if( pkt == null ) {
			pkt = ByteBuffer.allocate(10 + eventResult.remaining());
		}
		pkt.putShort( C.RORS_APDU );
		pkt.putShort( (short)(eventResult.remaining() + 6) );
		pkt.putShort( invoke_id );
		pkt.putShort( cmd );
		pkt.putShort( (short)eventResult.remaining() );
		
		pkt.put(eventResult);
		pkt.rewind();
		
		return pkt;
	}

}
