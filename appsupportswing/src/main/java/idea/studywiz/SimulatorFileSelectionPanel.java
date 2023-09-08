/*
 * Created by JFormDesigner on Wed Oct 07 11:47:58 CDT 2009
 */

package idea.studywiz;

import java.awt.BorderLayout;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.UndecoratedFilechooser;
import idea.gui.WizardPanelInterface;
import idea.gui.wizard.DefaultStudyHeaderPanel;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SimulatorFileSelectionPanel extends JPanel implements WizardPanelInterface, PropertyChangeListener {

	private UndecoratedFilechooser fc;
	private SimulationWizard simulationWizard;
	private static final String pref_key = "wizsimulatordir";

	RpStudy profile;

	public SimulatorFileSelectionPanel(SimulationWizard simulationWizard) {
		initComponents();

		this.simulationWizard = simulationWizard;

		initMore();

	}

	private void initMore() {
		fc = new UndecoratedFilechooser();

		String lastDir = PrefUtil.getUserPref(pref_key, null);

		FileNameExtensionFilter filter = new FileNameExtensionFilter("Study Files: dat, h5, stp", "dat", "h5", "stp");
		fc.setFileFilter(filter);

		fc.createDialog(null);
		if (lastDir != null) {
			fc.setCurrentDirectory(new File(lastDir));
		}
		fc.hideOptions();
		// fc.setDialogType(JFileChooser.CUSTOM_DIALOG);
		add(fc.nakedPanel, BorderLayout.CENTER);

		fc.addPropertyChangeListener(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY, this);
	}

	private RpSubject getSubjectInfo(File selectedFile) throws IOException {
		PiSubjectImporter importer = PiImporterUtil.getImporterFromFile(selectedFile);
		importer.connect();
		RpSubject hd = importer.getSubjectInfo();
		importer.disconnect();
		return hd;
	}

	protected void setSimulatorProfile(SimulationWizard wizard) {
		File file = fc.getSelectedFile();

		assert (false) : "setSimulatorProfile code is not ready!";
		// profile = getSelectedProfile( file );
		// wizard.setActiveProfile(profile);

		saveSelectedDir(file);

		RpSubject h = new RpSubject();
		h.setBaseFileName(file.getAbsolutePath());
		h.setCompany("Simulation");
		h.setStudyTitle("Simulation -- Fractal Analysis of Breathing Patterns During CPAP");
		wizard.setStudyHeader(h);
	}

	private RpHardware panelToModel(File file) {
		RpHardware profile = new RpHardware();

		GuiUtil.showMessage("FIXME: getSimulationDriver not ready");
		// DeviceConfiguration conf = SimulationDriver.createConfigInstance();
		//
		// System.err.println( "NOT READY: getSimulationDriver() ");
		// conf.setImporterFile(file.getAbsolutePath());

		assert (false) : "this code has not been converted to use RpStudy";
		// profile.addDevice( conf );

		return profile;
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {

		if (evt.getPropertyName().equals(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY)) {
			simulationWizard.enableNext(evt.getNewValue() != null);
		}

	}

	public File getSelectedFile() {
		return fc.getSelectedFile();
	}

	private void saveSelectedDir(File f) {
		if (f != null) {
			String parent = f.getParent();
			PrefUtil.saveUserPref(pref_key, parent);
		}
	}

	// public DeviceConfiguration getDeviceProfile() {
	// File f = getSelectedFile();
	// saveSelectedDir(f);
	//
	// DeviceConfiguration dp = SimulationDriver.createConfigInstance();
	// if (f != null) {
	// dp.setKeyValue("file", f.getAbsolutePath());
	// dp.setName("Simulation using " + f.getAbsolutePath());
	// }
	// return dp;
	// }

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents

		// ======== this ========
		setLayout(new BorderLayout());
		// //GEN-END:initComponents
	}

	@Override
	public boolean finish() {
		SimulationWizard wizard = SimulationWizard.getInstance();
		setSimulatorProfile(wizard);
		
		return true;
	}

	@Override
	public boolean next() {

		boolean ok = false;
		
		RpSubject header;
		try {
			header = getSubjectInfo(fc.getSelectedFile());
			SimulationWizard wizard = SimulationWizard.getInstance();
			setSimulatorProfile(wizard);

			panelToModel(null); // FIXME: I just stuck this in here as a
								// reminder

			DefaultStudyHeaderPanel studyInfo = null;
			assert (false) : "I LEFT THIS INCOMPLETE";
			// new DefaultStudyHeaderPanel(profile, false);
			studyInfo.setViewOnly(true);
			studyInfo.setStudyHeader(header);

			wizard.pushPage(studyInfo);
			ok = true;
		} catch (IOException e1) {
			GuiUtil.showError("Error opening study file", e1);
		}
		return ok;
	}

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
