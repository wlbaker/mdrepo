/*
 * Created by JFormDesigner on Wed Dec 04 09:09:04 CST 2013
 */

package idea.display.elegant;

import java.awt.Color;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

/**
 * @author User #1
 */
@Slf4j
public class Format5 extends JPanel implements ValuePanelInterface {
	private int curr = 0;
	private RpMetric[] descs = new RpMetric[3];

	public Format5() {
		initComponents();
	}

	@Override
	public void addParameter(RpMetric desc) {
		if (curr > 2) {
			log.error("too many parameters");
			return;
		}
		this.descs[curr++] = desc;
		if (curr == 1) {
			paramLabel.setText(desc.getCode());
			value1.setName(desc.getLocation());
			value1.setText(desc.getLocation());

		}
		if (curr == 2) {
			paramLabel2.setText(desc.getCode());
			value2.setName(desc.getLocation());
			value2.setText(desc.getLocation());
		}
		if (curr == 3) {
			value3.setName(desc.getLocation());
			value3.setText(desc.getLocation());
		}

	}

	@Override
	public void clear() {
		value1.setText(" ");
		value2.setText(" ");
		value3.setText(" ");
	}

	@Override
	public void setValue(RpMetric desc, Object item) {
		String loc = desc.getLocation();
		if (loc.equals(value1.getName())) {
			value1.setText("" + item);
		}
		if (loc.equals(value2.getName())) {
			value2.setText("" + item);
		}
		if (loc.equals(value3.getName())) {
			value3.setText("" + item);
		}
	}

	@Override
	public boolean containsLoc(String loc) {
		if (descs[0] != null && loc.equals(descs[0].getLocation())) {
			return true;
		}
		if (descs[1] != null && loc.equals(descs[1].getLocation())) {
			return true;
		}
		if (descs[2] != null && loc.equals(descs[2].getLocation())) {
			return true;
		}
		return false;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		paramLabel = new JLabel();
		value1 = new JLabel();
		paramLabel2 = new JLabel();
		paramLabel3 = new JLabel();
		value2 = new JLabel();
		value3 = new JLabel();
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("[30dlu,default], $lcgap, default:grow",
				"fill:default:grow, $lgap, default, $lgap, fill:default:grow"));

		// ---- paramLabel ----
		paramLabel.setText("param");
		paramLabel.setVerticalAlignment(SwingConstants.TOP);
		add(paramLabel, cc.xy(1, 1));

		// ---- value1 ----
		value1.setText("value");
		value1.setHorizontalAlignment(SwingConstants.TRAILING);
		value1.setVerticalAlignment(SwingConstants.TOP);
		add(value1, cc.xy(3, 1));

		// ---- paramLabel2 ----
		paramLabel2.setText("param");
		paramLabel2.setVerticalAlignment(SwingConstants.TOP);
		add(paramLabel2, cc.xy(1, 3));

		// ---- paramLabel3 ----
		paramLabel3.setText("param");
		paramLabel3.setVerticalAlignment(SwingConstants.TOP);
		add(paramLabel3, cc.xy(3, 3));

		// ---- value2 ----
		value2.setText("text");
		value2.setVerticalAlignment(SwingConstants.BOTTOM);
		add(value2, cc.xy(1, 5));

		// ---- value3 ----
		value3.setText("Format5");
		value3.setVerticalAlignment(SwingConstants.BOTTOM);
		value3.setHorizontalAlignment(SwingConstants.TRAILING);
		add(value3, cc.xy(3, 5));
		// JFormDesigner - End of component initialization
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel paramLabel;
	private JLabel value1;
	private JLabel paramLabel2;
	private JLabel paramLabel3;
	private JLabel value2;
	private JLabel value3;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void setColor(Color color) {
		paramLabel.setForeground(color);
		paramLabel2.setForeground(color);
		paramLabel3.setForeground(color);

		value1.setForeground(color);
		value2.setForeground(color);
		value3.setForeground(color);
	}

}
