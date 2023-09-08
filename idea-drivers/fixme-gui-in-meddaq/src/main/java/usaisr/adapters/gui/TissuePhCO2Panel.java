/*
 * Created by JFormDesigner on Sun Jun 03 13:03:33 CDT 2012
 */

package idea.adapters.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.AxisLocation;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.StandardXYItemRenderer;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.data.xy.XYDataset;
import org.jfree.ui.RectangleInsets;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.conf.DeviceConfiguration;
import idea.display.RefreshablePanel;
import idea.intf.IDEAClient;
import idea.intf.IDEATransferInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.IdeaTimeManager;
import idea.analysis.AnalysisPanelInterface;

/**
 * @author User #1
 */
@Slf4j
@SuppressWarnings("serial")
public class TissuePhCO2Panel extends JPanel implements StreamConsumer, RefreshablePanel, AnalysisPanelInterface {

	private static final int CCO_HISTORY_JOB = 103; // THIS WILL NOT
													// WORK...consider two cco
													// panels!!!

	private static final int POINTWIDTH_MINUTES = 2;

	private ChartPanel panel;
	private JFreeChart jfreechart;
	private XYPlot xyplot;

	private DeviceConfiguration conf;
	Map<String, TimeSeries> datasets = new HashMap<String, TimeSeries>();
	private static final int DOMAIN_IN_MINUTES = 60 * 2;
	private static final Color light_blue = new Color(180, 180, 255);

	private DecimalFormat df2 = new DecimalFormat("0.00");
	private DecimalFormat df1 = new DecimalFormat("0.0");
	private DecimalFormat df0 = new DecimalFormat("0");

	private DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	private StreamProducer driver;

	private JLabel[] fields;
	// private JLabel[] params;

	String phSensorLoc = "A0";
	private final static String PH_DEV = "phidget0";
	int tick = 0;

	private PhCO2Calibration lower_calibration;
	private PhCO2Calibration upper_calibration;
	private PhSensorCalibrationPanel calibrationPanel;

	public TissuePhCO2Panel(StreamProducer driver, DeviceConfiguration conf) {
		initComponents();
		this.calibrationPanel = new PhSensorCalibrationPanel();
		this.conf = conf;
		this.driver = driver;

		fields = new JLabel[] { tissueCO2Value, tissuePhValue, etCO2Value, mvValue, transQValue, btValue };

		panel = initChart();
		chartContainer.add(panel, BorderLayout.CENTER);

		reset(driver);

		errorText.setText(" ");

		clear();
		update(); // set the end time range on the domain axis
	}

	@Override
	public void reset(StreamProducer driver) {

		driver.addStreamListener(StreamID.MEASUREMENT, this);
	}

	private ChartPanel initChart() {
		jfreechart = createChart();
		ChartPanel chartpanel = new ChartPanel(jfreechart);
		chartpanel.setPreferredSize(new Dimension(600, 270));
		chartpanel.setDomainZoomable(true);
		chartpanel.setRangeZoomable(true);

		return chartpanel;
	}

