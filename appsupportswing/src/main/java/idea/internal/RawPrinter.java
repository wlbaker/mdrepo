/*
 * Created on Aug 13, 2005
 *
 */
package idea.internal;

import java.io.InputStream;

import javax.print.Doc;
import javax.print.DocFlavor;
import javax.print.DocPrintJob;
import javax.print.PrintException;
import javax.print.PrintService;
import javax.print.PrintServiceLookup;
import javax.print.ServiceUI;
import javax.print.SimpleDoc;
import javax.print.attribute.Attribute;
import javax.print.attribute.DocAttributeSet;
import javax.print.attribute.HashDocAttributeSet;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.print.attribute.PrintServiceAttributeSet;

/**
 * @author bbaker
 *  
 */
public class RawPrinter {

    public static boolean checkPrinter(String szCheckName) {
        boolean success = false;

        PrintRequestAttributeSet pras = new HashPrintRequestAttributeSet();
        // DocFlavor flavor = DocFlavor.INPUT_STREAM.AUTOSENSE;
        DocFlavor flavor = null;
        PrintService printService[] = PrintServiceLookup.lookupPrintServices(
                flavor, pras);

        PrintService[] services = PrintServiceLookup.lookupPrintServices(null,
                null);
        for (int i = 0; i < services.length; i++) {
            System.out.println(services[i].getName());
            PrintServiceAttributeSet attribs = services[i].getAttributes();
            Attribute[] ar = attribs.toArray();
            for (int j = 0; j < ar.length; j++) {
                Attribute attrib = ar[j];
                System.out.println("  - " + attrib.getName() + "="
                        + attrib.toString());
            }

            if (szCheckName.equals(services[i].getName())) {
                return true;
            }

        }
        
        /*
        //PrintService defaultService = PrintServiceLookup
        //        .lookupDefaultPrintService();
        PrintService defaultService = null;
        PrintService printPrintService = null;

        System.out.println("service len: " + printService.length);
        PrintService service = ServiceUI.printDialog(null, 200, 200,
                printService, defaultService, flavor, pras);

        if (service != null) {

            if (!service.isDocFlavorSupported(flavor)) {
                System.err
                        .println("The printer does not support the appropriate DocFlavor");
            }

            DocPrintJob job = service.createPrintJob();
            //FileInputStream fis = null;
            //try {
            //    fis = new FileInputStream("c:/tmp/hello.txt");
            //} catch (FileNotFoundException e) {
            //    e.printStackTrace();
            // }
            DocAttributeSet das = new HashDocAttributeSet();
            // Doc doc = new SimpleDoc( fis, flavor, das);
            Doc doc = new SimpleDoc("hello world!\n", flavor, das);

            try {
                job.print(doc, pras);
            } catch (PrintException e1) {
                e1.printStackTrace();
            }
        }
        */

        return success;
    }

    public static void sendStream(String printerName, InputStream is) throws PrintException {

        PrintRequestAttributeSet pras = new HashPrintRequestAttributeSet();
        // DocFlavor flavor = DocFlavor.INPUT_STREAM.AUTOSENSE;
        DocFlavor flavor = null;
        PrintService printService[] = PrintServiceLookup.lookupPrintServices(
                flavor, pras);

        PrintService[] services = PrintServiceLookup.lookupPrintServices(null,
                null);

        //PrintService defaultService = PrintServiceLookup
        //        .lookupDefaultPrintService();
        PrintService defaultService = null;
        PrintService service = null;
        
        if (printerName == null) {
            service = ServiceUI.printDialog(null, 200, 200, printService,
                    defaultService, flavor, pras);
        } else {
            for (int i = 0; (service == null) && (i < services.length); i++) {
                if (printerName.equals(services[i].getName())) {
                    service = services[i];
                }
            }
        }

        sendStream( service, is );

        return;
    }

	public static void sendStream(PrintService service, InputStream is) throws PrintException {
        if (service != null) {

            PrintRequestAttributeSet pras = new HashPrintRequestAttributeSet();
            DocFlavor flavor = DocFlavor.INPUT_STREAM.AUTOSENSE;
            
            if (!service.isDocFlavorSupported(flavor)) {
                System.err.println( "The printer does not support the appropriate DocFlavor");
            }

            DocPrintJob job = service.createPrintJob();
            
            //FileInputStream fis = null;
            //try {
            //    fis = new FileInputStream("c:/tmp/hello.txt");
            //} catch (FileNotFoundException e) {
            //    e.printStackTrace();
            // }
            DocAttributeSet das = new HashDocAttributeSet();
            // Doc doc = new SimpleDoc( fis, flavor, das);
            Doc doc = new SimpleDoc( is, flavor, das);

            job.print(doc, pras);
        }
	}
}