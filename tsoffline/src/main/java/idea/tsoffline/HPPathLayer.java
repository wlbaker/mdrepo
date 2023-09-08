package idea.tsoffline;

import java.awt.Paint;
import java.awt.Shape;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.ListIterator;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.extras.util.LineShape;
import org.piccolo2d.extras.util.MutablePoints;
import org.piccolo2d.extras.util.XYArray;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PPaintContext;

import idea.message.StreamID;
import idea.schema.rp.RpMetric;
import uk.me.berndporr.api.FilterInterface;
import idea.ts.TsFilter;
import idea.tsoffline.canvas.HPPath;

public class HPPathLayer extends PLayer {

	public List<HPPath> unfiltered_children;

	@Override
	public void setVisible(boolean isVisible) {
		// DEBUG SUPPORT ONLY
		super.setVisible(isVisible);
		System.out.println( this.getName() + " visible: " + isVisible );
		if( !isVisible ) {
			System.out.println( "SETTING INVISIBLE!");
		}
	}

	@Override
	public Paint getPaint() {
		// placed here for debugging
		Paint p = super.getPaint();
		return p;
	}

	public HPPathLayer(RpMetric sig, StreamID sid, String devName) {
		setPaint(null); // Color.GREEN);

		String loc = (sig == null) ? "NONE" : sig.getLocation();
		String name = (sig == null) ? "NONE" : sig.getName();
		if (name == null) {
			name = sig.getCode();
		}
		if (name == null) {
			name = loc;
		}
		setName(devName + "/" + name);
		addAttribute("dev_name", devName); // attributes to be saved in xml file
											// to enable reloading
		addAttribute("sig_name", name); // attributes to be saved in xml file to
										// enable reloading
		addAttribute("sig_loc", loc); // attributes to be saved in
										// xml file to enable
										// reloading
		addAttribute("sid_name", sid); // attributes to be saved in xml file to
										// enable reloading
		addAttribute("sig", sig); // this one is just handy to have!

		char code = 'W';
		if (sid != null) {
			code = (char) sid.getCode();
		}
		addAttribute("sid", "" + code); // this one is just handy to have!

	}

	/**
	 * Computes the full bounds and stores them in dstBounds, if dstBounds is null,
	 * create a new Bounds and returns it.
	 * 
	 * @param dstBounds output parameter where computed bounds will be stored
	 * @return the computed full bounds
	 */
	// public PBounds computeFullBounds(final PBounds dstBounds) {
	// final PBounds result;
	// if (dstBounds == null) {
	// result = new PBounds();
	// }
	// else {
	// result = dstBounds;
	// result.reset();
	// }
	//
	// result.add(getBoundsReference());
	// localToParent(result);
	// return result;
	// }

	/**
	 * Callback that receives notification of repaint requests from nodes in this
	 * node's tree.
	 * 
	 * @param localBounds region in local coordinations the needs repainting
	 * @param childOrThis the node that emitted the repaint notification
	 */
	// public void repaintFrom(final PBounds localBounds, final PNode
	// childOrThis) {
	// if (childOrThis != this) {
	// Rectangle2D.intersect(getBoundsReference(), localBounds, localBounds);
	// super.repaintFrom(localBounds, childOrThis);
	// }
	// else {
	// super.repaintFrom(localBounds, childOrThis);
	// }
	// }

	/**
	 * Paint's this node as a solid rectangle if paint is provided, clipping
	 * appropriately.
	 * 
	 * @param paintContext context into which this node will be painted
	 */
	protected void paint(final PPaintContext paintContext) {
		// paintContext.pushTransform( this.getTransform() );
		// final Paint p = getPaint();
		//
		// if (p != null) {
		// final Graphics2D g2 = paintContext.getGraphics();
		// g2.setPaint(p);
		// g2.fill(getPathReference());
		// }
		// paintContext.pushClip(getPathReference());
		// if( getPaint() == null ) {
		// setPaint( getStrokePaint() );
		// }

		// PCamera camera = paintContext.getCamera();
		// System.err.println( getName() + " PAINT=" + getPaint() );
		// System.err.println(getName() + " IDRAWTHELAYERRECT: " +
		// getPathReference() + " RECT: " + this.getBoundsReference());
		// if (getStroke() != null && getStrokePaint() != null) {
		// PBounds bounds = this.getBounds();
		//
		// final Graphics2D g2 = paintContext.getGraphics();
		// AffineTransform tr0 = g2.getTransform();
		// Paint p0 = g2.getPaint();
		// g2.setTransform( camera.getLocalToGlobalTransform(null) );
		// g2.setPaint(null);
		// g2.setStroke(getStroke());
		// g2.draw(bounds); // getPathReference() );
		//
		// g2.setTransform(tr0);
		// g2.setPaint(p0);
		// }
		super.paint(paintContext);
	}

	/**
	 * Paints a border around this node if it has a stroke and stroke paint
	 * provided.
	 * 
	 * @param paintContext context into which the border will be drawn
	 */
	protected void paintAfterChildren(final PPaintContext paintContext) {
		// paintContext.popClip(getPathReference());
		// paintContext.popTransform( null );
		// System.err.println(getName() + " IDRAWTHELAYERRECT: " +
		// getPathReference() + " RECT: " + this.getBoundsReference());
		// if (getStroke() != null && getStrokePaint() != null) {
		// final Graphics2D g2 = paintContext.getGraphics();
		// g2.setPaint(getStrokePaint());
		// g2.setStroke(getStroke());
		// g2.draw(getPathReference());
		// }
	}

