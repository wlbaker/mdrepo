/*
 * Created by JFormDesigner on Wed Nov 23 12:10:54 CST 2011
 */

package idea.meddaq.entry;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.JPanel;

import idea.PrefUtil;
import idea.gui.UndecoratedFilechooser;
import idea.gui.WizardPanelInterface;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class LoadFileSelection extends JPanel implements WizardPanelInterface, PropertyChangeListener {
	private static final String pref_key = "LoadFileSelection";
	private UndecoratedFilechooser fc;
	private File file;
	private LoadWizard wiz;

	public LoadFileSelection( LoadWizard wizard) {
		initComponents();

		this.wiz = wizard;
		
		fc = new UndecoratedFilechooser();
		fc.createDialog(null);
		fc.hideOptions();
		fileChooserHolder.add(fc.nakedPanel, BorderLayout.CENTER);
		fc.addPropertyChangeListener(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY, this);

		fc.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				file = fc.getSelectedFile();
				wiz.enableNext( file != null );

			}
		});

		refresh();  // isnt this automatic?
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		fileChooserHolder = new JPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow"));

		//======== fileChooserHolder ========
		{
			fileChooserHolder.setLayout(new BorderLayout());
		}
		add(fileChooserHolder, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel fileChooserHolder;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

	public File getFile() {
		return file;
	}

	@Override
	public void refresh() {

			String lastDir = PrefUtil.getUserPref(pref_key, null);
			if (lastDir != null) {
				fc.setCurrentDirectory(new File(lastDir));
			}

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean next() {
		file = fc.getSelectedFile();
		
		assert( file != null ) : "NEXT should be disabled until file selected.";
		
		if( file != null ) {
			PrefUtil.saveUserPref( pref_key, file.getPath() );
		}
		return true;
	}

	@Override
	public boolean finish() {
		// TODO Auto-generated method stub

		return true;
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		System.out.println("evt=" + evt);
		file = fc.getSelectedFile();
		wiz.enableNext( file != null );
	}
}
