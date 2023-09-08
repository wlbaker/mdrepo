/*
 * Created by JFormDesigner on Tue Sep 18 13:45:41 CDT 2007
 */

package idea.jasper;

//import gnu.hylafax.Client;
//import gnu.hylafax.HylaFAXClient;
//import gnu.hylafax.Job;
//import gnu.inet.ftp.FtpClientProtocol;
//import gnu.inet.ftp.ServerResponseException;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Date;
import java.util.Properties;

import javax.activation.DataHandler;
import javax.mail.Authenticator;
import javax.mail.BodyPart;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRExporter;
import net.sf.jasperreports.engine.JRExporterParameter;
import net.sf.jasperreports.engine.JasperPrint;
import net.sf.jasperreports.engine.export.JRPdfExporter;
import idea.ConfigurationInfo;
import idea.GuiUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

//import db.Contact;
//import db.Teledex;
//import db.type.TelephoneNumber;

class Contact {

	public String getEmail() {
		// TODO Auto-generated method stub
		return null;
	}

	public String getFirstName() {
		// TODO Auto-generated method stub
		return null;
	}

	public String getLastName() {
		// TODO Auto-generated method stub
		return null;
	}

	public TelephoneNumber getTele2() {
		// TODO Auto-generated method stub
		return null;
	}

}

class TelephoneNumber {
	
}
/**
 * @author William Baker
 * 
 * 
 * protocol = "smtp"; host = "auth.smtp.profimailer.de"; port = 25; String from="jens@jens-wannenmacher.de"; String
 * to="jens@jens-wannenmacher.de"; props.put("mail.smtp.host", host); props.put("mail.smtp.auth", "true"); Authenticator
 * auth = new PopupAuthenticator(); session=Session.getInstance(props,auth); MimeMessage message = new
 * MimeMessage(session); message.setFrom(new InternetAddress(from,"jens@jens-wannenmacher.de"));
 * message.addRecipient(Message.RecipientType.TO,new InternetAddress(to,"ToName")); message.setSubject("Hello
 * JavaMail"); message.setText("Welcome to JavaMail"); Transport.send(message);
 * 
 * static class PopupAuthenticator extends Authenticator { public PasswordAuthentication getPasswordAuthentication() {
 * return new PasswordAuthentication("e12345676", "mypass"); } }
 * 
 */

class PopupAuthenticator extends Authenticator {
	public PasswordAuthentication getPasswordAuthentication() {
		return new PasswordAuthentication("bbaker", "dabitot");
	}
}

@SuppressWarnings("serial")
public class SendPanel extends JPanel {
	private String contentType;
	// private String encoding;
	private byte[] data;
	private String attachmentName;

	public SendPanel() {
		initComponents();
		// GuiUtil.initPanel(this, null, null);

		from.setText(ConfigurationInfo.getEmailAddress());
		selfAddress.setText(ConfigurationInfo.getEmailAddress());

		checkActionPerformed(null);

		DefaultListModel model = new DefaultListModel();
		attachmentList.setModel(model);
		
	}

	public void addAttachment(String attachmentName, String contentType, byte[] data) {
		this.attachmentName = attachmentName;
		this.contentType = contentType;
		// this.encoding = encoding;
		this.data = data;

		DefaultListModel model = (DefaultListModel) attachmentList.getModel();
		model.addElement(attachmentName);
	}

	public void setContact(Contact contact) {
		emailAddress.setText(contact.getEmail());
		attention.setText(contact.getFirstName() + " " + contact.getLastName());
		
		TelephoneNumber faxTele = contact.getTele2();
		if( faxTele != null ) {
			String fax = faxTele.toString();
			fax = fax.replace("(", "" );
			fax = fax.replace(")", "" );
			fax = fax.trim();
			
//			if( fax.length() < 10 ) {
//				Teledex teledex = contact.getTeledex();
//				fax = teledex.getTele2().toString();
//				fax = fax.replace("(", "" );
//				fax = fax.replace(")", "" );
//				fax = fax.trim();
//			}
	
			faxNo.setText( fax );
		}
	}

	public void setName(String name) {
		if (name == null)
			name = "";
		attention.setText(name);
	}

	public void setEmailAddress(String emailAddress) {
		if (emailAddress == null)
			emailAddress = "";
		this.emailAddress.setText(emailAddress);

		// wlb! this.emailCheck.setSelected(emailAddress.length() > 1);
		checkActionPerformed(null);
	}

