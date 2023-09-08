/*
 * http://www.programcreek.com/java-api-examples/index.php?api=edu.umd.cs.piccolo.nodes.PPath
 */

package idea.tsoffline.canvas;

import static idea.tsoffline.canvas.DisplayLayout.TILED;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.PointerInfo;
import java.awt.Stroke;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.Collection;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import javax.swing.text.MutableAttributeSet;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.CannotUndoException;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.activities.PActivity;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.event.PInputEventListener;
import org.piccolo2d.extras.event.PNotification;
import org.piccolo2d.extras.event.PNotificationCenter;
import org.piccolo2d.extras.pswing.PSwing;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;
import org.sittingbull.gt.util.NiceStepSizeGenerator;
import org.sittingbull.gt.util.XWilkinson;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.jgoodies.forms.layout.FormLayout;

import idea.display.BandLayout;
import idea.model.DisplayConfig;
import idea.schema.rp.RpBandData;
import idea.schema.rp.RpDisplay;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import idea.schema.rp.RpWaveformSetup;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.ts.TsBand;
import idea.ts.TsCode;
import idea.ts.TsFilter;
import idea.ts.TsoAnnotationEntryType;
import idea.tsoffline.AppConstants;
import idea.tsoffline.AppFrame;
import idea.tsoffline.AppModel;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.LayerUtil;
import idea.tsoffline.TimelineModel;
import idea.tsoffline.canvas.edit.DeleteNodesEdit;
import idea.tsoffline.canvas.edit.TransformEdit;
import idea.tsoffline.model.D;
import idea.tsoffline.model.FormulaSignal;
import idea.tsoffline.tspico.AnnotationEditorTool;
import idea.tsoffline.tspico.CursorLocatorTool;
import idea.tsoffline.tspico.LegendTool;
import idea.tsoffline.tspico.RulerComponent;
import idea.tsoffline.tspico.ScrollTool;
import idea.tsoffline.tspico.SelectorTool;
import idea.tsoffline.tspico.XScrollbarEventTool;

/**
 * @author William L Baker
 * 
 *         Description of top level nodes:
 * 
 *         signalCamera: contains data that can be copied and scaled eventLayer:
 *         contains annotations that are invariant to the y scale
 * 
 *         TODO: (1) Tile and PClip (2) Remember selection
 *         preferences....timeline, scale...nah...part of the session, if saved
 *         (2a) ...well, yes, but in preferences! (3) Classic layout...and bands
 *         (4) Edit scale ranges
 * 
 */

@SuppressWarnings("serial")
@Slf4j
public class TsPSwingCanvas extends TsBaseCanvas {
	public static final String RULER_PROPERTY = "ruler";
	public static final String ACTIVE_LAYER_PROPERTY = "activeLayer";

	@Getter

	private static final double PREF_MAG = 1.4; // scroll zooms in 40%
												// increments

	public static final float LEFT_MARGIN = 60;

	private static final float BOTTOMM_MARGIN = 4;
	public static final float TOP_ANNOTATION_MARGIN = 30;
	public static float TOP_MARGIN = 10 + TOP_ANNOTATION_MARGIN;

	private static final float RIGHT_MARGIN = 20;

	private static final float SCALE_CAM_WIDTH = 20;
	private static final float LEGEND_CAM_WIDTH = 100;
	private static final float MODE_CAM_WIDTH = 140;

	private final static boolean BETA_FEATURES = false;

	private final static float TIMELINE_AREA_HEIGHT = 22;
	private final static float TIMELINE_TEXT_HEIGHT = 20;
	private final static float TIMELINE_CAM_HEIGHT = 20;
	private final static float SUBTITLE_HEIGHT = 16;
	private final static float PRIMARY_GRAPH_XLABEL_HEIGHT = 10;

	@Getter
	private boolean filter; // only the active layer is calibrated
	@Getter
	private boolean calibration; // only the active layer is calibrated
	@Getter
	private boolean intersection;
	@Getter
	private boolean anAnalysis;
	@Getter
	private boolean b2bAnalysis;
	@Getter
	private boolean showUnused;
	@Getter
	private boolean graphParams;

	@Getter
	@Setter
	private String subTitle = null;

	@Getter
	private LabelType graphXLabelFormat;

	private PCamera timelineCamera;
	private PCamera scaleCamera;

	protected PLayer rulerLayer;

	/**
	 * The signal camera has many layers. This is the active layer for editing and
	 * scaling purposes.
	 */

	@Getter
	private LegendTool legendHandler;
	private SelectorTool selectionHandler;

	// optimal tick-step calculation method
	XWilkinson wilkinson = new XWilkinson(new NiceStepSizeGenerator());

	XScrollbarEventTool dragableTimeTool = new XScrollbarEventTool(XScrollbarEventTool.HORIZONTAL);
	XScrollbarEventTool dragableScaleTool = new XScrollbarEventTool(XScrollbarEventTool.VERTICAL);

	@Getter
	RulerComponent x_ruler = new RulerComponent();
	@Getter
	RulerComponent y_ruler = new RulerComponent();

	private Timer resize_timer;

	@Getter
	private String displayName;
	private DisplayConfig displayConfig;

