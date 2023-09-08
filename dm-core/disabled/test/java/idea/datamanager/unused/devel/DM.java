package idea.datamanager.unused.devel;


import icuInterface.message.AbstractBlock;
import icuInterface.message.NumericBlock;
import idea.conf.DeviceConfiguration;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;
import idea.persistmanager.sql.JpaUtil;

import java.io.File;
import java.io.IOException;

import org.apache.commons.cli.BasicParser;
import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;

import idea.schema.rp.RpSubject;

public class DM {

	static DeviceConfiguration conf;

	public static void main(String[] args) {
		
	       try {
	            Options opt = new Options();

	            opt.addOption("h", false, "Print help for this application");
	            opt.addOption("c", "compute", false, "Compute a specific metric.");
	            opt.addOption("l", "list", false, "List devices.");
	            opt.addOption("a", "ascii", false, "Dump ASCII data from a specific device.");
	            opt.addOption("m", "merge", true, "Merge with data from the input file.");
	            opt.addOption("i", "in", true, "Input data file.  If not specified, use the DMFILE environment variable.");
	            opt.addOption("o", "out", true, "Output data file.  If not specified, the input file will be used.");

	            BasicParser parser = new BasicParser();
	            CommandLine cl = parser.parse(opt, args);

	            if ( cl.hasOption('h') ) {
	                HelpFormatter f = new HelpFormatter();
	                f.printHelp("OptionsTip", opt);
	            }
	            else {
	                System.out.println(cl.getOptionValue("o"));
	                System.out.println(cl.getOptionValue("i"));
	            }
	        }
	        catch (ParseException e) {
	            e.printStackTrace();
	        }

		try {
			File fin = new File("c:/tmp/0000.h5");
			
			 PiSubjectImporter importer = PiImporterUtil.getImporterFromFile(fin);
			
			// DreWorkstationExporter exporter = new DreWorkstationExporter("c:/tmp", "out0", null);
			String url1 = "jdbc:mysql://143.83.220.225/idea?zeroDateTimeBehavior=convertToNull";
			String url2 = "jdbc:oracle:thin:@143.83.220.225:1521:C3EDEVL";
			
			// JpaUtil.setUrl(url1, "dss_user", "3611d55u53r");
			Class.forName("oracle.jdbc.driver.OracleDriver");
			JpaUtil.setUrl(url2, "bbaker", "PW0rd4bb");
			
			SQLExporter exporter = new SQLExporter(null, null);

			dump( importer, exporter, args);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


	public static void dump(PiSubjectImporter importer, PiSubjectExporter exporter, String[] args) throws IOException {


		importer.connect();

		  RpSubject header = importer.getSubjectInfo();
		exporter.setHeader( header );

		exporter.connect();

		PersistentItem block;
		while ((block = (PersistentItem) importer.next()) != null) {
			if (block instanceof PersistentItem) {
				PersistentItem vdb = (PersistentItem) block;
				StreamID sid = StreamID.fromCode(vdb.getStreamID());
				exporter.streamEvent(0, importer, sid, vdb);
			} else {
				System.out.println("ignoring: " + block);
			}
			break;
		}

		exporter.disconnect();
		
		importer.disconnect();
	}

}
