/*
 * Created by JFormDesigner on Fri Sep 16 16:38:28 CDT 2016
 */

package idea.tsoffline.tspico;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Paint;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.geom.Point2D;
import java.math.BigDecimal;
import java.math.MathContext;
import java.text.DecimalFormat;
import java.util.Collection;
import java.util.Comparator;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.TreeSet;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.event.PBasicInputEventHandler;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.extras.event.PNotificationCenter;
import org.piccolo2d.extras.nodes.PLine;
import org.piccolo2d.extras.pswing.PSwing;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;

import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import lombok.Getter;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.ts.TsFilter;
import idea.ts.TsoAnnotationEntryType;
import idea.tsoffline.AppModel;
import idea.tsoffline.B2BUtil;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.canvas.PiccoUtil;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.model.DerivedUtil;

/**
 * @author User #1
 */

@Slf4j
public class LegendTool extends PBasicInputEventHandler {
	ImageIcon removeIcon = new ImageIcon(getClass().getResource("/fonta/resources/bolt.png"));

	private final static DecimalFormat df1 = new DecimalFormat("0.0");
	private final static DecimalFormat df2 = new DecimalFormat("0.00");
	private final static DecimalFormat df3 = new DecimalFormat("0.000");

	public static final String LEGEND_SEG_SELECTED_NOTIFICATION = "LEGEND_SEG_SELECTED";
	public static final String LEGEND_SELECTED_NOTIFICATION = "LEGEND_NOTIFICATION";
	public static final String LEGEND_PROPERTIES_NOTIFICATION = "LEGEND_PROPERTIES";
	public static final String LEGEND_HIDE_NOTIFICATION = "LEGEND_HIDE";
	public static final String LEGEND_DELETE_NOTIFICATION = "LEGEND_DELETE";
	public static final String LEGEND_FILTER_NOTIFICATION = "LEGEND_FILTER";
	public static final String LEGEND_RULER_NOTIFICATION = "LEGEND_RULER";

	Color theme_y_range_color = Color.BLACK;
	Color theme_header_color = Color.WHITE;

	private static Font emph_font = new Font("Ariel", Font.BOLD, 12);
	private static Font ticFont = new Font("Ariel", Font.BOLD, 10);

	private LegendPopupMenu popupLegendMenu = new LegendPopupMenu(this);
	PText curr;
	private PNode drag_node;
	private PNode beat_node;
	double rri;
	private PBounds drag_start;

	@Getter
	PLayer calibrationSegment = null;
	@Getter
	private HPSplitableLayer selectedSignal;
	@Getter
	private PCamera selectedCamera;

	protected static Font tfFont = new Font("Ariel", Font.PLAIN, 10);

	FocusAdapter gainFocusListener = new FocusAdapter() {

		@Override
		public void focusGained(FocusEvent e) {

		}

		@Override
		public void focusLost(FocusEvent e) {
			Object src = e.getSource();
			if (src instanceof JFormattedTextField) {
				JFormattedTextField tf = (JFormattedTextField) e.getSource();
				PLayer data_layer = (PLayer) tf.getClientProperty("data_layer");
				PAffineTransform tran = data_layer.getTransformReference(true);
				double tx = tran.getTranslateX();
				double ty = tran.getTranslateY();
				double sy = ((Number) tf.getValue()).doubleValue();
				tran.setToScale(1, sy); // seems to zero tx & ty
				tran.setOffset(tx, ty);
				data_layer.repaint();
			}
		}
	};

	FocusAdapter rangeFocusListener = new FocusAdapter() {

		@Override
		public void focusGained(FocusEvent e) {

		}

		@Override
		public void focusLost(FocusEvent e) {
			Object src = e.getSource();
			if (src instanceof JFormattedTextField) {
				JFormattedTextField tf = (JFormattedTextField) e.getSource();
				PCamera cam = (PCamera) tf.getClientProperty("cam");
				String typ = (String) tf.getClientProperty("typ");
				double val = ((Number) tf.getValue()).doubleValue();

				cam.addAttribute(typ, val);
				PNotificationCenter.defaultCenter().postNotification(LEGEND_RULER_NOTIFICATION, LegendTool.this);
			}
		}

	};

	FocusAdapter lockFocusListener = new FocusAdapter() {

		@Override
		public void focusGained(FocusEvent e) {

		}

		@Override
		public void focusLost(FocusEvent e) {
			Object src = e.getSource();
			if (src instanceof JCheckBox) {
				JCheckBox cb = (JCheckBox) e.getSource();
				PCamera cam = (PCamera) cb.getClientProperty("cam");

				if (cb.isSelected()) {
					cam.addAttribute("@locked", true);
				} else {
					cam.addAttribute("@locked", null);
				}
			}
		}
	};

	FocusAdapter zeroFocusListener = new FocusAdapter() {

		@Override
		public void focusGained(FocusEvent e) {

		}

		@Override
		public void focusLost(FocusEvent e) {
			Object src = e.getSource();
			if (src instanceof JCheckBox) {
				JCheckBox cb = (JCheckBox) e.getSource();
				PCamera cam = (PCamera) cb.getClientProperty("cam");

				if (cb.isSelected()) {
					cam.addAttribute("@baseline", true);
				} else {
					cam.addAttribute("@baseline", null);
				}
			}
		}
	};

	FocusAdapter offsetFocusListener = new FocusAdapter() {

		@Override
		public void focusGained(FocusEvent e) {
			// TODO Auto-generated method stub

		}

		@Override
		public void focusLost(FocusEvent e) {
			JFormattedTextField tf = (JFormattedTextField) e.getSource();
			PLayer data_layer = (PLayer) tf.getClientProperty("data_layer");
			PAffineTransform tran = data_layer.getTransformReference(true);
			double ty = ((Number) tf.getValue()).doubleValue();
			double tx = tran.getTranslateX();
			tran.setOffset(tx, ty);
			data_layer.repaint();
		}
	};

	public LegendTool() {
		getEventFilter().setAcceptsMouseClicked(true);
		getEventFilter().setAcceptsMouseEntered(true);
		getEventFilter().setAcceptsMouseExited(true);
		getEventFilter().setAcceptsMouseDragged(true);
		getEventFilter().setAcceptsMousePressed(true);
		getEventFilter().setAcceptsMouseReleased(true);
	}

