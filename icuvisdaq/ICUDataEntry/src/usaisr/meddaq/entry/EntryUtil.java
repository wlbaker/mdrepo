package idea.meddaq.entry;

import icuInterface.message.AbstractItem;
import icuInterface.message.NumericBlock;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Date;
import java.util.LinkedList;
import java.util.Set;
import java.util.TreeSet;

import javax.sound.sampled.LineUnavailableException;

import lombok.extern.slf4j.Slf4j;

import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellStyle;
import org.apache.poi.ss.usermodel.CreationHelper;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import idea.ToneUtil;

import com.sun.speech.freetts.Voice;
import com.sun.speech.freetts.VoiceManager;

@Slf4j
public class EntryUtil {

	private static final int TP_NAME_COL = 0;
	private static final int TP_DATE_COL = 1;
	private static final int TP_OFFSET_COL = 2;
	private static final int DEV_COL = 0;
	private static final int LOC_COL = 1;
	private static final int LOC2_COL = 2;
	private static final int FLAGS_COL = 3;
	private static final int VAL_COL = 4;
	
	private static int PROMPT_COL = 3;
	private static int START_ROW = 1;

	public static EntryModel loadEntrySheets(File file) throws IOException {

		Workbook wb = loadWorkbook( file );
		if( wb == null ) {
			return null;
		}
		return loadEntrySheets(wb);
	}

	public static Workbook loadWorkbook(File file) throws IOException  {
		if( file.exists() == false ) {
			return null;
		}
		FileInputStream in = new FileInputStream(file);

		Workbook wb;
		if (file.getName().endsWith("xlsx")) {
			wb = new XSSFWorkbook(in);
		} else {
			wb = new HSSFWorkbook(in);
		}

		in.close();
		return wb;
	}

	public static EntryModel loadEntrySheets(Workbook wb) throws IOException {
		LinkedList<EntrySheet> esheets = new LinkedList<EntrySheet>();
		LinkedList<ExecutableAction> actions = new LinkedList<ExecutableAction>();
		LinkedList<EntryTimePoint> timepoints = new LinkedList<EntryTimePoint>();

		for (int i = 0; i < wb.getNumberOfSheets(); i++) {
			Sheet sheet = wb.getSheetAt(i);
			String name = sheet.getSheetName();
			if ("Timepoints".equals(name)) {
				// load timepoint descriptions
				loadTimepointItems(sheet, timepoints);
				continue;
			}
			if ("Settings".equals(name)) {
				// load timepoint descriptions
				loadSettings(sheet, actions);
				continue;
			}
			if ("Actions".equals(name)) {
				// load timepoint descriptions
				loadExecutableActions(sheet, actions);
				continue;
			}

			LinkedList<EntryItem> items = new LinkedList<EntryItem>();
			LinkedList<String> item_timepoints = new LinkedList<String>();

			loadEntryItems(sheet, items, item_timepoints);
			EntrySheet esheet = new EntrySheet(name, items, item_timepoints);
			esheets.add(esheet);
		}

		EntryModel model = new EntryModel(timepoints, actions, esheets);
		return model;
	}

	private static void loadSettings(Sheet sheet, LinkedList<ExecutableAction> actions) {
		int rows = sheet.getLastRowNum() + 1;

		for (int r = 0; r < rows; r++) {
			Row row = sheet.getRow(r);
			String varName = getStringCol(row, 0);
			if (varName == null || varName.length() == 0)
				continue;
			switch (varName) {
			case "PROMPT_COL":
				PROMPT_COL = getIntCol(row, 1);
				break;
			case "START_ROW":
				START_ROW = getIntCol(row, 1);
				break;
			default:
				System.err.println("unknown setting: " + varName);
			}
		}

	}

