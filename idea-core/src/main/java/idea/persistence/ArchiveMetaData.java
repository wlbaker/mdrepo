package idea.persistence;

import java.util.Date;

public class ArchiveMetaData {

	private Date startTime;
	private Date stopTime;
	private int metric_count;

	public ArchiveMetaData() {
		// nuttin
	}
	
	public Date getStartTime() {
		return startTime;
	}

	public void setStartTime(Date startTime) {
		this.startTime = startTime;
	}

	public Date getStopTime() {
		return stopTime;
	}

	public void setStopTime(Date stopTime) {
		this.stopTime = stopTime;
	}

	public int getMetricCount() {
		return metric_count;
	}

	public void setMetricCount(int count) {
		this.metric_count = count;
	}

	public void add(ArchiveMetaData m2) {
		if( m2 == null ) {
			return;
		}
		if (getStartTime() == null)
			setStartTime(m2.getStartTime());
		if (getStopTime() == null)
			setStopTime(m2.getStopTime());

		if (getStartTime() != null && m2.getStartTime() != null) {
			if (getStartTime().getTime() > m2.getStartTime().getTime()) {
				setStartTime(m2.getStartTime());
			}
		}

		if (getStopTime() != null && m2.getStopTime() != null) {
			if (getStopTime().getTime() < m2.getStopTime().getTime()) {
				setStopTime(m2.getStopTime());
			}
		}

	}
}
