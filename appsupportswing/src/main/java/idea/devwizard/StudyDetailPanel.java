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
import javax.swing.event.ChangeEvent;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

import icuInterface.RpUtil;
import idea.persistmanager.sql.SQLExporter;
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
public class StudyDetailPanel extends JPanel implements WizardPanelInterface, DocumentListener {

	private WizardMasterInterface wizard;
	private File root;
	private RpStudy study;

	public StudyDetailPanel(WizardMasterInterface wizard, String root, boolean editLocation) {
		initComponents();
		this.wizard = wizard;
		this.root = new File(root);

		setName("Study Definition");
		refresh();

		Date now = new Date();
		startDate.setDate(now);

		title.getDocument().addDocumentListener(this);
		pi.getDocument().addDocumentListener(this);

		defaultLocation.setSelected(true);
		errorMessage.setText("");

		defaultLocation.setEnabled(editLocation);
		studyDir.setEnabled(editLocation);
		browse.setEnabled(editLocation);

		defaultLocationActionPerformed(null); // enable/disable fields as needed
		wizard.enableFinish(false);
	}

	@Override
	public void refresh() {

	}

	private void fieldTextChanged(InputMethodEvent e) {
		validateInput();
	}

	private void validateInput() {
		boolean ok = true;
		String err = "";

		String s = title.getText().trim();
		if (s.length() == 0) {
			err = "Study title is required.";
			ok = false;
		}

		s = pi.getText().trim();
		if (ok && s.length() == 0) {
			err = "PI: Principal Investigator is required.";
			ok = false;
		}

		if (defaultLocation.isEnabled() && defaultLocation.isSelected()) {
			String dest = title.getText().trim();
			File f = new File(root, dest);
			studyDir.setText(f.getPath());
			if (ok && f.exists()) {
				err = "A study with this name already exists.";
				ok = false;
			}
		}
		
		if( ok ) {
			
			boolean hasOutput = hdf5Check.isSelected();
			hasOutput |= sqlCheck.isSelected();
			hasOutput |= asciiCheck.isSelected();
			
			ok = hasOutput;
			
			if( !ok ) {
				err = "No data storage format selected.";
			}
		}

		errorMessage.setText(err);
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
			if (study == null) {
				study = new RpStudy();
			}
			study.setPi(pi.getText().trim());
			study.setTitle(title.getText().trim());
			study.setIdentifier(title.getText().trim());

			study.setStartDate(startDate.getDate());
			
			RpUtil.setParam( study, "hdf5", "" + hdf5Check.isSelected() );
			RpUtil.setParam( study, "sql", "" + sqlCheck.isSelected() );
			RpUtil.setParam( study, "ascii", "" +asciiCheck.isSelected() );
			RpUtil.setParam( study, "jdbc", jdbc.getText());

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

	private void defaultLocationActionPerformed(ActionEvent e) {
		boolean enable_edits = !defaultLocation.isSelected();
		studyDir.setEnabled(enable_edits);
		browse.setEnabled(enable_edits);
		fieldTextChanged(null);
	}

	private void hdf5CheckStateChanged(ChangeEvent e) {
		validateInput();
	}

	private void sqlCheckStateChanged(ChangeEvent e) {
		validateInput();
	}

	private void asciiCheckStateChanged(ChangeEvent e) {
		validateInput();
	}

	private void jdbcTestActionPerformed(ActionEvent e) {
		
		System.setProperty("SUBJECT", "TESTSUBJECT");
		System.setProperty("DATE", "20150101");
		System.setProperty("TIME", "091500");
		String message = "Passed";
		try {
			SQLExporter exporter = new SQLExporter( "exporterSQLite", jdbc.getText() );
			exporter.connect();
			exporter.disconnect();
		} catch( Exception x ) {
			message = x.getMessage();
		}
		GuiUtil.showMessage(message);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		panel1 = new JPanel();
		separator3 = compFactory.createSeparator("Study");
		panel2 = new JPanel();
		label2 = new JLabel();
		title = new JTextField();
		label4 = new JLabel();
		pi = new JTextField();
		label3 = new JLabel();
		startDate = new JDateChooser();
		label5 = new JLabel();
		label6 = new JLabel();
		separator1 = compFactory.createSeparator("Data Storage");
		panel3 = new JPanel();
		label7 = new JLabel();
		panel4 = new JPanel();
		hdf5Check = new JCheckBox();
		label10 = new JLabel();
		asciiCheck = new JCheckBox();
		sqlCheck = new JCheckBox();
		label8 = new JLabel();
		jdbc = new JTextField();
		jdbcTest = new JButton();
		label9 = new JLabel();
		label1 = new JLabel();
		defaultLocation = new JCheckBox();
		panel5 = new JPanel();
		studyDir = new JTextField();
		browse = new JButton();
		errorMessage = new JLabel();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"[250dlu,default]:grow",
			"fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow",
				"4*(default, $lgap), bottom:default:grow"));
			panel1.add(separator3, CC.xy(1, 1));

			//======== panel2 ========
			{
				panel2.setLayout(new FormLayout(
					"20dlu, $lcgap, right:[40dlu,default], $lcgap, [100dlu,default], $lcgap, [50dlu,default]:grow, $lcgap, default",
					"4*(default, $lgap), default"));

				//---- label2 ----
				label2.setText("Title:");
				panel2.add(label2, CC.xy(3, 1));

				//---- title ----
				title.addInputMethodListener(new InputMethodListener() {
					@Override
					public void caretPositionChanged(InputMethodEvent e) {}
					@Override
					public void inputMethodTextChanged(InputMethodEvent e) {
						fieldTextChanged(e);
					}
				});
				panel2.add(title, CC.xy(5, 1));

				//---- label4 ----
				label4.setText("PI:");
				panel2.add(label4, CC.xy(3, 3));
				panel2.add(pi, CC.xy(5, 3));

				//---- label3 ----
				label3.setText("Start Date:");
				panel2.add(label3, CC.xy(3, 5));
				panel2.add(startDate, CC.xy(5, 5));

				//---- label5 ----
				label5.setText("Status:");
				panel2.add(label5, CC.xy(3, 7));

				//---- label6 ----
				label6.setText("Open");
				panel2.add(label6, CC.xy(5, 7));
			}
			panel1.add(panel2, CC.xy(1, 3));
			panel1.add(separator1, CC.xy(1, 5));

