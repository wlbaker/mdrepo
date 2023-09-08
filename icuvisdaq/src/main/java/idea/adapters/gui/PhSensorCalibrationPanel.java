/*
 * Created by JFormDesigner on Mon Jan 26 12:07:13 CST 2015
 */

package idea.adapters.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DecimalFormat;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
public class PhSensorCalibrationPanel extends JPanel {

	private boolean lowerlimit_ok = false;
	private boolean upperlimit_ok = false;

	public PhSensorCalibrationPanel() {
		initComponents();

		pHUpperLimitField.setFormatterFactory( GuiUtil.getNumberFormatterFactory());
		pHLowerLimitField.setFormatterFactory( GuiUtil.getNumberFormatterFactory());
		
		co2UpperLimitField.setFormatterFactory( GuiUtil.getNumberFormatterFactory());
		co2LowerLimitField.setFormatterFactory( GuiUtil.getNumberFormatterFactory());
		
		reset();
		updateButtons();
	}

	private void acceptLowerCalibrationActionPerformed(ActionEvent e) {
		lowerlimit_ok = true;
		updateButtons();
		
		if( upperlimit_ok && lowerlimit_ok ) {
			GuiUtil.closeDialog(this);
		}
	}

	private void acceptUpperCalibrationActionPerformed(ActionEvent e) {
		upperlimit_ok = true;
		updateButtons();
		
		if( upperlimit_ok && lowerlimit_ok ) {
			GuiUtil.closeDialog(this);
		}
	}

	private void updateButtons() {
//		acceptLowerCalibration.setText(lowerlimit_ok ? "Reset" : "Accept");
//		acceptUpperCalibration.setText(upperlimit_ok ? "Reset" : "Accept");
		acceptLowerCalibration.setEnabled( !lowerlimit_ok );
		acceptUpperCalibration.setEnabled( !upperlimit_ok );

		pHUpperLimitField.setEnabled(!upperlimit_ok);
		co2UpperLimitField.setEnabled(!upperlimit_ok);

		pHLowerLimitField.setEnabled(!lowerlimit_ok);
		co2LowerLimitField.setEnabled(!lowerlimit_ok);
	}