	@Override
	public void mousePressed(PInputEvent event) {
		super.mousePressed(event);

		drag_node = event.getPickedNode();
		drag_start = drag_node.getBounds();

	}

	@Override
	public void mouseReleased(PInputEvent event) {
		super.mouseReleased(event);
		if (drag_node != null) {
			drag_node.setBounds(drag_start);
			event.setHandled(true);

			TsPSwingCanvas canv = (TsPSwingCanvas) event.getComponent();

			PCamera band = canv.getBandAt(event.getCanvasPosition());
			if (band != null) {
				HPSplitableLayer sig_layer = (HPSplitableLayer) drag_node.getAttribute("sig");
				String attr = (String) drag_node.getAttribute("attr");
				if (attr != null) {
					GuiUtil.showMessage("FIXME: unexpected attribute in LegendTool");
					String[] arr = attr.split("/");
					String key = arr[0];
					String subkey = (arr.length > 1) ? arr[1] : null;
					PLayer piece = buildLayerFromFeature(sig_layer, attr, key, subkey);
					sig_layer.addChild(piece);
				}

				canv.moveSignalToBand(band, sig_layer);

			}
		}
	}

	private PLayer buildLayerFromFeature(PLayer sig_layer, String layerName, String attr_name, String key_name) {

		String loc = layerName;
		RpMetric metric = new RpMetric(loc, null, null, RpLinearUnit.unit, DataTyp.DOUBLE_TYP);
		HPSplitableLayer sig = new HPSplitableLayer(metric);
		sig.setTyp(TimeseriesType.TT_TRACE);
		sig.setDefaultColor(Color.GREEN);
		sig.setPaint(Color.GREEN);

		PLayer layer = new HPPathLayer(sig.getMetric(), StreamID.TRACE, layerName);
		ListIterator it = sig_layer.getChildrenIterator();
		int idx = 0;

		double[] arr_x = new double[6];
		double[] arr_y = new double[6];
		while (it.hasNext()) {
			PNode node = (PNode) it.next();
			Object attr = node.getAttribute(attr_name);
			if (attr == null) {
				continue;
			}

			double val;
			if (attr instanceof Map) {
				Map map = (Map) attr;
				Object o = map.get(key_name);
				if (o == null) {
					continue;
				}
				val = (Double) o;
			} else {
				val = (Double) attr;
			}
			idx++;
			arr_x[idx] = node.getX();
			arr_y[idx] = val;
			if (idx == 5) {
				PLine path = PiccoUtil.createVariableResolutionLine(sig.getMetric(), arr_x, arr_y);
				layer.addChild(path);

				arr_x[0] = arr_x[5];
				arr_y[0] = arr_y[5];
				idx = 0;
			}
		}

		if (idx > 0) {
			// residue!
		}
		return layer;
	}

	@Override
	public void mouseDragged(PInputEvent event) {
		super.mouseDragged(event);
		if (drag_node != null) {
			Point2D canvPos = event.getCanvasPosition();
			drag_node.setX(canvPos.getX());
			drag_node.setY(canvPos.getY());

			event.setHandled(true);
		}
	}

	@Override
	public void mouseClicked(PInputEvent event) {
		super.mouseClicked(event);

		PNode picked = event.getPickedNode();
		
		if (event.isRightMouseButton()) {
			Component canvas = event.getSourceSwingEvent().getComponent();
			Point pt = canvas.getMousePosition();
			popupLegendMenu.refresh();
			popupLegendMenu.show(canvas, (int) pt.getX(), (int) pt.getY());
			event.setHandled(true);
		} else if ( picked instanceof PText ) {
			
			// used for changing calibration values
			curr = (PText)picked;
			selectedSignal = (HPSplitableLayer) curr.getAttribute("sig");
			selectedCamera = (PCamera) curr.getAttribute("parent_cam");
			if (selectedSignal == null) {
				selectedSignal = (HPSplitableLayer) curr.getAttribute("parent_sig");
				// calibration segment...use locally
				calibrationSegment = (PLayer) curr.getAttribute("data_layer");
				PNotificationCenter.defaultCenter().postNotification(LEGEND_SEG_SELECTED_NOTIFICATION, this);
			} else {
				// sig selection...tell host
				PLayer sigLayer = selectedSignal;
				calibrationSegment = (sigLayer instanceof HPPathLayer) ? sigLayer : null;
				PNotificationCenter.defaultCenter().postNotification(LEGEND_SELECTED_NOTIFICATION, this);
			}
			updateSignalColors(selectedSignal, calibrationSegment);
		}
	}

	private static void updateSignalColors(HPSplitableLayer selectedSignal, PLayer calibrationSegment) {

		if (calibrationSegment != null) {

		}
	}

	void firePropertiesNotificiation() {
		PNotificationCenter.defaultCenter().postNotification(LEGEND_PROPERTIES_NOTIFICATION, this);
	}

	@Override
	public void mouseEntered(PInputEvent event) {
		super.mouseEntered(event);

		PNode node = event.getPickedNode();

		// i get an instance of PSwing here when using the intersection panel layout
		// that may not last, but could happen for other panels
		if (node instanceof PText) {

			curr = (PText) event.getPickedNode();
			node.addAttribute("paint", curr.getTextPaint());
			node.addAttribute("font", curr.getFont());
			curr.setFont(emph_font);

			curr.setTextPaint(Color.WHITE);
		}
		// PNotificationCenter.defaultCenter().postNotification(
		// LEGEND_ENTERED_NOTIFICATION, this);
	}

	@Override
	public void mouseExited(PInputEvent event) {
		super.mouseExited(event);

		PNode o = event.getPickedNode();
		if (o instanceof PText) {
			curr = (PText) event.getPickedNode();
			curr.setTextPaint((Paint) curr.getAttribute("paint"));
			curr.setFont((Font) curr.getAttribute("font"));
		}
		// PNotificationCenter.defaultCenter().postNotification(
		// LEGEND_EXITED_NOTIFICATION, this);

	}

	public PText getSelectedPText() {
		return curr;
	}

