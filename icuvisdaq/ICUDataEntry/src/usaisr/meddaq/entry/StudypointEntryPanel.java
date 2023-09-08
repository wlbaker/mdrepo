/*
 * Created by JFormDesigner on Sun Jun 19 15:29:23 CDT 2011
 */

package idea.meddaq.entry;

import idea.conf.DeviceConfiguration;
import idea.intf.StreamConsumer;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.ModelUtil;
import idea.model.PersistentItem;

import java.awt.Color;
import java.awt.Component;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Set;

import javax.print.PrintService;
import javax.swing.DefaultCellEditor;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import lombok.extern.slf4j.Slf4j;
import net.sf.jasperreports.engine.JRException;
import idea.ConfigurationInfo;
import idea.GuiUtil;
import idea.PrintUtil;
import idea.SelectAllTextRunLater;
import idea.analysis.AnalysisPanelInterface;
import idea.gui.ColorRenderer;
import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpMetric;
import idea.schema.rp.StringStringMap;

import com.itextpdf.text.pdf.BarcodePDF417;
import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.factories.DefaultComponentFactory;
import com.jgoodies.forms.layout.FormLayout;
import com.toedter.calendar.JDateChooser;

/**
 * @author User #2
 */
class TimepointWrapper {

	private String time;
	private String offset;
	private EntryTimePoint tp;

	public TimepointWrapper(EntryTimePoint timepoint, String tpTime, String tpOffset) {
		this.time = tpTime;
		this.offset = tpOffset;
		this.tp = timepoint;
	}

	public String getTime() {
		return time;
	}

	public String getOffset() {
		return offset;
	}

	public String getTpName() {
		return tp.getTpName();
	}

	public EntryTimePoint getTimepoint() {
		return tp;
	}

	@Override
	public String toString() {

		return getTpName();
	}

}

class ListSelectionWrapper implements ListSelectionListener {

	private JTable table;

	public ListSelectionWrapper(JTable table) {
		this.table = table;
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		if (e.getValueIsAdjusting() == false) {
			// DefaultListSelectionModel model = (DefaultListSelectionModel) e.getSource();
			System.out.println(" listsel val=: " + e.getFirstIndex() + "/" + e);
			int last_idx = e.getLastIndex();
			table.editCellAt(last_idx, StudypointEntryPanel.COL_COMMIT);

		}
	}
}

@SuppressWarnings("serial")
@Slf4j
public class StudypointEntryPanel extends JPanel implements AnalysisPanelInterface, StreamConsumer {

	private static final RpAnalysis analysisInfo;
	static {
		analysisInfo = new RpAnalysis();
		analysisInfo.setName("Studypoint Entry");
		analysisInfo.setAnalysisClass(StudypointEntryPanel.class.getCanonicalName());
	}

	private static final String TASK = "StudyEntry";

	static final int COL_OBJECT = 0;

	static final int COL_KEY = 2;
	static final int COL_VALUE = 3;
	static final int COL_COMMIT = 4;

	//	private IDEADriver server_driver;
	//	private IDEAServer generator;

	private DeviceConfiguration ref_caps;
	ArrayList<JTable> tables = new ArrayList<JTable>();
	ArrayList<Class<? extends PersistentItem>> models = new ArrayList<Class<? extends PersistentItem>>();
	private ArrayList<ColorRenderer> colors = new ArrayList<ColorRenderer>();

	int verbose = 1;

	private Date startTime;

	/**
	 * This constructor is invoked by the online analysis processor. Caps are
	 * created from the xls indicated in the analysis object.
	 * 
	 * @param producers
	 * @param anal
	 */
	public StudypointEntryPanel(StreamProducer[] producers, RpAnalysis anal) {
		this(null);

		StringStringMap params = anal.getParam();
		String xls = null;
		if (params != null) {
			for (String key : params.keySet()) {
				log.error("config key: {}", key);
				System.out.println("fixme");
			}

			xls = params.get("excelFile");
		}
		if (xls == null) {
			// FIXME: BAD BAD BAD hardcode
			xls = "/opt/study/A-14-001 UTMB-EPI/protocol.xlsx";
			File f = new File(xls);
			if( !f.exists() ) {
				xls = "c:/opt/server/A-14-001 UTMB-EPI/protocol.xlsx";
				f = new File(xls);
			}
			if( !f.exists() ) {
				xls = "c:/opt/study/A-14-001 UTMB-EPI/protocol.xlsx";
				// dont need to check if it exists...last chance
			}
		}

		if (xls != null) {
			File f = new File(xls);
			try {
				EntryModel entryModel = EntryUtil.loadEntrySheets(f);
				// i need to turn this into a standard configuration for reporting my capabilities
				// ref_caps = EntryUtil.getModelAsConfiguration();
				refresh(null, entryModel);
			} catch (IOException e) {
				GuiUtil.showError("Error loading protocol data.", e);
			}

		}
	}

