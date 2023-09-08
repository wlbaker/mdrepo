package idea.tsoffline.model;

import idea.message.StreamID;
import idea.schema.rp.RpDevice;

public class OfflineDevice extends RpDevice<OfflineStream> {


	public OfflineDevice( String name ) {
		setName( name );
	}
	
	public void addStream(OfflineStream sig) {
		getStreams().add( sig );
	}

	public OfflineStream getStream(StreamID sid) {
		for( OfflineStream stream : getStreams() ) {
			
			if( sid.equals(stream.getSid()) ) {
				return stream;
			}
		}
		return null;
	}
	
	@Override public String toString() {
	     return getName();
	}
	
}
