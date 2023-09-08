/*
 * Created by JFormDesigner on Wed Oct 21 10:52:08 CDT 2009
 */

package idea.display.simple;

import java.awt.Color;
import java.awt.Font;
import java.text.NumberFormat;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.LineBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.UnitUtil;
import idea.schema.rp.RpUnit;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SingleValuePanel extends JPanel {

	NumberFormat default_fmt = NumberFormat.getInstance(); // new DecimalFormat("#,##0.###");
	NumberFormat fmt;

	public SingleValuePanel() {
		initComponents();
	}

	public void setValue(Number number, RpUnit unit) {
		if( number != null && unit != null ) {
			number = UnitUtil.getValue(unit,number.doubleValue());
		}
		
		setValue( number );
	}
	
	public void setValue(Number number) {
		String val = null;

		if (number != null) {
			if (number instanceof Integer) {
				int ii = (Integer) number;
				if (ii == Integer.MIN_VALUE) {
					val = "--";
				}
			}

			if (val == null) {
				if( fmt == null ) {
					val = default_fmt.format(number);
				} else {
					val = fmt.format(number);
				}
			}
		}

		if (val == null) {
			val = " ";
		}
		value.setText(val);
	}

	public void setValue(String val) {
		if (val == null) {
			val = " ";
		}
		value.setText(val);
	}

	public void clear() {
		value.setText(" ");
	}

	public void setUnits(String unit) {
		units.setText(unit);
	}

	public void setCode(String code) {
		code = "<html>" + code.replaceAll("sub\\(([^)]+)\\)", "<sub>$1</sub>");
		id.setText(code);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		value = new JLabel();
		units = new JLabel();
		id = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(new LineBorder(Color.magenta, 2));
		setLayout(new FormLayout(
			"[40dlu,default], $lcgap, [10dlu,default]",
			"fill:default:grow, default, $nlgap, fill:[12dlu,default]"));

		//---- value ----
		value.setText("0");
		value.setHorizontalAlignment(SwingConstants.TRAILING);
		value.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 30));
		value.setVerticalAlignment(SwingConstants.BOTTOM);
		add(value, cc.xywh(1, 1, 1, 4));

		//---- units ----
		units.setText("units");
		units.setVerticalAlignment(SwingConstants.BOTTOM);
		add(units, cc.xy(3, 2));

		//---- id ----
		id.setText("S");
		id.setVerticalAlignment(SwingConstants.TOP);
		add(id, cc.xy(3, 4));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel value;
	private JLabel units;
	private JLabel id;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
