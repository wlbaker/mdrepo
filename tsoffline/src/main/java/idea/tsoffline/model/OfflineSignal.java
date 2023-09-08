package idea.tsoffline.model;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.ListIterator;

import org.piccolo2d.PCamera;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.extras.nodes.PLine;

import idea.message.StreamID;
import idea.schema.rp.RpMetric;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import uk.me.berndporr.api.FilterInterface;
import idea.GuiUtil;
import idea.Stats;
import idea.ts.TsFilter;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.canvas.PiccoUtil;
import idea.tsoffline.filter.FilterUtil;

/**
 * 
 * @author william.l.baker2
 *
 * The "offline signal" consists of a PLayer (layer) that holds the data as well
 * as the type of signal (TimeseriesType) and the default color.  Since the color may 
 * change when, for example, an active signal is highlighted, the color is restored to
 * the default color when the active signal is de-selected. 
 */
@Slf4j
public class OfflineSignal extends RpMetric {

	@Getter
	@Setter
	protected PLayer layer;
	
	
	@Getter
	@Setter
	private TimeseriesType typ;
	
	@Getter
	@Setter
	private Color defaultColor;
	@Getter
	@Setter
	private Color color;

	@Getter
	@Setter
	private int bandId = -1;

	@Getter
	@Setter
	private String source = null;

	private double cachedSampleWidth = -1;

	public OfflineSignal(RpMetric m) {
		this( m, null);
	}

	public OfflineSignal(RpMetric m, TimeseriesType typ) {
		this.setLocation( m.getLocation() );
		this.setCode( m.getCode() );
		this.setName( m.getName() );
		this.setUnit( m.getUnit() );
		this.setSubtyp( m.getSubtyp() );
		this.setSampleRate( m.getSampleRate() );
		this.setSamplesPerPacket( m.getSamplesPerPacket() );
		
		this.setColor( Color.CYAN );  // something other than black!
		this.setDefaultColor( Color.CYAN );

		this.typ = typ;
	}


	// add a function: get-data-in-range, which will pull the data from the
	// signal layer
	public double getValueAt( double sec ) {

		double val = D.getValueAtPoint(layer, sec);
		return val;
	}

	// add a function: get-data-in-range, which will pull the data from the
	// signal layer
	public double [] getValueAt( double [] sec ) {

		double [] val = D.getValueAtPoint(layer, sec);
		return val;
	}
	// add a function: get-data-in-range, which will pull the data from the
	// signal layer
	public double[][] getDataInRange(long startX, long endX) {

		if (layer == null) {
			GuiUtil.showMessage("INTERNAL ERROR: SIGNAL NOT LOADED: " + getName());
			return null;
		}

		double startSec = startX / 1000.0;
		double endSec = endX / 1000.0;
		double[][] ret = D.getValuesInRange(layer, startSec, endSec);
		return ret;
	}

	/*
	 * Called by R
	 */
	public double[][] getData() {

		double[][] ret = D.getValuesInRange(layer, Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY);
		return ret;
	}
	
	/*
	 * Called by R
	 */
	public double[][] getDataInRange(double startSec, double endSec) {

		double[][] ret = D.getValuesInRange(layer, startSec, endSec);
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
		List<PNode> childs = layer.getChildrenReference();
		for( PNode node :  childs) {
			if( node.getX() > sec ) {
				break;
			}
			prev = node;
		}
		return prev;
	}
	
	public PNode getNodeBefore(double sec) {
		PNode prev = null;
		@SuppressWarnings("unchecked")
		List<PNode> childs = layer.getChildrenReference();
		for( PNode node :  childs) {
			if( node.getX() >= sec ) {
				break;
			}
			prev = node;
		}
		return prev;
	}
	
	public PNode getNodeAfter(double sec) {
		PNode after = null;
		@SuppressWarnings("unchecked")
		List<PNode> childs = layer.getChildrenReference();
		for( PNode node :  childs) {
			if( (node.getX() - sec) > 0.0001 ) {
				after = node;
				break;
			}
		}
		return after;
	}
	
	public double getMean(double startSec, double endSec) {
		double[][] xy = D.getValuesInRange(this.getLayer(), startSec, endSec );
		double[] x = xy[0];
		double[] y = xy[1];
		return Stats.mean(y);
	}
	
	public double[] getTimesInRange(double startSec, double endSec) {
		double[][] xy = D.getValuesInRange(this.getLayer(), startSec, endSec );
		double[] x = xy[0];
		double[] y = xy[1];
		return x;
	}
	
	public double[] getValuesInRange(double startSec, double endSec) {
		double[][] xy = D.getValuesInRange(this.getLayer(), startSec, endSec );
		double[] x = xy[0];
		double[] y = xy[1];
		return y;
	}
	
	public boolean isLoaded() {
		return (layer != null);
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
		return layer.getChildrenReference();
	}


	public void unload() {
		if (layer != null) {
			layer.setVisible(false);
			for (int idx = 0; idx < layer.getCameraCount(); idx++) {
				PCamera camera = layer.getCamera(idx);
				camera.removeChild(layer);
			}
			// signalLayer.repaint();
			layer.removeAllChildren();
			layer = null;
		}
	}

	public double getSampleWidth() {
		if (cachedSampleWidth < 0) {
			int sampleRate = 1;
			if (getSampleRate() != null) {
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
	 * Called by R
	 */

	public void addData( double[] x, double[] y ) {
		int spp = this.getSamplesPerPacket();
		
		double[] tm = new double[ spp + 1 ];  // one point of overlap with next node
		double[] val = new double[ spp + 1 ];
		if( layer == null) {
			layer = new HPPathLayer(null, StreamID.WAVEFORM, "R");
			layer.setName( getLocation() );
			layer.addAttribute("sig", this);
		}
		
		int pos = 0;
		for( int i = 0; i < x.length; i++ ) {
			if( pos == spp ) {
				tm[pos] = x[i];  // one point of overlap with next node
				val[pos] = y[i];
				
				PLine path_hi = PiccoUtil.createVariableResolutionLine(this, tm, val);
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
		if (layer != null) {
			if (layer.getVisible()) {
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
		((HPPathLayer)layer).dump();
		
	}


	public void applyFilter(TsFilter filter) {
		Object o = getLayer();
		
		FilterInterface cascade = null;
		if( filter != null ) {
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

}
