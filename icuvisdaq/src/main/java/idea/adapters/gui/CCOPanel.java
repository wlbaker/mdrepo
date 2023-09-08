/*
 * Created by JFormDesigner on Sun Jun 03 13:03:33 CDT 2012
 */

package idea.adapters.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.io.IOException;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import javax.swing.JLabel;
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

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.display.RefreshablePanel;
import idea.intf.IDEAClient;
import idea.intf.IDEATransferInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;
import idea.IdeaTimeManager;

/**
 * @author User #1
 */
@Slf4j
@SuppressWarnings("serial")
public class CCOPanel extends JPanel implements StreamConsumer, RefreshablePanel {

	private static final int CCO_HISTORY_JOB = 103; // THIS WILL NOT
													// WORK...consider two cco
													// panels!!!

	private static final int POINTWIDTH_MINUTES = 2;

	private ChartPanel panel;
	private JFreeChart jfreechart;
	private XYPlot xyplot;

	private RpDevice conf;
	Map<String, TimeSeries> datasets = new HashMap<String, TimeSeries>();
	private static final int DOMAIN_IN_MINUTES = 60 * 2;
	private static final Color light_blue = new Color(180, 180, 255);

	private DecimalFormat df1 = new DecimalFormat("0.0");
	private DecimalFormat df0 = new DecimalFormat("0");

	private DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	private StreamProducer driver;

	private JLabel[] fields;
	private JLabel[] params;

	public CCOPanel(StreamProducer driver, RpDevice conf2) {
		initComponents();
		this.conf = conf2;
		this.driver = driver;

		fields = new JLabel[] { ccoValue, svo2Value, sqiValue, edvValue, edviValue, rvefValue, rvefiValue, btValue };
		params = new JLabel[] { param1, param2, param3, param4, param5, param6, param7, param8 };

		panel = initChart();
		chartContainer.add(panel, BorderLayout.CENTER);

		reset(driver);
		setParamGroup();

		errorText.setText(" ");
	}

	@Override
	public void reset(StreamProducer driver) {

		driver.addStreamListener(StreamID.MEASUREMENT, this);
	}

	private void setParamGroup() {
		String[] group2 = { "DO2", "ESV", "VO2", "ESVI", "SaO2", "", "CVP", "MAP" };
		String[] group4 = { "CvO2", "CaO2", "PVR", "PVRI", "LVSWI", "RVSWI", "SV", "SVI" };
		param1.setName("DO2");
		param2.setName("ESV");
		param3.setName("VO2");
		param4.setName("ESVI");
		param5.setName("SaO2");
		param6.setName("");
		param7.setName("CVP");
		param8.setName("MAP");

		bf1.setText(param1.getName());
		bf2.setText(param2.getName());
		bf3.setText(param3.getName());
		bf4.setText(param4.getName());
		bf5.setText(param5.getName());
		bf6.setText(param6.getName());
		bf7.setText(param7.getName());
		bf8.setText(param8.getName());

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

		Color turquise = new Color(64, 224, 208);
		JFreeChart jfreechart = ChartFactory.createTimeSeriesChart("", "", "SvO2", null, true, true, false);
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
			NumberAxis numberaxis = new NumberAxis("CCO");
			numberaxis.setFixedDimension(25D);
			numberaxis.setAutoRangeIncludesZero(false);
			numberaxis.setLabelPaint(Color.yellow);
			numberaxis.setTickLabelPaint(Color.yellow);
			numberaxis.setAutoRange(false);
			numberaxis.setRange(2, 10);
			xyplot.setRangeAxis(0, numberaxis);
			xyplot.setRangeAxisLocation(1, AxisLocation.BOTTOM_OR_LEFT);

			StandardXYItemRenderer standardxyitemrenderer = new StandardXYItemRenderer();
			standardxyitemrenderer.setSeriesPaint(0, Color.yellow);
			xyplot.setRenderer(0, standardxyitemrenderer);
		}
		{

			NumberAxis numberaxis = new NumberAxis("SvO2");
			numberaxis.setFixedDimension(25D);
			numberaxis.setAutoRangeIncludesZero(false);
			numberaxis.setLabelPaint(turquise);
			numberaxis.setTickLabelPaint(turquise);
			numberaxis.setAutoRange(false);
			numberaxis.setRange(0, 100);

			xyplot.setRangeAxis(1, numberaxis);
			// XYItemRenderer xyitemrenderer = xyplot.getRenderer();
			StandardXYItemRenderer standardxyitemrenderer1 = new StandardXYItemRenderer();
			standardxyitemrenderer1.setSeriesPaint(0, turquise);
			// standardxyitemrenderer1.setSeriesPaint(1, turquise);
			xyplot.setRenderer(1, standardxyitemrenderer1);
		}

