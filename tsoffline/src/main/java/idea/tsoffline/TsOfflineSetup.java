package idea.tsoffline;

import java.util.prefs.BackingStoreException;

import idea.gui.AppSetup;

public class TsOfflineSetup extends AppSetup {

	private static TsOfflineSetup instance;
	
	// keys
	public static final String METRIC_EXPORT_DIR = "mexDir";
	public static final String WAVE_EXPORT_DIR = "wexDir";
	public static final String EXPORT_MERGE = "merge";
	public static final String EXPORT_RESAMPLE = "resample";
	public static final String EXPORT_MINTERVAL = "minterval";
	public static final String ARCHIVE_FILE = "archfile";
	public static final String CONNECTION_URI = "conn_uri";
	private static final String APP_KEY = "TSOFFLINE";
	public static final String SFTP_HOST = "sftp_host";


	static {
		instance = new TsOfflineSetup(APP_KEY);
	}


	private TsOfflineSetup(String appKey) {
		super(APP_KEY);
	}

	/*
	 * getters
	 */
	public static String getExportDir() {
		return instance.persistReadString( METRIC_EXPORT_DIR, System.getProperty("user.home") );
	}
	
	public static String getWaveExportDir() {
		return instance.persistReadString( WAVE_EXPORT_DIR, System.getProperty("user.home") );
	}

	/*
	 * getters
	 */
	public static String getArchiveFile() {
		return instance.persistReadString( ARCHIVE_FILE, System.getProperty("user.home") );
	}
	
	public static void setArchiveFile(String file ) throws BackingStoreException {
		instance.persistWriteString( ARCHIVE_FILE, file );
	}

	public static String getConnectionURI() {
		return instance.persistReadString( CONNECTION_URI, "jdbc:sqlite:/tmp/file${SUBJECT}.db" );
	}
	
	public static void setConnectionURI(String uri ) throws BackingStoreException {
		instance.persistWriteString( CONNECTION_URI, uri );
	}

	/*	 * setters
	 */
	
	public static void setExportDir( String dir ) throws BackingStoreException {
		instance.persistWriteString( METRIC_EXPORT_DIR, dir );
	}

	public static void setWaveExportDir( String dir ) throws BackingStoreException {
		instance.persistWriteString( WAVE_EXPORT_DIR, dir );
	}

	public static boolean getMerge() {
		String s = instance.persistReadString( EXPORT_MERGE, "F" );
		return "T".equals(s);
	}

	public static void setMerge(boolean flag) throws BackingStoreException {
		String s = (flag) ? "T" : "F";
		instance.persistWriteString( EXPORT_MERGE, s );
	}

	public static int getResampleMethod() {
		String resampleMethod = instance.persistReadString( EXPORT_RESAMPLE, "0" );
		return Integer.parseInt( resampleMethod );
	}

	public static void setResampleMethod(int selectedIndex) throws BackingStoreException {
		instance.persistWriteString( EXPORT_RESAMPLE, Integer.toString(selectedIndex) );
	}
	
	public static int getMetricInterval() {
		String resampleMethod = instance.persistReadString( EXPORT_MINTERVAL, "1000" );
		return Integer.parseInt( resampleMethod );
	}

	public static void setMetricInterval(int interval) throws BackingStoreException {
		instance.persistWriteString( EXPORT_MINTERVAL, Integer.toString(interval) );
	}

	public static TsOfflineSetup getInstance() {
		return instance;
	}

	public static String getSFTPHost() {
		return instance.persistReadString( SFTP_HOST, "www.softhorizons.com" );
	}

	public static void saveSFTPHost(String sftpHost) throws BackingStoreException {
		instance.persistWriteString( SFTP_HOST, sftpHost );
	}

}