	private Shape getPathReference() {
		return this.getBounds();
	}

	/**
	 * Paint this node and all of its descendants. Most subclasses do not need to
	 * override this method, they should override <code>paint</code> or
	 * <code>paintAfterChildren</code> instead.
	 * 
	 * @param paintContext the paint context to use for painting this node and its
	 *                     children
	 */
	public void fullPaint(final PPaintContext paintContext) {
		if (getVisible() && fullIntersects(paintContext.getLocalClip())) {
			PAffineTransform transform = this.getTransformReference(false);
			float transparency = this.getTransparency();
			List<HPPath> children = this.getChildrenReference();

			paintContext.pushTransform(transform);
			paintContext.pushTransparency(transparency);

			if (!getOccluded()) {
				paint(paintContext);
			}

			final int count = getChildrenCount();
			// 14FEB17: This looks like a performance issue when layer has 10's
			// of 1000's of nodes
			//
			// for (int i = 0; i < count; i++) {
			// final PNode each = (PNode) children.get(i);
			// each.fullPaint(paintContext);
			// }

			if (count > 0) {
				for (final HPPath each : children) { // 14FEB17: updated version
					each.fullPaintX(this.getPaint(), paintContext);
				}
			}

			paintAfterChildren(paintContext);

			paintContext.popTransparency(transparency);
			paintContext.popTransform(transform);
		}
	}

	public String getFilter() {
		return (String) getAttribute("@filterName");
	}

	public void applyFilter(TsFilter filter, FilterInterface filterImpl) {
		String filterName = filter.getName();
		addAttribute("filter", filter);
		addAttribute("@filterName", filterName);

		if (getChildrenCount() > 0) {

			applyForwardFilter(filter, filterImpl);
			Boolean bidir = filter.isBidirectional();
			if (bidir != null && bidir) {
				applyReverseFilter(filter, filterImpl);
			}
		}

	}

	protected void applyForwardFilter(TsFilter filter, FilterInterface filterImpl) {

		ListIterator<PNode> it = this.getChildrenIterator();
		HPPath prev = null;
		double[] prev_xy = null;
		HPPath curr = (HPPath) it.next();
		while (curr != null) {

			double[] xy = HPPath.filter(curr, filterImpl);

			if (prev != null) {
				// tie together the loose ends
				int pos = prev_xy.length - 2;
				prev_xy[pos++] = xy[0];
				prev_xy[pos++] = xy[1];
				MutablePoints points = new XYArray(prev_xy);
				LineShape line = prev.getLineReference();
				line.setPoints(points);
			}

			prev = curr;
			prev_xy = xy;
			curr = (it.hasNext()) ? (HPPath) it.next() : null;
		}

		if (prev != null) {
			// last path segment...which perhaps should be properly filtered
			int pos1 = prev_xy.length - 2;
			int pos0 = prev_xy.length - 4;
			prev_xy[pos1++] = prev_xy[pos0++];
			prev_xy[pos1++] = prev_xy[pos0++];
			MutablePoints points = new XYArray(prev_xy);
			LineShape line = prev.getLineReference();
			line.setPoints(points);
		}

	}

	protected void applyReverseFilter(TsFilter filter, FilterInterface filterImpl) {

	    List children = getChildrenReference();
	    
	    /* create a copy of the children */
	    List items = new ArrayList<>( children );  
	    
		/* reverse the list */
		Collections.reverse(items);
		
		ListIterator<PNode> it = items.listIterator();
		HPPath prev = null;
		double[] prev_xy = null;
		HPPath curr = (HPPath) it.next();
		while (curr != null) {

			double[] xy = HPPath.reverseFilter(curr, filterImpl);

			if (prev != null) {
				// tie together the loose ends
				int pos = prev_xy.length - 2;
				prev_xy[0] = xy[pos++];
				prev_xy[1] = xy[pos++];
				MutablePoints points = new XYArray(prev_xy);
				LineShape line = prev.getLineReference();
				line.setPoints(points);
			}

			prev = curr;
			prev_xy = xy;
			curr = (it.hasNext()) ? (HPPath) it.next() : null;
		}

		if (prev != null) {
			// last path segment...which perhaps should be properly filtered
			int pos1 = prev_xy.length - 2;
			int pos0 = prev_xy.length - 4;
			prev_xy[pos1++] = prev_xy[pos0++];
			prev_xy[pos1++] = prev_xy[pos0++];
			MutablePoints points = new XYArray(prev_xy);
			LineShape line = prev.getLineReference();
			line.setPoints(points);
		}

	}


	public void dump() {
		ListIterator<PNode> it = this.getChildrenIterator();
		while (it.hasNext()) {
			HPPath curr = (HPPath) it.next();
			curr.dump();
		}
	}

	public void resetFilter() {
		addAttribute("filter", null);
		addAttribute("@filterName", null);

		ListIterator<PNode> it = this.getChildrenIterator();
		while (it.hasNext()) {
			HPPath curr = (HPPath) it.next();
			curr.resetFilter();
		}
	}
}
