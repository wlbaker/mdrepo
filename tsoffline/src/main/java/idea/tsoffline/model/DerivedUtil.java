package idea.tsoffline.model;

import java.awt.geom.Path2D;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.extras.nodes.PLine;
import org.piccolo2d.extras.util.LineShape;
import org.piccolo2d.extras.util.XYArray;
import org.piccolo2d.nodes.PPath;
import org.piccolo2d.util.PAffineTransform;

import com.softhorizons.filterdesigner.GuiUtil;

import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpUnit;
import lombok.extern.slf4j.Slf4j;
import idea.Stats;
import idea.tsoffline.AppModel;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.canvas.HPPath;
import idea.tsoffline.canvas.LinkedNode;
import idea.tsoffline.canvas.PiccoUtil;

@Slf4j
public class DerivedUtil {

	public static int kludge_points_skipped;
	private static DerivedUtil inst = null;

	public static DerivedUtil getInstance() {

		if (inst == null) {
			inst = new DerivedUtil();
		}

		return inst;
	}

	//
	// called from R
	//

	public static double[] X(double[][] xy) {
		return xy[0];
	}

	//
	// called from R
	//

	public static double[] Y(double[][] xy) {
		return xy[1];
	}

	//
	// called from R
	//

	public static HPSplitableLayer add(HPSplitableLayer c, HPSplitableLayer a, HPSplitableLayer b) {
		return convoluteSignals(c, a, b, 1);
	}

	public static HPSplitableLayer subtract(HPSplitableLayer c, HPSplitableLayer a, HPSplitableLayer b) {
		return convoluteSignals(c, a, b, -1);
	}

	public static HPSplitableLayer divide(HPSplitableLayer c, HPSplitableLayer a, HPSplitableLayer b) {
		return convoluteSignals(c, a, b, 0);
	}

	public static HPSplitableLayer convoluteSignals(HPSplitableLayer c, HPSplitableLayer a, HPSplitableLayer b, int op) {
		c.setLayerSeq(AppModel.getNextLayerSeq());

		String loc = (op == 1) ? "add" : "subtract";
		if (op == 0)
			loc = "divide";

		if (a == null || b == null) {
			log.error("INTERNAL ERROR: Could not find signal for add/subtract/divide");
			return null;
		}
		loc += "(${" + a.getLocation() + "},${" + b.getLocation() + "})";

		RpMetric mc = c.getMetric();
		mc.setLocation(loc);
		mc.setSampleRate(a.getSampleRate());
		mc.setSubtyp(a.getSubtyp());
		mc.setSamplesPerPacket(a.getSamplesPerPacket());
		c.setTyp(TimeseriesType.TT_FORMULA);

		PLayer la = a;
		PLayer lb = b;
		PLayer lc = c;
		if (lc == null) {
			lc = new HPPathLayer(c.getMetric(), StreamID.WAVEFORM, c.getAlias());
			lc.setName(loc);
		} else {
			lc.removeAllChildren();
		}

		lc.addAttribute("sig", c);
		Object sid_name = la.getAttribute("sid_name");
		lc.addAttribute("sid_name", sid_name);

		Iterator<PNode> aa = la.getChildrenIterator(); // 22FEB17 WLB: Changed
														// from:
														// getAllNodes().iterator();
		Iterator<PNode> bb = lb.getChildrenIterator(); // 22FEB17 WLB: Changed
														// from:
														// getAllNodes().iterator();

		PNode anode = null;
		PNode bnode = null;

		if (aa.hasNext() == false || bb.hasNext() == false) {
			log.error("No data in array for convolution");
			return null;
		}

		int a_pos = 0;
		int a_end = 0;
		int b_pos = 0;
		int b_end = 0;
		int c_pos = 0;
		int c_end = 0;

		double[] ax = null;
		double[] ay = null;
		double[] bx = null;
		double[] by = null;
		double[] cx = null;
		double[] cy = null;
		do {

			while (a_pos >= a_end && aa.hasNext()) {
				anode = aa.next();
				double[][] arr_a = getValuesFromNode(null, anode);
				ax = arr_a[0];
				ay = arr_a[1];
				a_pos = 0;
				a_end = ax.length;
			}
			while (b_pos >= b_end && bb.hasNext()) {
				bnode = bb.next();
				double[][] arr_b = getValuesFromNode(null, bnode);
				bx = arr_b[0];
				by = arr_b[1];
				b_pos = 0;
				b_end = bx.length;
			}

			while (a_pos < a_end && b_pos < b_end) {
				if (ax[a_pos] < bx[b_pos]) {
					a_pos++;
					continue;
				}
				if (bx[b_pos] < ax[a_pos]) {
					b_pos++;
					continue;
				}

				if (cx == null) {
					cx = new double[ax.length];
					cy = new double[ax.length];
					c_end = cx.length;
				}

				cx[c_pos] = ax[a_pos]; // must be the same as bx anyway.

				if (op == 1) { // add
					cy[c_pos++] = ay[a_pos++] + by[b_pos++];
				} else if (op == -1) { // subtract
					cy[c_pos++] = ay[a_pos++] - by[b_pos++];
				} else if (op == 0) { // divide
					if (by[b_pos] == 0) {
						cy[c_pos++] = 0; // Double.NaN;
						b_pos++;
					} else {
						cy[c_pos++] = ay[a_pos++] / by[b_pos++];
					}
				}

				if (c_pos == c_end) {
					PNode child = PiccoUtil.createVariableResolutionLine(mc, cx, cy);
					lc.addChild(child);
					c_pos = 0;
				}
			}

		} while (aa.hasNext() && bb.hasNext());

		return c;
	}