	Stroke thick = new BasicStroke(0, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
	// Stroke thick = new PFixedWidthStroke( 2, BasicStroke.CAP_ROUND,
	// BasicStroke.JOIN_ROUND);
	Stroke thin = new BasicStroke(0, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
	Stroke thicker = new BasicStroke(3, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);

	@Setter
	private boolean subtitleVisible = false;

	@Getter
	private boolean graphScaleVisible = false;
	@Getter
	private boolean graphTimelineVisible = true;
	@Getter
	private boolean legendVisible = true;

	HPSplitableLayer tm_sig; // this is a dummy signal which is reported for data
								// purposes..it is the timeline

	private PCamera activeBand;
	private int defaultEditMode;
	private double prev_dataWidth; // dataWidth is recomputed each _redraw of
	@Getter
	private LabelType timelineLabelFormat = LabelType.LABEL_CLOCKTIME;
	private PLayer prevSegLayer;
	// the axis layer

	public TsPSwingCanvas() {
		this(true, true);
	}

	public TsPSwingCanvas(boolean withLineCursor, boolean withAnnotationEditor) {

		rulerLayer = new PLayer();
		rulerLayer.setPickable(false);
		rulerLayer.setChildrenPickable(true);
		rulerLayer.setName("ruler_layer");

		// undo.setLimit( 100 ); // this is the default value
		initComponents();

		RpMetric tm_metric = new RpMetric();
		tm_metric.setLocation("TM");
		tm_sig = new HPSplitableLayer(tm_metric);

		PCamera firstSignalCamera = addBand(0, 16);
		firstSignalCamera.setName("FIRST_SIGCAM");

		{
			timelineCamera = new PCamera();
			timelineCamera.setName("overview_camera");
			{
				PLayer indicatorLayer = new PLayer();
				indicatorLayer.setName("timelineIndicatorLayer");
				timelineCamera.addLayer(indicatorLayer);

				timelineCamera.addInputEventListener(dragableTimeTool);
				timelineCamera.addLayer(phaseLayer); // add beneath the indicator...how?
			}

			// enable dragging of time frame

			dragableTimeTool.addObserver(new Observer() {

				@Override
				public void update(Observable o, Object arg) {
					if (arg == null) { // end of drag
						redrawAxisLayer(0); // automatically re-enables
											// annotation layers
						fireUpdateFinished();

						PCamera cam0 = bandCameras.get(0);
						undoManager.addEdit(new TransformEdit(TsPSwingCanvas.this, cam0, //
								dragableTimeTool.getInitialTransform(), //
								dragableTimeTool.getFinalTransform()));

					} else {
						annotationEditorHandler.getLayer().setVisible(false); // this
																				// will
						// show/hides all
						// the annotations
						for (PCamera cam : bandCameras) {
							AffineTransform ref = (AffineTransform) arg;
							PAffineTransform tr = cam.getViewTransform();
							tr.setOffset(ref.getTranslateX(), tr.getTranslateY());
							cam.setViewTransform(tr);
						}
					}
				}
			});
		}

		{
			scaleCamera = new PCamera();
			scaleCamera.setName("scale_camera");
			PLayer layer = new PLayer();
			layer.setName("scale_layer");
			scaleCamera.addLayer(layer);

			// enable dragging of time frame
			layer.addInputEventListener(dragableScaleTool);
			scaleCamera.addInputEventListener(dragableScaleTool);

			// scaleCamera.setPickable( false );
			layer.setPickable(false);

			dragableScaleTool.addObserver(new Observer() {

				@Override
				public void update(Observable o, Object arg) {
					if (arg == null) { // end of drag
						redrawAxisLayer(0); // automatically re-enables
											// annotation layers

						if (activeLayer == null) {
							// ignore!
						} else {
							undoManager.addEdit(new TransformEdit(TsPSwingCanvas.this, activeLayer, //
									dragableScaleTool.getInitialTransform(), //
									dragableScaleTool.getFinalTransform())); //
						}
					} else {
						if (activeLayer == null) {
							log.error("unexpected scale - drag: no active layer");
						} else {
							// ? showAnnotationLayers(false); // say what? Is
							// this ever called?

							getActiveSegment().setTransform((AffineTransform) arg);
							activeLayer.repaint(); // since this camera does not
													// have focus, needs a hint
						}
					}
				}
			});

		}

		getLayer().setName("ts_pswing");

		getLayer().removeAllChildren();

		getLayer().setName("BACKGROUND");

		getLayer().addChild(axisLayer);

		// enable dragging of feature points
		if (withAnnotationEditor) {
			annotationEditorHandler = new AnnotationEditorTool(this);

			addInputEventListener(annotationEditorHandler);

			getLayer().addChild(annotationEditorHandler.getLayer());
		}

		/*
		 * handle the input events
		 */
		if (withLineCursor) {
			lineTool = new CursorLocatorTool(this);
			firstSignalCamera.addInputEventListener(lineTool);
			addKeyListener(lineTool);
		}

		if (BETA_FEATURES) {
			this.setLayout(null); // no flow layout!
			// add entry fields for resetting the scale

			JTextField scaleTop = new JTextField("999.9");
			scaleTop.setMinimumSize(new Dimension(50, 20));
			scaleTop.setPreferredSize(new Dimension(50, 20));
			// scaleTop.setLocation(40, 100);

			PSwing swing = new PSwing(scaleTop);
			swing.translate(20, 100);

			getLayer().addChild(swing);
		}

		// rect selection

		selectionHandler = new SelectorTool(this, axisLayer);
		axisLayer.addInputEventListener(selectionHandler);

		// PNotificationCenter.defaultCenter().addListener(this,
		// "selectionChanged",
		// SelectorTool.DRAG_COMPLETE_NOTIFICATION, selectionHandler);

		// middle-button roller scrolls
		PInputEventListener scrollHandler = new ScrollTool();
		addInputEventListener(scrollHandler);
		PNotificationCenter.defaultCenter().addListener(this, "scrollChanged", ScrollTool.SCROLL_NOTIFICATION,
				scrollHandler);

		setInteracting(true);

		// axisHandler calls the canvas directly...of course it could notify

		legendHandler = new LegendTool();
		PNotificationCenter.defaultCenter().addListener(this, "legendChanged", LegendTool.LEGEND_SELECTED_NOTIFICATION,
				legendHandler);
		PNotificationCenter.defaultCenter().addListener(this, "legendCalibSelect",
				LegendTool.LEGEND_SEG_SELECTED_NOTIFICATION, legendHandler);
		PNotificationCenter.defaultCenter().addListener(this, "legendHide", LegendTool.LEGEND_HIDE_NOTIFICATION,
				legendHandler);
		PNotificationCenter.defaultCenter().addListener(this, "legendDelete", LegendTool.LEGEND_DELETE_NOTIFICATION,
				legendHandler);
		PNotificationCenter.defaultCenter().addListener(this, "legendFilter", LegendTool.LEGEND_FILTER_NOTIFICATION,
				legendHandler);
		PNotificationCenter.defaultCenter().addListener(this, "legendRuler", LegendTool.LEGEND_RULER_NOTIFICATION,
				legendHandler);

		// Color theme_axis_background = Color.LIGHT_GRAY;
		// this.setBackground(theme_axis_background);

		// set the initial signal view transform...translate 60
		// initSlider();
		thisComponentResized(null);

		double h = 200;
		AffineTransform m = new AffineTransform(1, 0, 0, -1, LEFT_MARGIN, h);
		firstSignalCamera.setViewTransform(m); // we want signalCamera to always
												// have
												// y in pixels, lowest at the
												// bottom

		setGraphLabelFormat(LabelType.LABEL_REL_MMSS);
		setTimelineLabelFormat(LabelType.LABEL_CLOCKTIME);
	}

	public void setLocatorColor(Color color) {
		if (lineTool != null) {
			lineTool.setLocatorColor(color);
		}
	}

	@Override
	protected void _redrawAxisLayer() {
		super._redrawAxisLayer();
		axisLayer.addChild(rulerLayer);

		PCamera bottomSignalCamera = null;
		for (PCamera cam : bandCameras) {
			bottomSignalCamera = cam;

			PAffineTransform view = cam.getViewTransform();
			double determinate = view.getDeterminant();
			if (determinate == 0) {
				log.error("[2] SIGCAM CANNOT INVERT=" + view + " CAM=" + cam.getName());
				cam.setViewTransform(new PAffineTransform()); // UNITY
			}
		}

		if (bottomSignalCamera == null) {
			return; // no signals
		}

		PBounds bounds = bottomSignalCamera.getBounds();

		if (bounds.isEmpty()) {
			log.error("INTERNAL ERROR: empty bounds for camera");
			return;
		}
		PAffineTransform sigcam_view_m = bottomSignalCamera.getViewTransform();

		double visibleDataWidth = bounds.getWidth() / sigcam_view_m.getScaleX();
		try {

			x_ruler.drawXRuler(getStartTime(), ticFont, wilkinson, axisLayer, bottomSignalCamera, false, true,
					graphXLabelFormat);
			x_ruler.drawXRuler(getStartTime(), ticFont, wilkinson, axisLayer, timelineCamera, true, true,
					timelineLabelFormat);

			rulerLayer.removeAllChildren();
			for (PCamera cam : bandCameras) {
				y_ruler.drawYRuler(ticFont, wilkinson, rulerLayer, cam, activeLayer);
				y_ruler.drawReferenceLines(rulerLayer, cam);
			}

			Point2D origin_window = new Point2D.Double(bounds.getX(), bounds.getHeight());
			Point2D origin_data = sigcam_view_m.inverseTransform(origin_window, null); // ???

			timelineCamera.setVisible(graphTimelineVisible);
			if (graphTimelineVisible) {
				drawBoundingBox(axisLayer, timelineCamera.getBoundsReference());

				// only used for the X scale, so it doesnt matter which camera
				PCamera zero = bandCameras.get(0);
				drawOverviewBlock(timelineCamera, zero.getViewTransform(), origin_data.getX(), visibleDataWidth);
			}

			// legendCamera.setVisible(showLegend);
			if (legendVisible) {
				// drawBoundingBox(legendCamera.getBoundsReference());
				double left = 0;
				for (PCamera cam : bandCameras) {
					if (cam == null)
						continue;

					PBounds ccbounds = cam.getBoundsReference();

					// this is the "legend/text left", not the band camera left
					left = ccbounds.getX() + ccbounds.getWidth() + 15;
					if (graphScaleVisible && (activeLayer != null) && calibration) {
						left += scaleCamera.getWidth() + 4;
					}
				}
				if (isCalibration()) {
					((LegendTool) legendHandler).drawCalibrationLegend(axisLayer, bandCameras, left);
				} else if (isIntersection()) {
					((LegendTool) legendHandler).drawIntersectionLegend(axisLayer, bandCameras, left, analysisPoint);
				} else if (isB2bAnalysis()) {
					((LegendTool) legendHandler).drawAnalysisLegend(axisLayer, getAnnotationModel(), bandCameras, left,
							analysisPoint);
				} else if (isShowUnused()) {
					((LegendTool) legendHandler).drawUnusedLegend(axisLayer, getAnnotationModel(), bandCameras, left,
							layers);
				} else if (isAnAnalysis()) {
					((LegendTool) legendHandler).drawStandardLegend(axisLayer, bandCameras, left);
				} else if (isGraphParams()) {
					((LegendTool) legendHandler).drawGraphParamsLegend(axisLayer, bandCameras, left);
				} else if (isFilter()) {
					((LegendTool) legendHandler).drawFilterLegend(axisLayer, bandCameras, left, activeLayer);
				} else {
					((LegendTool) legendHandler).drawStandardLegend(axisLayer, bandCameras, left);
				}
			}

			scaleCamera.setVisible(graphScaleVisible && (activeLayer != null) && calibration);
			if (graphScaleVisible && (activeLayer != null) && calibration) {
				drawBoundingBox(axisLayer, scaleCamera.getBoundsReference());
				drawScaleBlock(scaleCamera);
			}

			if (annotationEditorHandler != null) {
				// WLB 11JAN15: I clear sticky here so that the user doesnt end
				// up changing an off-screen node accidentally, ie, by hitting
				// SPACE

				// 08FEB17 WLB: This also draws the annotation vertical line
				// indicators

				annotationEditorHandler.draw(bounds, visibleDataWidth, origin_data, sigcam_view_m);
			}

		} catch (NoninvertibleTransformException e) {
			log.error("_redrawAxis()", e);
		}

		int pos = axisLayer.getChildrenCount();
		_addCamerasToAxisLayer();
		selectionHandler.setZIndex(pos);

		if (graphTimelineVisible)
			axisLayer.addChild(timelineCamera);
		if (graphScaleVisible && (activeLayer != null))
			axisLayer.addChild(scaleCamera);

		if (transformActivity == null || transformActivity.isStepping() == false) {
			// only fire when animation is complete
			firePropertyChange(RULER_PROPERTY, prev_dataWidth, visibleDataWidth);
			prev_dataWidth = visibleDataWidth;

			// experimental baseline support
			// for( PCamera cam : bandCameras ) {
			// BaselineNode bl = new BaselineNode(cam);
			// axisLayer.addChild(bl);
			// }
		}

	}

	private void drawScaleBlock(PCamera scale_cam) {
		if ((activeLayer == null) || (activeSegment == null)) {
			log.warn("No active signal segment.");

			PLayer layer = scale_cam.getLayer(0);
			layer.removeAllChildren();
			return;
		}

		PCamera band_cam = activeBand;
		if (band_cam == null && activeLayer.getCameraCount() > 0) {
			band_cam = activeLayer.getCamera(0);
		}

		if (band_cam == null) {
			log.error("NO SIGNAL CAMERA FOR ACTIVE LAYER?");
			return;
		}

		PBounds r = band_cam.getBoundsReference();
		PAffineTransform view_tr = band_cam.getViewTransform();
		PAffineTransform active_tr = activeSegment.getTransform();

		double cam_x = scale_cam.getX();
		double cam_w = scale_cam.getWidth();

		Point2D origin = new Point2D.Double(0, 0);
		Point2D box = new Point2D.Double(0, cam_w);
		Point2D left = new Point2D.Double(r.width, 0);
		view_tr.inverseTransform(origin, origin);
		view_tr.inverseTransform(left, left);
		view_tr.inverseTransform(box, box);
		double data_startX = origin.getX();
		double data_endX = left.getX();

		double[] sig_minmax = D.getMinMaxInRange(activeSegment, data_startX, data_endX);
		double data_min = sig_minmax[0];
		double data_max = sig_minmax[1];

		PLayer layer = scale_cam.getLayer(0);

		AffineTransform sc = new AffineTransform(1, 0, 0, view_tr.getScaleY(), cam_x, view_tr.getTranslateY());
		scale_cam.setViewTransform(sc);
		AffineTransform lt = new AffineTransform(1, 0, 0, active_tr.getScaleY(), 0, active_tr.getTranslateY());
		layer.setTransform(lt);

		double dy = (origin.getY() - box.getY()) / lt.getScaleY();

		dragableScaleTool.buildSliders(activeSegment.getTransform(), layer, cam_w, data_min, data_max, dy,
				theme_slider_color);
	}

	private void drawOverviewBlock(PCamera cam, PAffineTransform trans, double x, double width) {
		double h = cam.getHeight();
		PLayer layer = cam.getLayer(0);

		layer.removeAllChildren();
		PPath node = PPath.createRectangle(x, 0, width, h - 4);
		System.out.println("drawing overview block: " + layer.getName() + " x=" + x + " w=" + width );

		node.setPaint(theme_slider_color);
		node.setStrokePaint(theme_border_color);
		node.setStroke(AppConstants.getDefaultSignalStroke());
		node.addAttribute("action", XScrollbarEventTool.SLIDE);
		layer.addChild(node);
		dragableTimeTool.setBar(node);
		dragableTimeTool.setTransformable(trans);
		dragableTimeTool.setScrollbarLayer(layer);
	}

	public void dispose() {
		for (PCamera cam : bandCameras) {
			cam.removeAllChildren();
		}
		timelineCamera.removeAllChildren();
		axisLayer.removeAllChildren();
		getLayer().removeAllChildren();
	}

	public void flip() {

		PCamera cam = getCameraAtMousePos();
		if (cam == null) {
			// I don't know what camera to flip!
			cam = bandCameras.get(0);
		}
		// BUG: ?Whatever getViewBounds() is returning, it's not what I'm
		// expecting!
		// PBounds r = signalCamera.getViewBounds();
		PBounds r = cam.getBounds();
		PAffineTransform vt = cam.getViewTransform();
		// PAffineTransform tr0 = signalCamera.getTransform();
		// PAffineTransform tr = activeSignalLayer.getTransformReference(true);
		// ca.concatenate(tr);

		Point2D gpt0 = new Point2D.Double(60, 0);
		Point2D gpt1 = new Point2D.Double(r.getWidth() + 60, r.getHeight());
		vt.inverseTransform(gpt0, gpt0);
		vt.inverseTransform(gpt1, gpt1);

		PBounds b = new PBounds(gpt0.getX(), gpt1.getY(), gpt1.getX(), gpt0.getY());

		// gpt0.setLocation( , gpt0.getY() );

		// double y1 = gpt0.getY();
		// gpt0.setLocation(gpt0.getX(), gpt1.getY());
		// gpt1.setLocation(gpt1.getX(), y1);

		zoomLayerYScaleToRectangle(activeLayer, cam.getBounds(), b);
	}

	public HPSplitableLayer[] getVisibleSigs() {

		List<HPSplitableLayer> sigs = new LinkedList<HPSplitableLayer>();

		sigs.add(tm_sig);
		for (PCamera cam : bandCameras) {
			for (int i = 0; i < cam.getLayerCount(); i++) {
				PLayer layer = cam.getLayer(i);

				// if it is not visible, it is not selectable
				if (layer.getVisible() == false) {
					continue;
				}
				HPSplitableLayer sig = (HPSplitableLayer) layer.getAttribute("sig");

				// if it does not have a signal, it is not selectable
				if (sig == null) {
					continue;
				}
				sigs.add(sig);
			}
		}

		HPSplitableLayer[] arr = new HPSplitableLayer[sigs.size()];
		sigs.toArray(arr);
		return arr;
	}

	public long getViewWidthMs() {
		PCamera cam = bandCameras.get(0);
		PBounds r = cam.getViewBounds();

		return (long) (1000 * r.getWidth());
	}

	public long getViewEndTimeMs() {
		PCamera cam = bandCameras.get(0);
		PBounds r = cam.getViewBounds();

		return (long) (1000 * (r.getX() + r.getWidth()));
	}

	public long getViewStartTimeMs() {
		PCamera cam = bandCameras.get(0);
		PBounds r = cam.getViewBounds();

		return (long) (1000 * r.getX());
	}

	@Deprecated
	public PCamera getSignalCamera() {
		return bandCameras.get(0);
	}

	public void resetLayersToUnityTransform(int cam_idx) {
		resetLayersToUnityTransform(bandCameras.get(cam_idx));
	}

	public void resetLayersToUnityTransform(PCamera cam) {
		if (cam == null) {
			// no camera indicated
			return;
		}
		AffineTransform tr = new AffineTransform(); // creates a unit transform

		for (int i = 0; i < cam.getLayerCount(); i++) {
			PLayer layer = cam.getLayer(i);
			if (layer.getVisible()) {
				layer.setTransform(tr);
			}
		}

		redrawAxisLayer(0);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents

		// ======== this ========
		addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent e) {
				thisComponentResizedDelayed(e);
			}
		});
		setLayout(new FormLayout("default, $lcgap, default", "2*(default, $lgap), default"));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	protected void processKeyPressed(PCamera cam0, KeyEvent e) {
		super.processKeyPressed(cam0, e);
		if (e.isConsumed()) {
			return;
		}

		int keyCode = e.getKeyCode();
		if (keyCode == KeyEvent.VK_0) {
			reset();
		} else if (keyCode == KeyEvent.VK_1) {
			resetLayersToUnityTransform(cam0);
		} else if (keyCode == KeyEvent.VK_2) {
			annotationEditorHandler.joinNodesAtDataPoint(null, null, 1, getMouseDataPosition(), null);
			redrawAxisLayer(0);

		} else if (keyCode == KeyEvent.VK_A) {

			if (e.isControlDown()) {
				// ignore...menu shortcut
			} else {
				applyDefaults();
				e.consume();
			}
			// } else if (keyCode == KeyEvent.VK_P) {
			//
			// Point2D pos = getMousePosition();
			// if (pos != null) {
			// next(pos, 0.3, 6, -1);
			// }
			// e.consume();
		} else if (keyCode == KeyEvent.VK_F9) {

			// invoke a debug function
			this.repaint();

			for (HPSplitableLayer sig : this.getSigs()) {
				System.out.println("SIG: " + sig.getAlias());
				System.out.println("   name: " + sig.getName());
				System.out.println("   band: " + sig.getBandId());
				System.out.println("  paint: " + sig.getPaint());
				System.out.println("dfpaint: " + sig.getDefaultColor());
				System.out.println("visible: " + sig.getVisible());
				System.out.println(" transf: " + sig.getTransform());
				System.out.println("      m: " + sig.getM());

				if (sig.getDefaultColor() == null) {
					sig.setDefaultColor(Color.yellow);
				}
				for (Object sub : sig.getChildrenReference()) {
					HPPathLayer player = (HPPathLayer) sub;
					System.out.println("     SUB: " + player.getName());
					System.out.println("            sig: " + player.getAttribute("sig"));
					System.out.println("          paint: " + player.getPaint());
					System.out.println("        visible: " + player.getVisible());
					System.out.println("         transf: " + player.getTransform());
					System.out.println("         childs: " + player.getChildrenCount());
					if (player.getPaint() == null) {
						player.setPaint(Color.pink);
					}
					player.setVisible(true);
				}
			}

		} else if (keyCode == KeyEvent.VK_F11) {
			if (activeLayer == null) {
				// ignore
			} else {
				AffineTransform unit = new AffineTransform();
				activeLayer.setTransform(unit);
				redrawAxisLayer(0);
			}
			e.consume();
		} else if (keyCode == KeyEvent.VK_PLUS || keyCode == KeyEvent.VK_ADD || keyCode == KeyEvent.VK_EQUALS) {

			if (cam0 == null) {
				// ignore for movement purposes...pressed a key over app, but
				// not over canvas
			} else if (e.isControlDown()) {
				zoomToMousePosition(cam0, 0, 1);
			} else if (e.isShiftDown()) {
				moveUpDown(cam0, 1);
			} else {
				zoomToMousePosition(cam0, 1, 0);
			}
			e.consume();
		} else if (keyCode == KeyEvent.VK_MINUS || keyCode == KeyEvent.VK_SUBTRACT) {

			if (cam0 == null) {
				// ignore for movement purposes...pressed a key over app, but
				// not over canvas
			} else if (e.isControlDown()) {
				zoomToMousePosition(cam0, 0, -1);
			} else if (e.isShiftDown()) {
				moveUpDown(cam0, -1);
			} else {
				zoomToMousePosition(cam0, -1, 0);
			}
			e.consume();
		} else if (keyCode == KeyEvent.VK_Y) {
			if (e.isControlDown()) {
				try {
					undoManager.redo();
				} catch (CannotRedoException ee) {
					Toolkit.getDefaultToolkit().beep();
				}
			}
		} else if (keyCode == KeyEvent.VK_Z) {
			if (e.isControlDown()) {
				try {
					undoManager.undo();
				} catch (CannotUndoException ee) {
					Toolkit.getDefaultToolkit().beep();
				}
			}
		} else if (keyCode == KeyEvent.VK_SHIFT) {
			// explicit pass through, no consumption
		} else if (keyCode == KeyEvent.VK_CONTROL) {
			// explicit pass through, no consumption

			// 20FEB17 WLB: D might be a code key for an annotation...this
			// method possibly is similar to the DELETE key
			// } else if (keyCode == KeyEvent.VK_D) {
			// Point pos = TsPSwingCanvas.this.getMousePosition();
			// removeNodesAtMousePoint(pos); // removes points around mouse
			// e.consume();
		} else if (keyCode == KeyEvent.VK_DELETE) {
			deleteSelectedAnnotation();
			e.consume();
		} else {
			if (e.isControlDown()) {
				// pass through menu shortcuts...like Ctrl-S for Save
			} else {
				String ch = KeyEvent.getKeyText(keyCode);
				String code = findCode(ch, 0);
				if (code != null) {
					double dataX = getMouseDataPosition();

					// 8-JAN-15 WLB: set data_y here
					PNode node = annotationEditorHandler.joinNodesAtDataPoint(null, null, defaultEditMode, dataX, code);
					if (node == null) {
						GuiUtil.showMessage("Could not add annotation: no annotation layer selected.");
					} else {
						// 22FEB17 WLB removed:
						// annotationEditorHandler.setDataY(node);
					}
					redrawAxisLayer(0);
					e.consume();
				}
			}
		}
	}

