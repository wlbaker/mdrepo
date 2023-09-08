/*
 * Created by JFormDesigner on Fri Jul 31 18:15:33 CDT 2015
 */

package idea.tsoffline.disp_manager;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.text.DecimalFormat;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.swing.DefaultComboBoxModel;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;

import org.piccolo2d.activities.PActivity;
import org.piccolo2d.activities.PInterpolatingActivity;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.tsoffline.AppUtil;
import idea.tsoffline.JobManager;
import idea.tsoffline.canvas.TsControlPanel;
import idea.tsoffline.canvas.TsPSwingCanvas;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class ReplayControlPanel extends JPanel {
	Clip clip;
	private TsControlPanel form;
	PActivity play_realtimeActivity;
	private int milliWidth;

	private Icon expandIcon;
	private Icon updownIcon;
	private Icon dunnoIcon;
	protected boolean ignore_scale_action;
	private boolean hasSound;

	class PAudioActivity extends PActivity {

		PAudioActivity( int dt) {
			super(-1);
		}
		
		@Override
		protected void activityStarted() {
			super.activityStarted();

			long micro = form.getViewEndTimeMs() * 1000;

			// behavior for negative values is undefined....
			if (micro < 0) {
				micro = 0;
			}
			clip.setMicrosecondPosition(micro);
			clip.loop(0);
			form.activityStarted(this);
		}

		@Override
		protected void activityStep(long elapsedTime) {
			super.activityStep(elapsedTime);

			long milli_pos = clip.getMicrosecondPosition() / 1000;
			long milli_max = clip.getMicrosecondLength() / 1000;
			if (milli_pos >= milli_max) {
				play_realtimeActivity.terminate(PActivity.TERMINATE_AND_FINISH);
				form.removeActivity(this);
				clip.stop();
			}

			form.setViewDomainInMillis(milli_pos - milliWidth, milli_pos);
			form.activityStepped(this);
		}

		@Override
		protected void activityFinished() {
			super.activityFinished();
			clip.stop();
			form.activityFinished(this);
		}

	};

	class PQuietActivity extends PInterpolatingActivity {

		private long startMillis;

		PQuietActivity( int dt) {
			super(-1);
		}
		
		@Override
		protected void activityStarted() {
			super.activityStarted();

			startMillis = form.getViewEndTimeMs();
			form.activityStarted(this);
		}

		@Override
		protected void activityStep(long elapsedTime) {
//			super.activityStep(elapsedTime);

			long milli_pos = startMillis + elapsedTime;
//			if (milli_pos >= milli_max) {
//				play_realtimeActivity.terminate(PActivity.TERMINATE_AND_FINISH);
//			}

			form.setViewDomainInMillis(milli_pos - milliWidth, milli_pos);
			form.activityStepped(this);
		}
		
		@Override
		protected void activityFinished() {
			super.activityFinished();
			form.activityFinished(this);
		}

	};
	
	
	public ReplayControlPanel(TsControlPanel form) {
		initComponents();

		this.form = form;

		resume.setEnabled(true); // everything starts off running
		rewind.setEnabled(true);
		pause.setEnabled(false);

		progressBar.setVisible(false);
		cancel.setVisible(false);

		message.setText("");

		expandIcon = new ImageIcon(getClass().getResource("/fonta/resources/expand.png"));
		updownIcon = new ImageIcon(getClass().getResource("/fonta/resources/arrows-v.png"));
		dunnoIcon = new ImageIcon(getClass().getResource("/fonta/resources/bolt.png"));


		TsPSwingCanvas canv = form.getCanvas1();
		canv.addKeyListener(new KeyListener() {

			@Override
			public void keyPressed(KeyEvent e) {
				processKeyPressed(e);
			}

			@Override
			public void keyReleased(KeyEvent e) {
				processKeyPressed(e);
			}

			@Override
			public void keyTyped(KeyEvent e) {
			}
		});

		JobManager.prepareProgressBar(message, progressBar, cancel);
		canv.addPropertyChangeListener(TsPSwingCanvas.RULER_PROPERTY, new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent evt) {
				DecimalFormat df2 = new DecimalFormat("#,##0.00");
				
				ignore_scale_action = true;
				Double secs = (Double) evt.getNewValue();
				DefaultComboBoxModel<String> model = (DefaultComboBoxModel<String>) scale.getModel();
				model.removeElementAt(0);

				model.insertElementAt( df2.format(secs) + " sec", 0);
				scale.setSelectedIndex(0);
				ignore_scale_action = false;
			}

		});
		
	}

	protected void processKeyPressed(KeyEvent e) {
		int keyCode = e.getKeyCode();
		if (keyCode == KeyEvent.VK_SHIFT || keyCode == KeyEvent.VK_CONTROL) {
			// fall through
		} else {
			return;
		}

		if (e.isControlDown() && e.isShiftDown()) {
			message.setIcon(dunnoIcon);
		} else if (e.isControlDown()) {
			message.setIcon(expandIcon);
		} else if (e.isShiftDown()) {
			message.setIcon(updownIcon);
		} else {
			message.setIcon(null);
		}

		putClientProperty("VK_CONTROL", e.isShiftDown());
	}

	private void resumeActionPerformed(ActionEvent e) {

		recalcMilliWidth();
		if (play_realtimeActivity != null) {
			play_realtimeActivity.terminate(PActivity.TERMINATE_AND_FINISH);
			form.removeActivity(play_realtimeActivity);
		}
		
		if( hasSound ) {
			play_realtimeActivity = new PAudioActivity( -1 );
		} else {
			play_realtimeActivity = new PQuietActivity( -1 );
		}
		form.addActivity(play_realtimeActivity);

		resume.setEnabled(false);
		rewind.setEnabled(false);
		pause.setEnabled(true);
	}

	private void pauseActionPerformed(ActionEvent e) {
		if( play_realtimeActivity != null ) {
			// this only happens if the GUI is out of sync...somewhat of an error.
			// in this case, pause should not have been enabled
			play_realtimeActivity.terminate(PActivity.TERMINATE_AND_FINISH);
			form.removeActivity(play_realtimeActivity);
		}

		resume.setEnabled(true);
		rewind.setEnabled(true);
		pause.setEnabled(false);
	}

	private void rewindActionPerformed(ActionEvent e) {
		recalcMilliWidth();
		form.setViewDomainInMillis(-milliWidth + 1000, 1000);
	}

	private void scaleActionPerformed(ActionEvent e) {
		if( ignore_scale_action ) {
			return;
		}
		recalcMilliWidth();
		form.zoomToWidthInMillis(milliWidth);

		form.redraw();
	}
	
	private void recalcMilliWidth() {
		String item = (String) scale.getSelectedItem();
		milliWidth = AppUtil.asMilliseconds(item);
	}

	public void setAudioFile(File audioFile) {

		if (audioFile == null) {
			if (clip != null) {
				clip.close();
				clip = null;
			}
			enableButtons(false);
			return;
		}

		enableButtons(true);
		try {
			InputStream in = new FileInputStream(audioFile);
			byte[] header = new byte[71];
			in.read(header, 0, 71);
//			for( int i = 0; i < 71; i++ ) {
//				if( i % 16 == 0 ) {
//					System.out.println();
//				}
//				System.out.print(" " + header[i]);
//			}

			AudioFormat f = new AudioFormat(11025, 16, 1, true, true);
			// create an audiostream from the inputstream
			AudioInputStream ais = new AudioInputStream(in, f, -1); // was... 11026 * 300

			// play the audio clip with the audioplayer class
			// AudioPlayer.player.start(audioStream);

			clip = AudioSystem.getClip();
			clip.open(ais);

			hasSound = true;
		} catch (Exception e) {
			GuiUtil.showError("Could not open audio source", e);
		}

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		message = new JLabel();
		progressBar = new JProgressBar();
		cancel = new JButton();
		label1 = new JLabel();
		scale = new JComboBox<>();
		rewind = new JButton();
		pause = new JButton();
		resume = new JButton();

		//======== this ========
		setBorder(null);
		setLayout(new FormLayout(
			"4dlu, [16dlu,default], $lcgap, default:grow, $lcgap, [50dlu,default], $lcgap, default, $lcgap, [50dlu,default], 3*($lcgap, default), 4dlu",
			"fill:default, 2dlu"));

		//---- message ----
		message.setText("FUNC");
		add(message, CC.xy(2, 1));
		add(progressBar, CC.xy(4, 1));

		//---- cancel ----
		cancel.setText("Cancel");
		add(cancel, CC.xy(6, 1));

		//---- label1 ----
		label1.setText("Scale:");
		add(label1, CC.xy(8, 1));

		//---- scale ----
		scale.setModel(new DefaultComboBoxModel<>(new String[] {
			"?",
			"3 sec",
			"6 sec",
			"15 sec",
			"30 sec",
			"60 sec",
			"10 min",
			"30 min",
			"1 hr",
			"4 hr"
		}));
		scale.addActionListener(e -> scaleActionPerformed(e));
		add(scale, CC.xy(10, 1));

		//---- rewind ----
		rewind.setIcon(new ImageIcon(getClass().getResource("/idea/image/rewind-hot-icon.png")));
		rewind.addActionListener(e -> rewindActionPerformed(e));
		add(rewind, CC.xy(12, 1));

		//---- pause ----
		pause.setIcon(new ImageIcon(getClass().getResource("/idea/image/Pause-Normal-icon.png")));
		pause.setToolTipText("Pause");
		pause.setMaximumSize(new Dimension(23, 23));
		pause.setMinimumSize(new Dimension(23, 23));
		pause.setPreferredSize(new Dimension(23, 23));
		pause.addActionListener(e -> pauseActionPerformed(e));
		add(pause, CC.xy(14, 1));

		//---- resume ----
		resume.setIcon(new ImageIcon(getClass().getResource("/idea/image/Play-1-Hot-icon.png")));
		resume.setToolTipText("Resume");
		resume.setMaximumSize(new Dimension(23, 23));
		resume.setMinimumSize(new Dimension(23, 23));
		resume.setPreferredSize(new Dimension(23, 23));
		resume.addActionListener(e -> resumeActionPerformed(e));
		add(resume, CC.xy(16, 1));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JLabel message;
	private JProgressBar progressBar;
	private JButton cancel;
	private JLabel label1;
	private JComboBox<String> scale;
	private JButton rewind;
	private JButton pause;
	private JButton resume;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void setMessage(String txt) {
		message.setText(txt);
	}

	public void clear() {
		setAudioFile( null );
		enableButtons(false);
	}

	private void enableButtons(boolean b) {
		label1.setEnabled(b);
		scale.setEnabled( b);
		rewind.setEnabled(b);
		pause.setEnabled(b);
		resume.setEnabled(b);
	}

	public void enableQuietReplay() {
		hasSound = false;
		
		enableButtons(true);
	}

	public void disableReplay() {
		enableButtons(false);
	}

}
