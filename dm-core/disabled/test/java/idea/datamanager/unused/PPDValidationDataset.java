package idea.datamanager.unused;

import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class PPDValidationDataset {
	private static SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	public static void generate_drager_evita() throws IOException, InterruptedException, ParseException {

		File root = new File("Y:/A-12-004 Conscious sheep/data/922/");
		String[] records = { "2012_08_29_14.33.03/0000.h5" };
		// String[] records = {"562/2012_01_17_09.51.38/0000.h5"};
		// String[] records = {"Pig194_2011_10_28_12.24.39"};
		// String[] records = {"Pig194_2011_10_30_15.15.24"};
		// String[] records = {"Pig562_2012_01_19_15.57.29"};

		Hdf5Upgrade upgrader = new Hdf5Upgrade();
		for (String record : records) {

			File inputFile = new File(root, record);

			if (!inputFile.exists()) {
				System.err.println("input file does not exist: " + inputFile);
			}

			System.out.println("Processing record:" + record);

			File outputDir = new File("c:/tmp/val_data/parts/delta_evita");
			outputDir.mkdirs();

			Calendar cal = Calendar.getInstance();

			Date endDate = sdf.parse("2012-01-04 14:00:00");
			cal.setTime(endDate);
			cal.add(Calendar.DATE, -14);
			Date startDate = cal.getTime();

			System.out.println("start date: " + sdf.format(startDate));
			System.out.println("  end date: " + sdf.format(endDate));

			try {
				String[] groups = { "Drager", "Drager_0", "Evita 4_0", "Evita_4", "Evita 4", "Vigileo", "Bard_Urimeter", "Plum-A" };
				upgrader.rebuildFile(inputFile, outputDir, groups, startDate, endDate);
				// upgrader.rebaseTimestamp(outputFile, "Bard_Urimeter_0", startDate );
			} catch (Exception e) {
				e.printStackTrace();
			}

			System.out.println("done w drager");
		}

	}

	public static void generate_criticore_epump() throws IOException, InterruptedException, ParseException {

		File root = new File("C:/opt/repository/test-kangabard/1111111");
		String[] records = { "2012_08_30_10.00.17/0000.h5" };

		Hdf5Upgrade upgrader = new Hdf5Upgrade();
		for (String record : records) {

			File inputFile = new File(root, record);

			if (!inputFile.exists()) {
				System.err.println("input file does not exist: " + inputFile);
			}

			System.out.println("Processing record:" + record);

			File outputDir = new File("c:/tmp/val_data/parts/epump_criticore");
			outputDir.mkdirs();

			Calendar cal = Calendar.getInstance();

			Date endDate = sdf.parse("2012-01-04 14:00:00");
			cal.setTime(endDate);
			cal.add(Calendar.DATE, -14);
			Date startDate = cal.getTime();

			System.out.println("start date: " + sdf.format(startDate));
			System.out.println("  end date: " + sdf.format(endDate));

			try {
				String[] groups = { "Criticore_0", "ePump_0" };
				upgrader.rebuildFile(inputFile, outputDir, groups, startDate, endDate);
			} catch (Exception e) {
				e.printStackTrace();
			}

		}

	}

	public static void generate_vigilance() throws IOException, InterruptedException, ParseException {

		File root = new File("C:/tmp/val_data/source");
		String[] records = { "vigilance/0000.h5" };

		Hdf5Upgrade upgrader = new Hdf5Upgrade();
		for (String record : records) {

			File inputFile = new File(root, record);

			if (!inputFile.exists()) {
				System.err.println("input file does not exist: " + inputFile);
			}

			System.out.println("Processing record:" + record);

			File outputDir = new File("c:/tmp/val_data/parts/vigilance");
			outputDir.mkdirs();

			Calendar cal = Calendar.getInstance();

			Date endDate = sdf.parse("2012-01-04 14:00:00");
			cal.setTime(endDate);
			cal.add(Calendar.DATE, -14);
			Date startDate = cal.getTime();

			System.out.println("start date: " + sdf.format(startDate));
			System.out.println("  end date: " + sdf.format(endDate));

			try {
				String[] groups = { "Vigilance II_0", "Vigilance+II_0" };
				upgrader.rebuildFile(inputFile, outputDir, groups, startDate, endDate);
			} catch (Exception e) {
				e.printStackTrace();
			}

		}

	}

	public static void generate_pluma() throws IOException, InterruptedException, ParseException {

		File root = new File("C:/tmp/val_data/source/pluma");
		String[] records = { "0000.h5" };

		Hdf5Upgrade upgrader = new Hdf5Upgrade();
		for (String record : records) {

			File inputFile = new File(root, record);

			if (!inputFile.exists()) {
				System.err.println("input file does not exist: " + inputFile);
			}

			System.out.println("Processing record:" + record);

			File outputDir = new File("c:/tmp/val_data/parts/pluma");
			outputDir.mkdirs();

			Calendar cal = Calendar.getInstance();

			Date endDate = sdf.parse("2012-01-04 14:00:00");
			cal.setTime(endDate);
			cal.add(Calendar.DATE, -14);
			Date startDate = cal.getTime();

			System.out.println("start date: " + sdf.format(startDate));
			System.out.println("  end date: " + sdf.format(endDate));

			try {
				String[] groups = { "Plum-A+_0", "Plum-A+" };
				upgrader.rebuildFile(inputFile, outputDir, groups, startDate, endDate);
			} catch (Exception e) {
				e.printStackTrace();
			}

		}

	}
	
	public static void generate_full_from_parts( File inputFile, File outputDir, Date startDate, Date endDate) throws IOException, InterruptedException, ParseException {

		Hdf5Upgrade upgrader = new Hdf5Upgrade();


		System.out.println("start date: " + sdf.format(startDate));
		System.out.println("  end date: " + sdf.format(endDate));

		try {
			String[] groups = null;
			upgrader.rebuildFile(inputFile, outputDir, groups, startDate, endDate);
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	public static void main(String[] args) throws IOException, InterruptedException, ParseException {
		Calendar cal = Calendar.getInstance();

		Date endDate = sdf.parse("2012-01-04 14:00:00");
		cal.setTime(endDate);
		cal.add(Calendar.DATE, -14);
		Date startDate = cal.getTime();

		File partsDir = new File("C:/tmp/val_data/parts");
		
		generate_drager_evita();
		// generate_criticore_epump();
		// generate_vigilance();
		// generate_pluma();
		

		if (!partsDir.exists()) {
			System.err.println("input file does not exist: " + partsDir);
			return;
		}

		File outputJan42012 = new File("c:/tmp/val_data/full");
		outputJan42012.mkdirs();
		
		generate_full_from_parts( partsDir, outputJan42012, startDate, endDate );
		
		//File outputToday = new File("c:/tmp/val_data/today");
		//outputToday.mkdirs();
		
		Date today = new Date();
		cal.setTime( today );
		cal.set( Calendar.HOUR, 0 );
		cal.set( Calendar.MINUTE, 0 );
		cal.set( Calendar.SECOND, 0 );
		cal.set( Calendar.MILLISECOND, 0 );
		cal.add(Calendar.DATE, -3);
		startDate = cal.getTime();
		
		// generate_full_from_parts( partsDir, outputToday, startDate, today );
	}

}
