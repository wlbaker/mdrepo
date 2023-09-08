/*
 * Created by JFormDesigner on Thu Jan 10 10:21:49 CST 2013
 */

package idea.adapters.gui;

import java.awt.Color;
import java.awt.Font;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
public class HemolungPanel extends JPanel {
	public HemolungPanel() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		panel2 = new JPanel();
		label1 = new JLabel();
		label3 = new JLabel();
		label2 = new JLabel();
		panel3 = new JPanel();
		label4 = new JLabel();
		label5 = new JLabel();
		label6 = new JLabel();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("[90dlu,default], $lcgap, default",
					"fill:default:grow, $lgap, fill:default:grow"));

			//======== panel2 ========
			{
				panel2.setBackground(Color.yellow);
				panel2.setLayout(new FormLayout("default:grow", "2*(default:grow, $lgap), default:grow"));

				//---- label1 ----
				label1.setText("CO2 Removal");
				panel2.add(label1, CC.xy(1, 1));

				//---- label3 ----
				label3.setText("text");
				label3.setHorizontalAlignment(SwingConstants.CENTER);
				label3.setFont(new Font("Tahoma", Font.PLAIN, 24));
				panel2.add(label3, CC.xy(1, 3, CC.FILL, CC.FILL));

				//---- label2 ----
				label2.setText("mL/min");
				panel2.add(label2, CC.xy(1, 5, CC.RIGHT, CC.DEFAULT));
			}
			panel1.add(panel2, CC.xy(1, 1));

			//======== panel3 ========
			{
				panel3.setBackground(Color.cyan);
				panel3.setLayout(new FormLayout("default:grow", "2*(default:grow, $lgap), default:grow"));

				//---- label4 ----
				label4.setText("Blood Flow");
				panel3.add(label4, CC.xy(1, 1));

				//---- label5 ----
				label5.setText("text");
				label5.setHorizontalAlignment(SwingConstants.CENTER);
				label5.setFont(new Font("Tahoma", Font.PLAIN, 24));
				panel3.add(label5, CC.xy(1, 3, CC.FILL, CC.FILL));

				//---- label6 ----
				label6.setText("mL/min");
				panel3.add(label6, CC.xy(1, 5, CC.RIGHT, CC.DEFAULT));
			}
			panel1.add(panel3, CC.xy(1, 3));
		}
		add(panel1, CC.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JPanel panel2;
	private JLabel label1;
	private JLabel label3;
	private JLabel label2;
	private JPanel panel3;
	private JLabel label4;
	private JLabel label5;
	private JLabel label6;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
