/*
 * Created by JFormDesigner on Wed Apr 17 10:31:22 CDT 2019
 */

package idea.tsoffline.setup;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;
import com.softhorizons.filterdesigner.DesignPanel;

import uk.me.berndporr.api.FilterInterface;
import idea.devwizard.SetupWizardInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author WILLIAM BAKER
 */
public class FilterSetupDesignPanel extends JPanel implements WizardPanelInterface, PropertyChangeListener, DocumentListener  {
	private SetupWizardInterface wizard;
	
	DesignPanel designer;
	FilterInterface filter;
	
	public FilterSetupDesignPanel(SetupWizardInterface wizard) {
		this.wizard = wizard;
		initComponents();
		
		designer = new DesignPanel();
		add(designer, CC.xy(1, 1));
		designer.addPropertyChangeListener("Filter", this);
		
		designer.notifyFilterListeners();  // send an event to "me"
	
		filterName.getDocument().addDocumentListener(this);
		refresh();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label1 = new JLabel();
		filterName = new JTextField();
		label2 = new JLabel();
		filterDetail = new JLabel();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, $rgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, [40dlu,default]:grow, $lcgap, default, $lcgap, [50dlu,default]:grow",
				"default"));

			//---- label1 ----
			label1.setText("Name:");
			panel1.add(label1, CC.xy(1, 1));
			panel1.add(filterName, CC.xy(3, 1));

			//---- label2 ----
			label2.setText("Detail:");
			panel1.add(label2, CC.xy(5, 1));

			//---- filterDetail ----
			filterDetail.setText("filterDetail");
			panel1.add(filterDetail, CC.xy(7, 1));
		}
		add(panel1, CC.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label1;
	private JTextField filterName;
	private JLabel label2;
	private JLabel filterDetail;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void refresh() {
		wizard.enableNext( filterName.getText().length() > 0 );
		filterName.requestFocus();
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean next() {
		
		// check for a valid filter name?
		// filterName.getText()
		return true;
	}

	@Override
	public boolean finish() {
		return false;
	}

	public DesignPanel getDesignPanel() {
		return designer;
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		this.filter = (FilterInterface)evt.getNewValue();
		
		if( filter == null ) {
			filterDetail.setText("");
		} else {
			filterDetail.setText( filter.getDescription() );
		}
		filter.setName( filterName.getText() );

	}

	public FilterInterface getFilter() {
		return filter;
	}

	@Override
	public void insertUpdate(DocumentEvent e) {
		wizard.enableNext( filterName.getText().length() > 0 );
	}

	@Override
	public void removeUpdate(DocumentEvent e) {
		wizard.enableNext( filterName.getText().length() > 0 );
	}

	@Override
	public void changedUpdate(DocumentEvent e) {
		wizard.enableNext( filterName.getText().length() > 0 );
	}
}
