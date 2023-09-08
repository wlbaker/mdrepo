/*
 * Created by JFormDesigner on Thu Dec 31 13:07:09 CST 2009
 */

package idea.tsoffline.event_editor;

import java.awt.event.ActionEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.DateFormat;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.tsoffline.B2BUtil;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.canvas.TsBaseCanvas;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class B2BAnnotationExplorer extends JPanel implements PropertyChangeListener {

	private static final int OBJECT_COL = 0;
	private static final int DT_COL = 1;
	private int value = JOptionPane.CANCEL_OPTION;

	Date selectedDate = null;
	Date selectedReturn = null;
	private TsBaseCanvas canv;

	public B2BAnnotationExplorer(TsBaseCanvas canv ) {
		initComponents();

		this.canv = canv;
		
		cancel.setEnabled(false);

		timeLabel.setText("");
		populate();
	}

	private void populate() {

		HPSplitableLayer ecgAnnotations = B2BUtil.getBeatSegmentationLayer();
		FeatureListPanel featurePanel = new FeatureListPanel(canv, ecgAnnotations, false, false );
		tabber.add(ecgAnnotations.getName(), featurePanel);
		featurePanel.addPropertyChangeListener("selected_dt", this);
		
		for (HPSplitableLayer info : canv.getAnnotationModel()) {
			if (ecgAnnotations == info) {
				// skip...already added
			} else {
				featurePanel.populateSegmentedLayer( info, B2BUtil.getBeatLeadLag() );
			}
		}

		int idx = 0;
		tabber.setSelectedIndex(idx);
		featurePanel.formatTable();
	}

	private void okActionPerformed(ActionEvent e) {
		value = JOptionPane.OK_OPTION;
		cancelActionPerformed(null);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	public int getValue() {
		return value;
	}

	private void goto_pointActionPerformed(ActionEvent e) {
		selectedReturn = selectedDate;
		okActionPerformed(null);
	}

	public Date getSelectedTime() {
		return selectedReturn;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		tabber = new JTabbedPane();
		panel4 = new JPanel();
		timeLabel = new JLabel();
		goto_point = new JButton();
		ok = new JButton();
		cancel = new JButton();

		// ======== this ========
		setLayout(new FormLayout("default:grow", "fill:default:grow, 2*($lgap, default)"));
		add(tabber, CC.xy(1, 1));

		// ======== panel4 ========
		{
			panel4.setLayout(new FormLayout("default:grow, 2*($lcgap, [50dlu,default]), 2*($lcgap, 50dlu)", "default"));

			// ---- timeLabel ----
			timeLabel.setText("text");
			panel4.add(timeLabel, CC.xy(1, 1));

			// ---- goto_point ----
			goto_point.setText("Go To");
			goto_point.addActionListener(e -> goto_pointActionPerformed(e));
			panel4.add(goto_point, CC.xy(3, 1));

			// ---- ok ----
			ok.setText("Ok");
			ok.addActionListener(e -> okActionPerformed(e));
			panel4.add(ok, CC.xy(7, 1));

			// ---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel4.add(cancel, CC.xy(9, 1));
		}
		add(panel4, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JTabbedPane tabber;
	private JPanel panel4;
	private JLabel timeLabel;
	private JButton goto_point;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		DateFormat df = GuiUtil.getDateTimeFormat();
		selectedDate = (Date) evt.getNewValue();
		timeLabel.setText((selectedDate == null) ? "" : df.format(selectedDate));
	}

}
