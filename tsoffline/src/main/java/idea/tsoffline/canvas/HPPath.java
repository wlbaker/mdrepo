package idea.tsoffline.canvas;

import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Stroke;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.text.DecimalFormat;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.extras.nodes.PLine;
import org.piccolo2d.extras.util.LineShape;
import org.piccolo2d.extras.util.MutablePoints;
import org.piccolo2d.extras.util.XYArray;
import org.piccolo2d.util.PPaintContext;

import idea.schema.rp.RpMetric;
import uk.me.berndporr.api.FilterInterface;

@SuppressWarnings("serial")
public class HPPath extends PLine {

	private RpMetric sig;
	private LineShape unmodified;

	public HPPath(LineShape s, Stroke stroke, RpMetric sig) {
		super(s);

		this.sig = sig;

		this.setStroke(stroke); // force calculation of bounds
	}

	@Override
	public Paint getStrokePaint() {
		PNode p = this.getParent();
		if (p != null) {
			PLayer layer = (PLayer) p;
			return layer.getPaint();
		}
		if (sig == null) {
			return super.getPaint();
		}

		PLayer layer = (PLayer) getParent();
		return layer.getPaint(); // 071219 sig.getColor();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.piccolo2d.extras.nodes.PLine#getLineBoundsWithStroke()
	 * 
	 * Custom version...since we know stroke is 1-pixel, optimize for speed
	 */
	@Override
	public Rectangle2D getLineBoundsWithStroke() {
		return getLineReference().getBounds2D();
	}

	@Override
	protected void paint(final PPaintContext paintContext) {

		Paint strokePaint = getStrokePaint();
		paint(strokePaint, paintContext);
	}

	private void paint(Paint strokePaint, final PPaintContext paintContext) {

		final Paint p = getPaint();
		final Graphics2D g2 = paintContext.getGraphics();

		final LineShape path = getLineReference();
		final Stroke stroke = getStroke();
		// Paint strokePaint = getStrokePaint();

		if (p != null) {
			g2.setPaint(p);
			g2.fill(path);
		}

		if (stroke != null && strokePaint != null) {
			g2.setPaint(strokePaint);
			g2.setStroke(stroke);
			g2.draw(path);
		}
	}

	/*
	 * 14FEB17 Performance enhanced fullPaint()
	 */
	public void fullPaintX(Paint color, PPaintContext paintContext) {
		if (getVisible() && fullIntersects(paintContext.getLocalClip())) {

			if (!getOccluded()) {
				paint(color, paintContext);
			}

		}

	}

	public LineShape getUnmodified() {
		if (unmodified == null) {
			MutablePoints pts = copyPoints(getLineReference());
			unmodified = new LineShape(pts);
		}
		return unmodified;
	}

	private MutablePoints copyPoints(LineShape line) {
		double[] seg = new double[6];
		int len = line.getPointCount();
		double[] xy = new double[2 * len];
		PathIterator it = line.getPathIterator(null);
		int pos = 0;
		while (it.isDone() == false) {
			it.currentSegment(seg);
			xy[pos++] = seg[0];
			xy[pos++] = seg[1];
			it.next();

		}
		return new XYArray(xy);
	}

	public static double[] filter(HPPath node, FilterInterface filter) {
		double[] seg = new double[6];
		int len = node.getUnmodified().getPointCount();

		// get the original unmodified data

		PathIterator it = node.unmodified.getPathIterator(null);
		double[] xy = new double[2 * len];
		int pos = 0;

		// dont add the last point to the filter
		// ...it is duplicate with the first point of the next block
		for (int i = 0; i < len - 1; i++) {

			if (it != null) {
				it.currentSegment(seg);
				it.next();
			}

			double x0 = seg[0];
			double y0 = seg[1];

			xy[pos++] = x0;
			xy[pos++] = filter.filter(y0);
		}

		return xy;
	}

	/**
	 * Apply a filter in the reverse direction. Utilizes previously modified data.
	 * Anticipated that this method will be used in combination with filter() to
	 * create a bi-directional filter.
	 * 
	 * @param node
	 * @param filter
	 * @return
	 */
	public static double[] reverseFilter(HPPath node, FilterInterface filter) {
		double[] seg = new double[6];
		int len = node.getPointCount();

		LineShape line = node.getLineReference();
		PathIterator it = line.getPathIterator(null);
		double[] xy = new double[2 * len];

		// dont add the last point to the filter
		// ...it is duplicate with the first point of the next block
		for (int pos = 0, i = 0; i < len; i++) {

			if (it != null) {
				it.currentSegment(seg);
				it.next();
			}

			double x0 = seg[0];
			double y0 = seg[1];

			xy[pos++] = x0;
			xy[pos++] = y0; // filter.filter( y0 );
		}

		// ...step through the list backward, applying the filter
		int pos;
		for ( pos = 2*len - 1; pos >=0; ) {

			xy[pos] = filter.filter( xy[pos] );  // y0
			pos--;  // y
			pos--;  // x
		}
		
		return xy;
	}

	private double init_buf(int npts, double[] buf, double[] tm, HPPath prev, PathIterator it) {
		double[] seg = new double[6];

		int idx = 0;
		if (prev == null) {
			idx = npts / 2; // expected truncation
		} else {
			LineShape line = prev.getUnmodified(); // get the unfiltered version
			int last = line.getPointCount() - 1;

			// this last point is actually a duplicate of the first point of the
			// next line

			// we are implicitly assuming the node has at least three xy points
			Point2D pt = new Point2D.Double();
			if (npts > 3) {
				line.getPoint(last - 2, pt);
				tm[idx] = pt.getX();
				buf[idx] = pt.getY();
				idx++;
			}
			line.getPoint(last - 1, pt);
			tm[idx] = pt.getX();
			buf[idx] = pt.getY();
			idx++;
		}
		it.currentSegment(seg);
		tm[idx] = seg[0];
		buf[idx] = seg[1];
		it.next();

		if (npts > 3) {
			idx++;
			it.currentSegment(seg);
			tm[idx] = seg[0];
			buf[idx] = seg[1];
			it.next();
		}

		// System.out.print(" init buff: " );
		// for( int i = 0; i < 4; i++ ) {
		// System.out.print( " [" + tm[i] + "," + buf[i] + "]");
		// }
		// System.out.println();

		// initialize tot to the sum of the buffer
		double tot = 0.0;
		for (int i = 0; i < npts - 1; i++) {
			tot += buf[i];
		}

		return tot;
	}

	public void dump() {
		DecimalFormat df1 = new DecimalFormat("0.0");
		DecimalFormat df3 = new DecimalFormat("0.000");

		double[] seg = new double[6];
		LineShape line = getLineReference();
		int count = line.getPointCount();

		System.out.print("LEN=" + count);
		PathIterator it = line.getPathIterator(null);
		int n = 0;
		while (it.isDone() == false) {
			it.currentSegment(seg);
			it.next();
			System.out.print(" [");
			System.out.print(df3.format(seg[0]));
			System.out.print(",");
			System.out.print(df1.format(seg[1]));
			System.out.print("]");
			n++;
			if (n == 10) {
				System.out.println();
				System.out.print("      ");
				n = 0;
			}
		}
		System.out.println();
	}

	public void resetFilter() {
		if (unmodified == null) {
			return; // no filter applied
		}
		LineShape curr_line = this.getLineReference();
		curr_line.setPoints(copyPoints(unmodified));
	}

}
