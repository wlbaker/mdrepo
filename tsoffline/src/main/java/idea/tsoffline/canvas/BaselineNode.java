package idea.tsoffline.canvas;

import java.awt.Color;
import java.awt.Paint;

import org.piccolo2d.PCamera;
import org.piccolo2d.extras.nodes.PComposite;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PBounds;

public class BaselineNode extends PComposite {
	PPath line = null;

	public BaselineNode(PCamera cam) {

		PBounds vb = cam.getViewBounds();
		double min = vb.getMinY();
		double max = vb.getMaxY();
		PBounds bounds = cam.getBounds();
		double bw = bounds.getWidth();
		
		Paint color = Color.GREEN;

		line = PPath.createLine(0, 0, bw, 0);
		line.setPickable(false);
		line.setPaint(color);
		line.setStrokePaint(color);

		PText point = null;
		point = new PText("HERE");
		point.setPickable(false);
		point.setTextPaint(color);
		point.setY(0);
		point.setX(bw);

//		txt_val.rotate(-Math.PI / 2);
//		txt_val.setTextPaint(color); // theme_annotation_text_color);
//
//		txt_seq.translate(-(3 * seqNo.length()),
//				txt_bounds.height + TsPSwingCanvas.TOP_MARGIN - TsPSwingCanvas.TOP_ANNOTATION_MARGIN - 2);

		setPickable(false);
		
		if (line != null) {
			addChild(line);
		}
		if (point != null) {
			addChild(point);
		}

		translate( 20, cam.getY() + 100);
	}
}
