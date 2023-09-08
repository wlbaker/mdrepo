package idea.driver.intellivue;

import java.nio.ByteBuffer;

import lombok.Data;

@Data
public class GlbHandle {

	private short contextID;  // get only
	private short handle;  // get only

	public static GlbHandle parse(ByteBuffer bb) {
		GlbHandle glb = new GlbHandle();
		glb.contextID = bb.getShort();
		glb.handle = bb.getShort();
		
		return glb;
	}

	public void encode(ByteBuffer pkt) {
		pkt.putShort( contextID );
		pkt.putShort( handle );
		
	}

	public static int size() {
		return 4;
	}

}
