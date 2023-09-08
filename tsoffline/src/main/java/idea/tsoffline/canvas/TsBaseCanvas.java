package idea.tsoffline.canvas;

import java.awt.Color;
import java.awt.Font;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.geom.Path2D;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import javax.swing.Timer;
import javax.swing.text.MutableAttributeSet;
import javax.swing.undo.UndoManager;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.activities.PActivity;
import org.piccolo2d.activities.PActivity.PActivityDelegate;
import org.piccolo2d.activities.PTransformActivity;
import org.piccolo2d.extras.nodes.PComposite;
import org.piccolo2d.extras.pswing.PSwingCanvas;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;

import idea.intf.DataTyp;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.tsoffline.AppFrame;
import idea.tsoffline.AppModel;
import idea.tsoffline.HPAnnotationLayer;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.LayerUtil;
import idea.tsoffline.canvas.edit.PanViewBoundsEdit;
import idea.tsoffline.canvas.edit.TransformEdit;
import idea.tsoffline.tspico.AnnotationEditorTool;
import idea.tsoffline.tspico.CursorLocatorTool;
import idea.tsoffline.tspico.TsCanvasToolInterface;

@SuppressWarnings("serial")
@Slf4j
public class TsBaseCanvas extends PSwingCanvas {
	public static final String ADD_ANNOTATION_PROPERTY = "ADD_ANNO_LAYER";
	public static final String ADD_FORMULA_PROPERTY = "ADD_FORMULA_LAYER";

	private static PropertyChangeSupport psupport;
	private   LinkedList<HPSplitableLayer> annotationModel= new LinkedList<HPSplitableLayer>();
	protected List<HPSplitableLayer> layers = new LinkedList<HPSplitableLayer>();

	@Getter
	private long startTime;
	@Getter
	@Setter
	private long stopTime;

	@Getter
	protected PLayer activeLayer;
	@Getter
	protected PLayer activeSegment;

	@Setter
	private boolean showStudyPhase;

	/*
	 * theme support
	 */
	protected Color theme_plot_background = Color.BLACK; // Color.DARK_GRAY;
	protected Color theme_tick_color = Color.WHITE;
	protected Color theme_slider_color = Color.LIGHT_GRAY;
	protected Color theme_ruler_color = Color.WHITE;
	protected Color theme_border_color = Color.BLUE;
	protected Color theme_y_range_color = Color.GREEN;
	// Color theme_annotation_text_color = Color.WHITE;

	private boolean debugBandTransforms;

	/*
	 * base class common with TsPhaseCanvas and TsPSwingCanvas
	 */
	@Getter
	protected List<PCamera> bandCameras = new LinkedList<PCamera>();
	public final static String BAND_ID = "bandID";
	protected final static String BAND_WEIGHT = "bandWeight";
	protected static final float BAND_SPACING = 4;

	public static final int PREF_ANIMATE_MS = 400;
	protected static final double PREF_ZOOM_X_MAX = 600; // max amount of zoom
	private static final double PREF_SCROLL = 0.3; // left-right scroll in 30%
													// increments

	UndoManager undoManager = new UndoManager();
	protected PTransformActivity transformActivity;

	AnnotationEditorTool annotationEditorHandler;
	public CursorLocatorTool lineTool; // FIXME: move back into
										// TsPSwingCanvas...when
										// TsCanvasToolInterface is ready!

	protected PLayer axisLayer;
	@Getter
	protected PLayer phaseLayer;
	protected static Font ticFont = new Font("Ariel", Font.BOLD, 10);

	private Timer redraw_timer;
	Double analysisPoint;
	
	public TsBaseCanvas() {
		
		psupport = new PropertyChangeSupport(this);
		resetAll();
		initKeyListener();

		getCamera().setPaint(theme_plot_background);

		axisLayer = new PLayer();
		axisLayer.setPickable(false);
		axisLayer.setChildrenPickable(true);
		axisLayer.setName("axis_layer");

		phaseLayer = new PLayer();
		phaseLayer.setPickable(false);
		phaseLayer.setChildrenPickable(true);
		phaseLayer.setName("phase_layer");

		// Surprisingly, this is not the default!
		this.setPanEventHandler(null);
		this.setZoomEventHandler(null);
		
	}

	// replace the SWING property change listener with our own, so that we can remove SWING from this class completely
	@Override
	public void addPropertyChangeListener(String prop, PropertyChangeListener listener) {
		psupport.addPropertyChangeListener(prop, listener);
	}
	
	@Override
	public void addPropertyChangeListener( PropertyChangeListener listener) {
		psupport.addPropertyChangeListener(listener);
	}

	/*
	 * FIXME: don't need to reference line tool if handled like most tools! ...why
	 * does lineTool need the start time anyway?
	 */
	public void setStartTime(long startTime) {
		this.startTime = startTime;

		if (lineTool != null) {
			lineTool.setStartTime(startTime);
		}
	}

