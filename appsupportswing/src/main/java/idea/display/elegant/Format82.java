/*
 * Created by JFormDesigner on Wed Mar 27 16:11:54 CDT 2013
 */

package idea.display.elegant;

import java.awt.Color;
import java.awt.Font;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpMetric;

/**
 * @author User #1
 */
public class Format82 extends JPanel  implements ValuePanelInterface  {
	private RpMetric desc;
	public Format82() {
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
		panel1 = new JPanel();
		paramLabel = new JLabel();
		value = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[30dlu,default], $lcgap, [50dlu,default]:grow",
			"fill:[30dlu,default]:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow",
				"2*(default, $lgap), fill:default:grow"));

			//---- paramLabel ----
			paramLabel.setText("Pulse?");
			panel1.add(paramLabel, cc.xy(1, 1));
		}
		add(panel1, cc.xy(1, 1));

		//---- value ----
		value.setText("text");
		value.setHorizontalAlignment(SwingConstants.TRAILING);
		value.setFont(new Font("Dialog", Font.PLAIN, 22));
		add(value, cc.xy(3, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JLabel paramLabel;
	private JLabel value;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void setColor(Color color) {
		paramLabel.setForeground(color);

		value.setForeground(color);
	}
}
