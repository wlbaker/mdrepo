package idea.display.elegant;

import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.font.FontRenderContext;
import java.awt.font.LineMetrics;
import java.awt.geom.AffineTransform;

import javax.swing.JLabel;

@SuppressWarnings("serial")
class ScaledLabel extends JLabel {

	private double fixed_scale;

	public ScaledLabel(  ) {
		this(0.0);
	}
	
	public ScaledLabel( double fixed_scale ) {
		super("?");
		this.fixed_scale = fixed_scale;
		
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		if (isOpaque()) {
			g.setColor(getBackground());
			g.fillRect(0, 0, getWidth(), getHeight());
		}

		String s = getText();

		Graphics2D g2 = (Graphics2D) g;

		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON);
		FontRenderContext frc = g2.getFontRenderContext();
		Font font = g2.getFont().deriveFont(16f);
		g2.setFont(font);
		float sw = (float) font.getStringBounds(s, frc).getWidth();
		LineMetrics lm = font.getLineMetrics(s, frc);
		float sh = lm.getAscent() + lm.getDescent();

		Rectangle r = new Rectangle();
		r.setSize(getSize());

		// g2.setPaint(Color.pink);
		// g2.fill(r);

		// scale text to fit and center in r
		double scale;
		double tx = 0;
		double ty = 0;
		if( fixed_scale == 0 ) {
			double xScale = r.width / sw;
			double yScale = r.height / sh;
			scale = Math.min(xScale, yScale);
			tx = r.x + scale * (r.width - scale * sw) / 4; // WRONG!!!
			ty = r.getMaxY() - lm.getDescent();
		} else {
			scale = fixed_scale;
			tx = r.x + scale * (r.width - scale * sw) / 4; // WRONG!!!
			ty = r.getMaxY() - lm.getDescent();
		}

		AffineTransform at = AffineTransform.getTranslateInstance(tx, ty);
		at.scale(scale, scale);
		g2.setColor(getForeground());
		g2.setFont(font.deriveFont(at));
		g2.drawString(s, 0, 0);
	}
}
