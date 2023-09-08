package idea.display;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.Image;
import java.awt.Stroke;
import java.awt.Transparency;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JPanel;

/*
 * TODO:
 * 
 * 1- determine when to concat waveforms
 * 2- sync initial time
 * 3-
 * 
 */

import icuInterface.UnitUtil;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

enum StripRedrawMode {
	REALTIME, // gaps for missing data
	INCREMENTAL, // no gaps
	NONE
	// turn off redraws...may be useful for debugging
}

enum StripScrollerMode {
	SCROLLING, CURSOR, RAW
}

@Slf4j
@SuppressWarnings("serial")
public class CardioStrip extends JPanel implements ActionListener, ComponentListener, ViewableSignalInterface {

	private static final int CURSOR_PTS = 20;
	private static final int CURSOR_MS = 500;

	private static DecimalFormat df_sci = new DecimalFormat("0.###E0");
	private static DecimalFormat df6 = new DecimalFormat("0.000000");
	private static DecimalFormat df3 = new DecimalFormat("0.000");
	private static DecimalFormat df2 = new DecimalFormat("#,###,##0.00");
	private static DecimalFormat df1 = new DecimalFormat("#,###,##0.0");
	private static DecimalFormat df0 = new DecimalFormat("#,###,##0");

	// protected List<ScaleChangeListener> listeners = new
	// LinkedList<ScaleChangeListener>();

	public Image signal_image = null;
	// public Image final_image = null;

	int xOffset = 0;

	int scrollRate = 0;
	int debug_idx = 0;

	public long drawTimeInMillis;

	int visibleMs;

	ViewableSignalMenu popupMenu;

	StripRedrawMode redrawMode = StripRedrawMode.INCREMENTAL;
	StripScrollerMode scrollerMode = StripScrollerMode.SCROLLING;

	double PACKET_MS;
	double PACKET_PTS;

	AffineTransform identity = new AffineTransform(1, 0, 0, 1, 0, 0);

	public StripRedrawMode getRedrawMode() {
		return redrawMode;
	}

	public void setRedrawMode(StripRedrawMode redrawMode) {
		this.redrawMode = redrawMode;
	}

	public StripScrollerMode getScrollerMode() {
		return scrollerMode;
	}

	public void setScrollerMode(StripScrollerMode scrollerMode) {
		this.scrollerMode = scrollerMode;
	}

	// private List<WaveformDescription> waves = new
	// LinkedList<WaveformDescription>();
	private List<StripSetup> setups = new LinkedList<StripSetup>();
	private RpMetric[] waves;

	private long lastStartMs;
	private int last_draw_pos;
	private boolean have_data = false;
	private boolean isClear;
	private Color EMPTY_BACKGROUND_COLOR_1 = Color.BLACK;
	private Color EMPTY_BACKGROUND_COLOR_2 = Color.BLACK;
	private Color EMPTY_BACKGROUND_COLOR_3 = Color.BLACK;
	private Color EMPTY_BACKGROUND_COLOR_4 = Color.BLACK;
	private int last_dest_x;
	private int verbose_debug = 0;

	public CardioStrip() {
		drawTimeInMillis = -1;

		initMenu();

		addComponentListener(this);
		visibleMs = 20000;

		if (log.isDebugEnabled()) {
			EMPTY_BACKGROUND_COLOR_1 = Color.MAGENTA;
			EMPTY_BACKGROUND_COLOR_2 = Color.blue;
			EMPTY_BACKGROUND_COLOR_3 = Color.ORANGE;
			EMPTY_BACKGROUND_COLOR_4 = Color.GREEN;
		}
	}

	public Color getPenColor(int idx) {
		return setups.get(idx).getColor();
	}

	@Override
	public void setPenColor(String loc, Color penColor) {
		for( StripSetup s : setups ) {
			if( loc == null || loc.equals(s.getLoc()) ) {
				s.setColor(penColor);
			}
		}
	}

	public Stroke getPenStroke(int idx) {
		return setups.get(idx).getStroke();
	}

	public void setPenStroke(Stroke stroke) {
		if (setups != null) {
			for (StripSetup setup : setups) {
				setup.setStroke(stroke);
			}
		}

	}

	public void setScaleMinimumRange(Double range) {
		if (setups != null) {
			for (StripSetup setup : setups) {
				setup.setScaleMinimumRange(range);
			}
		}

	}

