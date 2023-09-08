package idea.display.gl;

import java.awt.Color;
import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.text.DecimalFormat;
import java.util.Calendar;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import com.jogamp.opengl.GL;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GL2GL3;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.fixedfunc.GLMatrixFunc;
import com.jogamp.opengl.fixedfunc.GLPointerFunc;
import com.jogamp.opengl.glu.GLU;

import com.jogamp.common.nio.Buffers;

import idea.display.BandLayout;
import idea.display.WaveformData;
import idea.intf.DataTyp;
import idea.model.Annotation;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;

class TimedNote {
	float tm;
	String message;
}

@Slf4j
public class GLBandPainter implements GLEventListener {

	private static final int SIZEOF_COORD = 4;
	private final static int VBO_VERTEX_COUNT = 100000;
	private final static int COORD_TYPE = GL2.GL_FLOAT;
	private final static int COORDS_PER_VERTEX = 2;

	private static DecimalFormat df0 = new DecimalFormat("#,##0");

	/**
	 * Ratio of world-space units to screen pixels. Increasing this zooms the
	 * display out, decreasing it zooms the display in.
	 */
	protected double width_in_msec = 15000;

	int[] insert_vertex_pos;
	boolean method_2 = false;

	private boolean overflow = false;

	private int y_t0;
	private float[] y_last;
	GLU glu = new GLU();

	private int[] vbos;
	private List<WaveformSetupDataEx> setups = new LinkedList<WaveformSetupDataEx>();
	private List<TimedNote> annos = new LinkedList<TimedNote>();

	/*
	 * viewport
	 */
	private int x;
	private int y;
	private int w;
	private int h;
	private int weight;
	private boolean visible;
	private boolean did_missing_error;

	public GLBandPainter(BandLayout band) {

		weight = band.getWeight();
		if( weight == 0 ) {
			weight = band.getWaveCount();
		}
		if (band.getWaveCount() > 0) {
			for (WaveformData wave : band.getWaves()) {
				System.out.println("FIXME: gl_painter ignoring wave.getWaveColor: " + wave.getWaveColor());
				addWaveformDescription(wave, null);
			}
		}

	}

	@Override
	public void init(GLAutoDrawable drawable) {

		// this routine gets called if you drag from one monitor to another
		// ...even on the same graphics card
		// ...the VBO's become invalid

		// GLInstrumentDisplay sig = (GLInstrumentDisplay) drawable;
		GL gl = drawable.getGL();
		if (vbos != null) {
			log.error("deleting buffers: " + vbos);

			gl.glDeleteBuffers(vbos.length, vbos, 0);

			vbos = null;
		}
		
		did_missing_error = false;
	}

	public void addWaveformData(GLInstrumentDisplay instrument, int tm, PersistentItem parent, RpMetric desc) {
		int t0 = tm;
		float dt = 5;
		if (desc != null) {
			int r = desc.getSampleRate();
			if (r != 0) {
				dt = 1000.0f / r;
			}
		}

		float[] y_data = null;

		int subtyp = desc.getSubtyp();
		Object data = IntfUtil.getRawValue(parent, desc);
		if (data == null) {
			if( did_missing_error == false ) {
				did_missing_error = true;
				log.error("MISSING ITEM IN DATA STRUCTURE: {}", desc);
			}
		} else if (subtyp == DataTyp.FLOAT_ARR_TYP) {
			y_data = (float[]) data;
		} else if (subtyp == DataTyp.INT_ARR_TYP) {
			int[] i_data = (int[]) data;
			y_data = new float[i_data.length];
			int idx = 0;
			for (int dat : i_data) {
				y_data[idx++] = dat;
			}
		} else if (subtyp == DataTyp.DOUBLE_ARR_TYP) {
			double[] dd_data = (double[]) data;
			y_data = new float[dd_data.length];
			int idx = 0;
			for (double dat : dd_data) {
				y_data[idx++] = (float) dat;
			}
		}
		if (y_data != null) {
			String loc = desc.getLocation();
			for (int vbo_idx = 0; vbo_idx < setups.size(); vbo_idx++) {
				WaveformSetupDataEx setup = setups.get(vbo_idx);
				if (loc.equals(setup.getLoc())) {
					setup.setUnit(desc.getUnit());
					setup.setCode(desc.getCode());
					addVertices(instrument, t0, dt, vbo_idx, y_data);
					break;
				}
			}
		}

	}

