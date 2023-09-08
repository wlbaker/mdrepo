/*
 * Created by JFormDesigner on Mon Oct 05 16:17:27 CDT 2009
 */

package idea.wizfx;

import java.io.File;
import java.io.IOException;
import java.net.URL;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
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
public class SiteSetupController implements WizardPanelInterface {

	@FXML
	private TextField dir;
	@FXML
	private Button browse;
	@FXML
	private TextField company;
	@FXML
	private TextField organization;
	@FXML
	private URL location;

	private WizardMasterInterface wizard;

	public SiteSetupController() {
		// wizardless setup!
	}
	
	public void setWizard(WizardMasterInterface wizard) {
		this.wizard = wizard;

		//? setName("Site Identification");
		refresh();

		wizard.enableNext(true);
		wizard.enableFinish(false);

		dir.setText(AppSetup.getLocalRepositoryDir());

	}

	@Override
	public void refresh() {
		try {
			SiteInfo info = AppSetup.readSiteInfo(AppSetup.getLocalRepositoryDir() + "/site.xml");
			setTextField(company, info.getCompany());
			setTextField(organization, info.getOrganization());
			// setTextField(location, info.getLocation());

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

	private void setTextField(TextField tf, String val) {
		if (val == null) {
			tf.setText("");
		} else {
			tf.setText(val);
		}
	}

//	private void browseActionPerformed(ActionEvent e) {
//		File parent = null;
//		String lastDir = PrefUtil.getUserPref(AppSetup.getLocalRepositoryDir(), null);
//		if (lastDir != null) {
//			parent = new File(lastDir);
//		}
//
//		GuiUtil.doOpenFileChooser(JFileChooser.DIRECTORIES_ONLY, "Local Repository", this, parent,
//				new ActionListener() {
//
//					@Override
//					public void actionPerformed(ActionEvent e) {
//						File file = (File) e.getSource();
//						dir.setText(file.getAbsolutePath());
//					}
//				});
//	}

	@Override
	public boolean next() {

		boolean ok = false;

		try {
			SiteInfo siteInfo = new SiteInfo();
			siteInfo.setCompany(company.getText());
			// siteInfo.setLocation(location.getText());
			siteInfo.setOrganization(organization.getText());

			AppSetup.setLocalRepositoryDir(dir.getText());

			File repoDir = new File(AppSetup.getLocalRepositoryDir());
			if (repoDir.exists() == false) {
				System.err.println("FIXME: showConformDialog");
//				int yes = GuiUtil.showConfirmDialog("Repository directory does not exist: " + repoDir
//						+ "\n\nCreate Directory?", "Create Directory", JOptionPane.YES_NO_OPTION);
//				if (yes == JOptionPane.OK_OPTION) {
					ok = repoDir.mkdirs();

					if (ok == false) {
						throw new RuntimeException("Could not create directory: " + repoDir);
					}
//				} else {
//					return false;
//				}

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

	@Override
	public void dump() {
		System.out.println("location=" + location);
	}

}
