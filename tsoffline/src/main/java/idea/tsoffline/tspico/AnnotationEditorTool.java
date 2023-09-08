package idea.tsoffline.tspico;

import java.awt.Color;
import java.awt.Paint;
import java.awt.Point;
import java.awt.event.ComponentEvent;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.activities.PActivity;
import org.piccolo2d.event.PBasicInputEventHandler;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.extras.nodes.PComposite;
import org.piccolo2d.extras.nodes.PLine;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;

import idea.schema.rp.RpMetric;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.ts.TsoAnnotationEntryType;
import idea.tsoffline.AppFrame;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.LayerUtil;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.model.D;
import idea.tsoffline.model.DerivedUtil;
import idea.tsoffline.model.OfflineSignal;

@Slf4j
public class AnnotationEditorTool extends PBasicInputEventHandler {

	public static final int MAX = 1;
	public static final int MIN = 2;
	public static final int PICK = 3;
	public static final int DATA = 4;

	// if more than this many annotation indicator lines are indicated...don't
	// display
	private static final int MAX_VISIBLE_NODES = 60;
	// autohide too many indicators if time is greater than...
	private static final double AUTOHIDE_TIME = 90.0;

	TsPSwingCanvas canvas;

	// annotationLayer is laid on top of the the axis coordinate system in
	// general, but the signal camera
	// specifically. It's coordinate frame is the same as axisLayer coordinate
	// frame.
	// This keeps the event indicator points and text from changing size as
	// layer is zoomed in/out.
	// All items are removed from this layer and rebuild with each new layout of
	// the graph, ie, after a
	// zoom or scroll. This layer only holds the currently displayed annotations
	// and events.

	private PLayer annotationLayer;
	XDraggableEventTool dragableFeaturesTool;

	@Setter
	@Getter
	private String editableLayerName;

	public AnnotationEditorTool(TsPSwingCanvas canvas) {
		this.canvas = canvas;

		annotationLayer = new PLayer();
		annotationLayer.setPickable(false);
		annotationLayer.setChildrenPickable(true);
		annotationLayer.setName("anno_layer");

		dragableFeaturesTool = new XDraggableEventTool(canvas);

		annotationLayer.addInputEventListener(dragableFeaturesTool);
	}

	@Override
	public void mouseClicked(final PInputEvent e) {

		if (e == null) {
			// this can happen if the draggable signal decides not to handle the
			// event...
			// caused by selection outside a band area
			return;
		}
		int button = e.getButton();

		if (e.isShiftDown() || e.isControlDown()) {
			PLayer editLayer = canvas.getAnnotationLayer(editableLayerName);
			if (editLayer == null) {
				AppFrame.getInstance().showErrorMessage("No editable layer.");
				return;
			} else {
				AppFrame.getInstance().showErrorMessage(null);
			}
		}

		Point2D dataPt = e.getPosition();
		if (button == 1) {
			if (e.isShiftDown() && e.isControlDown()) {
				joinNodesAtDataPoint(null, null, 0, dataPt, null);
			} else if (e.isShiftDown()) {
				joinNodesAtDataPoint(null, null, 1, dataPt, null);
			} else if (e.isControlDown()) {
				joinNodesAtDataPoint(null, null, -1, dataPt, null);
			} else {
				// ignore...just a focus change
				// canvas.addEventPoint("r", x);
			}

		} else if (button == 3) {
			if (e.isShiftDown() || e.isControlDown()) {
				// shift+control together is a special case of exact
				// positioning...but we let it
				// fly here too
				canvas.removeNodesAtMousePoint(dataPt);
			} else {
				// ignore...just a focus change
				// canvas.removeEventClosest( x, min, max );
			}
		}

	}

	public void joinNodesAtDataPoint(PLayer editLayer, PLayer dataLayer, int dir, Point2D data_pt, String code) {
		if (editLayer == null) {
			editLayer = canvas.getAnnotationLayer(editableLayerName);
		}
		if (dataLayer == null) {
			dataLayer = canvas.getActiveLayer();
		}

		if (dataLayer == null) {
			// Toolkit.getDefaultToolkit().beep();
			AppFrame.getInstance().showErrorMessage("No data layer selected.");
			return;
		}
		joinNodesAtDataPoint(editLayer, dataLayer, dir, data_pt.getX(), code);

		// FIXME: not necessary if the children are already in order
		renumberFiducials(editLayer);
	}

