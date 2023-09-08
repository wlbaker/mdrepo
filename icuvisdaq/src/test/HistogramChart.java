package idea.chart;

import icuInterface.events.NumericsEvent;
import icuInterface.message.NumericBlock;
import idea.display.ImageSelection;
import idea.display.ScaleChangeListener;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Alarm;
import idea.model.IntfUtil;
import idea.model.PersistentItem;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.Image;
import java.awt.Transparency;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.LinkedList;

import javax.swing.JPanel;

import lombok.extern.slf4j.Slf4j;
import idea.schema.rp.RpMetric;

@Slf4j
@SuppressWarnings("serial")
public class HistogramChart extends JPanel implements StreamConsumer {

	int[] bins;
	int minBin = 0;
	int maxBin = 0;
	int maxValue = 0;

	/**************************************
	 * Colors for the Plotting Components *
	 **************************************/
	protected Color rrIntervalPlotColor = Color.MAGENTA;
	protected Color frameLineColor = Color.BLACK;
	protected Color frameInsideLineColor = Color.LIGHT_GRAY;
	protected Color frameFillColor = Color.WHITE;
	protected Color axesNumColor = Color.GRAY;
	protected Color titleColor = Color.BLACK;
	protected Color bgColor = Color.WHITE;

	// RR coordinates origin
	final int horzRRScaleWidth = 100;
	final int horzRRScaleHeight = 20;
	final int fRRScaleNumSize = 9;

	/****************************************************
	 * Limit below which scale values use decimal format, above which they use
	 * scientific format.
	 ****************************************************/
	double upLimit = 100.0;
	double loLimit = 0.01;

	/******************************
	 * Plotting variables
	 ******************************/
	boolean readyToPlotRRBins;
	int plotRRScrollBarValue;
	double plotRRZoom = 20;
	/* Flag Variable, show if data has been generated. */
	private boolean ecgGenerated = false;
	private boolean rrGenerated = false;

	// Histogram bar parameters.
	protected Color fBarLineColor = Color.DARK_GRAY;
	protected Color fBarFillColor = Color.BLUE; // Color.PINK;
	int fGap = 2; // 2 pixels between bars

	// Fractional margin between highest bar and top frame
	double fTopMargin = 0.05;

	// Fractional margnin between side bars and frame
	double fSideMargin = 0.01;

	// Arrays to hold numbers for axes scale values
	double[] fXScaleValue;
	double[] fYScaleValue;

	// Number of values on each axis
	int fNumYScaleValues = 2;
	int fNumXScaleValues = 5;

	public enum XAxisMode {
		TIME, POINT
	}

	public final static int VERTICAL_LINE_STYLE = 1;
	public final static int POINT_STYLE = 2;
	private static final int CURSOR_WIDTH = 50;

	protected Image image = null;
	protected LinkedList<WaveformData> signals = new LinkedList<WaveformData>();
	protected LinkedList<ScaleChangeListener> listeners = new LinkedList<ScaleChangeListener>();

	protected LinkedList<PersistentItem> events = new LinkedList<PersistentItem>();

	private boolean scrolling;

	public boolean isScrolling() {
		return scrolling;
	}

	public void setScrolling(boolean scrolling) {
		this.scrolling = scrolling;
	}

	public XAxisMode getAxisMode() {
		return axis_mode;
	}

	public void setAxisMode(XAxisMode axisMode) {
		axis_mode = axisMode;
	}

	private XAxisMode axis_mode;

	private int widthMs;
	private int visibleMs;
	private int visiblePts;
	private long startTime = -1;

	double mag = 0.5;
	double offset = 100;
	private int totBlocks = 0;
	private int sweep;
	private int insideAutoScale;

	public HistogramChart() {

		axis_mode = XAxisMode.POINT;

		initMenu();
		setTimeScalesInMillis(6000, 1000);

		addComponentListener(new ComponentAdapter() {

			@Override
			public void componentResized(ComponentEvent e) {
				checkImageSize();
				autoScale(); // WARNING: this is probably not exactly what you
				// want
				repaint();
			}

		});

	}

	public void setTimeScalesInMillis(int visibleMs, int bufferMs) {
		this.widthMs = visibleMs + bufferMs;
		this.visibleMs = visibleMs;

		axis_mode = XAxisMode.TIME;
	}

