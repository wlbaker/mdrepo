/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.tsoffline.openwiz;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.io.File;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.LinkedList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTree;
import javax.swing.text.Position.Bias;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.persistence.ArchiveMetaData;
import idea.persistence.PiDatastreamImporter;
import idea.persistence.PiSubjectImporter;
import idea.persistmanager.PiImporterUtil;
import idea.schema.rp.ObjectFactory;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;
import idea.studywiz.StudyErrorPanel;
import idea.studywiz.StudySelectionPanel;
import idea.ts.TsoSession;
import idea.tsoffline.AppFrame;
import idea.tsoffline.TsSignalTreeSelectionPanel;
import idea.tsoffline.explorer.InfoAndRangeSelection;
import idea.tsoffline.importwiz.ImportFileSelectionPanel;
import idea.tsoffline.importwiz.ImportSFTPSelectionPanel;
import idea.tsoffline.importwiz.STPDetailPanel;
import idea.tsoffline.wiz.MethodSelectionPanel;
import idea.tsoffline.wiz.SubjectSelectionPanel;

// import static WizDeviceID.*;

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class OpenStudyWizard extends JPanel implements WizardMasterInterface {

	private static final String METHOD_SELECTION = "Data Source";
	private static final String STUDY_SELECTION = "Study Selection";
	// private static final String STUDY_INFO = "Study Info";
	private static final String SUBJECT_SELECTION = "Subject Selection";
	private static final String OPEN_ERROR = "Open Error";
	private static final String FILE_SELECTION = "File Selection";
	private static final String SFTP_SELECTION = "Remote Selection";
	private static final String DETAIL_SELECTION = "Detail";
	private static final String STP_DETAIL_PAGE = "STP Detail";
	private static final String SIGNALS_SELECTION = "Signal Selection";

	private CardLayout card;

	private boolean finished = false;

	LinkedList<String> stack = new LinkedList<String>();
	private StudySelectionPanel studySelection;
	// private DefaultStudyHeaderPanel studyInfo;
	private SubjectSelectionPanel subjectSelection;
	private MethodSelectionPanel methodSelection;
	private ImportFileSelectionPanel fileSelection;
	private ImportSFTPSelectionPanel remoteSelection;
	private STPDetailPanel stpDetailPanel;
	private RpSubject subjectb;
	private RpStudy studyb;
	private InfoAndRangeSelection detailPanel;
	private TsSignalTreeSelectionPanel signalsPanel;
	private PiDatastreamImporter[] devs;
	private PiSubjectImporter importer;
	private String sessionDir;
	private TsoSession session;

	public OpenStudyWizard() {
		initComponents();
		card = (CardLayout) filler.getLayout();

		enableNext(false);
		enableFinish(false);
		enablePrevious(false);

		safeAdd(methodSelection = new MethodSelectionPanel(this), METHOD_SELECTION);
		safeAdd(studySelection = new StudySelectionPanel(this, true, false, false), STUDY_SELECTION);
		// safeAdd(studyInfo = new DefaultStudyHeaderPanel(this), STUDY_INFO);
		safeAdd(subjectSelection = new SubjectSelectionPanel(this), SUBJECT_SELECTION);
		safeAdd(fileSelection = new ImportFileSelectionPanel(this), FILE_SELECTION);
		safeAdd(remoteSelection = new ImportSFTPSelectionPanel(this), SFTP_SELECTION);
		safeAdd(stpDetailPanel = new STPDetailPanel(this), STP_DETAIL_PAGE);
		safeAdd(detailPanel = new InfoAndRangeSelection(this), DETAIL_SELECTION );
		safeAdd(signalsPanel = new TsSignalTreeSelectionPanel( this ), SIGNALS_SELECTION);

		JPanel page;
		page = new StudyErrorPanel(
				"<html>No available studies.<br><br>Create a local study or retrieve a collaboration study with <i>Setup</i>.</html>");
		safeAdd(page, OPEN_ERROR);

		buildWizardNavigationTree();
		tree.setSelectionInterval(0, 0);

		stack.addFirst(METHOD_SELECTION);
		setCurrentPanel(METHOD_SELECTION);
		
		message.setText("");
	}

	private void safeAdd(JPanel p, String tag) {
		try {
			p.setName(tag);
			filler.add(p, tag);
		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(null, "Internal Error: " + e.getMessage());
		}
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode method = new DefaultMutableTreeNode(METHOD_SELECTION);
		DefaultMutableTreeNode studySelection = new DefaultMutableTreeNode(STUDY_SELECTION);
		// DefaultMutableTreeNode studyInfo = new
		// DefaultMutableTreeNode(STUDY_INFO);
		DefaultMutableTreeNode subjectSelection = new DefaultMutableTreeNode(SUBJECT_SELECTION);
		DefaultMutableTreeNode fileSelection = new DefaultMutableTreeNode(FILE_SELECTION);
		DefaultMutableTreeNode remoteSelection = new DefaultMutableTreeNode(SFTP_SELECTION);
		DefaultMutableTreeNode detailsNode = new DefaultMutableTreeNode( DETAIL_SELECTION );
		DefaultMutableTreeNode signalsNode = new DefaultMutableTreeNode( SIGNALS_SELECTION);

		root.add(method);
		root.add(studySelection);
		// root.add(studyInfo);
		root.add(subjectSelection);
		root.add(fileSelection);
		root.add(remoteSelection);
		root.add(detailsNode);
		root.add(signalsNode);

		tree.setModel(new DefaultTreeModel(root));
		expandAll();
	}

	private void expandAll() {
		for (int i = 0; i < tree.getRowCount(); i++) {
			tree.expandRow(i);
		}
	}

	private void nextActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				try {
					_next(ri);
				} catch (Exception e1) {
					GuiUtil.showError("Could not advance to next item.", e1);
				}

				break;
			}
		}
	}

	private void _next(WizardPanelInterface ri) throws Exception {
		message.setText("");
		
		boolean ok = ri.next();
		if (!ok) {
			return;
		}

		String nextPage = null;

		String curr = stack.getFirst();
		if (curr.equals(METHOD_SELECTION)) {
			if (methodSelection.isSignalFromFile()) {
				enableNext(false);
				enableFinish(false);  // until a file is selected...

				nextPage = FILE_SELECTION;
			} else if (methodSelection.isSignalFromRemote()) {
				enableNext(false);
				enableFinish(false);  // until a file is selected...

				nextPage = SFTP_SELECTION;
			} else {
				RepositoryInterface local = RepositoryFactory.getLocalRepository();
				List<RpStudy> studies = null;

				try {
					studies = local.getStudyList(null);
				} catch (Exception e) {
					GuiUtil.showError("Error loading studies.", e);
				}

				if (studies == null || studies.size() == 0) {
					nextPage = OPEN_ERROR;
				} else {
					nextPage = STUDY_SELECTION;
				}
			}
		} else if (curr.equals(STUDY_SELECTION)) {
			nextPage = SUBJECT_SELECTION;
			enableNext(false);
			enableFinish(true);

			subjectSelection.setStudy(getStudy());
		} else if (curr.equals(FILE_SELECTION)) {
			File f = fileSelection.getSelectedFile();
			String fileName = f.getPath();
			
			int dot_pos = fileName.lastIndexOf('.');
			String extension = fileName.substring(dot_pos + 1);
			if (extension != null && extension.toLowerCase().equals("stp")) {
				nextPage = STP_DETAIL_PAGE;
				stpDetailPanel.setFile( f );
				// FIXME: must seb subject before arriving at DETAIL screen
			} else if (extension != null && extension.toLowerCase().equals("spad")) {
					nextPage = DETAIL_SELECTION;
					stpDetailPanel.setFile( f );
					detailPanel.refresh();

					// FIXME: must seb subject before arriving at DETAIL screen
			} else {
				if( importer != null) {
					importer.disconnect();
				}
				importer = PiImporterUtil.getImporterFromFile(f);
				if( importer == null ) {
					message.setText("Could not import file: " + f);
					return;
				}
				importer.connect();
				
				sessionDir = f.getParent();
				
				System.out.println("set importer");
				detailPanel.setImporter(importer);
				//signalsPanel.setImporter(importer);
				subjectb = importer.getSubjectInfo();
				subjectb.setBaseFileName( f.getName() );
				
				studyb = new RpStudy();
				studyb.setTitle(f.getPath());
				studyb.setPi(subjectb.getOperator());
				studyb.setRepositoryLink(f.getParent());
				studyb.setRepositoryId(f.getPath());
				
				
				ArchiveMetaData meta = importer.getMetaData();
				// importer.getDatastreamImporter(name, sid)
				devs = importer.getDevices();
				//importer.disconnect();
				detailPanel.setSubjectAndTime( subjectb, meta.getStartTime(), meta.getStopTime());
				nextPage = DETAIL_SELECTION;
			}
			// not used...this path falls under finish
		} else if (curr.equals(SFTP_SELECTION)) {
			File f = remoteSelection.getSelectedFile();
			// not used...this path falls under finish
		} else if (curr.equals(STP_DETAIL_PAGE)) {
			// subject.;
			signalsPanel.setSignalsInfo( devs );
			nextPage = SIGNALS_SELECTION;
		} else if (curr.equals(DETAIL_SELECTION)) {
			// subject.;
			signalsPanel.setSignalsInfo( devs );
			nextPage = SIGNALS_SELECTION;
		} else if (curr.equals(SUBJECT_SELECTION)) {
			// nextPage = SUBJECT_SELECTION;
			// enableNext(false);
			// enableFinish(true);
			// subjectSelection.setStudy(getStudy());
		}

		if( nextPage == null && finish.isEnabled() ) {
			finishActionPerformed(null);
		} else {
			stack.addFirst(nextPage);
			setCurrentPanel(nextPage);
		}

		// ********* 1

		// ********* 2

	}

	private void setCurrentPanel(String nextPage) {
		card.show(filler, nextPage);

		TreePath path = tree.getNextMatch(nextPage, 0, Bias.Forward);
		tree.setSelectionPath(path);

		previous.setEnabled(stack.size() > 1);
		refresh();

	}

	private void finishActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.finish();

				if (ok) {
					String curr = stack.getFirst();
					File f = null;
					if (curr.equals(FILE_SELECTION)) {
						f = fileSelection.getSelectedFile();
						
						AppFrame frame = AppFrame.getInstance();
						sessionDir = f.getParentFile().toString();
						try {
							session = frame.getSessionInfoStep1(f);
						} catch (Exception e1) {
							// echo and ignore
							session = null;
							e1.printStackTrace();
						}
					} else if (curr.equals(SFTP_SELECTION)) {
						f = remoteSelection.getSelectedFile();
					} else if (curr.equals(DETAIL_SELECTION)) {
						f = remoteSelection.getSelectedFile();
					} else if (curr.equals(SIGNALS_SELECTION)) {
						session = signalsPanel.getSession();
						session.setDataStart( detailPanel.getStartDate() );
						session.setDataEnd( detailPanel.getEndDate() );
					}
					if( f != null ) {
						subjectb = new RpSubject();
						subjectb.setSubject("FIXME ImporterUtil.getSubjectFromFile(f);");
						subjectb.setBaseFileName(f.getName());
						studyb = new RpStudy();
						studyb.setTitle(f.getPath());
						studyb.setPi(subjectb.getOperator());
						studyb.setRepositoryLink(f.getParent());
						studyb.setRepositoryId(f.getPath());
					}
					
					setFinished(true);
					GuiUtil.closeDialog(this);
				}
				break;
			}
		}

	}

	private void previousActionPerformed(ActionEvent e) {
		popPage();
		refresh();
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
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
		message = new JLabel();
		previous = new JButton();
		next = new JButton();
		finish = new JButton();
		cancel = new JButton();

		//======== this ========
		setLayout(new FormLayout(
			"[250dlu,default]:grow",
			"fill:default:grow, 2*($lgap, default)"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"80dlu, $lcgap, default:grow",
				"fill:default:grow"));

			//======== scrollPane1 ========
			{

				//---- tree ----
				tree.setBackground(null);
				tree.setRootVisible(false);
				tree.setEnabled(false);
				tree.setModel(null);
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
				"default:grow, 3*($lcgap, default), 3*($lcgap, [50dlu,default]), $ugap, [50dlu,default]",
				"default"));

			//---- message ----
			message.setText("text");
			panel1.add(message, CC.xy(1, 1));

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

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel1.add(cancel, CC.xy(15, 1));
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
	private JLabel message;
	private JButton previous;
	private JButton next;
	private JButton finish;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void pushPage(JPanel panel) {
		try {
			String tag = panel.getName();

			filler.add(panel, tag);
			card.show(filler, tag);
			stack.addFirst(tag);

			TreeModel model = tree.getModel();
			if (model != null) {
				TreePath path = tree.getNextMatch(tag, 0, Bias.Forward);
				tree.setSelectionPath(path);

				previous.setEnabled(stack.size() > 1);
			}
		} catch (Exception e) {
			GuiUtil.showError("Internal Error", e);
		}

	}

	public void enableNext(boolean b) {
		next.setEnabled(b);
	}

	public void enablePrevious(boolean b) {
		previous.setEnabled(b);
	}

	public void enableFinish(boolean b) {
		finish.setEnabled(b);
	}

	private void popPage() {
		String prev_top = stack.removeFirst();
		// filler.remove(page);

		// ? card.removeLayoutComponent( page );

		String tag = stack.getFirst();
		TreePath path = tree.getNextMatch(tag, 0, Bias.Forward);
		tree.setSelectionPath(path);

		card.show(filler, tag);

		previous.setEnabled(stack.size() > 1);
	}

	public void popPageUntil(String key) {
		String top = stack.removeFirst();
		while (!key.equals(top)) {
			popPage();
			top = stack.getFirst();
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

	public RpStudy getStudy() {
		// if( isLocalFile) {
		// return fileSelection.getSelectedStudy();
		// }
		// return studySelection.getSelectedStudy();
		return studyb;
	}

	public RpSubject getSubject() {
		return subjectb;
		// return subjectSelection.getSelectedSubject();
	}

	public void pushSignalSelectionPage(Class<?> clazz) {
		try {
			_pushSignalSelectionPage(clazz);
		} catch (Exception e) {
			GuiUtil.showError("Signal Selection Panel: ", e);
		}
	}

	public void _pushSignalSelectionPage(Class<?> clazz) throws SecurityException, NoSuchMethodException,
			IllegalArgumentException, InstantiationException, IllegalAccessException, InvocationTargetException {
		ObjectFactory of = new ObjectFactory();
		RpDevice dev_conf = of.createRpDevice();

		Constructor<?> mid = clazz.getConstructor(RpDevice.class);
		Object[] args = new Object[] { dev_conf };
		// args[0] = null;
		JPanel panel = (JPanel) mid.newInstance(args);
		panel.setName("Signal Selection");

		pushPage(panel);
	}

	@Override
	public void setFinished(boolean finished) {
		this.finished = finished;
	}

	public boolean isFinished() {
		return finished;
	}

	public PiSubjectImporter getImporter() {
		return importer;
	}

	public TsoSession getSession() {
		return session;
	}

	public File getSessionDir() {
		return new File(sessionDir);
	}

}