	public boolean isOK() {
		return lowerlimit_ok && upperlimit_ok;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Lower Limit");
		panel2 = new JPanel();
		label7 = new JLabel();
		degLowerLimitLabel = new JLabel();
		label3 = new JLabel();
		voltageLowerLimitLabel = new JLabel();
		label1 = new JLabel();
		pHLowerLimitField = new JFormattedTextField();
		label2 = new JLabel();
		co2LowerLimitField = new JFormattedTextField();
		acceptLowerCalibration = new JButton();
		separator2 = compFactory.createSeparator("Upper Limit");
		panel3 = new JPanel();
		label8 = new JLabel();
		degUpperLimitLabel = new JLabel();
		label4 = new JLabel();
		voltageUpperLimitLabel = new JLabel();
		label5 = new JLabel();
		pHUpperLimitField = new JFormattedTextField();
		label6 = new JLabel();
		co2UpperLimitField = new JFormattedTextField();
		acceptUpperCalibration = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "3*(default, $lgap), default, $rgap, default"));
		add(separator1, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
					"[20dlu,default], $lcgap, right:[30dlu,default], $lcgap, [50dlu,default], $lcgap, default:grow, $lcgap, [50dlu,default]",
					"5*(default, $lgap), default"));

			//---- label7 ----
			label7.setText("Temperature:");
			panel2.add(label7, cc.xy(3, 3));

			//---- degLowerLimitLabel ----
			degLowerLimitLabel.setText("text");
			panel2.add(degLowerLimitLabel, cc.xy(5, 3));

			//---- label3 ----
			label3.setText("Voltage:");
			panel2.add(label3, cc.xy(3, 5));

			//---- voltageLowerLimitLabel ----
			voltageLowerLimitLabel.setText("---");
			panel2.add(voltageLowerLimitLabel, cc.xy(5, 5));

			//---- label1 ----
			label1.setText("pH:");
			panel2.add(label1, cc.xy(3, 7));
			panel2.add(pHLowerLimitField, cc.xy(5, 7));

			//---- label2 ----
			label2.setText("CO2:");
			panel2.add(label2, cc.xy(3, 9));
			panel2.add(co2LowerLimitField, cc.xy(5, 9));

			//---- acceptLowerCalibration ----
			acceptLowerCalibration.setText("Accept");
			acceptLowerCalibration.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					acceptLowerCalibrationActionPerformed(e);
				}
			});
			panel2.add(acceptLowerCalibration, cc.xy(9, 11));
		}
		add(panel2, cc.xy(1, 3));
		add(separator2, cc.xy(1, 5));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
					"[20dlu,default], $lcgap, right:[30dlu,default], $lcgap, [50dlu,default], $lcgap, default:grow, $lcgap, [50dlu,default]",
					"5*(default, $lgap), default"));

			//---- label8 ----
			label8.setText("Temperature:");
			panel3.add(label8, cc.xy(3, 3));

			//---- degUpperLimitLabel ----
			degUpperLimitLabel.setText("text");
			panel3.add(degUpperLimitLabel, cc.xy(5, 3));

			//---- label4 ----
			label4.setText("Voltage:");
			panel3.add(label4, cc.xy(3, 5));

			//---- voltageUpperLimitLabel ----
			voltageUpperLimitLabel.setText("---");
			panel3.add(voltageUpperLimitLabel, cc.xy(5, 5));

			//---- label5 ----
			label5.setText("pH:");
			panel3.add(label5, cc.xy(3, 7));
			panel3.add(pHUpperLimitField, cc.xy(5, 7));

			//---- label6 ----
			label6.setText("CO2:");
			panel3.add(label6, cc.xy(3, 9));
			panel3.add(co2UpperLimitField, cc.xy(5, 9));

			//---- acceptUpperCalibration ----
			acceptUpperCalibration.setText("Accept");
			acceptUpperCalibration.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					acceptUpperCalibrationActionPerformed(e);
				}
			});
			panel3.add(acceptUpperCalibration, cc.xy(9, 11));
		}
		add(panel3, cc.xy(1, 7));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel2;
	private JLabel label7;
	private JLabel degLowerLimitLabel;
	private JLabel label3;
	private JLabel voltageLowerLimitLabel;
	private JLabel label1;
	private JFormattedTextField pHLowerLimitField;
	private JLabel label2;
	private JFormattedTextField co2LowerLimitField;
	private JButton acceptLowerCalibration;
	private JComponent separator2;
	private JPanel panel3;
	private JLabel label8;
	private JLabel degUpperLimitLabel;
	private JLabel label4;
	private JLabel voltageUpperLimitLabel;
	private JLabel label5;
	private JFormattedTextField pHUpperLimitField;
	private JLabel label6;
	private JFormattedTextField co2UpperLimitField;
	private JButton acceptUpperCalibration;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

	public PhCO2Calibration getLowerLimitCalibration() {
		PhCO2Calibration rt = new PhCO2Calibration();
		rt.setCo2( asDouble(co2LowerLimitField));
		rt.setPh(asDouble(pHLowerLimitField));
		double voltage = -1;
		try {
			voltage = Double.parseDouble(voltageLowerLimitLabel.getText());
		} catch (Exception e) {

		}
		rt.setMv(voltage);
		return rt;
	}

	public PhCO2Calibration getUpperLimitCalibration() {
		PhCO2Calibration rt = new PhCO2Calibration();
		rt.setCo2( asDouble(co2UpperLimitField));
		rt.setPh(asDouble(pHUpperLimitField));
		double voltage = -1;
		try {
			voltage = Double.parseDouble(voltageUpperLimitLabel.getText());
		} catch (Exception e) {

		}
		rt.setMv(voltage);
		return rt;
	}

	private double asDouble(JFormattedTextField fld) {
		Number n = (Number) fld.getValue();
		return n.doubleValue();
	}

	public void setVoltage(DecimalFormat df2, double v) {
		String txt = df2.format(v);
		if( !lowerlimit_ok ) {
			voltageLowerLimitLabel.setText( txt );
		}
		if( !upperlimit_ok ) {
			voltageUpperLimitLabel.setText( txt );
		}
	}

	public void reset() {
		lowerlimit_ok = false;
		upperlimit_ok = false;
		
		degLowerLimitLabel.setText("---");
		degUpperLimitLabel.setText("---");
		
		voltageLowerLimitLabel.setText("---");
		voltageUpperLimitLabel.setText("---");
		updateButtons();
	}
}
