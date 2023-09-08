package idea;

import java.util.LinkedList;
import java.util.prefs.BackingStoreException;
import java.util.prefs.Preferences;

import javax.print.DocFlavor;
import javax.print.PrintService;
import javax.print.PrintServiceLookup;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;

public class ConfigurationInfo {
	public static String getSelectedPrinter(String task) {
		Preferences userPrefs = PrefUtil.getPreferences();
		return userPrefs.get("PRINTER:" + task, null);
	}

	public static void setSelectedPrinter(String task, String printerName) throws BackingStoreException {
		Preferences userPrefs = PrefUtil.getPreferences();
		userPrefs.put("PRINTER:" + task, printerName);
		userPrefs.flush();
	}

	public static Object[] getPrinterList() {
		LinkedList<Object> l = new LinkedList<Object>();

		DocFlavor flavor = DocFlavor.SERVICE_FORMATTED.PRINTABLE;
		PrintRequestAttributeSet aset = new HashPrintRequestAttributeSet();
		// aset.add(new JobName("Test", null));
		PrintService[] services = PrintServiceLookup.lookupPrintServices(flavor, aset);

		for (int i = 0; i < services.length; i++) {
			l.add(services[i]);
			// l.add(services[i].getName());
		}

		return l.toArray();

	}

	public static PrintService getNamedPrinter(String printerName) {

		DocFlavor flavor = DocFlavor.SERVICE_FORMATTED.PRINTABLE;
		PrintRequestAttributeSet aset = new HashPrintRequestAttributeSet();
		PrintService[] services = PrintServiceLookup.lookupPrintServices(flavor, aset);
		PrintService service = null;

		for (int i = 0; i < services.length; i++) {
			String name = services[i].getName();
			if (printerName.equals(name)) {
				service = services[i];
				break;
			}
			name = services[i].toString();
			;
			if (printerName.equals(name)) {
				service = services[i];
				break;
			}
		}

		return service;

	}

	public static Object[] getDetectorList() {
		String[] l = new String[] { //
				"PT1", "PT2", "CAT", "MOBD", "AESOP", //
				"FB", "FIXED", "CL", //
				"EMD", "BEBOP", "BEBOP2", "MULTIW", "ONSET" };

		return l;
	}

	public static Float getObject(String string) {
		// TODO Auto-generated method stub
		return null;
	}

	public static String getLogoName() {
		// TODO Auto-generated method stub
		return null;
	}

	public static void putObject(String string, float zoom) {
		// TODO Auto-generated method stub

	}

	public static String getCompanyName() {
		return "CompanyFromSiteInfo";
	}

	public static String getEmailAddress() {
		// TODO Auto-generated method stub
		return null;
	}

	public static String getEmailServer() {

		return "SiteConfigEmailServer";
	}

	public static String getEmailProtocol() {
		// TODO Auto-generated method stub
		return "SiteConfigEmailProtocol";
	}

	public static Object getEmailPort() {
		return -1;
	}

	//	public static String getLocaleLanguage() {
	//		Preferences userPrefs = AppSetup.getPreferences();
	//
	//		return userPrefs.get("Lang", "en");
	//	}
	//
	//	public static String getLocaleCountry() {
	//		Preferences userPrefs = AppSetup.getPreferences();
	//
	//		return userPrefs.get("Ctry", "US");
	//	}
}
