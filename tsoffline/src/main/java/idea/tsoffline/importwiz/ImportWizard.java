/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.tsoffline.importwiz;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.io.File;
import java.lang.reflect.Constructor;
import java.util.LinkedList;

import javax.swing.JButton;
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

import idea.schema.rp.RpSubject;
import idea.GuiUtil;
import idea.devwizard.WizIDEAPanel;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.gui.wizard.DefaultStudyHeaderPanel;
import idea.studywiz.StudySelectionPanel;
import idea.tsoffline.TsSignalTreeSelectionPanel;
import idea.tsoffline.explorer.InfoAndRangeSelection;

@SuppressWarnings("serial")
public class ImportWizard extends JPanel implements WizardMasterInterface {

	private static final String IMPORT_SOURCE = "Import Source";
	private static final String STUDY_INFO = "Study/Device Selection";
	//private static final String DEVICE_CONNECTION = "Source Detail";
	private static final String SIGNALS_SELECTION = "Signal Selection";
	private static final String TIME_RANGE = "Time Range";
	private static final String STUDY_HEADER = "Study Info";
	private static final String STUDY_SELECTION = "Study Selection";


	private CardLayout card;

	private File importFile;
	private RpSubject header;
	private static ImportWizard instance;
	private boolean finished = false;

	LinkedList<Component> stack = new LinkedList<Component>();
	private SourceSelectionPanel importSource;
	private StudySelectionPanel studySelection;
	private DefaultStudyHeaderPanel studyInfo;
	//private DeviceConnectionPanel deviceConnection;
	private WizIDEAPanel ideaPanel;
	private TimeRangePanel timerangePanel;
	private ImporterFilechooser fileChooser;
	
	private TsSignalTreeSelectionPanel signalSelection;
	private InfoAndRangeSelection headerPanel;

	public ImportWizard() {
		initComponents();
		card = (CardLayout) filler.getLayout();
		instance = this; // must be set before any sub-panels added

		enableNext(false);
		enableFinish(false);
		enablePrevious(false);

		safeAdd(importSource = new SourceSelectionPanel(this), IMPORT_SOURCE);
		safeAdd(studySelection = new StudySelectionPanel(this, true, false, false), STUDY_SELECTION);
		safeAdd(studyInfo = new DefaultStudyHeaderPanel(this), STUDY_INFO);
		//safeAdd(deviceConnection = new DeviceConnectionPanel(this), DEVICE_CONNECTION);
		safeAdd(ideaPanel = new WizIDEAPanel(this,null), SourceSelectionPanel.DEVICE_SELECTION );
		safeAdd(timerangePanel = new TimeRangePanel(this), TIME_RANGE );
		safeAdd(fileChooser = new ImporterFilechooser(), SourceSelectionPanel.FILE_SELECTION );
		safeAdd(headerPanel = new InfoAndRangeSelection(this), STUDY_HEADER );
		safeAdd(signalSelection = new TsSignalTreeSelectionPanel( this ), SIGNALS_SELECTION);


		buildWizardNavigationTree();
		tree.setSelectionInterval(0, 0);

		pushPage(importSource);
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
	
	public static ImportWizard getInstance() {
		return instance;
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode source = new DefaultMutableTreeNode(IMPORT_SOURCE);
		DefaultMutableTreeNode studyInfo = new DefaultMutableTreeNode(STUDY_INFO);
		//DefaultMutableTreeNode fileSelection = new DefaultMutableTreeNode(DEVICE_CONNECTION);
		DefaultMutableTreeNode signalSelection = new DefaultMutableTreeNode(SIGNALS_SELECTION);
		DefaultMutableTreeNode hardwareSetup = new DefaultMutableTreeNode(TIME_RANGE);
		// DefaultMutableTreeNode ideaDevice = new DefaultMutableTreeNode(SourceSelectionPanel.DEVICE_SELECTION );

		root.add(source);
		root.add(studyInfo);
		//root.add(fileSelection);
		root.add(signalSelection);
		root.add(hardwareSetup);

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
				_next(ri);

				break;
			}
		}
	}

	private void _next(WizardPanelInterface ri) {
		ri.next();
//		
		if ( ri == importSource ) {
			String nextPage = importSource.getNextPage();
			if( SourceSelectionPanel.EVENTS_SELECTION.equals(nextPage) ) {
				pushPage( ideaPanel);
			} else if( SourceSelectionPanel.DEVICE_SELECTION.equals(nextPage) ) {
				pushPage( ideaPanel);
			} else if( SourceSelectionPanel.FILE_SELECTION.equals(nextPage) ) {
				pushPage( fileChooser);
			}
		} else if ( ri == fileChooser ) {
			pushPage( timerangePanel) ; // headerPanel );
		} else if ( ri == headerPanel ) {
			pushPage( signalSelection );
		} else if (ri == ideaPanel) {
			pushPage( timerangePanel );
		} else if (ri == timerangePanel ){
			// walked past the end
			finishActionPerformed(null);
		}
//
		//********* 1 

		//********* 2 

	}

	private void finishActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.finish();
				if (ok) {
					setFinished(true);
					GuiUtil.closeDialog(this);
				}
				break;
			}
		}
	}

	private static WizardPanelInterface buildPanel(Class<?> clazz) {
		WizardPanelInterface panel = null;

		try {
			Constructor<?> mid = clazz.getConstructor(); // DeviceConfiguration.class
			// );
			Object[] args = new Object[0];
			// args[0] = null;
			panel = (WizardPanelInterface) mid.newInstance(args);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return panel;
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
	private JButton previous;
	private JButton next;
	private JButton finish;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void pushPage(JPanel panel) {
		try {
			String tag = panel.getName();

			filler.add(panel, tag);
			card.show(filler, tag);
			stack.addFirst(panel);

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

	@Override
	public void enableNext(boolean b) {
		next.setEnabled(b);
	}

	@Override
	public void enablePrevious(boolean b) {
		previous.setEnabled(b);
	}

	@Override
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


	@Override
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

	public File getImportFile() {
		return importFile;
	}

	public void setImportFile(File importFile) {
		this.importFile = importFile;
	}

	public RpSubject getSubjectInfo() {
		return header;
	}

	public void setStudyHeader(RpSubject header) {
		this.header = header;
	}

	public boolean isFinished() {
		return finished;
	}

	@Override
	public void setFinished(boolean b) {
		this.finished = b;
	}


}
