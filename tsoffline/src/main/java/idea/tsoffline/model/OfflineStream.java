package idea.tsoffline.model;

import java.util.LinkedList;
import java.util.List;


import idea.message.StreamID;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.Getter;

// @Data
public class OfflineStream extends RpStream {

	@Getter
	private StreamID sid;

	public OfflineStream(StreamID sid) {
		this.sid = sid;
		if( sid != null ) {
			this.setName( sid.getName() );
		}
	}

	public void addSignal(OfflineSignal sig) {
		getMetric().add(sig);
	}

	public OfflineSignal getSignalFromLoc(String loc) {
		if (metric != null) {
			for (RpMetric sig : (List<? extends RpMetric>) metric) {
				if (loc.equals(sig.getLocation())) {
					return (OfflineSignal) sig;
				}
			}
		}
		return null;
	}

	public void removeChildSignal(OfflineSignal offlineSignal) {
		getMetric().remove(offlineSignal);
	}

	@Override
	public String toString() {
		return "" + sid;
	}

	public List<OfflineSignal> getCachedSignals() {
		// log.error( "FIXME: bad method to get signal info...deleteme");
		List<OfflineSignal> l = new LinkedList<OfflineSignal>();
		
		List<RpMetric> mm = super.getMetric();
		for( RpMetric m : mm ) {
			l.add( (OfflineSignal) m );
		}
		return l;
	}

}
