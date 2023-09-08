package idea.tsoffline.canvas;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Stroke;
import java.awt.geom.Ellipse2D;
import java.awt.geom.GeneralPath;
import java.awt.geom.Rectangle2D;
import java.util.List;

import org.piccolo2d.PNode;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;
import org.piccolo2d.util.PPaintContext;

@SuppressWarnings("serial")
public class LinkedNode extends PPath.Float {

	private static final BasicStroke DEFAULT_STROKE = new BasicStroke(1f);
	private static final Color DEFAULT_STROKE_PAINT = Color.black;
	public static final int FIDUCIAL = 0;
	public static final int SIGNAL = 1;

	private static int drawMode;
	private LinkedNode prev;

	public LinkedNode(LinkedNode prev) {
		super(new Ellipse2D.Float(0, 0, 2, 2));
		setStroke(DEFAULT_STROKE);
		setStrokePaint(DEFAULT_STROKE_PAINT);
		// path = new GeneralPath();

		this.prev = prev;
		setName("sw0");
	}

	@Override
	public void fullPaint(PPaintContext paintContext) {
		// THIS ROUTINE HERE FOR DEBUG PURPOSES ONLY
		// super.fullPaint(paintContext);
		PAffineTransform transform = this.getTransform();
		float transparency = this.getTransparency();
		List children = this.getChildrenReference();
		boolean vis = getVisible();
		Rectangle2D clip = paintContext.getLocalClip();
		boolean intersects = fullIntersects(clip);
		// FIXME: I dont know why this routine is not called consistently!
		//System.out.print("@"); // clip=" + clip + " intersects=" + intersects + " o="+ getAttribute("userObject") + " x=" + getX() + " bounds=" + getFullBoundsReference() );
		if (vis && intersects) {
			paintContext.pushTransform(transform);
			paintContext.pushTransparency(transparency);

			if (!getOccluded()) {
				paint(paintContext);
			}

			final int count = getChildrenCount();
			for (int i = 0; i < count; i++) {
				final PNode each = (PNode) children.get(i);
				each.fullPaint(paintContext);
			}

			paintAfterChildren(paintContext);

			paintContext.popTransparency(transparency);
			paintContext.popTransform(transform);
		}
	}

	@Override
	public PBounds getBounds() {
		System.out.println( "  bounds-->" + this);
		return super.getBounds();
	}

	@Override
	public PBounds getBoundsReference() {
		PBounds bounds = super.getBoundsReference();
		// double x = bounds.getX();
		// bounds.setRect(x, y, width, height)
		// System.out.println( "  [get bounds] " + bounds.getX() + " " + bounds.getY() + " " + bounds.getWidth() + "  " + bounds.getHeight());
		return bounds;
	}

	@Override
	public String toString() {

		return "[SwitchableNode] x=" + getX() + " y=" + getY() + " w=" + getWidth() + " h=" + getHeight();
	}

	@Override
	public boolean fullIntersects(final Rectangle2D parentBounds) {
		// THIS ROUTINE HERE FOR DEBUG PURPOSES ONLY
		if (parentBounds == null) {
			return true;
		}
		return getFullBoundsReference().intersects(parentBounds);
		//		return super.fullIntersects(parentBounds);
		//		if (parentBounds == null) {
		//			return true;
		//		}
		//		double x = getX();
		//		double endX = x + getWidth();
		//
		//		boolean intersects = (x > parentBounds.getX()) && (x < parentBounds.getMaxX());
		//		if (intersects == false) {
		//			intersects = (endX > parentBounds.getX()) && (endX < parentBounds.getMaxX());
		//		}
		//		return intersects;
	}

	/** {@inheritDoc} */
	@Override
	protected void paint(final PPaintContext paintContext) {
		// super.paint( paintContext );
		final Graphics2D g2d = paintContext.getGraphics();

		Stroke stroke = getStroke();
		Paint strokePaint = Color.YELLOW;

		//PCamera camera = paintContext.getCamera();
		//camera.getLayer(index)
		if (stroke != null && strokePaint != null) {
			g2d.setPaint(strokePaint);
			g2d.setStroke(stroke);

			GeneralPath path = new GeneralPath();
			
//			if (drawMode == FIDUCIAL) {
//				path.moveTo(getX(), getY() + 10000000);
//				path.lineTo(getX(), getY() - 20000000);
//			} else if (drawMode == SIGNAL) {
				path.moveTo(getX(), getY());
				path.lineTo(getX() + getWidth(), getY() + getHeight());
//			}

			g2d.draw(path);

		}

	}

	public static void startDrawMode(int rriDrawMode) {
		// drawMode = rriDrawMode;
		drawMode = rriDrawMode % 2;

	}

	public static int getDrawMode() {
		return drawMode;
	}

}
