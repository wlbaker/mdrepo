package idea.tsoffline.video;

import java.awt.Color;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.awt.geom.Point2D;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.DateFormat;
import java.util.Collection;
import java.util.Date;

import javax.swing.text.MutableAttributeSet;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.event.PInputEvent;
import org.piccolo2d.event.PInputEventListener;
import org.piccolo2d.event.PPanEventHandler;
import org.piccolo2d.event.PZoomEventHandler;
import org.piccolo2d.extras.nodes.PLine;
import org.piccolo2d.extras.util.LineShape;
import org.piccolo2d.extras.util.XYArray;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.nodes.PText;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;
import org.piccolo2d.util.PPaintContext;
import org.sittingbull.gt.util.NiceStepSizeGenerator;
import org.sittingbull.gt.util.XWilkinson;

import idea.schema.rp.RpMetric;
import lombok.Getter;
import idea.GuiUtil;
import idea.Stats;
import idea.tsoffline.AppConstants;
import idea.tsoffline.canvas.LabelType;
import idea.tsoffline.canvas.PiccoUtil;
import idea.tsoffline.canvas.TsBaseCanvas;
import idea.tsoffline.model.OfflineSignal;
import idea.tsoffline.tspico.RulerComponent;

@SuppressWarnings("serial")
public class TsPhaseSpaceCanvas extends TsBaseCanvas {

	public static final float LEFT_MARGIN = 50;
	private static final float BOTTOM_MARGIN = 14;
	public static float TOP_MARGIN = 10;
	public static float RULER_HEIGHT = 12;
	private static final float RIGHT_MARGIN = 20;
	private static final int BUFFER_SECONDS = 30;
	private static final int BUFFER_BEATS = 60;
	private static final double FUDGE_CENTROID_OFFSET_SEC = 1.5;

	/*
	 * theme support
	 */
	Color theme_inset_color = Color.BLACK; // Color.DARK_GRAY;
	Color theme_plot_background = Color.BLACK; // Color.DARK_GRAY;
	Color theme_axis_background = Color.LIGHT_GRAY;
	Color theme_tick_color = Color.WHITE;
	Color theme_slider_color = Color.LIGHT_GRAY;
	Color theme_ruler_color = Color.WHITE;
	Color theme_border_color = Color.BLUE;
	Color theme_y_range_color = Color.GREEN;
	Color theme_spotter_color = Color.RED.darker();
	Color theme_centroid_color = Color.MAGENTA;

	boolean inverse;

	private PCamera phaseCamera;
	private PCamera signalCamera;
	
	private PLayer phaseLayer;
	private PLayer centroidLayer;
	int seq = 0;
	private double dsecs;
	double[][] tm;
	double[][] xx;
	double[][] yy;

	PLine[] llines = null;
	private PPath centroid[];

	private PPath spotter;
	private PText time_txt;
	private PText date_txt;
	private PText title_txt;

	private int start_idx;
	private int start_pos;
	private Color[] colors;
	private float prev_w;
	private float prev_h;

	private double ph_x0 = 1000;
	private double ph_x1 = 7400;
	private double ph_y0 = -60000;
	private double ph_y1 = 180000;

	@Getter
	RulerComponent pressure_ruler = new RulerComponent();
	@Getter
	RulerComponent time_ruler = new RulerComponent();
	RulerComponent dpdt_ruler = new RulerComponent();

	XWilkinson wilkinson = new XWilkinson(new NiceStepSizeGenerator());

	private int ffreq = 200;
	private int pkt_len = 100;
	int dest_sec = 0;
	private int curr_sec;
	private double data_xmax;
	private double data_xmin;
	private double data_ymax;
	private double data_ymin;
	@Getter
	private String sigName;
	OfflineSignal centroidSignal;
	
	@Getter
	private String subject;

	@Getter
	private Date currentDate;
	
	double dtUpper = -2;
	double dtLower = 28;
	
	double [] sc_upper = { -2.0, -1.0, -0.5 }; 
	double [] sc_lower = { 28.0, 12.0, 4.0 };
	int sc_seq = 0;
	private PInputEventListener centroidEventListener;