	public void deleteSelectedAnnotation() {
		// removes exactly one point...at most
		AppModel.setDirty(true);
		PLayer layer = annotationEditorHandler.getStickyLayer();
		List<PNode> nodes = annotationEditorHandler.deleteAnnotation();
		if (nodes != null) {
			redrawAxisLayer(0); // actually only need the annotation layer
			// PLayer layer = annotationEditorHandler.getLayer();
			undoManager.addEdit(new DeleteNodesEdit(this, layer, nodes));
		}
	}

	public void reset() {
		thisComponentResized(null);

		// provides an import function of setting the timeline scale camera
		PCamera cam = bandCameras.get(0);

		scaleToFit();

		zoomCameraToXScale(cam, -2, 28.0); // starts an animation

		transformActivity.terminate(PActivity.TERMINATE_AND_FINISH);

		// shouldn't this happen automatically with TERMINATE_AND_FINISH?
		syncTransforms(cam.getViewTransform().getScaleX(), cam.getViewTransform().getTranslateX());

		// you have to finish the animation before you can center
		centerView(null);
	}

	private String findCode(String ch, int offset) {
		List<TsCode> codes = AppFrame.getInstance().getCodeModel();
		String code = null;
		// find a code with the matching first character
		if (codes != null) {
			Iterator<TsCode> ii = codes.iterator();
			while (ii.hasNext()) {
				TsCode tsc = ii.next();
				String ref = tsc.getCode().toUpperCase();
				if (ref.startsWith(ch)) {
					while (offset > 0) {
						if (ii.hasNext() == false) {
							ii = codes.iterator(); // start over
						}
						tsc = ii.next();

						offset--;
					}
					code = tsc.getCode();
					break;
				}
			}
		}

		return code;
	}

