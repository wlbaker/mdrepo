/*
 * Created by JFormDesigner on Sun Feb 28 12:55:51 CST 2010
 */

package idea.gui.wizard;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.InputMethodEvent;
import java.awt.event.InputMethodListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.CustomizedDocument;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
@Slf4j
public class DefaultStudyHeaderPanel extends JPanel implements WizardPanelInterface {

	private WizardMasterInterface wizard;
	private RpSubject header;

	public DefaultStudyHeaderPanel(WizardMasterInterface wiz) {
		initComponents();
		setName("Study Info");

		this.wizard = wiz;

		String fmt = studyDate.getDateFormatString();
		GuiUtil.initPanel(this); // this standardizes the date format string!
		if (fmt != null) {
			studyDate.setDateFormatString(fmt);
		}

		CustomizedDocument customDoc = new CustomizedDocument();
		customDoc.setUpperCase(true);
		customDoc.setMaxChars(7);

		medicalID.setDocument(customDoc);

		Calendar cal = Calendar.getInstance();
		Date today = cal.getTime();

		studyDate.setDate(today);
		studyDate.setForeground(Color.BLACK);  // for JTattoo...why does this field have color problems
	
		for ( int idx = 0; idx < studyDate.getComponentCount(); idx++) {
			Component comp = studyDate.getComponent(idx);
			if( comp instanceof JComponent ) {
				JComponent my_jc = (JComponent)comp;
				my_jc.setForeground( Color.BLACK);
			};
		}
		
		operator.setText(System.getProperty("user.name"));

	}

	public void setSiteInfo(SiteInfo site) {
		company.setText(site.getCompany());
		location.setText(site.getLocation());
		organization.setText(site.getOrganization());
	}

	public void setStudyTitle(String titleText ) {
		studyTitle.setText( titleText );
	}

	private RpSubject panel2Model() {
		if (header == null) {
			header = new RpSubject();
		}

		header.setCompany(company.getText());
		header.setOrganization(organization.getText());
		header.setLocation(location.getText());
		header.setStudyTitle(studyTitle.getText());
		header.setSurgeryDate( studyDate.getDate() );
		header.setSeqNo(subjectNumber.getText());
		header.setMedicalId(medicalID.getText());
		header.setOperator(operator.getText());
		header.setNotes(notes.getText());

		return header;
	}

	public void setViewOnly(boolean b) {
		studyDate.setEnabled(!b);
		medicalID.setEnabled(!b);
		operator.setEnabled(!b);
		notes.setEnabled(!b);
	}

	public void setStudyHeader(RpSubject studyHeader) {
		if (studyHeader == null) {

		} else {
			company.setText(safe(studyHeader.getCompany()));
			organization.setText(safe(studyHeader.getOrganization()));
			location.setText(safe(studyHeader.getLocation() ));
			studyTitle.setText(safe(studyHeader.getStudyTitle() ));
			studyDate.setDate( studyHeader.getSurgeryDate() );
			subjectNumber.setText(safe(studyHeader.getSeqNo()));
			medicalID.setText(safe(studyHeader.getMedicalId()));
			operator.setText(safe(studyHeader.getOperator() ));
			notes.setText(safe(studyHeader.getNotes() ));
		}
	}

	private String safe(String s) {
		if( s == null ) {
			s = "";
		}
		return s;
	}

	private void medicalIDInputMethodTextChanged(InputMethodEvent e) {
		boolean ok = true;

		String s = medicalID.getText().trim();
		if (s.length() == 0) {
			System.err.println("FIXME: need better determination of field validity");
			ok = false;
		}

		wizard.enableNext(ok);
	}

