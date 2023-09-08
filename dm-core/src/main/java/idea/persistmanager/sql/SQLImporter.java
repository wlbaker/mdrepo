package idea.persistmanager.sql;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

//import icuInterface.persistence.ArchiveMetaData;
//import idea.persistence.PiDatastreamImporter;
import idea.conf.DeviceCapabilities;
import idea.intf.AbstractStreamProducer;
import idea.message.StreamID;
import idea.model.ModelUtil;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpPrecisionUnit;
import idea.schema.rp.RpSubject;
import idea.persistence.PiDatastreamImporter;
import javassist.CannotCompileException;
import javassist.NotFoundException;
import lombok.extern.slf4j.Slf4j;

/*
 * possible methods to use:
 * 
 * - Hibernate Interceptor
 * 
 * - Dynamic models (HashMap) see hibernate community documentation section 4.4 of hibernate version 4.3 of manual
 * 
 * - dynamically created classes a la ModelUtil
 * 
 * - Spring configuration
 * - EclipseLink methods
 * - saw reference to HibernateEntityManager and HibernateEntityManagerFactory 
 * that bring JPA closer to native Hibernate and allow more native methods of configuration and extension
 * 
 */
@Slf4j
public class SQLImporter extends AbstractStreamProducer implements PiSubjectImporter {

	private String url;
	private EntityManagerFactory emf;
	private List<SQLTableImporter> tables;

	public SQLImporter(String url) {
		this.url = url;
	}

