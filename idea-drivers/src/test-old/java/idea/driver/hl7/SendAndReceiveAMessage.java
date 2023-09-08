package idea.driver.hl7;

import java.io.IOException;

/**
    * The contents of this file are subject to the Mozilla Public License Version 1.1
    * (the "License"); you may not use this file except in compliance with the License.
    * You may obtain a copy of the License at http://www.mozilla.org/MPL/
    * Software distributed under the License is distributed on an "AS IS" basis,
    * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the
    * specific language governing rights and limitations under the License.
    *
    * The Original Code is "SendAndReceiveAMessage.java".  Description:
   * "Example Code"
   *
   * The Initial Developer of the Original Code is University Health Network. Copyright (C)
   * 2001.  All Rights Reserved.
   *
   * Contributor(s): James Agnew
   *
   * Alternatively, the contents of this file may be used under the terms of the
   * GNU General Public License (the  �GPL�), in which case the provisions of the GPL are
   * applicable instead of those above.  If you wish to allow use of your version of this
   * file only under the terms of the GPL and not to allow others to use your version
   * of this file under the MPL, indicate your decision by deleting  the provisions above
   * and replace  them with the notice and other provisions required by the GPL License.
   * If you do not delete the provisions above, a recipient may use your version of
   * this file under either the MPL or the GPL.
   *
   */

import java.util.Map;

import org.apache.log4j.Level;
import org.apache.log4j.LogManager;

import ca.uhn.hl7v2.DefaultHapiContext;
import ca.uhn.hl7v2.HL7Exception;
import ca.uhn.hl7v2.HapiContext;
import ca.uhn.hl7v2.app.*;
import ca.uhn.hl7v2.llp.LLPException;
import ca.uhn.hl7v2.model.Message;
import ca.uhn.hl7v2.parser.CanonicalModelClassFactory;
import ca.uhn.hl7v2.parser.Parser;
import ca.uhn.hl7v2.protocol.ReceivingApplication;
import ca.uhn.hl7v2.protocol.ReceivingApplicationExceptionHandler;
import ca.uhn.hl7v2.validation.builder.support.NoValidationBuilder;

/**
 * Example code
 * 
 * @author James Agnew
 * @author Christian Ohr
 * @version $Revision: 1.2 $ updated on $Date: 2010-09-06 17:29:21 $ by $Author:
 *          jamesagnew $
 */
public class SendAndReceiveAMessage {

	/**
	 * Example for how to send messages out
	 */
	public static void main(String[] args) throws Exception {

		LogManager.getRootLogger().setLevel((Level) Level.INFO);
		/*
		 * Before we can send, let's create a server to listen for incoming
		 * messages. The following section of code establishes a server
		 * listening on port 1011 for new connections.
		 */
		int port = 9101; // The port to listen on
		boolean useTls = false; // Should we use TLS/SSL?

		HapiContext context = new DefaultHapiContext();

		context.setValidationRuleBuilder(new NoValidationBuilder());

		// Create the MCF. We want all parsed messages to be for HL7 version
		// 2.5,
		// despite what MSH-12 says.
		// CanonicalModelClassFactory mcf = new
		// CanonicalModelClassFactory("2.5");
		// context.setModelClassFactory(mcf);

		HL7Service server = context.newServer(port, useTls);

		/*
		 * The server may have any number of "application" objects registered to
		 * handle messages. We are going to create an application to listen to
		 * ADT^A01 messages.
		 * 
		 * You might want to look at the source of ExampleReceiverApplication
		 * (it's a nested class below) to see how it works.
		 */
		ReceivingApplication handler = new AesculonReceiverApplication();
		server.registerApplication("ADT", "A01", handler);

		/*
		 * We are going to register the same application to handle ADT^A02
		 * messages. Of course, we coud just as easily have specified a
		 * different handler.
		 */
		server.registerApplication("ORU", "R01", handler);
		server.registerApplication("QRY", "R02", handler);

		/*
		 * Another option would be to specify a single application to handle all
		 * messages, like this:
		 */
		// server.registerApplication("*", "*", handler);

		/*
		 * If you want to be notified any time a new connection comes in or is
		 * lost, you might also want to register a connection listener (see the
		 * bottom of this class to see what the listener looks like). It's fine
		 * to skip this step.
		 */
		server.registerConnectionListener(new MyConnectionListener());

		/*
		 * If you want to be notified any processing failures when receiving,
		 * processing, or responding to messages with the server, you can also
		 * register an exception handler. (See the bottom of this class to see
		 * what the listener looks like. ) It's also fine to skip this step, in
		 * which case exceptions will simply be logged.
		 */
		server.setExceptionHandler(new MyExceptionHandler());

		// Start the server listening for messages
		server.startAndWait();

		/*
		 * Note: if you don't want to wait for the server to initialize itself,
		 * it can start in the background:
		 */

		// server.start();

		// sendDemo(context, port, useTls);
		// server.stopAndWait(); // Stop the receiving server and client

	}

