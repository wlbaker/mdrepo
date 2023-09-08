package idea.tsoffline;

import java.awt.Color;
import java.awt.Paint;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.rosuda.REngine.REXPJavaReference;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngineException;

import com.softhorizons.filterdesigner.GuiUtil;

import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStudy;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import uk.me.berndporr.api.FilterInterface;
import idea.analysis.event.BeatBlock;
import idea.r.RUtil;
import idea.ts.TsFilter;
import idea.ts.TsoAnnotationEntryType;
import idea.ts.TsoPhase;
import idea.tsoffline.canvas.TsBaseCanvas;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.filter.FilterUtil;
import idea.tsoffline.model.DerivedUtil;
import idea.tsoffline.model.FormulaOp;
import idea.tsoffline.model.FormulaSignal;
import idea.tsoffline.model.OfflineDevice;

/*
 * This class provides the entry point for the API available to plugins.
 */
@Slf4j
public class AppModel {

	private static RpHardware hww0 = new RpHardware();
	
	@Getter
	private static AppModel instance = new AppModel();

	private static LinkedList<TsoPhase> phases;

	@Getter
	@Setter
	private static boolean dirty;
	@Getter
	@Setter
	private static boolean beta;

	static TimelineModel timelineModel = new TimelineModel();

	private static String[][] translation = { { "Tape#01", "LVP" }, { "Tape#02", "AoP" }, { "Tape#03", "AoVel" },
			{ "Tape#04", "PAP" }, { "Tape#05", "RVP" }, { "Tape#06", "RAP" }, { "Tape#07", "Fluid" },
			{ "Tape#08", "Resp" }, { "Tape#09", "ECG" }, { "Tape#10", "Phono1" }, { "Tape#11", "Phono2" },
			{ "Tape#12", null }, // indicator to hide these signals
			{ "Tape#13", null }, { "Tape#14", null }, { "Tape#15", null } };

	public static PNode addAnnotation(PLayer layer, Object item, boolean modified) {
		PNode node = new PNode();

		long initialTm = timelineModel.getStartTime().getTime();
		Object entry;

		String message = null;
		if (item instanceof PersistentItem) {
			PersistentItem pi = (PersistentItem) item;
			node.setX((pi.getTime() - initialTm) / 1000.0);

			String loc = findTextLoc(pi.getMetrics());
			message = (String) IntfUtil.getRawValueByLoc(pi, loc);
			if (message == null) {
				message = (String) IntfUtil.getRawValueByLoc(pi, "message");
			}
			if (message == null) {
				message = (String) IntfUtil.getRawValueByLoc(pi, "desc");
			}
			if (message == null) {
				message = (String) IntfUtil.getRawValueByLoc(pi, "txt");
			}
			TsoAnnotationEntryType anno = new TsoAnnotationEntryType();
			if (item instanceof BeatBlock) {
				BeatBlock bb = (BeatBlock) item;
				anno.setValue(bb.getMs_interval());
				message = "R";
			}
			anno.setOffset(node.getX());
			anno.setValue(node.getY());
			anno.setCode(message);
			anno.setTm(pi.getTm());
			
			entry = anno;
		} else if( item instanceof TsoPhase ){
			TsoPhase phase = (TsoPhase) item;
			long start_tm = phase.getStartTm().getTime();  // date/time in millis
			long end_tm = phase.getStopTm().getTime();  // date/time in millis
			node.setName( phase.getName() );
			node.setX((start_tm - initialTm) / 1000.0);
			node.setY( -10000 );
			node.setWidth( (end_tm - start_tm) / 1000.0 );
			node.setHeight( 20000 );
			node.setPaint( ColorManager.asColor( phase.getColor() ) );
			node.setVisible( true );
			node.setTransparency( (float) 0.2 );
			node.setPickable( false );
			message = phase.getName();
			entry = phase; 
		} else {
			TsoAnnotationEntryType anno = (TsoAnnotationEntryType) item;
			node.setX((anno.getTm().getTime() - initialTm) / 1000.0);
			node.setY(anno.getValue());
			message = anno.getCode();
			
			entry = item;
		}
		node.addAttribute("item", entry);
		node.addAttribute("txt", message);

		layer.addChild(node);

		if (modified) {
			layer.addAttribute("modified", true);
			setDirty(true);
		}

		return node;
	}

	// called from R
	public static PNode addAnnotationWithRelativeTime(PLayer layer, TsoAnnotationEntryType event, double sec,
			boolean modified) {
		long startTm = timelineModel.getStartTime().getTime();
		long ms = (long) (1000.0 * sec + 0.5); // round up
		Date dt = new Date(startTm + ms);
		event.setTm(dt);

		return addAnnotation(layer, event, modified);
	}

