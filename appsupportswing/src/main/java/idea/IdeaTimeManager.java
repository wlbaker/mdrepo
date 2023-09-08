package idea;

import java.util.Date;

public class IdeaTimeManager {

	private static Date currentDate = null;

	public static void setCurrentTime(Date dt) {
		currentDate = dt;
	}

	public static Date getCurrentTime() {
		if (currentDate == null) {
			return new Date();
		}

		return currentDate;
	}
}
