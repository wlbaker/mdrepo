/*
 * Created by JFormDesigner on Wed May 11 09:20:51 CDT 2011
 */

package idea.simulator;

import idea.intf.IDEAClient;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.persistence.ArchiveMetaData;
import idea.schema.rp.RpDevice;

import java.io.IOException;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.repository.RepositoryInterface;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

class MetaInfo {
	RepositoryInterface repo;
	RpDevice device;
	String studyId;
	String devName;
}

/**
 * @author User #2
 */
@Slf4j
@SuppressWarnings("serial")
public class TimeSelectionPanel extends JPanel implements WizardPanelInterface, ListSelectionListener, StreamConsumer {
	private static final int OBJECT_COL = 0;

	private WizardMasterInterface wiz;

	private IDEAClient driver;

	public TimeSelectionPanel(WizardMasterInterface wiz) {
		initComponents();

		this.wiz = wiz;

		ListSelectionModel selectionModel = table1.getSelectionModel();
		selectionModel.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		selectionModel.addListSelectionListener(this);
	}

	public void requestMeta() throws IOException {
		log.error("FIXME: driver.requestArchiveMetadata( 111 );");
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting()) {
			// ignore
		} else {
			int rows = table1.getSelectedRowCount();

			// wizard.enableNext( rows > 0);
		}

	}

	public void refresh() {
		log.error("FIXME: See refresh methods below");
	}

//	public void refresh(IppArchiveReply arch) {
//		DefaultTableModel model = (DefaultTableModel) table1.getModel();
//		model.setRowCount(0);
//		List<IppMeta> metas = arch.getMetasList();
//		if (metas != null) {
//			for (IppMeta meta : metas) {
//				addMeta(model, meta);
//			}
//		}
//
//	}
//
//	private void addMeta(DefaultTableModel model, IppMeta meta) {
//		Date startTime = new Date(meta.getStartTime());
//		Date endTime = new Date(meta.getEndTime());
//		
//		ArchiveMetaData ameta = new ArchiveMetaData();
//		ameta.setStartTime( startTime );
//		ameta.setStopTime(endTime);
//		model.addRow(new Object[] { ameta, meta.getName(), startTime, endTime });
//	}

	@Override
	public boolean finish() {
		try {
			if (save()) {
				return true;	
			}
			
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
			table1.setModel(new DefaultTableModel(new Object[][] { { null, null, null, null }, { null, null, null, null }, }, new String[] { "O", "Segment",
					"Start Date", "End Date" }) {
				boolean[] columnEditable = new boolean[] { false, false, false, false };

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
				cm.getColumn(1).setPreferredWidth(120);
				cm.getColumn(2).setPreferredWidth(120);
				cm.getColumn(3).setPreferredWidth(80);
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

	public void setDriver(IDEAClient driver) {
		this.driver = driver;
		log.error("FIXME: ?? driver.addStreamListener( null, this );");
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		System.out.println("FIXME: [timeselectionpanel event: " + item );
		
//		if( source instanceof IppArchiveReply ) {
//			System.out.println("timeSelectionPanel refreshing");
//			refresh( (IppArchiveReply) source );
//		}
	}

	public ArchiveMetaData getMeta() {
		int row = table1.getSelectedRow();
		if( row < 0 ) {
			return null;
		}
		
		return (ArchiveMetaData) table1.getValueAt( row, OBJECT_COL );
	}
}
