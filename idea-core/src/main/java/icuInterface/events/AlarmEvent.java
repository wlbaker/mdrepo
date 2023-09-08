package icuInterface.events;

import idea.model.Alarm;

import java.util.EventObject;

@SuppressWarnings("serial")
public class AlarmEvent extends EventObject {
	private Alarm alarmItem;

	public AlarmEvent(Object source, Alarm alarmItem) {
		super(source);
		
		// assert( source instanceof AdapterInterface ) : "Expecting source to be an adapter/driver";
		
		this.setAlarmItem(alarmItem);

	}

	public void setAlarmItem(Alarm alarmItem) {
		this.alarmItem = alarmItem;
	}

	public Alarm getAlarmItem() {
		return alarmItem;
	}
	
	@Override
	public String toString() {
		
		return "alarmevt: " + alarmItem.toString();
	}

}
