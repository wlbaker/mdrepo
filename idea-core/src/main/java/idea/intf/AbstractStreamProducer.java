package idea.intf;

import icuInterface.ConnectionStatus;
import icuInterface.events.CapabilitiesEvent;
import icuInterface.events.ConnectionItem;
import icuInterface.events.IdentificationEvent;
import icuInterface.events.ManagementEvent;
import icuInterface.events.SecurityEvent;
import idea.conf.DeviceConfiguration;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.DisplayConfig;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStream;

import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class AbstractStreamProducer implements StreamProducer {

	private List<Object> streamListeners = new LinkedList<Object>();

	protected HashMap<StreamID, PersistentItem> cacheMap = new HashMap<StreamID, PersistentItem>();
	private ConnectionStatus connStat;

	@Override
	public void addStreamListener(StreamID sid, StreamConsumer l) {

		if (l == null) {
			log.error("cannot add null stream listener!");
		} else {

			Iterator<Object> ii = streamListeners.iterator();
			while (ii.hasNext()) {
				Object sid2 = ii.next();
				Object listener2 = ii.next();

				if (l == listener2) {
					if ((sid == null || sid2 == null)) {
						log.warn("REJECTING OVERLAP: {}", l);
						return;
					}
					if (sid.equals(sid2)) {
						log.warn("REJECTING DUPLICATE STREAM LISTENER: {}", l);
						return;
					}
				}
			}
			streamListeners.add(sid);
			streamListeners.add(l);
		}

	}

	/**
	 * Will remove an EventType from the EventListener's set. Meaning the
	 * listener no longer wants to receives events of this type. If the
	 * EventListener is not in the ListenerMap then it will do nothing.
	 * 
	 * @param eventListener
	 * @param eventType
	 */
	public void removeStreamListener(StreamConsumer eventListener, StreamID sid) {

		int pos = 0;

		if (eventListener == null) {
			log.warn("FIXME: removing all listeners...perfer a seperate method just for clarity!");
		}
		synchronized (streamListeners) {

			Iterator<Object> ii = streamListeners.iterator();
			while (ii.hasNext()) {
				StreamID ssid = (StreamID) ii.next();
				if (ssid.equals(sid)) {
					StreamConsumer l = (StreamConsumer) ii.next();
					if (eventListener == null || l == eventListener) {
						streamListeners.remove(pos);
						streamListeners.remove(pos);

						ii = streamListeners.iterator(); // bubble sort
															// effeciency
						pos = 0;
						continue;
					}
				}
				pos += 2;
			}

		}
	}

	public void removeAllStreamListeners() {

		synchronized (streamListeners) {

			Iterator<Object> ii = streamListeners.iterator();
			while (ii.hasNext()) {
				ii.remove();  // StreamID ssid = (StreamID) ii.next();
				ii.remove();  // StreamConsumer l = (StreamConsumer) ii.next();
			}

		}
	}

	/**
	 * Will remove an EventListener's from the ListenerMap. Meaning the listener
	 * no longer wants to receives events. If the EventListener is not in the
	 * ListenerMap then it will do nothing.
	 * 
	 * @param eventListener
	 */
	@Override
	public void removeStreamListener(StreamConsumer eventListener) {
		int pos = 0;

		synchronized (streamListeners) {

			Iterator<Object> ii = streamListeners.iterator();
			while (ii.hasNext()) {
				Object o = ii.next();
				StreamConsumer l = (StreamConsumer) ii.next();
				if (l == eventListener) {
					streamListeners.remove(pos);
					streamListeners.remove(pos);

					ii = streamListeners.iterator(); // bubble sort effeciency
					pos = 0;
					continue;
				}
				pos += 2;
			}
		}
	}

	/**
	 * Fires event to listener. A listener will receive the event only if they
	 * are listening for events of eventType.
	 * 
	 * @param eventType
	 *            The Type of Event being sent
	 * @param event
	 *            Event to be sent
	 */
	// @Override
	public void fireStreamEvent(int jobId, StreamProducer src, StreamID sid, PersistentItem block) {

		cacheMap.put(sid, block);

		synchronized (streamListeners) {
			Iterator ii = streamListeners.iterator();
			while (ii.hasNext()) {
				Object ssid = ii.next();
				StreamConsumer l = (StreamConsumer) ii.next();
				assert (l != null) : "fire to NULL LISTENER!!!";
				if (ssid == null || ssid.equals(sid)) {
					l.streamEvent(jobId, src, sid, block);
				}
			}
		}
	}

	public void setStatus(ConnectionStatus stat) {
		setStatus(stat, null);
	}

	public void setStatus(ConnectionStatus stat, String info) {
		if (stat != connStat) {
			connStat = stat;

			ConnectionItem e = new ConnectionItem(stat, info);
			fireStreamEvent(0, this, StreamID.CONNECTION, e);
		}
	}

	public void fireDisplayEvent(StreamProducer src, DisplayConfig disp) {
		fireStreamEvent(0, src, StreamID.DISPLAY, disp);
	}

	public void fireCapabilitiesEvent(StreamProducer src, DeviceConfiguration conf) {
		fireStreamEvent(0, src, StreamID.CAPABILITIES, new CapabilitiesEvent(src, conf));
	}

	public void fireIdentificationEvent(StreamProducer src, String id) {
		fireStreamEvent(0, src, StreamID.IDENTIFICATION, new IdentificationEvent(src, id));
	}

	public void fireManagementEvent(StreamProducer src, int action, int reqid, RpDevice conf) {
		fireStreamEvent(0, src, StreamID.MANAGEMENT, new ManagementEvent(src, action, reqid, conf));
	}

	public void fireAlarmEvent(StreamProducer src, Alarm alarmBlock) {
		fireStreamEvent(0, src, StreamID.ALARM, alarmBlock);
	}

	protected void fireConnectionEvent(StreamProducer src, ConnectionStatus stat) {
		fireStreamEvent(0, src, StreamID.CONNECTION, new ConnectionItem(stat));
	}

	public void fireSecurityEvent(StreamProducer src, boolean access) {
		fireStreamEvent(0, src, StreamID.SECURITY, new SecurityEvent(src, access));
	}

	protected void fireNoData(RpDevice conf) {
		cacheMap.clear();

		for (RpStream stream : (List<? extends RpStream>)conf.getStreams()) {
			StreamID sid = StreamID.fromName(stream.getName());
			fireStreamEvent(0, this, sid, null);
		}
	}

	@SuppressWarnings("unchecked")
	@Override
	public PersistentItem getEvent(StreamID sid) {
		return cacheMap.get(sid);
	}

	// a little help for the script engine
	public PersistentItem getEvent(String streamName) {
		StreamID sid = StreamID.fromName(streamName);
		return getEvent(sid);
	}

	@Override
	public ConnectionStatus getStatus() {
		return connStat;
	}

	@Override
	public void requestCapabilities() throws IOException {
		RpDevice caps = getStaticCapabilities();
		CapabilitiesEvent ce = new CapabilitiesEvent(this, (DeviceConfiguration) caps);

		fireStreamEvent(0, this, StreamID.CAPABILITIES, ce);
	}

	@Override
	public RpDevice getConfiguration() {
		return getStaticCapabilities();
	}

	public void requestSettingsUpdate(PersistentItem settings) throws IOException {
		assert (false) : "this device does not support settings";
		log.error("requestSettingsUpdate not available for this device: {}", this);
	}


}
