/*
 * Created by JFormDesigner on Sun Apr 29 18:20:21 CDT 2012
 */

package idea.tsoffline.util;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;

import org.piccolo2d.PLayer;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import lombok.Getter;
import idea.GuiUtil;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.model.OfflineSignal;

class AnnotationInfoRenderer implements ListCellRenderer<OfflineSignal> {

	private ListCellRenderer defaultRenderer;
	AnnotationInfoRenderer( ListCellRenderer d ) {
		this.defaultRenderer = d;
	}
	@Override
	public Component getListCellRendererComponent(JList<? extends OfflineSignal> list, OfflineSignal value, int index,
			boolean isSelected, boolean cellHasFocus) {
		ListCellRenderer<OfflineSignal> r = (ListCellRenderer<OfflineSignal>)this;
		JLabel f = (JLabel)defaultRenderer.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
		f.setText( value.getName() );
		return f;
	}

}

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class AutocorrectOptionPanel extends JPanel {
	@Getter
	boolean finished = false;
	public AutocorrectOptionPanel(TsPSwingCanvas timeseriesCanvas1) {
		initComponents();

		tolerance.setFormatterFactory(GuiUtil.getIntegerFormatterFactory());
		tolerance.setValue(40);

		List<HPSplitableLayer> annos = timeseriesCanvas1.getAnnotationModel();

		HPSplitableLayer[] anno_arr = new HPSplitableLayer[annos.size()];
		annos.toArray(anno_arr);
		featureSignal.setModel(new DefaultComboBoxModel<>(anno_arr));
		
		//AnnotationInfoRenderer r = new AnnotationInfoRenderer( featureSignal.getRenderer() );
		//featureSignal.setRenderer( r );
		referenceSignal.setModel(new DefaultComboBoxModel<>(timeseriesCanvas1.getVisibleSigs()));
		referenceSignal.setEnabled(true);
	}

	public void setFeatureName(String name) {
		featureSignal.setSelectedItem(name);
	}

	public Integer getTolerance() {
		return (Integer) tolerance.getValue();
	}

	public int getDirection() {
		String item = (String) directionCombo.getSelectedItem();
		item = item.toLowerCase();

		int dir = -1;
		if (item.startsWith("max"))
			dir = 1;
		if (item.startsWith("top"))
			dir = 1;

		return dir;
	}

	private void okActionPerformed(ActionEvent e) {
		finished = true;
		GuiUtil.closeDialog(this);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void featureSignalActionPerformed(ActionEvent e) {
		System.out.println("selected anno: " + featureSignal.getSelectedItem());
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label6 = new JLabel();
		featureSignal = new JComboBox<>();
		label7 = new JLabel();
		referenceSignal = new JComboBox<>();
		label2 = new JLabel();
		label3 = new JLabel();
		label1 = new JLabel();
		directionCombo = new JComboBox<>();
		label4 = new JLabel();
		tolerance = new JFormattedTextField();
		label5 = new JLabel();
		panel2 = new JPanel();
		ok = new JButton();
		cancel = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[250dlu,default]:grow",
			"default, $lgap, top:default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[80dlu,default], $lcgap, [100dlu,default], $lcgap, default:grow",
				"2*(default, $lgap), [12dlu,default], 2*($lgap, default), $lgap, [12dlu,default], 3*($lgap, default)"));

			//---- label6 ----
			label6.setText("Feature:");
			panel1.add(label6, CC.xy(1, 1));

			//---- featureSignal ----
			featureSignal.addActionListener(e -> featureSignalActionPerformed(e));
			panel1.add(featureSignal, CC.xy(3, 1));

			//---- label7 ----
			label7.setText("Reference Signal:");
			panel1.add(label7, CC.xy(1, 5));
			panel1.add(referenceSignal, CC.xy(3, 5));

			//---- label2 ----
			label2.setText("Start Event:");
			panel1.add(label2, CC.xy(1, 7));

			//---- label3 ----
			label3.setText("Stop Event:");
			panel1.add(label3, CC.xy(1, 9));

			//---- label1 ----
			label1.setText("Direction:");
			panel1.add(label1, CC.xy(1, 13));

			//---- directionCombo ----
			directionCombo.setModel(new DefaultComboBoxModel<>(new String[] {
				"Maximum",
				"Minimum"
			}));
			panel1.add(directionCombo, CC.xy(3, 13));

			//---- label4 ----
			label4.setText("Tolerance:");
			panel1.add(label4, CC.xy(1, 15));
			panel1.add(tolerance, CC.xy(3, 15));

			//---- label5 ----
			label5.setText("ms");
			panel1.add(label5, CC.xy(5, 15));
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
		add(panel2, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label6;
	private JComboBox<HPSplitableLayer> featureSignal;
	private JLabel label7;
	private JComboBox<HPSplitableLayer> referenceSignal;
	private JLabel label2;
	private JLabel label3;
	private JLabel label1;
	private JComboBox<String> directionCombo;
	private JLabel label4;
	private JFormattedTextField tolerance;
	private JLabel label5;
	private JPanel panel2;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public HPSplitableLayer getSelectedReference() {
		return (HPSplitableLayer) referenceSignal.getSelectedItem();
	}

	public void setReferenceSignal(HPSplitableLayer sig) {
		referenceSignal.setSelectedItem(sig);
	}

	public PLayer getFeatureLayer() {
		HPSplitableLayer fitem = (HPSplitableLayer) featureSignal.getSelectedItem();
		return fitem;
	}
}
