package idea.display.gl;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.text.NumberFormat;
import java.util.Date;
import java.util.List;

import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLContext;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.GLException;
import com.jogamp.opengl.awt.GLCanvas;

import com.jogamp.opengl.util.awt.TextRenderer;

import icuInterface.RpUtil;
import idea.display.BandLayout;
import idea.display.InstrumentDisplayInterface;
import idea.display.ParameterLayout;
import idea.display.WaveformData;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.Annotation;
import idea.model.DisplayConfig;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

class MyFontFixer implements GLEventListener {

	GLInstrumentDisplay d;
	
	public MyFontFixer( GLInstrumentDisplay inst ) {
		d = inst;
	}
	@Override
	public void init(GLAutoDrawable drawable) {
		// when you switch screens, you get an init() call, and the
		// fonts need to be
		// reloaded because they are driven by a screen-specific VBO.
		d.init();

	}

	@Override
	public void dispose(GLAutoDrawable drawable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void display(GLAutoDrawable drawable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
		// TODO Auto-generated method stub

	}
}
@SuppressWarnings("serial")
@Slf4j
public class GLInstrumentDisplay extends GLCanvas implements InstrumentDisplayInterface, StreamConsumer {

	public static final String PROPERTY_FPS = "INSTRUMENT_FPS";
	public static final String PROPERTY_TIME = "INSTRUMENT_TIME";
	public static final String PROPERTY_SELECTED_PARAM = "INSTRUMENT_PARAM";

	private GLInstrumentPainter painter;
	TextRenderer arielBlack;
	TextRenderer monospaced;

	final static Dimension MINSIZE = new Dimension(100, 20);

	GLBandPainter[] bands = new GLBandPainter[0];
	GLParameterPainter[] params = new GLParameterPainter[0];

	/** X distance to translate the viewport by. */
	protected int tm_offset = 0;
	private long tm0;
	private DisplayConfig display;
	private boolean realtime = true;
	private RpDevice conf;
	private GLDisplayShim shim;

	private int fps;
	private int millisWidth;
	private GLParameterPainter activeParam;
	private boolean display_persist;
	private GLEventListener fontFixer;

	public GLInstrumentDisplay() {
		this(null, null);
	}

	public GLInstrumentDisplay(RpDevice conf) {
		this.conf = conf;

		this.addGLEventListener( fontFixer = new MyFontFixer(this) );

		this.addMouseListener(new MouseAdapter() {

			@Override
			public void mousePressed(MouseEvent e) {
				int x = e.getX();
				int y = e.getY();
				int h = getHeight();

				y = h - y; // mouse and OGL coordinates are inverted
				for (GLParameterPainter param : params) {
					if (param.isHit(x, y)) {
						setActiveParameter(param);
						break;
					}
				}
			}

		});

		this.addMouseWheelListener(new MouseWheelListener() {

			@Override
			public void mouseWheelMoved(MouseWheelEvent e) {
				if (!isRealtime()) {
					int notches = e.getWheelRotation();
					setTime(getTTime() + 1000 * notches);
				}

			}
		});

		tm0 = System.currentTimeMillis();

		this.setWidthInMillis(15000);
	}

	public GLInstrumentDisplay(StreamProducer driver, DisplayConfig display) {
		this( driver.getConfiguration() );
		
		this.setDisplay( display , true, true);
		
		driver.addStreamListener( null, this);
	}

	public void clearSelection() {
		setActiveParameter( null );
	}
	
	protected void setActiveParameter(GLParameterPainter param) {
		GLParameterPainter old = activeParam;
		activeParam = param;
		firePropertyChange(PROPERTY_SELECTED_PARAM, //
				(old == null) ? null : old.getBox(), //
				(param == null) ? null : param.getBox());
	}

	public void init() {
		painter = new GLInstrumentPainter();
		setMinimumSize(MINSIZE);
		setShallUseOffscreenLayer(true);
		addGLEventListener(painter);

		// sanSerif = new TextRenderer(new Font("SansSerif", Font.BOLD, 36));
		arielBlack = new TextRenderer(new Font("Ariel Black", Font.BOLD, 36));
		monospaced = new TextRenderer(new Font("Dialog", Font.PLAIN, 12));

		setDisplay(display, true, display_persist );
	}

	public void setTime0(long tm0) {
		this.tm0 = tm0;
	}

	public int getTTime() {
		return tm_offset;
	}

