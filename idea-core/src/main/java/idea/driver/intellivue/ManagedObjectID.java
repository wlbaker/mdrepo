package idea.driver.intellivue;

import java.nio.ByteBuffer;

import lombok.Data;

@Data
public class ManagedObjectID implements Reportable {

	short object_class;
	GlbHandle object_inst = new GlbHandle();
		
	public static ManagedObjectID parse(ByteBuffer bb) {
		ManagedObjectID mo = new ManagedObjectID();
		mo.object_class = bb.getShort();
		GlbHandle.parse( bb );
		return mo;
	}

	public void encode(ByteBuffer pkt) {
		pkt.putShort( object_class );
		object_inst.encode( pkt );
		
	}
	public static void encode(ByteBuffer pkt, short m_obj_class, short context_id, short handle) {
		pkt.putShort( m_obj_class );
		pkt.putShort( context_id );
		pkt.putShort( handle );
	}

	public static int size() {
		return 2 + GlbHandle.size();
	}

	@Override
	public void dump() {
		System.out.println( "Managed Object");
		System.out.println(  "m_obj_class=" + object_class);
		System.out.println(  "    context=" + object_inst.getContextID() );
		System.out.println(  "     handle=" + object_inst.getHandle() );
		
	}
}
