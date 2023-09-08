package idea.tsoffline.tspico;

import java.awt.Color;
import java.awt.Font;
import java.awt.geom.Point2D;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import javax.swing.SwingConstants;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PAffineTransformException;
import org.piccolo2d.util.PBounds;
import org.sittingbull.gt.util.Label;
import org.sittingbull.gt.util.XWilkinson;

import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.tsoffline.canvas.LabelType;
import idea.tsoffline.canvas.Ruler;

@Slf4j
public class RulerComponent extends Ruler {

	Color theme_ruler_color = Color.WHITE;
	Color theme_y_range_color = Color.GREEN;

	private static Font axisFont = new Font("Ariel", Font.BOLD, 11);

	private static final DecimalFormat df0 = new DecimalFormat("#,##0");
	private static final DecimalFormat df1 = new DecimalFormat("#,##0.0");
	private static final DecimalFormat df2 = new DecimalFormat("#,##0.00");

	public void drawXRuler(long startTime, Font ticFont, XWilkinson wilkinson, PLayer axisLayer, PCamera camera,
			boolean isSummary, boolean inline, LabelType labelType) {

		PBounds bounds = camera.getBounds();

		PAffineTransform view_transform = camera.getViewTransform();

		Point2D origin_data;
		try {
			Point2D origin_window = new Point2D.Double(bounds.getX(), bounds.getHeight());
			origin_data = view_transform.inverseTransform(origin_window, null); // ???
		} catch (PAffineTransformException e) {
			// ignore!
			return;
		}

		double dataWidth = bounds.getWidth() / view_transform.getScaleX();

		if (getTicks() <= 2) {
			setTicks(10);
		}
		float yBase;

		/*
		 * put the tics on the diagram
		 */
		DateFormat datef = GuiUtil.getDateFormat();
		DateFormat timef = GuiUtil.getTimeFormat();
		if (dataWidth < 10) {
			timef = new SimpleDateFormat("HH:mm:ss.SSS");
		}
		Label labels = null;
		int tick_len;
		int justify = SwingConstants.LEFT;

		if (inline) {
			labels = new Label();
			labels.min = origin_data.getX();
			labels.max = origin_data.getX() + dataWidth;
			labels.step = dataWidth;
			yBase = (float) bounds.getY();
			tick_len = 0;

			if (isSummary) {
				// yBase is inline with the camera
			} else {
				// yBase is slightly beneath the camera
				yBase += bounds.getHeight() + 4;
			}
		} else {
			wilkinson.setLooseFlag(!isSummary);
			int m = (int) (bounds.getWidth() / 100);
			m = (m < 5) ? 5 : m;
			labels = wilkinson.search(origin_data.getX(), origin_data.getX() + dataWidth, m);
			yBase = (float) (bounds.getY() + bounds.getHeight());
			tick_len = 6;
			justify = SwingConstants.CENTER;
		}

		if (labels == null) {
			// dont bother to draw the labels...nothing to draw
			return;
		}

		DecimalFormat df = df0;
		if (labels.step < 3.0)
			df = df1;

		Point2D src = new Point2D.Double(0, 0);
		Point2D dst = new Point2D.Double(0, 0);
		int seq = 0;
		for (double tic_value = labels.min; tic_value <= labels.max; tic_value += labels.step) {

			src.setLocation(tic_value, 0);
			view_transform.transform(src, dst);

			if (tick_len > 0) {
				PPath tic = new PPath.Float();
				tic.moveTo(dst.getX(), yBase);
				tic.lineTo(dst.getX(), yBase + 6);
				tic.setStrokePaint(theme_ruler_color); // x_ruler.color);
				axisLayer.addChild(tic);
			}

			String label = null;
			String label2 = null;
			if (labelType == LabelType.LABEL_CLOCKTIME) {
				long millis = (long) (tic_value * 1000);
				millis += startTime;
				Date dt = new Date(millis);
				label = timef.format(dt);
				if (isSummary) {
					if (tic_value == labels.min || tic_value == labels.max) {
						label2 = datef.format(dt);
					}
				}
			} else if (labelType == LabelType.LABEL_REL_SECS && false) {
				long millis = (long) (tic_value * 1000);
				millis += startTime;
				Date dt = new Date(millis);
				label = timef.format(dt);
				if (isSummary) {
					if (tic_value == labels.min || tic_value == labels.max) {
						label2 = datef.format(dt);
					}
				}
			} else if (labelType == LabelType.LABEL_REL_MMSS) {
				long sec = (long) tic_value;
				boolean neg = (sec < 0);

				if (neg) {
					sec = -sec;
				}
				long min = sec / 60;
				sec = sec % 60;
				long millis = (long) (1000 * tic_value);
				millis %= 1000;
				long hundredths = millis / 10;

				String fmt = "%02d:%02d";
				if (neg) {
					fmt = "-" + fmt;
				}
				if (labels.step < 3.0) {
					fmt = fmt + ".%02d";
				}
				label = String.format(fmt, min, sec, hundredths);
			} else {
				if (unit != null) {
					tic_value = unit.transform_d(tic_value);
				}
				label = df.format(tic_value);

			}

			if (inline) {
				if (seq == 0) {
					dst.setLocation(camera.getX() - 6, camera.getY() - 2);
					justify = SwingConstants.RIGHT;
				} else {
					dst.setLocation(camera.getX() + camera.getWidth() + 6, camera.getY() - 2);
					justify = SwingConstants.LEFT;
				}
				seq++;
			}

			PText pt_label = new PText(label);
			pt_label.setFont(ticFont);
			// 16NOV2016 pt_label.addInputEventListener(axisHandler);

			double justify_dx = calculateJustification(justify, pt_label);

			pt_label.setX(dst.getX() - justify_dx);
			pt_label.setY(yBase + tick_len + 2);
			pt_label.setTextPaint(theme_ruler_color);
			axisLayer.addChild(pt_label);

			if (label2 != null) {
				pt_label = new PText(label2);
				pt_label.setFont(ticFont);

				justify_dx = calculateJustification(justify, pt_label);
				pt_label.setX(dst.getX() - justify_dx);
				pt_label.setY(yBase + tick_len + 14);
				pt_label.setTextPaint(theme_ruler_color);
				axisLayer.addChild(pt_label);
			}

		}

	}

