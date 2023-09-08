/*
 * Created by JFormDesigner on Fri Jul 31 18:15:33 CDT 2015
 */

package idea.display.editor;

import icuInterface.RpUtil;
import idea.model.DisplayConfig;
import idea.schema.rp.RpDisplay;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.text.DateFormat;
import java.util.Date;

import javax.swing.DefaultComboBoxModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;

import idea.display.gl.GLInstrumentDisplay;
import idea.meddaq.AppSetup;
import idea.repository.RepositoryFactory;
import idea.repository.io.LocalJAXBRepository;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
public class DisplayButtonBar extends JPanel implements PropertyChangeListener {
	private GLInstrumentDisplay form;

	public DisplayButtonBar(GLInstrumentDisplay form) {
		initComponents();

		this.form = form;
		form.addPropertyChangeListener(this);
		
		resume.setEnabled( false );  // everything starts off running
	}

	private void pauseActionPerformed(ActionEvent e) {
		if (form.isPaused()) {
			form.resume();
		} else {
			form.pause();
		}

		resume.setEnabled(form.isPaused());
		pause.setEnabled(!form.isPaused());
	}

	private void scaleActionPerformed(ActionEvent e) {
		System.out.println("scale action: " + e.getSource());
		JComboBox cbox = (JComboBox) e.getSource();
		String item = (String) cbox.getSelectedItem();
		String[] arr = item.split(" ");
		form.setWidthInMillis(1000 * Integer.parseInt(arr[0]));
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		String key = evt.getPropertyName();
		if (GLInstrumentDisplay.PROPERTY_FPS.equals(key)) {
			Integer fps = (Integer) evt.getNewValue();
			fpsLabel.setText("[fps=" + fps + "]");
		} else if (GLInstrumentDisplay.PROPERTY_TIME.equals(key)) {
			Date dt = (Date) evt.getNewValue();
			DateFormat df = DateFormat.getDateTimeInstance();
			fpsLabel.setText(df.format(dt));
		}
	}

	private void saveActionPerformed(ActionEvent e) {
		File dir = AppSetup.getLocalStudyDir();
		String formName = form.getName();
		formName += ".dsp";
		File displayFile = new File(dir, formName);

		DisplayConfig display = form.getDisplay();
		RpDisplay rp_disp = RpUtil.createDisplay( display );
		
		LocalJAXBRepository repo = RepositoryFactory.getLocalRepository();
		repo.createDisplay( displayFile, rp_disp );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY //GEN-BEGIN:initComponents
		fpsLabel = new JLabel();
		label1 = new JLabel();
		scale = new JComboBox<>();
		pause = new JButton();
		resume = new JButton();
		save = new JButton();

		// ======== this ========
		setLayout(new FormLayout("default:grow, $lcgap, default, $lcgap, [50dlu,default], 3*($lcgap, default)",
				"default"));

		// ---- fpsLabel ----
		fpsLabel.setText("[fps=?]");
		add(fpsLabel, CC.xy(1, 1));

		// ---- label1 ----
		label1.setText("Scale:");
		add(label1, CC.xy(3, 1));

		// ---- scale ----
		scale.setModel(new DefaultComboBoxModel<>(new String[] { "15 sec", "30 sec", "60 sec" }));
		scale.addActionListener(e -> scaleActionPerformed(e));
		add(scale, CC.xy(5, 1));

		// ---- pause ----
		pause.setIcon(new ImageIcon(getClass().getResource("/idea/image/Pause-Normal-icon.png")));
		pause.setToolTipText("Pause");
		pause.setMaximumSize(new Dimension(23, 23));
		pause.setMinimumSize(new Dimension(23, 23));
		pause.setPreferredSize(new Dimension(23, 23));
		pause.addActionListener(e -> pauseActionPerformed(e));
		add(pause, CC.xy(7, 1));

		// ---- resume ----
		resume.setIcon(new ImageIcon(getClass().getResource("/idea/image/Play-1-Hot-icon.png")));
		resume.setToolTipText("Resume");
		resume.setMaximumSize(new Dimension(23, 23));
		resume.setMinimumSize(new Dimension(23, 23));
		resume.setPreferredSize(new Dimension(23, 23));
		resume.addActionListener(e -> pauseActionPerformed(e));
		add(resume, CC.xy(9, 1));

		// ---- save ----
		save.setText("Save");
		save.setToolTipText("Save screen layout as default");
		save.addActionListener(e -> saveActionPerformed(e));
		add(save, CC.xy(11, 1));
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	private JLabel fpsLabel;
	private JLabel label1;
	private JComboBox<String> scale;
	private JButton pause;
	private JButton resume;
	private JButton save;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
