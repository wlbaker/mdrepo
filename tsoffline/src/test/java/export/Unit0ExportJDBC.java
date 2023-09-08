package export;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;

import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;
import idea.tsoffline.export.ExportUtil;

public class Unit0ExportJDBC {
	/*
	 * example usage and test code
	 */
	public static void main(String[] args) throws IOException {

		ExportUtil util = new ExportUtil();

		util.setOutput("XLS", "c:/tmp/t0.xlsx");
		util.setOutput("JDBC", "jdbc:sqlite:/c:/tmp/file${SUBJECT}.db");

		util.setClipStart(null);
		util.setClipEnd(null);

		util.setInterval(60 * 1000);

		// File f = new File("L:/RESEARCH/PROTOCOLS/PROTOCOL NOTEBOOK/PIDCOKE
		// WORK/Pidcoke - Clinical OR Bleeding Study
		// H-11-058/DATA/IDEA/subject_data/H48");
		File f = new File("C:/tmp/H48");

		PiSubjectImporter importer = PiImporterUtil.getImporterFromFile(f);
		importer.connect();
		HashMap<String, List> dev_signals = null;

		util.setImporter(importer);
		util.setSignals(dev_signals);

		util.run();

		importer.disconnect();
	}


}
