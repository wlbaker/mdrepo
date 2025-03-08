package idea.persistmanager.sql;

import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityTransaction;
import jakarta.persistence.Table;

import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.PiSubjectExporter;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;

// import org.apache.commons.beanutils.PropertyUtils;

@Slf4j
public class SQLExporter implements PiSubjectExporter {

	private RpSubject header;
	private String auth;
	List<RpDevice> devs = new LinkedList<RpDevice>();
	private boolean connected;
	private String persistentUnit;
	
	volatile private MetaTally tally;

	public SQLExporter(String persistentUnit, String auth) {
		this.persistentUnit = persistentUnit;
		this.auth = auth;

	}

	@Override
	public void addDevice(RpDevice dev) throws IOException {
		devs.add(dev);

		if (connected) {
			addMeta(dev);
		}
	}

	@Override
	public void connect() throws IOException {

		JpaUtil.init(persistentUnit, auth);

		for (RpDevice dev : devs) {
			addMeta(dev);
		}

		putHeader();

		connected = true;
	}

	private void putHeader() {
		if (header == null) {
			return;
		}

		try {

			EntityManager em = JpaUtil.getEntityManager();
			EntityTransaction tx = em.getTransaction();

			tx.begin();
			if( tally == null ) {
				tally = new MetaTally( header.getBranch(), header.getMedicalId(), header.getSurgeryDate(), -1.0 );
				em.persist(tally);
			}
			
			long tallyOID = tally.getOid();
			em.persist(new MetaKV(tallyOID, "company", header.getCompany()));
			em.persist(new MetaKV(tallyOID,"organization", header.getOrganization()));
			em.persist(new MetaKV(tallyOID,"studyTitle", header.getStudyTitle()));

			em.persist(new MetaKV(tallyOID,"location", header.getLocation()));
			em.persist(new MetaKV(tallyOID,"sampleDate", "" + header.getSurgeryDate()));
			em.persist(new MetaKV(tallyOID,"subjectNumber", header.getSeqNo()));

			em.persist(new MetaKV(tallyOID,"medicalId", header.getMedicalId()));
			em.persist(new MetaKV(tallyOID,"operator", header.getOperator()));
			em.persist(new MetaKV(tallyOID,"notes", header.getNotes()));
			tx.commit();

		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	private void addMeta(RpDevice dev) {
		EntityManager em = JpaUtil.getEntityManager();

		String dev_name = dev.getName();

		EntityTransaction tr = em.getTransaction();
		tr.begin();
		for (RpStream stream : (List<? extends RpStream>)dev.getStreams()) {
			String table_name = getTableName(stream);
			int seq = 0;
			StreamID sid = StreamID.fromName(stream.getName());
			int scode = sid.getCode();

			MetaStream s = new MetaStream(tally.getOid(), dev_name, table_name, scode, stream);
			em.persist(s);
			for (RpMetric m : (List<? extends RpMetric>)stream.getMetric()) {
				MetaColumn l = new MetaColumn(tally.getOid(), table_name, scode, seq++, m);
				em.persist(l);
			}
		}

		tr.commit();
		em.close();
	}

	private String getTableName(RpStream stream) {

		/*
		 * the table name is in the entity "@Table" annotation, but assume class name
		 * if not found, which is the same behavior as JPA.
		 * 
		 * The exporter should have this class!
		 * 
		 */
		String cl_name = stream.getModel();
		String tableName = cl_name;
		if (cl_name != null) {
			try {
				Class<?> cl = Class.forName(cl_name);
				Table t = cl.getAnnotation(Table.class);
				if (t != null) {
					tableName = t.name();
				}
			} catch (ClassNotFoundException e) {
				log.error("no table for class", e);
			}

		}
		return tableName;
	}

	@Override
	public void disconnect() throws IOException {
		JpaUtil.close();

		connected = false;
	}

	@Override
	public void setHeader(RpSubject header) {
		this.header = header;
		
		if( connected ) {
			putHeader();
		}
	}

	@Override
	public void setDestination(File archiveDir) {
		// Well...not used by SQL...maybe should be destination database?

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		persist( item , true);
	}
	
	private void persist( PersistentItem item, boolean retry ) {
		EntityManager em = JpaUtil.getEntityManager();
		EntityTransaction tx = em.getTransaction();
		
		boolean register_and_retry = false;

		if( tally != null ) {
			item.setTallyOID(tally.getOid()); // this should come from the header!
		}
		
		item.setDeviceLoc("ROOM_id"); // also from the header
		try {
			tx.begin();
			em.persist(item);
			tx.commit();
		} catch (Exception ex) {
			// sqlite can generate a RollbackException when the database is locked, we log and ignore.
			log.error("Commit error", ex);
			String message = ex.getMessage();
			if( message.startsWith("Unknown entity")) {
				register_and_retry = true;
			}
		} finally {

			em.close();
		}
		
		if( register_and_retry && retry ) {
			
			JpaUtil.resetEntityManagerFactory();  // new object in classpath since last emf create
			persist(item, false);
		}

	}

}