	void fireHideNotificiation() {
		PNotificationCenter.defaultCenter().postNotification(LEGEND_HIDE_NOTIFICATION, this);
	}

	void fireDeleteNotificiation() {
		PNotificationCenter.defaultCenter().postNotification(LEGEND_DELETE_NOTIFICATION, this);
	}

	void fireFilterNotificiation(TsFilter filter) {
		PText pt_label = getSelectedPText();
		HPSplitableLayer sig = (HPSplitableLayer) pt_label.getAttribute("sig");

		Map<String, Object> map = new HashMap<String, Object>();

		map.put("filter", filter);
		map.put("sig", sig);
		PNotificationCenter.defaultCenter().postNotification(LEGEND_FILTER_NOTIFICATION, this, map);

		pt_label.setText(getLabelForSig(sig));
	}

	public void drawCalibrationLegend(PLayer axisLayer, List<PCamera> bandCameras, double left_ref) {
		theme_y_range_color = Color.BLACK;
		drawCalibrationHeader(axisLayer, left_ref + 100);
		drawCalibrationLegendDetail(axisLayer, bandCameras, left_ref + 30);
	}

	public void drawIntersectionLegend(PLayer axisLayer, List<PCamera> bandCameras, double left_ref,
			Double analysisPoint) {
		theme_y_range_color = Color.BLACK;
		drawIntersectionHeader(axisLayer, left_ref + 20);
		drawIntersectionLegendDetail(axisLayer, bandCameras, left_ref + 20);
	}

	public void drawAnalysisLegend(PLayer axisLayer, List<HPSplitableLayer> annos, List<PCamera> bandCameras,
			double left_ref, Double startSec) {
		theme_y_range_color = Color.WHITE;

		// drawStandardLegend(axisLayer, bandCameras, left_ref, false);
		drawAnalysisHeader(axisLayer, left_ref + 10);

		if (startSec != null) {
			List<HPSplitableLayer> ll = AppModel.getSignals();

			PBounds bounds = new PBounds();
			for (PCamera cam : bandCameras) {
				if (cam == null)
					continue;

				PBounds cam_bounds = cam.getBoundsReference();
				bounds.add(cam_bounds);
			}

			drawAnalysisInfo(axisLayer, annos, bounds.getY(), left_ref + 20, startSec);
			if (beat_node != null) {
				double lead_lag = B2BUtil.getBeatLeadLag();

				double c_bottom = bounds.getY() + bounds.getHeight();
				double c_width = bounds.getWidth();

				PCamera cam0 = bandCameras.get(0);
				PBounds view_bounds = cam0.getViewBounds();

				double dx = beat_node.getX() - view_bounds.getX() + lead_lag;
				double x0 = c_width * dx / view_bounds.width + bounds.getX();
				double w = c_width * rri / view_bounds.width;

				drawBrace(axisLayer, c_bottom + 20, x0, w, -10);
			}
		}
	}

	public void drawUnusedLegend(PLayer axisLayer, List<HPSplitableLayer> annos, List<PCamera> bandCameras,
			double left_ref, List<HPSplitableLayer> lref) {

		List<HPSplitableLayer> invisible = new LinkedList<HPSplitableLayer>();
		invisible.addAll(lref);

		// remove visible signals
		for (PCamera cam : bandCameras) {
			if (cam == null)
				continue;

			for (int i = 0; i < cam.getLayerCount(); i++) {

				PLayer layer = cam.getLayer(i);
				// if the layer is not visible, don't allocate space for it
				if (layer == null || layer.getVisible() == false) {
					continue;
				}

				invisible.remove(layer);
			}
		}

		drawUnusedHeader1(axisLayer, left_ref);
		/*
		 * Now show the available/unused sigs
		 */
		// only used for the x position, so it doesnt matter which band
		double top = 30;
		double left = left_ref + 20;

		for (HPSplitableLayer sig : invisible) {
			if (sig.getSubtyp() == DataTyp.STRING_TYP) {
				// well, this is one way to identify an annotation
				// stream...maybe not the best
				// anyway, annotation types don't have a layer, so filter
				// them out here.
				continue;
			}
			PText pt_label = new PText(getLabelForSig(sig));

			pt_label.setFont(ticFont);
			pt_label.setX(left); // center around tic
			pt_label.setY(top); // center the font around the tic
			pt_label.addAttribute("sig", sig);

			pt_label.setTextPaint(sig.getPaint()); // y_ruler.color
			pt_label.addInputEventListener(this);
			axisLayer.addChild(pt_label);
			top += 15;
		}

		top += 15;

		top = drawUnusedHeader2(axisLayer, left_ref, top);
		for (HPSplitableLayer anno : annos) {

			TreeSet<String> attrs = getLayerAttributes(anno);
			if (attrs == null || attrs.size() == 0) {
				continue;
			}

			PText anno_label = new PText(getLabelForSig(anno));

			anno_label.setFont(ticFont);
			anno_label.setX(left); // center around tic
			anno_label.setY(top); // center the font around the tic
			anno_label.addAttribute("sig", anno);

			anno_label.setTextPaint(theme_header_color);
			anno_label.addInputEventListener(this);
			axisLayer.addChild(anno_label);
			top += 15;

			for (String attr : attrs) {

				PText attr_label = new PText(attr);

				attr_label.setFont(ticFont);
				attr_label.setX(left + 20); // center around tic
				attr_label.setY(top); // center the font around the tic
				attr_label.addAttribute("sig", anno);
				attr_label.addAttribute("attr", attr);
				attr_label.addAttribute("subkey", attr);
				attr_label.setTextPaint(Color.YELLOW);
				attr_label.addInputEventListener(this);
				axisLayer.addChild(attr_label);

				top += 15;
			}

			top += 5;
		}

	}

