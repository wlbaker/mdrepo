package idea.display.gl;

import java.awt.Color;
import java.awt.geom.Rectangle2D;
import java.util.LinkedList;
import java.util.List;

import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.fixedfunc.GLMatrixFunc;

import com.jogamp.opengl.util.awt.TextRenderer;

import icuInterface.RpUtil;
import idea.display.DisplayUtil;
import idea.display.FieldData;
import idea.display.ParameterLayout;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class GLParameterPainter implements GLEventListener {

	private int SMALL = 1;
	private int LARGE = 2;
	private int x;
	private int y;
	private int w;
	private int h;

	/**
	 * Ratio of world-space units to screen pixels. Increasing this zooms the
	 * display out, decreasing it zooms the display in.
	 */

	private int styl;

	List<ParamDataEx> fields = new LinkedList<ParamDataEx>();
	private ParameterLayout box;

	private static final String[] pbox_labels = { null, //
			"HR", // 1
			"SpO2", // 2
			"C.O.", // 3
			null, // 4 -- IBP
			"etCO2", // 5
			"NIBP", // 6
			"?Arr", // 7 Arrhythmia
			"Resp", //
			"Ta", // 9 Temp
			"O2/N2O", // MGM O2/N2O
			"Agent", // MGM Agent
			"MIX", // MGM Mixed Agent
			null, // MGM Unknown Agent
			null, // Generic MIB
			"Paw", // 15 MIB Vent Paw
			"Vent", // MIB Vent Vol
			"", // blank pbox
			null, // _17 Wall and tank for Alladin
			null, // 17A O2/Agent/N2O
			"ST", //
			"STx", // Double height ST
			null, // O2/Unknown Agent/N2O
			null, // O2/Unknown Agent/N2O
			"TCP", //
			null, // Spirometry
			null, // EEG
			"BIS", //
			"LAB", // Double Height Lab Results
			null, // Generic vent pbox with 4 parameters
			"SpO2*", // Second SPO2
			"DUAL", // Dual agent
			"NMT", //
			"PCCO", //
			"PCO", //
			null, // Unkonwn Agent/N2O
			null, // AGT/N2O
	};

	public GLParameterPainter(ParameterLayout box, RpStream stream) {
		this.box = box;

		FieldData[] paramData = box.getFieldData();

		ParamDataEx f;
		FieldData param;
		int format = box.getFormat();
		if (format < 0) {
			format = 0; // should never happen
		}
		switch (format) {
		case 1: // Drager ECG format
			param = paramData[0];
			// f = addField(param.getLoc(), null, 1, -1, SMALL);
			f = addField("LABEL", null, 1, -1, SMALL);
			f.setText("HR");
			f = addField("ecg.arr", null, 1, 3, SMALL);
			f.setText("ARR");
			f = addField("***", param, -1, -1, LARGE);
			f.setText("***");

			break;

		case 2: // Drager SPO2 & PLS
		case 4: // Drager IBP/ABP format
		case 8: // Drager RESP
			createBasicBox248(format, paramData);
			break;
		case 5: // ETCO2
		case 16: // MIB_Vent
			createBasicBox516(format, paramData);
			break;
		case 9: // Temperature

			y = -1;
			for (int i = 0; i < paramData.length; i++) {
				param = paramData[i];
				if (param == null) {
					continue;
				}

				f = addField(param.getLoc(), null, 1, y, SMALL);

				RpMetric metric = RpUtil.getMetricFromStream(stream, param.getLoc());
				String fieldName;
				if (metric == null) {
					fieldName = "ERR:" + param.getLoc();
				} else {
					fieldName = metric.getCode();
					if (fieldName == null || fieldName.length() == 0) {
						fieldName = param.getLoc();
					}
				}
				f.setText(fieldName);
				addField(param.getLoc(), param, -1, y, SMALL);
				y -= 6;
			}
			break;

		case 19: // Multigas
			param = paramData[0];
			// f = addField(param.getLoc(), null, 1, -1, SMALL);
			String[] gasses = new String[] { "O2", "HAL", "N2O" };
			int[] xx = new int[] { 2, 12, 22 };
			int field_idx = 0;
			int column = 0;
			for (String gas : gasses) {
				f = addField(gas, null, xx[column], -1, SMALL);
				f.setText(gas);
				if (field_idx < paramData.length) {
					f = addField(paramData[field_idx].getLoc(), paramData[field_idx], xx[column], -4, SMALL);
					f.setText("**");
				}
				field_idx++;
				if (field_idx < paramData.length) {
					f = addField(paramData[field_idx].getLoc(), paramData[field_idx], xx[column], -7, SMALL);
					f.setText("**");
				}
				field_idx++;
				column++;
			}

			break;
		case 20: // Drager 3 vertical lines...PCCI
		case 33: // Drager 3 vertical lines...GEDVI

			int y = -1;
			for (int i = 0; i < paramData.length; i++) {
				param = paramData[i];
				if (param == null) {
					continue;
				}
				f = addField(param.getLoc(), null, 1, y, SMALL);
				f.setText(param.getLoc());
				addField(param.getLoc(), param, -1, y, SMALL);
				y -= 2;
			}
		case 80: // Philips

			if (paramData == null || paramData.length != 1) {
				log.error("invalid field data for style={} data={}", styl, paramData);
			} else {
				FieldData d = paramData[0];
				f = addField("code", null, 1, -2, SMALL);
				f.setText("--");
				f = addField("value", d, 3, 1, LARGE);
				f.setText("---");
			}
			break;
		case 81: // Philips

			if (paramData == null || paramData.length != 1) {
				log.error("invalid field data for style={} data={}", styl, paramData);
			} else {
				FieldData d = paramData[0];
				f = addField("label1", null, 1, -2, SMALL);
				f.setText("NBP");
				f = addField("label2", null, 8, -2, SMALL);
				f.setText("Pulse");
				f = addField("label3", null, 16, -2, SMALL);
				f.setText("MAN");
				f = addField("labelsys", null, 1, 5, SMALL);
				f.setText("Sys");
				f = addField("alup", null, 3, 4, SMALL);
				f.setText("90");
				f = addField("aldn", null, 3, 3, SMALL);
				f.setText("40");
				f = addField("value", d, 8, 1, LARGE);
				f.setText("??/?? (??)");
			}
			break;
		default:
			if (paramData == null) {
				System.err.println("FORMAT=" + styl + " FOR ARRAY PARAM[] = NULL");
			} else if (paramData.length == 0) {
				System.err.println("FORMAT=" + styl + " PARAM LENGTH = 0");
			} else if (paramData[0] == null) {
				System.err.println("FORMAT=" + styl + " FIRST ELEMENT PARAM[0] == NULL");
			}

		case 0: // this is the default style for auto-created fields

			if (paramData == null || paramData.length == 0) {
				log.error("no parameter in box");
				break;
			}
			param = paramData[0];
			if (param == null) {
				log.error("param boxs not initialized");
				break;
			}
			String signal_group = getSignalGroup(format, param.getLoc());
			f = addField("label1", null, 1, -1, SMALL);
			f.setText(signal_group);
			y = -3;
			for (int i = 0; i < paramData.length; i++) {
				param = paramData[i];
				if (param == null) {
					continue;
				}

				f = addField(param.getLoc(), null, 5, y, SMALL);

				RpMetric metric = RpUtil.getMetricFromStream(stream, param.getLoc());
				String fieldName;
				if (metric == null) {
					fieldName = getParamName(format, param.getLoc());
				} else {
					fieldName = metric.getCode();
					if (fieldName == null || fieldName.length() == 0) {
						fieldName = param.getLoc();
					}
				}
				f.setText(fieldName);
				addField(param.getLoc(), param, -1, y, SMALL);
				y -= 3;
			}
			break;
		}
	}

	private void createBasicBox248(int format, FieldData[] paramData) {

		FieldData param = paramData[0];
		String label = getSignalGroup(format, param.getLoc());

		ParamDataEx f = addField("LABEL", null, 1, -1, SMALL);
		f.setText(label);

		int sz = (format == 2) ? LARGE : SMALL;
		if (paramData.length == 1)
			sz = LARGE;

		addField(param.getLoc(), param, -1, -1, sz); // upper right hand
														// corner

		if (paramData.length > 1) {
			param = paramData[1];

			addField(param.getLoc(), param, -1, 1, SMALL);
			if (format == 2) {
				f = addField("LABEL2", null, 1, 1, SMALL); // lower left
				f.setText("PLS");
			} else if (format == 4) {

				if (paramData.length > 2) {
					param = paramData[2];
					f = addField(param.getLoc(), param, 1, 1, LARGE); // lower
																		// left
					f.setText(param.getLoc());
				}
			}

		}
	}

	private void createBasicBox516(int format, FieldData[] paramData) {

		if( paramData == null || paramData.length == 0 ) {
			return;
		}
		FieldData param = paramData[0];
		String signalGroup = getSignalGroup(format, param.getLoc());
		String paramID = getParamName(format, param.getLoc());

		ParamDataEx f = addField("SIG_GROUP", null, 1, -1, SMALL);
		f.setText(signalGroup);

		f = addField("PARAM_NAME", null, 1, -8, SMALL);
		if (format == 5) {
			paramID = "RRc";
		} else if (format == 16) {
			paramID = "RRv";
		}
		f.setText(paramID);

		f = addField(param.getLoc(), param, -1, -1, SMALL); // upper right hand
															// corner
		f.setText("**");

		if (paramData.length > 1) {
			param = paramData[1];

			f = addField(param.getLoc(), param, -1, 1, SMALL);
			f.setText("**");
		}
		if (paramData.length > 2) {
			param = paramData[2];
			f = addField(param.getLoc(), param, 1, 1, SMALL); // lower left
			f.setText("**");
		}
	}

	private String getSignalGroup(int format, String loc) {
		String label = null;
		if (format < pbox_labels.length) {
			label = pbox_labels[format];
		}

		if (label == null) {
			label = loc;
			int idx = label.indexOf('.');
			if (idx > 0) {
				label = label.substring(0, idx).toUpperCase();
			}
		}
		return label;
	}

	private String getParamName(int format, String loc) {
		String label = loc;

		int idx = label.indexOf('.');
		if (idx > 0) {
			label = label.substring(idx + 1).toUpperCase();
		}
		return label;
	}

	private ParamDataEx addField(String name, FieldData pdat, int x, int y, int sz) {
		ParamDataEx f = new ParamDataEx(name, pdat, x, y, sz);
		fields.add(f);
		return f;
	}

	@Override
	public void init(GLAutoDrawable drawable) {

	}

	@Override
	public void display(GLAutoDrawable drawable) {

		GLInstrumentDisplay instrument = (GLInstrumentDisplay) drawable;
		GL2 gl = drawable.getGL().getGL2();

		gl.glViewport(x, y, w, h);

		gl.glMatrixMode(GLMatrixFunc.GL_MODELVIEW);

		gl.glLoadIdentity();

		// gl.glEnableClientState(GLPointerFunc.GL_VERTEX_ARRAY);

		gl.glColor3b((byte) 115, (byte) 0, (byte) 110);

		byte bg = box.getBackground();
		if (bg != 0) {
			Color color = DisplayUtil.getColorFromDrager(bg);
			if (color != null) {
				gl.glColor3ub((byte) color.getRed(), (byte) color.getGreen(), (byte) color.getBlue());
				// System.out.print("c");
			}
			gl.glBegin(GL2.GL_QUADS);
			gl.glVertex3f(-1, -1, 0);
			gl.glVertex3f(1, -1, 0);
			gl.glVertex3f(1, 1, 0);
			gl.glVertex3f(-1, 1, 0);
			// gl.glRecti(x, y, w, h);
			gl.glEnd();

		}
		processFields(instrument.arielBlack, LARGE);
		processFields(instrument.monospaced, SMALL);
	}

	private void processFields(TextRenderer font, int REQ_SIZE) {
		font.beginRendering(w, h);

		Color color = DisplayUtil.getColorFromDrager(box.getForeground());

		if (color == null) {
			font.setColor(1.0f, 0.2f, 0.2f, 0.8f);
		} else {
			if (color == Color.BLACK)
				color = Color.GREEN;
			font.setColor(color);
		}

		for (ParamDataEx f : fields) {
			if (f.getText() != null) {

				FieldData fieldData = f.getPdat();
				if (fieldData != null) {
					byte fg_code = f.getPdat().getForeground();
					if (fg_code > 0) {
						font.setColor(DisplayUtil.getColorFromDrager(fg_code));
					}
				}
				if (f.getSz() != REQ_SIZE) {
					continue;
				}

				int xx = 5 * f.getX();
				if (xx < 0) {
					Rectangle2D bounds = font.getBounds(f.getText());
					xx = (int) (w - bounds.getWidth() + xx);
				}
				int yy = f.getY();

				if (yy < 0) {
					Rectangle2D bounds = font.getBounds(f.getText());
					yy = h - (int) bounds.getHeight() + 5 * yy;
				} else {
					yy = yy * 5;
				}

				// System.out.println(f.getSz() + " " + f.getText() + "@" + xx +
				// "," + yy + ": " + f.getText() );

				font.draw(f.getText(), xx, yy);
			}
		}
		font.endRendering();
	}

	@Override
	public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
	}

	@Override
	public void dispose(GLAutoDrawable arg0) {
		// TODO Auto-generated method stub
	}

	public void setXYWH(int x, int y, int w, int h) {
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
	}

	/*
	 * *************************************************************************
	 * ****** Routines for management of displayed values
	 */
	public void setValue(String loc, String value) {
		// String loc = item.getLocation();
		for (ParamDataEx f : fields) {
			String f_loc = f.getLoc();
			if (loc.equals(f_loc)) {
				if (value == null) {
					f.setText("---");
				} else {
					f.setText(value);
				}
			} else if ("code".equals(f_loc)) {
				log.error("hmm...dunno about code as loc");
				// String code = item.getCode();
				// if (code != null) {
				// f.setText(code);
				// }
			}
		}
	}

	public boolean containsLoc(String loc) {
		for (ParamDataEx f : fields) {
			String f_loc = f.getLoc();
			if (loc.equals(f_loc)) {
				return true;
			}
		}
		return false;
	}

	public int getFormat() {
		return styl;
	}

	public String getLoc(int field_idx) {
		return fields.get(field_idx).getLoc();
	}

	public float getX() {
		return x;
	}

	public float getY() {
		return y;
	}

	public float getHeight() {
		return h;
	}

	public float getWidth() {
		return w;
	}

	public boolean isHit(int ogl_x, int ogl_y) {
		// System.out.print(ogl_x + "," + ogl_y + " hit? " + x + "," + y + ","
		// + w + "," + h);
		if (ogl_x > x && ogl_x < (x + w)) {
			if (ogl_y > y && ogl_y < (y + h)) {
				return true;
			}
		}
		return false;
	}

	public ParameterLayout getBox() {
		return box;
	}

	public boolean isSelected() {
		return box.isSelected();
	}
}
