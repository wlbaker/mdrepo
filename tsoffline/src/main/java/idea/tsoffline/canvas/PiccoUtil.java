package idea.tsoffline.canvas;

import java.awt.Color;

import org.piccolo2d.extras.nodes.PLine;
import org.piccolo2d.extras.util.LineShape;
import org.piccolo2d.extras.util.XYArray;

import idea.schema.rp.RpMetric;
import idea.tsoffline.AppConstants;

public class PiccoUtil {

	@Deprecated
	public static PLine createPolyline(double[] xp, double[] yp) {
		final LineShape path = new LineShape( new XYArray(xp.length) );
		for (int i = 0; i < xp.length; i++) {
			path.addPoint(i, xp[i], yp[i]);
		}
		final PLine result = new PLine(path);

		result.setPaint(Color.white);
		return result;
	}

	public static void appendPolyline(PLine node, double[] xp, double[] yp, int off, int len) {
		
		LineShape line = node.getLineReference();
		int n = line.getPointCount();
		while( len > 0 ) {
			line.addPoint(n++, xp[off], yp[off]);
			off++;
			len--;
		}
	}

	/**
	 * Creates a PPath for the poly-line for the given points.
	 * 
	 * @param xp
	 *            array of x components of the points of the poly-lines
	 * @param yp
	 *            array of y components of the points of the poly-lines
	 * 
	 * @return created poly-line for the given points
	 */
	public static PLine createVariableResolutionLine(RpMetric sig, final double[] xp, final double[] yp) {
		
		// PERFORMANCE: add all the points to the xy array before adding to the LineShape
		XYArray xy = new XYArray( xp.length );  
		for (int i = 0; i < xp.length; i++) {
			xy.addPoint(i, xp[i], yp[i]);
		}
		
		return createVariableResolutionLine( sig, xy );
	}
	
	public static PLine createVariableResolutionLine(RpMetric sig, XYArray xy ) {
		// PERFORMANCE: don't add points individually at this stage...updateBounds is called for each point added!
		// BUG-FEATURE: updateBounds really should be called automatically on the xy constructor, but it isnt.
		final LineShape path = new LineShape( xy  );
		path.updateBounds();  

		final HPPath result = new HPPath(path, AppConstants.getDefaultSignalStroke(), sig);

		return result;
	}

}
