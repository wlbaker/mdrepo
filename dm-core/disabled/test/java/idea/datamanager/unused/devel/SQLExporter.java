package idea.datamanager.unused.devel;

import idea.conf.DeviceConfiguration;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.persistence.StudyDefinition;
import idea.persistmanager.sql.JpaUtil;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.Date;
import java.util.EventObject;

import javax.persistence.EntityManager;

import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpSubject;


@Slf4j
public class SQLExporter implements PiSubjectExporter {

	private StudyDefinition header;
	String auth;

	public SQLExporter( StudyDefinition header, String auth ) {
		this.header = header;
		this.auth = auth;
	}

	public void addDevice(DeviceConfiguration conf) throws IOException {
		log.error("addDevice not supported");
	}

	@Override
	public void connect() throws IOException {
		JpaUtil.init(null,auth);
		
	}


	private String buildSourceName(StreamProducer source, String srcName) {
		RpDevice conf = null;
		if( source != null ) {
			conf = source.getConfiguration();
		}
		if( conf != null ) {
			srcName = conf.getDriverName();
		}
		return srcName;
	}

	private Field setSimpleProperty(Class c, String itName) {
		String methodName = "set" + itName;  
		return null;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setHeader(RpSubject header) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setDestination(File archiveDir) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void disconnect() throws IOException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void addDevice(RpDevice conf) throws IOException {
		// TODO Auto-generated method stub
		
	}


}
