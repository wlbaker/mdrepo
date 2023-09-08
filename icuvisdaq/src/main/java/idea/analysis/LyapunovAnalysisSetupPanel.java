/*
 * Created by JFormDesigner on Thu May 19 07:57:03 CDT 2011
 */

package idea.analysis;


import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;

import idea.GuiUtil;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
public class LyapunovAnalysisSetupPanel extends JPanel {
	public LyapunovAnalysisSetupPanel() {
		initComponents();
		
		points.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		slidingWindow.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		m.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		J.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		W.setFormatterFactory( GuiUtil.getIntegerFormatterFactory() );
		
		points.setValue( 512 );
		slidingWindow.setValue( 50 );
		m.setValue( 2 );
		J.setValue( 1 );
		W.setValue( 10 );

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label1 = new JLabel();
		points = new JFormattedTextField();
		label6 = new JLabel();
		label2 = new JLabel();
		slidingWindow = new JFormattedTextField();
		label7 = new JLabel();
		label3 = new JLabel();
		m = new JFormattedTextField();
		label8 = new JLabel();
		label4 = new JLabel();
		J = new JFormattedTextField();
		label9 = new JLabel();
		label5 = new JLabel();
		W = new JFormattedTextField();
		label10 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, right:default, $lcgap, [20dlu,default], $lcgap, default",
				"4*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Points:");
			panel1.add(label1, cc.xy(3, 1));
			panel1.add(points, cc.xy(5, 1));

			//---- label6 ----
			label6.setText("text");
			panel1.add(label6, cc.xy(7, 1));

			//---- label2 ----
			label2.setText("Sliding Window:");
			panel1.add(label2, cc.xy(3, 3));
			panel1.add(slidingWindow, cc.xy(5, 3));

			//---- label7 ----
			label7.setText("text");
			panel1.add(label7, cc.xy(7, 3));

			//---- label3 ----
			label3.setText("m:");
			panel1.add(label3, cc.xy(3, 5));
			panel1.add(m, cc.xy(5, 5));

			//---- label8 ----
			label8.setText("text");
			panel1.add(label8, cc.xy(7, 5));

			//---- label4 ----
			label4.setText("J:");
			panel1.add(label4, cc.xy(3, 7));
			panel1.add(J, cc.xy(5, 7));

			//---- label9 ----
			label9.setText("text");
			panel1.add(label9, cc.xy(7, 7));

			//---- label5 ----
			label5.setText("W:");
			panel1.add(label5, cc.xy(3, 9));
			panel1.add(W, cc.xy(5, 9));

			//---- label10 ----
			label10.setText("text");
			panel1.add(label10, cc.xy(7, 9));
		}
		add(panel1, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label1;
	private JFormattedTextField points;
	private JLabel label6;
	private JLabel label2;
	private JFormattedTextField slidingWindow;
	private JLabel label7;
	private JLabel label3;
	private JFormattedTextField m;
	private JLabel label8;
	private JLabel label4;
	private JFormattedTextField J;
	private JLabel label9;
	private JLabel label5;
	private JFormattedTextField W;
	private JLabel label10;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
