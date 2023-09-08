package idea.tsoffline.tspico;

import java.awt.Color;
import java.awt.geom.AffineTransform;
import java.awt.geom.Dimension2D;
import java.util.Observable;
import java.util.Observer;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.event.PBasicInputEventHandler;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;

import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.AppConstants;

class PObservable extends Observable {

	public void setChanged() {
		super.setChanged();
	}
}

@Slf4j
public class XScrollbarEventTool extends PBasicInputEventHandler {

	PObservable oable = new PObservable();

	/*
	 * scroll direction
	 */
	public static final int HORIZONTAL = 2;
	public static final int VERTICAL = 3;

	/*
	 * actions
	 */
	public static final int SLIDE = 100;
	public static final int EXPAND_UP = 99;
	public static final int EXPAND_DOWN = 101;

	private PNode stickyNode;
	private int dir;
	private PPath bar;
	private PPath down;
	private PPath up;
	private PBounds initial_bounds;
	private PLayer layer;
	
	@Getter
	private PAffineTransform initialTransform;

	private PAffineTransform sig_transform;

	@Getter
	private AffineTransform finalTransform;

	public XScrollbarEventTool(int scrollDir) {
		this.dir = scrollDir;
	}

	public void mousePressed(PInputEvent ev) {

		PNode aNode = ev.getPickedNode();

		if (aNode instanceof PCamera) {
			System.out.println("dont pick camera");

			ev.setHandled(true);
			return;
		}

		initial_bounds = bar.getBounds();

		if (stickyNode != null) {
			stickyNode.setPaint(Color.green);
		}
		stickyNode = aNode;

		aNode.setPaint(Color.orange);
		aNode.repaint();
		ev.setHandled(true);
	}

	public void mouseDragged(PInputEvent ev) {
		PNode aNode = ev.getPickedNode();

		// dont drag camera
		if (aNode instanceof PCamera) {
			ev.setHandled(true);
			return;
		}

		Dimension2D delta = ev.getDeltaRelativeTo(aNode);
		double dw = 0;
		double dh = 0;
		if (dir == VERTICAL) {
			dh = delta.getHeight();
		} else if (dir == HORIZONTAL) {
			dw = delta.getWidth();
		}
		aNode.translate(dw, dh);

		Integer action = (Integer) aNode.getAttribute("action");
		
		if (action == null) {
			log.error("Expecting /action/ code with node: {} obj: {}", aNode.getName(), aNode );
		} else if (action == EXPAND_DOWN) {
			bar.setHeight(bar.getHeight() - dh);
			bar.setY(bar.getY() + dh);
		} else if (action == EXPAND_UP) {
			bar.setHeight(bar.getHeight() + dh);
		} else if (action == SLIDE) {
			if (dir == VERTICAL && up != null) {
				up.setY(up.getY() + dh);
				down.setY(down.getY() + dh);
			}
		}

		sync_graphs();

		// printEventCoords(ev);
		ev.setHandled(true);
	}

	private AffineTransform create_transform(PBounds initial_bounds, PBounds final_bounds) {

		double m00 = 1, tx = 0;
		double m11 = 1, ty = 0;

		// let (x1, y1) --> (x1,y2) 
		// and (xa, ya) --> (xa, yb)
		// then
		//  m11 = (y2-yb) / (y1-ya)
		if (dir == VERTICAL) {
			double y_1 = initial_bounds.y;
			double y_2 = final_bounds.y;
			double y_a = initial_bounds.y + initial_bounds.height;
			double y_b = final_bounds.y + final_bounds.height;

			m11 = (y_2 - y_b) / (y_1 - y_a);
			ty = y_2 - m11 * y_1;
		}

		if (dir == HORIZONTAL) {
			double x_1 = initial_bounds.x;
			double x_2 = final_bounds.x;
			double x_a = initial_bounds.x + initial_bounds.width;
			double x_b = final_bounds.x + final_bounds.width;

			m00 = (x_2 - x_b) / (x_1 - x_a);
			tx = x_2 - m00 * x_1;
			
			tx = -tx;  // hmmm  Sliding the wrong direction for my purposes.
		}

		AffineTransform tr = new AffineTransform(m00, 0, 0, m11, tx, ty);

		return tr;
	}