		{
			NumberAxis numberaxis1 = new NumberAxis("EDV");
			numberaxis1.setLabelPaint(Color.magenta);
			numberaxis1.setTickLabelPaint(Color.magenta);
			numberaxis1.setAutoRange(false);
			numberaxis1.setRange(60, 360);
			xyplot.setRangeAxis(2, numberaxis1);

			xyplot.mapDatasetToRangeAxis(2, 2);
			StandardXYItemRenderer standardxyitemrenderer1 = new StandardXYItemRenderer();
			standardxyitemrenderer1.setSeriesPaint(0, Color.magenta);
			xyplot.setRenderer(2, standardxyitemrenderer1);
		}
		{
			NumberAxis numberaxis2 = new NumberAxis("RVEF");
			numberaxis2.setLabelPaint(light_blue);
			numberaxis2.setTickLabelPaint(light_blue);
			numberaxis2.setAutoRange(false);
			numberaxis2.setRange(0, 100);
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

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		chartContainer = new JPanel();
		boxPanel = new JPanel();
		panel2 = new JPanel();
		label2 = new JLabel();
		svo2Value = new JLabel();
		sqiValue = new JLabel();
		panel1 = new JPanel();
		label1 = new JLabel();
		ccoValue = new JLabel();
		panel3 = new JPanel();
		label3 = new JLabel();
		edvValue = new JLabel();
		edviValue = new JLabel();
		panel4 = new JPanel();
		label4 = new JLabel();
		rvefValue = new JLabel();
		rvefiValue = new JLabel();
		panel5 = new JPanel();
		label5 = new JLabel();
		btValue = new JLabel();
		panel6 = new JPanel();
		panel7 = new JPanel();
		bf1 = new JLabel();
		param1 = new JLabel();
		bf2 = new JLabel();
		param2 = new JLabel();
		bf3 = new JLabel();
		param3 = new JLabel();
		bf4 = new JLabel();
		param4 = new JLabel();
		panel8 = new JPanel();
		bf5 = new JLabel();
		param5 = new JLabel();
		bf6 = new JLabel();
		param6 = new JLabel();
		bf7 = new JLabel();
		param7 = new JLabel();
		bf8 = new JLabel();
		param8 = new JLabel();
		errorText = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow, $lcgap, [90dlu,default]", "fill:default:grow, $rgap, default"));

		//======== chartContainer ========
		{
			chartContainer.setLayout(new BorderLayout());
		}
		add(chartContainer, cc.xy(1, 1));

		//======== boxPanel ========
		{
			boxPanel.setLayout(new FormLayout("default:grow",
					"4*(fill:default:grow, $lgap), default, $lgap, fill:default:grow"));

			//======== panel2 ========
			{
				panel2.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(0, 10, 0, 4)));
				panel2.setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, default:grow",
						"default, $lgap, default:grow, $lgap, default"));

				//---- label2 ----
				label2.setText("SvO2");
				panel2.add(label2, cc.xy(1, 1));

				//---- svo2Value ----
				svo2Value.setText("62");
				svo2Value.setFont(new Font("Tahoma", Font.PLAIN, 26));
				svo2Value.setName("SvO2");
				panel2.add(svo2Value, cc.xywh(1, 3, 1, 3));

				//---- sqiValue ----
				sqiValue.setText("/2.9");
				sqiValue.setName("SQI");
				panel2.add(sqiValue, cc.xy(5, 5));
			}
			boxPanel.add(panel2, cc.xy(1, 1));

			//======== panel1 ========
			{
				panel1.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(4, 10, 0, 4)));
				panel1.setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, default:grow",
						"default, $lgap, default:grow, $lgap, default"));

				//---- label1 ----
				label1.setText("CCO");
				panel1.add(label1, cc.xy(1, 1));

				//---- ccoValue ----
				ccoValue.setText("5.8");
				ccoValue.setFont(new Font("Tahoma", Font.PLAIN, 26));
				ccoValue.setName("CO");
				panel1.add(ccoValue, cc.xywh(1, 3, 1, 3));
			}
			boxPanel.add(panel1, cc.xy(1, 3));

			//======== panel3 ========
			{
				panel3.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(0, 10, 0, 4)));
				panel3.setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, default:grow",
						"default, $lgap, default:grow, $lgap, default"));

				//---- label3 ----
				label3.setText("EDV");
				panel3.add(label3, cc.xy(1, 1));

				//---- edvValue ----
				edvValue.setText("145");
				edvValue.setFont(new Font("Tahoma", Font.PLAIN, 26));
				edvValue.setName("EDV");
				panel3.add(edvValue, cc.xywh(1, 3, 1, 3));

				//---- edviValue ----
				edviValue.setText("edvi");
				edviValue.setName("EDVi");
				panel3.add(edviValue, cc.xy(5, 5));
			}
			boxPanel.add(panel3, cc.xy(1, 5));

			//======== panel4 ========
			{
				panel4.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(0, 10, 0, 4)));
				panel4.setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, default:grow",
						"default, $lgap, default:grow, $lgap, default"));

				//---- label4 ----
				label4.setText("RVEF");
				panel4.add(label4, cc.xy(1, 1));

				//---- rvefValue ----
				rvefValue.setText("50");
				rvefValue.setFont(new Font("Tahoma", Font.PLAIN, 26));
				rvefValue.setName("RVEF");
				panel4.add(rvefValue, cc.xywh(1, 3, 1, 3));

				//---- rvefiValue ----
				rvefiValue.setText("/73");
				rvefiValue.setName("RVEFi");
				panel4.add(rvefiValue, cc.xy(5, 5));
			}
			boxPanel.add(panel4, cc.xy(1, 7));

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
			boxPanel.add(panel5, cc.xy(1, 9));

			//======== panel6 ========
			{
				panel6.setBorder(LineBorder.createBlackLineBorder());
				panel6.setLayout(new FormLayout("default:grow, $lcgap, default:grow", "fill:default:grow"));

				//======== panel7 ========
				{
					panel7.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(4, 4, 4, 4)));
					panel7.setLayout(new FormLayout("left:default:grow, $lcgap, right:[20dlu,default]:grow",
							"4*(default, $lgap), default"));

					//---- bf1 ----
					bf1.setText("SVR:");
					panel7.add(bf1, cc.xy(1, 1));

					//---- param1 ----
					param1.setText("txt");
					panel7.add(param1, cc.xy(3, 1));

					//---- bf2 ----
					bf2.setText("ESV:");
					panel7.add(bf2, cc.xy(1, 3));

					//---- param2 ----
					param2.setText("text");
					panel7.add(param2, cc.xy(3, 3));

					//---- bf3 ----
					bf3.setText("SVRI:");
					panel7.add(bf3, cc.xy(1, 5));

					//---- param3 ----
					param3.setText("text");
					panel7.add(param3, cc.xy(3, 5));

					//---- bf4 ----
					bf4.setText("ESVI:");
					panel7.add(bf4, cc.xy(1, 7));

					//---- param4 ----
					param4.setText("text");
					panel7.add(param4, cc.xy(3, 7));
				}
				panel6.add(panel7, cc.xy(1, 1));

				//======== panel8 ========
				{
					panel8.setBorder(new CompoundBorder(new LineBorder(Color.lightGray), new EmptyBorder(4, 4, 4, 4)));
					panel8.setLayout(new FormLayout("default:grow, $lcgap, right:[20dlu,default]:grow",
							"default, $lgap, fill:10dlu, $lgap, default, $lgap, fill:default, $lgap, default"));

					//---- bf5 ----
					bf5.setText("SaO2:");
					panel8.add(bf5, cc.xy(1, 1));

					//---- param5 ----
					param5.setText("text");
					panel8.add(param5, cc.xy(3, 1));
					panel8.add(bf6, cc.xy(1, 3));

					//---- param6 ----
					param6.setText("text");
					panel8.add(param6, cc.xy(3, 3));

					//---- bf7 ----
					bf7.setText("MAP:");
					panel8.add(bf7, cc.xy(1, 5));

					//---- param7 ----
					param7.setText("text");
					panel8.add(param7, cc.xy(3, 5));

					//---- bf8 ----
					bf8.setText("CVP:");
					panel8.add(bf8, cc.xy(1, 7));

					//---- param8 ----
					param8.setText("text");
					panel8.add(param8, cc.xy(3, 7));
				}
				panel6.add(panel8, cc.xy(3, 1));
			}
			boxPanel.add(panel6, cc.xy(1, 11));
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
	private JLabel label2;
	private JLabel svo2Value;
	private JLabel sqiValue;
	private JPanel panel1;
	private JLabel label1;
	private JLabel ccoValue;
	private JPanel panel3;
	private JLabel label3;
	private JLabel edvValue;
	private JLabel edviValue;
	private JPanel panel4;
	private JLabel label4;
	private JLabel rvefValue;
	private JLabel rvefiValue;
	private JPanel panel5;
	private JLabel label5;
	private JLabel btValue;
	private JPanel panel6;
	private JPanel panel7;
	private JLabel bf1;
	private JLabel param1;
	private JLabel bf2;
	private JLabel param2;
	private JLabel bf3;
	private JLabel param3;
	private JLabel bf4;
	private JLabel param4;
	private JPanel panel8;
	private JLabel bf5;
	private JLabel param5;
	private JLabel bf6;
	private JLabel param6;
	private JLabel bf7;
	private JLabel param7;
	private JLabel bf8;
	private JLabel param8;
	private JLabel errorText;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	private void refreshNumerics(int reqId, PersistentItem block) {

		if( block == null ) {
			clear();
			return;
		}
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

		Number Fnn = IntfUtil.getScaledValueByLoc(block, "Fnn");
		Number fnn = IntfUtil.getScaledValueByLoc(block, "fnn");
		if (Fnn != null) {
			err = " CO: " + Fnn;
		}
		if (fnn != null) {
			if (err == null) {
				err = " ";
			}
			err += " / OXY: " + fnn;
		}
		if (err == null) {
			errorText.setText(" ");
		} else {
			errorText.setText(df.format(new Date()) + err);
		}

		boolean showField = (reqId != CCO_HISTORY_JOB);
		for (JLabel field : fields) {
			String name = field.getName();
			Number val = IntfUtil.getScaledValueByLoc(block, name);
			if (val == null ) {
				if (showField) {
					field.setText("--");
				}
			} else {
				String pfx = (name.endsWith("i")) ? "/" : "";
				DecimalFormat fmt = df1;
				if (name.equals("EDV") || name.equals("RVEF")) {
					fmt = df0;
				}
				// don't update numerics values for history events
				if (showField) {
					field.setText(pfx + fmt.format(val.doubleValue()));
				}
				TimeSeries ds = datasets.get(name);
				if (ds != null) {
					NMinute ti = new NMinute(dt, 2);
					ds.addOrUpdate(ti, val);
				}
			}
			if (showField) {
				for (JLabel param : params) {
					name = param.getName();
					Number pval = IntfUtil.getScaledValueByLoc(block, name);
					if (pval == null) {
						param.setText("");
					} else {
						String pfx = (name.endsWith("i")) ? "/" : "";
						DecimalFormat fmt = df0;
						param.setText(pfx + fmt.format(pval.doubleValue()));
					}
				}
			}
		}
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
		XYDataset xydataset1 = createDataset("CO", 1000D, NMinute.class);
		xyplot.setDataset(0, xydataset1);
		xyplot.mapDatasetToRangeAxis(1, 1);

		XYDataset xydataset = createDataset("SvO2", 100D, NMinute.class);
		xyplot.setDataset(1, xydataset);
		XYDataset xydataset2 = createDataset("EDV", 10000D, NMinute.class);
		xyplot.setDataset(2, xydataset2);
		XYDataset xydataset3 = createDataset("RVEF", 25D, NMinute.class);
		xyplot.setDataset(3, xydataset3);

	}

	@Override
	public void update() {
		setRangeEndTime(IdeaTimeManager.getCurrentTime());

		Set<String> keys = datasets.keySet();
		for (String key : keys) {
			TimeSeries ds = datasets.get(key);
			log.info("BETA2 FIXME: ds.removeAgedItems(arg0, arg1)");
		}
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
		for (JLabel param : params) {
			param.setText("");
		}
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		
		if (sid == StreamID.MEASUREMENT) {
			refreshNumerics(jobID, item);
		}
	}

}