	/*
	 * The update delegate performs three functions during animation: - sync layers
	 * so that everybody gets the same X offset - update axis redraws during
	 * animation - notify listeners when animation is complete
	 */
	PActivityDelegate updateDelegate = new PActivityDelegate() {

		long ms = 0;

		@Override
		public void activityStarted(PActivity activity) {
			List<TsCanvasToolInterface> tools = new LinkedList<TsCanvasToolInterface>();
			for (TsCanvasToolInterface tool : tools) {
				tool.activityStarted(activity);
			}

			// FIXME: Remove when tools() works
			// if( annotationEditorHandler != null ) {
			// annotationEditorHandler.activityStarted(activity);
			// }

			analysisPoint = null;
			_redrawAxisLayer();
			ms = System.currentTimeMillis();
		}

		@Override
		public void activityStepped(PActivity activity) {
			long ms2 = System.currentTimeMillis();
			if (ms2 - ms > 100) {
				_redrawAxisLayer();
				ms = ms2;
			}

			PCamera cam0 = bandCameras_get0();
			double sx = cam0.getViewTransform().getScaleX();
			double tx = cam0.getViewTransform().getTranslateX();
			syncTransforms(sx, tx);
		}

		@Override
		public void activityFinished(PActivity activity) {
			AppFrame.getInstance().showErrorMessage(null);
			double[] tr_arr = transformActivity.getDestinationTransform();
			PAffineTransform tr0 = new PAffineTransform(tr_arr);
			syncTransforms(tr0.getScaleX(), tr0.getTranslateX());

			List<TsCanvasToolInterface> tools = new LinkedList<TsCanvasToolInterface>();
			for (TsCanvasToolInterface tool : tools) {
				tool.activityFinished(activity);
			}

			// FIXME: Remove when tools() works
			if (annotationEditorHandler != null) {
				annotationEditorHandler.activityFinished(activity);
			}

			// FIXME: Remove when tools() works
			if (lineTool != null) {
				lineTool.activityFinished(activity);
			}

			_redrawAxisLayer();

			fireUpdateFinished();
		}
	};

	/*
	 * The final delegate sync layers when animation is complete, this is needed
	 * when animating multiple cameras. You may need to animate multiple cameras to
	 * get a smooth flow...the delegate is not called with every redraw cycle
	 */
	PActivityDelegate finalDelegate = new PActivityDelegate() {

		@Override
		public void activityStarted(PActivity activity) {
			// ignore

			List<TsCanvasToolInterface> tools = new LinkedList<TsCanvasToolInterface>();
			for (TsCanvasToolInterface tool : tools) {
				tool.activityStarted(activity);
			}

			// FIXME: Remove when tools() works
			if (annotationEditorHandler != null) {
				annotationEditorHandler.activityStarted(activity);
			}

		}

		@Override
		public void activityStepped(PActivity activity) {
			// ignore
		}

		@Override
		public void activityFinished(PActivity activity) {
			double[] tr_arr = transformActivity.getDestinationTransform();
			PAffineTransform tr0 = new PAffineTransform(tr_arr);
			syncTransforms(tr0.getScaleX(), tr0.getTranslateX());

			List<TsCanvasToolInterface> tools = new LinkedList<TsCanvasToolInterface>();
			for (TsCanvasToolInterface tool : tools) {
				tool.activityFinished(activity);
			}

			// FIXME: Remove when tools() works
			if (annotationEditorHandler != null) {
				annotationEditorHandler.activityFinished(activity);
			}

			// FIXME: Remove when tools() works
			if (lineTool != null) {
				lineTool.activityFinished(activity);
			}

			_redrawAxisLayer();
			fireUpdateFinished();
		}
	};
	private PActivityDelegate pactivityListener;

	protected void _redrawAxisLayer() {
		axisLayer.removeAllChildren();
		for (PCamera cam : bandCameras) {
			drawBoundingBox(axisLayer, cam.getBounds());
		}
	}

	public void clearAnnotations() {
		annotationModel = new LinkedList<HPSplitableLayer>();
	}

	public PLayer getAnnotationLayer(String layerName) {
		PLayer editLayer = null;

		// use the last layer as the editable layer
		Iterator<HPSplitableLayer> ii = annotationModel.iterator();
		while (ii.hasNext()) {
			HPSplitableLayer info = ii.next();
			if (layerName.equals(info.getName())) {
				editLayer = info;
				break;
			}
		}

		return editLayer;
	}

	public List<HPSplitableLayer> getAnnotationModel() {
		return annotationModel;
	}
	public void removeAnnotationLayer(String loc) {

		Iterator<HPSplitableLayer> ii = annotationModel.iterator();
		while (ii.hasNext()) {
			HPSplitableLayer info = ii.next();
			if (loc.equals(info.getLocation())) {
				ii.remove();
			}
		}
	}

	public void resetAll() {
		clearAnnotations();
		log.error("FIXME: add clearData();");
		AppModel.setDirty(false);
	}



	/**
	 * This route adds/removes the phase layer to/from each of the band cameras to
	 * simulate he effect of turning the layer on or off. It is ineffective to turn
	 * the layer on or off because this affects the overview timeline as well. The
	 * phase layer should always be visible in the overview timeline.
	 * 
	 * @param show
	 */
	protected void showPhaseLayer(boolean b) {
		for (PCamera cam : bandCameras) {
			if (b && showStudyPhase) {
				List<PLayer> layers = cam.getLayersReference();
				for (PLayer layer : layers) {
					if (layer == phaseLayer) {
						return; // don't add twice
					}
				}
				cam.addLayer(phaseLayer);
			} else {
				cam.removeLayer(phaseLayer);
			}
		}
	}

