/*
 * Created by JFormDesigner on Wed May 11 09:20:51 CDT 2011
 */

package idea.simulator;

import java.io.File;
import java.io.IOException;
import java.util.List;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import idea.GuiUtil;

import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;
import idea.repository.io.LocalJAXBRepository;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpStudy;
import idea.schema.rp.RpSubject;

class RSS {
	RepositoryInterface repo;
	RpStudy study;
	RpSubject subject;
}

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SimulatorRepositoryPanel extends JPanel implements WizardPanelInterface, ListSelectionListener {
	private static final int OBJECT_COL = 0;
	private SimulatorWizard wizard;

	public SimulatorRepositoryPanel(SimulatorWizard wiz) {
		initComponents();
		this.wizard = wiz;

		refresh();

		ListSelectionModel selectionModel = table1.getSelectionModel();
		selectionModel.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		selectionModel.addListSelectionListener(this);

		wiz.enableFinish(false);
		wiz.enableNext(false);

	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting()) {
			// ignore
		} else {
			int rows = table1.getSelectedRowCount();

			wizard.enableNext(rows > 0);
		}

	}

	public void refresh() {
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);
		RepositoryInterface[] repos = RepositoryFactory.getRegisteredRepositories();
		for (RepositoryInterface repo : repos) {
			try {
				addRepoSubjects(model, repo);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	private void addRepoSubjects(DefaultTableModel model, RepositoryInterface repo) throws Exception {
		List<RpStudy> studies = repo.getStudyList(null);
		if (studies == null) {
			return;
		}
		for (RpStudy study : studies) {
			System.err.println("FIXME: SimulatorRepositoryPanel");
			List<RpSubject> subjects = null; // repo.getSubjectList(study.getIdentifier());
			if (subjects == null) {
				continue;
			}
			for (RpSubject subject : subjects) {
				RSS rss = new RSS();
				rss.repo = repo;
				rss.study = study;
				rss.subject = subject;
				model.addRow(new Object[] { rss, repo.getName(), study.getTitle(), subject.getIdentifier() });
			}
		}

	}

	@Override
	public boolean finish() {
		try {
			if (!save()) {
				return false;
			}
			return true;
		} catch (Exception e) {
			GuiUtil.showError("Error saving repository info", e);
		}
		return false;
	}

	@Override
	public boolean next() {
		boolean ok = false;
		try {
			ok = save();

			if (ok) {

				GuiUtil.showMessage("FIXME: AnalysisSelectionPanel?");
//				JPanel page = new AnalysisSelectionPanel(wizard, wizard.getStudy() );
//
//				page.setName("Analysis");
				// wizard.pushPage(page);
			}
		} catch (Exception e) {
			GuiUtil.showError("Error getting repository info", e);
		}
		return ok;
	}

	private boolean save() throws IOException {
		boolean ok = false;
		int sel = table1.getSelectedRow();

		if (sel >= 0) {
			DefaultTableModel model = (DefaultTableModel) table1.getModel();

			Object o = model.getValueAt(sel, OBJECT_COL);
			RSS rss = (RSS) o;

			LocalJAXBRepository locr = (LocalJAXBRepository) rss.repo;
			File dataFile = locr.getSessionFile(rss.study, rss.subject, null, "0000.h5");
			wizard.setSimulationSource("file", null, dataFile.getCanonicalPath());

			ok = true;
		}
		;

		return ok;
	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:default:grow, $lgap, default"));

		//======== scrollPane1 ========
		{

			//---- table1 ----
			table1.setModel(new DefaultTableModel(new Object[][] { { null, null, null, null, null },
					{ null, null, null, null, null }, }, new String[] { "O", "Repository", "Study", "Subject", "Date" }) {
				boolean[] columnEditable = new boolean[] { false, false, false, false, false };

				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = table1.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(80);
				cm.getColumn(2).setPreferredWidth(150);
				cm.getColumn(3).setPreferredWidth(80);
				cm.getColumn(4).setPreferredWidth(150);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, cc.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JScrollPane scrollPane1;
	private JTable table1;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

}
