/*
 * Created by JFormDesigner on Tue Dec 10 10:54:29 CST 2013
 */

package idea.analysis;

import idea.conf.DeviceConfiguration;
import idea.display.RefreshablePanel;
import idea.intf.IDEAClient;
import idea.intf.IDEATransferInterface;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.StringStringMap;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.io.IOException;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.JPanel;

import lombok.extern.slf4j.Slf4j;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.labels.StandardXYToolTipGenerator;
import org.jfree.chart.plot.CombinedDomainXYPlot;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.chart.title.LegendTitle;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;

import idea.adapters.gui.NMinute;
import idea.analysis.event.EntropyBlock;
import idea.meddaq.AppModel;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class TrendVisualizationPanel extends JPanel implements AnalysisPanelInterface, StreamConsumer, RefreshablePanel {
	private static final RpAnalysis analysisInfo;
	static { 
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("Trend Visualization");
		analysisInfo.setAnalysisClass( TrendVisualizationPanel.class.getCanonicalName() );
		// analysisInfo.
	}
	private static final int HISTORY_IN_HOURS = 2;
	private static final int TREND_HISTORY_JOBID = 300;
	private static final int MINS_PER_DATAPOINT = 1;
	private static final long MINIMUM_REFRESH_MS = 10000;

	private DateAxis domainAxis;
	private CombinedDomainXYPlot cplot;
	// private XYItemRenderer lineRenderer;
	private Map<String, TimeSeries> series = new HashMap<String, TimeSeries>();
	private Map<String, Long> updateTimes = new HashMap<String, Long>();
	private int tick;
	private XYPlot lastPlot;

	public TrendVisualizationPanel(StreamProducer[] producers, RpAnalysis anal) {
		initComponents();

		domainAxis = new DateAxis("");
		domainAxis.setLowerMargin(0.0);
		domainAxis.setUpperMargin(0.02);

		cplot = new CombinedDomainXYPlot(domainAxis);
		cplot.setGap(8.0);
		cplot.setDomainGridlinePaint(Color.white);
		cplot.setDomainGridlinesVisible(true);

		StreamProducer drager = AppModel.getSignalProducer("Drager");
		addTrends(null, drager, "ecg.hr", Color.GREEN);
		addTrends(null, drager, "art.sys", Color.RED);
		addTrends(null, drager, "gp1.sys", Color.BLUE);
		addTrends(null, drager, "gp2.sys", Color.BLACK);
		if (drager != null) {
			drager.addStreamListener(StreamID.MEASUREMENT, this);
		}

		TimeSeriesCollection ds = new TimeSeriesCollection();

		StreamProducer aesculon = AppModel.getSignalProducer("Aesculon");
		if (aesculon != null) {
			addTrends(ds, aesculon, "5010", Color.CYAN); // HRC
			aesculon.addStreamListener(StreamID.MEASUREMENT, this);
		}

		StreamProducer entropy = AppModel.getSignalProducer("Entropy");
		if (entropy != null) {
			addTrends(ds, entropy, EntropyBlock.SAMPENT_LOC, Color.MAGENTA);
			entropy.addStreamListener(StreamID.MEASUREMENT, this);
		}

		/*
		 * loop here?
		 */

		// addTrends();
		JFreeChart chart = new JFreeChart(null, JFreeChart.DEFAULT_TITLE_FONT, cplot, false);
		chart.setBackgroundPaint(Color.white);
		LegendTitle legend = new LegendTitle(cplot);
		chart.addSubtitle(legend);

		ChartPanel p0 = new ChartPanel(chart);
		p0.setPreferredSize(new Dimension(100, 200));

		this.add(p0, BorderLayout.CENTER);

		/*
		 * end loop
		 */

		wireProducersAndConsumers(producers, anal);
		updateDomainAxis(new Date());

	}

	private XYItemRenderer createLineRenderer( Color color ) {

		// BETA2: V @ hr: ( , val )...should say ml or whatever the UOM is

		XYItemRenderer renderer1 = new XYLineAndShapeRenderer(true, false);
		renderer1.setBaseToolTipGenerator(new StandardXYToolTipGenerator(
				StandardXYToolTipGenerator.DEFAULT_TOOL_TIP_FORMAT, new SimpleDateFormat("d-MMM-yyyy HH:mm"),
				new DecimalFormat("0.00")));
		renderer1.setSeriesStroke(0, new BasicStroke(4.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_BEVEL));
		renderer1.setSeriesPaint(0, color );

		return renderer1;
	}

	private void addTrends(TimeSeriesCollection ds, StreamProducer producer, String sig, Color color) {
		if (producer == null) {
			log.error("could not add trends: producer not found for sigs: {}", sig);
			return;
		}

		if (ds == null) {
			ds = new TimeSeriesCollection();
		}

		/*
		 * loop for more than one variable/plot
		 */
		TimeSeries s = new TimeSeries(sig);
		s.setDescription(sig);
		series.put(sig, s);  // keep a lookup table of the series created

		ds.addSeries(s);

		if (ds.getSeriesCount() == 1) {
			// might not be intuitive that you need a distinct renderer for each plot,
			// but the renderer has a link back to the plot which is used for some
			// small bits of information, like the series name used in the legend
			// ...and it also knows the series colors
			XYItemRenderer lineRenderer = createLineRenderer(Color.BLUE);

			ValueAxis yAxis = new NumberAxis(sig);
			XYPlot plot = new XYPlot(ds, null, yAxis, lineRenderer);
			// plot1.setBackgroundPaint(Color.lightGray);
			plot.setDomainGridlinePaint(Color.lightGray);
			plot.setRangeGridlinePaint(Color.lightGray);
			plot.getRangeAxis().setUpperBound(20.0);
			plot.getRangeAxis().setLowerBound(0);
			plot.getRangeAxis().setAutoRange(true);
			cplot.add(plot, 3);

			lastPlot = plot;
		}

		XYItemRenderer r = lastPlot.getRenderer();
		r.setSeriesPaint(ds.getSeriesCount() - 1, color );

		return;
	}

	private void updateDomainAxis(Date date) {
		int domainInMinutes = HISTORY_IN_HOURS * 60;

		Calendar cal = Calendar.getInstance();
		cal.setTime(date);
		cal.add(Calendar.MINUTE, -domainInMinutes - 30);
		Date lower = cal.getTime();
		cal.add(Calendar.MINUTE, domainInMinutes + 60);
		Date upper = cal.getTime();
		domainAxis.setRange(lower, upper);

		return;
	}

	private void wireProducersAndConsumers(StreamProducer[] producers, RpAnalysis anal) {

		log.error("this routine doesnt do anything. is it supposed to???");
		
		StringStringMap params = anal.getParam();

		if (producers == null || producers.length == 0) {
			log.error("NO SIGNAL PRODUCERS");
			// assert( false ) : "No signal producers for analysis.";
			return;
		}

		if( params == null ) {
			log.error("Expected required parameter \"detector\".");
			return;
		}
		String detector_param = params.get( "detector");
		if (detector_param == null) {
			assert (detector_param != null) : "CONFIG ERROR: detector not available";
			log.error("NO DETECTOR --> NO ANALYSIS");
			return;
		}

	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.MEASUREMENT) {

			long tm = item.getTime();
			Date dt = new Date(tm);
			for (Entry<String, TimeSeries> entry : series.entrySet()) {
				String loc = entry.getKey();
				Long lastTime = updateTimes.get(loc);
				if (lastTime != null) {
					long delta = tm - lastTime;
					if (delta < MINIMUM_REFRESH_MS) {
						continue;
					}
				}
				Number val = IntfUtil.getScaledValueByLoc(item, loc);
				if (val != null) {
					TimeSeries s = entry.getValue();
					add1MinData(s, dt, val);
					updateTimes.put(loc, tm);
				}
			}
		}

	}

	@Override
	public void clear() {
		for (TimeSeries s : series.values()) {
			s.setMaximumItemAge(1);
			s.setMaximumItemAge(HISTORY_IN_HOURS * 60 / MINS_PER_DATAPOINT);
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
			updateDomainAxis(new Date());
			tick = 0;
		}
	}

	@Override
	public StreamProducer[] getSignalProducers() {
		// TODO Auto-generated method stub
		return null;
	}

	public void add1MinData(TimeSeries series, Date ts, Number val) {
		if (val != null)
			series.addOrUpdate(new NMinute(ts, MINS_PER_DATAPOINT), val);
	}

	@Override
	public void refresh(IDEAClient idea, Date dt) {
		Calendar cal = Calendar.getInstance();
		if (dt != null) {
			cal.setTime(dt);
		}
		cal.add(Calendar.HOUR, -HISTORY_IN_HOURS);
		Date dtStart = cal.getTime();
		Date dtEnd = dt;

		log.error("FIXME: need conf of variables to retrieve");
		DeviceConfiguration conf = null;
		IDEATransferInterface req = idea.createTransferRequest(TREND_HISTORY_JOBID, dtStart, dtEnd, conf, 10 * 60 * 1000);
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

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY //GEN-BEGIN:initComponents

		//======== this ========
		setLayout(new BorderLayout());
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
