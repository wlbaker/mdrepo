/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.devwizard;

import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.LinkedList;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTree;
import javax.swing.text.Position.Bias;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpStudy;
import lombok.Getter;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.studywiz.AnalysisSelectionPanel;
import idea.studywiz.StudySelectionPanel;

// import static WizDeviceID.*;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SetupWizard extends JPanel implements SetupWizardInterface {

	public static int HARDWARE_FLAG = 0x10;
	public static int ANALYSIS_FLAG = 0x20;
	public static int REVIEW_FLAG = 0x40;
	public static int STUDYSELECTION_FLAG = 0x80;
	// public static int NO_DEVICES = 0x07;
	public static int DATACOLLECTION_FLAGS = 0x00ff;
	public static int RESOURCES_FLAG = 0x0100;
	public static int ANNOTATION_FLAG = 0x0200;
	public static int PORTS_FLAG = 0x0800;

	private CardLayout card;

	private RpStudy study;
	private RpDevice dev;

	LinkedList<Component> stack = new LinkedList<Component>();
	// private int opt_flags;
	@Getter
	private boolean finished;

	public SetupWizard() {
		initComponents();

		// this.opt_flags = opt_flags;

		card = (CardLayout) filler.getLayout();

		pushPage(new SiteSetupPanel(this));

		root = new DefaultMutableTreeNode();
		//buildWizardNavigationTree(root);
		
		tree.setSelectionInterval(0, 0);

	}
	
	public DefaultMutableTreeNode addPage( DefaultMutableTreeNode parent, String name ) {
		return addPage( parent, name, null );
	}
	
	public DefaultMutableTreeNode addPage( DefaultMutableTreeNode parent, String name, Class<? extends WizardPanelInterface> clz ) {
		if( parent == null ) {
			parent = root;
		}
		DefaultMutableTreeNode node = new DefaultMutableTreeNode( name );
		node.setUserObject( clz );
		return node;
	}