	private TreeSet<String> getLayerAttributes(HPSplitableLayer sig) {
		TreeSet<String> ts = new TreeSet<>();
		PLayer layer = sig;
		ListIterator<PNode> it = layer.getChildrenIterator();
		int count = 0;
		while (it.hasNext() && count < 10) {
			PNode node = it.next();
			Enumeration<?> keys = node.getClientPropertyKeysEnumeration();
			while (keys.hasMoreElements()) {
				Object attr_key = keys.nextElement();
				Object note = node.getAttribute(attr_key);

				if ("txt".equals(attr_key)) {
					// ignore
				} else if (note instanceof Map) {
					Map map = (Map) note;
					for (Object subkey : map.keySet()) {
						ts.add(attr_key + "/" + (String) subkey);
					}
				} else if (note instanceof TsoAnnotationEntryType) {
					// dunno
				} else {
					ts.add((String) attr_key);
				}
			}
			count++;
		}
		return ts;
	}

	private String getLabelForSig(HPSplitableLayer sig) {
		String name = sig.getAlias();
		if (name == null || name.length() == 0) {
			name = sig.getCode();
		}
		if (name == null || name.length() == 0) {
			name = sig.getLocation();
		}
		TsFilter filter = (TsFilter) sig.getAttribute("filter");
		if (filter != null) {
			name += " [" + filter.getName() + "]";
		}
		return name;
	}

	private void drawAnalysisInfo(PLayer axisLayer, List<HPSplitableLayer> annos, double top, double left_ref,
			double startSec) {

		double currY = top + 10;

		if (annos.size() == 0) {
			return;
		}
		HPSplitableLayer ecgSignal = annos.get(0); // in general, this is wrong
		log.error("FIXME: ecgSignal may not be correct in drawing analysis info");

		int seq = 0;
		Collection<PNode> r_nodes = ecgSignal.getNodes();
		if (r_nodes == null) {
			return;
		}

		PNode next_node = null;
		beat_node = null;

		Iterator<PNode> it = r_nodes.iterator();
		while (it.hasNext()) {
			PNode node = it.next();
			if (node.getX() < startSec) {
				seq++;
			} else {
				if (next_node == null) {
					next_node = node;
					break;
				}
			}
			beat_node = node;
		}

		if (next_node == null) {
			return;
		}

		rri = next_node.getX() - beat_node.getX();

		PText pt_label = new PText("BEAT: " + seq);
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(currY);
		pt_label.setTextPaint(theme_y_range_color);
		axisLayer.addChild(pt_label);

		currY += 15;

		pt_label = new PText("RRI: " + df3.format(rri));
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(currY);
		pt_label.setTextPaint(theme_y_range_color);
		axisLayer.addChild(pt_label);
		currY += 15;

		for (HPSplitableLayer anno : annos) {
			currY += 15;

			double calib_label_x = left_ref;

			pt_label = new PText(anno.getAlias());
			pt_label.setFont(ticFont);
			pt_label.setX(calib_label_x);
			pt_label.setY(currY);
			pt_label.setTextPaint(theme_y_range_color);
			axisLayer.addChild(pt_label);
			calib_label_x += 20;

			currY += 14;

			// to debug the laer attributes...add this
			// currY = drawAttributes(axisLayer, anno.getLayer(), calib_label_x,
			// currY);

			Collection<PNode> anno_nodes = findAnnoNodesForBeat(anno, beat_node, rri);
			if (anno_nodes == null) {
				continue;
			}

			for (PNode node : anno_nodes) {
				currY = drawAttributes(axisLayer, node, calib_label_x, currY);
			}
		}

	}

	private Collection<PNode> findAnnoNodesForBeat(HPSplitableLayer anno, PNode beat_node, double rri) {
		double x = beat_node.getX();
		double lead_lag = B2BUtil.getBeatLeadLag();
		return DerivedUtil.getNodesInRange(anno, x + lead_lag, x + rri + lead_lag);
	}

	private double drawAttributes(PLayer axisLayer, PNode node, double left, double currY) {
		PText pt_label;

		String code = (String) node.getAttribute("txt");
		pt_label = new PText(code);
		pt_label.setFont(ticFont);
		pt_label.setX(left);
		pt_label.setY(currY);
		pt_label.setTextPaint(theme_y_range_color);
		axisLayer.addChild(pt_label);

		int count = 0;
		if (code == null || code.startsWith("_")) {
			// time is not really relevent for this class of nodes
		} else {
			pt_label = new PText("TM=" + df3.format(node.getX()));
			pt_label.setFont(ticFont);
			pt_label.setX(left + 50);
			pt_label.setY(currY);
			pt_label.setTextPaint(theme_y_range_color);
			axisLayer.addChild(pt_label);
			currY += 14;
			count++;
		}

		if (node.getY() != 0) {
			pt_label = new PText("VAL=" + df3.format(node.getY()));
			pt_label.setFont(ticFont);
			pt_label.setX(left + 50);
			pt_label.setY(currY);
			pt_label.setTextPaint(theme_y_range_color);
			axisLayer.addChild(pt_label);
			currY += 14;
			count++;
		}
		if (count == 0) {
			currY += 14;
		}
		left += 15;

		Enumeration ii = node.getClientPropertyKeysEnumeration();
		while (ii != null && ii.hasMoreElements()) {
			String key = (String) ii.nextElement();
			if ("txt".equals(key)) {
				continue;
			} else if ("item".equals(key)) {
				continue;
			} else if (key.startsWith("@")) {
				continue;
			}

			pt_label = new PText(key);
			pt_label.setFont(ticFont);
			pt_label.setX(left);
			pt_label.setY(currY);
			pt_label.setTextPaint(theme_y_range_color);
			axisLayer.addChild(pt_label);

			if (pt_label.getWidth() > 50) {
				currY += 14;
			}
			Object value = node.getAttribute(key);
			if (value == null) {
				// ignore
			} else if (value instanceof Double) {
				double d = (Double) value;
				if (d < 10) {
					value = df3.format(d);
				} else if (d < 100) {
					value = df2.format(d);
				} else {
					value = df1.format(d);
				}
			} else if (value instanceof double[]) {
				double[] d = (double[]) value;
				value = "[";
				String comma = "";
				for (int i = 0; i < d.length; i++) {
					value += comma + df1.format(d[i]);
					comma = ", ";
				}
				value += "]";
			}

			if (value != null) {
				pt_label = new PText(value.toString());
				pt_label.setFont(ticFont);
				pt_label.setX(left + 50);
				pt_label.setY(currY);
				pt_label.setTextPaint(theme_y_range_color);
				axisLayer.addChild(pt_label);
			}

			currY += 14;
		}
		return currY;

	}