	public void updateSelection(double selectionTm) {
		if (isB2bAnalysis()) {
			analysisPoint = selectionTm;
			_redrawAxisLayer(); // redraw the annotations
		}
	}

	@Override
	public void redrawAxisLayer(int dt) {
		super.redrawAxisLayer(dt);
		setIntervalDates();
	}

	private void setIntervalDates() {
		PCamera cam0 = bandCameras.get(0);
		PBounds bounds = cam0.getBounds();
		PAffineTransform view_m = cam0.getViewTransform(); // waveLayer.getTransform();
		Point2D origin_mouse = new Point2D.Double(bounds.getX(), bounds.getHeight());
		Point2D origin_data;
		try {
			origin_data = view_m.inverseTransform(origin_mouse, null); // ???
		} catch (Exception e) {
			// NoninvertibleTransformException
			// ignore and return
			log.warn("could not invert transform in setIntervalDates()");
			return;
		}
		float tic_value = (float) origin_data.getX();
		long millis = (long) (tic_value * 1000);
		millis += getStartTime();

		TimelineModel tl_model = AppModel.getTimelineModel();
		tl_model.setStartIntervalTime(new Date(millis));

		double dataWidth = bounds.getWidth() / view_m.getScaleX();
		millis += (dataWidth * 1000);

		tl_model.setEndIntervalTime(new Date(millis));
		tl_model.publish();
	}

	/*
	 * extract the data from startX to endX of the specified layer and center on
	 * screen.
	 * 
	 * if dataLayer is null, all layers are examined to find the min/max for
	 * centering.
	 * 
	 * Y is always scaled...x is optional
	 */
	public void scaleToFit() {
		for (PCamera cam : getBandCameras()) {
			scaleToFit(cam, null);
		}
	}

	public void scaleToFit(PCamera cam, PBounds r) {

		boolean update_overview = false;

		// special case: fit full data width
		// and this is the opportunity to set the x-scale of the overview window
		if (r == null) {
			update_overview = true;
		}

		PBounds cumulDataRect = new PBounds();

		// find the cumulative min/max for all the layers
		for (int i = 0; i < cam.getLayerCount(); i++) {
			HPSplitableLayer parent = (HPSplitableLayer) cam.getLayer(i);
			for (Object node : parent.getChildrenReference()) {
				PLayer layer = (PLayer) node; 
				if (layer.getVisible() == false) {
					continue;
				}
				if (layer.getChildrenCount() == 0) {
					continue;
				}

				Collection<PNode> nodes = layer.getChildrenReference();
				PBounds data_rect = getDataRange(nodes, 0, Double.MAX_VALUE);

				// Rectangle2D layer_rect = data_rect;
				PAffineTransform layer_tr = layer.getTransform();
				Rectangle2D layer_rect = layer_tr.transform(data_rect, null);

				cumulDataRect.add(layer_rect);
			}

		}

		scaleCameraXToFit(cam, cumulDataRect, update_overview);
	}

	private void scaleCameraXToFit(PCamera cam, Rectangle2D combined, boolean update_overview) {
		if (combined == null) {
			return; // no visible layers with data
		}

		double startX = combined.getX();
		double yMin = combined.getY();
		double endX = startX + combined.getWidth();
		double yMax = yMin + combined.getHeight();

		// add a little buffer above and below
		double dy = 0.15 * (yMax - yMin);
		if (dy < 0.1) { // set some minimum y scale!
			dy = 0.1;
		}

		yMax += dy;
		yMin -= dy;

		if (yMin == yMax) {
			yMin--;
			yMax++;
		}

		if (yMax <= yMin) {
			log.error("FIXME: NOT SURE ABOUT THIS");
			return; // at most one point found
		}

		AffineTransform desired = zoomCameraToXScale(cam, startX, endX);

		if (update_overview) {
			PBounds ov_bounds = timelineCamera.getBoundsReference();
			AffineTransform m = new AffineTransform( //
					desired.getScaleX(), 0, 0, 1, //
					desired.getTranslateX(), ov_bounds.getY() + 2);

			timelineCamera.setViewTransform(m);
		}

	}

	public long getMouseMillisecondPosition() {
		double data_pos = getMouseDataPosition();
		long ts = (long) (data_pos * 1000);
		return ts + getStartTime();
	}

	public double getMouseDataPosition() {

		Point pt = this.getMousePosition();
		if (pt == null) {
			log.debug("original pt={}", pt);

			PointerInfo pointerInfo = MouseInfo.getPointerInfo();
			if (pointerInfo != null) {
				pt = pointerInfo.getLocation();
				SwingUtilities.convertPointFromScreen(pt, this);
				log.debug("revised pt={}", pt);
			}
		}

		PCamera cam = bandCameras.get(0);
		PAffineTransform tr = cam.getViewTransform();

		Point2D data_pt = tr.inverseTransform(pt, null);

		return data_pt.getX();

	}