	public void setPenStroke(int idx, Stroke stroke) {
		setups.get(idx).setStroke(stroke);
	}

	private void initMenu() {

		popupMenu = new ViewableSignalMenu(this, null);
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
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub

	}

	public void setTimeScalesInMillis(int visibleMs) {

		this.visibleMs = visibleMs;
		resetTrans();

	}

	private void resetTrans() {
		for (StripSetup setup : setups) {
			setup.resetTrans();
		}
	}

	private void checkImage() {
		Dimension dim = getSize();
		if (dim.width == 0) { // this can happen for not-yet-rendered
			// components
			dim = new Dimension(100, 100);
		}

		int ww = 2 * dim.width;
		if (scrollerMode == StripScrollerMode.RAW) {
			ww = dim.width;
		}
		if (signal_image == null || signal_image.getWidth(null) != ww || signal_image.getHeight(null) != dim.height) {

			GraphicsConfiguration gc = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice()
					.getDefaultConfiguration();

			int im_width = ww;
			int im_height = dim.height;
			signal_image = gc.createCompatibleImage(im_width, im_height, Transparency.TRANSLUCENT);
			Graphics gc2 = signal_image.getGraphics();
			gc2.setColor(EMPTY_BACKGROUND_COLOR_3);
			gc2.fillRect(0, 0, im_width, im_height);
			gc2.dispose();

			resetTrans();

		}
	}

	@Override
	public void paint(Graphics g) {

		// this.setOpaque(false);
		// super.paint(g); // sets the background
		Graphics2D g2 = (Graphics2D) g;
		if (PACKET_MS <= 0 || PACKET_PTS == 0) {
			// Color c = new Color(16, 12, 12);
			g2.setColor(EMPTY_BACKGROUND_COLOR_2);
			g2.fillRect(0, 0, getWidth(), getHeight());
			log.debug("draw empty rect");

		} else {

			drawFinalImage(g2);
			g2.setTransform(identity);

		}
		drawAxisLabels(g2);

		checkImage(); // check for size changes

		g2.dispose();

	}

	public void addWaveformItem(long waveStartMs, RpMetric wfitem, int[] values) {
		addWaveformItem(waveStartMs, wfitem, values, null, null);
	}

	public void addWaveformItem(long waveStartMs, RpMetric wfitem, float[] values) {
		addWaveformItem(waveStartMs, wfitem, null, values, null);
	}

	public void addWaveformItem(long waveStartMs, RpMetric wfitem, double[] values) {
		addWaveformItem(waveStartMs, wfitem, null, null, values);
	}

