/*
 * Created by JFormDesigner on Thu Jul 08 18:38:41 CDT 2010
 */

package idea.adapters.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.plot.XYPlot;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class InfusionVerticalPanel extends JPanel {

	private static final int BARWIDTH_MINUTES = 5;
	CombinedRateVolumeChart chart;
	Calendar cal = Calendar.getInstance();

	/**
	 * Constructor
	 */

	public InfusionVerticalPanel(String id) {
		initComponents();

		// WARNING: maybe you want initChannel...dont know!
		PumpInfo info = initChannel(id);
		chart = info.chart;
		ChartPanel p0 = new ChartPanel(chart.getChart());
		p0.setPreferredSize(new Dimension(100, 200));
		chart1Panel.add(p0, BorderLayout.CENTER);

	}

	public void clear() {
		rateA.setText("---");
		vtbiA.setText("---");
		totalVolumeA.setText("---");
		devStatusA.setText("---");
		controlStatusA.setText("---");
		infusionStatusA.setText("---");
		actionStatusA.setText("---");
	}

	private static CombinedRateVolumeChart initChart(String title) {
		CombinedRateVolumeChart chart = new CombinedRateVolumeChart(); // createChart(info);

		// no title chart.getChart().setTitle(title);
		chart.getChart().removeLegend();

		XYPlot volumePlot = chart.getVolumePlot();
		volumePlot.getRangeAxis().setUpperBound(2000.0);
		volumePlot.getRangeAxis().setLowerBound(0);
		volumePlot.getRangeAxis().setAutoRange(false);

		// add a second dataset and renderer...

		XYPlot ratePlot = chart.getRatePlot();
		ratePlot.getRangeAxis().setUpperBound(1000.0);
		ratePlot.getRangeAxis().setLowerBound(0);
		ratePlot.getRangeAxis().setAutoRange(false);

		return chart;
	}

	private PumpInfo initChannel(String id) {
		PumpInfo info = new PumpInfo();

		info.pumpId = id;
		info.rate = rateA;
		info.vtbi = vtbiA;
		info.totvol = totalVolumeA;

		info.devStatus = devStatusA;
		info.infusionStatus = infusionStatusA;
		info.controlStatus = controlStatusA;
		info.actionStatus = actionStatusA;

		info.settings = null; //?? pump1Settings;

		String channelName = "Channel " + id;
		channelLabel.setText(channelName);
		info.chart = initChart(channelName);

		return info;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		pump1DetailPanel2 = new JPanel();
		channelLabel = new JLabel();
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
		chart1Panel = new JPanel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow", "fill:default:grow"));

		//======== pump1DetailPanel2 ========
		{
			pump1DetailPanel2.setBorder(new EmptyBorder(5, 5, 5, 5));
			pump1DetailPanel2.setLayout(new FormLayout("default:grow",
					"fill:[16dlu,default], $lgap, fill:default, $lgap, fill:default:grow"));

			//---- channelLabel ----
			channelLabel.setText("Channel 1");
			channelLabel.setBackground(new Color(0, 153, 0));
			channelLabel.setOpaque(true);
			channelLabel.setHorizontalAlignment(SwingConstants.CENTER);
			pump1DetailPanel2.add(channelLabel, cc.xy(1, 1));

			//======== panel7 ========
			{
				panel7.setLayout(new FormLayout("right:default:grow, $lcgap, [30dlu,default]",
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

			//======== chart1Panel ========
			{
				chart1Panel.setLayout(new BorderLayout());
			}
			pump1DetailPanel2.add(chart1Panel, cc.xy(1, 5));
		}
		add(pump1DetailPanel2, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel pump1DetailPanel2;
	private JLabel channelLabel;
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
	private JPanel chart1Panel;

	// JFormDesigner - End of variables declaration //GEN-END:variables
	private void setOneItem(JLabel field, Number item) {
		field.setText("" + item);
	}
	private void setOneItem(JLabel field, String item) {
		field.setText(item);
	}

	public void setRate(Number rate) {
		setOneItem(this.rateA, rate);
	}

	public void setVTBD(Number vtbd) {
		setOneItem(this.vtbiA, vtbd);
	}

	public void setVTOT(Number vtot) {
		setOneItem(this.totalVolumeA, vtot);
	}

	public void setDrugName(String dn) {
		setOneItem(this.controlStatusA, dn);
	}

	public void setStatus(String sta) {
		setOneItem(this.infusionStatusA, sta);
	}

	public void addChart(Date dt, Number rate, Number vol) {
		/*
		 * round date to BARWIDTH_MINUTES (5-min?) marker
		 */
		cal.setTime(dt);
		cal.set(Calendar.SECOND, 0);
		cal.set(Calendar.MILLISECOND, 0);
		int unroundedMinutes = cal.get(Calendar.MINUTE);
		int mod = unroundedMinutes % BARWIDTH_MINUTES;
		int min = unroundedMinutes + (BARWIDTH_MINUTES - mod);

		cal.set(Calendar.MINUTE, min);
		dt = cal.getTime();

		int series = 0;
		if (min > (60 - BARWIDTH_MINUTES))
			series = 1;

		chart.add5MinData(series, dt, rate, vol);
	}

	public void clearHistory() {
		chart.clear();
	}

	public void update() {
		chart.update();
	}
}
