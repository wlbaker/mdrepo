package idea;

// SEE:
//   http://stackoverflow.com/questions/4370225/custom-classloader-for-hibernate-mapping
//   http://docs.jboss.org/hibernate/core/3.6/reference/en-US/html/persistent-classes.html#persistent-classes-tuplizers
	
import java.util.Arrays;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

import icuInterface.RpUtil;
import idea.intf.DataTyp;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.persistmanager.sql.JpaUtil;

public class TestJPA {
	
	private static RpMetric[] namesToFields(String [] fieldNames ) {
		RpMetric[] fields = new RpMetric[fieldNames.length];

		RpLinearUnit linear = new RpLinearUnit();
		linear.setM(1);
		linear.setB(0);
		linear.setUnitName("");

		int idx = 0;
		for (String name : fieldNames) {
			RpMetric md = RpUtil.createRpMetric(name, name, null, linear, DataTyp.FLOAT_TYP);
			fields[idx++] = md;
		}
		return fields;
	}


	public static void main(String [] args) throws Exception {
		
		String [] names = { "COL1", "COL2" };
		RpMetric[] fields = namesToFields( names );
		
		Class<? extends PersistentItem> cl = ModelUtil.createDynamicModel("idea.model.auto.ZZEnt",  Arrays.asList(fields) );

		JpaUtil.init("exporterSQLite", "jdbc:sqlite:/tmp/filezz0.db");
		
		EntityManagerFactory emf = JpaUtil.getEntityManagerFactory(); 
		EntityManager em = emf.createEntityManager();
		
		PersistentItem entity = ModelUtil.getModelFromDataClass(cl);
		em.getTransaction().begin();
		em.persist(entity);
		em.getTransaction().commit();
		
		em.close();
		
		
	}
}