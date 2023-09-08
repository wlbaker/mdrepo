package idea.meddaq.entry;

import java.util.Date;

public class TimepointAction {
	private String actionName;
	private int timeDeltaInSeconds;
	
	public TimepointAction(String actionName, int timeDiff) {
		this.actionName = actionName;
		this.timeDeltaInSeconds = timeDiff;
	}

	public String getName() {
		return actionName;
	}
	
	public Date getActionTime(Date tpTime) {
		long ms = tpTime.getTime() - 1000* timeDeltaInSeconds;
		return new Date(ms);
	}

	
}
