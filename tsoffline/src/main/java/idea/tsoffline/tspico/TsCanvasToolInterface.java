package idea.tsoffline.tspico;

import java.awt.event.ComponentEvent;
import java.awt.geom.Point2D;

import org.piccolo2d.activities.PActivity;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;

public interface TsCanvasToolInterface {
	public void activityStarted(PActivity activity);
	public void activityFinished(PActivity activity);
	public void clear();
	public void componentResized(ComponentEvent e, float plot_width, float plot_h);
	public void draw(PBounds bounds, double visibleDataWidth, Point2D origin_data, PAffineTransform sigcam_view_m);
}