	private void addWaveformItem(long waveStartMs, RpMetric wfitem, int[] ivals, float[] fvals, double[] dvals) {

		log.info("{} addWaveformItem: {} visibleMS={}", waveStartMs % 10000, wfitem, visibleMs );
		if( ivals != null ) log.info(" --> ivals.length=" + ivals.length );
		if( fvals != null ) log.info(" --> fvals.length=" + fvals.length );
		if( dvals != null ) log.info(" --> dvals.length=" + dvals.length );

		int val_len = 0;
		if (ivals != null) {
			val_len += ivals.length;
		}
		if (fvals != null) {
			val_len += fvals.length;
		}
		if (dvals != null) {
			val_len += dvals.length;
		}

		if (val_len == 0) {
			// NO WAVEFORM VALUES
			return;
		}

		if (signal_image == null) {
			log.debug("signal_image is null");
			return;
		}

		isClear = false;

		// ? int h = image.getHeight(null);
		int w = signal_image.getWidth(null);
		int h = signal_image.getHeight(null);

		if (PACKET_PTS == 0) {

			int freq = wfitem.getSampleRate();
			if (freq <= 0) {
				freq = 1;
			}

			PACKET_MS = (1000.0 * val_len) / freq;

			double pts = visibleMs * freq / 1000;

			PACKET_PTS = val_len * w / pts;
			
			log.error("PACKET_MS={} PACKET_PTS={} WFITEM={}", PACKET_MS, PACKET_PTS, wfitem );
			

		}
		int wave_idx = -1; // doesnt work!
		// waves.indexOf(wfitem.getDescription());
		Object loc = wfitem.getLocation();
		for (int idx = 0; idx < setups.size(); idx++) {
			StripSetup setup = setups.get(idx);
			RpMetric wave = setup.getDescription();
			if (wave.getLocation().equals(loc)) {
				wave_idx = idx;
				break;
			}
		}

		if (wave_idx < 0) {

			log.error("not my wave: {}", wfitem);

			return; // this waveform is not setup for this viewer
		}

		StripSetup setup = setups.get(wave_idx);
		Color penColor = setup.getColor();
		if (penColor == null) {
			penColor = Color.WHITE;
		}

		Stroke stroke = setup.getStroke();

		boolean do_repaint = false;

		synchronized (signal_image) {

			if (redrawMode == StripRedrawMode.NONE) {
				return;
			}
			if (redrawMode == StripRedrawMode.REALTIME) {

				long endTimeInMillis = -1;
				long msWave = waveStartMs; // wf.getStartTime();
				long msEnd = endTimeInMillis;

				long msDelta = msEnd - msWave;

				long msWidth = 12345; // (long) (values.length * pixelsPerMs);
				if (msDelta < msWidth) {
					// slideMs( bufferMs );
					// msEnd = endTime.getTime();

					// msDelta = msEnd - msWave;
				}

				// x1 = 999; // signal_image.getWidth(null) - msDelta *
				// pixelsPerMs
				// - 100;

			} else {

				// clear screen on startup or out-of-order packets
				if (waveStartMs == 0 || waveStartMs > lastStartMs) {
					// _slidePixels(values.length);
				}

				lastStartMs = waveStartMs;

				// x1 = w - values.length;

			}

			drawTimeInMillis = System.currentTimeMillis();

			// cal.add( Calendar.MILLISECOND, 500);
			// endTimeInMillis = cal.getTimeInMillis() + (int)deltaMs +
			// FUDGE_MS; //
			// now...an initial value
			Graphics2D g = (Graphics2D) signal_image.getGraphics();

			AffineTransform trans = setup.getTrans(visibleMs, w, h);
			g.setTransform(trans);

			int effw = (int) (w / trans.getScaleX());
			log.info(" --> (w,h)=({},{}) scaleX={}  effw={}", w, h, trans.getScaleX(), effw );

			// this avoids a div-by-zero error further down when modulus is
			// taken
			if (effw < 10)
				effw = 10;

			g.setColor(penColor);
			if (stroke != null) {
				g.setStroke(stroke);
			}

			//
			// draw a line backward...to previous end of draw
			//
			// this still isn't perfect...i guess due to endcaps and rounding,
			// but it's better. Draw in another color if you really want to
			// see the effect.
			int x1 = setup.getInitialX();
			double y1 = setup.getInitialY();

			// g.drawLine((int) x1, (int) y1, (int) x2, (int) y2);
			int x2 = x1;
			double y2 = y1;

			if (ivals != null) {
				for (double d : ivals) {
					if (x1 >= effw) {
						x1 %= effw;
					}

					x2 = x1 + 1;
					y2 = d; // * mag + offset;

					g.drawLine((int) x1, (int) y1, (int) x2, (int) y2);
					x1 = x2;
					y1 = y2;
					// System.out.print(" " + (int)y2);

					setup.addAutoscaleData(h, d);
				}
			}
			if (fvals != null) {
				for (double d : fvals) {
					if (x1 >= effw) {
						x1 %= effw;
					}

					x2 = x1 + 1;
					y2 = d; // * mag + offset;

					g.drawLine((int) x1, (int) y1, (int) x2, (int) y2);
					x1 = x2;
					y1 = y2;
					// System.out.print(" " + (int)y2);

					setup.addAutoscaleData(h, d);
				}
			}
			if (dvals != null) {
				for (double d : dvals) {
					if (x1 >= effw) {
						x1 %= effw;
					}

					x2 = x1 + 1;
					y2 = d; // * mag + offset;

					g.drawLine((int) x1, (int) y1, (int) x2, (int) y2);
					x1 = x2;
					y1 = y2;
					// System.out.print(" " + (int)y2);

					setup.addAutoscaleData(h, d);
				}
			}

			setup.setInitialX(x2);
			setup.setInitialY(y2);

			g.setTransform(identity);

			g.setColor(EMPTY_BACKGROUND_COLOR_1); // Color.BLACK );  // magenta for debug
			int mx1 = (int) (x1 * trans.getScaleX());
			int mx2 = (int) (val_len * trans.getScaleX());
			g.fillRect(mx1 + 1, 0, mx2 + 1, h);
			if (mx1 + mx2 > w) {
				g.fillRect(0, 0, mx2 + 1, h);
			}

			g.dispose();

			if (trans != null) {
				// trans can be nulled by autoscale
				Point2D ptSrc = new Point2D.Double(x1, -1);
				Point2D ptDst = new Point2D.Double();
				trans.transform(ptSrc, ptDst);

				// FIXME: graph is jumping
				//				if (ptDst.getX() > last_draw_pos) {
				//					last_draw_pos = (int) ptDst.getX(); // HERE! LAST DRAW ASSIGN
				//					if (verbose_debug > 0) {
				//						System.out.println("** write1: " + last_draw_pos);
				//					}
				//				}
				// FIXME: works, but make the graph jumpy
				int prev_last_draw_pos = last_draw_pos;
				last_draw_pos = (int) ptDst.getX();
				log.info(" --> {} jumpy last draw ={} was {}", wfitem.getCode(), last_draw_pos, prev_last_draw_pos);

				have_data = true;
			}

			if (redrawMode != StripRedrawMode.REALTIME) {

				do_repaint = true;
			}

		}

		if (do_repaint) {
			repaint();
		}
	}

