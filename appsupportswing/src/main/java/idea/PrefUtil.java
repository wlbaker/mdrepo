package idea;


import java.util.prefs.BackingStoreException;
import java.util.prefs.Preferences;

import lombok.Getter;
import lombok.Setter;

public class PrefUtil {
	@Setter
	@Getter
	private static String APP_KEY = "Global";
	/**
	 *  This is a convenient place to store app version, but not used directly by prefs.
	 *  App name and version are used for exception reporting by GuiUtil.
	 */
	@Setter
	@Getter
	private static String appVersion = null;
	
	@Setter
	@Getter
	private static String appFile = null;  // only used for debug message generation
	private static String persistanceRoot = null;  // maybe these two should be the same???


	/*
	 * 
	 */
	
	public static void saveUserPref( String sub, String val ) {
		saveUserPref( APP_KEY, sub , val);
	}
	
	public static void saveUserPref( String appKey, String sub, String val ) {
		// write into HKCU\Software\Javasoft\Prefs\$APP_KEY
		Preferences p = Preferences.userRoot();
		p.put(appKey + "/" + sub, val);
		try {
			p.flush();
		} catch (BackingStoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static String getUserPref( String sub, String def_val ) {
		return getUserPref( APP_KEY, sub, def_val);
	}

	public static String getUserPref( String appKey, String sub, String def_val ) {
		Preferences p = Preferences.userRoot();
		return p.get(appKey + "/" + sub, def_val);
	}

	/*
	 * 
	 */
	
	public static void saveSystemPref( String sub, String val ) {
		// write into HKLM\Software\Javasoft\Prefs\$APP_KEY
		Preferences p = Preferences.systemRoot();
		p.put(APP_KEY + "/" + sub , val );
		try {
			p.flush();
		} catch (BackingStoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static String getSystemPref( String sub, String def_val ) {
		Preferences p = Preferences.systemRoot();
		return p.get(APP_KEY + "/" + sub, def_val);
	}

	/*
	 * 
	 */
	
	public static void setAppName(String appName) {
		APP_KEY = appName;
	}

	public static String getAppName() {
		return APP_KEY;
	}

	public static Preferences getPreferences() {
		Preferences pref = null;

		if (persistanceRoot != null) {
			pref = Preferences.userRoot().node(persistanceRoot);
		} else {
			pref = Preferences.userRoot().node("global");
		}

		return pref;
	}


}
