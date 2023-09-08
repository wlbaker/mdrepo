/*
 * Created by JFormDesigner on Fri Jun 17 16:47:14 CDT 2011
 */

package idea.meddaq.entry;

import idea.intf.StreamProducer;
import idea.model.IntfUtil;
import idea.model.PersistentItem;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.print.PageFormat;
import java.awt.print.PrinterException;
import java.io.File;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

import javax.print.PrintService;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.HashPrintServiceAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.print.attribute.PrintServiceAttributeSet;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTree;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;

import net.sf.jasperreports.engine.JRDataSource;
import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRExporterParameter;
import net.sf.jasperreports.engine.JasperFillManager;
import net.sf.jasperreports.engine.JasperPrint;
import net.sf.jasperreports.engine.JasperPrintManager;
import net.sf.jasperreports.engine.JasperReport;
import net.sf.jasperreports.engine.export.JRPrintServiceExporter;
import net.sf.jasperreports.engine.export.JRPrintServiceExporterParameter;
import net.sf.jasperreports.engine.util.JRLoader;
import idea.GuiUtil;
import idea.PrintUtil;
import idea.gui.ExcelAdapter;
import idea.jasper.ListModelDataSource;
import idea.schema.rp.RpDevice;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class StudypointReviewPanel extends JPanel {
	private static final String TASK = "StudyReview";

	private Image image0;

	private MedDAQEntryFrame frame;
	private List<JTable> tables = new LinkedList<JTable>();

	public StudypointReviewPanel(MedDAQEntryFrame frame) {
		initComponents();
		this.frame = frame;

		GuiUtil.initPrinters(printerList, TASK);

	}

	private void printSampleActionPerformed(ActionEvent evt) {
		try {
			printLaserActionPerformed(null);
		} catch (Exception e) {
			GuiUtil.showError("Print Sample", e);
		}
	}

	private void printSubjectActionPerformed(ActionEvent evt) {
		try {
			printLaserActionPerformed(null);
		} catch (Exception e) {
			GuiUtil.showError("Print Subject", e);
		}
	}

	private JasperPrint getFilledLabelReport() throws JRException {

		JasperReport jasperReport = null;
		JasperPrint jasperPrint = null;

		HashMap<String, Object> parameters = new HashMap<String, Object>();

		DefaultListModel m = new DefaultListModel();
		// LabelDataObject o = new LabelDataObject();
		//
		// o.ITEM_NO = proxy.getItemNo();
		// o.WEIGHT = proxy.getShipWt().intValue();
		// o.IMAGE = ia.getImage();
		// o.DESCRIPTION = ( lbl == null ) ? null : lbl.getDescr1();
		// o.UPC = (ship == null) ? "" : ship.getUpc();
		// o.DESCR2 = ( lbl == null ) ? "" : lbl.getDescr2();
		// o.COLOR = proxy.getColor();
		//
		// o.LABEL_TYPE = "*LO*";
		// o.INITIALS = "FJD/CRJ/RBM/NL";
		// o.PATENT = ( lbl == null) ? null : lbl.getPatent();
		//
		// if( o.DESCRIPTION == null || o.DESCRIPTION.length() == 0 ) {
		// o.DESCRIPTION = proxy.getDescription();
		// }
		//
		// m.addElement(o);

		JRDataSource jrds = new ListModelDataSource(m);
		parameters.put("REPORT_DATA_SOURCE", jrds);
		// parameters.put("REPORT_CONNECTION", JpaUtil.getExecutionConnection()
		// );

		String report = "StudyLabel"; // (String)template.getSelectedItem();

		String file_path = PrintUtil.findReportFile(parameters, report);
		System.err.println("ignoring file path...getting label myself!");
		file_path = "c:/opt/workspace/caddo/cardioStrip/bin/idea/labels/StudyData.jasper";
		File file = null;
		if (file_path != null) {
			file = new File(file_path);
		}
		if (file == null || !file.canRead()) {
			throw new JRException("Could not open file: " + file_path);
		}
		jasperReport = (JasperReport) JRLoader.loadObject(file);

		jasperPrint = JasperFillManager.fillReport(jasperReport, parameters, jrds);

		return jasperPrint;
	}

	private void previewActionPerformed(ActionEvent e) {
		try {
			JasperPrint jasperPrint = getFilledLabelReport();
			image0 = JasperPrintManager.printPageToImage(jasperPrint, 0, (float) 1.0);
			// image1 = JasperPrintManager.printPageToImage(jasperPrint, 0,
			// (float) 2.0);
			ImageIcon imageIcon = new ImageIcon(image0);
			// lblPage.setIcon(imageIcon);
		} catch (Exception e1) {
			e1.printStackTrace();
			JOptionPane.showMessageDialog(null, e1.getMessage());
		}
	}

	private void printLaserActionPerformed(ActionEvent e) {
		PrintService service = (PrintService) printerList.getSelectedItem();
		JasperPrint jasperPrint;
		try {
			jasperPrint = getFilledLabelReport();

		} catch (JRException e2) {
			// TODO Auto-generated catch block
			e2.printStackTrace();
			return;
		}

		// beginning of test

		// JasperViewer.viewReport(jasperPrint);

		PrintRequestAttributeSet printRequestAttributeSet = new HashPrintRequestAttributeSet();
		// printRequestAttributeSet.add( OrientationRequested.LANDSCAPE);

		PrintServiceAttributeSet printServiceAttributeSet = new HashPrintServiceAttributeSet();
		JRPrintServiceExporter exporter = new JRPrintServiceExporter() {

			@Override
			public int print(Graphics graphics, PageFormat arg1, int arg2) throws PrinterException {
				System.out.println("print rotated");
				Graphics2D g2d = (Graphics2D) graphics;
				g2d.rotate(Math.PI / 2.0);
				int err = super.print(graphics, arg1, arg2);
				g2d.rotate(-Math.PI / 2.0);
				return err;
			}

		};

		if (service != null) {
			exporter.setParameter(JRPrintServiceExporterParameter.PRINT_SERVICE, service);
			exporter.setParameter(JRPrintServiceExporterParameter.DISPLAY_PRINT_DIALOG, Boolean.FALSE);
		} else {
			exporter.setParameter(JRPrintServiceExporterParameter.DISPLAY_PRINT_DIALOG, Boolean.TRUE);
		}

		exporter.setParameter(JRExporterParameter.JASPER_PRINT, jasperPrint);

		exporter.setParameter(JRPrintServiceExporterParameter.PRINT_REQUEST_ATTRIBUTE_SET, printRequestAttributeSet);
		exporter.setParameter(JRPrintServiceExporterParameter.PRINT_SERVICE_ATTRIBUTE_SET, printServiceAttributeSet);
		exporter.setParameter(JRPrintServiceExporterParameter.DISPLAY_PAGE_DIALOG, Boolean.FALSE);

		try {
			exporter.exportReport();
		} catch (JRException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	private void entryActionPerformed(ActionEvent e) {
		frame.showEntryPanel();
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		scrollPane2 = new JScrollPane();
		tree1 = new JTree();
		tabber = new JTabbedPane();
		buttonPanel = new JPanel();
		printerList = new JComboBox();
		printSubject = new JButton();
		printSample = new JButton();
		entry = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout("default:grow", "default, $lgap, fill:default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout("80dlu, $rgap, default:grow", "fill:default:grow"));

			//======== scrollPane2 ========
			{

				//---- tree1 ----
				tree1.setRootVisible(false);
				tree1.setModel(new DefaultTreeModel(new DefaultMutableTreeNode("(root)") {
					{
						DefaultMutableTreeNode node1 = new DefaultMutableTreeNode("583");
						node1.add(new DefaultMutableTreeNode("June 1 2011"));
						node1.add(new DefaultMutableTreeNode("June 2 2011"));
						add(node1);
						node1 = new DefaultMutableTreeNode("584");
						node1.add(new DefaultMutableTreeNode("July 1 2011"));
						node1.add(new DefaultMutableTreeNode("July 2 2011"));
						add(node1);
					}
				}));
				tree1.setShowsRootHandles(true);
				scrollPane2.setViewportView(tree1);
			}
			panel1.add(scrollPane2, CC.xy(1, 1));
			panel1.add(tabber, CC.xy(3, 1));
		}
		add(panel1, CC.xy(1, 3));

		//======== buttonPanel ========
		{
			buttonPanel.setLayout(new FormLayout(
					"default:grow, 2*($lcgap, default), $lcgap, $ugap, $lcgap, [50dlu,default]", "default"));
			buttonPanel.add(printerList, CC.xy(1, 1));

			//---- printSubject ----
			printSubject.setText("Print Subject");
			printSubject.setEnabled(false);
			printSubject.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					printSubjectActionPerformed(e);
				}
			});
			buttonPanel.add(printSubject, CC.xy(3, 1));

			//---- printSample ----
			printSample.setText("Print Sample");
			printSample.setEnabled(false);
			printSample.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					printSampleActionPerformed(e);
				}
			});
			buttonPanel.add(printSample, CC.xy(5, 1));

			//---- entry ----
			entry.setText("Entry");
			entry.setEnabled(false);
			entry.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					entryActionPerformed(e);
				}
			});
			buttonPanel.add(entry, CC.xy(9, 1));
		}
		add(buttonPanel, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JScrollPane scrollPane2;
	private JTree tree1;
	private JTabbedPane tabber;
	private JPanel buttonPanel;
	private JComboBox printerList;
	private JButton printSubject;
	private JButton printSample;
	private JButton entry;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void refresh(Collection<EntrySheet> sheets) {
		tabber.removeAll();
		tables.clear();

		for (EntrySheet sheet : sheets) {

			JTable table = buildTableFromEntrySheet(sheet);
			if (table != null) {
				fillTable(table, sheet.getItems());

				tables.add(table);
				tabber.addTab(sheet.getName(), new JScrollPane(table));
			}

		}
	}

	private JTable buildTableFromEntrySheet(EntrySheet sheet) {

		LinkedList<String> timepoints = sheet.getTimepoints();
		int n = (timepoints == null) ? 0 : timepoints.size();
		if (n == 0) {
			return null;
		}

		JTable table = new JTable();
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		ExcelAdapter adapter = new ExcelAdapter(table);

		int idx = 0;
		String[] colNames = new String[n + 2];
		colNames[idx++] = "O";
		colNames[idx++] = "Prompt";

		for (String timepoint : timepoints) {
			colNames[idx++] = timepoint;
		}

		// ---- table1 ----
		table.setModel(new DefaultTableModel(colNames, 0) {
			Class<?>[] columnTypes = new Class<?>[] { Object.class, String.class, Double.class };

			@Override
			public Class<?> getColumnClass(int columnIndex) {
				if (columnIndex > 2) {
					columnIndex = 2;
				}
				return columnTypes[columnIndex];
			}

			// boolean[] columnEditable = new boolean[] { false, false, false,
			// false, true };

			@Override
			public boolean isCellEditable(int rowIndex, int columnIndex) {
				return false;
			}
		});

		TableColumnModel cm = table.getColumnModel();
		cm.getColumn(0).setResizable(false);
		cm.getColumn(0).setMinWidth(1);
		cm.getColumn(0).setMaxWidth(1);
		cm.getColumn(0).setPreferredWidth(1);
		cm.getColumn(1).setPreferredWidth(300);
		for (int i = 0; i < n; i++) {
			cm.getColumn(i + 2).setPreferredWidth(100);
		}

		return table;
	}

	private void fillTable(JTable table, LinkedList<EntryItem> entries) {
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount(0);

		double dummy = 0;
		for (EntryItem entry : entries) {
			model.addRow(new Object[] { entry, entry.getPrompt() });
			dummy++;
		}
	}

	public void clear() {
		DefaultTreeModel m1 = new DefaultTreeModel(new DefaultMutableTreeNode("(root)"));

		tree1.setModel(m1);

		tabber.removeAll();
		// DefaultTableModel m2 = (DefaultTableModel) table1.getModel();
		// m2.setRowCount( 0 );
	}

	public void enableEntry(boolean b) {
		entry.setEnabled(true);
	}

	public void addNumericsBlock(StreamProducer driver, PersistentItem item) {
		System.out.println("   driver=" + driver);
		RpDevice conf = null;
		if (driver != null) {
			conf = driver.getConfiguration();
		}
		System.out.println("     conf=" + conf);
		if (conf == null) {
			System.err.println("DRIVER/CONF IS NULL");
			return;
		}
		String name = conf.getName();
		System.out.println("     name=" + name);

		for (int i = 0; i < tabber.getTabCount(); i++) {
			String tab_title = tabber.getTitleAt(i);
			if (tab_title.equals(name)) {
				JTable table = tables.get(i);
				populateColumn(table, item);
				break;
			}
		}
	}

	private void populateColumn(JTable table, PersistentItem item2) {
		String tpName = (String) IntfUtil.getRawValueByLoc( item2, "TPOINT");
		System.out.println("checking tp=" + tpName);
		for (int col = 0; col < table.getColumnCount(); col++) {
			String colName = table.getColumnName(col);
			if (tpName.equals(colName)) {
				System.out.println("found tp at col=" + col);
				populateColumn(table, col, item2);
				break;
			}
		}

	}

	private void populateColumn(JTable table, int col, PersistentItem item2) {

		for (int row = 0; row < table.getRowCount(); row++) {
			EntryItem entry = (EntryItem) table.getValueAt(row, 0);
			String loc = entry.getSourceLoc();
			Object item = IntfUtil.getRawValueByLoc(item2, loc);
			if( item instanceof Number ) {
				item = IntfUtil.getScaledValueByLoc(item2, loc);
			}
			if (item != null) {
				table.setValueAt(item, row, col);
			}
		}

	}
}
