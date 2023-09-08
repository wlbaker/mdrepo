package idea.persistmanager.dbf;

import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.util.Collection;
import java.util.Date;
import java.util.List;

import idea.conf.DeviceConfiguration;
import idea.intf.AbstractStreamProducer;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;
import net.iryndin.jdbf.core.DbfField;
import net.iryndin.jdbf.core.DbfFieldTypeEnum;
import net.iryndin.jdbf.core.DbfMetadata;
import net.iryndin.jdbf.core.DbfRecord;
import net.iryndin.jdbf.reader.DbfReader;

@Slf4j
public class DBFTableReader extends AbstractStreamProducer implements PiDatastreamImporter {

	private static int model_idx = 1;

	private Class<? extends PersistentItem> modelClass;
	private File f;

	DbfReader reader;

	private StreamID sid = null;

	private RpMetric[] metrics;

	private String name;

	private long start;

	public DBFTableReader(File f) {
		this.f = f;
		
		name = f.getName();
		int idx = name.indexOf('.');
		if( idx > 0 ) {
			name = name.substring(0,idx);
		}
				
	}

	@Override
	public void connect() throws IOException {
		// super.connect(datasetName);
		reader = new DbfReader(f);

		DbfMetadata meta = reader.getMetadata();
		Collection<DbfField> fields = meta.getFields();

		RpStream stream = new RpStream();
		for (DbfField field : fields) {
			RpMetric metric = buildMetric(field);
			stream.getMetric().add(metric);
		}
		DeviceConfiguration conf = new DeviceConfiguration(DBFTableReader.class);
		conf.addStream(stream);

		List<RpMetric> sm = stream.getMetric();
		metrics = new RpMetric[sm.size()];
		metrics = sm.toArray(metrics);
		
		/*
		 * Check to see what types of variables we have.  A String is an indicator that this dataset
		 * is an ANNOTATION dataset
		 */
		sid = StreamID.MEASUREMENT;
		boolean haveTS = false;
		boolean haveSTR = false;
		for( RpMetric m : metrics ) {
			if( "timestamp".equalsIgnoreCase(m.getLocation() ) ) {
				// somewhat expected
				haveTS = true;
			} else if( m.getSubtyp() == DataTyp.STRING_TYP ) {
				// call this an annotation
				haveSTR = true;
				break; // only need one string to make the decision
			}
		}
		
		if( haveTS && haveSTR ) {
			sid = StreamID.ANNOTATION;
		}

		modelClass = ModelUtil.findCachedModel(sm);

		if (modelClass == null) {

			String modelName = "idea.model.auto.DBFAuto" + name + model_idx;
			model_idx++;

			try {
				modelClass = ModelUtil.createDynamicModel(modelName, sm);
			} catch (Exception e) {
				log.error("could not creating dynamic model", e);
			}
		}
	}

	private RpMetric buildMetric(DbfField field) {
		DbfFieldTypeEnum typ = field.getType();
		int subtyp = -1;
		switch (typ) {
		case Character:
			subtyp = DataTyp.STRING_TYP;
			break;
		case Double:
			subtyp = DataTyp.DOUBLE_TYP;
			break;
		case Float:
			subtyp = DataTyp.FLOAT_TYP;
			break;
		case Integer:
			subtyp = DataTyp.INT_TYP;
			break;
		case L7Double:
			subtyp = DataTyp.DOUBLE_TYP;
			break;
		case L7Timestamp:
			subtyp = DataTyp.LONG_TYP;
			break;
		default:
			log.error("INVALID DATA TYP: {} in file {}", typ, f);

		}

		RpMetric metric = new RpMetric(field.getName(), null, null, RpLinearUnit.unit, subtyp);
		if (typ == DbfFieldTypeEnum.Character) {
			metric.setSamplesPerPacket( field.getLength() );  // FIXME: shouldnt this be everybody???
		}
		return metric;
	}

