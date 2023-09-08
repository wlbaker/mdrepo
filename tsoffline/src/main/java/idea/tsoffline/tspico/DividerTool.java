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

class DObservable extends Observable {

	/*
	 * (non-Javadoc)
	 * @see java.util.Observable#setChanged()
	 * 
	 * Make the setChanged() function public
	 */
	public void setChanged() {
		super.setChanged();
	}
}

@Slf4j
public class DividerTool extends PBasicInputEventHandler {

	DObservable oable = new DObservable();

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

	public DividerTool(int scrollDir) {
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
		if (action == EXPAND_DOWN) {
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

		System.out.println("FIXME: sync_graphs() - b");

		// printEventCoords(ev);
		ev.setHandled(true);
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

		System.out.println("FIXME: sync_graphs() - a");

		// notify parent to redraw axis layer
		oable.setChanged();
		oable.notifyObservers( null );

		ev.setHandled(true);
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
		bar.addAttribute("action", DividerTool.SLIDE);

		down = PPath.createRectangle(0, data_min + d_factor * dy, cam_w - 2, dy);
		down.setPaint(Color.RED);
		down.setStrokePaint(Color.BLACK);
		down.setStroke(AppConstants.getDefaultSignalStroke());
		down.addAttribute("action", DividerTool.EXPAND_DOWN);

		up = PPath.createRectangle(0, data_max + u_factor * dy, cam_w - 2, dy);
		up.setPaint(Color.GREEN);
		up.setStrokePaint(Color.BLACK);
		up.setStroke(AppConstants.getDefaultSignalStroke());
		up.addAttribute("action", DividerTool.EXPAND_UP);

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
