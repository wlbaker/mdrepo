package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class PollProfileExt implements Reportable {

	private int options;
	private AttributeList attrs = new AttributeList();
	
	public PollProfileExt(int options) {
		this.options = options;
	}

	public ByteBuffer encode(ByteBuffer bb) {
		assert( bb == null ) : "always returning a new re-wound bytebuffer";
		
		ByteBuffer pollProfileExt = ByteBuffer.allocate(44);
		pollProfileExt.putInt( options );
		pollProfileExt.putShort( (short) 0 ); // count
		pollProfileExt.putShort( (short) 0); // length
		pollProfileExt.limit( pollProfileExt.position() );
		pollProfileExt.position(0);
		return pollProfileExt;
	}

	@Override
	public void dump() {
		boolean pipe = false;
		System.out.println("PollProfileExt");
		System.out.print("  options : 0x" + Integer.toHexString(options) + " ");
		if( (options &  C.POLL_EXT_PERIOD_NU_1SEC) != 0 ) {
			System.out.print( "POLL_EXT_PERIOD_NU_1SEC" );
			pipe = true;
		}
		if( (options &  C.POLL_EXT_PERIOD_RTSA) != 0 ) {
			if( pipe ) System.out.print(" | ");
			System.out.print( "POLL_EXT_PERIOD_RTSA" );
			pipe = true;
		}
		if( (options &  C.POLL_EXT_DYN_MODALITIES) != 0 ) {
			if( pipe ) System.out.print(" | ");
			System.out.print( "POLL_EXT_DYN_MODALITIES" );
			pipe = true;
		}
		if( (options &  C.POLL_EXT_PERIOD_NU_AVG_12SEC) != 0 ) {
			if( pipe ) System.out.print(" | ");
			System.out.print( "POLL_EXT_PERIOD_NU_AVG_12SEC" );
			pipe = true;
		}
		if( (options &  C.POLL_EXT_PERIOD_NU_AVG_60SEC) != 0 ) {
			if( pipe ) System.out.print(" | ");
			System.out.print( "POLL_EXT_PERIOD_NU_AVG_60SEC" );
			pipe = true;
		}
		if( (options &  C.POLL_EXT_PERIOD_NU_AVG_300SEC) != 0 ) {
			if( pipe ) System.out.print(" | ");
			System.out.print( "POLL_EXT_PERIOD_NU_AVG_300SEC" );
			pipe = true;
		}
		System.out.println();
		System.out.println("*attr" );
		// assert( options == (C.POLL_EXT_PERIOD_NU_1SEC | C.POLL_EXT_PERIOD_RTSA) ) : "PollProfileExt NOT EXPECTED OPTIONS!";
		attrs.dump();
	}

	public static PollProfileExt parse(ByteBuffer bb) {
		PollProfileExt ext = new PollProfileExt( 0 );
		ext.options = bb.getInt();
		ext.attrs = AttributeList.parse(bb);
		return ext;
	}
	
	

}
