package idea.analysis;

import idea.intf.StreamProducer;


public interface AnalysisPanelInterface { // extends SignalConsumer {
	// public void connect();
	public void clear();
	public void autoscale();
	
	public void tick();
	
	public StreamProducer [] getSignalProducers();
}
