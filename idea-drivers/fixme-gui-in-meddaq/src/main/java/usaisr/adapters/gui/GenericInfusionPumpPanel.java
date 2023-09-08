/*
 * NOTE: This might not be the class you want!
 * 
 * You might want the MultiChannelInfusionPump panel.
 * 
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

import org.jfree.chart.ChartPanel;
import org.jfree.chart.plot.XYPlot;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.UnitUtil;
import icuInterface.adapters.C2Driver;
import idea.conf.DeviceConfiguration;
import idea.intf.AdapterInterface;
import idea.intf.DataTyp;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class GenericInfusionPumpPanel extends JPanel implements StreamConsumer {

	private AdapterInterface driver;
	private LinkedList<PumpInfo> pumpInfos;

	private DecimalFormat df2 = new DecimalFormat("0.00");
	private LinkedList<CombinedRateVolumeChart> charts;

	/**
	 * Constructor
	 */
	public GenericInfusionPumpPanel() {
		this(null, null);
	}

	public GenericInfusionPumpPanel(AdapterInterface driver, DeviceConfiguration conf) {
		initComponents();

		pumpInfos = new LinkedList<PumpInfo>();
		charts = new LinkedList<CombinedRateVolumeChart>();
		this.driver = driver;

		String modelName = conf.getModelName();
		// String title = modelName;

		if (C2Driver.class.getCanonicalName().equals(conf.getDeviceClass())) {
			// "PC-2".equals(modelName)
			// title = "Gemini";
			initChannelA();
			initChannelB();
		} else if ("AS50".equals(modelName)) {
			initChannelA();
		} else if ("BodyGuard".equals(modelName)) {
			initChannelA();
			initChannelB();
		} else {
			initChannelA();
		}

		ChartPanel p0 = new ChartPanel(charts.get(0).getChart());
		p0.setPreferredSize(new Dimension(100, 200));
		chart1Panel.add(p0, BorderLayout.CENTER);

		if (charts.size() > 1) {
			ChartPanel p1 = new ChartPanel(charts.get(1).getChart());
			p1.setPreferredSize(new Dimension(100, 200));
			chart2Panel.add(p1, BorderLayout.CENTER);
		}

	}

	private static CombinedRateVolumeChart initChart(String title) {
		CombinedRateVolumeChart chart = new CombinedRateVolumeChart(); // createChart(info);

		chart.getChart().setTitle(title);
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

		charts.add(initChart("Channel A"));
	}

	private void initChannelB() {

		PumpInfo info = new PumpInfo();

		info.pumpId = "B";
		info.rate = rateB;
		info.vtbi = vtbiB;
		info.totvol = totalVolumeB;

		info.devStatus = devStatusB;
		info.infusionStatus = infusionStatusB;
		info.controlStatus = controlStatusB;
		info.actionStatus = actionStatusB;

		info.settings = pump2Settings;

		pumpInfos.add(info);

		charts.add(initChart("Channel B"));
	}

	int x = 0;
	int y = 0;

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem block) {

		if (sid == StreamID.MEASUREMENT) {

			// determine which pump to update
			RpMetric item = IntfUtil.getMetricByLoc(block, "ARATE");
			if (item != null) {
				PumpInfo info = pumpInfos.get(0);
				CombinedRateVolumeChart chart = charts.get(0);
				updateGeminiPump(block, chart, 0, info);
			}

			item = IntfUtil.getMetricByLoc(block, "BRATE");
			if (item != null) {
				// we are not handling dual-channel pumps in a single
				// panel...for now
				if (pumpInfos.size() > 1) {
					PumpInfo info = pumpInfos.get(1);
					CombinedRateVolumeChart chart = charts.get(1);
					updateGeminiPump(block, chart, 0, info);
				}
			}

			item = IntfUtil.getMetricByLoc(block, "PRIRATE");
			if (item != null) {
				PumpInfo info = pumpInfos.get(0);
				CombinedRateVolumeChart chart = charts.get(0);

				updateAS50Pump(block, chart, info);
			}

			item = IntfUtil.getMetricByLoc(block, "RATE1");
			if (item != null) {
				PumpInfo info = pumpInfos.get(0);
				updateBodyGuardPump(block, "RATE1", "VTBI1", "STATE1", info);
			}
			item = IntfUtil.getMetricByLoc(block, "RATE2");
			if (item != null) {
				PumpInfo info = pumpInfos.get(1);
				updateBodyGuardPump(block, "RATE2", "VTBI2", "STATE2", info);
			}

			log.info("Infusion Chart updated, x: {}   y: {}", x, y);
		}
	}

	private void updateGeminiPump(PersistentItem block, CombinedRateVolumeChart chart, int id, PumpInfo info) {

		// System.out.println( id + ": " + info.pumpId + " info: " + info );

		String pfx = info.pumpId;

//		NumericItem rate = (NumericItem) block.getItem(pfx + "RATE");
//		NumericItem vol = (NumericItem) block.getItem(pfx + "VINF");
		RpMetric rate = IntfUtil.getMetricByLoc(block, pfx + "RATE");
		RpMetric vol = IntfUtil.getMetricByLoc(block, pfx + "VINF");

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
			Number rate_val = (Number) IntfUtil.getScaledValue(block, rate);
			Number vol_val = (Number) IntfUtil.getScaledValue(block, vol);
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
			chart.add5MinData(id, ts, rate_val, vol_val );
		} else {
			assert (false) : "unexpected rate/vol=null rate: " + rate + " vol: " + vol;
		}

	}

	private void updateAS50Pump(PersistentItem block, CombinedRateVolumeChart chart, PumpInfo info) {

		String val = "---";

		// NumericsItem item = (NumericsItem) block.getItem("PRIRATE");
		RpMetric totvol = IntfUtil.getMetricByLoc(block, "TVI");
		RpMetric priRate = IntfUtil.getMetricByLoc(block, "PRIRATE");

		if (priRate != null) {
			// info.series.add(block.getTime(), item.getValue());
			// System.out.println("series: " + info.series.getItemCount());
			// if (info.series.getItemCount() > 200) {
			// info.series.remove(0);
			// }
			RpUnit priUnit = priRate.getUnit();
			RpUnit totUnit = totvol.getUnit();

			Number pp = (Number) IntfUtil.getScaledValue(block, priRate );
			Number tt = (Number) IntfUtil.getScaledValue(block, totvol );

			pp = pp.doubleValue() / 100.0;
			tt = tt.doubleValue() / 100.0;
			Date ts = new Date(block.getTime());
			chart.add5MinData(0, ts, pp, tt);
			val = "" + pp;
		}
		info.rate.setText(val);

		setNumericItem(block, info.vtbi, "PRIVTBI");
		setNumericItem(block, info.totvol, "TVI");

		setTextItem(block, info.devStatus, "PROTOCOL");
		setTextItem(block, info.controlStatus, "STATUS");

		String status = (String) IntfUtil.getRawValueByLoc(block, "STATUS");
		if (status != null) {
			decodeAS50StatusMessages(info, status );
		}

		String con_stat = info.controlStatus.getText();
		info.settings.setEnabled("ENABLE".equals(con_stat) || "ESTAB".equals(con_stat));

		// redrawLabel(info);

	}

	private void updateBodyGuardPump(PersistentItem block, String rateName, String vtbiName, String statusName,
			PumpInfo info) {

		String val = "---";

		// Date ts = new Date(block.getTime());
		val = "" + IntfUtil.getScaledValueByLoc(block, rateName);
		info.rate.setText(val);

		setNumericItem(block, info.vtbi, vtbiName);
		setTextItem(block, info.controlStatus, statusName);

		Object status = IntfUtil.getRawValueByLoc(block, statusName);
		if (status != null) {
			// decodeAS50StatusMessages(info, status.getValue());
			info.devStatus.setText("" + status );
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
		RpMetric desc = IntfUtil.getMetricByLoc(block, loc);
		Number num = null;
		if (desc != null) {
			num = (Number) IntfUtil.getScaledValue(block, desc );
		}
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

		RpMetric it = IntfUtil.getMetricByLoc(block, loc);
		if (it == null) {
			// ignore
		}
		if (it.getSubtyp() == DataTyp.STRING_TYP ) {
			val = (String) IntfUtil.getRawValue(block, it);
		} else {
			Number num = (Number) IntfUtil.getScaledValue(block, it);
			val = num.toString();
		}
		label.setText(val);
	}

	private void pump1SettingsActionPerformed(ActionEvent e) {
		InfusionSettingsPanel panel = new InfusionSettingsPanel(driver, "A");
		GuiUtil.doDialog("Infusion Settings", this, panel, null);
	}

	private void pump2SettingsActionPerformed(ActionEvent e) {
		InfusionSettingsPanel panel = new InfusionSettingsPanel(driver, "B");
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
		pump1Settings = new JButton();
		chart1Panel = new JPanel();
		chart2Panel = new JPanel();
		pump1DetailPanel = new JPanel();
		label14 = new JLabel();
		panel6 = new JPanel();
		label4 = new JLabel();
		rateB = new JLabel();
		label10 = new JLabel();
		vtbiB = new JLabel();
		label8 = new JLabel();
		totalVolumeB = new JLabel();
		label3 = new JLabel();
		devStatusB = new JLabel();
		label6 = new JLabel();
		controlStatusB = new JLabel();
		label7 = new JLabel();
		infusionStatusB = new JLabel();
		label12 = new JLabel();
		actionStatusB = new JLabel();
		pump2Settings = new JButton();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("default, 2*($lcgap, default:grow), $lcgap, [90dlu,default]",
				"fill:default:grow, 2*($lgap, default)"));

		// ======== pump1DetailPanel2 ========
		{
			pump1DetailPanel2.setBorder(new EmptyBorder(5, 5, 5, 5));
			pump1DetailPanel2.setLayout(new FormLayout("default:grow",
					"fill:[16dlu,default], $lgap, fill:default:grow, $lgap, default"));

			// ---- label13 ----
			label13.setText("Channel 1");
			label13.setBackground(new Color(0, 153, 0));
			label13.setOpaque(true);
			label13.setHorizontalAlignment(SwingConstants.CENTER);
			pump1DetailPanel2.add(label13, cc.xy(1, 1));

			// ======== panel7 ========
			{
				panel7.setLayout(new FormLayout("right:default:grow, $lcgap, [30dlu,default]",
						"default, $lgap, [12dlu,default], 2*($lgap, default), $lgap, [12dlu,default], 4*($lgap, default)"));

				// ---- label5 ----
				label5.setText("Rate:");
				label5.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label5, cc.xy(1, 1));

				// ---- rateA ----
				rateA.setText("---");
				rateA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(rateA, cc.xy(3, 1));

				// ---- label11 ----
				label11.setText("VTBI:");
				label11.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label11, cc.xy(1, 5));

				// ---- vtbiA ----
				vtbiA.setText("---");
				vtbiA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(vtbiA, cc.xy(3, 5));

				// ---- label9 ----
				label9.setText("Total Volume:");
				label9.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(label9, cc.xy(1, 7));

				// ---- totalVolumeA ----
				totalVolumeA.setText("---");
				totalVolumeA.setHorizontalAlignment(SwingConstants.RIGHT);
				panel7.add(totalVolumeA, cc.xy(3, 7));

				// ---- label17 ----
				label17.setText("Dev Status:");
				panel7.add(label17, cc.xy(1, 11));

				// ---- devStatusA ----
				devStatusA.setText("---");
				panel7.add(devStatusA, cc.xy(3, 11));

				// ---- label19 ----
				label19.setText("Control Status:");
				panel7.add(label19, cc.xy(1, 13));

				// ---- controlStatusA ----
				controlStatusA.setText("---");
				panel7.add(controlStatusA, cc.xy(3, 13));

				// ---- label21 ----
				label21.setText("Infusion Status:");
				panel7.add(label21, cc.xy(1, 15));

				// ---- infusionStatusA ----
				infusionStatusA.setText("---");
				panel7.add(infusionStatusA, cc.xy(3, 15));

				// ---- label23 ----
				label23.setText("Action Status:");
				panel7.add(label23, cc.xy(1, 17));

				// ---- actionStatusA ----
				actionStatusA.setText("---");
				panel7.add(actionStatusA, cc.xy(3, 17));
			}
			pump1DetailPanel2.add(panel7, cc.xy(1, 3));

			// ---- pump1Settings ----
			pump1Settings.setText("Settings");
			pump1Settings.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					pump1SettingsActionPerformed(e);
				}
			});
			pump1DetailPanel2.add(pump1Settings, cc.xy(1, 5));
		}
		add(pump1DetailPanel2, cc.xy(1, 1));

		// ======== chart1Panel ========
		{
			chart1Panel.setLayout(new BorderLayout());
		}
		add(chart1Panel, cc.xy(3, 1));

		// ======== chart2Panel ========
		{
			chart2Panel.setLayout(new BorderLayout());
		}
		add(chart2Panel, cc.xy(5, 1));

		// ======== pump1DetailPanel ========
		{
			pump1DetailPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
			pump1DetailPanel.setLayout(new FormLayout("default:grow",
					"fill:[16dlu,default], $lgap, fill:default:grow, $lgap, default"));

			// ---- label14 ----
			label14.setText("Channel 2");
			label14.setHorizontalAlignment(SwingConstants.CENTER);
			label14.setOpaque(true);
			label14.setBackground(new Color(0, 0, 204));
			pump1DetailPanel.add(label14, cc.xy(1, 1));

			// ======== panel6 ========
			{
				panel6.setLayout(new FormLayout("right:default:grow, $lcgap, [30dlu,default]",
						"default, $lgap, [12dlu,default], 2*($lgap, default), $lgap, [12dlu,default], 4*($lgap, default)"));

				// ---- label4 ----
				label4.setText("Rate:");
				label4.setHorizontalAlignment(SwingConstants.RIGHT);
				panel6.add(label4, cc.xy(1, 1));

				// ---- rateB ----
				rateB.setText("---");
				rateB.setHorizontalAlignment(SwingConstants.RIGHT);
				panel6.add(rateB, cc.xy(3, 1));

				// ---- label10 ----
				label10.setText("VTBI:");
				label10.setHorizontalAlignment(SwingConstants.RIGHT);
				panel6.add(label10, cc.xy(1, 5));

				// ---- vtbiB ----
				vtbiB.setText("---");
				vtbiB.setHorizontalAlignment(SwingConstants.RIGHT);
				panel6.add(vtbiB, cc.xy(3, 5));

				// ---- label8 ----
				label8.setText("Total Volume:");
				label8.setHorizontalAlignment(SwingConstants.RIGHT);
				panel6.add(label8, cc.xy(1, 7));

				// ---- totalVolumeB ----
				totalVolumeB.setText("---");
				totalVolumeB.setHorizontalAlignment(SwingConstants.RIGHT);
				panel6.add(totalVolumeB, cc.xy(3, 7));

				// ---- label3 ----
				label3.setText("Dev Status:");
				panel6.add(label3, cc.xy(1, 11));

				// ---- devStatusB ----
				devStatusB.setText("---");
				panel6.add(devStatusB, cc.xy(3, 11));

				// ---- label6 ----
				label6.setText("Control Status:");
				panel6.add(label6, cc.xy(1, 13));

				// ---- controlStatusB ----
				controlStatusB.setText("---");
				panel6.add(controlStatusB, cc.xy(3, 13));

				// ---- label7 ----
				label7.setText("Infusion Status:");
				panel6.add(label7, cc.xy(1, 15));

				// ---- infusionStatusB ----
				infusionStatusB.setText("---");
				panel6.add(infusionStatusB, cc.xy(3, 15));

				// ---- label12 ----
				label12.setText("Action Status:");
				panel6.add(label12, cc.xy(1, 17));

				// ---- actionStatusB ----
				actionStatusB.setText("---");
				panel6.add(actionStatusB, cc.xy(3, 17));
			}
			pump1DetailPanel.add(panel6, cc.xy(1, 3));

			// ---- pump2Settings ----
			pump2Settings.setText("Settings");
			pump2Settings.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					pump2SettingsActionPerformed(e);
				}
			});
			pump1DetailPanel.add(pump2Settings, cc.xy(1, 5));
		}
		add(pump1DetailPanel, cc.xy(7, 1));
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
	private JPanel chart2Panel;
	private JPanel pump1DetailPanel;
	private JLabel label14;
	private JPanel panel6;
	private JLabel label4;
	private JLabel rateB;
	private JLabel label10;
	private JLabel vtbiB;
	private JLabel label8;
	private JLabel totalVolumeB;
	private JLabel label3;
	private JLabel devStatusB;
	private JLabel label6;
	private JLabel controlStatusB;
	private JLabel label7;
	private JLabel infusionStatusB;
	private JLabel label12;
	private JLabel actionStatusB;
	private JButton pump2Settings;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
