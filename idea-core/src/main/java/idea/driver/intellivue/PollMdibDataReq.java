package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class PollMdibDataReq {

	public static ByteBuffer encode(ByteBuffer pkt, short poll_no,
			short nomPartObj, short polled_obj_type, short polled_attr_grp,
			AttributeList l) {

		
		ByteBuffer attrib_bb = null;
		short attrib_len = 0;
		
		// l==null this is the difference between a single poll data request and an extended request  
		if( l != null ) {  
			attrib_bb = l.encode( null );
			attrib_bb.rewind();
			attrib_len = (short) attrib_bb.remaining();
		}

		if (pkt == null) {
			pkt = ByteBuffer.allocate(8 + attrib_len);
		}
		pkt.putShort(poll_no);
		pkt.putShort(nomPartObj);
		pkt.putShort(polled_obj_type);
		pkt.putShort(polled_attr_grp);
		if( attrib_bb != null ) {
			pkt.put( attrib_bb );
		}

		return pkt;
	}

}
