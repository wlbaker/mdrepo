package idea.meddaq;

import java.util.Date;

public interface MedDAQSubpanelInterface {

	void setRunMode(RunMode runMode);

	void updateClock(Date dt);

	void addAlarm(AlarmEnum timeout);

	void removeAlarm(AlarmEnum timeout);

}