	/**
	 * This constructor is invoked as part of a client who already received the
	 * caps.
	 * 
	 * @param server_driver
	 * @param caps
	 */
	public StudypointEntryPanel(DeviceConfiguration caps) {

		this.ref_caps = caps; // caps for the remote idea server

		initComponents();

		GuiUtil.initPrinters(printerList, TASK);

	}

	private void refreshActionPerformed(ActionEvent e) {

		int idx = tabber.getSelectedIndex();
		if (idx < 0) {
			return; // shouldn't happen?
		}

		JTable table = tables.get(idx);
		ColorRenderer colorRenderer = colors.get(idx);
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		clearCurrentValues(colorRenderer, model);

		//		DeviceCapabilities tran_req = new DeviceCapabilities();
		//		for (int row = 0; row < model.getRowCount(); row++) {
		//			EntryItem tp = (EntryItem) model.getValueAt(row, COL_OBJECT);
		//			assert (tp != null) : "invalid";
		//
		//			System.out.println("adding tp: " + tp + " of count=" + model.getRowCount());
		//			String devName = tp.getDev();
		//			String loc = tp.getLoc();
		//
		//			int pos;
		//			if ((pos = devName.indexOf(':')) > 0) {
		//				loc = devName.substring(pos + 1);
		//				devName = devName.substring(0, pos - 1);
		//			}
		//
		//			if ("Evita".equals(devName)) {
		//				//MetricDescription d = new MetricDescription( loc, null, null, (String)null );
		//				//metrics.add( d );
		//			}
		//		}
		//
		//		MgEntryFrame.dump_dev("studyentrypoint", tran_req);

		int reqId = 333;
		Date dt = refreshTime.getDate();

		try {
			//			long tsStart = IDEA.CURRENT_MSTIME;
			//			long tsEnd = IDEA.CURRENT_MSTIME;
			//			if (dt != null) {
			//				tsStart = dt.getTime();
			//				System.err.println("StudypointEntryPanel ERR: tsEnd should always be 0");
			//				tsEnd = tsStart + 5000;
			//			}

			GuiUtil.showMessage("FIXME in StudypopintEntry requestTransfer");
			// server_driver.requestTransfer(reqId, new Date(tsStart), new Date(tsEnd), null);
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}//  job_req );
	}

	private void clearCurrentValues(ColorRenderer colorRenderer, DefaultTableModel model) {
		colorRenderer.clear();

		for (int row = 0; row < model.getRowCount(); row++) {
			model.setValueAt(null, row, COL_VALUE);
		}
	}

	public void refresh(Date startTime, EntryModel entryModel) {
		refreshTimepoints(startTime, entryModel.getTimepoints());
		refreshSheets(startTime, entryModel.getSheets());
		this.startTime = startTime;
		timepointComboActionPerformed(null);
	}

