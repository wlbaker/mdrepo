package idea.tsoffline.canvas;

public enum LabelType {
	LABEL_CLOCKTIME, LABEL_SEC_DELETEME, LABEL_REL_MMSS, LABEL_REL_SECS;
	
	public static LabelType fromString(String s) {
		LabelType ret = null;
		switch (s) {
		case "ClockTime":
			ret = LABEL_CLOCKTIME;
			break;
		case "Sec":
			ret = LABEL_SEC_DELETEME;
			break;
		case "Relative MMSS":
			ret = LABEL_REL_MMSS;
			break;
		case "MMSS":
			ret = LABEL_REL_MMSS;
			break;
		case "Relative Secs":
			ret = LABEL_REL_SECS;
			break;
		case "None":
			ret = LABEL_REL_SECS;
			break;
		case "Inline":
			ret = LABEL_REL_SECS;
			break;
		}
		return ret;
	}
}