	public static FormulaSignal createFormulaSignal(TsBaseCanvas canvas, String name, Paint color, FormulaSignal formula) {

		log.info("add formula: {}", name);
		// removeOfflineSignal(formula);
		HPSplitableLayer sig1 = canvas.findSignal( formula.sig1);
		HPSplitableLayer sig2 = null;
		if (formula.sig2 != null) {
			sig2 = canvas.findSignal( formula.sig2);
		}

		// some formulas are waveforms...others are not!
		StreamID sid = StreamID.WAVEFORM;
		switch (formula.op) {
		case Add:
			sid = StreamID.WAVEFORM;
			DerivedUtil.add(formula, sig1, sig2);

			break;
		case Subtract:
			sid = StreamID.WAVEFORM;
			DerivedUtil.subtract(formula, sig1, sig2);
			break;
		case Divide:
			sid = StreamID.WAVEFORM;
			DerivedUtil.divide(formula, sig1, sig2);
			break;
		case Mean:
			sid = StreamID.MEASUREMENT;
			DerivedUtil.mean(formula, sig1, sig2);
			break;
		case Derivative:
			sid = StreamID.WAVEFORM;
			DerivedUtil.derivative(formula, sig1);
			break;
		case Duplicate:
			sid = StreamID.WAVEFORM;
			DerivedUtil.duplicate(formula, sig1);
			break;
		default:
			log.error("Could not perform formula operation: {} / {}", formula, formula.op );
			return null;
		}
		formula.setPaint(color);
		formula.setDefaultColor((Color)color);
		formula.setSource("formula");

		GuiUtil.showMessage("FIXME: formula is a splitable layer");
		HPPathLayer layer = (HPPathLayer) formula.getChild(0);
		if (layer != null) {
			layer.setName(name);
			String filterName = (String) layer.getAttribute("@filterName");
			if (filterName != null) {
				TsFilter filter = FilterUtil.findFilterFromName( filterName );
				FilterInterface cascade = FilterUtil.createFilterFromJSON(filter.getDescription());
				layer.applyFilter(filter, cascade);
			}
		}

		return formula;
	}

	public static FormulaSignal addFormula(String layerName, Color color, String formula) {
		RpMetric boguus = new RpMetric();

		// String s_p2 = "([^}]+},?)*";
		// String s_pattern = "(\\w+)\\([^}]+},?])*\\)";
		//
		// Pattern p2 = Pattern.compile(s_p2);
		// Matcher m2 = p2.matcher("${Lt Dist}");
		//
		// Pattern pattern = Pattern.compile(s_pattern);
		// Matcher matcher = pattern.matcher(formula);
		int n = 0;
		// while( matcher.find() ) {
		// System.out.println("seg: " + matcher.group() );
		// arr[n++] = matcher.group();
		// }

		String loc = formula;
		String[] arr = new String[3];
		int idx = formula.indexOf('(');
		if (idx > 0) {
			arr[n++] = formula.substring(0, idx);
			formula = formula.substring(idx + 1);
		}

		idx = findArgEnd( formula );
		if (idx > 2) {
			arr[n++] = formula.substring(2, idx);
			formula = formula.substring(idx + 2); // skip the comma if there is
													// another arg
		}

		idx = formula.indexOf('}');
		if (idx > 2) {
			arr[n++] = formula.substring(2, idx);
			formula = formula.substring(idx + 1);
		}

		// Object detail = new SimpleFormulaEditorPanel(sorted_sigs);
		boguus.setLocation(loc);
		boguus.setName(layerName);
		boguus.setCode(loc);
		FormulaSignal f = new FormulaSignal(boguus);

		f.op = FormulaOp.fromString(arr[0]);
		f.sig1 = arr[1];
		f.sig2 = arr[2];

		f.setPaint(color);
		f.setDefaultColor(color);
		f.setSource("formula");
		StreamID sid = StreamID.WAVEFORM;
		HPPathLayer unused = new HPPathLayer(f.getMetric(), sid, layerName);  // empty layer
		
		GuiUtil.showMessage("FIXME: is formula saved in canvas?");

		GuiUtil.showMessage("FIXME: psupport.firePropertyChange(ADD_FORMULA_PROPERTY, null, f );");


		return f; // createFormulaSignal(layerName, color, f);
	}

	private static int findArgEnd(String formula) {
		int stack = 0;
		for( int idx = 0; idx < formula.length(); idx++ ) {
			char ch = formula.charAt(idx);
			if( ch == '{') {
				stack++;
			}
			if( ch == '}') {
				stack--;
				if( stack == 0 ) {
					return idx;
				}
			}
		}
		log.error("Error in formula: {}", formula );
		return -1;
	}


	private static String findTextLoc(RpMetric[] metrics) {
		for (RpMetric m : metrics) {
			try {
				m.getSubtyp();
			} catch (NullPointerException e) {
				System.err.println("DEBUG ENTRY: subtyp not set.");
			}
			if (m.getSubtyp() == DataTyp.STRING_TYP) {
				return m.getLocation();
			}
		}

		return null;
	}
	
