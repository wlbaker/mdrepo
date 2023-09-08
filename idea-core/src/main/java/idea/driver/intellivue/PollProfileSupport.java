package idea.driver.intellivue;

import static idea.driver.intellivue.C.POLL_PROFILE_REV_0;
import static idea.driver.intellivue.C.RELTIME_1SEC;

import java.nio.ByteBuffer;

public class PollProfileSupport implements Reportable {
	int poll_profile_revision = POLL_PROFILE_REV_0; // u_32
	int min_poll_period = 20 * RELTIME_1SEC; // u_32...unit is 1/8ms..8-->1ms 8000-->1sec
	int max_mtu_rx = 2500;
	int max_mtu_tx = 1000;
	int max_bw_tx = -1;
	int options = C.P_OPT_DYN_CREATE_OBJECTS | C.P_OPT_DYN_DELETE_OBJECTS;
	AttributeList optional_packages = new AttributeList() ;

	public PollProfileSupport() {

	}

	public ByteBuffer encode(ByteBuffer bb) {

		if( bb == null ) {
			bb = ByteBuffer.allocate(44);
		}
		bb.putInt(poll_profile_revision);
		bb.putInt(min_poll_period);
		bb.putInt(max_mtu_rx);
		bb.putInt(max_mtu_tx);
		bb.putInt( max_bw_tx );
		bb.putInt(options);
		optional_packages.encode(bb);
		
		bb.limit( bb.position() );
		bb.rewind();
		
		return bb;
	}

	public static PollProfileSupport parse(ByteBuffer bb) {
		PollProfileSupport sup = new PollProfileSupport();
		sup.poll_profile_revision = bb.getInt();
		sup.min_poll_period = bb.getInt();
		sup.max_bw_tx = bb.getInt();
		sup.max_mtu_rx = bb.getInt();
		sup.max_bw_tx = bb.getInt();
		sup.options = bb.getInt();
		sup.optional_packages = AttributeList.parse(bb);
		return sup;
	}
	
	@Override
	public void dump() {
		boolean pipe = false;
		
		System.out.println( "Poll Profile Support");
		System.out.println( "  poll_profile_revision : 0x" + Integer.toHexString(poll_profile_revision) );
		System.out.println( "        min_poll_period : " + min_poll_period );
		System.out.println( "             max_mtu_rx : " + max_mtu_rx );
		System.out.println( "             max_mtu_tx : " + max_mtu_tx );
		System.out.println( "              max_bw_tx : 0x" + Integer.toHexString(max_bw_tx) );
		System.out.print( "                options : 0x" + Integer.toHexString(options) + " " );
		if( (options &  C.P_OPT_DYN_CREATE_OBJECTS) != 0 ) {
			System.out.print( "P_OPT_DYN_CREATE_OBJECTS" );
			pipe = true;
		}
		if( (options &  C.P_OPT_DYN_DELETE_OBJECTS) != 0 ) {
			if( pipe ) System.out.print(" | ");
			System.out.print( "P_OPT_DYN_DELETE_OBJECTS" );
		}
		System.out.println();
		
		System.out.println( "  poll_profile_revision : " + poll_profile_revision );
		System.out.println( "*Optional Packages");
		optional_packages.dump();
	}

	//	typedef struct {
	//		OIDType attribute_id // u_16;
	//		u_16 length;
	//		u_16 attribute_val;
	//		} AVAType;

	public void addOptionalPackages(AVAType typ) {
		optional_packages.add( typ );
	}
	
	public AttributeList getOptionalPackages() {
		return optional_packages;
	}

}

