package idea.datamanager;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import org.apache.poi.hssf.usermodel.HSSFDateUtil;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellStyle;
import org.apache.poi.ss.usermodel.CellType;
import org.apache.poi.ss.usermodel.CreationHelper;
import org.apache.poi.ss.usermodel.FillPatternType;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.streaming.SXSSFWorkbook;
import org.apache.poi.xssf.usermodel.XSSFCellStyle;

import icuInterface.RpUtil;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpSubject;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ExcelExporter implements PiSubjectExporter {

	public final static int SINGLE_SHEET = 1;
	public final static int MULTIPLE_SHEET = 2;

	private final static int MAX_SHEETS = 64;

	private int sheet_mode = MULTIPLE_SHEET;

	Workbook wb;

	private RpSubject header;

	String fqName;
	String seqNo = null;

	private File xlsFile;

	private CellStyle dateStyle;
	private CellStyle dateSepStyle;
	private CellStyle headerStyle;

	private String rootName;

	private long start_time, stop_time; // max 32 sheets
	private long[] last_time = new long[MAX_SHEETS]; // max 32 sheets
	private double[] mss_interval = new double[MAX_SHEETS];

	private boolean show_units;
	private final static RpMetric rel_time_metric = //
			RpUtil.createRpMetric("REL", "TM", "Rel Time", new RpLinearUnit(1.0, 0, "s"), -1);
	private final static RpMetric mrk_no_metric = //
			RpUtil.createRpMetric("MRK #", null, null, new RpLinearUnit(1.0, 0, ""), -1);
	int headerRows;
	private FileOutputStream fos;

	int max_row = -1;
	private Map<String, Row> cachedRow0 = new HashMap<String, Row>();

	public ExcelExporter(File file, RpSubject header, boolean show_units) {
		this.header = header;

		this.xlsFile = file;
		this.show_units = show_units;
		headerRows = (show_units) ? 2 : 1;
	}

	/**
	 * 
	 * Single sheet or multiple sheets. Use a constant:
	 * ExcelExporter.SINGLE_SHEET. Defaults to MULTIPLE_SHEETS.
	 */
	public void setSheetMode(int sheetMode) {
		this.sheet_mode = sheetMode;
	}

	@Override
	public void connect() throws IOException {

		for (int i = 0; i < last_time.length; i++) {
			last_time[i] = 0;
		}

		if (rootName == null) {
			rootName = xlsFile.getName();
		}
		createExcelFile();

		String path = xlsFile.getPath();
		String subject = System.getProperty("SUBJECT");
		if (subject != null) {
			path = path.replace("${SUBJECT}", subject);
		}

		fos = new FileOutputStream(path);

		if (header != null) {
			writeHeaderSheet();
		}
	}

	private void createExcelFile() throws IOException {
		String suffix = "xlsx";
		if (xlsFile != null && xlsFile.getName() != null) {
			String name = xlsFile.getName().toLowerCase();
			if (name.endsWith("xls")) {
				suffix = "xls";
			}
		}

		wb = new SXSSFWorkbook(1000);
		// if ("xls".equals(suffix)) {
		// wb = new HSSFWorkbook();
		// } else {
		// wb = new XSSFWorkbook();
		// }

		CreationHelper createHelper = wb.getCreationHelper();

		dateStyle = wb.createCellStyle();
		dateStyle.setDataFormat(createHelper.createDataFormat().getFormat("m/d/yy HH:mm:ss.000"));
		dateStyle.setFillForegroundColor(HSSFColor.HSSFColorPredefined.LIGHT_ORANGE.getIndex());
		dateStyle.setFillPattern(FillPatternType.SOLID_FOREGROUND);

		dateSepStyle = wb.createCellStyle();
		dateSepStyle.setDataFormat(createHelper.createDataFormat().getFormat("m/d/yy HH:mm:ss.000"));
		dateSepStyle.setFillForegroundColor(HSSFColor.HSSFColorPredefined.LIGHT_BLUE.getIndex());
		dateSepStyle.setFillPattern(FillPatternType.SOLID_FOREGROUND);

		headerStyle = wb.createCellStyle();
		headerStyle.setFillForegroundColor(HSSFColor.HSSFColorPredefined.LIGHT_ORANGE.getIndex());
		headerStyle.setFillPattern(FillPatternType.SOLID_FOREGROUND);

	}

	public void specialFullSequence(String sheetName, String colName) {
		//
		for (int idx = wb.getNumberOfSheets() - 1; idx >= 0; idx--) {
			Sheet sheet = wb.getSheetAt(idx);
			if (sheetName == null) {
				// ignore
			} else if (!sheetName.equals(sheet.getSheetName())) {
				// a sheet name is specified, but it is not the current sheet
				continue;
			}

			Row row0 = sheet.getRow(0);
			if (row0 == null) {
				log.error("No row0: {}", sheetName);
				continue;
			}
			int col_idx = findCol(row0, colName);

			if (col_idx > 0) {
				double seq_no = 0;
				for (int row_idx = 1; row_idx <= sheet.getLastRowNum(); row_idx++) {
					Row row = sheet.getRow(row_idx);
					if (row == null) {
						// 14MAR17 WLB: NPE fix triggered by Rubal
						row = sheet.createRow(row_idx);
					}
					Cell cell = row.getCell(col_idx);
					if (cell == null) {
						cell = row.createCell(col_idx, CellType.NUMERIC);
						cell.setCellValue(seq_no); // only set a value if
													// creating the cell
					} else if (cell.getCellTypeEnum() == CellType.NUMERIC) {
						seq_no = cell.getNumericCellValue();
					}

				}
			}
		}
	}

	@Override
	public void disconnect() throws IOException {
		if (wb == null) {
			log.error("attempt to close file not open.");
			return;
		}

		for (int idx = wb.getNumberOfSheets() - 1; idx >= 0; idx--) {
			Sheet sheet = wb.getSheetAt(idx);
			if (sheet.getLastRowNum() < 1) {
				log.info("removing sheet: " + sheet.getSheetName());
				wb.removeSheetAt(idx);
			} else {
				sheet.createFreezePane(1, headerRows);
			}
		}

		if (wb instanceof SXSSFWorkbook) {
			// cannot autosize untracked column.
			// (although I might autosize right after writing the header line?)
		} else {
			// autosize first 20 cols
			for (int i = 0; i < wb.getNumberOfSheets(); i++) {
				Sheet sheet = wb.getSheetAt(i);

				int lastCol = 20;
				Row row0 = sheet.getRow(0);
				if (row0 == null) {
					// cannot autosize columns for streaming interface beyond
					// cached limit
					continue;
				}
				lastCol = row0.getLastCellNum();

				for (short col = 0; col < lastCol; col++) {
					// exception thrown here for SXSSFWorkbook
					sheet.autoSizeColumn(col); // adjust width of column
				}
			}
		}

		wb.write(fos);
		fos.close();

		wb = null;
		start_time = 0;

	}

	private void putGeneric(int curr_row, PersistentItem mb, RpMetric[] metrics, Sheet sheet, int sheet_idx)
			throws IOException {

		Row xrow = null;
		if (mss_interval[sheet_idx] > 0) {
			curr_row = getDestinationRowByTime(sheet, sheet_idx, mb.getTime());
		} else {
			// // annotation time
			// curr_row = sheet.getLastRowNum();
			// // if (sid == StreamID.ANNOTATION) {
			// curr_row++;

			// create a row in the annotation sheet
			xrow = putDatedString(curr_row, mb.getTm(), sheet_idx, sheet);
			System.out.println("ADDING ANNO LINE: " + sheet.getSheetName() + " at " + curr_row);

			// update the last entry time
			Date dt = mb.getTm();

			boolean rel_time = false;
			if (rel_time) {
				if (start_time <= 0) {
					start_time = dt.getTime();
				}

				Cell cell = xrow.getCell(1);
				if (cell == null) {
					cell = xrow.createCell(1);
					cell.setCellType(CellType.NUMERIC);
				}
				cell.setCellValue((dt.getTime() - start_time) / 1000.0);

			}

		}

		if (curr_row < 1) {
			return;
		}

		if (xrow == null) {
			xrow = sheet.getRow(curr_row);
		}
		if (xrow == null) {
			// FIXME: maybe...should be closest interval time?
			xrow = putDatedString(curr_row, mb.getTm(), sheet_idx, sheet);
		}
		for (RpMetric metric : metrics) {
			int col = findOrCreateColumn(sheet, metric);
			Cell cell = xrow.getCell(col);
			if (cell == null) {
				cell = xrow.createCell(col);
			}
			Object value = IntfUtil.getScaledValue(mb, metric);
			if (value == null) {
				// log.warn("nullvalue for: {} / {}", metric.getLocation(),
				// metric.getName());
			} else if (value instanceof double[]) {
				// already handled
				// assert( mss > 0);
			} else if (value instanceof float[]) {
				// already handled
				// assert( mss > 0);
			} else if (value instanceof String) {
				cell.setCellValue((String) value);
				cell.setCellType(CellType.STRING);
			} else if (value instanceof Number) {
				Number d = (Number) value;
				cell.setCellValue(d.doubleValue());
				cell.setCellType(CellType.NUMERIC);
			} else if (value instanceof Date) {
				Date d = (Date) value;
				cell.setCellValue(HSSFDateUtil.getExcelDate(d));
				cell.setCellType(CellType.NUMERIC);
			} else if (value instanceof Boolean) {
				Boolean d = (Boolean) value;
				cell.setCellValue(d);
				cell.setCellType(CellType.BOOLEAN);
			} else {
				log.error("Cannot handle type: {} field: {}", value.getClass(), metric);
			}
		}
	}

	private void putWaveform(PersistentItem wfb, RpMetric metric, Sheet sheet, int sheet_idx, double mss, int firstRow,
			int lastDataRow) throws IOException {

		long tm = wfb.getTime();

		Row xrow = null;

		int rowNum = firstRow;

		int col = findOrCreateColumn(sheet, metric);
		Object value = IntfUtil.getScaledValue(wfb, metric);
		if (value == null) {
			log.debug("null value for: {} {}", metric.getLocation(), metric.getCode());
		} else if (value instanceof float[]) {
			float[] arr = (float[]) value;
			for (float f : arr) {
				if (rowNum >= headerRows && rowNum < lastDataRow) {
					xrow = sheet.getRow(rowNum);
					if (xrow == null) {
						xrow = getDestinationRowByIndex(sheet_idx, sheet, rowNum, tm);
					}
					Cell cell = xrow.createCell(col);
					cell.setCellValue(f);
					cell.setCellType(CellType.NUMERIC);
				}
				tm += mss;
				rowNum++;
			}
		} else if (value instanceof double[]) {
			double[] arr = (double[]) value;
			for (double f : arr) {
				if (rowNum >= headerRows && rowNum < lastDataRow) {
					xrow = sheet.getRow(rowNum);
					if (xrow == null) {
						xrow = getDestinationRowByIndex(sheet_idx, sheet, rowNum, tm);
					}
					Cell cell = xrow.createCell(col);
					cell.setCellValue(f);
					cell.setCellType(CellType.NUMERIC);
				}
				tm += mss;
				rowNum++;
			}
		} else {
			// ignore...handle in putGeneric
		}
	}

	private Row putDatedString(int row, Date dt, int sheet_idx, Sheet sheet, String... string) throws IOException {
		int col = 0;

		Row xrow = sheet.createRow(row);
		Cell cell = xrow.createCell(col++);
		cell.setCellValue(HSSFDateUtil.getExcelDate(dt));
		cell.setCellStyle(dateStyle);

		if (start_time <= 0) {
			start_time = dt.getTime();
		}

		cell = xrow.createCell(col++);
		cell.setCellValue((dt.getTime() - start_time) / 1000.0);

		for (String str : string) {
			cell = xrow.createCell(col++);
			cell.setCellValue(str);
			// cell.setCellType(CellType.NUMERIC);
		}

		return xrow;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		Sheet sheet = getOrCreateSheet(source, sid, item);
		if (sheet == null) {
			log.warn("ignoring annotation/alarm? block: ", item);
			return;
		}

		int sheet_idx = wb.getSheetIndex(sheet);
		// if we are using sheet-per-device...reject duplicate data
		// else single-sheet-merge, overwrite duplicate data
		if (sheet_mode == MULTIPLE_SHEET && mss_interval[sheet_idx] > 0) {
			if (sheet_idx >= MAX_SHEETS) {
				log.error("EXCEEDED MAX_SHEETS={}", MAX_SHEETS);
				return; // too many sheets!
			}

			// long currTime = mb.getTime();
			// if (currTime - last_time[sheet_idx] < mss_interval) {
			// return; // don't save
			// }
			last_time[sheet_idx] = item.getTime();
		}

		RpMetric[] metrics = IntfUtil.getMetrics(item);
		if (metrics == null) {
			log.error("NO VALUES FIND IN BLOCK: {} TM={}", item, item.getTm());
			return;
		}

		try {
			int firstDataRow = getDestinationRowByTime(sheet, sheet_idx, item.getTime());
			int lastDataRow = getDestinationRowByTime(sheet, sheet_idx, stop_time);

			for (RpMetric metric : metrics) {
				Integer rate = metric.getSampleRate();
				if (rate != null && rate > 0) {
					double mss = mss_interval[sheet_idx];
					putWaveform(item, metric, sheet, sheet_idx, mss, firstDataRow, lastDataRow);
				}
			}
			putGeneric(firstDataRow, item, metrics, sheet, sheet_idx);
		} catch (IOException e1) {
			// BLIND: notify someone that data is being lost!
		}
	}

	@Override
	public void setHeader(RpSubject header) {
		this.header = header;

		if (fos != null) {
			writeHeaderSheet();
		}
	}

	private void writeHeaderSheet() {
		String name = "Header";

		Sheet sheet = wb.getSheet(name);
		if (sheet == null) {
			sheet = wb.createSheet(name);
		}

		writePair(sheet, "Company Name", header.getCompany());
		writePair(sheet, "Organization", header.getOrganization());
		writePair(sheet, "Study Title", header.getStudyTitle());
		writePair(sheet, "Sugery Date", header.getSurgeryDate());
		// writePaire("Subject Number: HRV"+ endl );
		writePair(sheet, "Medical ID", header.getMedicalId());
		writePair(sheet, "DAQ Operator(s)", header.getOperator());
		writePair(sheet, "Base File Name", header.getBaseFileName());
		// writePair("Sequence Number: ", seqNo + endl );
		// writePair("Notes: Subset File"+ endl );

	}

	private void writePair(Sheet sheet, String key, Object value) {
		if (value == null) {
			return; // ignore
		}
		int idx = sheet.getLastRowNum();
		Row row = sheet.createRow(idx + 1);
		Cell cell = row.createCell(0);
		cell.setCellValue(key);
		cell = row.createCell(1);
		if (value instanceof String) {
			cell.setCellValue((String) value);
		} else if (value instanceof Date) {
			cell.setCellValue(HSSFDateUtil.getExcelDate((Date) value));
			cell.setCellStyle(dateStyle);
		} else {
			cell.setCellValue("???" + value);
		}
	}

	private Sheet getOrCreateSheet(StreamProducer ds, StreamID sid, PersistentItem mb) {

		String name = "Data";
		if (sid != null) {
			name = sid.getName();
		}

		if ("annot".equals(name)) {
			name = "Notes";
		} else if ("waveform".equals(name)) {
			name = "Waveforms";
		}

		/*
		 * if (ds instanceof PiDatastreamImporter) { // FIXME: maybe getName() should
		 * be moved up into StreamProducer name = ((PiDatastreamImporter)
		 * ds).getName(); } else { RpDevice conf = null; if (ds != null) { conf
		 * = ds.getConfiguration(); } if (conf != null) { name = conf.getName();
		 * } }
		 * 
		 * if (name == null) { name = "NONE"; }
		 * 
		 * if (sid != null) { char code = (char) sid.getCode();
		 * 
		 * name += "_"; name += code; }
		 * 
		 * if ("Annotations".equals(name)) { // no special handling for single
		 * sheet or multiple sheets } else if (sheet_mode == SINGLE_SHEET) {
		 * name = "Data"; }
		 * 
		 * if (name.indexOf('[') > 0) { name = name.replaceAll("\\[", ""); name
		 * = name.replaceAll("\\]", ""); } if (name.indexOf(':') > 0) { name =
		 * name.replaceAll(": ", ":"); // remove space if present name =
		 * name.replaceAll(":", "__"); } if (name.indexOf('/') > 0) { String[]
		 * arr = name.split("/"); name = arr[0]; } if (name.length() == 0) {
		 * name = "NO_NAME"; } if (name.length() > 30) { // maximum length of a
		 * sheet name name = name.substring(name.length() - 30); }
		 */

		Sheet sheet = wb.getSheet(name);
		if (sheet == null) {
			sheet = wb.createSheet(name);
			Row row0 = sheet.createRow(0);
			cachedRow0.put(name, row0);

			if (show_units) {
				sheet.createRow(1);
			}

			boolean rel_time = true; // sid == StreamID.WAVEFORM;
			if (rel_time) {
				findOrCreateColumn(sheet, rel_time_metric);
			}

			if (sid == StreamID.ANNOTATION) {
				findOrCreateColumn(sheet, mrk_no_metric);
			}
		}

		/*
		 * make sure all the columns exist ... additional columns cannot be
		 * added in streaming mode after the first data row has been written!
		 */
		if (sheet.getLastRowNum() < 3) {
			prepareSheetHeader(sheet, ds, sid, mb);
		}

		return sheet;
	}

	private void prepareSheetHeader(Sheet sheet, StreamProducer ds, StreamID sid, PersistentItem mb) {
		if (ds == null) {
			log.warn("cannot prepare sheet headers: null stream producer");
		} else {

			Row row0 = sheet.getRow(0);
			cachedRow0.put(sheet.getSheetName(), row0);

			Cell cell0 = row0.getCell(0);
			if (cell0 == null) {
				cell0 = row0.createCell(0);

				/*
				 * make sure all the columns exist
				 */

				// column 0 is special
				char code = (sid == null) ? 'x' : (char) sid.getCode();
				int rate = 0;
				for (RpMetric metric : mb.getMetrics()) {
					findOrCreateColumn(sheet, metric);
					if (code == 'W') {
						Integer r = metric.getSampleRate();
						if (r != null) {
							rate = Math.max(rate, r);
						}
					}
				}

				cell0.setCellType(CellType.STRING);

				if (rate > 0) {
					cell0.setCellValue("" + code + ":" + rate);
					int sheet_idx = wb.getSheetIndex(sheet);
					int interval = 1000 / rate;
					if (mss_interval[sheet_idx] == 0 || interval < mss_interval[sheet_idx]) {
						mss_interval[sheet_idx] = interval;
					}
				} else {
					cell0.setCellValue("" + code);
				}
				cell0.setCellStyle(headerStyle);

			}
		}
	}

	/**
	 * 
	 * @param sheet
	 * @param sheet_idx
	 * @param tm
	 * @param update_last_time
	 * @return
	 * 
	 * 		It is possible for this routine to return a negative row number
	 *         based on the start_time.
	 * 
	 *         Handles the case of when rows are sent slightly out of sequence
	 */

	private int getDestinationRowByTime(Sheet sheet, int sheet_idx, long tm) {

		if (mss_interval[sheet_idx] < 0) {
			// rows are advanced via a seperate mechanism (ie, annotation time)
			int last = sheet.getLastRowNum();

			log.error("NOT EXPECTING THIS CODE TO BE CALLED");
			return last;
		}

		if (start_time == 0) {
			start_time = tm;
		}

		// int last_row = sheet.getLastRowNum();
		int row_no;
		if (mss_interval[sheet_idx] > 0) {
			row_no = (int) ((tm - start_time) / mss_interval[sheet_idx]);
			row_no++; // skip first header row, column labels
			if (show_units)
				row_no++;
		} else {
			row_no = sheet.getLastRowNum() + 1;
			if (row_no > 2) {
				long row_time = getRowTimeInMillis( sheet, sheet.getLastRowNum() );
				if (tm <= row_time) {
					// go back!
					int tot = 0; // I can only go back so far...
					while (row_no > 2 && tot < 10) {
						row_no--;

						row_time = getRowTimeInMillis( sheet, row_no );
						if (row_time <= tm) {
							// found my row!
							break;
						}

						tot++;
					}
				}
			}
		}

		return row_no; // getDestinationRowByIndex(sheet_idx, sheet, row_no,
						// tm);
	}

	private long getRowTimeInMillis(Sheet sheet, int row_no ) {
		Row rr = sheet.getRow(row_no);
		Cell cc = rr.getCell(0);
		Date dt = cc.getDateCellValue();
		if (dt == null) {
			log.error("not expecting empty DATE cell at row: {}", row_no);
			return 0;
		}
		return dt.getTime();
	}

	private Row getDestinationRowByIndex(int sheet_idx, Sheet sheet, int row_no, long tm) {
		Date dt = new Date(tm);

		Row xrow;
		if (sheet_mode == MULTIPLE_SHEET || mss_interval[sheet_idx] == 0) {

			xrow = sheet.getRow(row_no);
			if (xrow == null) {
				xrow = sheet.createRow(row_no);
			}
		} else {
			// this is the approach I want only for MERGE into a single
			// Spreadsheet
			// this uses an overwrite-existing-cell approach to remove
			// duplicates
			int row = (int) ((tm - start_time) / mss_interval[sheet_idx]) + headerRows;
			xrow = sheet.getRow(row);
			if (xrow == null) {
				xrow = sheet.createRow(row);
			}
		}

		Cell cell = xrow.createCell(0);
		cell.setCellValue(HSSFDateUtil.getExcelDate(dt));
		cell.setCellType(CellType.NUMERIC);
		cell.setCellStyle(dateStyle);

		if (start_time <= 0) {
			start_time = tm;
		}
		cell = xrow.createCell(1);
		cell.setCellValue((tm - start_time) / 1000.0);

		return xrow;
	}

	private int findOrCreateColumn(Sheet sheet, RpMetric metric) {
		String loc = metric.getLocation();
		String code = metric.getCode();
		String name = metric.getName();
		return findOrCreateColumn(sheet, loc, code, name, metric.getUnit());
	}

	private int findOrCreateColumn(Sheet sheet, String loc, String code, String name, RpUnit unit) {

		if (code != null && code.equals(loc)) {
			code = null;
		}
		String key = loc; // "[" + loc;
		if (code != null)
			key += "/" + code;
		if (name != null)
			key += ": " + name;

		/*
		 * kludgey way to handle this case
		 */
		if (key.startsWith("val: ")) {
			key = key.substring(5);
		}

		Row row0 = cachedRow0.get(sheet.getSheetName());

		/*
		 * make sure all the columns exist
		 */

		int col_idx = findCol(row0, key);

		if (col_idx < 0) {
			col_idx = row0.getLastCellNum();
			if (col_idx < 0) {
				col_idx = 1;
			}

			Cell cell = row0.createCell(col_idx);
			cell.setCellType(CellType.STRING);
			cell.setCellValue(key);
			cell.setCellStyle(headerStyle);

			if (show_units) {
				Row row1 = sheet.getRow(1);

				cell = row1.createCell(col_idx);
				cell.setCellType(CellType.STRING);
				cell.setCellStyle(headerStyle);
				if (unit != null) {
					cell.setCellValue(unit.toString());
				}
			}
		}

		return col_idx;
	}

	private int findCol(Row row0, String key) {
		int col_idx = -1;

		if (row0 == null) {
			log.error("row0 is null!");
		}
		for (int i = 0; i < row0.getLastCellNum(); i++) {
			Cell cell = row0.getCell(i);
			if (cell == null) {
				// System.err.println( "null cell? pos: " + i );
			} else {
				String val = cell.getStringCellValue();
				if (key.equals(val)) {
					col_idx = i;
					break;
				}
			}
		}
		return col_idx;
	}

	public void setStartAndStopTimes(long start_time, long stop_time) {
		this.start_time = start_time;
		this.stop_time = stop_time;
	}

	public void setInterval(int msInterval) {
		for (int i = 0; i < mss_interval.length; i++) {
			mss_interval[i] = msInterval;
		}
	}

	@Override
	public void addDevice(RpDevice conf) {
		log.error("THIS DOES NOT WORK: getOrCreateSheet(conf);");
	}

	@Override
	public void setDestination(File archiveDir) {
		xlsFile = new File(archiveDir, "root.xls");
	}
}
