/*
 * Created by JFormDesigner on Thu Dec 31 13:07:09 CST 2009
 */

package idea.tsoffline.event_editor;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.DateFormat;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.canvas.TsPSwingCanvas;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class AnnotationExplorer extends JPanel implements PropertyChangeListener {
	
	private static final int OBJECT_COL = 0;
	private static final int DT_COL = 1;
	private int value = JOptionPane.CANCEL_OPTION;
	
	Date selectedDate = null;
	Date selectedReturn = null;

	List<FeatureListPanel> fpanels = new LinkedList<FeatureListPanel>();
	
	public AnnotationExplorer( TsPSwingCanvas canvas ) {
		initComponents();

		for( HPSplitableLayer info : canvas.getAnnotationModel() ) {
			FeatureListPanel featurePanel = new FeatureListPanel(canvas, info, false, true );
			tabber.add(info.getName(), featurePanel);
			featurePanel.addPropertyChangeListener("selected_dt", this);
			
			fpanels.add(featurePanel);
		}

		int idx = 0;
		for( FeatureListPanel p : fpanels ) {
			if( p.getRowCount() > 0 ) {
				tabber.setSelectedIndex(idx);
				break;
			}
			idx++;
		}

		cancel.setEnabled(false);
		
		timeLabel.setText("");
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
		// Generated using JFormDesigner non-commercial license
		tabber = new JTabbedPane();
		panel4 = new JPanel();
		timeLabel = new JLabel();
		goto_point = new JButton();
		ok = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, 2*($lgap, default)"));
		add(tabber, cc.xy(1, 1));

		//======== panel4 ========
		{
			panel4.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default]), 2*($lcgap, 50dlu)",
				"default"));

			//---- timeLabel ----
			timeLabel.setText("text");
			panel4.add(timeLabel, cc.xy(1, 1));

			//---- goto_point ----
			goto_point.setText("Go To");
			goto_point.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					goto_pointActionPerformed(e);
				}
			});
			panel4.add(goto_point, cc.xy(3, 1));

			//---- ok ----
			ok.setText("Ok");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel4.add(ok, cc.xy(7, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel4.add(cancel, cc.xy(9, 1));
		}
		add(panel4, cc.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
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
		timeLabel.setText( (selectedDate == null) ? "" : df.format(selectedDate) );
	}


}
