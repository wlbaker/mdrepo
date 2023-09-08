/*
 * Created by JFormDesigner on Thu Jul 08 18:38:41 CDT 2010
 */

package idea.adapters.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DecimalFormat;
import java.util.Date;
import java.util.LinkedList;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import com.jgoodies.forms.factories.*;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.plot.XYPlot;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.RpUtil;
import icuInterface.UnitUtil;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.GuiUtil;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class InfusionPanel extends JPanel implements StreamConsumer {

	private int verbose = 0;
	private StreamProducer driver;
	private LinkedList<PumpInfo> pumpInfos;

	private DecimalFormat df2 = new DecimalFormat("0.00");
	private CombinedRateVolumeChart chart;

	//private LinkedList<CombinedInfusionChart> charts;

	/**
	 * Constructor
	 */
	public InfusionPanel() {
		this(null, null);
	}

	public InfusionPanel(StreamProducer driver, RpDevice conf) {
		initComponents();

		pumpInfos = new LinkedList<PumpInfo>();
		this.driver = driver;

		initChannelA();

		ChartPanel p0 = new ChartPanel(chart.getChart());
		p0.setPreferredSize(new Dimension(100, 200));
		chart1Panel.add(p0, BorderLayout.CENTER);

		pump1Settings.setVisible(false);
		if (conf == null) {
			portLabel.setText("");
		} else {
			portLabel.setText(" " + RpUtil.getConnectionPort(conf) );
		}

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

	private void initChannelA() {
		PumpInfo info = new PumpInfo();

		info.pumpId = "A";
		info.rate = rateA;
		info.vtbi = vtbiA;
		info.totvol = totalVolumeA;

		info.devStatus = devStatusA;
		info.infusionStatus = infusionStatusA;
		info.controlStatus = controlStatusA;
		info.actionStatus = actionStatusA;

		info.settings = pump1Settings;

		pumpInfos.add(info);

		chart = initChart("Channel A");
	}

	int x = 0;
	int y = 0;

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem block) {

		if (sid == StreamID.MEASUREMENT) {

			// determine which pump to update
			Number item = IntfUtil.getScaledValueByLoc(block, "ARATE");
			if (item != null) {
				PumpInfo info = pumpInfos.get(0);
				updateGeminiPump(block, chart, 0, info);
			}

			item = IntfUtil.getScaledValueByLoc(block, "BRATE");
			if (item != null) {
				// we are not handling dual-channel pumps in a single
				// panel...for now
				if (pumpInfos.size() > 1) {
					PumpInfo info = pumpInfos.get(1);
					updateGeminiPump(block, chart, 0, info);
				}
			}

			item = IntfUtil.getScaledValueByLoc(block, "PRIRATE");
			if (item != null) {
				PumpInfo info = pumpInfos.get(0);
				updateAS50Pump(block, chart, info);
			}

			item = IntfUtil.getScaledValueByLoc(block, "RATE1");
			if (item != null) {
				PumpInfo info = pumpInfos.get(0);
				updateBodyGuardPump(block, "RATE1", "VTBI1", "STATE1", info);
			}
			item = IntfUtil.getScaledValueByLoc(block, "RATE2");
			if (item != null) {
				PumpInfo info = pumpInfos.get(1);
				updateBodyGuardPump(block, "RATE2", "VTBI2", "STATE2", info);
			}

			if (verbose > 0) {
				System.out.println("Infusion Chart updated, x: " + x + "   y:" + y);
			}
		}
	}

	private void updateGeminiPump(PersistentItem block, CombinedRateVolumeChart chart, int id, PumpInfo info) {

		// System.out.println( id + ": " + info.pumpId + " info: " + info );

		String pfx = info.pumpId;

		Number rate = IntfUtil.getScaledValueByLoc(block, pfx + "RATE");
		Number vol = IntfUtil.getScaledValueByLoc(block, pfx + "VINF");

		setNumericItem(block, info.rate, pfx + "RATE");
		setNumericItem(block, info.vtbi, pfx + "VTBI");
		setNumericItem(block, info.totvol, pfx + "VINF");

		setTextItem(block, info.devStatus, pfx + "*MDEV");
		setTextItem(block, info.controlStatus, pfx + "*MCON");
		setTextItem(block, info.actionStatus, pfx + "*MACT");
		setTextItem(block, info.infusionStatus, pfx + "*MINF");

		String con_stat = info.controlStatus.getText();
		info.settings.setEnabled("ENABLE".equals(con_stat) || "ESTAB".equals(con_stat));

		Date ts = new Date(block.getTime());

		if (rate != null && vol != null) {
			Number rate_val = rate;
			String status = info.actionStatus.getText();
			if (status == null || !status.startsWith("INFUS")) {
				rate_val = 0; // rate can only be non-zero when infusing

				// and don't display the other values either
				info.rate.setVisible(false);
				info.vtbi.setVisible(false);
			} else {
				info.rate.setVisible(true);
				info.vtbi.setVisible(true);
			}
			chart.add5MinData(id, ts, rate_val, vol );
		} else {
			assert (false) : "unexpected rate/vol=null rate: " + rate + " vol: " + vol;
		}

	}

	private void updateAS50Pump(PersistentItem block, CombinedRateVolumeChart chart, PumpInfo info) {

		String val = "---";

		// NumericsItem item = (NumericsItem) block.getItem("PRIRATE");
		RpMetric tvi_metric = IntfUtil.getMetricByLoc(block,  "TVI");
		RpMetric pri_metric = IntfUtil.getMetricByLoc(block,  "PRIRATE");
		Number totvol = (Number) IntfUtil.getScaledValue(block, tvi_metric );
		Number priRate = (Number) IntfUtil.getScaledValue(block, pri_metric );

		double tt;
		if (priRate != null) {
			// info.series.add(block.getTime(), item.getValue());
			// System.out.println("series: " + info.series.getItemCount());
			// if (info.series.getItemCount() > 200) {
			// info.series.remove(0);
			// }
			RpUnit priUnit = pri_metric.getUnit();
			RpUnit totUnit = tvi_metric.getUnit();

			double pp = UnitUtil.getValue(priUnit, priRate.doubleValue());
			tt = UnitUtil.getValue(totUnit, totvol.doubleValue());

			pp = pp / 100.0;
			tt = tt / 100.0;
			Date ts = new Date(block.getTime());
			chart.add5MinData(0, ts, pp, tt);
			val = "" + pp;
		}
		info.rate.setText(val);

		setNumericItem(block, info.vtbi, "PRIVTBI");
		setNumericItem(block, info.totvol, "TVI");

		setTextItem(block, info.devStatus, "PROTOCOL");
		setTextItem(block, info.controlStatus, "STATUS");

		Object status = IntfUtil.getRawValueByLoc(block, "STATUS");
		if (status != null) {
			decodeAS50StatusMessages(info, "" + status );
		}

		String con_stat = info.controlStatus.getText();
		info.settings.setEnabled("ENABLE".equals(con_stat) || "ESTAB".equals(con_stat));

		// redrawLabel(info);

	}

	private void updateBodyGuardPump(PersistentItem block, String rateName, String vtbiName, String statusName,
			PumpInfo info) {

		String val = "---";

		Number priRate = IntfUtil.getScaledValueByLoc(block, rateName);
		if (priRate != null) {
			val = "" + priRate;
		}
		info.rate.setText(val);

		setNumericItem(block, info.vtbi, vtbiName);
		setTextItem(block, info.controlStatus, statusName);

		Object status = IntfUtil.getRawValueByLoc(block, statusName);
		if (status != null) {
			// decodeAS50StatusMessages(info, status.getValue());
			info.devStatus.setText("" + status);
		}

		String con_stat = info.controlStatus.getText();
		info.settings.setEnabled("ENABLE".equals(con_stat) || "ESTAB".equals(con_stat));
	}

	private void decodeAS50StatusMessages(PumpInfo info, String status) {
		String infusionStatus = "---";
		String actionStatus = "---";
		String devStatus = "---";

		if (status != null && status.length() > 7) {

			int dev = status.charAt(1);
			if ((dev & 0x03) != 0) {
				devStatus = "NEARVOL";
			} else if ((dev & 0x02) != 0) {
				devStatus = "MOUNT";
			} else if ((dev & 0x01) != 0) {
				devStatus = "BLOCKED";
			}

			int mode = status.charAt(3);
			if ((mode & 0x08) != 0) {
				infusionStatus = "STRTBOLUS";
			} else if ((mode & 0x04) != 0) {
				infusionStatus = "RUNNING";
			} else if ((mode & 0x02) != 0) {
				infusionStatus = "WAITING";
			} else if ((mode & 0x01) != 0) {
				infusionStatus = "COMMFAIL";
			} else {
				infusionStatus = "STOPPED";
			}

			int err = status.charAt(7);
			if ((err & 0x04) != 0) {
				actionStatus = "PLUNGER";
			} else if ((err & 0x02) != 0) {
				actionStatus = "FLANGE";
			} else if ((err & 0x01) != 0) {
				actionStatus = "BARREL";
			} else {
				// actionStatus = "OK";
			}

		}

		info.devStatus.setText(devStatus);
		info.infusionStatus.setText(infusionStatus);
		info.actionStatus.setText(actionStatus);
	}

	// private void redrawLabel(PumpInfo info) {
	// int width = info.lblChart.getWidth();
	// int height = info.lblChart.getHeight();
	// if (width < 30 || height < 20) {
	// // cant draw
	// } else {
	// BufferedImage image = info.chart.createBufferedImage(width - 20, height -
	// 10);
	// info.lblChart.setIcon(new ImageIcon(image));
	// // info.lblChart.repaint();
	// }
	// }

	private void setNumericItem(PersistentItem block, JLabel label, String loc) {
		String val = "---";
		RpMetric desc  = IntfUtil.getMetricByLoc(block, loc);
		Number num = (Number) IntfUtil.getScaledValue(block, desc);
		if (num != null) {
			double dval = num.doubleValue();
			RpUnit unit = null;
			if (desc != null) {
				unit = desc.getUnit();
			}

			if (unit != null) {
				val = df2.format(UnitUtil.getValue(unit, dval));
			} else {
				val = df2.format(dval);
			}
		}
		label.setText(val);

	}

	private void setTextItem(PersistentItem block, JLabel label, String loc) {
		String val = "---";

		Object it = IntfUtil.getRawValueByLoc(block, loc);
		val = "" + it;
		label.setText(val);
	}

	private void pump1SettingsActionPerformed(ActionEvent e) {
		InfusionSettingsPanel panel = new InfusionSettingsPanel(driver, "A");
		GuiUtil.doDialog("Infusion Settings", this, panel, null);
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
		portLabel = new JLabel();
		pump1Settings = new JButton();
		chart1Panel = new JPanel();

		//======== this ========
		setLayout(new FormLayout(
			"default, $lcgap, default:grow",
			"fill:default:grow, $lgap, default"));

		//======== pump1DetailPanel2 ========
		{
			pump1DetailPanel2.setBorder(new EmptyBorder(5, 5, 5, 5));
			pump1DetailPanel2.setLayout(new FormLayout(
				"default:grow",
				"fill:[16dlu,default], $lgap, default, $lgap, fill:default:grow, 2*($lgap, default)"));

			//---- label13 ----
			label13.setText("Channel 1");
			label13.setBackground(new Color(0, 153, 0));
			label13.setOpaque(true);
			label13.setHorizontalAlignment(SwingConstants.CENTER);
			pump1DetailPanel2.add(label13, CC.xy(1, 1));

			//======== panel7 ========
			{
				panel7.setLayout(new FormLayout(
					"right:default:grow, $lcgap, [30dlu,default]",
					"default, $lgap, [12dlu,default], 2*($lgap, default), $lgap, [12dlu,default], 4*($lgap, default)"));

				//---- label5 ----
				label5.setText("Rate:");
				label5.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label5, CC.xy(1, 1));

				//---- rateA ----
				rateA.setText("---");
				rateA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(rateA, CC.xy(3, 1));

				//---- label11 ----
				label11.setText("VTBI:");
				label11.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label11, CC.xy(1, 5));

				//---- vtbiA ----
				vtbiA.setText("---");
				vtbiA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(vtbiA, CC.xy(3, 5));

				//---- label9 ----
				label9.setText("Total Volume:");
				label9.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label9, CC.xy(1, 7));

				//---- totalVolumeA ----
				totalVolumeA.setText("---");
				totalVolumeA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(totalVolumeA, CC.xy(3, 7));

				//---- label17 ----
				label17.setText("Dev Status:");
				panel7.add(label17, CC.xy(1, 11));

				//---- devStatusA ----
				devStatusA.setText("---");
				panel7.add(devStatusA, CC.xy(3, 11));

				//---- label19 ----
				label19.setText("Control Status:");
				panel7.add(label19, CC.xy(1, 13));

				//---- controlStatusA ----
				controlStatusA.setText("---");
				panel7.add(controlStatusA, CC.xy(3, 13));

				//---- label21 ----
				label21.setText("Infusion Status:");
				panel7.add(label21, CC.xy(1, 15));

				//---- infusionStatusA ----
				infusionStatusA.setText("---");
				panel7.add(infusionStatusA, CC.xy(3, 15));

				//---- label23 ----
				label23.setText("Action Status:");
				panel7.add(label23, CC.xy(1, 17));

				//---- actionStatusA ----
				actionStatusA.setText("---");
				panel7.add(actionStatusA, CC.xy(3, 17));
			}
			pump1DetailPanel2.add(panel7, CC.xy(1, 5));

			//---- portLabel ----
			portLabel.setText("Port:");
			pump1DetailPanel2.add(portLabel, CC.xy(1, 7));

			//---- pump1Settings ----
			pump1Settings.setText("Settings");
			pump1Settings.addActionListener(e -> pump1SettingsActionPerformed(e));
			pump1DetailPanel2.add(pump1Settings, CC.xy(1, 9));
		}
		add(pump1DetailPanel2, CC.xy(1, 1));

		//======== chart1Panel ========
		{
			chart1Panel.setLayout(new BorderLayout());
		}
		add(chart1Panel, CC.xy(3, 1));
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
	private JLabel portLabel;
	private JButton pump1Settings;
	private JPanel chart1Panel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
