/*
 * Created by JFormDesigner on Fri Nov 25 18:36:19 CST 2016
 */

package idea.tsoffline.canvas;

import java.awt.Color;
import java.awt.event.ActionEvent;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.piccolo2d.PLayer;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import lombok.Getter;
import idea.GuiUtil;
import idea.gui.ColorListCellRenderer;
import idea.tsoffline.ColorManager;

/**
 * @author User #1
 */
public class AddAnnotationLayerPanel extends JPanel {
	@Getter
	boolean finished = false;
	
	public AddAnnotationLayerPanel() {
		initComponents();
		
		layerColor.setRenderer( new ColorListCellRenderer() );
		ComboBoxModel<Color> model = new DefaultComboBoxModel<Color>(ColorManager.getColors());
		layerColor.setModel(model );

	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void okActionPerformed(ActionEvent e) {
		finished = true;
		GuiUtil.closeDialog(this);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label1 = new JLabel();
		layerName = new JTextField();
		label2 = new JLabel();
		layerColor = new JComboBox();
		panel2 = new JPanel();
		ok = new JButton();
		cancel = new JButton();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[20dlu,default], $lcgap, right:default, $lcgap, [150dlu,default]",
				"2*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Layer Name:");
			panel1.add(label1, CC.xy(3, 3));
			panel1.add(layerName, CC.xy(5, 3));

			//---- label2 ----
			label2.setText("Color:");
			panel1.add(label2, CC.xy(3, 5));
			panel1.add(layerColor, CC.xy(5, 5));
		}
		add(panel1, CC.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("Ok");
			ok.addActionListener(e -> okActionPerformed(e));
			panel2.add(ok, CC.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel2.add(cancel, CC.xy(5, 1));
		}
		add(panel2, CC.xy(1, 7));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label1;
	private JTextField layerName;
	private JLabel label2;
	private JComboBox layerColor;
	private JPanel panel2;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

	public PLayer apply(TsBaseCanvas canvas) {

		String loc = layerName.getText();
		Color color = (Color)layerColor.getSelectedItem();
		
		
		return canvas.addAnnotationLayer( loc, color, "source$user");

	}
}
