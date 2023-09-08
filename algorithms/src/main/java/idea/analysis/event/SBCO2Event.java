package idea.analysis.event;

import icuInterface.events.NumericsEvent;
import icuInterface.message.NumericBlock;
import idea.message.StreamID;

@SuppressWarnings("serial")
public class SBCO2Event extends NumericsEvent {

	public SBCO2Event(Object source, NumericBlock vitals) {
		super(source, StreamID.MEASUREMENT, vitals, 0);
	}

	public SBCO2Block getSBCO2Block() {
		return (SBCO2Block)block;
	}

}
