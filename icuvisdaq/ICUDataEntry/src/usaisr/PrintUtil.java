package idea;

import java.io.File;
import java.net.URL;
import java.sql.Connection;
import java.util.HashMap;

import javax.print.PrintService;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.HashPrintServiceAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.print.attribute.PrintServiceAttributeSet;
import javax.print.attribute.standard.OrientationRequested;

import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRExporterParameter;
import net.sf.jasperreports.engine.JasperFillManager;
import net.sf.jasperreports.engine.JasperPrint;
import net.sf.jasperreports.engine.JasperReport;
import net.sf.jasperreports.engine.export.JRPrintServiceExporterParameter;
import net.sf.jasperreports.engine.util.JRLoader;
import idea.jasper.DDD;
import idea.jasper.ideaPrintServiceExporter;


public class PrintUtil {
	public static void print( PrintService service, String report ) throws JRException {
		File bd = new File( report ); // "accounting/payable");
		HashMap<String, Object> map = new HashMap<String, Object>();
		map.put("BaseDir", bd);
		map.put("report", report ); // "accounting/payable/VoucherLabel");
		map.put("title", "Voucher Label");
		map.put("IdNumber", "999-55-999999");
		// map.put("Company", "Burger Electronics");
		// map.put("Amount", new BigDecimal(0.07) );

		// map.put("REPORT_CONNECTION", JpaUtil.getReportConnection());
		JasperReport jasperReport = (JasperReport) JRLoader.loadObjectFromFile(report);
		
		print( service, map, jasperReport );
	}
	
	public static void print( PrintService service, URL url ) throws JRException {
		HashMap<String, Object> map = new HashMap<String, Object>();
		print( service, map, url );
	}
	
	public static void print(PrintService service, HashMap<String, Object> map, URL url) throws JRException {
		// map.put("BaseDir", bd);
		// map.put("report", report ); // "accounting/payable/VoucherLabel");
		JasperReport jasperReport = (JasperReport) JRLoader.loadObject(url);
		print( service, map, jasperReport );
	}
	
	public static void print( PrintService service, HashMap<String,Object> map, JasperReport jasperReport ) throws JRException {

		JasperPrint jrprint = JasperFillManager.fillReport(jasperReport, map, (Connection) map
				.get("REPORT_CONNECTION"));


		PrintRequestAttributeSet printRequestAttributeSet = new HashPrintRequestAttributeSet();
		// printRequestAttributeSet.add(MediaSizeName.NA_LETTER);
		// printRequestAttributeSet.add(MediaSize.NA_LETTER);
		printRequestAttributeSet.add( OrientationRequested.LANDSCAPE);
		
//		MediaPrintableArea area = new MediaPrintableArea( 0.12f, 0.12f, 1.4f, 3.1f, MediaPrintableArea.INCH );
//		printRequestAttributeSet.add(area);


		PrintServiceAttributeSet printServiceAttributeSet = new HashPrintServiceAttributeSet();
		// printServiceAttributeSet.add(new PrinterName("HP LaserJet 4P",
		// null));

		ideaPrintServiceExporter exporter = new ideaPrintServiceExporter();

		if (service != null) {
			exporter.setParameter(JRPrintServiceExporterParameter.PRINT_SERVICE, service);
			exporter.setParameter(JRPrintServiceExporterParameter.DISPLAY_PRINT_DIALOG, Boolean.FALSE);
		} else {
			exporter.setParameter(JRPrintServiceExporterParameter.DISPLAY_PRINT_DIALOG, Boolean.TRUE);
		}
		exporter.setParameter(JRExporterParameter.JASPER_PRINT, jrprint);
		exporter.setParameter(JRPrintServiceExporterParameter.PRINT_REQUEST_ATTRIBUTE_SET, printRequestAttributeSet);
		exporter.setParameter(JRPrintServiceExporterParameter.PRINT_SERVICE_ATTRIBUTE_SET, printServiceAttributeSet);
		exporter.setParameter(JRPrintServiceExporterParameter.DISPLAY_PAGE_DIALOG, Boolean.FALSE );

		exporter.exportReport();

	}



	public static JasperReport loadReport(String report) throws JRException {
		return (JasperReport) JRLoader.loadObjectFromFile(report);
	}

	public static String findReportFile(HashMap map, String report) {
		// String title = (String) map.get("title");

		if( report == null ) {
			report = (String)map.get("report");
		} else {
			map.put("report", report);
		}
		
		String root = DDD.getJasperRoot(false);
		File f = new File(root + report + ".jasper");
		System.out.println("looking for: " + f.getAbsolutePath());
		if (!f.canRead()) {
			root = DDD.getJasperRoot(true);
			f = new File(root + report + ".jasper");

			System.out.println("looking for: " + f.getAbsolutePath());
			if (!f.canRead()) {
				f = null;
			}
		}

		if (f != null) {
			report = f.getAbsolutePath();
			map.put("BaseDir", f.getParentFile());
			map.put("PFT_LINKPFX", "app://report/");
		} else {
			report = null;
		}


		String logoName = ConfigurationInfo.getLogoName();
		if (logoName != null) {
			map.put("PMC_LOGO_NAME", logoName);
		}

//		String localeLanguage = ConfigurationInfo.getLocaleLanguage();
//		String localeCountry = ConfigurationInfo.getLocaleCountry();
//		if (localeLanguage != null) {
//			Locale locale = null;
//			if (localeCountry == null) {
//				locale = new Locale(localeLanguage);
//			} else {
//				locale = new Locale(localeLanguage, localeCountry);
//			}
//			map.put("REPORT_LOCALE", locale);
//		}

		System.out.println("report found: " + report);

		return report;
	}


}
