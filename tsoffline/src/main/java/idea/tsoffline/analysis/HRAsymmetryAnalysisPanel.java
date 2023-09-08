/*
 * Created by JFormDesigner on Tue Sep 28 13:30:34 CDT 2010
 */

package idea.tsoffline.analysis;

import java.text.DecimalFormat;

import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class HRAsymmetryAnalysisPanel extends JPanel {
	DecimalFormat df2 = new DecimalFormat( "0.00");

	public HRAsymmetryAnalysisPanel() {
		initComponents();
	}
	
	public void process(long startTime, long endTime, double[] signal) {
		
	}
	
	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		label3 = new JLabel();
		pNN10 = new JLabel();
		label10 = new JLabel();
		mse1 = new JLabel();
		label14 = new JLabel();
		asym002 = new JLabel();
		label1 = new JLabel();
		label15 = new JLabel();
		label17 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"right:[50dlu,default], $lcgap, [50dlu,default], $lcgap, default, $lcgap, right:[50dlu,default], $lcgap, [50dlu,default], 2*($lcgap, default), $lcgap, [50dlu,default]",
			"5*(default, $lgap), default"));

		//---- label3 ----
		label3.setText("pNN10:");
		add(label3, cc.xy(1, 3));

		//---- pNN10 ----
		pNN10.setText("text");
		add(pNN10, cc.xy(3, 3));

		//---- label10 ----
		label10.setText("SD1/up");
		add(label10, cc.xy(7, 3));

		//---- mse1 ----
		mse1.setText("text");
		add(mse1, cc.xy(9, 3));

		//---- label14 ----
		label14.setText("Asymmetry (r=0.002):");
		add(label14, cc.xy(13, 3));

		//---- asym002 ----
		asym002.setText("text");
		add(asym002, cc.xy(15, 3));

		//---- label1 ----
		label1.setText("SD1/down");
		add(label1, cc.xy(7, 5));

		//---- label15 ----
		label15.setText("Asymmetry (r=0.004):");
		add(label15, cc.xy(13, 5));

		//---- label17 ----
		label17.setText("text");
		add(label17, cc.xy(15, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JLabel label3;
	private JLabel pNN10;
	private JLabel label10;
	private JLabel mse1;
	private JLabel label14;
	private JLabel asym002;
	private JLabel label1;
	private JLabel label15;
	private JLabel label17;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
