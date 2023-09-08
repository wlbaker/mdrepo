package idea.analysis;

import idea.display.simple.TwoValuePanel;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class UpdateNumericField implements StreamConsumer {

	private TwoValuePanel metricPanel;
	private int pos;
	private String loc;
	private double mult;

	public UpdateNumericField(TwoValuePanel metricPanel, int pos, String loc) {
		this(metricPanel, pos, loc, 0);
	}

	public UpdateNumericField(TwoValuePanel metricPanel, int pos, String loc, double mult) {
		this.metricPanel = metricPanel;
		this.pos = pos;
		this.loc = loc;
		this.mult = mult; // CURRENTLY IGNORED!
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.MEASUREMENT) {
			Number val = IntfUtil.getScaledValueByLoc(item, loc);

			if (val == null) {
				log.error("invalid loc code: {}", loc);
			} else {

				// v = v.intValue();
				if (pos == 0) {
					metricPanel.setUpperValue(val);
				} else if (pos == 1) {
					metricPanel.setLowerValue(val);
				}
			}
		} else {
			log.error("INTERNAL TYPE ERROR IN UPDATE NUMERIC");
		}
	}
}
