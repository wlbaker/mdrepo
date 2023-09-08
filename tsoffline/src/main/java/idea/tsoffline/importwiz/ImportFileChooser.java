package idea.tsoffline.importwiz;

import java.awt.BorderLayout;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;

import javax.swing.JPanel;

import idea.PrefUtil;
import idea.gui.UndecoratedFilechooser;
import idea.gui.WizardPanelInterface;

@SuppressWarnings("serial")
class ImporterFilechooser extends JPanel implements WizardPanelInterface {
	private static final String PREF_KEY = "IMPORT_WIZ";

	UndecoratedFilechooser fc;
	
	public ImporterFilechooser() {
		
		fc = new UndecoratedFilechooser();
		fc.createDialog(null);
		fc.hideOptions();

		refresh();

		fc.addPropertyChangeListener("SelectedFileChangedProperty", new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				// UndecoratedFilechooser source = evt.getSource();
				ImportWizard wiz = ImportWizard.getInstance();
				System.out.println("fc property: " + evt + " propname=" + evt.getPropertyName() + " value="
						+ evt.getNewValue());
				wiz.enableNext( evt.getNewValue() != null );
				wiz.setImportFile( (File)evt.getNewValue() );
			}
		});
		
		this.setLayout( new BorderLayout() );
		this.add( fc.nakedPanel, BorderLayout.CENTER );
	}
	
	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public boolean next() {

		ImportWizard wiz = ImportWizard.getInstance();
		
		File lastFile = wiz.getImportFile();
		try {
			PrefUtil.saveUserPref(PREF_KEY, lastFile.getCanonicalPath() );
		} catch (IOException e) {
			// mostly ignore if not successful
			e.printStackTrace();
		}

		JPanel page = new SignalSelectionPanel();
		page.setName("Signal Selection");

		wiz.pushPage(page);
		return true;

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public void refresh() {
		String lastDir = PrefUtil.getUserPref(PREF_KEY, null);
		if (lastDir != null) {
			fc.setCurrentDirectory(new File(lastDir));
		}
	}

}