	private void drawAxisLabels(Graphics2D g) {
		g.setColor(Color.WHITE);
		int x = 10;
		int h = getHeight();
		int w = getWidth();

		for (StripSetup ssetup : setups) {
			double min = ssetup.getScaleMin();
			double max = ssetup.getScaleMax();
			boolean show_curr_val = ssetup.showCurrentValue();

			RpMetric desc = ssetup.getDescription();
			RpUnit unit = null;
			if (desc != null) {
				unit = desc.getUnit();
			}
			if (unit != null) {
				max = UnitUtil.getValue(unit, max);
				min = UnitUtil.getValue(unit, min);
			}
			double delta = Math.abs(max - min);

			NumberFormat format = df0;
			if (delta < 1.0e-6) {
				format = df_sci;
			} else if (delta < 1.0e-3) {
				format = df6;
			} else if (delta < 1.0e-1) {
				format = df3;
			} else if (delta < 100) {
				format = df1;
			} else {
				format = df0;
			}
			g.drawString(format.format(max), x, h - 6);
			g.drawString(format.format(min), x, 20);

			if (show_curr_val) {
				double map = ssetup.getCurrentValue();
				double dia = ssetup.getDiaValue();
				double sys = ssetup.getSysValue();
				g.drawString(format.format(map) + " (" + format.format(sys) + "," + format.format(dia) + ")", w - x
						- 120, h - 6);
			} else {

				double freq = ssetup.getFreq();
				g.drawString("" + (int) freq, w - x - 30, h - 6);
			}

			if (setups.size() > 1) {
				g.drawString(ssetup.getCode(), x, h / 2);
			} else {
				String code = "??";
				if (desc != null) {
					code = desc.getCode();
				}
				String unitName = "??";
				if (unit != null) {
					unitName = unit.getUnitName();
				}
				g.drawString(code + " (" + unitName + ")", x + 50, 20);
			}

			x += 30;
		}

	}

	public void addRWave(int rPos) {
		synchronized (signal_image) {
			int h = signal_image.getHeight(null);

			// int x = 0;
			// if (redrawMode == StripRedrawMode.REALTIME) {
			// x = (int) (lastDrawnX + rPos); // pixelTime * rPos);
			// } else {
			// int w = signal_image.getWidth(null);
			// x = (int) (w + rPos); // pixelTime * rPos);
			// }

			// Graphics2D g = (Graphics2D) signal_image.getGraphics();
			// g.setColor(Color.BLUE);
			// g.drawLine((int) x, 0, (int) x, h);
			// g.dispose();
		}
	}