	public void mouseReleased(PInputEvent ev) {
		PNode aNode = ev.getPickedNode();

		// dont drag camera
		if (aNode instanceof PCamera) {
			ev.setHandled(true);
			return;
		}

		//		PDimension delta = ev.getDeltaRelativeTo(aNode);
		//		

		sync_graphs();

		// notify parent to redraw axis layer
		oable.setChanged();
		oable.notifyObservers( null );

		ev.setHandled(true);
	}

	private void sync_graphs() {
		PBounds final_bounds = new PBounds(bar.getX(), bar.getY(), bar.getWidth(), bar.getHeight());
		// System.out.println("aNode transform: " + aNode.getTransform() );
		bar.getTransform().transform(final_bounds, final_bounds);

		finalTransform = create_transform(initial_bounds, final_bounds);

		AffineTransform sig_tr = new AffineTransform(); // identity
		sig_tr.concatenate(initialTransform);
		sig_tr.concatenate(finalTransform);

		sig_transform.setTransform(sig_tr);

		oable.setChanged();
		oable.notifyObservers( sig_tr );
		layer.repaint(); // necessary if mouse continues to drag while outside the scrollbar area proper

	}

	public String getStickyCode() {
		String code = null;
		if (stickyNode != null) {
			PNode source = (PNode) stickyNode.getAttribute("source");
			if (source != null) {
				code = (String) source.getAttribute("txt");
			}
		}
		return code;
	}

	public void setStickyCode(String code) {
		if (stickyNode != null) {
			PNode source = (PNode) stickyNode.getAttribute("source");
			if (source != null) {
				source.addAttribute("txt", code);
			}
			PText label = (PText) stickyNode.getAttribute("label");
			if (label == null) {
				log.error("Unexpected null label for stickyNode: {}", stickyNode);
			} else {
				label.setText(code);
				label.repaint();
			}
		}
		return;
	}

	public void clearStickyNode() {
		stickyNode = null;
	}

	public void buildSliders(PAffineTransform sig_transform, PLayer layer, double cam_w, double data_min, double data_max, double dy, Color sliderColor ) {
		double data_height = data_max - data_min;

		this.layer = layer;
		this.setTransformable(sig_transform);

		double d_factor = -1.15;
		double u_factor = 0.15;

		if( dy < 0 ) {
			dy = -dy;
		}
		
		layer.removeAllChildren();
		bar = PPath.createRectangle(0, data_min, cam_w - 2, data_height);
		bar.setPaint(Color.LIGHT_GRAY);
		bar.setStrokePaint(sliderColor);
		bar.setStroke(AppConstants.getDefaultSignalStroke());
		bar.addAttribute("action", XScrollbarEventTool.SLIDE);

		down = PPath.createRectangle(0, data_min + d_factor * dy, cam_w - 2, dy);
		down.setPaint(Color.RED);
		down.setStrokePaint(Color.BLACK);
		down.setStroke(AppConstants.getDefaultSignalStroke());
		down.addAttribute("action", XScrollbarEventTool.EXPAND_DOWN);

		up = PPath.createRectangle(0, data_max + u_factor * dy, cam_w - 2, dy);
		up.setPaint(Color.GREEN);
		up.setStrokePaint(Color.BLACK);
		up.setStroke(AppConstants.getDefaultSignalStroke());
		up.addAttribute("action", XScrollbarEventTool.EXPAND_UP);

		layer.addChild(bar);
		layer.addChild(up);
		layer.addChild(down);

	}

	public void addObserver(Observer o) {
		oable.addObserver(o);
	}

	public void deleteObserver(Observer o) {
		oable.deleteObserver(o);
	}

	public void setBar(PPath bar) {
		this.bar = bar;
	}

	public void setTransformable(PAffineTransform sig_transform) {
		initialTransform = new PAffineTransform(sig_transform);
		// make a copy
		this.sig_transform = sig_transform;
	}

	public void setScrollbarLayer(PLayer layer) {
		this.layer = layer;
	}

}