	/**
	 * 
	 * @param dest destination signal info for metric and layer info
	 * @param src source signal from which 
	 * 
	 * Destination can be null.  If it is null, a new (empty) metric and signal
	 * are created.  If the destination exists but has no layer data, then a layer
	 * is created and associated with the destination signal.  If the layer exists,
	 * all data is removed before creating and adding the derivative data.
	 * 
	 * @return Returns the destination signal.
	 */
	public static HPSplitableLayer derivative(HPSplitableLayer dest, HPSplitableLayer src) {
		if (src == null) {
			log.error("INTERNAL ERROR: Could not find source signal for derivative");
			return null;
		}
		RpMetric metric = new RpMetric( );
		if( dest == null ) {
			dest = new HPSplitableLayer( metric );
		}
		dest.setLayerSeq(AppModel.getNextLayerSeq());

		String loc = "derivative";
		loc += "(${" + src.getLocation() + "})";

		//double sr = src.getSampleRate();
		metric.setLocation(loc);
		metric.setSampleRate(src.getSampleRate());
		metric.setSubtyp(src.getSubtyp());
		metric.setSamplesPerPacket(src.getSamplesPerPacket());
		dest.setTyp(TimeseriesType.TT_FORMULA);

		PLayer la = src;
		PLayer lc = dest;
		if (lc == null) {
			lc = new HPPathLayer(metric, StreamID.WAVEFORM, dest.getAlias());
			lc.setName(loc);
			dest.addChild( lc);
		} else {
			lc.removeAllChildren();
		}

		lc.addAttribute("sig", dest);
		Object sid_name = la.getAttribute("sid_name");
		lc.addAttribute("sid_name", sid_name);

		Point2D pprev = new Point2D.Double(); // we need to backup one when we
												// reach the end
		Point2D prev = new Point2D.Double();
		Point2D curr = new Point2D.Double();

//		PrintStream pout = null;
//		try {
//			pout = new PrintStream( "c:/tmp/dout.csv" );
//		} catch (FileNotFoundException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		boolean first = true;
		ListIterator<PNode> aa = la.getChildrenIterator();
		while (aa.hasNext()) {
			HPPath anode = (HPPath) aa.next();
			LineShape line = anode.getLineReference();
			// PathIterator it = line.getPathIterator(null);

			int tot = line.getPointCount();

			double[] xy_pts = new double[2 * tot];

			int pos = 0;
			for (int i = 0; i < tot; i++) {
				line.getPoint(i, curr);
				xy_pts[pos++] = curr.getX();
				xy_pts[pos++] = curr.getY() - prev.getY();
				pprev.setLocation(prev);
				prev.setLocation(curr);
//				pout.println( curr.getX() +", " + curr.getY() + ", " + xy_pts[pos-1] );
			}
			prev.setLocation(pprev); // backup by one

			if (first) {
				xy_pts[1] = xy_pts[3]; // straighten out the first Y point
				first = false;
			}

			PNode child = PiccoUtil.createVariableResolutionLine(dest.getMetric(), new XYArray(xy_pts));
			lc.addChild(child);

		}
		
//		pout.close();
		return dest;
	}

	/**
	 * Create a duplicate signal.  Often used to compare filter characteristics.
	 * 
	 * @param dest Destination signal, output, can be null.
	 * @param src  Source signal, input.
	 * 
	 * @return dest
	 */
	public static HPSplitableLayer duplicate(HPSplitableLayer dest, HPSplitableLayer src) {
		if (src == null) {
			log.error("INTERNAL ERROR: Could not find signal for duplication");
			return null;
		}
		RpMetric metric = new RpMetric( );
		if( dest == null ) {
			dest = new HPSplitableLayer( metric );
		}
		dest.setLayerSeq(AppModel.getNextLayerSeq());

		String loc = "duplicate";
		loc += "(${" + src.getLocation() + "})";

		metric.setLocation(loc);
		metric.setSampleRate(0);
		metric.setSamplesPerPacket(1);
		metric.setSubtyp(DataTyp.FLOAT_TYP);
		dest.setTyp(TimeseriesType.TT_FORMULA);

		PLayer la = src;
		PLayer lc = new HPPathLayer(dest.getMetric(), StreamID.WAVEFORM, dest.getAlias());
		lc.setName(loc);
		dest.addChild(lc);

		lc.addAttribute("sig", dest);
		Object sid_name = la.getAttribute("sid_name");
		lc.addAttribute("sid_name", sid_name);

		Iterator<PNode> aa = la.getChildrenIterator();

		while (aa.hasNext()) {
			PNode anode = aa.next();

			// 22FEB17 WLB: Changed from: getAllNodes().iterator();
			// if (anode instanceof PLayer) {
			// PLayer lbad = (PLayer) anode;
			// log.error("a-clippable layer should not be here: " +
			// lbad.getName());
			// continue;
			// }
			double[][] arr_a = getValuesFromNode(null, anode);
			double[] x_a = arr_a[0];
			double[] y_a = arr_a[1];
			
			PNode child = PiccoUtil.createVariableResolutionLine(dest.getMetric(), x_a, y_a);
			lc.addChild(child);
		}
		return dest;
	}