	public void drawStandardLegend(PLayer axisLayer, List<PCamera> bandCameras, double left_ref) {

		for (PCamera cam : bandCameras) {
			if (cam == null)
				continue;

			PBounds bounds = cam.getBoundsReference();

			// this is the "legend/text left", not the band camera left
			double left = left_ref;

			TreeSet<HPSplitableLayer> sorted_sigs = sortSignals(cam);

			double top = bounds.getY() + 10;
			double bottom = bounds.getY() + cam.getHeight() - 5;
			double currY = top;
			for (HPSplitableLayer sig : sorted_sigs) {
				PText pt_label = new PText(getLabelForSig(sig));

				pt_label.setFont(ticFont);
				pt_label.setX(left);
				pt_label.setY(currY);
				pt_label.setTextPaint(sig.getPaint());
				pt_label.addAttribute("sig", sig);
				pt_label.addAttribute("cam", cam);
				axisLayer.addChild(pt_label);

				pt_label.addInputEventListener(this);

				currY += 20;
				if (currY > bottom) {
					left += 50;
					currY = top;
				}

			}
		}

	}

	private TreeSet<HPSplitableLayer> sortSignals(PCamera cam) {
		TreeSet<HPSplitableLayer> sorted_sigs = new TreeSet<HPSplitableLayer>(new Comparator<HPSplitableLayer>() {

			@Override
			public int compare(HPSplitableLayer o1, HPSplitableLayer o2) {
				Integer i1 = (Integer) o1.getLayerSeq();
				Integer i2 = (Integer) o2.getLayerSeq();
				int comp = i1.compareTo(i2);
				if (comp == 0) {
					String n1 = o1.getAlias();
					String n2 = o2.getAlias();
					comp = n1.compareTo(n2);
				}
				return comp;
			}
		});

		for (int i = 0; i < cam.getLayerCount(); i++) {

			PLayer layer = cam.getLayer(i);
			// if the layer is not visible, don't allocate space for it
			if (layer == null || layer.getVisible() == false) {
				continue;
			}

			HPSplitableLayer sig = (HPSplitableLayer) layer;
			if (sig != null) { // phase layer has a null signal
				sorted_sigs.add(sig);
			}
		}

		return sorted_sigs;
	}

	public void drawCalibrationLegendDetail(PLayer axisLayer, List<PCamera> bandCameras, double left_ref) {

		for (PCamera cam : bandCameras) {
			if (cam == null)
				continue;

			PBounds bounds = cam.getBoundsReference();

			// this is the "legend/text left", not the band camera left
			double left = left_ref;

			TreeSet<HPSplitableLayer> sorted_sigs = sortSignals(cam);

			double top = bounds.getY() + 10;
			double bottom = bounds.getY() + cam.getHeight() - 5;
			double currY = top;

			for (HPSplitableLayer sig : sorted_sigs) {
				PText pt_label = new PText(getLabelForSig(sig));

				pt_label.setFont(ticFont);
				pt_label.setX(left);
				pt_label.setY(currY);
				pt_label.setTextPaint(sig.getPaint());
				pt_label.addAttribute("sig", sig);
				pt_label.addAttribute("cam", cam);
				pt_label.addInputEventListener(this);

				axisLayer.addChild(pt_label);

				PLayer layer = sig;

				boolean first = true;
				if (layer instanceof HPPathLayer) {
					// data layer
					addCalibrationDataLayer(cam, sig, axisLayer, layer, left + 80, currY, first);
				} else {
					// composed of two or more PClippableLayers
					ListIterator<PNode> it = layer.getChildrenIterator();
					while (it.hasNext()) {
						PLayer data_layer = (PLayer) it.next();
						addCalibrationDataLayer(cam, sig, axisLayer, data_layer, left + 80, currY, first);
						currY += 20;
						first = false;
					}
				}

				currY += 20;
				if (currY > bottom) {
					left += 50;
					currY = top;
				}

			}
		}

	}

	public void drawIntersectionLegendDetail(PLayer axisLayer, List<PCamera> bandCameras, double left_ref) {

		for (PCamera cam : bandCameras) {
			if (cam == null)
				continue;

			PBounds bounds = cam.getBoundsReference();

			// this is the "legend/text left", not the band camera left
			double left = left_ref;

			TreeSet<HPSplitableLayer> sorted_sigs = sortSignals(cam);

			double top = bounds.getY() + 10;
			double bottom = bounds.getY() + cam.getHeight() - 5;
			double currY = top;

			for (HPSplitableLayer sig : sorted_sigs) {
				PText pt_label = new PText(getLabelForSig(sig));

				pt_label.setFont(ticFont);
				pt_label.setX(left);
				pt_label.setY(currY);
				pt_label.setTextPaint(sig.getPaint());
				pt_label.addAttribute("sig", sig);
				pt_label.addAttribute("cam", cam);
				pt_label.addInputEventListener(this);

				axisLayer.addChild(pt_label);

				PLayer layer = sig;

				boolean first = true;
				if (layer instanceof HPPathLayer) {
					// data layer
					addIntersectionDataLayer(cam, sig, axisLayer, layer, left + 60, currY, first);
				} else {
					// composed of two or more PClippableLayers
					ListIterator<PNode> it = layer.getChildrenIterator();
					while (it.hasNext()) {
						PLayer data_layer = (PLayer) it.next();
						addIntersectionDataLayer(cam, sig, axisLayer, data_layer, left + 60, currY, first);
						currY += 20;
						first = false;
					}
				}

				currY += 20;
				if (currY > bottom) {
					left += 50;
					currY = top;
				}

			}
		}

	}