	public void setTime(int new_offset) {

		if (realtime == false) {
			Date old_dt = new Date(tm0 + tm_offset);
			Date new_dt = new Date(tm0 + new_offset);
			firePropertyChange(PROPERTY_TIME, old_dt, new_dt);
		}

		tm_offset = new_offset;
		repaint();
	}

	public void setWidthInMillis(int millis) {
		this.millisWidth = millis;
		for (GLBandPainter sig : bands) {
			sig.setWidthInMillis(millis);
		}

		repaint(); // if we are not realtime, trigger a redraw
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		try {
			_streamEvent( jobID, source, sid, item);
		} catch( RuntimeException r ) {
			log.error("Lock timeout? initting: {}", r.getMessage());
			this.init();
		}
	}
	
	public void _streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (sid == StreamID.WAVEFORM) {
			waveformEvent(source, item);
		} else if (sid == StreamID.MEASUREMENT) {
			numericsEvent(source, item); // same code...but allows breakpoint
		} else if (sid == StreamID.ANNOTATION) {
			annotationEvent(source, (Annotation) item);
		} else if (sid == StreamID.CAPABILITIES) {
			// this.conf = item;
			log.error("CHANGE CONF TO REFLECT CAPABILITIES...there is a routine to do this somewhere");

		} else if (sid == StreamID.DISPLAY) {

			DisplayConfig disp = (DisplayConfig) item;
			setDisplay(disp, true, false );

		} else if (sid == StreamID.CONNECTION) {
			System.err.println("GLINSTRUMENT CONNECTION=" + item );
		} else {
			log.error("Unhandled event: {}/{}", sid, item);
		}
	}

	private void annotationEvent(StreamProducer source, Annotation anno) {

		GLContext context = getContext();
		if (context == null) {
			log.error("null context");
			return;
		}

		context.makeCurrent();

		GLBandPainter band = bands[0];
		long tm = anno.getTime();
		band.addAnnotation(this, (int) (tm - tm0), anno, anno.getMessage());
		repaint();
		try {
			context.release();
		} catch (GLException glx) {
			glx.printStackTrace();
		}
	}

	public void setDisplay(DisplayConfig display, boolean overwrite, boolean ignoreupdates ) {

		if (display == null) {
			return;
		}
		
		System.err.println("set display: " + getName() + " count=" + display.getNumBands() + " hash=" + this.hashCode());
		
		if( overwrite == false && this.display != null ) {
			return;  // dont overwrite an existing display
		}

		if( ignoreupdates == false && display_persist == true ) {
			// this is not a persistent display, but we currently have a persistent display
			// so ignore
			return;  
		}

		this.display_persist = ignoreupdates;
		this.display = display;

		if (painter == null) {
			// dont try to layout the display until after the GL init
			return;
		}

		List<BandLayout> config_bands = display.getBands();

		if (config_bands == null) {
			log.warn("SET DISPLAY no bands");
		} else {
			GLBandPainter [] temp_bands = new GLBandPainter[config_bands.size()];
			int idx = 0;
			for (BandLayout band : config_bands) {
				GLBandPainter bandPainter = new GLBandPainter(band);
				temp_bands[idx++] = bandPainter;

				bandPainter.reset();
				List<WaveformData> waves = band.getWaves();
				if (waves != null) {
					for (WaveformData wave : waves) {
						bandPainter.addWaveformDescription(wave, null);
					}
				}
			}
			bands = temp_bands;  // anatomic to avoid locking in painter
		}

		RpStream stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
		if (display.getNumPBoxes() > 0) {
			GLParameterPainter[] temp_params = new GLParameterPainter[display.getNumPBoxes()];
			int idx = 0;
			for (ParameterLayout box : display.getParameterBoxs()) {
				GLParameterPainter paramPainter = new GLParameterPainter(box, stream);
				temp_params[idx++] = paramPainter;

			}
			params = temp_params;  // anatomic to avoid locking in painter
		}

		painter.invalidate(); // forces a new layout on next request
		this.invalidate();

		this.setWidthInMillis(millisWidth);
	}

	protected GLBandPainter findBand(String loc) {
		GLBandPainter sig_found = null;

		for (GLBandPainter sig : bands) {
			if (sig == null) {
				log.error("null sig!");
			} else {
				Object setup = sig.getSetup(loc);
				if (setup != null) {

					sig_found = sig;
					break;
				}
			}
		}
		return sig_found;
	}

	public GLParameterPainter findParameterPainter(String loc) {

		if (params == null) {
			return null;
		}

		GLParameterPainter p_found = null;

		for (GLParameterPainter p : params) {
			if (p == null) {
				log.error("null param!");
			} else {
				if (p.containsLoc(loc)) {

					p_found = p;
					break;
				}
			}
		}

		return p_found;
	}

