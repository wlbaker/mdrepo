/*
 * Created by JFormDesigner on Thu Mar 18 16:06:08 CDT 2010
 */

package idea.analysis;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Stroke;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.Path2D;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.DecimalFormat;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.SwingConstants;
import javax.swing.SwingWorker;
import javax.swing.SwingWorker.StateValue;
import javax.swing.border.CompoundBorder;
import javax.swing.border.TitledBorder;

import org.piccolo2d.PCamera;
import org.piccolo2d.PCanvas;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.extras.nodes.PLine;
import org.piccolo2d.nodes.PPath;
import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;
import org.rosuda.REngine.REngineException;
import org.rosuda.javaGD.JGDBufferedPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.intf.AdapterInterface;
import idea.schema.rp.RpAnalysis;
import j_experiments.RecurrencePlot;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.Stats;
import idea.buffer.CircularIntBuffer;
import idea.r.RCue;
import idea.r.RUtil;
import idea.tsoffline.LayerUtil;
import idea.tsoffline.canvas.PiccoUtil;
import idea.tsoffline.canvas.TimeseriesPropertiesPanel;
import idea.tsoffline.canvas.TsPSwingCanvas;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class AttractorAnalysisPanel extends JPanel {
	private BufferedImage phaseImage;
	private Color themed_bg;
	private PropertyChangeListener progressUpdateListener;
	private Collection<PNode> nodes;
	private int phase_width;
	private int phase_height;
	private boolean running;
	private PPath indicatorRect;
	private PLayer attractorLayer;

	private static final int DELAY = 4;
	private static final int PTS_TO_SHOW = 100;

	private final static Stroke pen = new BasicStroke(0, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);

	private DecimalFormat df2 = new DecimalFormat("0.00");

	private PCanvas attractorCanvas;
	private JGDBufferedPanel plotter;
	private JPanel imagePanel;
	private RecurrencePlot recur_plot = null;
	private int recur_trigger;
	private CircularIntBuffer rri_buffer;
	long study_sec = 0;
	private PLayer indicatorLayer;

	public AttractorAnalysisPanel() {
		initComponents();

		themed_bg = phasePanel.getBackground();
		log.error("FIXME: timeseries.setBackground(themed_bg);");

		indicatorRect = PPath.createRectangle(0, 0, 1000, 500);
		indicatorRect.setStroke(pen);
		indicatorRect.setStrokePaint(Color.BLUE);
		indicatorRect.setPaint(Color.GREEN);

		indicatorRect.setVisible( false );
		indicatorRect.setTransparency( 0.25f );
		// indicatorRect.setS
		
		indicatorLayer = new PLayer();
		indicatorLayer.addChild(indicatorRect);
		indicatorLayer.setName("::indicatorLayer");

		ComboBoxModel methodModel = new DefaultComboBoxModel(new Object[] { "Attractor", "Recurrence" });
		method.setModel(methodModel);
		method.setSelectedIndex(1);

		progressUpdateListener = new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {

				if ("state".equals(evt.getPropertyName())) {
					StateValue s = (StateValue) evt.getNewValue();

					System.out.println("property state: " + s);
					if (s == StateValue.STARTED) {
					}
					return;
				}

				if ("error".equals(evt.getPropertyName())) {
					Exception e = (Exception) evt.getNewValue();
					GuiUtil.showError("Visualization Error", e);
					return;
				}

				if ("time".equals(evt.getPropertyName())) {
					Long newTime = (Long) evt.getNewValue();
					// Long oldTime = evt.getOldValue();
					study_sec = newTime / 1000;
					long min = study_sec / 60;
					long sec = study_sec % 60;

					String t = String.format("%02d:%02d", min, sec);
					timeLabel.setText(t);

					// indicatorRect.setX(newTime);
					phasePanel.repaint();
					if (attractorCanvas != null) {
						attractorCanvas.repaint();
					}
					if (plotter != null) {
						plotter.repaint();
					}

					return;
				}

			}
		};

	}

	private void preparePopup(JPopupMenu popup) {

		JMenuItem properties = new JMenuItem("Properties");

		properties.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				propertiesActionPerformed();
			}
		});

		popup.addSeparator();
		popup.add(properties);

	}

	protected void propertiesActionPerformed() {

		TimeseriesPropertiesPanel panel = new TimeseriesPropertiesPanel(timeseries);
		GuiUtil.doDialog("Properties", this, panel, null);
	}

	public void connect(AdapterInterface[] producers, RpAnalysis analConfs) {

	}

	private void startActionPerformed(ActionEvent ae) {
		try {
			_startActionPerformed();
		} catch (Exception e) {
			GuiUtil.showError("Visualization Setup Error", e);

		}
	}

	private void _startActionPerformed() throws REngineException, REXPMismatchException {

		phase_width = phasePanel.getWidth();
		phase_height = phasePanel.getHeight();

		Insets insets = phasePanel.getInsets();
		phaseImage = new BufferedImage(phase_width, phase_height, BufferedImage.TYPE_INT_RGB);

		Graphics2D g = (Graphics2D) phaseImage.getGraphics();
		g.setColor(themed_bg);
		g.fillRect(0, 0, phase_width, phase_height);

		g.translate(insets.right, insets.top);
		phase_width -= (insets.left + insets.right);
		phase_height -= (insets.top + insets.bottom);

		boolean ok = initAttractorMethod();
		if (ok == false) {
			GuiUtil.showMessage("Select visualization method to continue.");
			return;
		}
		phasePanel.repaint();

		start.setEnabled(false);
		stop.setEnabled(true);

		SwingWorker<Integer, Void> worker = new SwingWorker<Integer, Void>() {

			@Override
			protected Integer doInBackground() throws Exception {
				running = true;

				drawPhaseDiagram(this);
				return 1;
			}

			@Override
			protected void done() {
				super.done();
				running = false;
				start.setEnabled(true);
				stop.setEnabled(false);
			}

		};

		worker.addPropertyChangeListener(progressUpdateListener);
		worker.execute();

	}

	protected boolean initAttractorMethod() throws REngineException, REXPMismatchException {
		int idx = method.getSelectedIndex();
		if (idx < 0) {
			return false;
		}

		String methodName = (String) method.getSelectedItem();

		attractorCanvas = null;
		recur_plot = null;

		// titledAttractorPanel.getremove( recurrencePlot );
		if (methodName.equals("R-Recur")) {
			initRPlot("recurrencePlot");
		} else if (methodName.equals("Recurrence")) {

			GuiUtil.showMessage("Need a parameter prompt here: m=2 nt=4, eps=32, n=1000");
			recur_plot = new RecurrencePlot(550, 550, 2, 1, 32, 4, 1000);
			recur_trigger = 1000;
			rri_buffer = new CircularIntBuffer(1000, true);
			imagePanel = new JPanel() {

				@Override
				public void paint(Graphics g) {
					super.paint(g);
					Image image = recur_plot.getImage();

					g.drawImage(image, 10, 10, imagePanel);
					g.dispose();
				}

			};

			titledAttractorPanel.add(imagePanel, BorderLayout.CENTER);

		} else if (methodName.equals("Attractor")) {
			plotter = null;
			attractorCanvas = new PCanvas();
			attractorCanvas.setBackground(themed_bg);

			PCamera cam = attractorCanvas.getCamera();
			attractorLayer = new PLayer();
			cam.addLayer(attractorLayer);
			titledAttractorPanel.add(attractorCanvas, BorderLayout.CENTER);
		} else {
			return false;
		}

		return true;
	}

	private void initRPlot(String plotName) throws REngineException, REXPMismatchException {
		RCue.parent = titledAttractorPanel;

		REngine engine = RUtil.getREngine();

		engine.parseAndEval(".setenv <- if (exists(\"Sys.setenv\")) Sys.setenv else Sys.putenv");
		// engine.eval(".setenv(\"JAVAGD_CLASS_NAME\"=\"idea/tsoffline/analysis/RCue\")");
		engine.parseAndEval(".setenv(\"JAVAGD_CLASS_NAME\"=\"idea/tsoffline/analysis/RCue\")");
		REXP v = engine.parseAndEval("library(JavaGD)");
		v = engine.parseAndEval("JavaGD(name=\"" + plotName + "\")");
		v = engine.parseAndEval("plot(rnorm(100))");

		plotter = RCue.plotter;
	}

	private void drawPhaseDiagram(SwingWorker<Integer, Void> worker) {
		try {
			_drawPhaseDiagram(worker);
		} catch (Exception e) {
			e.printStackTrace();
			worker.firePropertyChange("error", null, e);
		}
	}

	private void _drawPhaseDiagram(SwingWorker<Integer, Void> worker) throws REngineException, REXPMismatchException {

		int[] x = new int[DELAY + 1 + PTS_TO_SHOW];
		int pts = 0;

		Point2D gpt0 = new Point2D.Double(0, 2000); // 2*phase_height );
		Point2D gpt1 = new Point2D.Double(2000, 0);

		Rectangle2D.Double rect = new Rectangle2D.Double(0, 0, phase_width, phase_height);

		AffineTransform trans = LayerUtil.getTransformForLayer(rect, gpt0, gpt1, 0);
		Graphics2D g = (Graphics2D) phaseImage.getGraphics();

		g.setTransform(trans);
		long oldTime = 0;
		long newTime = 0;
		int pos = 0;

		Iterator<PNode> ii = nodes.iterator();
		while (ii.hasNext() && running) {

			worker.firePropertyChange("time", oldTime, newTime);
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			PNode n = ii.next();
			if (n instanceof PPath) {
				PPath pp = (PPath) n;

				float[] coords = new float[2];

				Path2D path = pp.getPathReference();
				PathIterator it = path.getPathIterator(null);

				while (!it.isDone()) {
					it.next();

					if (!it.isDone()) {
						it.currentSegment(coords);
						for (int i = x.length - 1; i > 0; i--) {
							x[i] = x[i - 1]; // the 0-the point is always the
							// most recent
						}

						x[0] = (int) coords[1];
						newTime += x[0]; // increment by RRI

						if (attractorCanvas != null) {
							updateAttractor(pos++, x[0]);
						} else if (recur_plot != null) {
							updateRecurPlot(pos++, coords[0], x[0]);
						} else {
							updateRRecur(pos++, x[0]);
						}

						// y[0] = (int)coords[1];

						if (pts > 3) {
							int tot_pts = Math.min(pts, PTS_TO_SHOW);
							g.setColor(Color.BLUE); // erase last point
							for (int i = tot_pts; i >= 0; i--) {
								g.drawLine(x[i], x[i + DELAY - 1], x[i + 1], x[i + DELAY]);
								if (i == tot_pts) {
									g.setColor(Color.WHITE); // draw rest of
									// points in
									// white
								}
							}
						}
						pts++;
					}
				}
			}

		}
	}

	private void stopActionPerformed(ActionEvent e) {
		running = false;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		timeseries = new idea.tsoffline.canvas.TsPSwingCanvas();
		panel1 = new JPanel();
		titledPhaseBox = new JPanel();
		phasePanel = new JPanel() {
			@Override     
			public void paintComponent(Graphics g) {
			    if( phaseImage == null ) {
			        super.paintComponent(g);
			    } else {
		 		    g.drawImage(phaseImage, 0, 0, null);
		        }
			} 

		};
		titledAttractorPanel = new JPanel();
		panel2 = new JPanel();
		start = new JButton();
		stop = new JButton();
		label1 = new JLabel();
		method = new JComboBox();
		timeLabel = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setPreferredSize(new Dimension(680, 500));
		setLayout(new FormLayout(
			"default:grow",
			"2*(fill:[100dlu,default]:grow, $lgap), default"));

		//---- timeseries ----
		timeseries.setBackground(new Color(212, 208, 200));
		timeseries.setBorder(new CompoundBorder(
			new TitledBorder("Signal RRI"),
			null));
		add(timeseries, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[100dlu,default]:grow, $lcgap, [100dlu,default]:grow",
				"fill:default:grow"));

			//======== titledPhaseBox ========
			{
				titledPhaseBox.setBorder(new TitledBorder("Phase Diagram"));
				titledPhaseBox.setLayout(new BorderLayout());

				//======== phasePanel ========
				{
					phasePanel.setLayout(new BorderLayout());
				}
				titledPhaseBox.add(phasePanel, BorderLayout.CENTER);
			}
			panel1.add(titledPhaseBox, cc.xy(1, 1));

			//======== titledAttractorPanel ========
			{
				titledAttractorPanel.setBorder(new TitledBorder("Attractor"));
				titledAttractorPanel.setLayout(new BorderLayout());
			}
			panel1.add(titledAttractorPanel, cc.xy(3, 1));
		}
		add(panel1, cc.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"3*([50dlu,default], $lcgap), [70dlu,default], $lcgap, right:default:grow, $lcgap, [40dlu,default]",
				"default"));

			//---- start ----
			start.setText("Start");
			start.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					startActionPerformed(e);
				}
			});
			panel2.add(start, cc.xy(1, 1));

			//---- stop ----
			stop.setText("Stop");
			stop.setEnabled(false);
			stop.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					stopActionPerformed(e);
				}
			});
			panel2.add(stop, cc.xy(3, 1));

			//---- label1 ----
			label1.setText("Method:");
			label1.setHorizontalAlignment(SwingConstants.TRAILING);
			panel2.add(label1, cc.xy(5, 1));
			panel2.add(method, cc.xy(7, 1));

			//---- timeLabel ----
			timeLabel.setText("00:00");
			timeLabel.setHorizontalAlignment(SwingConstants.TRAILING);
			panel2.add(timeLabel, cc.xy(11, 1));
		}
		add(panel2, cc.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private TsPSwingCanvas timeseries;
	private JPanel panel1;
	private JPanel titledPhaseBox;
	private JPanel phasePanel;
	private JPanel titledAttractorPanel;
	private JPanel panel2;
	private JButton start;
	private JButton stop;
	private JLabel label1;
	private JComboBox method;
	private JLabel timeLabel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	private float currCogX;
	private float currCogY;
	private float y0, y1, ym1, ym2, ym3, ym4;

	@SuppressWarnings("unchecked")
	public void setRRILayer(PLayer rri_layer) {
		PCamera cam = timeseries.getSignalCamera();

		while (cam.getLayerCount() > 0) {
			cam.removeLayer(0);
		}

		// add indicator layer underneath rri layer
		cam.addLayer(rri_layer);
		cam.addLayer(indicatorLayer);
		indicatorLayer.setVisible( true );

		rri_layer.setVisible(true);

		timeseries.reset();

		nodes = rri_layer.getChildrenReference();
		
		// all layers were removed above...need to add indicator back!

	}

	public static void createDummy(PLayer layer) {

		int n = 100;
		double[] x = new double[n];
		double[] y = new double[n];

		createSpiral(x, y, n);

		PLine p = PiccoUtil.createPolyline(x, y);
		p.setStroke(pen);
		// p.setPaint( Color.RED );
		p.setStrokePaint(Color.BLACK);
		layer.addChild(p);
		layer.setVisible(true);

	}

	private void updateRecurPlot(int pos, double xx, int rri) {
		rri_buffer.addData(rri);

		if (recur_trigger <= 0) {
			double[] x = rri_buffer.asDoubles();
			recur_plot.isr_recurrencePlot(x);
			imagePanel.repaint();

			recur_trigger += 20;

			double msWidth = Stats.sum(x);
			double ind_x = xx - msWidth;
			System.out.println("setting xx=" + xx + " ind_x=" + ind_x + " width=" + msWidth);
			indicatorRect.setX(ind_x);
			indicatorRect.setWidth(msWidth);
			indicatorRect.setHeight(5000);
			indicatorRect.setY(-1000);
			indicatorRect.setVisible(true);

			indicatorRect.repaint();
		}

		recur_trigger--;
	}

	private void updateRRecur(int i, int j) throws REngineException, REXPMismatchException {
		REngine eng = RUtil.getREngine();

		double[] data = new double[512];
		eng.assign("rri", data);
		eng.parseAndEval("plot( rnorm(100) )");
	}

	@SuppressWarnings("unchecked")
	private void updateAttractor(int pos, double signal) {

		float y2 = (float) signal;

		// {Draw Attractor}
		if (pos > 6) { // six is the size of the y array

			float ax1 = y0;
			float ax2 = y1;
			float ay1 = ym4;
			float ay2 = ym3;

			PPath line = PPath.createLine(ax1, ay1, ax2, ay2);
			line.setStroke(pen);
			line.setStrokePaint(Color.ORANGE);

			attractorLayer.addChild(line);
			List<PPath> nodeList = attractorLayer.getChildrenReference();
			if (nodeList.size() > 512) {
				attractorLayer.removeChild(nodeList.get(0));
			}

			//
			// section on center-of-gravity and scaling
			//

			double maxX = 0;
			double minX = 0;
			double maxY = 0;
			double minY = 0;
			double scale = 99;

			float cogX = 0; // COG --> Center of Gravity
			float cogY = 0;
			int tot = 0;

			do {
				PPath p = nodeList.get(tot++);
				maxX = p.getX();
				minX = p.getX();
				maxY = p.getY();
				minY = p.getY();
			} while (minX == 0 && tot < nodeList.size() - 1); // this will
			// happen if
			// both ends of
			// the line are
			// the same
			// point

			tot = 0;

			for (PPath path : nodeList) {

				if (path.getX() == 0 || path.getY() == 0) {
					// this will happen if both ends of the line are the same
					// point
				} else {
					if (path.getX() > maxX) {
						maxX = path.getX();
					} else if (path.getX() < minX) {
						minX = path.getX();
					}
					if (path.getY() > maxY) {
						maxY = path.getY();
					} else if (path.getY() < minY) {
						minY = path.getY();
					}

					cogX += path.getX();
					cogY += path.getY();
					tot++;
				}

			}

			cogX /= tot;
			cogY /= tot;

			double x_scale;
			double y_scale;

			if (maxX == minX || maxY == minY) {
				// can't auto-scale
			} else {
				x_scale = 200.0 / (maxX - minX);
				y_scale = 200.0 / (maxY - minY);
				scale = Math.min(x_scale, y_scale);
				scale /= 2; // WLB!!!
			}

			double actual_scale = scale;

			if (scale > 1.0f) {
				scale = 1.0f;
			}

			// System.out.print( "adding point (" + ax1 + "," + ay1 + ") (" +
			// ax2 + "," + ay2 + ")" );
			if (Math.abs(cogX - currCogX) > 20 || Math.abs(cogY - currCogY) > 20) {
				double width = maxX - minX;
				double height = maxY - minY;
				double r = Math.max(width, height);

				Point2D gpt0 = new Point2D.Double(cogX - r / 2, cogY + r / 2);
				Point2D gpt1 = new Point2D.Double(cogX + r / 2, cogY - r / 2);
				PCamera cam = attractorCanvas.getCamera();
				AffineTransform m = LayerUtil.getTransformForLayer(cam.getBounds(), gpt0, gpt1, 4.0);

				System.out.print(" max=(" + (int) maxX + "," + (int) maxY + ")");
				System.out.print(" min=(" + (int) minX + "," + (int) minY + ")");
				System.out.print(" scale=" + df2.format(scale) + " cog=" + df2.format(cogX) + "," + df2.format(cogY));
				// AffineTransform m = new PAffineTransform();
				// m.scale(scale, scale);
				// m.translate(-cogX + 200 / scale, -cogY + 140 / scale);
				cam.setViewTransform(m);
				// drawBorder(isolatedAttractor);
				currCogX = cogX;
				currCogY = cogY;
			}

			Color lineColor = new Color(255, (int) (240 - 200 * scale * scale), 40, 40);
			if (actual_scale > 4.0) {
				int gb = (int) (40 + (actual_scale - 4) * 100);
				if (gb > 255) {
					gb = 255;
				}
				lineColor = new Color(255, gb, gb / 2, 20);
			}
			line.setPaint(lineColor);
		}

		ym4 = ym3;
		ym3 = ym2;
		ym2 = ym1;
		ym1 = y0;
		y0 = y1;
		y1 = y2;
	}

	private static void createSpiral(double[] x, double[] y, int tot) {
		for (int i = 0; i < tot; i++) {
			double r = (Math.exp(i / 30.0));

			x[i] = r * Math.sin(i) + 100;
			y[i] = r * Math.cos(i) + 100;
		}
	}

}