	private void addIntersectionDataLayer(PCamera cam, HPSplitableLayer sig, PLayer axisLayer, PLayer data_layer,
			double calib_label_x, double currY, boolean first) {

		Paint color = (data_layer == calibrationSegment) ? Color.RED/* sig.getColor() */ : Color.yellow;
		{
			double d = 99.9;
			PNode pt_label = null;
			double align = 0;

			PText pt = new PText(df3.format(d));
			pt.setFont(ticFont);
			pt.setTextPaint(color);
			// pt.setHorizontalAlignment( Component.LEFT_ALIGNMENT );
			align = pt.getWidth() - 30;
			pt_label = pt;

			calib_label_x += 10;
			JFormattedTextField tf = new JFormattedTextField();
			tf.putClientProperty("data_layer", data_layer);
			tf.setFormatterFactory(GuiUtil.getNumberFormatterFactory());
			tf.setFont(tfFont);
			tf.setColumns(4);
			tf.setValue(round(d, 4));
			tf.addFocusListener(offsetFocusListener);

			pt_label = new PSwing(tf); // df1.format(d));
			pt_label.translate(calib_label_x, currY);
			pt_label.addInputEventListener(this);
			pt_label.addAttribute("data_layer", data_layer);
			pt_label.addAttribute("parent_sig", sig);
			pt_label.addAttribute("parent_cam", cam);

			pt_label.setX(calib_label_x - align);
			pt_label.setY(currY);
			axisLayer.addChild(pt_label);
			calib_label_x += 40;
		}
	}

	private void addCalibrationDataLayer(PCamera cam, HPSplitableLayer sig, PLayer axisLayer, PLayer data_layer,
			double calib_label_x, double currY, boolean first) {
		PAffineTransform tran = data_layer.getTransform();
		PNode zero;
		if (data_layer.getChildrenCount() == 0) {
			zero = new PNode();
		} else {
			zero = data_layer.getChild(0);
		}

		double[] arr = { zero.getX(), tran.getTranslateX(), tran.getScaleY(), tran.getTranslateY(), 0 };

		Paint color = (data_layer == calibrationSegment) ? Color.RED/* sig.getColor() */ : Color.yellow;
		for (int i = 0; i < arr.length; i++) {
			double d = arr[i];
			PNode pt_label = null;
			double align = 0;
			if (i == 0) {
				PText pt = new PText(df3.format(d));
				pt.setFont(ticFont);
				pt.setTextPaint(color);
				// pt.setHorizontalAlignment( Component.LEFT_ALIGNMENT );
				align = pt.getWidth() - 30;
				pt_label = pt;
			} else if (i == 1) {
				PText pt = new PText(df3.format(d));
				pt.setFont(ticFont);
				pt.setTextPaint(color);
				pt_label = pt;
			} else if (i < 4) {
				calib_label_x += 10;
				JFormattedTextField tf = new JFormattedTextField();
				tf.putClientProperty("data_layer", data_layer);
				tf.setFormatterFactory(GuiUtil.getNumberFormatterFactory());
				tf.setFont(tfFont);
				tf.setColumns(4);
				tf.setValue(round(d, 4));
				tf.addFocusListener((i == 2) ? gainFocusListener : offsetFocusListener);
				pt_label = new PSwing(tf); // df1.format(d));
				pt_label.translate(calib_label_x, currY);
			} else if (i == 4 && !first) {
				calib_label_x += 8;
				JButton remove = new JButton();
				remove.putClientProperty("sig", sig);
				remove.putClientProperty("layer", data_layer);
				remove.addActionListener(e -> removeAction(e));
				// remove.setIcon(new
				// ImageIcon(getClass().getResource("/idea/image/rewind-hot-icon.png")));
				remove.setIcon(removeIcon);
				remove.setPreferredSize(new Dimension(20, 20));
				pt_label = new PSwing(remove); // df1.format(d));
				pt_label.translate(calib_label_x, currY);
			}
			if (i == 0) {
				pt_label.addInputEventListener(this);
				pt_label.addAttribute("data_layer", data_layer);
				pt_label.addAttribute("parent_sig", sig);
				pt_label.addAttribute("parent_cam", cam);
			}

			if (pt_label != null) {
				pt_label.setX(calib_label_x - align);
				pt_label.setY(currY);
				axisLayer.addChild(pt_label);
				calib_label_x += 40;
			}
		}
	}

	private void removeAction(ActionEvent e) {
		JButton remove = (JButton) e.getSource();
		HPSplitableLayer sig = (HPSplitableLayer) remove.getClientProperty("sig");
		PLayer data_layer = (PLayer) remove.getClientProperty("layer");

		List<PLayer> childs = sig.getChildrenReference();
		PLayer curr = null;
		for (int i = 0; i < childs.size(); i++) {
			PLayer prev = curr; // you can't remove the first layer
			curr = childs.get(i);
			if (curr == data_layer) {
				childs.remove(i);
				while (data_layer.getChildrenCount() > 0) {
					prev.addChild(data_layer.getChild(0));
				}
				break;
			}
		}
		calibrationSegment = null;
		PNotificationCenter.defaultCenter().postNotification(LEGEND_SEG_SELECTED_NOTIFICATION, this);

		AppModel.setDirty(true);
	}

