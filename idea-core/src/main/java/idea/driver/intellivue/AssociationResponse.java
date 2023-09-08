package idea.driver.intellivue;

import java.nio.ByteBuffer;

public class AssociationResponse implements Reportable {
	
	private MDSEUserInfoStd std;

	private AssociationResponse() { }
	
	public static AssociationResponse parse(ByteBuffer bb) {

		AssociationResponse resp = new AssociationResponse();
		
		byte pkt_type = bb.get();
		short li = parseLI(bb);

		byte [] seq1 = new byte[] { (byte)0xbe, (byte)0x80, 0x28, (byte)0x80, (byte)0x81 };
		int seq1_pos = 0;
		byte [] seq2 = new byte[] { (byte)0xbe, (byte)0x80, 0x28, (byte)0x80, 0x02, 0x01, 0x02, (byte)0x81 };
		int seq2_pos = 0;
		
		while( bb.remaining() > 0 ) {
			byte b = bb.get();
			seq1_pos = ( b == seq1[seq1_pos]) ? seq1_pos+1 : 0;
			seq2_pos = ( b == seq2[seq2_pos]) ? seq2_pos+1 : 0;
			
			if( seq1_pos == seq1.length || seq2_pos == seq2.length ) {
				parseLI(bb);
				resp.std = MDSEUserInfoStd.parse( bb );
				
				break;
			}
		}
		
		return resp;
	}

	private static short parseLI(ByteBuffer bb) {
		short val = bb.get();
		if (val < 0) {
			val += 256;
		}
		if (val == 0xff) {
			val = bb.getShort();
		}

		return val;
	}

	@Override
	public void dump() {
		
		System.out.println( "Association Response");
		
		System.out.println( "header...blob");
		std.dump();
		
	}

}
