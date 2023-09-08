package idea.tsoffline;

import java.awt.Color;
import java.awt.Paint;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.ListIterator;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.extras.nodes.PLine;
import org.piccolo2d.util.PBounds;

import idea.message.StreamID;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import uk.me.berndporr.api.FilterInterface;
import idea.GuiUtil;
import idea.Stats;
import idea.ts.TsFilter;
import idea.tsoffline.canvas.PiccoUtil;
import idea.tsoffline.filter.FilterUtil;
import idea.tsoffline.model.DerivedUtil;

@Slf4j
public class HPSplitableLayer extends PLayer {

	@Getter // for debugging
	private RpMetric m;

	public HPSplitableLayer(RpMetric m) {
		this(m, TimeseriesType.TT_DATA);
	}

	public HPSplitableLayer(RpMetric m, TimeseriesType ttyp) {
		
		if ( m == null ) {
			log.error("metric is null");
			m = new RpMetric();
			m.setCode("zzz");
			m.setLocation("zzz");
			m.setSubtyp( 0 );
		}
		
		if( m.getSubtyp() == null ) {
			log.error("metric subtype is null for: {}", m);
			m.setSubtyp(-1);
		}
		
		this.m = m;
		this.typ = ttyp;
		addAttribute("sig", m); // this one is just handy to have!
	}

	@Getter
	@Setter
	private int layerSeq;
	@Getter
	@Setter
	private TimeseriesType typ;

	@Getter
	@Setter
	private Color defaultColor;

	@Getter
	@Setter
	private int bandId = 0;

	@Getter
	@Setter
	private String source = null;
	private double cachedSampleWidth = -1;

	/*
	 * Some get's are proxied from RpMetric member
	 */
	public RpMetric getMetric() {
		return m;
	}

	public String getAlias() {
		return m.getAlias();
	}

	public String getCode() {
		return m.getCode();
	}

	public String getLocation() {
		return m.getLocation();
	}

	public int getSubtyp() {
		return m.getSubtyp();
	}

	public int getSampleRate() {
		return m.getSampleRate();
	}

	/*
	 * Data management routines
	 */

	// add a function: get-data-in-range, which will pull the data from the
	// signal layer
	public double getValueAt(double sec) {

		double val = DerivedUtil.getValueAtPoint(this, sec);
		return val;
	}

	// add a function: get-data-in-range, which will pull the data from the
	// signal layer
	public double[] getValueAt(double[] sec) {

		double[] val = DerivedUtil.getValueAtPoint(this, sec);
		return val;
	}

	// add a function: get-data-in-range, which will pull the data from the
	// signal layer
	public double[][] getDataInRange(long startX, long endX) {

		double startSec = startX / 1000.0;
		double endSec = endX / 1000.0;
		double[][] ret = DerivedUtil.getValuesInRange(this, startSec, endSec);
		return ret;
	}

	/*
	 * Called by R
	 */
	public double[][] getData() {

		double[][] ret = DerivedUtil.getValuesInRange(this, Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY);
		return ret;
	}

	/*
	 * Called by R
	 */
	public double[][] getDataInRange(double startSec, double endSec) {

		double[][] ret = DerivedUtil.getValuesInRange(this, startSec, endSec);
		return ret;
	}

	public Collection<PNode> getNodesInRange(double startTime, double endTime) {
		ArrayList<PNode> dest = new ArrayList<PNode>();
		getNodesInRange(dest, getNodes(), startTime, endTime);

		return dest;
	}

	public static int getNodesInRange(ArrayList<PNode> dest, Collection<PNode> nodes, double startX, double endX) {

		int idx = 0;
		for (PNode node : nodes) {
			double x = node.getX();
			if (x < startX) {
				idx++;
			}
			if (x >= startX && x <= endX) {
				dest.add(node);
			}
		}
		return idx;
	}

	public PNode getNodeBeforeOrEqual(double sec) {
		PNode prev = null;
		@SuppressWarnings("unchecked")
		List<PNode> layers = getChildrenReference();
		for (PNode layer : layers) {
			List<PNode> childs = getChildrenReference();
			for (PNode node : childs) {
				if (node.getX() > sec) {
					break;
				}
				prev = node;
			}
		}
		return prev;
	}

	public PNode getNodeBefore(double sec) {
		PNode prev = null;
		@SuppressWarnings("unchecked")
		List<PNode> layers = getChildrenReference();
		for (PNode layer : layers) {
			List<PNode> childs = getChildrenReference();
			for (PNode node : childs) {
				if (node.getX() >= sec) {
					break;
				}
				prev = node;
			}
		}
		return prev;
	}

	public PNode getNodeAfter(double sec) {
		PNode after = null;
		@SuppressWarnings("unchecked")
		List<PNode> layers = getChildrenReference();
		for (PNode layer : layers) {
			List<PNode> childs = getChildrenReference();
			for (PNode node : childs) {
				if ((node.getX() - sec) > 0.0001) {
					after = node;
					break;
				}
			}
		}
		return after;
	}

	public double getMean(double startSec, double endSec) {
		double[][] xy = DerivedUtil.getValuesInRange(this, startSec, endSec);
		double[] x = xy[0];
		double[] y = xy[1];
		return Stats.mean(y);
	}

