/*
 * Created by JFormDesigner on Fri Apr 16 12:30:26 CDT 2010
 */

package idea.simulator;

import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.io.File;
import java.io.IOException;
import java.util.Date;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.WizardPanelInterface;
import idea.meddaq.AppSetup;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SimulatorFilePanel extends JPanel implements WizardPanelInterface {

	SimulatorWizard wizard;
	private ArchiveMetaData meta;

	public SimulatorFilePanel(SimulatorWizard wizard) {
		initComponents();
		setName("Data Format");
		this.wizard = wizard;
		prepareDocs();

		GuiUtil.initPanel(this);

		startTimeChooser.setDate(wizard.getMetaStartTime());
		endTimeChooser.setDate(wizard.getMetaEndTime());

		startTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
		endTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");

		String lastFile = AppSetup.getSimulatorFile();
		if (lastFile != null) {
			dir.setText(lastFile);
			try {
				refresh(new File(lastFile));
			} catch (IOException e) {
				// we can ignore this exception...user will see no start/stop
				// times on the screen
			}
		}

	}

	private void prepareDocs() {

		// doc = new CustomizedDocument();
		// doc.setMaxChars(32);
		// username.setDocument(doc);

	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = dir.getText();
		if (lastDir.length() == 0) {
			lastDir = AppSetup.getSimulatorFile();
		}
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "Simulator File", this, parent, new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				File file = (File) e.getSource();
				dir.setText(file.getAbsolutePath());

				try {
					SimulatorFilePanel.this.refresh(file);
				} catch (IOException e1) {
					GuiUtil.showError("Simulator File Error", e1);
				}
			}
		});
	}

	protected void refresh(File file) throws IOException {

		if (!file.exists()) {
			startTimeChooser.setDate(null);
			endTimeChooser.setDate(null);
			return;
		}
		wizard.enableFinish(false);

		PiSubjectImporter importer = PiImporterUtil.getImporterFromFile(file);
		importer.connect();

		meta = importer.getMetaData();
		importer.disconnect();

		if (wizard.getMetaStartTime() == null || wizard.getMetaEndTime() == null) {
			startTimeChooser.setDate(meta.getStartTime());
			endTimeChooser.setDate(meta.getStopTime());
		} else {
			startTimeChooser.setDate(wizard.getMetaStartTime());
			endTimeChooser.setDate(wizard.getMetaEndTime());
		}
		
		wizard.enableFinish(true);
		wizard.setSimulationSource("file", null, file.getCanonicalPath());
	}

	private void saveActionPerformed(ActionEvent e) {

		try {
			AppSetup.setSimulatorFile(dir.getText());

		} catch (Exception ee) {
			GuiUtil.showError("Export Data Format: ", ee);
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
		Date dt0a = wizard.getMetaStartTime();
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
		endTimeChooser.setDate(meta.getStopTime());
	}

	private void plus10MActionPerformed(ActionEvent e) {
		addEndTime(10 * 60 * 1000);
	}

	private void plus1HActionPerformed(ActionEvent e) {
		addEndTime(60 * 60 * 1000);
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

		Date metaEnd = meta.getStopTime();
		if (metaEnd != null) {
			if (dt0.getTime() > metaEnd.getTime()) {
				dt0 = metaEnd;
			}
		}

		endTimeChooser.setDate(dt0);
	}

	private void dirFocusLost(FocusEvent e) {
		File file = new File( dir.getText() );
		try {
			refresh(file);
		} catch (IOException e1) {
			GuiUtil.showError("Simulator: Refresh Dates", e1);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Simulation File");
		panel3 = new JPanel();
		label5 = new JLabel();
		dir = new JTextField();
		browse = new JButton();
		label7 = new JLabel();
		startTimeChooser = new JDateChooser();
		label8 = new JLabel();
		endTimeChooser = new JDateChooser();
		panel4 = new JPanel();
		stopMin = new JButton();
		stopMax = new JButton();
		plus10M = new JButton();
		plus1H = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, default, $ugap, default, $lgap, default"));
		add(separator1, cc.xy(1, 1));

		//======== panel3 ========
		{
			panel3.setLayout(new FormLayout(
				"right:60dlu, $lcgap, [80dlu,default], $lcgap, [80dlu,default]:grow, $lcgap, [50dlu,default]",
				"4*(default, $lgap), default"));

			//---- label5 ----
			label5.setText("File Name:");
			panel3.add(label5, cc.xy(1, 3));

			//---- dir ----
			dir.addFocusListener(new FocusAdapter() {
				@Override
				public void focusLost(FocusEvent e) {
					dirFocusLost(e);
				}
			});
			panel3.add(dir, cc.xywh(3, 3, 3, 1));

			//---- browse ----
			browse.setText("Browse");
			browse.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					browseActionPerformed(e);
				}
			});
			panel3.add(browse, cc.xy(7, 3));

			//---- label7 ----
			label7.setText("Start Time:");
			panel3.add(label7, cc.xy(1, 5));

			//---- startTimeChooser ----
			startTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			startTimeChooser.addFocusListener(new FocusAdapter() {
				@Override
				public void focusLost(FocusEvent e) {
					startTimeChooserFocusLost(e);
				}
			});
			panel3.add(startTimeChooser, cc.xy(3, 5));

			//---- label8 ----
			label8.setText("Stop Time:");
			panel3.add(label8, cc.xy(1, 7));

			//---- endTimeChooser ----
			endTimeChooser.setDateFormatString("MM/dd/yyyy HH:mm:ss");
			panel3.add(endTimeChooser, cc.xy(3, 7));

			//======== panel4 ========
			{
				panel4.setLayout(new FormLayout(
					"2*(default), $lcgap, default, $lcgap, 40dlu, $lcgap, default",
					"default"));

				//---- stopMin ----
				stopMin.setIcon(new ImageIcon(getClass().getResource("/idea/image/left-solid-circle.PNG")));
				stopMin.setPreferredSize(new Dimension(24, 21));
				stopMin.setMinimumSize(new Dimension(20, 20));
				stopMin.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						stopMinActionPerformed(e);
					}
				});
				panel4.add(stopMin, cc.xy(1, 1));

				//---- stopMax ----
				stopMax.setIcon(new ImageIcon(getClass().getResource("/idea/image/right-solid-circle.PNG")));
				stopMax.setMinimumSize(new Dimension(24, 21));
				stopMax.setPreferredSize(new Dimension(24, 21));
				stopMax.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						stopMaxActionPerformed(e);
					}
				});
				panel4.add(stopMax, cc.xy(2, 1));

				//---- plus10M ----
				plus10M.setText("+10min");
				plus10M.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						plus10MActionPerformed(e);
					}
				});
				panel4.add(plus10M, cc.xy(4, 1));

				//---- plus1H ----
				plus1H.setText("+1hr");
				plus1H.addActionListener(new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						plus1HActionPerformed(e);
					}
				});
				panel4.add(plus1H, cc.xy(6, 1));
			}
			panel3.add(panel4, cc.xywh(5, 7, 3, 1));
		}
		add(panel3, cc.xy(1, 3));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel3;
	private JLabel label5;
	private JTextField dir;
	private JButton browse;
	private JLabel label7;
	private JDateChooser startTimeChooser;
	private JLabel label8;
	private JDateChooser endTimeChooser;
	private JPanel panel4;
	private JButton stopMin;
	private JButton stopMax;
	private JButton plus10M;
	private JButton plus1H;
	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public boolean finish() {
		saveActionPerformed(null);

		wizard.setFinished(true);

		return true;
	}

	@Override
	public boolean next() {
		saveActionPerformed(null);

		Date dt = startTimeChooser.getDate();

		wizard.setStartTime(dt);

		dt = endTimeChooser.getDate();
		wizard.setEndTime(dt);
		GuiUtil.showMessage("FIXME: Analysis Selection Panel disabled");
//		JPanel panel = new AnalysisSelectionPanel(wizard, wizard.getStudy());
//		wizard.pushPage(panel);

		return true;
	}

	@Override
	public void refresh() {
		wizard.enableNext(true);

		File parent;
		String lastDir = dir.getText();
		if (lastDir.length() == 0) {
			lastDir = PrefUtil.getUserPref(AppSetup.getSimulatorFile(), null);
		}
		if (lastDir != null) {
			parent = new File(lastDir);
		}

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

}
