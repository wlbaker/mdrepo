/*
 * Created by JFormDesigner on Tue Nov 04 17:03:08 CST 2014
 */

package idea.display.elegant;

import java.awt.Color;

import javax.swing.JPanel;

import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpMetric;

/**
 * @author User #1
 */
public class Format70Philips3 extends JPanel implements ValuePanelInterface {
	public Format70Philips3() {
		initComponents();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents

		//======== this ========
		setLayout(new FormLayout(
			"default, $lcgap, default",
			"default, $lgap, default"));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	@Override
	public void addParameter(RpMetric desc) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void clear() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setValue(RpMetric desc, Object item) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean containsLoc(String loc) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void setColor(Color color) {
		// TODO Auto-generated method stub
		
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
