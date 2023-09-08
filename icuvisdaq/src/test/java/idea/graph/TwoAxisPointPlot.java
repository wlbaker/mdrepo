package idea.graph;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.ComponentListener;
import java.util.LinkedList;
import java.util.List;



class ColorPoint {
	double x;
	double y;
	Color c;

	public ColorPoint(double x, double y, Color c) {
		this.x = x;
		this.y = y;
		this.c = c;
	}
}

@SuppressWarnings("serial")
public class TwoAxisPointPlot extends BufferedGraph implements ComponentListener {
	
	private List<ColorPoint> list;
	private int maxPoints = 100;

	
	public TwoAxisPointPlot() {
		list = new LinkedList<ColorPoint>();
		
		addComponentListener(this);
	}

	public void setYScale( double yMin, double yMax ) {
		this.yMin = yMin;
		this.yMax = yMax;
	}
	/*
	 * a few getters and setters
	 */
	public int getMaxPoints() {
		return maxPoints;
	}

	public void setMaxPoints(int maxPoints) {
		this.maxPoints = maxPoints;
	}

	/*
	 * the real meat and potatoes starts here
	 */
	
	public void addPoint( double x, double y, Color c ) {
		
		ColorPoint pt = new ColorPoint( x, y, c );
		list.add( pt );
		while( list.size() > maxPoints ) {
			list.remove(0);
		}
		
		// if( incrementalRender && image != null ) {
			Graphics2D g = (Graphics2D) image.getGraphics();
			
			int h = getHeight();
			transformToGraphCoordinages(g, h);

			drawPoint( g, pt );
			
			g.dispose();
		// }

	}

	@Override
	public void clear() {
		list = new LinkedList<ColorPoint>();
		super.clear();
	}

	@Override
	protected void render(Graphics2D g) {
		int w = getWidth();
		int h = getHeight();
		
		g.setColor(getBackground());
		g.fillRect(0, 0, w, h );
		
		g.drawLine( 0, 0, w - 20, 0 );
		g.drawLine( 0, 0, 0, h - 10 - BOTTOM_MARGIN );

		transformToGraphCoordinages(g, h);
		
		g.setStroke( stroke );
		g.setColor( Color.GRAY );
		
		for( ColorPoint pt : list ) {
			drawPoint( g, pt );
		}
	}

	private void drawPoint(Graphics2D g, ColorPoint pt) {
		double x_scale = 0.50;
		double y_scale = 1.0;
		double x_offset = 60;
		double y_offset = 35;
		
		int x = (int)(pt.x * x_scale + x_offset);
		int y = (int)(pt.y * y_scale + y_offset);
		
		g.setColor(pt.c);
		g.drawRect( x, y, 3, 3);
	}


}
