/*
 * Created by JFormDesigner on Mon Apr 02 09:07:57 CDT 2012
 */

package idea.tsoffline.event_editor;

import java.awt.event.ActionEvent;
import java.awt.event.FocusEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.Date;
import java.util.List;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

import idea.GuiUtil;
import idea.ts.TsoAnnotationEntryType;
import idea.tsoffline.AppModel;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.canvas.TsBaseCanvas;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SingleEventPanel extends JPanel {
	private TsoAnnotationEntryType event;
	private boolean ok_selected;
	private boolean ignoreChange;

	private long startTime;
	private TsBaseCanvas canvas;

	public SingleEventPanel(TsBaseCanvas canvas, TsoAnnotationEntryType it) {
		initComponents();

		this.event = it;
		this.canvas = canvas;
		startTime = AppModel.getStartTime();

		description.setText(it.getCode());
		dateChooser.setDate(it.getTm());
		dateChooser.addPropertyChangeListener("date", new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				startTimeChooserFocusLost(null);
			}
		});
		startTimeChooserFocusLost(null); // sync with relative time

		// relativeTime.setFormatterFactory( GuiUtil.getHHMMSSFormatterFactory() );
		relativeTime.setFormatterFactory(GuiUtil.getNumberFormatterFactory());
		relativeTime.addPropertyChangeListener("value", new PropertyChangeListener() {

			@Override
			public void propertyChange( PropertyChangeEvent evt) {
				relativeTimeFocusLost(null);
			}
		});
		
		List<HPSplitableLayer> annos = canvas.getAnnotationModel();
		DefaultComboBoxModel mm = new DefaultComboBoxModel( annos.toArray() );
		annotationLayerCombo.setModel(mm);
	}

	private void okActionPerformed(ActionEvent e) {
		ok_selected = true;
		event.setCode(description.getText());
		event.setTm(dateChooser.getDate());
		cancelActionPerformed(null);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void startTimeChooserFocusLost(FocusEvent e) {
		if (ignoreChange) {
			return;
		}
		ignoreChange = true;
		Date dt = dateChooser.getDate();
		long rtm = dt.getTime() - startTime;
		relativeTime.setValue(rtm / 1000.0);
		System.out.println("set value to: " + relativeTime.getValue()); // relativeTime.getE
		// relativeTime.setText( "");
		ignoreChange = false;
	}

	public boolean isOk() {
		return ok_selected;
	}

	private void relativeTimeFocusLost(FocusEvent e) {
		if (ignoreChange) {
			return;
		}
		ignoreChange = true;
		// Date rtm = (Date) relativeTime.getValue();
		Number rtm = (Number) relativeTime.getValue();
		if (rtm != null) {
			Date abs_dt = new Date((long) ((1000 * rtm.doubleValue()) + startTime));
			dateChooser.setDate(abs_dt);
		}
		ignoreChange = false;
	}

	/**
	 * Used by the dialog to set a form default button.
	 * 
	 * @return
	 * 
	 * The OK button.
	 */
	public JButton getOKButton() {
		return ok;
	}
	
	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label4 = new JLabel();
		annotationLayerCombo = new JComboBox();
		label3 = new JLabel();
		description = new JTextField();
		label2 = new JLabel();
		dateChooser = new JDateChooser();
		label1 = new JLabel();
		relativeTime = new JFormattedTextField();
		panel2 = new JPanel();
		ok = new JButton();
		cancel = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, top:default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:default, 2*($lcgap, [50dlu,default])",
				"4*(default, $lgap), [20dlu,default]"));

			//---- label4 ----
			label4.setText("Annotation Layer:");
			panel1.add(label4, CC.xy(1, 1));
			panel1.add(annotationLayerCombo, CC.xywh(3, 1, 3, 1));

			//---- label3 ----
			label3.setText("Event Text:");
			panel1.add(label3, CC.xy(1, 3));
			panel1.add(description, CC.xywh(3, 3, 3, 1));

			//---- label2 ----
			label2.setText("Date/Time:");
			panel1.add(label2, CC.xy(1, 5));

			//---- dateChooser ----
			dateChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			panel1.add(dateChooser, CC.xywh(3, 5, 3, 1));

			//---- label1 ----
			label1.setText("Relative Time:");
			panel1.add(label1, CC.xy(1, 7));
			panel1.add(relativeTime, CC.xy(3, 7));
		}
		add(panel1, CC.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("OK");
			ok.addActionListener(e -> okActionPerformed(e));
			panel2.add(ok, CC.xy(3, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel2.add(cancel, CC.xy(5, 1));
		}
		add(panel2, CC.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label4;
	private JComboBox annotationLayerCombo;
	private JLabel label3;
	private JTextField description;
	private JLabel label2;
	private JDateChooser dateChooser;
	private JLabel label1;
	private JFormattedTextField relativeTime;
	private JPanel panel2;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

	public HPSplitableLayer getCachedSignal() {
		HPSplitableLayer sig = (HPSplitableLayer) this.annotationLayerCombo.getSelectedItem();
		return sig;
	}

}
