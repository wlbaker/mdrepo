/*
 * Created by JFormDesigner on Thu Jul 08 18:38:41 CDT 2010
 */

package idea.adapters.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.conf.DeviceConfiguration;
import idea.intf.AdapterInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class InfusionHorizPanel extends JPanel {

	/**
	 * Constructor
	 */
	public InfusionHorizPanel() {
		this(null, null);
	}

	public InfusionHorizPanel(AdapterInterface driver, DeviceConfiguration conf) {
		initComponents();

	}

	private static CombinedRateVolumeChart initChart(String title) {
		CombinedRateVolumeChart chart = new CombinedRateVolumeChart(); // createChart(info);

		chart.getChart().setTitle(title);
		chart.getChart().removeLegend();

		return chart;
	}

	private void initChannel( String id ) {
		PumpInfo info = new PumpInfo();

		info.pumpId = id;
		info.rate = rateA;
		info.vtbi = vtbiA;
		info.totvol = totalVolumeA;

		info.devStatus = devStatusA;
		info.infusionStatus = infusionStatusA;
		info.controlStatus = controlStatusA;
		info.actionStatus = actionStatusA;

		info.settings = pump1Settings;

		info.chart = initChart("Channel " + id );
	}

	private void pump1SettingsActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void pump2SettingsActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		pump1DetailPanel2 = new JPanel();
		label13 = new JLabel();
		panel7 = new JPanel();
		label5 = new JLabel();
		rateA = new JLabel();
		label11 = new JLabel();
		vtbiA = new JLabel();
		label9 = new JLabel();
		totalVolumeA = new JLabel();
		label17 = new JLabel();
		devStatusA = new JLabel();
		label19 = new JLabel();
		controlStatusA = new JLabel();
		label21 = new JLabel();
		infusionStatusA = new JLabel();
		label23 = new JLabel();
		actionStatusA = new JLabel();
		pump1Settings = new JButton();
		chart1Panel = new JPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"2*(default, $lcgap), default:grow",
			"fill:default:grow, 2*($lgap, default)"));

		//======== pump1DetailPanel2 ========
		{
			pump1DetailPanel2.setBorder(new EmptyBorder(5, 5, 5, 5));
			pump1DetailPanel2.setLayout(new FormLayout(
				"default:grow",
				"fill:[16dlu,default], $lgap, fill:default:grow, $lgap, default"));

			//---- label13 ----
			label13.setText("Channel 1");
			label13.setBackground(new Color(0, 153, 0));
			label13.setOpaque(true);
			label13.setHorizontalAlignment(SwingConstants.CENTER);
			pump1DetailPanel2.add(label13, cc.xy(1, 1));

			//======== panel7 ========
			{
				panel7.setLayout(new FormLayout(
					"right:default:grow, $lcgap, [30dlu,default]",
					"default, $lgap, [12dlu,default], 2*($lgap, default), $lgap, [12dlu,default], 4*($lgap, default)"));

				//---- label5 ----
				label5.setText("Rate:");
				label5.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label5, cc.xy(1, 1));

				//---- rateA ----
				rateA.setText("---");
				rateA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(rateA, cc.xy(3, 1));

				//---- label11 ----
				label11.setText("VTBI:");
				label11.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label11, cc.xy(1, 5));

				//---- vtbiA ----
				vtbiA.setText("---");
				vtbiA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(vtbiA, cc.xy(3, 5));

				//---- label9 ----
				label9.setText("Total Volume:");
				label9.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label9, cc.xy(1, 7));

				//---- totalVolumeA ----
				totalVolumeA.setText("---");
				totalVolumeA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(totalVolumeA, cc.xy(3, 7));

				//---- label17 ----
				label17.setText("Dev Status:");
				panel7.add(label17, cc.xy(1, 11));

				//---- devStatusA ----
				devStatusA.setText("---");
				panel7.add(devStatusA, cc.xy(3, 11));

				//---- label19 ----
				label19.setText("Control Status:");
				panel7.add(label19, cc.xy(1, 13));

				//---- controlStatusA ----
				controlStatusA.setText("---");
				panel7.add(controlStatusA, cc.xy(3, 13));

				//---- label21 ----
				label21.setText("Infusion Status:");
				panel7.add(label21, cc.xy(1, 15));

				//---- infusionStatusA ----
				infusionStatusA.setText("---");
				panel7.add(infusionStatusA, cc.xy(3, 15));

				//---- label23 ----
				label23.setText("Action Status:");
				panel7.add(label23, cc.xy(1, 17));

				//---- actionStatusA ----
				actionStatusA.setText("---");
				panel7.add(actionStatusA, cc.xy(3, 17));
			}
			pump1DetailPanel2.add(panel7, cc.xy(1, 3));

			//---- pump1Settings ----
			pump1Settings.setText("Settings");
			pump1DetailPanel2.add(pump1Settings, cc.xy(1, 5));
		}
		add(pump1DetailPanel2, cc.xy(3, 1));

		//======== chart1Panel ========
		{
			chart1Panel.setLayout(new BorderLayout());
		}
		add(chart1Panel, cc.xy(5, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel pump1DetailPanel2;
	private JLabel label13;
	private JPanel panel7;
	private JLabel label5;
	private JLabel rateA;
	private JLabel label11;
	private JLabel vtbiA;
	private JLabel label9;
	private JLabel totalVolumeA;
	private JLabel label17;
	private JLabel devStatusA;
	private JLabel label19;
	private JLabel controlStatusA;
	private JLabel label21;
	private JLabel infusionStatusA;
	private JLabel label23;
	private JLabel actionStatusA;
	private JButton pump1Settings;
	private JPanel chart1Panel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
