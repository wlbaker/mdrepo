package idea.driver.intellivue;

import java.nio.ByteBuffer;

import lombok.Data;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@Data
public class SingleContextPoll implements Reportable {

	ObservationPoll[] observations;
	private short context_id;

	private SingleContextPoll() {
	}

	public static SingleContextPoll parse(ByteBuffer bb) {

		SingleContextPoll single_poll = new SingleContextPoll();

		single_poll.context_id = bb.getShort();
		short count = bb.getShort();
		short length = bb.getShort();

		assert (count >= 0) : "parseSingleContextPoll: count < 0";

		if (count > 0) {
			single_poll.observations = new ObservationPoll[count];
			for (int i = 0; i < count; i++) {
				single_poll.observations[i] = ObservationPoll.parse(bb);
			}
		}

		return single_poll;

	}

	@Override
	public void dump() {
		System.out.println("SingleContextPoll context=" + context_id );
		if( observations == null ) {
			System.out.println("no observation polls!");
		} else {
			for( ObservationPoll ob : observations ) {
				System.out.println( " OBSERVATION: ");
				ob.dump();
			}
		}
		
	}

}