	public static HPSplitableLayer mean(HPSplitableLayer c, HPSplitableLayer src, HPSplitableLayer delimiter) {
		if (src == null) {
			log.error("INTERNAL ERROR: Could not find signal for mean");
			return null;
		}
		if (delimiter == null) {
			log.error("INTERNAL ERROR: Could not find delimiter for mean");
			return null;
		}
		c.setLayerSeq(AppModel.getNextLayerSeq());

		String loc = "mean";
		loc += "(${" + src.getLocation() + "},${" + delimiter.getLocation() + "})";

		RpMetric mc = c.getMetric();
		mc.setLocation(loc);
		mc.setSampleRate(0);
		mc.setSamplesPerPacket(1);
		mc.setSubtyp(DataTyp.FLOAT_TYP);
		c.setTyp(TimeseriesType.TT_FORMULA);

		PLayer la = src;
		PLayer lb = delimiter;
		PLayer lc = new HPPathLayer(c.getMetric(), StreamID.WAVEFORM, c.getAlias());
		lc.setName(loc);
		c.addChild(lc);

		lc.addAttribute("sig", c);
		Object sid_name = la.getAttribute("sid_name");
		lc.addAttribute("sid_name", sid_name);

		// 22FEB17 WLB: Changed from: getAllNodes().iterator();
		Iterator<PNode> aa = la.getChildrenIterator();
		Iterator<PNode> bb = lb.getChildrenIterator();

		outer_loop: while (aa.hasNext()) {
			PNode anode = aa.next();

			// 22FEB17 WLB: Changed from: getAllNodes().iterator();
			// if (anode instanceof PLayer) {
			// PLayer lbad = (PLayer) anode;
			// log.error("a-clippable layer should not be here: " +
			// lbad.getName());
			// continue;
			// }
			double[][] arr_a = getValuesFromNode(null, anode);
			double[] x_a = arr_a[0];
			double[] y_a = arr_a[1];
			double[][] arr_b = null;
			double[] x_b = null;
			double[] y_b = null;
			PNode bnode = null;

			boolean retry = true;

			while (retry) {
				retry = bb.hasNext();
				if (retry == false) {
					break outer_loop;
				}
				bnode = bb.next();

				// 22FEB17 WLB: Changed from: getAllNodes().iterator();
				// if (bnode instanceof PLayer) {
				// PLayer lbad = (PLayer) bnode;
				// log.error("[216] b-clippable layer should not be here: {}",
				// lbad.getName());
				// continue;
				// }

				arr_b = getValuesFromNode(null, bnode);
				x_b = arr_b[0];
				y_b = arr_b[1];

				if (x_b[0] < x_a[0]) {
					retry = true;
				} else {
					retry = false;
				}
			}

			if (x_a[0] != x_b[0]) {
				log.error("UNALIGNED NODES: {} != {}", x_a[0], x_b[0]);
				// UNALIGNED NODES!
				return null;
			}

			for (int i = 0; i < y_a.length; i++) {
				y_a[i] += y_b[i];
			}

			PNode child = PiccoUtil.createVariableResolutionLine(c.getMetric(), x_a, y_a);
			lc.addChild(child);
		}
		return c;
	}

	//
	// called from R
	//

	public static double[] getSegment(HPSplitableLayer dataSig, double startTime, double endTime) {
		double[][] pts = getValuesInRange(dataSig.getNodes(), startTime, endTime);

		return pts[1];
	}

	//
	// called from R
	//

	public static Collection<PNode> getNodesInRange(HPSplitableLayer dataSig, double startTime, double endTime) {

		return dataSig.getNodesInRange(startTime, endTime);
	}

	//
	// called from R: Trend-Feature
	//

	public static double[] getXFromNodes(Collection<PNode> nodes) {
		double[] tm = new double[nodes.size()];
		int i = 0;
		Iterator<PNode> it = nodes.iterator();
		while (it.hasNext()) {
			tm[i++] = it.next().getX();
		}
		return tm;
	}

	//
	// called from R: BBB-step6
	//
	
//  df <- read.csv( "c:/tmp/842.csv" )
//	r <- c(1:200)
//	plot( x=df$X0[r], y= df$Y0[r], xlim=c(0,100), ylim=c(-300,620) )
//	points( x=r/3, y=df$CUMA0[r]/100 )
	
	private static double centroid_signedArea = 0;
	private static boolean verbose;
	public static void JAVA_centroid_area(double[] xx, double[] yy) {

		int n = xx.length;
		double x0 = xx[0];
		double y0 = yy[0];

		double A = 0;

		centroid_signedArea = 0;
		
		for (int i = 1; i < n; i++) {
			double x1 = xx[i];
			double y1 = yy[i];

			double a = (y0 - x0);
			double b = (y1 - x1);
			double h = (x1 - x0);
			A = (a + b) * h;
			centroid_signedArea = centroid_signedArea + A;
			if( verbose ) {
				// System.out.println("  (" + x0 + "*" + y1 + ") -   (" + x1 + "*" + y0 + ") --> " + a + " --> " + centroid_signedArea );
				System.out.println(" " + x0 + ", " + y0 + ", " + x1 + "," + y1 + ", " + a + ", " + centroid_signedArea );
			}
			x0 = x1;
			y0 = y1;
		}

		centroid_signedArea = centroid_signedArea * 0.5;

		return;
	}

	public static Point2D JAVA_centroid_trapezoid(double[] xx, double[] yy) {

		int n = xx.length;
		double x0 = xx[0];
		double y0 = yy[0];

		double a = 0;

		double Cx = 0;
		double Cy = 0;

		centroid_signedArea = 0;
		
		for (int i = 1; i < n; i++) {
			double x1 = xx[i];
			double y1 = yy[i];

			a = x0 * y1 - x1 * y0;
			centroid_signedArea = centroid_signedArea + a;
			if( verbose ) {
				// System.out.println("  (" + x0 + "*" + y1 + ") -   (" + x1 + "*" + y0 + ") --> " + a + " --> " + centroid_signedArea );
			}
			Cx = Cx + (x0 + x1) * a;
			Cy = Cy + (y0 + y1) * a;
			x0 = x1;
			y0 = y1;
		}

		centroid_signedArea = centroid_signedArea * 0.5;
		Cx = Cx / (6.0 * centroid_signedArea);
		Cy = Cy / (6.0 * centroid_signedArea);

		return new Point2D.Double(Cx, Cy);
	}
	//
	// called from R: BBB-step6
	//

