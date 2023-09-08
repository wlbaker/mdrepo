package idea.zoll;

import java.io.IOException;
import java.util.Iterator;
import java.util.Map;

import javax.websocket.Endpoint;
import javax.websocket.EndpointConfig;
import javax.websocket.MessageHandler;
import javax.websocket.Session;

import com.google.gson.Gson;

public class ZollEndpoint extends Endpoint implements MessageHandler.Whole<String> {

	private static Gson gson = new Gson();
	private static final String HEARTBEAT_MESSAGE = "{\"command\": \"heartbeat\", \"params\": {\"state\": true}}";
	private Session session;

	private int seq = 0;

	@Override
	public void onOpen(Session session, EndpointConfig config) {

		this.session = session;
		try {
			session.addMessageHandler(this);

			// session.getBasicRemote().sendText(HEARTBEAT_MESSAGE);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	@SuppressWarnings("rawtypes")
	public void onMessage(String jsonStr) {
		System.out.println( jsonStr );
		seq++;
		if( seq > 1000 ) System.exit(0);
		Map m = gson.fromJson(jsonStr, Map.class);
//		Iterator it = m.keySet().iterator();
//		String k = (String) it.next();
//		String v = k.substring(0, 1);
//		System.out.print(v);
//		if (v.equals("P")) {
//			System.out.println();
//		}
//		if (seq > 60) {
//			System.out.println();
//			seq = 0;
//		} else {
//			seq++;
//		}
//		System.out.print(".");
	}

	public void tick() {
		try {
			session.getBasicRemote().sendText(HEARTBEAT_MESSAGE);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
