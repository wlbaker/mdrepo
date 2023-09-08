package idea.tsoffline.tspico;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Point;
import java.awt.Stroke;
import java.awt.Toolkit;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.activities.PActivity;
import org.piccolo2d.event.PBasicInputEventHandler;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.extras.nodes.PComposite;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;

import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.canvas.LabelType;
import idea.tsoffline.canvas.TsPSwingCanvas;

@Slf4j
@Data
public class CursorLocatorTool extends PBasicInputEventHandler implements KeyListener {

	Color theme_ruler_color = Color.WHITE;
	Color theme_locator_color = Color.BLUE;

	private PPath line;
	private PPath horiz, raise_r, raise_l, lower_r, lower_l;
	private PComposite cross;
	// private TsPSwingCanvas canv;
	Cursor transparent;
	@Getter
	@Setter
	private PComposite figure;

	private boolean b_max;
	private boolean b_min;

	private boolean showCursorValue = true;
	private PText data_val;
	private PText tm_val;
	private static Font font = new Font("Ariel", Font.BOLD, 9);
	private DecimalFormat df2 = new DecimalFormat("0.00");
	private LabelType labelType;
	private long startTime;
	private TsPSwingCanvas canv;
	private int defaultEditMode;
	private PLayer cursorLayer;

	public CursorLocatorTool(TsPSwingCanvas canv) {
		this.canv = canv;

		// Toolkit.getDefaultToolkit().createCustomCursor( null, null, null );
		Toolkit tk = Toolkit.getDefaultToolkit();
		transparent = tk.createCustomCursor(tk.getImage(""), new Point(), "trans");

		initComposites();

		cursorLayer = new PLayer();
		cursorLayer.setPickable(false);
		cursorLayer.setChildrenPickable(false);
		cursorLayer.setName("cursor_layer");

		// HINT: see if you can use these to get rid of local can variable,
		// and replace the dispatch below
		// getEventFilter().setAcceptsMouseClicked(true);
		// getEventFilter().setAcceptsMouseEntered(true);
		// getEventFilter().setAcceptsMouseExited(true);
		// getEventFilter().setAcceptsMouseDragged(true);
		// getEventFilter().setAcceptsMousePressed(true);
		// getEventFilter().setAcceptsMouseReleased(true);

		cursorLayer.addChild(getFigure());
		canv.getLayer().addChild(cursorLayer);
	}

	private void initComposites() {
		float minY = 0;
		float maxY = 100;
		line = PPath.createLine((float) 0, minY, (float) 0, maxY - 1);
		horiz = PPath.createLine((float) 0, (float) 0, (float) 20, (float) 0);
		lower_l = PPath.createLine((float) -5, (float) -5, (float) 0, (float) 0);
		lower_r = PPath.createLine((float) 5, (float) -5, (float) 0, (float) 0);
		raise_l = PPath.createLine((float) -5, (float) 5, (float) 0, (float) 0);
		raise_r = PPath.createLine((float) 5, (float) 5, (float) 0, (float) 0);
		data_val = new PText("???");
		data_val.setFont(font);
		data_val.setX(0);
		data_val.setY(0);
		data_val.setVisible(true);

		tm_val = new PText("???");
		tm_val.setFont(font);
		tm_val.setX(0);
		tm_val.setY(0);
		tm_val.setVisible(true);

		cross = new PComposite();
		cross.addChild(horiz);
		cross.addChild(raise_l);
		cross.addChild(lower_l);
		cross.addChild(raise_r);
		cross.addChild(lower_r);
		cross.setName("Composite.LINETOOL.Cross");

		figure = new PComposite();
		figure.addChild(line);
		figure.addChild(cross);
		figure.addChild(data_val);
		figure.addChild(tm_val);
		figure.setName("Composite.LINETOOL");
		setLocatorColor(theme_locator_color);
	}

	public void setBounds(Rectangle2D sig_rect) {

		if (line == null) {
		}

		line.setHeight(sig_rect.getHeight());
		line.setWidth(8);
		line.setY(sig_rect.getY());

		double y_base = sig_rect.getY() + sig_rect.getHeight() + 4;
		tm_val.setY( y_base + 10 );  // 29SEPT17
		data_val.setY( y_base );  // 29SEPT17 

	}

