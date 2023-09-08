/*
 * Created by JFormDesigner on Wed Dec 04 09:09:04 CST 2013
 */

package idea.display.elegant;

import java.awt.Color;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;

/**
 * @author User #1
 */
@Slf4j
public class Format15 extends JPanel implements ValuePanelInterface {

	private int curr = 0;
	private RpMetric[] descs = new RpMetric[4];

	public Format15() {
		initComponents();
	}

	@Override
	public void addParameter(RpMetric desc) {
		if( curr > 3 ) {
				log.error("too many parameters");
				return;
		}
		this.descs[curr++] = desc;
		if (curr == 1) {
			paramLabel1.setText(desc.getCode());
			value1.setName(desc.getLocation());
			value1.setText( desc.getLocation() );

		}
		if (curr == 2) {
			paramLabel2.setText(desc.getCode());
			value2.setName(desc.getLocation());
			value2.setText( desc.getLocation() );
		}
		if (curr == 3) {
			paramLabel3.setText(desc.getCode());
			value3.setName(desc.getLocation());
			value3.setText( desc.getLocation() );
		}
		if (curr == 4) {
			paramLabel4.setText(desc.getCode());
			value4.setName(desc.getLocation());
			value4.setText( desc.getLocation() );
		}

	}

	@Override
	public void clear() {
		value1.setText(" ");
		value2.setText(" ");
		value3.setText(" ");
		value4.setText(" ");

	}

	@Override
	public void setValue(RpMetric desc, Object item ) {
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
		if (loc.equals(value4.getName())) {
			value4.setText("" + item);
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
		if (descs[3] != null && loc.equals(descs[3].getLocation())) {
			return true;
		}
		return false;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		paramLabel1 = new JLabel();
		paramLabel2 = new JLabel();
		paramLabel3 = new JLabel();
		paramLabel4 = new JLabel();
		value1 = new JLabel();
		value2 = new JLabel();
		value3 = new JLabel();
		value4 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(new EmptyBorder(2, 2, 2, 2));
		setLayout(new FormLayout(
			"default:grow, $lcgap, default:grow",
			"3*(default, $lgap), default"));

		//---- paramLabel1 ----
		paramLabel1.setText("PAW");
		add(paramLabel1, cc.xy(1, 1));

		//---- paramLabel2 ----
		paramLabel2.setText("MAP");
		add(paramLabel2, cc.xy(1, 5));

		//---- paramLabel3 ----
		paramLabel3.setText("PIP");
		add(paramLabel3, cc.xy(3, 1));

		//---- paramLabel4 ----
		paramLabel4.setText("RESP");
		add(paramLabel4, cc.xy(3, 5));

		//---- value1 ----
		value1.setText("value1");
		value1.setHorizontalAlignment(SwingConstants.TRAILING);
		add(value1, cc.xy(1, 3));

		//---- value2 ----
		value2.setText("value2");
		value2.setHorizontalAlignment(SwingConstants.TRAILING);
		add(value2, cc.xy(1, 7));

		//---- value3 ----
		value3.setText("value3");
		value3.setHorizontalAlignment(SwingConstants.TRAILING);
		add(value3, cc.xy(3, 3));

		//---- value4 ----
		value4.setText("value4");
		value4.setHorizontalAlignment(SwingConstants.TRAILING);
		add(value4, cc.xy(3, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JLabel paramLabel1;
	private JLabel paramLabel2;
	private JLabel paramLabel3;
	private JLabel paramLabel4;
	private JLabel value1;
	private JLabel value2;
	private JLabel value3;
	private JLabel value4;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void setColor(Color color) {
		paramLabel1.setForeground( color );
		paramLabel2.setForeground( color );
		paramLabel3.setForeground( color );
		paramLabel4.setForeground( color );
		
		value1.setForeground( color );
		value2.setForeground( color );
		value3.setForeground( color );
		value4.setForeground( color );
	}
}
