package idea.gui;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.prefs.BackingStoreException;
import java.util.prefs.Preferences;

public abstract class AppSetup {

	private String APP_KEY;
	
	private static DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	
	public AppSetup(String appName) {
		APP_KEY = appName;
	}
	/*
	 * utility
	 */
	public String persistReadString(String key, String deflt ) {
		
		Preferences p = Preferences.userRoot();
		return p.get(APP_KEY + "/" + key, deflt );
	}
	
	public void persistWriteString(String key, String val) throws BackingStoreException {
		
		Preferences p = Preferences.userRoot();
		if( val == null ) {
			//System.out.println( "   persist removing key: " + key );
			p.remove( key );
		} else {
			p.put(APP_KEY + "/" + key, val);
		}
		p.flush();		
	}

	public void persistWriteFloat(String key, float val) throws BackingStoreException {
		Preferences p = Preferences.userRoot();
		p.putFloat(APP_KEY + "/" + key, val);
		p.flush();		
	}
	
	public float persistReadFloat(String key ) throws BackingStoreException {
		Preferences p = Preferences.userRoot();
		return p.getFloat(APP_KEY + "/" +  key , -1);
	}
	
	public void persistWriteDate(String key, Date tm) throws BackingStoreException {
		Preferences p = Preferences.userRoot();
		p.put(APP_KEY + "/" + key, df.format(tm));
		p.flush();		
	}

	public Date persistReadDate(String key) throws BackingStoreException, ParseException {
		Preferences p = Preferences.userRoot();
		String f = p.get(APP_KEY + "/" + key, null);
		return (f==null) ? null : df.parse(f);
	}

}