	public static Point2D JAVA_moment(double[] xx, double[] yy, double Cx, double Cy) {
		int n = xx.length;
		double x0 = xx[0] - Cx;
		double y0 = yy[0] - Cy;

		double I_x = 0;
		double I_y = 0;
		for (int i = 1; i < n; i++) {
			double x1 = xx[i] - Cx;
			double y1 = yy[i] - Cy;

			I_x = I_x + (y0 * y0 + y0 * y1 + y1 * y1) * (x1 * y0 - x0 * y1);
			I_y = I_y + (x0 * x0 + x0 * x1 + x1 * x1) * (x1 * y0 - x0 * y1);

			x0 = x1;
			y0 = y1;
		}

		I_x = (I_x / 12) / 1000000;
		I_y = (I_y / 12) / 1000000;

		return new Point2D.Double(I_x, I_y);
	}

	//
	// called from R: BBB-step6
	//

	public static void init_centroids(HPSplitableLayer seg_sig, HPSplitableLayer x_sig, HPSplitableLayer y_sig, double startSecs, double stopSecs) { 
		// layer$addAttribute( "@centroid_seg_sig", seg_sig )
		
		Collection<PNode> rwave_nodes = seg_sig.getNodesInRange( startSecs, stopSecs );

		int n = rwave_nodes.size();
		if( n <= 0 ) {
			return;
		}
		
		String key = x_sig.getAlias();
		HPSplitableLayer yy_sig = y_sig;
		if( yy_sig == null ) {
			RpMetric metric = new RpMetric( "d" + x_sig.getLocation() + "/dt", null, null, x_sig.getUnit(), x_sig.getSubtyp() );
			yy_sig = new HPSplitableLayer(metric);
			derivative(yy_sig, x_sig);
			//HPPathLayer l2 = (HPPathLayer) yy_sig;
			// FIXME: fix the line here
			log.error("l2.applyFilter(null, 5);"); // mean of 5 points...
			GuiUtil.showMessage("Development error: @centroid_seg_sig feature is currently disabled.  Please notify the developer that it needs to be re-enabled.");
		}
		
		Iterator<PNode> it = rwave_nodes.iterator();
		 PNode prev_node = it.next();
		while( it.hasNext() ) {
			PNode next_node = it.next();

			double a = prev_node.getX();
			double b = next_node.getX();
			
			verbose = (a > 841) && (a < 843);
			
			if( verbose ) {
				System.out.println("Centroid at: " + a);
			}
			
			double[] xx = x_sig.getValuesInRange( a, b);
			double[] yy = yy_sig.getValuesInRange( a, b);

			Point2D centroid = JAVA_centroid_trapezoid(xx,yy);
			// double area0 = centroid_signedArea;
			JAVA_centroid_area(xx,yy);
			double area1 = centroid_signedArea;
//			if( Math.abs(area0 + area1) > 0.001 ) {
//				System.out.println("TM=" + a + " AREA ERROR: " + area0 + " != " + area1 );
//			}
			Point2D moment = JAVA_moment(xx,yy, centroid.getX(), centroid.getY() );
			Map<String,Object> map = new HashMap<>();
			if( y_sig != null ) {
				map.put("@y_sig", y_sig.getAlias());
			}
			map.put("centroid_x", centroid.getX() );	
			map.put("centroid_y", centroid.getY() );	
			map.put("area", (area1 > 0) ? area1 : -area1 );	
			map.put("moment_x", moment.getX() );
			map.put("moment_y", moment.getY() );
			map.put("systolic", Stats.max(xx) );
			map.put("diastolic", Stats.min(xx) );
			map.put("mean", Stats.mean(xx) );
			next_node.addAttribute(key, map );
			
			prev_node = next_node;
		}
		
	}

	//
	// called from R: Trend-Feature
	//

	public static double[] getAttributeFromNodes(Collection<PNode> nodes, String key) {
		double[] val = new double[nodes.size()];
		int i = 0;
		Iterator<PNode> it = nodes.iterator();
		String subkey = null;
		
		if( key.startsWith("{")) {
			int end = key.indexOf("}/");
			if( end < 0 ) {
				log.error("Could not find end of node name: " + key );
				return null;
			}
			
			subkey = key.substring( end+2 );
			key = key.substring(1, end);
		}
		while (it.hasNext()) {
			Object o = it.next().getAttribute(key);
			double v = Double.NaN;
			if( o == null ) {
				// NaN remains
			} else if( o instanceof Double ) {
				v = (Double)o;
			} else if (o instanceof Map && subkey != null) {
				Map map = (Map) o;
				v = (Double)map.get( subkey );
			}
			val[i++] = v ;
		}
		return val;
	}

	//
	// called from R
	//

	public static double[] getZeroCrossingTime(double[] dpdt, double[] dpdt_tm, double rwave_tm[]) {

		int p_pos = 0; // pressure position
		int zero_pos = 0;

		double[] zero_tms = new double[rwave_tm.length];
		;

		for (double tm0 : rwave_tm) {
			while (p_pos < dpdt_tm.length && dpdt_tm[p_pos] < tm0)
				p_pos++;
			if (p_pos == dpdt_tm.length)
				break;

			int end_pos = p_pos + 500;
			if (end_pos >= dpdt.length) {
				// we are falling off the end of the data
				break;
			}

			double crossing_tm = dpdt_tm[end_pos];
			int three_consec = 0;

			// find three consecutive negative dpdt points
			while (p_pos < end_pos && three_consec < 0) {
				if (dpdt[p_pos] < 0) {
					three_consec++;
				} else {
					three_consec = 0;
				}
			}

			// now find the zero
			for (int i = p_pos; i < end_pos; i++) {
				if (dpdt[i] > 0) {
					crossing_tm = dpdt_tm[i];
					break;
				}
			}
			zero_tms[zero_pos++] = crossing_tm;
		}

		return zero_tms;
	}