	private double calculateJustification(int justify, PText text) {
		double dx = 0;
		if (justify == SwingConstants.CENTER) {
			dx = text.getWidth() / 2;
		} else if (justify == SwingConstants.RIGHT) {
			dx = text.getWidth();
		}
		return dx;
	}

	public void drawYRuler(Font ticFont, XWilkinson wilkinson, PLayer axisLayer, PCamera cam, PLayer activeLayer) {

		PBounds bounds = cam.getBounds();
		double camera_x = bounds.getX();
		double camera_h = bounds.getHeight();
		double camera_y = bounds.getY();

		PLayer layer = null;
		String unitName = null;
		boolean mixed_scales = false;

		RpUnit unit = null;
		// if there is only one transform for all the layers, use it
		for (int i = 0; i < cam.getLayerCount(); i++) {
			PLayer sub = cam.getLayer(i);

			if (!sub.getVisible()) { // only consider visible layers
				continue;
			}
			if (activeLayer != null && sub != activeLayer) {
				// if we have an active layer, ignore other layers
				continue;
			}

			PAffineTransform tr0 = sub.getTransform();
			if (layer == null) {
				layer = sub; // use the first layer as the reference
			}
			/*
			 * Check to see if all the layers use the same transform
			 */
			RpMetric sig = (RpMetric) sub.getAttribute("sig");
			if (sig != null) {
				unit = sig.getUnit();
				String uu = sig.getUnitName();
				if (unitName == null) {
					unitName = (uu == null) ? "" : uu;
				}

				if (!unitName.equals(sig.getUnitName())) {
					unitName = ""; // no common unit name
				}

				PAffineTransform tr1 = layer.getTransform();

				if (!tr0.equals(tr1)) {
					mixed_scales = true;
					break;
				}

			}

		}

		if (mixed_scales) {
			// cant draw a single unified scale
			return;
		}

		/*
		 * 
		 */
		drawYRulerOneTile(ticFont, wilkinson, axisLayer, cam, title, unit/* unitName */, layer, camera_x, camera_y,
				camera_h);

	}