	public void setFaxNo(String faxNo) {
		if (faxNo == null)
			faxNo = "";
		this.faxNo.setText(faxNo);

		this.faxCheck.setSelected(faxNo.length() > 7);
		checkActionPerformed(null);
	}

	public void setSubject(String subject) {
		if (subject == null)
			subject = "";
		this.subject.setText(subject);
	}

	private void checkActionPerformed(ActionEvent e) {

		faxNo.setEnabled(faxCheck.isSelected());
		attention.setEnabled(faxCheck.isSelected());
		emailAddress.setEnabled(emailCheck.isSelected());

	}

	private void sendActionPerformed(ActionEvent a) {

		try {
			if (faxCheck.isSelected()) {
				// String faxTo = attention.getText() + "@" + faxNo.getText();
				String faxTo = faxNo.getText();
				sendFax(faxTo, from.getText(), subject.getText(), body.getText());
			}

			if (emailCheck.isSelected()) {
				// "base64", null gives 7bit ascii
				sendMessage(emailAddress.getText(), selfAddress.getText(), subject.getText(), body.getText());
			}
			if (selfSend.isSelected()) {
				// "base64", null gives 7bit ascii
				sendMessage(selfAddress.getText(), "Hylafax <faxer@priefert.com>", subject.getText(), body.getText());
			}
			cancelActionPerformed(a);
		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(null, e.getMessage());
		}

	}