	private static void loadTimepointItems(Sheet sheet, LinkedList<EntryTimePoint> timepoints) {
		int rows = sheet.getLastRowNum();

//		LinkedList<String> actionNamesList = new LinkedList<String>();
//
//		Row row0 = sheet.getRow(0);
//		for (int col = 2; col < row0.getLastCellNum(); col++) {
//			String actionName = getStringCol(row0, col);
//			if (actionName == null || actionName.length() == 0)
//				break;
//			actionNamesList.add(actionName);
//		}
//
//		String[] actionNames = new String[actionNamesList.size()];
//		actionNames = actionNamesList.toArray(actionNames);

		// load variables
		for (int idx = 1; idx < rows; idx++) {
			Row row = sheet.getRow(idx);

			String name = getStringCol(row, TP_NAME_COL );
			// search through at least the first five rows
			if ((name == null || name.length() == 0) && idx < 5) {
				continue;
			}
			if (name == null)
				break;

			String time_offset = getStringCol(row, TP_OFFSET_COL);
			Date dt = getDateCol( row, TP_DATE_COL);

//			int[] actionTimes = new int[actionNames.length];
//			for (int col = 0; col < actionTimes.length; col++) {
//				String t = getStringCol(row, col + 2);
//				actionTimes[col] = getTpOffsetInMinutes(t);
//			}
//
//			int mins = EntryUtil.getTpOffsetInMinutes(time_offset);
//			EntryTimePoint tp = new EntryTimePoint(name, mins, actionNames, actionTimes);
			EntryTimePoint tp = new EntryTimePoint(name, dt);
			timepoints.add(tp);
		}

	}

	public static void loadExecutableActions(Sheet sheet, LinkedList<ExecutableAction> actions) throws IOException {

		int rows = sheet.getLastRowNum();

		// load variables
		for (int idx = 1; idx <= rows; idx++) {
			Row row = sheet.getRow(idx);
			if (row == null)
				continue;

			String eventName = getStringCol(row, 0);
			String cmd = getStringCol(row, 1);
			String arg1 = getStringCol(row, 2);
			String arg2 = getStringCol(row, 3);

			ExecutableAction action = new ExecutableAction(eventName, cmd, arg1, arg2);
			actions.add(action);

			log.info("adding action: {} - {}", eventName, cmd);

		}
	}

	public static void loadEntryItems(Sheet sheet, LinkedList<EntryItem> items, LinkedList<String> item_timepoints)
			throws IOException {

		Set<String> s = new TreeSet<String>();
		
		int rows = sheet.getLastRowNum();
		// load variables
		for (int idx = START_ROW; idx < rows; idx++) {
			Row row = sheet.getRow(idx);

			String dev = getStringCol(row, DEV_COL );
			if (dev == null && idx < 5) {
				continue;
			}
			if (dev == null)
				break;

			if ("skip".compareToIgnoreCase(dev) == 0) {
				continue;
			}

			String loc = getStringCol(row, LOC_COL );
			String loc2 = getStringCol(row, LOC2_COL );
			String flags = getStringCol(row, FLAGS_COL);
			String validation = getStringCol(row, VAL_COL);
			String prompt = getStringCol(row, PROMPT_COL);

			if (loc == null) {
				log.error("NULL LOC row={} DEV={}", idx, dev);
				continue;
			}
			if (loc.endsWith(".")) {
				loc = loc.replace(".", "");
			}
			
			if( loc2 == null ) {
				loc2 = loc; 
			}
			
			if( s.contains( loc2 ) ) {
				log.warn("ignoring existing item: {}/{}", dev, loc );
				continue;
			}
			s.add( loc2 );

			EntryItem p = new EntryItem(prompt, dev, loc, loc2, validation);
			double scale = 1;
			if (flags != null && flags.length() > 0) {
				String[] ar = flags.split(":");
				for (String flag : ar) {
					if( flag.startsWith("scale")) {
						String [] ar2 = flag.split("=");
						flag = ar2[0];
						scale = Double.parseDouble(ar2[1]);
					}
					switch (flag) {
					case "scale":
						p.setScale(scale);
						break;
					case "vis":
						p.setVisible(true);
						break;
					case "novis":
						p.setVisible(false);
						break;
					case "date":
						p.setValueClass(java.util.Date.class);
						break;
					case "string":
						p.setValueClass(String.class);
						break;
					case "manual":
						p.setManual(true);
						break;
					default:
						log.error("unrecognized entry flag: {}", flag);
					}
				}
			}
			items.add(p);
		}

		// load timepoints
		Row row = sheet.getRow(2);
		for (int col = 4; col <= row.getLastCellNum(); col++) {
			String name = getStringCol(row, col);
			if (name != null) {
				item_timepoints.addLast(name);
			}
		}

		return;
	}

	public static boolean checkCapabilities() {
		// TODO Auto-generated method stub

		return true;
	}

	private static Integer getIntCol(Row row, int pos) {
		Integer val = null;

		Cell cell = row.getCell(pos);
		if (cell != null) {
			switch (cell.getCellType()) {
			case Cell.CELL_TYPE_NUMERIC:
				val = (int) cell.getNumericCellValue();
				break;
			case Cell.CELL_TYPE_STRING:
				val = new Integer(cell.getStringCellValue());
				break;
			}
		}

		return val;
	}