	//
	// called from R
	//

	public static double[] getDiastolTime(double[] pressure, double[] p_tm, double[] rwave_tm) {

		int p_pos = 0; // pressure position
		int diastol_pos = 0;

		double[] diastol_tms = new double[rwave_tm.length];

		for (double tm0 : rwave_tm) {
			while (p_pos < p_tm.length && p_tm[p_pos] < tm0)
				p_pos++;
			if (p_pos == p_tm.length)
				break;

			// now that we have found the position of the r_wave, trace it back
			// to find a min.
			int start_pos = p_pos - 100;
			if (start_pos < 0)
				continue;
			double min_pressure = pressure[start_pos];
			double min_tm = p_tm[start_pos];
			for (int i = start_pos; i < p_pos; i++) {
				if (pressure[i] < min_pressure) {
					min_pressure = pressure[i];
					min_tm = p_tm[i];
				}
			}
			diastol_tms[diastol_pos++] = min_tm;
		}

		return diastol_tms;
	}
	//
	// called from R
	//

	public static double[] getMean(double[] pressure, double[] p_tm, double start_tm[], double end_tm[], int dir) {

		int p_pos = 0; // pressure position
		int e_pos = 0; // end time position

		int mean_pos = 0;

		double[] means = new double[start_tm.length];

		// double dt = p_tm[1] - p_tm[0];
		for (double tm0 : start_tm) {
			while (e_pos < end_tm.length && (end_tm[e_pos] - tm0 <= 0.0001))
				e_pos++;
			while (p_pos < p_tm.length && (p_tm[p_pos] - tm0 <= -0.0001))
				p_pos++;
			if (e_pos == end_tm.length)
				break;
			if (p_pos == p_tm.length)
				break;

			double tm1 = end_tm[e_pos];

			double mean = 0;
			int n = 0;
			while (p_pos < p_tm.length && p_tm[p_pos] < tm1) {
				double p = pressure[p_pos];
				boolean skip = (dir == 1 && p < 0);
				if (!skip) {
					mean += p;
					n++;
				}
				p_pos++;
			}
			if (n > 0) {
				means[mean_pos] = mean / n;
			}
			log.info("BEAT mean[{}] = {} tm=({},{})", (mean_pos + 1), means[mean_pos], tm0, tm1);
			mean_pos++;
		}

		return means;
	}

	//
	// called from R
	//
	public static double[] getValuesAtTimes(double[] src, double[] src_tm, double[] req_tm) {
		double[] vals = new double[req_tm.length];

		int pos = 0;
		for (int i = 0; i < req_tm.length; i++) {
			double tm0 = req_tm[i];
			while (pos < src_tm.length && src_tm[pos] < tm0)
				pos++;
			if (pos >= src_tm.length)
				break;
			vals[i] = src[pos];
		}
		return vals;
	}

	//
	// called from R
	//
	public static double[] getTimeOfCrossing(double[] y, double[] y_tm, double start_tm[], double end_tm[],
			double threshold[]) {

		double[] crossing = new double[start_tm.length];

		int y_pos = 0;
		int e_pos = 0;

		int s_pos;
		outer: for (s_pos = 0; s_pos < start_tm.length; s_pos++) {
			double tm0 = start_tm[s_pos];
			double tm1 = end_tm[e_pos];
			double v = threshold[s_pos];

			/*
			 * find the segment end time
			 */
			while (tm0 >= tm1) {
				e_pos++;
				if (e_pos >= end_tm.length)
					break outer;
				tm1 = end_tm[e_pos];
			}

			inner: while (y_tm[y_pos] < tm1) {
				y_pos++;
				if (y_pos == y_tm.length)
					break outer;
				if (y_tm[y_pos] > tm0 && y[y_pos] < v)
					break inner;
			}

			crossing[s_pos] = y_tm[y_pos];
		}

		if (crossing.length != s_pos) {
			crossing = Arrays.copyOf(crossing, s_pos);
		}
		return crossing;

	}

	public static double getPositiveMean(double[] y, double[] y_tm, double start_tm, double end_tm) {
		// R helper function
		double[] arr_start_tm = { start_tm };
		double[] arr_end_tm = { end_tm };

		double[] out = getPositiveMean(y, y_tm, arr_start_tm, arr_end_tm);

		return out[0];
	}

	/*
	 * Used by B2B-step4 [AOP&LVP]sd Means.r
	 * 
	 * --> I'm expecting a mean for each beat, but getting a mean for the entire
	 *     series....maybe it should be calling getMean() where start_tm and end_tm are both
	 *     arrays.
	 */
	public static double [] getMean(double[] y, double[] y_tm, double start_tm, double end_tm) {
		// R helper function
		double[] arr_start_tm = { start_tm };
		double[] arr_end_tm = { end_tm };

		double[] out = getMean(y, y_tm, arr_start_tm, arr_end_tm, 0);

		return out;
	}

	public static double[] getPositiveMean(double[] y, double[] y_tm, double start_tm[], double end_tm[]) {
		return getMean(y, y_tm, start_tm, end_tm, 1);
	}

	/*
	 * Used by B2B-step4 [AOP&LVP]sd Means.r
	 *
	 * ... should be calling this, not the routine two lines above
	 */
	public static double[] getMean(double[] y, double[] y_tm, double start_tm[], double end_tm[]) {
		return getMean(y, y_tm, start_tm, end_tm, 0);
	}

	public static double[] getTimeOfMax(double[] dpdt, double[] p_tm, double start_tm[], double end_tm[]) {
		return getMaxMin(dpdt, p_tm, start_tm, end_tm, 2);
	}

	public static double[] getValueAt(double[] dpdt, double[] p_tm, double start_tm[]) {
		return getMaxMin(dpdt, p_tm, start_tm, null, 0);
	}