	public PNode joinNodesAtDataPoint(PLayer editLayer, PLayer dataLayer, final int dir, double dataX, String code) {
		if (editLayer == null && editableLayerName != null) {
			editLayer = canvas.getAnnotationLayer(editableLayerName);
		}

		if (editLayer == null) {
			return null;
		}

		if (dataLayer == null) {
			dataLayer = canvas.getActiveLayer();
		}

		PNode node;

		if (dir == 0) {
			node = add_fucidial(editLayer, dataX, code);
		} else {
			log.error("FIXME: DATAX: " + dataX + " not always in the right coord system! -- expecting DATA coord");
			float[] r = canvas.createMaxAndMin(dataX);
			node = joinNodesAndInsert(editLayer, dataLayer, dir, r[0], r[1], code);
		}

		return node;
	}

	@SuppressWarnings("unchecked")
	public PNode joinNodesAndInsert(PLayer featureLayer, PLayer dataLayer, final int dir, double min_x, double max_x,
			String code) {

		PNode dest = null;
		// PNode newnode = null;

		if (dir != 0) {
			List<PNode> children = featureLayer.getChildrenReference();
			ArrayList<PNode> rri_nodes = getNodesInRange(children, min_x, max_x);

			if (rri_nodes.size() > 0) {
				dest = rri_nodes.get(0);
			}

			// I only want one node remaining, delete everything after the first
			// node
			for (int i = 1; i < rri_nodes.size(); i++) {
				PNode node = rri_nodes.get(i);
				node.removeFromParent();
				featureLayer.removeChild(node);
			}

		}

		if (dest == null) {
			dest = add_fucidial(featureLayer, min_x, code);
		}

		if (dataLayer != null) {

			double[][] d_ar = D.getValuesInRange(dataLayer, min_x, max_x);
			int sz = d_ar[0].length;

			double[] d_x = d_ar[0];
			double[] d_y = d_ar[1];

			if (d_x == null || d_x.length == 0) {
				// no data in selected area
				return null;
			}

			double x = d_x[0];
			double y_max = d_y[0];
			double y_min = d_y[0];
			if (dir == 0) {
				x = d_x[sz / 2];
			} else {
				for (int idx = 0; idx < sz; idx++) {
					double y = d_y[idx];
					if (dir > 0 && y > y_max) {
						y_max = y;
						x = d_x[idx];
					} else if (dir < 0 && y < y_min) {
						y_min = y;
						x = d_x[idx];
					}
				}
			}

			dest.setX(x);
		}

		return dest;
	}

	private void renumberFiducials(PLayer editLayer) {
		List<PNode> children = editLayer.getChildrenReference();
		Collections.sort(children, new Comparator<PNode>() {

			@Override
			public int compare(PNode o1, PNode o2) {
				return Double.compare(o1.getX(), o2.getX());
			}

		});

		int index = 1;
		for (PNode node : children) {
			TsoAnnotationEntryType item = (TsoAnnotationEntryType) node.getAttribute("item");
			;
			item.setOffset((float) node.getX());
			item.setTempSeq(index++);
		}

	}

	public ArrayList<PNode> getNodesInRange(Collection<PNode> nodes, double startX, double endX) {
		ArrayList<PNode> dest = new ArrayList<PNode>();

		for (PNode node : nodes) {
			double x = node.getX();
			if (x <= startX || x >= endX) {
				continue;
			}
			if (x > endX) { // ASSUME nodes in order!
				break;
			}
			dest.add(node);
		}

		return dest;
	}

	private PNode add_fucidial(PLayer editLayer, double x, String code) {
		List<PNode> fudicials = editLayer.getChildrenReference();

		TsoAnnotationEntryType item = new TsoAnnotationEntryType();
		item.setCode(code);
		item.setValue(0);
		item.setOffset((float) x);
		item.setTm(new Date(canvas.getStartTime() + (long) (x * 1000)));

		PNode node = LayerUtil.addFiducialPoint(editLayer, (float) x, 0, code);
		node.addAttribute("item", item);
		node.addAttribute("txt", code);

		int before_idx = findNodeIdxBefore(fudicials, node.getX());

		// have to set the node_before first...this gives it the RRI used to set
		// Y in node_before
		if (before_idx >= 0) {
			PNode node_before = fudicials.get(before_idx);

			node_before.setWidth(node.getX() - node_before.getX());
			node.setY(node_before.getWidth() * 1000);
			node_before.setHeight(node.getY() - node_before.getY());
		}

		if (before_idx + 2 < fudicials.size()) {
			PNode node_after = fudicials.get(before_idx + 2);
			if (node_after != null) {
				node.setWidth(node_after.getX() - node.getX()); // seconds
				node_after.setY(node.getWidth() * 1000); // milliseconds
				node.setHeight(node_after.getY() - node.getY());

				if (before_idx + 3 < fudicials.size()) {
					PNode node_after_after = fudicials.get(before_idx + 3);
					if (node_after_after != null) {
						node_after.setHeight(node_after_after.getY() - node_after.getY());
					}
				}
			}
		}

		return node;
	}

