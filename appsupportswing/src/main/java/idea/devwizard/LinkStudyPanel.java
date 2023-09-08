/*
 * Created by JFormDesigner on Mon Oct 05 16:17:27 CDT 2009
 */

package idea.devwizard;


import java.awt.BorderLayout;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;

import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.UndecoratedFilechooser;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class LinkStudyPanel extends JPanel implements WizardPanelInterface, PropertyChangeListener {

	private static final String pref_key = "IMPORT_STUDY_DIR";
	
	private WizardMasterInterface wizard;
	private UndecoratedFilechooser fc;
	public LinkStudyPanel(WizardMasterInterface wizard ) {
		initComponents();
		this.wizard = wizard;
		
		setName( "Study Link" );

		initMore();
	}
	
	private void initMore() {
		fc = new UndecoratedFilechooser();

		String lastDir = PrefUtil.getUserPref(pref_key, null);

		// FileNameExtensionFilter filter = new FileNameExtensionFilter("Study Files: dat, h5", "dat", "h5");
		// fc.setFileFilter(filter);
		fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);     // disable the "All files" option.    
		fc.setAcceptAllFileFilterUsed(false);
		
		fc.createDialog(null);
		if (lastDir != null) {
			fc.setCurrentDirectory(new File(lastDir));
		}
		fc.hideOptions();
		fc.setDialogType(JFileChooser.CUSTOM_DIALOG);

		fc.addPropertyChangeListener(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY, this);
		
		customContent.add(fc.nakedPanel, BorderLayout.CENTER);
		// customContent.add( fc, BorderLayout.CENTER );
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		File f = fc.getSelectedFile();
		boolean ok = false;
		if( f != null && f.isDirectory() ) {
			ok = true;
		}
		
		wizard.enableNext( ok );
	}

	@Override
	public void refresh() {

	}

	@Override
	public boolean next() {
		boolean ok = false;
		RepositoryInterface local = RepositoryFactory.getLocalRepository();
		try {
			File f = fc.getSelectedFile();

			local.createLink( f );
			PrefUtil.saveUserPref(pref_key, f.getPath() );

			wizard.popPageUntil("Study Selection");
			ok = true;
		} catch (Exception e) {
			GuiUtil.showError("Creating Study: ", e);
		}

		return ok;
	}


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		panel1 = new JPanel();
		separator3 = compFactory.createSeparator("Study");
		customContent = new JPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[250dlu,default]:grow",
			"fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow",
				"default, $lgap, fill:default:grow"));
			panel1.add(separator3, cc.xy(1, 1));

			//======== customContent ========
			{
				customContent.setLayout(new BorderLayout());
			}
			panel1.add(customContent, cc.xy(1, 3));
		}
		add(panel1, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JComponent separator3;
	private JPanel customContent;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}


}