	private JFreeChart createChart() {
		// Calendar cal = Calendar.getInstance();
		// cal.add(Calendar.HOUR, -2);

		JFreeChart jfreechart = ChartFactory.createTimeSeriesChart("", "", "CO2", null, true, true, false);
		jfreechart.setBackgroundPaint(Color.BLACK); // DARK_GRAY);
		jfreechart.removeLegend();

		xyplot = (XYPlot) jfreechart.getPlot();
		xyplot.setOrientation(PlotOrientation.VERTICAL);
		xyplot.setBackgroundPaint(Color.DARK_GRAY); // lightGray);
		xyplot.setDomainGridlinePaint(Color.white);
		xyplot.setRangeGridlinePaint(Color.white);
		xyplot.setAxisOffset(new RectangleInsets(5D, 5D, 5D, 5D));

		clearTrends();
		// jfreechart.addSubtitle(new
		// TextTitle("Four datasets and four range axes."));
		{
			NumberAxis numberaxis = new NumberAxis("Tissue CO2");
			// numberaxis.setFixedDimension(30D);
			numberaxis.setAutoRangeIncludesZero(false);
			numberaxis.setLabelPaint(Color.yellow);
			numberaxis.setTickLabelPaint(Color.yellow);
			numberaxis.setAutoRange(false);
			numberaxis.setRange(10, 90);
			xyplot.setRangeAxis(0, numberaxis);
			xyplot.setRangeAxisLocation(1, AxisLocation.BOTTOM_OR_LEFT);

			StandardXYItemRenderer standardxyitemrenderer = new StandardXYItemRenderer();
			standardxyitemrenderer.setSeriesPaint(0, Color.yellow);
			xyplot.setRenderer(0, standardxyitemrenderer);
		}
		{
			NumberAxis numberaxis1 = new NumberAxis("End Tidal");
			numberaxis1.setLabelPaint(Color.magenta);
			numberaxis1.setTickLabelPaint(Color.magenta);
			numberaxis1.setAutoRange(false);
			numberaxis1.setRange(10, 90);
			xyplot.setRangeAxis(2, numberaxis1);

			xyplot.mapDatasetToRangeAxis(2, 2);
			StandardXYItemRenderer standardxyitemrenderer1 = new StandardXYItemRenderer();
			standardxyitemrenderer1.setSeriesPaint(0, Color.magenta);
			xyplot.setRenderer(2, standardxyitemrenderer1);
		}
		{
			NumberAxis numberaxis2 = new NumberAxis("TransQ");
			numberaxis2.setLabelPaint(light_blue);
			numberaxis2.setTickLabelPaint(light_blue);
			numberaxis2.setAutoRange(false);
			numberaxis2.setRange(10, 90);
			xyplot.setRangeAxis(3, numberaxis2);

			xyplot.mapDatasetToRangeAxis(3, 3);
			StandardXYItemRenderer standardxyitemrenderer2 = new StandardXYItemRenderer();
			standardxyitemrenderer2.setSeriesPaint(0, light_blue);
			xyplot.setRenderer(3, standardxyitemrenderer2);
		}

		return jfreechart;
	}

	private XYDataset createDataset(String s, double startValue, Class cl) {
		TimeSeries timeseries = new TimeSeries(s, cl);
		// RegularTimePeriod regulartimeperiod1 = startTimeperiod;
		// double d1 = startValue;
		// for(int j = 0; j < i; j++)
		// {
		// timeseries.add(regulartimeperiod1, d1);
		// regulartimeperiod1 = regulartimeperiod1.next();
		// d1 *= 1.0D + (Math.random() - 0.495D) / 10D;
		// }

		datasets.put(s, timeseries);

		TimeSeriesCollection timeseriescollection = new TimeSeriesCollection();
		timeseriescollection.addSeries(timeseries);
		return timeseriescollection;
	}

	private void calibrateActionPerformed(ActionEvent e) {
		Object[] options = new Object[0];
		calibrationPanel.reset();

		JOptionPane p = new JOptionPane(calibrationPanel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null,
				options, null);
		JDialog d = p.createDialog(this, "Sensor Calibration");
		GuiUtil.initModalDialog(d, p); // makes the escape key work
		d.setResizable(true);
		d.pack();
		d.setVisible(true);

		if (calibrationPanel.isOK()) {
			try {
				
				/*
				 * save copies of calibration to local variables until all parsing successful
				 */
				PhCO2Calibration ll_cal = calibrationPanel.getLowerLimitCalibration();
				PhCO2Calibration up_cal = calibrationPanel.getUpperLimitCalibration();
				
				updateCalibrationDisplay(ll_cal, lowerPh, lowerCO2, lowerVoltage);				
				updateCalibrationDisplay(up_cal, upperPh, upperCO2, upperVoltage);
				
				lower_calibration = ll_cal;
				lower_calibration = up_cal;
			} catch (Exception ex) {
				log.error("Calibration entry error", ex);
				GuiUtil.showMessage("Invalid Calibration");
			}
		}
	}