	private int findNodeIdxBefore(List<PNode> children, double ref_x) {
		int before_idx = -1;

		// PNode node_before = null;
		int idx = 0;
		for (PNode node : children) {
			if (node instanceof PLine) {
				// assume x of a vertical line
				float x = (float) node.getX();
				if (x < ref_x) { // NOTE: STRICTLY < COMPARISON
					// node_before = node;
					before_idx = idx;
				} else {
					break; // we've found enough
				}
			}
			idx++;
		}
		return before_idx;
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
	// / </returns>+
	public boolean isOptionSelection(PInputEvent e) {
		return e.isShiftDown();
	}

	public void draw(PBounds bbounds, double dataWidth, Point2D origin_data, PAffineTransform sigcam_view_m)
			throws NoninvertibleTransformException {

		PBounds bounds = annotationLayer.getBounds();
		annotationLayer.removeAllChildren();

		List<HPSplitableLayer> annotationData = canvas.getAnnotationModel();

		int stagger_offset = 0;
		Iterator<HPSplitableLayer> it = annotationData.iterator();
		while (it.hasNext()) {
			HPSplitableLayer parent = it.next();
			PLayer data_layer = parent;
			if( data_layer.getChildrenCount() == 0 ) {
				RpMetric m = parent.getMetric();
				log.error("Expecting one or more children in layer: {}/{}/{}", data_layer.getName(), m, (m == null) ? "no metric" : m.getLocation());
				continue;
			}
			PNode o = data_layer.getChild(0);
			if( o instanceof HPSplitableLayer ) {
				data_layer = (HPSplitableLayer) o;
			}

			if (data_layer == null || data_layer.getVisible() == false) {
				// dont draw invisible layers
				continue;
			}

			double startValue = origin_data.getX();
			double endValue = startValue + dataWidth;

			Collection<PNode> nodes = data_layer.getChildrenReference();
			if (nodes == null) {
				return;
			}

			// sort the data points
			Collections.sort((List<PNode>) nodes, new Comparator<PNode>() {

				@Override
				public int compare(PNode o1, PNode o2) {
					// TODO Auto-generated method stub
					return Double.compare(o1.getX(), o2.getX());
				}
			});

			annotationLayer.setVisible(true);

			ArrayList<PNode> vis_nodes = new ArrayList<PNode>();
			int start_pos = DerivedUtil.getNodesInRange(vis_nodes, nodes, startValue, endValue);
			log.debug("drawIndicators: {}", parent.getName());

			if (vis_nodes.size() > MAX_VISIBLE_NODES && dataWidth > AUTOHIDE_TIME) {
				continue; // don't show...too many nodes
			}

			boolean editable = false;
			if (editableLayerName != null) {
				editable = editableLayerName.equals(data_layer.getName());
			}

			PAffineTransform view_m = sigcam_view_m;
			// WLB 17FEB17: view_m should be specific to the camera where the
			// annotation is shown
			HPSplitableLayer src_sig = (HPSplitableLayer) data_layer.getAttribute("@pressure_sig");
			if (src_sig == null) {
				src_sig = (HPSplitableLayer) data_layer.getAttribute("@ref_sig");
			}
			Paint refColor = null;
			if (src_sig != null) {
				// maybe it should be shown on all cameras!
				PCamera cam0 = src_sig.getCamera(0);

				view_m = cam0.getViewTransform();
				refColor = src_sig.getDefaultColor();
			}
			drawIndicators(data_layer, start_pos, vis_nodes, origin_data, bounds, view_m, parent.getPaint(), refColor, editable,
					stagger_offset);
			stagger_offset += 5;
			
		}
	}
	
	/**
	 * 
	 * @param layer
	 * @param seq_no
	 * @param vis_nodes	Collection of nodes to be drawn.
	 * @param origin
	 * @param sigcam_bounds
	 * @param view_m
	 * @param color
	 * @param refColor
	 * @param editable	Flag to indicate if the indicator is drag-able
	 * @param stagger_offset  Distance to offset the height at which the drag-able ball is drawn to avoid overlap 
	 * @throws NoninvertibleTransformException
	 * 
	 * Some aspects of the drawing are controlled by attributes of the layer, including: 
	 * 	@style: points or lines
	 *  @enum_by	??
	 *  
	 * Visible nodes must contain the attribute "item", which must be a Tso type that provides additional
	 * drawing information, such as the code to be placed above the line.
	 */

	private void drawIndicators(PLayer layer, int seq_no, ArrayList<PNode> vis_nodes, Point2D origin,
			PBounds sigcam_bounds, PAffineTransform view_m, Paint color, Paint refColor, boolean editable,
			int stagger_offset) throws NoninvertibleTransformException {

		if (vis_nodes == null || vis_nodes.size() == 0) {
			return;
		}

		String style = (String) layer.getAttribute("@style");
		boolean points = "points".equals(style);
		boolean lines = !points;

		Object enum_by = layer.getAttribute("@enum_by");

		// Iterator<Double> yy = ys.iterator();
		for (PNode vis : vis_nodes) {

			double tm = vis.getX();
			double y = vis.getY(); // we really dont care about y here. it only
									// reflects the node-to-node distance

			String message = (String) vis.getAttribute("txt");
			if (message != null && message.startsWith("_")) {
				// ignore this node for drawing purposes
				continue;
			}

			Point2D pt = new Point2D.Double(tm, y);
			Point2D pos = view_m.transform(pt, null);

			seq_no++;

			PPath line = null;
			if (lines) {
				line = PPath.createLine(0, (float) sigcam_bounds.getMinY() + TsPSwingCanvas.TOP_ANNOTATION_MARGIN, 0,
						(float) sigcam_bounds.getMaxY() - 4);
				line.setPickable(false);
				line.setPaint(color);
				line.setStrokePaint(color);
			}

			PText point = null;
			if (points) {
				OfflineSignal ref_sig = (OfflineSignal) vis.getAttribute("@ref_sig");
				Paint c2 = null;
				if (ref_sig != null) {
					c2 = ref_sig.getDefaultColor();
				}

				Object o_item = vis.getAttribute("item");
				if (!(o_item instanceof TsoAnnotationEntryType)) {
					log.error("Annotation type problem: {}", o_item);
					continue;
				}
				TsoAnnotationEntryType item = (TsoAnnotationEntryType) o_item;
				String code = "?";
				if (item != null && item.getCode() != null) {
					code = item.getCode();
				}

				if (c2 == null) {
					c2 = refColor;
				}
				if (c2 == null) {
					c2 = color;
				}
				point = new PText(code);
				point.setPickable(false);
				point.setTextPaint(c2);
				point.setY(pos.getY());
			}

			PText txt_val = null;
			PText txt_seq = null;
			if (lines) {
				if (message == null) {
					message = "??";
				}
				txt_val = new PText(message);

				PBounds txt_bounds = txt_val.getBoundsReference();
				txt_val.setPickable(false);
				// first, translate to the desired position
				txt_val.translate(-(3 * message.length()),
						txt_bounds.height + TsPSwingCanvas.TOP_MARGIN - TsPSwingCanvas.TOP_ANNOTATION_MARGIN - 16);
				// second, rotate to the desired angle
				// txt_val.rotate(-Math.PI / 2);
				txt_val.setTextPaint(color); // theme_annotation_text_color);

				if (message.length() > 1) {
					txt_val.setTextPaint(Color.WHITE);
				}

				if (enum_by == null) {
					String seqNo = "" + seq_no;
					txt_seq = new PText(seqNo);
					txt_seq.setPickable(false);
					txt_seq.translate(-(3 * seqNo.length()),
							txt_bounds.height + TsPSwingCanvas.TOP_MARGIN - TsPSwingCanvas.TOP_ANNOTATION_MARGIN - 2);
					txt_seq.setTextPaint(color); // theme_annotation_text_color);
				}
			}

			PComposite figure = new PComposite();
			figure.setPickable(false);
			if (line != null) {
				figure.addChild(line);
			}
			if (point != null) {
				figure.addChild(point);
			}
			if (txt_val != null) {
				figure.addChild(txt_val);
			}
			if (txt_seq != null) {
				figure.addChild(txt_seq);
			}

			figure.translate(pos.getX(), 0);

			if (editable) {
				dragableFeaturesTool.decorateDraggableNode(figure, layer, txt_val, color, vis, pos.getX(),
						sigcam_bounds.getMaxY() - 4, stagger_offset);
			}
			annotationLayer.addChild(figure);

		}

	}

	public void clear() {
		annotationLayer.removeAllChildren();
	}

	public void componentResized(ComponentEvent e, float plot_width, float plot_h) {
		Rectangle2D annotation_rect = new Rectangle2D.Float( //
				TsPSwingCanvas.LEFT_MARGIN, //
				TsPSwingCanvas.TOP_MARGIN - TsPSwingCanvas.TOP_ANNOTATION_MARGIN, //
				plot_width, plot_h + TsPSwingCanvas.TOP_ANNOTATION_MARGIN);
		annotationLayer.setBounds(annotation_rect);
	}

	public PLayer getLayer() {
		return annotationLayer;
	}

	public PNode getAnnotationAtMousePos(Point p1) {

		PNode sticky = dragableFeaturesTool.getStickyNode();
		if (sticky != null) {
			// TsoAnnotationEntryType entry = (TsoAnnotationEntryType)
			// sticky.getAttribute("item");

			double sticky_mousex = dragableFeaturesTool.getStickyMouseX();
			System.out.println("sticky_mouse=" + sticky_mousex + "  p1=" + p1);

			if (Math.abs(p1.getX() - sticky_mousex) < 4) {
				return sticky;
			}

		}

		return null;
	}

	public List<PNode> deleteAnnotation() {
		List<PNode> nodes = null;
		PNode node = dragableFeaturesTool.getStickyNode();
		if (node != null) {
			// NO this is not the best way to do this.
			// but romoveEventInRange() needs a rewrite to remove events one
			// at a time
			nodes = new LinkedList<PNode>(); // getNodesInRange(children,
												// min, max);
			nodes.add(node);
			removeFeatures(dragableFeaturesTool.getStickyLayer(), nodes);
			dragableFeaturesTool.clearStickyNode();
		}
		return nodes;
	}

	public void setStickyCode(String code) {
		dragableFeaturesTool.setStickyCode(code);
	}

	@SuppressWarnings("unchecked")
	public void removeFeatures(PLayer editLayer, List<PNode> features) {

		if (features == null || features.size() == 0) {
			return;
		}

		PNode sticky = dragableFeaturesTool.getStickyNode();
		List<PNode> children = editLayer.getChildrenReference();

		double min = features.get(0).getX();
		for (PNode node : features) {
			log.info("removing rri at: {}", node.getX());

			if (node.getX() < min) {
				min = node.getX();
			}
			editLayer.removeChild(node);

			if (node == sticky) {
				dragableFeaturesTool.clearStickyNode();
			}
		}

		/*
		 * update RRI for node after removal
		 */

		// find the node before removal
		int before_idx = -1;
		int idx = 0;
		for (PNode node : children) {
			if (node instanceof PLine) {
				// assume x of a vertical line
				float x = (float) node.getX();
				if (x <= min) {
					before_idx = idx;
				} else {
					break; // we've found enough
				}
			}
			idx++;
		}

		double before_x = 0;
		PNode node_before = null;
		if (before_idx > 0) {
			node_before = children.get(before_idx);
			before_x = node_before.getX();
		}

		int after_idx = before_idx + 1; // ok...mostly documentation and
		// readability
		PNode node_after = null;
		if (after_idx < children.size()) {
			node_after = children.get(after_idx);
			node_after.setY(1000 * (node_after.getX() - before_x));

			if (after_idx + 1 < children.size()) {
				PNode node_after_after = children.get(after_idx + 1);
				node_after.setHeight(node_after_after.getY() - node_after.getY());
			}
			log.info("new_rri  y=" + node_after.getY() + " h={} w={}", //
					node_after.getHeight(), node_after.getWidth());

		}

		if (node_before != null && node_after != null) {
			node_before.setWidth(node_after.getX() - node_before.getX());
			node_before.setHeight(node_after.getY() - node_before.getY());
		}

	}

	@SuppressWarnings("unchecked")
	public List<PNode> removeEventInRange(PLayer editLayer, float min, float max) {
		List<PNode> nodes = null;

		if (editLayer == null) {
			editLayer = canvas.getAnnotationLayer(editableLayerName);
		}

		if (editLayer != null) {
			List<PNode> children = editLayer.getChildrenReference();
			nodes = getNodesInRange(children, min, max);

			removeFeatures(editLayer, nodes);
		}

		return nodes;
	}

	public void activityStarted(PActivity activity) {
		annotationLayer.setVisible(false); // this will show/hides all the
											// annotations
	}

	public void activityFinished(PActivity activity) {
		annotationLayer.setVisible(true);
	}

	public PLayer getStickyLayer() {
		return dragableFeaturesTool.getStickyLayer();
	}

}