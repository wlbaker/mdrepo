package idea.zoll;

import java.net.URI;
import java.util.Base64;
import java.util.Base64.Encoder;

import javax.websocket.ClientEndpointConfig;

import org.glassfish.grizzly.ssl.SSLContextConfigurator;
import org.glassfish.grizzly.ssl.SSLEngineConfigurator;
import org.glassfish.tyrus.client.ClientManager;
import org.glassfish.tyrus.client.ClientProperties;
import org.glassfish.tyrus.client.SslContextConfigurator;
import org.glassfish.tyrus.client.SslEngineConfigurator;

public class ZollDemo {

	private static String encodeAuth(String auth) {
		 Encoder encoder = Base64.getEncoder();
		 byte[] code1 = encoder.encode( auth.getBytes() );
		 String extendedCode1 = "Basic " + new String(code1);
		 byte[] code2 = encoder.encode( extendedCode1.getBytes() );
		 return new String(code2);
		 
		 
	}
	
	public static void main(String[] args) throws Exception {
		
		if( args.length < 4 ) {
			System.out.println("USAGE: <prog> <device> <auth_name_pwd> <keystore_file> <keystore_password>");
			return;
		}
		String device = args[0]; // "AP14E001105.X-Series.device.ZOLL.local";
		String auth = args[1];  // myuser:mypassword
		String keystoreFile = args[2];
		String keystorePassword = args[3];
		
		// device = "localhost:7681";
		
		String encodedAuth = encodeAuth( auth );
		String uri = "wss://" + device + "/Comet?auth=" + encodedAuth;
		
		System.out.println("URI=" + uri);

		ZollEndpoint endpoint = new ZollEndpoint(); 

		ClientManager client = ClientManager.createClient();

		System.getProperties().put(SSLContextConfigurator.TRUST_STORE_FILE, keystoreFile );
		System.getProperties().put(SSLContextConfigurator.TRUST_STORE_PASSWORD, keystorePassword );

		final SSLContextConfigurator defaultConfig = new SSLContextConfigurator();

		defaultConfig.retrieve(System.getProperties());
		// or setup SSLContextConfigurator using its API.

		SSLEngineConfigurator sslEngineConfigurator1 = new SSLEngineConfigurator(defaultConfig, true, false, false);
		client.getProperties().put(ClientProperties.SSL_ENGINE_CONFIGURATOR, sslEngineConfigurator1);
		client.connectToServer(endpoint, ClientEndpointConfig.Builder.create().build(), new URI(uri));

		SslEngineConfigurator sslEngineConfigurator = new SslEngineConfigurator(new SslContextConfigurator());
		sslEngineConfigurator.setHostVerificationEnabled(false);

		for(;;) {
			Thread.sleep(2500);
			
			endpoint.tick();
			
		}
	}


}