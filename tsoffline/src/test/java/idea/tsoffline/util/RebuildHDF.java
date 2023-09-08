/*
 * Created by JFormDesigner on Wed Apr 11 11:45:23 CDT 2012
 */

package idea.tsoffline.util;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiHdf5Exporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.RpSubject;
import idea.GuiUtil;
import idea.PrefUtil;
import idea.tsoffline.TsOfflineSetup;

/**
 * @author User #2
 */
public class RebuildHDF extends JPanel implements PropertyChangeListener {
	PiSubjectImporter importer;
	PiHdf5Exporter exporter;
	private Exception import_exception;
	private int err;

	public RebuildHDF() {
		initComponents();

		// String s_src = PrefUtil.getUserPref("RebuildSRC", "y:\\A-12-004 Conscious sheep\\data\\147\\parts");
		// String s_dest = PrefUtil.getUserPref("RebuildDEST", "y:\\A-12-004 Conscious sheep\\data\\147\\full\\0000.h5");
		String s_src = PrefUtil.getUserPref("RebuildSRC", "y:\\A-12-004 Conscious sheep\\data\\137\\parts");
		String s_dest = PrefUtil.getUserPref("RebuildDEST", "y:\\A-12-004 Conscious sheep\\data\\137\\full\\0000.h5");
		src.setText(s_src);
		dest.setText(s_dest);
	}

	private void startActionPerformed(ActionEvent e) {
		setEnableAllControls(false);
		try {
			if (openFiles()) {

				startBackgroundTask();
			} else
				setEnableAllControls(true);
		} catch (IOException e1) {
			GuiUtil.showErrorInGuiThread("RebuildHDF", e1);
		}
	}

	private boolean openFiles() throws IOException {
		File fsrc = new File(src.getText().trim());
		File fdest = new File(dest.getText().trim());

		if (fsrc.exists() == false) {
			GuiUtil.showMessage("Source does not exist: " + src.getText());

			return false;
		}
		if (fdest.exists()) {
			int ok = GuiUtil.showConfirmDialog("Dest file already exists.  Delete?", "Dest File Exists",
					JOptionPane.YES_NO_CANCEL_OPTION);
			if (ok != JOptionPane.YES_OPTION) {
				return false;
			}
			fdest.delete();
		}

		PrefUtil.saveUserPref("RebuildSRC", fsrc.getCanonicalPath());
		PrefUtil.saveUserPref("RebuildDEST", fdest.getCanonicalPath());

		importer = PiImporterUtil.getImporterFromFile(fsrc);
		importer.connect();
		RpSubject header = importer.getSubjectInfo();
		exporter = new PiHdf5Exporter(header, fdest.getPath(), true);
		exporter.connect();

		return true;
	}

	private void startBackgroundTask() {
		ArchiveMetaData meta = null;
		try {
			meta = importer.getMetaData();
		} catch (IOException e) {
			e.printStackTrace();
		}

		Date startTime = meta.getStartTime();
		Date endTime = meta.getStopTime();
		if (startTime != null && endTime != null) {
			progressBar1.setMinimum(0);
			progressBar1.setMaximum(100);
		}

		RpSubject header = importer.getSubjectInfo();
		Date surgeryDate = header.getSurgeryDate();
		if (startTime != null && startTime.getTime() < surgeryDate.getTime())
			startTime = surgeryDate;

		class Rebuilder extends SwingWorker<Void, Void> {
			final long stTime, edTime;

			public Rebuilder(Date startTime, Date endTime) {
				if (startTime != null && endTime != null) {
					this.stTime = startTime.getTime();
					this.edTime = endTime.getTime();
				} else {
					this.stTime = 0;
					this.edTime = 0;
				}
			}

			@Override
			protected Void doInBackground() throws Exception {

				long percentProgress = 0;
				import_exception = null;
				try {
					PersistentItem block = importer.next();
					while (block != null) {
						StreamID sid = StreamID.fromCode(block.getStreamID() );
						exporter.streamEvent(0, block.getSource(), sid, block);

						if (edTime > stTime && block.getTime() > stTime)
							percentProgress = (long) (((double) (block.getTime() - stTime)) / (edTime - stTime) * 100);

						setProgress(Math.min((int) percentProgress, 100));

						block = importer.next();
					}
					exporter.disconnect();
					importer.disconnect();

				} catch (Exception ex) {
					import_exception = ex;
					ex.printStackTrace();
				}

				return null;
			}

			@Override
			public void done() {

				setEnableAllControls(true);
				if (import_exception != null) {
					GuiUtil.showError("Rebuild", import_exception);
				}
				if (err > 0) {
					GuiUtil.showMessage("Unrecognized blocks in export: " + err);
				}
			}
		}
		;

		Rebuilder worker = new Rebuilder(startTime, endTime);
		worker.addPropertyChangeListener(this);
		worker.execute();
		progressBar1.setValue(0);
	}