	public void setVisibleDataPoints(int visibleCount, int bufferCount) {
		this.visiblePts = visibleCount;
		axis_mode = XAxisMode.POINT;
	}

	private void initMenu() {

		final HistogramChartMenu popupMenu = new HistogramChartMenu(this);
		// popupMenu.me

		addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				checkForTriggerEvent(e);
			}

			public void mouseReleased(MouseEvent e) {
				checkForTriggerEvent(e);
			}

			private void checkForTriggerEvent(MouseEvent e) {
				if (e.isPopupTrigger())
					popupMenu.show(e.getComponent(), e.getX(), e.getY());
			}
		});
	}

	@Override
	public void paint(Graphics g) {

		this.setOpaque(false);
		// super.paint(g); // sets the background

		// First call the paintComponent of the
		// superclass, in this case JPanel.
		// super.paintComponent(g);

		// Get the histogram max value and bin data
		int max_data_value = getMaxValue();
		String strValue;
		// int length = bins.size();
		int length = getBinMaxIndex() - getBinMinIndex() + 1;

		if (max_data_value == 0)
			return;

		Color old_color = g.getColor(); // remember color for later

		// Dimensions of the drawing area for the bars
		int side_space = (int) (getWidth() * fSideMargin);
		int draw_width = getWidth() - 2 * side_space - (length - 1) * fGap;

		int draw_height = (int) (getHeight() * (1.0 - fTopMargin));

		// To avoid build up of round off errors, the bar
		// positions will be calculated from a FP value.
		float step_width = (float) draw_width / (float) length;
		int bar_width = Math.round(step_width);
		step_width += fGap;

		// Scale the bars to the maximum bin value.
		float scale_factor = (float) draw_height / max_data_value;

		int start_x = side_space;
		int start_y = getHeight();

		// for (int i = 0; i < length; i++) {
		for (int i = getBinMinIndex(); i < getBinMaxIndex(); i++) {
			int bar_height = (int) (bins[i] * scale_factor);

			int bar_x = (int) (i * step_width) + start_x;

			// Bar drawn from top left corner
			int bar_y = start_y - bar_height;

			g.setColor(fBarLineColor);
			g.drawRect(bar_x, bar_y, bar_width, bar_height);

			g.setColor(fBarFillColor);
			g.fillRect(bar_x + 1, bar_y + 1, bar_width - 2, bar_height - 1);

			strValue = String.valueOf(i);

			/*
			 * if (i%250 == 0) { g.setColor(axesNumColor); drawText(g, strValue,
			 * bar_x + bar_width, horzRRScaleY, horzRRScaleWidth,
			 * horzRRScaleHeight, fRRScaleNumSize,LEFT);
			 * g.setColor(frameInsideLineColor); g.drawLine(bar_x + bar_width,
			 * posFrameY, bar_x + bar_width, horzRRScaleY + 5); }
			 */
		}

		// Draw the label along the vertical axis
		// lblMaxFrequency.setText(String.valueOf((int)histogramOb.getMax()));
		// lblMidFrequency.setText(String.valueOf((int)histogramOb.getMax()/2));
		// lblMinFrequency.setText("0");
		/*
		 * strValue = String.valueOf(histogramOb.getMax());
		 * 
		 * g.setColor(axesNumColor); drawText(g, strValue, posFrameX, posFrameY,
		 * horzRRScaleWidth, horzRRScaleHeight, fRRScaleNumSize,LEFT);
		 */

		g.dispose();
	}

	private void checkImageSize() {
		Dimension dim = getSize();
		if (dim.width == 0) { // this can happen for not-yet-rendered
			// components
			dim = new Dimension(100, 100);
		}
		int reqWidth = 0;
		if (axis_mode == XAxisMode.TIME) {
			reqWidth = (dim.width * widthMs) / visibleMs;
		} else if (axis_mode == XAxisMode.POINT) {
			reqWidth = dim.width;
		}
		if (image == null || image.getWidth(null) != reqWidth || image.getHeight(null) != dim.height) {
			// image = createImage(dim.width, dim.height);

			GraphicsConfiguration gc = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice()
					.getDefaultConfiguration();

			image = gc.createCompatibleImage(reqWidth, dim.height, Transparency.TRANSLUCENT);

			// set hte background color and fill
			Graphics2D graphics = (Graphics2D) image.getGraphics();

			graphics.setColor(Color.BLACK);
			graphics.fillRect(0, 0, image.getWidth(null), image.getHeight(null));

			if (events != null && events.size() > 0) {
				renderFromHistory(graphics);
			}

			graphics.dispose();
		}
	}

	private void renderFromHistory(Graphics2D graphics) {

		synchronized (events) {

			// no connecting lines, we are redrawing from history
			for (WaveformData wd : signals) {
				wd.lastX = -1;
			}

			for (PersistentItem event : events) {
				_signalEvent(event, true);
			}

		}
	}

	public void addWaveform(String loc, Color color, int freq) {
		WaveformData wd = new WaveformData(null, loc, color, freq, 0);
		signals.add(wd);
	}

	public void addNumerics(String loc, Color color, int freq, int style) {
		WaveformData wd = new WaveformData(null, loc, color, freq, style);
		signals.add(wd);
	}

	/*
	 * Signal processing
	 */

	boolean rescale;
	private Alarm alarmItem;
	private boolean bSummary;
	private int beats;
	private int tot;

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		rescale = false;

		long tm = _signalEvent(item, false);

		if (tm != 0) {
			totBlocks++;
			bufferEvent(tm, item);
		}

		if (rescale) {
			autoScale();
			totBlocks++; // if you get a "render from history" call on the
		}

		repaint();
	}

	public long _signalEvent(PersistentItem item, boolean reprocess) {

		long tm = 0;
		rescale = false;

		tm = item.getTime();
		if (item.getStreamID() == StreamID.WAVEFORM.getCode()) {

			for (WaveformData wd : signals) {
				int[] values = (int[]) IntfUtil.getRawValueByLoc(item, wd.getLoc());
				if (values != null) {

					setBins(values);

					rescale |= drawWaveform(tm, values);
					if (alarmItem != null) {
						drawAlarm(alarmItem);
					}

					// drawTotalTime();
				}
			}
		} else if (item.getStreamID() == StreamID.ALARM.getCode()) {
			alarmItem = (Alarm) item;

			drawAlarm(alarmItem);
		} else if (item.getStreamID() == StreamID.MEASUREMENT.getCode()) {

			for (WaveformData wd : signals) {
				Number ni = (Number) IntfUtil.getRawValueByLoc(item, wd.getLoc());
				if (ni != null) {
					if (wd.getStyle() == VERTICAL_LINE_STYLE) {
						drawNumerics(tm, ni);
					} else if (wd.getStyle() == POINT_STYLE) {

						int[] values = new int[1];
						values[0] = ni.intValue();

						rescale |= drawWaveform(tm, values);
						rescale = true; // force a redraw and rescale

						if (bSummary) {
							if (!reprocess) {
								beats++;
								tot += values[0];
							}

							drawMessage("Beat: " + beats + " Tot: " + (tot / 1000) + "s");
						}
					}
				}
			}
		}

		return tm;

	}

	private void setBins(int[] values) {
		minBin = 0;
		maxBin = values.length;
		for (int i = 0; i < values.length; i++) {
			bins[i] = values[i];
			maxValue = Math.max(maxValue, values[i]);
		}
	}

	private int getBinMinIndex() {
		return minBin;
	}

	private int getBinMaxIndex() {
		return maxBin;
	}

	private int getMaxValue() {
		return maxValue;
	}

	private void drawAlarm(Alarm alarmInfo) {
		drawMessage(alarmInfo.getMessage());
	}

	private void bufferEvent(long curr, PersistentItem item) {

		// System.out.println("buffering: event=" + e);

		if (axis_mode == XAxisMode.TIME) {
			while (events.size() > 0) {
				PersistentItem block = events.get(0);
				log.error("FIXME: WAVEFORM EVENTS NO LONGER EXIST");
				if (curr - block.getTime() > visibleMs) {
					events.remove(0);
				} else {
					break;
				}
			}

		} else {

			// axis mode == point

			// FIXME: history should be variable length!

			while (events.size() > 200) { // number of history points to display
				events.remove(0);
			}
		}

		events.addLast(item);
	}

	protected boolean drawWaveform(long waveStartMs, int[] values) {

		if (image == null || widthMs == 0) {
			return false;
		}

		if (mag == 0) { // happens with first data block
			return true; // force a rescale...no need to draw now
		}

		if (startTime < 0) {
			startTime = waveStartMs;

			System.out.println("HISTO START TIME: " + startTime);
		}

		waveStartMs -= startTime;
		waveStartMs %= widthMs;

		boolean rescale = false;

		synchronized (image) {

			int image_width = image.getWidth(null);
			int chart_width = getWidth();

			this.setOpaque(false);
			// super.paint(g); // sets the background

			// First call the paintComponent of the
			// superclass, in this case JPanel.
			// super.paintComponent(g);

			// Get the histogram max value and bin data
			int max_data_value = getMaxValue();
			String strValue;
			// int length = bins.size();
			int length = getBinMaxIndex() - getBinMinIndex() + 1;

			if (max_data_value == 0)
				return false;

			// Dimensions of the drawing area for the bars
			int side_space = (int) (getWidth() * fSideMargin);
			int draw_width = getWidth() - 2 * side_space - (length - 1) * fGap;

			int draw_height = (int) (getHeight() * (1.0 - fTopMargin));

			// To avoid build up of round off errors, the bar
			// positions will be calculated from a FP value.
			float step_width = (float) draw_width / (float) length;
			int bar_width = Math.round(step_width);
			step_width += fGap;

			// Scale the bars to the maximum bin value.
			float scale_factor = (float) draw_height / max_data_value;

			int start_x = side_space;
			int start_y = getHeight();

			// for (int i = 0; i < length; i++) {
			for (int i = getBinMinIndex(); i < getBinMaxIndex(); i++) {
				int bar_height = (int) (bins[i] * scale_factor);

				int bar_x = (int) (i * step_width) + start_x;

				// Bar drawn from top left corner
				int bar_y = start_y - bar_height;

				Graphics g = image.getGraphics();
				g.setColor(fBarLineColor);
				g.drawRect(bar_x, bar_y, bar_width, bar_height);

				g.setColor(fBarFillColor);
				g.fillRect(bar_x + 1, bar_y + 1, bar_width - 2, bar_height - 1);
				g.dispose();

				strValue = String.valueOf(i);

				/*
				 * if (i%250 == 0) { g.setColor(axesNumColor); drawText(g,
				 * strValue, bar_x + bar_width, horzRRScaleY, horzRRScaleWidth,
				 * horzRRScaleHeight, fRRScaleNumSize,LEFT);
				 * g.setColor(frameInsideLineColor); g.drawLine(bar_x +
				 * bar_width, posFrameY, bar_x + bar_width, horzRRScaleY + 5); }
				 */
			}

			// Draw the label along the vertical axis
			// lblMaxFrequency.setText(String.valueOf((int)histogramOb.getMax()));
			// lblMidFrequency.setText(String.valueOf((int)histogramOb.getMax()/2));
			// lblMinFrequency.setText("0");
			/*
			 * strValue = String.valueOf(histogramOb.getMax());
			 * 
			 * g.setColor(axesNumColor); drawText(g, strValue, posFrameX,
			 * posFrameY, horzRRScaleWidth, horzRRScaleHeight,
			 * fRRScaleNumSize,LEFT);
			 */

		}

		return rescale;
	}

	protected void drawMessage(String m) {

		if (image == null) {
			return;
		}

		synchronized (image) {

			int w = image.getWidth(null);
			int h = image.getHeight(null);

			Graphics2D g = (Graphics2D) image.getGraphics();

			int textWidth = 200;
			int textHeight = 15;

			g.clearRect(w - textWidth, h - 2 * textHeight, textWidth, textHeight);
			g.drawString(m, w - textWidth, h - textHeight);

			g.dispose();

			repaint();
		}
	}

	protected void drawNumerics(long waveStartMs, Number v) {
		synchronized (image) {
			int h = image.getHeight(null);

			int w = image.getWidth(null);
			int x = (int) (w + v.intValue()); // pixelTime * rPos);

			Graphics2D g = (Graphics2D) image.getGraphics();

			/*
			 * graphics.setColor(Color.RED); graphics.drawLine(2, 0, w-2, 0);
			 * graphics.drawLine(0, 0, 100, 100); graphics.drawLine(w-1, 0,
			 * w-200, 200);
			 */
			g.setColor(Color.BLUE);
			g.drawLine((int) x, 0, (int) x, h);
			g.dispose();
		}
	}

	/*
	 * misc utility routines
	 */

	public void clear() {
		Dimension dim = getSize();

		synchronized (image) {
			Graphics2D graphics = (Graphics2D) image.getGraphics();

			startTime = -1;
			/*
			 * graphics.setColor(Color.RED); graphics.drawLine(2, 0, w-2, 0);
			 * graphics.drawLine(0, 0, 100, 100); graphics.drawLine(w-1, 0,
			 * w-200, 200);
			 */
			Color c = new Color(16, 12, 12);
			graphics.setColor(c); // getBackground() );
			graphics.fillRect(0, 0, (int) dim.getWidth(), (int) dim.getHeight());

			graphics.dispose();
		}
	}

	public void copyImageToClipboard() {
		// Work around a Sun bug that causes a hang in
		// "sun.awt.image.ImageRepresentation.reconstruct".
		ImageSelection.copyImageToClipboard(image);
	}

	public void setPenColor(String signalName, Color white) {
		// TODO Auto-generated method stub

	}

	public void autoScale() {
		// this routine will trigger a render-from-history call
		if (image == null) {
			return;
		}

		if (insideAutoScale > 0) { // dont recurse into autoscale when rendering
			// from history
			return;
		}

		if (events.size() == 0) {
			return;
		}

		insideAutoScale++;

		double as_min = Double.MAX_VALUE;
		double as_max = Double.MIN_VALUE;

		for (PersistentItem block : events) {
			RpMetric[] metrics = block.getMetrics();
			RpMetric m1 = metrics[1];
			log.warn("UNTESTED CODE...metric 1?...FIXME??");
			if (block.getStreamID() == StreamID.WAVEFORM.getCode()) {

				int[] values = (int[]) IntfUtil.getRawValue(block, m1);
				if (values != null) {
					for (int d : values) {
						if (d > as_max) {
							as_max = d;
						}
						if (d < as_min) {
							as_min = d;
						}
					}
				}
			} else if (block.getStreamID() == StreamID.MEASUREMENT.getCode()) {

				// System.out.println(" checkme: why am i getting a numerics
				// item from wd?");
				Number wf = (Number) IntfUtil.getRawValue(block, m1);
				if (wf != null) {
					double d = wf.doubleValue();
					if (d > as_max) {
						as_max = d;
					}
					if (d < as_min) {
						as_min = d;
					}
					// System.out.println(" d=" + d + " max=" + as_max +
					// " min=" + as_min);
				}
			}
		}

		setYScale(as_min, as_max);
		image = null;
		checkImageSize();

		insideAutoScale--;
	}

	public void setYScale(double as_min, double as_max) {

		if (as_min == as_max) {
			as_min -= 1.0;
			as_max += 1.0;
		}

		double range = as_max - as_min;
		if (range == 0.0)
			range = 1.0;
		as_max += 0.1 * range;
		as_min -= 0.1 * range;

		boolean flip = true;
		if (flip) {
			double t = as_min;
			as_min = as_max;
			as_max = t;
		}

		checkImageSize();

		int h = image.getHeight(null);
		mag = h / (as_max - as_min);
		offset = -mag * as_min;

		// System.out.println(this.getName() + " h=" + h + " min=" + as_min +
		// " max=" + as_max + " mag=" + mag + " range="
		// + range + " offset=" + offset);
		fireScaleChange(as_min, as_max);

	}

	/*
	 * scale change handlers
	 */
	private void fireScaleChange(double asMin, double asMax) {
		synchronized (listeners) {
			for (ScaleChangeListener l : listeners) {
				l.scaleChange(asMin, asMax);
			}
		}
	}

	public void addScaleChangeListener(ScaleChangeListener l) {
		synchronized (listeners) {
			listeners.add(l);
		}
		// double as_min = offset/mag;
		// double as_max = this.getHeight() / mag + as_min;
		// l.scaleChange(as_min, as_max );
	}

	public void removeScaleChangeListener(ScaleChangeListener l) {
		synchronized (listeners) {
			listeners.remove(l);
		}
	}

	public void showSummary(boolean bSummary) {
		this.bSummary = bSummary;
	}

}