			//======== panel3 ========
			{
				panel3.setLayout(new FormLayout(
					"20dlu, $lcgap, right:[40dlu,default], $lcgap, [150dlu,default]:grow",
					"fill:default, 2*($lgap, default)"));

				//---- label7 ----
				label7.setText("Format:");
				panel3.add(label7, CC.xy(3, 1, CC.DEFAULT, CC.TOP));

				//======== panel4 ========
				{
					panel4.setLayout(new FormLayout(
						"2*(default, $lcgap), [150dlu,default]:grow, $lcgap, [40dlu,default]",
						"5*(default, $lgap), default"));

					//---- hdf5Check ----
					hdf5Check.setText("HDF5");
					hdf5Check.addChangeListener(e -> hdf5CheckStateChanged(e));
					panel4.add(hdf5Check, CC.xy(1, 1));

					//---- label10 ----
					label10.setText("Hint:  jdbc:sqlite:/c:/tmp/file${SUBJECT}_${DATE}_${TIME}.db");
					panel4.add(label10, CC.xy(3, 3));

					//---- asciiCheck ----
					asciiCheck.setText("ASCII");
					asciiCheck.addChangeListener(e -> asciiCheckStateChanged(e));
					panel4.add(asciiCheck, CC.xy(1, 5));

					//---- sqlCheck ----
					sqlCheck.setText("SQLLite");
					sqlCheck.addChangeListener(e -> sqlCheckStateChanged(e));
					panel4.add(sqlCheck, CC.xy(1, 7));

					//---- label8 ----
					label8.setText("JDBC:");
					panel4.add(label8, CC.xy(3, 7));
					panel4.add(jdbc, CC.xy(5, 7));

					//---- jdbcTest ----
					jdbcTest.setText("Test");
					jdbcTest.addActionListener(e -> jdbcTestActionPerformed(e));
					panel4.add(jdbcTest, CC.xy(7, 7));

					//---- label9 ----
					label9.setText("Hint:  jdbc:sqlite:/c:/tmp/file${SUBJECT}_${DATE}_${TIME}.db");
					panel4.add(label9, CC.xywh(3, 9, 5, 1));
				}
				panel3.add(panel4, CC.xy(5, 1));

				//---- label1 ----
				label1.setText("Location:");
				panel3.add(label1, CC.xy(3, 3));

				//---- defaultLocation ----
				defaultLocation.setText("Use default location");
				defaultLocation.addActionListener(e -> defaultLocationActionPerformed(e));
				panel3.add(defaultLocation, CC.xy(5, 3));

				//======== panel5 ========
				{
					panel5.setLayout(new FormLayout(
						"default:grow, $lcgap, [40dlu,default]",
						"default"));
					panel5.add(studyDir, CC.xy(1, 1));

					//---- browse ----
					browse.setText("Browse");
					browse.addActionListener(e -> browseActionPerformed(e));
					panel5.add(browse, CC.xy(3, 1));
				}
				panel3.add(panel5, CC.xy(5, 5));
			}
			panel1.add(panel3, CC.xy(1, 7));

			//---- errorMessage ----
			errorMessage.setText("Error message.");
			panel1.add(errorMessage, CC.xy(1, 9));
		}
		add(panel1, CC.xy(1, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JComponent separator3;
	private JPanel panel2;
	private JLabel label2;
	private JTextField title;
	private JLabel label4;
	private JTextField pi;
	private JLabel label3;
	private JDateChooser startDate;
	private JLabel label5;
	private JLabel label6;
	private JComponent separator1;
	private JPanel panel3;
	private JLabel label7;
	private JPanel panel4;
	private JCheckBox hdf5Check;
	private JLabel label10;
	private JCheckBox asciiCheck;
	private JCheckBox sqlCheck;
	private JLabel label8;
	private JTextField jdbc;
	private JButton jdbcTest;
	private JLabel label9;
	private JLabel label1;
	private JCheckBox defaultLocation;
	private JPanel panel5;
	private JTextField studyDir;
	private JButton browse;
	private JLabel errorMessage;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public boolean finish() {
		return true;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	public void setStudy(RpStudy study) {
		this.study = study;
		if (study == null) {
			title.setText("");
			pi.setText("");
			defaultLocation.setText("");
			return;
		}
		title.setText(study.getTitle());
		pi.setText(study.getPi());
		studyDir.setText(study.getRepositoryLink());
		startDate.setDate(study.getStartDate());
		
		String useHdf5 = RpUtil.getParam(study, "hdf5" );
		hdf5Check.setSelected( "true".equals( useHdf5 ));
		String useSQL = RpUtil.getParam( study, "sql");
		sqlCheck.setSelected( "true".equals( useSQL ) );
		String useASCII = RpUtil.getParam( study, "ascii" );
		asciiCheck.setSelected( "true".equals( useASCII ) );
		
		String jdbc_string = RpUtil.getParam( study, "jdbc");
		if( jdbc_string == null ) {
			jdbc_string = "jdbc:sqlite:";
		}
		jdbc.setText( jdbc_string );
	}

}