	private void addVertices(GLInstrumentDisplay sig, int t0, float dt, int vbo_idx, float[] y_data) {
		GL2 gl = sig.getGL().getGL2();

		if (vbo_idx >= setups.size()) {
			log.error("attempt to insert into non-existant signal");
			return;
		}

		check_vbos(gl);

		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, vbos[vbo_idx]);

		if (insert_vertex_pos[vbo_idx] >= VBO_VERTEX_COUNT) {
			System.out.println("VBO:" + vbo_idx + " !!OVERFLOW.0  Y_T0:" + y_t0);

			insert_vertex_pos[vbo_idx] = 0;
			overflow = true;
			_addVertices(vbo_idx, gl, y_t0, dt, vbos[vbo_idx], 0, y_last, 0, 1);
		}

		int vbo_offset = insert_vertex_pos[vbo_idx] * SIZEOF_COORD * COORDS_PER_VERTEX;
		int y_length = y_data.length;
		int y_remainder = 0;

		if (insert_vertex_pos[vbo_idx] + y_length > VBO_VERTEX_COUNT) {
			y_length = (VBO_VERTEX_COUNT - insert_vertex_pos[vbo_idx]);
			y_remainder = y_data.length - y_length;
		}

		_addVertices(vbo_idx, gl, t0, dt, vbos[vbo_idx], vbo_offset, y_data, 0, y_length);
		if (y_remainder > 0) {
			System.out.println("!!OVERFLOW.1 last:" + y_last + " rmd:" + y_remainder + " y_t0=" + y_t0 + " t0=" + t0);
			insert_vertex_pos[vbo_idx] = 0;
			overflow = true;
			t0 = _addVertices(vbo_idx, gl, y_t0, dt, vbos[vbo_idx], 0, y_last, 0, 1);
			_addVertices(vbo_idx, gl, t0, dt, vbos[vbo_idx], COORDS_PER_VERTEX * SIZEOF_COORD, y_data, y_length,
					y_remainder);
		}

		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);

	}

	private void check_vbos(GL2 gl) {
		if (setups.size() == 0) {
			return;
		}

		if (vbos != null && vbos.length > 0 && vbos.length != setups.size()) {
			log.error("deallocate each vbo!");

			gl.glDeleteBuffers(vbos.length, vbos, 0);

			vbos = null;
		}

		if (vbos == null) {
			vbos = new int[setups.size()];
			insert_vertex_pos = new int[setups.size()];
			y_last = new float[setups.size()];

			gl.glGenBuffers(vbos.length, vbos, 0);

			for (int vbo : vbos) {
				gl.glBindBuffer(GL.GL_ARRAY_BUFFER, vbo);

				// allocate space, but dont put anything in it
				int sz = VBO_VERTEX_COUNT * SIZEOF_COORD * COORDS_PER_VERTEX;
				gl.glBufferData(GL.GL_ARRAY_BUFFER, sz, null, GL.GL_DYNAMIC_DRAW);
				System.out.println("allocated vbo: " + vbo + " sz=" + sz);
			}

			// log.debug("VBO allocated: {}", sz );
		}
	}

	private int _addVertices(int vbo_idx, GL2 gl, int t0, float dt, int vbo, int vbo_offset, float[] y_data,
			int y_offset, int y_length) {

		int vbo_length = y_length * SIZEOF_COORD * COORDS_PER_VERTEX;

		ByteBuffer bytebuffer;

		// save the last vertexes in case of overrun
		if (y_length > 1) {
			int pos = y_offset + y_length - 1;
			y_t0 = t0 + (int) (dt * pos);
			y_last[vbo_idx] = y_data[pos];
		}

		if (method_2) {
			System.err.println("FIXME method2 is not right!!");
			FloatBuffer coord_pairs = Buffers.newDirectFloatBuffer(y_data, y_offset, COORDS_PER_VERTEX * y_length);
			gl.glBufferSubData(GL.GL_ARRAY_BUFFER, vbo_offset, vbo_length, coord_pairs);
			insert_vertex_pos[vbo_idx] += y_length;
		} else {
			// System.out.println("methodXX t0=" + t0 + " dt=" + dt);

			// log.info("mapping vbo offset=" + vbo_offset + " len=" + vbo_length + " dt=" + dt);
			bytebuffer = gl.glMapBufferRange(GL.GL_ARRAY_BUFFER, vbo_offset, vbo_length, GL2GL3.GL_MAP_WRITE_BIT
					| GL2GL3.GL_MAP_INVALIDATE_RANGE_BIT); // |
			if (bytebuffer == null) {
				int err = gl.glGetError();
				log.error("WRITE MAP RANGE ERROR: " + err + " ?= " + GL.GL_INVALID_OPERATION + " for vbo_offset="
						+ vbo_offset + " vbo_len=" + vbo_length);
			} else {

				FloatBuffer coord_pairs = bytebuffer.asFloatBuffer();
				for (int i = y_offset; i < y_offset + y_length; i++) {
					// System.out.println(" vbo add," + vbo_idx + ", " + t0 +
					// ", " + i + "," + y_data[i]);

					coord_pairs.put(t0);
					t0 += dt;
					coord_pairs.put(y_data[i]);

				}

				insert_vertex_pos[vbo_idx] += y_length;
			}
			gl.glUnmapBuffer(GL.GL_ARRAY_BUFFER);

		}

		return t0;
	}

	void readVertices(GL2 gl, int vbo_idx, float[] arr, int count) {
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, vbos[vbo_idx]);
		ByteBuffer bytebuffer = gl.glMapBufferRange(GL.GL_ARRAY_BUFFER, 0, SIZEOF_COORD * count * COORDS_PER_VERTEX,
				GL2GL3.GL_MAP_READ_BIT); // |
		if (bytebuffer == null) {
			int err = gl.glGetError();
			log.error("READ MAP RANGE ERROR: {} ?= {}  MESSAGE=", err, GL.GL_INVALID_OPERATION);
			return;
		}
		FloatBuffer buf = bytebuffer.asFloatBuffer();
		int ii = 0;
		while (buf.hasRemaining()) {
			float v_x = buf.get(); // ignore the x for now
			float v_y = buf.get();
			arr[ii++] = v_y;
		}
		gl.glUnmapBuffer(GL.GL_ARRAY_BUFFER);
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);

		System.out.println();
	}

	@Override
	public void display(GLAutoDrawable drawable) {

		if( visible == false ) {
			return;
		}
		
		GLInstrumentDisplay instrument = (GLInstrumentDisplay) drawable;
		GL2 gl = drawable.getGL().getGL2();

		check_vbos(gl);
		if (vbos == null) {
			return;
		}

		int ddt = instrument.getTTime() - 2000;
		gl.glViewport(x, y, w, h);

		gl.glMatrixMode(GLMatrixFunc.GL_MODELVIEW);
		gl.glLoadIdentity();
		// gl.glTranslatef(-dt, 0f, 0.0f);

		gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
		gl.glPushMatrix();

		// sig.setTime(sig.getTime() + 10 );

		gl.glEnableClientState(GLPointerFunc.GL_VERTEX_ARRAY);

		gl.glLineWidth(2);
		
		// gl.glBlendFunc(GL2.GL_SRC_ALPHA, GL2.GL_ONE_MINUS_SRC_COLOR);
		for (int vbo_idx = 0; vbo_idx < vbos.length; vbo_idx++) {
			int vbo = vbos[vbo_idx];
			WaveformSetupDataEx setup = setups.get(vbo_idx);
			Color color = setup.getColor();
			if (color != null) {
				gl.glColor3ub((byte) color.getRed(), (byte) color.getGreen(), (byte) color.getBlue() ); //, (byte)255);
			}

			/*
			 * set the y-scale
			 */
			gl.glLoadIdentity();
			glu.gluOrtho2D(ddt - width_in_msec, ddt, setup.getRangeMin(), setup.getRangeMax());
			
			gl.glBindBuffer(GL.GL_ARRAY_BUFFER, vbo);
			gl.glVertexPointer(COORDS_PER_VERTEX, COORD_TYPE, 0, 0);
			gl.glDrawArrays(GL.GL_LINE_STRIP, 0, insert_vertex_pos[vbo_idx]);
			if (overflow) {
				int start_vertex = insert_vertex_pos[vbo_idx];
				int count_vertex = VBO_VERTEX_COUNT - start_vertex;
				gl.glDrawArrays(GL.GL_LINE_STRIP, start_vertex, count_vertex);
			}
		}

		Iterator<TimedNote> ii = annos.iterator();
		while (ii.hasNext()) {
			TimedNote note = ii.next();
			float pos = note.tm;
			if (pos < 0) { // FIXME: NO, this doesnt work to determine if the
							// not should be dropped off
				ii.remove();
			} else {
				gl.glBegin(GL.GL_LINES);
				gl.glColor3f(1.0f, 0.0f, 0.0f);
				gl.glVertex2f(pos, 0f);
				gl.glVertex2f(pos, 5f);
				gl.glEnd();
				// instrument.monospaced.beginRendering(pos, 1);
				// instrument.monospaced.draw(note.message, pos, 1.0);
				// instrument.monospaced.endRendering();
			}
		}

		gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
		gl.glPopMatrix();

		// disable arrays once we're done
		gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);

		gl.glDisableClientState(GLPointerFunc.GL_VERTEX_ARRAY);

		instrument.monospaced.beginRendering(w, h);
		instrument.monospaced.setColor(1.0f, 1.0f, 0.6f, 0.8f);
		// optionally set the color
		int idx = 0;
		for (WaveformSetupDataEx setup : setups) {
			int xoff = 20 + 80 * idx;
			Color color = setup.getColor();
			if (color != null) {
				instrument.monospaced.setColor(color.brighter().brighter());
			}
			RpUnit unit = setup.getUnit();

			String unitName = "";
			double rangeMax = setup.getRangeMax();
			double rangeMin = setup.getRangeMin();
			if (unit != null) {
				rangeMax = unit.transform((int) rangeMax);
				rangeMin = unit.transform((int) rangeMin);
				unitName = " [" + unit.getUnitName() + "]";
			}
			instrument.monospaced.draw(df0.format(rangeMax), xoff, h - 20);
			instrument.monospaced.draw(setup.getCode(), xoff + 40, h - 20);
			instrument.monospaced.draw(df0.format(rangeMin) + unitName, xoff, 10);
			idx++;
		}
		instrument.monospaced.endRendering();

	}

	@Override
	public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
	}

	@Override
	public void dispose(GLAutoDrawable arg0) {
		// TODO Auto-generated method stub
	}

	public void setWidthInMillis(int msec) {
		width_in_msec = msec;
	}

	public long getDateOffsetInMillis() {
		Calendar c = Calendar.getInstance();
		// c.add(Calendar.DAY_OF_MONTH, 1);
		c.set(Calendar.HOUR_OF_DAY, 0);
		c.set(Calendar.MINUTE, 0);
		c.set(Calendar.SECOND, 0);
		c.set(Calendar.MILLISECOND, 0);
		return c.getTimeInMillis();
	}

	public WaveformSetupDataEx getSetup(String loc) {
		WaveformSetupDataEx setup_found = null;
		if (loc != null) {
			for (WaveformSetupDataEx setup : setups) {

				if (setup != null && loc.equals(setup.getLoc())) {
					setup_found = setup;
				}
			}
		}
		return setup_found;
	}

	public void addWaveformDescription(WaveformData wave, RpUnit unit) {
		WaveformSetupDataEx setup = new WaveformSetupDataEx(wave, unit);
		setups.add(setup);		
	}

	public void setXYWH(int x, int y, int w, int h) {
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
	}

	public void reset() {
		while (setups.size() > 0) {
			setups.remove(0);
		}
	}

	public void clear() {
		overflow = false;
		if (insert_vertex_pos != null) { // can be null if we havent received
											// first packet
			for (int i = 0; i < insert_vertex_pos.length; i++) {
				insert_vertex_pos[i] = 0;
			}
		}

	}

	public void addAnnotation(GLInstrumentDisplay glInstrumentDisplay, int tm, Annotation anno, String message) {
		TimedNote note = new TimedNote();
		note.tm = tm;
		note.message = message;
		annos.add(note);

	}

	public float[] getDisplayData(GLInstrumentDisplay instrument, String loc, float[] arr) {
		GL2 gl = instrument.getGL().getGL2();
		for (int vbo_idx = 0; vbo_idx < setups.size(); vbo_idx++) {
			WaveformSetupDataEx setup = setups.get(vbo_idx);
			if (loc.equals(setup.getLoc())) {
				int n = insert_vertex_pos[vbo_idx];
				if( n == 0 ) {
					// FIXME: corner case... insert pos can be 0 due to wrap, also
					// want to limit n to size of data on screen!
					log.warn("no data in buffer");
					return null;
				}
				if (arr == null) {
					arr = new float[n];
				} else {
					if (n > arr.length) {
						n = arr.length;
					}
				}
				readVertices(gl, vbo_idx, arr, n);
				return arr;
			}
		}
		return null;
	}

	public float getY() {
		return y;
	}

	public void setVisible(boolean b) {
		visible = b;
	}

	public boolean hasWaveforms() {
		if( setups == null || setups.size() == 0 ) {
			return false;
		}
		return true;
	}

	public boolean isVisible() {
		return visible;
	}

	public int getWeight() {
		return weight;
	}


}