	protected PCamera bandCameras_get0() {
		for (PCamera cam : bandCameras) {
			Object nosync = cam.getAttribute("nosync");
			if (nosync == null) {
				return cam;
			}
		}
		return null;
	}

	public void redrawAxisLayer(int dt) {

		if (redraw_timer != null && redraw_timer.isRunning() && dt > 0) {
			// STOPPING REDRAW THREAD
			redraw_timer.stop();
		}

		if (dt == 0) {
			_redrawAxisLayer();
		} else {

			ActionListener listener = new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					_redrawAxisLayer();
				}
			};
			redraw_timer = new Timer(dt + 10, listener);

			redraw_timer.setRepeats(false);
			redraw_timer.start();

		}
	}

	protected void _addCamerasToAxisLayer() {
		int pos = axisLayer.getChildrenCount();
		for (PCamera cam : bandCameras) {
			if (debugBandTransforms) {
				drawBandTransformInfo(axisLayer, cam);
			}
			// 22FEB17 WLB: replaced axisLayer.getAllNodes() with getChildReference()
			if (axisLayer.getChildrenReference().contains(cam)) {
				log.error("re-adding camera? " + cam.getName());
			}
			axisLayer.addChild(pos, cam); // add to the bottom
		}

	}

	private void initKeyListener() {
		this.addKeyListener(new KeyListener() {

			@Override
			public void keyPressed(KeyEvent e) {
				PCamera cam0 = getCameraAtMousePos();
				processKeyPressed(cam0, e);
			}

			@Override
			public void keyReleased(KeyEvent e) {
			}

			@Override
			public void keyTyped(KeyEvent e) {
			}
		});

	}

	protected void processKeyPressed(PCamera cam0, KeyEvent e) {
		int keyCode = e.getKeyCode();
		double mod = (e.isControlDown()) ? 0.1 : 1;
		if (keyCode == KeyEvent.VK_LEFT) {
			moveLeftRight(-1 * mod);
			e.consume();
		} else if (keyCode == KeyEvent.VK_RIGHT) {
			moveLeftRight(1 * mod);
			e.consume();
		} else if (keyCode == KeyEvent.VK_PAGE_UP) {
			moveUpDown(cam0, -3 * mod);
			e.consume();
		} else if (keyCode == KeyEvent.VK_UP) {
			moveUpDown(cam0, -1 * mod);
			e.consume();
		} else if (keyCode == KeyEvent.VK_DOWN) {
			moveUpDown(cam0, 1 * mod);
			e.consume();
		} else if (keyCode == KeyEvent.VK_PAGE_DOWN) {
			moveUpDown(cam0, 3 * mod);
			e.consume();
		} else if (keyCode == KeyEvent.VK_C) {
			centerView(cam0);
			e.consume();
		} else if (keyCode == KeyEvent.VK_F10) {
			dumpBands(3, 0, getLayer());
			dumpSignals(layers);

			debugBandTransforms = !debugBandTransforms;
			_redrawAxisLayer();
			e.consume();
		}
	}

	public void applyPanToBounds(PCamera node, PBounds original) {
		transformActivity = node.animateViewToPanToBounds(original, TsPSwingCanvas.PREF_ANIMATE_MS);
		transformActivity.setDelegate(updateDelegate);
	}

	public void moveLeftRight(double dir) {

		PCamera cam0 = getCameraAtMousePos();
		if (cam0 == null) {
			cam0 = bandCameras_get0();
		}
		if (cam0 == null) {
			// what do you mean there are no cameras?
			return;
		}
		PBounds view_rr = cam0.getViewBounds();
		double data_width = view_rr.getWidth();

		int dt = PREF_ANIMATE_MS;

		if (transformActivity != null && transformActivity.isStepping()) {
			transformActivity.terminate(PActivity.TERMINATE_AND_FINISH);
		}

		Object nosync = cam0.getAttribute("nosync");
		boolean cam0_only = (nosync != null); // if this cam0 is no-sync, then
												// dont scroll the others!

		boolean first = true;
		for (PCamera cam : bandCameras) {
			if (cam0_only && cam != cam0) {
				continue; // only cam0
			}

			if (cam == cam0) {
				// this is the selected camera: it must get scrolled
			} else {
				// this one might get skipped...
				nosync = cam.getAttribute("nosync");
				if (nosync != null) {
					continue; // skip camera with no-sync selected
				}
			}
			PBounds ori_r = cam.getViewBounds();
			PBounds view_r = cam.getViewBounds();
			view_r.moveBy(data_width * dir * PREF_SCROLL, 0);
			transformActivity = cam.animateViewToPanToBounds(view_r, dt);
			if (first && !cam0_only) {
				transformActivity.setDelegate(finalDelegate);
				first = false;
			}

			undoManager.addEdit(new PanViewBoundsEdit(this, cam, ori_r, view_r));
		}

		redrawAxisLayer(dt);

	}

	public void moveUpDown(PCamera cam0, double mdir) {

		if (cam0 == null) {
			cam0 = getCameraAtMousePos();
		}

		if (cam0 == null && bandCameras.size() == 1) {
			cam0 = bandCameras_get0();
		}

		if (cam0 == null) {
			log.error("moveUpDown: No camera available for transform?");
			return;
		}

		PAffineTransform sc = cam0.getTransform();

		int dt = PREF_ANIMATE_MS;

		PBounds r = cam0.getViewBounds();
		double h = r.height;

		// scaling up and down only depends on the camera scale, not the layer
		// scale
		double delta = h / 8;

		Object nosync = cam0.getAttribute("nosync");
		boolean cam0_only = (nosync != null); // if this cam0 is no-sync, then
												// dont scroll the others!

		PBounds ori_rect = cam0.getViewBounds();
		if (sc.getScaleY() > 0) {
			mdir = -mdir;
		}
		r.moveBy(0, -mdir * delta);
		// The cameras are vertically independent. We only move the selected
		// camera up/down.
		transformActivity = cam0.animateViewToPanToBounds(r, dt);
		if (!cam0_only) {
			transformActivity.setDelegate(updateDelegate);
		}
		undoManager.addEdit(new PanViewBoundsEdit(this, cam0, ori_rect, r));

	}

	private void drawBandTransformInfo(PLayer axisLayer, PCamera cam) {
		PAffineTransform tr = cam.getTransform();
		PAffineTransform vt = cam.getViewTransform();

		PAffineTransform[] arr = { tr, vt };
		double top = cam.getY() + 10;
		double left = cam.getX() + 10;
		for (PAffineTransform t : arr) {
			PText pt_label = new PText(t.toString());
			pt_label.setFont(ticFont);
			pt_label.setX(left); // center around tic
			pt_label.setY(top); // center the font around the tic
			pt_label.setTextPaint(theme_ruler_color); // y_ruler.color
			axisLayer.addChild(pt_label);

			top += 14;
		}

		// top = cam.getY() + 10;
		left = cam.getX() + 140;
		for (int i = 0; i < cam.getLayerCount(); i++) {
			PLayer layer = cam.getLayer(i);
			if (layer.getVisible()) {
				PText pt_label = new PText(layer.getName() + ": " + layer.getTransform().toString());
				pt_label.setFont(ticFont);
				pt_label.setX(left); // center around tic
				pt_label.setY(top); // center the font around the tic
				pt_label.setTextPaint(theme_ruler_color); // y_ruler.color
				axisLayer.addChild(pt_label);

				top += 14;
			}
		}
	}

	private static void dumpBands(int level, int suffix, PNode parent) {
		if (level < 0) {
			return;
		}

		String pad = "      ".substring(level);
		String id = level + "." + suffix;
		String name = parent.getName();
		if (name == null) {
			if (parent instanceof PPath.Float) {
				// ignore
			} else if (parent instanceof PText) {
				// ignore
			} else if (parent instanceof HPPath) {
				// ignore
			} else if (parent instanceof PComposite) {
				// ignore
			} else {
				System.out.println(pad + id + " me=" + parent.getClass() + " bounds=" + parent.getBounds() + " childs="
						+ parent.getChildrenCount());
			}
		} else {
			if (parent instanceof LinkedNode) {
				// ignore
				// name is probably sw0
			} else {
				System.out.println(pad + id + " me=" + parent.getName() + " bounds=" + parent.getBounds() + " childs="
						+ parent.getChildrenCount());
			}
		}

		if (parent instanceof PLayer) {
			PLayer layer = (PLayer) parent;
			System.out.print(pad + " * cams=" + layer.getCameraCount());
			for (Object cam : layer.getCamerasReference()) {
				System.out.print(" " + ((PNode) cam).getName());
			}
			System.out.println();
		}

		for (int i = 0; i < parent.getChildrenCount(); i++) {
			PNode node = parent.getChild(i);
			dumpBands(level - 1, i, node);
		}
		if (parent instanceof PCamera) {
			PCamera cam = (PCamera) parent;
			System.out.println(pad + "**Drilling layers of cam: " + cam.getName());

			for (int i = 0; i < cam.getLayerCount(); i++) {
				PLayer layer = cam.getLayer(i);
				dumpBands(level - 1, i + 100, layer);
			}
		}
	}

	private void dumpSignals(List<HPSplitableLayer> ll) {
		for (HPSplitableLayer sig : ll) {
			System.out.print(sig.getLocation() + "/" + sig.getCode() + "/" + sig.getName() + "  ");
			if (sig.getVisible() == false) {
				System.out.println("invisible: " + sig.getName());
			} else {
				System.out.println(
						sig.getName() + "  count=" + sig.getChildrenCount() + " hash=" + sig.hashCode() + " o=" + sig);
			}
		}

	}

	/*
	 * SECTION copied from TsPSwingCanvas
	 */
	protected void resizeCameras(float top, float left_margin, float plot_width, float plot_h) {

		float avail_h = plot_h;

		float totalWeight = 0;
		for (PCamera cam : bandCameras) {
			MutableAttributeSet props = cam.getClientProperties();
			double weight = ((Number) props.getAttribute(BAND_WEIGHT)).doubleValue();
			if (weight < 0) { // indicates a fixed size
				avail_h += weight;
			} else {
				totalWeight += weight;
			}
		}
		for (PCamera cam : bandCameras) {
			 MutableAttributeSet props = cam.getClientProperties();
			double weight = ((Number) props.getAttribute(BAND_WEIGHT)).doubleValue();
			double band_h = avail_h * weight / totalWeight - BAND_SPACING;
			if (weight < 0) {
				band_h = -weight;
			}
			Rectangle2D band_rect = new Rectangle2D.Double(left_margin, top, plot_width, band_h);
			cam.setBounds(band_rect);
			top += band_h + 4;
			Object locked = cam.getAttribute("@locked");
			if (locked != null) {
				resizeCameraViewArea(cam);
			}
		}
	}

	protected void resizeCameraViewArea(PCamera cam) {
		Double min = (Double) cam.getAttribute("@min");
		Double max = (Double) cam.getAttribute("@max");

		if (min == null || max == null) {
			return;
		}

		PBounds vb = cam.getViewBounds();

		double h = max - min;
		vb = new PBounds(vb.getX(), min, vb.getWidth(), h);

		cam.setViewBounds(vb);
	}

	protected AffineTransform zoomLayerYScaleToRectangle(PLayer layer, PBounds layoutBounds, PBounds dataBounds) {

		PCamera cam0 = bandCameras_get0();

		// FIXME: This is so wrong!!! Change the LayerUtil method to take a
		// PBounds
		Point2D dataPt0 = new Point2D.Double(dataBounds.getMinX(), dataBounds.getMaxX());
		Point2D dataPt2 = new Point2D.Double(dataBounds.getMinY(), dataBounds.getMaxY());

		AffineTransform desired = LayerUtil.getTransformForLayer(layoutBounds, dataPt0, dataPt2, PREF_ZOOM_X_MAX);
		AffineTransform camera_transform = cam0.getViewTransform();

		// new AffineTransform(desired.getScaleX(), 0, 0, -1,
		// desired.getTranslateX(), 300 + TOP_MARGIN);

		// desired = camera*layer
		// camera_inv* desired = camera_inv * camera * layer --> layer
		// AffineTransform layer_m = new AffineTransform(1, 0, 0,
		// desired.getScaleY(), 0, desired.getTranslateY());
		AffineTransform layer_m = null;
		try {
			// log.debug("** PREZOOM layer transform: {}",
			// layer.getTransform());
			layer_m = camera_transform.createInverse();
			layer_m.concatenate(desired);

			// WLB 09-MAR-2015: This whole routine is suspect, been changed many
			// times for many purposes
			// In current and anticipated usage, the X scale should remain 1.
			// Only y scale and translation should change
			layer_m = new AffineTransform(1, 0, 0, layer_m.getScaleY(), 0, layer_m.getTranslateY());
			layer.setTransform(layer_m);

		} catch (NoninvertibleTransformException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// log.warn("redrawAxisLayer(0); -- but this loop can be called a
		// lot!");
		return layer_m;
	}

	/*
	 * Only changes the X scale of the camera. No layer changes.
	 */
	public AffineTransform zoomCameraToXScale(PCamera cam, double start_x, double end_x) {

		if (transformActivity != null) {
			// if rescaling animation is in progress for this canvas, cancel it!
			transformActivity.terminate(PActivity.TERMINATE_WITHOUT_FINISHING);
		}

		AffineTransform ori = cam.getViewTransform();
		AffineTransform desired = LayerUtil.getTransformForCamera(cam, start_x, end_x, PREF_ZOOM_X_MAX);

		int dt = PREF_ANIMATE_MS;
		double m00 = desired.getScaleX();
		if (Double.isNaN(m00)) {
			for (PCamera cam_n : bandCameras) {
				cam.setViewTransform(desired);
				System.out.println("00: setViewTransform " + cam_n.getName() + " SIGCAM: " + cam_n.getViewTransform());
			}
			log.error("ZTR cant animate from NaN", desired);
		} else {
			transformActivity = cam.animateViewToTransform(desired, dt);
			if (cam.getAttribute("nosync") == null) {
				transformActivity.setDelegate(updateDelegate);
			}
			undoManager.addEdit(new TransformEdit(this, cam, ori, desired));
		}

		return desired;
	}

	public void applyTransform(PNode node, AffineTransform tr) {
		if (node instanceof PLayer) {
			PLayer layer = ((PLayer) node);
			layer.setTransform(tr);
			layer.repaint();
			_redrawAxisLayer();
		} else {
			if (annotationEditorHandler != null) {
				// this will show/hides all the annotations
				annotationEditorHandler.getLayer().setVisible(false);
			}
			transformActivity = node.animateToTransform(tr, TsPSwingCanvas.PREF_ANIMATE_MS);
			transformActivity.setDelegate(updateDelegate);
		}
	}

	public void syncTransforms(double sx, double tx) {

		for (PCamera cam : bandCameras) {
			Object nosync = cam.getAttribute("nosync");
			if (nosync == null) {
				double ty = cam.getViewTransform().getTranslateY();
				double sy = cam.getViewTransform().getScaleY();
				cam.getViewTransformReference().setToScale(sx, sy);
				cam.getViewTransformReference().setOffset(tx, ty);
			}
		}

	}

	public PCamera getCameraAtMousePos() {
		Point pos = getMousePosition();

		if (pos == null) {
			// this can happen when the mouse is not over the application
			// that has the keyboard focus.
			return null;
		}

		for (int i = 0; i < bandCameras.size(); i++) {
			PCamera cam = bandCameras.get(i);
			if (cam.getBounds().contains(pos)) {
				return cam;
			}
		}
		return null;
	}

	public void centerView(PCamera cam) {
		if (cam == null) {
			for (PCamera cam0 : getBandCameras()) {
				_centerCamera(cam0);
			}
		} else {
			_centerCamera(cam);
		}
		_redrawAxisLayer();
	}

	public void _centerCamera(PCamera cam) {
		if (cam.getLayerCount() == 0) {
			return;
		}
		PBounds r = cam.getViewBounds();
		double startX = 0;
		double endX = 0;

		int cameraType = 0; // timeline camera
		if (cam.getAttribute("nosync") != null) {
			cameraType = 1; // phase space camera
		}

		if (cameraType == 0) {
			startX = r.getX();
			endX = startX + r.getWidth();
		} else {
			startX = Double.MIN_VALUE;
			endX = Double.MAX_VALUE;
		}

		Rectangle2D data_bounds = null;
		for (Object o : cam.getLayersReference()) {
			HPSplitableLayer splitable = (HPSplitableLayer) o;
			if (splitable.getVisible() == false) {
				continue; // ignore hidden layers
			}
			if (splitable.getAttribute("background") != null) {
				continue; // ignore hidden layers
			}

			for (Object oo : splitable.getChildrenReference()) {
				PLayer layer = (PLayer) oo;
				@SuppressWarnings("unchecked")
				List<PNode> nodes = layer.getChildrenReference();
				// FIXME: this only applies to timeline cameras, phase space cameras
				// are different!
				PBounds raw_bounds = getDataRange(nodes, startX, endX);
				PBounds layer_bounds = new PBounds();
				layer.getTransform().transform(raw_bounds, layer_bounds);

				if (data_bounds == null) {
					data_bounds = layer_bounds;
				} else {
					data_bounds = data_bounds.createUnion(layer_bounds);
				}
			}

		}

		System.out.println("[DATA BOUNDS]: " + data_bounds);
		if (data_bounds == null) {
			// no layers to center
			return;
		}

		double dy = 0.15 * (data_bounds.getHeight());
		// r.y = data_ymin - dy;
		// r.height = data_ymax - data_ymin + dy;

		// FIXME: timeline camera
		if (cameraType == 0) {
			System.out.println(
					"[TIMESERIES CAM] " + cam.getName() + " view bounds=" + r + " trans=" + cam.getViewTransform());
			// WLB 020717 This loop should disappear!

			double l_sy = -1;
			double l_avg_y = -1;

			for (Object o : cam.getLayersReference()) {
				PLayer layer = (PLayer) o;
				if (layer.getVisible() == false) {
					continue; // ignore hidden layers
				}

				PAffineTransform tran = new PAffineTransform(); // identity
				double h = cam.getHeight();
				tran.translate(0, h / 2);

				double data_ymax = data_bounds.getMaxY();
				double data_ymin = data_bounds.getMinY();

				l_sy = h / (data_ymax - data_ymin + dy);
				tran.scale(1, l_sy);
				l_avg_y = (data_ymax + data_ymin) / 2;
				tran.translate(0, -l_avg_y);

			}

			// WLB 020717 -- this call should disappear
			// WLB 020717 zoomCameraToXScale(cam, startX, endX);

			if (transformActivity != null) {
				// if rescaling animation is in progress for this canvas, cancel it!
				transformActivity.terminate(PActivity.TERMINATE_WITHOUT_FINISHING);
			}

			Rectangle2D.Double camera_r = cam.getBounds();

			double sx = camera_r.getWidth() / (endX - startX);
			double sy = -1;
			sy = -l_sy;

//			if (maxXMag > 0 && sx > maxXMag) {
//				sx = maxXMag; // keep the user from doing something he doesn't
//			}

			double txx = camera_r.getX() - sx * startX;
			double tyy = camera_r.getHeight() / 2 + cam.getY();
			double diff = l_avg_y * l_sy;
			tyy += diff;

			AffineTransform desired = new PAffineTransform(sx, 0.0f, 0.0f, sy, txx, tyy); // + (l_avg_y/l_sy));
			cam.setViewTransform(desired);

		} else if (cameraType == 1) {
			System.out.println("[PHASE CAM] " + cam.getName() + " old view bounds=" + r);
			System.out.println("[PHASE CAM] " + cam.getName() + " old trans=" + cam.getViewTransform());

			// FIXME: temporary! layer should be unit transform!
			for (Object o : cam.getLayersReference()) {
				PLayer layer = (PLayer) o;
				System.out.println("[PHASE LAYER] " + layer.getName() + " trans=" + layer.getTransform());
			}

			double sx = cam.getWidth() / (data_bounds.getMaxX() - data_bounds.getMinX());
			double sy = -cam.getHeight() / (data_bounds.getMaxY() - data_bounds.getMinY()); // invert
																							// the
																							// signal
																							// coordinates

			PAffineTransform tran = new PAffineTransform(); // identity
			double h = cam.getHeight();
			double w = cam.getWidth();
			tran.translate(w / 2, h / 2);
			tran.scale(sx, sy);

			cam.setViewTransform(tran); // fix the transform for tye Y scale
			System.out.println("[PHASE CAM] " + cam.getName() + " new trans=" + tran);
		}

	}

	/*
	 * This works for timeseries lines
	 */
	public PBounds getDataRange(Collection<PNode> nodes, double startX, double endX) {

		boolean inited = false;

		double xmin = 0, xmax = 0; // initialization used by java validation
		// checker only
		double ymin = 0, ymax = 0; // initialization used by java validation
		// checker only

		if (startX == endX) {
			endX = Double.MAX_VALUE;
		}

		float[] coords = new float[2];
		// int n_nodes = nodes.size();

		log.debug("FIXME: binary search to determine nodes I need...TIMELINE ONLY!...would not work for PHASE");

		// int idx = 0;
		for (PNode node : nodes) {

			if (node instanceof PLayer) {
				log.warn("FIXME: layer child of layer: " + ((PLayer) node).getName());
				continue;
			}
			PBounds bounds = node.getBounds();
			double x0 = bounds.getMinX();
			double y0 = bounds.getMinY();
			double x1 = bounds.getMaxX();
			double y1 = bounds.getMaxY();

			if (x1 < startX || x0 > endX) {
				continue;
			}

			if (!inited) {
				ymin = bounds.getMinY();
				ymax = bounds.getMaxY();
				xmin = bounds.getMinX();
				xmax = bounds.getMaxX();
				inited = true;
			}

			if (node instanceof PText) {
				PText txt = (PText) node;

				for (int i = 0; i < 2; i++) {
					if (x0 >= startX && x0 <= endX) {
						ymin = Math.min(y0, ymin);
						ymax = Math.max(y0, ymax);
						xmin = Math.min(x0, xmin);
						xmax = Math.max(x0, xmax);
					}
					x0 += txt.getWidth();
					y0 += txt.getHeight();
				}

			} else if (node instanceof HPPath) {
				// idx++;
				PBounds b1 = bounds;
				ymin = Math.min(b1.getMinY(), ymin);
				ymax = Math.max(b1.getMaxY(), ymax);
				xmin = Math.min(b1.getMinX(), xmin);
				xmax = Math.max(b1.getMaxX(), xmax);
				// }
			} else if (node instanceof LinkedNode) {
				LinkedNode n = (LinkedNode) node;
				xmin = n.getX();
				xmax = n.getX();
				ymin = n.getY();
				ymax = n.getY();
			} else if (node instanceof PPath) {
				PPath p = (PPath) node;

				Path2D path = p.getPathReference();
				PathIterator it = path.getPathIterator(null);

				while (!it.isDone()) {
					it.next();

					if (!it.isDone()) {
						it.currentSegment(coords);
						x0 = coords[0];
						y0 = coords[1];
						if (x0 >= startX && x0 <= endX) {
							ymin = Math.min(y0, ymin);
							ymax = Math.max(y0, ymax);
							xmin = Math.min(x0, xmin);
							xmax = Math.max(x0, xmax);
						}
					}
				}
			} else { // this will get PLine and any other items

				ymin = Math.min(bounds.getMinY(), ymin);
				ymax = Math.max(bounds.getMaxY(), ymax);
				xmin = Math.min(bounds.getMinX(), xmin);
				xmax = Math.max(bounds.getMaxX(), xmax);
			}
		}

		if (xmin < startX) {
			xmin = startX;
		}
		if (xmax > endX) {
			xmax = endX;
		}

		if (ymax <= ymin) {
			ymax += 1.0;
			ymin -= 1.0;
		}

		PBounds rect = new PBounds(xmin, ymin, (xmax - xmin), (ymax - ymin));

		return rect;
	}

	//
	// draw plot area bounding box and white background
	//
	protected void drawBoundingBox(PLayer layer, PBounds bounds) {
		// NOTE: the selector tool expects this box to come first for the
		// signalCamera. It inserts and itself second!
		// That puts the selector box on top of this white backdrop but behind
		// the signal camera
		PPath p = PPath.createRectangle((float) (bounds.getX() - 1), (float) bounds.getY() - 1,
				(float) (bounds.getWidth() + 2), (float) bounds.getHeight() + 1);
		p.setPaint(theme_plot_background);
		p.setStrokePaint(theme_border_color);
		layer.addChild(p);
	}

	protected void thisComponentResized(ComponentEvent e) {
		// override if needed
	}

	public PCamera findSignalCamera(String sigName) {

		// first, check to see if the signal layer is already assigned to a
		// camera
		for (PCamera band : bandCameras) {
			// check each layer
			for (int idx = 0; idx < band.getLayerCount(); idx++) {
				PLayer layer = band.getLayer(idx);
				if (sigName.equals(layer.getName())) {
					return band;
				}
			}
			// check the configuration to see if the layer SHOULD be assigned to
			// this camera
		}

		return null;
	}

	public PCamera addBand(int band_id, double weight) {
		return insertBand(bandCameras.size(), band_id, weight);
	}

	public void addReferenceLine(PCamera band, double pos) {
		List<Double> refLines = (List<Double>) band.getAttribute("@refLines");
		if (refLines == null) {
			refLines = new LinkedList<Double>();
			band.addAttribute("@refLines", refLines);
		}
		refLines.add(pos);
	}

	public PCamera insertBand(int idx, int band_id, double weight) {
		if (band_id < 0) {
			band_id = bandCameras.size();
		}
		PCamera cam = new PCamera();
		MutableAttributeSet props = cam.getClientProperties();
		props.addAttribute(BAND_ID, band_id);
		props.addAttribute(BAND_WEIGHT, weight);
		if (showStudyPhase) {
			cam.addLayer(phaseLayer);
		}

		cam.setName("band_" + band_id);
		bandCameras.add(idx, cam);
		if (lineTool != null) {
			cam.addInputEventListener(lineTool);
		}
		return cam;
	}

	public HPSplitableLayer addAnnotationLayer(String name, Color color, String source) {

		if (name == null) {
			int seq = 1;
			name = "Annotation";

			Iterator<HPSplitableLayer> it = annotationModel.descendingIterator();
			while (it.hasNext()) {
				HPSplitableLayer sig = it.next();
				if (name.equals(sig.getName())) {
					seq++;
					name = "Annotation[" + seq + "]";
					it = annotationModel.descendingIterator(); // restart the
																// scan...a kind
																// of bubble
																// sort
				}
			}
			// we have a unique name
		}
		RpMetric m = new RpMetric("val", null, name, RpLinearUnit.unit, DataTyp.STRING_TYP);
		HPSplitableLayer layer = new HPAnnotationLayer(m );
		layer.setPaint(color);
		layer.setDefaultColor(color);
		layer.setSource(source);
		layer.setName(name);

		m.setSamplesPerPacket(100);
		log.error("FIXME: SETTING A BOGUS STRING LENGTH FOR " + name);

//		HPSplitableLayer info = new HPSplitableLayer(m);
//		info.setPaint(color);
//		info.setDefaultColor(color);
//		info.setSource(source);
//		info.setName( name );
//		layer.addAttribute("sig", info); // sig);
		
		annotationModel.addLast(layer); // last layer is the editable layer
		// sig.setSignalLayer(layer); // bi-directional link


		psupport.firePropertyChange(ADD_ANNOTATION_PROPERTY, null, layer);
		return layer;
	}


	public void addDataLayer(int band_id, HPSplitableLayer layer) {
		if (layer instanceof HPSplitableLayer) {
			// just add it
		} else {
			log.error("Cannot add non-splittable layer");
			return;
		}
		PCamera dest = null;
		for (PCamera camera : bandCameras) {
			MutableAttributeSet props = camera.getClientProperties();
			if ((Integer) props.getAttribute(BAND_ID) == band_id) {
				dest = camera;
				break;
			}
		}
		_addSignalLayer(dest, layer);
	}

	/**
	 * 
	 * @param camera
	 * 
	 * Camera to which the layer should be added.  If this is null, then the first camera is used.
	 * 
	 * @param layer
	 * 
	 * Data layer to add to the camera
	 */
	private void _addSignalLayer(PCamera camera, HPSplitableLayer layer) {

		if (layer instanceof HPSplitableLayer) {
			// just add it
		} else {
			log.error("Cannot add non-splittable layer");
			return;
		}
		
		// we may be adding the layer to a new band...so don't duplicate in 
		// it's always safe to attempt to remove
		layers.remove( layer );  
		layers.add(layer);

		if (camera == null) {
			camera = bandCameras.get(0);
		}

		// /*
//		 * initially, all layers have the same layer transform for each camera
//		 */
//		if (camera.getLayerCount() > 0) {
//			PLayer l0 = camera.getLayer(0);
//			layer.setTransform(l0.getTransform());
//
//		}
//
//		AffineTransform identity = new AffineTransform();
//		layer.setTransform(identity);
		// AVOID DUPLICATES REMOVE/ADD: " + layer.getName() + " from CAM=" +
		// camera.getName());
		camera.removeLayer(layer);
		camera.addLayer(layer);

		// layer.setVisible(true);
		this.firePropertyChange("addLayer", null, layer);
	}

	public void removeSignalLayer(PLayer layer) {

		if (layer == null) {
			return;
		}
		for (PCamera cam : bandCameras) {
			cam.removeLayer(layer);
			layer.removeCamera(cam);
		}
		layers.remove(layer);
	}

	public HPSplitableLayer[] getSigs() {

		HPSplitableLayer[] arr = new HPSplitableLayer[layers.size()];
		layers.toArray(arr);
		return arr;
	}
	
	public HPSplitableLayer[] getAnnotations() {

		HPSplitableLayer[] arr = new HPSplitableLayer[annotationModel.size()];
		annotationModel.toArray(arr);
		return arr;
	}
	

	public HPSplitableLayer findSignal(String loc) {
		for( HPSplitableLayer layer : layers) {
			if( loc.equals( layer.getLocation() ) ) {
				return layer;
			}
		}
		for( HPSplitableLayer layer : annotationModel) {
			if( loc.equals( layer.getLocation() ) ) {
				return layer;
			}
		}
		return null;
	}


	public void addPActivityListener(PActivityDelegate pad) {
		pactivityListener = pad;
	}

	protected void fireUpdateFinished() {
		if (pactivityListener != null) {
			pactivityListener.activityFinished(null);
		}

	}

}
