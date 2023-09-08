/*
 * Created by JFormDesigner on Fri Apr 06 09:49:40 CDT 2012
 */

package idea.tsoffline;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.util.Date;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.IDateEditor;
import com.toedter.calendar.JDateChooser;
import com.toedter.calendar.JTextFieldDateEditor;

import idea.persistence.ArchiveMetaData;
import idea.GuiUtil;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class DateRangeSelectionPanel extends JPanel {
	private Date metaStart;
	private Date metaEnd;
	private ArchiveMetaData meta;

	public DateRangeSelectionPanel() {
		initComponents();

		GuiUtil.initUIFixes(this, false);

		startTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
		endTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");

	}

	public void setStartStop(Date startTime, Date endTime) {
		this.metaStart = startTime;
		this.metaEnd = endTime;
		if (metaStart != null) {
			startTimeChooser.setDate(metaStart);
		}
		if (metaEnd != null) {
			endTimeChooser.setDate(metaEnd);
		}
	}

	private void startTimeChooserFocusLost(FocusEvent e) {
		Date dtStart = startTimeChooser.getDate();
		Date dtEnd = endTimeChooser.getDate();
		if (dtStart == null || dtEnd == null) {
			return;
		}

		if (dtStart.getTime() > dtEnd.getTime()) {
			endTimeChooser.setDate(dtStart);
		}
	}

	private void stopMinActionPerformed(ActionEvent e) {
		Date dt0a = metaStart;
		Date dt0b = startTimeChooser.getDate();
		if (dt0a == null || dt0b == null) {
			// keep going
		} else if (dt0b.getTime() < dt0a.getTime()) {
			// set startTime to beginning of data
			startTimeChooser.setDate(dt0a);
		}
		endTimeChooser.setDate(startTimeChooser.getDate());
	}

	private void stopMaxActionPerformed(ActionEvent e) {
		endTimeChooser.setDate(metaEnd);
	}

	private void plus10MActionPerformed(ActionEvent e) {
		addEndTime(10 * 60 * 1000);
	}

	private void plus1HActionPerformed(ActionEvent e) {
		addEndTime(60 * 60 * 1000);
	}

	private void minus10MActionPerformed(ActionEvent e) {
		addStartTime(-10 * 60 * 1000);
	}

	private void minus1HActionPerformed(ActionEvent e) {
		addStartTime(-60 * 60 * 1000);
	}

	private void addEndTime(long ms) {
		Date dt0 = endTimeChooser.getDate();
		if (dt0 == null) {
			dt0 = startTimeChooser.getDate();
		}
		if (dt0 == null) {
			return;
		}

		dt0.setTime(dt0.getTime() + ms);

		if (metaEnd != null) {
			if (dt0.getTime() > metaEnd.getTime()) {
				dt0 = metaEnd;
			}
		}

		endTimeChooser.setDate(dt0);
		// 060319 endTimeChooser.setForeground(Color.WHITE);
		IDateEditor editor = endTimeChooser.getDateEditor();
		JTextFieldDateEditor sub_comp = (JTextFieldDateEditor) editor.getUiComponent();
		// 060319 sub_comp.setForeground(Color.WHITE);
	}

	private void addStartTime(long ms) {
		Date dt0 = startTimeChooser.getDate();
		if (dt0 == null) {
			dt0 = endTimeChooser.getDate();
		}
		if (dt0 == null) {
			return;
		}

		dt0.setTime(dt0.getTime() + ms);

		if (metaEnd != null) {
			if (dt0.getTime() > metaEnd.getTime()) {
				dt0 = metaEnd;
			}
		}

		if (metaStart != null) {
			if (dt0.getTime() < metaStart.getTime()) {
				dt0 = metaStart;
			}
		}

		startTimeChooser.setDate(dt0);
		// 060319 startTimeChooser.setForeground(Color.WHITE);
		IDateEditor editor = startTimeChooser.getDateEditor();
		JTextFieldDateEditor sub_comp = (JTextFieldDateEditor) editor.getUiComponent();
		// 060319 sub_comp.setForeground(Color.WHITE);
	}

	private void startMinActionPerformed(ActionEvent e) {
		startTimeChooser.setDate(metaStart);
	}

	private void startMaxActionPerformed(ActionEvent e) {
		startTimeChooser.setDate(metaEnd);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		panel3 = new JPanel();
		panel1 = new JPanel();
		panel5 = new JPanel();
		label7 = new JLabel();
		startTimeChooser = new JDateChooser();
		startMin = new JButton();
		startMax = new JButton();
		minus10M = new JButton();
		minus1H = new JButton();
		panel4 = new JPanel();
		label8 = new JLabel();
		endTimeChooser = new JDateChooser();
		stopMin = new JButton();
		stopMax = new JButton();
		plus10M = new JButton();
		plus1H = new JButton();

		//======== this ========
		setLayout(new BorderLayout());

		//======== panel3 ========
		{
			panel3.setBorder(Borders.DLU4);
			panel3.setLayout(new FormLayout(
				"[80dlu,default]:grow",
				"default"));

			//======== panel1 ========
			{
				panel1.setLayout(new FormLayout(
					"[10dlu,default], 2*($lcgap, default)",
					"2*(default, $lgap), default"));

				//======== panel5 ========
				{
					panel5.setLayout(new FormLayout(
						"right:[50dlu,default], $rgap, [90dlu,default], 2*(default), $lcgap, [50dlu,default], $lcgap, [50dlu,pref], $lcgap, default",
						"default"));

					//---- label7 ----
					label7.setText("Start Time:");
					panel5.add(label7, CC.xy(1, 1));

					//---- startTimeChooser ----
					startTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
					startTimeChooser.addFocusListener(new FocusAdapter() {
						@Override
						public void focusLost(FocusEvent e) {
							startTimeChooserFocusLost(e);
						}
					});
					panel5.add(startTimeChooser, CC.xy(3, 1));

					//---- startMin ----
					startMin.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/left-solid-circle.PNG")));
					startMin.setPreferredSize(new Dimension(24, 21));
					startMin.setMinimumSize(new Dimension(20, 20));
					startMin.addActionListener(e -> startMinActionPerformed(e));
					panel5.add(startMin, CC.xy(4, 1));

					//---- startMax ----
					startMax.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/right-solid-circle.PNG")));
					startMax.setMinimumSize(new Dimension(24, 21));
					startMax.setPreferredSize(new Dimension(24, 21));
					startMax.addActionListener(e -> startMaxActionPerformed(e));
					panel5.add(startMax, CC.xy(5, 1));

					//---- minus10M ----
					minus10M.setText("-10min");
					minus10M.addActionListener(e -> minus10MActionPerformed(e));
					panel5.add(minus10M, CC.xy(7, 1));

					//---- minus1H ----
					minus1H.setText("-1hr");
					minus1H.setActionCommand("-1hr");
					minus1H.addActionListener(e -> minus1HActionPerformed(e));
					panel5.add(minus1H, CC.xy(9, 1));
				}
				panel1.add(panel5, CC.xy(3, 1));

				//======== panel4 ========
				{
					panel4.setLayout(new FormLayout(
						"right:[50dlu,default], $rgap, [90dlu,default], 2*(default), $lcgap, [50dlu,default], $lcgap, [50dlu,pref], $lcgap, default",
						"default"));

					//---- label8 ----
					label8.setText("Stop Time:");
					panel4.add(label8, CC.xy(1, 1));

					//---- endTimeChooser ----
					endTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
					panel4.add(endTimeChooser, CC.xy(3, 1));

					//---- stopMin ----
					stopMin.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/left-solid-circle.PNG")));
					stopMin.setPreferredSize(new Dimension(24, 21));
					stopMin.setMinimumSize(new Dimension(20, 20));
					stopMin.addActionListener(e -> stopMinActionPerformed(e));
					panel4.add(stopMin, CC.xy(4, 1));

					//---- stopMax ----
					stopMax.setIcon(new ImageIcon(getClass().getResource("/idea/tsoffline/images/right-solid-circle.PNG")));
					stopMax.setMinimumSize(new Dimension(24, 21));
					stopMax.setPreferredSize(new Dimension(24, 21));
					stopMax.addActionListener(e -> stopMaxActionPerformed(e));
					panel4.add(stopMax, CC.xy(5, 1));

					//---- plus10M ----
					plus10M.setText("+10min");
					plus10M.addActionListener(e -> plus10MActionPerformed(e));
					panel4.add(plus10M, CC.xy(7, 1));

					//---- plus1H ----
					plus1H.setText("+1hr");
					plus1H.addActionListener(e -> plus1HActionPerformed(e));
					panel4.add(plus1H, CC.xy(9, 1));
				}
				panel1.add(panel4, CC.xy(3, 3));
			}
			panel3.add(panel1, CC.xy(1, 1));
		}
		add(panel3, BorderLayout.CENTER);
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel panel3;
	private JPanel panel1;
	private JPanel panel5;
	private JLabel label7;
	private JDateChooser startTimeChooser;
	private JButton startMin;
	private JButton startMax;
	private JButton minus10M;
	private JButton minus1H;
	private JPanel panel4;
	private JLabel label8;
	private JDateChooser endTimeChooser;
	private JButton stopMin;
	private JButton stopMax;
	private JButton plus10M;
	private JButton plus1H;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

	public Date getStartDate() {
		return startTimeChooser.getDate();
	}

	public Date getEndDate() {
		return endTimeChooser.getDate();
	}

	public void setStartDate(Date sig_start) {
		startTimeChooser.setDate(sig_start);
	}

	public void setEndDate(Date sig_end) {
		endTimeChooser.setDate(sig_end);
	}
}
