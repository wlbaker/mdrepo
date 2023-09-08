package idea.driver.hl7;
import ca.uhn.hl7v2.parser.*;
import ca.uhn.hl7v2.model.Message;
import ca.uhn.hl7v2.model.v26.message.ACK;

public class ParserDemo {

    public static void main(String args[]) {
        //for demo purposes, we just declare a literal message string 
        String ackMessageString 
            = "MSH|^~\\&|foo|foo||foo|200108151718||ACK^A01^ACK|1|D|2.4|\rMSA|AA\r";

        //instantiate a PipeParser, which handles the "traditional encoding" 
        PipeParser pipeParser = new PipeParser();

        try {
            //parse the message string into a Message object 
            Message message = pipeParser.parse(ackMessageString);

            //if it is an ACK message (as we know it is),  cast it to an 
            // ACK object so that it is easier to work with, and change a value            
            if (message instanceof ACK) {
                ACK ack = (ACK) message;
                ack.getMSH().getProcessingID().getProcessingMode().setValue("P");
            }

            //instantiate an XML parser 
            XMLParser xmlParser = new DefaultXMLParser();

            //encode message in XML 
            String ackMessageInXML = xmlParser.encode(message);

            //print XML-encoded message to standard out
            System.out.println(ackMessageInXML);
        } catch (Exception e) {
            e.printStackTrace();
        }       
    }
}