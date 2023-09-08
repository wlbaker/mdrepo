package idea.analysis.event;

import icuInterface.events.NumericsEvent;
import icuInterface.message.NumericBlock;
import idea.message.StreamID;

@SuppressWarnings("serial")
public class BeatEvent extends NumericsEvent {

	public BeatEvent(Object source, NumericBlock vitals) {
		super(source, StreamID.MEASUREMENT, vitals, 0);
	}

	public BeatBlock getBeatBlock() {
		return (BeatBlock)block;
	}

}
