/*
 * Created by JFormDesigner on Mon Oct 05 16:17:27 CDT 2009
 */

package idea.devwizard;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputMethodEvent;
import java.awt.event.InputMethodListener;
import java.io.File;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

import idea.schema.rp.RpStudy;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.meddaq.AppSetup;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class RetrievalStudyPanel extends JPanel implements WizardPanelInterface, DocumentListener {

	public static final int IMPORT = 1;
	public static final int PUBLISH = 2;
	public static final int SUBSCRIBE = 3;
	
	private WizardMasterInterface wizard;
	public RetrievalStudyPanel(WizardMasterInterface wizard, int style ) {
		initComponents();
		this.wizard = wizard;
		
		setName( "Study Definition" );
		refresh();

		Date now = new Date();
		startDate.setDate(now);

		title.getDocument().addDocumentListener(this);
		pi.getDocument().addDocumentListener(this);
		if( style == IMPORT ) {
			retrieve.setVisible( false );
			retrieveData.setVisible( false );
			uriName.setVisible( false );
			uriLabel.setVisible(false);
		}
	}

	@Override
	public void refresh() {

	}

	private void fieldTextChanged(InputMethodEvent e) {

		boolean ok = true;

		String s = title.getText().trim();
		if (s.length() == 0) {
			ok = false;
		}

		s = pi.getText().trim();
		if (s.length() == 0) {
			ok = false;
		}

		String dir = title.getText().trim();
		
		wizard.enableNext(ok);
	}

	@Override
	public void changedUpdate(DocumentEvent e) {
		fieldTextChanged(null);
	}

	@Override
	public void insertUpdate(DocumentEvent e) {
		fieldTextChanged(null);
	}

	@Override
	public void removeUpdate(DocumentEvent e) {
		fieldTextChanged(null);
	}

	@Override
	public boolean next() {
		boolean ok = false;
		RepositoryInterface local = RepositoryFactory.getLocalRepository();
		try {
			RpStudy study = new RpStudy();

			study.setPi(pi.getText().trim());
			study.setTitle(title.getText().trim());

			study.setStartDate(startDate.getDate());

			local.createStudy(study);

			wizard.popPageUntil("Study Selection");
			ok = true;
		} catch (Exception e) {
			GuiUtil.showError("Creating Study: ", e);
		}

		return ok;
	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = PrefUtil.getUserPref(AppSetup.getLocalRepositoryDir(), null);
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.DIRECTORIES_ONLY, "Directory", this, parent, new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				File file = (File) e.getSource();
				studyDir.setText(file.getAbsolutePath());
			}
		});
	}


	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		panel1 = new JPanel();
		separator3 = compFactory.createSeparator("Study");
		panel2 = new JPanel();
		uriLabel = new JLabel();
		uriName = new JTextField();
		label7 = new JLabel();
		studyDir = new JTextField();
		browse = new JButton();
		retrieveData = new JCheckBox();
		retrieve = new JButton();
		label2 = new JLabel();
		title = new JTextField();
		label4 = new JLabel();
		pi = new JTextField();
		label3 = new JLabel();
		startDate = new JDateChooser();
		label5 = new JLabel();
		label6 = new JLabel();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[250dlu,default]:grow, $rgap, [100dlu,default]",
			"fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow",
				"2*(default, $lgap), default"));
			panel1.add(separator3, cc.xy(1, 1));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout(
					"20dlu, $lcgap, right:default, $lcgap, [100dlu,default], $lcgap, [50dlu,default], $lcgap, default",
					"9*(default, $lgap), default"));

				//---- uriLabel ----
				uriLabel.setText("URI:");
				panel2.add(uriLabel, cc.xy(3, 3));
				panel2.add(uriName, cc.xywh(5, 3, 3, 1));

				//---- label7 ----
				label7.setText("Local Directory:");
				panel2.add(label7, cc.xy(3, 5));
				panel2.add(studyDir, cc.xywh(5, 5, 3, 1));

				//---- browse ----
				browse.setText("Browse");
				browse.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						browseActionPerformed(e);
					}
				});
				panel2.add(browse, cc.xy(9, 5));

				//---- retrieveData ----
				retrieveData.setText("Retrieve study data");
				panel2.add(retrieveData, cc.xy(5, 7));

				//---- retrieve ----
				retrieve.setText("Retrieve");
				retrieve.setEnabled(false);
				panel2.add(retrieve, cc.xy(9, 7));

				//---- label2 ----
				label2.setText("Title:");
				panel2.add(label2, cc.xy(3, 11));

				//---- title ----
				title.setEnabled(false);
				title.addInputMethodListener(new InputMethodListener() {
					@Override
					public void caretPositionChanged(InputMethodEvent e) {}
					@Override
					public void inputMethodTextChanged(InputMethodEvent e) {
						fieldTextChanged(e);
					}
				});
				panel2.add(title, cc.xy(5, 11));

				//---- label4 ----
				label4.setText("PI:");
				panel2.add(label4, cc.xy(3, 13));

				//---- pi ----
				pi.setEnabled(false);
				panel2.add(pi, cc.xy(5, 13));

				//---- label3 ----
				label3.setText("Start Date:");
				panel2.add(label3, cc.xy(3, 15));

				//---- startDate ----
				startDate.setEnabled(false);
				panel2.add(startDate, cc.xy(5, 15));

				//---- label5 ----
				label5.setText("Status:");
				panel2.add(label5, cc.xy(3, 17));

				//---- label6 ----
				label6.setText("Open");
				panel2.add(label6, cc.xy(5, 17));
			}
			panel1.add(panel2, cc.xy(1, 3));
		}
		add(panel1, cc.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JComponent separator3;
	private JPanel panel2;
	private JLabel uriLabel;
	private JTextField uriName;
	private JLabel label7;
	private JTextField studyDir;
	private JButton browse;
	private JCheckBox retrieveData;
	private JButton retrieve;
	private JLabel label2;
	private JTextField title;
	private JLabel label4;
	private JTextField pi;
	private JLabel label3;
	private JDateChooser startDate;
	private JLabel label5;
	private JLabel label6;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return false;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

}
