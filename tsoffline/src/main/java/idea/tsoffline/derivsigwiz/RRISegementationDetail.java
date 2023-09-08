/*
 * Created by JFormDesigner on Mon Apr 02 14:46:45 CDT 2012
 */

package idea.tsoffline.derivsigwiz;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.ConfigurationInfo;
import idea.tsoffline.model.DerivedParamsBase;
import idea.tsoffline.model.RRIParameters;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class RRISegementationDetail extends JPanel implements ParameterProvider {
	public RRISegementationDetail() {
		initComponents();
		
		detectorComboBox.setModel(new DefaultComboBoxModel(ConfigurationInfo.getDetectorList()));
	}


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		functionSeparator = compFactory.createSeparator("RRI Segmentation Setup");
		panel2 = new JPanel();
		label2 = new JLabel();
		detectorComboBox = new JComboBox();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, default:grow, $lgap, default"));
		add(functionSeparator, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"right:[50dlu,default], $lcgap, [60dlu,default]",
				"$ugap, $lgap, default, $lgap, $ugap"));

			//---- label2 ----
			label2.setText("Detector:");
			panel2.add(label2, cc.xy(1, 3));
			panel2.add(detectorComboBox, cc.xy(3, 3));
		}
		add(panel2, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent functionSeparator;
	private JPanel panel2;
	private JLabel label2;
	private JComboBox detectorComboBox;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public DerivedParamsBase getParameters() {
		String detectorName = (String) detectorComboBox.getSelectedItem();
		
		RRIParameters params = new RRIParameters();
		params.setDetector(detectorName);
		return params;
	}
}
