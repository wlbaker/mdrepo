package idea.gui;

import java.awt.Color;
import java.awt.Component;

import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;
import javax.swing.border.CompoundBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.MatteBorder;

import idea.schema.rp.RpMetric;

@SuppressWarnings("serial")
public class RpMetricListCellRenderer extends JPanel implements ListCellRenderer<RpMetric> {
	private CompoundBorder activeBorder;
	private CompoundBorder inactiveBorder;
	private JLabel label = new JLabel();

	public RpMetricListCellRenderer() {
		super();

		activeBorder = new CompoundBorder(new MatteBorder(2, 10, 2, 10, Color.white), new LineBorder(Color.black));
		inactiveBorder = new CompoundBorder(new MatteBorder(2, 10, 2, 10, Color.DARK_GRAY), new LineBorder(Color.black));

		setBorder(activeBorder);
	}

	@Override
	public Component getListCellRendererComponent(JList<? extends RpMetric> RpMetric, RpMetric obj, int row, boolean sel,
			boolean hasFocus) {
		label.setText(  RpMetricTableCellRenderer.toString(obj) );
		return label;
	}

	@Override
	public void setEnabled( boolean b ) {
		super.setEnabled( b );;
		setBorder( b ? activeBorder : inactiveBorder );
	}

}