	public void copyImageToClipboard() {
		// Work around a Sun bug that causes a hang in
		// "sun.awt.image.ImageRepresentation.reconstruct".

		System.err.println("I really want to copy the displayed image, not the signal image");
		ImageSelection.copyImageToClipboard(signal_image);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seejava.awt.event.ComponentListener#componentHidden(java.awt.event.
	 * ComponentEvent)
	 * 
	 * When the image is resized, reallocate space for the hidden image
	 */
	@Override
	public void componentHidden(ComponentEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void componentMoved(ComponentEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void componentResized(ComponentEvent e) {
		checkImage();
		repaint();
	}

	@Override
	public void componentShown(ComponentEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void autoScale(String loc) {
		int h = signal_image.getHeight(null);

		for (StripSetup setup : setups) {
			if (loc == null || loc.equals(setup.getLoc())) {
				setup.autoScale(h);
			}
		}
		// fireScaleChange(as_min, as_max);
	}

	public void addWaveformDescription(RpMetric desc, Color color, double scaleValue1, double scaleValue2,
			boolean autoscale) {
		assert (desc != null) : "cannot add null waveform description to cardiostrip";

		double sample_rate = 1;
		if (desc != null) {
			sample_rate = desc.getSampleRate() / 2;
		}

		StripSetup setup = new StripSetup(desc, color, sample_rate, scaleValue1, scaleValue2);
		setup.enableAutoscale(autoscale);
		setups.add(setup);
		_createWavesArray();

		log.debug("ADD WF: {}", desc);
		log.debug("ADD WF: --> SCALE1=={}  SCALE2==", scaleValue1, scaleValue2);
	}

	private void _createWavesArray() {
		RpMetric[] arr = new RpMetric[setups.size()];
		int idx = 0;
		for (StripSetup s : setups) {
			arr[idx++] = s.getDescription();
		}

		waves = arr;
	}

	public RpMetric[] getWaveforms() {
		return waves;
	}

	public void clear() {

		log.debug("clear");

		if (signal_image == null) {
			return;
		}

		if (isClear == true) {
			return;
		}
		Dimension dim = getSize();

		synchronized (signal_image) {
			Graphics2D graphics = (Graphics2D) signal_image.getGraphics();

			/*
			 * graphics.setColor(Color.RED); graphics.drawLine(2, 0, w-2, 0);
			 * graphics.drawLine(0, 0, 100, 100); graphics.drawLine(w-1, 0,
			 * w-200, 200);
			 */
			graphics.setColor(EMPTY_BACKGROUND_COLOR_4);
			graphics.fillRect(0, 0, (int) (2 * dim.getWidth()), (int) dim.getHeight());

			graphics.dispose();

			isClear = true;
		}
	}

	// public Double getScaleMinY() {
	// return scale_min_y;
	// }
	//
	// public void setYScale(Double scale_min_y, Double scale_max_y) {
	// this.scale_min_y = scale_min_y;
	// this.scale_max_y = scale_max_y;
	// }
	//
	// public Double getScaleMaxY() {
	// return scale_max_y;
	// }

	public void refresh(long msNow) {

		repaint();

		/*
		 * Image image = signal_image;
		 * 
		 * if (image != null) {
		 * 
		 * Graphics2D g2 = (Graphics2D) image.getGraphics(); drawFinalImage(g2);
		 * 
		 * if (image != null) { Rectangle rect = new Rectangle(); if
		 * (scrollerMode == StripScrollerMode.SCROLLING) { repaint(); } else {
		 * rect.x = first_draw_pos; rect.y = 0; rect.width = last_draw_pos -
		 * first_draw_pos; rect.height = image.getHeight(null); first_draw_pos =
		 * last_draw_pos; System.out.println("redraw rect=" + rect);
		 * repaint(rect); } }
		 * 
		 * g2.dispose();
		 */

	}

	private void drawFinalImage(Graphics2D g2) {

		switch (scrollerMode) {
		case RAW:
			log.debug("fillImage: RAW");
			// image = signal_image;
			g2.drawImage(signal_image, // source image
					0, 0, null);
			break;
		case CURSOR:
			log.debug("fillImage: draw CURSOR");
			drawCursorImage(g2);
			break;
		case SCROLLING:
			synchronized (signal_image) {
				drawScrollingImage(g2);
			}
			break;
		}

	}

	private void drawScrollingImage(Graphics2D g2) {
		long msDelta = System.currentTimeMillis() - drawTimeInMillis;
		double frac = msDelta / PACKET_MS;
		int ptDelta = (int) (PACKET_PTS * frac);

		int w = getWidth();
		int h = getHeight();
		

		int data_pos = last_draw_pos + ptDelta - CURSOR_PTS;

		if (data_pos > 2 * w) {
			log.info("off the end?");
			clear();
			last_draw_pos = ptDelta; // HERE! WRITE number 2
			//System.out.println("** write2: " + last_draw_pos);
			data_pos = 0;
		}

		log.info("* draw frac={} ptDelta={} w={} h={}", frac, ptDelta, w, h);
		log.info("  + msDelta={} drawTimeInMillis={}", msDelta, drawTimeInMillis);

		// draw most recent data
		int dest_x = w - data_pos;
		int src_x = 0;
		int draw_w = data_pos;
		if (data_pos > w) {
			dest_x = 0;
			src_x = data_pos - w;
			draw_w = w;
		}

		if (verbose_debug > 0) {
			System.out.print(" drawA xsrc,w to dest,w:");
			System.out.print(" [" + data_pos + "," + w);
			System.out.print(" [" + src_x + "," + draw_w);
			System.out.println();
		}

		g2.drawImage(signal_image, // source image
				dest_x, 0, w, h, // dest x,y,x2,y2
				src_x, 0, src_x + draw_w, h, // source x,y,x2,y2
				null);

		if (dest_x > 0) { // we skipped the front of the image, now draw it.
			// log.debug("    B xsrc-dest w: {} 0 {}", 2 * w - dest_x, dest_x);
			g2.drawImage(signal_image, // source image
					0, 0, dest_x, h, // dest x,y,x2,y2
					2 * w - dest_x, 0, 2 * w, h, // source x,y,x2,y2
					null);
		}

	}

	private void drawCursorImage(Graphics2D g2) {

		int w = getWidth();
		int h = getHeight();

		if (last_draw_pos > w) {

			// first half of box2
			g2.drawImage(signal_image, // source image
					0, 0, last_draw_pos - w, h, // dest x,y,x2,y2
					w, 0, last_draw_pos, h, // source x,y,x2,y2
					null);

			// second half of box1
			g2.drawImage(signal_image, // source image
					last_draw_pos - w, 0, w, h, // dest x,y,x2,y2
					last_draw_pos - w, 0, w, h, // source x,y,x2,y2
					null);

		} else {

			// first half of box1
			g2.drawImage(signal_image, // source image
					0, 0, last_draw_pos, h, // dest x,y,x2,y2
					0, 0, last_draw_pos, h, // source x,y,x2,y2
					null);

			// second half of box2
			g2.drawImage(signal_image, // source image
					last_draw_pos, 0, w, h, // dest x,y,x2,y2
					w + last_draw_pos, 0, w + w, h, // source x,y,x2,y2
					null);

		}

		drawCursor(g2, w, h);
	}

	private void drawCursor(Graphics2D g2, int im_width, int im_height) {
		int pos = last_draw_pos;
		if (pos > im_width) {
			pos = last_draw_pos - im_width;
		}

		long msDelta = System.currentTimeMillis() - drawTimeInMillis;
		double frac = msDelta / PACKET_MS;
		int ptDelta = (int) (PACKET_PTS * frac);

		log.debug("cursor msDelta={},{} frac=" + frac, msDelta, ptDelta);

		g2.setColor(Color.PINK); // FIXME: obvious a DEBUG color
		int cursor_start = pos - CURSOR_PTS + ptDelta;
		g2.fillRect(cursor_start, 0, CURSOR_PTS, im_height);
		if (cursor_start + CURSOR_PTS > im_width) {
			g2.fillRect(cursor_start - im_width, 0, CURSOR_PTS, im_height);
		}

	}

	public void reset() {
		synchronized (setups) {
			while (setups.size() > 0) {
				setups.remove(0);
			}
			_createWavesArray();
		}

	}

	public void enableAutoscale(boolean b) {

		for (StripSetup setup : setups) {
			setup.enableAutoscale(b);
		}

	}

	public void setSweepSpeed(int sweepSpeed) {
		if (sweepSpeed == 0) {
			setRedrawMode(StripRedrawMode.NONE);
		} else {
			setRedrawMode(StripRedrawMode.REALTIME);
		}
	}

	public StripSetup[] getSetups() {
		StripSetup[] arr = new StripSetup[setups.size()];
		setups.toArray(arr);
		return arr;
	}

}