	@Override
	public PersistentItem next() throws IOException {
		DbfRecord rec = reader.read();
		if( rec == null ) {
			return null;
		}
		PersistentItem item = decode(rec);
		Object o = IntfUtil.getRawValueByLoc(item, "Timestamp");
		if( o == null ) {
			o = IntfUtil.getRawValueByLoc(item, "TimeStamp");
		}
		Double tso = 0.0;
		if( o != null ) {
			if( o instanceof Double ) {
				tso = (Double)o;
			}
		}
		item.setTime( start + (long)(tso * 1000));
		return item;
	}

	private PersistentItem decode(DbfRecord rec) {
		if (rec == null) {
			return null;
		}

		PersistentItem item = ModelUtil.getModelFromDataClass(modelClass);

		for (DbfField field : rec.getFields()) {
			String name = field.getName();
			Object val = null;
			switch (field.getType()) {
			case Character:
				val = rec.getString(name);
				break;
			case L7Double:
				val = rec.getDouble(name);
				break;
			case Integer:
				val = rec.getInteger(name);
				break;
			case Numeric:
				val = rec.getBigDecimal(name);
				break;
			case Date:
				try {
					val = rec.getDate(name);
				} catch (ParseException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				break;
			case Logical:
				val = rec.getBoolean(name);
				break;

			case L7Timestamp:
				val = rec.getL7Timestamp(name);
				break;
			default:
				System.err.println("How to handle typ: " + field.getType());

				break;
			}
			if (val != null) {
				IntfUtil.setValue(item, name, val);
			}
			
			if( "timestamp".equalsIgnoreCase(name)) {
				item.setTime( ((Double)val).longValue() );
			}
		}
		return item;
	}

	public void rewind() throws IOException {
		reader.findFirstRecord();
	}

	@Override
	public String getName() {
		return name;
	}

	public PersistentItem read(int pos) {
		PersistentItem message = null;
		try {
			message = next();
		} catch (NullPointerException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return message;
	}

	public void skip(int count) {
		reader.skip(count);
	}

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {
		if (!sid.equals(this.sid)) {
			return null;
		}
		return modelClass;
	}

	@Override
	public StreamID[] getStreams() {
		return new StreamID[] { sid };
	}

	@Override
	public RpDevice getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	public StreamID getStreamID() {
		return sid;
	}

	public RpMetric[] getMetrics() {
		return metrics;
	}

	@Override
	public ArchiveMetaData getMeta() throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void seek(long startTime) throws IOException {
		// TODO Auto-generated method stub

	}

	@Override
	public void disconnect() throws IOException {
		// TODO Auto-generated method stub

	}

	public void setStartTime(Date start) {
		this.start = start.getTime();
	}
	public static void main(String[] argv) throws IOException {

		System.out.println("CURRTIME=" + System.currentTimeMillis());
		// File dir = new File("/opt/study/hse/checked MSC/Pig_3144/EXP_DATA_Pig_3144_BL_PV");
		// File dir = new File("/opt/study/data-HSE/HSE/DATA/MSC/Pig_3486/EXP_DATA_Pig_3486_BL");
		// File dir = new File("/opt/study/hse/Pig_3062/EXP_DATA_Pig_3062_BL_PV");
		// File dir = new File("/opt/study/data-HSE/HSE/DATA/MSC/Pig_3486/EXP_DATA_Pig_3486_BL");
		File dir = new File("/opt/study/hse/checked MSC/Pig_3061/EXP_DATA_Pig_3061_BL_EP");
		for (File f : dir.listFiles()) {
			String name = f.getName();
			if (!name.endsWith("DBF")) {
				// only open DBF files
				continue;
			}
			//			if (!name.equals("TIMEPATTERN.DBF")) {
			//				// only this one file
			//				continue;
			//			}
			System.out.println("FILE: " + f);
			DBFTableReader importer = new DBFTableReader(f);
			importer.connect();

			do {
				PersistentItem item = importer.next();
				if (item == null) {
					break;
				}
				for (RpMetric metric : item.getMetrics()) {
					System.out.print("[");
					System.out.print(metric.getLocation());
					System.out.print(":");
					System.out.print(IntfUtil.getRawValue(item, metric));
					System.out.print("]");
				}
				System.out.println();
			} while (true);

			importer.disconnect();
		}
	}

}