	public static double[] getTimeOfMin(double[] dpdt, double[] p_tm, double start_tm[], double end_tm[]) {
		return getMaxMin(dpdt, p_tm, start_tm, end_tm, -2);
	}

	public static double[] getMax(double[] dpdt, double[] p_tm, double start_tm[], double end_tm[]) {
		return getMaxMin(dpdt, p_tm, start_tm, end_tm, 1);
	}

	public static double[] getMin(double[] dpdt, double[] p_tm, double start_tm[], double end_tm[]) {
		return getMaxMin(dpdt, p_tm, start_tm, end_tm, -1);
	}

	public static double[] getMaxMin(double[] yy, double[] p_tm, double start_tm[], double end_tm[], int dir) {

		// yy may be pressure, or yy may be dpdt

		int p_pos = 0; // pressure position
		int e_pos = 0;
		int seq = 0;

		double[] maxmin = new double[start_tm.length];

		// double dt = p_tm[1] - p_tm[0];
		for (int s_pos = 0; s_pos < start_tm.length; s_pos++) {
			double tm0 = start_tm[s_pos];
			if (end_tm != null) {
				while (e_pos < end_tm.length && end_tm[e_pos] <= tm0)
					e_pos++;
				if (e_pos == end_tm.length)
					break;
			}

			while (p_pos < p_tm.length && p_tm[p_pos] < tm0)
				p_pos++;
			if (p_pos == p_tm.length)
				break;

			double tm1 = (end_tm == null) ? tm0 : end_tm[e_pos];
			double mm_pressure = yy[p_pos];
			maxmin[seq] = (dir == 2 || dir == -2) ? p_tm[p_pos] : mm_pressure;

			while (p_pos < p_tm.length && p_tm[p_pos] < tm1) {
				if (dir == 0) {
					maxmin[seq] = yy[p_pos];
				} else if (dir < 0) {
					if (yy[p_pos] < mm_pressure) {
						mm_pressure = yy[p_pos];
						maxmin[seq] = (dir == -2) ? p_tm[p_pos] : mm_pressure;
					}
				} else if (dir > 0) {
					if (yy[p_pos] > mm_pressure) {
						mm_pressure = yy[p_pos];
						maxmin[seq] = (dir == 2) ? p_tm[p_pos] : mm_pressure;
					}
				}
				p_pos++;
			}
			// System.out.print( seq + " dir=" + dir + " maxmin=" + maxmin[seq]
			// );
			seq++;
		}

		if (maxmin.length != seq) {
			maxmin = Arrays.copyOf(maxmin, seq);
		}
		return maxmin;
	}
	//
	// called from R
	//

	public static double[][] getSegments(HPSplitableLayer segmentsSig, HPSplitableLayer dataSig, double secsLeading,
			double secsTrailing) {

		double[][] arr = segmentsSig.getDataInRange(0, 1000);
		if (arr == null) {
			return null;
		}
		double[] xx = arr[0];
		return getSegments(xx, dataSig, secsLeading, secsTrailing);
	}

	//
	// called from R
	//

	public static double[][] getSegments(double[] tms, HPSplitableLayer dataSig, double secsLeading, double secsTrailing) {

		if (tms == null || tms.length == 0) {
			return null;
		}

		double[][] segs = new double[tms.length - 1][];

		int idx = 0;
		double prev = -1; // assign a value to make the compiler happy
		boolean first = true;
		for (double tm : tms) {
			if (!first) {
				double startX = prev + secsLeading;
				double endX = tm + secsTrailing;
				double[][] pts = getValuesInRange(dataSig.getNodes(), startX, endX);
				segs[idx++] = pts[1];
			}
			prev = tm;
			first = false;
		}

		return segs;
	}

	//
	// called from R
	//

	public static double[][] getSegments(double[] start_tms, double[] end_tms, HPSplitableLayer dataSig,
			double secsLeading, double secsTrailing) {

		if (start_tms == null || start_tms.length == 0) {
			return null;
		}

		double[][] segs = new double[start_tms.length][];

		int idx = 0;
		int j = 0;
		for (double tm : start_tms) {
			while (end_tms[j] <= tm) {
				j++;
				if (j == end_tms.length) {
					break;
				}
			}
			double startX = tm + secsLeading;
			double endX = end_tms[j] + secsTrailing;
			double[][] pts = getValuesInRange(dataSig.getNodes(), startX, endX);
			segs[idx++] = pts[1];
		}

		return segs;
	}

	//
	// multiple return values not allowed in Java. This is a
	// non-thread-safe kludge
	//
	// so i'm thinking about it
	//

	public static int getNodesInRange(ArrayList<PNode> dest, Collection<PNode> nodes, double startX, double endX) {

		return OfflineSignal.getNodesInRange(dest, nodes, startX, endX);
	}

	/*
	 * called from R
	 */
	public static double[] getXValues(double[][] vals) {
		if (vals == null) {
			return null;
		}
		return vals[0];
	}

	/*
	 * called from R
	 */
	public static double[] getYValues(double[][] vals) {
		if (vals == null) {
			return null;
		}
		return vals[1];
	}

	/*
	 * called from R
	 */
	public static double[] getYValuesInRange(HPSplitableLayer sig, double startX, double endX) {
		double[][] vals = getValuesInRange(sig.getNodes(), startX, endX);
		if (vals == null) {
			return null;
		}
		return vals[1];
	}

	/*
	 * called from R
	 */
	public static double[] getXValuesInRange(HPSplitableLayer sig, double startX, double endX) {
		double[][] vals = getValuesInRange(sig.getNodes(), startX, endX);
		if (vals == null) {
			return null;
		}
		return vals[0];
	}