	private static void sendDemo(HapiContext context, int port, boolean useTls)
			throws HL7Exception, LLPException, IOException {
		/*
		 * All of the code above created a listening server, which waits for
		 * connections to come in and then handles any messages that arrive on
		 * those connections.
		 * 
		 * Now, the code below creates a client, which will connect to our
		 * waiting server and send messages to it.
		 */

		// Create a message to send
		String msg1 = "MSH|^~\\&|HIS|RIH|EKG|EKG|199904140038||ADT^A01|12345|P|2.2\r"
				+ "PID|0001|00009874|00001122|A00977|SMITH^JOHN^M|MOM|19581119|F|NOTREAL^LINDA^M|C|564 SPRING ST^^NEEDHAM^MA^02494^US|0002|(818)565-1551|(425)828-3344|E|S|C|0000444444|252-00-4414||||SA|||SA||||NONE|V1|0001|I|D.ER^50A^M110^01|ER|P00055|11B^M011^02|070615^BATMAN^GEORGE^L|555888^NOTREAL^BOB^K^DR^MD|777889^NOTREAL^SAM^T^DR^MD^PHD|ER|D.WT^1A^M010^01|||ER|AMB|02|070615^NOTREAL^BILL^L|ER|000001916994|D||||||||||||||||GDD|WA|NORM|02|O|02|E.IN^02D^M090^01|E.IN^01D^M080^01|199904072124|199904101200|199904101200||||5555112333|||666097^NOTREAL^MANNY^P\r"
				+ "NK1|0222555|NOTREAL^JAMES^R|FA|STREET^OTHER STREET^CITY^ST^55566|(222)111-3333|(888)999-0000|||||||ORGANIZATION\r"
				+ "PV1|0001|I|D.ER^1F^M950^01|ER|P000998|11B^M011^02|070615^BATMAN^GEORGE^L|555888^OKNEL^BOB^K^DR^MD|777889^NOTREAL^SAM^T^DR^MD^PHD|ER|D.WT^1A^M010^01|||ER|AMB|02|070615^VOICE^BILL^L|ER|000001916994|D||||||||||||||||GDD|WA|NORM|02|O|02|E.IN^02D^M090^01|E.IN^01D^M080^01|199904072124|199904101200|||||5555112333|||666097^DNOTREAL^MANNY^P\r"
				+ "PV2|||0112^TESTING|55555^PATIENT IS NORMAL|NONE|||19990225|19990226|1|1|TESTING|555888^NOTREAL^BOB^K^DR^MD||||||||||PROD^003^099|02|ER||NONE|19990225|19990223|19990316|NONE\r"
				+ "AL1||SEV|001^POLLEN\r"
				+ "GT1||0222PL|NOTREAL^BOB^B||STREET^OTHER STREET^CITY^ST^77787|(444)999-3333|(222)777-5555||||MO|111-33-5555||||NOTREAL GILL N|STREET^OTHER STREET^CITY^ST^99999|(111)222-3333\r"
				+ "IN1||022254P|4558PD|BLUE CROSS|STREET^OTHER STREET^CITY^ST^00990||(333)333-6666||221K|LENIX|||19980515|19990515|||PATIENT01 TEST D||||||||||||||||||02LL|022LP554";
		String msg2 = "MSH|^~\\&|iControl||||20171221145413||ORU^R01|20171221145413785|P|2.3\r"
				+ "PID|1||anaphylactic shock^^^^||Demo^John||20000611000000|M||||||||||\r" //
				+ "PV1|1||^^||||||||||||||||\r" //
				+ "OBR|1||||||20171221145413\r" //
				+ "OBX|1|NM|||100|%|||||R|||20171221145413\r" //
				+ "OBX|2|NM|||100|bpm|||||R|||20171221145413\r" //
				+ "OBX|3|NM|||8.8|l/min|||||R|||20171221145413\r" //
				+ "OBX|4|NM|||3.2|BSA|||||R|||20171221145413\r" //
				+ "OBX|5|NM|||0.08|WT|||||R|||20171221145413\r" //
				+ "OBX|6|NM|||89|ml|||||R|||20171221145413\r" //
				+ "OBX|7|NM|||46|BSA|||||R|||20171221145413\r" //
				+ "OBX|8|NM|||1.17|WT|||||R|||20171221145413\r" //
				+ "OBX|9|NM|||39||||||R|||20171221145413\r" //
				+ "OBX|10|NM|||327|ms|||||R|||20171221145413\r" //
				+ "OBX|11|NM|||35.3||||||R|||20171221145413\r" //
				+ "OBX|12|NM|||0.15||||||R|||20171221145413\r" //
				+ "OBX|13|NM|||5|%|||||R|||20171221145413\r" //
				+ "OBX|14|NM|||8|%|||||R|||20171221145413\r" //
				+ "OBX|15|NM|||95|ms|||||R|||20171221145413\r" //
				+ "OBX|16|NM|||305|ms|||||R|||20171221145413\r" //
				+ "OBX|17|NM|||747|dyn?s/cm?|||||R|||20171221145413\r" //
				+ "OBX|18|NM|||1,926|BSA|||||R|||20171221145413\r" //
				+ "OBX|19|NM|||76,132|WT|||||R|||20171221145413\r" //
				+ "OBX|20|NM|||68||||||R|||20171221145413\r" //
				+ "OBX|21|NM|||133|BSA|||||R|||20171221145413\r" //
				+ "OBX|22|NM|||5,251|WT|||||R|||20171221145413\r" //
				+ "OBX|23|NM|||0.56|BSA|||||R|||20171221145413\r" //
				+ "OBX|24|NM|||0.014|WT|||||R|||20171221145413\r" //
				+ "OBX|25|NM|||19.6|ml/dL|||||R|||20171221145413\r" //
				+ "OBX|26|NM|||1,218|ml/min|||||R|||20171221145413\r" //
				+ "OBX|27|NM|||625|BSA|||||R|||20171221145413\r" //
				+ "OBX|28|NM|||15.8|WT|||||R|||20171221145413\r" //
				+ "OBX|29|NM|||9.2|ms|||||R|||20171221145413\r" //
				+ "OBX|30|NM|||0.73||||||R|||20171221145413\r" //
				+ "OBX|31|NM|||1.87||||||R|||20171221145413\r" //
				+ "OBX|32|NM|||0.00|%|||||R|||20171221145413\r" //
				+ "OBX|33|NM|||0.24||||||R|||20171221145413\r" //
				+ "OBX|34|NM|||6.6|kg?m|||||R|||20171221145413\r" //
				+ "OBX|35|NM|||3.4|BSA|||||R|||20171221145413\r" //
				+ "OBX|36|NM|||0.086|WT|||||R|||20171221145413\r" //
				+ "OBX|37|NM|||96.3||||||R|||20171221145413\r" //
				+ "OBX|38|NM|||49.4|BSA|||||R|||20171221145413\r" //
				+ "OBX|39|NM|||1.25|WT|||||R|||20171221145413\r";

		String msg3 = "MSH|^~\\&|ULTRA|TML|OLIS|OLIS|200905011130||ORU^R01|20169838-v25|T|2.5\r" //
				+ "PID|||7005728^^^TML^MR||TEST^RACHEL^DIAMOND||19310313|F|||200 ANYWHERE ST^^TORONTO^ON^M6G 2T9||(416)888-8888||||||1014071185^KR\r" //
				+ "PV1|1||OLIS||||OLIST^BLAKE^DONALD^THOR^^^^^921379^^^^OLIST\r" //
				+ "ORC|RE||T09-100442-RET-0^^OLIS_Site_ID^ISO|||||||||OLIST^BLAKE^DONALD^THOR^^^^L^921379\r" //
				+ "OBR|0||T09-100442-RET-0^^OLIS_Site_ID^ISO|RET^RETICULOCYTE COUNT^HL79901 literal|||200905011106|||||||200905011106||OLIST^BLAKE^DONALD^THOR^^^^L^921379||7870279|7870279|T09-100442|MOHLTC|200905011130||B7|F||1^^^200905011106^^R\r" //
				+ "OBX|1|ST|||Test Value" //
		;

		String msg4 = "MSH|^~\\&|iControl||||20171222153656||QRY^R02|20171222153656947|P|2.3"
				+ "QRD|20171222153656|R|I|20171222153656963|||1^RD|cardiogenic shock^Demo^John" //
				+ "QRF||20171222153656" //
				;
		String msg = msg4;
		System.out.println(msg);

		Parser p = context.getPipeParser();
		Message adt = p.parse(msg);

		// Remember, we created our HAPI Context above like so:
		// HapiContext context = new DefaultHapiContext();

		// A connection object represents a socket attached to an HL7 server
		Connection connection = context.newClient("localhost", port, useTls);

		// The initiator is used to transmit unsolicited messages
		Initiator initiator = connection.getInitiator();
		Message response = initiator.sendAndReceive(adt);

		String responseString = p.encode(response);
		System.out.println("Received response:\n" + responseString);

		/*
		 * MSH|^~\&|||||20070218200627.515-0500||ACK|54|P|2.2 MSA|AA|12345
		 */

		/*
		 * If you want to send another message to the same destination, it's
		 * fine to ask the context again for a client to attach to the same
		 * host/port. The context will be smart about it and return the same
		 * (already connected) client Connection instance, assuming it hasn't
		 * been closed.
		 */
		connection = context.newClient("localhost", port, useTls);
		initiator = connection.getInitiator();
		response = initiator.sendAndReceive(adt);

		/*
		 * Close the connection when you are done with it. If you are designing
		 * a system which will continuously send out messages, you may want to
		 * consider not closing the connection until you have no more messages
		 * to send out. This is more efficient, as most (if not all) HL7
		 * receiving applications are capable of receiving lots of messages in a
		 * row over the same connection, even with a long delay between
		 * messages.
		 * 
		 * See http://hl7api.sourceforge.net/xref/ca/uhn/hl7v2/examples/
		 * SendLotsOfMessages. html for an example of this.
		 */
		connection.close();

	}