	private void refreshSheets(Date startTime, LinkedList<EntrySheet> sheets) {
		tabber.removeAll();

		tables.clear();
		models.clear();
		colors.clear();

		for (EntrySheet sheet : sheets) {

			JTable table = buildTableFromEntrySheet(sheet);
			GuiUtil.initTable(table, true);
			fillTable(table, sheet.getItems());
			Class<? extends PersistentItem> block = sheet.getDataModel(); // buildNumericsBlockFromEntrySheet(sheet.getItems());

			ColorRenderer colorRenderer = new ColorRenderer(table, table.getDefaultRenderer(Object.class));

			colorRenderer.addRenderer(Double.class, table.getDefaultRenderer(Double.class));
			colorRenderer.addRenderer(Integer.class, table.getDefaultRenderer(Integer.class));
			colorRenderer.addRenderer(String.class, table.getDefaultRenderer(String.class));
			//			colorRenderer.addRenderer(Number.class, table.getDefaultRenderer(Number.class));
			table.setDefaultRenderer(Double.class, colorRenderer);
			table.setDefaultRenderer(Integer.class, colorRenderer);
			//			table.setDefaultRenderer(Object.class, colorRenderer);
			table.setDefaultRenderer(String.class, colorRenderer);

			tables.add(table);
			models.add(block);
			colors.add(colorRenderer);

			table.getInputMap().put(KeyStroke.getKeyStroke("ENTER"), "selectNextColumnCell");
			table.getInputMap().put(KeyStroke.getKeyStroke("shift ENTER"), "selectPreviousColumnCell");

			table.getSelectionModel().addListSelectionListener(new ListSelectionWrapper(table));
			table.addPropertyChangeListener(new PropertyChangeListener() {

				@Override
				public void propertyChange(PropertyChangeEvent evt) {
					System.out.println("prop: " + evt.getPropertyName() + "/" + evt);

					if ("tableCellEditor".equals(evt.getPropertyName())) {

						final JTable table = (JTable) evt.getSource();
						DefaultCellEditor editor = (DefaultCellEditor) evt.getNewValue();
						if (editor == null) {
							//							final int row = table.getSelectedRow();
							//							SwingUtilities.invokeLater(new Runnable() {
							//
							//								@Override
							//								public void run() {
							//									System.out.println("editing next cell at: " + (row + 1));
							//									table.getSelectionModel().setSelectionInterval( row+1, row+1);
							//									table.editCellAt(row + 1, COL_COMMIT);
							//								}
							//							});

						} else {
							Component comp = editor.getComponent();
							if (comp != null) {
								SelectAllTextRunLater selector = new SelectAllTextRunLater((JTextField) comp);
								SwingUtilities.invokeLater(selector);
							}
						}
					}
				}
			});
			//			TableCellEditor editor1 = table.getDefaultEditor(Double.class);
			//			Component comp = editor1.getTableCellEditorComponent(table, null, false, 0, 0);
			//			GuiUtil.initSelectAllOnFocus( (JComponent) comp );
			//			TableCellEditor editor2 = table.getDefaultEditor(Integer.class);
			//			if( editor1 != editor2 ) {
			//				GuiUtil.initSelectAllOnFocus( (JComponent) editor2 );
			//			}

			tabber.addTab(sheet.getName(), new JScrollPane(table));
		}
	}

	private void refreshTimepoints(Date startTime, LinkedList<EntryTimePoint> timepoints) {
		DefaultComboBoxModel model = new DefaultComboBoxModel();

		for (EntryTimePoint timepoint : timepoints) {
			
			Date dt = timepoint.getTpTime(startTime);

			model.addElement(new TimepointWrapper(timepoint, "" + dt, "" + dt));
		}

		timepointCombo.setModel(model);
	}

	private void fillTable(JTable table, LinkedList<EntryItem> entries) {
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount(0);

		double dummy = 0;
		for (EntryItem entry : entries) {
			model.addRow(new Object[] { entry, entry.getPrompt(), entry.getDevValue(), dummy + 1, dummy });
			dummy++;
		}
	}

	private void fillValues(String deviceName, PersistentItem parent, RpMetric[] rpMetrics) {

		JTable table = tables.get(0);
		ColorRenderer colorRenderer = colors.get(0);
		DefaultTableModel model = (DefaultTableModel) table.getModel();

		System.out.println("  filling values for device: " + deviceName);
		for (int row = 0; row < model.getRowCount(); row++) {
			EntryItem entry = (EntryItem) model.getValueAt(row, COL_OBJECT);
			if (deviceName.equals(entry.getDev())) {

				RpMetric metric = findItem(entry.getSourceLoc(), rpMetrics);
				if (metric == null) {
					log.error("could not find item: {}/{}", entry.getPrompt(), entry.getSourceLoc());
				} else {
					Object val = IntfUtil.getRawValue(parent, metric);
					entry.setEntryValue(val);
					model.setValueAt(val, row, COL_VALUE);
					colorRenderer.setCellColor(row, COL_KEY, Color.green);
					colorRenderer.setCellColor(row, COL_VALUE, Color.green);
					colorRenderer.setRowColor(row, Color.green);
				}
			}
		}
	}

	private RpMetric findItem(String loc, RpMetric[] rpMetrics) {
		if (loc == null) {
			return null;
		}

		for (int i = 0; i < rpMetrics.length; i++) {
			RpMetric item = rpMetrics[i];
			assert (item != null) : "StudypointEntryPanel/findItem: NULL item";

			if (item == null) {
				System.err.println("StudypointEntryPanel/findItem: NULL item");
				continue;
			}

			if (loc.equals(item.getLocation())) {
				return item;
			}

			// I allow the CODE to be used for the loc in the spreadsheet
			String code = item.getLocation();
			if (loc.equals(code)) {
				return item;
			}
		}

		return null;
	}

