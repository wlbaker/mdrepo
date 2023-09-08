/*
 * Created by JFormDesigner on Tue Aug 02 12:06:05 CDT 2011
 */

package idea.adapters.gui;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.conf.DeviceConfiguration;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ProxyDeviceStatus extends JPanel implements StreamConsumer {
	private StreamProducer driver;
	private DeviceConfiguration conf;
	
	public ProxyDeviceStatus(StreamProducer driver, DeviceConfiguration conf) {
		initComponents();
		
		this.driver = driver;
		this.conf = conf;
		
		// String ip = conf.get
		assert( driver != null ) : "ProxyDeviceStatus driver cannot be null.";
			
		//?
		// driver.addEventListener( NumericsEvent.class, this);
		
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount( 0 );
	}
	
	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		if ( sid == StreamID.MEASUREMENT ) {
			DefaultTableModel model = (DefaultTableModel) table.getModel();
			model.addRow( new Object[] { item, "tm", "Entry" });
		}
		
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator1 = compFactory.createSeparator("Status");
		panel1 = new JPanel();
		label2 = new JLabel();
		binding = new JLabel();
		label1 = new JLabel();
		connectionCount = new JLabel();
		separator2 = compFactory.createSeparator("Log");
		scrollPane1 = new JScrollPane();
		table = new JTable();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"default:grow",
			"3*(default, $lgap), default:grow"));
		add(separator1, cc.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, right:default, $lcgap, default:grow",
				"3*(default, $lgap), default"));

			//---- label2 ----
			label2.setText("Binding:");
			panel1.add(label2, cc.xy(3, 3));

			//---- binding ----
			binding.setText("localhost/9999");
			panel1.add(binding, cc.xy(5, 3));

			//---- label1 ----
			label1.setText("Connections:");
			panel1.add(label1, cc.xy(3, 5));

			//---- connectionCount ----
			connectionCount.setText("text");
			panel1.add(connectionCount, cc.xy(5, 5));
		}
		add(panel1, cc.xy(1, 3));
		add(separator2, cc.xy(1, 5));

		//======== scrollPane1 ========
		{

			//---- table ----
			table.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null},
					{null, null, null},
				},
				new String[] {
					"O", "tm", "Event"
				}
			) {
				boolean[] columnEditable = new boolean[] {
					false, false, false
				};
				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			{
				TableColumnModel cm = table.getColumnModel();
				cm.getColumn(0).setResizable(false);
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(80);
				cm.getColumn(2).setPreferredWidth(300);
			}
			scrollPane1.setViewportView(table);
		}
		add(scrollPane1, cc.xy(1, 7));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator1;
	private JPanel panel1;
	private JLabel label2;
	private JLabel binding;
	private JLabel label1;
	private JLabel connectionCount;
	private JComponent separator2;
	private JScrollPane scrollPane1;
	private JTable table;
	// JFormDesigner - End of variables declaration  //GEN-END:variables

}