	private void zoomToMousePosition(PCamera cam, int xdir, int ydir) {

		Point2D mouse_pos = getMousePosition();
		if (mouse_pos != null) {

			PAffineTransform trans = cam.getViewTransform();
			Point data_pos = new Point();
			trans.inverseTransform(mouse_pos, data_pos);

			zoomToDataPosition(cam, data_pos.getX(), data_pos.getY(), xdir, ydir);
		}
	}

	public void zoomToDataPosition(PCamera cam, double x, double y, int xdir, int ydir) {
		if (cam == null) {
			cam = bandCameras.get(0);
		}
		PBounds r = cam.getViewBounds();

		double view_width = r.getWidth();
		double view_height = r.getHeight();
		// double proportion = (x - waveCamera.Bounds.X) / width;

		double mag = PREF_MAG;

		if (xdir != 0) {
			Point2D lowerLeft = r.getOrigin();
			double deltaRight = 0;
			double deltaLeft = 0;
			if (xdir > 1) { // absolute position
				lowerLeft.setLocation(x - view_width / 2, lowerLeft.getY());
				// width is unchanged
			} else if (xdir != 0) {
				double x_proportion = (x - r.getX()) / view_width;
				if (xdir > 0) {
					// zoom in amount
					deltaRight = x_proportion * (view_width / 3);
					deltaLeft = -(1.0 - x_proportion) * (view_width / 3);
				} else {
					// zoom out amount
					deltaRight = x_proportion * (view_width / mag);
					deltaLeft = -(1.0 - x_proportion) * (view_width / mag);
				}
			}
			double x0 = lowerLeft.getX() + xdir * deltaRight;
			double x1 = lowerLeft.getX() + xdir * deltaLeft + view_width;

			zoomCameraToXScale(cam, x0, x1);
		}

		if (ydir != 0) {
			double deltaTop = 0;
			double deltaBottom = 0;

			double y_proportion = (y - r.getY()) / view_height;
			deltaTop = (y_proportion * view_height) / 3;
			deltaBottom = -(1.0 - y_proportion) * view_height / 3;

			double top = r.getY() + view_height - ydir * deltaTop;
			double bottom = r.getY() - ydir * deltaBottom;
			PBounds rr = new PBounds(r.getX(), bottom, view_width, top - bottom);

			PAffineTransform tr = cam.getViewTransform();

			double sy = -cam.getHeight() / (rr.getHeight());
			double ty = cam.getY() + cam.getHeight() - sy * rr.getY();
			PAffineTransform ttr = new PAffineTransform(tr.getScaleX(), 0, 0, sy, tr.getTranslateX(), ty);

			cam.setViewTransform(ttr);

			_redrawAxisLayer();
		}
	}

	/*
	 * DO NOT DELETE...this method referenced by name in listener above
	 */
	public void scrollChanged(PNotification notfication) {
		ScrollTool tool = (ScrollTool) notfication.getObject();
		PInputEvent e = tool.getInputEvent();
		int dir = -e.getWheelRotation();

		PCamera cam0 = getCameraAtMousePos();

		if (e.isShiftDown()) {
			moveUpDown(cam0, dir);
		} else if (e.isControlDown()) {
			zoomToMousePosition(cam0, dir, 0);
		} else {
			moveLeftRight(-dir);
		}
	}

	/*
	 * DO NOT DELETE...this method referenced by name in listener above
	 */
	public void legendCalibSelect(PNotification notfication) {
		LegendTool tool = (LegendTool) notfication.getObject();

		HPSplitableLayer sig = tool.getSelectedSignal();
		PLayer seg = tool.getCalibrationSegment();
		activeBand = tool.getSelectedCamera();

		setActiveSignal(sig, seg);
		_redrawAxisLayer();
	}

	public void legendRuler(PNotification notfication) {
		// LegendTool tool = (LegendTool) notfication.getObject();

		rulerLayer.removeAllChildren();
		for (PCamera cam : bandCameras) {
			resizeCameraViewArea(cam);
			y_ruler.drawYRuler(ticFont, wilkinson, rulerLayer, cam, activeLayer);
		}
	}

	public void legendChanged(PNotification notfication) {
		LegendTool tool = (LegendTool) notfication.getObject();

		PText pt_label = tool.getSelectedPText();
		HPSplitableLayer sig = (HPSplitableLayer) pt_label.getAttribute("sig");
		PLayer seg = tool.getCalibrationSegment();

		activeBand = (PCamera) pt_label.getAttribute("cam");

		if (sig == this.getActiveLayer()) {
			setActiveSignal(null, null);
		} else {
			setActiveSignal(sig, seg);
		}

	}

	/*
	 * DO NOT DELETE...this method referenced by name in listener above
	 */
	public void legendFilter(PNotification notification) {
		TsFilter filter = (TsFilter) notification.getProperty("filter");
		HPSplitableLayer sig = (HPSplitableLayer) notification.getProperty("sig");

		sig.applyFilter(filter);
		updateFormulas();
	}

	public void updateFormulas() {
		for (HPSplitableLayer sig : getSigs()) {

			if (sig instanceof FormulaSignal) {
				FormulaSignal formula = (FormulaSignal) sig;
				AppModel.createFormulaSignal(this, formula.getName(), formula.getPaint(), formula);

				sig.repaint();
			}
		}

	}

	/*
	 * DO NOT DELETE...this method referenced by name in listener above
	 */
	public void legendDelete(PNotification notfication) {
		LegendTool tool = (LegendTool) notfication.getObject();

		PText pt_label = tool.getSelectedPText();
		HPSplitableLayer sig = (HPSplitableLayer) pt_label.getAttribute("sig");

		removeSignalLayer(sig);

		_redrawAxisLayer();
	}

	/*
	 * DO NOT DELETE...this method referenced by name in listener above
	 */
	public void legendHide(PNotification notfication) {
		LegendTool tool = (LegendTool) notfication.getObject();

		PText pt_label = tool.getSelectedPText();
		HPSplitableLayer sig = (HPSplitableLayer) pt_label.getAttribute("sig");

		PLayer hideableLayer = sig;
		hideableLayer.setVisible(false);
		if (hideableLayer == activeLayer) {
			setActiveSignal(null, null);
		}

		_redrawAxisLayer();
	}

