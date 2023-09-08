/*
 * Created by JFormDesigner on Mon Apr 02 09:07:57 CDT 2012
 */

package idea.tsoffline.event_editor;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.ParseException;
import java.util.Date;

import javax.swing.ComboBoxModel;
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
import idea.gui.ColorListCellRenderer;
import idea.ts.TsoPhase;
import idea.tsoffline.AppModel;
import idea.tsoffline.ColorManager;
import idea.tsoffline.canvas.LabelType;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class PhaseEditorPanel extends JPanel {
	private TsoPhase event;
	private boolean ok_selected;
	private boolean ignoreChange;

	private long startTime;
	private LabelType mode;
	private long initialTime;

	/**
	 * 
	 * Edit a TsoPhase object.
	 * 
	 * @param phase The TsoPhase object to be edited.
	 * @param mode  The method of displaying/managing dates and times.
	 * 
	 *              Mode determines if the time is managed by absolute time (Monday,
	 *              Jan 1, 1969) or by relative time (9min 57sec). Use mode=0 for
	 *              absolute time, and mode =1 for relative time.
	 */

	public PhaseEditorPanel(TsoPhase phase, long initialTime, LabelType mode) {
		initComponents();

		this.event = phase;
		this.mode = mode;
		this.initialTime = initialTime;
		
		startTime = AppModel.getStartTime();

		long tm0 = phase.getStartTm().getTime() - initialTime;
		long tm1 = phase.getStopTm().getTime() - initialTime;
		
		if( mode == LabelType.LABEL_CLOCKTIME ) {
			startDateChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss.SSS");
			stopDateChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss.SSS");
			
			startDateChooser.setDate(phase.getStartTm());
			stopDateChooser.setDate(phase.getStopTm());
			
		} else if (mode == LabelType.LABEL_REL_MMSS) {
			startDateChooser.setDateFormatString("HH:mm:ss.SSS");
			stopDateChooser.setDateFormatString("HH:mm:ss.SSS");
			
			startDateChooser.setDate( new Date(tm0));
			stopDateChooser.setDate( new Date(tm1));
		} else { // if (mode == LabelType.LABEL_REL_SECS) {
			startSecs.setFormatterFactory( GuiUtil.getNumberFormatterFactory() );
			stopSecs.setFormatterFactory( GuiUtil.getNumberFormatterFactory() );
		}
		
		if( mode == LabelType.LABEL_CLOCKTIME || mode == LabelType.LABEL_REL_MMSS) {
			startSecsLabel.setVisible( false );
			stopSecsLabel.setVisible(false);
			startSecs.setVisible(false);
			stopSecs.setVisible(false);
			
			initDateChoosers();
			duration.setValue( (tm1-tm0)/1000.0 );
		} else {
			startDateLabel.setVisible( false );
			stopDateLabel.setVisible(false);
			startDateChooser.setVisible(false);
			stopDateChooser.setVisible(false);
			
			initSecEntry();
		}
		
		description.setText(phase.getName());
		/*
		 * No longer using relative time
		 */
		/*
		 * // relativeTime.setFormatterFactory( GuiUtil.getHHMMSSFormatterFactory() );
		 * startRelativeTime.setFormatterFactory(GuiUtil.getNumberFormatterFactory());
		 * startRelativeTime.addPropertyChangeListener("value", new
		 * PropertyChangeListener() {
		 * 
		 * @Override public void propertyChange( PropertyChangeEvent evt) {
		 * relativeTimeFocusLost(null); } });
		 * 
		 */
		duration.setFormatterFactory(GuiUtil.getNumberFormatterFactory());
		colorCombo.setRenderer(new ColorListCellRenderer());
		ComboBoxModel<Color> model = new DefaultComboBoxModel<Color>(ColorManager.getColors());
		colorCombo.setModel(model);

		ok.setEnabled(true);
		ignoreChange = false;
	}

	private void initSecEntry() {
		FocusAdapter fad = new FocusAdapter() {

			@Override
			public void focusLost(FocusEvent e) {
				durationFocusLost(null);
			}

		};
		startSecs.addFocusListener( fad );
		stopSecs.addFocusListener( fad );
	}

	private void initDateChoosers() {
		PropertyChangeListener pcl = new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				timeChooserFocusLost(null);
			}
		};
		
		FocusAdapter fad = new FocusAdapter() {

			@Override
			public void focusLost(FocusEvent e) {
				timeChooserFocusLost(null);
			}

		};
		
		startDateChooser.addPropertyChangeListener("date", pcl );
		stopDateChooser.addPropertyChangeListener("date",  pcl );

		stopDateChooser.addFocusListener(fad);

	}

	private void okActionPerformed(ActionEvent e) {
		ok_selected = true;
		
		event.setName(description.getText());
		if( mode == LabelType.LABEL_CLOCKTIME ) {
			event.setStartTm(startDateChooser.getDate());
			event.setStopTm(stopDateChooser.getDate());
		} else if (mode == LabelType.LABEL_REL_MMSS) {
			Date dt0 = startDateChooser.getDate();
			Date dt1 = stopDateChooser.getDate();
			
			event.setStartTm( new Date( initialTime + dt0.getTime()));
			event.setStopTm( new Date( initialTime + dt1.getTime()));
		} else if (mode == LabelType.LABEL_REL_SECS) {
			
		}
		event.setColor(ColorManager.asBytes((Color) colorCombo.getSelectedItem()));
		cancelActionPerformed(null);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void timeChooserFocusLost(FocusEvent e) {
		if (ignoreChange) {
			return;
		}

		boolean ena = false;
		try {
			ignoreChange = true;
			Date dt1 = startDateChooser.getDate();
			Date dt2 = stopDateChooser.getDate();
			if (dt1 == null || dt2 == null) {
				return; // subtly invokes the finally clause before return
			}
			long dt = dt2.getTime() - dt1.getTime();
			if (dt < 0) {
				return;
			}
			duration.setValue(dt / 1000.0);
			System.out.println("set duration to: " + duration.getValue()); // relativeTime.getE
			ena = true;
			// relativeTime.setText( "");
		} finally {
			ignoreChange = false;
			ok.setEnabled(ena);
		}
	}

	public boolean isOk() {
		return ok_selected;
	}

	private void durationFocusLost(FocusEvent e) {
		System.out.println("duration/number entry focus lost");
		if (ignoreChange) {
			return;
		}
		Component comp = e.getComponent();
		boolean enaOk = false;
		try {
			ignoreChange = true;
			JFormattedTextField tf = null;
			if( comp instanceof JFormattedTextField ) {
				tf = (JFormattedTextField) comp;
				tf.commitEdit();
				
				if( tf.getValue() == null ) {
					return;
				}
			}
			

			Number dt = (Number) duration.getValue();
			switch( mode ) {
			case LABEL_CLOCKTIME:
			case LABEL_REL_MMSS:
				if (dt == null) {
					return;
				}
				double ddt = dt.doubleValue();
				long deltaMs = (long) (ddt * 1000);
				Date dt1 = (Date) startDateChooser.getDate();
				Date dt2 = (Date) new Date(dt1.getTime() + deltaMs);

				stopDateChooser.setDate(dt2);
				break;
			case LABEL_REL_SECS:
				Number n0 = (Number) startSecs.getValue();
				Number n1 = (Number) stopSecs.getValue();
				if( n0 == null ) {
					return;
				}
				double d0 = n0.doubleValue();

				if( tf == duration ) {
					if( dt == null ) {
						return;
					}
					
					stopSecs.setValue( d0 + dt.doubleValue() );
					
				} else {
					if( n1 == null ) {
						return;
					}
					double d1 = n1.doubleValue();
					duration.setValue( d1 - d0 );
				}
				break;
			}
			// Date rtm = (Date) relativeTime.getValue();
			enaOk = true;
		} catch (ParseException e1) {
			// ignore e1.printStackTrace();
		} finally {
			ignoreChange = false;
			ok.setEnabled(enaOk);
		}
	}

	/**
	 * Used by the dialog to set a form default button.
	 * 
	 * @return
	 * 
	 *         The OK button.
	 */
	public JButton getOKButton() {
		return ok;
	}

	private void createUIComponents() {
		// TODO: add custom component creation code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label3 = new JLabel();
		description = new JTextField();
		label4 = new JLabel();
		colorCombo = new JComboBox<>();
		startDateLabel = new JLabel();
		startDateChooser = new JDateChooser();
		startSecsLabel = new JLabel();
		startSecs = new JFormattedTextField();
		stopDateLabel = new JLabel();
		stopDateChooser = new JDateChooser();
		stopSecsLabel = new JLabel();
		stopSecs = new JFormattedTextField();
		label7 = new JLabel();
		duration = new JFormattedTextField();
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
				"right:default, 2*($lcgap, [50dlu,default]), $lcgap, default, $lcgap, [40dlu,default]",
				"5*(default, $lgap), fill:default, 3*($lgap, default)"));

			//---- label3 ----
			label3.setText("Name:");
			panel1.add(label3, CC.xy(1, 1));
			panel1.add(description, CC.xywh(3, 1, 3, 1));

			//---- label4 ----
			label4.setText("Color:");
			panel1.add(label4, CC.xy(1, 3));
			panel1.add(colorCombo, CC.xy(3, 3));

			//---- startDateLabel ----
			startDateLabel.setText("Start Date/Time:");
			panel1.add(startDateLabel, CC.xy(1, 7));

			//---- startDateChooser ----
			startDateChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			panel1.add(startDateChooser, CC.xywh(3, 7, 3, 1));

			//---- startSecsLabel ----
			startSecsLabel.setText("Start Secs:");
			panel1.add(startSecsLabel, CC.xy(1, 9));
			panel1.add(startSecs, CC.xy(3, 9));

			//---- stopDateLabel ----
			stopDateLabel.setText("Stop Date/Time:");
			panel1.add(stopDateLabel, CC.xy(1, 11));

			//---- stopDateChooser ----
			stopDateChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			panel1.add(stopDateChooser, CC.xywh(3, 11, 3, 1));

			//---- stopSecsLabel ----
			stopSecsLabel.setText("Stop Secs:");
			panel1.add(stopSecsLabel, CC.xy(1, 13));
			panel1.add(stopSecs, CC.xy(3, 13));

			//---- label7 ----
			label7.setText("Duration(sec):");
			panel1.add(label7, CC.xywh(7, 11, 1, 3));

			//---- duration ----
			duration.addFocusListener(new FocusAdapter() {
				@Override
				public void focusLost(FocusEvent e) {
					durationFocusLost(e);
				}
			});
			panel1.add(duration, CC.xywh(9, 11, 1, 3));
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
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label3;
	private JTextField description;
	private JLabel label4;
	private JComboBox<Color> colorCombo;
	private JLabel startDateLabel;
	private JDateChooser startDateChooser;
	private JLabel startSecsLabel;
	private JFormattedTextField startSecs;
	private JLabel stopDateLabel;
	private JDateChooser stopDateChooser;
	private JLabel stopSecsLabel;
	private JFormattedTextField stopSecs;
	private JLabel label7;
	private JFormattedTextField duration;
	private JPanel panel2;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
