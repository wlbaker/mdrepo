package idea.driver.intellivue;


import java.nio.ByteBuffer;

public class EventReportArgument {

	public ManagedObjectID mo;
	public short handle;
	public int current_time;
	public short event_type;
	public short payload_len;
	
	public static EventReportArgument parse(ByteBuffer bb) {
		EventReportArgument era = new EventReportArgument();
		
		era.mo = ManagedObjectID.parse( bb );
		era.current_time = bb.getInt();
		era.event_type = bb.getShort();
		era.payload_len = bb.getShort();

		return era;
	}

	public ManagedObjectID getManagedObject() {
		return mo;
	}

}