	private void browseSourceActionPerformed(ActionEvent e) {
		browseActionPerformed(e, "Source", src);
	}

	private void browseDestActionPerformed(ActionEvent e) {
		browseActionPerformed(e, "Destination", dest);
	}

	private void browseActionPerformed(ActionEvent e, final String title, final JTextField dir) {
		File parent = null;
		String lastDir = dir.getText();
		if (lastDir.length() == 0) {
			lastDir = PrefUtil.getUserPref(TsOfflineSetup.getExportDir(), null);
		}
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, title, this, parent, new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				File file = (File) e.getSource();
				dir.setText(file.getAbsolutePath());
			}
		});
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		label1 = new JLabel();
		src = new JTextField();
		browseSource = new JButton();
		label2 = new JLabel();
		dest = new JTextField();
		browseDest = new JButton();
		panel2 = new JPanel();
		progressBar1 = new JProgressBar();
		start = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:[80dlu,default]:grow, $rgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("right:[50dlu,default], $lcgap, [250dlu,default]:grow, $lcgap, default",
					"2*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Source:");
			panel1.add(label1, cc.xy(1, 1));
			panel1.add(src, cc.xy(3, 1));

			//---- browseSource ----
			browseSource.setText("Browse");
			browseSource.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					browseSourceActionPerformed(e);
				}
			});
			panel1.add(browseSource, cc.xy(5, 1));

			//---- label2 ----
			label2.setText("Destination:");
			panel1.add(label2, cc.xy(1, 3));
			panel1.add(dest, cc.xy(3, 3));

			//---- browseDest ----
			browseDest.setText("Browse");
			browseDest.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					browseDestActionPerformed(e);
				}
			});
			panel1.add(browseDest, cc.xy(5, 3));
		}
		add(panel1, cc.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout("default:grow, $lcgap, [50dlu,default]", "default"));
			panel2.add(progressBar1, cc.xy(1, 1));

			//---- start ----
			start.setText("Start");
			start.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					startActionPerformed(e);
				}
			});
			panel2.add(start, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JLabel label1;
	private JTextField src;
	private JButton browseSource;
	private JLabel label2;
	private JTextField dest;
	private JButton browseDest;
	private JPanel panel2;
	private JProgressBar progressBar1;
	private JButton start;

	// JFormDesigner - End of variables declaration  //GEN-END:variables

	public static void main(String[] args) throws InterruptedException, InvocationTargetException {

		for (int i = 0; i < args.length; i++) {

			if ("-log".equals(args[i])) {
				i++;
				String fileName = args[i];
				if (fileName.indexOf("{Date}") > 0) {
					DateFormat df = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss");
					Date now = new Date();
					String str = df.format(now);
					fileName = fileName.replaceAll("\\{Date\\}", str);
				}
				GuiUtil.redirectStdOutAndErr("RebuildHDF", fileName);
			}
		}

		try {
			System.loadLibrary("jhdf5");

			GuiUtil.initApplication("RebuildHDF", "0.0", args);
		} catch (UnsatisfiedLinkError e) {
			GuiUtil.showError("Link error", e);
		} catch (Throwable e) {
			GuiUtil.showError("Init app error", e);
		}

		SwingUtilities.invokeAndWait(new Runnable() {

			@Override
			public void run() {
				JPanel p = new RebuildHDF();

				JFrame f = new JFrame("Rebuild HDF");
				f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				f.add(p);
				f.pack();
				f.setVisible(true);

			}
		});
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		if (evt.getPropertyName() == "progress") {
			int progress = (Integer) evt.getNewValue();
			if (progress > 0 && progressBar1.isIndeterminate())
				progressBar1.setIndeterminate(false);
			progressBar1.setValue(progress);
			progressBar1.repaint();
		}
	}

	private void setEnableAllControls(boolean enabled) {
		start.setEnabled(enabled);
		src.setEnabled(enabled);
		dest.setEnabled(enabled);
		progressBar1.setIndeterminate(!enabled);
	}
}
