package idea.datamanager.unused.devel;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class TestOracle {

	public static void main(String[] args) throws ClassNotFoundException, SQLException {
		Class.forName("oracle.jdbc.driver.OracleDriver");
		//
		// or
		// DriverManager.registerDriver
		//        (new oracle.jdbc.driver.OracleDriver());

		String url = "jdbc:oracle:thin:@143.83.220.225:1521:C3EDEVL";
		//               jdbc:oracle:thin:@//host:port/service
		// or
		// String url = "jdbc:oracle:thin:@server.local:1521:prodsid";
		//               jdbc:oracle:thin:@host:port:SID
		//
		//  SID  - System ID of the Oracle server database instance.
		//         By default, Oracle Database 10g Express Edition
		//         creates one database instance called XE.
		//         ex : String url = "jdbc:oracle:thin:@myhost:1521:xe";

		Connection conn = DriverManager.getConnection(url, "bbaker", "PW0rd4bb");

		conn.setAutoCommit(false);
		Statement stmt = conn.createStatement();
		ResultSet rset = stmt.executeQuery("select BANNER from SYS.V_$VERSION");
		while (rset.next()) {
			System.out.println(rset.getString(1));
		}
		stmt.close();
		System.out.println("Ok.");
	}

}
