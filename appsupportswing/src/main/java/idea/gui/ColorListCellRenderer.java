package idea.gui;

import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;

import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;
import javax.swing.border.CompoundBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.MatteBorder;

@SuppressWarnings("serial")
public class ColorListCellRenderer extends JPanel implements ListCellRenderer<Color> {
	protected Color m_c = Color.black;
	protected Color transparentBorder;
	private CompoundBorder activeBorder;
	private CompoundBorder inactiveBorder;

	public ColorListCellRenderer() {
		super();

		transparentBorder = new Color(255, 255, 255, 30);

		activeBorder = new CompoundBorder(new MatteBorder(2, 10, 2, 10, Color.white), new LineBorder(Color.black));
		inactiveBorder = new CompoundBorder(new MatteBorder(2, 10, 2, 10, Color.DARK_GRAY), new LineBorder(Color.black));

		setBorder(activeBorder);
	}

	@Override
	public Component getListCellRendererComponent(JList<? extends Color> list, Color obj, int row, boolean sel,
			boolean hasFocus) {
		if (obj instanceof Color)
			m_c = (Color) obj;
		return this;
	}

	public void paint(Graphics g) {
		setBackground(m_c);
		super.paint(g);
	}
	
	@Override
	public void setEnabled( boolean b ) {
		super.setEnabled( b );;
		setBorder( b ? activeBorder : inactiveBorder );
	}

}