	private void drawCalibrationHeader(PLayer axisLayer, double left_ref) {
		double yBase = 10;
		PText pt_label = new PText("Calibration");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(8);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		yBase = 24;
		pt_label = new PText("Start");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("Time");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(yBase + 12);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("Phase");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 50);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("Gain");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 100);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("Bias");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 150);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("mmHg");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 150);
		pt_label.setY(yBase + 12);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		double xBase = left_ref - 10;
		yBase = 20;
		double w = 228;
		PPath brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase, yBase + 26);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase + w, yBase);
		brace.lineTo(xBase + w, yBase + 26);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase + w, yBase);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);

	}

	private void drawIntersectionHeader(PLayer axisLayer, double left_ref) {
		double yBase = 10;
		PText pt_label = new PText("Intersections");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(8);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		yBase = 24;
		pt_label = new PText("Signal");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("Name");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(yBase + 12);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("Value");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 50);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		double xBase = left_ref - 10;
		yBase = 20;
		double w = 140;
		PPath brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase, yBase + 26);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase + w, yBase);
		brace.lineTo(xBase + w, yBase + 26);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase + w, yBase);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);

	}

	private void drawUnusedHeader1(PLayer axisLayer, double left_ref) {
		double yBase = 10;
		PText pt_label = new PText("Available Signals");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 50);
		pt_label.setY(10);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		double xBase = left_ref;
		yBase = 20;
		double w = 210;
		PPath brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase, yBase + 10);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase + w, yBase);
		brace.lineTo(xBase + w, yBase + 10);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase + w, yBase);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);

	}

	private double drawUnusedHeader2(PLayer axisLayer, double left_ref, double yBase) {
		PText pt_label = new PText("Features");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 50);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		double xBase = left_ref;
		double w = 210;
		yBase += 10;
		PPath brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase, yBase + 10);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase + w, yBase);
		brace.lineTo(xBase + w, yBase + 10);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase + w, yBase);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);

		return yBase + 10;
	}

	public void drawFilterLegend(PLayer axisLayer, List<PCamera> bandCameras, double left_ref, PLayer activeLayer) {
		theme_y_range_color = Color.BLACK;
		drawFilterHeader(axisLayer, left_ref + 100);
		drawFilterLegendDetail(axisLayer, bandCameras, left_ref + 30, activeLayer);
	}

	private void drawFilterHeader(PLayer axisLayer, double left_ref) {
		double yBase = 10;
		PText pt_label = new PText("Filter");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(8);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		yBase = 24;
		pt_label = new PText("Filter");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		// pt_label = new PText("Time");
		// pt_label.setFont(ticFont);
		// pt_label.setX(left_ref);
		// pt_label.setY(yBase + 12);
		// pt_label.setTextPaint(theme_header_color);
		// axisLayer.addChild(pt_label);

		pt_label = new PText("N");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 50);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("E");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 100);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("F");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 150);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_header_color);
		axisLayer.addChild(pt_label);

		// pt_label = new PText("mmHg");
		// pt_label.setFont(ticFont);
		// pt_label.setX(left_ref + 150);
		// pt_label.setY(yBase + 12);
		// pt_label.setTextPaint(theme_header_color);
		// axisLayer.addChild(pt_label);
		//
		double xBase = left_ref - 10;
		yBase = 20;
		double w = 228;
		PPath brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase, yBase + 26);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase + w, yBase);
		brace.lineTo(xBase + w, yBase + 26);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(xBase, yBase);
		brace.lineTo(xBase + w, yBase);
		brace.setStrokePaint(theme_header_color);
		axisLayer.addChild(brace);

	}

	protected void drawFilterLegendDetail(PLayer axisLayer, List<PCamera> bandCameras, double left_ref,
			PLayer activeLayer) {

		double ttop = -1;
		for (PCamera cam : bandCameras) {
			if (cam == null)
				continue;

			PBounds bounds = cam.getBoundsReference();

			// this is the "legend/text left", not the band camera left
			double left = left_ref;

			TreeSet<HPSplitableLayer> sorted_sigs = sortSignals(cam);

			double top = bounds.getY() + 10;
			double bottom = bounds.getY() + cam.getHeight() - 5;
			double currY = top;
			if (ttop < 0) {
				ttop = top;
			}

			for (HPSplitableLayer sig : sorted_sigs) {
				PText pt_label = new PText(getLabelForSig(sig));

				pt_label.setFont(ticFont);
				pt_label.setX(left);
				pt_label.setY(currY);
				pt_label.setTextPaint(sig.getPaint());
				pt_label.addAttribute("sig", sig);
				pt_label.addAttribute("cam", cam);
				pt_label.addInputEventListener(this);

				axisLayer.addChild(pt_label);

				if (sig == activeLayer) {
					addFilterConfig(cam, sig, axisLayer, sig, left + 60, ttop);
				}

				currY += 20;
				if (currY > bottom) {
					left += 50;
					currY = top;
				}

			}
		}

	}

	private void addFilterDataLayer(PCamera cam, HPSplitableLayer sig, PLayer axisLayer, PLayer data_layer,
			double filter_label_x, double currY) {
		PAffineTransform tran = data_layer.getTransform();
		PNode zero;
		if (data_layer.getChildrenCount() == 0) {
			zero = new PNode();
		} else {
			zero = data_layer.getChild(0);
		}

		String[] filterTypes = { "None", "bwlpf", "bwhpf", "bwbpf", "bwbsf" };

		Paint color = (data_layer == calibrationSegment) ? Color.RED/* sig.getColor() */ : Color.yellow;
		double freq = 500;
		double s = 250;

		for (int i = 0; i < 4; i++) {
			PNode pt_label = null;
			if (i == 0) {
				// JPanel panel = new JPanel();
				// panel.setLayout(new FlowLayout());
				// for( String name : filterTypes ) {
				// panel.add( new JButton(name));
				// }
				// pt_label = new PSwing(panel);
				JComboBox combo = new JComboBox(filterTypes) {

					@Override
					public Point getLocationOnScreen() {
						Point pt2 = super.getLocationOnScreen();

						PSwing pswing = (PSwing) this.getClientProperty("pswing");
						double x = pswing.getTransform().getTranslateX();
						double y = pswing.getTransform().getTranslateY();
						return new Point((int) (pt2.getX() + x), (int) (pt2.getY() + y));
					}

				};
				combo.setPreferredSize(new Dimension(80, 18));
				pt_label = new PSwing(combo);
				pt_label.translate(filter_label_x, currY);

				combo.putClientProperty("pswing", pt_label);

			} else if (i == 1) {
				PText pt = new PText(df3.format(freq));
				pt.setFont(ticFont);
				pt.setTextPaint(color);
				pt_label = pt;
				filter_label_x += 50;
			} else if (i < 4) {
				filter_label_x += 10;
				JFormattedTextField tf = new JFormattedTextField();
				tf.putClientProperty("data_layer", data_layer);
				tf.setFormatterFactory(GuiUtil.getNumberFormatterFactory());
				tf.setFont(tfFont);
				tf.setColumns(4);
				tf.setValue(round(freq, 4));
				tf.addFocusListener((i == 2) ? gainFocusListener : offsetFocusListener);
				pt_label = new PSwing(tf); // df1.format(d));
				pt_label.translate(filter_label_x, currY);
			}
			if (i == 0) {
				// pt_label.addInputEventListener(this);
				pt_label.addAttribute("data_layer", data_layer);
				pt_label.addAttribute("axis_layer", axisLayer);
				pt_label.addAttribute("parent_sig", sig);
				pt_label.addAttribute("parent_cam", cam);
			}

			if (pt_label != null) {
				pt_label.setX(filter_label_x);
				pt_label.setY(currY);
				axisLayer.addChild(pt_label);
				filter_label_x += 40;
			}
		}
	}

	private void addFilterConfig(PCamera cam, HPSplitableLayer sig, PLayer axisLayer, PLayer data_layer, double left,
			double top) {

		Paint color = Color.WHITE;
		int COL_WIDTH = 74;
		String filterName = (String) data_layer.getAttribute("@filterName");
		if (filterName != null) {
			PText pt = new PText(filterName);
			pt.setWidth(COL_WIDTH - 6);
			pt.setHorizontalAlignment(Component.RIGHT_ALIGNMENT);
			pt.setFont(ticFont);
			pt.setTextPaint(color);
			pt.translate(left, top);
			axisLayer.addChild(pt);
		}
	}

	private void drawAnalysisHeader(PLayer axisLayer, double left_ref) {
		double yBase = 8;
		PText pt_label = new PText("Analysis");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref);
		pt_label.setY(10);
		pt_label.setTextPaint(theme_y_range_color);
		axisLayer.addChild(pt_label);

		yBase = 22;
		pt_label = new PText("Variable");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 10);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_y_range_color);
		axisLayer.addChild(pt_label);

		pt_label = new PText("Value");
		pt_label.setFont(ticFont);
		pt_label.setX(left_ref + 80);
		pt_label.setY(yBase);
		pt_label.setTextPaint(theme_y_range_color);
		axisLayer.addChild(pt_label);

		double xBase = left_ref;
		yBase = 20;
		double w = 160;
		drawBrace(axisLayer, yBase, xBase, w, 10);
	}

	private void drawBrace(PLayer axisLayer, double y, double x0, double w, double dy) {
		PPath brace = new PPath.Float();
		brace.moveTo(x0, y);
		brace.lineTo(x0, y + dy);
		brace.setStrokePaint(theme_y_range_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(x0 + w, y);
		brace.lineTo(x0 + w, y + dy);
		brace.setStrokePaint(theme_y_range_color);
		axisLayer.addChild(brace);
		brace = new PPath.Float();
		brace.moveTo(x0, y);
		brace.lineTo(x0 + w, y);
		brace.setStrokePaint(theme_y_range_color);
		axisLayer.addChild(brace);
	}

	public void drawGraphParamsLegend(PLayer axisLayer, List<PCamera> bandCameras, double left) {
		double last_y = 0;
		double extra_x = 0;
		for (PCamera cam : bandCameras) {
			PBounds bounds = cam.getBounds();
			double x = bounds.getX();
			double w = bounds.getWidth();
			last_y = drawGraphParamsDetail(axisLayer, cam, x + w + 36 + extra_x, bounds.getY());
			if (extra_x > 0) {
				extra_x = 0;
			} else {
				extra_x = (last_y > (bounds.y + bounds.height)) ? 120 : 0;
			}
		}
	}

	public double drawGraphParamsDetail(PLayer axisLayer, PCamera cam, double left, double curr_y) {
		PBounds vb = cam.getViewBounds();

		// this will also give you the view bounds
		PBounds bounds = cam.getBounds();
		// Point2D origin_window = new Point2D.Double(bounds.getX(),
		// bounds.getY());
		// Point2D origin_data = null;
		//
		// origin_data = tran.inverseTransform(origin_window, null);
		// System.out.println(cam.getName() + "@" + bounds.getY() + "/" +
		// bounds.getHeight() + " origin_data=" + origin_data );
		System.out.println(cam.getName() + "@" + bounds.getY() + "/" + bounds.getHeight() + " vb=" + vb);

		double[] arr = { vb.y + vb.height, vb.y, 0, 0 };
		String[] label = { "Range Max:", "Range Min:", "Locked:", "Baseline:" };

		Paint color = Color.WHITE;

		for (int i = 0; i < arr.length; i++) {
			double d = arr[i];
			double align = 0;

			PText pt = new PText(label[i]);
			pt.setFont(ticFont);
			pt.setTextPaint(color);
			// pt.setHorizontalAlignment( Component.LEFT_ALIGNMENT );
			align = pt.getWidth() - 30;
			pt.setX(left - align);
			pt.setY(curr_y);
			axisLayer.addChild(pt);

			if (i < 2) {
				JFormattedTextField tf = new JFormattedTextField();
				tf.putClientProperty("cam", cam);
				String typ = (i == 0) ? "@max" : "@min";
				tf.putClientProperty("typ", typ);
				tf.putClientProperty(typ, d);

				tf.setFormatterFactory(GuiUtil.getNumberFormatterFactory());
				tf.setFont(tfFont);
				tf.setColumns(4);
				tf.setValue(round(d, 3));
				tf.addFocusListener(rangeFocusListener);
				PNode pt_label = new PSwing(tf);
				pt_label.translate(left + 34, curr_y);
				axisLayer.addChild(pt_label);
			} else if (i == 2) {
				JCheckBox tf = new JCheckBox();
				tf.putClientProperty("cam", cam);
				tf.setFont(tfFont);
				tf.setSelected(cam.getAttribute("@locked") != null);
				tf.addFocusListener(lockFocusListener);
				PNode pt_label = new PSwing(tf);
				pt_label.translate(left + 34, curr_y);
				axisLayer.addChild(pt_label);
			} else {
				JCheckBox tf = new JCheckBox();
				tf.putClientProperty("cam", cam);
				tf.setFont(tfFont);
				tf.setSelected(cam.getAttribute("@baseline") != null);
				tf.addFocusListener(zeroFocusListener);
				PNode pt_label = new PSwing(tf);
				pt_label.translate(left + 34, curr_y);
				axisLayer.addChild(pt_label);
			}

			curr_y += 20;
		}

		return curr_y + 20;
	}

	private double round(double d, int prec) {
		BigDecimal bd = new BigDecimal(d);
		bd = bd.round(new MathContext(prec));
		double rounded = bd.doubleValue();
		return rounded;
	}
}
