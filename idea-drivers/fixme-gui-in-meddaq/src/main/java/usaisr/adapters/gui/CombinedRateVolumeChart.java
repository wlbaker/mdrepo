package idea.adapters.gui;

/* ===========================================================
 * JFreeChart : a free chart library for the Java(tm) platform
 * ===========================================================
 *
 * (C) Copyright 2000-2009, by Object Refinery Limited and Contributors.
 *
 * Project Info:  http://www.jfree.org/jfreechart/index.html
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * [Java is a trademark or registered trademark of Sun Microsystems, Inc.
 * in the United States and other countries.]
 *
 * ------------------------
 * CombinedXYPlotDemo1.java
 * ------------------------
 * (C) Copyright 2008, 2009, by Object Refinery Limited and Contributors.
 *
 * Original Author:  David Gilbert (for Object Refinery Limited);
 * Contributor(s):   ;
 *
 * Changes
 * -------
 * 05-May-2008 : Version 1 (DG);
 *
 */

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Paint;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.labels.StandardXYToolTipGenerator;
import org.jfree.chart.plot.CombinedDomainXYPlot;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYBarRenderer;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.chart.title.LegendTitle;
import org.jfree.data.time.RegularTimePeriod;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.data.time.TimeSeriesDataItem;
import org.jfree.data.xy.IntervalXYDataset;
import org.jfree.data.xy.XYDataset;

import lombok.extern.slf4j.Slf4j;
import idea.IdeaTimeManager;

/**
 * A demonstration application showing a {@link CombinedXYPlot} with two
 * subplots.
 */
@Slf4j
@SuppressWarnings("serial")
public class CombinedRateVolumeChart {
	private static final Color CHART_BACKGROUND_COLOR = Color.BLACK;

	private int domainInMinutes = 4 * 60;

	protected JFreeChart chart;
	protected TimeSeries[] volSeries = new TimeSeries[2];
	protected TimeSeries[] rateSeries = new TimeSeries[2];

	private DateAxis domainAxis = new DateAxis("");
	private XYPlot volumePlot, ratePlot;

	private XYItemRenderer lineRenderer;

	private XYBarRenderer barRenderer;
	public boolean debug = false;

	private int dump_in_count;

	public CombinedRateVolumeChart() {
		chart = createCombinedChart();

		XYPlot plot = (XYPlot) chart.getPlot();

	}

	public XYPlot getVolumePlot() {
		return volumePlot;
	}

	public XYPlot getRatePlot() {
		return ratePlot;
	}

	public JFreeChart getChart() {
		return chart;
	}

	public void setDomainInMinutes(int mins) {
		this.domainInMinutes = mins;
	}

	public int getDomainInMinutes() {
		return domainInMinutes;
	}

	private void setRangeEndTime(Date date) {
		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		cal.add(Calendar.MINUTE, -domainInMinutes - 30);
		Date lower = cal.getTime();
		cal.add(Calendar.MINUTE, domainInMinutes + 60);
		Date upper = cal.getTime();
		domainAxis.setRange(lower, upper);

	}

	/**
	 * Creates an overlaid chart.
	 * 
	 * @return The chart.
	 */
	private JFreeChart createCombinedChart() {

		// create plot ...
		IntervalXYDataset data1 = createDataset1();
		IntervalXYDataset data2 = createDataset2();

		lineRenderer = createLineRenderer();
		barRenderer = createBarRenderer();

		domainAxis = new DateAxis("");
		domainAxis.setLowerMargin(0.0);
		domainAxis.setUpperMargin(0.02);
		update(); // causes an update of the axis range

		ValueAxis volAxis = new NumberAxis("Volume");
		volumePlot = new XYPlot(data1, null, volAxis, barRenderer);
		// plot1.setBackgroundPaint(Color.lightGray);
		volumePlot.setDomainGridlinePaint(Color.lightGray);
		volumePlot.setRangeGridlinePaint(Color.lightGray);
		volumePlot.getRangeAxis().setUpperBound(20.0);
		volumePlot.getRangeAxis().setLowerBound(0);
		volumePlot.getRangeAxis().setAutoRange(true);

		// add a second dataset and renderer...

		ValueAxis rateAxis = new NumberAxis("Rate");
		ratePlot = new XYPlot(data2, null, rateAxis, lineRenderer);
		// plot2.setBackgroundPaint(Color.lightGray);
		ratePlot.setDomainGridlinePaint(Color.lightGray);
		ratePlot.setRangeGridlinePaint(Color.lightGray);
		ratePlot.getRangeAxis().setUpperBound(10.0);
		ratePlot.getRangeAxis().setLowerBound(0);
		ratePlot.getRangeAxis().setAutoRange(true);

		CombinedDomainXYPlot cplot = new CombinedDomainXYPlot(domainAxis);
		cplot.add(volumePlot, 3);
		cplot.add(ratePlot, 2);
		cplot.setGap(8.0);
		cplot.setDomainGridlinePaint(Color.white);
		cplot.setDomainGridlinesVisible(true);
		//		cplot.setDomainPannable(true);
		//		cplot.setRangePannable( true );

		volumePlot.setRangeAxis(volAxis);
		ratePlot.setRangeAxis(rateAxis);
		volumePlot.setBackgroundPaint(CHART_BACKGROUND_COLOR);
		ratePlot.setBackgroundPaint(CHART_BACKGROUND_COLOR);

		// return a new chart containing the overlaid plot...
		JFreeChart chart = new JFreeChart(null, JFreeChart.DEFAULT_TITLE_FONT, cplot, false);
		chart.setBackgroundPaint(Color.white);
		LegendTitle legend = new LegendTitle(cplot);
		chart.addSubtitle(legend);

		return chart;
	}

