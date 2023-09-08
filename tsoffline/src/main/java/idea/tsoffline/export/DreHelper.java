package idea.tsoffline.export;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellType;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.ss.usermodel.WorkbookFactory;

import idea.message.StreamID;
import idea.persistmanager.PiConstants;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;

@Slf4j
public class DreHelper {
	public static final String endl = "\r\n";
	private RpSubject header;
	private Date clipStart;
	private Date clipEnd;
	private Date dateStart;

	public DreHelper( RpSubject header, Date dateStart, Date clipStart, Date clipEnd ) {
		this.header = header;
		this.clipStart = clipStart;
		this.clipEnd = clipEnd;
		this.dateStart = dateStart;
	}
	
	public void exportDAT(ExportComplete expComplete, String xlsName, String waveSpec, File audioInputFile, boolean isFileOutput, boolean hasAudio ) {
		long dataStartMs = dateStart.getTime();

		try {
			File xlsFile = new File(xlsName);
			Workbook wb = WorkbookFactory.create(
					xlsFile,  // file 
					null,     // password
					true);    // read only
			
			boolean firstNotesFile = true;
			File audioOutputFile = null;
			
			for (int sheet_no = 0; sheet_no < wb.getNumberOfSheets(); sheet_no++) {
				Sheet sheet = wb.getSheetAt(sheet_no);

				if ("Header".equals(sheet.getSheetName())) {
					// read header but take no further action
					continue;
				}
				Row row0 = sheet.getRow(0);
				if (row0 == null || row0.getLastCellNum() < 2) {
					continue;
				}

				String datName = xlsName;
				int dot = datName.lastIndexOf('.');
				if (dot > 0) {
					datName = datName.substring(0, dot);
				}

				File datFile = null;

				Cell cell0 = row0.getCell(0);
				StreamID sid = getStreamID(cell0);

				String ext = null;
				if (sid == StreamID.WAVEFORM)
					ext = "_w_%03d.dat";
				else if (sid == StreamID.MEASUREMENT)
					ext = "_v_%03d.vtl";

				boolean append = false;
				if (ext == null) {
					sid = StreamID.ANNOTATION;
					datFile = new File(datName + " (notes).txt");
					append = !firstNotesFile;
					firstNotesFile = false;
				} else {

					int idx = 1;
					String suffix = "";
					do {
						suffix = String.format(ext, idx);
						datFile = new File(datName + suffix);
						idx++;
					} while (datFile.exists());
				}

				expComplete.setDatFile(sid, datFile);

				try (FileWriter writer = new FileWriter(datFile, append)) {
					int firstCol = (sid == StreamID.WAVEFORM) ? 2 : 1;
					if (!append) {
						if (sid == StreamID.WAVEFORM) {
							log.error("FIXME: where do i find sample rate...or any of the data?");
							int sampleRate = 0;
							exportWaveformHeader(writer, sheet, sampleRate );
							exportColumnHeaders(writer, sheet, "TM", firstCol);
						} else if (sid == StreamID.MEASUREMENT) {
							exportVitalsHeader(writer, sheet);
							exportColumnHeaders(writer, sheet, "TM", firstCol);
						} else { 
							// if (sid == StreamID.ANNOTATION) 
							exportNotesHeader(writer, sheet);
							writer.write("Time");
							writer.write("\t");
							writer.write("MRK #");
							writer.write("\t");
							writer.write("Notes");
							writer.write( DreHelper.endl );
						}

					}
					
					if (sid == StreamID.WAVEFORM) {
						exportWaveformDetail(writer, sheet);
					} else if (sid == StreamID.MEASUREMENT) {
						exportDetail(writer, sheet);
					} else {
						exportAnnotation(writer, sheet);
					}
				}
			}
			audioOutputFile = null;
			if (audioInputFile != null && isFileOutput&& hasAudio) {
				
				int suffixPos = waveSpec.lastIndexOf(".");
				if (suffixPos > 0) {
					waveSpec = waveSpec.substring(0, suffixPos);
				}
				String ext = "_a_%03d.aud";
				int idx = 1;
				String suffix = "";
				do {
					suffix = String.format(ext, idx);
					audioOutputFile = new File(waveSpec + suffix);
					idx++;
				} while (audioOutputFile.exists());
			}
			if (audioOutputFile == null) {
				expComplete.setDatFile(StreamID.AUDIO, null);
			} else {
				expComplete.setDatFile(StreamID.AUDIO, audioOutputFile);
				long clipStartMs = clipStart.getTime();
				long clipEndMs = clipEnd.getTime();
				ExportUtil.exportAudio(audioInputFile, audioOutputFile, "RAW", dataStartMs, clipStartMs, clipEndMs);
			}

		} catch (Exception e) {
			GuiUtil.showError("Could not export DAT file.", e);
		}
	}

