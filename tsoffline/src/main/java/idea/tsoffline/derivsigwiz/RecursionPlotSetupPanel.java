/*
 * Created by JFormDesigner on Tue Feb 15 12:00:41 CST 2011
 */

package idea.tsoffline.derivsigwiz;

import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.tsoffline.model.DerivedParamsBase;
import idea.tsoffline.model.RecursionParameters;

/**
 * @author User #2
 */
public class RecursionPlotSetupPanel extends JPanel implements ParameterProvider {
	public RecursionPlotSetupPanel() {
		initComponents();
	}
	
	@Override
	public DerivedParamsBase getParameters() {
		RecursionParameters params = new RecursionParameters();
		// params.setDetector(detector);
		return params;
	}
	

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Recursion Plot Setup");
		panel1 = new JPanel();
		label1 = new JLabel();
		m = new JFormattedTextField();
		label2 = new JLabel();
		J = new JFormattedTextField();
		label4 = new JLabel();
		continuousDiscrete = new JComboBox();
		label5 = new JLabel();
		discreteStart = new JFormattedTextField();
		label6 = new JLabel();
		discreteStep = new JFormattedTextField();
		label3 = new JLabel();
		colorScheme = new JComboBox();
		separator2 = compFactory.createSeparator("Signal Selection");
		panel2 = new JPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"5*(default, $lgap), default"));
		add(separator1, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[50dlu,default], $lcgap, [30dlu,default], $lcgap, [20dlu,default], $lcgap, default",
				"5*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Dimension (m):");
			panel1.add(label1, cc.xy(1, 1));
			panel1.add(m, cc.xy(3, 1));

			//---- label2 ----
			label2.setText("Lag (J):");
			panel1.add(label2, cc.xy(1, 3));
			panel1.add(J, cc.xy(3, 3));

			//---- label4 ----
			label4.setText("Continuous/Discrete:");
			panel1.add(label4, cc.xy(1, 5));
			panel1.add(continuousDiscrete, cc.xywh(3, 5, 3, 1));

			//---- label5 ----
			label5.setText("Discrete Start:");
			panel1.add(label5, cc.xy(1, 7));
			panel1.add(discreteStart, cc.xy(3, 7));

			//---- label6 ----
			label6.setText("Discrete Step:");
			panel1.add(label6, cc.xy(1, 9));
			panel1.add(discreteStep, cc.xy(3, 9));

			//---- label3 ----
			label3.setText("Color Scheme:");
			panel1.add(label3, cc.xy(1, 11));
			panel1.add(colorScheme, cc.xywh(3, 11, 3, 1));
		}
		add(panel1, cc.xy(1, 5));
		add(separator2, cc.xy(1, 9));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default, $lcgap, default",
				"2*(default, $lgap), default"));
		}
		add(panel2, cc.xy(1, 11));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label1;
	private JFormattedTextField m;
	private JLabel label2;
	private JFormattedTextField J;
	private JLabel label4;
	private JComboBox continuousDiscrete;
	private JLabel label5;
	private JFormattedTextField discreteStart;
	private JLabel label6;
	private JFormattedTextField discreteStep;
	private JLabel label3;
	private JComboBox colorScheme;
	private JComponent separator2;
	private JPanel panel2;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
