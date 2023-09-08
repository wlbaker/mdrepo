package idea.chart;

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
import java.util.Date;
import java.util.LinkedList;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class SignalChart extends JPanel implements StreamConsumer {

	public enum XAxisMode {
		TIME, POINT
	}

	public final static int VERTICAL_LINE_STYLE = 1;
	public final static int POINT_STYLE = 2;
	private static final int CURSOR_WIDTH = 20;
	private static final int MAX_EVENTS = 400;

	protected Image image = null;
	protected LinkedList<WaveformData> signals = new LinkedList<WaveformData>();
	protected LinkedList<ScaleChangeListener> listeners = new LinkedList<ScaleChangeListener>();

	protected LinkedList<PersistentItem> events = new LinkedList<PersistentItem>();

	private boolean scrolling;

	private Double scale_min_y;
	private Double scale_max_y;

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
	// double offset = 100;
	private int totBlocks = 0;
	private int offscale_count;
	private int insideAutoScale;
	private int create_width;
	private int create_height;

	public SignalChart() {

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

		final SignalChartMenu popupMenu = new SignalChartMenu(this);
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

		if (image != null) {

			synchronized (image) { // actually, this is not adequate to ensure
				// image is not null
				if (scrolling) {

					int lastX = 0;
					for (WaveformData wd : signals) {
						if (wd.lastX > lastX)
							lastX = (int) wd.lastX;
					}

					/*
					 * origin to current point ...this is the most recent
					 * section of the image
					 */
					int h = getHeight();
					int w = getWidth();

					int sx1 = 0;
					int sy1 = 0;

					int dx1 = w - lastX;
					int dy1 = 0;

					int dx2 = w;
					int dy2 = h;
					int sx2 = lastX;
					int sy2 = h;

					int dw = dx2 - dx1;
					int ref1 = dx1;

					System.err.println(this.getName() + " x1=" + dx1 + " y1=" + dy1 + " x2=" + dx2 + " y2=" + dy2
							+ " sx1=" + sx1 + " sy1=" + sy1 + " sx2=" + sx2 + " sy2=" + sy2);
					g.drawImage(image, dx1, dy1, dx2, dy2, sx1, sy1, sx2, sy2, null);

					/*
					 * remainder of the image, from the cursor to the end
					 * ...this is the oldest section of the image
					 */
					int bufferPixels = 20; // FIXME: the buffer size is not
					// right
					sx1 = lastX + bufferPixels;
					sy1 = 0;
					sx2 = w;
					sy2 = h;

					dx1 = sx1 - dw;
					dy1 = 0;

					dx2 = sx2 - dw;
					dy2 = h;

					g.drawImage(image, dx1, dy1, dx2, dy2, sx1, sy1, sx2, sy2, null);

					g.setColor(Color.RED);
					g.drawLine(ref1, 0, ref1, h);

					g.setColor(Color.GREEN);
					g.drawLine(dx1, 0, dx1, h);

					// g.drawImage(image, x2, 0, lastX, h, null );
				} else {
					g.drawImage(image, 0, 0, null);
				}
			}
		}

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
		if (image == null || create_width != reqWidth || create_height != dim.height) {
			create_width = reqWidth;
			create_height = dim.height;

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

			// System.out.println("render from history: " + getName());
			// no connecting lines, we are redrawing from history
			for (WaveformData wd : signals) {
				wd.lastX = -1;
			}

			for (PersistentItem event : events) {
				_signalEvent(StreamID.WAVEFORM, event, true);
			}

		}
	}

	public void addWaveform(String loc, Color color, int freq) {
		addWaveform(null, loc, color, freq);
	}

	public void addWaveform(String code, String loc, Color color, int freq) {
		WaveformData wd = new WaveformData(code, loc, color, freq, 0);
		signals.add(wd);
	}

	public void addNumerics(String loc, Color color, int freq, int style) {
		addNumerics(null, loc, color, freq, style);
	}

	public void addNumerics(String code, String loc, Color color, int freq, int style) {
		WaveformData wd = new WaveformData(code, loc, color, freq, style);
		signals.add(wd);
	}

	public LinkedList<WaveformData> getSignals() {
		return signals;
	}

	/*
	 * Signal processing
	 */

	boolean rescale;
	private Alarm alarmItem;
	private boolean bSummary;
	private int beats;
	private int tot;
	private Double scale_min_range;
	private int numDataPoints = 200;
	private double offset;

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		rescale = false;

		long tm = _signalEvent(sid, item, false);

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

	public long _signalEvent(StreamID sid, PersistentItem item, boolean reprocess) {

		long tm = 0;

		if (sid == StreamID.WAVEFORM) {

			tm = item.getTime();

			for (WaveformData wd : signals) {
				int[] wf = (int[]) IntfUtil.getRawValueByLoc(item, wd.getLoc());
				if (wf != null) {

					// FIXME: int double disagreement
					// OK, so here you have it. Numerics are drawn as doubles
					// and waves are drawn as int's.
					// This needs more thought, changes, and testing

					double[] dvalues = new double[wf.length];

					int i = 0;
					for (int val : wf) {
						dvalues[i++] = val;
					}

					rescale |= drawWaveform(tm, wd, dvalues);
					if (alarmItem != null) {
						drawAlarm(alarmItem);
					}

					// drawTotalTime();
				}
			}

		} else if (sid == StreamID.ALARM) {

			drawAlarm((Alarm) item);
		} else if (sid == StreamID.MEASUREMENT) {
			PersistentItem pib = (PersistentItem) item;
			Date dt = pib.getTm();

			for (WaveformData wd : signals) {
				Number ni_value = IntfUtil.getScaledValueByLoc(pib, wd.getLoc());
				if (ni_value != null) {
					addSignalValue(tm, wd, ni_value, reprocess);
				}
			}

		}

		return tm;

	}

	private void addSignalValue(long tm, WaveformData wd, Number ni_value, boolean reprocess) {
		rescale = false;

		if (wd.getStyle() == VERTICAL_LINE_STYLE) {
			drawNumerics(tm, ni_value, wd);
		} else if (wd.getStyle() == POINT_STYLE) {
			if (ni_value != null) {
				double[] values = new double[1];
				values[0] = ni_value.doubleValue();

				rescale = drawWaveform(tm, wd, values);
				if (!reprocess && rescale) {
					autoScale();
				}
				// rescale = true; // force a redraw and rescale

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

	private void drawAlarm(Alarm alarmInfo) {
		drawMessage(alarmInfo.getMessage());
	}

	private void bufferEvent(long curr, PersistentItem e) {

		synchronized (events) {

			if (axis_mode == XAxisMode.TIME) {
				while (events.size() > 0) {
					Object o = events.get(0);
					PersistentItem block = (PersistentItem) o;
					if (curr - block.getTime() > visibleMs || events.size() > MAX_EVENTS) {
						events.remove(0);
					} else {
						break;
					}
				}
			} else {

				// axis mode == point

				// FIXME: history should be variable length!

				while (events.size() > numDataPoints || events.size() > MAX_EVENTS) { // number of history
					// points to display
					events.remove(0);
				}
			}

			events.addLast(e);
		}
	}

	protected boolean drawWaveform(long waveStartMs, WaveformData wd, double[] values) {

		if (image == null || widthMs == 0) {
			return false;
		}

		if (mag == 0) { // happens with first data block
			return true; // force a rescale...no need to draw now
		}

		if (startTime < 0) {
			startTime = waveStartMs;
		}

		waveStartMs -= startTime;
		waveStartMs %= widthMs;

		boolean rescale = false;

		synchronized (image) {

			int image_width = image.getWidth(null);
			int chart_width = getWidth();

			double dt;

			double x1;
			double y1 = values[0] * mag + offset;

			if (axis_mode == XAxisMode.TIME) {
				int pixelsPerS = (widthMs > 0) ? (1000 * chart_width) / (widthMs) : 1;

				dt = (wd.freq > 0.0) ? pixelsPerS / wd.freq : 1.0;
				x1 = (waveStartMs * pixelsPerS) / widthMs;

				if (insideAutoScale > 0) {
					System.out.print("  > ");
				}
				System.out.print(this.getName() + " ( " + x1 + " : " + waveStartMs + " )  ***********");
				System.out.println(" dt=" + dt + " x1=" + x1);

			} else {
				int pixelsPerDatum = (visiblePts > 0) ? chart_width / (visiblePts) : 1;

				x1 = wd.lastX % image_width;
				dt = pixelsPerDatum;
			}

			// if we have a previous plot point and the time delta from this
			// packet to the previous
			if (wd.lastX != -1 && x1 - wd.lastX < 3 * dt) {
				x1 = wd.lastX;
				y1 = wd.lastY;
			}

			Graphics2D g = (Graphics2D) image.getGraphics();

			/*
			 * find the upper and lower bounds of the drawing region
			 */
			int h = image.getHeight(null);

			/*
			 * draw the lines
			 */
			g.setColor(wd.getColor());

			double x2 = -1;
			double y2 = 0;

			int debug_idx = 0;
			for (double d : values) {
				x2 = x1 + dt;
				y2 = d * mag + offset;

				if (x2 > image_width) {
					x1 = 0;
					x2 = dt;
				}

				g.drawLine((int) x1, (int) y1, (int) x2, (int) y2);

				x1 = x2;
				y1 = y2;

				if (y1 < 0 || y1 > h) {
					// System.out.println("need rescale: y1=" + y1 + " h=" + h);
					offscale_count++;
					if (offscale_count > 5) {
						rescale = true;
					}

					rescale = true;
				} else {
					offscale_count = 0;
				}
			}

			/*
			 * always clear the cursor spot
			 */

			int clearWidth = CURSOR_WIDTH; // ok, width should be a ms
			// width...perhaps buffer?
			int startClear = (int) (x1 + 1);
			g.clearRect((int) (x1 + 1), 0, clearWidth, h);
			if (startClear + clearWidth > image_width) {
				g.clearRect(0, 0, image_width - startClear, h);
			}

			g.dispose();

			wd.lastX = (int) x2;
			wd.lastY = (int) y2;

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
			int textHeight = 17;

			g.clearRect(w - textWidth, h - 2 * textHeight, textWidth, textHeight);
			g.drawString(m, w - textWidth, h - textHeight);

			g.dispose();

			repaint();
		}
	}

	protected void drawNumerics(long waveStartMs, Number ni, WaveformData wd) {
		synchronized (image) {
			int h = image.getHeight(null);

			int w = image.getWidth(null);
			int x = (int) (w + ni.intValue()); // pixelTime *
												// rPos);

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
		if (image == null) {
			return; // not rendered yet...premature call to clear
		}

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
			checkImageSize();
		}

		if (insideAutoScale > 0) { // dont recurse into autoscale when rendering
			// from history
			return;
		}

		if (events.size() == 0) {

			if (scale_min_y != null && scale_max_y != null) {
				setYScale(scale_min_y, scale_max_y);
			}

			return;
		}

		insideAutoScale++;

		double as_min = Double.MAX_VALUE;
		double as_max = Double.MIN_VALUE;

		for (PersistentItem block : events) {
			if (block.getStreamID() == StreamID.WAVEFORM.getCode()) {

				for (WaveformData wd : signals) {
					int[] values = (int[]) IntfUtil.getRawValueByLoc(block, wd.getLoc());
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
				}
			} else if (block.getStreamID() == StreamID.MEASUREMENT.getCode()) {

				// System.out.println(" checkme: why am i getting a numerics item from wd?");
				for (WaveformData wd : signals) {
					Number wf = (Number) IntfUtil.getRawValueByLoc(block, wd.getLoc());
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
		}

		setYScale(as_min, as_max);
		image = null;
		checkImageSize();
		rescale = false;

		insideAutoScale--;
	}

	public void setYScale(double as_min, double as_max) {

		if (as_min == as_max) {
			as_min -= 1.0;
			as_max += 1.0;
		}

		double range = as_max - as_min;
		if (scale_min_range != null) {
			if (range < scale_min_range) {
				double halfRange = (scale_min_range - range) / 2.0;
				as_max += halfRange;
				as_min -= halfRange;
			}
		} else {

			if (range == 0.0)
				range = 1.0;
			as_max += 0.1 * range;
			as_min -= 0.1 * range;
		}

		if (scale_min_y != null) {
			// if (as_min > scale_min_y) {
			as_min = scale_min_y;
			// }
		}
		if (scale_max_y != null) {
			// if (as_max < scale_max_y) {
			as_max = scale_max_y;
			// }
		}

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
		// " max=" + as_max + " mag=" + mag + " range=" + range + " offset=" +
		// offset);

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

	// **********************************************

	public void setScaleMinY(Double scale_min_y) {
		this.scale_min_y = scale_min_y;
	}

	public Double getScaleMinY() {
		return scale_min_y;
	}

	public void setScaleMaxY(Double scale_max_y) {
		this.scale_max_y = scale_max_y;
	}

	public Double getScaleMaxY() {
		return scale_max_y;
	}

	public void setScaleMinRange(Double scale_min_range) {
		this.scale_min_range = scale_min_range;
	}

	public Double getScaleMinRange() {
		return scale_min_range;
	}

	public void setDisplayDataPoints(Integer pts) {
		if (pts == null) {
			pts = 200;
		}
		this.numDataPoints = pts;
	}

	public Integer getDisplayDataPoints() {
		return numDataPoints;
	}
}