	private void drawYRulerOneTile(Font ticFont, XWilkinson wilkinson, PLayer axisLayer, PCamera cam, String title,
			RpUnit unit2, PNode sub, double camera_x, double camera_y, double camera_h) {

		if (sub == null || !sub.getVisible()) { // only consider visible layers
			return;
		}
		float xBase = (float) (camera_x - 6); // 6 for the bounding rectangle

		PBounds bounds = sub.getBounds();
		if (bounds.isEmpty()) {
			bounds = cam.getBounds();
		}
		PAffineTransform view_transform = cam.getViewTransform();
		if (view_transform.getDeterminant() == 0) {
			log.error("cannot invert transform...drawing error!");
			return;
		}

		Point2D origin_window = new Point2D.Double(bounds.getX(), bounds.getY());
		Point2D origin_data = null;

		try {
			origin_data = view_transform.inverseTransform(origin_window, null); // ???
		} catch (Throwable nit) {
			log.error("FIXME: why could not invert this transform??? {}", nit.getClass());
			return;
		}

		double dataHeight = bounds.getHeight() / view_transform.getScaleY();

		/*
		 * calculate optimal tic positions
		 */

		double y1 = origin_data.getY();
		double y2 = origin_data.getY() + dataHeight;
		// System.out.println("DRAWING TICKS: " + cam.getName() + " BOUNDS=" +
		// bounds + " y1=" + y1 + " y2=" + y2);
		RpUnit unit = null;
		if (unit2 != null) {
			unit = unit2;

			if (unit != null) {
				y1 = unit.transform_d(y1);
				y2 = unit.transform_d(y2);
			}
			// System.out.println("* transformed y1=" + y1 + " y2=" + y2);
		}

		wilkinson.setLooseFlag(true);
		Label labels = wilkinson.search(y1, y2, 6);
		if (labels == null) {
			return;
		}

		double divisor = 1.0;
		String suffix = "";
		if (labels.step > 1.0e6) {
			divisor = 1.0e6;
			suffix = "M";
		} else if (labels.step > 1.0e3) {
			divisor = 1.0e3;
			suffix = "K";
		}

		DecimalFormat df = df0;
		if (labels.step / divisor < 3.0)
			df = df1;
		if (labels.step / divisor < 0.3)
			df = df2;

		/*
		 * bounding braces
		 */
		Point2D lower = new Point2D.Double(0, origin_data.getY());
		Point2D upper = new Point2D.Double(0, origin_data.getY() + dataHeight);
		view_transform.transform(lower, lower);
		view_transform.transform(upper, upper);

		PPath brace = new PPath.Float();
		brace.moveTo(xBase - 20, lower.getY());
		brace.lineTo(xBase, lower.getY());
		brace.setStrokePaint(theme_y_range_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase, lower.getY());
		brace.lineTo(xBase, upper.getY());
		brace.setStrokePaint(theme_y_range_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase - 20, upper.getY());
		brace.lineTo(xBase, upper.getY());
		brace.setStrokePaint(theme_y_range_color);
		axisLayer.addChild(brace);

		/*
		 * draw ticks
		 */
		Point2D src = new Point2D.Double(0, 0);
		Point2D dst = new Point2D.Double(0, 0);

		for (double tic_value = labels.min; tic_value <= labels.max; tic_value += labels.step) {

			double raw_tic = ((unit == null) ? tic_value : unit.inverse_d(tic_value));

			src.setLocation(0, raw_tic);
			view_transform.transform(src, dst);

			PPath tic = new PPath.Float();

			double y = dst.getY();
			tic.moveTo(xBase, y);
			tic.lineTo(xBase - 6, y);
			tic.setStrokePaint(theme_ruler_color); // x_ruler.color
			axisLayer.addChild(tic);

			PText pt_label = new PText(df.format(tic_value / divisor) + suffix);
			pt_label.setFont(ticFont);
			pt_label.setX(xBase - 8 - pt_label.getWidth()); // center around tic
			pt_label.setY(y - 6); // center the font around the tic
			pt_label.setTextPaint(theme_ruler_color); // y_ruler.color
			axisLayer.addChild(pt_label);

		}

		// if (unitName != null) {
		// title += " " + unitName;
		// }
		PText yLabel = new PText(title);
		yLabel.setFont(axisFont);
		// if (displayLayout == TILED) {
		// yLabel.translate(LEFT_MARGIN + 10, bounds.getY());
		// } else {
		yLabel.translate(10, bounds.getY() + (yLabel.getWidth() + bounds.getHeight()) / 2);
		yLabel.rotate(-Math.PI / 2f);
		// }
		yLabel.setTextPaint(theme_ruler_color); // y_ruler.color

		axisLayer.addChild(yLabel);
	}

	public void setThemeColor(Color color) {
		theme_ruler_color = color;
	}

	public void drawReferenceLines(PLayer axisLayer, PCamera cam) {
		List<Double> refLines = (List<Double>) cam.getAttribute("@refLines");
		if (refLines == null || refLines.size() == 0) {
			return;
		}
		PBounds bounds = cam.getBounds();
		double camera_x = bounds.getX();
		double camera_h = bounds.getHeight();
		double camera_y = bounds.getY();
		double camera_w = bounds.getWidth();

		for (int idx = 0; idx < cam.getLayerCount(); idx++) {
			PLayer sub = cam.getLayer(idx);
			if (sub == null || !sub.getVisible()) { // only consider visible layers
				continue;
			}

			// ?PBounds bounds = sub.getBounds();
			// ?if (bounds.isEmpty()) {
			// ? bounds = cam.getBounds();
			// ?}
			PAffineTransform view_transform = cam.getViewTransform();
			if (view_transform.getDeterminant() == 0) {
				log.error("cannot invert transform...drawing error!");
				return;
			}

			/*
			 * don't apply signal scaling RpUnit unit = null; if (unit2 != null) { unit =
			 * unit2;
			 *
			 * if (unit != null) { y1 = unit.transform_d(y1); y2 = unit.transform_d(y2); } }
			 */

			// currently no label for the reference line
			// DecimalFormat df = df0;
			// if (labels.step / divisor < 3.0)
			// df = df1;
			// if (labels.step / divisor < 0.3)
			// df = df2;

			/*
			 * the lines themselves
			 */
			for (Double pos : refLines) {
				Point2D pt = new Point2D.Double(0, pos);
				view_transform.transform(pt, pt);

				double y0 = pt.getY();
				if( y0 < camera_y || y0 > camera_y + camera_h ) {
					continue;  // out of range for display in this viewport
				}
				
				PPath brace = new PPath.Float();
				brace.moveTo(camera_x, y0 );
				brace.lineTo(camera_x + camera_w, y0 );
				brace.setStrokePaint(theme_y_range_color);
				axisLayer.addChild(brace);

			}
			break;  // only needed for first layer  
		}
	}

}
