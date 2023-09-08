package idea.driver.hl7;

import java.io.IOException;
import java.util.Map;

import ca.uhn.hl7v2.DefaultHapiContext;
import ca.uhn.hl7v2.HL7Exception;
import ca.uhn.hl7v2.model.Message;
import ca.uhn.hl7v2.model.Segment;
import ca.uhn.hl7v2.model.Structure;
import ca.uhn.hl7v2.protocol.ReceivingApplication;
import ca.uhn.hl7v2.protocol.ReceivingApplicationException;
import ca.uhn.hl7v2.util.Terser;

/**
 * Application class for receiving ADT^A01 messages
 */
public class AesculonReceiverApplication implements ReceivingApplication {

	/**
	 * {@inheritDoc}
	 */
	public boolean canProcess(Message theIn) {
		return true;
	}

	/**
	 * {@inheritDoc}
	 */
	public Message processMessage(Message theMessage, Map<String, Object> theMetadata)
			throws ReceivingApplicationException, HL7Exception {

		 String encodedMessage = new DefaultHapiContext().getPipeParser().encode(theMessage);
		 System.out.println("Received message:\n" + encodedMessage + "\n\n");
		//Structure[] obx = theMessage.getAll("/OBX");
		//System.out.println("obx=" + obx);
	     /* 
		          * A generic message has a flat structure, so you can ask for any
		          * field by only its segment name, not a complex path 
		          */
		         Terser t = new Terser(theMessage);
		         //Segment pid = t.getSegment("/RESPONSE/ORDER_OBSERVATION");
		         //System.out.print(pid);
		         System.out.println(t.get("/RESPONSE/ORDER_OBSERVATION/OBSERVATION(0)/OBX-2"));
		         System.out.println(t.get("/RESPONSE/ORDER_OBSERVATION/OBSERVATION(0)/OBX-5"));
		         System.out.println(t.get("/RESPONSE/ORDER_OBSERVATION/OBSERVATION(1)/OBX-2"));
		         System.out.println(t.get("/RESPONSE/ORDER_OBSERVATION/OBSERVATION(1)/OBX-5"));
		         System.out.println(t.get("/RESPONSE/ORDER_OBSERVATION/OBSERVATION(2)/OBX-5"));
//		         System.out.println(t.get("/PATIENT_RESULT/ORDER_OBSERVATION/OBSERVATION(0)/OBX(4)-5"));
		         //System.out.println(t.get("/PATIENT_RESULT/ORDER_OBSERVATION/OBSERVATION(0)/OBX(5)-5"));
//		         System.out.println(t.get("/OBX-5"));
//		         System.out.println(t.get("/OBX3-5"));
//		         System.out.println(t.get("/OBX4-5"));
//		         System.out.println(t.get("/OBX5-5"));
		         
		// Now generate a simple acknowledgment message and return it
		try {
			return theMessage.generateACK();
		} catch (IOException e) {
			throw new HL7Exception(e);
		}

	}

}
