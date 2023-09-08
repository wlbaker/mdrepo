package idea.analysis;

import idea.intf.AbstractStreamProducer;
import idea.intf.StreamConsumer;

public abstract class AbstractAnalysisProcessor extends AbstractStreamProducer implements StreamConsumer {
	abstract void reset();
}
