/*
 * Created by JFormDesigner on Tue Sep 28 13:30:34 CDT 2010
 */

package idea.tsoffline.analysis;

import java.text.DecimalFormat;

import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.analysis.MultiscaleEntropyProcessor;
import idea.analysis.PNNxProcessor;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class MSEAnalysisPanel extends JPanel {
	private final static double[] buckets = { 10.0, 20.0, 30.0, 40.0, 50.0 };

	private final double r = 0.15; // tolorence as a pct of std
	private final int m = 2; // epoch

	DecimalFormat df2 = new DecimalFormat("0.00");
	DecimalFormat df3 = new DecimalFormat("0.000");

	public MSEAnalysisPanel() {
		initComponents();
	}

	public void process(long startTime, long endTime, int[] signal) {

		double[] pnnx = PNNxProcessor.PNNx(buckets, signal);

		if (pnnx != null) {
			pNN10.setText(df2.format(100 * pnnx[0]));
			pNN20.setText(df2.format(100 * pnnx[1]));
			pNN30.setText(df2.format(100 * pnnx[2]));
			pNN40.setText(df2.format(100 * pnnx[3]));
			pNN50.setText(df2.format(100 * pnnx[4]));
		}

		// SignalBuffer<Double> signal = new SignalBuffer<Double>(signalD, true);
		double val1 = MultiscaleEntropyProcessor.process(signal, 1, r, m);
		double val2 = MultiscaleEntropyProcessor.process(signal, 2, r, m);
		double val3 = MultiscaleEntropyProcessor.process(signal, 3, r, m);
		double val4 = MultiscaleEntropyProcessor.process(signal, 4, r, m);
		double val5 = MultiscaleEntropyProcessor.process(signal, 5, r, m);

		mse1.setText(df3.format(val1));
		mse2.setText(df3.format(val2));
		mse3.setText(df3.format(val3));
		mse4.setText(df3.format(val4));
		mse5.setText(df3.format(val5));
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		label6 = new JLabel();
		label3 = new JLabel();
		pNN10 = new JLabel();
		label10 = new JLabel();
		mse1 = new JLabel();
		label14 = new JLabel();
		asym002 = new JLabel();
		label1 = new JLabel();
		pNN20 = new JLabel();
		label11 = new JLabel();
		mse2 = new JLabel();
		label15 = new JLabel();
		label17 = new JLabel();
		label2 = new JLabel();
		pNN30 = new JLabel();
		label12 = new JLabel();
		mse3 = new JLabel();
		label4 = new JLabel();
		pNN40 = new JLabel();
		label13 = new JLabel();
		mse4 = new JLabel();
		label5 = new JLabel();
		pNN50 = new JLabel();
		label16 = new JLabel();
		mse5 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
				"right:[50dlu,default], $lcgap, [50dlu,default], $lcgap, default, $lcgap, right:[50dlu,default], $lcgap, [50dlu,default], 2*($lcgap, default), $lcgap, [50dlu,default]",
				"6*(default, $lgap), default"));

		//---- label6 ----
		label6.setText("m=2,r=0.15");
		add(label6, cc.xy(9, 1));

		//---- label3 ----
		label3.setText("pNN10:");
		add(label3, cc.xy(1, 3));

		//---- pNN10 ----
		pNN10.setText("text");
		add(pNN10, cc.xy(3, 3));

		//---- label10 ----
		label10.setText("MSE (s=1):");
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
		label1.setText("pNN20:");
		add(label1, cc.xy(1, 5));

		//---- pNN20 ----
		pNN20.setText("text");
		add(pNN20, cc.xy(3, 5));

		//---- label11 ----
		label11.setText("MSE (s=2):");
		add(label11, cc.xy(7, 5));

		//---- mse2 ----
		mse2.setText("text");
		add(mse2, cc.xy(9, 5));

		//---- label15 ----
		label15.setText("Asymmetry (r=0.004):");
		add(label15, cc.xy(13, 5));

		//---- label17 ----
		label17.setText("text");
		add(label17, cc.xy(15, 5));

		//---- label2 ----
		label2.setText("pNN30:");
		add(label2, cc.xy(1, 7));

		//---- pNN30 ----
		pNN30.setText("text");
		add(pNN30, cc.xy(3, 7));

		//---- label12 ----
		label12.setText("MSE (s=3):");
		add(label12, cc.xy(7, 7));

		//---- mse3 ----
		mse3.setText("text");
		add(mse3, cc.xy(9, 7));

		//---- label4 ----
		label4.setText("pNN40:");
		add(label4, cc.xy(1, 9));

		//---- pNN40 ----
		pNN40.setText("text");
		add(pNN40, cc.xy(3, 9));

		//---- label13 ----
		label13.setText("MSE (s=4):");
		add(label13, cc.xy(7, 9));

		//---- mse4 ----
		mse4.setText("text");
		add(mse4, cc.xy(9, 9));

		//---- label5 ----
		label5.setText("pNN50:");
		add(label5, cc.xy(1, 11));

		//---- pNN50 ----
		pNN50.setText("text");
		add(pNN50, cc.xy(3, 11));

		//---- label16 ----
		label16.setText("MSE (s=5):");
		add(label16, cc.xy(7, 11));

		//---- mse5 ----
		mse5.setText("text");
		add(mse5, cc.xy(9, 11));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JLabel label6;
	private JLabel label3;
	private JLabel pNN10;
	private JLabel label10;
	private JLabel mse1;
	private JLabel label14;
	private JLabel asym002;
	private JLabel label1;
	private JLabel pNN20;
	private JLabel label11;
	private JLabel mse2;
	private JLabel label15;
	private JLabel label17;
	private JLabel label2;
	private JLabel pNN30;
	private JLabel label12;
	private JLabel mse3;
	private JLabel label4;
	private JLabel pNN40;
	private JLabel label13;
	private JLabel mse4;
	private JLabel label5;
	private JLabel pNN50;
	private JLabel label16;
	private JLabel mse5;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
