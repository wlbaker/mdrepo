package idea.tsoffline.tspico;

import org.piccolo2d.event.PBasicInputEventHandler;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.extras.event.PNotificationCenter;


public class ScrollTool extends PBasicInputEventHandler {
	public static final String SCROLL_NOTIFICATION = "SCROLL_NOTIFICATION";

	private PInputEvent e;
	
	// private PointF viewZoomPoint;

	// / <summary>
	// / Constructs a new ISRZoomEventHandler.
	// / </summary>
	public ScrollTool() {
		getEventFilter().setAcceptsMouseWheelRotated(true);
	}

	@Override
	public void mouseWheelRotated(PInputEvent e) {
		// super.mouseWheelRotated(e);
		
		this.e = e;
		
		PNotificationCenter.defaultCenter().postNotification(
				SCROLL_NOTIFICATION, this);

	}

	public PInputEvent getInputEvent() {
		return e;
	}

}
