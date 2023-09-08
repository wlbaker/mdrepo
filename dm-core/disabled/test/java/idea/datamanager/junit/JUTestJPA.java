package idea.datamanager.junit;

import idea.model.dev.IstatMeasurement;
import idea.persistmanager.sql.JpaUtil;

import java.util.Date;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;

public class JUTestJPA {

	public static void main(String[] args) {

		JpaUtil.initHibernateLogging();
		JpaUtil.init("managerSQLite", null);

		EntityManager em = JpaUtil.getEntityManager();
		EntityTransaction tx = em.getTransaction();

		IstatMeasurement m = new IstatMeasurement();

		m.setTm(new Date()); // now
		m.setPanel("CG7+");
		m.setField1("bill");

		try {
			//Account m = new Account();
			//m.setZero("zero");

			tx.begin();
			em.persist(m);
			tx.commit();
		} finally {

			em.close();

			JpaUtil.close();
		}
	}

}
