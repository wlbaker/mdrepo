package idea.tsoffline.tspico;

import java.awt.Color;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

import org.piccolo2d.PCamera;
import org.piccolo2d.PNode;
import org.piccolo2d.event.PDragSequenceEventHandler;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.extras.event.PNotification;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;

import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.AppConstants;
import idea.tsoffline.canvas.TsPSwingCanvas;

@Slf4j
public class SelectorTool extends PDragSequenceEventHandler {

	public static final String DRAG_COMPLETE_NOTIFICATION = "DRAG_COMPLETE_NOTIFICATION";

	private PPath marquee = null;
	private PNode marqueeParent = null; // Node that marquee is added to as a
										// child
	private Rectangle2D selected_r;
	private Point2D canvasPressPt = null; // PointF.Empty;

	private PInputEvent startEvent;

	private int z_pos;

	private TsPSwingCanvas canvas;

	public SelectorTool(TsPSwingCanvas canvas, PNode marqueeParent) {
		this.canvas = canvas;
		this.marqueeParent = marqueeParent;
	}

	// ****************************************************************
	// Dragging - Overridden methods from PDragSequenceEventHandler
	// ****************************************************************

	// / <summary>
	// / Overridden. See <see cref="PDragSequenceEventHandler.OnStartDrag">
	// / PDragSequenceEventHandler.OnStartDrag</see>.
	// / </summary>
	@Override
	protected void startDrag(PInputEvent e) {
		if( e.getCamera() == null || e.getCamera().getRoot() == null ) {
			log.error("Cannot drag while loading new data (?)  Null camera/root.");
			return;
		}
		super.startDrag(e);

		TsPSwingCanvas canv = (TsPSwingCanvas) e.getComponent();
		PCamera cam = canv.getCameraAtMousePos();

		if (cam == null) {
			marquee = null;
			canvasPressPt = null;
			startEvent = null;
			selected_r = null;
		} else {
			this.startEvent = e;

			canvasPressPt = e.getCanvasPosition();
			selected_r = null; // Rectangle2D.Empty;

			initializeMarquee(e);
			e.setHandled(true);
		}
	}

	@Override
	public void mouseReleased(PInputEvent event) {
		super.mouseReleased(event);
		if( marquee != null ) {
			log.error("FIXME: do we have a sticky drag?  See notes in drag()");
			log.error("FIXME: problem appears to be triggered by right-click on popup menu in legendtool");
			endDrag(event);
		}
	}

	// / <summary>
	// / Overridden. See <see cref="PDragSequenceEventHandler.OnDrag">
	// / PDragSequenceEventHandler.OnDrag</see>.
	// / </summary>
	@Override
	protected void drag(PInputEvent e) {
		super.drag(e);

		if( marquee == null ) {
			 // PICOLLO BUG? sometimes missing start drag message
			 startDrag(e);
			 
			 // FIXME: well, when this happens, you may also miss the end-drag message.
			 // Check out: PDragSequenceEventHandler::mouseReleased(final PInputEvent event) 
			 // line 3: if (sequenceInitiatedButton == event.getButton()) {
			 // sometimes it gets sequenceInitiatedButton = 3 when you are pressing button 1?
			 
		}
		updateMarquee(e);
	}

	// / <summary>
	// / Overridden. See <see cref="PDragSequenceEventHandler.OnEndDrag">
	// / PDragSequenceEventHandler.OnEndDrag</see>.
	// / </summary>
	@Override
	protected void endDrag(PInputEvent e) {
		
		super.endDrag(e);

		if (isMarqueeSelection(e)) {
			endMarqueeSelection(e);
		}

		selectionChanged( null );
	}

	/*
	 * DO NOT DELETE...this method referenced by name in listener above
	 */
	public void selectionChanged(PNotification notfication) {
		PCamera cam = canvas.getBandCameras().get(0);
		PBounds ref = cam.getViewBounds();
		PAffineTransform m = cam.getViewTransform();

		Rectangle2D r = this.getSelectedRect();
		
		if( canvasPressPt == null ) {
			// spurious activity during startup and loading caused by random clicks
			return;
		}

		if (r == null || r.getWidth() < 5 || r.getHeight() < 5) {
			
			Point2D view_pos = m.inverseTransform( canvasPressPt, null);
			// zoom (scroll) too small, treat as a simple click
			canvas.updateSelection( view_pos.getX() );
			return;
		}
		Point2D mouse0 = new Point2D.Double(r.getX(), r.getY());
		Point2D mouse1 = new Point2D.Double(r.getX() + r.getWidth(), r.getY() + r.getHeight());

		PBounds mrect = cam.getBounds();

		if (mrect.contains(mouse0) && mrect.contains(mouse1)) {
			// mouse point is inside the signal camera
		} else {
			boolean b0 = mrect.contains(mouse0);
			boolean b1 = mrect.contains(mouse1);
			// mouse point is outside the signal camera
			// return;
			System.err.println("Canvas BOUNDS CHECK error..rect=" + mrect + " m0=" + mouse0 + " m1=" + mouse1);
		}

		Rectangle2D data_r = m.inverseTransform(r, null);

		double y = ref.getY();
		double h = ref.getHeight();

		double y1 = y;
		double y2 = y + h;

		log.error("FIXME: SELECTIONCHANGE FLIP removed");
		// if (flip) {
		y = y1;
		y1 = y2;
		y2 = y;
		// }

//		Point2D pt0 = new Point2D.Double(data_r.getX(), y2);
//		Point2D pt1 = new Point2D.Double(data_r.getX() + data_r.getWidth(), y1);

		canvas.zoomCameraToXScale(cam, data_r.getX(), data_r.getX() + data_r.getWidth());
	}