	private StreamID getStreamID(Cell cell0) {
		StreamID sid = null;
		if (cell0 != null) {
			String id = cell0.getStringCellValue();
			if (id != null && id.length() > 0) {
				int code = id.getBytes()[0];
				sid = StreamID.fromCode(code);
			}
		}
		if (sid == null) {
			sid = StreamID.MEASUREMENT;
		}
		return sid;
	}


	/**
	 * 
	 * @param writer
	 * @param sheet
	 * 
	 *            Dynamic Research Evaluation Workstation Vitals Report Tuesday,
	 *            October 27, 2015
	 * @throws IOException
	 */

	public void exportVitalsHeader(FileWriter writer, Sheet sheet) throws IOException {
		SimpleDateFormat df1 = new SimpleDateFormat("EEEEEEEE, MMMMMMMMM dd, yyyy");

		if (header != null) {
			writer.write("Dynamic Research Evaluation Workstation" + endl);
			writer.write("Vitals Report" + endl);
			writer.write(df1.format(clipStart) + endl);
			writer.write(endl);
		}
	}

	public void exportLabBookHeader(FileWriter writer, Sheet sheet) throws IOException {
		SimpleDateFormat df1 = new SimpleDateFormat("EEEEEEEE, MMMMMMMMM dd, yyyy");

		if (header != null) {
			writer.write("Dynamic Research Evaluation Workstation" + endl);
			writer.write("Electronic Lab Book" + endl);
			writer.write(df1.format(clipStart) + endl);
			writer.write(endl);
		}
	}

	public void exportNotesHeader(FileWriter writer, Sheet sheet) throws IOException {
		SimpleDateFormat df1 = new SimpleDateFormat("EEEEEEEE, MMMMMMMMM dd, yyyy");

		if (header != null) {
			writer.write("Dynamic Research Evaluation Workstation" + endl);
			writer.write("Notes and Comments" + endl);
			writer.write(df1.format(clipStart) + endl);
			writer.write(endl);
		}
	}

	public void exportWaveformHeader(FileWriter writer, Sheet sheet, int sampleRate) throws IOException {

		int seqNo = 1;
		SimpleDateFormat df1 = new SimpleDateFormat("EEEEEEEE, MMMMMMMMM dd, yyyy");
		SimpleDateFormat tf1 = new SimpleDateFormat("HH:mm:ss.SSS");
		String devName = "sigmaPAD";

		if (header != null) {
			writer.write("Dynamic Research Evaluation Workstation" + endl);
			writer.write("Analog Waveform Recording: ");
			writer.write("v" + PiConstants.DRE_VERSION + endl);
			writer.write("Subset Format : Scaled ASCII (TXT)" + endl);
			writer.write(df1.format(clipStart) + "    :   " + tf1.format(clipStart) + endl + endl);
			writer.write("Company Name: " + header.getCompany() + endl);
			writer.write("Organization: " + header.getOrganization() + endl);
			writer.write("Study Title: " + header.getStudyTitle() + endl);
			writer.write("Sugery Date: " + df1.format(clipStart) + endl);
			writer.write("Subject Number: HRV" + endl);
			writer.write("Medical ID: " + header.getMedicalId() + endl);
			writer.write("DAQ Operator(s): " + header.getOperator() + endl);
			writer.write("Base File Name: " + devName + endl);
			writer.write("Sequence Number: " + seqNo + endl);
			writer.write("Sample Rate: " + sampleRate + endl);
			writer.write("Notes: Subset File" + endl);
			writer.write(endl);
		}
	}

	public void exportColumnHeaders(FileWriter writer, Sheet sheet, String colZero, int firstCol)
			throws IOException {
		Row row0 = sheet.getRow(0);

		if( colZero != null ) {
			writer.write("TM");
		}
		// write column headers
		for (int cellnum = firstCol; cellnum < row0.getLastCellNum(); cellnum++) {
				writer.write("\t");
				Cell cell = row0.getCell(cellnum);
				String colName = cell.getStringCellValue();
				int colon = colName.indexOf(":");
				if (colon > 0) {
					colName = colName.substring(colon + 1).trim();
				}
				writer.write(colName);
		}
		writer.write(endl);
	}

