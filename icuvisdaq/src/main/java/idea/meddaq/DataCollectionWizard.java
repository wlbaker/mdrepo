package idea.meddaq;

import java.awt.Component;
import java.awt.event.ActionEvent;

import javax.swing.JPanel;
import javax.swing.tree.DefaultMutableTreeNode;

import idea.devwizard.AnnotationPanel;
import idea.devwizard.HardwareEditPanel;
import idea.devwizard.ResourcePanel;
import idea.devwizard.SetupWizard;
import idea.devwizard.SiteSetupPanel;
import idea.devwizard.StudyDefReviewPanel;
import idea.gui.WizardPanelInterface;
import idea.studywiz.AnalysisSelectionPanel;
import idea.studywiz.StudySelectionPanel;

public class DataCollectionWizard extends SetupWizard {

	public DataCollectionWizard() {
		final SetupWizard panel = new SetupWizard();
		addPage(null, "Site Identification");

		DefaultMutableTreeNode studySelection = addPage(null, "Study Selection");
		addPage(studySelection, "Study Link");
		addPage(studySelection, "Study Definition");

		DefaultMutableTreeNode hardwareSetup = addPage(null, "Hardware Setup", HardwareEditPanel.class);
		// hardwareSetup.add(new DefaultMutableTreeNode("Edit Hardware"));
		addPage(hardwareSetup, "Device Selection");
		addPage(hardwareSetup, "Signal Selection");

		addPage(null, "Analysis Setup");

		addPage(null, "Review");

	}

	protected void nextActionPerformed(ActionEvent e) {
		JPanel filler = getFiller();
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.next();

				if (!ok)
					return;

				if (ri instanceof SiteSetupPanel) {
					boolean enable_creation = true;
					boolean enable_finish = true;
					// pushPage(new RepositorySetupPanel(this));

					JPanel panel = new StudySelectionPanel(this, false, enable_creation, enable_finish);
					pushPage(panel);

				} else if (ri instanceof StudySelectionPanel) {
					this.setStudy(((StudySelectionPanel) ri).getSelectedStudy());
					// if ((opt_flags & HARDWARE_FLAG) != 0) {
					// JPanel panel = new HardwarePanel(this);
					// panel.setName("Hardware Setup");
					// pushPage(panel);
					// } else
						HardwareEditPanel panel = new HardwareEditPanel(this, getStudy());

						panel.setName("Hardware Setup");
						pushPage(panel);

				} else if (ri instanceof HardwareEditPanel) {

					AnalysisSelectionPanel panel = new AnalysisSelectionPanel(this, getStudy());
					pushPage(panel);

				} else if (ri instanceof AnalysisSelectionPanel) {
					enableFinish(true);
					pushPage(new StudyDefReviewPanel(this));
				} else {
					enableFinish(true);
				}
				break;
			}
		}
	}

}
