/*
 * Created by JFormDesigner on Thu Jul 21 12:45:32 CDT 2011
 */

package idea.analysis;

import icuInterface.RpUtil;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;

import lombok.extern.slf4j.Slf4j;

import org.jdesktop.beansbinding.AutoBinding.UpdateStrategy;
import org.jdesktop.beansbinding.BeanProperty;
import org.jdesktop.beansbinding.BindingGroup;
import org.jdesktop.beansbinding.Bindings;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.AxisLocation;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.DateTickUnit;
import org.jfree.chart.axis.DateTickUnitType;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.labels.StandardCategoryItemLabelGenerator;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.category.BarRenderer;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.title.TextTitle;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.time.Second;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;

import idea.GuiUtil;
import idea.gui.ExcelAdapter;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class CosmosAnalysisPanel extends JPanel implements AnalysisPanelInterface, StreamConsumer {

	private static final RpAnalysis analysisInfo;
	static { 
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("Ontonix Analysis");
		analysisInfo.setAnalysisClass( CosmosAnalysisPanel.class.getCanonicalName() );
		// analysisInfo.
	}
	
	private static final int COL_TM = 0;
	private static final int N_FIXED = 10;
	private static final int MAX_SECONDS = 3600;
	private static final DateFormat display_df = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
	private static final DateFormat log_df = new SimpleDateFormat("HH:mm:ss");
	private static final DateFormat tstamp_df = new SimpleDateFormat("yyyyMMdd-HHmmss");
	private static CategoryPlot relativePlot;
	private static XYPlot complexityPlot;
	private static XYPlot stabilityPlot;
	private static TextTitle dateTitle;
	private RpAnalysis analysis;
	private int secsValue;
	private int nValues;
	private long startTm = 0;
	int file_exist_count = 0;

	private Map<String, Integer> locMap = new HashMap<String, Integer>();
	private Set<String> reqDevs = new HashSet<String>();
	private String outFileName;
	private String outTempName;
	private String outHeaderName;
	private String[] colNames;
	private String[] devNames;
	private boolean disconnected = false;

	long last_event_tm;

	double shortTermStability;
	double midTermStability;
	double longTermStability;
	double complexity;
	double lower_complexity;
	double upper_complexity;
	double entropy;
	double robustness;

	private TimeSeries shortTermStabilitySeries;
	private TimeSeries mediumTermStabilitySeries;
	private TimeSeries longTermStabilitySeries;
	private TimeSeries complexitySeries;
	private JFreeChart complexityChart;
	private boolean _internal_init;
	private static final int SKIP_NUMBER = 1;
	private int skip = SKIP_NUMBER;
	CosmosProcessor processor;
	private DecimalFormat df2 = new DecimalFormat("0.00");

	public CosmosAnalysisPanel(RpAnalysis analysis) {
		initComponents();

		processor = new CosmosProcessor();
		//
		// not needed here! see how processLog is called
		//
		// processor.addEventListener( NumericsEvent.class, this);
		//
		this.analysis = analysis;
		parseParameters(analysis.getParam());

		DefaultTableModel model = (DefaultTableModel) logTable.getModel();
		model.setRowCount(0);

		new ExcelAdapter(logTable);
		new ExcelAdapter(metricTable);

		CategoryDataset detailDataset = createRelativeComplexityDataset(logTable, -1);
		JFreeChart detailChart = createRelativeComplexityChart(detailDataset);

		TimeSeriesCollection complexityDataset = createComplexityDataset();
		complexityChart = createComplexityChart(complexityDataset);

		TimeSeriesCollection stabilityDataset = createStabilityDataset();
		JFreeChart stabilityChart = createStabilityChart(stabilityDataset);

		shortTermStabilitySeries.setMaximumItemAge(MAX_SECONDS);
		mediumTermStabilitySeries.setMaximumItemAge(MAX_SECONDS);
		longTermStabilitySeries.setMaximumItemAge(MAX_SECONDS);
		complexitySeries.setMaximumItemAge(MAX_SECONDS);

		// ChartPanel p0 = new ChartPanel(detailChart);
		// p0.setPreferredSize(new Dimension(100, 200));
		CellConstraints cc = new CellConstraints();

		ChartPanel cp;
		relativePanel.add(cp = new ChartPanel(detailChart), BorderLayout.CENTER);
		cp.setPreferredSize(new Dimension(130, 200));
		cp.setMouseZoomable(false);
		cp.setRangeZoomable(false);
		stabilityPanel.add(cp = new ChartPanel(complexityChart), cc.xy(1, 1));
		cp.setPreferredSize(new Dimension(130, 100));
		cp.setMouseZoomable(false);
		cp.setRangeZoomable(false);
		stabilityPanel.add(cp = new ChartPanel(stabilityChart), cc.xy(1, 3));
		cp.setPreferredSize(new Dimension(130, 100));
		cp.setMouseZoomable(false);
		cp.setRangeZoomable(false);

		// http://blogs.oracle.com/thejavatutorials/entry/watching_a_directory_for_changes
		// import static java.nio.file.StandardWatchEventKind.\*;

		// WatchService watcher = FileSystems.getDefault().newWatchService();
		// Path dir = ...;
		// try {
		// WatchKey key = dir.register(watcher, ENTRY_CREATE, ENTRY_DELETE,
		// ENTRY_MODIFY);
		// } catch (IOException x) {
		// System.err.println(x);
		// }
		//

		logTable.getSelectionModel().addListSelectionListener(new ListSelectionListener() {

			@Override
			public void valueChanged(ListSelectionEvent e) {
				if (e.getValueIsAdjusting()) {
					return; // ignore
				}

				int row = logTable.getSelectedRow();
				CategoryDataset dataset = createRelativeComplexityDataset(logTable, row);
				relativePlot.setDataset(dataset);
			}
		});

		cmplx_field.setText(" ? ");
		stability_field.setText(" ? ");
	}

	/**
	 * Creates a chart.
	 * 
	 * @param dataset
	 *            the dataset.
	 * 
	 * @return A chart.
	 */
	private static JFreeChart createComplexityChart(final TimeSeriesCollection dataset) {
		JFreeChart chart = ChartFactory.createTimeSeriesChart(null, null, "Complexity", dataset, true, true, false);
		complexityPlot = chart.getXYPlot();

		XYItemRenderer renderer = complexityPlot.getRenderer();
		renderer.setSeriesStroke(0, new BasicStroke(4.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND, 1.0f, null,
				0.0f));

		DateAxis axis = (DateAxis) complexityPlot.getDomainAxis();
		// HorizontalDateAxis axis = (HorizontalDateAxis) plot.getDomainAxis();
		// axis.setTickUnit(new DateTickUnit(DateTickUnit.MONTH, 1,
		// new SimpleDateFormat("MMM-yyyy")));
		// axis.setVerticalTickLabels(true);

		axis.setAutoRange(false);
		axis.setTickUnit(new DateTickUnit(DateTickUnitType.MINUTE, 10, new SimpleDateFormat("HH:mm")));
		axis.setVerticalTickLabels(true);

		ValueAxis range_axis = complexityPlot.getRangeAxis();
		range_axis.setAutoRange(false);
		range_axis.setRange(0, 100);

		chart.removeLegend();
		// chart.setBackgroundPaint( Color.BLACK );
		complexityPlot.setBackgroundPaint(Color.BLACK);
		return chart;
	}

	/**
	 * Creates a chart.
	 * 
	 * @param dataset
	 *            the dataset.
	 * 
	 * @return A chart.
	 */
	private static JFreeChart createStabilityChart(final TimeSeriesCollection dataset) {
		JFreeChart chart = ChartFactory.createTimeSeriesChart(null, null, "Stability", dataset, true, true, false);
		stabilityPlot = chart.getXYPlot();

		XYItemRenderer renderer = stabilityPlot.getRenderer(0);
		for (int idx = 0; idx < 3; idx++) {
			// there should be three renderers in this dataset
			if (renderer != null) {
				renderer.setSeriesStroke(idx, new BasicStroke(4.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
						1.0f, null, 0.0f));
			}
		}

		DateAxis axis = (DateAxis) stabilityPlot.getDomainAxis();
		// HorizontalDateAxis axis = (HorizontalDateAxis) plot.getDomainAxis();
		// axis.setTickUnit(new DateTickUnit(DateTickUnit.MONTH, 1,
		// new SimpleDateFormat("MMM-yyyy")));
		// axis.setVerticalTickLabels(true);

		axis.setAutoRange(false);
		axis.setTickUnit(new DateTickUnit(DateTickUnitType.MINUTE, 10, new SimpleDateFormat("HH:mm")));
		axis.setVerticalTickLabels(true);

		// I can't tell what this does!
		// XYLineAndShapeRenderer renderer = (XYLineAndShapeRenderer)
		// stabilityPlot.getRenderer();
		// // renderer.setPlotShapes(true);
		// renderer.setSeriesShapesFilled(0, Boolean.TRUE);
		// renderer.setSeriesShapesFilled(1, Boolean.FALSE);
		//
		ValueAxis range_axis = stabilityPlot.getRangeAxis();
		range_axis.setAutoRange(false);
		range_axis.setRange(0, 100);

		// chart.setBackgroundPaint( Color.BLACK );
		stabilityPlot.setBackgroundPaint(Color.BLACK);

		return chart;
	}

	private static JFreeChart createRelativeComplexityChart(final CategoryDataset dataset) {
		// create the chart...
		JFreeChart chart = ChartFactory.createBarChart(null, // title
				"Relative Complexity", // range axis label
				null, // domain axis label
				dataset, // data
				PlotOrientation.HORIZONTAL, // orientation
				false, // include legend
				true, false);

		chart.addSubtitle(dateTitle = new TextTitle("Source date goes here!", new Font("Dialog", Font.ITALIC, 10)));
		chart.setBackgroundPaint(Color.white);
		relativePlot = (CategoryPlot) chart.getPlot();
		relativePlot.setBackgroundPaint(Color.lightGray);
		relativePlot.setRangeGridlinePaint(Color.white);
		relativePlot.setRangeAxisLocation(AxisLocation.BOTTOM_OR_LEFT);
		BarRenderer renderer = (BarRenderer) relativePlot.getRenderer();
		renderer.setBaseItemLabelsVisible(true);
		renderer.setBaseItemLabelGenerator(new StandardCategoryItemLabelGenerator());
		CategoryAxis categoryAxis = relativePlot.getDomainAxis();
		categoryAxis.setCategoryMargin(0.0);
		categoryAxis.setUpperMargin(0.02);
		categoryAxis.setLowerMargin(0.02);
		NumberAxis rangeAxis = (NumberAxis) relativePlot.getRangeAxis();
		rangeAxis.setStandardTickUnits(NumberAxis.createIntegerTickUnits());
		rangeAxis.setUpperMargin(0.10);
		rangeAxis.setAutoRange(false);

		relativePlot.setBackgroundPaint(Color.BLACK);

		return chart;
	}

	private TimeSeriesCollection createComplexityDataset() {
		complexitySeries = new TimeSeries("Stability");
		// complexitySeries.add(new Month(12, 2002), 345.6);

		TimeSeriesCollection dataset = new TimeSeriesCollection();
		dataset.addSeries(complexitySeries);

		return dataset;
	}

	private TimeSeriesCollection createStabilityDataset() {
		shortTermStabilitySeries = new TimeSeries("Short Term");
		mediumTermStabilitySeries = new TimeSeries("Medium Term");
		longTermStabilitySeries = new TimeSeries("Long Term");
		// complexitySeries.add(new Month(12, 2002), 345.6);

		TimeSeriesCollection dataset = new TimeSeriesCollection();
		dataset.addSeries(shortTermStabilitySeries);
		dataset.addSeries(mediumTermStabilitySeries);
		dataset.addSeries(longTermStabilitySeries);

		return dataset;
	}

	private CategoryDataset createRelativeComplexityDataset(JTable table, int row) {

		DefaultCategoryDataset dataset = new DefaultCategoryDataset();
		// String seriesKey = "Relative Complexity Index";

		if (row < 0) {
			return dataset;
		}

		class Pair {
			String name;
			String dev;
			double val;
			int col;
		}

		List<Pair> list = new LinkedList<Pair>();

		int cols = table.getColumnCount();
		for (int table_col = N_FIXED; table_col < cols; table_col++) {
			Pair pair = new Pair();
			pair.col = table_col - N_FIXED;

			if (pair.col >= colNames.length) {
				log.error("CosmosAnalysis UNEXPECTED TRUNCATION/DATA SET CHANGE");
				break;
			}
			Double val = (Double) table.getValueAt(row, table_col);
			String tableColName = table.getColumnName(table_col);

			if (val != null) {
				pair.val = val;
				pair.name = colNames[pair.col];
				pair.dev = devNames[pair.col]; // NEW NEW NEW
				if (pair.name == null) {
					pair.name = tableColName;
				}

				list.add(pair);
			}
		}

		if (lock.isSelected() == false) {
			Collections.sort(list, new Comparator<Pair>() {

				@Override
				public int compare(Pair o1, Pair o2) {
					if (o1.val > o2.val) {
						return -1;
					} else if (o1.val < o2.val) {
						return 1;
					}
					return 0;
				}
			});

			int count = 0;
			int maxLines = 9999;
			try {
				maxLines = Integer.parseInt((String) displayCount.getSelectedItem());
			} catch (Exception ee) {
				// ignore...perhaps it just says "All"
			}

			for (Pair p : list) {
				if (p.name == null) {
					p.name = "p.name";
				}
				if (p.dev == null) {
					int pos;
					if ((pos = p.name.indexOf('$')) > 1) {
						p.dev = p.name.substring(0, pos - 1);
						p.name = p.name.substring(pos + 1);
					} else {
						p.dev = "p.dev";
					}
				}
				dataset.addValue(p.val, p.dev, p.name);
				count++;
				if (count > maxLines) {
					break;
				}
			}
		}

		setRelativeComplexityValueRange(0, list.get(0).val);

		return dataset;
	}

	protected void processLogFile(File f) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader(f));

		try {
			_processLogFile(f, in);
		} finally {
			in.close();
			f.delete();
		}

	}

	private String[] readLines(BufferedReader in) throws IOException {
		List<String> arr = new LinkedList<String>();
		String line;
		while ((line = in.readLine()) != null) {
			arr.add(line);
		}
		String[] ar = new String[arr.size()];
		return arr.toArray(ar);
	}

	protected void _processLogFile(File f, BufferedReader in) throws IOException {
		DefaultTableModel model = (DefaultTableModel) logTable.getModel();

		String[] arr = readLines(in);

		if (arr.length < 10) {
			log.error("DATA ERROR IN COSMOS LOG file={} count={}", f, arr.length);
			//if( log.isDebugEnabled()) {
			for (String s : arr) {
				System.err.println("   * " + s);
			}
			//}
			return;
		}
		if( arr.length > 100 ) {
			log.error("too many columns...ignoring!");
			return;
		}
		Object[] row = new Object[arr.length];
		int idx = 0;
		//String tm = arr[idx++];
		String tm = "";
		shortTermStability = safe_parseDouble(arr[idx++]);
		midTermStability = safe_parseDouble(arr[idx++]);
		longTermStability = safe_parseDouble(arr[idx++]);
		complexity = safe_parseDouble(arr[idx++]);
		lower_complexity = safe_parseDouble(arr[idx++]);
		upper_complexity = safe_parseDouble(arr[idx++]);
		entropy = safe_parseDouble(arr[idx++]);
		robustness = safe_parseDouble(arr[idx++]);
		row[0] = tm;
		row[1] = shortTermStability;
		row[2] = midTermStability;
		row[3] = longTermStability;
		row[4] = complexity;
		row[5] = lower_complexity;
		row[6] = upper_complexity;
		row[7] = entropy;
		row[8] = robustness;

		Date dt = new Date();
		try {
			System.out.println("dat not in this file");
			//dt = safe_parseDate(tm);

			Calendar cal = Calendar.getInstance();
			cal.set(Calendar.HOUR_OF_DAY, dt.getHours());
			cal.set(Calendar.MINUTE, dt.getMinutes());
			cal.set(Calendar.SECOND, dt.getSeconds());

			dt = cal.getTime();
		} catch (Exception e) {
			log.error("INVALID COSMOS DATE: " + tm, e);
		}
		log.info("COSMOS got dt: " + display_df.format(dt));
		dt = new Date(last_event_tm);
		log.info("Overriding date: " + display_df.format(dt));

		shortTermStabilitySeries.addOrUpdate(new Second(dt), shortTermStability);
		mediumTermStabilitySeries.addOrUpdate(new Second(dt), midTermStability);
		longTermStabilitySeries.addOrUpdate(new Second(dt), longTermStability);
		complexitySeries.addOrUpdate(new Second(dt), complexity);

		if (_internal_init == false) {

			XYItemRenderer renderer = stabilityPlot.getRenderer(0);
			for (int iidx = 0; iidx < 3; iidx++) {
				// there should be three renderers in this dataset
				if (renderer != null) {
					renderer.setSeriesStroke(iidx, new BasicStroke(4.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
							1.0f, null, 0.0f));
				}
			}
			_internal_init = true;
		}
		setDomainRanges(dt);
		// set chart date title
		dateTitle.setText(display_df.format(dt));

		// shortTermStabilitySeries.removeAgedItems( false );
		// complexitySeries.removeAgedItems( false );

		System.out.println("items in series: " + shortTermStabilitySeries.getItemCount());

		System.out.print("[" + shortTermStability + "-->" + longTermStability + "]");
		System.out.println(" cplx=" + complexity + "  entr=" + entropy + " robust=" + robustness);

		cmplx_field.setText(df2.format(complexity));
		stability_field.setText(df2.format(robustness));

		boolean init = model.getRowCount() == 0;

		while (idx < arr.length - 1) { // the last index is "Correct Data"
			try {
				row[idx] = Double.valueOf(arr[idx]);
			} catch (Exception e) {
				// data format...not a double
				row[idx] = null;
			}
			idx++;

			if (init) {
				model.addColumn("CM" + (idx - N_FIXED));
			}
		}
		model.addRow(row);

		in.close();
	}

	private Date safe_parseDate(String tm) {
		Date dt = null;
		if (tm != null && tm.length() > 0) {
			dt = new Date(Long.parseLong(tm));
		}
		return dt;
	}

	private double safe_parseDouble(String val) {
		double d = -1;
		if (val != null && val.length() > 0) {
			d = Double.parseDouble(val);
		}
		return d;
	}

	private void setRelativeComplexityValueRange(double lower, double upper) {

		NumberAxis rangeAxis = (NumberAxis) relativePlot.getRangeAxis();
		rangeAxis.setStandardTickUnits(NumberAxis.createIntegerTickUnits());
		rangeAxis.setUpperMargin(0.10);
		rangeAxis.setAutoRange(false);

		upper *= 1.05; // scale at least 5% above upper

		if (upper < 20) {
			upper = 20;
		}

		rangeAxis.setRange(lower, upper);

	}

	private void setDomainRanges(Date dt) {
		Calendar cal = Calendar.getInstance();
		cal.setTime(dt);
		cal.add(Calendar.SECOND, -MAX_SECONDS);
		Date lower = cal.getTime();

		DateAxis axis = (DateAxis) complexityPlot.getDomainAxis();
		axis.setRange(lower, dt);
		axis = (DateAxis) stabilityPlot.getDomainAxis();
		axis.setRange(lower, dt);

	}

	public void wire(StreamProducer[] drivers) {
		for (StreamProducer intf : drivers) {
			RpDevice conf = intf.getConfiguration();

			// this is a real HACK since EVITA can be EVITA_4 or EVITA<sp>4
			String dname = conf.getName();
			// if (reqDevs.contains(dname)) {

			int slen = Math.min(4, dname.length());

			dname = dname.substring(0, slen);
			for (String reqName : reqDevs) {
				reqName = reqName.substring(0, slen);
				if (reqName.equals(dname)) {
					addColNames(intf);
					log.info("cosmos analysis panel/wire: adding listener: {}", intf);
					intf.addStreamListener(StreamID.MEASUREMENT, this);
					break; // break inner loop
				}
			}
		}

	}

	private void addColNames(StreamProducer intf) {
		for (RpMetric metric : RpUtil.getMetrics( intf.getConfiguration(), StreamID.MEASUREMENT) ) {
			Object key = metric.getLocation();
			Integer pos = locMap.get(key);
			if (pos != null) {
				colNames[pos] = metric.getCode();
				devNames[pos] = intf.getConfiguration().getName();
			}
		}
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem block) {

		if (disconnected) {
			log.error("S-DISCONNECT!");
			return;
		}

		last_event_tm = block.getTime();

		if (startTm == 0) {
			startTm = last_event_tm;
		}

		int row;

		DefaultTableModel model = (DefaultTableModel) metricTable.getModel();
		do {
			int sec = (int) ((last_event_tm - startTm) / 1000);
			row = sec / secsValue;

			if (row > nValues) {
				try {
					if (skip <= 0) {
						String h = dumpHeader(model);
						dumpData(model);
						skip = SKIP_NUMBER;
						processor.process(outFileName, h);
					} else {
						skip--;
					}
					startTm += 1 * secsValue * 1000; // skip 1 datapoints
					// startTm += (1*secsValue*1000)/2; // add half a datapoint
					// row -= cleanData(model, startTm);
					model.removeRow(0); // just remove one line
					row = row - 1;

				} catch (Exception e) {
					// could be file not found, could be file in use
					e.printStackTrace();
				}
				if (row > 2 * nValues) {
					// start over!
					startTm = last_event_tm;
					model.setRowCount(0);
				}
			}

		} while (row > nValues);

		index.setText("" + row);
		try {
			addData(model, last_event_tm, row, block);
		} catch (Exception e) {
			log.error("error adding to data model", e);
		}
	}

	private void addData(DefaultTableModel model, long tm, int row, PersistentItem block) {
		RpMetric[] items = block.getMetrics();

		while (row >= model.getRowCount()) {
			// we might end up skipping a row
			Object[] rowData = new Object[model.getColumnCount()];
			// rowData[0] = tm;
			model.addRow(rowData);
		}

		model.setValueAt(tm, row, COL_TM);
		for (RpMetric item : items) {
			Object loc = item.getLocation();
			Integer col = locMap.get(loc.toString());
			if (col != null) {
				Object val = IntfUtil.getRawValue(block, item);
				model.setValueAt(val, row, col);
			}
		}
	}

	/*
	 * remove rows less than the (new) start time
	 */

	private void cleanData(DefaultTableModel model, long startTm) {

		do {
			if (model.getRowCount() == 0) {
				return;
			}
			Long tm = (Long) model.getValueAt(0, COL_TM);
			if (tm < startTm) {
				model.removeRow(0);
				continue;
			}
			break;
		} while (true);
	}

	private String dumpHeader(TableModel model) throws FileNotFoundException {
		StringBuffer h = new StringBuffer();
		PrintStream out = new PrintStream(outHeaderName);

		h.append("tm");

		int cols = model.getColumnCount();
		for (int i = 0; i < cols; i++) {
			String colName = colNames[i];
			if (colName == null || colName.length() == 0) {
				colName = model.getColumnName(i);
			}
			out.println(colName);
			h.append(",");
			h.append(colName);

		}

		out.close();

		return h.toString();
	}

	private void dumpData(TableModel model) throws FileNotFoundException {
		PrintStream out = new PrintStream(outTempName);

		int rows = model.getRowCount();
		int cols = model.getColumnCount();
		for (int row = 0; row < rows; row++) {
			Object val = null;
			try {
				val = model.getValueAt(row, COL_TM);
			} catch (Exception e) {
				System.err.println("*** ???Maybe row is short??? ***");
				e.printStackTrace();
			}

			if (val == null) {
				// on occasion, we might skip a row...ignore these empty rows
				continue;
			}

			for (int col = 0; col < cols; col++) {
				val = model.getValueAt(row, col);
				if (col > 0) {
					out.print(",");
				}
				int ival = 0;
				if (val instanceof Integer) {
					ival = ((Integer) val).intValue();
				}
				if (val != null && ival != -1) {
					String seg = val.toString();
					if( seg.indexOf('.') < 0 ) {
						seg = seg + ".00";
					}
					out.print(seg);
				}
			}
			out.println();
		}
		out.close();

		File f = new File(outTempName);
		File dest = new File(outFileName);
		if (dest.exists()) {
			log.error("dest exists, removing: {}", dest.getPath());
			dest.delete();
		}
		f.renameTo(dest);

		try {
			File timestampCopy = new File("c:/tmp/ontomed/cosmo-" + tstamp_df.format(new Date()) + ".log");
			PrintStream tsout = new PrintStream(timestampCopy);
			Path tsin = Paths.get(outFileName);
			Files.copy(tsin, tsout);
			tsout.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private void parseParameters(Map<String,String> params) {
		if (params == null || params.size() == 0) {
			return;
		}

		if (analysis == null) {
			return;
		}

		DefaultTableModel model = new DefaultTableModel();
		model.addColumn("tm");
		for (String key : params.keySet() ) {
			String val = params.get(key);

			if ("dest".equals(key)) {
				destFile.setText(val);
				outFileName = val;
				int idx = outFileName.lastIndexOf('.');
				outTempName = outFileName.substring(0, idx) + ".tmp";
				outHeaderName = outFileName.substring(0, idx) + ".nms";

			} else if ("secs".equals(key)) {
				secs.setText(val);
				if (val.endsWith("sec")) {
					val = val.substring(0, val.length() - 4);
				}
				secsValue = Integer.parseInt(val);
			} else if ("window".equals(key)) {
				windowPoints.setText(val);
				nValues = Integer.parseInt(val);
			} else {
				addDeviceMetrics(model, key, val);
			}
		}

		metricTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		metricTable.setModel(model);

		colNames = new String[model.getColumnCount()];
		devNames = new String[model.getColumnCount()];

	}

	private void addDeviceMetrics(DefaultTableModel model, String key, String val) {

		reqDevs.add(key);

		if (val == null || val.length() == 0) {
			return; // nothing to add??
		}
		String[] arr = val.split(",");
		for (String loc : arr) {
			model.addColumn(loc);
			locMap.put(loc, model.getColumnCount() - 1);
		}

	}

	public String getTempFileName() {
		return outTempName;
	}

	public String getOutputFileName() {
		return outFileName;
	}

	@Override
	public void tick() {
		if (disconnected) {
			log.error("DISCONNECTED!");
			return;
		}
		String zzout = "c:/tmp/ontomed/data/cosmos_out.out";
		File f = new File(zzout); //outFileName); // logFileName);

		if (f.exists()) {
			synchronized (this) {
				try {
					cmplx_field.setText("");
					stability_field.setText("");
					processLogFile(f);
					// this can only be done on event dispatch thread...is it useful???
					//	if (autoUpdate.isSelected()) {
					//		int row = logTable.getRowCount() - 1;
					//		logTable.getSelectionModel().setSelectionInterval(row, row);
					//	}
					File outf = new File(zzout); // outFileName);
					if (outf.exists()) {
						outf.delete();
					}
				} catch (Exception e) {
					log.error("cosmos tick", e);
				}
			}
		}

	}

	private void selectSignalsActionPerformed(ActionEvent e) {
		SignalPriorityPanel spanel = new SignalPriorityPanel();
		spanel.setSignals();

		String[] options = {};
		JOptionPane p = new JOptionPane(spanel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options, null);
		JDialog d = p.createDialog(this, "Signal Selection");
		GuiUtil.initModalDialog(d, p); // makes the escape key work
		d.setResizable(true);
		d.pack();
		d.setVisible(true);

		if (spanel.isOk()) {
			lock.setSelected(true);
			GuiUtil.showMessage("Select Signals not ready");
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		tabbedPane1 = new JTabbedPane();
		panel99 = new JPanel();
		panel4 = new JPanel();
		autoUpdate = new JCheckBox();
		lock = new JCheckBox();
		label1 = new JLabel();
		displayCount = new JComboBox<>();
		label5 = new JLabel();
		label6 = new JLabel();
		selectSignals = new JButton();
		cmplx_field = new JLabel();
		stability_field = new JLabel();
		panel1 = new JPanel();
		relativePanel = new JPanel();
		stabilityPanel = new JPanel();
		panel3 = new JPanel();
		scrollPane1 = new JScrollPane();
		metricTable = new JTable();
		panel2 = new JPanel();
		destFile = new JLabel();
		label3 = new JLabel();
		secs = new JLabel();
		label4 = new JLabel();
		windowPoints = new JLabel();
		label2 = new JLabel();
		index = new JLabel();
		panel5 = new JPanel();
		scrollPane2 = new JScrollPane();
		logTable = new JTable() {

			@Override
			public boolean isCellEditable(int row, int column) {

				return false;
			}

		};
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:default:grow(0.5)"));

		//======== tabbedPane1 ========
		{

			//======== panel99 ========
			{
				panel99.setLayout(new BorderLayout());

				//======== panel4 ========
				{
					panel4.setLayout(new FormLayout("8*(default, $lcgap), default:grow, $lcgap, default",
							"default, $lgap, default"));

					//---- autoUpdate ----
					autoUpdate.setText("Auto update");
					autoUpdate.setSelected(true);
					autoUpdate.setToolTipText("Update the display with each new complexity computation.");
					panel4.add(autoUpdate, cc.xy(1, 1));

					//---- lock ----
					lock.setText("Lock");
					lock.setToolTipText("Lock selected signals in place, don't change the order or selection of signals.");
					panel4.add(lock, cc.xy(3, 1));

					//---- label1 ----
					label1.setText("Displayed Items:");
					panel4.add(label1, cc.xy(5, 1));

					//---- displayCount ----
					displayCount.setModel(new DefaultComboBoxModel<>(new String[] { "10", "20", "40" }));
					displayCount.setToolTipText("Number of signals displayed.");
					displayCount.setSelectedIndex(1);
					panel4.add(displayCount, cc.xy(7, 1));

					//---- label5 ----
					label5.setText("Complexity:");
					panel4.add(label5, cc.xy(9, 1));

					//---- label6 ----
					label6.setText("Stability:");
					panel4.add(label6, cc.xy(13, 1));

					//---- selectSignals ----
					selectSignals.setText("Select Signals");
					selectSignals.addActionListener(new ActionListener() {
						@Override
						public void actionPerformed(ActionEvent e) {
							selectSignalsActionPerformed(e);
						}
					});
					panel4.add(selectSignals, cc.xy(19, 1));

					//---- cmplx_field ----
					cmplx_field.setText("_cmplx");
					panel4.add(cmplx_field, cc.xy(9, 3));

					//---- stability_field ----
					stability_field.setText("_stability");
					panel4.add(stability_field, cc.xy(13, 3));
				}
				panel99.add(panel4, BorderLayout.SOUTH);

				//======== panel1 ========
				{
					panel1.setLayout(new FormLayout("[250dlu,default,360dlu], $lcgap, [50dlu,default,360dlu]:grow",
							"fill:default:grow"));

					//======== relativePanel ========
					{
						relativePanel.setLayout(new BorderLayout());
					}
					panel1.add(relativePanel, cc.xy(1, 1));

					//======== stabilityPanel ========
					{
						stabilityPanel.setLayout(new FormLayout("default:grow",
								"fill:default:grow, $lgap, fill:default:grow"));
					}
					panel1.add(stabilityPanel, cc.xy(3, 1));
				}
				panel99.add(panel1, BorderLayout.CENTER);
			}
			tabbedPane1.addTab("Relative Complexity", panel99);

			//======== panel3 ========
			{
				panel3.setLayout(new FormLayout("default:grow", "fill:default:grow, $lgap, default"));

				//======== scrollPane1 ========
				{

					//---- metricTable ----
					metricTable.setBorder(null);
					metricTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
					metricTable.setPreferredScrollableViewportSize(new Dimension(450, 200));
					scrollPane1.setViewportView(metricTable);
				}
				panel3.add(scrollPane1, cc.xy(1, 1));

				//======== panel2 ========
				{
					panel2.setLayout(new FormLayout(
							"default:grow, $lcgap, default, $lcgap, [20dlu,default], $lcgap, default, $lcgap, [20dlu,default], $lcgap, default, $lcgap, [20dlu,default]",
							"default"));

					//---- destFile ----
					destFile.setText("[NONE]");
					panel2.add(destFile, cc.xy(1, 1));

					//---- label3 ----
					label3.setText("Secs:");
					panel2.add(label3, cc.xy(3, 1));

					//---- secs ----
					secs.setText("--");
					panel2.add(secs, cc.xy(5, 1));

					//---- label4 ----
					label4.setText("Window:");
					panel2.add(label4, cc.xy(7, 1));

					//---- windowPoints ----
					windowPoints.setText("0");
					panel2.add(windowPoints, cc.xy(9, 1));

					//---- label2 ----
					label2.setText("Pos:");
					panel2.add(label2, cc.xy(11, 1));

					//---- index ----
					index.setText("0");
					panel2.add(index, cc.xy(13, 1));
				}
				panel3.add(panel2, cc.xy(1, 3));
			}
			tabbedPane1.addTab("Input", panel3);

			//======== panel5 ========
			{
				panel5.setLayout(new FormLayout("default:grow", "fill:default:grow, $lgap, default"));

				//======== scrollPane2 ========
				{

					//---- logTable ----
					logTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
					logTable.setModel(new DefaultTableModel(new Object[][] {
							{ null, null, null, null, null, "", null, null, null },
							{ null, null, null, null, null, null, null, null, null }, }, new String[] { "TM",
							"Short-Term", "Mid-Term", "Long-Term", "Complexity", "Lower Bound", "Upper Bound",
							"Entropy", "Robustness" }) {
						boolean[] columnEditable = new boolean[] { false, false, false, false, false, false, false,
								false, false };

						@Override
						public boolean isCellEditable(int rowIndex, int columnIndex) {
							return columnEditable[columnIndex];
						}
					});
					logTable.setPreferredScrollableViewportSize(new Dimension(450, 200));
					logTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
					scrollPane2.setViewportView(logTable);
				}
				panel5.add(scrollPane2, cc.xy(1, 1));
			}
			tabbedPane1.addTab("Output", panel5);

		}
		add(tabbedPane1, cc.xy(1, 3));

		//---- bindings ----
		bindingGroup = new BindingGroup();
		bindingGroup.addBinding(Bindings.createAutoBinding(UpdateStrategy.READ, lock, BeanProperty.create("selected"),
				displayCount, BeanProperty.create("enabled")));
		bindingGroup.bind();
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JTabbedPane tabbedPane1;
	private JPanel panel99;
	private JPanel panel4;
	private JCheckBox autoUpdate;
	private JCheckBox lock;
	private JLabel label1;
	private JComboBox<String> displayCount;
	private JLabel label5;
	private JLabel label6;
	private JButton selectSignals;
	private JLabel cmplx_field;
	private JLabel stability_field;
	private JPanel panel1;
	private JPanel relativePanel;
	private JPanel stabilityPanel;
	private JPanel panel3;
	private JScrollPane scrollPane1;
	private JTable metricTable;
	private JPanel panel2;
	private JLabel destFile;
	private JLabel label3;
	private JLabel secs;
	private JLabel label4;
	private JLabel windowPoints;
	private JLabel label2;
	private JLabel index;
	private JPanel panel5;
	private JScrollPane scrollPane2;
	private JTable logTable;
	private BindingGroup bindingGroup;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void setDisconnected(boolean b) {
		disconnected = b;
	}

	@Override
	public StreamProducer[] getSignalProducers() {
		StreamProducer[] producers = new StreamProducer[] { processor };
		return producers;
	}

	@Override
	public void clear() {
		// TODO Auto-generated method stub

	}

	@Override
	public void autoscale() {
		// TODO Auto-generated method stub

	}

}
