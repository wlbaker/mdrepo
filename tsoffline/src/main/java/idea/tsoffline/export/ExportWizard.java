/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.tsoffline.export;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.prefs.BackingStoreException;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTree;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import javax.swing.text.Position.Bias;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.intf.StreamProducer;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiCompositeImporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import lombok.Setter;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.ts.TsoSession;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TsOfflineSetup;
import idea.tsoffline.canvas.PLayerSignalProducer;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.wiz.TimeRangeSelectionPanel;

// import static WizDeviceID.*;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class ExportWizard extends JPanel implements WizardMasterInterface, ActionListener, PropertyChangeListener {

	public static final String SOURCE_NAME = "Export-Name";

	private CardLayout card;
	private static ExportWizard instance;

	LinkedList<Component> stack = new LinkedList<Component>();
	HashMap<String, StreamProducer> cachedOutputDrivers;

	private int progressActual;
	private Timer swingTimer;

	boolean exportWaveTimestamp = false;
	private boolean doFileSelection;

	private ExportFileSelectionPanel fileSelectionPanel;
	private ExportRubalMethod expRubalPanel;
	private TimeRangeSelectionPanel timeRangePanel;
	private ExportDestinationPanel destPanel;
	private ExportSubjectPanel subjectPanel;
	// private AnalysisSelectionPanel expAnalysisPanel;

	private PiSubjectImporter importer;
	private RpStudy study;

	Thread export_th = null;
	private boolean stop_export;

	private TsPSwingCanvas canvas;
	private ExportComplete expComplete;
	private RpSubject header;
	Date clipStart, clipEnd;

	@Setter
	private File audioInputFile;
	private File audioOutputFile;

	private String xlsName;

	/**
	 * 
	 * @param doFileSelection
	 * @param isDialog
	 *            Enable the Cancel button if true. Give a status message and
	 *            trigger System.exit() when complete if false.
	 * 
	 */
	public ExportWizard(TsPSwingCanvas canvas, boolean doFileSelection) {
		initComponents();
		card = (CardLayout) filler.getLayout();
		instance = this; // must be set before any sub-panels added

		this.doFileSelection = doFileSelection;

		study = new RpStudy();

		fileSelectionPanel = new ExportFileSelectionPanel(this);
		subjectPanel = new ExportSubjectPanel(this);

		timeRangePanel = new TimeRangeSelectionPanel(this, canvas);
		timeRangePanel.setName("Time Range");
		timeRangePanel.setTitle("Export Time Range");

		destPanel = new ExportDestinationPanel(this);
		destPanel.setName("Destination");

		this.canvas = canvas;

		if (canvas == null) {
			// expAnalysisPanel = new AnalysisSelectionPanel(this, study);

			timeRangePanel.setName("Time Range");
			// expAnalysisPanel.setName("Analysis");
		} else {
			expRubalPanel = new ExportRubalMethod();
			expRubalPanel.setName("Signals");
		}

		expComplete = new ExportComplete(this);

		addListeners();

		if (doFileSelection) {
			pushPage(fileSelectionPanel);
			next.setEnabled(false);
		} else {
			pushPage(timeRangePanel);
			next.setEnabled(true);
		}

		buildWizardNavigationTree();
		tree.setSelectionInterval(0, 0);

		progressMessage.setText("Progress: ");

		progressMessage.setEnabled(false); // improves L&F colors when export is
											// disabled.
		progressBar1.setEnabled(false); // improves L&F colors when export is
										// disabled
	}

	private void addListeners() {
		PropertyChangeListener l = new PropertyChangeListener() {

			@Override
			public void propertyChange(PropertyChangeEvent arg0) {
				String prop = arg0.getPropertyName();
				if (prop.equals("export.next")) {
					Boolean val = (Boolean) arg0.getNewValue();
					enableNext(val);
				} else if (prop.equals("export.finish")) {
					Boolean val = (Boolean) arg0.getNewValue();
					enableFinish(val);
				} else if (prop.equals(JFileChooser.SELECTED_FILE_CHANGED_PROPERTY)) {
					enableNext(true);
				} else {
					log.error("unknown: {}", arg0);
				}
			}

		};

		fileSelectionPanel.getFilechooser().addPropertyChangeListener(l);
		//if (expAnalysisPanel != null) {
		//	expAnalysisPanel.addPropertyChangeListener("EXPORTABLE", this);
		//}

	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		String pname = evt.getPropertyName();
		if ("EXPORTABLE".equals(pname)) {
			// Boolean val = (Boolean) evt.getNewValue();
			// enableExport(val);
		} else if (ExportUtil.PNAME_CURRENT_DEVICE.equals(pname)) {
			String val = (String) evt.getNewValue();
			progressMessage.setText(val);
		} else if (ExportUtil.PNAME_MAX_PROGRESS.equals(pname)) {
			Integer val = (Integer) evt.getNewValue();
			if (val == null || val < 0) {
				progressBar1.setIndeterminate(true);
			} else {
				progressBar1.setIndeterminate(false);
				progressBar1.setMinimum(0);
				progressBar1.setMaximum(val);
			}
		} else if (ExportUtil.PNAME_CURRENT_PROGRESS.equals(pname)) {
			Integer val = (Integer) evt.getNewValue();
			progressActual = val; // progress bar will be updated with swing
									// timer thread
			if (val == -1) {
				progressBar1.setVisible(false);
				progressMessage.setText("Writing file...");
			}
			if (val == -2) {
				progressBar1.setVisible(false);
				progressMessage.setText("Complete");

				Runnable r = new Runnable() {

					@Override
					public void run() {
						pushPage(expComplete);
						expComplete.refresh();
					}
				};
				SwingUtilities.invokeLater(r);
			}
		}

	}

	public void setImporter(PiSubjectImporter importer) {
		this.importer = importer;
	}

	public static ExportWizard getInstance() {
		return instance;
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		if (doFileSelection) {
			DefaultMutableTreeNode node = new DefaultMutableTreeNode("File Selection");
			root.add(node);
		}
		DefaultMutableTreeNode source_tn = new DefaultMutableTreeNode("Time Range");
		DefaultMutableTreeNode dest_tn = new DefaultMutableTreeNode("Destination");
		DefaultMutableTreeNode signals = new DefaultMutableTreeNode("Signals", true);
		signals.add(new DefaultMutableTreeNode("Vitals"));
		signals.add(new DefaultMutableTreeNode("Sensors/Waveforms"));
		DefaultMutableTreeNode analysis_tn = new DefaultMutableTreeNode("Analysis", true);

		root.add(source_tn);
		root.add(dest_tn);
		root.add(signals);
		root.add(analysis_tn);

		tree.setModel(new DefaultTreeModel(root));
		expandAll(tree);
	}

	private void expandAll(JTree tree2) {
		for (int i = 0; i < tree.getRowCount(); i++) {
			tree.expandRow(i);
		}
	}

	private void nextActionPerformed(ActionEvent e) {
		try {
			_nextActionPerformed(e);
		} catch (IOException e1) {
			GuiUtil.showError("Error creating export:", e1);
		}
	}

	private void _nextActionPerformed(ActionEvent e) throws IOException {

		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.next();
				if (ok == false) {
					return;
				}

				if (c instanceof ExportDestinationPanel) {

					//if (expAnalysisPanel != null) {
					//	expAnalysisPanel.setFileOutput(destPanel.isFileOutput());
					//}
					//outputFile = 
					
					pushPage(expRubalPanel);

				} else if (c instanceof ExportRubalMethod) {
					// pushPage(fileSelectionPanel);
					exportActionPerformed(null);
				} else if (c instanceof ExportFileSelectionPanel) {
					File[] ff = fileSelectionPanel.getSelectedFiles();
					if (ff.length == 1) {
						File f = ff[0];
						importer = PiImporterUtil.getImporterFromFile(f, PiImporterUtil.HDF5_FLAG);
						putClientProperty(SOURCE_NAME, f.getPath());
					} else {
						PiCompositeImporter ci = new PiCompositeImporter(ff[0], PiImporterUtil.HDF5_FLAG);
						importer = ci;
						for (int i = 1; i < ff.length; i++) {
							ci.addFile(ff[i]);
						}
						putClientProperty(SOURCE_NAME, "[Multiple Subjects]");
					}
					importer.connect();
					try {
						TsOfflineSetup.setArchiveFile(ff[0].getPath());
					} catch (BackingStoreException e1) {
						// print error, but otherwise ignore
						e1.printStackTrace();
					}

					if (importer instanceof PiCompositeImporter) {
						PiCompositeImporter ci = (PiCompositeImporter) importer;
						pushPage(subjectPanel);
						subjectPanel.refresh(ci);
					} else {
						destPanel.hasAudio(audioInputFile != null);
						pushPage(destPanel);
						destPanel.refresh(importer);
					}
				} else if (c instanceof ExportSubjectPanel) {
					destPanel.hasAudio(audioInputFile != null);
					pushPage(destPanel);
					destPanel.refresh(importer);

					try {
						TsOfflineSetup.setConnectionURI(destPanel.getJDBCConnectionURI());
					} catch (BackingStoreException e1) {
						// print error, but otherwise ignore
						e1.printStackTrace();
					}
				} else if (c instanceof TimeRangeSelectionPanel) {
					destPanel.hasAudio(audioInputFile != null);
					pushPage(destPanel);

				}

				break;
			}
		}

	}

	private void finishActionPerformed(ActionEvent e) {
		if (export_th != null) {
			int op = GuiUtil.showConfirmDialog("Cancel current export?", "MedDAQ Exporter",
					JOptionPane.YES_NO_CANCEL_OPTION);
			if (op != JOptionPane.YES_OPTION) {
				return;
			}
			stop_export = true;
			try {
				export_th.wait(1000);
			} catch (InterruptedException e1) {
				// log and continue
				log.warn("could not stop export thread", e1);
			}
		}
		GuiUtil.closeDialog(this);
	}

	private void previousActionPerformed(ActionEvent e) {
		popPage();
		refresh();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel2 = new JPanel();
		scrollPane1 = new JScrollPane();
		tree = new JTree();
		filler = new JPanel();
		separator1 = new JSeparator();
		panel1 = new JPanel();
		progressMessage = new JLabel();
		progressBar1 = new JProgressBar();
		previous = new JButton();
		next = new JButton();
		finish = new JButton();

		//======== this ========
		setLayout(new FormLayout(
			"[250dlu,default]:grow, default",
			"fill:default:grow, 2*($lgap, default)"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"80dlu, $lcgap, [default,840dlu]:grow",
				"fill:default:grow"));

			//======== scrollPane1 ========
			{

				//---- tree ----
				tree.setBackground(null);
				tree.setRootVisible(false);
				tree.setEnabled(false);
				scrollPane1.setViewportView(tree);
			}
			panel2.add(scrollPane1, CC.xy(1, 1));

			//======== filler ========
			{
				filler.setLayout(new CardLayout());
			}
			panel2.add(filler, CC.xy(3, 1));
		}
		add(panel2, CC.xy(1, 1));
		add(separator1, CC.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default:grow, $lcgap, default, $lcgap, 12dlu, 3*($lcgap, default)",
				"default"));

			//---- progressMessage ----
			progressMessage.setText("file");
			panel1.add(progressMessage, CC.xy(1, 1));
			panel1.add(progressBar1, CC.xy(3, 1));

			//---- previous ----
			previous.setText("< Previous");
			previous.setEnabled(false);
			previous.addActionListener(e -> previousActionPerformed(e));
			panel1.add(previous, CC.xy(9, 1));

			//---- next ----
			next.setText("Next >");
			next.addActionListener(e -> nextActionPerformed(e));
			panel1.add(next, CC.xy(11, 1));

			//---- finish ----
			finish.setText("Finish");
			finish.setEnabled(false);
			finish.addActionListener(e -> finishActionPerformed(e));
			panel1.add(finish, CC.xy(13, 1));
		}
		add(panel1, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel2;
	private JScrollPane scrollPane1;
	private JTree tree;
	private JPanel filler;
	private JSeparator separator1;
	private JPanel panel1;
	private JLabel progressMessage;
	private JProgressBar progressBar1;
	private JButton previous;
	private JButton next;
	private JButton finish;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void pushPage(JPanel panel) {
		try {
			String tag = panel.getName();

			filler.add(panel, tag);
			card.show(filler, tag);
			stack.addFirst(panel);

			TreePath path = tree.getNextMatch(tag, 0, Bias.Forward);
			tree.setSelectionPath(path);

			previous.setEnabled(stack.size() > 1);
		} catch (Exception e) {
			e.printStackTrace();
			GuiUtil.showError("Internal Error", e);
		}

	}

	public void enableNext(boolean b) {
		next.setEnabled(b);
	}

	public void enableFinish(boolean b) {
		finish.setEnabled(b);
	}

	private void popPage() {
		Component page = stack.removeFirst();
		filler.remove(page);

		// ? card.removeLayoutComponent( page );

		page = stack.getFirst();
		String tag = page.getName();
		TreePath path = tree.getNextMatch(tag, 0, Bias.Forward);
		tree.setSelectionPath(path);

		card.show(filler, page.getName());

		previous.setEnabled(stack.size() > 1);
	}

	public void popPageUntil(String key) {
		Component page = stack.getFirst();
		while (!key.equals(page.getName())) {
			System.out.println("POPPING PAGE: " + page.getName());
			popPage();
			page = stack.getFirst();
		}
		refresh();
	}

	public void refresh() {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.refresh();
				break;
			}
		}
	}

	private void exportActionPerformed(ActionEvent e) {

		if (!checkFiles()) {
			return;
		}

		ExportUtil exp = new ExportUtil();
		exp.addPropertyChangeListener(this);
		stop_export = false;

		if (importer instanceof PiCompositeImporter) {
			PiCompositeImporter ci = (PiCompositeImporter) importer;
			ci.addSubjectChangeListener(new PropertyChangeListener() {

				@Override
				public void propertyChange(PropertyChangeEvent evt) {
					exp.subjectChange((String) evt.getNewValue());

				}
			});

		}

		PLayerSignalProducer importer;
		importer = new PLayerSignalProducer(canvas);

		Map<String, LinkedList<HPSplitableLayer>> hm_sigs = getSignals();
		

		exp.setImporter(importer);
		GuiUtil.showMessage("FIXME: exp.setHeader(header);");

		exp.setDataStartMs(canvas.getStartTime());
		exp.setClipStart(clipStart = timeRangePanel.getClipStart());
		exp.setClipEnd(clipEnd = timeRangePanel.getClipEnd());

		DateFormat df = new SimpleDateFormat("yyyyMMdd_HHmmss");

		System.setProperty("SUBJECT", "NONE");
//		if (header != null) {
//			if (header.getMedicalId() != null) {
//				System.setProperty("SUBJECT", header.getMedicalId());
//			}
//			if (header.getSubject() != null && header.getSubject().trim().length() > 0) {
//				System.setProperty("SUBJECT", header.getSubject());
//			}
//		}
		System.setProperty("START_TIME", df.format(clipStart));
		System.setProperty("STOP_TIME", df.format(clipEnd));
		String spec = getExportSpec();
		xlsName = spec;
		exp.setOutput(getExportMethod(), spec);
		exp.setSignals(hm_sigs);
		exp.setMergeOption(destPanel.getMergeOption());

		audioOutputFile = null;
		if (audioInputFile != null && destPanel.isFileOutput() && destPanel.hasAudio()) {
			String waveSpec = spec;
			int suffixPos = waveSpec.lastIndexOf(".");
			if (suffixPos > 0) {
				waveSpec = waveSpec.substring(0, suffixPos);
			}
			waveSpec += ".wav";
			audioOutputFile = new File(waveSpec);
		}
		exp.setAudioInputFile(audioInputFile);
		exp.setAudioOutputFile(audioOutputFile);

		progressBar1.setVisible(true);
		progressBar1.setEnabled(true);
		progressMessage.setText("Progress:");

		previous.setEnabled(false);
		next.setEnabled(false);
		finish.setEnabled(false);

		exp.init(); // this should be done in the GUI thread...sets the progress
					// bar info

		Runnable r = new Runnable() {

			@Override
			public void run() {

				startSwingTimer();

				try {

					log.error("FIXME: Exporter is hard coded for XLS/RUBAL OUTPUT");
					exp.run();
					progressMessage.setText("Complete.");

				} catch (OutOfMemoryError e) {
					GuiUtil.showMessage("Out of memory.");
				} catch (Exception e) {
					GuiUtil.showError("Export", e);
				} finally {
					// progressBar1.setValue(0);
					// progressBar1.setIndeterminate(false);
					stopSwingTimer();
				}

				previous.setEnabled(true);
				next.setEnabled(true);
				finish.setEnabled(true);

				// if (isDialog == true) {
				// GuiUtil.showMessage("Export complete.");
				// System.exit(0);
				// }

				export_th = null;
			}

		};

		export_th = new Thread(r, "Export Worker Thread");
		export_th.start();
	}

	private boolean checkFiles() {
		String method = getExportMethod();
		if ("JDBC".equals(method)) {
			return true; // actually...might need more checking.
		}

		return true;
	}

	private boolean checkExportDir(String dirName) {

		File dirFile = new File(dirName);

		if (dirFile.exists()) {
			int ok = GuiUtil.showConfirmDialog("Directory exists.  Do you wish to overwrite this directory?",
					"File Exists", JOptionPane.YES_NO_OPTION);
			if (ok != JOptionPane.OK_OPTION) {
				return false;
			}
		}

		dirFile.mkdirs();

		return true;
	}

	private boolean checkExportFile(String fileName) {

		File file = new File(fileName);
		if (file.isDirectory()) {
			GuiUtil.showMessage("The export location is a directory.  Please specify a file name.");
			return false;
		}
		String path = file.getPath().toUpperCase();
		if (path.endsWith("XLS") || path.endsWith("XLSX")) {
			// this is accepted
		} else {
			GuiUtil.showMessage("The export file name must end in XLS or XLSX.");
			return false;
		}
		if (file.exists()) {
			int ok = GuiUtil.showConfirmDialog("Export file exists.  Do you wish to overwrite this file?",
					"File Exists", JOptionPane.YES_NO_OPTION);
			if (ok != JOptionPane.OK_OPTION) {
				return false;
			}
		}

		return true;
	}

	private String getExportMethod() {
		String method = null;
		if (destPanel.isJDBCOutput()) {
			method = "JDBC";
		} else if (destPanel.isDreOutput()) {
				method = "DRE";
		} else if (destPanel.isHdf5Output()) {
			method = "HDF5";
		} else if (destPanel.isFileOutput()) {
			Component top = stack.getFirst();
			method = "XLS";
		}
		return method;
	}

	public String getExportSpec() {
		String spec = null;
		if (destPanel.isJDBCOutput()) {
			spec = destPanel.getJDBCConnectionURI();			
		} else if (destPanel.isDreOutput()) {
			spec = destPanel.getDreOutputFile();
		} else if (destPanel.isHdf5Output()) {
			spec = destPanel.getHdf5OutputFile();
		} else if (destPanel.isFileOutput()) {
			spec = destPanel.getFilePath();
			Component top = stack.getFirst();
			//if (top == expAnalysisPanel) {
			//	spec = expAnalysisPanel.getOutputFile();
			//} else if (top == expRubalPanel) {
			//	// handled by default value above
			//}
		}

		spec = spec.replace("${SUBJECT}", System.getProperty("SUBJECT"));
		spec = spec.replace("${START_TIME}", System.getProperty("START_TIME"));
		spec = spec.replace("${STOP_TIME}", System.getProperty("STOP_TIME"));

		return spec;
	}

	private Map<String, LinkedList<HPSplitableLayer>> getSignals() {
		Map<String, LinkedList<HPSplitableLayer>> spec = null;
		Component top = stack.getFirst();
		if (top == expRubalPanel) {
			spec = expRubalPanel.getSignals();
		//} else if (top == expAnalysisPanel) {
		//	spec = null;
		}
		return spec;
	}

	protected void startSwingTimer() {
		swingTimer = new Timer(1000, this);
		swingTimer.start();

	}

	protected void stopSwingTimer() {
		swingTimer.stop();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		progressBar1.setValue(progressActual);
		progressBar1.repaint();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see idea.gui.WizardMasterInterface#setFinished(boolean)
	 */
	@Override
	public void setFinished(boolean b) {
		// unused

	}

	@Override
	public void enablePrevious(boolean b) {
		// unused
		previous.setEnabled(b);
	}

	public void setSession(TsoSession session) {
		// this.header = subject;
		setAudioInputFile(session.getAudioFile());
	}

	public File getAudioFile() {
		return audioOutputFile;
	}

	public void exportDAT() {
		GuiUtil.showMessage("FIXME: no header");
		DreHelper h = new DreHelper(header, new Date(canvas.getStartTime()), clipStart, clipEnd );

		h.exportDAT(expComplete, xlsName, getExportSpec(), audioInputFile, destPanel.isFileOutput(), destPanel.hasAudio());
	}

	public void setAudioInputFile(String audioFileName) {
		audioInputFile = ( audioFileName == null ) ?  null : new File(audioFileName);
	}

}