	@Override
	public void mouseMoved(PInputEvent event) {
		TsPSwingCanvas canv = (TsPSwingCanvas) event.getComponent();
		Point2D posMouse = event.getPosition();
		if (Double.isNaN(posMouse.getX())) {
			return;
		}
		// PBounds bounds = cam.getBoundsReference();
		PCamera cam = canv.getCameraAtMousePos();
		if (cam == null) {
			cam = canv.getSignalCamera(); // ? do I want this??
		}
		PAffineTransform vt = cam.getViewTransformReference();

		vt.transform(posMouse, posMouse);

		if (Double.isNaN(posMouse.getX())) {
			log.error("transformed to X=NaN in mouse move");
			return;
		}
		long data_width_ms = canv.getViewWidthMs();
		line.setX(posMouse.getX());

		horiz.setX(posMouse.getX() - 10);
		horiz.setY(posMouse.getY());

		raise_r.setX(horiz.getX() + 22);
		raise_r.setY(horiz.getY() + 3);
		raise_l.setX(horiz.getX() - 6);
		raise_l.setY(horiz.getY() + 3);

		lower_r.setX(horiz.getX() + 22);
		lower_r.setY(horiz.getY() - 7);
		lower_l.setX(horiz.getX() - 6);
		lower_l.setY(horiz.getY() - 7);

		cross.setX(posMouse.getX());
		cross.setY(posMouse.getY());

		// System.out.println("X=" + posMouse.getX() + "," + " showCursorValue="
		// + showCursorValue );
		/*
		 * show the data value
		 */
		if (showCursorValue) {
			String v = null;
			PLayer layer = null; // when null, then display the camera coord
									// value
			layer = canv.getActiveLayer();

			if (layer == null) {

				//
				// convert mouse coordinates from global to the camera view
				// coordinates
				//
				Point2D camMouse = new Point2D.Double();

				cam.getViewTransformReference().transform(posMouse, camMouse);
				// System.out.println(" MOUSE Y=" + posMouse.getY() + " --> " +
				// camMouse.getY() );

				int candidates = 0;

				for (int i = 0; i < cam.getLayerCount(); i++) {

					PLayer l0 = cam.getLayer(i);
					if (l0.getVisible() == false) {
						continue;
					}

					// transform the bounds to cam coordinates...flip in our
					// case
					PBounds bounds = l0.getBounds();
					// System.out.println(" l0 pre=" + l0.getName() + " y=" +
					// df2.format(bounds.y) + " h=" +
					// df2.format(bounds.height) + " w=" +
					// df2.format(bounds.width) );
					cam.getViewTransform().transform(bounds, bounds);
					// System.out.println(" post=" + l0.getName() + " y=" +
					// df2.format(bounds.y) + " h=" +
					// df2.format(bounds.height) + " w=" +
					// df2.format(bounds.width) );

					double ymin = bounds.y;
					double ymax = bounds.y + bounds.height;

					if (camMouse.getY() > ymin && camMouse.getY() < ymax) {
						// System.out.println("CANDIDATE!!! " + l0.getName() );

						layer = l0;
						candidates++;
					}
				}
				if (candidates > 1) {
					log.error("overlapping layers not expected");

					layer = null;
				}
			}

			Point2D posData = new Point2D.Double();
			PAffineTransform c_inv = cam.getViewTransform();

			if (layer == null) {
				// ignore: i could show the cursor value, but what good would
				// that be?
				v = ""; // make it blank, but still give the mouse position as
						// time
				try {
					c_inv.invert();
					c_inv.transform(posMouse, posData);
				} catch (NoninvertibleTransformException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			} else {
				PAffineTransform l_inv = layer.getTransform();
				try {
					c_inv.invert();
					l_inv.invert();
				} catch (NoninvertibleTransformException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				Point2D posLayer = new Point2D.Double();
				c_inv.transform(posMouse, posLayer);
				l_inv.transform(posLayer, posData);

				RpMetric sig = (RpMetric) layer.getAttribute("sig");
				
				double raw_val = posData.getY();
				double display_val = raw_val;
				double crosshairs_val = ((HPSplitableLayer)layer).getValueAt(  posData.getX() );
				
				RpUnit unit = sig.getUnit();
				if (unit != null) {
					display_val = unit.transform_d(raw_val);
					crosshairs_val = unit.transform_d(crosshairs_val);
				}
				
				// FIXME: I don't have any code here to get the actual value under the cursor,
				// only the value at the mouse position.
				

				v = df2.format(display_val  );
				v += " / ";
				v += df2.format( crosshairs_val );
				if (unit != null) {
					v += " " + unit.getUnitName();
				}
				String name = sig.getName();
				if (name == null) {
					name = sig.getCode();
				}
				if (name == null) {
					name = sig.getLocation();
				}
				v = name + ": " + v;
			}

			if (v != null) {
				data_val.setX(posMouse.getX() - data_val.getWidth() / 2);
				// 14FEB17 data_val.setY(posMouse.getY() + 10);
				data_val.setText(v);
			}

			tm_val.setX(posMouse.getX() - tm_val.getWidth() / 2);
			tm_val.setText(getLabelText(posData.getX(), data_width_ms/1000));
		}

		super.mouseMoved(event);
	}

	private String getLabelText(double x, long data_width_sec) {
		String label;

		if (labelType == LabelType.LABEL_CLOCKTIME ) {
			DateFormat timef;
			if( data_width_sec < 100 ) {
				timef = new SimpleDateFormat("HH:mm:ss.SSS");
			} else {
				timef = GuiUtil.getTimeFormat();
			}

			long millis = (long) (x * 1000);
			millis += startTime;
			Date dt = new Date(millis);
			label = timef.format(dt);
			// label2 = datef.format(dt);
		} else if (labelType == LabelType.LABEL_REL_MMSS) {
			long msec = (long) (x * 1000);
			msec %= 1000;
			long sec = (long) x;
			long min = sec / 60;
			sec %= 60;

			label = String.format("%02d:%02d.%03d", min, sec, msec);
		} else {
			label = df2.format(x);

		}
		return label;
	}

	public void mouseEntered(PInputEvent ev) {
		line.setVisible(true);
		horiz.setVisible(true);
		cross.setVisible(true); // ?

		data_val.setVisible(showCursorValue);
		tm_val.setVisible(showCursorValue);

		b_min = ev.isShiftDown();
		b_max = ev.isControlDown();

		check_cursor();
	}

	public void mouseExited(PInputEvent ev) {
		line.setVisible(false);
		horiz.setVisible(false);
		raise_r.setVisible(false);
		lower_r.setVisible(false);
		raise_l.setVisible(false);
		lower_l.setVisible(false);
		data_val.setVisible(false);
		tm_val.setVisible(false);

		cross.setVisible(false);
	}

	@Override
	public void processEvent(PInputEvent evt, int code) {
		// I don't call the super...I delegate the events myself, since super
		// doesnt get mouse-enter / mouse-exit
		// super.processEvent(evt, code );

		if (code == MouseEvent.MOUSE_ENTERED) {
			canv.setCursor(transparent);
			canv.requestFocus();
			mouseEntered(evt);
		} else if (code == MouseEvent.MOUSE_EXITED) {
			canv.setCursor(Cursor.getDefaultCursor());
			mouseExited(evt);
		} else if (code == MouseEvent.MOUSE_MOVED) {
			mouseMoved(evt);
		} else if (code == MouseEvent.MOUSE_PRESSED) {
			mousePressed(evt);
		} else if (code == MouseEvent.MOUSE_RELEASED) {
			mouseReleased(evt);
		} else if (code == MouseEvent.MOUSE_DRAGGED) {
			// ignore
		}
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void keyPressed(KeyEvent e) {
		int keyCode = e.getKeyCode();
		if (keyCode == KeyEvent.VK_CONTROL) {
			b_max = true;
			check_cursor();
		} else if (keyCode == KeyEvent.VK_SHIFT) {
			b_min = true;
			check_cursor();
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		int keyCode = e.getKeyCode();

		if (keyCode == KeyEvent.VK_CONTROL) {
			b_max = false;
			check_cursor();
		} else if (keyCode == KeyEvent.VK_SHIFT) {
			b_min = false;
			check_cursor();
		}
	}

	private void check_cursor() {
		if (b_max || b_min) {
			raise_r.setVisible(b_max);
			lower_r.setVisible(b_min);
		} else {
			raise_r.setVisible(defaultEditMode >= 0);
			lower_r.setVisible(defaultEditMode <= 0);
		}

		raise_l.setVisible(raise_r.getVisible());
		lower_l.setVisible(lower_r.getVisible());
	}

	public void setLabelType(LabelType labelType) {
		this.labelType = labelType;
	}

	public void setStartTime(long startTime) {
		this.startTime = startTime;
	}

	public void setDefaultEditMode(int editMode) {
		this.defaultEditMode = editMode;
		check_cursor();
	}

	public PLayer getLayer() {
		return cursorLayer;
	}

	public void componentResized(ComponentEvent e, float plot_width, float plot_h) {
		Rectangle2D cursor_rect = new Rectangle2D.Float(TsPSwingCanvas.LEFT_MARGIN, TsPSwingCanvas.TOP_MARGIN,
				plot_width, plot_h);

		setBounds(cursor_rect);
		cursorLayer.setBounds(cursor_rect);
	}

	public void activityFinished(PActivity activity) {
		cursorLayer.setVisible(true);
	}

	public void setLocatorColor(Color color) {
		if( color == null ) {
			color = Color.BLUE;
		}
		this.theme_locator_color = color;
		this.theme_ruler_color = color;
		
		Stroke thick = new BasicStroke(1, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);

		PPath[] segs = new PPath[] { line, horiz, raise_r, raise_l, lower_r, lower_l };
		for (PPath p : segs) {
			p.setPaint(theme_locator_color);
			p.setStrokePaint(theme_locator_color);
			p.setPickable(false);
			p.setVisible(true);
			p.setStroke(thick);
		}
		data_val.setTextPaint(theme_ruler_color);
		tm_val.setTextPaint(theme_ruler_color);

	}
}
