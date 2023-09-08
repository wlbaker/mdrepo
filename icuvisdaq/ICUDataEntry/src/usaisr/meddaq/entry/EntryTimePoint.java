package idea.meddaq.entry;

import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

public class EntryTimePoint {

	private String tpName;
	private int tpOffset;
	private LinkedList<TimepointAction> actions = new LinkedList<TimepointAction>();
	private Date dt;

	public EntryTimePoint(String name, int time_offset, String[] actionNames, int[] actionTimes) {
		this.tpName = name;
		this.tpOffset = time_offset;

		if (actionNames != null) {
			for (int idx = 0; idx < actionNames.length; idx++) {
				addAction(actionNames[idx], actionTimes[idx]);
			}
		}
	}

	public EntryTimePoint(String name, Date dt) {
		this.tpName = name;
		this.dt = dt;
	}

	public String getTpName() {
		return tpName;
	}

	public Date getTpTime(Date start) {
		if( start == null ) {
			return null;
		}
		Calendar cal = Calendar.getInstance();
		cal.setTime(start);
		
		cal.add(Calendar.MINUTE, tpOffset);
		Date tpValue = cal.getTime();
		
		return tpValue;
	}

	public List<TimepointAction> getActions() {
		
		return actions;
	}
	
	public void setTpOffsetInMinutes(int tpOffset) {
		this.tpOffset = tpOffset;
	}

	public int getTpOffsetInMinutes() {
		return tpOffset;
	}

	public void addAction(String actionName, int timeDiff) {
		TimepointAction action = new TimepointAction(actionName, timeDiff);

		actions.add( action );
	}

	public Date getTpDate() {
		return dt;
	}

	public void setTpDate(Date dt) {
		this.dt = dt;
	}

}
