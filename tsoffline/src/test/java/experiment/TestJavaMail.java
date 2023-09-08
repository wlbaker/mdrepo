package experiment;

import java.util.Properties;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.NoSuchProviderException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

public class TestJavaMail {

	public static void main(String[] args) throws NoSuchProviderException {
	    final String username = "william.l.baker2.civ@mail.mil";  // like yourname@outlook.com
	    final String password = "";   // password here

	    Properties props = new Properties();
	    props.put("mail.smtp.auth", "true");
	    props.put("mail.smtp.starttls.enable", "true");
	    props.put("mail.smtp.host", "mail-ogdn01.easf.csd.disa.mil");
	    props.put("mail.smtp.port", "587");

	    Session session = Session.getInstance(props,
	      new javax.mail.Authenticator() {
	        @Override
	        protected PasswordAuthentication getPasswordAuthentication() {
	            return new PasswordAuthentication(username, password);
	        }
	      });
	    
	    session.getTransport();
	    session.setDebug(true);

	    try {

	        Message message = new MimeMessage(session);
	        message.setFrom(new InternetAddress(username));
	        message.setRecipients(Message.RecipientType.TO,
	            InternetAddress.parse("william.l.baker2@gmail.com"));   // like inzi769@gmail.com
	        message.setSubject("Test");
	        message.setText("HI you have done sending mail with outlook");

	        Transport.send(message);

	        System.out.println("Done");

	    } catch (MessagingException e) {
	        throw new RuntimeException(e);
	    }
	}
}
