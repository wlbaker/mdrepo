/*
 * Created by JFormDesigner on Fri Feb 04 11:51:52 CST 2011
 */

package idea.tsoffline.derivsigwiz;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.tsoffline.TsOfflineSetup;
import idea.tsoffline.model.DerivedParamsBase;
import idea.tsoffline.model.EntropyParameters;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SEParamPanel extends JPanel implements ParameterProvider {
	public SEParamPanel(String prefix, String separatorLabel) {
		initComponents(separatorLabel);

		windowPoints.setFormatterFactory(GuiUtil.getIntegerFormatterFactory());
		toleranceField.setFormatterFactory(GuiUtil.getNumberFormatterFactory());

		TsOfflineSetup setup = TsOfflineSetup.getInstance();
		String txtWindowPoints = setup.persistReadString(prefix + "window", "200");
		String txtEmbedding = setup.persistReadString(prefix + "embedding", "2");
		String txtLag = setup.persistReadString(prefix + "lag", "1");
		String txtTolerance = setup.persistReadString(prefix + "tolerance", "6");
		String txtBaseline = setup.persistReadString(prefix + "baseline", "false");

		try {
			windowPoints.setValue(Integer.valueOf(txtWindowPoints));
			embedDim.setSelectedItem(txtEmbedding);
			lag.setSelectedItem(txtLag);
			toleranceField.setValue(Double.valueOf(txtTolerance));
			baseline.setSelected(Boolean.parseBoolean(txtBaseline));
		} catch (Exception e) {
			System.err.println("[SEParamPanel] could not parse persisted data: " + e.getMessage());
			e.printStackTrace();
		}
	}

	@Override
	public DerivedParamsBase getParameters() {
		EntropyParameters params = new EntropyParameters();
		
		params.setWindow( (Integer) windowPoints.getValue() );
		params.setEmbedding( Integer.parseInt((String) embedDim.getSelectedItem()) );
		params.setLag( Integer.parseInt((String) lag.getSelectedItem()) );
		params.setTolerance( (Double) toleranceField.getValue() );
		params.setBaselineRemoval( baseline.isSelected() );
		return params;
	}
	
	private void initComponents(String separatorLabel) {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		seperatorTitle = compFactory.createSeparator(separatorLabel);
		panel1 = new JPanel();
		label1 = new JLabel();
		panel2 = new JPanel();
		windowPoints = new JFormattedTextField();
		label2 = new JLabel();
		panel3 = new JPanel();
		embedDim = new JComboBox();
		label3 = new JLabel();
		panel4 = new JPanel();
		lag = new JComboBox();
		label4 = new JLabel();
		panel7 = new JPanel();
		toleranceField = new JFormattedTextField();
		panel5 = new JPanel();
		label5 = new JLabel();
		panel6 = new JPanel();
		baseline = new JCheckBox();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "3*(default, $lgap), default"));
		add(seperatorTitle, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setBorder(Borders.DLU4);
			panel1.setLayout(new FormLayout("right:default, $lcgap, [50dlu,default]:grow", "5*(default, $lgap), 12dlu, 2*($lgap, default)"));

			//---- label1 ----
			label1.setText("Window Points:");
			panel1.add(label1, cc.xy(1, 3));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout("[50dlu,default], 2*($lcgap, default)", "default"));
				panel2.add(windowPoints, cc.xy(1, 1));
			}
			panel1.add(panel2, cc.xy(3, 3));

			//---- label2 ----
			label2.setText("Embedding Dimension (m):");
			panel1.add(label2, cc.xy(1, 5));

			//======== panel3 ========
			{
				panel3.setLayout(new FormLayout("[30dlu,default], $lcgap, default", "default"));

				//---- embedDim ----
				embedDim.setModel(new DefaultComboBoxModel(new String[] { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" }));
				embedDim.setEditable(true);
				panel3.add(embedDim, cc.xy(1, 1));
			}
			panel1.add(panel3, cc.xy(3, 5));

			//---- label3 ----
			label3.setText("Lag (J):");
			panel1.add(label3, cc.xy(1, 7));

			//======== panel4 ========
			{
				panel4.setLayout(new FormLayout("[30dlu,default], $lcgap, default", "default"));

				//---- lag ----
				lag.setModel(new DefaultComboBoxModel(new String[] { "1", "2", "3", "4", "5", "6" }));
				lag.setEditable(true);
				panel4.add(lag, cc.xy(1, 1));
			}
			panel1.add(panel4, cc.xy(3, 7));

			//---- label4 ----
			label4.setText("Tolerance (ms):");
			panel1.add(label4, cc.xy(1, 9));

			//======== panel7 ========
			{
				panel7.setLayout(new FormLayout("[50dlu,default], $lcgap, default", "default"));
				panel7.add(toleranceField, cc.xy(1, 1));
			}
			panel1.add(panel7, cc.xy(3, 9));

			//======== panel5 ========
			{
				panel5.setLayout(new FormLayout("default, $lcgap, default", "default"));
			}
			panel1.add(panel5, cc.xy(3, 11));

			//---- label5 ----
			label5.setText("Remove Baseline:");
			panel1.add(label5, cc.xy(1, 13));

			//======== panel6 ========
			{
				panel6.setLayout(new FormLayout("default, $lcgap, default", "default"));

				//---- baseline ----
				baseline.setText("Yes");
				panel6.add(baseline, cc.xy(1, 1));
			}
			panel1.add(panel6, cc.xy(3, 13));
		}
		add(panel1, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent seperatorTitle;
	private JPanel panel1;
	private JLabel label1;
	private JPanel panel2;
	private JFormattedTextField windowPoints;
	private JLabel label2;
	private JPanel panel3;
	private JComboBox embedDim;
	private JLabel label3;
	private JPanel panel4;
	private JComboBox lag;
	private JLabel label4;
	private JPanel panel7;
	private JFormattedTextField toleranceField;
	private JPanel panel5;
	private JLabel label5;
	private JPanel panel6;
	private JCheckBox baseline;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
