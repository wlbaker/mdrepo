/*
 * Created by JFormDesigner on Wed Mar 27 11:21:08 CDT 2013
 */

package idea.display.elegant;

import java.awt.Color;
import java.awt.Font;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import icuInterface.message.CompositeItem;
import icuInterface.message.NumericItem;
import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

/**
 * @author User #1
 */
@Slf4j
public class Format81 extends JPanel implements ValuePanelInterface {
	private RpMetric desc;

	public Format81() {
		initComponents();
		
		unk1Label.setText("");
		unk2Label.setText("");
	}

	@Override
	public void addParameter(RpMetric desc) {
		this.desc = desc;
		paramLabel.setText(desc.getCode());
		value.setName(desc.getLocation());
	}

	@Override
	public void clear() {
		value.setText("clear");
	}

	@Override
	public void setValue(RpMetric desc, Object val) {
		if( val == null ) {
			value.setText("N/A");
		} else if (val instanceof CompositeItem) {
			CompositeItem ci = (CompositeItem) val;

			String loc = desc.getLocation();
			if (loc.equals(value.getName())) {
				NumericItem[] values = ci.getValues();
				String [] v = new String[3];
				for( int i = 0; i < 3; i++ ) {
					Number v0 = values[i].getValue();
					if( v0 != null && v0.intValue() >= 0x7fffff) {
						v[i] = "";
					} else {
						v[i] = "" + v0;
					}
				}
				value.setText(v[0] + "/" + v[1] + " (" + v[2] + ")");
			}
		} else {
			clear();
			log.error("Unexpected item: {}", desc);
		}
	}

	@Override
	public boolean containsLoc(String loc) {
		if (desc != null && loc.equals(desc.getLocation())) {
			return true;
		}
		return false;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		paramLabel = new JLabel();
		panel1 = new JPanel();
		panel2 = new JPanel();
		label2 = new JLabel();
		unk1Label = new JLabel();
		unk2Label = new JLabel();
		value = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow"));

		//---- paramLabel ----
		paramLabel.setText("NBP Pulse xxx  Man   12:11");
		add(paramLabel, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[30dlu,default], $lcgap, default:grow",
				"fill:default:grow"));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout(
					"default:grow",
					"3*(default, $lgap), default:grow"));

				//---- label2 ----
				label2.setText("Sys:");
				panel2.add(label2, cc.xy(1, 1));

				//---- unk1Label ----
				unk1Label.setText("90?");
				unk1Label.setHorizontalAlignment(SwingConstants.TRAILING);
				panel2.add(unk1Label, cc.xy(1, 3));

				//---- unk2Label ----
				unk2Label.setText("40?");
				unk2Label.setHorizontalAlignment(SwingConstants.TRAILING);
				panel2.add(unk2Label, cc.xy(1, 5));
			}
			panel1.add(panel2, cc.xy(1, 1));

			//---- value ----
			value.setText("80/50 (60)");
			value.setVerticalAlignment(SwingConstants.BOTTOM);
			value.setFont(new Font("Dialog", Font.PLAIN, 20));
			panel1.add(value, cc.xy(3, 1));
		}
		add(panel1, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JLabel paramLabel;
	private JPanel panel1;
	private JPanel panel2;
	private JLabel label2;
	private JLabel unk1Label;
	private JLabel unk2Label;
	private JLabel value;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public void setColor(Color color) {
		paramLabel.setForeground(color);
		label2.setForeground(color);
		unk1Label.setForeground(color);
		unk2Label.setForeground(color);
		value.setForeground(color);
	}
}
