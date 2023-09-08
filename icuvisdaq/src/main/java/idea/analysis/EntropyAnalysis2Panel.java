/*
 * Created by JFormDesigner on Tue Dec 10 10:54:29 CST 2013
 */

package idea.analysis;

import icuInterface.PlatformUtil;
import icuInterface.RpUtil;
import idea.buffer.SignalBuffer;
import idea.conf.DeviceConfiguration;
import idea.display.BandLayout;
import idea.display.RefreshablePanel;
import idea.display.WaveformData;
import idea.intf.IDEAClient;
import idea.intf.IDEATransferInterface;
import idea.intf.MultiplexInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.DisplayConfig;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.StringStringMap;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;

import lombok.extern.slf4j.Slf4j;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.annotations.XYTextAnnotation;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.labels.StandardXYToolTipGenerator;
import org.jfree.chart.plot.CombinedDomainXYPlot;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.chart.title.LegendTitle;
import org.jfree.data.Range;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.ui.TextAnchor;

import idea.GuiUtil;
import idea.adapters.gui.NMinute;
import idea.analysis.ecg.HRVPoint;
import idea.analysis.event.BeatBlock;
import idea.analysis.event.EntropyBlock;
import idea.analysis.event.MSEBlock;
import idea.buffer.SignalBuffer;
import idea.meddaq.AppModel;
import idea.qrsdet.AbstractDetector;
import idea.qrsdet.DetectorFactory;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