	private static Date getDateCol(Row row, int pos) {
		Date val = null;

		Cell cell = row.getCell(pos);
		if (cell != null) {
			switch (cell.getCellType()) {
			case Cell.CELL_TYPE_NUMERIC:
				val = cell.getDateCellValue();
				break;
			}
		}

		return val;
	}

	private static String getStringCol(Row row, int pos) {
		String val = null;

		Cell cell = row.getCell(pos);
		if (cell != null) {
			switch (cell.getCellType()) {
			case Cell.CELL_TYPE_NUMERIC:
				val = "" + ((int) cell.getNumericCellValue()); // locs can be
																// ints
				break;
			case Cell.CELL_TYPE_STRING:
				val = cell.getStringCellValue();
				break;
			}
		}

		if (val != null) {
			val = val.trim();
			if (val.length() == 0) {
				val = null;
			}
		}

		return val;
	}

	public static int getTpOffsetInMinutes(String tpOffset) {
		double mins = 0;

		if (tpOffset != null) {
			tpOffset = tpOffset.toLowerCase();
			int len = tpOffset.length();
			if (tpOffset.endsWith("hr") && len > 2) {
				String amount = tpOffset.substring(0, len - 2);
				mins = 60 * Double.parseDouble(amount.trim());
			} else if (tpOffset.endsWith("min")) {
				String amount = tpOffset.substring(0, len - 3);
				mins = Double.parseDouble(amount.trim());
			} else {
				mins = Double.parseDouble(tpOffset);
			}
		}

		return (int) mins;
	}

