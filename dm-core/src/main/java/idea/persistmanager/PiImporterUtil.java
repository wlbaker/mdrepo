package idea.persistmanager;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

import idea.persistence.PiSubjectExporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.sql.SQLExporter;
import idea.persistmanager.sql.SQLImporter;
import lombok.extern.slf4j.Slf4j;
import idea.datamanager.ExcelExporter;
import idea.datamanager.ExcelImporter;

@Slf4j
public class PiImporterUtil {

	public static final int HDF5_FLAG = 1;
	public static final int DAT_FLAG = 2;
	public static final int VTL_FLAG = 4;
	public static final int ANY_FLAG = 0xffff;

	public static PiSubjectImporter getWritableImporterFromFile(File file) throws IOException {
		return getImporter(file, ANY_FLAG, false);
	}

	public static PiSubjectImporter getImporterFromFile(File file) {
		return getImporter(file, ANY_FLAG, true);
	}

	public static PiSubjectImporter getImporterFromFile(File file, int flags) {
		return getImporter(file, flags, true);
	}

	private static PiSubjectImporter getImporter(File file, int flags, boolean readonly) {
		String name = file.getName().toLowerCase();
		String line = null;

		if (name.endsWith("xls") || name.endsWith("xlsx")) {
			line = "xlsx";
		} else if (name.endsWith("ses") || name.endsWith("sesBAK")) {
			line = "zHDF5";
		} else if (name.endsWith("h5")) {
			line = "zHDF5";
		} else if (name.endsWith("db")) {
			line = "SQLITE";
		} else if (name.endsWith("stp")) {
			line = "Dynamic";
		} else if (file.isDirectory()) {
			// is there a DBF in the directory?
			line = "MULTI"; // composite HDF
			for( File f : file.listFiles() ) {
				String sub_name = f.getName().toLowerCase();
//				if( sub_name.endsWith("vtl")) {
//					line = "MULTI";
//					break;
//				} else 
				if( sub_name.endsWith("dbf")) {
					line = "dbf";
					break;
				}
			}
		} else {
			FileReader r = null;
			try {
				r = new FileReader(file);
				BufferedReader reader = new BufferedReader(r);
				line = reader.readLine();
				reader.close();
			} catch (Exception e) {
				// line is null
			} finally {
				if (r != null) {
					try {
						r.close();
					} catch (IOException e) {
						// ignore
					}
				}
			}
		}

		PiSubjectImporter importer = null;
		if (line == null ) {
			log.warn("Could not open file/dir to analyze: {}", file );
		} else if (line.startsWith("Dynamic")) {
			importer = new PiDreImporter(file, null);
		} else if (line.endsWith("dbf")) {
			importer = new DBFImporter(file);
		} else if ("MULTI".equals(line)) {
			importer = new PiCompositeImporter(file, flags);  // reader will be readonly
			if( !readonly ) {
				log.warn("Composite importer is READONLY");
			}
		} else if ("SQLITE".equals(line)) {
			String path = file.getPath().replace("\\", "/");
			importer = new SQLImporter("jdbc:sqlite:" + path);
		} else if (line.length() >= 3 && "HDF".equals(line.substring(1, 4))) {
			importer = new PiHdf5Importer(file, readonly);
//		} else if (line.startsWith("PK")) {
//			importer = new ExcelImporter(file);
		} else if (line.startsWith("xls")) {
			importer = new ExcelImporter(file);
		} else {
			log.error("NO SUCH IMPORTER: ", line);
		}

		return importer;
	}

	private static PiSubjectExporter getExporter(File file, int flags) {
		String name = file.getName().toLowerCase();
		String line = null;

		if (name.endsWith("xls") || name.endsWith("xlsx")) {
			line = "xlsx";
		} else if (name.endsWith("ses") || name.endsWith("sesBAK")) {
			line = "zHDF5";
		} else if (name.endsWith("h5")) {
			line = "zHDF5";
		} else if (name.endsWith("db")) {
			line = "SQLITE";
		} else if (name.endsWith("stp")) {
			line = "Dynamic";
		} else if (file.isDirectory()) {
			// is there a DBF in the directory?
			line = "MULTI"; // composite HDF
			for( File f : file.listFiles() ) {
				String sub_name = f.getName().toLowerCase();
//				if( sub_name.endsWith("vtl")) {
//					line = "MULTI";
//					break;
//				} else 
				if( sub_name.endsWith("dbf")) {
					line = "dbf";
					break;
				}
			}
		} else {
			line = "dat";
		}
		
		PiSubjectExporter exporter = null;
		if (line == null ) {
			log.warn("Could not open file/dir to analyze: {}", file );
		} else if (line.equals("dat") ) {
			exporter = new PiDreExporter(null, file);
		//} else if (line.endsWith("dbf")) {
		//	importer = new DBFExporter(file);
		//} else if ("MULTI".equals(line)) {
		//	importer = new PiCompositeImporter(file, flags);  // reader will be readonly
		//	if( !readonly ) {
		//		log.warn("Composite importer is READONLY");
		//	}
		} else if ("SQLITE".equals(line)) {
			String path = file.getPath().replace("\\", "/");
			exporter = new SQLExporter("jdbc:sqlite:" + path, null);
		} else if (line.length() >= 3 && "HDF".equals(line.substring(1, 4))) {
			exporter = new PiHdf5Exporter(null, file.getPath(), false);
//		} else if (line.startsWith("PK")) {
//			importer = new ExcelImporter(file);
		} else if (line.startsWith("xls")) {
			exporter = new ExcelExporter(file, null, true);
		} else {
			log.error("NO SUCH IMPORTER: ", line);
		}

		return exporter;
	}
}
