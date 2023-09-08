/*
 * Created by JFormDesigner on Wed Nov 18 03:08:13 CST 2009
 */

package idea.tsoffline.canvas;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.geom.Point2D;
import java.awt.image.BufferedImage;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.StringReader;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JToggleButton;
import javax.swing.JToolBar;
import javax.swing.border.LineBorder;
import javax.swing.filechooser.FileFilter;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.activities.PActivity;
import org.piccolo2d.activities.PActivity.PActivityDelegate;
import org.piccolo2d.extras.event.PNotification;
import org.piccolo2d.extras.event.PNotificationCenter;
import org.piccolo2d.util.PAffineTransform;
import org.piccolo2d.util.PBounds;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.display.ImageSelection;
import idea.model.DisplayConfig;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.ts.TsCode;
import idea.ts.TsoAnnotationEntryType;
import idea.ts.TsoPhase;
import idea.ts.TsoPrefs;
import idea.tsoffline.AppFrame;
import idea.tsoffline.AppModel;
import idea.tsoffline.AppUtil;
import idea.tsoffline.ColorManager;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.event_editor.PhaseEditorPanel;
import idea.tsoffline.event_editor.SingleEventPanel;
import idea.tsoffline.lib.swing.ClosableTabbedPaneUI;
import idea.tsoffline.model.D;
import idea.tsoffline.tspico.AnnotationEditorTool;
import idea.tsoffline.tspico.LegendTool;
import idea.tsoffline.util.AutocorrectOptionPanel;
import idea.tsoffline.util.OpenFileFilter;
import idea.tsoffline.video.TsPhaseSpaceCanvas;
import idea.tsoffline.vizwiz.RPlotterPanel;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class TsControlPanel extends JPanel implements PropertyChangeListener, PActivityDelegate {

	ClosableTabbedPaneUI tabberUI;

	int absPos = 0;
	// private MeasureUnit msUnit = new LinearUnit(1.0, 0.0, "ms");
	private TsPSwingCanvas timeseriesCanvas1;
	private TsBaseCanvas current_canvas;

	PNode annotationNode; // temporarily valid while annotationPopupMenu is
							// displayed
	boolean didAnnotationPopupInit = false;
	private PCamera camera_when_popup;

	LegendTool legendTool;
	JToggleButton plus;

	ArrayList<Component> ext_graphs = new ArrayList();
	private long prev_option_refresh_tm = -1;
	private long tmLastOptionsUpdate;

	JMenu graphTimeMenu = new JMenu("Graph Time Format...");
	JMenu timelineMenu = new JMenu("Timeline Time Format...");
	JMenuItem splitMI = new JMenuItem("Split for Calibration");
	JMenuItem eventMI = new JMenuItem("Add Event");
	JMenuItem phaseMI = new JMenuItem("Add Study Phase");
	// JMenuItem filterMI = new JMenuItem("Formulas and Filters...");
	JMenuItem autoCorrectMI = new JMenuItem("Auto-Adjust");
	JMenuItem updateMI = new JMenuItem("Check/Update");
	JMenuItem propertiesMI = new JMenuItem("Properties");
	private Point2D split_point = new Point2D.Double();

	PropertyChangeListener desalination = new PropertyChangeListener() {

		@Override
		public void propertyChange(PropertyChangeEvent evt) {
			LayerMultistateCheckBox cbox = (LayerMultistateCheckBox) evt.getSource();
			PLayer layer = cbox.getLayer();
			AnnotationEditorTool annoEditor = timeseriesCanvas1.annotationEditorHandler;

			int cb_state = cbox.getSelectionState();
			if (cb_state == 0) {
				layer.setVisible(false);
			} else {
				layer.setVisible(true);
			}

			layer.addAttribute("@style", (cb_state == 3) ? "points" : "lines");

			if (cb_state == 0 || cb_state == 1 || cb_state == 3) {
				String editableName = annoEditor.getEditableLayerName();
				if (layer.getName().equals(editableName)) {
					annoEditor.setEditableLayerName(null);
				}
				timeseriesCanvas1._redrawAxisLayer();
				return;
			}

			// cb_state must be 2...
			Container parent = cbox.getParent();
			for (int cid = 0; cid < parent.getComponentCount(); cid++) {
				Object o = parent.getComponent(cid);
				if (o instanceof LayerMultistateCheckBox) {
					LayerMultistateCheckBox tcb = (LayerMultistateCheckBox) o;
					if (cbox != tcb) {
						// de-select edit indicator of all layers except myself
						if (tcb.getSelectionState() == 2) {
							tcb.setSelectionState(1);
						}
					}
				}
			}

			// let everyone know, it is me who you will edit
			annoEditor.setEditableLayerName(layer.getName());
			timeseriesCanvas1._redrawAxisLayer(); // redraw the annotation layer

		}

	};

	private JCheckBoxMenuItem timeRel;

	private JCheckBoxMenuItem timeClock;

	private JCheckBoxMenuItem timeNone;

	private JCheckBoxMenuItem graphXRel;

	private JCheckBoxMenuItem graphXClock;

	private JCheckBoxMenuItem graphXNone;

	public TsControlPanel() {
		initComponents();
		initTimeseriesCanvas();
		initMajorPopupMenu();
		initMinorPopupMenu(minorPopupMenu, null);

		legendTool = (LegendTool) timeseriesCanvas1.getLegendHandler();
		// have to delay this until settings are loaded
		// initAnnotationPopupMenu();
		initPopupHandler(timeseriesCanvas1);
		initKeyListener();

		setName("tsControlPanel");

		featureMax.setEnabled(false);
		featureMin.setEnabled(false);
		featureExact.setEnabled(false);

		addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent e) {
				doLayout(); // hmm...this seems to be compensating for a swing
							// bug?
			}
		});

		timeseriesCanvas1.addPropertyChangeListener(TsPSwingCanvas.ACTIVE_LAYER_PROPERTY, new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				boolean has_active_layer = (evt.getNewValue() != null);
				featureMax.setEnabled(has_active_layer);
				featureMin.setEnabled(has_active_layer);
				featureExact.setEnabled(has_active_layer);
			}

		});

		timeseriesCanvas1.addPropertyChangeListener(TsBaseCanvas.ADD_ANNOTATION_PROPERTY, new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				refreshAnnotationLayerIndicators();
			}
		});

		layerSelectionPanel.removeAll();
		layerSelectionPanel.add(plus = new JToggleButton("+"));
		plus.setToolTipText("Add Annotation Layer");
		plus.addActionListener(e -> addLayerActionPerformed(e));

		LabelType lt = LabelType.fromString(PrefUtil.getUserPref("graphx", "Inline"));
		timeseriesCanvas1.setGraphLabelFormat(lt);
		selectWhich(lt, graphXClock, graphXRel, graphXNone);

		lt = LabelType.fromString(PrefUtil.getUserPref("time", "Inline"));
		timeseriesCanvas1.setTimelineLabelFormat(lt);
		selectWhich(lt, timeClock, timeRel, timeNone);

		timeseriesCanvas1.addPActivityListener(this);
		buttonAN.setEnabled(false);
		optionsPanel.setVisible(false);

		if (AppModel.isBeta()) {
			pasteFromClipboard.setEnabled(true);
		}
	}

	private void initMinorPopupMenu(JPopupMenu popup, JComponent plot) {
		// ---- detach or remove ----
		JMenuItem detachPlot = new JMenuItem();
		detachPlot.setText("Detach Plot");
		detachPlot.setEnabled(true);
		detachPlot.addActionListener(e -> detachPlotActionPerformed(e));
		detachPlot.putClientProperty("plot", plot);
		popup.add(detachPlot);

		JMenuItem removePlot = new JMenuItem();
		removePlot.setText("Remove Plot");
		removePlot.setEnabled(true);
		removePlot.addActionListener(e -> removePlotActionPerformed(e));
		removePlot.putClientProperty("plot", plot);
		popup.add(removePlot);

	}

	private void selectWhich(LabelType lt, JCheckBoxMenuItem clock, JCheckBoxMenuItem rel, JCheckBoxMenuItem none) {

		if (lt == LabelType.LABEL_CLOCKTIME)
			clock.setSelected(true);
		if (lt == LabelType.LABEL_REL_MMSS)
			rel.setSelected(true);
		if (lt == LabelType.LABEL_REL_SECS)
			none.setSelected(true);
	}

	private void addLayerActionPerformed(ActionEvent e) {
		AddAnnotationLayerPanel panel = new AddAnnotationLayerPanel();

		Object[] options = new Object[] {};

		JOptionPane op = new JOptionPane(panel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options);

		JDialog dlg = op.createDialog(this, "Add Annotation Layer");
		GuiUtil.initModalDialog(dlg, panel);
		dlg.setResizable(true);
		dlg.setVisible(true);

		if (panel.isFinished()) {
			PLayer layer = panel.apply( timeseriesCanvas1 );

			AnnotationEditorTool annoEditor = timeseriesCanvas1.annotationEditorHandler;
			annoEditor.setEditableLayerName(layer.getName());
		}
		refreshAnnotationLayerIndicators();
	}

	private void refreshAnnotationLayerIndicators() {
		layerSelectionPanel.removeAll();

		Dimension dd = new Dimension(27, 19);

		AnnotationEditorTool annoEditor = timeseriesCanvas1.annotationEditorHandler;
		String editableName = annoEditor.getEditableLayerName();
		JToggleButton selected = null;
		
		TsPSwingCanvas canv = this.getCanvas1();

		List<HPSplitableLayer> annos = canv.getAnnotationModel();
		for (HPSplitableLayer anno : annos) {
			if (anno.getName() == null) {
				// no layer data? ignore!
				log.error("NO NAME FOR ANNOTATION LAYER: IGNORING LAYER");
				continue;
			}
			LayerMultistateCheckBox layer_button = new LayerMultistateCheckBox(anno);
			layer_button.addPropertyChangeListener("SelectionState", desalination);
			// layer_button.setIcon(createIcon(anno.getColor()));
			layer_button.setToolTipText(anno.getName());
			// layer_button.putClientProperty("signal", anno);
			// layer_button.setPreferredSize(d);
			// layer_button.setSelected(false);
			layerSelectionPanel.add(layer_button);

			// 19FEB17 Don't set edit mode...unless this is the editable
			// layer...its probably stored in the layer
			if (anno.getName().equals(editableName)) {
				layer_button.setSelectionState(2);
				// } else if (!anno.getLayer().getVisible()) {
				// layer_button.setSelectionState(1);
				// } else {
				// layer_button.setSelectionState(0);
			}
		}
		plus.setPreferredSize(dd);
		layerSelectionPanel.add(plus);

		if (selected != null) {
			selected.setSelected(true);
		}
		layerSelectionPanel.validate();
	}

	private void initPopupHandler(TsBaseCanvas canvas) {
		canvas.addMouseListener(new MouseAdapter() {

			private void showPopup(MouseEvent evt) {
				current_canvas = canvas;
				if (canvas instanceof TsPSwingCanvas) {
					showMajorPopupMenu(evt);
				} else {
					showMinorPopupMenu(evt);
				}
			}

			private void showMinorPopupMenu(MouseEvent evt) {
				camera_when_popup = canvas.getCameraAtMousePos();
				minorPopupMenu.show(evt.getComponent(), evt.getX(), evt.getY());
			}

			private void showMajorPopupMenu(MouseEvent evt) {
				camera_when_popup = canvas.getCameraAtMousePos();
				AnnotationEditorTool annoEditor = canvas.annotationEditorHandler;
				if (annoEditor != null) {
					annotationNode = annoEditor.getAnnotationAtMousePos(canvas.getMousePosition());
					if (annotationNode != null) {
						initAnnotationPopupMenu();
						annotationOptionsMenu.show(evt.getComponent(), evt.getX(), evt.getY() + 10);
						return;
					}
				}

				if (timeseriesCanvas1.isCalibration()) {
					PLayer active = timeseriesCanvas1.getActiveLayer();
					splitMI.setVisible(active != null);

					PCamera split_cam = timeseriesCanvas1.getCameraAtMousePos();

					if (split_cam != null) {
						Point2D mouse_pos = getMousePosition();
						if (mouse_pos != null) {
							PAffineTransform trans = split_cam.getViewTransform();
							Point data_pos = new Point();
							trans.inverseTransform(mouse_pos, split_point);
						}
					}

					graphTimeMenu.setVisible(false);
					timelineMenu.setVisible(false);
					eventMI.setVisible(false);
					phaseMI.setVisible(false);
					// filterMI.setVisible(false);
					autoCorrectMI.setVisible(false);
					updateMI.setVisible(false);
				} else {
					splitMI.setVisible(false);

					graphTimeMenu.setVisible(true);
					timelineMenu.setVisible(true);
					eventMI.setVisible(true);
					phaseMI.setVisible(true);
					// filterMI.setVisible(true);
					autoCorrectMI.setVisible(true);
					updateMI.setVisible(true);
				}

				PCamera cam0 = canvas.getCameraAtMousePos();
				if (cam0 != null) {
					// must be a canvas...
					majorPopupMenu.show(evt.getComponent(), evt.getX(), evt.getY());
					return;
				}
			}

			/*
			 * Different L&F environments and OS may trigger popup on either pressed or
			 * released...either way, isPopupTrigger() is set correctly to the OS and
			 * L&F...so rely on it to determine when to show the popup.
			 */
			@Override
			public void mousePressed(MouseEvent evt) {
				if (evt.isShiftDown())
					return;
				if (evt.isControlDown())
					return;
				if (evt.isPopupTrigger()) {
					showPopup(evt);
				}
			}

			@Override
			public void mouseReleased(MouseEvent evt) {
				if (evt.isShiftDown())
					return;
				if (evt.isControlDown())
					return;
				if (evt.isPopupTrigger()) {
					showPopup(evt);
				}
			}

		});

	}

	private void initAnnotationPopupMenu() {
		if (didAnnotationPopupInit) {
			return;
		}
		didAnnotationPopupInit = true;
		ActionListener codeListener = new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				String code = e.getActionCommand();
				TsoAnnotationEntryType entry = (TsoAnnotationEntryType) annotationNode.getAttribute("item");
				entry.setCode(code);
				annotationNode.addAttribute("txt", code);
				timeseriesCanvas1.redrawAxisLayer(0);
			}

		};

		List<TsCode> codes = AppFrame.getInstance().getCodeModel();
		for (TsCode code : codes) {
			String desc = code.getDescription();
			if (desc == null || desc.length() == 0) {
				desc = code.getCode();
			}
			JMenuItem item = new JMenuItem(desc);
			item.setActionCommand(code.getCode());
			item.addActionListener(codeListener);
			annotationOptionsMenu.add(item);
		}
	}

	private void initMajorPopupMenu() {
		splitMI.setEnabled(true);
		splitMI.addActionListener(e -> splitLayerForCalibrationActionPerformed(e));

		timeRel = new JCheckBoxMenuItem("Clock");
		timeClock = new JCheckBoxMenuItem("Relative (HH:MM)");
		timeNone = new JCheckBoxMenuItem("Relative (sec)");
		ButtonGroup buttonGroup1 = new ButtonGroup();
		buttonGroup1.add(timeRel);
		buttonGroup1.add(timeClock);
		buttonGroup1.add(timeNone);

		graphXRel = new JCheckBoxMenuItem("Clock");
		graphXClock = new JCheckBoxMenuItem("Relative (HH:MM)");
		graphXNone = new JCheckBoxMenuItem("Relative (sec)");
		// ---- buttonGroup1 ----
		ButtonGroup buttonGroup2 = new ButtonGroup();
		buttonGroup2.add(graphXRel);
		buttonGroup2.add(graphXClock);
		buttonGroup2.add(graphXNone);

		graphTimeMenu.setMnemonic('T');
		graphTimeMenu.add(graphXRel);
		graphTimeMenu.add(graphXClock);
		graphTimeMenu.add(graphXNone);

		timelineMenu.setMnemonic('T');
		timelineMenu.add(timeRel);
		timelineMenu.add(timeClock);
		timelineMenu.add(timeNone);

		eventMI.addActionListener(e -> addEventActionPerformed());
		phaseMI.addActionListener(e -> addPhaseActionPerformed());
		// filterMI.addActionListener(e -> formulaActionPerformed());
		propertiesMI.addActionListener(e -> propertiesActionPerformed());
		autoCorrectMI.addActionListener(e -> autoCorrectActionPerformed());
		updateMI.addActionListener(e -> updateActionPerformed());

		graphXRel.addActionListener(e -> {
			PrefUtil.saveUserPref("graphx", "ClockTime");
			timeseriesCanvas1.setGraphLabelFormat(LabelType.LABEL_CLOCKTIME);
		});
		graphXClock.addActionListener(e -> {
			PrefUtil.saveUserPref("graphx", "Relative MMSS");
			timeseriesCanvas1.setGraphLabelFormat(LabelType.LABEL_REL_MMSS);
		});
		graphXNone.addActionListener(e -> {
			PrefUtil.saveUserPref("graphx", "Relative Secs");
			timeseriesCanvas1.setGraphLabelFormat(LabelType.LABEL_REL_SECS);
		});

		timeRel.addActionListener(e -> {
			PrefUtil.saveUserPref("time", "ClockTime");
			timeseriesCanvas1.setTimelineLabelFormat(LabelType.LABEL_CLOCKTIME);
		});
		timeClock.addActionListener(e -> {
			PrefUtil.saveUserPref("time", "Relative MMSS");
			timeseriesCanvas1.setTimelineLabelFormat(LabelType.LABEL_REL_MMSS);
		});
		timeNone.addActionListener(e -> {
			PrefUtil.saveUserPref("time", "Relative Secs");
			timeseriesCanvas1.setTimelineLabelFormat(LabelType.LABEL_REL_SECS);
		});

		majorPopupMenu.addSeparator();
		majorPopupMenu.add(splitMI);
		majorPopupMenu.add(eventMI);
		majorPopupMenu.add(phaseMI);
		// majorPopupMenu.add(filterMI);
		majorPopupMenu.addSeparator();
		majorPopupMenu.add(graphTimeMenu);
		majorPopupMenu.add(timelineMenu);

		majorPopupMenu.add(autoCorrectMI);
		majorPopupMenu.add(updateMI);
		majorPopupMenu.add(propertiesMI);

	}

	private void initKeyListener() {
		timeseriesCanvas1.addKeyListener(new KeyListener() {

			@Override
			public void keyPressed(KeyEvent e) {
				processKeyPressed(e);

			}

			@Override
			public void keyReleased(KeyEvent e) {
				// processKeyPressed(e);
			}

			@Override
			public void keyTyped(KeyEvent e) {
			}
		});

	}

	protected void processKeyPressed(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_E) {
			e.consume();
			addEventActionPerformed();
		} else if (e.getKeyCode() == KeyEvent.VK_PRINTSCREEN) {
			// copyImageActionPerformed();
			saveImageActionPerformed(null);
			e.consume();
		}
	}

	private void initTimeseriesCanvas() {
		CellConstraints cc = new CellConstraints();
		timeseriesCanvas1 = new TsPSwingCanvas();
		timeseriesCanvas1.setName("timeseriesCanvas1-in-tsControl");
		// ---- timeseriesCanvas1 ----
		timeseriesCanvas1.setBorder(LineBorder.createBlackLineBorder());
		timeseriesCanvas1.setBackground(new Color(212, 208, 200));
		// add(timeseriesCanvas1, cc.xy(1, 1));
		add(timeseriesCanvas1, BorderLayout.CENTER);

		PNotificationCenter.defaultCenter().addListener( //
				this, "legendProperties", LegendTool.LEGEND_PROPERTIES_NOTIFICATION, //
				legendTool);

	}

	/*
	 * DO NOT DELETE...this method referenced by name in listener above
	 */
	public void legendProperties(PNotification notfication) {
		// LegendTool tool = (LegendTool) notfication.getObject();

		propertiesActionPerformed();
	}

	protected void propertiesActionPerformed() {

		TimeseriesPropertiesPanel panel = new TimeseriesPropertiesPanel(timeseriesCanvas1);
		GuiUtil.doDialog("Timeseries Properties", this, panel, null);

		redraw();
	}

	private void addEventActionPerformed() {

		TsoAnnotationEntryType event = new TsoAnnotationEntryType();
		event.setTm(new Date(timeseriesCanvas1.getMouseMillisecondPosition()));

		SingleEventPanel panel = new SingleEventPanel(getCanvas1(), event);

		Object[] options = new Object[] {};

		JOptionPane op = new JOptionPane(panel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options);

		JDialog dlg = op.createDialog(this, "Add Event");
		GuiUtil.initModalDialog(dlg, panel);
		dlg.setResizable(true);
		dlg.getRootPane().setDefaultButton(panel.getOKButton());
		dlg.setVisible(true);

		if (panel.isOk()) {
			HPSplitableLayer anno = panel.getCachedSignal();

			AppModel.addAnnotation(anno, event, true);
			timeseriesCanvas1.redrawAxisLayer(0); // force a refresh to redraw
													// events
		}

	}

	private void addPhaseActionPerformed() {

		TsoPhase phase = new TsoPhase();

		TsPSwingCanvas canv = timeseriesCanvas1;
		long t0 = canv.getStartTime();
		phase.setStartTm(new Date(t0 + canv.getViewStartTimeMs()));
		phase.setStopTm(new Date(t0 + canv.getViewEndTimeMs()));

		PhaseEditorPanel panel = new PhaseEditorPanel(phase, t0, canv.getGraphXLabelFormat());

		Object[] options = new Object[] {};

		JOptionPane op = new JOptionPane(panel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options);

		JDialog dlg = op.createDialog(this, "Add Study Phase");
		GuiUtil.initModalDialog(dlg, panel);
		dlg.setResizable(true);
		dlg.getRootPane().setDefaultButton(panel.getOKButton());
		dlg.setVisible(true);

		if (panel.isOk()) {

			AppModel.addAnnotation(getCanvas1().getPhaseLayer(), phase, true);
			timeseriesCanvas1.redrawAxisLayer(0); // force a refresh to redraw
													// events
		}

	}

	/**
	 * Split a layer into to parts to be calibrated separately.
	 */
	private void splitLayerForCalibrationActionPerformed(ActionEvent e) {
		PLayer active = (PLayer) timeseriesCanvas1.getActiveLayer();
		if (active == null) {
			return;
		}

		PLayer layer1 = splitLayerForCalibration(active, split_point.getX());

		if (layer1 != null) {
			HPSplitableLayer sig = (HPSplitableLayer) layer1.getAttribute("sig");
			timeseriesCanvas1.setActiveSignal(sig, layer1);

			AppModel.setDirty(true);
		}
	}

	public PLayer splitLayerForCalibration(PLayer data_layer, double split_pos) {
		PLayer revised;
		PLayer subset;

		Paint p = data_layer.getPaint();
		PCamera cam = null;
		HPSplitableLayer sig = null;
		if (data_layer.getCameraCount() > 0) {
			cam = data_layer.getCamera(0);
		}
		if (data_layer instanceof HPPathLayer) {
			if (cam != null)
				cam.removeLayer(data_layer);
			revised = new PLayer();
			revised.setName(data_layer.getName() + "!R");
			Enumeration ekeys = data_layer.getClientPropertyKeysEnumeration();
			while (ekeys.hasMoreElements()) {
				Object key = ekeys.nextElement();
				Object prop = data_layer.getAttribute(key);
				if ("sig".equals(key)) {
					sig = (HPSplitableLayer) prop;
					// sig.setLayer(revised);
				}
				revised.addAttribute(key, prop);
			}
			subset = data_layer;

			if (cam != null)
				cam.addLayer(revised);
		} else {
			revised = data_layer;
			subset = timeseriesCanvas1.getActiveSegment();

			revised.removeChild(subset);
			sig = (HPSplitableLayer) revised.getAttribute("sig");
		}

		if (sig == null) {
			log.error("Internal Error: Could not find signal.");
			return null;
		}

		PLayer[] layer = splitDataIntoTwoLayers(subset, split_pos);
		//layer[0].addAttribute("sig", sig);
		//layer[1].addAttribute("sig", sig);

		layer[0].setName(subset.getName() + "#1");
		layer[1].setName(subset.getName() + "#2");

		layer[0].setPaint(p);
		layer[1].setPaint(p);

		// debug dump(layer[0]);
		// debug dump(layer[1]);

		subset.removeAllChildren();

		List<PLayer> children = revised.getChildrenReference();
		boolean added = false;
		for (int i = 0; i < children.size(); i++) {
			PLayer curr = children.get(i);
			double pos = curr.getChild(0).getX();
			if (layer[0].getX() < pos) {
				children.add(i, layer[0]);
				children.add(i + 1, layer[1]);
				added = true;
				break;
			}
		}
		if (!added) {
			revised.addChild(layer[0]);
			revised.addChild(layer[1]);
		}

		return layer[1];
	}

	private void dump(PLayer layer) {
		System.out.println("dumping layer info: " + layer.getName() + " child count=" + layer.getChildrenCount());
		for (int i = 0; i < 20 && i < layer.getChildrenCount(); i++) {
			PNode node = layer.getChild(i);
			System.out.println("  " + i + " x=" + node.getX() + " class=" + node.getClass());

		}
	}

	private PLayer[] splitDataIntoTwoLayers(PLayer source, double dataPos) {

		// don't pass in sig here...it will reset the layer that sig points to
		PLayer layer1 = new HPPathLayer(null, null, "subset");
		PLayer layer2 = new HPPathLayer(null, null, "subset");

		layer1.setTransform(source.getTransform());
		layer2.setTransform(source.getTransform());

		Iterator<PNode> it = source.getChildrenReference().iterator();
		while (it.hasNext()) {
			PNode node = it.next();
			it.remove();
			if (node.getX() < dataPos) {
				layer1.addChild(node);
			} else {
				layer2.addChild(node);
			}
		}
		return new PLayer[] { layer1, layer2 };
	}

	protected void autoCorrectActionPerformed() {

		AutocorrectOptionPanel autoc = new AutocorrectOptionPanel(timeseriesCanvas1);

		PLayer active = timeseriesCanvas1.getActiveLayer();
		if (active != null) {
			autoc.setReferenceSignal((HPSplitableLayer) active.getAttribute("sig"));
		}
		GuiUtil.doDialog("AutoCorrect", this, autoc, null);
		if (autoc.isFinished()) {

			int dir = autoc.getDirection();
			int tol_ms = autoc.getTolerance();
			double tol_s = tol_ms / 1000.0;

			HPSplitableLayer ref = autoc.getSelectedReference();
			if (ref == null) {
				GuiUtil.showMessage("Could not find reference layer: null");
				return;
			}

			PLayer featureLayer = autoc.getFeatureLayer();
			if (featureLayer == null) {
				GuiUtil.showMessage("Could not find feature layer: ??");
				return;
			}

			timeseriesCanvas1.dumpFiducialNodes(featureLayer);

			log.error(
					"FIXME: the algorithm below will process nodes twice when a new node is inserted.  Iterator is perferable...but other routines have to be fixed for that to work.");
			for (int i = 0; i < featureLayer.getChildrenCount(); i++) { // this
																		// allows
																		// children
																		// to be
																		// added
																		// and
																		// removed
				PNode node = featureLayer.getChild(i);

				double x = node.getX();

				double min = (x - tol_s);
				double max = (x + tol_s);
				AnnotationEditorTool annoEditor = timeseriesCanvas1.annotationEditorHandler;
				annoEditor.joinNodesAndInsert(featureLayer, ref, dir, min, max, "R");
			}

			timeseriesCanvas1.redrawAxisLayer(0); // redraw after node changes
		}
	}

	protected void updateActionPerformed() {

		UpdatePanel panel = new UpdatePanel(getCanvas1());

		Object[] options = new Object[0];
		JOptionPane p = new JOptionPane(panel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null, options, null);
		JDialog d = p.createDialog(this, "Update Features");
		GuiUtil.initModalDialog(d, p); // makes the escape key work
		d.setResizable(true);
		d.pack();
		d.setVisible(true);

	}

	private void copyImageActionPerformed(ActionEvent e) {
		BufferedImage out = createScreenshot();
		ImageSelection.copyImageToClipboard(out);
	}

	private void saveImageActionPerformed(ActionEvent e) {
		BufferedImage out = createScreenshot();

		JFileChooser fc = new JFileChooser();
		FileFilter[] filters = fc.getChoosableFileFilters();
		for (FileFilter ff : filters) {
			fc.removeChoosableFileFilter(ff);
		}
		fc.addChoosableFileFilter(new OpenFileFilter("png", "PNG Image"));

		int returnVal = fc.showSaveDialog(AppFrame.getInstance());

		if (returnVal == JFileChooser.APPROVE_OPTION) {
			File file = fc.getSelectedFile(); // new File(f);
			try {
				ImageIO.write(out, "png", file);
			} catch (IOException e1) {
				throw new RuntimeException(e1); // let the global error handler
												// catch it
			}
		}

	}

	private BufferedImage createScreenshot() {
		JComponent p = timeseriesCanvas1;
		if (current_canvas != null) {
			p = current_canvas;
		}
		int w = p.getWidth();
		int h = p.getHeight();
		int type = BufferedImage.TYPE_INT_RGB;
		BufferedImage out = new BufferedImage(w, h, type);
		Graphics2D g2 = out.createGraphics();
		p.paint(g2);
		g2.dispose();

		return out;
	}

	private void copyDataActionPerformed(ActionEvent e) {

		List<PLayer> layers = null;
		PCamera cam;
		{
			PLayer layer = timeseriesCanvas1.getActiveLayer();
			if (layer == null) {
				cam = timeseriesCanvas1.getCameraAtMousePos();
				if (cam == null) {
					cam = timeseriesCanvas1.getSignalCamera();
				}
				layers = cam.getLayersReference();
			} else {
				cam = layer.getCamera(0);
				layers = new LinkedList<PLayer>();
				layers.add(layer);
			}
		}

		PBounds r = cam.getViewBounds();
		double startX = r.getX();
		double endX = r.getX() + r.getWidth();

		List<String> cols = new LinkedList<String>();
		cols.add("TM");

		for (PLayer layer : layers) {
			HPSplitableLayer sig = (HPSplitableLayer) layer.getAttribute("sig");
			if (sig.getTyp() == TimeseriesType.TT_ANNOTATION) {
				Collection<PNode> nodes = getLayerNodesData(layer, startX, endX);
				copyNodesToClipboard(nodes);
			} else {
				cols.add(layer.getName());
			}
		}

		ArrayList<double[]> d = getLayerLineDataObsolete(cam, cols, startX, endX);
		copyListToClipboard(cols, d);

	}

	private void pasteFromClipboardActionPerformed(ActionEvent e) {
		Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
		Transferable transferable = clipboard.getContents(null);
		for (DataFlavor flavor : transferable.getTransferDataFlavors()) {
			System.out.println("DEBUG: flavor=" + flavor.getHumanPresentableName());
		}
		
		if (transferable != null && transferable.isDataFlavorSupported(DataFlavor.plainTextFlavor)) {
			StringReader reader = null;
			try {
				reader = (StringReader) transferable.getTransferData(DataFlavor.plainTextFlavor);
			} catch (UnsupportedFlavorException e1) {
				// handle this as desired
				e1.printStackTrace();
			} catch (IOException e2) {
				// handle this as desired
				e2.printStackTrace();
			}
			BufferedReader in = new BufferedReader(reader);
			try {
				int lineNo = 0;
				while (true) {
					String line = in.readLine();
					if (line == null)
						break;
					lineNo++;
					
					String[] arr = line.split("[,\t]");
					if( lineNo == 1 ) {
						// is this a column header?
						System.out.println("header line=" + line);
						continue;
					}
					
					// data...
					System.out.println("data line=" + line);
					
				}
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			// DataInputStream br = new DataInputStream(reader);
			// reader.re
			System.out.println("done");
		}
		return;
	}

	public Collection<PNode> getLayerNodesData(PLayer layer, double startX, double endX) {


		ArrayList<PNode> subset = new ArrayList<PNode>();
		D.getNodesInRange(subset, layer, startX, endX);

		return subset;
	}

	/*
	 * this routine just isn't flexible enough, but still might be used to extract
	 * data for RAnalysisExecutor
	 */
	@Deprecated
	public ArrayList<double[]> getLayerLineDataObsolete(PCamera cam, List<String> cols, double startX, double endX) {
		if (cols == null) {
			return null;
		}

		ArrayList<double[]> d = new ArrayList<double[]>();

		boolean first = true;
		for (String col : cols) {
			if (first) {
				// first column contains the name of the TM column...which is not a layer
				first = false;
				continue;
			}

			PLayer layer = null;
			for (int ii = 0; ii < cam.getLayerCount(); ii++) {
				PLayer l0 = cam.getLayer(ii);

				if (col.equals(l0.getName())) {
					layer = l0;
					break;
				}
			}

			if (layer == null) {
				log.error("Could not find named layer: {}", col);
				continue;
			}

			HPSplitableLayer sig = (HPSplitableLayer) layer.getAttribute("sig");
			RpUnit unit = (sig == null) ? null : sig.getUnit();


			double[][] dd = D.getValuesInRange(layer, startX, endX);
			log.error("FIXME: ASSUMING EQUALLY SPACED WF POINTS!");
			if (d.size() == 0) {
				d.add(dd[0]); // add TM column
			}
			int len = dd[0].length;
			double[] arr = dd[1];
			if (unit != null) {
				for (int ii = 0; ii < len; ii++) {
					arr[ii] = unit.transform_d(arr[ii]);
				}
			}
			d.add(arr);
		}

		return d;
	}

	private void copyListToClipboard(List<String> cols, List<double[]> d) {
		NumberFormat df3 = new DecimalFormat("0.000");
		Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();

		StringBuffer sbf = new StringBuffer();

		int pos = 0;
		for (String col : cols) {
			if (pos > 0)
				sbf.append("\t");
			sbf.append(col);
			pos++;
		}
		sbf.append("\n");

		double[] xx = d.get(0);
		int len = xx.length;
		for (int i = 0; i < len; i++) {

			appendOneValue(sbf, df3.format(xx[i]));
			for (int j = 1; j < d.size(); j++) {
				double[] yy = d.get(j);
				sbf.append("\t");
				if (i < yy.length) {
					// if one of the signals ends early...
					appendOneValue(sbf, "" + yy[i]);
				}
			}
			sbf.append("\n");
		}
		StringSelection stsel = new StringSelection(sbf.toString());
		clipboard.setContents(stsel, stsel);
	}

	private void copyNodesToClipboard(Collection<PNode> d) {
		NumberFormat df3 = new DecimalFormat("0.000");
		Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();

		StringBuffer sbf = new StringBuffer();
		sbf.append("TM\tIVL\n");

		Iterator<PNode> pii = d.iterator();
		while (pii.hasNext()) {
			PNode node = pii.next();
			Double x_val = node.getX();
			Double y_val = node.getY();
			Object q = node.getAttribute("q");
			Object dctor = node.getAttribute("dctor");
			Object lead = node.getAttribute("lead");

			appendOneValue(sbf, (x_val == null) ? null : df3.format(x_val));
			sbf.append("\t");
			appendOneValue(sbf, (y_val == null) ? null : "" + y_val);
			sbf.append("\t");

			if (q != null) {
				appendOneValue(sbf, q.toString());
			}
			sbf.append("\t");
			if (dctor != null) {
				appendOneValue(sbf, dctor.toString());
			}
			sbf.append("\t");
			if (lead != null) {
				appendOneValue(sbf, lead.toString());
			}

			sbf.append("\n");
		}
		StringSelection stsel = new StringSelection(sbf.toString());
		clipboard.setContents(stsel, stsel);
	}

	private void appendOneValue(StringBuffer sbf, String val) {
		if (val == null) {
			sbf.append(""); // empty string
		} else {
			sbf.append(val);
		}

	}

	void centerViewActionPerformed() {
		timeseriesCanvas1.centerView(timeseriesCanvas1.getCameraAtMousePos());
	}

	private void graphSplitActionPerformed(ActionEvent e) {
		AppModel.setDirty(true);
		timeseriesCanvas1.split(camera_when_popup);
	}

	private void graphJoinActionPerformed(ActionEvent e) {
		AppModel.setDirty(true);
		timeseriesCanvas1.join(camera_when_popup);
	}

	private void deleteAnnotationActionPerformed(ActionEvent e) {
		timeseriesCanvas1.deleteSelectedAnnotation();
	}

	private void featureMaxActionPerformed(ActionEvent e) {
		timeseriesCanvas1.setFeatureMode(1);
	}

	private void featureMinActionPerformed(ActionEvent e) {
		timeseriesCanvas1.setFeatureMode(-1);
	}

	private void featureExactActionPerformed(ActionEvent e) {
		timeseriesCanvas1.setFeatureMode(0);
	}

	private void buttonGraphParamsActionPerformed(ActionEvent e) {
		optionsPanel.setVisible(false);
		timeseriesCanvas1.setGraphParams(buttonGraphParams.isSelected());

		if (buttonGraphParams.isSelected() == false) {
			buttonExplore.setSelected(true);
		}
	}

	private void buttonIntersectionActionPerformed(ActionEvent e) {
		optionsPanel.setVisible(false);
		timeseriesCanvas1.setIntersection(buttonIntersection.isSelected());

		if (buttonGraphParams.isSelected() == false) {
			buttonExplore.setSelected(true);
		}
	}

	private void buttonCActionPerformed(ActionEvent e) {
		optionsPanel.setVisible(false);
		timeseriesCanvas1.setCalibration(buttonC.isSelected());

		if (buttonC.isSelected() == false) {
			buttonExplore.setSelected(true);
		}
	}

	private void buttonFiltersActionPerformed(ActionEvent e) {
		optionsPanel.setVisible(false);
		timeseriesCanvas1.setFilter(buttonFilters.isSelected());

		if (buttonFilters.isSelected() == false) {
			buttonExplore.setSelected(true);
		}
	}

	private void buttonANActionPerformed(ActionEvent e) {
		// timeseriesCanvas1.setAnAnalysis(buttonAN.isSelected());
		optionsPanel.setVisible(buttonAN.isSelected());
		if (buttonAN.isSelected() == false) {
			buttonExplore.setSelected(true);
		}
	}

	private void buttonExploreActionPerformed(ActionEvent e) {
		optionsPanel.setVisible(false);
		timeseriesCanvas1.setExplore(true);
		if (buttonExplore.isSelected() == false) {
			buttonExplore.setSelected(true);
		}
	}

	private void buttonB2BActionPerformed(ActionEvent e) {
		optionsPanel.setVisible(false);
		timeseriesCanvas1.setB2BAnalysis(buttonB2B.isSelected());
		if (buttonB2B.isSelected() == false) {
			buttonExplore.setSelected(true);
		}
	}

	private void buttonUnusedActionPerformed(ActionEvent e) {
		optionsPanel.setVisible(false);
		timeseriesCanvas1.setShowUnused(buttonUnused.isSelected());
		if (buttonUnused.isSelected() == false) {
			buttonExplore.setSelected(true);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		optionsPanel = new JPanel();
		toolBar1 = new JToolBar();
		featureMax = new JToggleButton();
		featureMin = new JToggleButton();
		featureExact = new JToggleButton();
		buttonExplore = new JToggleButton();
		buttonUnused = new JToggleButton();
		buttonGraphParams = new JToggleButton();
		buttonIntersection = new JToggleButton();
		buttonFilters = new JToggleButton();
		buttonC = new JToggleButton();
		buttonB2B = new JToggleButton();
		buttonAN = new JToggleButton();
		toolBar2 = new JToolBar();
		layerSelectionPanel = new JPanel();
		majorPopupMenu = new JPopupMenu();
		copyImage = new JMenuItem();
		saveImage = new JMenuItem();
		menu1 = new JMenu();
		menuItem2 = new JMenuItem();
		menuItem3 = new JMenuItem();
		menuItem4 = new JMenuItem();
		copyData = new JMenuItem();
		pasteFromClipboard = new JMenuItem();
		graphSplit = new JMenuItem();
		graphJoin = new JMenuItem();
		annotationOptionsMenu = new JPopupMenu();
		deleteAnnotation = new JMenuItem();
		minorPopupMenu = new JPopupMenu();
		copyImage2 = new JMenuItem();
		saveImage2 = new JMenuItem();
		copyData2 = new JMenuItem();

		//======== this ========
		setBorder(null);
		setLayout(new BorderLayout(4, 0));

		//======== optionsPanel ========
		{
			optionsPanel.setLayout(new FormLayout(
				"[100dlu,default]:grow",
				"6*(default, $lgap), fill:default:grow, 3*(default, $lgap), default"));
		}
		add(optionsPanel, BorderLayout.EAST);

		//======== toolBar1 ========
		{

			//---- featureMax ----
			featureMax.setToolTipText("CTRL-LMB: Select maximum around the cursor");
			featureMax.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/max-maximum-27-unsel.png")));
			featureMax.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/max-maximum-27.png")));
			featureMax.addActionListener(e -> featureMaxActionPerformed(e));
			toolBar1.add(featureMax);

			//---- featureMin ----
			featureMin.setToolTipText("SHIFT-LMB: Select minimum around the cursor");
			featureMin.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/min-minimum-27-unsel.png")));
			featureMin.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/min-minimum-27.png")));
			featureMin.addActionListener(e -> featureMinActionPerformed(e));
			toolBar1.add(featureMin);

			//---- featureExact ----
			featureExact.setToolTipText("CTRL+SHFIT+LMB: Select exact cursor position");
			featureExact.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/ext-exact-27-unsel.png")));
			featureExact.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/ext-exact-27.png")));
			featureExact.addActionListener(e -> featureExactActionPerformed(e));
			toolBar1.add(featureExact);
			toolBar1.addSeparator();

			//---- buttonExplore ----
			buttonExplore.setToolTipText("Explore");
			buttonExplore.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/explore-27-unsel.png")));
			buttonExplore.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/explore-27.png")));
			buttonExplore.setSelected(true);
			buttonExplore.addActionListener(e -> buttonExploreActionPerformed(e));
			toolBar1.add(buttonExplore);

			//---- buttonUnused ----
			buttonUnused.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/add-wf-27-unsel.png")));
			buttonUnused.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/add-wf-27.png")));
			buttonUnused.setToolTipText("Add waveforms");
			buttonUnused.addActionListener(e -> buttonUnusedActionPerformed(e));
			toolBar1.add(buttonUnused);

			//---- buttonGraphParams ----
			buttonGraphParams.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/ruler-27-unsel.png")));
			buttonGraphParams.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/ruler-27.png")));
			buttonGraphParams.setToolTipText("Graph setup and ranges");
			buttonGraphParams.addActionListener(e -> buttonGraphParamsActionPerformed(e));
			toolBar1.add(buttonGraphParams);

			//---- buttonIntersection ----
			buttonIntersection.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/ruler-27-unsel.png")));
			buttonIntersection.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/ruler-27.png")));
			buttonIntersection.setToolTipText("Intersections");
			buttonIntersection.addActionListener(e -> buttonIntersectionActionPerformed(e));
			toolBar1.add(buttonIntersection);

			//---- buttonFilters ----
			buttonFilters.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/filter-27-unsel.png")));
			buttonFilters.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/filter-27.png")));
			buttonFilters.setToolTipText("Filters");
			buttonFilters.addActionListener(e -> buttonFiltersActionPerformed(e));
			toolBar1.add(buttonFilters);

			//---- buttonC ----
			buttonC.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/calibrate-27-unsel.png")));
			buttonC.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/calibrate-27.png")));
			buttonC.setToolTipText("Calibration");
			buttonC.addActionListener(e -> buttonCActionPerformed(e));
			toolBar1.add(buttonC);

			//---- buttonB2B ----
			buttonB2B.setText("B2B");
			buttonB2B.setToolTipText("Beat to Beat Analysis");
			buttonB2B.setSelectedIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/analysis-27.png")));
			buttonB2B.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/analysis-27-unsel.png")));
			buttonB2B.addActionListener(e -> buttonB2BActionPerformed(e));
			toolBar1.add(buttonB2B);

			//---- buttonAN ----
			buttonAN.setIcon(null);
			buttonAN.setSelectedIcon(null);
			buttonAN.setToolTipText("Analysis");
			buttonAN.setText("AN");
			buttonAN.addActionListener(e -> buttonANActionPerformed(e));
			toolBar1.add(buttonAN);
			toolBar1.addSeparator();
		}
		add(toolBar1, BorderLayout.NORTH);

		//======== toolBar2 ========
		{
			toolBar2.setMinimumSize(new Dimension(33, 32));
			toolBar2.setPreferredSize(new Dimension(33, 32));

			//======== layerSelectionPanel ========
			{
				layerSelectionPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
			}
			toolBar2.add(layerSelectionPanel);
		}
		add(toolBar2, BorderLayout.SOUTH);

		//======== majorPopupMenu ========
		{

			//---- copyImage ----
			copyImage.setText("Save Screenshot to Clipboard");
			copyImage.addActionListener(e -> copyImageActionPerformed(e));
			majorPopupMenu.add(copyImage);

			//---- saveImage ----
			saveImage.setText("Save Screenshot to File");
			saveImage.addActionListener(e -> saveImageActionPerformed(e));
			majorPopupMenu.add(saveImage);

			//======== menu1 ========
			{
				menu1.setText("Copy");

				//---- menuItem2 ----
				menuItem2.setText("Selected Signal");
				menuItem2.setEnabled(false);
				menu1.add(menuItem2);

				//---- menuItem3 ----
				menuItem3.setText("Selected Graph");
				menuItem3.setEnabled(false);
				menu1.add(menuItem3);

				//---- menuItem4 ----
				menuItem4.setText("All Graphs");
				menuItem4.setEnabled(false);
				menu1.add(menuItem4);

				//---- copyData ----
				copyData.setText("Copy Data to Clipboard");
				copyData.addActionListener(e -> copyDataActionPerformed(e));
				menu1.add(copyData);
			}
			majorPopupMenu.add(menu1);

			//---- pasteFromClipboard ----
			pasteFromClipboard.setText("Paste");
			pasteFromClipboard.setEnabled(false);
			pasteFromClipboard.addActionListener(e -> pasteFromClipboardActionPerformed(e));
			majorPopupMenu.add(pasteFromClipboard);
			majorPopupMenu.addSeparator();

			//---- graphSplit ----
			graphSplit.setText("Split Graph");
			graphSplit.addActionListener(e -> graphSplitActionPerformed(e));
			majorPopupMenu.add(graphSplit);

			//---- graphJoin ----
			graphJoin.setText("Join Graph Below");
			graphJoin.addActionListener(e -> graphJoinActionPerformed(e));
			majorPopupMenu.add(graphJoin);
		}

		//======== annotationOptionsMenu ========
		{

			//---- deleteAnnotation ----
			deleteAnnotation.setText("Delete Annotation    [DEL]");
			deleteAnnotation.addActionListener(e -> deleteAnnotationActionPerformed(e));
			annotationOptionsMenu.add(deleteAnnotation);
			annotationOptionsMenu.addSeparator();
		}

		//======== minorPopupMenu ========
		{

			//---- copyImage2 ----
			copyImage2.setText("Save Screenshot to Clipboard");
			copyImage2.addActionListener(e -> copyImageActionPerformed(e));
			minorPopupMenu.add(copyImage2);

			//---- saveImage2 ----
			saveImage2.setText("Save Screenshot to File");
			saveImage2.addActionListener(e -> saveImageActionPerformed(e));
			minorPopupMenu.add(saveImage2);

			//---- copyData2 ----
			copyData2.setText("Copy Data to Clipboard");
			copyData2.addActionListener(e -> copyDataActionPerformed(e));
			minorPopupMenu.add(copyData2);
			minorPopupMenu.addSeparator();
		}

		//---- cursorEditType ----
		ButtonGroup cursorEditType = new ButtonGroup();
		cursorEditType.add(featureMax);
		cursorEditType.add(featureMin);
		cursorEditType.add(featureExact);

		//---- buttonGroup1 ----
		ButtonGroup buttonGroup1 = new ButtonGroup();
		buttonGroup1.add(buttonExplore);
		buttonGroup1.add(buttonUnused);
		buttonGroup1.add(buttonGraphParams);
		buttonGroup1.add(buttonIntersection);
		buttonGroup1.add(buttonFilters);
		buttonGroup1.add(buttonC);
		buttonGroup1.add(buttonB2B);
		buttonGroup1.add(buttonAN);
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel optionsPanel;
	private JToolBar toolBar1;
	private JToggleButton featureMax;
	private JToggleButton featureMin;
	private JToggleButton featureExact;
	private JToggleButton buttonExplore;
	private JToggleButton buttonUnused;
	private JToggleButton buttonGraphParams;
	private JToggleButton buttonIntersection;
	private JToggleButton buttonFilters;
	private JToggleButton buttonC;
	private JToggleButton buttonB2B;
	private JToggleButton buttonAN;
	private JToolBar toolBar2;
	private JPanel layerSelectionPanel;
	private JPopupMenu majorPopupMenu;
	private JMenuItem copyImage;
	private JMenuItem saveImage;
	private JMenu menu1;
	private JMenuItem menuItem2;
	private JMenuItem menuItem3;
	private JMenuItem menuItem4;
	private JMenuItem copyData;
	private JMenuItem pasteFromClipboard;
	private JMenuItem graphSplit;
	private JMenuItem graphJoin;
	private JPopupMenu annotationOptionsMenu;
	private JMenuItem deleteAnnotation;
	private JPopupMenu minorPopupMenu;
	private JMenuItem copyImage2;
	private JMenuItem saveImage2;
	private JMenuItem copyData2;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void dispose() {

		timeseriesCanvas1.dispose();
	}

	public long getViewStartTimeMs() {
		return timeseriesCanvas1.getViewStartTimeMs();
	}

	public long getViewEndTimeMs() {
		return timeseriesCanvas1.getViewEndTimeMs();
	}

	public void redraw() {
		// thread safe
		synchronized (timeseriesCanvas1) {
			timeseriesCanvas1.redrawAxisLayer(0);
			refreshAnnotationLayerIndicators();
		}
	}

	public TsPSwingCanvas getCanvas1() {
		return timeseriesCanvas1;
	}

	public void clear() {
		// thread safe
		synchronized (timeseriesCanvas1) {
			timeseriesCanvas1.clear();
		}
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {

		String action = evt.getPropertyName();
		HPSplitableLayer sig = (HPSplitableLayer) evt.getNewValue();
		switch (action) {
		case "selected_signal":
			timeseriesCanvas1.setActiveSignal(sig, null); // FIXME: when is this called?
			break;
		case "removed_signal":
			timeseriesCanvas1.removeSignalLayer(sig);
			break;
		}

	}

	public void showOptions() {
		optionsPanel.setVisible(true);
	}

	public void hideOptions() {
		optionsPanel.setVisible(false);
	}

	public void showCursorValue(boolean selected) {
		timeseriesCanvas1.showCursorValue(selected);
	}

	public void showGraphScale(boolean selected) {
		timeseriesCanvas1.showGraphScale(selected);

	}

	public void showGraphTimeline(boolean selected) {
		timeseriesCanvas1.showGraphTimeline(selected);
	}

	public void showLegend(boolean selected) {
		timeseriesCanvas1.showGraphLegend(selected);
	}

	public boolean isGraphScaleVisible() {
		return timeseriesCanvas1.isGraphScaleVisible();
	}

	public boolean isGraphTimelineVisible() {
		return timeseriesCanvas1.isGraphTimelineVisible();
	}

	public void setDisplay(String displayName, DisplayConfig display) {
		timeseriesCanvas1.setDisplay(displayName, display);
	}

	public boolean isLegendVisible() {
		return timeseriesCanvas1.isLegendVisible();
	}

	public void addActivity(PActivity activity) {
		timeseriesCanvas1.getRoot().addActivity(activity);
	}

	public void removeActivity(PActivity activity) {
		// ? timeseriesCanvas1.getRoot().removeaddActivity(activity);
	}

	public void zoomToWidthInMillis(int millis) {
		timeseriesCanvas1.zoomToWidthInMillis(millis);
	}

	public void setViewDomainInMillis(long milli_start, long milli_end) {
		timeseriesCanvas1.setViewDomainInMillis(milli_start, milli_end);
	}

	public long getStartTime() {
		return timeseriesCanvas1.getStartTime();
	}

	public void showShowUnused(boolean selected) {
		timeseriesCanvas1.setShowUnused(selected);
	}

	public void reset() {
		timeseriesCanvas1.reset();
		// sync visible annotation layers

		AnnotationEditorTool annoEditor = timeseriesCanvas1.annotationEditorHandler;
		String editableLayerName = annoEditor.getEditableLayerName();
		// cb_state must be 2...
		for (int cid = 0; cid < layerSelectionPanel.getComponentCount(); cid++) {
			Object o = layerSelectionPanel.getComponent(cid);
			if (o instanceof LayerMultistateCheckBox) {
				LayerMultistateCheckBox tcb = (LayerMultistateCheckBox) o;
				PLayer layer = tcb.getLayer();
				int cb_state = tcb.getSelectionState();
				layer.setVisible(cb_state > 0);
				if (layer.getName().equals(editableLayerName)) {
					tcb.setSelectionState(2);
				}

			}
		}
	}

	public void addOptionPanel(JComponent plot) {
		int row = 2 * optionsPanel.getComponentCount() + 1;
		optionsPanel.add(plot, CC.xy(1, row));
		buttonAN.setEnabled(true);
		buttonAN.setSelected(true);
		if (optionsPanel.isVisible() == false) {
			buttonANActionPerformed(null);
		}

		JPopupMenu popupMenu = null;

		if (plot instanceof RPlotterPanel) {
			RPlotterPanel rpp = (RPlotterPanel) plot;
			popupMenu = rpp.getPopupMenu();
			// add detach options
			initMinorPopupMenu(popupMenu, rpp);
		} else if (plot instanceof TsPhaseSpaceCanvas) {
			TsPhaseSpaceCanvas psc = (TsPhaseSpaceCanvas) plot;
			initPopupHandler(psc);
		}

		doLayout();
	}

	private void detachPlotActionPerformed(ActionEvent e) {
		JComponent comp = removePlotActionPerformed(e);
		String title = (String) comp.getClientProperty("title");
		if (title == null) {
			title = comp.getName();
		}
		JDialog f = new DetachedPlotFrame((JFrame) AppFrame.getInstance(), title, comp);
		f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		f.getContentPane().add(comp, BorderLayout.CENTER);
		f.pack();
		f.setVisible(true);
		ext_graphs.add(comp);

		f.addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosed(WindowEvent e) {
				super.windowClosed(e);
				DetachedPlotFrame frame = (DetachedPlotFrame) e.getSource();
				Container cont = frame.getContentPane();
				Component[] comps = cont.getComponents();
				for (Component plot : comps) {
					ext_graphs.remove(plot);
				}
			}

		});
	}

	private JComponent removePlotActionPerformed(ActionEvent e) {
		Object obj = e.getSource();
		JComponent plot = current_canvas;
		if (plot == null) {
			plot = (JComponent) ((JComponent) obj).getClientProperty("plot");
		}
		optionsPanel.remove(plot);

		if (optionsPanel.getComponentCount() == 0) {
			optionsPanel.setVisible(false);
			buttonAN.setSelected(false);
			buttonAN.setEnabled(false);
		}

		// reposition objects in the option panel
		Component[] comps = optionsPanel.getComponents();
		if (comps != null) {
			for (Component comp : comps) {
				optionsPanel.remove(comp);
			}

			for (Component comp : comps) {
				int row = 2 * optionsPanel.getComponentCount() + 1;
				optionsPanel.add(comp, CC.xy(1, row));
			}
		}
		current_canvas = null;

		doLayout();
		return plot;
	}

	@Override
	public void activityStarted(PActivity activity) {
		// TODO Auto-generated method stub
		tmLastOptionsUpdate = System.currentTimeMillis();
	}

	@Override
	public void activityStepped(PActivity activity) {
		long dt = System.currentTimeMillis() - tmLastOptionsUpdate;
		if (dt > 2000) {
			updateOptionsGraphs(true);
			tmLastOptionsUpdate = System.currentTimeMillis();
		} else {
			updateOptionsGraphs(false);
		}
	}

	@Override
	public void activityFinished(PActivity activity) {
		updateOptionsGraphs(true);
	}

	private void updateOptionsGraphs(boolean slow_graphs) {
		long tm_ms = timeseriesCanvas1.getViewEndTimeMs();
		if (tm_ms == prev_option_refresh_tm) {
			return;
		}
		prev_option_refresh_tm = tm_ms;

		ArrayList<Component> graphs = new ArrayList();

		Component[] conts = null;
		if (optionsPanel.isVisible()) {
			conts = optionsPanel.getComponents();
			if (conts != null) {
				for (Component c : conts) {
					graphs.add(c);
				}
			}
		}

		graphs.addAll(ext_graphs);

		double tm = tm_ms / 1000.0;
		for (Component c : graphs) {
			if (c.isVisible() == false) {
				continue;
			}
			if (slow_graphs && c instanceof RPlotterPanel) {
				RPlotterPanel plotter = (RPlotterPanel) c;
				int num = plotter.getDeviceNumber() + 1;
				String env_name = (String) plotter.getClientProperty("env_name");
				// String script = "with( " + env_name + ", { update(100) } )";
				String script = "dev.set( " + num + ")\nupdate(" + tm + ")";
				AppUtil.runScriptCurrentThread(env_name, script, false);
			} else if (c instanceof TsPhaseSpaceCanvas) {
				TsPhaseSpaceCanvas canvas = (TsPhaseSpaceCanvas) c;
				canvas.update(tm_ms);
			}
		}
	}

	/**
	 * This method loads the current preferences and redraws the canvas.
	 */
	public void refresh(TsoPrefs prefs) {
		String s = prefs.getAttribute("indicatorColorIndex");
		if (s != null) {
			int idx = Integer.parseInt(s);
			Color color = ColorManager.getDefaultColor(idx);
			timeseriesCanvas1.setLocatorColor(color);
			timeseriesCanvas1.redrawAxisLayer(0);
		}

		s = prefs.getAttribute("showStudyPhase");
		boolean b = AppUtil.stringAsBoolean(s, false);
		timeseriesCanvas1.setShowStudyPhase(b);

	}

}
