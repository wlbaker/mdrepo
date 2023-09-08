package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class MdsGenSystemInfoEntry {

	private short choice;
	private byte[] value;

	private MdsGenSystemInfoEntry() {
		
	}
	
	public static MdsGenSystemInfoEntry[] parseArray(ByteBuffer bb) {
		short count = bb.getShort();
		short length = bb.getShort();
		
		for( int i = 0; i < count ; i++ ) {
			parse(bb);
		}
		return null;
	}

	private static void parse(ByteBuffer bb) {
		MdsGenSystemInfoEntry info = new MdsGenSystemInfoEntry();
		info.choice = bb.getShort();
		int len = bb.getShort();
		if( len > 0 ) {
			info.value = new byte[len];
			bb.get( info.value );
		}
		
		if( info.choice == C.MDS_GEN_SYSTEM_INFO_SYSTEM_PULSE_CHOSEN ) {
			// hm...ignore
		} else {
			System.err.println( "UNKNOWN MDS_GEN_SYSTEM_INFO=" + info.choice );
		}
	}

}
