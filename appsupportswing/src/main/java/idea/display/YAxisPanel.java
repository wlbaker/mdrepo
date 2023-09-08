package idea.display;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.text.DecimalFormat;
import java.text.NumberFormat;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class YAxisPanel extends JPanel implements ScaleChangeListener {
	double yMax = 1;
	double yMin = 0;
	int verbose = 0;

	Color axisColor = Color.YELLOW;
	Color labelColor = Color.WHITE;

	protected BasicStroke stroke = new BasicStroke(2);
	private String title;
	private boolean rotateLabel = false;
	private Double minRange = null;

	NumberFormat df0 = new DecimalFormat("#,###");
	NumberFormat df1 = new DecimalFormat("#,###.0");
	NumberFormat df2 = new DecimalFormat("0.00");

	public YAxisPanel() {

		setBackground(null);
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);

		if( !isVisible() ) {
			return;
		}
		
		Dimension d;

		d = getSize();

		Graphics2D g2 = (Graphics2D) g;

		g2.setColor(axisColor);

		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2.setStroke(stroke);
		g2.drawLine(d.width - 5, 2, d.width - 5, d.height - 2);

		NumberFormat df = df0;
		double diff = Math.abs( yMax - yMin );
		if (diff < 10) {
			df = df1;
		}
		if (diff < 1) {
			df = df2;
		}
		String yMinText = df.format(yMin);
		String yMaxText = df.format(yMax);

		FontMetrics metrics = g2.getFontMetrics(g2.getFont());
		// get the height of a line of text in this font and render context

		int hgt = metrics.getHeight();
		// get the advance of my text in this font and render context
		int adv = metrics.stringWidth(yMinText);
		g2.drawString(yMinText, d.width - 10 - adv, hgt);
		adv = metrics.stringWidth(yMaxText);
		g2.drawString(yMaxText, d.width - 10 - adv, d.height - 2);

		if (title != null) {
			if (rotateLabel) {
				adv = metrics.stringWidth(title);
				// g2.rotate(arg0, arg1, arg2)
				g2.translate(d.width / 2, d.height - (d.height - adv) / 2);
				g2.rotate(-Math.PI / 2.0);
			} else {
				g2.translate(6, (d.height + hgt) / 2);
			}
			g2.setColor(labelColor);
			g2.drawString(title, 0, 0);
		}
		g2.dispose();
	}

	public void setLabelRotation(boolean b) {
		rotateLabel = b;
	}
	
	public void setAxisLabel(String title) {
		this.title = title;
	}

	public String getAxisLabel() {
		return title;
	}

	public String getTitle() {
		return this.title;
	}

	public void setScale(double yMin, double yMax) {
		this.yMin = yMin;
		this.yMax = yMax;
		if( isVisible() && verbose  > 0 ) {
			System.out.println( "setScale: " + yMin + " to " + yMax);
		}
	}

	@Override
	public void scaleChange(double vMin, double vMax) {
		setScale(vMin, vMax);

		repaint();
	}

}
