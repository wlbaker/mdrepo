/*
 * Created by JFormDesigner on Wed May 18 09:08:55 CDT 2011
 */

package idea;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.List;
import java.util.Map.Entry;
import java.util.prefs.BackingStoreException;

import javax.print.PrintService;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.table.DefaultTableModel;

import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRExpression;
import net.sf.jasperreports.engine.JRParameter;
import net.sf.jasperreports.engine.JasperReport;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class PrintProcessSetupForm extends JPanel {
	private final static String TASK = "PRINT_PROCESS";
	private RpAnalysis analysis;

	public PrintProcessSetupForm(RpStudy study, RpHardware hw, RpAnalysis analysis) {
		initComponents();

		this.analysis = analysis;
		if (hw == null) {
			hw = study.getHardware().get(0);
		}

		GuiUtil.initPrinters(printerList, TASK);

		String[] ar = new String[] { "On Print", "On Data: [device]" };

		DefaultComboBoxModel m = new DefaultComboBoxModel(ar);
		trigger.setModel(m);

		initDeviceList(hw);

		initFieldMappings(); // empty the table

		fileName.getDocument().addDocumentListener(new DocumentListener() {

			@Override
			public void changedUpdate(DocumentEvent e) {
				initFieldMappings();
			}

			@Override
			public void insertUpdate(DocumentEvent e) {
				initFieldMappings();
			}

			@Override
			public void removeUpdate(DocumentEvent e) {
				initFieldMappings();
			}
		});

		modelToPanel();

		String lastFileName = PrefUtil.getUserPref(TASK + "file", fileName.getText());
		if (lastFileName != null) {
			fileName.setText(lastFileName);
		}

	}

	private void initDeviceList(RpHardware hw) {
		DefaultComboBoxModel m = new DefaultComboBoxModel();
		List<RpDevice> devs = hw.getDevices();
		for (RpDevice dev : devs) {
			m.addElement(dev.getName());
		}
		device.setModel(m);
	}

	private void modelToPanel() {
		if (analysis == null) {
			return;
		}

		 StringStringMap params = analysis.getParam();
		for (Entry<String, String> p  : params.entrySet()) {
			String key = p.getKey();
			String value = (String) p.getValue();

			if (key.equals("report")) {
				fileName.setText(value);
			} else if (key.equals("printer")) {
				GuiUtil.selectComboString(printerList, value);
			} else if (key.equals("trigger")) {
				GuiUtil.selectComboString(trigger, value);
			} else if (key.equals("device")) {
				GuiUtil.selectComboString(device, value);
			} else {
				System.err.println("Print Process Setup: unknown param " + key);
			}
		}
	}

	/*
	 * 
	 * 
	 * var cev = dest.getEvent( ConnectionEvent ); var nev = dest.getEvent(
	 * NumericsEvent );
	 * 
	 * dest.setDisplayMessage( "IDE2A", "" + nev ); dest.setDisplayMessage(
	 * "IDEA", "Doch" );
	 */
	protected void initFieldMappings() {

		DefaultTableModel model = (DefaultTableModel) fieldMappings.getModel();
		model.setRowCount(0);

		File f = new File(fileName.getText());
		if (f.exists()) {
			// JasperReport report = PrintUtil.loadReport( fileName.getText() );
			// PrintUtil.getParameters( report );

			PrefUtil.saveUserPref(TASK + "file", fileName.getText());

			try {
				addJasperParameters(f, model);
			} catch (JRException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		model.addRow(new Object[] { "file", fileName });
		model.addRow(new Object[] { "param", "drager0$ecg.hr" });

	}

	private void addJasperParameters(File f, DefaultTableModel model) throws JRException {
		JasperReport report = PrintUtil.loadReport(f.getAbsolutePath());
		JRParameter[] params = report.getParameters();
		for (JRParameter param : params) {
			String name = param.getName();
			JRExpression expr = param.getDefaultValueExpression();
			if (expr == null) {
				System.out.println("expr is null for: " + param);
				model.addRow(new Object[] { param, name, param.getDescription(), "?" });
			} else {
				System.out.println(" " + name + " --> " + expr.getText());

				model.addRow(new Object[] { param, name, param.getDescription(), expr.getText() });
			}
		}

	}

	private void browseActionPerformed(ActionEvent e) {
		File parent = null;
		String lastDir = fileName.getText();
//		if (lastDir.length() == 0) {
//			lastDir = PrefUtil.getUserPref(AppSetup.getAnalysisFile(), null);
//		}
		if (lastDir != null) {
			parent = new File(lastDir);
		}

		GuiUtil.doOpenFileChooser(JFileChooser.FILES_AND_DIRECTORIES, "Printer Label", this, parent, new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				File file = (File) e.getSource();
				fileName.setText(file.getAbsolutePath());
			}
		});

	}

	private void okActionPerformed(ActionEvent e) {
		PrintService service = (PrintService) printerList.getSelectedItem();
		try {
			ConfigurationInfo.setSelectedPrinter(TASK, service.toString());
		} catch (BackingStoreException e1) {
			GuiUtil.showError("[ STORE ]", e1);
		}
		panelToModel();
		cancelActionPerformed(null);
	}

	private void panelToModel() {
		StringStringMap params = analysis.getParam();

		while (params.size() > 0) {
			params.remove(0);
		}

		params.put("report", fileName.getText());

		PrintService service = (PrintService) printerList.getSelectedItem();

		params.put("printer", service.toString());
		params.put("trigger", (String)trigger.getSelectedItem());

		if (device.isEnabled() && device.getSelectedIndex() >= 0) {
			params.put("device", (String)device.getSelectedItem());
		}
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void testActionPerformed(ActionEvent e) {
		panelToModel();
		PrintProcess process = new PrintProcess(analysis);
		try {
			process.print();
		} catch (Exception e1) {
			GuiUtil.showError("Printer Test", e1);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		separator2 = compFactory.createSeparator("Destination");
		panel1 = new JPanel();
		label3 = new JLabel();
		fileName = new JTextField();
		browse = new JButton();
		label2 = new JLabel();
		trigger = new JComboBox();
		label4 = new JLabel();
		device = new JComboBox();
		label1 = new JLabel();
		printerList = new JComboBox();
		separator1 = compFactory.createSeparator("Field Mappings");
		scrollPane1 = new JScrollPane();
		fieldMappings = new JTable();
		panel2 = new JPanel();
		ok = new JButton();
		test = new JButton();
		cancel = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"3*(default, $lgap), fill:[120dlu,default]:grow, $lgap, default"));
		add(separator2, CC.xy(1, 1));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, right:default, $lcgap, [121dlu,default], $lcgap, [40dlu,default]:grow, 2*($lcgap, default)",
				"5*(default, $lgap), default"));

			//---- label3 ----
			label3.setText("Report File:");
			panel1.add(label3, CC.xy(3, 3));
			panel1.add(fileName, CC.xywh(5, 3, 3, 1));

			//---- browse ----
			browse.setText("Browse");
			browse.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					browseActionPerformed(e);
				}
			});
			panel1.add(browse, CC.xy(9, 3));

			//---- label2 ----
			label2.setText("Trigger:");
			panel1.add(label2, CC.xy(3, 5));
			panel1.add(trigger, CC.xy(5, 5));

			//---- label4 ----
			label4.setText("Device:");
			panel1.add(label4, CC.xy(3, 7));
			panel1.add(device, CC.xy(5, 7));

			//---- label1 ----
			label1.setText("Destination Printer:");
			panel1.add(label1, CC.xy(3, 9));
			panel1.add(printerList, CC.xy(5, 9));
		}
		add(panel1, CC.xy(1, 3));
		add(separator1, CC.xy(1, 5));

		//======== scrollPane1 ========
		{

			//---- fieldMappings ----
			fieldMappings.setPreferredScrollableViewportSize(new Dimension(450, 100));
			fieldMappings.setModel(new DefaultTableModel(
				new Object[][] {
					{null, null, null, null},
					{null, null, null, null},
				},
				new String[] {
					"O", "Name", "Description", "Value"
				}
			) {
				boolean[] columnEditable = new boolean[] {
					false, false, false, false
				};
				@Override
				public boolean isCellEditable(int rowIndex, int columnIndex) {
					return columnEditable[columnIndex];
				}
			});
			scrollPane1.setViewportView(fieldMappings);
		}
		add(scrollPane1, CC.xy(1, 7));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow, 3*($lcgap, [50dlu,default])",
				"default"));

			//---- ok ----
			ok.setText("OK");
			ok.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					okActionPerformed(e);
				}
			});
			panel2.add(ok, CC.xy(3, 1));

			//---- test ----
			test.setText("Test");
			test.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					testActionPerformed(e);
				}
			});
			panel2.add(test, CC.xy(5, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel2.add(cancel, CC.xy(7, 1));
		}
		add(panel2, CC.xy(1, 9));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JComponent separator2;
	private JPanel panel1;
	private JLabel label3;
	private JTextField fileName;
	private JButton browse;
	private JLabel label2;
	private JComboBox trigger;
	private JLabel label4;
	private JComboBox device;
	private JLabel label1;
	private JComboBox printerList;
	private JComponent separator1;
	private JScrollPane scrollPane1;
	private JTable fieldMappings;
	private JPanel panel2;
	private JButton ok;
	private JButton test;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