	private void sendFax(String faxTo, String from, String subject, String body) throws
			IOException {
		
//		File tmpFile = null;
//		Client c = new HylaFAXClient();
//		try {
//
//			String host = ConfigurationInfo.getFaxServer();
//			// Open the host.
//			c.open(host);
//			c.user("hylafaxer");
//			// c.pass(password)
//
//			// Set the transfer mode and type. This is important if you are
//			// having problems getting the HylaFAX server recognize the files
//			// you are sending.
//			c.mode(FtpClientProtocol.MODE_ZLIB);
//			c.type(FtpClientProtocol.TYPE_IMAGE);
//
//			// Do this only is a password is required in the hosts.hfaxd
//			// file on the server.
//			// c.pass(password);
//
//			// Do this if you want to do admin functions. Must be configured
//			// correctly in the hosts.hfaxd file.
//			// c.admin(password);
//
//			// Create a new job.
//			Job job = c.createJob();
//
//			// Set the job properties. This can be any jparm property specified
//			// in the hfaxd manual page. If there is not a native function for
//			// the property you are trying to set, use the setProperty function
//			// to set it.
//			job.setFromUser(from);
//			job.setNotifyAddress(from);
//			job.setKilltime("000259"); // 2hrs 59 minutes
//			job.setMaximumDials(3);
//			job.setMaximumTries(3);
//			job.setPriority(50);
//			job.setDialstring(faxTo);
//			// job.setVerticalResolution(resolution);
//			// job.setPageDimension(pagesize);
//			// job.setNotifyType("bbaker@priefert.com");
//			// job.setChopThreshold(chopthreshold);
//			job.setJobInfo("tdxrecnum");
//
//			job.setProperty("COVER", "/etc/faxcover.ps");
//	//		job.setProperty("USECOVER", 1 );
//			job.setProperty("TOCOMPANY", "1 DOWNING STREET");
//
//			// Add any documents to send. As long as the HylaFAX server is setup
//			// properly you should be able to send PS, PDF, and TIFF documents.
//			// The HylaFAX server always converts them to PS before sending them.
//			tmpFile = File.createTempFile("faxer", ".pdf");
//
//			InputStream in = new ByteArrayInputStream( data );
//			// for (int i = 0; i < documents.size(); i++) {
//			// String document = (String) documents.elementAt(i);
//			// job.addDocument(document);
//			//String pathName = tmpFile.getPath();
//			//System.out.println("sending file: " + pathName);
//			//job.addDocument(tmpFile.getPath());
//			// }
//			String doc = c.put( in );
//			job.addDocument(doc);
//			
//			// Submit the job to the scheduler.
//			c.submit(job);
//
//			in.close();
//		}	finally {
//		
//			// Close the client.
//			try {
//				c.quit();
//				
//				if( tmpFile != null ) {
//					tmpFile.delete();
//				}
//			} catch (Exception e) {
//				e.printStackTrace();
//			}
//		}

	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	public void sendMessage(String szTo, String szFrom, String szSubject, String body) throws AddressException,
			MessagingException {
		Properties props = System.getProperties();

		// -- Attaching to default Session, or we could start a new one --
		String smtpHost = ConfigurationInfo.getEmailServer();
		if (smtpHost == null) {
			smtpHost = "mail.priefert.com";
			JOptionPane.showMessageDialog(null, "Could not find smtp.host.  Assuming value: " + smtpHost);
		}

		props.put("mail.smtp.host", smtpHost);

		Session session;

		String protocol = ConfigurationInfo.getEmailProtocol();
		props.put("mail.smtp.port", ConfigurationInfo.getEmailPort());

		if (protocol.toLowerCase().startsWith("auth")) {
			props.put("mail.smtp.auth", "true");
			props.put("mail.smtp.starttls.enable", "true");
			// props.put("mail.debug", "true"); // to enable debugging messages

			System.err.println( "NOT LONGER ACCESSIBLE: java.security.Security.addProvider(new com.sun.net.ssl.internal.ssl.Provider())" );

			Authenticator auth = new PopupAuthenticator();
			session = Session.getInstance(props, auth);
		} else {
			session = Session.getDefaultInstance(props, null);
		}

		// -- Create a new message --
		Message msg = new MimeMessage(session);

		// Now the message body.
		Multipart mp = new MimeMultipart();

		BodyPart textPart = new MimeBodyPart();
		textPart.setText(body); // sets type to "text/plain"
		mp.addBodyPart(textPart);

		// Part two is attachment

		if (data != null) {
			MimeBodyPart attachmentBodyPart = new MimeBodyPart();
			attachmentBodyPart.setDataHandler(new DataHandler(new ByteArrayDataSource(data, contentType)));
			attachmentBodyPart.setFileName(attachmentName);

			// Collect the Parts into the MultiPart
			mp.addBodyPart(attachmentBodyPart);
		}

		// Put the MultiPart into the Message
		msg.setContent(mp);

		// -- Set the FROM and TO fields --
		msg.setFrom(new InternetAddress(szFrom));
		msg.setRecipients(Message.RecipientType.TO, InternetAddress.parse(szTo, false));

		// -- We could include CC recipients too --
		// if (cc != null)
		// msg.setRecipients(Message.RecipientType.CC
		// ,InternetAddress.parse(cc, false));

		// -- Set the subject and body text --
		msg.setSubject(szSubject);

		// if (szEncoding != null)
		// msg.setHeader("Content-Transfer-Encoding", szEncoding); // "base64"

		// -- Set some other header information --
		msg.setSentDate(new Date());

		// -- Send the message --

		Transport.send(msg);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		label3 = new JLabel();
		from = new JTextField();
		label2 = new JLabel();
		subject = new JTextField();
		faxCheck = new JCheckBox();
		faxNo = new JTextField();
		label1 = new JLabel();
		attention = new JTextField();
		emailCheck = new JCheckBox();
		emailAddress = new JTextField();
		label4 = new JLabel();
		scrollPane1 = new JScrollPane();
		body = new JTextArea();
		label5 = new JLabel();
		scrollPane2 = new JScrollPane();
		attachmentList = new JList();
		panel1 = new JPanel();
		selfSend = new JCheckBox();
		selfAddress = new JLabel();
		send = new JButton();
		cancel = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow, $lcgap, default, $lcgap, [151dlu,default], $lcgap, [150dlu,default], $lcgap, default:grow",
			"6*(default, $lgap), fill:[40dlu,default]:grow, $lgap, [default,60dlu], 2*($lgap, default)"));

		//---- label3 ----
		label3.setText("From:");
		label3.setHorizontalAlignment(SwingConstants.TRAILING);
		add(label3, CC.xy(3, 3));

		//---- from ----
		from.setEnabled(false);
		from.setEditable(false);
		add(from, CC.xy(5, 3));

		//---- label2 ----
		label2.setText("Subject:");
		label2.setHorizontalAlignment(SwingConstants.TRAILING);
		add(label2, CC.xy(3, 5));
		add(subject, CC.xy(5, 5));

