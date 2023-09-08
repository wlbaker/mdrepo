/*
 * Created by JFormDesigner on Tue Sep 28 07:22:27 CDT 2010
 */

package idea.tsoffline.analysis;

import java.text.DateFormat;
import java.text.DecimalFormat;
import java.util.Calendar;

import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.analysis.EntropyFilter;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ComplexityAnalysisPanel extends JPanel {
	
	DecimalFormat df1 = new DecimalFormat( "0.00");
	
	private double meanVal;
	private double sdVal;
	
	public ComplexityAnalysisPanel() {
		initComponents();
	}

	private void get_smv( double [] signal ) {
		meanVal = 0.0;
		double variance = 0.0;

		int length = signal.length;

		for (int i = 0; i < length; ++i) {
			meanVal += signal[i];
		}
		meanVal /= length;

		for (int i = 0; i < length; ++i) {
			double d = signal[i] - meanVal;
			variance += (int) (d * d);
		}
		variance /= (length - 1);

		sdVal = Math.sqrt(variance);
	}

	public void process(long startTime, long endTime, double[] signal) {
		Calendar cal = Calendar.getInstance();
		
		samples.setText("" + signal.length);

		DateFormat datef = GuiUtil.getDateTimeFormat();
		cal.setTimeInMillis( startTime );
		this.startTime.setText(datef.format(cal.getTime()));
		
		cal.setTimeInMillis( endTime );
		this.endTime.setText(datef.format(cal.getTime()));
		
		int m = 2;
		double r = 0.2;
		double seVal = EntropyFilter.SaEn(signal, r, m);
		seParams.setText("r=" + r + "*sd, m=" + m);
		sampEn.setText(df1.format(seVal));
		
		get_smv( signal );
		sd.setText( df1.format(sdVal) );
		mean.setText( df1.format(meanVal));
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel3 = new JPanel();
		label1 = new JLabel();
		samples = new JLabel();
		label21 = new JLabel();
		startTime = new JLabel();
		label22 = new JLabel();
		endTime = new JLabel();
		panel2 = new JPanel();
		label3 = new JLabel();
		mean = new JLabel();
		label7 = new JLabel();
		appEn = new JLabel();
		label17 = new JLabel();
		label24 = new JLabel();
		label4 = new JLabel();
		sd = new JLabel();
		label8 = new JLabel();
		sampEn = new JLabel();
		seParams = new JLabel();
		label18 = new JLabel();
		label5 = new JLabel();
		rmssd = new JLabel();
		label9 = new JLabel();
		lzEn = new JLabel();
		label19 = new JLabel();
		label20 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"left:[50dlu,default], $lcgap, default",
			"default, $lgap, default"));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"default, $lcgap, [30dlu,default], $lcgap, default, $lcgap, right:[30dlu,default], $lcgap, [30dlu,default], $lcgap, default, $lcgap, right:[30dlu,default], $lcgap, [50dlu,default]",
				"default"));

			//---- label1 ----
			label1.setText("Samples:");
			panel3.add(label1, cc.xy(1, 1));

			//---- samples ----
			samples.setText("text");
			panel3.add(samples, cc.xy(3, 1));

			//---- label21 ----
			label21.setText("Start:");
			panel3.add(label21, cc.xy(7, 1));

			//---- startTime ----
			startTime.setText("text");
			panel3.add(startTime, cc.xy(9, 1));

			//---- label22 ----
			label22.setText("End:");
			panel3.add(label22, cc.xy(13, 1));

			//---- endTime ----
			endTime.setText("text");
			panel3.add(endTime, cc.xy(15, 1));
		}
		add(panel3, cc.xy(1, 1));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"right:[50dlu,default], 2*($lcgap, default), $lcgap, right:default, 3*($lcgap, default), $lcgap, right:[50dlu,default], $lcgap, default",
				"4*(default, $lgap), default"));

			//---- label3 ----
			label3.setText("Mean:");
			panel2.add(label3, cc.xy(1, 3));

			//---- mean ----
			mean.setText("text");
			panel2.add(mean, cc.xy(3, 3));

			//---- label7 ----
			label7.setText("Approximate Entropy:");
			panel2.add(label7, cc.xy(7, 3));

			//---- appEn ----
			appEn.setText("text");
			panel2.add(appEn, cc.xy(9, 3));

			//---- label17 ----
			label17.setText("SEn:");
			panel2.add(label17, cc.xy(15, 3));

			//---- label24 ----
			label24.setText("sen?");
			panel2.add(label24, cc.xy(17, 3));

			//---- label4 ----
			label4.setText("SD:");
			panel2.add(label4, cc.xy(1, 5));

			//---- sd ----
			sd.setText("text");
			panel2.add(sd, cc.xy(3, 5));

			//---- label8 ----
			label8.setText("Sample Entropy:");
			panel2.add(label8, cc.xy(7, 5));

			//---- sampEn ----
			sampEn.setText("text");
			panel2.add(sampEn, cc.xy(9, 5));

			//---- seParams ----
			seParams.setText("text");
			panel2.add(seParams, cc.xy(11, 5));

			//---- label18 ----
			label18.setText("CD:");
			panel2.add(label18, cc.xy(15, 5));

			//---- label5 ----
			label5.setText("RMSSD:");
			panel2.add(label5, cc.xy(1, 7));

			//---- rmssd ----
			rmssd.setText("text");
			panel2.add(rmssd, cc.xy(3, 7));

			//---- label9 ----
			label9.setText("LZEntropy:");
			panel2.add(label9, cc.xy(7, 7));

			//---- lzEn ----
			lzEn.setText("text");
			panel2.add(lzEn, cc.xy(9, 7));

			//---- label19 ----
			label19.setText("FD-CL:");
			panel2.add(label19, cc.xy(15, 7));

			//---- label20 ----
			label20.setText("FD-DA:");
			panel2.add(label20, cc.xy(15, 9));
		}
		add(panel2, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel3;
	private JLabel label1;
	private JLabel samples;
	private JLabel label21;
	private JLabel startTime;
	private JLabel label22;
	private JLabel endTime;
	private JPanel panel2;
	private JLabel label3;
	private JLabel mean;
	private JLabel label7;
	private JLabel appEn;
	private JLabel label17;
	private JLabel label24;
	private JLabel label4;
	private JLabel sd;
	private JLabel label8;
	private JLabel sampEn;
	private JLabel seParams;
	private JLabel label18;
	private JLabel label5;
	private JLabel rmssd;
	private JLabel label9;
	private JLabel lzEn;
	private JLabel label19;
	private JLabel label20;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
