/*
 * Created by JFormDesigner on Tue Sep 25 14:47:36 CDT 2012
 */

package idea.resources_obs;

import javax.swing.JPanel;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
public class TwoColumnPanel extends JPanel {
	public TwoColumnPanel(JPanel left, JPanel right) {
		initComponents();
		
		CellConstraints cc = new CellConstraints();

		add(left, cc.xy(1, 1));
		add(right, cc.xy(3, 1));
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license

		//======== this ========
		setLayout(new FormLayout(
			"default:grow, $lcgap, default:grow",
			"fill:70dlu:grow"));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
