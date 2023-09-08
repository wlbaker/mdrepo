/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.tsoffline.vizwiz;

import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

import javax.swing.JButton;
import javax.swing.JComponent;
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

import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.analysis.AnalysisFactory;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.tsoffline.AppModel;
import idea.tsoffline.AppUtil;
import idea.tsoffline.ViewUtil;
import idea.tsoffline.canvas.TsControlPanel;
import idea.tsoffline.wiz.BeatInfoSetupPanel;
import idea.tsoffline.wiz.FeatureSelectionPanel;
import idea.tsoffline.wiz.PromoptDescriptionPanel;
import idea.tsoffline.wiz.SignalSelectionPanel;
import idea.tsoffline.wiz.TimeRangeSelectionPanel;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
@Slf4j
public class VizWizard extends JPanel implements WizardMasterInterface {

	private static int vizwiz_envidx = 0;
	private CardLayout card;

	private boolean finished = false;

	LinkedList<Component> stack = new LinkedList<Component>();

	private RpAnalysis anal;

	private TsControlPanel controller;

	private RpStudy study;
	private String rEnvName;
	
	class DialogRequest {
		List<String> args = new LinkedList<String>();
		
		public void addArg( String arg ) {
			args.add(arg);
		}

		public String getDialogName() {
			return args.get(0);
		}
	}

	ArrayList<DialogRequest> script_request;

	private TimeRangeSelectionPanel timeRange;
	private FeatureSelectionPanel featurePanel;

	public VizWizard(TsControlPanel controller, RpStudy study) {
		initComponents();

		this.controller = controller;
		this.study = study;

		card = (CardLayout) filler.getLayout();

		enableNext(false);
		enableFinish(false);
		enablePrevious(false);

		buildWizardNavigationTree();
		setInitialTimes();
		tree.setSelectionInterval(0, 0);

		JPanel page = new VizAnalysisSelection(this);
		page.setName("Analysis");
		pushPage(page);
		
		rEnvName = "vizre" + (vizwiz_envidx++);
	}

	private void setInitialTimes() {
		
		long ms = AppModel.getStartTime();
		AppUtil.setParam("CANVAS", "startDate", new Date(ms) );
	}

	private void buildWizardNavigationTree() {

		DefaultMutableTreeNode root = new DefaultMutableTreeNode();

		DefaultMutableTreeNode analysisSelection = new DefaultMutableTreeNode("Analysis");
		DefaultMutableTreeNode timeInfo = new DefaultMutableTreeNode("Time Range");
		DefaultMutableTreeNode signalInfo = new DefaultMutableTreeNode("Signals");
		DefaultMutableTreeNode scriptInfo = new DefaultMutableTreeNode("Detail");
		DefaultMutableTreeNode selectionInfo = new DefaultMutableTreeNode("Selection");
		DefaultMutableTreeNode analysisResults = new DefaultMutableTreeNode("Results");

		root.add(analysisSelection);
		root.add(timeInfo);
		root.add(signalInfo);
		root.add(scriptInfo);
		root.add(selectionInfo);
		root.add(analysisResults);

		tree.setModel(new DefaultTreeModel(root));
		expandAll(tree);
	}

	private static void expandAll(JTree tree) {
		for (int i = 0; i < tree.getRowCount(); i++) {
			tree.expandRow(i);
		}
	}

