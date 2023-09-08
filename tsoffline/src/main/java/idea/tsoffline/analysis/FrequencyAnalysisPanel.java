/*
 * Created by JFormDesigner on Tue Sep 28 07:22:27 CDT 2010
 */

package idea.tsoffline.analysis;

import java.text.DecimalFormat;

import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.analysis.HRVProcessor;
import idea.analysis.ecg.HRVPoint;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class FrequencyAnalysisPanel extends JPanel {
	DecimalFormat df2 = new DecimalFormat("0.00");

	public FrequencyAnalysisPanel() {
		initComponents();
	}

	public void process(long startTime, long endTime, double[] signal) {

		long dt = endTime - startTime; // time series length in ms
		if (dt == 0) {
			return;
		}

		double freq = signal.length * 1000.0 / dt;

		HRVProcessor processor = new HRVProcessor(freq, signal.length, 4096);

		int[] isignal = new int[signal.length];
		for (int i = 0; i < signal.length; i++) {
			isignal[i] = (int) signal[i];
		}

		HRVPoint hrv = processor.ComputeHRV(isignal);

		hf.setText(df2.format(hrv.getHF()));
		lf.setText(df2.format(hrv.getLF()));
		hf_lf.setText(df2.format(hrv.getHF_LF()));
		lf_hf.setText(df2.format(hrv.getLF_HF()));
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		label3 = new JLabel();
		label14 = new JLabel();
		label6 = new JLabel();
		lf_hf = new JLabel();
		label17 = new JLabel();
		label4 = new JLabel();
		label15 = new JLabel();
		label0 = new JLabel();
		hf_lf = new JLabel();
		label18 = new JLabel();
		label5 = new JLabel();
		label16 = new JLabel();
		label8 = new JLabel();
		nLF = new JLabel();
		label19 = new JLabel();
		label1 = new JLabel();
		lf = new JLabel();
		label9 = new JLabel();
		nHF = new JLabel();
		label20 = new JLabel();
		label2 = new JLabel();
		hf = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
				"right:default, 2*($lcgap, default), $lcgap, right:default, 2*($lcgap, default), $lcgap, right:default, $lcgap, default",
				"5*(default, $lgap), default"));

		//---- label3 ----
		label3.setText("Total Power:");
		add(label3, cc.xy(1, 3));

		//---- label14 ----
		label14.setText("text");
		add(label14, cc.xy(3, 3));

		//---- label6 ----
		label6.setText("LF/HF (%):");
		add(label6, cc.xy(7, 3));

		//---- lf_hf ----
		lf_hf.setText("text");
		add(lf_hf, cc.xy(9, 3));

		//---- label17 ----
		label17.setText("nLF/nHF:");
		add(label17, cc.xy(13, 3));

		//---- label4 ----
		label4.setText("ULF:");
		add(label4, cc.xy(1, 5));

		//---- label15 ----
		label15.setText("text");
		add(label15, cc.xy(3, 5));

		//---- label0 ----
		label0.setText("HF/LF:");
		add(label0, cc.xy(7, 5));

		//---- hf_lf ----
		hf_lf.setText("text");
		add(hf_lf, cc.xy(9, 5));

		//---- label18 ----
		label18.setText("nHF/nLF:");
		add(label18, cc.xy(13, 5));

		//---- label5 ----
		label5.setText("VLF:");
		add(label5, cc.xy(1, 7));

		//---- label16 ----
		label16.setText("text");
		add(label16, cc.xy(3, 7));

		//---- label8 ----
		label8.setText("nLF:");
		add(label8, cc.xy(7, 7));

		//---- nLF ----
		nLF.setText("text");
		add(nLF, cc.xy(9, 7));

		//---- label19 ----
		label19.setText("RRI DF Alpha S:");
		add(label19, cc.xy(13, 7));

		//---- label1 ----
		label1.setText("LF:");
		add(label1, cc.xy(1, 9));

		//---- lf ----
		lf.setText("text");
		add(lf, cc.xy(3, 9));

		//---- label9 ----
		label9.setText("nHF:");
		add(label9, cc.xy(7, 9));

		//---- nHF ----
		nHF.setText("text");
		add(nHF, cc.xy(9, 9));

		//---- label20 ----
		label20.setText("Alpha L:");
		add(label20, cc.xy(13, 9));

		//---- label2 ----
		label2.setText("HF:");
		add(label2, cc.xy(1, 11));

		//---- hf ----
		hf.setText("text");
		add(hf, cc.xy(3, 11));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel label3;
	private JLabel label14;
	private JLabel label6;
	private JLabel lf_hf;
	private JLabel label17;
	private JLabel label4;
	private JLabel label15;
	private JLabel label0;
	private JLabel hf_lf;
	private JLabel label18;
	private JLabel label5;
	private JLabel label16;
	private JLabel label8;
	private JLabel nLF;
	private JLabel label19;
	private JLabel label1;
	private JLabel lf;
	private JLabel label9;
	private JLabel nHF;
	private JLabel label20;
	private JLabel label2;
	private JLabel hf;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