	private void medicalIDKeyTyped(KeyEvent e) {
		medicalIDInputMethodTextChanged(null); // not getting input method text changed?
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		label3 = new JLabel();
		company = new JLabel();
		label4 = new JLabel();
		organization = new JLabel();
		label1 = new JLabel();
		location = new JLabel();
		label2 = new JLabel();
		studyTitle = new JLabel();
		label7 = new JLabel();
		panel1 = new JPanel();
		studyDate = new JDateChooser();
		label8 = new JLabel();
		panel2 = new JPanel();
		subjectNumber = new JTextField();
		allocate = new JButton();
		label9 = new JLabel();
		panel3 = new JPanel();
		medicalID = new JTextField();
		label10 = new JLabel();
		panel4 = new JPanel();
		operator = new JTextField();
		label11 = new JLabel();
		panel5 = new JPanel();
		notes = new JTextField();

		//======== this ========
		setLayout(new FormLayout(
			"default, $lcgap, right:default, $lcgap, default:grow",
			"12*(default, $lgap), default"));

		//---- label3 ----
		label3.setText("Company:");
		add(label3, CC.xy(3, 3));

		//---- company ----
		company.setText("US Army Institute of Surgical Research");
		add(company, CC.xy(5, 3));

		//---- label4 ----
		label4.setText("Organization:");
		add(label4, CC.xy(3, 5));

		//---- organization ----
		organization.setText("CCCE");
		add(organization, CC.xy(5, 5));

		//---- label1 ----
		label1.setText("Location:");
		add(label1, CC.xy(3, 7));

		//---- location ----
		location.setText("Brooke Army Medical Center");
		add(location, CC.xy(5, 7));

		//---- label2 ----
		label2.setText("Study Title:");
		add(label2, CC.xy(3, 11));

		//---- studyTitle ----
		studyTitle.setText("text");
		add(studyTitle, CC.xy(5, 11));

		//---- label7 ----
		label7.setText("Study Date:");
		add(label7, CC.xy(3, 13));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[100dlu,default], $lcgap, default",
				"default"));

			//---- studyDate ----
			studyDate.setDateFormatString("MM/dd/yyyy HH:mm");
			panel1.add(studyDate, CC.xy(1, 1));
		}
		add(panel1, CC.xy(5, 13));

		//---- label8 ----
		label8.setText("Subject Number:");
		add(label8, CC.xy(3, 15));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, [20dlu,default], $lcgap, default",
				"default"));

			//---- subjectNumber ----
			subjectNumber.setEnabled(false);
			panel2.add(subjectNumber, CC.xy(1, 1));

			//---- allocate ----
			allocate.setText("Allocate");
			allocate.setEnabled(false);
			panel2.add(allocate, CC.xy(5, 1));
		}
		add(panel2, CC.xy(5, 15));

		//---- label9 ----
		label9.setText("Medical Record No:");
		add(label9, CC.xy(3, 17));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default",
				"default"));

			//---- medicalID ----
			medicalID.addInputMethodListener(new InputMethodListener() {
				@Override
				public void caretPositionChanged(InputMethodEvent e) {}
				@Override
				public void inputMethodTextChanged(InputMethodEvent e) {
					medicalIDInputMethodTextChanged(e);
				}
			});
			medicalID.addKeyListener(new KeyAdapter() {
				@Override
				public void keyTyped(KeyEvent e) {
					medicalIDKeyTyped(e);
				}
			});
			panel3.add(medicalID, CC.xy(1, 1));
		}
		add(panel3, CC.xy(5, 17));

		//---- label10 ----
		label10.setText("Operator:");
		add(label10, CC.xy(3, 21));

		//======== panel4 ========
		{
			panel4.setLayout(new FormLayout(
				"[150dlu,default], 2*($lcgap, default)",
				"default"));
			panel4.add(operator, CC.xy(1, 1));
		}
		add(panel4, CC.xy(5, 21));

		//---- label11 ----
		label11.setText("Notes:");
		add(label11, CC.xy(3, 23));

		//======== panel5 ========
		{
			panel5.setLayout(new FormLayout(
				"[150dlu,default], $lcgap, default",
				"default"));
			panel5.add(notes, CC.xy(1, 1));
		}
		add(panel5, CC.xy(5, 23));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JLabel label3;
	private JLabel company;
	private JLabel label4;
	private JLabel organization;
	private JLabel label1;
	private JLabel location;
	private JLabel label2;
	private JLabel studyTitle;
	private JLabel label7;
	private JPanel panel1;
	private JDateChooser studyDate;
	private JLabel label8;
	private JPanel panel2;
	private JTextField subjectNumber;
	private JButton allocate;
	private JLabel label9;
	private JPanel panel3;
	private JTextField medicalID;
	private JLabel label10;
	private JPanel panel4;
	private JTextField operator;
	private JLabel label11;
	private JPanel panel5;
	private JTextField notes;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		// Wizard wizard = (Wizard) e.getSource();
		//
		// RpSubject header = createStudyHeader();
		// wizard.setStudyHeader(header);
		//
		//
		// Wizard wizard = (Wizard) e.getSource();
		//
		// RpSubject header = createStudyHeader();
		//
		// wizard.setStudyHeader(header);
		//
		// GuiUtil.closeDialog(DefaultStudyHeaderPanel.this);

		return true;
	}

	@Override
	public boolean next() {
		return true;
	}

	public RpSubject getHeader() {
		return panel2Model();
	}

	@Override
	public void refresh() {
		
		if( medicalID.isEnabled() ) {
			medicalID.requestFocus();
		}

		if (header != null) {
			company.setText(header.getCompany());
			organization.setText(header.getOrganization());
			location.setText(header.getLocation());
			studyTitle.setText(header.getStudyTitle());
			studyDate.setDate( header.getSurgeryDate() );
			subjectNumber.setText(header.getSeqNo());
			medicalID.setText(header.getMedicalId());
			operator.setText(header.getOperator());
			notes.setText(header.getNotes());
		}

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	public void setStartTime(Date time) {
		studyDate.setDate(time);
	}

	public void enableEdits(boolean b) {
			studyDate.setEnabled(b);
			subjectNumber.setEnabled(b);
			medicalID.setEnabled(b);
			operator.setEnabled(b);
			notes.setEnabled(b);
			
			//log.warning("In case of substance dark L&F, set studyData to white");
			//studyDate.setForeground(Color.WHITE);
	}

	public String getNotes() {
		return notes.getText();
	}

}