	public static void execute(ExecutableAction exe) {

		String cmd = exe.getCmd();
		if ("tts".equals(cmd)) {
			executeTTS(exe.getArg1(), exe.getArg2());
		} else if ("flash".equals(cmd)) {
			try {
				executeFLASH(exe.getArg1(), exe.getArg2());
			} catch (LineUnavailableException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} else if ("lock".equals(cmd)) {
			executeLOCK(exe.getArg1(), exe.getArg2());
		} else {
			System.err.println("UNKNOWN execute action: " + exe.getName() + "/" + exe.getCmd());
		}

		return;
	}

	private static void executeTTS(String arg1, String arg2) {
		System.err.println("EXECUTING TTS: " + arg1 + "/" + arg2);

		String voiceName = "kevin16";
		VoiceManager voiceManager = VoiceManager.getInstance();
		Voice helloVoice = voiceManager.getVoice(voiceName);

		if (helloVoice == null) {
			System.err.println("Cannot find a voice named " + voiceName + ".  Please specify a different voice.");
			return;
		}

		/*
		 * Allocates the resources for the voice.
		 */
		helloVoice.allocate();

		/*
		 * Synthesize speech.
		 */
		helloVoice.speak(arg2);

		/*
		 * Clean up and leave.
		 */
		helloVoice.deallocate();
	}

	private static void executeFLASH(String arg1, String arg2) throws LineUnavailableException {

		ToneUtil.playTone(2000, 4000, 10);

	}

	private static void executeLOCK(String arg1, String arg2) {
		System.err.println("EXECUTING LOCK: " + arg1 + "/" + arg2);
	}

	public static void updateWorkbook(Workbook wb, String sheetName, EntryTimePoint timepoint, NumericBlock block) {
		
		CreationHelper createHelper = wb.getCreationHelper();

		CellStyle dateStyle = wb.createCellStyle();
		dateStyle.setDataFormat(createHelper.createDataFormat().getFormat("m/d/yy HH:mm:ss"));
		dateStyle.setFillForegroundColor(HSSFColor.LIGHT_ORANGE.index);
		dateStyle.setFillPattern(CellStyle.SOLID_FOREGROUND);

		Sheet tp_sheet = wb.getSheet("Timepoints");
		Sheet vitals_sheet = wb.getSheet(sheetName);
		
		if( tp_sheet != null ) {
			AbstractItem tp = block.getItem("TP"); 
			String tp_name = (String) tp.getValue();
			
			if( tp_name == null ) {
				log.warn("No TP name to update");
				return;
			}
			
			long tm = block.getTime();
			Date dt = new Date(tm);
			
			timepoint.setTpDate( dt );  // save to local model
			updateTimepoints( tp_sheet, tp_name, dt, dateStyle );
		}
		updateVitals( vitals_sheet, block, dateStyle );
	}
	
	private static void updateTimepoints(Sheet sheet,String tp_name, Date dt, CellStyle dateStyle) {
		int TOP_ROW = 1;
		boolean updated = false;

		
		for (int row = TOP_ROW; row < sheet.getLastRowNum(); row++) {
			Row r = sheet.getRow(row);

			String name = getStringCol(r, TP_NAME_COL );
			// search through at least the first five rows
			if ((name == null || name.length() == 0) && row < 5) {
				continue;
			}
			if (name == null)
				break;

			if( tp_name.equals(name)) {
				Cell cell = r.getCell( TP_DATE_COL );
				if( cell == null ) {
					cell = r.createCell( TP_DATE_COL );
				}
				cell.setCellValue( dt );
				cell.setCellStyle( dateStyle );
				updated = true;
				break;
			}
		}
		
		if( !updated ) {
			log.error("COULD NOT FIND TIMEPOINT: {}", tp_name );
			Row r = sheet.createRow( sheet.getLastRowNum() );
			Cell cell = r.createCell( TP_NAME_COL );
			cell.setCellValue( tp_name );
			cell = r.createCell( TP_DATE_COL );
			cell.setCellValue(dt);
			cell.setCellStyle( dateStyle );
		}

	}
	
	
	private static void updateVitals(Sheet sheet, NumericBlock block, CellStyle dateStyle) {
		int TOP_ROW = 1;

		Row r = sheet.getRow(TOP_ROW); // this row cannot be null!
		int col;
		for( col = 0; col < r.getLastCellNum() ; col++ ) {
			Cell cell = r.getCell(col);
			if (cell.getCellType() == Cell.CELL_TYPE_STRING) {
				String txt = cell.getStringCellValue();
				System.out.println("[" + col + "]" + txt );
			}
			if( cell.getCellType() == Cell.CELL_TYPE_NUMERIC) {
				System.out.println("[" + col + "]" + cell.getNumericCellValue() );
			}
		}
		log.debug("last col={}", col );
		
		for (col = 6; col < r.getLastCellNum(); col++) {
			
			Cell cell = r.getCell(col);
			if (cell == null)
				break;
			if (cell.getCellType() == Cell.CELL_TYPE_BLANK) {
				break;
			}
			if (cell.getCellType() == Cell.CELL_TYPE_STRING) {
				String txt = cell.getStringCellValue();
				if (txt == null || txt.trim().length() == 0) {
					break;
				}
			}
			// else, assume cell is already filled
		}

		for (int row = TOP_ROW; row < sheet.getLastRowNum(); row++) {
			r = sheet.getRow(row);
			if (r == null) {
				continue;
			}
			Cell devCell = r.getCell(0);
			String src_loc = getStringCol(r, LOC_COL);
			String dest_loc = getStringCol(r, LOC2_COL);
			String flags = getStringCol(r, FLAGS_COL );
			
			if( dest_loc == null ) {
				dest_loc = src_loc;
			}
			if (dest_loc == null || dest_loc.length() < 1) {
				continue; // ignore no-value cells
			}
			boolean is_date = false;
			if( flags != null ) {
				is_date = flags.indexOf("date") >= 0;
			}

			AbstractItem ai = null;
			if (dest_loc != null) {
				ai = block.getItem(dest_loc);
			}
			if (ai != null) {
				Object val = ai.getScaledValue();
				if (val == null) {
					continue;
				}
				Cell cell = r.getCell(col);
				if (cell == null) {
					cell = r.createCell(col);
					System.out.println( "created cell [" + row + "," + col + "]");
				} else {
					log.debug( "got cell col: {} overwrite {}", col, val);
				}
				
				if( is_date ) {
					cell.setCellStyle( dateStyle );
					if( val instanceof Long ) {
						val = new Date( (Long)val );
					} else if( val instanceof Double ) {
						val = new Date( ((Double)val).longValue() );
					}
				}
				
				if (val instanceof String) {
					cell.setCellValue((String) val);
				} else if (val instanceof Number) {
					cell.setCellValue(((Number) val).doubleValue());
				} else if (val instanceof Date) {
					cell.setCellValue((Date) val);
				} else {
					log.error("Could not save value for unrecognized type: {}", val.getClass());
				}
				
			}
		}
	}
}
