/*
 * Created by JFormDesigner on Wed Apr 17 10:31:22 CDT 2019
 */

package idea.tsoffline.setup;

import javax.swing.JPanel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;
import com.softhorizons.filterdesigner.DesignPanel;
import com.softhorizons.filterdesigner.EvaluatePanel;

import idea.devwizard.SetupWizardInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author WILLIAM BAKER
 */
public class FilterSetupEvaluatePanel extends JPanel implements WizardPanelInterface  {
	private SetupWizardInterface wizard;
	
	EvaluatePanel evaluator;
	public FilterSetupEvaluatePanel(SetupWizardInterface wizard) {
		this.wizard = wizard;
		initComponents();
		
		evaluator = new EvaluatePanel();
		add(evaluator, CC.xy(1, 1));
	}
	
	public void setDesignPanel(DesignPanel designPanel) {
		evaluator.setDesignPanel( designPanel );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow"));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void refresh() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean next() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean finish() {
		// TODO Auto-generated method stub
		return false;
	}

}