	private void updateCalibrationDisplay(PhCO2Calibration cal, JLabel ph, JLabel co2, JLabel volt) {
		ph.setText(df2.format(cal.getPh()));
		co2.setText(df1.format(cal.getCo2()));
		volt.setText(df0.format(cal.getMv()));
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		chartContainer = new JPanel();
		boxPanel = new JPanel();
		panel2 = new JPanel();
		tissueCO2Label = new JLabel();
		tissueCO2Value = new JLabel();
		tissuePhLabel = new JLabel();
		tissuePhValue = new JLabel();
		panel1 = new JPanel();
		etCO2Label = new JLabel();
		etCO2Value = new JLabel();
		mvLabel = new JLabel();
		mvValue = new JLabel();
		panel3 = new JPanel();
		transQLabel = new JLabel();
		transQValue = new JLabel();
		panel5 = new JPanel();
		label5 = new JLabel();
		btValue = new JLabel();
		panel6 = new JPanel();
		panel7 = new JPanel();
		label9 = new JLabel();
		bf1 = new JLabel();
		upperPh = new JLabel();
		bf2 = new JLabel();
		upperVoltage = new JLabel();
		bf3 = new JLabel();
		upperCO2 = new JLabel();
		panel8 = new JPanel();
		label10 = new JLabel();
		bf5 = new JLabel();
		lowerPh = new JLabel();
		bf6 = new JLabel();
		lowerVoltage = new JLabel();
		bf7 = new JLabel();
		lowerCO2 = new JLabel();
		calibrate = new JButton();
		errorText = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow, $lcgap, [90dlu,default]", "fill:default:grow, $rgap, default"));

		//======== chartContainer ========
		{
			chartContainer.setLayout(new BorderLayout());
		}
		add(chartContainer, cc.xy(1, 1));

		//======== boxPanel ========
		{
			boxPanel.setLayout(new FormLayout("default:grow",
					"3*(fill:default:grow, $lgap), default, $lgap, fill:default:grow, $lgap, default"));

			//======== panel2 ========
			{
				panel2.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(0, 10, 0, 4)));
				panel2.setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, default:grow",
						"default, $lgap, default:grow, $lgap, default"));

				//---- tissueCO2Label ----
				tissueCO2Label.setText("Tissue CO2");
				panel2.add(tissueCO2Label, cc.xy(1, 1));

				//---- tissueCO2Value ----
				tissueCO2Value.setText("62");
				tissueCO2Value.setFont(new Font("Tahoma", Font.PLAIN, 26));
				tissueCO2Value.setName("SvO2");
				panel2.add(tissueCO2Value, cc.xywh(1, 3, 1, 3));

				//---- tissuePhLabel ----
				tissuePhLabel.setText("pH");
				panel2.add(tissuePhLabel, cc.xy(3, 5));

				//---- tissuePhValue ----
				tissuePhValue.setText("/7.4");
				tissuePhValue.setName("SQI");
				panel2.add(tissuePhValue, cc.xy(5, 5));
			}
			boxPanel.add(panel2, cc.xy(1, 1));

			//======== panel1 ========
			{
				panel1.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(4, 10, 0, 4)));
				panel1.setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, default:grow",
						"default, $lgap, default:grow, $lgap, default"));

				//---- etCO2Label ----
				etCO2Label.setText("End Tidal");
				panel1.add(etCO2Label, cc.xy(1, 1));

				//---- etCO2Value ----
				etCO2Value.setText("58");
				etCO2Value.setFont(new Font("Tahoma", Font.PLAIN, 26));
				etCO2Value.setName("CO");
				panel1.add(etCO2Value, cc.xywh(1, 3, 1, 3));

				//---- mvLabel ----
				mvLabel.setText("MV");
				panel1.add(mvLabel, cc.xy(3, 5));

				//---- mvValue ----
				mvValue.setText("/4.2");
				panel1.add(mvValue, cc.xy(5, 5));
			}
			boxPanel.add(panel1, cc.xy(1, 3));

			//======== panel3 ========
			{
				panel3.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(0, 10, 0, 4)));
				panel3.setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, default:grow",
						"default, $lgap, default:grow, $lgap, default"));

				//---- transQLabel ----
				transQLabel.setText("TransQ");
				panel3.add(transQLabel, cc.xy(1, 1));

				//---- transQValue ----
				transQValue.setText("40");
				transQValue.setFont(new Font("Tahoma", Font.PLAIN, 26));
				transQValue.setName("EDV");
				panel3.add(transQValue, cc.xywh(1, 3, 1, 3));
			}
			boxPanel.add(panel3, cc.xy(1, 5));

			//======== panel5 ========
			{
				panel5.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(4, 10, 4, 4)));
				panel5.setLayout(new FormLayout("default, $lcgap, right:default:grow", "default"));

				//---- label5 ----
				label5.setText("BT:");
				panel5.add(label5, cc.xy(1, 1));

				//---- btValue ----
				btValue.setText("36.9");
				btValue.setName("BT");
				panel5.add(btValue, cc.xy(3, 1));
			}
			boxPanel.add(panel5, cc.xy(1, 7));

			//======== panel6 ========
			{
				panel6.setBorder(LineBorder.createBlackLineBorder());
				panel6.setLayout(new FormLayout("default:grow, $lcgap, default:grow", "fill:default:grow"));

				//======== panel7 ========
				{
					panel7.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(4, 4, 4, 4)));
					panel7.setLayout(new FormLayout("right:default:grow, $lcgap, right:[20dlu,default]:grow",
							"4*(default, $lgap), default"));

					//---- label9 ----
					label9.setText("Upper Cal");
					panel7.add(label9, cc.xywh(1, 1, 3, 1, CellConstraints.CENTER, CellConstraints.DEFAULT));

					//---- bf1 ----
					bf1.setText("pH:");
					panel7.add(bf1, cc.xy(1, 5));

					//---- upperPh ----
					upperPh.setText("txt");
					panel7.add(upperPh, cc.xy(3, 5));

					//---- bf2 ----
					bf2.setText("mV:");
					panel7.add(bf2, cc.xy(1, 7));

					//---- upperVoltage ----
					upperVoltage.setText("text");
					panel7.add(upperVoltage, cc.xy(3, 7));

					//---- bf3 ----
					bf3.setText("CO2:");
					panel7.add(bf3, cc.xy(1, 9));

					//---- upperCO2 ----
					upperCO2.setText("text");
					panel7.add(upperCO2, cc.xy(3, 9));
				}
				panel6.add(panel7, cc.xy(1, 1));

				//======== panel8 ========
				{
					panel8.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(4, 4, 4, 4)));
					panel8.setLayout(new FormLayout("right:default:grow, $lcgap, right:[20dlu,default]:grow",
							"3*(default, $lgap), fill:default, $lgap, default"));

					//---- label10 ----
					label10.setText("Lower Cal");
					panel8.add(label10, cc.xywh(1, 1, 3, 1, CellConstraints.CENTER, CellConstraints.DEFAULT));

					//---- bf5 ----
					bf5.setText("pH:");
					panel8.add(bf5, cc.xy(1, 5));

					//---- lowerPh ----
					lowerPh.setText("text");
					panel8.add(lowerPh, cc.xy(3, 5));

					//---- bf6 ----
					bf6.setText("mV:");
					panel8.add(bf6, cc.xy(1, 7));

					//---- lowerVoltage ----
					lowerVoltage.setText("text");
					panel8.add(lowerVoltage, cc.xy(3, 7));

					//---- bf7 ----
					bf7.setText("CO2:");
					panel8.add(bf7, cc.xy(1, 9));

					//---- lowerCO2 ----
					lowerCO2.setText("text");
					panel8.add(lowerCO2, cc.xy(3, 9));
				}
				panel6.add(panel8, cc.xy(3, 1));
			}
			boxPanel.add(panel6, cc.xy(1, 9));

			//---- calibrate ----
			calibrate.setText("Calibrate");
			calibrate.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					calibrateActionPerformed(e);
				}
			});
			boxPanel.add(calibrate, cc.xy(1, 11));
		}
		add(boxPanel, cc.xy(3, 1));

		//---- errorText ----
		errorText.setText("text");
		add(errorText, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel chartContainer;
	private JPanel boxPanel;
	private JPanel panel2;
	private JLabel tissueCO2Label;
	private JLabel tissueCO2Value;
	private JLabel tissuePhLabel;
	private JLabel tissuePhValue;
	private JPanel panel1;
	private JLabel etCO2Label;
	private JLabel etCO2Value;
	private JLabel mvLabel;
	private JLabel mvValue;
	private JPanel panel3;
	private JLabel transQLabel;
	private JLabel transQValue;
	private JPanel panel5;
	private JLabel label5;
	private JLabel btValue;
	private JPanel panel6;
	private JPanel panel7;
	private JLabel label9;
	private JLabel bf1;
	private JLabel upperPh;
	private JLabel bf2;
	private JLabel upperVoltage;
	private JLabel bf3;
	private JLabel upperCO2;
	private JPanel panel8;
	private JLabel label10;
	private JLabel bf5;
	private JLabel lowerPh;
	private JLabel bf6;
	private JLabel lowerVoltage;
	private JLabel bf7;
	private JLabel lowerCO2;
	private JButton calibrate;
	private JLabel errorText;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	private void refreshNumerics(int reqId, PersistentItem block) {

		Date dt = block.getTm();
		Calendar cal = Calendar.getInstance();
		cal.setTime(dt);
		cal.set(Calendar.SECOND, 0);
		cal.set(Calendar.MILLISECOND, 0);
		int unroundedMinutes = cal.get(Calendar.MINUTE);
		int mod = unroundedMinutes % POINTWIDTH_MINUTES;
		int min = unroundedMinutes + (POINTWIDTH_MINUTES - mod);

		cal.set(Calendar.MINUTE, min);
		dt = cal.getTime();

		String err = null;

		Number ph_sensor = IntfUtil.getScaledValueByLoc(block, phSensorLoc);

		if (ph_sensor != null) {
			double v = ph_sensor.doubleValue();
			double tissueCO2 = fromCalibrationCO2(v);
			tissueCO2Value.setText(df2.format(tissueCO2));
			double tissuePH = fromCalibrationPH(v);
			tissuePhValue.setText(df2.format(tissuePH));
			err = " pH: " + tissuePH;

			TimeSeries ds = datasets.get("tiCO2");
			NMinute ti = new NMinute(dt, 2);
			ds.addOrUpdate(ti, tissueCO2);

			if (calibrationPanel.isVisible()) {
				calibrationPanel.setVoltage(df2, v);
			}
		}
		
		String tdt = df.format(new Date());
		if (err == null) {
			errorText.setText(tdt);
		} else {
			errorText.setText(tdt + err);
		}

	}

	private double fromCalibrationPH(double mv) {
		return 8 + mv / 100;
	}

	private double fromCalibrationCO2(double mv) {
		// calibUpper = 1;
		return 50 + mv / 10;
	}

	@Override
	public void refresh(IDEAClient idea, Date dt) {

		clearTrends();

		if (dt == null) {
			dt = IdeaTimeManager.getCurrentTime();
		}

		Calendar cal = Calendar.getInstance();
		if (dt != null) {
			cal.setTime(dt);
		}
		cal.add(Calendar.MINUTE, -DOMAIN_IN_MINUTES);
		Date dtStart = cal.getTime();
		Date dtEnd = dt;

		setRangeEndTime(dtEnd);

		IDEATransferInterface req = idea.createTransferRequest(CCO_HISTORY_JOB, dtStart, dtEnd, conf, 60 * 1000);
		req.addStreamListener(StreamID.MEASUREMENT, this);
		try {
			req.connect();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void clearTrends() {
		// let the old series die in garbage collection
		XYDataset xydataset1 = createDataset("tiCO2", 1000D, NMinute.class);
		xyplot.setDataset(0, xydataset1);
		xyplot.mapDatasetToRangeAxis(1, 1);

		XYDataset xydataset = createDataset("ZZ", 100D, NMinute.class);
		xyplot.setDataset(1, xydataset);
		XYDataset xydataset2 = createDataset("etCO2", 10000D, NMinute.class);
		xyplot.setDataset(2, xydataset2);
		XYDataset xydataset3 = createDataset("trCO2", 25D, NMinute.class);
		xyplot.setDataset(3, xydataset3);

	}

	@Override
	public void update() {
		setRangeEndTime(IdeaTimeManager.getCurrentTime());

	}

	private void setRangeEndTime(Date date) {

		XYPlot xyplot = (XYPlot) jfreechart.getPlot();
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		cal.add(Calendar.MINUTE, -DOMAIN_IN_MINUTES - 6);
		Date lower = cal.getTime();
		cal.add(Calendar.MINUTE, DOMAIN_IN_MINUTES + 12);
		Date upper = cal.getTime();

		DateAxis domainAxis = (DateAxis) xyplot.getDomainAxis();
		domainAxis.setRange(lower, upper);
		domainAxis.setTickLabelPaint(Color.WHITE);
		// domainAxis.set

	}

	@Override
	public void clear() {
		for (JLabel field : fields) {
			field.setText("--");
		}
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if (sid == StreamID.MEASUREMENT) {
			String src_name = source.getConfiguration().getName();
			try {
				if (PH_DEV.equals(src_name)) {
					refreshNumerics(jobID, item);
				}
			} catch (Exception e) {
				log.error("refresh erro", e);
			}
		}
	}

	@Override
	public void autoscale() {
		// TODO Auto-generated method stub

	}

	@Override
	public void tick() {
		tick++;
		if (tick > 10) {
			update();
			tick = 0;
		}

	}

	@Override
	public StreamProducer[] getSignalProducers() {
		// TODO Auto-generated method stub
		return null;
	}

}