	private JTable buildTableFromEntrySheet(EntrySheet sheet) {
		JTable table = new JTable();

		// ---- table1 ----
		table.setModel(new DefaultTableModel(new String[] { "O", "Prompt", "[Device]", "Current Value", "Confirm" }, 0) {
			Class<?>[] columnTypes = new Class<?>[] { Object.class, String.class, String.class, Double.class,
					Double.class };

			@Override
			public Class<?> getColumnClass(int columnIndex) {
				return columnTypes[columnIndex];
			}

			boolean[] columnEditable = new boolean[] { false, false, false, false, true };

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
			cm.getColumn(1).setPreferredWidth(50);
			cm.getColumn(2).setPreferredWidth(50);
			cm.getColumn(3).setPreferredWidth(50);
			cm.getColumn(4).setPreferredWidth(50);
		}

		return table;
	}

	private void commitActionPerformed(ActionEvent e) {
		int idx = tabber.getSelectedIndex();
		if (idx < 0) {
			return; // shouldn't happen?
		}
		String formName = tabber.getTitleAt(idx);
		JTable table = tables.get(idx);
		Class<? extends PersistentItem> model = models.get(idx);
		PersistentItem block = ModelUtil.getModelFromDataClass(model);
		String message = "Sending to server";
		try {
			save(formName, table, block);
			message = "Printing";
			// PrintService printer = (PrintService) printerList.getSelectedItem();
			// print(formName, table, printer);
			System.err.println("Send data...skipping print");
		} catch (Exception ex) {
			GuiUtil.showError(message, ex);
		}
	}

	private void save(String formName, JTable table, PersistentItem block) throws IOException {

		GuiUtil.showMessage("FIXME: save not implemented");
		//		timepoint_td = EntryUtil.getTimepointTD();
		//
		//		TimepointWrapper wrapper = (TimepointWrapper) timepointCombo.getSelectedItem();
		//		String tpName = wrapper.getTpName();
		//		TextItem tpItem = (TextItem) block.getItem(timepoint_td.getLocation());
		//		tpItem.setValue(tpName);
		//
		//		for (int row = 0; row < table.getRowCount(); row++) {
		//			// EntryItem item = (EntryItem) table.getValueAt(row, COL_OBJECT );
		//			String key = (String) table.getValueAt(row, COL_KEY);
		//			Double value = (Double) table.getValueAt(row, COL_COMMIT);
		//
		//			// item can't be null
		//			 item = (NumericItem) block.getItem(key);
		//			item.setValue(value);
		//		}
		//
		//		SocketDeviceConfiguration conf = (SocketDeviceConfiguration) server_driver.getConfiguration();
		//		InetAddress server_address = InetAddress.getByName(conf.getHost()); // create
		//																			// an
		//
		//		byte[] sendData = generator.buildNumericsBlock(formName, 0, 0, IppProtos.DevT.DT_ARCHIVE, 0, block);
		//
		//		// BLIND: Hack for the remote entry panel address and port
		//		generator.sendDatagrams(sendData, server_address, conf.getPort());

	}

	private void print(String formName, JTable table, PrintService printer) {
		if (printer == null) {
			GuiUtil.showMessage("Printer not found!");
			return;
		}
		try {
			ConfigurationInfo.setSelectedPrinter(TASK, printer.toString());
		} catch (Exception e1) {
			// we can ignore this error
		}

		HashMap<String, Object> map = new HashMap<String, Object>();

		for (int row = 0; row < table.getRowCount(); row++) {
			// EntryItem item = (EntryItem) table.getValueAt(row, COL_OBJECT );
			String key = (String) table.getValueAt(row, COL_KEY);
			Double value = (Double) table.getValueAt(row, COL_COMMIT);
			map.put(key, value);
		}

		Set<String> params = ref_caps.getKeys();
		if (params != null) {
			for (String param : params) {
				map.put(param, ref_caps.getParam(param));
			}
		}

		map.put("tm", new Date());
		map.put("StudyTime", new Date());
		map.put("form", formName);

		try {
			BarcodePDF417 pdf417 = new BarcodePDF417();
			pdf417.setText("www.java2s.com has some demo for PDF");
			//            Document document = new Document(PageSize.A4, 50, 50, 50, 50);
			//            PdfWriter writer = PdfWriter.getInstance(document, new FileOutputStream("ExampleBarcodePDF417.pdf"));
			//            document.open();
			com.itextpdf.text.Image img = pdf417.getImage();
			Image awt_image = pdf417.createAwtImage(Color.BLACK, Color.WHITE);
			// img.scalePercent(50, 50 * pdf417.getYHeight());
			//            document.add(img);
			//            document.close();
			map.put("barcode", awt_image);
		} catch (Exception e) {
			e.printStackTrace();
		}

		try {
			URL url = new URL("classpath:idea/labels/StudyData.jasper");

			PrintUtil.print(printer, map, url);
		} catch (JRException ee) {
			GuiUtil.showError("study report", ee);
			return;
		} catch (MalformedURLException ee) {
			GuiUtil.showError("study report", ee);
			return;
		} catch (Exception ee) {
			GuiUtil.showError("Could not print label", ee);
			return;
		}

	}

	private void timepointComboActionPerformed(ActionEvent e) {
		TimepointWrapper wrapper = (TimepointWrapper) timepointCombo.getSelectedItem();
		String tmText = wrapper.getTime();
		expectedTime.setText(tmText);
		if (tmText.endsWith("hr")) {
			tmText = tmText.substring(0, tmText.length() - 2);
			int hrs = Integer.parseInt(tmText);
			Calendar cal = Calendar.getInstance();
			cal.setTime(startTime);
			cal.add(Calendar.HOUR_OF_DAY, hrs);
			this.refreshTime.setDate(cal.getTime());
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		DefaultComponentFactory compFactory = DefaultComponentFactory.getInstance();
		panel2 = new JPanel();
		label1 = new JLabel();
		timepointCombo = new JComboBox();
		label2 = new JLabel();
		expectedTime = new JLabel();
		label3 = new JLabel();
		refreshTime = new JDateChooser();
		separator1 = compFactory.createSeparator("Data");
		panel1 = new JPanel();
		tabber = new JTabbedPane();
		buttonPanel = new JPanel();
		printerList = new JComboBox();
		refresh = new JButton();
		commit = new JButton();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"2*(default, $lgap), fill:default:grow, $lgap, default"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default, $lcgap, [100dlu,default], 2*($lcgap, default), $lcgap, [40dlu,default], 2*($lcgap, default)",
				"default"));

			//---- label1 ----
			label1.setText("Timepoint:");
			panel2.add(label1, CC.xy(1, 1));

			//---- timepointCombo ----
			timepointCombo.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					timepointComboActionPerformed(e);
				}
			});
			panel2.add(timepointCombo, CC.xy(3, 1));

			//---- label2 ----
			label2.setText("Expected Time:");
			panel2.add(label2, CC.xy(7, 1));

			//---- expectedTime ----
			expectedTime.setText("text");
			panel2.add(expectedTime, CC.xy(9, 1));

			//---- label3 ----
			label3.setText("Refresh time:");
			panel2.add(label3, CC.xy(11, 1));

			//---- refreshTime ----
			refreshTime.setDateFormatString("MM/dd/yyyy HH:mm");
			panel2.add(refreshTime, CC.xy(13, 1));
		}
		add(panel2, CC.xy(1, 1));
		add(separator1, CC.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, [default,800dlu]:grow",
				"fill:default:grow"));
			panel1.add(tabber, CC.xy(3, 1));
		}
		add(panel1, CC.xy(1, 5));

		//======== buttonPanel ========
		{
			buttonPanel.setLayout(new FormLayout(
				"default:grow, 2*($lcgap, [50dlu,default])",
				"default"));
			buttonPanel.add(printerList, CC.xy(1, 1));

			//---- refresh ----
			refresh.setText("Refresh");
			refresh.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					refreshActionPerformed(e);
				}
			});
			buttonPanel.add(refresh, CC.xy(3, 1));

			//---- commit ----
			commit.setText("Commit");
			commit.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					commitActionPerformed(e);
				}
			});
			buttonPanel.add(commit, CC.xy(5, 1));
		}
		add(buttonPanel, CC.xy(1, 7));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel2;
	private JLabel label1;
	private JComboBox timepointCombo;
	private JLabel label2;
	private JLabel expectedTime;
	private JLabel label3;
	private JDateChooser refreshTime;
	private JComponent separator1;
	private JPanel panel1;
	private JTabbedPane tabber;
	private JPanel buttonPanel;
	private JComboBox printerList;
	private JButton refresh;
	private JButton commit;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {

		if (StreamID.CAPABILITIES.equals(sid)) {
			// some housekeeping is taken care of by the driver...this can be ignored
			log.error("FIXME: capabilities block");
		} else if (StreamID.MEASUREMENT.equals(sid)) {
			String name = "DEADBEEF";
			if (source != null) {
				RpDevice conf = source.getConfiguration();
				if (conf != null) {
					name = conf.getName();
				}
			}
			fillValues(name, item, item.getMetrics());

		} else {
			log.error("ignoring event event");
		}
	}

	@Override
	public void clear() {
		// hmm...well...ignore for now
	}

	@Override
	public void autoscale() {
		// ignore
	}

	@Override
	public void tick() {
		// nothing for now
	}

	@Override
	public StreamProducer[] getSignalProducers() {
		// TODO Auto-generated method stub
		return null;
	}

}