	/**
	 * Connection listener which is notified whenever a new connection comes in
	 * or is lost
	 */
	public static class MyConnectionListener implements ConnectionListener {

		public void connectionReceived(Connection theC) {
			System.out.println("New connection received: " + theC.getRemoteAddress().toString());
		}

		public void connectionDiscarded(Connection theC) {
			System.out.println("Lost connection from: " + theC.getRemoteAddress().toString());
		}

	}

	/**
	 * Exception handler which is notified any time
	 */
	public static class MyExceptionHandler implements ReceivingApplicationExceptionHandler {

		/**
		 * Process an exception.
		 * 
		 * @param theIncomingMessage
		 *            the incoming message. This is the raw message which was
		 *            received from the external system
		 * @param theIncomingMetadata
		 *            Any metadata that accompanies the incoming message. See
		 *            {@link ca.uhn.hl7v2.protocol.Transportable#getMetadata()}
		 * @param theOutgoingMessage
		 *            the outgoing message. The response NAK message generated
		 *            by HAPI.
		 * @param theE
		 *            the exception which was received
		 * @return The new outgoing message. This can be set to the value
		 *         provided by HAPI in <code>outgoingMessage</code>, or may be
		 *         replaced with another message. <b>This method may not return
		 *         <code>null</code></b>.
		 */
		public String processException(String theIncomingMessage, Map<String, Object> theIncomingMetadata,
				String theOutgoingMessage, Exception theE) throws HL7Exception {

			/*
			 * Here you can do any processing you like. If you want to change
			 * the response (NAK) message which will be returned you may do so,
			 * or just return the NAK which HAPI already created
			 * (theOutgoingMessage)
			 */

			return theOutgoingMessage;
		}

	}

}
