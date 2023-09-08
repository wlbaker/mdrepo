package idea.driver.intellivue;


import java.nio.ByteBuffer;

public class SinglePollDataRequest {
	
	private static final short CONTEXT_ID = 0;

	private static final short HANDLE = 0;
	
	public static ByteBuffer encode(ByteBuffer pkt, short m_obj_class, ByteBuffer mdib ) {

		if (pkt == null) {
			pkt = ByteBuffer.allocate(mdib.remaining() + 14);
		}

		pkt.putShort( m_obj_class );
		pkt.putShort( CONTEXT_ID );
		pkt.putShort( HANDLE );
		pkt.putInt( IntellivueDriver.RESERVED_SCOPE );
		pkt.putShort( C.NOM_ACT_POLL_MDIB_DATA );
		pkt.putShort( (short) mdib.remaining() );
		pkt.put( mdib );
		pkt.rewind();

		
		return pkt;
	}

	// public void FIXME() {
	// ByteBuffer bb = ByteBuffer.allocate(8);
	// bb.putShort((short) C.NOM_ATTR_TIME_PD_POLL);
	// bb.putShort((short) 4); // length
	// bb.putInt(12345); // attribute_val...relativetime is u_32
	// bb.position(0);
	// }
}
