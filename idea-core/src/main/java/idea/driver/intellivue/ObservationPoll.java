package idea.driver.intellivue;

import java.nio.ByteBuffer;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

@Data
@Slf4j
public class ObservationPoll implements Reportable {
	private short obj_handle;
	private AttributeList attributes;

	private ObservationPoll() { }

	public static ObservationPoll parse(ByteBuffer bb) {
		ObservationPoll poll = new ObservationPoll();
		poll.obj_handle = bb.getShort();
		log.debug("parsing observation obj: {}", poll.obj_handle );
		poll.attributes = AttributeList.parse(bb);
		
		return poll;
	}
	
	@Override
	public void dump() {
		System.out.println("ObservationPoll");
		System.out.println("   obs object_handle: 0x" + Integer.toHexString(obj_handle) );
		System.out.println("   obs attributes: " );
		attributes.dump();
	}
	
	
}
