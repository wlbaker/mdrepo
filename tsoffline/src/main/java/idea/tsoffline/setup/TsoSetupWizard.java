package idea.tsoffline.setup;

import java.awt.Component;
import java.awt.event.ActionEvent;

import javax.swing.JPanel;
import javax.swing.tree.DefaultMutableTreeNode;

import uk.me.berndporr.api.FilterInterface;
import idea.devwizard.SetupWizard;
import idea.devwizard.SiteSetupPanel;
import idea.gui.WizardPanelInterface;
import idea.ts.TsFilter;
import idea.ts.TsoPrefs;

public class TsoSetupWizard extends SetupWizard {

	FilterSetupEvaluatePanel evaluator;
	private TsoPrefs prefs;
	
	public TsoSetupWizard(TsoPrefs prefs) {
		super();
		
		addPage(null, "Site Identification");

//		DefaultMutableTreeNode studySelection = addPage(null, "Study Selection");
//		addPage(studySelection, "Study Link");
//		addPage(studySelection, "Study Definition");

		addPage( null, "Annotations");
		
		DefaultMutableTreeNode filters = addPage(null, "Filter Selection");
		addPage( filters, "Design");
		addPage( filters, "Evaluation");
		
//		JTree tree = super.getTree();
//		tree.setModel(new DefaultTreeModel(root));
//		expandAll();
		this.prefs = prefs;
	}

	protected void nextActionPerformed(ActionEvent e) {

		JPanel filler = getFiller();

		for (Component c : filler.getComponents()) {
			if( !c.isVisible() ) {
				continue;
			}
			if ( c instanceof SiteSetupPanel) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.next();

				if (!ok)
					return;

				FilterSelectionPanel panel = new FilterSelectionPanel(this);
				panel.setPrefs( prefs );
				pushPage(panel);
				enableNext(false);
				enableFinish(true);
				return;

			} else if (c instanceof FilterSetupDesignPanel) {
				
				FilterSetupDesignPanel designer = (FilterSetupDesignPanel)c;
				
				// WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = designer.next();

				if (!ok)
					return;

				if( evaluator == null ) {
					evaluator = new FilterSetupEvaluatePanel(this);
					evaluator.setName( "Evaluation");
				}
				
				evaluator.setDesignPanel( designer.getDesignPanel() );
				pushPage(evaluator);
				enableNext(true);
				enableFinish(true);
				return;
			} else if (c instanceof FilterSetupEvaluatePanel) {
				
				FilterSetupDesignPanel designer = (FilterSetupDesignPanel)getPage("Design");
				FilterInterface filter = designer.getFilter();
				TsFilter savable = null;
				
				for( TsFilter f : prefs.getFilters() ) {
					String filterName = filter.getName();
					if( filterName.equals( f.getName()) ) {
						savable = f;
						break;
					}
				}
				
				if( savable == null ) {
					savable = new TsFilter();
					prefs.getFilters().add( savable );
				}
				
				savable.setName( filter.getName() );
				savable.setDescription( filter.getDescription() );
				savable.setGlobal(true);
				popPageUntil("Filter Selection");
				
				enableFinish(true);
			} else if (c instanceof FilterSelectionPanel) {
				
				enableFinish(true);
				finishActionPerformed(e);
			} else {
				super.nextActionPerformed(e);
			}
		}

	}
	
	protected void finishActionPerformed(ActionEvent e) {
		Component curr = this.getPage(null);
		if( curr instanceof FilterSetupEvaluatePanel ) {
			this.nextActionPerformed(e);  // initiates save of work on screen
		}
		
		super.finishActionPerformed(e);
	}

}