	public static OfflineDevice getDevice(String devName) {
		for (OfflineDevice dev : getDevices()) {
			if (dev.getName().equals(devName)) {
				return dev;
			}
		}
		return null;
	}

	public static List<OfflineDevice> getDevices() {
		List list = hww0.getDevices();
		return list;
	}

	@Deprecated
	public static OfflineDevice[] getDevicesAsArray() {
		List list = hww0.getDevices();
		OfflineDevice[] arr = new OfflineDevice[list.size()];
		return (OfflineDevice[]) list.toArray(arr);
	}

	public static RpStudy getModelAsStudy() {
		RpStudy study = new RpStudy();

		study.getHardware().add(hww0);
		return study;
	}

	public static int getNextLayerSeq() {
		GuiUtil.showMessage("FIXME: next seq no");
//		List<OfflineSignal> sigs = AppModel.getSignals();
//		int maxSeq = 0;
//		for (OfflineSignal sig : sigs) {
//			int seq = sig.getLayerSeq();
//			if (seq > maxSeq) {
//				maxSeq = seq;
//			}
//		}
//		return maxSeq + 1;
		return 9999;
	}

	public static List<TsoPhase> getPhaseModel() {
		return phases;
	}

	public static List<HPSplitableLayer> getSignals() {
		
		GuiUtil.showMessage("AppModel getSignals()...DELETE ME");
		LinkedList<HPSplitableLayer> ll = new LinkedList<HPSplitableLayer>();
		// zzzz
		return ll;
	}

	public static long getStartTime() {

		// avoid NPE when opening analysis/vizwizard without an open session
		if (timelineModel == null) {
			return 0;
		}

		if (timelineModel.getStartTime() == null) {
			return 0;
		}

		return timelineModel.getStartTime().getTime();
	}

	public static String[][] getSubstitutionsModel() {
		return translation;
	}

	public static TimelineModel getTimelineModel() {
		return timelineModel;
	}

	public static void removeAnnotation(PLayer layer, PNode node) {
		layer.removeChild(node);
		layer.addAttribute("modified", true);
		setDirty(true);
	}

	public static void updateAnnotationData(PNode prev, PNode node, PNode next) {
		PNode layer = node.getParent();
		Object update = node.getAttribute("@update");
		if (update == null) {
			update = layer.getAttribute("@update");
		}
		if (update == null) {
			return;
		}
		if (prev == null) {
			@SuppressWarnings("unchecked")
			List<PNode> nodes = layer.getChildrenReference();
			PNode p = null;
			boolean find_next = false;
			for (PNode curr : nodes) {
				if (find_next) {
					next = curr;
					break;
				} else if (curr == node) {
					prev = p;
					find_next = true;
				} else {
					p = curr;
				}
			}
		}

		AppUtil.setParam("UPDATE", "layer", layer);
		AppUtil.setParam("UPDATE", "prev", prev);
		AppUtil.setParam("UPDATE", "next", next);
		AppUtil.setParam("UPDATE", "node", node);
		AppUtil.setParam("UPDATE", "xpos", node.getX());

		if (log.isDebugEnabled()) {
			String txt = (String) node.getAttribute("txt");
			if ("_LTVmean".equals(txt)) {
				System.out.println("DEBUG");
			}

			System.out.print("[PRE ] ");
			if (prev != null) {
				System.out.print("prev-x=" + prev.getX() + "  ");
			}
			System.out.print(node.getAttribute("txt") + " curr-x=(" + node.getX() + "," + node.getY() + ") -- ");
			if (next != null) {
				System.out.print(next.getAttribute("txt") + " next-x=(" + next.getX() + "," + next.getY() + ")");
			}
			System.out.println();
		}

		try {
			RUtil.getREngine().assign("layer", new REXPJavaReference(layer));
			RUtil.getREngine().assign("node", new REXPJavaReference(node));
			RUtil.getREngine().assign("prev", (prev == null) ? null : new REXPJavaReference(prev));
			RUtil.getREngine().assign("next_node", (next == null) ? null : new REXPJavaReference(next));
			String script = (String) update + "( layer, prev, node, next_node )";
			// String script = "update_b2b_ref_value(layer, prev, node,
			// next_node)";
			AppUtil.runScript(script, true);
		} catch (REngineException | REXPMismatchException e) {
			throw new RuntimeException(e);
		}

		if (log.isDebugEnabled()) {
			System.out.print("[POST]  ");
			if (prev != null) {
				System.out.print("prev-x=" + prev.getX() + "  ");
			}
			System.out.print(node.getAttribute("txt") + " curr-x=(" + node.getX() + "," + node.getY() + ") -- ");
			if (next != null) {
				System.out.print(next.getAttribute("txt") + " next-x=(" + next.getX() + "," + next.getY() + ")");
			}
			System.out.println();
			System.out.print(""); // debug
		}
	}	
	
	public static TsPSwingCanvas getActiveCanvas() {
		return AppFrame.getInstance().getCanvas();
	}

}
