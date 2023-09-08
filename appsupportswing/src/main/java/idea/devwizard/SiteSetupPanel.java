/*
 * Created by JFormDesigner on Mon Oct 05 16:17:27 CDT 2009
 */

package idea.devwizard;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.gui.wizard.SiteInfo;
import idea.meddaq.AppSetup;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SiteSetupPanel extends JPanel implements WizardPanelInterface {

	private static final int OBJECT_COL = 0;
	private WizardMasterInterface wizard;

	public SiteSetupPanel(WizardMasterInterface wizard) {
		initComponents();
		this.wizard = wizard;

		setName("Site Identification");
		refresh();

		wizard.enableNext(true);
		wizard.enableFinish(false);

		GuiUtil.initPanel(this);

		dir.setText(AppSetup.getLocalRepositoryDir());

	}

	@Override
	public void refresh() {
		try {
			SiteInfo info = AppSetup.readSiteInfo(AppSetup.getLocalRepositoryDir() + "/site.xml");
			setTextField(company, info.getCompany());
			setTextField(organization, info.getOrganization());
			setTextField(location, info.getLocation());

		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SAXException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void setTextField(JTextField tf, String val) {
		if (val == null) {
			tf.setText("");
		} else {
			tf.setText(val);
		}
	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = PrefUtil.getUserPref(AppSetup.getLocalRepositoryDir(), null);
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.DIRECTORIES_ONLY, "Local Repository", this, parent,
				new ActionListener() {

					@Override
					public void actionPerformed(ActionEvent e) {
						File file = (File) e.getSource();
						dir.setText(file.getAbsolutePath());
					}
				});
	}

	@Override
	public boolean next() {

		boolean ok = false;

		try {
			SiteInfo siteInfo = new SiteInfo();
			siteInfo.setCompany(company.getText());
			siteInfo.setLocation(location.getText());
			siteInfo.setOrganization(organization.getText());

			AppSetup.setLocalRepositoryDir(dir.getText());

			File repoDir = new File(AppSetup.getLocalRepositoryDir());
			if (repoDir.exists() == false) {
				int yes = GuiUtil.showConfirmDialog("Repository directory does not exist: " + repoDir
						+ "\n\nCreate Directory?", "Create Directory", JOptionPane.YES_NO_OPTION);
				if (yes == JOptionPane.OK_OPTION) {
					ok = repoDir.mkdirs();

					if (ok == false) {
						throw new RuntimeException("Could not create directory: " + repoDir);
					}
				} else {
					return false;
				}

			}
			AppSetup.saveSiteSetup(AppSetup.getLocalRepositoryDir() + "/site.xml", siteInfo);

			ok = true;
		} catch (Exception e) {
			GuiUtil.showError("Site Setup Error", e);
		}

		return ok;
	}

	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Local Study Files");
		panel3 = new JPanel();
		label5 = new JLabel();
		dir = new JTextField();
		browse = new JButton();
		separator2 = compFactory.createSeparator("Site Identification");
		panel2 = new JPanel();
		label4 = new JLabel();
		label3 = new JLabel();
		company = new JTextField();
		organization = new JTextField();
		location = new JTextField();
		label1 = new JLabel();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[250dlu,default]:grow",
			"2*(default, $lgap), default, $rgap, fill:default:grow, $lgap, default"));
		add(separator1, CC.xy(1, 1));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"right:50dlu, $lcgap, [160dlu,default]:grow, $lcgap, [50dlu,default], $lcgap, 70dlu",
				"12dlu, $lgap, default, $lgap, 12dlu"));

			//---- label5 ----
			label5.setText("Directory:");
			panel3.add(label5, CC.xy(1, 3));
			panel3.add(dir, CC.xy(3, 3));

			//---- browse ----
			browse.setText("Browse");
			browse.addActionListener(e -> browseActionPerformed(e));
			panel3.add(browse, CC.xy(5, 3));
		}
		add(panel3, CC.xy(1, 3));
		add(separator2, CC.xy(1, 5));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"right:50dlu, $lcgap, 140dlu, $lcgap, default, $lcgap, 84dlu",
				"3*(default, $lgap), default"));

			//---- label4 ----
			label4.setText("Organization:");
			panel2.add(label4, CC.xy(1, 5));

			//---- label3 ----
			label3.setText("Company:");
			panel2.add(label3, CC.xy(1, 3));

			//---- company ----
			company.setText("US Army Institute of Surgical Research");
			panel2.add(company, CC.xy(3, 3));

			//---- organization ----
			organization.setText("CCCE");
			panel2.add(organization, CC.xy(3, 5));

			//---- location ----
			location.setText("Brooke Army Medical Center");
			panel2.add(location, CC.xy(3, 7));

			//---- label1 ----
			label1.setText("Location:");
			panel2.add(label1, CC.xy(1, 7));
		}
		add(panel2, CC.xy(1, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel3;
	private JLabel label5;
	private JTextField dir;
	private JButton browse;
	private JComponent separator2;
	private JPanel panel2;
	private JLabel label4;
	private JLabel label3;
	private JTextField company;
	private JTextField organization;
	private JTextField location;
	private JLabel label1;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
