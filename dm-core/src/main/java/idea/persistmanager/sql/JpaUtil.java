/*
 * 
 */

// hibernate 4.3 method to add jpa classes programatically
//properties.put(
//    org.hibernate.jpa.AvailableSettings.LOADED_CLASSES, 
//    Arrays.asList(persistentClasses));
//Persistence.createEntityManagerFactory("persistence-unit", properties);

// Have a look at the HibernateEntityManager and HibernateEntityManagerFactory classes. 
// You can cast entity manager factories and entity managers to them and do the usual hibernate stuff.

package idea.persistmanager.sql;

import java.io.File;
import java.sql.Connection;
import java.sql.DriverManager;
import java.util.HashMap;
import java.util.Map;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.persistence.PersistenceUtil;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;
// import org.hibernate.cfg.Configuration;

import lombok.extern.log4j.Log4j;

public class JpaUtil {

	// private static final SessionFactory sessionFactory;

	private static EntityManagerFactory emf = null;

	private static EntityManager em = null;

	// private static DataSource ds;
	private static String dbUrl = null;

	private static String dbPassword = "3611d55u53r";
	private static String dbUser = "dss_user";

	private static Connection execConn;

	private static String safe_persistanceUnit;

	private static String safe_jdbc;

	public static void unused_init(String persistanceUnit, String jdbc, Class[] classes) {
		System.setProperty("org.jboss.logging.provider", "log4j");

		Map<String, Object> properties = new HashMap<String, Object>();
		properties.put("hibernate.show_sql", true);
		properties.put("hibernate.temp.use_jdbc_metadata_defaults", false);
		properties.put("hibernate.connection.url", jdbc);
		loadDrivers(jdbc);

		// emf = Persistence.createEntityManagerFactory(persistanceUnit, properties );
		// emf.addNamedEntityGraph(graphName, entityGraph);

		// Configuration cfg = new AnnotationConfiguration();
		// emf = cfg.setProperties(properties) //add some properties
		// // .setInterceptor(myInterceptorImpl) // set an interceptor
		// .addAnnotatedClass(SimuSine_Waveform.class) //add a class to be mapped
		// .addAnnotatedClass(SimuSine_Measurement.class) //add a class to be mapped
		// // .addClass( NonAnnotatedClass.class ) //add an hbm.xml file using the Hibernate convention
		// .addRerousce("mypath/MyOtherCLass.hbm.xml") //add an hbm.xml file
		// .addRerousce("mypath/orm.xml") //add an EJB3 deployment descriptor
		// .configure("/mypath/hibernate.cfg.xml") //add a regular hibernate.cfg.xml
		// .buildEntityManagerFactory(); //Create the entity manager factory
		emf = Persistence.createEntityManagerFactory(persistanceUnit, properties);

	}

	public static void init(String persistanceUnit, String jdbc) {

		JpaUtil.safe_persistanceUnit = persistanceUnit;
		JpaUtil.safe_jdbc = jdbc;
		
		System.setProperty("org.jboss.logging.provider", "log4j");

		Map<String, Object> addedOrOverridenProperties = new HashMap<String, Object>();
		addedOrOverridenProperties.put("hibernate.show_sql", "true");
		addedOrOverridenProperties.put("hibernate.temp.use_jdbc_metadata_defaults", false);

		addedOrOverridenProperties.put("hibernate.hbm2ddl.auto", "create");

		if (jdbc == null) {
			String dbFile = "/tmp/testfile1.db";

			File f = new File(dbFile);
			if (!f.exists()) {
				initDatabase(dbFile);
			}

			jdbc = "jdbc:sqlite:" + dbFile;
		}
		addedOrOverridenProperties.put("hibernate.connection.url", jdbc);
		loadDrivers(jdbc);

		// addedOrOverridenProperties.put("jar-file", >file:../target/classes</jar-file>

		// Create the entity manager factory
		PersistenceUtil util1 = Persistence.getPersistenceUtil();
		emf = Persistence.createEntityManagerFactory(persistanceUnit, addedOrOverridenProperties);

	}

	private static String loadDrivers(String jdbc) {
		Connection c = null;
		try {
			if (jdbc.indexOf("sqlite") > 0) {
				Class.forName("org.sqlite.JDBC");
			}
			if (jdbc.indexOf("oracle") > 0) {
				Class.forName("org.ORACLE DRIVER NAME GOES HERE");
			}
			if (jdbc.indexOf("postgres") > 0) {
				Class.forName("org.postgresql.Driver");
			}
		} catch (Exception e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			System.exit(0);
		}
		return "jpaUtilJDBC";
	}

	private static void initDatabase(String dbFile) {
		Connection c = null;
		try {
			Class.forName("org.sqlite.JDBC");
			c = DriverManager.getConnection("jdbc:sqlite:" + dbFile);
			c.close();
		} catch (Exception e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
			System.exit(0);
		}
		System.out.println("Created database successfully");
	}

	/*
	 * spring
	 */
	// @Bean
	// public LocalContainerEntityManagerFactoryBean emf(){
	// properties.put("javax.persistence.jdbc.driver", dbDriverClassName);
	// properties.put("javax.persistence.jdbc.url", dbConnectionURL);
	// properties.put("javax.persistence.jdbc.user", dbUser); //if needed
	//
	// LocalContainerEntityManagerFactoryBean emf = new LocalContainerEntityManagerFactoryBean();
	// emf.setPersistenceProviderClass(org.eclipse.persistence.jpa.PersistenceProvider.class); //If your using eclipse
	// or change it to whatever you're using
	// emf.setPackagesToScan("com.yourpkg"); //The packages to search for Entities, line required to avoid looking into
	// the persistence.xml
	// emf.setPersistenceUnitName(SysConstants.SysConfigPU);
	// emf.setJpaPropertyMap(properties);
	// emf.setLoadTimeWeaver(new ReflectiveLoadTimeWeaver()); //required unless you know what your doing
	// return emfConfigBean;
	// }

	/*
	 * public static Session getSession() { return sessionFactory.openSession(); }
	 * 
	 * public static SessionFactory getSessionFactory() { return sessionFactory; }
	 */

	public static EntityManager getEntityManager() {
		em = getEntityManagerFactory().createEntityManager();

		return em;
	}

	public synchronized static EntityManagerFactory getEntityManagerFactory() {
		return emf;
	}

	public static void setUrl(String url, String user, String password) {
		dbUrl = url;
		dbUser = user;
		dbPassword = password;
	}

	public static Connection getExecutionConnection() {

		try {
			if (execConn == null || execConn.isClosed()) {

				execConn = DriverManager.getConnection(dbUrl, dbUser, dbPassword);

			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		return execConn;
	}

	public static void close() {
		if (emf != null) {
			emf.close();
			emf = null;
		}
	}

	public static void initHibernateLogging() {
		Class<Log4j> c = Log4j.class;
		System.setProperty("org.jboss.logging.provider", "log4j");

		Logger logger = Logger.getLogger("org.hibernate");
		if (logger == null) {
			System.err.println("NO SUCH LOGGER for DEBUG");
		} else {
			logger.setLevel(Level.DEBUG);
			logger.setLevel(Level.WARN);
		}
	}

	public static void resetEntityManagerFactory() {
		close();
		init( safe_persistanceUnit, safe_jdbc );  // we have new objects in the classpath...just maybe...
	}

}
