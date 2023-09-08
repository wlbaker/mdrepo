/*
 * Created by JFormDesigner on Wed Oct 07 11:47:58 CDT 2009
 */

package idea.tsoffline.export;

import java.awt.BorderLayout;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.filechooser.FileNameExtensionFilter;

import idea.schema.rp.RpStudy;
import idea.gui.UndecoratedFilechooser;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.TsOfflineSetup;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ExportFileSelectionPanel extends JPanel implements WizardPanelInterface, PropertyChangeListener {

	private UndecoratedFilechooser fc;
	private ExportWizard wizard;

	RpStudy profile;

	public ExportFileSelectionPanel(ExportWizard wizard) {
		initComponents();
		
		setName( "File Selection");

		this.wizard = wizard;

		initMore();

		putClientProperty("export.next", false);
		putClientProperty("export.finish", false);
	}
	
	public JFileChooser getFilechooser() {
		return fc;
	}

	private void initMore() {
		fc = new UndecoratedFilechooser();

		// String lastDir = PrefUtil.getUserPref(pref_key, null);
		String lastDir = TsOfflineSetup.getArchiveFile(); // PrefUtil.getUserPref(pref_key, null);

		FileNameExtensionFilter filter = new FileNameExtensionFilter("Study Files: H5", "h5");
		fc.setFileFilter(filter);
		fc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
		fc.setMultiSelectionEnabled( true );
		fc.createDialog(null);
		if (lastDir != null) {
			File f = new File(lastDir);
			fc.setCurrentDirectory( f.getParentFile() );
			// fc.setSelectedFile( f );
		}
		fc.hideOptions();
		// fc.setDialogType(JFileChooser.CUSTOM_DIALOG);
		add(fc.nakedPanel, BorderLayout.CENTER);

		fc.addPropertyChangeListener(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY, this);
		// fc.addPropertyChangeListener(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY, this);
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {

		if (evt.getPropertyName().equals(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY)) {
			wizard.enableNext(evt.getNewValue() != null);
		}

	}

	public File getSelectedFile() {
		return fc.getSelectedFile();
	}

	public File[] getSelectedFiles() {
		return fc.getSelectedFiles();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents

		//======== this ========
		setLayout(new BorderLayout());
		// //GEN-END:initComponents
	}

	@Override
	public boolean next() {

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

	@Override
	public boolean finish() {
		return false;
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
