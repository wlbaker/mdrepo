package idea.graph;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.Transparency;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.geom.Line2D;

import javax.swing.JPanel;

import idea.buffer.SignalBuffer;

@SuppressWarnings("serial")
public class BufferedGraph extends JPanel implements ComponentListener {

	public enum Direction {
		LEFT_TO_RIGHT, RIGHT_TO_LEFT
	}

	private Direction direction;
	protected Image image = null;

	protected final int BOTTOM_MARGIN = 30;
	protected final int LEFT_MARGIN = 10;
	protected final int RIGHT_MARGIN = 10;

	protected BasicStroke stroke;

	public BufferedGraph() {
		setStrokeWidth(1.0f);
	}

	//
	float m = 0.05f;
	double yMin = 0.0;
	double yMax = 100.0;
	float b = 0.0f;

	public void addDoubleLine(SignalBuffer<Double> data, Color c) {
		clear();

		if (data.getSampleCount() < 2) {
			return;
		}

		if (image == null) {
			return; // WARNING: Image in transition
		}

		Graphics2D g = (Graphics2D) image.getGraphics();

		int h = getHeight();
		int w = getWidth();
		transformToGraphCoordinages(g, h);

		g.setColor(c);

		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g.setStroke(stroke);

		int x1 = (direction == Direction.LEFT_TO_RIGHT) ? 0 : w - LEFT_MARGIN - RIGHT_MARGIN;
		double y1 = data.get(0);

		for (int i = 1; i < data.getSampleCount(); i++) {

			int x2 = (direction == Direction.LEFT_TO_RIGHT) ? x1 + 1 : x1 - 1;
			double y2 = data.get(i);

			g.draw(new Line2D.Double(x1, y1, x2, y2));

			x1 = x2;
			y1 = y2;

		}
		g.dispose();

	}

	public void addLine(SignalBuffer<Integer> data, Color c) {

		clear();

		if (data.getSampleCount() < 2) {
			return;
		}

		if (image == null) {
			return; // WARNING: we should probably create it if it is null...hmm..
		}

		Graphics2D g = (Graphics2D) image.getGraphics();

		int h = getHeight();
		int w = getWidth();
		transformToGraphCoordinages(g, h);

		g.setColor(c);

		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g.setStroke(stroke);

		int x1 = (direction == Direction.LEFT_TO_RIGHT) ? 0 : w - LEFT_MARGIN - RIGHT_MARGIN;
		int y1 = data.get(0);

		for (int i = 1; i < data.getSampleCount(); i++) {

			int x2 = (direction == Direction.LEFT_TO_RIGHT) ? x1 + 1 : x1 - 1;
			int y2 = data.get(i);

			g.drawLine(x1, y1, x2, y2);

			x1 = x2;
			y1 = y2;

		}
		g.dispose();

	}

	public void setStrokeWidth(float width) {
		stroke = new BasicStroke(width);
	}

	// **************************************

	public Direction getDirection() {
		return direction;
	}

	public void setDirection(Direction direction) {
		this.direction = direction;
	}

	@Override
	public void componentHidden(ComponentEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void componentMoved(ComponentEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void componentResized(ComponentEvent e) {
		image = null; // checkImage();
		repaint();
	}

	@Override
	public void componentShown(ComponentEvent e) {
		// TODO Auto-generated method stub

	}

	protected void checkImage() {
		Dimension dim = getSize();
		if (dim.width == 0) { // this can happen for not-yet-rendered
			// components
			dim = new Dimension(100, 100);
		}
		if (image == null || image.getWidth(null) != dim.width || image.getHeight(null) != dim.height) {
			// image = createImage(dim.width, dim.height);

			GraphicsConfiguration gc = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice()
					.getDefaultConfiguration();

			image = gc.createCompatibleImage(dim.width, dim.height, Transparency.TRANSLUCENT);

		}
	}

	public void clear() {
		if (image != null) {
			Graphics2D graphics = (Graphics2D) image.getGraphics();

			graphics.setColor(getBackground());
			graphics.fillRect(0, 0, image.getWidth(null), image.getHeight(null));

			render(graphics);

			graphics.dispose();
		}
	}

	protected void render(Graphics2D g) {
		int w = getWidth();
		int h = getHeight();

		g.setColor(getBackground());
		g.fillRect(0, 0, w, h);

		transformToGraphCoordinages(g, h);

		// g.setColor(Color.GRAY);
		// g.drawLine(0, 0, w - 20, 0);
		// g.drawLine(0, 0, 0, h - 10 - BOTTOM_MARGIN);

	}

	@Override
	public void paint(Graphics g) {

		this.setOpaque(false);
		// super.paint(g); // sets the background

		if (image == null) {
			// Dimension dim = getSize();
			checkImage(); // check for size changes

			clear();
		}

		synchronized (image) {
			g.drawImage(image, 0, 0, null);
		}

		g.dispose();
	}

	protected void transformToGraphCoordinages(Graphics2D g, int h) {
		b = (float) yMin;
		if (yMax != yMin) {
			m = (float) (h / (yMax - yMin));
		}

		g.scale(1.0, -m);
		g.translate(LEFT_MARGIN, -h / m - yMin);
		// g.translate( LEFT_MARGIN, (-h + BOTTOM_MARGIN) / m);
	}

}
