package idea.driver.hl7;

import java.io.*;
import java.net.*;

import ca.uhn.hl7v2.DefaultHapiContext;
import ca.uhn.hl7v2.HL7Exception;
import ca.uhn.hl7v2.HapiContext;
import ca.uhn.hl7v2.model.Message;
import ca.uhn.hl7v2.model.v26.message.ORU_R01;
import ca.uhn.hl7v2.parser.GenericParser;
import ca.uhn.hl7v2.parser.ModelClassFactory;
import ca.uhn.hl7v2.util.ReflectionUtil;

class TestAesculon {
	
	static HapiContext context = new DefaultHapiContext();
	static private GenericParser p;

	 protected static  Message instantiateMessage(String theName, String theVersion, boolean isExplicit) throws HL7Exception {
		ModelClassFactory factory = context.getModelClassFactory();
		Class<? extends Message> messageClass = factory.getMessageClass(theName, theVersion, isExplicit);
		if (messageClass == null)
			throw new HL7Exception("Can't find message class in current package list: " + theName);
		return ReflectionUtil.instantiateMessage(messageClass, factory);
	}

	public static void main(String argv[]) throws Exception {
		String clientSentence;
		String reply;

		p = context.getGenericParser();

		ServerSocket welcomeSocket = new ServerSocket(9101);

		int i = 0;
		while (i < 20) {
			Socket connectionSocket = welcomeSocket.accept();
			System.out.println("reading");
			BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
			DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
			
			String s = "";
			do {
				clientSentence = inFromClient.readLine();
				System.out.println("Received: " + clientSentence);
				s += clientSentence + "\n";
			} while( clientSentence != null && clientSentence.length() > 2 );
			
			reply = clientSentence.toUpperCase() + '\n';

			System.out.println("parsing message: " + s);
			Message hapiMsg = null;

			// hapiMsg = p.parse( s );
			hapiMsg = instantiateMessage("ORU_R01", "2.6", true);
			ORU_R01 oru = (ORU_R01) hapiMsg;
			oru.setParser(p);
			p.parse(oru, s);

			System.out.println("creating acknowledgement");
			
			Message ack = oru.generateACK();
			System.out.println("sending ack: " + ack);
			reply = "" + ack;
			outToClient.writeBytes(reply);
			
			i++;
			connectionSocket.close();
		}
		welcomeSocket.close();
	}

}
