package icuInterface.events;


import icuInterface.message.NumericBlock;
import idea.message.StreamID;

import java.util.EventObject;


@SuppressWarnings("serial")
public class NumericsEvent extends EventObject {

	protected Object block;
	private StreamID subclass;
	private int requestId;
	
	public NumericsEvent(Object source,StreamID scope, Object block, int requestId ) {
		super(source);

		this.setSubclass(scope);
		this.block = block;
		this.requestId = requestId;
	}
	
	public int getRequestId() {
		return requestId;
	}

	public Object getBlock() {
		return block;
	}
	public NumericBlock getNumericsBlock() {
		if( block instanceof NumericBlock ) {
			return (NumericBlock) block;
		}
		return null;
	}
	
	public StreamID getSubclass() {
		return subclass;
	}

	public void setSubclass(StreamID subclass) {
		this.subclass = subclass;
	}


}