	/*
	 * called from R
	 */
	public static double[][] getValuesInRange(HPSplitableLayer sig, double startX, double endX) {
		return getValuesInRange(sig.getNodes(), startX, endX);
	}

	public static double[][] getValuesInRange(Collection<PNode> nodes, double startX, double endX) {

		double[] d_x = new double[5000];
		double[] d_y = new double[5000];

		int sz = 0;
		for (PNode node : nodes) {
			double[][] ar2 = getValuesFromNode(node, startX, endX);
			if (ar2 != null) {
				double[] s_x = ar2[0];
				double[] s_y = ar2[1];
				int pts = s_x.length;
				if (pts < 1) {
					continue;
				}

				double x0 = s_x[0];
				if (x0 < startX || x0 > endX) {
					continue;
				}

				if (pts + sz >= d_x.length) {
					d_x = Arrays.copyOf(d_x, d_x.length + 10000);
					d_y = Arrays.copyOf(d_y, d_y.length + 10000);
				}

				for (int i = 0; i < pts; i++) {
					d_x[sz] = s_x[i];
					d_y[sz] = s_y[i];
					sz++;
				}

			}
		}

		d_x = Arrays.copyOf(d_x, sz);
		d_y = Arrays.copyOf(d_y, sz);

		double[][] ar = new double[2][];
		ar[0] = d_x;
		ar[1] = d_y;

		return ar;
	}

	@SuppressWarnings("unchecked")
	public static double[][] getValuesFromNode(PNode node, double startX, double endX) {

		int pos = 0;
		int n = -1;

		if (endX < 0) {
			endX = Double.MAX_VALUE;
		}
		PathIterator it = null;
		if (node instanceof HPPath) {
			HPPath p = (HPPath) node;
			double x = p.getX();
			double w = p.getWidth();

			if (startX != endX) {

				if ((x + w) < startX || x > endX) {

					if (x < startX) {
						// BLIND: big assumption, only one point / path
						// works for signal if startX == 0...since this function
						// never called
						// works for fiducial always
						kludge_points_skipped++;
					}

					return null;
				}
			}

			LineShape line = p.getLineReference();
			it = line.getPathIterator(null);

			n = line.getPointCount();

		} else if (node instanceof PPath.Float || node instanceof PLine) { // covers
																			// SwitchableNode
			n = 1;
		} else if (node instanceof PPath) { // ouch....how this overlaps with
											// PPath.Float

			PPath p = (PPath) node;
			double x = p.getX();
			double w = p.getWidth();

			if (startX != endX) {

				if ((x + w) < startX || x > endX) {

					if (x < startX) {
						// BLIND: big assumption, only one point / path
						// works for signal if startX == 0...since this function
						// never called
						// works for fiducial always
						kludge_points_skipped++;
					}

					return null;
				}
			}

			Path2D path = p.getPathReference();
			it = path.getPathIterator(null);

			while (!it.isDone()) {
				log.error("INTERNAL ERROR: FIXME: find class for better efficiency");
				it.next();
				n++;
			}
			it = path.getPathIterator(null);
		} else if (node instanceof PNode) {
			// fiducial points loaded from XML file....hmm!
			// d_y[pos] = node.getY();
			// pos++;
			n = 1;
		}

		if (n == 0) {
			log.error("INTERNAL ERROR: FIXME -- unknown number of points!");
			n = 1000;
		}
		double[] d_x = new double[n]; // WARNING: no node should be permitted
		// to have this many values!!!
		double[] d_y = new double[n]; // it is probably already limited to

		// 101 points
		if (it != null) {

			double[] coords = new double[6];
			while (!it.isDone()) {

				it.currentSegment(coords);
				// BLIND: assumptions about evenly spaced
				double x0 = coords[0];
				double y0 = coords[1];
				if (x0 >= startX && x0 <= endX) {
					d_x[pos] = x0;
					d_y[pos] = y0;
					pos++;
				} else if (x0 < endX) {
					kludge_points_skipped++;
				}
				it.next();
			}

		} else {
			double x0 = node.getX();
			double y0 = node.getY();

			if (x0 >= startX && x0 <= endX) {
				d_x[pos] = x0;
				d_y[pos] = y0;
				pos++;
			} else if (x0 < endX) {
				kludge_points_skipped++;
			}
		}

		double[][] ar = null;
		if (pos < n) {
			d_x = Arrays.copyOf(d_x, pos);
			d_y = Arrays.copyOf(d_y, pos);

		}

		if (pos > 0) {
			ar = new double[2][];
			ar[0] = d_x;
			ar[1] = d_y;
		}

		return ar;
	}

	@SuppressWarnings("unchecked")
	public static double[][] getValuesFromNode(PAffineTransform tran, PNode node) {
		double[] d_x = null;
		double[] d_y = null;

		int pos = 0;
		int tot = -1;

		PathIterator it = null;
		if (node instanceof HPPath) {
			HPPath p = (HPPath) node;

			LineShape line = p.getLineReference();
			it = line.getPathIterator(null);

			tot = line.getPointCount();
		} else if (node instanceof PPath) {

			PPath p = (PPath) node;
			double x = p.getX();
			double w = p.getWidth();

			Path2D path = p.getPathReference();
			it = path.getPathIterator(null);

			tot = 0;
			while (!it.isDone()) {
				it.next();
				tot++;
			}
			it = path.getPathIterator(null);

		} else if (node instanceof PLine) {
			// assume a vertical line
			double x0 = ((PLine) node).getX();
			double y0 = ((PLine) node).getY();

			d_x = new double[1];
			d_y = new double[1];
			d_x[pos] = x0;
			d_y[pos] = y0;
			pos++;
		} else {
			// d_x and d_y are null
		}

		if (it != null) {

			// cut off the last point...its overlap with next seg
			tot = tot - 1;

			d_x = new double[tot];
			d_y = new double[tot];

			double[] coords = new double[6];
			while (tot > 0 && !it.isDone()) {

				tot--;
				it.currentSegment(coords);
				it.next();

				double x0 = coords[0];
				double y0 = coords[1];
				d_x[pos] = x0;
				d_y[pos] = y0;
				pos++;
			}

			if (pos != d_x.length) {
				d_x = Arrays.copyOf(d_x, pos);
				d_y = Arrays.copyOf(d_y, pos);
			}
		}

		if( tran != null && d_x != null) {  // d_x is null at end of the data
			for( int i = 0; i < d_x.length; i++) {
				d_x[i] = d_x[i] + tran.getTranslateX();
				d_y[i] = d_y[i]*tran.getScaleY() + tran.getTranslateY();
			}
		}
		
		double[][] ar = null;
		if (pos > 0) {
			ar = new double[2][];
			ar[0] = d_x;
			ar[1] = d_y;
		}
		

		return ar;
	}

