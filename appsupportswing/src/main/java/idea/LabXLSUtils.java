package idea;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Date;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellStyle;
import org.apache.poi.ss.usermodel.CellType;
import org.apache.poi.ss.usermodel.DateUtil;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class LabXLSUtils {

	public final static DateFormat r_df = new SimpleDateFormat("yyyy-MM-dd HH:mm");

	public static Date addTime(Date dt, Date tm) {
		Calendar cal = Calendar.getInstance();
		cal.setTime(dt);
		cal.set(Calendar.HOUR_OF_DAY, tm.getHours());
		cal.set(Calendar.MINUTE, tm.getMinutes());
		cal.set(Calendar.SECOND, tm.getSeconds());
		return cal.getTime();
	}

	public static Cell getCell(Sheet sheet, int row, int col) {
		Cell cell = null;

		Row r = sheet.getRow(row);
		if (r != null) {
			cell = r.getCell(col);
		}
		return cell;
	}

	public static String getValueAsString(Cell cell) {
		String value = null;

		if (cell != null) {
			switch (cell.getCellType()) {
			case STRING:
				value = cell.getStringCellValue();
				break;
			case NUMERIC:

				if (DateUtil.isCellDateFormatted(cell)) {
					value = r_df.format(cell.getDateCellValue());
				} else {
					value = "" + (int) (cell.getNumericCellValue() + .01);
				}

				break;
			case BLANK:
				// just null, but not an error
				break;
			case FORMULA:
				switch (cell.getCachedFormulaResultType()) {
				case NUMERIC:

					value = "" + cell.getNumericCellValue();

					if (DateUtil.isCellDateFormatted(cell)) {
						value = r_df.format(cell.getDateCellValue());
					} else {
						value = "" + cell.getNumericCellValue();
					}
					break;
				case STRING:
					value = cell.getStringCellValue();
					break;
				default:
					log.error("Cannot get cached cell type/value: {}/{}", cell.getCachedFormulaResultType(), cell);
				}
				break;
			default:
				log.error("Unexpected value type: " + cell.getCellType());
			}
		}

		if (value != null) {
			value = value.trim();
		}
		return value;
	}

	private static Date getValueAsTime_FromHHMMSS(Cell cell) {
		Date value = null;

		int tm;

		if (cell != null) {
			switch (cell.getCellType()) {
			case BLANK:
				// nothing here
				break;
			case NUMERIC:
				value = cell.getDateCellValue();
				CellStyle sty = cell.getCellStyle();
				String fmt = sty.getDataFormatString();
				// System.out.println("format=" + fmt );
				if (fmt.indexOf("h:mm") < 0) {
					tm = (int) (cell.getNumericCellValue() + 0.01);

					if (tm < 10000) {
						tm *= 100;
					}

					Calendar cal = Calendar.getInstance();

					cal.set(Calendar.HOUR_OF_DAY, tm / 10000);
					cal.set(Calendar.MINUTE, (tm / 100) % 100);
					cal.set(Calendar.SECOND, tm % 100);
					value = cal.getTime();
				} else {
					value = cell.getDateCellValue();
				}
				break;
			case STRING: {
				Calendar cal = Calendar.getInstance();
				String s = cell.getStringCellValue();
				if (s.equals("N/A")) {
					// leave value null
				} else {
					try {
						tm = Integer.parseInt(s);
						if (tm < 10000) {
							tm *= 100;
						}

						cal.set(Calendar.HOUR_OF_DAY, tm / 10000);
						cal.set(Calendar.MINUTE, (tm / 100) % 100);
						cal.set(Calendar.SECOND, tm % 100);
						value = cal.getTime();
					} catch (Exception e) {
						try {
							DateFormat df = new SimpleDateFormat("M/d/yyyy HH:mm:ss");
							value = df.parse(s);
						} catch (Exception ee) {
							log.error("COULD NOT PARSE HHMMSS: {}", s);
						}
					}
				}
			}
				break;
			default:
				log.error("Unexpected value type: " + cell.getCellType());
			}
		}
		return value;
	}

	private static int getNamedRow(String name, Sheet sheet) {
		int namedRow = -1;
		for (int i = 0; i < sheet.getLastRowNum(); i++) {
			Row row = sheet.getRow(i);
			Cell cell = row.getCell(0);
			String rowName = getValueAsString(cell);
			if (name.equalsIgnoreCase(rowName)) {
				namedRow = i;
				break;
			}
		}
		return namedRow;
	}

	public static double[] read_row_as_double(Sheet sheet, int row_idx, int first_col, int count) {
		Row row = sheet.getRow(row_idx);
		double[] arr = new double[count];
		
		int last_col = first_col + count - 1;
		Cell cell;
		for (int col = first_col; col <= last_col; col++) {

			double val = Double.NaN;
			cell = row.getCell(col);

			if (cell != null) {
				if (cell.getCellType() == CellType.BLANK) {
					// ok...leave as NaN
				} else if (cell.getCellType() == CellType.FORMULA) {
					switch (cell.getCachedFormulaResultType()) {
					case NUMERIC:
						val = cell.getNumericCellValue();
						break;
					case STRING:
						String txt = cell.getStringCellValue();
						if (txt.length() > 0) {
							try {
								val = Double.parseDouble(txt);
							} catch (Exception e) {
								//log.warn("error parsing formula double: {} (r,c)=({}) sheet=" + sheet.getSheetName(), txt,
								//		row_idx + "," + col);
							}
						}
						break;
					default:
						log.error("Cannot get cached cell value: {} ({})", sheet.getSheetName(), row_idx + "," + col);
					}
				} else if (cell.getCellType() == CellType.NUMERIC) {
					val = cell.getNumericCellValue();
				} else if (cell.getCellType() == CellType.STRING) {
					String txt = cell.getStringCellValue().trim();
					if ("N/A".equalsIgnoreCase(txt)) {
						val = Double.NaN; // redundant...but ok
					} else if ("OFF".equalsIgnoreCase(txt)) {
						val = Double.NaN; // redundant...but ok
					} else if ("BAR".equals(txt)) {
						val = Double.NaN; // redundant...but ok
					} else if ("***".equals(txt)) {
						val = Double.NaN; // redundant...but ok
					} else if (txt.length() > 0) {
						try {
							val = Double.parseDouble(txt);
						} catch (Exception e) {
							//log.warn("read_row_as_double error parsing double: {} (r,c)=({}) sheet=" + sheet.getSheetName(), txt, row_idx
							//		+ "," + col);
						}
					}
				} else {
					log.warn("Unknown double data in sheet: {} (r,c)=({})", sheet.getSheetName(), row_idx + "," + col);
				}
			}

			arr[col - first_col] = val;
		}

		return arr;
	}

	public static double[] read_row_as_temp(Sheet sheet, int row_idx, int first_col, int last_col) {
		Row row = sheet.getRow(row_idx);
		double[] arr = new double[last_col - first_col + 1];
		Cell cell;
		for (int col = first_col; col <= last_col; col++) {

			double val = Double.NaN;
			cell = row.getCell(col);

			if (cell != null) {
				if (cell.getCellType() == CellType.BLANK) {
					// ok...leave as NaN
				} else if (cell.getCellType() == CellType.NUMERIC) {
					val = cell.getNumericCellValue();
				} else if (cell.getCellType() == CellType.STRING) {
					String txt = cell.getStringCellValue().trim();
					if (txt.length() > 0) {
						try {
							txt = txt.replace("C", "");
							txt = txt.trim();
							val = Double.parseDouble(txt);
						} catch (Exception e) {
							log.warn("error parsing temp: {} (r,c)=({}) sheet=" + sheet.getSheetName(), txt, row_idx
									+ "," + col);
						}
					}
				} else {
					log.warn("Unknown double data in sheet: {} (r,c)=({})", sheet.getSheetName(), row_idx + "," + col);
				}
			}

			arr[col - first_col] = val;
		}

		return arr;
	}

	public static double[] read_col_as_double(Sheet sheet, int col_idx, int first_row, int last_row) {
		double[] arr = new double[last_row - first_row + 1];
		Cell cell;
		for (int row_idx = first_row; row_idx <= last_row; row_idx++) {
			double val = Double.NaN;

			Row row = sheet.getRow(row_idx);
			cell = row.getCell(col_idx);

			if (cell != null && cell.getCellType() == CellType.NUMERIC) {
				val = cell.getNumericCellValue();
			}

			arr[row_idx - first_row] = val;
		}

		return arr;
	}

	public static String[] read_row_as_time_special_HHMMSS(Sheet sheet, int row_idx, int first_col, int last_col,
			Date[] vitals_dates) {
		Row row = sheet.getRow(row_idx);

		String[] arr = new String[last_col - first_col];
		Cell cell;
		for (int col = first_col; col <= last_col; col++) {

			cell = row.getCell(col);
			Date tm = getValueAsTime_FromHHMMSS(cell);

			if (tm == null) {
				// System.out.println("**** no time col: " + col + "   SKIP");
			} else {
				arr[col - first_col] = r_df.format(addTime(vitals_dates[col], tm));
			}

		}

		return arr;
	}

	public static String[] read_row_as_time_special_HHMMSS(Sheet sheet, int row_idx, int first_col, int last_col,
			Date dt) {
		Row row = sheet.getRow(row_idx);

		String[] arr = new String[last_col - first_col];
		Cell cell;
		for (int col = first_col; col <= last_col; col++) {

			cell = row.getCell(col);
			Date tm = getValueAsTime_FromHHMMSS(cell);

			if (tm == null) {
				// System.out.println("**** no time col: " + col + "   SKIP");
			} else {
				arr[col - first_col] = r_df.format(addTime(dt, tm));
			}

		}

		return arr;
	}

	public static Date[] read_row_as_date(Sheet sheet, int row_idx, int first_col, int last_col) {
		Row row = sheet.getRow(row_idx);

		boolean trim_length = false;
		if (last_col <= 0) {
			last_col = row.getLastCellNum();
			trim_length = true;
		}
		int non_null = 0;

		Date[] arr = new Date[last_col - first_col + 1];
		Cell cell;
		for (int col = first_col; col <= last_col; col++) {

			cell = row.getCell(col);
			if (cell == null) {
				continue;
			}
			Date tm = getValueAsDate(cell);

			if (tm == null) {
				continue;
			}

			arr[col - first_col] = tm;
			non_null = col;

		}

		if (trim_length) {
			if (non_null < first_col) {
				log.error("no data found: {}", sheet.getSheetName());
				arr = null;
			} else {
				arr = Arrays.copyOf(arr, non_null + 1 - first_col);
			}

		}

		return arr;
	}

	public static String[] read_date_and_time(Sheet sheet, int date_row_idx, int time_row_idx, int first_col,
			int last_col) {
		Row date_row = sheet.getRow(date_row_idx);
		Row time_row = sheet.getRow(time_row_idx);

		String[] arr = new String[last_col - first_col + 1];
		Cell dt_cell;
		Cell tm_cell;
		for (int col = first_col; col <= last_col; col++) {

			dt_cell = date_row.getCell(col);
			tm_cell = time_row.getCell(col);
			Date dt = dt_cell.getDateCellValue();
			Date tm = getValueAsTime_FromHHMMSS(tm_cell);

			if (tm == null) {
				// System.out.println("**** no time col: " + col + "   SKIP");
			} else {
				arr[col - first_col] = r_df.format(addTime(dt, tm));
			}

		}

		return arr;
	}

	public static String[] read_col_as_time_special_HHMMSS(Sheet sheet, int col_idx, int first_row, int last_row,
			Date dt) {

		String[] arr = new String[last_row - first_row + 1];
		Cell cell;
		for (int row_idx = first_row; row_idx <= last_row; row_idx++) {
			Row row = sheet.getRow(row_idx);

			cell = row.getCell(col_idx);
			Date tm = getValueAsTime_FromHHMMSS(cell);

			if (tm == null) {
				// System.out.println("**** no time col: " + col + "   SKIP");
			} else {
				arr[row_idx - first_row] = r_df.format(addTime(dt, tm));
			}

		}

		return arr;
	}

	public static String[] read_col_as_time(Sheet sheet, int col_idx, int first_row, int last_row) {
		if (last_row < 0) {
			last_row = sheet.getLastRowNum();
		}

		String[] arr = new String[last_row - first_row + 1];
		Cell cell;
		for (int row_idx = first_row; row_idx <= last_row; row_idx++) {
			Row row = sheet.getRow(row_idx);
			cell = row.getCell(col_idx);
			Date tm = cell.getDateCellValue();

			arr[row_idx - first_row] = r_df.format(tm);
		}

		//		if( trim_length ) {
		//			arr = Arrays.copyOf(arr, non_null + 1 - first_col);
		//		}

		return arr;
	}

	public static String[] read_row_as_string(Sheet sheet, int row_idx, int first_col, int last_col) {
		Row row = sheet.getRow(row_idx);
		int non_null = 0;

		boolean trim_length = false;
		if (last_col <= 0) {
			last_col = row.getLastCellNum();
			trim_length = true;
		}
		String[] arr = new String[last_col - first_col + 1];
		Cell cell;
		for (int col = first_col; col <= last_col; col++) {
			cell = row.getCell(col);
			if (cell != null) {

				arr[col - first_col] = getValueAsString(cell);
				if (arr[col - first_col] != null) {
					non_null = col;
				}
			}
		}

		if (trim_length) {
			if (non_null < first_col) {
				log.error("no data found: {}", sheet.getSheetName());
				arr = null;
			} else {
				arr = Arrays.copyOf(arr, non_null + 1 - first_col);
			}

		}
		return arr;
	}

	public static String[] read_col_as_string(Sheet sheet, int col_idx, int start, int r_count) {
		int count = r_count;
		if (count < 0) {
			count = sheet.getLastRowNum() + 1;
		}
		int non_null = 0;
		String[] vals = new String[count];
		//vals[0] = "timep"; // label the first row as TP in case it is not named in xls

		for (int row_idx = start; row_idx < vals.length; row_idx++) {
			Row row = sheet.getRow(row_idx);
			if (row == null) {
				continue;
			}
			Cell cell = row.getCell(col_idx);
			if (cell == null) {
				// ignore
			} else {
				String val = getValueAsString(cell);
				if (val != null && val.length() > 0) {
					vals[row_idx - start] = val;
					non_null = row_idx - start;
				}
			}
		}

		if (r_count < 0) {
			// 	scrape off the nulls if we are asking for variable length
			vals = Arrays.copyOf(vals, non_null + 1);
		}

		return vals;
	}

	public static void writeWorkbook(Workbook wb, File outputFile) throws FileNotFoundException, IOException {
		for (int idx = 0; idx < wb.getNumberOfSheets(); idx++) {
			Sheet sheet = wb.getSheetAt(idx);
			for (short col = 0; col < 30; col++) {
				sheet.autoSizeColumn(col); // adjust width of column
			}
		}

		if (outputFile.exists()) {
			outputFile.delete();
		}
		wb.write(new FileOutputStream(outputFile));
	}

	public static Date getValueAsDate(Cell cell) {

		if (cell == null) {
			return null;
		}

		Date tm = null;

		CellType typ = cell.getCellType();

		retry: do {
			switch (typ) {
			case BLANK:
				continue;
			case STRING:
				String value = cell.getStringCellValue();
				try {
					DateFormat df = new SimpleDateFormat("d-MMM-yy");
					tm = df.parse(value);
				} catch (Exception ee) {
					log.error("COULD NOT PARSE D-MMM-yy: {}", value);
				}
				break;
			case NUMERIC:
				if (DateUtil.isCellDateFormatted(cell)) {
					tm = cell.getDateCellValue();
				} else {
					log.error("numeric but not date: " + cell.getNumericCellValue());
				}
				break;
			case FORMULA:
				typ = cell.getCachedFormulaResultType();
				continue retry;
			default:
				log.error("unknown cell typ for date conversion: " + cell.getCellType());
			}
			break;
		} while (true);
		return tm;
	}
}
