/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.tsoffline.derivsigwiz;


import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Constructor;
import java.util.LinkedList;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTree;
import javax.swing.text.Position.Bias;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.model.DerivedParamsBase;


/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class DerivedSigWizard extends JPanel {

	private CardLayout card;

	private static DerivedSigWizard instance;
	private boolean finished = false;

	LinkedList<Component> stack = new LinkedList<Component>();

	private HPSplitableLayer sourceSignal;


	public DerivedSigWizard(HPSplitableLayer sourceSignal) {
		initComponents();
		card = (CardLayout) filler.getLayout();
		instance = this; // must be set before any sub-panels added
		this.sourceSignal = sourceSignal;

		enableNext(false);
		enableFinish(false);
		enablePrevious(false);

		buildWizardNavigationTree();
		tree.setSelectionInterval(0, 0);

		DerivedSignalSelection panel = new DerivedSignalSelection();
		panel.setName("Derived Signal");
//		JPanel page = new SourceSignalSelection( sourceSignal );
//		page.setName( "Source Signal");
		pushPage(panel);
	}

	public static DerivedSigWizard getInstance() {
		return instance;
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode studyInfo = new DefaultMutableTreeNode("Source Signal");
		DefaultMutableTreeNode analysisSelection = new DefaultMutableTreeNode("Derived Signal");

//		root.add(studyInfo);
		root.add(analysisSelection);

		tree.setModel(new DefaultTreeModel(root));
		expandAll(tree);
	}

	private static void expandAll(JTree tree) {
		for (int i = 0; i < tree.getRowCount(); i++) {
			tree.expandRow(i);
		}
	}

	private void nextActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.next();
				break;
			}
		}
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
		CellConstraints cc = new CellConstraints();

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
			panel2.add(scrollPane1, cc.xy(1, 1));

			//======== filler ========
			{
				filler.setLayout(new CardLayout());
			}
			panel2.add(filler, cc.xy(3, 1));
		}
		add(panel2, cc.xy(1, 1));
		add(separator1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, 6*($lcgap, default), $ugap, default",
				"default"));

			//---- previous ----
			previous.setText("< Previous");
			previous.setEnabled(false);
			previous.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					previousActionPerformed(e);
				}
			});
			panel1.add(previous, cc.xy(9, 1));

			//---- next ----
			next.setText("Next >");
			next.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					nextActionPerformed(e);
				}
			});
			panel1.add(next, cc.xy(11, 1));

			//---- finish ----
			finish.setText("Finish");
			finish.setEnabled(false);
			finish.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					finishActionPerformed(e);
				}
			});
			panel1.add(finish, cc.xy(13, 1));

			//---- cancel ----
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

	private String derivedSignalProcess;

	private ParameterProvider parameterProvider;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void pushPage(String pageName ) {
		
		if( "derivedSignalSelection".equals(pageName)) {
		
		} else if ("paramPanel".equals(pageName)) {
			setFinished( true );
			GuiUtil.closeDialog( this );
		} else if (pageName.startsWith("RECUR")){
			RecursionPlotSetupPanel detail = new RecursionPlotSetupPanel();;
			derivedSignalProcess = "Recursion Plot";
			pushPage( detail );
			parameterProvider = detail;
		} else if (pageName.startsWith("RRI")){
			RRISegementationDetail detail = new RRISegementationDetail();
			DerivedDetailPanel panel = new DerivedDetailPanel(sourceSignal, detail);;
			panel.setSignal1Label( "ECG:");
			panel.setSignal2Label( null );
			derivedSignalProcess = "RRI";
			pushPage( panel );
			parameterProvider = panel;
		} else if (pageName.startsWith("IBI")){
			IBISegementationDetail detail = new IBISegementationDetail();
			DerivedDetailPanel panel = new DerivedDetailPanel(sourceSignal, detail);
			panel.setSourceSignal( sourceSignal );
			panel.setSignal1Label( "Flow:");
			panel.setSignal2Label( null );
			derivedSignalProcess = "IBI";
			
			pushPage( panel );
			parameterProvider = panel;
			
		} else if (pageName.startsWith("SE")){
			SEParamPanel detail = new SEParamPanel( pageName, "Sample Entropy Parameters -- " + pageName );
			JPanel panel = new DerivedDetailPanel(sourceSignal, detail);;
			derivedSignalProcess = pageName;
			pushPage( panel );
			parameterProvider = detail;
		} else if (pageName.startsWith("QSE")){
			SEParamPanel detail = new SEParamPanel("QSE", "Quadratic Sample Entropy Parameters");;
			JPanel panel = new DerivedDetailPanel(sourceSignal, detail);;
			derivedSignalProcess = "QSE";
			pushPage( panel );
			parameterProvider = detail;
		} else if (pageName.startsWith("MSE")){
			SEParamPanel detail = new SEParamPanel("MSE", "Multiscale Entropy Parameters");;
			JPanel panel = new DerivedDetailPanel(sourceSignal, detail);;
			derivedSignalProcess = "MSE";
			pushPage( panel );
			parameterProvider = detail;
		} else if (pageName.startsWith("LYA")){
			LyaParamPanel detail = new LyaParamPanel();;
			JPanel panel = new DerivedDetailPanel(sourceSignal, detail);;
			derivedSignalProcess = "LYA";
			pushPage( panel );
			parameterProvider = detail;
		} else if (pageName.startsWith("HIST")){
			// FIXME 
			JPanel detail = new JPanel();
			derivedSignalProcess = "HIST";
			JPanel panel = new DerivedDetailPanel(sourceSignal, detail);;
			pushPage( panel );
			// FIXME parameterProvider = detail;
		} else {
			GuiUtil.showMessage("FIXME: analysis method not implemented: " + pageName);
		}

	}
	
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
			// POPPING PAGE
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

	public void setFinished( boolean b ) {
		this.finished = b;
	}
	
	public boolean isFinished() {
		return finished;
	}

	public void setSourceSignal(HPSplitableLayer sourceSignal) {
		this.sourceSignal = sourceSignal;
	}
	
	public HPSplitableLayer getSourceSignal( ) {
		return sourceSignal;
	}

	public String getDerivedSignalProcess() {
		return derivedSignalProcess;
	}

	public Object getDerivedParameters() {
		DerivedParamsBase params = parameterProvider.getParameters();
		
		return params;
	}


//	public void setDerivedSignal(String derivedSignal ) {
//		this.derivedSignal = derivedSignal;
//		
//	}
//	public String getDerivedSignal( ) {
//		return derivedSignal;
//	}

}
