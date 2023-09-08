package idea.tsoffline.tspico;

import java.awt.Color;
import java.awt.Paint;
import java.awt.geom.Dimension2D;
import java.text.DecimalFormat;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.event.PBasicInputEventHandler;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.extras.nodes.PComposite;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;

import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.ts.TsoAnnotationEntryType;
import idea.tsoffline.AppModel;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.model.D;

class DD {
	// PNode line;
	PText label;
	PText txt_val;
	PNode src;
	PNode ellipse;

	public PText pos_val;
	PLayer layer;
	public double mouse_x;

	public DD(PLayer layer) {
		this.layer = layer;
	}

	public static double[][] getValuesInRange(PLayer dataLayer, double min_x, double max_x) {
		// TODO Auto-generated method stub
		return null;
	}
}

@Slf4j
public class XDraggableEventTool extends PBasicInputEventHandler {

	private static final DecimalFormat df2 = new DecimalFormat("#,##0.00");

	private float last_anno_x;
	private int dy;

	private double data_y;

	private DD sticky;

	private TsPSwingCanvas canv;
	Color theme_hilight_stickyColor = Color.WHITE;

	@Setter
	private PLayer editableLayer;

	public XDraggableEventTool(TsPSwingCanvas canv) {
		this.canv = canv;
	}

	public void mousePressed(PInputEvent ev) {
		PNode aNode = ev.getPickedNode();

		DD d = (DD) aNode.getAttribute("#d");
		if( sticky == null || d.src != sticky.src ) {
			editableLayer = d.layer;
			d.pos_val.setVisible(true);
			setStickyNode(d);
		}
		ev.setHandled(true);
	}

	private void setStickyNode(DD d) {
		clearStickyNode();
		if (d != null) {
			this.sticky = d;
			// NOTE: this code failed...the value 255,0,255 mapped to itself!
			// Color labelColor = (Color) sticky.pos_val.getPaint();
			// Color hilightColor = labelColor.brighter().brighter();

			// There is a good article on one approach: take the original
			// color and split it into a "brighter" and a "darker", which
			// would solve this problem.
			
			// http://stackoverflow.com/questions/2355157/dynamically-creating-colors-with-different-brightness
			sticky.ellipse.setPaint(theme_hilight_stickyColor);
		}
	}

	public void mouseDragged(PInputEvent ev) {
		PNode aNode = ev.getPickedNode();

		PLayer dataLayer = canv.getActiveLayer();

		Dimension2D delta = ev.getDeltaRelativeTo(aNode);
		aNode.translate(delta.getWidth(), 0);
		DD d = (DD) aNode.getAttribute("#d");

		if (d == null) {
			log.error("FIXME: cannot drag w/o a point");
			return;
		}

		// if (d != null) {
		// d.line.translate(delta.getWidth(), 0);
		// d.label.translate(delta.getWidth(), 0);
		// d.txt_val.translate(delta.getWidth(), 0);
		// }

		// 07-JAN-15 WLB: show Y value of active/associated signal
		if (dataLayer == null) {
			d.pos_val.setText(formatPosLabel( aNode ));
			// d.pos_val.setText( );
			data_y = Double.NaN;
		} else {
			double x1 = calcDataXPos(aNode);
			data_y = D.getValueAtPoint(dataLayer, x1);
			// String name = activeLayer.getName();

			if (d.txt_val != null) {
				d.txt_val.setText(df2.format(data_y));
			}
		}

		ev.setHandled(true);
	}

	private String formatPosLabel(PNode aNode) {
		double x = calcDataXPos(aNode);
		long msec = (long) (x * 1000);
		msec %= 1000;
		long sec = (long) x;
		long min = sec / 60;
		sec %= 60;

		return String.format("%02d:%02d.%03d", min, sec, msec);
	}

	public void mouseReleased(PInputEvent ev) {
		PNode aNode = ev.getPickedNode();
		if (aNode == null) {
			return; // ignore
		}

		
		DD d = (DD) aNode.getAttribute("#d");
		if (d == null) {
			log.error("Unexpected drag-release w/o sticky");
			return;
		}
		d.pos_val.setVisible(false);

		double x0 = d.src.getX();
		double x1 = calcDataXPos(aNode);
		d.src.setX(x1);

		AppModel.updateAnnotationData( null, d.src, null );
		AppModel.setDirty(true);

		canv.redrawAxisLayer(0);  // updates the B2B analysis info
		ev.setHandled(true);
	}

	private double calcDataXPos(PNode aNode) {

		PCamera sourceCamera = canv.getSignalCamera();
		PAffineTransform view_m = sourceCamera.getViewTransform();
		double x0 = aNode.getX() + aNode.getXOffset(); // 4 for half dot width
														// width??
		double x1 = (x0 - view_m.getTranslateX()) / view_m.getScaleX();
		return x1;
	}

	public String getStickyCode() {
		String code = null;
		if (sticky != null) {
			code = (String) sticky.src.getAttribute("txt");
		}
		return code;
	}

	public void setStickyCode(String code) {
		if (sticky != null) {
			log.error("FIXME: sticky...code? txt? other value?");
			sticky.src.addAttribute("txt", code);

			sticky.label.setText(code);
			sticky.label.repaint();

			TsoAnnotationEntryType entry = (TsoAnnotationEntryType) sticky.src.getAttribute("item");
			entry.setCode(code);

		}
		return;
	}

	public void clearStickyNode() {
		if (sticky != null) {
			// sticky.ellipse.setPaint(Color.green);
			Color labelColor = (Color) sticky.pos_val.getPaint();
			sticky.ellipse.setPaint(labelColor);
			sticky = null;
		}
	}

	public void decorateDraggableNode(PComposite figure, PLayer layer, PText label, Paint color, PNode vis,
			double mouse_x, double maxY, int stagger_offset) {

		DD d;
		
		PNode ellipse;
		PText pos_val;
		if( sticky != null && sticky.src == vis ) {
			d = sticky;
			ellipse = d.ellipse;
			pos_val = d.pos_val;
			ellipse.setPaint(theme_hilight_stickyColor);
		} else {
			ellipse = PPath.createEllipse(-4, maxY - 20, 8.0, 8.0);
			ellipse.setPaint(color);

			pos_val = new PText(formatPosLabel( vis));
			pos_val.translate(-2, ellipse.getY() - 10); // first, translate to the
														// desired position
			pos_val.rotate(-Math.PI / 2); // second, rotate to the desired angle
			pos_val.setVisible(false);
			pos_val.setPaint(color);

			d = new DD(layer);
			d.txt_val = null; // txt_val;
			d.label = label;
			d.src = vis;
			d.ellipse = ellipse;
			d.mouse_x = mouse_x;
			d.pos_val = pos_val;

		}

		figure.addChild(ellipse);
		figure.addChild(pos_val);

		figure.addAttribute("#d", d);

	}

	public void reset() {

		this.dy = 30;
		last_anno_x = -1;
	}

	public PNode getStickyNode() {
		PNode node = null;
		if (sticky != null) {
			node = sticky.src;
		}
		return node;
	}

	public double getStickyMouseX() {
		double val = -1;
		if (sticky != null) {
			val = sticky.mouse_x;
		}
		return val;
	}

	public PLayer getStickyLayer() {
		return sticky.layer;
	}

}