	// ****************************************************************
	// Additional Methods - Other miscellaneous methods.
	// ****************************************************************

	// / <summary>
	// / Returns a value indicating whether or not the input event was modified
	// / with a <c>Shift</c> key, in which case multiple selections will be
	// / allowed.
	// / </summary>
	// / <param name="e">A PInputEventArgs that contains the event data.</param>
	// / <returns>
	// / True if the input event was modified with a shift key; otherwise false.
	// / </returns>
	public boolean isOptionSelection(PInputEvent e) {
		return e.isShiftDown();
	}

	// / <summary>
	// / Returns a value indicating whether the event represents a marquee
	// / selection or a normal selection.
	// / </summary>
	// / <param name="e">A PInputEventArgs that contains the event data.</param>
	// / <returns>
	// / True if the input event represents a marquee selection; otherwise,
	// false.
	// / </returns>
	public boolean isMarqueeSelection(PInputEvent e) {
		return true;
	}

	// / <summary>
	// / Sets some initial values for the marquee including it's brush and pen.
	// / </summary>
	// / <param name="e">A PInputEventArgs that contains the event data.</param>
	protected void initializeMarquee(PInputEvent e) {
		marquee = PPath.createRectangle(canvasPressPt.getX(), canvasPressPt.getY(), 0, 0);
		// marquee.setTransparency(0.0f);
		// ?? marquee.Brush = marqueeBrush;
		marquee.setPaint(Color.RED);
		// marquee.setTransparency(0.5f);
		marquee.setStrokePaint(Color.BLACK);
		marquee.setStroke(AppConstants.getDefaultSignalStroke());

		marqueeParent.addChild(z_pos, marquee);

	}

	// / <summary>
	// / Update the marquee bounds based on the given event data.
	// / </summary>
	// / <param name="e">A PInputEventArgs that contains the event data.</param>
	protected void updateMarquee(PInputEvent e) {
		if (marquee == null) {
			// this happens with a drag outside of band cameras
			return;
		}
		selected_r = new Rectangle2D.Float((float) canvasPressPt.getX(), (float) canvasPressPt.getY(), 0, 0);
		selected_r.add(e.getCanvasPosition());

		selected_r = marquee.globalToLocal(selected_r);
		marquee.reset();
		// setSafeMarqueePen((float) selected_r.getWidth(), (float)
		// selected_r.getHeight());
		PPath rect = PPath.createRectangle((float) selected_r.getX(), (float) selected_r.getY(),
				(float) selected_r.getWidth(), (float) selected_r.getHeight());
		marquee.setPaint(Color.RED);
		marquee.setStrokePaint(Color.BLACK);
		marquee.setStroke(AppConstants.getDefaultSignalStroke());
		marquee.addChild(rect);

	}

	// / <summary>
	// / Ends a marquee selection sequence.
	// / </summary>
	// / <param name="e">A PInputEventArgs that contains the event data.</param>
	// / <remarks>
	// / <b>Notes to Inheritors:</b> Subclasses can override this method to be
	// notified
	// / at the end of a marquee selection sequence.
	// / <para>
	// / Overriding methods must still call <c>base.EndMarqueeSelection()</c>
	// for correct
	// / behavior.
	// / </para>
	// / </remarks>
	protected void endMarqueeSelection(PInputEvent e) {
		// Remove marquee
		if (marquee != null) {
			marquee.removeFromParent();
			marquee = null;
		}
	}

	public PNode getParent() {
		return marqueeParent;
	} // probably a layer

	public Rectangle2D getSelectedRect() {
		return selected_r;
	} // the selected box

	public PInputEvent getStartEvent() {
		return startEvent;
	}

	public void setZIndex(int z_pos) {
		this.z_pos = z_pos;
	}
}