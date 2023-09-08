package idea.python;

import py4j.GatewayServer;

public class PythonInterface {

	public static void main(String[] args) {
		PythonInterface app = new PythonInterface();
		    // app is now the gateway.entry_point
		    GatewayServer server = new GatewayServer(app);
		    server.start();
	}

}
