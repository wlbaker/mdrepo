/*
 * Created by JFormDesigner on Thu Apr 07 11:46:18 CDT 2016
 */

package idea.tsoffline.explorer;

import java.awt.BorderLayout;
import java.io.IOException;
import java.util.Date;

import javax.swing.JPanel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.persistence.ArchiveMetaData;
import idea.persistence.PiSubjectImporter;
import idea.schema.rp.RpSubject;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.gui.wizard.DefaultStudyHeaderPanel;
import idea.tsoffline.DateRangeSelectionPanel;

/**
 * @author User #1
 */
public class InfoAndRangeSelection extends JPanel  implements WizardPanelInterface  {
	private DefaultStudyHeaderPanel headerPanel;
	private WizardMasterInterface wiz;
	public InfoAndRangeSelection(WizardMasterInterface wiz) {
		initComponents();
		
		this.wiz = wiz;
		
		contentPanel.add( headerPanel = new DefaultStudyHeaderPanel(wiz), BorderLayout.CENTER );
		headerPanel.enableEdits(false);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		contentPanel = new JPanel();
		dateRangeSelectionPanel = new DateRangeSelectionPanel();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"fill:default:grow, $lgap, default"));

		//======== contentPanel ========
		{
			contentPanel.setLayout(new BorderLayout());
		}
		add(contentPanel, CC.xy(1, 1));
		add(dateRangeSelectionPanel, CC.xy(1, 3));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JPanel contentPanel;
	private DateRangeSelectionPanel dateRangeSelectionPanel;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	
	
	@Override
	public void refresh() {
		headerPanel.refresh();
		wiz.enableNext(true);
	}

	@Override
	public void previous() {
		// let it go
	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public boolean finish() {
		return true;
	}

	public void setImporter(PiSubjectImporter importer) throws IOException {
		RpSubject header = importer.getSubjectInfo();
		ArchiveMetaData meta = importer.getMetaData();
		setSubjectAndTime( header, meta.getStartTime(), meta.getStopTime() );
	}
	
	public void setSubjectAndTime(RpSubject subject, Date startTime, Date endTime) {
		headerPanel.setStudyHeader(subject);
		dateRangeSelectionPanel.setStartStop(startTime, endTime);
	}


	public Date getStartDate() {
		return dateRangeSelectionPanel.getStartDate();
	}

	public Date getEndDate() {
		return dateRangeSelectionPanel.getEndDate();
	}

	public String getNotes() {
		return headerPanel.getNotes();
	}

}