	public double[] getTimesInRange(double startSec, double endSec) {
		double[][] xy = DerivedUtil.getValuesInRange(this, startSec, endSec);
		double[] x = xy[0];
		double[] y = xy[1];
		return x;
	}

	public double[] getValuesInRange(double startSec, double endSec) {
		double[][] xy = DerivedUtil.getValuesInRange(this, startSec, endSec);
		double[] x = xy[0];
		double[] y = xy[1];
		return y;
	}

	public boolean isLoaded() {
		return getCameraCount() > 0;
	}

	public boolean isDerived() {
		return typ == null;
	}

//	public PiDatastreamImporter getImportDevice() {
//		PLayerStream importer = new PLayerStream( 0, 'A');
//		importer.add( layer );
//		return importer;
//	}
//
//
	@SuppressWarnings("unchecked")
	public Collection<PNode> getNodes() {
		GuiUtil.showMessage("FIXME: getNodes() returning first segment only");
		log.error( "FIXME: getNodes()...returning first segment only");
		
		List ref = getChildrenReference();
		PNode child = (PNode) ref.get(0);
		return child.getChildrenReference();
	}

	public void unload() {
		while (getCameraCount() > 0) {
			PCamera camera = getCamera(0);
			camera.removeChild(this);
		}
		removeAllChildren();
	}

	public double getSampleWidth() {
		if (cachedSampleWidth  < 0) {
			int sampleRate = 1;
			if (m.getSampleRate() != null) {
				sampleRate = getSampleRate();
			}
			cachedSampleWidth = (sampleRate <= 0) ? 0 : (float) (1000.0 / sampleRate);
		}

		return cachedSampleWidth;
	}

	/**
	 * 
	 * @param x
	 * @param y
	 * 
	 *          Called by R
	 */

	public void addData(double[] x, double[] y) {
		int spp = this.getSamplesPerPacket();

		double[] tm = new double[spp + 1]; // one point of overlap with next node
		double[] val = new double[spp + 1];

		PNode layer = this.getChild(0);
		if (layer == null) {
			layer = new HPPathLayer(null, StreamID.WAVEFORM, "R");
			layer.setName(getLocation());
			layer.addAttribute("sig", this);
			this.addChild(layer);
		}

		int pos = 0;
		for (int i = 0; i < x.length; i++) {
			if (pos == spp) {
				tm[pos] = x[i]; // one point of overlap with next node
				val[pos] = y[i];

				PLine path_hi = PiccoUtil.createVariableResolutionLine(m, tm, val);
				path_hi.setStrokePaint(Color.WHITE);
				layer.addChild(path_hi);
				pos = 0;
			}
			tm[pos] = x[i];
			val[pos] = y[i];
			pos++;
		}

	}

	@Override
	public String toString() {
		StringBuffer b = new StringBuffer();
		if (isLoaded()) {
			if (getVisible()) {
				b.append("[Visible] ");
			} else {
				b.append("[Hidden] ");
			}
		}
		String t_name = getName();
		if (t_name == null || t_name.length() == 0) {
			t_name = getCode();
		}
		if (t_name == null || t_name.length() == 0) {
			t_name = getLocation();
		}
		b.append(t_name);

		return b.toString();
	}

	public void dump() {
		ListIterator it = getChildrenIterator();
		while (it.hasNext()) {
			((HPPathLayer) it.next()).dump();
		}

	}

	public void applyFilter(TsFilter filter) {
		Object o = this;

		FilterInterface cascade = null;
		if (filter != null) {
			cascade = FilterUtil.createFilterFromJSON(filter.getDescription());
		}
		if (o instanceof HPPathLayer) {
			HPPathLayer layer = (HPPathLayer) o;
			_applyFilter(layer, filter, cascade);
		} else {
			log.warn("Some refactoring of container layer would remove this code");
			PLayer layer = (PLayer) o;
			ListIterator it = layer.getChildrenIterator();
			while (it.hasNext()) {
				HPPathLayer hpplayer = (HPPathLayer) it.next();
				_applyFilter(hpplayer, filter, cascade);

			}
		}
	}

	public void _applyFilter(HPPathLayer layer, TsFilter filter, FilterInterface cascade) {
		// LegendTool tool = (LegendTool) notification.getObject();

		if (filter == null) {
			layer.resetFilter();
		} else {
			layer.applyFilter(filter, cascade);
		}

		layer.repaint();
	}

	public int getSamplesPerPacket() {
		return m.getSamplesPerPacket();
	}

	public RpUnit getUnit() {
		log.error("getUnit() not implemented");
		return null;
	}

	@Override
	public PBounds getBounds() {
		
		PBounds bounds = null;
		for( Object o : getChildrenReference() ) {
			PLayer layer = (PLayer)o;
			PBounds b = layer.getBounds();
			if( bounds == null ) {
				bounds = b;
			} else {
				log.error("create union of bounds");
				// bounds.un
			}
		}
		
		return bounds;
	}

	@Override
	public void setPaint(Paint newPaint) {
		super.setPaint(newPaint);
		for( Object o : getChildrenReference() ) {
			PLayer layer = (PLayer)o;
			layer.setPaint( newPaint );
		}
		
	}

}
