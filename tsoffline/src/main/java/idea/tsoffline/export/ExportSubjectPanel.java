/*
 * Created by JFormDesigner on Sun Jan 31 15:10:59 CST 2016
 */

package idea.tsoffline.export;

import java.io.File;
import java.io.IOException;

import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

import idea.persistmanager.H5CompositeWithMeta;
import idea.persistmanager.PiCompositeImporter;
import idea.gui.WizardPanelInterface;

/**
 * @author User #1
 */
public class ExportSubjectPanel extends JPanel  implements WizardPanelInterface {
	private ExportWizard wizard;
	public ExportSubjectPanel(ExportWizard wiz) {
		initComponents();
		this.wizard = wiz;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Subject Detail");
		panel1 = new JPanel();
		checkBox1 = new JCheckBox();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();

		//======== this ========
		setName("Subject");
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), fill:default:grow"));
		add(separator1, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"20dlu, $lcgap, default:grow, $lcgap, default",
				"default"));

			//---- checkBox1 ----
			checkBox1.setText("Add Subject ID to dataset");
			panel1.add(checkBox1, CC.xy(3, 1));
		}
		add(panel1, CC.xy(1, 3));

		//======== scrollPane1 ========
		{

			//---- table1 ----
			table1.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null},
					{null, null, null},
				},
				new String[] {
					"O", "Subject ID", "File"
				}
			) {
				boolean[] columnEditable = new boolean[] {
					false, true, false
				};
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
				cm.getColumn(2).setPreferredWidth(320);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, CC.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComponent separator1;
	private JPanel panel1;
	private JCheckBox checkBox1;
	private JScrollPane scrollPane1;
	private JTable table1;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
	@Override
	public void refresh() {
		// TODO Auto-generated method stub
		
	}

	public void refresh(PiCompositeImporter importer) throws IOException {

		wizard.enableNext(true);
		
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount( 0 );
		
		importer.rewind();
		do {
			H5CompositeWithMeta meta = importer.getCurrentMetaData();
			File f = importer.getFile();
			model.addRow( new Object[] { meta, meta.getSubject(), f.getPath()} );
		} while(importer.nextFile());
	}


	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public boolean finish() {
		// TODO Auto-generated method stub
		return false;
	}
}