	protected void waveformEvent(Object sss, PersistentItem item) {

		if (item == null) {
			log.warn("null waveform block");
			return;
		}
		if (bands == null) {
			log.warn("no bands displayed");
			return;
		}
		RpMetric[] waveforms = IntfUtil.getMetrics(item);
		if (waveforms == null) {
			log.error("NO WAVEFORMS IN EVENT");
			return;
		}

		GLContext context = getContext();
		if (context == null) {
			log.error("null context");
			return;
		}

		int rc = context.makeCurrent();
		if( rc == GLContext.CONTEXT_NOT_CURRENT) {
			log.warn("Context not current, ignoring waveform event.");
			return;
		}

		long tm = item.getTime();
		// boolean do_repaint = false;
		for (int idx = 0; idx < waveforms.length; idx++) {

			RpMetric wf = waveforms[idx];

			for (GLBandPainter sig : bands) {
				if (sig == null) {
					log.error("null sig!");
				} else {
					WaveformSetupDataEx setup = sig.getSetup(wf.getLocation());
					if (setup != null) {
						sig.addWaveformData(this, (int) (tm - tm0), item, wf);
						// do_repaint = true;
					}
				}
			}
		}
		try {
			context.release();
		} catch (GLException glx) {
			glx.printStackTrace();
		}
		// if (do_repaint) {
		// repaint();
		// }
	}

	synchronized protected void numericsEvent(Object sss, PersistentItem block) {
		if (block == null) {
			log.warn("null numerics block");
			return;
		}
		RpMetric[] items = IntfUtil.getMetrics(block);
		if (items == null) {
			log.error("NO NUMERICS IN EVENT");
			return;
		}
		
		for (int idx = 0; idx < items.length; idx++) {

			RpMetric m = items[idx];
			Object o = IntfUtil.getScaledValue(block, m);
			String loc = m.getLocation();

			GLParameterPainter box = findParameterPainter(loc);
			if (box == null) {

				log.debug("NO PARAM: {}", m.getName());
			} else {
				if (o == null) {
					// pass as-is
				}
				if (o instanceof Number) {
					NumberFormat default_nf = NumberFormat.getInstance();
					o = default_nf.format((Number) o);
				}
				box.setValue(m.getLocation(), (String) o);
			}

		}

	}

	public GLBandPainter[] getBandPainters() {
		return bands;
	}

	public GLParameterPainter[] getParameters() {
		return params;
	}

	public long getTime0() {
		return tm0;
	}

	public void clear() {

		if (bands == null) {
			return; // nothing to clear
		}

		for (GLBandPainter sig : bands) {
			sig.clear();
		}
	}

	public float[] getDisplayData(String loc, float[] arr) {

		GLContext context = getContext();
		if (context == null) {
			log.error("null context");
			return null;
		}

		context.makeCurrent();

		GLBandPainter sig = findBand(loc);
		if (sig != null) {
			arr = sig.getDisplayData(this, loc, arr);
		}
		try {
			context.release();
		} catch (GLException glx) {
			glx.printStackTrace();
		}
		return arr;
	}

	public boolean isRealtime() {
		return realtime;
	}

	public void setRealtime(boolean realtime) {
		this.realtime = realtime;

		setTime(tm_offset); // no time change, but triggers a property fire with time
	}

	public DisplayConfig getDisplay() {
		return display;
	}

	public RpDevice getCapabilities() {
		return conf;
	}

	public void setDisplayShim(GLDisplayShim shim) {
		this.shim = shim;
	}

	@Override
	public void display() {
		super.display();

		if (shim != null) {
			shim.microTick();
			repaint();  // if the shim is there, then we need to trigger the repaint loop
		}
	}

	public void pause() {
		setRealtime(false);
	}

	public void resume() {
		setRealtime(true);
		repaint();
	}

	public boolean isPaused() {
		return !isRealtime();
	}

	public void setFPS(int fps) {
		firePropertyChange(PROPERTY_FPS, this.fps, fps);
		this.fps = fps;
	}

	public int getFPS() {
		return fps;
	}

	public int getHParamAreaHeight() {
		if (painter == null) {
			return 0;
		}
		return painter.getHParameterAreaHeight();
	}

	public int getPDXCount(int i) {
		return params[i].fields.size();
	}

	public ParamDataEx getPDX(int i, int field_idx) {
		return params[i].fields.get(field_idx);
	}


}
