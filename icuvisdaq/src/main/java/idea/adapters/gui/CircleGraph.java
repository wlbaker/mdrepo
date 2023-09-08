package idea.adapters.gui;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.text.DecimalFormat;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class CircleGraph extends JPanel {

	private int data_pos = 0;
	private int[] xdata = new int[1024];
	private int[] ydata = new int[1024];

	BufferedImage bufferedImage;

	private Color bg = Color.white;
	private Color fg = Color.black;

	private boolean drawTitle = true;
	private String title = "PAW vs VOL";

	private boolean drawXTitle = true;
	private String xAxis = "VOL";
	private boolean drawYTitle = true;
	private String yAxis = "PAW";

	private boolean drawXTicks = true;
	private boolean drawYTicks = true;
	private boolean drawLegend = false;

	int xMax = -150;
	int xMin = 150;
	int yMax = -150;
	int yMin = 150;
	private int x2;
	private int y2;
	private int verbose = 0;

	private final static int IM_WIDTH = 100;
	private final static int IM_HEIGTH = 100;

	public CircleGraph(String xAxis, String yAxis) {
		this.xAxis = xAxis;
		this.yAxis = yAxis;
		this.title = null;
		this.drawTitle = false;

		// OK...300 chosen out of the blue
		bufferedImage = new BufferedImage(IM_WIDTH, IM_HEIGTH, BufferedImage.TYPE_INT_ARGB);

	}

	public void addPath(int[] x, int[] y) {
		for (int i = 0; i < x.length; i++) {
			xdata[data_pos] = x[i];
			ydata[data_pos] = y[i];
			data_pos++;
			if (data_pos >= xdata.length) {
				data_pos = 0;
				clear();
			}
		}

		drawData(x, y, x.length);

	}

	private void clear() {
		Graphics2D g = bufferedImage.createGraphics();

		int width = bufferedImage.getWidth();
		int height = bufferedImage.getHeight();

		this.setOpaque(true);

		// clear the panel
		g.setColor(bg);
		g.fillRect(0, 0, width, height);
	}

	/**
	 * Creates a BufferedImage of the actual data plot.
	 * 
	 * After doing some profiling, it was discovered that 90% of the drawing
	 * time was spend drawing the actual data (not on the axes or tick marks).
	 * Since the Graphics2D has a drawImage method that can do scaling, we are
	 * using that instead of scaling it ourselves. We only need to draw the data
	 * into the bufferedImage on startup, or if the data or gradient changes.
	 * This saves us an enormous amount of time. Thanks to Josh Hayes-Sheen
	 * (grey@grevian.org) for the suggestion and initial code to use the
	 * BufferedImage technique.
	 * 
	 * Since the scaling of the data plot will be handled by the drawImage in
	 * paintComponent, we take the easy way out and draw our bufferedImage with
	 * 1 pixel per data point. Too bad there isn't a setPixel method in the
	 * Graphics2D class, it seems a bit silly to fill a rectangle just to set a
	 * single pixel...
	 * 
	 * This function should be called whenever the data or the gradient changes.
	 */
	private void drawData(int[] xdata, int[] ydata, int pos) {
		Graphics2D g = bufferedImage.createGraphics();

		AffineTransform tr = new AffineTransform(0.1, 0.0, 0.0, 0.1, IM_WIDTH / 2, IM_HEIGTH / 2);
		g.setTransform(tr);

		int x1 = x2;
		int y1 = y2;

		g.setColor(fg);

		for (int idx = 0; idx < pos; idx++) {
			x2 = xdata[idx];
			y2 = ydata[idx];

			g.drawLine(x1, IM_HEIGTH - y1, x2, IM_HEIGTH - y2);
			y1 = y2;
			x1 = x2;

			if (verbose  > 0) {
				if (idx < 20) {
					System.out.print(x1 + "," + y1 + " ");
				}
				if (idx == 20) {
					System.out.println();
				}
			}
		}
		g.dispose();
	}

	/**
	 * The overridden painting method, now optimized to simply draw the data
	 * plot to the screen, letting the drawImage method do the resizing. This
	 * saves an extreme amount of time.
	 */
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D) g;

		int width = this.getWidth();
		int height = this.getHeight();

		this.setOpaque(true);

		// clear the panel
		g2d.setColor(bg);
		g2d.fillRect(0, 0, width, height);

		if (bufferedImage == null) {
			drawData(xdata, ydata, data_pos);
		}

		// The data plot itself is drawn with 1 pixel per data point, and the
		// drawImage method scales that up to fit our current window size. This
		// is very fast, and is much faster than the previous version, which 
		// redrew the data plot each time we had to repaint the screen.
		g2d.drawImage(bufferedImage, 31, 31, width - 30, height - 30, 0, 0, bufferedImage.getWidth(), bufferedImage.getHeight(), null);

		// border
		g2d.setColor(fg);
		g2d.drawRect(30, 30, width - 60, height - 60);

		// title
		if (drawTitle && title != null) {
			g2d.drawString(title, (width / 2) - 4 * title.length(), 20);
		}

		// axis ticks - ticks start even with the bottom left coner, end very close to end of line (might not be right on)
		int numXTicks = (width - 60) / 50;
		int numYTicks = (height - 60) / 50;

		String label = "";
		DecimalFormat df = new DecimalFormat("##.##");

		// Y-Axis ticks
		if (drawYTicks) {
			int yDist = (int) ((height - 60) / (double) numYTicks); //distance between ticks
			for (int y = 0; y <= numYTicks; y++) {
				g2d.drawLine(26, height - 30 - y * yDist, 30, height - 30 - y * yDist);
				label = df.format(((y / (double) numYTicks) * (yMax - yMin)) + yMin);
				int labelY = height - 30 - y * yDist - 4 * label.length();
				//to get the text to fit nicely, we need to rotate the graphics
				g2d.rotate(Math.PI / 2);
				g2d.drawString(label, labelY, -14);
				g2d.rotate(-Math.PI / 2);
			}
		}

		// Y-Axis title
		if (drawYTitle && yAxis != null) {
			//to get the text to fit nicely, we need to rotate the graphics
			g2d.rotate(Math.PI / 2);
			g2d.drawString(yAxis, (height / 2) - 4 * yAxis.length(), -3);
			g2d.rotate(-Math.PI / 2);
		}

		// X-Axis ticks
		if (drawXTicks) {
			int xDist = (int) ((width - 60) / (double) numXTicks); //distance between ticks
			for (int x = 0; x <= numXTicks; x++) {
				g2d.drawLine(30 + x * xDist, height - 30, 30 + x * xDist, height - 26);
				label = df.format(((x / (double) numXTicks) * (xMax - xMin)) + xMin);
				int labelX = (31 + x * xDist) - 4 * label.length();
				g2d.drawString(label, labelX, height - 14);
			}
		}

		// X-Axis title
		if (drawXTitle && xAxis != null) {
			g2d.drawString(xAxis, (width / 2) - 4 * xAxis.length(), height - 3);
		}

		// Legend
		if (drawLegend) {
			//            g2d.drawRect(width - 20, 30, 10, height - 60);
			//            for (int y = 0; y < height - 61; y++)
			//            {
			//                int yStart = height - 31 - (int) Math.ceil(y * ((height - 60) / (colors.length * 1.0)));
			//                yStart = height - 31 - y;
			//                g2d.setColor(colors[(int) ((y / (double) (height - 60)) * (colors.length * 1.0))]);
			//                g2d.fillRect(width - 19, yStart, 9, 1);
			//            }
		}
	}

}