	private XYItemRenderer createLineRenderer() {

		// BETA2: V @ hr: ( , val )...should say ml or whatever the UOM is

		XYItemRenderer renderer1 = new XYLineAndShapeRenderer(true, false);
		renderer1.setBaseToolTipGenerator(new StandardXYToolTipGenerator(
				StandardXYToolTipGenerator.DEFAULT_TOOL_TIP_FORMAT, new SimpleDateFormat("d-MMM-yyyy HH:mm"),
				new DecimalFormat("0.00")));
		renderer1.setSeriesStroke(0, new BasicStroke(4.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
		renderer1.setSeriesPaint(0, Color.blue);

		return renderer1;
	}

	private XYBarRenderer createBarRenderer() {
		XYBarRenderer renderer = new XYBarRenderer() {
			public Paint getItemPaint(int series, int item) {
				XYDataset dataset = getPlot().getDataset();

				if (series == 0) {
					return Color.red;
				} else if (series == 1) {
					return Color.blue;
				}

				if (dataset.getYValue(series, item) >= 0.0) {
					return Color.red;
				} else {
					return Color.green;
				}
			}
		};
		renderer.setSeriesPaint(0, Color.blue);
		renderer.setSeriesPaint(1, Color.red);
		renderer.setDrawBarOutline(true);

		renderer.setShadowVisible(false);
		renderer.setBaseToolTipGenerator(new StandardXYToolTipGenerator(
				StandardXYToolTipGenerator.DEFAULT_TOOL_TIP_FORMAT, new SimpleDateFormat("d-MMM-yyyy HH:mm"),
				new DecimalFormat("0.00")));

		return renderer;
	}

	/**
	 * Creates a sample dataset. You wouldn't normally hard-code the population
	 * of a dataset in this way (it would be better to read the values from a
	 * file or a database query), but for a self-contained demo this is the
	 * least complicated solution.
	 * 
	 * @return The dataset.
	 */
	private IntervalXYDataset createDataset1() {

		class Vtp extends TimeSeries {
			String t;

			public Vtp(String t) {
				super(t);
				this.t = t;
			}

			public RegularTimePeriod getTimePeriod(int index) {
				RegularTimePeriod p = super.getTimePeriod(index); // getRawDataItem(index).getPeriod();
				//System.out.println(t + " p=" + p);
				return p;
			}
		}
		// create dataset 1...
		Calendar cal = Calendar.getInstance();
		cal.add(Calendar.HOUR, -1);
		volSeries[0] = new Vtp("Vol");
		volSeries[1] = new Vtp("V @ hr");

		TimeSeriesCollection dataset = new TimeSeriesCollection();
		dataset.addSeries(volSeries[0]);
		dataset.addSeries(volSeries[1]);

		return dataset;

	}

	/**
	 * Creates a sample dataset. You wouldn't normally hard-code the population
	 * of a dataset in this way (it would be better to read the values from a
	 * file or a database query), but for a self-contained demo this is the
	 * least complicated solution.
	 * 
	 * @return A sample dataset.
	 */
	private IntervalXYDataset createDataset2() {

		Calendar cal = Calendar.getInstance();
		cal.add(Calendar.HOUR, -1);
		rateSeries[0] = new TimeSeries("Rate Series 1");
		rateSeries[1] = new TimeSeries("Rate Series 2");

		TimeSeriesCollection dataset = new TimeSeriesCollection();
		dataset.addSeries(rateSeries[0]);
		dataset.addSeries(rateSeries[1]);
		return dataset;

	}

	public void add5MinData(int series, Date ts, Number rate, Number vol) {
		if (vol != null)
			volSeries[series].addOrUpdate(new NMinute(ts, 5), vol);
		if (rate != null)
			rateSeries[1].addOrUpdate(new NMinute(ts, 5), rate);
	}

	public void add10MinData(int series, Date ts, Number rate, Number vol) {
		if (vol != null)
			volSeries[series].addOrUpdate(new NMinute(ts, 10), vol);
		if (rate != null)
			rateSeries[1].addOrUpdate(new NMinute(ts, 10), rate);
	}

	public void clear() {
		// let the old series die in garbage collection
		volumePlot.setDataset(createDataset1());
		ratePlot.setDataset(createDataset2());

		dump_in_count = 3;
	}

	/**
	 * called by a timer started in this class
	 * 
	 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
	 * 
	 */
	public void update() {
		Date currTime = IdeaTimeManager.getCurrentTime();
		setRangeEndTime(currTime);

		if (debug) {
			if (dump_in_count > 0) {
				log.debug("chart: {} dump in: {}", hashCode(), dump_in_count);
				dump_in_count--;
				if (dump_in_count == 0) {
					dump();
				}
			}
		}
	}

	private void dump() {
		log.debug("chart: {} dumping volume series: {}", hashCode(), volSeries);

		for (int i = 0; i < volSeries.length; i++) {
			TimeSeries s = volSeries[i];
			log.debug("  series: {} hash: {}", i, s.hashCode());
			if (s != null) {
				List items = s.getItems();
				if (items != null) {
					int count = 0;
					for (Object item : items) {
						count++;
						TimeSeriesDataItem it = (TimeSeriesDataItem) item;
						log.debug("   item: {} at {}", it.getValue(), it.getPeriod());

						if (count > 10)
							break;
					}
				}
			}
		}

	}

}
