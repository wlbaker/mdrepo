package idea.tsoffline;

import java.util.Date;
import java.util.Observable;

import lombok.Data;

@Data
public class TimelineModel extends Observable {
	private Date endTime;
	private Date startTime;
	private Date startIntervalTime;
	private Date endIntervalTime;
	
	public void publish() {
		setChanged();
		notifyObservers();
	}
}