	public TsPhaseSpaceCanvas() {

		addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent e) {
				TsPhaseSpaceCanvas.this.componentResized(e);
			}
		});

		getCamera().setName("ph_camera.ROOTCAMERA");
		getCamera().setPaint(theme_plot_background);
		
		phaseLayer = new PLayer();
		phaseLayer.setName("ph_datalayer");

		centroidLayer = new PLayer();
		centroidLayer.setName("centroid_datalayer");

		{
			phaseCamera = new PCamera() {

				@Override
				protected void paint(PPaintContext paintContext) {
					// TODO Auto-generated method stub
					super.paint(paintContext);
				}
			
			};
			phaseCamera.setName("ph_datacam");
			phaseCamera.addLayer(phaseLayer);
			phaseCamera.addLayer(centroidLayer);
			MutableAttributeSet props = phaseCamera.getClientProperties();
			props.addAttribute(BAND_WEIGHT, 3.0);

			phaseCamera.addAttribute("nosync", true);
			phaseCamera.addAttribute("nocenter", true);
		}

		{
			signalCamera = new PCamera();
			signalCamera.setName("ph_sigcam");
			MutableAttributeSet props = signalCamera.getClientProperties();
			props.addAttribute(BAND_WEIGHT, 1.0);

			signalCamera.setPickable(false);
			signalCamera.setChildrenPickable(false);
		}

		bandCameras.add(phaseCamera);
		bandCameras.add(signalCamera);

		// this property gets changed with mouse-drags of the layer inside
		// ...of course you could set the layer to non-pickable, but I like it
		// being pickable!
		// ...redraw the rulers when the view changes.
		phaseCamera.addPropertyChangeListener("viewTransform", new PropertyChangeListener() {
			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				_redrawAxisLayer();
			}
		});

		PPanEventHandler peh = new PPanEventHandler() {

			@Override
			protected void pan(PInputEvent event) {
				PCamera cam = event.getCamera();
				if (cam == phaseCamera) {
					super.pan(event);
				}
			}

		};

		PZoomEventHandler zeh = new PZoomEventHandler() {

			@Override
			protected void dragActivityStep(PInputEvent event) {
				final PCamera camera = event.getCamera();
				if (camera == phaseCamera) {
					super.dragActivityStep(event);
				}
			}

		};

		this.setPanEventHandler(peh);
		this.setZoomEventHandler(zeh);

		getLayer().removeAllChildren();
		getLayer().addChild(axisLayer);

		initTools();
		
		this.setBackground( Color.WHITE );
		this.setDefaultRenderQuality(PPaintContext.LOW_QUALITY_RENDERING);
		
		setInverse(false);
		
	}


	@Override
	protected void processKeyPressed(PCamera cam0, KeyEvent e) {

		int keyCode = e.getKeyCode();
		if (keyCode == KeyEvent.VK_0) {
			setPhasespaceSize( ph_x0,  ph_x1,  ph_y0, ph_y1);
			e.consume();
		} else if (keyCode == KeyEvent.VK_A) {
			resizePhasespace( );
			e.consume();
		} else if (keyCode == KeyEvent.VK_PLUS || keyCode == KeyEvent.VK_ADD || keyCode == KeyEvent.VK_EQUALS ) {
			if( sc_seq < sc_upper.length - 1 ) {
				sc_seq++;
				dtUpper = sc_upper[sc_seq];
				dtLower = sc_lower[sc_seq];
				
				zoomCameraToXScale(signalCamera, dsecs + dtUpper, dsecs+dtLower);
				updateSigCamera();
			}
			e.consume();
		} else if (keyCode == KeyEvent.VK_MINUS || keyCode == KeyEvent.VK_SUBTRACT ) {
			if( sc_seq > 0 ) {
				sc_seq--;
				dtUpper = sc_upper[sc_seq];
				dtLower = sc_lower[sc_seq];
				zoomCameraToXScale(signalCamera, dsecs + dtUpper, dsecs+dtLower);
				updateSigCamera();
			}
			e.consume();
		}
		if (e.isConsumed() == false ) {
			super.processKeyPressed(cam0, e);
		}
	}

	/*
	 * handle linear data
	 */

	public void setDataArray(long tm0, double[] tm, double[] xx, double[] yy) {
		double[][] arr_tm = new double[1][];
		double[][] arr_xx = new double[1][];
		double[][] arr_yy = new double[1][];
		arr_tm[0] = tm;
		arr_xx[0] = xx;
		arr_yy[0] = yy;
		setDataPackets(tm0, arr_tm, arr_xx, arr_yy);
		
		dsecs = tm[0];
		
		zoomCameraToXScale(signalCamera, dsecs + dtUpper, dsecs+dtLower); // starts an animation

	}

	/*
	 * handle packetized data
	 */

	public void setDataPackets(long tm0, double[][] tm, double[][] xx, double[][] yy) {
		this.setStartTime(tm0);
		this.tm = tm;
		this.xx = xx;
		this.yy = yy;

		if (xx != null) {
			pkt_len = xx[0].length;
			// llines = new LinkedList<PLine>();
			llines = new PLine[BUFFER_SECONDS];
			curr_sec = -1;
			centroid = new PPath[BUFFER_BEATS];
		}

		if (xx != null) {
			data_xmax = Stats_max(xx);
			data_xmin = Stats_min(xx);
			data_ymax = Stats_max(yy);
			data_ymin = Stats_min(yy);

			_componentResized();
		}
	}

	private double Stats_max(double[][] xx) {
		double max = Stats.max(xx[0]);
		for (int pkt = 1; pkt < xx.length; pkt++) {
			double m2 = Stats.max(xx[pkt]);
			if (m2 > max) {
				max = m2;
			}
		}
		return max;
	}

	private double Stats_min(double[][] xx) {
		double min = Stats.min(xx[0]);
		for (int pkt = 1; pkt < xx.length; pkt++) {
			double m2 = Stats.min(xx[pkt]);
			if (m2 < min) {
				min = m2;
			}
		}
		return min;
	}

	@Override
	protected void _redrawAxisLayer() {
		super._redrawAxisLayer();
		_addCamerasToAxisLayer();

		axisLayer.addChild(spotter);
		axisLayer.addChild(date_txt);
		axisLayer.addChild(title_txt);

		PBounds bounds = phaseCamera.getBounds();
		double w = time_txt.getWidth();
		double corner = bounds.getX() + bounds.getWidth();
		time_txt.setX(corner - w - 4); // upper-right-hand corner
		axisLayer.addChild(time_txt); 

		pressure_ruler.drawXRuler(0, ticFont, wilkinson, axisLayer, phaseCamera, false, true, LabelType.LABEL_SEC_DELETEME);
		time_ruler.drawYRuler( ticFont, wilkinson, axisLayer, signalCamera, null );
		dpdt_ruler.drawYRuler( ticFont, wilkinson, axisLayer, phaseCamera, null );
	}

	protected void componentResized(ComponentEvent e) {

		float w = this.getWidth();
		float h = this.getHeight();

		if (w == prev_w && h == prev_h) {
			return;
		}

		prev_w = w;
		prev_h = h;

		_componentResized();
	}

	protected void _componentResized() {

		float ww = this.getWidth();
		float hh = this.getHeight();

		if (ww == 0 || hh == 0) {
			return;
		}

		{
			float plot_width = ww - LEFT_MARGIN - RIGHT_MARGIN;
			float plot_h = hh - TOP_MARGIN - BOTTOM_MARGIN - RULER_HEIGHT;

			resizeCameras(TOP_MARGIN, LEFT_MARGIN, plot_width, plot_h);
		}

		this._centerCamera(signalCamera);
		zoomCameraToXScale(signalCamera, dsecs+dtUpper, dsecs+dtLower); // starts an animation
		
		resizePhasespace();

		_redrawAxisLayer();

	}

	private void initTools() {
		spotter = PPath.createEllipse(0, 0, 8, 8);
		spotter.setPaint(theme_spotter_color);
		spotter.setStrokePaint(theme_border_color);
		spotter.setVisible(false);

		time_txt = new PText("0:00.000");
		time_txt.setFont(ticFont);
		time_txt.setX(LEFT_MARGIN + 4); // center around tic
		time_txt.setY(TOP_MARGIN + 4); // center the font around the tic
		time_txt.setTextPaint(theme_ruler_color); // y_ruler.color

		title_txt = new PText("?");
		title_txt.setFont(ticFont);
		title_txt.setX(LEFT_MARGIN + 4); // center around tic
		title_txt.setY(TOP_MARGIN + 4); // center the font around the tic
		title_txt.setTextPaint(theme_ruler_color); // y_ruler.color

		date_txt = new PText("?dt?");
		date_txt.setFont(ticFont);
		date_txt.setX(LEFT_MARGIN + 4); // center around tic
		date_txt.setY(TOP_MARGIN + 16); // center the font around the tic
		date_txt.setTextPaint(theme_ruler_color); // y_ruler.color

		axisLayer.addChild(time_txt);
		axisLayer.addChild(date_txt);
		axisLayer.addChild(title_txt);
		axisLayer.addChild(spotter);
	}

	public boolean update(long dt_ms) {
		boolean ok = updateAttractor(dt_ms);
		if( ok ) {
			updateCentroid(dt_ms);
		}
		return ok;
	}
	
	
	private void updateCentroid(long dt_ms) {
		double endSec = dt_ms / 1000.0 - FUDGE_CENTROID_OFFSET_SEC;
		double startSec = endSec - 30;
		if( endSec < 0 ) {
			return;
		}
		if( startSec < 0 ) {
			startSec = 0;
		}
		Collection<PNode> arr = centroidSignal.getNodesInRange(startSec, endSec);
		if( arr == null || arr.size() == 0 ) {
			return;
		}
		int cidx = 0;
		for( PNode node : arr ) {
			Double Cx = (Double) node.getAttribute("centroid_x");
			Double Cy = (Double) node.getAttribute("centroid_y");
			
			if( Cx == null || Cy == null ) {
				continue;
			}
			Double Ix = (Double) node.getAttribute("moment_x");
			Double Iy = (Double) node.getAttribute("moment_y");
			double Iz = (Ix/1000 + Iy)/100;
			
			PPath cent = null; // centroid[cidx];
			// if( cent == null ) {
			if( Iz < 3 ) {
				Iz = 3;
			}
				cent = PPath.createEllipse(0, 0, Iz, Iz);
				cent.setPaint(theme_centroid_color);
				cent.setStrokePaint(theme_border_color);
				cent.setVisible(true);
				cent.addInputEventListener(centroidEventListener);
				cent.addAttribute("source", node);
				// centroid[cidx++] = cent;
			//}
			Point2D cent_pt = new Point2D.Double( Cx, Cy );
			Point2D ptDst = new Point2D.Double();

			phaseCamera.getViewTransform().transform(cent_pt, ptDst);
			cent.setX(ptDst.getX());
			cent.setY(ptDst.getY());
			cent.setVisible(true);
			axisLayer.addChild(cent);
			cidx++;
		}
		axisLayer.repaint(); // repaint the spotter and the data camera

	}


	private boolean updateAttractor(long dt_ms) {
		int sample_pos;
		int end_idx;
		int end_pos;

		double dt_sec = dt_ms / 1000.0;

		if (ffreq == 0) {
			// FIXME: this has array overruns...untested...intended for vitals
			// type use

			end_idx = 0;
			while (xx[end_idx + 1][0] < dt_sec) {
				end_idx++;
			}
			end_pos = 0;
			while (xx[end_idx][end_pos + 1] < dt_sec) {
				end_pos++;
			}
			sample_pos = (int) (dt_ms / 1000);
		} else {
			/*
			 * Show the date/time at the top of the screen
			 */
			sample_pos = (int) (dt_ms * ffreq / 1000);
			end_idx = (int) (sample_pos / pkt_len);
			end_pos = (int) (sample_pos % pkt_len);

			// gap since last update caon't be more than 5 secs!
			if( sample_pos - start_pos > 5*500) {
				// this is only vaguely correct...works as long as we only have one LONG array
				start_pos = sample_pos - 5*500;
				if( start_pos < 0 ) start_pos = 0;
			}
			if( start_pos > end_pos) {
				start_pos = end_pos;
			}
			{
				int mins = (int) (dt_ms / 60000);
				int secs = (int) ((dt_ms % 60000) / 1000);
				int millis = (int) (dt_ms % 1000);
				String t = String.format("%d:%02d.%03d", mins, secs, millis);
				time_txt.setText(t);
			}

			if (tm != null) {
				dsecs = tm[start_idx][start_pos];
				long world_millis = getStartTime() + (long) (1000.0 * dsecs);
				currentDate = new Date(world_millis);
				DateFormat df = GuiUtil.getDateTimeFormat();
				date_txt.setText(df.format(currentDate));
			}
			if (end_idx >= xx.length) {
				return false;
			}

			updateSigCamera();

			_redrawAxisLayer();
		}

		for (int src_idx = start_idx; src_idx <= end_idx; src_idx++) {
			int src_len = pkt_len - start_pos;
			if (src_idx == end_idx) {
				src_len = end_pos - start_pos;
			}
			if (src_len == 0) {
				continue;
			}

			dest_sec = sample_pos / ffreq;

			if (dest_sec != curr_sec) {
				curr_sec = dest_sec;

				XYArray xy = new XYArray(ffreq + 1);
				int pp = 0;
				if (start_pos > 0 && start_idx > 0) {
					int prev_idx = start_idx;
					int prev_pos = start_pos - 1;
					prev_pos--;
					if (prev_pos < 0) {
						prev_pos += pkt_len;
						prev_idx--;
					}
					xy.addPoint(pp++, xx[prev_idx][prev_pos], yy[prev_idx][prev_pos]);
				}
				for (int i = 0; i < src_len; i++) {
					xy.addPoint(pp++, xx[src_idx][start_pos + i], yy[src_idx][start_pos + i]);
				}
				final LineShape path = new LineShape(xy);
				path.updateBounds();
				
				PLine line = new PLine(path);

				PLine last = llines[BUFFER_SECONDS - 1];
				if (last != null) {
					phaseLayer.removeChild(last);
				}
				for (int i = BUFFER_SECONDS - 2; i >= 0; i--) {
					llines[i + 1] = llines[i];
				}
				llines[0] = line;

				line.setStroke(AppConstants.getDefaultSignalStroke());
				// line.setStroke( new PFixedWidthStroke(3.0f) );

				line.setStrokePaint(Color.RED);
				line.setPaint(Color.GREEN);
				line.setVisible(true);

				phaseLayer.addChild(line);
				updateDataColors();
			} else {
				PLine line = llines[0]; // llines.get(0);
				PiccoUtil.appendPolyline(line, xx[src_idx], yy[src_idx], start_pos, src_len);
			}
			start_pos = 0;
		}
		start_idx = end_idx;
		start_pos = end_pos;

		Point2D spotter_pt = new Point2D.Double(xx[end_idx][end_pos], yy[end_idx][end_pos]);
		Point2D ptDst = new Point2D.Double();

		phaseCamera.getViewTransform().transform(spotter_pt, ptDst);
		spotter.setX(ptDst.getX());
		spotter.setY(ptDst.getY());
		spotter.setVisible(true);
		// dataCamera.getViewTransform().inverseTransform(spotter_pt, ptDst);

		// redrawAxisLayer();
		// dataCamera.repaint();
		axisLayer.repaint(); // repaint the spotter and the data camera

		return true;
	}

	private void updateSigCamera() {
		// PBounds vbounds = signalCamera.getViewBounds();
		double vbounds_width = dtLower - dtUpper; 
		PAffineTransform vtrans = signalCamera.getViewTransformReference();

		double sx = vtrans.getScaleX();
		double tx = sx * (vbounds_width - dsecs ); // aka m12
		
		// System.out.println("sx=" + sx + " tx=" + tx + " dsecs=" + dsecs + " width=" + vbounds_width );
		vtrans.setTransform(sx, 0, 0, vtrans.getScaleY(), tx, vtrans.getTranslateY());
	}

	public void clear() {
		phaseLayer.removeAllChildren();
		centroidLayer.removeAllChildren();
		phaseLayer.addChild(spotter);

		start_idx = 0;
		start_pos = 0;
		curr_sec = -1;

		// llines = new LinkedList<PLine>();
		llines = new PLine[BUFFER_SECONDS];

		spotter.setVisible(false);
		repaint();
	}

	public void updateGradient(Color[] colors) {
		this.colors = (Color[]) colors.clone();

		if (colors != null) {
			updateDataColors();

			// drawData();
			repaint();
		}
	}

	private void updateDataColors() {
		if (colors == null || llines == null) {
			return;
		}
		int lastColor = colors.length;

		int nColors = BUFFER_SECONDS;
		int colorStep = lastColor / nColors;

		int currColor = 0;

		if (!inverse) {
			currColor = lastColor - 1;
			colorStep = -colorStep;
		}

		for (PLine node : llines) {
			if (node == null) {
				break;
			}

			node.setStrokePaint(colors[currColor]);
			currColor += colorStep;
		}

	}

	public void setSubject(String subject) {
		this.subject = subject;
		updateTitle();
	}

	public void setDisplaySignal(RpMetric sigInfo) {
		ffreq = 0;
		if (sigInfo.getSampleRate() != null) {
			ffreq = sigInfo.getSampleRate();
		}
		sigName = sigInfo.getAlias();
		updateTitle();

		pressure_ruler.setUnit(sigInfo.getUnit());
		time_ruler.setUnit(sigInfo.getUnit());

		if (sigInfo instanceof OfflineSignal) {
			OfflineSignal sig = (OfflineSignal) sigInfo;

			if (sig.getLayer() != null) {
				while (signalCamera.getLayerCount() > 0) {
					signalCamera.removeLayer(0);
				}
				signalCamera.addLayer(sig.getLayer());
			}
		}
	}

	public void setCentroidSignal(OfflineSignal sig) {
		centroidSignal = sig;

	}

	private void updateTitle() {
		String title = subject;
		if (title == null) {
			title = "";
		}

		if (sigName != null) {
			if (title.length() > 0) {
				title += "/";
			}
			title += sigName;
		}
		title_txt.setText(title);
		this.setName( title );
	}

	public void setInverse(boolean b) {
		this.inverse = b;

		if (b) {
			theme_inset_color = Color.WHITE;
			theme_plot_background = Color.LIGHT_GRAY;
			theme_axis_background = Color.DARK_GRAY;
			theme_tick_color = Color.BLACK;
			theme_slider_color = Color.DARK_GRAY;
			theme_ruler_color = Color.BLACK;
			theme_border_color = Color.BLUE;
			theme_y_range_color = Color.GREEN;
			theme_spotter_color = Color.RED.darker();
			theme_centroid_color = Color.MAGENTA;
		} else {
			theme_inset_color = Color.BLACK;
			theme_plot_background = Color.BLACK; // Color.DARK_GRAY;
			theme_axis_background = Color.LIGHT_GRAY;
			theme_tick_color = Color.WHITE;
			theme_slider_color = Color.LIGHT_GRAY;
			theme_ruler_color = Color.WHITE;
			theme_border_color = Color.BLUE;
			theme_y_range_color = Color.GREEN;
			theme_spotter_color = Color.RED.darker();
			theme_centroid_color = Color.MAGENTA;
		}

		phaseCamera.setPaint( theme_plot_background );
		signalCamera.setPaint( theme_plot_background );
		getCamera().setPaint(theme_inset_color);
		//getLayer().setPaint(theme_plot_background);

		time_txt.setTextPaint(theme_ruler_color);
		title_txt.setTextPaint(theme_ruler_color);
		date_txt.setTextPaint(theme_ruler_color);

		pressure_ruler.setThemeColor(theme_ruler_color);
		time_ruler.setThemeColor(theme_ruler_color);
		dpdt_ruler.setThemeColor(theme_ruler_color);

		this._componentResized();

	}

	public void setPhasespaceSize(double x0, double x1, double y0, double y1) {
		this.ph_x0 = x0;
		this.ph_x1 = x1;
		this.ph_y0 = y0;
		this.ph_y1 = y1;
		
		PAffineTransform tran = new PAffineTransform(); // identity

		double w = x1 - x0;
		
		double h = y1 - y0;
		
		double sx = phaseCamera.getWidth() / w;
		double sy = -phaseCamera.getHeight() / h;
		double tx = (-x0/w)*phaseCamera.getWidth();
		double ty = (-y0/h)*phaseCamera.getHeight();

		tran.translate(tx, ty);
		tran.scale(sx, sy);
		
		if( tran.getDeterminant() == 0 ) {
			
			// say what?
			resizePhasespace();
		} else {
			phaseCamera.setViewTransform(tran);
		}

	}
	
	public void resizePhasespace() {

		// AUTO-size
		double sx = 1.0;
		double sy = 1.0;
		double dx = data_xmax - data_xmin;

		PBounds bounds = phaseCamera.getBounds();
		if (dx > 0) {
			sx = bounds.width / (1.3 * dx);
		}
		double dy = data_ymax - data_ymin;
		if (dy > 0) {
			sy = bounds.height / (1.3 * dy);
		}
		PAffineTransform tran = new PAffineTransform(); // identity
		tran.translate(bounds.width / 2, bounds.height / 2);
		tran.scale(sx, -sy);
		double avg_x = (data_xmax + data_xmin) / 2;
		double avg_y = (data_ymax + data_ymin) / 2;
		tran.translate(-avg_x, -avg_y);
		
		if( tran.getDeterminant() == 0 ) {
			tran = new PAffineTransform();  // if I cant build a usable transform, then use an identity transform
		}
		phaseCamera.setViewTransform(tran);

	}


	public void setCentroidEventListener(PInputEventListener listener) {
		this.centroidEventListener = listener;
	}

}