	public static double[] getMinMaxInRange(Collection<PNode> nodes, double startX, double endX) {
		double[] minmax = new double[2];
		minmax[0] = Double.MAX_VALUE;
		minmax[1] = Double.MIN_VALUE;
		for (PNode node : nodes) {
			getMinMaxInNode(node, startX, endX, minmax);
		}
		return minmax;
	}

	private static void getMinMaxInNode(PNode node, double startX, double endX, double[] minmax) {

		PathIterator it = null;
		if (node instanceof HPPath) {
			HPPath p = (HPPath) node;
			double x = p.getX();
			double w = p.getWidth();

			if ((x + w) < startX || x > endX) {
				return;
			}

			LineShape line = p.getLineReference();
			it = line.getPathIterator(null);
		} else if (node instanceof PLine) {
			// assume a vertical line
			double x0 = ((PLine) node).getX();
			double y0 = ((PLine) node).getY();

			if (x0 >= startX && x0 <= endX) {
				if (y0 < minmax[0]) {
					minmax[0] = y0;
				}
				if (y0 > minmax[1]) {
					minmax[1] = y0;
				}
			}

		} else if (node instanceof LinkedNode) {
			double x0 = ((LinkedNode) node).getX();
			double y0 = ((LinkedNode) node).getY();

			if (x0 >= startX && x0 <= endX) {
				if (y0 < minmax[0]) {
					minmax[0] = y0;
				}
				if (y0 > minmax[1]) {
					minmax[1] = y0;
				}
			}
		} else if (node instanceof PPath) {
			PPath p = (PPath) node;
			double x = p.getX();
			double w = p.getWidth();

			if ((x + w) < startX || x > endX) {
				return;
			}

			Path2D path = p.getPathReference();
			it = path.getPathIterator(null);

		}

		if (it != null) {
			double[] coords = new double[6];
			while (!it.isDone()) {
				it.next();

				if (!it.isDone()) { // BLIND: ?? we have to ignore the last
					// point...is this the way?
					it.currentSegment(coords);
					double y0 = coords[1];
					if (y0 < minmax[0]) {
						minmax[0] = y0;
					}
					if (y0 > minmax[1]) {
						minmax[1] = y0;
					}
				}
			}
		}

		return;
	}

	public static double getValueAtPoint(PLayer layer, double xpos) {

		if( layer == null ) {
			return Double.NaN;
		}
		// find the node of interest
		List<PNode> nodes = layer.getChildrenReference();

		PNode node = null;
		for (PNode next : nodes) {
			double x = next.getX();
			if (x > xpos) {
				break;
			}
			node = next;
		}

		RpMetric sig = (RpMetric) layer.getAttribute("sig");

		RpUnit unit = null;
		if (sig != null) {
			unit = sig.getUnit();
		}
		return getValueAtPoint(node, xpos, unit);
	}

	public static double[] getValueAtPoint(PLayer layer, double[] xposs) {

		double[] results = new double[xposs.length];

		List<PNode> nodes = layer.getChildrenReference();
		Iterator<PNode> it = nodes.iterator();

		int idx = 0;
		PNode next = it.next();
		for (double xpos : xposs) {
			PNode node = null;
			while (it.hasNext()) {
				double x = next.getX();
				if (x > xpos) {
					break;
				}
				node = next;
				next = it.next();
			}

			RpMetric sig = (RpMetric) layer.getAttribute("sig");

			RpUnit unit = null;
			if (sig != null) {
				unit = sig.getUnit();
			}
			results[idx++] = getValueAtPoint(node, xpos, unit);
		}
		return results;
	}

	public static double getValueAtPoint(PNode node, double xpos, RpUnit unit) {

		if (node == null) {
			return Double.NaN;
		}

		double y = Double.NaN;

		PathIterator it = null;
		if (node instanceof HPPath) {

			HPPath p = (HPPath) node;

			LineShape line = p.getLineReference();
			it = line.getPathIterator(null);

		} else if (node instanceof PLine) { // assume a vertical line...should
											// not happen!
			y = ((PLine) node).getY();
			log.error("FIXME: unexpected use case PLine");
		} else if (node instanceof LinkedNode) {
			y = ((LinkedNode) node).getY();
		} else if (node instanceof PPath) {
			PPath p = (PPath) node;

			Path2D path = p.getPathReference();
			it = path.getPathIterator(null);
		}

		if (it != null) {
			double[] coords = new double[6];
			while (!it.isDone()) {
				it.next();

				if (!it.isDone()) { // BLIND: ?? we ignore the last pt??
					it.currentSegment(coords);
					double x0 = coords[0];
					y = coords[1];
					// there may be float/double conversion or other small
					// perturbation giving a small difference
					if (xpos - x0 < 0.00001) {
						break;
					}
				}
			}
		}

		if (unit != null) {
			y = unit.transform_d(y);
		}

		return y;
	}

}
