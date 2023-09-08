package idea.tsoffline;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Stroke;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.util.PAffineTransform;

import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.canvas.LinkedNode;


class Reversed<T> implements Iterable<T> {
	private final List<T> original;

	public Reversed(List<T> original) {
		this.original = original;
	}

	@Override
	public Iterator<T> iterator() {
		final ListIterator<T> i = original.listIterator(original.size());

		return new Iterator<T>() {
			@Override
			public boolean hasNext() {
				return i.hasPrevious();
			}

			@Override
			public T next() {
				return i.previous();
			}

			@Override
			public void remove() {
				i.remove();
			}
		};
	}

	// this code konks out int jdk6 under eclipse compiler...T is non-static...can't reference from static function
	//    public static Reversed<T> reversed(List<T> original) {
	//        return new Reversed<T>(original);
	//    }
}

@Slf4j
public class LayerUtil {

	static Stroke line_pen = new BasicStroke((float) 0.01, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
	private static int verbose = 1;


	public static PNode addEvent(PLayer eventLayer, Color color, double x, double y, String code ) {


		LinkedNode path = new LinkedNode( null );

		path.setStroke(line_pen);
		path.setPaint(Color.BLUE);
		path.setStrokePaint(color);
		path.setX(x);
		path.setY(y);

		path.setWidth(1);
		path.setHeight(1);

		// quality and detector values from AESOP
		if (code != null) {
			path.addAttribute("txt", code);
		}


		eventLayer.addChild(path);


		return path;
	}

	public static PNode addFiducialPoint(PLayer l, double x, double y, String code ) {

		PNode node = addEvent(l, Color.RED, x, y, code);

		l.repaint();

		return node;
	}

	public static AffineTransform getTransformForCamera(PCamera cam, double start_x, double end_x, double maxXMag) {

		Rectangle2D.Double camera_r = cam.getBounds();
		
		double sx = camera_r.getWidth() / (end_x - start_x);
		double sy = -1;
		
		if (maxXMag > 0 && sx > maxXMag) {
			sx = maxXMag; // keep the user from doing something he doesn't
		}
		
		double txx = camera_r.getX() - sx * start_x;
		double tyy = camera_r.getHeight() +  cam.getY();
		
		AffineTransform m = new PAffineTransform(sx, 0.0f, 0.0f, sy, txx, tyy);
		return m;
	}


	public static AffineTransform getTransformForLayer( Rectangle2D.Double camera_r, Point2D gpt0, Point2D gpt1, double maxXMag) {

		double magyy = camera_r.getHeight() / (gpt1.getY() - gpt0.getY());
		double magxx = camera_r.getWidth() / (gpt1.getX() - gpt0.getX());
		
		if (maxXMag > 0 && magxx > maxXMag) {
			magxx = maxXMag; // keep the user from doing something he doesn't
			// want
		}
		
		double txx = camera_r.getX() - magxx * gpt0.getX();
		double tyy = camera_r.getY() - magyy * gpt0.getY();
		
		AffineTransform m = new PAffineTransform(magxx, 0.0f, 0.0f, magyy, txx, tyy);
		return m;
	}

	public static Double find_next_anomoly(List<PNode> nodes, double data_x, double tolerance, int direction) {

		assert (direction == 0) : "Which way did he go?  Which way did he go?";

		Double anomoly_x = null;
		double last_rri, last_x;
		double rri = 0;
		double x = 0;

		System.out.println("starting at x=" + data_x);

		int skip = 2; // skip at least two points inside our valid range

		Iterator<PNode> it;

		if (direction > 0) {
			it = nodes.iterator();
		} else {
			Reversed<PNode> l = new Reversed<PNode>(nodes);
			it = l.iterator();
		}

		while (it.hasNext()) {
			PNode node = it.next();
			if (node instanceof LinkedNode) { // data source for RRI's
				last_rri = rri;
				last_x = x;
				rri = node.getY();
				x = node.getX();

				if ((node.getX() < data_x) && (direction > 0)) {
					// node out of range going forward
				} else if ((node.getX() > data_x) && (direction < 0)) {
					// node out of range in reverse
				} else if (skip > 0) {
					// skip a couple in range to get last_rri populated correctly
					skip--;
				} else {

					double delta = last_rri * tolerance;

					System.out.println(" process: " + node.getX() + " delta=" + delta);

					if (last_rri + delta < rri || last_rri - delta > rri) {
						// go to the middle of the anomoly if it is not too wide
						double anomoly_width = x - last_x;
						if (anomoly_width > 3) { // more than 3 secs means this is an extended error...go to start
							anomoly_width = 0;
						}
						anomoly_x = last_x; // + anomoly_width / 2;
						break;
					}

				}
			}
		}

		return anomoly_x;
	}


}
