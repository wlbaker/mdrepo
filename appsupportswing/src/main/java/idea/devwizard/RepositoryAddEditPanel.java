/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.devwizard;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.CustomizedDocument;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.meddaq.AppSetup;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class RepositoryAddEditPanel extends JPanel implements WizardPanelInterface {

	private WizardMasterInterface wizard;
	public RepositoryAddEditPanel( WizardMasterInterface wizard ) {
		initComponents();
		setName("Add/Edit");

		this.wizard = wizard;
		prepareDocs();

		GuiUtil.initPanel(this);

		server.setText(AppSetup.getRemoteRepositoryHost());
		username.setText(AppSetup.getRemoteRepositoryUser());
		password.setText(AppSetup.getRemoteRepositoryPwd());

	}

	private void prepareDocs() {
		CustomizedDocument doc = new CustomizedDocument();
		doc.setMaxChars(32);
		server.setDocument(doc);

		doc = new CustomizedDocument();
		doc.setMaxChars(32);
		username.setDocument(doc);

		doc = new CustomizedDocument();
		doc.setMaxChars(32);
		password.setDocument(doc);
	}

	private void testLoginActionPerformed(ActionEvent e) {
		String s_host = server.getText();
		String s_user = username.getText();
		String s_password = new String(password.getPassword());

//		try {
//			SftpScraps.send(s_host, s_user, s_password, null);
//			GuiUtil.showMessage("Authentication successful.");
//		} catch (InvalidHostFileException e1) {
//			GuiUtil.showError("Invalid host: ", e1);
//		} catch (IOException e1) {
//			GuiUtil.showError("Network error: ", e1);
//		} catch (AuthenticationException e1) {
//			GuiUtil.showError("Authentication error: ", e1);
//		} catch (Exception e1) {
//			GuiUtil.showError("Unknown error: ", e1);
//		}
		GuiUtil.showMessage("Incomplete.");
	}

	private void saveActionPerformed(ActionEvent e) {

		try {
			AppSetup.setRemoteRepositoryHost(server.getText());
			AppSetup.setRemoteRepositoryUser(username.getText());

			String s_password = new String(password.getPassword());
			AppSetup.setRemoteRepositoryPwd(s_password);

		} catch (Exception ee) {
			GuiUtil.showError("Repository Setup: ", ee);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Remote Repository");
		panel1 = new JPanel();
		label4 = new JLabel();
		comboBox1 = new JComboBox<>();
		label1 = new JLabel();
		server = new JTextField();
		label2 = new JLabel();
		username = new JTextField();
		label3 = new JLabel();
		password = new JPasswordField();
		testLogin = new JButton();
		panel2 = new JPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, default, $ugap, default, $lgap, default, $ugap, default, $lgap, fill:[20dlu,default]:grow"));
		add(separator2, cc.xy(1, 5));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:90dlu, $lcgap, [100dlu,default], 3*($lcgap, [50dlu,default]), $lcgap, default:grow",
				"5*(default, $lgap), default"));

			//---- label4 ----
			label4.setText("Repository Type:");
			panel1.add(label4, cc.xy(1, 3));

			//---- comboBox1 ----
			comboBox1.setModel(new DefaultComboBoxModel<>(new String[] {
				"SFTP"
			}));
			comboBox1.setEnabled(false);
			panel1.add(comboBox1, cc.xy(3, 3));

			//---- label1 ----
			label1.setText("Host:");
			panel1.add(label1, cc.xy(1, 5));
			panel1.add(server, cc.xy(3, 5));

			//---- label2 ----
			label2.setText("User Name:");
			panel1.add(label2, cc.xy(1, 7));
			panel1.add(username, cc.xy(3, 7));

			//---- label3 ----
			label3.setText("Password:");
			panel1.add(label3, cc.xy(1, 9));
			panel1.add(password, cc.xy(3, 9));

			//---- testLogin ----
			testLogin.setText("Test");
			testLogin.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					testLoginActionPerformed(e);
				}
			});
			panel1.add(testLogin, cc.xy(7, 9));
		}
		add(panel1, cc.xy(1, 7));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"[90dlu,default], $lcgap, default:grow, $lcgap, default",
				""));
		}
		add(panel2, cc.xy(1, 11));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator2;
	private JPanel panel1;
	private JLabel label4;
	private JComboBox<String> comboBox1;
	private JLabel label1;
	private JTextField server;
	private JLabel label2;
	private JTextField username;
	private JLabel label3;
	private JPasswordField password;
	private JButton testLogin;
	private JPanel panel2;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public boolean next() {
		saveActionPerformed( null );
		
		return true;
	}

	@Override
	public void refresh() {
		wizard.enableNext( true );
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}
}
