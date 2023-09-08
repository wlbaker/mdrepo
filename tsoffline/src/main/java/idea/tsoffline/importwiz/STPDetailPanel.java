/*
 * Created by JFormDesigner on Mon Feb 18 15:38:58 CST 2019
 */

package idea.tsoffline.importwiz;

import java.io.File;
import java.io.IOException;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.DefaultComponentFactory;

import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import net.miginfocom.swing.MigLayout;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.persist.TsoSessionSTPUtil;

/**
 * @author WILLIAM BAKER
 */
@Slf4j
public class STPDetailPanel extends JPanel implements WizardPanelInterface {
	@Setter
	TsoSessionSTPUtil stp;

	public STPDetailPanel(WizardMasterInterface openStudyWizard) {
		initComponents();
	}

	public void setFile(File f) throws IOException {
		stp = new TsoSessionSTPUtil();
		stp.readSessionFile(f);
		
	}
	
	@Override
	public void refresh() {
		String [] configInfo = null;
		
		if (stp != null) {
			configInfo = stp.getConfigInfo();
		}

		JLabel [] labels = { txtFile, txtSession, txtInstitute, txtLocation, txtDetail, txtDate, txtSubjectName, txtSubjectID, txtOperator };
		
		for( int i = 0; i < labels.length ; i++ ) {
			JLabel label = labels[i];
			if( configInfo == null || configInfo[i] == null ) {
				label.setText("");
			} else {
				label.setText( configInfo[i] );
			}
		}
		
		txt26.setText( ( configInfo == null || configInfo[26] == null) ? "" : configInfo[26] );		
		txt27.setText( ( configInfo == null || configInfo[27] == null) ? "" : configInfo[27] );

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean next() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean finish() {
		// TODO Auto-generated method stub
		return false;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Configuration Detail");
		label1 = new JLabel();
		txtFile = new JLabel();
		label2 = new JLabel();
		txtSession = new JLabel();
		label3 = new JLabel();
		txtInstitute = new JLabel();
		label4 = new JLabel();
		txtLocation = new JLabel();
		label5 = new JLabel();
		txtDetail = new JLabel();
		label6 = new JLabel();
		txtDate = new JLabel();
		label7 = new JLabel();
		txtSubjectName = new JLabel();
		label8 = new JLabel();
		txtSubjectID = new JLabel();
		label9 = new JLabel();
		txtOperator = new JLabel();
		label18 = new JLabel();
		txt26 = new JLabel();
		label19 = new JLabel();
		txt27 = new JLabel();

		//======== this ========
		setLayout(new MigLayout(
			"hidemode 3",
			// columns
			"[fill]" +
			"[100:n,right]" +
			"[grow,fill]",
			// rows
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]" +
			"[]"));
		add(separator1, "cell 0 0 3 1");

		//---- label1 ----
		label1.setText("Original File:");
		add(label1, "cell 1 1");

		//---- txtFile ----
		txtFile.setText("txtFile");
		add(txtFile, "cell 2 1");

		//---- label2 ----
		label2.setText("Session ID:");
		add(label2, "cell 1 2");

		//---- txtSession ----
		txtSession.setText("txtSession");
		add(txtSession, "cell 2 2");

		//---- label3 ----
		label3.setText("Institute:");
		add(label3, "cell 1 3");

		//---- txtInstitute ----
		txtInstitute.setText("txtInstitute");
		add(txtInstitute, "cell 2 3");

		//---- label4 ----
		label4.setText("Location:");
		add(label4, "cell 1 4");

		//---- txtLocation ----
		txtLocation.setText("txtLocation");
		add(txtLocation, "cell 2 4");

		//---- label5 ----
		label5.setText("Detail:");
		add(label5, "cell 1 5");

		//---- txtDetail ----
		txtDetail.setText("txtDetail");
		add(txtDetail, "cell 2 5");

		//---- label6 ----
		label6.setText("Date:");
		add(label6, "cell 1 6");

		//---- txtDate ----
		txtDate.setText("txtDate");
		add(txtDate, "cell 2 6");

		//---- label7 ----
		label7.setText("Subject Name:");
		add(label7, "cell 1 7");

		//---- txtSubjectName ----
		txtSubjectName.setText("txtSubjectName");
		add(txtSubjectName, "cell 2 7");

		//---- label8 ----
		label8.setText("Subject ID:");
		add(label8, "cell 1 8");

		//---- txtSubjectID ----
		txtSubjectID.setText("txtSubjectID");
		add(txtSubjectID, "cell 2 8");

		//---- label9 ----
		label9.setText("Operator:");
		add(label9, "cell 1 9");

		//---- txtOperator ----
		txtOperator.setText("txtOperator");
		add(txtOperator, "cell 2 9");

		//---- label18 ----
		label18.setText("26:");
		add(label18, "cell 1 11");

		//---- txt26 ----
		txt26.setText("txt26");
		add(txt26, "cell 2 11");

		//---- label19 ----
		label19.setText("27:");
		add(label19, "cell 1 12");

		//---- txt27 ----
		txt27.setText("txt27");
		add(txt27, "cell 2 12");
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	private JComponent separator1;
	private JLabel label1;
	private JLabel txtFile;
	private JLabel label2;
	private JLabel txtSession;
	private JLabel label3;
	private JLabel txtInstitute;
	private JLabel label4;
	private JLabel txtLocation;
	private JLabel label5;
	private JLabel txtDetail;
	private JLabel label6;
	private JLabel txtDate;
	private JLabel label7;
	private JLabel txtSubjectName;
	private JLabel label8;
	private JLabel txtSubjectID;
	private JLabel label9;
	private JLabel txtOperator;
	private JLabel label18;
	private JLabel txt26;
	private JLabel label19;
	private JLabel txt27;
	// JFormDesigner - End of variables declaration //GEN-END:variables

}
