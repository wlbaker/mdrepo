package idea.repository;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class DaqUtil {
	private static final int BINARY_FLAG = 0x10;
	private static final int VITALS_TYPE = 0x01;
	private static final int WAVEFORM_TYPE = 0x02;
	private static final int NOTES_TYPE = 0x03;
	private static final int LAB_TYPE = 0x04;

	private static DateFormat vitals_df = new SimpleDateFormat("MMMMM dd, yyyy");
	private static DateFormat vitals_tmf = new SimpleDateFormat("HH:mm:ss");
	private static int sampleRate;

	private static Date parseVitalsReportDate(String line) {
		int pos = line.indexOf(',');
		line = line.substring(pos + 2);

		Date dout = null;
		try {
			dout = vitals_df.parse(line);
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return dout;
	}

	private static Date parseGuyDrewDate(String line) {
		int pos = line.indexOf(',');
		line = line.substring(pos + 2);
		pos = line.indexOf(':');

		String dt = line.substring(0, pos - 1);
		String tm = line.substring(pos + 1);

		dt = dt.trim();
		tm = tm.trim();

		line = dt + " " + tm;

		DateFormat df = new SimpleDateFormat("MMMMM dd, yyyy HH:mm:ss");

		Date dout = null;
		try {
			dout = df.parse(line);
		} catch (ParseException e) {
			log.error("Could not parse GD date: {}", line);
		}
		// Calendar cal = Calendar.getInstance();
		// cal.setTimeInMillis( Date.parse(line) );
		return dout;
	}

	public static RpSubject readDaqHeader(File f) throws IOException {
		RpSubject subject = null;
		FileReader reader = null;
		try {
			reader = new FileReader(f);
			subject = readDaqHeader(new BufferedReader(reader));
			subject.setBaseFileName(f.getName());
		} finally {
			if (reader != null)
				try {
					reader.close();
				} catch (IOException e) {
					// error already given
				}
		}
		return subject;
	}

	public static RpSubject readDaqHeader(SeekableByteChannel sbc, ByteBuffer bb) throws IOException {
		sampleRate = 0;

		String workstation = readLine(sbc,bb);
		if (!workstation.startsWith("Dynamic Research Evaluation Workstation")) {
			log.error("File is not DRE format");
			return null;
		}
		RpSubject header = new RpSubject();

		String recording = readLine(sbc,bb); // with version v4.67
		if (parseRecording(header, recording) == 0) {
			String line = readLine(sbc,bb);
			header.setSurgeryDate(parseVitalsReportDate(line));

			readLine(sbc,bb); // empty line
			return header;
		}

		String dataFormat = readLine(sbc,bb);
		parseHeaderLine(header, dataFormat);

		Date dt = parseGuyDrewDate(readLine(sbc,bb));
		header.setSurgeryDate(dt);

		readLine(sbc,bb); // blank line
		do {
			String line = readLine(sbc,bb).trim();
			if (line.length() == 0) {
				// next line is column headers
				break;
			}

			parseHeaderLine(header, line);

		} while (true);
		
		return header;
	}

	public static String readLine(SeekableByteChannel sbc, ByteBuffer bb) throws IOException {
		String line = null;
		StringBuffer buf = new StringBuffer();
		do {
			byte b = bb.get();
			if( b == '\n') {
				line = buf.toString();
				break;
			}
			if( b == '\r') {
				// ignore
			} else {
				buf.append( (char) b);
			}
		} while( true );

		return line;
	}

	@Deprecated
	public static RpSubject readDaqHeader(BufferedReader reader) throws IOException {

		sampleRate = 0;
		String workstation = reader.readLine();
		if (!workstation.startsWith("Dynamic Research Evaluation Workstation")) {
			log.error("File is not DRE format");
			return null;
		}
		RpSubject header = new RpSubject();

		String recording = reader.readLine(); // with version v4.67
		if (parseRecording(header, recording) == 0) {
			String line = reader.readLine();
			header.setSurgeryDate(parseVitalsReportDate(line));

			reader.readLine(); // empty line
			return header;
		}

		String dataFormat = reader.readLine();
		parseHeaderLine(header, dataFormat);

		Date dt = parseGuyDrewDate(reader.readLine());
		header.setSurgeryDate(dt);

		reader.readLine(); // blank line
		do {
			String line = reader.readLine().trim();
			if (line.length() == 0) {
				// next line is column headers
				break;
			}

			parseHeaderLine(header, line);

		} while (true);
		return header;
	}

	/*
	 * * EXACT DUPLICATE OF ROUTINE ABOVE...only RandomAccessFile and BufferedReader don't share a common readLine()
	 * ancestor
	 */

	@Deprecated
	public static RpSubject readDaqHeader(RandomAccessFile reader) throws IOException {

		sampleRate = 0;
		String workstation = reader.readLine();
		if (!workstation.startsWith("Dynamic Research Evaluation Workstation")) {
			log.error("File is not DRE format");
			return null;
		}
		RpSubject header = new RpSubject();

		String recording = reader.readLine(); // with version v4.67
		if (parseRecording(header, recording) == 0) {
			
			String line = reader.readLine();
			Date dt = parseVitalsReportDate(line);
			header.setSurgeryDate( dt);

			reader.readLine(); // empty line
			long pos = reader.getFilePointer();
			String colNames = reader.readLine(); // ignore
			String firstDataLine = reader.readLine(); // ignore
			String [] arr = firstDataLine.split("\t");
			if( arr != null && arr.length > 1 ) {
				Date tm;
				try {
					tm = vitals_tmf.parse(arr[0]);
					dt.setHours( tm.getHours() );
					dt.setMinutes( tm.getMinutes() );
					dt.setSeconds( tm.getSeconds() );
					header.setSurgeryDate( dt );
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			reader.seek(pos);
			return header;
		}

		String dataFormat = reader.readLine();
		parseHeaderLine(header, dataFormat);

		String drewDate = reader.readLine();
		Date dt = parseGuyDrewDate( drewDate );
		header.setSurgeryDate(dt);

		reader.readLine(); // expecting a BLANK line
		do {
			String line = reader.readLine();
			line = line.trim();  // if the DAT file was written by Excel, then it probably has trailing TABS
			if (line.length() == 0) {
				// next line is column headers
				break;
			}

			parseHeaderLine(header, line);

		} while (true);
		return header;
	}

	private static int parseRecording(RpSubject header, String recording) {
		if (recording.startsWith("Vitals Report")) {
			header.setDataType(VITALS_TYPE);

			return 0;
		} else if (recording.startsWith("Analog Waveform")) {
			header.setDataType(WAVEFORM_TYPE);
		} else if (recording.startsWith("Electronic Lab Book")) {
			header.setDataType(LAB_TYPE);
		} else if (recording.startsWith("Notes and Comments")) {
			header.setDataType(NOTES_TYPE);
		} else {
			log.error("Unknown recording: {}", recording);
		}

		return 1;
	}

	private static void parseHeaderLine(RpSubject header, String line) {
		int idx = line.indexOf(':');

		if (idx < 2) {
			log.error("Unexpected line: {}", line);
			return;
		}

		String key = line.substring(0, idx).trim();
		String value = "";
		if (idx < line.length() - 1) {
			value = line.substring(idx + 1).trim();
		}

		if ("Company Name".equals(key)) {
			header.setCompany(value);
		} else if ("Organization".equals(key)) {
			header.setOrganization(value);
		} else if ("Location".equals(key)) {
			header.setLocation(value);
		} else if ("Study Title".equals(key)) {
			header.setStudyTitle(value);
		} else if ("Surgery Date".equals(key) || key.startsWith("Sugery Date")) {
			// yes, possible mispelling
			if (header.getSurgeryDate() != null) {
				// already set with a more precise date
			} else {
				// second best
				int pos = value.indexOf(",");
				if (pos < 0) {
					log.error("could not recognize date: ", value);
				} else {
					value = value.substring(pos + 2);
					try {
						Date dt = vitals_df.parse(value);
						header.setSurgeryDate(dt);
					} catch (ParseException e) {
						log.error("error parsing vitals date: ", value);
					}
				}
			}
		} else if ("Subject Number".equals(key)) {
			header.setSubject(value);
			header.setIdentifier(value);
		} else if ("Medical ID".equals(key)) {
			header.setMedicalId(value);
		} else if ("DAQ Operator(s)".equals(key)) {
			header.setOperator(value);
		} else if ("Base File Name".equals(key)) {
			header.setBaseFileName(value);
		} else if ("Sequence Number".equals(key)) {
			header.setSeqNo(value);
		} else if ("Sample Rate".equals(key)) {
			// header.setSampleRate(Integer.parseInt(value));
			sampleRate = Integer.parseInt(value);
		} else if ("Notes".equals(key)) {
			header.setNotes(value);
		} else if ("Subset Format".equals(key) || "Data Format".equals(key)) {
			if (line.indexOf("Scaled ASCII") > 0) {
				// Subset Format : Scaled ASCII (TXT)
				// header.setProperty( "subformat", "ascii");
				// header.setDataType( );s
			} else if (line.indexOf("Voltage Binary") > 0) {
				// Subset Format : Voltage Binary (SGL)
				// header.setProperty( "subformat", "binary");
				header.setDataType(header.getDataType() + BINARY_FLAG);
			} else if (line.indexOf("SGL") > 0) {
				// Subset Format : Voltage Binary (SGL)
				// header.setProperty( "subformat", "binary");
				header.setDataType(header.getDataType() + BINARY_FLAG);
			} else {
				log.error("unrecognized subset format: " + line);
			}

		} else {
			log.error("Unrecognized key/value: {}/{}", key, value);
		}
	}

	public static int getSampleRate() {
		return sampleRate;
	}


}
