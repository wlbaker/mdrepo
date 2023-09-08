/*
 * Created by JFormDesigner on Wed Oct 07 11:47:58 CDT 2009
 */

package idea.tsoffline.importwiz;

import java.awt.BorderLayout;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.util.prefs.BackingStoreException;

import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

import idea.schema.rp.RpStudy;
import lombok.extern.slf4j.Slf4j;
import idea.gui.UndecoratedFilechooser;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.TsOfflineSetup;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class ImportFileSelectionPanel extends JPanel implements WizardPanelInterface, PropertyChangeListener {

	private UndecoratedFilechooser fc;
	private WizardMasterInterface wizard;

	// RpSubject header;
	RpStudy profile;

	public ImportFileSelectionPanel(WizardMasterInterface wizard) {
		initComponents();

		this.wizard = wizard;

		initMore();

	}

	private void initMore() {
		fc = new UndecoratedFilechooser();

		fc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);

		// String lastDir = PrefUtil.getUserPref(pref_key, null);
		String lastDir = TsOfflineSetup.getArchiveFile(); // PrefUtil.getUserPref(pref_key,
															// null);

		FileNameExtensionFilter session_filter = new FileNameExtensionFilter("Session Files: spad, xml, stp", "spad", "xml", "stp");
		FileNameExtensionFilter study_filter = new FileNameExtensionFilter("Study Files: dat, h5", "dat", "h5" );
		fc.setFileFilter(session_filter);
		fc.addChoosableFileFilter(  study_filter);

		fc.createDialog(null);
		if (lastDir != null) {
			fc.setCurrentDirectory(new File(lastDir));
		}
		fc.hideOptions();
		// fc.setDialogType(JFileChooser.CUSTOM_DIALOG);
		add(fc.nakedPanel, BorderLayout.CENTER);

		fc.addPropertyChangeListener(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY, this);
		// fc.addPropertyChangeListener( (PropertyChangeEvent evt) -> {
		// System.out.println( evt.getPropertyName() + "--> " +
		// evt.getNewValue() );} );
	}

	private void panelToModel(File file) {
		log.error("FIXME: need function PiImporterUtil.getStudyFromFile(file)");
		profile = null; // PiImporterUtil.getStudyFromFile(file);
		return;
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {

		if (evt.getPropertyName().equals(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY)) {
			// System.out.println("evt=" + evt.getNewValue() );
			// System.out.println("file=" + fc.getSelectedFile() );
			// System.out.println("current dir=" + fc.getCurrentDirectory() );
			File currentDir = fc.getCurrentDirectory();
			File selected = fc.getSelectedFile();
			boolean empty = (evt.getNewValue() == null);
			if (selected != null && selected.isDirectory()) {
				// System.out.println("selected parent=" +
				// fc.getSelectedFile().getParent() );
				File parent = selected.getParentFile();
				if (parent.isDirectory() == false) {
					// JAVA BUG: this is the case of a share.
					parent = selected;
					empty = true; // treat as if no file/directory is
									// selected..don't enable finish
				}
				if (currentDir == null || !currentDir.equals(parent)) {
					fc.setCurrentDirectory(parent);
				}
			}
			wizard.enableNext(!empty);
			wizard.enableFinish(!empty);
		}

	}

	public File getSelectedFile() {
		return fc.getSelectedFile();
	}

	private void saveSelectedDir(File f) {
		if (f != null) {
			String parent = f.getParent();
			// PrefUtil.saveUserPref(pref_key, parent);
			try {
				TsOfflineSetup.setArchiveFile(parent);
			} catch (BackingStoreException e) {
				log.error("saveSelectedDir()", e);
			}
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
		return next();
	}

	@Override
	public boolean next() {

		File file = fc.getSelectedFile();
		// header = DaqUtil.readDaqHeader(file);

		saveSelectedDir(file);

		// header.setBaseFileName(file.getAbsolutePath());
		// header.setCompany("Simulation");

		panelToModel(null); // FIXME: here as a reminder

		return true;
	}

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	public RpStudy getSelectedStudy() {
		return profile;
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