//	protected void buildWizardNavigationTree(DefaultMutableTreeNode root) {
//
//		DefaultMutableTreeNode site = new DefaultMutableTreeNode("Site Identification");
//		root.add(site);
//
//		if ((opt_flags &STUDYSELECTION_FLAG) != 0) {
//			DefaultMutableTreeNode studySelection = new DefaultMutableTreeNode("Study Selection", true);
//			studySelection.add(new DefaultMutableTreeNode("Study Link"));
//			studySelection.add(new DefaultMutableTreeNode("Study Definition"));
//			root.add(studySelection);
//		}
//
//		if ((opt_flags & HARDWARE_FLAG) != 0) {
//			DefaultMutableTreeNode hardwareSetup = new DefaultMutableTreeNode("Hardware Setup", true);
//			// hardwareSetup.add(new DefaultMutableTreeNode("Edit Hardware"));
//			hardwareSetup.add(new DefaultMutableTreeNode("Device Selection"));
//			hardwareSetup.add(new DefaultMutableTreeNode("Signal Selection"));
//			root.add(hardwareSetup);
//		}
//
//		if ((opt_flags & ANALYSIS_FLAG) != 0) {
//			DefaultMutableTreeNode analysisSetup = new DefaultMutableTreeNode("Analysis Setup");
//			root.add(analysisSetup);
//		}
//
//		if ((opt_flags & REVIEW_FLAG) != 0) {
//			DefaultMutableTreeNode review = new DefaultMutableTreeNode("Review");
//			root.add(review);
//		}
//		if ((opt_flags & RESOURCES_FLAG) != 0) {
//			DefaultMutableTreeNode review = new DefaultMutableTreeNode("Resources");
//			root.add(review);
//		}
//		if ((opt_flags & ANNOTATION_FLAG) != 0) {
//			DefaultMutableTreeNode review = new DefaultMutableTreeNode("Annotations");
//			root.add(review);
//		}
//	}

	protected void expandAll() {
		for (int i = 0; i < tree.getRowCount(); i++) {
			tree.expandRow(i);
		}
	}

	protected JPanel getFiller() {
		return filler;
	}

	protected void nextActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.next();

				if (!ok)
					return;
				
				DefaultMutableTreeNode node = nextNode( );
				if( node != null ) {
					Class<WizardPanelInterface> clazz = (Class<WizardPanelInterface>) node.getUserObject();
					pushPage(node.toString(), clazz);
				}
				break;
			}
		}
	}

	private DefaultMutableTreeNode nextNode() {
		TreePath path = tree.getSelectionPath();
		Object comp = path.getLastPathComponent();
		DefaultMutableTreeNode node = (DefaultMutableTreeNode) comp;
		TreeNode next_node = null;
		while( next_node == null && node != null ) {
			DefaultMutableTreeNode parent = (DefaultMutableTreeNode) node.getParent();
			next_node = parent.getChildAfter( node );
			if( next_node == null ) {
				node = parent;				
			}
		}
		
		
		return node;
	}

	protected void finishActionPerformed(ActionEvent e) {
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

	protected void previousActionPerformed(ActionEvent e) {

		enableNext(true); // if NEXT is not desired, must be handled in refresh
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.previous();
				break;
			}
		}

		popPage();
		refresh();
	}

	protected void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
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
		CellConstraints cc = new CellConstraints();

		// ======== this ========
		setLayout(new FormLayout("[250dlu,default]:grow", "fill:default:grow, 2*($lgap, default)"));

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("80dlu, $lcgap, default:grow", "fill:default:grow"));

			// ======== scrollPane1 ========
			{

				// ---- tree ----
				tree.setBackground(null);
				tree.setRootVisible(false);
				tree.setEnabled(false);
				scrollPane1.setViewportView(tree);
			}
			panel2.add(scrollPane1, cc.xy(1, 1));

			// ======== filler ========
			{
				filler.setLayout(new CardLayout());
			}
			panel2.add(filler, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 1));
		add(separator1, cc.xy(1, 3));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default:grow, 6*($lcgap, default), $ugap, default", "default"));

			// ---- previous ----
			previous.setText("< Previous");
			previous.setEnabled(false);
			previous.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					previousActionPerformed(e);
				}
			});
			panel1.add(previous, cc.xy(9, 1));

			// ---- next ----
			next.setText("Next >");
			next.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					nextActionPerformed(e);
				}
			});
			panel1.add(next, cc.xy(11, 1));

			// ---- finish ----
			finish.setText("Finish");
			finish.setEnabled(false);
			finish.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					finishActionPerformed(e);
				}
			});
			panel1.add(finish, cc.xy(13, 1));

			// ---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel1.add(cancel, cc.xy(15, 1));
		}
		add(panel1, cc.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
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
	private DefaultMutableTreeNode root;

	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void pushPage(JPanel panel) {
		try {
			String tag = panel.getName();

			filler.add(panel, tag);
			card.show(filler, tag);
			stack.addFirst(panel);

			TreePath path = tree.getNextMatch(tag, 0, Bias.Forward);
			tree.setSelectionPath(path);

			previous.setEnabled(true);
		} catch (Exception e) {
			e.printStackTrace();
			GuiUtil.showError("Error setting page/panel.", e);
		}

	}
	
	public Component getPage( String name ) {
		if( name == null ) {
			name = stack.getFirst().getName();
		}
		
		for( Component page : stack ) {
			if( page.getName().equals(name)) {
				return page;
			}
		}
		
		return null;
	}

	public JTree getTree() {
		return tree;
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

	public RpStudy getStudy() {
		return study;
	}

	public void setStudy(RpStudy study) {
		this.study = study;
	}

	public void pushPage(String name, Class<?> clazz) {
		try {
			_pushPage( name, clazz);
		} catch (Exception e) {
			GuiUtil.showError("Could not add wizard page: ", e);
		}
	}

	public void _pushPage(String name, Class<?> clazz) throws SecurityException, NoSuchMethodException,
			IllegalArgumentException, InstantiationException, IllegalAccessException, InvocationTargetException {

		Constructor<?> mid = clazz.getConstructor(WizardMasterInterface.class);
		Object[] args = new Object[] { this};
		// args[0] = null;
		JPanel panel = (JPanel) mid.newInstance(args);
		panel.setName(name);

		pushPage(panel);
	}

	public void setDevice(RpDevice dev) {
		this.dev = dev;
	}

	public RpDevice getDevice() {
		return dev;
	}

	@Override
	public void setFinished(boolean b) {
		finished = b;
	}

}