		//---- faxCheck ----
		faxCheck.setText("Fax");
		faxCheck.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				checkActionPerformed(e);
			}
		});
		add(faxCheck, CC.xy(3, 7));

		//---- faxNo ----
		faxNo.setEnabled(false);
		add(faxNo, CC.xy(5, 7));

		//---- label1 ----
		label1.setText("Attention:");
		label1.setHorizontalAlignment(SwingConstants.TRAILING);
		add(label1, CC.xy(3, 9));

		//---- attention ----
		attention.setEnabled(false);
		add(attention, CC.xy(5, 9));

		//---- emailCheck ----
		emailCheck.setText("Email");
		emailCheck.setSelected(true);
		emailCheck.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				checkActionPerformed(e);
			}
		});
		add(emailCheck, CC.xy(3, 11));
		add(emailAddress, CC.xy(5, 11));

		//---- label4 ----
		label4.setText("Message:");
		label4.setHorizontalAlignment(SwingConstants.TRAILING);
		add(label4, CC.xy(3, 13, CC.DEFAULT, CC.TOP));

		//======== scrollPane1 ========
		{
			scrollPane1.setViewportView(body);
		}
		add(scrollPane1, CC.xywh(5, 13, 3, 1));

		//---- label5 ----
		label5.setText("Attachments:");
		add(label5, CC.xy(3, 15, CC.RIGHT, CC.TOP));

		//======== scrollPane2 ========
		{
			scrollPane2.setPreferredSize(new Dimension(35, 30));

			//---- attachmentList ----
			attachmentList.setEnabled(false);
			scrollPane2.setViewportView(attachmentList);
		}
		add(scrollPane2, CC.xywh(5, 15, 3, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default:grow, 3*($lcgap, default)",
				"default"));

			//---- selfSend ----
			selfSend.setText("Send a copy to myself:");
			panel1.add(selfSend, CC.xy(1, 1));

			//---- selfAddress ----
			selfAddress.setText("text");
			panel1.add(selfAddress, CC.xy(3, 1));

			//---- send ----
			send.setText("Send");
			send.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					sendActionPerformed(e);
				}
			});
			panel1.add(send, CC.xy(7, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel1.add(cancel, CC.xy(9, 1));
		}
		add(panel1, CC.xywh(1, 19, 9, 1));
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel label3;
	private JTextField from;
	private JLabel label2;
	private JTextField subject;
	private JCheckBox faxCheck;
	private JTextField faxNo;
	private JLabel label1;
	private JTextField attention;
	private JCheckBox emailCheck;
	private JTextField emailAddress;
	private JLabel label4;
	private JScrollPane scrollPane1;
	private JTextArea body;
	private JLabel label5;
	private JScrollPane scrollPane2;
	private JList attachmentList;
	private JPanel panel1;
	private JCheckBox selfSend;
	private JLabel selfAddress;
	private JButton send;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public static void send( String subject, String docName, JasperPrint jasperPrint, Contact contact ) {
		JRExporter exporter = new JRPdfExporter();
		ByteArrayOutputStream baos = new ByteArrayOutputStream();

		exporter.setParameter(JRExporterParameter.JASPER_PRINT, jasperPrint);
		exporter.setParameter(JRExporterParameter.OUTPUT_STREAM, baos);
		try {
			exporter.exportReport();
		} catch (JRException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();

			JOptionPane.showMessageDialog(null, e.getMessage());
			return;
		}

		SendPanel p = new SendPanel( );
		p.setContact( contact );

		p.addAttachment( getPdfAttachmentName( docName ), "application/pdf", baos.toByteArray());

		if (subject == null) {
			subject = ConfigurationInfo.getCompanyName();
		} else {
			subject = ConfigurationInfo.getCompanyName() + " " + subject;
		}
		p.setSubject(subject);

		JOptionPane o = new JOptionPane(p, JOptionPane.INFORMATION_MESSAGE, JOptionPane.NO_OPTION, null, new Object[0],
				null);
		JDialog dialog = o.createDialog(null, "Send...");
		dialog.setResizable(true);

		dialog.setVisible(true);

		/*
		 * Thread thread = new Thread( new Runnable() { public void run() { try {
		 * JasperPrintManager.printReport(jasperPrint, true); } catch (Exception ex) { ex.printStackTrace();
		 * JOptionPane.showMessageDialog(null, "Error sending report. See the console for details."); } } } );
		 * thread.start();
		 */
	}

	private static String getPdfAttachmentName( String title ) {
		if( title == null ) {
			title = "document";
		}
		title += ".pdf";
		title = title.replace(' ', '_' );
		title = title.replace(":", "" );
		return title;
	}


}