// [done] ... ISSUE #1: get time from either numerics block or PersistenceItemBase
// ... ISSUE #2: get scaled value from IntfUtil.getScaledValue( pib ) is not scaled
// [test?] ... ISSUE #3: RRI time is wrong!
// [done] ... ISSUE #4: correctly position values on graph
// [done] ... ISSUE #5: Get IntfUtil from d*
// [fixed] ... ISSUE #6: Get EntropyBlock from d*
// ... ISSUE #7: Why does MSE jump up to 420? Multip blocks with same loc?

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class EntropyAnalysis2Panel extends JPanel implements AnalysisPanelInterface, StreamConsumer, RefreshablePanel {
	private static final int DEFAULT_HISTORY_IN_HOURS = 2;
	private static final int TREND_HISTORY_JOBID = 303;
	private static final int MINS_PER_DATAPOINT = 1;
	private static final long MINIMUM_REFRESH_MS = 10000;
	private static final long DISCONNECT_MS = 80 * 1000;

	private int historyInHours = DEFAULT_HISTORY_IN_HOURS;
	private DateAxis domainAxis;
	private CombinedDomainXYPlot topPlot;
	private CombinedDomainXYPlot rightPlot;
	private CombinedDomainXYPlot leftPlot;
	// private XYItemRenderer lineRenderer;
	private Map<String, TimeSeries> series = new HashMap<String, TimeSeries>();
	private Map<String, Long> updateTimes = new HashMap<String, Long>();
	private int tick;
	private XYPlot lastPlot;

	NumberFormat df1 = new DecimalFormat("0.#");
	NumberFormat df2 = new DecimalFormat("0.00");

	AbstractDetector detector;
	EntropyFilter entr;
	MultiscaleEntropyProcessor mse;
	HRVProcessor hrv;

	private RpDevice dev_conf;

	private XYPlot rri_plot;
	private int deltaMinutes;
	private XYTextAnnotation mse_warning_annotation;
	private XYTextAnnotation entr_warning_annotation;
	private XYTextAnnotation mse_value_annotation;
	private XYTextAnnotation entr_value_annotation;
	private XYTextAnnotation qse_value_annotation;

	private XYTextAnnotation hf_warning_annotation;
	private XYTextAnnotation hf_value_annotation;

	private XYTextAnnotation lf_warning_annotation;
	private XYTextAnnotation lf_value_annotation;

	private int rri_timer;
	private XYTextAnnotation rri_annotation;
	private Font anno_font;
	private XYPlot hf_plot;
	private XYPlot lf_plot;
	private String debug_name;
	private long last_entropy_tm;

	private static final DateFormat tf = new SimpleDateFormat("_yyyyMMdd_HHmmss");

	public EntropyAnalysis2Panel(StreamProducer[] producers, RpAnalysis anal) {
		initComponents();

		String anal_name = anal.getName();
		if (anal_name != null) {
			anal_name = anal_name.replace(":", "_");
			anal_name = anal_name.replace(" ", "");
			setName(anal_name);
		}
		debug_name = anal_name;

		anno_font = new Font("Tahoma", Font.PLAIN, 26);
		domainAxis = new DateAxis("");
		domainAxis.setLowerMargin(0.0);
		domainAxis.setUpperMargin(0.02);

		topPlot = new CombinedDomainXYPlot(domainAxis);
		topPlot.setGap(8.0);
		topPlot.setDomainGridlinePaint(Color.white);
		topPlot.setDomainGridlinesVisible(true);

		wire(producers, anal);

		if (detector == null) {
			log.error("Could not find detector.");
		} else {
			detector.addStreamListener(StreamID.MEASUREMENT, this);
			entr = new EntropyFilter(200, 6, 2);
			entr.setRecalcPeriod(10000);

			detector.addStreamListener(StreamID.MEASUREMENT, entr);

			mse = new MultiscaleEntropyProcessor(800, 6, 2);
			mse.setRecalcPeriod(10000);
			detector.addStreamListener(StreamID.MEASUREMENT, mse);

		}

		if (detector != null) {
			TimeSeriesCollection ds = new TimeSeriesCollection();
			rri_plot = addTrends(null, ds, BeatBlock.MS_INTERVAL_LOC, Color.GREEN);
			rri_plot.getRangeAxis().setUpperBound(1200.0);
			rri_plot.getRangeAxis().setLowerBound(200.0);
			rri_plot.getRangeAxis().setAutoRange(false);
			topPlot.add(rri_plot, 3);

			rri_annotation = new XYTextAnnotation("-- RRI --", 0.0, 300);
			rri_plot.addAnnotation(rri_annotation);

			final TimeSeries rri_series = ds.getSeries(0);
			detector.addStreamListener(StreamID.MEASUREMENT, new StreamConsumer() {

				@Override
				public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

					BeatBlock block = (BeatBlock) item;
					Number val = IntfUtil.getScaledValueByLoc(block, "rri");
					if (val == null) {
						val = block.getMs_interval();
					}

					long tm = IntfUtil.getTime(block);

					Date dt = new Date(tm);

					add1MinData(rri_series, dt, val, true);
				}
			});

		}

		StreamProducer drager = AppModel.getSignalProducer("Drager");
		buildRightPlot(drager);
		buildLeftPlot(drager);
		/*
		 * loop here?
		 */

		// addTrends();
		addChart(topPanel, topPlot);
		addChart(rightPanel, rightPlot);
		addChart(leftPanel, leftPlot);

		/*
		 * end loop
		 */

		wireProducersAndConsumers(producers, anal);
		updateDomainAxis(getDate());

		live.setVisible(false);
		hf.setText(" ");
		lf.setText(" ");
		hf_lf.setText(" ");
		lf_hf.setText(" ");

		mse_d.setText(" ");
		sampen_d.setText(" ");
		qse_d.setText(" ");
	}

	private void buildLeftPlot(StreamProducer drager) {

		hrv = new HRVProcessor( //
				200, // 200 hz from Drager
				200 * 120, // 200 hz for 120 secs....2 min window
				1024 // resample size...pretty much fixed
		);

		if (detector == null) {
			log.error("No detector for left plot.");
		} else {
			detector.addStreamListener(StreamID.MEASUREMENT, hrv);
		}

		leftPlot = new CombinedDomainXYPlot(domainAxis);
		leftPlot.setGap(8.0);
		leftPlot.setDomainGridlinePaint(Color.white);
		leftPlot.setDomainGridlinesVisible(true);

		TimeSeriesCollection ds2 = new TimeSeriesCollection();
		hf_plot = addTrends(null, ds2, HRVPoint.HF_LOC, Color.MAGENTA);
		if (hrv != null) {
			hrv.addStreamListener(StreamID.MEASUREMENT, this);
			hrv.addStreamListener(StreamID.ALARM, this);
		}

		// hf_plot.getRangeAxis().setUpperBound(3.0);
		// hf_plot.getRangeAxis().setLowerBound(0);
		hf_plot.getRangeAxis().setAutoRange(true);

		hf_warning_annotation = new XYTextAnnotation("-- HF --", 0.0, 0.2);
		hf_warning_annotation.setFont(anno_font);
		hf_plot.addAnnotation(hf_warning_annotation);

		hf_value_annotation = new XYTextAnnotation(" ", 0.0, 5.0);
		hf_value_annotation.setFont(anno_font);
		hf_value_annotation.setTextAnchor(TextAnchor.BASELINE_RIGHT);
		hf_plot.addAnnotation(hf_value_annotation);

		leftPlot.add(hf_plot, 3);

		lf_plot = addTrends(null, ds2, HRVPoint.LF_LOC, Color.BLUE);
		if (hrv != null) {
			hrv.addStreamListener(StreamID.MEASUREMENT, this);
			hrv.addStreamListener(StreamID.ALARM, this);
		}

		// hf_plot.getRangeAxis().setUpperBound(3.0);
		// hf_plot.getRangeAxis().setLowerBound(0);
		lf_plot.getRangeAxis().setAutoRange(true);

		lf_warning_annotation = new XYTextAnnotation("-- LF --", 0.0, 0.2);
		lf_warning_annotation.setFont(anno_font);
		lf_plot.addAnnotation(lf_warning_annotation);

		lf_value_annotation = new XYTextAnnotation(" ", 0.0, 0.4);
		lf_value_annotation.setFont(anno_font);
		lf_value_annotation.setTextAnchor(TextAnchor.BASELINE_RIGHT);
		lf_plot.addAnnotation(lf_value_annotation);

		leftPlot.add(lf_plot, 3);
	}

	private void buildRightPlot(StreamProducer drager) {
		rightPlot = new CombinedDomainXYPlot(domainAxis);
		rightPlot.setGap(8.0);
		rightPlot.setDomainGridlinePaint(Color.white);
		rightPlot.setDomainGridlinesVisible(true);

		XYPlot plot;
		plot = addTrends(null, null, "gp2.sys", Color.BLACK);
		if (drager != null) {
			drager.addStreamListener(StreamID.MEASUREMENT, this);
			rightPlot.add(plot, 3);
		}

		TimeSeriesCollection ds2 = new TimeSeriesCollection();
		XYPlot entr_plot = addTrends(null, ds2, EntropyBlock.SAMPENT_LOC, Color.MAGENTA);
		if (entr != null) {
			entr.addStreamListener(StreamID.MEASUREMENT, this);
			entr.addStreamListener(StreamID.ALARM, this);
		}

		entr_plot.getRangeAxis().setUpperBound(3.0);
		entr_plot.getRangeAxis().setLowerBound(0);
		entr_plot.getRangeAxis().setAutoRange(false);

		entr_warning_annotation = new XYTextAnnotation("-- SampEn --", 0.0, 0.3);
		entr_warning_annotation.setFont(anno_font);
		entr_plot.addAnnotation(entr_warning_annotation);

		entr_value_annotation = new XYTextAnnotation(" ", 0.0, 0.2);
		entr_value_annotation.setFont(anno_font);
		entr_value_annotation.setTextAnchor(TextAnchor.BASELINE_RIGHT);
		entr_plot.addAnnotation(entr_value_annotation);

		qse_value_annotation = new XYTextAnnotation(" ", 0.6, 1.2);
		qse_value_annotation.setFont(anno_font);
		qse_value_annotation.setTextAnchor(TextAnchor.BASELINE_RIGHT);
		entr_plot.addAnnotation(qse_value_annotation);

		rightPlot.add(entr_plot, 3);

		TimeSeriesCollection ds1 = new TimeSeriesCollection();
		XYPlot mse_plot = addTrends(null, ds1, MSEBlock.MSE1_LOC, Color.YELLOW); // HRC
		addTrends(mse_plot, ds1, MSEBlock.MSE2_LOC, Color.GREEN); // HRC
		addTrends(mse_plot, ds1, MSEBlock.MSECOMPLEXITY_LOC, Color.RED); // HRC
		if (mse != null) {
			mse.addStreamListener(StreamID.MEASUREMENT, this);
			mse.addStreamListener(StreamID.ALARM, this);
		}

		mse_plot.getRangeAxis().setUpperBound(14.0);
		mse_plot.getRangeAxis().setLowerBound(0);
		mse_plot.getRangeAxis().setAutoRange(false);

		mse_warning_annotation = new XYTextAnnotation("-- MSE --", 0.0, 1.0);
		mse_warning_annotation.setFont(anno_font);
		mse_plot.addAnnotation(mse_warning_annotation);
		mse_value_annotation = new XYTextAnnotation(" ", 0.0, 11.0);
		mse_value_annotation.setFont(anno_font);
		mse_value_annotation.setTextAnchor(TextAnchor.BASELINE_RIGHT);
		mse_plot.addAnnotation(mse_value_annotation);

		rightPlot.add(mse_plot, 3);

	}

	private Date getDate() {
		Calendar cal = Calendar.getInstance();
		cal.add(Calendar.MINUTE, -deltaMinutes);
		return cal.getTime();
	}

	private void addChart(JPanel panel, CombinedDomainXYPlot plot) {
		JFreeChart chart = new JFreeChart(null, JFreeChart.DEFAULT_TITLE_FONT, plot, false);
		chart.setBackgroundPaint(Color.white);
		LegendTitle legend = new LegendTitle(plot);
		chart.addSubtitle(legend);

		ChartPanel p0 = new ChartPanel(chart);
		p0.setPreferredSize(new Dimension(100, 200));

		panel.add(p0, BorderLayout.CENTER);

	}

	private void wire(StreamProducer[] producers, RpAnalysis anal) {
		StringStringMap params = anal.getParam();

		String detector_name = params.get("detector");
		if (detector_name == null) {
			log.error("NO DETECTOR --> NO ANALYSIS");
			throw new RuntimeException("NO DETECTOR --> NO ANALYSIS");
		}

		String sourceName = params.get("DEV");

		// multiple devices of the same name can occur from composite importers, but we
		// only need ONE of these devices to get the waveform frequency
		
		StreamProducer producer = getNamedDevice(producers, sourceName, false);
		if (producer == null ) {
			if( sourceName.equals("Drager")) {
				sourceName = "Delta";
			} else if( sourceName.equals("Delta")) {
				sourceName = "Drager";
			}
			producer = getNamedDevice(producers, sourceName, false);
		}
		if( producer == null ) {
			sourceName = "Drager_1";
			producer = getNamedDevice(producers, sourceName, false);
		}
		if (producer == null) {
			log.error("CONFIG ERROR: signal producer does not exist: {}", sourceName);

			throw new RuntimeException("Could not find source device for entropy analysis: " + sourceName);
		}

		RpMetric wf_desc = null;
		String lloc = params.get("signal");

		dev_conf = producer.getConfiguration();
		populateSelectSignal(dev_conf);

		wf_desc = RpUtil.getMetricFromStreamID(dev_conf, StreamID.WAVEFORM, lloc);
		currentSignal.setText(lloc);

		if (wf_desc == null) {
			log.error("CONFIG ERROR/requested ECG signal not available: {}", lloc);

			throw new RuntimeException("Signal not available for entropy analysis: " + sourceName + "/" + lloc);
		}

		if (detector == null) {
			// we need the sample rate to create a beat detector
			// NOTE: although there can be multiple devices of the same name, we assume the sample rate
			// is the same between them...
			
			detector = DetectorFactory.createDetector(detector_name, wf_desc);

			if (detector == null) {
				throw new RuntimeException("DETECTOR NOT FOUND: " + detector_name);
			}
		}

		// multiple devices of the same name can occur from composite importers
		String rootSourceName = noSuffix(sourceName);
		for (StreamProducer intf : producers) {
			RpDevice dc = intf.getConfiguration();
			if (dc == null) {
				continue;
			}
			String devName = dc.getName();
			String rootDevName = noSuffix(devName);
			if (rootSourceName.equals(rootDevName) ) {
				intf.addStreamListener(StreamID.WAVEFORM, detector);
				intf.addStreamListener(StreamID.ALARM, detector);
				intf.addStreamListener(StreamID.CONNECTION, detector);
				intf.addStreamListener(StreamID.DISPLAY, this);
			}

		}
	}
	
	private String noSuffix( String extended ) {
		int pos = extended.lastIndexOf('_');
		if( pos > 0 ) {
			return extended.substring(0, pos);
		}
		return extended;
	}

	private void populateSelectSignal(RpDevice dev) {

		List<? extends RpMetric> list = RpUtil.getMetrics(dev, StreamID.WAVEFORM);

		RpMetric[] waves = new RpMetric[list.size()];
		waves = list.toArray(waves);
		DefaultComboBoxModel model = new DefaultComboBoxModel(waves);
		model.addElement("Auto");
		signalSelection.setModel(model);
	}

	private StreamProducer getNamedDevice(StreamProducer[] producers, String sourceName, boolean verbose) {
		if (producers == null) {
			return null;
		}
		if (sourceName == null) {
			log.error("source not specified for getNamedDevice()");
			return null;
		}
		String sourceAltName = sourceName + "_0";

		StreamProducer source = null;
		for (StreamProducer intf : producers) {
			RpDevice dc = intf.getConfiguration();
			if (dc == null) {
				log.warn("missing device configuration: " + intf);
				continue;
			}
			String devName = dc.getName();
			if (sourceName.equals(devName) || sourceAltName.equals(devName)) {
				source = intf;
				break;
			}
			if (intf instanceof MultiplexInterface) {
				MultiplexInterface mintf = (MultiplexInterface) intf;

				source = getNamedDevice(mintf.getSubInterfaces(), sourceName, verbose);
			}

			if (source != null) {
				break;
			}
		}

		return source;
	}

	private XYItemRenderer createLineRenderer(Color color) {

		// BETA2: V @ hr: ( , val )...should say ml or whatever the UOM is

		XYItemRenderer renderer1 = new XYLineAndShapeRenderer(true, false);
		renderer1.setBaseToolTipGenerator(
				new StandardXYToolTipGenerator(StandardXYToolTipGenerator.DEFAULT_TOOL_TIP_FORMAT,
						new SimpleDateFormat("d-MMM-yyyy HH:mm"), new DecimalFormat("0.00")));
		renderer1.setSeriesStroke(0, new BasicStroke(4.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
		renderer1.setSeriesPaint(0, color);

		return renderer1;
	}

	private XYPlot addTrends(XYPlot plot, TimeSeriesCollection ds, String sig, Color color) {

		if (ds == null) {
			ds = new TimeSeriesCollection();
		}

		/*
		 * loop for more than one variable/plot
		 */
		TimeSeries s = new TimeSeries(sig);
		s.setDescription(sig);
		series.put(sig, s); // keep a lookup table of the series created

		ds.addSeries(s);

		if (plot == null) {
			// might not be intuitive that you need a distinct renderer for each
			// plot,
			// but the renderer has a link back to the plot which is used for
			// some
			// small bits of information, like the series name used in the
			// legend
			// ...and it also knows the series colors
			XYItemRenderer lineRenderer = createLineRenderer(Color.BLUE);

			ValueAxis yAxis = new NumberAxis(sig);
			plot = new XYPlot(ds, null, yAxis, lineRenderer);
			// plot1.setBackgroundPaint(Color.lightGray);
			plot.setDomainGridlinePaint(Color.lightGray);
			plot.setRangeGridlinePaint(Color.lightGray);
			plot.getRangeAxis().setUpperBound(20.0);
			plot.getRangeAxis().setLowerBound(0);
			plot.getRangeAxis().setAutoRange(true);

			lastPlot = plot;
		}

		XYItemRenderer r = lastPlot.getRenderer();
		r.setSeriesPaint(ds.getSeriesCount() - 1, color);

		return plot;
	}

	private void updateDomainAxis(Date date) {
		int domainInMinutes = historyInHours * 60;

		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		cal.add(Calendar.MINUTE, -domainInMinutes - 2);
		Date lower = cal.getTime();
		cal.add(Calendar.MINUTE, domainInMinutes + 4);
		Date upper = cal.getTime();
		domainAxis.setRange(lower, upper);

		long range = upper.getTime() - lower.getTime();
		long mid_x = (lower.getTime() + upper.getTime()) / 2;
		mse_warning_annotation.setX(mid_x);
		entr_warning_annotation.setX(mid_x);

		long value_pos = upper.getTime() - range / 20;
		mse_value_annotation.setX(value_pos);
		entr_value_annotation.setX(value_pos);
		qse_value_annotation.setX(value_pos - 80);
		hf_value_annotation.setX(value_pos);
		lf_value_annotation.setX(value_pos);

		ValueAxis hf_axis = hf_plot.getRangeAxis();
		Range r = hf_axis.getRange();
		hf_value_annotation.setY(r.getCentralValue());

		ValueAxis lf_axis = lf_plot.getRangeAxis();
		r = lf_axis.getRange();
		lf_value_annotation.setY(r.getCentralValue());

		return;
	}

	private void wireProducersAndConsumers(StreamProducer[] producers, RpAnalysis anal) {
		StringStringMap params = anal.getParam();

		if (producers == null || producers.length == 0) {
			log.error("NO SIGNAL PRODUCERS");
			// assert( false ) : "No signal producers for analysis.";
			return;
		}

		String detector_param = params.get("detector");
		if (detector_param == null) {
			assert (detector_param != null) : "CONFIG ERROR: detector not available";
			log.error("NO DETECTOR --> NO ANALYSIS");
			return;
		}

	}

	@Override
	public void streamEvent(int jobID, StreamProducer producer, StreamID sid, PersistentItem block) {

		if (block == null) {
			log.error("unexpected null block in numerics event");
			return;
		}

		if (sid == StreamID.MEASUREMENT) {
			last_entropy_tm = IntfUtil.getTime(block);

			Number hf_val = null;
			Number lf_val = null;

			Date dt = new Date(last_entropy_tm);
			for (Entry<String, TimeSeries> entry : series.entrySet()) {
				boolean continuous = true;

				String loc = entry.getKey();
				Long lastTime = updateTimes.get(loc);
				if (lastTime != null) {
					long delta = last_entropy_tm - lastTime;
					if (delta < MINIMUM_REFRESH_MS) {
						continue;
					}
					if (delta > DISCONNECT_MS) {
						continuous = false;
					}
				}

				RpMetric metric = IntfUtil.getMetricByLoc(block, loc);
				if (metric == null) {
					continue;
				}
				Number val = (Number) IntfUtil.getScaledValue(block, metric);
				if (val != null) {
					TimeSeries s = entry.getValue();
					add1MinData(s, dt, val, continuous);
					updateTimes.put(loc, last_entropy_tm);

					if (producer instanceof EntropyFilter) {
						dump("sampen", block);

						if (!EntropyBlock.SAMPENT_LOC.equals(loc)) {
							log.error("SAMPEN VALUE EXPECTED BUT NOT FOUND");
							entr_value_annotation.setText("SAMPEN: ERR");
						} else {
							entr_value_annotation.setText("SAMPEN: " + df1.format(val));
							sampen_d.setText(df1.format(val));

							RpMetric qse = IntfUtil.getMetricByLoc(block, "QSE");
							val = (Double) IntfUtil.getScaledValue(block, qse);
							String ss = "?";
							if (val != null) {
								ss = df1.format(val);
							}
							qse_value_annotation.setText("QSE: " + ss);
							qse_d.setText(ss);
						}
					} else if (producer instanceof MultiscaleEntropyProcessor) {
						dump("mse", block);
						if (MSEBlock.MSECOMPLEXITY_LOC.equals(loc)) {
							mse_value_annotation.setText("MSE: " + df1.format(val));
							mse_d.setText(df1.format(val));
						}
					}

					if (HRVPoint.HF_LOC.equals(loc)) {
						// hf_plot.getRangeAxis().setUpperBound(3.0);
						// hf_plot.getRangeAxis().setLowerBound(0);

						hf_value_annotation.setText("HF: " + df1.format(val));
						hf.setText(df1.format(val));
						hf_val = val;
					}
					if (HRVPoint.LF_LOC.equals(loc)) {
						lf_value_annotation.setText("LF: " + df1.format(val));
						lf.setText(df1.format(val));
						lf_val = val;
					}
				}

			}
			if (hf_val != null && lf_val != null) {
				double hf_d = hf_val.doubleValue();
				double lf_d = lf_val.doubleValue();

				if (hf_d > 0 && lf_d > 0) {
					hf_lf.setText(df1.format(hf_d / lf_d));
					lf_hf.setText(df1.format(lf_d / hf_d));
				}
			}
		} else if (sid == StreamID.DISPLAY) {
			String loc = null;
			DisplayConfig disp = (DisplayConfig) block;
			if (disp == null) {
				log.error("EMPTY DISPLAY EVENT");
				return;
			}
			List<BandLayout> bands = disp.getBands();
			if (bands == null || bands.size() == 0) {
				log.warn("No display bands");
				bands = null;
			} else {
				BandLayout band0 = bands.get(0);
				if (band0.getWaveCount() == 0) {
					log.error("No waves in band[0]");
				}
				WaveformData wave0 = band0.getWave(0);
				loc = wave0.getLoc();
				RpMetric wf_desc = RpUtil.getMetricFromStreamID(dev_conf, StreamID.WAVEFORM, loc);
				if (wf_desc != null) {
					log.error("CONFIG ERROR/requested signal not available: {}", loc);
				}
			}
			if (detector != null && loc != null) {

				if (isAutoSignal()) {
					detector.setSignalLoc(loc);
					currentSignal.setText(loc);

					rri_annotation.setText("Auto signal change: " + loc);
					rri_timer = 20;
				} else {
					// ignore
				}
			}
		} else if (sid == StreamID.ALARM) {
			Alarm alarm = (Alarm) block;

			String message = alarm.getMessage();
			if (producer instanceof EntropyFilter) {
				entr_warning_annotation.setText(message);
			} else if (producer instanceof MultiscaleEntropyProcessor) {
				mse_warning_annotation.setText(message);
			} else {
				hf_warning_annotation.setText(message);
			}
		}

	}

	private void dump(String src, Object block) {
		File f = new File("c:/tmp", src);
		f.mkdirs();
		f = new File(f, debug_name + tf.format(new Date()) + ".dat");
		FileWriter w = null;
		try {
			SignalBuffer<? extends Number> rris;
			w = new FileWriter(f);
			if (block instanceof EntropyBlock) {
				EntropyBlock eb = (EntropyBlock) block;
				w.write("" + eb.getSampEnt() + "\n");
				rris = entr.getRRIs();
			} else if (block instanceof MSEBlock) {
				MSEBlock eb = (MSEBlock) block;
				w.write("" + eb.getMSE());
				w.write(" " + eb.getMSE1());
				w.write(" " + eb.getMSE2());
				w.write(" " + eb.getMSE3());
				w.write("\n");
				rris = mse.getRRIs();
			} else {
				log.error("UNRECOGNIZED DUMP TARGET");
				rris = null;
			}
			for (int i = 0; i < rris.getSampleCount(); i++) {
				w.write("" + rris.get(i));
				w.write(" ");
			}
			w.write("\n");
		} catch (Exception e) {
			log.error("dump()", e);
		} finally {
			if (w != null) {
				try {
					w.flush();
					w.close();
				} catch (IOException e) {
				}
			}

		}
	}

	private boolean isAutoSignal() {
		Object item = signalSelection.getSelectedItem();
		return "Auto".equals(item);
	}

	@Override
	public void clear() {
		for (TimeSeries s : series.values()) {
			s.setMaximumItemAge(1);
			s.setMaximumItemAge(historyInHours * 60 / MINS_PER_DATAPOINT);
		}

		clearAnnotations();
	}

	private void clearAnnotations() {
		sampen_d.setText(" ");
		mse_d.setText(" ");
		qse_d.setText(" ");
		hf.setText(" ");
		lf.setText(" ");
		hf_lf.setText(" ");
		lf_hf.setText(" ");

		entr_value_annotation.setText(" ");
		mse_value_annotation.setText(" ");

		hf_value_annotation.setText(" ");
		lf_value_annotation.setText(" ");
	}

	@Override
	public void autoscale() {
		// TODO Auto-generated method stub

	}

	@Override
	public void tick() {
		tick++;
		if (tick > 10) {
			updateDomainAxis(getDate());
			tick = 0;

			if (PlatformUtil.currentTimeMillis() - last_entropy_tm > 10000) {
				clearAnnotations();
			}
		}
		if (rri_timer > 0) {
			if (rri_timer == 1) {
				rri_annotation.setText("-- --");
			}
			rri_timer--;
		}

	}

	@Override
	public StreamProducer[] getSignalProducers() {
		StreamProducer[] producers = new StreamProducer[] { entr, mse, detector, hrv };
		return producers;
	}

	public void add1MinData(TimeSeries series, Date ts, Number val, boolean continuous) {

		if (val != null) {
			if (continuous == false) {
				Calendar cal = Calendar.getInstance();
				cal.setTime(ts);
				cal.add(Calendar.MINUTE, -1);
				NMinute prev = new NMinute(cal.getTime(), MINS_PER_DATAPOINT);
				series.addOrUpdate(prev, null);
				// ?? DOES THIS WORK???
			}
			series.addOrUpdate(new NMinute(ts, MINS_PER_DATAPOINT), val);
		}
	}

	@Override
	public void refresh(IDEAClient idea, Date dt) {
		Calendar cal = Calendar.getInstance();
		if (dt != null) {
			cal.setTime(dt);
		}
		cal.add(Calendar.HOUR, -historyInHours);
		Date dtStart = cal.getTime();
		Date dtEnd = dt;

		log.error("FIXME: need conf of variables to retrieve");
		DeviceConfiguration conf = null;
		IDEATransferInterface req = idea.createTransferRequest(TREND_HISTORY_JOBID, dtStart, dtEnd, conf,
				10 * 60 * 1000);
		req.addStreamListener(StreamID.MEASUREMENT, this);
		try {
			req.connect();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void update() {
		// TODO Auto-generated method stub

	}

	@Override
	public void reset(StreamProducer driver) {
		log.debug("attempting to retrieve historical data");
	}

	private void rangeActionPerformed(ActionEvent e) {
		String sel = (String) range.getSelectedItem();
		if (sel != null) {
			String[] arr = sel.split(" ");
			historyInHours = Integer.parseInt(arr[0]);
			updateDomainAxis(getDate());
		}
	}

	private void backActionPerformed(ActionEvent e) {
		deltaMinutes -= (historyInHours * 60) / 2;
		updateDomainAxis(getDate());
	}

	private void currentActionPerformed(ActionEvent e) {
		deltaMinutes = 0;
		updateDomainAxis(getDate());
	}

	private void forwardActionPerformed(ActionEvent e) {
		deltaMinutes -= (historyInHours * 60) / 2;
		updateDomainAxis(getDate());
	}

	private void signalSelectionActionPerformed(ActionEvent e) {
		Object item = signalSelection.getSelectedItem();

		if ("Auto".equals(item)) {
			// auto
		} else {
			currentSignal.setText(item.toString());
			RpMetric desc = (RpMetric) item;
			String loc = desc.getLocation();
			detector.setSignalLoc(loc);
			currentSignal.setText(loc);

			rri_annotation.setText("Manual signal change: " + loc);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		label1 = new JLabel();
		currentSignal = new JLabel();
		live = new JCheckBox();
		label3 = new JLabel();
		signalSelection = new JComboBox();
		topPanel = new JPanel();
		panel3 = new JPanel();
		rightPanel = new JPanel();
		leftPanel = new JPanel();
		panel2 = new JPanel();
		label11 = new JLabel();
		sampen_d = new JLabel();
		label13 = new JLabel();
		qse_d = new JLabel();
		label12 = new JLabel();
		mse_d = new JLabel();
		label5 = new JLabel();
		hf = new JLabel();
		label6 = new JLabel();
		lf = new JLabel();
		label7 = new JLabel();
		hf_lf = new JLabel();
		label8 = new JLabel();
		lf_hf = new JLabel();
		label4 = new JLabel();
		range = new JComboBox<>();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(
				new FormLayout("default:grow", "fill:default, $rgap, 100dlu, $lgap, fill:default:grow, fill:default"));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
					"default, $lcgap, [50dlu,default], $lcgap, default:grow, 2*($lcgap, default), $lcgap, [70dlu,default]",
					"default"));

			// ---- label1 ----
			label1.setText("Current Signal:");
			panel1.add(label1, cc.xy(1, 1));

			// ---- currentSignal ----
			currentSignal.setText("text");
			panel1.add(currentSignal, cc.xy(3, 1));

			// ---- live ----
			live.setText("Historic");
			live.setEnabled(false);
			panel1.add(live, cc.xy(7, 1));

			// ---- label3 ----
			label3.setText("Signal Selection:");
			panel1.add(label3, cc.xy(9, 1));

			// ---- signalSelection ----
			signalSelection.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					signalSelectionActionPerformed(e);
				}
			});
			panel1.add(signalSelection, cc.xy(11, 1));
		}
		add(panel1, cc.xy(1, 1));

		// ======== topPanel ========
		{
			topPanel.setLayout(new BorderLayout());
		}
		add(topPanel, cc.xy(1, 3));

		// ======== panel3 ========
		{
			panel3.setLayout(new FormLayout("default:grow, $lcgap, default:grow", "fill:default:grow"));

			// ======== rightPanel ========
			{
				rightPanel.setLayout(new BorderLayout());
			}
			panel3.add(rightPanel, cc.xy(1, 1));

			// ======== leftPanel ========
			{
				leftPanel.setLayout(new BorderLayout());
			}
			panel3.add(leftPanel, cc.xy(3, 1));
		}
		add(panel3, cc.xy(1, 5));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
					"default, $lcgap, 40dlu, $lcgap, default, $lcgap, [30dlu,default], $lcgap, default, $lcgap, 40dlu, $lcgap, default, $lcgap, 40dlu, $lcgap, default, $lcgap, 40dlu, $lcgap, default, $lcgap, 40dlu, $lcgap, default, $lcgap, [50dlu,default]:grow, 2*($lcgap, default)",
					"default"));

			// ---- label11 ----
			label11.setText("SampEn:");
			label11.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(label11, cc.xy(1, 1));

			// ---- sampen_d ----
			sampen_d.setText("text");
			sampen_d.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(sampen_d, cc.xy(3, 1));

			// ---- label13 ----
			label13.setText("QSE:");
			label13.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(label13, cc.xy(5, 1));

			// ---- qse_d ----
			qse_d.setText("text");
			qse_d.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(qse_d, cc.xy(7, 1));

			// ---- label12 ----
			label12.setText("MSE:");
			label12.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(label12, cc.xy(9, 1));

			// ---- mse_d ----
			mse_d.setText("text");
			mse_d.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(mse_d, cc.xy(11, 1));

			// ---- label5 ----
			label5.setText("HF:");
			label5.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(label5, cc.xy(13, 1));

			// ---- hf ----
			hf.setText("text");
			hf.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(hf, cc.xy(15, 1));

			// ---- label6 ----
			label6.setText("LF:");
			label6.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(label6, cc.xy(17, 1));

			// ---- lf ----
			lf.setText("text");
			lf.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(lf, cc.xy(19, 1));

			// ---- label7 ----
			label7.setText("HF_LF:");
			label7.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(label7, cc.xy(21, 1));

			// ---- hf_lf ----
			hf_lf.setText("text");
			hf_lf.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(hf_lf, cc.xy(23, 1));

			// ---- label8 ----
			label8.setText("LF_HF:");
			label8.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(label8, cc.xy(25, 1));

			// ---- lf_hf ----
			lf_hf.setText("text");
			lf_hf.setFont(new Font("Tahoma", Font.PLAIN, 18));
			panel2.add(lf_hf, cc.xy(27, 1));

			// ---- label4 ----
			label4.setText("Range:");
			panel2.add(label4, cc.xy(29, 1));

			// ---- range ----
			range.setModel(new DefaultComboBoxModel<>(new String[] { "1 hr", "2 hr", "4 hr", "8 hr", "24 hr" }));
			range.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					rangeActionPerformed(e);
				}
			});
			panel2.add(range, cc.xy(31, 1));
		}
		add(panel2, cc.xy(1, 6));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JLabel label1;
	private JLabel currentSignal;
	private JCheckBox live;
	private JLabel label3;
	private JComboBox signalSelection;
	private JPanel topPanel;
	private JPanel panel3;
	private JPanel rightPanel;
	private JPanel leftPanel;
	private JPanel panel2;
	private JLabel label11;
	private JLabel sampen_d;
	private JLabel label13;
	private JLabel qse_d;
	private JLabel label12;
	private JLabel mse_d;
	private JLabel label5;
	private JLabel hf;
	private JLabel label6;
	private JLabel lf;
	private JLabel label7;
	private JLabel hf_lf;
	private JLabel label8;
	private JLabel lf_hf;
	private JLabel label4;
	private JComboBox<String> range;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
