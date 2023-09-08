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

/**
 * @author User #1
 */
public class Format9 extends JPanel  implements ValuePanelInterface  {
	private RpMetric desc;


	public Format9() {
		initComponents();
	}
	@Override
	public void addParameter(RpMetric desc) {
		this.desc = desc;
		paramLabel.setText( desc.getCode() );
		value.setName( desc.getLocation() );

	}

	@Override
	public void clear() {
		value.setText("clear");
	}

	@Override
	public void setValue(RpMetric desc, Object item) {
		String loc = desc.getLocation();
		if( loc.equals(value.getName()) ) {
			value.setText( "" + item );
		}
	}

	@Override
	public boolean containsLoc(String loc) {
		if( desc != null && loc.equals(desc.getLocation() ) ) {
			return true;
		}
		return false;
	}


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		paramLabel = new JLabel();
		value = new JLabel();
		paramLabel2 = new JLabel();
		paramLabel3 = new JLabel();
		value2 = new JLabel();
		value3 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[30dlu,default], $lcgap, default:grow",
			"2*(default, $lgap), default"));

		//---- paramLabel ----
		paramLabel.setText("param");
		add(paramLabel, cc.xy(1, 1));

		//---- value ----
		value.setText("value");
		value.setHorizontalAlignment(SwingConstants.TRAILING);
		add(value, cc.xy(3, 1));

		//---- paramLabel2 ----
		paramLabel2.setText("[mac]");
		add(paramLabel2, cc.xy(1, 3));

		//---- paramLabel3 ----
		paramLabel3.setText("[etISO]");
		add(paramLabel3, cc.xy(3, 3));

		//---- value2 ----
		value2.setText("text");
		add(value2, cc.xy(1, 5));

		//---- value3 ----
		value3.setText("Format9");
		add(value3, cc.xy(3, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel paramLabel;
	private JLabel value;
	private JLabel paramLabel2;
	private JLabel paramLabel3;
	private JLabel value2;
	private JLabel value3;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

	@Override
	public void setColor(Color color) {
		paramLabel.setForeground(color);
		paramLabel2.setForeground(color);
		paramLabel3.setForeground(color);

		value.setForeground(color);
		value2.setForeground(color);
		value3.setForeground(color);
	}
}
