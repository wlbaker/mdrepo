package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class ROIVapdus {

	public static ByteBuffer encode(ByteBuffer pkt, short invoke_id, short cmd, ByteBuffer arg ) {
		
		if( pkt == null ) {
			pkt = ByteBuffer.allocate(6 + arg.remaining() );
		}
		pkt.putShort( invoke_id );
		pkt.putShort(cmd);
		pkt.putShort( (short)arg.remaining() ); 

		
		pkt.put( arg );
		return pkt;
	}

}
