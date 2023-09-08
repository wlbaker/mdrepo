package idea.display.gl;

import com.jogamp.opengl.GL;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GL2ES1;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.fixedfunc.GLMatrixFunc;

import idea.model.DisplayConfig;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class GLInstrumentPainter implements GLEventListener {

	private static final int PARAM_ROW_HEIGHT = 75;
	private int PARAMETER_COL_WIDTH = 150;
	private int last_width;
	private int last_height;
	private boolean force_reshape = false;

	/*
	 * internal variables to measure performance
	 */
	private int fps; // frames per second
	private long last_secs;
	private int hparamAreaHeight;

	@Override
	public void init(GLAutoDrawable drawable) {
		GLInstrumentDisplay instrument = (GLInstrumentDisplay) drawable;

		GLBandPainter[] bands = instrument.getBandPainters();
		if (bands == null) {
			return;
		}
		for (GLBandPainter sig : bands) {
			if (sig == null) {
				log.error("unexpected null signal");
			} else {
				sig.init(instrument);
			}
		}

		GLParameterPainter[] params = instrument.getParameters();
		if (params != null) {
			for (GLParameterPainter p : params) {
				p.init(instrument);
			}
		}

		int iWidth = drawable.getSurfaceWidth();
		int iHeight = drawable.getSurfaceHeight();

		reshape(drawable, 0, 0, iWidth, iHeight);
		/*
		 * int iWidth = drawable.getWidth(); int iHeight = drawable.getHeight(); int h = iHeight / N_BANDS;
		 * 
		 * sigs[0].setXYWH( 0, iHeight - h, iWidth - PARAMETERS_WIDTH, h ); sigs[1].setXYWH( 0, iHeight - 2*h, iWidth -
		 * PARAMETERS_WIDTH, h );
		 */

		GL2 gl = drawable.getGL().getGL2();

		gl.setSwapInterval(1);
		// gl.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// gl.glClearDepth(1.0);
		gl.glHint(GL2ES1.GL_PERSPECTIVE_CORRECTION_HINT, GL.GL_NICEST);

		// antialiasing
		gl.glEnable(GL.GL_LINE_SMOOTH);
		gl.glHint(GL.GL_LINE_SMOOTH_HINT, GL.GL_NICEST);
		gl.glEnable(GL2ES1.GL_POINT_SMOOTH);
		gl.glHint(GL2ES1.GL_POINT_SMOOTH_HINT, GL.GL_NICEST);
		gl.glEnable(GL.GL_BLEND);
		gl.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA);

	}

	@Override
	public void dispose(GLAutoDrawable drawable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void display(GLAutoDrawable drawable) {

		int iWidth = drawable.getSurfaceWidth();
		int iHeight = drawable.getSurfaceHeight();

		if( force_reshape ) {
			//last_width = width;
			//last_height = height;
			reshape(drawable, 0, 0, last_width, last_height);  // TESTING THIS FEATURE
		}

		GL2 gl = drawable.getGL().getGL2();
		gl.glClear(GL.GL_COLOR_BUFFER_BIT);

		gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
		gl.glPushMatrix();
		gl.glLoadIdentity();
		gl.glMatrixMode(GLMatrixFunc.GL_MODELVIEW);
		gl.glPushMatrix();
		gl.glViewport(0, 0, iWidth, iHeight);
		gl.glLoadIdentity();

		GLInstrumentDisplay instrument = (GLInstrumentDisplay) drawable;
		GLBandPainter[] bands = instrument.getBandPainters();
		GLParameterPainter[] params = instrument.getParameters();

		fps++;
		if (instrument.isRealtime()) {
			instrument.setTime((int) (System.currentTimeMillis() - instrument.getTime0()));

			long secs = System.currentTimeMillis() / 1000;
			if (secs != last_secs) {
				instrument.setFPS(fps);
				last_secs = secs;
				fps = 0;
			}
		}

		// attempt antialiasing...I guess I'm going to have to read the manuals

		// gl.glDepthMask( false );
		gl.glPushAttrib(GL2.GL_ALL_ATTRIB_BITS);
		// gl.glEnable(GL.GL_POLYGON_OFFSET_FILL);
		// gl.glPolygonOffset(1.0f, 1.0f);
		gl.glEnable(GL2.GL_BLEND);
		gl.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA);
		gl.glEnable(GL.GL_LINE_SMOOTH);
		gl.glHint(GL2.GL_LINE_SMOOTH_HINT, GL2.GL_NICEST);

		for (GLBandPainter band : bands) {
			band.display(instrument);
		}

		for (GLParameterPainter param : params) {
			param.display(instrument);
		}
		// gl.glDisable(GL.GL_POLYGON_OFFSET_FILL);
		gl.glPopAttrib();

		/*
		 * 
		 */

		gl.glLineWidth(1);

		gl.glPushAttrib(GL2.GL_ENABLE_BIT);
		gl.glLineStipple(1, (short) 0xAAAA);
		gl.glEnable(GL2.GL_LINE_STIPPLE);

		/*
		 * show band dividing lines
		 */
		gl.glTranslatef(-1, -1, 0f); // move the 0,0 to the lower right corner
		gl.glScalef(2f / iWidth, 2f / iHeight, 1f);
		for (GLBandPainter band : bands) {
			if (band.isVisible()) {
				gl.glBegin(GL.GL_LINES);
				gl.glColor3f(0.4f, 0.4f, 0.4f);
				gl.glVertex2f(1f, band.getY());
				gl.glVertex2f(iWidth, band.getY());
				gl.glEnd();
			}
		}

		/*
		 * show parameter dividing lines
		 */
		gl.glColor3f(0.4f, 0.4f, 0.4f);
		for (GLParameterPainter param : params) {
			gl.glBegin(GL.GL_LINES);

			// segments are discontinuous: each line segment has to have two
			// points.

			// right
			gl.glVertex2f(param.getX(), param.getY() + param.getHeight());
			gl.glVertex2f(param.getX(), param.getY());

			// bottom
			gl.glVertex2f(param.getX(), param.getY());
			gl.glVertex2f(param.getX() + param.getWidth(), param.getY());

			// left
			gl.glVertex2f(param.getX() + param.getWidth(), param.getY());
			gl.glVertex2f(param.getX() + param.getWidth(), param.getY() + param.getHeight());

			gl.glEnd();
		}
		gl.glPopAttrib(); // pop stipple attribute

		/*
		 * show pbox selection
		 */
		gl.glLineWidth(3);
		gl.glColor3f(0.4f, 0.4f, 1.0f);
		for (GLParameterPainter param : params) {
			if (!param.isSelected()) {
				continue;
			}
			gl.glBegin(GL.GL_LINES);

			// segments are discontinuous: each line segment has to have two
			// points.

			// right
			gl.glVertex2f(param.getX(), param.getY() + param.getHeight());
			gl.glVertex2f(param.getX(), param.getY());

			// bottom
			gl.glVertex2f(param.getX(), param.getY());
			gl.glVertex2f(param.getX() + param.getWidth(), param.getY());

			// left
			gl.glVertex2f(param.getX() + param.getWidth(), param.getY());
			gl.glVertex2f(param.getX() + param.getWidth(), param.getY() + param.getHeight());

			// top
			gl.glVertex2f(param.getX() + param.getWidth(), param.getY() + param.getHeight());
			gl.glVertex2f(param.getX(), param.getY() + param.getHeight());

			gl.glEnd();
		}

		gl.glPopMatrix();
		gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
		gl.glPopMatrix();

	}

	@Override
	public void reshape(GLAutoDrawable drawable, int canv_x, int canv_y, int width, int height) {
		// FIXME: this routine is called too often due to overlapping swing widgets...optimize
		if (force_reshape) {
			// dont ignore the reshape
		} else if (width == last_width && height == last_height) {
			// bogus reshape
			return;
		}
		last_width = width;
		last_height = height;
		force_reshape = false;

		GLInstrumentDisplay instrument = (GLInstrumentDisplay) drawable;
		GLBandPainter[] bands = instrument.getBandPainters();
		GLParameterPainter[] params = instrument.getParameters();

		/*
		 * get total band weight...used to determine relative height of individual bands
		 */
		int tot_bandWeight = 0;
		if (bands != null) {
			for (GLBandPainter band : bands) {
				tot_bandWeight += band.getWeight();
			}
		}

		/*
		 * get number of vertical param columns
		 */
		int numVertPCols = 0;
		if (tot_bandWeight > 0) {
			DisplayConfig display = instrument.getDisplay();
			if (display != null) {
				numVertPCols = display.getVertPboxes() / tot_bandWeight;
			}
		}

		int iWidth = drawable.getSurfaceWidth();
		int iHeight = drawable.getSurfaceHeight();

		int n_param_rows = getNumParamRows(params.length, iWidth, tot_bandWeight, numVertPCols);
		hparamAreaHeight = n_param_rows * PARAM_ROW_HEIGHT;

		int band_y = iHeight;
		int param_idx = 0;

		if (tot_bandWeight == 0) {
			log.warn("[reshape] No display bands.");
		} else {
			iHeight -= hparamAreaHeight;
			band_y = iHeight;
			int h = iHeight / tot_bandWeight;

			int paramAreaWidth = PARAMETER_COL_WIDTH * numVertPCols;

			int cumulWeight = 0;
			for (int band_idx = 0; band_idx < bands.length; band_idx++) {
				GLBandPainter band = bands[band_idx];
				int bandWeight = band.getWeight(); // getOverlaps(bands, band_idx);
				cumulWeight += bandWeight;

				band.setVisible(bandWeight > 0);
				if (bandWeight > 0) {
					band_y = iHeight - (cumulWeight) * h + hparamAreaHeight;
					band.setXYWH(0, band_y, iWidth - paramAreaWidth, bandWeight * h);
				}
			}

			cumulWeight = 0;
			for (int col = 0; col < numVertPCols; col++) {
				for (int row_idx = 0; row_idx < tot_bandWeight; row_idx++) {
					int param_x = iWidth - (numVertPCols - col ) * PARAMETER_COL_WIDTH;
					int param_y = iHeight - (row_idx + 1) * h + hparamAreaHeight;
					GLParameterPainter param = null;
					if (param_idx < params.length) {
						param = params[param_idx++];
					}
					if (param != null) {
						// these parameters use the variable BAND HEIGHT not the
						// constant PARAM_ROW_HEIGHT
						param.setXYWH(param_x, param_y, PARAMETER_COL_WIDTH, h);
					}
				}
			}
		}

		// remaining params go along the bottom
		int param_y = band_y - PARAM_ROW_HEIGHT;
		int param_x = 0;
		for (; param_idx < params.length; param_idx++) {
			GLParameterPainter param = params[param_idx];
			int param_w = PARAMETER_COL_WIDTH;
			if (param.getFormat() == 81) {
				param_w += PARAMETER_COL_WIDTH;
			}
			param.setXYWH(param_x, param_y, param_w, PARAM_ROW_HEIGHT);
			param_x += param_w;

			if (param_x + param_w > iWidth) {
				param_y -= PARAM_ROW_HEIGHT;
				param_x = 0;
			}
		}
	}

	private int getOverlaps(GLBandPainter[] bands, int band_idx) {
		int n = 0;
		boolean needs_waveforms = true;
		for (; band_idx < bands.length; band_idx++) {
			GLBandPainter band = bands[band_idx];
			if (band.hasWaveforms() != needs_waveforms)
				break;
			n++;
			needs_waveforms = false; // only the first band needs waveforms
		}
		return n;
	}

	private int getNumParamRows(int numParams, int iWidth, int n_bands, int numVertPCols) {
		numParams -= n_bands * numVertPCols;
		if (numParams < 0) {
			return 0;
		}

		int paramsPerRow = iWidth / PARAMETER_COL_WIDTH;
		if (paramsPerRow <= 0) {
			paramsPerRow = 1;
		}

		return (numParams + paramsPerRow - 1) / paramsPerRow;
	}

	public void invalidate() {
		force_reshape = true;
	}

	public int getHParameterAreaHeight() {
		return hparamAreaHeight;
	}

}