	public void exportWaveformDetail(FileWriter writer, Sheet sheet)
			throws  IOException {
		for (int rownum = 1; rownum <= sheet.getLastRowNum(); rownum++) {
			Row xrow = sheet.getRow(rownum);
			Cell cell = xrow.getCell(0);
			// Date dt = cell.getDateCellValue();
			// writer.write(df1.format(dt));
			// ignore for WF
			for (int cellnum = 1; cellnum < xrow.getLastCellNum(); cellnum++) {
				if (cellnum > 1) {
					writer.write("\t");
				}
				cell = xrow.getCell(cellnum);
				if( cell == null ) {
					// ignore unexpected empty cell
				} else if (cell.getCellTypeEnum() == CellType.NUMERIC) {
					double d = cell.getNumericCellValue();
					// five significant figures
					BigDecimal value = BigDecimal.valueOf(d);
					BigDecimal wantedValue = value.round(new MathContext(5, RoundingMode.HALF_UP));
					writer.write(wantedValue.toString());
				} else if (cell.getCellTypeEnum() == CellType.STRING) {
					writer.write(cell.getStringCellValue());
				} else {
					writer.write("?" + cell.getCellTypeEnum());
					log.error("unknown XLSX type: " + cell.getCellTypeEnum());
				}
			}
			writer.write(endl);
		}
	}

	public void exportDetail(FileWriter writer, Sheet sheet)
			throws IOException {
		SimpleDateFormat tf1 = new SimpleDateFormat("HH:mm:ss.SSS");

		for (int rownum = 1; rownum <= sheet.getLastRowNum(); rownum++) {
			Row xrow = sheet.getRow(rownum);
			Cell cell = xrow.getCell(0);
			// Date dt = cell.getDateCellValue();
			// writer.write(df1.format(dt));
			// ignore for WF
			for (int cellnum = 0; cellnum < xrow.getLastCellNum(); cellnum++) {
				if (cellnum > 0) {
					writer.write("\t");
				}
				cell = xrow.getCell(cellnum);
				if (cell == null ) {
					// ignore
				} else if (cellnum == 0) {
					Date dt = cell.getDateCellValue();
					if (dt != null) {
						writer.write(tf1.format(dt));
					}
				} else if (cell.getCellTypeEnum() == CellType.NUMERIC) {
					double d = cell.getNumericCellValue();
					// five significant figures
					BigDecimal value = BigDecimal.valueOf(d);
					BigDecimal wantedValue = value.round(new MathContext(5, RoundingMode.HALF_UP));
					writer.write(wantedValue.toString());
				} else if (cell.getCellTypeEnum() == CellType.STRING) {
					writer.write(cell.getStringCellValue());
				} else {
					log.error("unknown XLSX type: " + cell.getCellTypeEnum());
				}
			}
			writer.write(endl);
		}
	}

	public void exportAnnotation(FileWriter writer, Sheet sheet)
			throws IOException {
		SimpleDateFormat tf1 = new SimpleDateFormat("HH:mm:ss.SSS");

		for (int rownum = 1; rownum <= sheet.getLastRowNum(); rownum++) {
			Row xrow = sheet.getRow(rownum);
			Cell cell = xrow.getCell(0);
			// Date dt = cell.getDateCellValue();
			// writer.write(df1.format(dt));
			// ignore for WF
			int seq = 1;
			for (int cellnum = 0; cellnum < xrow.getLastCellNum(); cellnum++) {
				if (cellnum ==1 ) {
					continue; // skip
				}
				if (cellnum > 0 && cellnum < 4) {
					writer.write("\t");
				}
				cell = xrow.getCell(cellnum);
				if (cell == null && cellnum != 2 ) {
					// ignore
				} else if (cellnum == 0) {
					Date dt = cell.getDateCellValue();
					if (dt != null) {
						writer.write(tf1.format(dt));
					}
				} else if (cellnum ==2 ) {
					writer.write("" + seq);
					seq++;
				} else if (cell.getCellTypeEnum() == CellType.NUMERIC) {
					double d = cell.getNumericCellValue();
					// five significant figures
					BigDecimal value = BigDecimal.valueOf(d);
					BigDecimal wantedValue = value.round(new MathContext(5, RoundingMode.HALF_UP));
					writer.write(wantedValue.toString());
				} else if (cell.getCellTypeEnum() == CellType.STRING) {
					writer.write(cell.getStringCellValue());
				} else {
					log.error("unknown XLSX type: " + cell.getCellTypeEnum());
				}
			}
			writer.write(endl);
		}
	}

}