	@Override
	public void connect() throws IOException {

		Map<String, Object> addedOrOverridenProperties = new HashMap<String, Object>();

		// Let's suppose we are using Hibernate as JPA provider
		// addedOrOverridenProperties.put("hibernate.show_sql", true);
		addedOrOverridenProperties.put("hibernate.dialect", "idea.sqlite.SQLiteDialect");
		addedOrOverridenProperties.put("hibernate.connection.driver_class", "org.sqlite.JDBC");
		addedOrOverridenProperties.put("hibernate.connection.username", "sa");
		addedOrOverridenProperties.put("hibernate.connection.password", "");
		addedOrOverridenProperties.put("hibernate.connection.url", url);
		// addedOrOverridenProperties.put("jar-file", >file:../target/classes</jar-file>

		/*
		addedOrOverridenProperties.put("hibernate.default_schema", "public");
		addedOrOverridenProperties.put("hibernate.hbm2ddl.auto", "update");
		addedOrOverridenProperties.put("hibernate.show_sql", "true");
		addedOrOverridenProperties.put("hibernate.format_sql", "true");
		*/

		List<Class<?>> persistentClasses = null;
		try {
			persistentClasses = createDynamicEntities();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		log.error("FIXME: this method of dynamically loading classes seems to no longer be available");
		log.error("FIXME: also, sqlite hardcoded in this file");
		log.error("addedOrOverridenProperties.put(org.hibernate.jpa.AvailableSettings.LOADED_CLASSES, persistentClasses);");

		// Create the entity manager factory
		// emf = Persistence.createEntityManagerFactory(persistanceUnit, addedOrOverridenProperties );
		emf = Persistence.createEntityManagerFactory("importerSQLite", addedOrOverridenProperties);

		tables = new LinkedList<SQLTableImporter>();
		for (Class clazz : persistentClasses) {
			log.error("FIXME: need to know where to get the sid from!!!!");
			SQLTableImporter table = new SQLTableImporter(emf, clazz.getSimpleName(), StreamID.MEASUREMENT_2, clazz);
			tables.add(table);
		}
	}

	/*
	 * 
	 * http://wiki.eclipse.org/EclipseLink/Examples/JPA/Dynamic
	 * 
		DynamicClassLoader dcl = new DynamicClassLoader(currentLoader);
		 
		Class<?> employeeClass = dcl.createDynamicClass(packagePrefix + "Employee");
		JPADynamicTypeBuilder address = new JPADynamicTypeBuilder(addressClass, null, "D_ADDRESS");
	 */
	private List<Class<?>> createDynamicEntities() throws Exception {

		List<Class<?>> clazzes = new LinkedList<Class<?>>();

		Class.forName("org.sqlite.JDBC");
		System.out.println("Driver Loaded.");

		Connection conn = DriverManager.getConnection(url);
		DatabaseMetaData dbmd = conn.getMetaData();
		String[] types = null; // { "TABLE" };
		ResultSet rs = dbmd.getTables(null, "main", "%", types);
		while (rs.next()) {
			String table = rs.getString("TABLE_NAME");
			String className = "idea.auto." + table;

			Collection<? extends RpMetric> properties = readTableProperties(dbmd, null, table);
			Class<?> clazz = ModelUtil.createDynamicModel(className, properties);
			System.out.println("table: " + table);
			if (clazz != null) {
				clazzes.add(clazz);
			}
		}

		conn.close();

		return clazzes;
	}

	public String targetTypename(String sqlTypename, int typeCode) {
		return sqlTypename;
	}

	private Collection<RpMetric> readTableProperties(DatabaseMetaData metaData, String schema, String tableName)
			throws SQLException {
		LinkedList<RpMetric> fields = new LinkedList<RpMetric>();

		ResultSet columnsMetadata = metaData.getColumns(null, null, tableName, null);
		Set<String> pkNames = new HashSet<String>(3);

		try {
			ResultSet pkResultSet = metaData.getPrimaryKeys(null, null, tableName);
			while (pkResultSet.next()) {
				pkNames.add(pkResultSet.getString(4));
			}

			pkResultSet.close();
		} catch (Exception e) {
			log.warn("Could not determine primary keys; will need to be manually configured", e);
		}

		Set<String> cols = new HashSet<String>();
		StringBuffer sql = new StringBuffer();
		sql.append("CREATE TABLE ");
		if (schema != null) {
			sql.append(schema + ".");
		}
		sql.append(tableName + " (");
		String delim = "";
		boolean has_tm = false;
		while (columnsMetadata.next()) {

			String columnName = columnsMetadata.getString(4);
			if (cols.contains(columnName)) {
				// System.err.println("skipping duplicate: " + tableName + "/" + columnName );
				continue;
			}
			sql.append(delim);
			delim = ", ";

			cols.add(columnName);
			String sqlTypename = columnsMetadata.getString(6);
			int typeCode = columnsMetadata.getInt(5);
			String targetTypename = targetTypename(sqlTypename, typeCode);
			if (targetTypename == null) {
				log.info("Unknown typename for type code " + typeCode + "; SQL type name is " + sqlTypename);
				continue;
			}
			int columnSize = 0;
			if (!"DATE".equals(sqlTypename)) {
				columnSize = columnsMetadata.getInt(7);
			}
			boolean nullsProhibited = "NO".equalsIgnoreCase(columnsMetadata.getString(18));
			int precision = columnsMetadata.getInt(9);

			if (columnName.equalsIgnoreCase("tm")) {
				System.err.println("skipping tm...found in superclass: " + tableName);
				has_tm = true;
			} else if (columnName.equalsIgnoreCase("dev_loc")) {
				System.err.println("skipping dev_loc...found in superclass: " + tableName);
				has_tm = true;
			} else if (columnName.equalsIgnoreCase("patient_oid")) {
				System.err.println("skipping patient_oid...found in superclass: " + tableName);
				has_tm = true;
			} else if (columnName.equalsIgnoreCase("oid")) {
				System.err.println("skipping oid...found in superclass: " + tableName);
				has_tm = true;
			} else {
				RpMetric desc = appendFieldCreationClause(sql, columnName, targetTypename, columnSize,
						precision, nullsProhibited, pkNames.contains(columnName), metaData.getIdentifierQuoteString(),
						columnsMetadata);
				fields.add(desc);
			}
		}
		sql.append(");");

		columnsMetadata.close();
		System.out.println(sql.toString());

		if (has_tm == false) {
			System.err.println("TM NOT FOUND...not a PersistentItem!");
		}
		return fields;
	}

	public RpMetric appendFieldCreationClause(StringBuffer buffer, String columnName, String targetTypename,
			int columnSize, int precision, boolean nullsProhibited, boolean isPrimaryKey, String identifierQuoteString,
			ResultSet columnMetaData) {

		if (isPrimaryKey) {
			targetTypename = "INT";
			precision = 0;
		}
		buffer.append(identifierQuoteString + columnName + identifierQuoteString + " " + targetTypename);
		if (columnSize > 0) {
			buffer.append("(" + columnSize);
			if (precision > 0) {
				buffer.append("," + precision);
			}
			buffer.append(")");
		}
		if ("id".equalsIgnoreCase(columnName)) {
			buffer.append(" UNIQUE");
		}
		if (nullsProhibited) {
			buffer.append(" NOT NULL");
		}
		if (isPrimaryKey) {
			buffer.append(" AUTO_INCREMENT");
			buffer.append(" PRIMARY KEY");
		}

		RpMetric metric = new RpMetric();
		metric.setLocation(columnName);
		metric.setCode(columnName);
		metric.setUnit( new RpPrecisionUnit(precision, ""));
		return metric;
	}

	private void method3() {
		// deprecated and removed
		//
		//		Ejb3Configuration cfg = new Ejb3Configuration();
		//		EntityManagerFactory emf = 
		//		  cfg.addProperties( properties ) //add some properties
		//		     .setInterceptor( myInterceptorImpl ) // set an interceptor
		//		     .addAnnotatedClass( MyAnnotatedClass.class ) //add a class to be mapped
		//		     .addClass( NonAnnotatedClass.class ) //add an hbm.xml file using the Hibernate convention
		//		     .addRerousce( "mypath/MyOtherCLass.hbm.xml" ) //add an hbm.xml file
		//		     .addRerousce( "mypath/orm.xml" ) //add an EJB3 deployment descriptor
		//		     .configure("/mypath/hibernate.cfg.xml") //add a regular hibernate.cfg.xml
		//		     .buildEntityManagerFactory(); //Create the entity manager factory
	}

	@Override
	public void disconnect() {
		emf.close();
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PersistentItem next() throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void rewind() throws IOException {
		// TODO Auto-generated method stub

	}

	@Override
	public void seek(long startTime) throws IOException {
		// TODO Auto-generated method stub

	}

	@Override
	public long getTimeInMillis() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public RpSubject getSubjectInfo() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PiDatastreamImporter[] getDevices() {
		if (tables == null) {
			return null;
		}
		PiDatastreamImporter[] t = new PiDatastreamImporter[tables.size()];
		return tables.toArray(t);
	}

	@Override
	public ArchiveMetaData getMetaData() throws IOException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PiDatastreamImporter getDatastreamImporter(String name, StreamID sid) {
		// TODO Auto-generated method stub
		return null;
	}

}
