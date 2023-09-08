/*
 * Created by JFormDesigner on Mon Apr 02 14:46:45 CDT 2012
 */

package idea.tsoffline.derivsigwiz;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.tsoffline.model.DerivedParamsBase;
import idea.tsoffline.model.IBIParameters;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class IBISegementationDetail extends JPanel implements ParameterProvider {
	public IBISegementationDetail() {
		initComponents();
		
		minIBIField.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		maxIBIField.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		flowThresholdField.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		
		minIBIField.setValue( new Integer(1000) );
		maxIBIField.setValue( new Integer(15000) );
		flowThresholdField.setValue( new Integer(100) );
	}

	private void flowEstimateActionPerformed(ActionEvent e) {
		// TODO add your code here
	}


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		functionSeparator = compFactory.createSeparator("IBI Parameters");
		panel2 = new JPanel();
		label2 = new JLabel();
		minIBIField = new JFormattedTextField();
		label4 = new JLabel();
		label1 = new JLabel();
		maxIBIField = new JFormattedTextField();
		label3 = new JLabel();
		flowThresholdField = new JFormattedTextField();
		panel1 = new JPanel();
		flowEstimate = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, default:grow, $lgap, default"));
		add(functionSeparator, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"right:[70dlu,default], $lcgap, [40dlu,default], $lcgap, default:grow",
				"$ugap, 3*($lgap, default), $rgap, default"));

			//---- label2 ----
			label2.setText("Minimum IBI (ms):");
			panel2.add(label2, cc.xy(1, 3));
			panel2.add(minIBIField, cc.xy(3, 3));

			//---- label4 ----
			label4.setText("Shortest allowable breath.");
			panel2.add(label4, cc.xy(5, 3));

			//---- label1 ----
			label1.setText("Maximum IBI (ms):");
			panel2.add(label1, cc.xy(1, 5));
			panel2.add(maxIBIField, cc.xy(3, 5));

			//---- label3 ----
			label3.setText("Flow Threshold:");
			panel2.add(label3, cc.xy(1, 7));
			panel2.add(flowThresholdField, cc.xy(3, 7));

			//======== panel1 ========
			{
				panel1.setLayout(new FormLayout(
					"default, $lcgap, default",
					"default"));

				//---- flowEstimate ----
				flowEstimate.setText("Estimate");
				flowEstimate.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						flowEstimateActionPerformed(e);
					}
				});
				panel1.add(flowEstimate, cc.xy(1, 1));
			}
			panel2.add(panel1, cc.xy(5, 7));
		}
		add(panel2, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent functionSeparator;
	private JPanel panel2;
	private JLabel label2;
	private JFormattedTextField minIBIField;
	private JLabel label4;
	private JLabel label1;
	private JFormattedTextField maxIBIField;
	private JLabel label3;
	private JFormattedTextField flowThresholdField;
	private JPanel panel1;
	private JButton flowEstimate;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public DerivedParamsBase getParameters() {
		IBIParameters params = new IBIParameters();
		
		params.setMinIBI( (Integer)minIBIField.getValue()  );
		params.setMaxIBI( (Integer)maxIBIField.getValue() );
		params.setFlowThreshold( (Integer)flowThresholdField.getValue() );
		return params;
	}
}