	protected void thisComponentResizedDelayed(ComponentEvent e) {
		log.info("* TsPSwingCanvas thisComponentResizedDelayed: {}", getSize());
		if (resize_timer != null && resize_timer.isRunning()) {
			// STOPPING REDRAW THREAD
			resize_timer.stop();
		}

		resize_timer = new Timer(100, new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				log.info("* [thisComponentResized timer from delayed]");
				thisComponentResized(null);
				if (displayConfig != null) {
					setDisplay(null, displayConfig);
				}
			}
		});

		resize_timer.setRepeats(false);
		resize_timer.start();
	}

	/**
	 * Reposition cameras for the individual graphs and subsequently redraw the
	 * entire graph
	 */

	protected void thisComponentResized(ComponentEvent e) {
		log.info("thisComponentResized: {}, {} == {}", this.getWidth(), this.getHeight(), this.getSize());

		float w = this.getWidth();
		float h = this.getHeight();

		if (w < (LEFT_MARGIN + RIGHT_MARGIN + LEGEND_CAM_WIDTH + MODE_CAM_WIDTH)) {
			w = LEFT_MARGIN + RIGHT_MARGIN + LEGEND_CAM_WIDTH + MODE_CAM_WIDTH + 100;
		}

		if (h < (TOP_MARGIN + BOTTOMM_MARGIN)) {
			h = TOP_MARGIN + BOTTOMM_MARGIN + 100;
		}

		float plot_width = w - LEFT_MARGIN - RIGHT_MARGIN;
		float plot_h = h - TOP_MARGIN - BOTTOMM_MARGIN;

		if (subtitleVisible) {
			plot_h -= SUBTITLE_HEIGHT;
		}

		// if (graphXLabelFormat != LabelType.NONE) {
		// plot_h -= 20;
		// }

		// if (timelineLabelFormat != LabelType.LABEL_REL_SECS) {
		// plot_h -= 20;
		// }

		if (graphTimelineVisible) {
			plot_h -= TIMELINE_TEXT_HEIGHT;
			plot_h -= TIMELINE_AREA_HEIGHT;
			plot_h -= PRIMARY_GRAPH_XLABEL_HEIGHT;
		}
		if (graphScaleVisible && (activeLayer != null)) {
			plot_width -= SCALE_CAM_WIDTH;
		}

		if (legendVisible) {
			plot_width -= LEGEND_CAM_WIDTH;
		}
		if (calibration || filter) {
			plot_width -= 100;
		}
		if (intersection) {
			plot_width -= 50;
		}
		if (this.isB2bAnalysis() || this.isCalibration() || this.isShowUnused() || this.graphParams || this.filter) {
			plot_width -= MODE_CAM_WIDTH;
		}

		plot_h -= 10;

		if (annotationEditorHandler != null) {
			annotationEditorHandler.componentResized(e, plot_width, plot_h);
		}
		if (lineTool != null) {
			lineTool.componentResized(e, plot_width, plot_h);
		}

		resizeCameras(TOP_MARGIN, LEFT_MARGIN, plot_width, plot_h);

		{ // scope vars for debug
			Rectangle2D ov_rect = new Rectangle2D.Float(LEFT_MARGIN,
					TOP_MARGIN + plot_h + TIMELINE_AREA_HEIGHT + PRIMARY_GRAPH_XLABEL_HEIGHT, plot_width,
					TIMELINE_CAM_HEIGHT);
			timelineCamera.setBounds(ov_rect);

			PAffineTransform m = timelineCamera.getViewTransformReference();
			long dt = getStopTime() - getStartTime();
			double tx = m.getTranslateX();
			if (dt > 0) {
				double sx = timelineCamera.getWidth() * 1000.0 / dt;
				m.setToScale(sx, 1.0);
				tx = timelineCamera.getX();
			}
			m.setOffset(tx, ov_rect.getY() + 2);

			Rectangle2D sc_rect = new Rectangle2D.Float(LEFT_MARGIN + plot_width + 12, TOP_MARGIN, SCALE_CAM_WIDTH,
					plot_h - BAND_SPACING);
			scaleCamera.setBounds(sc_rect);
		}

		redrawAxisLayer(0);
		// dump(3, 0, getLayer());

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

		double[] tr = new double[6];
		ori.getMatrix(tr);
		tr[0] = desired.getScaleX();
		tr[4] = desired.getTranslateX();
		desired = new AffineTransform(tr);

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
			transformActivity.setDelegate(updateDelegate);
			undoManager.addEdit(new TransformEdit(this, cam, ori, desired));
		}

		return desired;
	}

	@Override
	public void paintComponent(Graphics g) {

		PCamera cam0 = bandCameras.get(0);
		PAffineTransform trans = cam0.getViewTransformReference();
		if (trans.getDeterminant() == 0) {
			log.error("CANNOT INVERT TRANSFORM...maybe too soon?");
			return;
		}

		double scaleX = trans.getScaleX();

		// int resolution = 0;
		// if (scaleX < 1)
		// resolution = 5;
		// if (scaleX < 0.2)
		// resolution = 10;
		// if (scaleX < 0.02)
		// resolution = 50;
		//
		// HPPath.setPaintResolution(resolution);
		//
		LinkedNode.startDrawMode(LinkedNode.FIDUCIAL);

		super.paintComponent(g);
	}

	public void clear() {
		for (PCamera cam : bandCameras) {
			while (cam.getLayerCount() > 0) {
				PLayer l0 = cam.removeLayer(0);
				l0.removeCamera(cam); // bijective
				System.out.println(" * CLEAR REMOVAL: " + l0.getName() + " from CAM=" + cam.getName());
			}
		}

		setActiveSignal(null, null);

		// FIXME: all tools should implement this, then we should iterate
		// through all tools and call on clear!
		annotationEditorHandler.clear();
	}

	public void setActiveSignal(HPSplitableLayer sig, PLayer seg) {

		PLayer layer = sig;
		if (sig != null) {

			// if the signal is not loaded or is not visible, treat as if not
			// selected.
			if (layer == null || layer.getVisible() == false) {
				sig = null;
				layer = null;
				seg = null;
			}
		}

		PLayer oldActiveLayer = activeLayer;
		this.activeLayer = layer;
		y_ruler.title = (activeLayer == null) ? "" : activeLayer.getName();

		if (activeLayer != null) {
			activeSegment = seg;
		}

		if (layer != null && layer.getCameraCount() > 0) {
			// move this layer to the top,
			PCamera cam0 = layer.getCamera(0);
			cam0.removeLayer(layer);
			cam0.addLayer(layer);
		}

		resetSignalColors(sig, (activeSegment == null) ? activeLayer : activeSegment);

		this.redrawAxisLayer(0);

		firePropertyChange(ACTIVE_LAYER_PROPERTY, oldActiveLayer, activeLayer);
	}

	private void resetSignalColors(HPSplitableLayer selected_signal, PLayer segLayer) {

		if (selected_signal == null) {
			segLayer = null;
		}

		for (PCamera cam : bandCameras) {
			for (Object l : cam.getLayersReference()) {
				HPSplitableLayer layer = (HPSplitableLayer) l;

				Color color = layer.getDefaultColor();
				if (selected_signal != null) {
					color = (layer == selected_signal && segLayer == layer) ? Color.RED : Color.DARK_GRAY;
				}

				layer.setPaint(color);

				// otherwise
				// drill down and reset color of children
				for (Object child : layer.getChildrenReference()) {
					PLayer sublayer = (PLayer) child;
					sublayer.setPaint(color);
				}

			}

		}

		if (prevSegLayer != null) {
			HPSplitableLayer sig = (HPSplitableLayer) prevSegLayer;
			prevSegLayer.setPaint(sig.getPaint());
		}

		if (segLayer != null) {
			segLayer.setPaint(Color.RED);
		}
		prevSegLayer = segLayer;

	}

	public void showCursorValue(boolean b) {
		if (lineTool != null) {
			lineTool.setShowCursorValue(b);
		}
	}

	public void showGraphScale(boolean selected) {
		graphScaleVisible = selected;
		thisComponentResized(null);
	}

	public void showGraphTimeline(boolean selected) {
		graphTimelineVisible = selected;
		thisComponentResized(null);
	}

	public void showGraphLegend(boolean selected) {
		legendVisible = selected;
		thisComponentResized(null);
	}

	public RpDisplay getDisplay() {
		RpDisplay display = new RpDisplay();

		List<RpBandData> bands = display.getBandData();

		for (PCamera cam : bandCameras) {
			PBounds bounds = cam.getViewBounds();

			List<PLayer> layers = cam.getLayersReference();
			System.out.println("LAYER COUNT: " + layers.size());

			for (PLayer l0 : layers) { // hide all layers except the ones we
										// explicitly layout

				if (l0.getVisible() == false) {
					// only store visible layers
					continue;
				}
				RpBandData band = new RpBandData();

				List<RpWaveformSetup> waves = band.getWaveformSetup(); // for
																		// now,
																		// we
																		// only
																		// understand
																		// one
																		// wave/band

				HPSplitableLayer sig = (HPSplitableLayer) l0.getAttribute("sig");
				// String loc = sig.getLocation();
				// String code = sig.getDescription().getCode(); // CODE needed
				// for
				// HSE
				//
				RpWaveformSetup wave = new RpWaveformSetup();
				wave.setLoc(sig.getLocation());
				wave.setSampleRate(sig.getSampleRate());
				waves.add(wave);

			}
		}

		return display;
	}

	// FIXME: only handles the old one-camera approach
	@Deprecated
	public void setDisplay(String displayName, DisplayConfig display) {
		resetLayout();

		List<BandLayout> bands = display.getBands();

		PCamera cam0 = addBand(1, 16);
		PBounds bounds = cam0.getBounds();
		double h = bounds.getHeight() / bands.size() - BAND_SPACING;
		double w = bounds.getWidth();
		double x = bounds.getX();
		double y = bounds.getY();

		if (y != TOP_MARGIN) {
			log.error("Y should be top margin: {} <> {}", y, TOP_MARGIN);
		}

		y += BAND_SPACING / 2;

		for (BandLayout band : display.getBands()) {

			log.error("FIXME: setDisplay(DisplayConfig) not ready");
			y += h + BAND_SPACING;
		}
		repaint();
	}

	/**
	 * Change the graph layout by indicating the number of bands and their relative
	 * size explicitly. Layout description is provided in a JSON encoded array of
	 * band descriptions..
	 * 
	 * @param json
	 * 
	 *             {@code}
	 * 
	 *             std_layout <- '[ { "bandName" : "band0", "bandId" : 0,
	 *             "bandWeight" : 0.25, "yScale" : 1.0, "yTranslate": 0.0 }, {
	 *             "bandName" : "band1", "bandId" : 1, "bandWeight" : 0.25, "yScale"
	 *             : 1.0, "yTranslate": 0.0 }, { "bandName" : "band2", "bandId" : 2,
	 *             "bandWeight" : 0.5, "yScale" : 1.0, "yTranslate": 0.0 } ]'
	 * 
	 *             canvas$setDisplayLayout( std_layout )
	 * 
	 */
	public void setDisplayLayout(String json) {
		List<TsBand> bands = new LinkedList<TsBand>();

		Gson gson = new Gson();
		// TsBand desc = gson.fromJson(json, TsBand.class );
		bands = gson.fromJson(json, new TypeToken<List<TsBand>>() {
		}.getType());

		setDisplayLayout(bands);
	}

	public void setDisplayLayout(List<TsBand> bands) {
		resetLayout();

		PCamera default_cam = null;
		double default_weight = -1;

		for (TsBand band : bands) {
			float weight = band.getBandWeight();
			PCamera cam = addBand(band.getBandId(), weight);
			cam.setName(band.getBandName());
			cam.addAttribute("tsBand", band);

			if (weight > default_weight) {
				default_cam = cam;
			}
		}

//		if (default_cam != null) {
//			populateDefaultCam(default_cam);
//
//			reset();
//		}
		thisComponentResized(null);

	}

	public void getDisplayBands(List<TsBand> tsoBands) {
		for (PCamera cam : bandCameras) {
			MutableAttributeSet props = cam.getClientProperties();
			Integer band_id = (Integer) props.getAttribute(BAND_ID);
			Double weight = (Double) props.getAttribute(BAND_WEIGHT);

			TsBand band = new TsBand();
			band.setBandId(band_id);
			band.setBandName(cam.getName());
			band.setBandWeight(weight.floatValue());

			PAffineTransform tr0 = cam.getViewTransform();
			band.setYScale(tr0.getScaleY());
			band.setYTranslate(tr0.getTranslateY());

			tsoBands.add(band);
		}

	}

	public void setDisplayLayout(DisplayLayout displayLayout) {

		resetLayout();

		PCamera default_cam = null;
		switch (displayLayout) {
		case GD_ONE:
			default_cam = addBand(0, 16);
			break;
		case GD_TWO_BOTTOM:
			addBand(0, 4);
			default_cam = addBand(1, 12);
			break;
		case GD_TWO_EQUAL:
			addBand(0, 8);
			default_cam = addBand(1, 8);
			break;
		case GD_TWO_TOP:
			default_cam = addBand(0, 12);
			addBand(1, 4);
			break;
		case GD_THREE_BOTTOM:
			addBand(0, 4);
			addBand(1, 4);
			default_cam = addBand(2, 8);
			break;
		case GD_THREE_CENTER:
			addBand(0, 4);
			default_cam = addBand(1, 8);
			addBand(2, 4);
			break;
		case GD_THREE_TOP:
			default_cam = addBand(0, 8);
			addBand(1, 4);
			addBand(2, 4);
			break;
		case GD_FOUR:
			addBand(0, 4);
			addBand(1, 4);
			addBand(2, 4);
			default_cam = addBand(3, 4);
			break;
		case TILED:
		default:
			default_cam = addBand(0, 16);
		}

//		populateDefaultCam(default_cam);

		if (displayLayout != TILED) {

			reset();
			thisComponentResized(null);

			return;
		}

		// this handles the TILED case only. Everything else has
		// exited this routine already

		// UNTESTED
		log.error("FIXME: Tiled routine is untested");
		PCamera cam0 = bandCameras.get(0);
		PAffineTransform tr = cam0.getViewTransformReference();

		// set y scale to 1 using a matrix concat operation
		double sy = tr.getScaleY();
		tr.scale(1, Math.abs(1 / sy));

		PBounds bounds = cam0.getViewBounds();
		tr.translate(0, bounds.getY()); // reset y translation to 0, matrix
										// concat, see javadoc
		bounds = cam0.getBounds(); // need the initial Y value

		int count = cam0.getLayerCount();
		// y scale should be 1...so this can come from view bounds or layout
		// bounds
		double h = bounds.getHeight() / count;
		double w = bounds.getWidth();

		double x = bounds.getX();
		double y = bounds.getY();

		for (int i = 0; i < count; i++) {
			PLayer layer = cam0.getLayer(i);
			layer.setBounds(x, y, w, h);
			if (i == 0) {
				layer.setPaint(Color.RED);
				layer.setTransparency(1);
			}
			System.out.print("L3: " + layer.getName());
			System.out.println(" bounds: " + layer.getBounds());

			y += h;
		}

		repaint();
	}

	private AffineTransform transformFromSignal(HPSplitableLayer sig) {
		AffineTransform tran = new AffineTransform();

		RpUnit u = sig.getUnit();
		if (u instanceof RpLinearUnit) {
			RpLinearUnit lu = (RpLinearUnit) u;
			tran.setToScale(1, lu.getM());
		}

		return tran;
	}

	public void resetLayout() {
		if (transformActivity != null) {
			// if rescaling animation is in progress for this canvas, cancel it!
			transformActivity.terminate(PActivity.TERMINATE_WITHOUT_FINISHING);
		}

		while (bandCameras.size() > 0) {
			PCamera cam = bandCameras.get(0);
			System.out.println("REMOVING ALL CHILDREN FROM CAM: " + cam.getName());
			// dump(3, 0, cam);

			while (cam.getLayerCount() > 0) {
				PLayer layer0 = cam.getLayer(0);
				cam.removeLayer(layer0);
				layer0.removeCamera(cam);
				System.out.println(" * removed: " + layer0.getName());
			}
			cam.removeAllChildren();
			bandCameras.remove(0);
			System.out.println("DUMP AND REMOVAL COMPLETE: " + cam.getName());
		}
	}

	/*
	 * one of the scroll functions...
	 */
	public void zoomToWidthInMillis(int millis) {
		if (transformActivity != null && transformActivity.isStepping()) {
			// if rescaling animation is in progress for this canvas, cancel it!
			transformActivity.terminate(PActivity.TERMINATE_WITHOUT_FINISHING);
		}

		PCamera cam0 = bandCameras.get(0);
		PBounds view_r = cam0.getViewBounds();

		double desired_w = millis / 1000.0;
		double end_x = view_r.getX() + view_r.getWidth();
		double start_x = end_x - desired_w;

		PAffineTransform ori = cam0.getViewTransform();

		double sx = cam0.getWidth() / desired_w;
		double sy = ori.getScaleY();
		AffineTransform desired = new AffineTransform();
		desired.scale(sx, sy);
		desired.translate(-start_x, ori.getTranslateY() / sy);

		transformActivity = cam0.animateViewToTransform(desired, PREF_ANIMATE_MS);
		transformActivity.setDelegate(updateDelegate);
		undoManager.addEdit(new TransformEdit(this, cam0, ori, desired));
	}

	/*
	 * one of the scroll functions...
	 * 
	 * FIXME: this function does not do what it advertises :) Needs work
	 * 
	 * The domain APPLIES TO ALL CAMERAS.
	 */
	public void setViewDomainInMillis(long start_pos, long end_pos) {

		if (transformActivity != null && transformActivity.isStepping()) {
			// if rescaling animation is in progress for this canvas, cancel it!
			transformActivity.terminate(PActivity.TERMINATE_WITHOUT_FINISHING);
		}

		PCamera cam0 = bandCameras.get(0);
		PBounds view_r = cam0.getViewBounds();

		double end_x = end_pos / 1000.0;
		double start_x = start_pos / 1000.0; // end_x - view_r.width;

		for (PCamera cam : bandCameras) {
			view_r = cam.getViewBounds();
			view_r.x = start_x;
			view_r.width = end_x - start_x;
			cam.setViewBounds(view_r);
		}
		_redrawAxisLayer();
	}

	public void terminateAnimation(int terminateAndFinish) {
		if (transformActivity != null && transformActivity.isStepping()) {
			transformActivity.terminate(terminateAndFinish);
		}
	}

	/*
	 * *************************************************************************
	 * Edit functionality...wish it were part of another module, but depends on
	 * local variables, even more so once you add the undo functionality
	 * *************************************************************************
	 */

	public List<PNode> removeNodesAtMousePoint(Point2D mousePt) {
		PCamera cam0 = bandCameras.get(0);
		PAffineTransform tr = cam0.getViewTransform();

		Point2D dataPt = new Point2D.Double();
		tr.inverseTransform(mousePt, dataPt);

		float[] r = createMaxAndMin(dataPt.getX());
		return annotationEditorHandler.removeEventInRange(null, r[0], r[1]);
	}

	public void dumpFiducialNodes(PLayer editLayer) {
		List<PNode> children = editLayer.getChildrenReference();
		int index = 0;
		for (PNode node : children) {
			TsoAnnotationEntryType item = (TsoAnnotationEntryType) node.getAttribute("item");
			;
			System.out.println("node[" + index + ": " + item.getOffset() + " == " + node.getX() + " seq="
					+ item.getTempSeq() + " code=" + item.getCode());
			index++;
		}
	}

	public PCamera getBand(String cameraName) {
		PCamera camera = null;
		for (PCamera band : bandCameras) {
			if (cameraName.equals(band.getName())) {
				camera = band;
				break;
			}
		}
		return camera;
	}

	public PCamera getBandAt(Point2D canvasPressPt) {
		for (PCamera band : bandCameras) {
			PBounds bounds = band.getBounds();
			if (bounds.contains(canvasPressPt)) {
				return band;
			}
		}
		return null;
	}

	public float[] createMaxAndMin(double mouseX) {

		PCamera camera = bandCameras.get(0);
		PAffineTransform tr = camera.getViewTransform();

		double x_scale = tr.getScaleX();

		float cursor_width = (float) (16f / x_scale);

		float x = (float) mouseX;
		float mmin = x - cursor_width;
		float mmax = mmin + 2 * cursor_width;
		return new float[] { mmin, mmax };
	}

	public void split(PCamera cam) {
		if (cam == null) {
			cam = getCameraAtMousePos();
		}

		if (cam == null) {
			log.warn("No camera specified or at mouse location");
			return;
		}

		MutableAttributeSet props = cam.getClientProperties();
		// props.getAttribute(BAND_ID, band_id);
		double weight = ((Number) props.getAttribute(BAND_WEIGHT)).doubleValue();
		double weight_rev = weight / 2;
		props.addAttribute(BAND_WEIGHT, weight_rev);

		int max_id = 0;
		for (PCamera cam0 : bandCameras) {
			props = cam0.getClientProperties();
			Integer band_id = (Integer) props.getAttribute(BAND_ID);
			if (band_id > max_id) {
				max_id = band_id;
			}
		}

		for (int idx = 0; idx < bandCameras.size(); idx++) {
			if (bandCameras.get(idx) == cam) {
				PCamera new_cam = insertBand(idx, max_id + 1, weight_rev);

				PAffineTransform old = cam.getViewTransform();

				double m00 = old.getScaleX();
				double m01 = 0;
				double m10 = 0;
				double m11 = -1;
				double m02 = old.getTranslateX();
				// height of this camera has not been computed yet, so take half
				// the height
				// of the old camera
				double m12 = cam.getHeight() / 2;

				PAffineTransform new_tran = new PAffineTransform(m00, m10, m01, m11, m02, m12);

				new_cam.setViewTransform(new_tran);
				break;
			}
		}

		this.thisComponentResized(null);
		return;
	}

	public void join(PCamera cam_to_remove) {
		if (cam_to_remove == null) {
			// this probably doesnt work...if mouse was moved to make menu
			// selection
			cam_to_remove = getCameraAtMousePos();
		}

		if (cam_to_remove == null) {
			log.warn("No camera specified or at mouse location");
			return;
		}

		System.out.println("cam to remove: " + cam_to_remove.getName());

		// get weight of camera being removed
		MutableAttributeSet props = cam_to_remove.getClientProperties();
		double removed_weight = (Double) props.getAttribute(BAND_WEIGHT);

		// find the next camera below...if any
		PCamera next_cam = null;
		double min_y = cam_to_remove.getY();
		double next_y = Double.MAX_VALUE;
		for (PCamera cam0 : bandCameras) {
			double cam0_y = cam0.getY();
			System.out.println("cam: " + cam0.getName() + " y=" + cam0_y);
			if (cam0_y <= min_y) {
				continue;
			}
			if (cam0_y < next_y) {
				System.out.println("selected cam: " + cam0.getName() + " y=" + cam0_y);
				next_cam = cam0;
				next_y = cam0_y;
			}
		}

		if (next_cam != null) {
			// get weight of camera being removed
			props = next_cam.getClientProperties();
			double next_weight = (Double) props.getAttribute(BAND_WEIGHT);
			props.addAttribute(BAND_WEIGHT, next_weight + removed_weight);

			Iterator<PLayer> lit = cam_to_remove.getLayersReference().iterator();
			while (lit.hasNext()) {
				PLayer layer = lit.next();
				lit.remove();

				next_cam.addLayer(layer);
			}
			Iterator<PCamera> ii = bandCameras.iterator();
			while (ii.hasNext()) {
				if (cam_to_remove == ii.next()) {
					ii.remove();
					break;
				}
			}
		}

		this.thisComponentResized(null);
		return;
	}

	public void setFeatureMode(int editMode) {
		this.defaultEditMode = editMode;
		lineTool.setDefaultEditMode(editMode);
	}

	public void setTimelineLabelFormat(LabelType timeFormat) {
		timelineLabelFormat = timeFormat;
		thisComponentResized(null);
		// _redrawAxisLayer();
	}

	public void setGraphLabelFormat(LabelType labelType) {
		graphXLabelFormat = labelType;
		if (labelType == LabelType.LABEL_CLOCKTIME) {
			x_ruler.title = "Time [clock]";
		} else if (labelType == LabelType.LABEL_REL_MMSS) {
			x_ruler.title = "Relative Time [mm:ss]";
		} else if (labelType == LabelType.LABEL_REL_SECS) {
			x_ruler.title = null;
		} else {
			log.error("Unexpected label type: {}", labelType);
		}
		this.graphXLabelFormat = labelType;

		if (lineTool != null) {
			lineTool.setLabelType(labelType);
		}
		// redrawAxisLayer(0);
		thisComponentResized(null); // repositions cameras, which is not done in a simple redraw
		// _redrawAxisLayer();
	}

	public void setCalibration(boolean b) {
		allModesOff();
		calibration = b;
		Color theme_filter_background = Color.RED.darker().darker().darker().darker();
		getCamera().setPaint((b) ? theme_filter_background : theme_plot_background);

		showGraphScale(b);
		thisComponentResized(null);
	}

	public void setIntersection(boolean b) {
		allModesOff();
		intersection = b;
		Color theme_filter_background = Color.YELLOW.darker().darker().darker().darker();
		getCamera().setPaint((b) ? theme_filter_background : theme_plot_background);

		showGraphScale(b);
		thisComponentResized(null);
	}

	public void setFilter(boolean b) {
		allModesOff();
		filter = b;
		Color theme_calib_background = Color.CYAN.darker().darker().darker().darker();
		getCamera().setPaint((b) ? theme_calib_background : theme_plot_background);

		thisComponentResized(null);
	}

	public void setGraphParams(boolean b) {
		allModesOff();
		graphParams = b;

		Color theme_graphparams_background = Color.ORANGE.darker().darker().darker().darker();
		getCamera().setPaint((b) ? theme_graphparams_background : theme_plot_background);

		thisComponentResized(null);
	}

	private void allModesOff() {
		calibration = false;
		b2bAnalysis = false;
		anAnalysis = false;
		showUnused = false;
		graphParams = false;
		filter = false;
		intersection = false;
		showGraphScale(false);
	}

	public void setAnAnalysis(boolean b) {
		allModesOff();
		anAnalysis = b;

		Color theme_analysis_background = Color.BLUE.darker().darker().darker().darker();
		getCamera().setPaint((b) ? theme_analysis_background : theme_plot_background);

		thisComponentResized(null);
	}

	public void setB2BAnalysis(boolean b) {
		allModesOff();
		b2bAnalysis = b;
		Color theme_analysis_background = Color.BLUE.darker().darker().darker().darker();
		getCamera().setPaint((b) ? theme_analysis_background : theme_plot_background);

		thisComponentResized(null);
	}

	public void setShowUnused(boolean b) {
		allModesOff();
		showUnused = true;
		Color theme_unusedsigs_background = Color.GREEN.darker().darker().darker().darker().darker().darker();
		getCamera().setPaint((b) ? theme_unusedsigs_background : theme_plot_background);

		thisComponentResized(null);
	}

	public void setExplore(boolean b) {
		allModesOff();
		getCamera().setPaint(theme_plot_background);

		thisComponentResized(null);
	}

	public void moveLeftRight(double dir) {

		if (calibration) {
			PLayer dataSeg = legendHandler.getCalibrationSegment();
			calibrateLeftRight(dataSeg, dir);
		} else {
			super.moveLeftRight(dir);
		}

	}

	public void moveUpDown(PCamera cam0, double mdir) {
		if (calibration) {
			PLayer dataSeg = legendHandler.getCalibrationSegment();
			calibrateUpDown(dataSeg, mdir);
		} else {
			super.moveUpDown(cam0, mdir);
		}
	}

	private void calibrateLeftRight(PLayer dataSeg, double dir) {
		if (dataSeg == null) {
			return;
		}

		AffineTransform tran = new AffineTransform();
		tran.translate(dir * 0.002, 0); // WARNING: hard coded calibration step
										// size

		dataSeg.getTransformReference(true).concatenate(tran);
		_redrawAxisLayer();
	}

	public void calibrateUpDown(PLayer dataSeg, double dir) {
		if (dataSeg == null) {
			return;
		}
		// PAffineTransform ori_tr = layer.getTransform();

		// PBounds view_rr = dataSeg.getCamera(0).getViewBounds();
		double data_height = 10; // view_rr.getWidth();

		AffineTransform tran = new AffineTransform();
		tran.translate(0, -dir * data_height * 0.01); // WARNING: hard coded
														// calibration step size

		dataSeg.getTransformReference(true).concatenate(tran);
		// undoManager.addEdit(new TransformEdit(this, layer, ori_tr,
		// desired_tr));
		_redrawAxisLayer();
	}

	public void moveSignalToBand(PCamera band, HPSplitableLayer sig) {
		if (band == null || sig == null) {
			log.error("Cannot move signal: {} to band: {}", sig, band);
			return;
		}
		PLayer sig_layer = sig;
		log.debug("ATTEMPTING TO INSERT LAYER {} INTO BAND: {}", sig_layer.getName(), band.getName());
		if (sig_layer != null) {
			System.out.println("LOOKS OK...ADDING TO: " + band.getName());
		}

		while (sig_layer.getCameraCount() > 0) {
			PCamera cam = sig_layer.getCamera(0);
			cam.removeLayer(sig_layer);
			sig_layer.removeCamera(cam);
			System.out.println("...but first removing from " + cam.getName());
		}
		if (sig.getPaint() == null) {
			sig.setPaint(sig.getDefaultColor()); // for newly created sigs, this may be empty
		}
		sig_layer.setPaint(sig.getPaint()); // not redundant, but won't work otherwise
		sig_layer.setVisible(true); // just in case...
		band.addLayer(sig_layer);
		centerView(band);

		redrawAxisLayer(0);
	}

	public void applyDefaults() {
		for (PCamera cam : bandCameras) {
			scaleToFit(cam, null);
		}
	}

}
