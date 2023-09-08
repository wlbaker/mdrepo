package idea.datamanager;

import java.io.IOException;
import java.util.Arrays;
import java.util.Date;
import java.util.LinkedList;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellType;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;

import icuInterface.RpUtil;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.AdapterInterface;
import idea.intf.DataTyp;
import idea.intf.StreamConsumer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ExcelPageImporter extends AbstractStreamProducer implements PiDatastreamImporter, AdapterInterface {

	private static final int TS_COL = 0;
	private static final int INTERVAL_COL = 1;

	ArchiveMetaData meta;

	private PersistentItem currNdb;

	DeviceConfiguration conf;

	private Sheet sheet;

	private int curr_row;
	boolean header;
	private int headerLines = 1;
	private Class<? extends PersistentItem> model;
	private static int rev;

	public ExcelPageImporter(Sheet sheet) {

		this.sheet = sheet;
		this.conf = new DeviceConfiguration((DeviceConfiguration)null);

		conf.setName(sheet.getSheetName());
		conf.setDriverName("Excel");

	}

	public Sheet getSheet() {
		return sheet;
	}

	@Override
	public void connect() throws IOException {

		LinkedList<RpMetric> metrics_list = new LinkedList<RpMetric>();

		curr_row = headerLines - 1;
		if (curr_row < 0) {
			curr_row = 1;
		}

		currNdb = null;

		Row row = sheet.getRow(curr_row);
		if (row == null) {
			return; // no data in first row....not our file
		}

		int tot = row.getLastCellNum();

		int cols = 0;
		header = false;

		for (int col = 0; col < tot; col++) {

			Cell cell = row.getCell(col);
			if (cell == null) {
				// end of the data
				break;
			}

			if (col == TS_COL) {
				// expecting timestamp here
				continue;
			}

			if (col == INTERVAL_COL) {
				header = (cell.getCellType() == CellType.STRING);
			}

			String title = "COL" + cols;
			if (header) {
				title = cell.getStringCellValue();
			}
			String unit = "s";
			if (col == 1) {
				unit = "ms";
			} else if (col > 1) {
				unit = "N/A";
			}
			RpLinearUnit lin = new RpLinearUnit( 1.0, 0, unit );
			RpMetric metric = RpUtil.createRpMetric(title, title, title, lin, DataTyp.INT_TYP);
			metrics_list.add(metric);

			cols++;
		}

		if (header) { // data starts on the next row
			curr_row++;
		}

		try {
			model = ModelUtil.createDynamicModel("ExcelImporter" + rev, metrics_list );
			currNdb = ModelUtil.getModelFromDataClass(model);
			
			RpStream s = new RpStream();
			s.setName( StreamID.MEASUREMENT.getName() );
			s.getMetric().addAll( Arrays.asList(IntfUtil.getMetrics(model)) );

			conf.addStream( s );
		} catch (Exception e) {
			log.error("Could not create importer model.", e);
		}
		rev++;
				
	}

	@Override
	public void disconnect() throws IOException {

	}

	public void rewind() {
		curr_row = 0;
		if (header) {
			curr_row += headerLines;
		}
	}

	public PersistentItem next() throws IOException {
		return _next();
	}

	public PersistentItem _next() throws IOException {

		if (currNdb != null) {
			currNdb.setDriver(this);
		}

		Row row = sheet.getRow(curr_row++);
		if (row == null) {
			return null; // no data in first row....not our file
		}

		Cell cell = row.getCell(TS_COL);
		if (cell.getCellType() == CellType.BLANK) {
			cell = null;
		}
		if (cell == null || cell.getCellType() != CellType.NUMERIC) {
			return null;
		}

		long tm = (long)cell.getNumericCellValue();
		if( tm > 30000 ) {
			// WARNING: not a really good approach!
			Date dt = cell.getDateCellValue();
			currNdb.setTime( dt.getTime() );
		} else {
			// expecting ts in sec...convert to ms
			tm = (long) (cell.getNumericCellValue() * 1000.0); 
			currNdb.setTime(tm);
		}

		int col = 1;
		RpMetric[] items = IntfUtil.getMetrics(currNdb);
		for (RpMetric it : items) {
			cell = row.getCell(col++);
			if (cell != null && cell.getCellType() == CellType.BLANK) {
				cell = null;
			}
			if (cell != null) {
				IntfUtil.setScaledValue(currNdb, it, cell.getNumericCellValue());
			}
		}

		return currNdb;
	}

	@Override
	public DeviceConfiguration getConfiguration() {
		return conf;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return null;
	}

	@Override
	public void removeStreamListener(StreamConsumer eventListener) {
		assert (false) : "not implemented / not used addEventListener / TODO ";
	}

	@Override
	public int tick() {
		// ignore
		return 0;
	}

	@Override
	public ArchiveMetaData getMeta() throws IOException {
		if (meta != null) {
			return meta;
		}
		meta = new ArchiveMetaData();

		ArchiveMetaData metric_meta = new ArchiveMetaData();

		if (meta.getStartTime() == null)
			meta.setStartTime(metric_meta.getStartTime());
		if (meta.getStopTime() == null)
			meta.setStopTime(metric_meta.getStopTime());

		if (meta.getStartTime() != null && metric_meta.getStartTime() != null) {
			if (meta.getStartTime().getTime() > metric_meta.getStartTime().getTime()) {
				meta.setStartTime(metric_meta.getStartTime());
			}
		}

		if (meta.getStopTime() != null && metric_meta.getStopTime() != null) {
			if (meta.getStopTime().getTime() < metric_meta.getStopTime().getTime()) {
				meta.setStopTime(metric_meta.getStopTime());
			}
		}

		return meta;
	}

	@Override
	public void seek(long startTime) throws IOException {

	}

	public void setHeaderLines(int headerLines) {
		this.headerLines = headerLines;
	}

	@Override
	public String getName() {
		return sheet.getSheetName();
	}

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {
		if( sid == StreamID.MEASUREMENT) {
			return model;
		}
		return null;
	}

	@Override
	public StreamID[] getStreams() {
		return new StreamID[] { StreamID.MEASUREMENT};
	}

	RpMetric[] getMetrics() {
		return IntfUtil.getMetrics( model );
	}

}
