package idea.datamanager;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;

import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpSubject;
import idea.persistence.PiDatastreamImporter;
import lombok.extern.slf4j.Slf4j;

// import static idea.datamanager.hdf5.H5G_object.*;

@Slf4j
public class ExcelImporter extends AbstractStreamProducer implements PiSubjectImporter {

	private File file;

	// private WaveformBlock nextWave;
	// private NumericsBlock nextNumerics;
	private PersistentItem[] arNext = null;

	// H5DatasetImporter anno;

	private LinkedList<ExcelPageImporter> importers;

	private RpSubject header;

	boolean readOnly;
	long startTime;

	private int headerLines;

	public ExcelImporter(File file) {
		this(file, true);
	}

	public ExcelImporter(File file, boolean readOnly) {
		this.file = file;
		this.readOnly = readOnly;

	}

	@Override
	public void connect() throws IOException {
			importers = new LinkedList<ExcelPageImporter>();
			
			FileInputStream in = new FileInputStream(file);
			Workbook wb = null;
			try {
				wb = new XSSFWorkbook(in);
				
			} catch( Exception ex ) {
				in.close();
				in = new FileInputStream(file);
				wb = new HSSFWorkbook(in);
			}
			in.close();

			int n = wb.getNumberOfSheets();
			for (int i = 0; i < n; i++) {
				Sheet sheet = wb.getSheetAt(i);
				ExcelPageImporter importer = new ExcelPageImporter(sheet);
				importer.setHeaderLines(headerLines);
				importer.connect();
				RpMetric[] metrics = importer.getMetrics();
				if (metrics != null && metrics.length > 0) {
					importers.add(importer);
				}
			}
			readHeader();


	}

	private void readHeader() throws IOException {
		ExcelPageImporter importer = importers.getFirst();
		Sheet sheet = importer.getSheet();
		
		// date/time is expected to be in the first column
		Row row = sheet.getRow(headerLines);

		Cell cell = row.getCell(0);
		Date dt = cell.getDateCellValue();
		Calendar cal = Calendar.getInstance();
		cal.setTime( dt );
		cal.set( Calendar.HOUR, 0 );
		cal.set( Calendar.MINUTE, 0 );
		cal.set( Calendar.SECOND, 0 );
		cal.set( Calendar.MILLISECOND, 0 );

		header = new RpSubject();
		header.setSurgeryDate( cal.getTime() );
		
		return;

	}

	@Override
	public void disconnect() {

		// Close the file.
		try {

			if (importers != null) {
				for (ExcelPageImporter dev : importers) {
					dev.disconnect();
				}
			}

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	@Override
	public long getTimeInMillis() {
		return startTime;
	}


	@Override
	public PersistentItem next() throws IOException {

		if (arNext == null) {
			arNext = new PersistentItem[importers.size()];

			for (int idx = 0; idx < importers.size(); idx++) {
				ExcelPageImporter importer = importers.get(idx);
				try {
					arNext[idx] = importer.next();
				} catch (Exception e) {
					throw new IOException(e);
				}
			}
		}

		PersistentItem ret = null;
		long nextTime = Long.MAX_VALUE;
		int nextPos = 0;
		for (int idx = 0; idx < arNext.length; idx++) {
			PersistentItem m = arNext[idx];
			if (m != null && m.getTime() < nextTime) {
				nextPos = idx;
				nextTime = m.getTime();
				ret = m;
			}
		}

		try {
			if (ret != null) { // if ret is null, then all the importers are out
				// of messages
				ExcelPageImporter importer = importers.get(nextPos);
				if (importer != null) {
					arNext[nextPos] = importer.next();
				}
			}
		} catch (Exception e) {
			throw new IOException(e);
		}

			fireStreamEvent(0,this,StreamID.WAVEFORM, ret);

		return ret;
	}

	@Override
	public RpSubject getSubjectInfo() {
		return header;
	}

	/*
	 * public DeviceConfiguration[] getConfs() {
	 * 
	 * DeviceConfiguration[] ar = null;
	 * 
	 * if ( importers != null && importers.size() > 0) { ar = new
	 * DeviceConfiguration[importers.size()];
	 * 
	 * int idx = 0; for( ImportDevice importer : importers ) { ar[idx++] =
	 * importer.getConfiguration(); } }
	 * 
	 * return ar; }
	 */

	public ExcelPageImporter getDevice(int deviceIdx) {
		ExcelPageImporter device = importers.get(deviceIdx);

		return device;
	}

	public ExcelPageImporter[] getDevices() {
		ExcelPageImporter[] devices = new ExcelPageImporter[importers.size()];

		devices = importers.toArray(devices);
		return devices;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public ArchiveMetaData getMetaData() throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void rewind() throws IOException {
		// TODO Auto-generated method stub

	}

	@Override
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid ) {
		if( importers == null || importers.size() == 0 ) {
			return null;
		}
		ExcelPageImporter found = null;
		for ( ExcelPageImporter importer : importers ) {
			if( name.equals(importer.getName())) {
				found = importer;
				break;
			}
		}
		
		if( sid != StreamID.MEASUREMENT ) {
			log.error("Unexpected SID {} != MEASUREMENT", sid );
		}
		return found;
	}

	public void setHeaderLines(int headerLines ) {
		this.headerLines = headerLines;
	}

	@Override
	public void seek(long startTime) throws IOException {
		// TODO Auto-generated method stub
		
	}

}