	private void nextActionPerformed(ActionEvent e) {
		for ( Component ac : filler.getComponents()) {
			JComponent c = (JComponent) ac;
			
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				if( c instanceof RAnalysisExecutorSetupPanel ) {
					((RAnalysisExecutorSetupPanel)c).setEnvironmentName( rEnvName );
				}
				boolean ok = ri.next();
				if (!ok) {
					break;
				}

				log.debug("Processing page={} of {}", getCurrentPage(), getPageCount());
				// System.out.println("script_request=" + script_request.size());

				String name = c.getName();
				if (name.equals("Analysis")) {
					VizAnalysisSelection p = (VizAnalysisSelection) c;
					anal = p.getAnalysis();

				
					StringStringMap map = anal.getParam();
					if (map != null) {
						String scriptPath = map.get("script");
						if (scriptPath != null) {
							String script = AppUtil.getScript(scriptPath);
							Reader r = new StringReader(script);
							BufferedReader script_reader = new BufferedReader(r);
							buildDialogArray( script_reader );
						}
					}
					
					JPanel panel = buildNextPanel(0);
					pushPage(panel);

				} else if (name.equals("Detail")) {

					List<? extends JPanel> plots = AppUtil.getPendingPlots();

					int additional_pages = 0;
					if (plots != null) {
						for (JPanel plot : plots) {
							String plot_name = "Results";
							if (additional_pages > 0) {
								plot_name += " [" + additional_pages + "]";
							}
							plot.setName(plot_name);
							pushPage(plot);
							additional_pages++;
						}
					}

					// FIXME: crude method to decide how to do
					// analysis...and I don't like this, but it works
					if (anal.getName().startsWith("ECG")) {
						log.error("FIXME: broken method to ");
						ViewUtil.doAnalysis(controller.getCanvas1(), AppModel.getStartTime(), AppModel.getModelAsStudy(), anal, Color.MAGENTA);
					}

					enableFinish(true);
					if (additional_pages == 0) {
						finishActionPerformed(null);
					}

				} else {

					Integer idx = (Integer)c.getClientProperty("panel_idx");
					if( getCurrentPage() < getPageCount() && idx != null) {
						JPanel panel = buildNextPanel(idx+1);
						pushPage(panel);
					} else if (getCurrentPage() == getPageCount()) {
						finishActionPerformed(null);
					}
				}

				break;

			}
		}
	}

	private void buildDialogArray(BufferedReader script_reader) {
		script_request = new ArrayList<DialogRequest>();
		
		while (script_reader != null) {
			try {
				String line;
				repeat: do {
					line = script_reader.readLine();
					if (line != null) {
						StringTokenizer tokenizer = new StringTokenizer(line);
						for (int i = 0; i < 3 && tokenizer.hasMoreTokens(); i++) {
							String token = tokenizer.nextToken();
							if (i == 0 && !token.startsWith("#")) {
								continue repeat;
							} else if (i == 1 && !token.equalsIgnoreCase("DIALOG")) {
								continue repeat;
							} else if (i == 2) {
								DialogRequest req = new DialogRequest();
								do { 
									req.addArg( token );
									token = (tokenizer.hasMoreTokens()) ? tokenizer.nextToken() : null;
								} while(token != null );
								script_request.add(req);
								break repeat;
							}
						}
					}
				} while (line != null);

				if (line == null) {
					script_reader.close();
				}
			} catch (IOException e) {
				try {
					script_reader.close();
					script_reader = null;
				} catch (Exception e1) {
					// ignore
				}
				script_reader = null;
			}
		}

		
	}

	private JPanel buildNextPanel(Integer idx) {

		DialogRequest dialog_request = null;
		if( idx != null ) {
			if( script_request != null && idx < script_request.size() ) {
				dialog_request = script_request.get(idx);
			} else {
				idx = null;
			}
		}
		
		String request = null;
		if( dialog_request != null ) {
			request = dialog_request.getDialogName();
		}
		JPanel p = null;
		if (request == null) {
			JPanel setup = AnalysisFactory.buildSetupPanel(this, null, study, anal);

			if (setup == null) {
				GuiUtil.showMessage("Error building setup panel for analysis: " + anal.getName());
			} else {
				setup.setName("Detail");
			}
			p = setup;
		} else if ("TIMERANGE".equalsIgnoreCase(request)) {
			timeRange = new TimeRangeSelectionPanel(this, controller.getCanvas1());
			timeRange.setName("Time Range");
			timeRange.setTitle("Analysis Time Range");
			timeRange.enableRealtime(true);
			p = timeRange;
		} else if ("FEATURE".equalsIgnoreCase(request)) {
			featurePanel = new FeatureSelectionPanel(this, dialog_request.args);
			featurePanel.setName("Feature");
			// featurePanel.setTitle("Features Time Range");
			p = featurePanel;
		} else if ("BEATINFO".equalsIgnoreCase(request)) {
			BeatInfoSetupPanel ss = new BeatInfoSetupPanel(this);
			ss.setName("Beat Info");
			p = ss;
		} else if ("SIGNAL".equalsIgnoreCase(request)) {
			SignalSelectionPanel ss = new SignalSelectionPanel(this, controller.getCanvas1(), dialog_request.args);
			ss.setName("Signal Selection");
			p = ss;
		} else if ("PROMPT".equalsIgnoreCase(request)) {
			PromoptDescriptionPanel ss = new PromoptDescriptionPanel(this, dialog_request.args );
			ss.setName("Prompt");
			p = ss;
		} else {
			GuiUtil.showMessage("Could not find requested dialog: " + script_request);
		}
		
		if( request != null ) {
			p.putClientProperty("panel_idx", idx);
		}

		return p;
	}

	private void finishActionPerformed(ActionEvent e) {
		for (int i = filler.getComponentCount() - 1; i >= 0; i--) {
			Component c = filler.getComponent(i);
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.finish();
				if (ok) {
					setFinished(true);
				}
			}
			filler.remove(i); // remove the plots...and everything...to allow
								// plots to be reused inside another frame
		}
		GuiUtil.closeDialog(this);
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
				tree.setModel(null);
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

		if (page instanceof WizardPanelInterface) {
			WizardPanelInterface wpi = (WizardPanelInterface) page;
			wpi.previous();
		}
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

	public void setFinished(boolean b) {
		this.finished = b;
	}

	public boolean isFinished() {
		return finished;
	}

	public RpAnalysis getSelectedAnalysis() {
		return anal;
	}

	public TsControlPanel getController() {
		return controller;
	}

	/*
	 * Candidates for WizardMaster someday
	 */
	public int getPageCount() {
		return filler.getComponentCount();
	}

	public int getCurrentPage() {
		return stack.size() - 1;
	}

	public boolean isRealtime() {
		boolean rt = false;
		if( timeRange != null ) {
			rt = timeRange.isRealtime();
		}
		return rt;
	}

	public String getREnvName() {
		return rEnvName;
	}

}
