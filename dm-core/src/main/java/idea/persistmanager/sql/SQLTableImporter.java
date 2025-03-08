package idea.persistmanager.sql;

import java.io.IOException;
import java.util.Iterator;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Query;

import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.schema.rp.RpDevice;

class SQLTableImporter extends AbstractStreamProducer  implements PiDatastreamImporter {

	private Class<? extends PersistentItem> clazz;
	private String name;
	
	private EntityManager em;
	private EntityManagerFactory emf;
	private Query q;
	private Iterator ii;
	private StreamID sid;

	public SQLTableImporter(EntityManagerFactory emf, String name, StreamID sid, Class<? extends PersistentItem> clazz) {
		this.emf = emf;
		this.name = name;
		this.clazz = clazz;
		this.sid = sid;
	}

	@Override
	public PersistentItem next() throws IOException {
		if ( em == null ) {
			em = emf.createEntityManager();
			// q = em.createNamedQuery("from " + name + " order by tm");
			q = em.createQuery("from " + name + " order by tm");
			ii = q.getResultList().iterator();
		}
		PersistentItem item = null;
		if( ii.hasNext() ) {
			item = (PersistentItem) ii.next();
		}
		
		return item;
	}

	@Override
	public void rewind() throws IOException {
		// TODO Auto-generated method stub
		
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
	public void connect() throws IOException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void disconnect() throws IOException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public String toString() {
		
		return this.clazz + "[" + name + "]";
	}

	@Override
	public Class<? extends PersistentItem> getModel(StreamID sid) {
		if( !sid.equals(this.sid)) {
			return null;
		}
		return clazz;
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

}
