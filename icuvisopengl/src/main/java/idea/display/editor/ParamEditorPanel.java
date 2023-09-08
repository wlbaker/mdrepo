/*
 * Created by JFormDesigner on Tue Jul 28 12:10:36 CDT 2015
 */

package idea.display.editor;

import java.awt.*;
import icuInterface.RpUtil;
import idea.display.BandLayout;
import idea.display.DisplayUtil;
import idea.display.FieldData;
import idea.display.ParameterLayout;
import idea.intf.DataTyp;
import idea.message.StreamID;
import idea.model.DisplayConfig;
import idea.schema.rp.RpDevice;
import idea.schema.rp.RpLinearUnit;
import idea.schema.rp.RpMetric;
import idea.schema.rp.RpStream;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.List;

import javax.swing.DefaultCellEditor;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableModel;

import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.display.gl.GLInstrumentDisplay;
import idea.display.gl.GLParameterPainter;
import idea.display.gl.ParamDataEx;
import idea.gui.RpMetricListCellRenderer;
import idea.gui.RpMetricTableCellRenderer;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class ParamEditorPanel extends JPanel implements TableModelListener, PropertyChangeListener,
		ListSelectionListener {
	protected static final int FORMAT_COL = 0;
	protected static final int SETUP_COL = 0;
	private static final int METRIC_COL = 2;
	private static final int COLOR_COL = 3;

	private GLInstrumentDisplay form;
	private GLInstrumentDisplay demo;
	
	boolean debug = false;

	private RpMetric[] metrics;
	private ParameterLayout demo_layout;
	private ParameterLayout display_format;
	// private ParameterLayout demo_pbox;

	public ParamEditorPanel(GLInstrumentDisplay form) {

		/*
		 * I allow the form to be null for disconnected testing purposes
		 */
		this.form = form;
		initComponents();

		/*
		 * create the demo form
		 */
		this.demo = new GLInstrumentDisplay(createDemoConfig());
		demo.setDisplay(createDemoDisplay(), true, false);
		demoPanel.add(demo, CC.xy(1, 1));

		if (form != null) {

			/*
			 * get metrics
			 */
			RpDevice conf = form.getCapabilities();

			RpStream stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
			if (stream != null) {
				List<RpMetric> metrics_list = stream.getMetric();
				if (metrics_list != null) {
					metrics = new RpMetric[metrics_list.size()];
					metrics_list.toArray(metrics);
				}
			}
		}

		if (metrics == null) {
			metrics = new RpMetric[0];
		}

		boxName.setText("");

		initFormatsTable();
		initSignalTable();

		refreshFieldTable();

		formatTable.setEnabled(false);
		formatTable.setForeground(Color.LIGHT_GRAY);
		signalTable.setEnabled(false);
	}

	private RpDevice createDemoConfig() {
		RpDevice dev = new RpDevice();
		RpUtil.addMetric(dev, StreamID.MEASUREMENT, //
				new RpMetric("d1", "D1", "DMeasurement 1", RpLinearUnit.unit, DataTyp.DOUBLE_TYP));
		RpUtil.addMetric(dev, StreamID.MEASUREMENT, //
				new RpMetric("d2", "D2", null, RpLinearUnit.unit, DataTyp.DOUBLE_TYP));
		RpUtil.addMetric(dev, StreamID.MEASUREMENT, //
				new RpMetric("d3", null, null, RpLinearUnit.unit, DataTyp.DOUBLE_TYP));
		RpUtil.addMetric(dev, StreamID.MEASUREMENT, //
				new RpMetric("i1", "I1", "IMeasurement 1", RpLinearUnit.unit, DataTyp.INT_TYP));
		RpUtil.addMetric(dev, StreamID.MEASUREMENT, //
				new RpMetric("i2", "I2", null, RpLinearUnit.unit, DataTyp.INT_TYP));
		RpUtil.addMetric(dev, StreamID.MEASUREMENT, //
				new RpMetric("i3", null, null, RpLinearUnit.unit, DataTyp.INT_TYP));
		return dev;
	}

	private DisplayConfig createDemoDisplay() {
		DisplayConfig display = new DisplayConfig();
		FieldData[] params = new FieldData[3];
		params[0] = new FieldData("d1", (byte) 0);
		params[1] = new FieldData("d2", (byte) 0);
		params[2] = new FieldData("i2", (byte) 0);

		demo_layout = new ParameterLayout((byte) 0, (byte) 0, (byte) 0, params);
		display.addParamBox(demo_layout);
		display.setVertPboxes((short) 0);
		return display;
	}

	private void initFormatsTable() {

		DefaultTableModel model = (DefaultTableModel) formatTable.getModel();
		model.setRowCount(0);

		for (String name : DisplayUtil.getFormatNames()) {
			ParameterLayout format = DisplayUtil.getFormatByName(name);
			int n_fields = format.getFieldCount();
			model.addRow(new Object[] { format, name, n_fields });
		}

		formatTable.getSelectionModel().addListSelectionListener(this);
	}

	private void initSignalTable() {
		TableColumn col = signalTable.getColumnModel().getColumn(COLOR_COL);
		GuiUtil.initColorColumn(col, DisplayUtil.getColors());

		col = signalTable.getColumnModel().getColumn(METRIC_COL);
		JComboBox<RpMetric> comboBox = new JComboBox<RpMetric>(metrics);
		col.setCellEditor(new DefaultCellEditor(comboBox));
		comboBox.setRenderer(new RpMetricListCellRenderer());

		col.setCellRenderer(new RpMetricTableCellRenderer());

		DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
		model.setRowCount(0);
		model.addTableModelListener(this);

	}

	/*
	 * triggered from the formatTable by changes to selection
	 */
	@Override
	public void valueChanged(ListSelectionEvent e) {
		if( e.getValueIsAdjusting() ) {
			return;
		}
		
		Object src = e.getSource();
		if (src == formatTable.getSelectionModel()) {
			int row = formatTable.getSelectedRow();
			byte format = 0;
			if (row < 0) {
				demo_layout = null;
			} else {
				demo_layout = (ParameterLayout) formatTable.getValueAt(row, FORMAT_COL);
				format = demo_layout.getFormat();
			}

			// update demo
			DisplayConfig demo_display = demo.getDisplay();
			List<ParameterLayout> boxes = demo_display.getParameterBoxs();
			demo_layout = boxes.get(0); // must exist...its the only one
			demo_layout.setFormat(format);
			if( display_format != null ) {
				demo_layout.fields = display_format.fields;
			}
			demo.setDisplay(demo_display, true, true);
			
			// int cidx = 1;
			for( FieldData field : demo_layout.fields ) {
				// field.setForeground( (byte) cidx++ );
				String loc = field.getLoc();
				GLParameterPainter painter = demo.findParameterPainter( loc );
				if( painter == null ) {
					log.error("no painter for field: " + loc );
				} else {
					painter.setValue( loc, loc );
				}
			}
			demo.repaint();

			// show the fields
			refreshFieldTable();
		}
	}

	/*
	 * triggered from the signalTable by changes
	 */
	
	@Override
	public void tableChanged(TableModelEvent tme) {
		// Object src = tme.getSource();
		
		signalTableChanged(tme);
			// } else if (src == formatTable) {
			// formatTableChanged(tme);
		demo.repaint();
	}

	public void signalTableChanged(TableModelEvent tme) {
		if (tme.getType() == TableModelEvent.UPDATE) {
			int row_num = tme.getFirstRow();
			int col_num = tme.getColumn();
			Object val = signalTable.getValueAt(row_num, col_num);
			System.out.println(row_num + ", " + col_num + "value: " + val);

			RpMetric metric = (RpMetric) signalTable.getValueAt(row_num, METRIC_COL);
			ParamDataEx pdx = (ParamDataEx)signalTable.getValueAt(row_num, SETUP_COL);
			FieldData ref_field = (FieldData)pdx.getPdat();
			
			FieldData disp_field = null;
			if( display_format != null ) {
				disp_field = display_format.getField(row_num);
			}

			if (col_num == COLOR_COL) {
				Color color = (Color) val;
				byte color_code = DisplayUtil.getDragerFromColor(color);
				if (ref_field != null) {
					ref_field.setForeground(color_code );
				}
				
				if( disp_field != null ) {
					disp_field.setForeground(color_code );
				}
			} else if (col_num == METRIC_COL) {

				if (metric != null) {
					// FieldData setup = current_format.getField(current_field);
					// // WaveformData setup = buildWaveformSetup(metric);
					// Color color = (Color) signalTable.getValueAt(row_num, COLOR_COL);
					// setup.setForeground(DisplayUtil.getDragerFromColor(color));
					//
					// signalTable.setValueAt(setup, row_num, SETUP_COL); // triggers a recursive call
				} else {
					// current_format.setField(current_field, null);
				}

			}
		}
	}

	private void removeBandActionPerformed(ActionEvent e) {
		DisplayConfig display = form.getDisplay();
		// display.getBands().remove( current_field );
		// refresh();
		// displaySelectedBandData( 0 );
		form.setDisplay(display, true, true);
	}

	private void insertBandActionPerformed(ActionEvent e) {
		DisplayConfig display = form.getDisplay();
		display.addBand( new BandLayout((byte)0,(byte)0) );
		display.addParamBox( new ParameterLayout((byte)0,0) );
		// int idx = display.getNumBands();
		// refresh();
		// displaySelectedBandData( idx - 1);
		form.setDisplay(display, true, true);
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		Object src = evt.getSource();
		if (src == form) {
			ParameterLayout old_format = (ParameterLayout) evt.getOldValue();
			if (old_format != null) {
				old_format.setSelected( false );
				formatTable.getSelectionModel().clearSelection();
			}
			display_format = (ParameterLayout) evt.getNewValue();
			updateFormatTableSelection(evt);
			updateDemoPBox(display_format);
			boxName.setText(buildBoxName(display_format));
			
			// } else if (src == formatTable) {
			// updateSignalTable();
		} else if (src == signalTable) {
			// updateField();
		}
	}

	private void updateDemoPBox(ParameterLayout layout) {
		if( demo_layout == null || layout == null ) {
			log.warn("Not expecting NULL layout");
			return;
		}
		demo_layout.setFormat( layout.getFormat() );
		for( int i = 0; i < layout.getFieldCount(); i++ ) {
			String loc = "loc" + i;
			FieldData val = new FieldData( loc, (byte)0);
			demo_layout.setField(i, val);
		}
	}

	private String buildBoxName(ParameterLayout f) {
		if (f == null) {
			return null;
		}

		String orientation = (f.getOrientation() == 0) ? "Horizontal" : "Vertical";

		return orientation + " [" + f.getRow() + "," + f.getColumn() + "] L" + (int) f.getFormat();
	}

	private void updateFormatTableSelection(PropertyChangeEvent evt) {
		if (display_format == null) {
			clear();
		} else {
			formatTable.setEnabled(true);
			formatTable.setForeground(Color.WHITE);
			display_format.setSelected(true);

			TableModel model = formatTable.getModel();
			for (int row = 0; row < model.getRowCount(); row++) {
				ParameterLayout format = (ParameterLayout) formatTable.getValueAt(row, FORMAT_COL);
				if (format.getFormat() == display_format.getFormat()) {
					formatTable.getSelectionModel().setSelectionInterval(row, row);
					break;
				}
			}
		}
	}

	public void refreshFieldTable() {

		signalTable.getModel().removeTableModelListener( this );
		
		if (signalTable.isEditing())
			signalTable.getCellEditor().stopCellEditing();
		
		DefaultTableModel model = (DefaultTableModel) signalTable.getModel();
		model.setRowCount(0);

		if (display_format == null && debug == false ) {
			signalTable.setEnabled(false);
			formatTable.setEnabled(false);
			formatTable.setForeground(Color.LIGHT_GRAY);
			return;
		}

		if (demo_layout == null) {
			return;
		}

		if (metrics == null) {
			return;
		}

		RpStream stream = null;
		if (form != null) {
			RpDevice conf = form.getCapabilities();
			stream = RpUtil.getStream(conf, StreamID.MEASUREMENT);
		}

		int n_fields = demo.getPDXCount( 0 ); // _layout.getFieldCount();

		for (int field_idx = 0; field_idx < n_fields; field_idx++) {

			String fieldName = "Field " + (field_idx + 1);

			ParamDataEx pdx = demo.getPDX( 0, field_idx );
			/*
			 * Show the display_format's field info if it matches the demo
			 * format ...otherwise just show the demo field info
			 */
			FieldData field = pdx.getPdat(); // null;
			//if (display_format != null && demo_layout.getFormat() == display_format.getFormat()) {
			//	field = display_format.getField(field_idx);
			//}
			if (field == null) {
				fieldName += "*";
				field = demo_layout.getField(field_idx);
			}

			RpMetric metric = null;
			if (field == null || field.getLoc() == null) {
				// this is ok...just means Loc has not been set
				fieldName = pdx.getName();
				if( fieldName == null || fieldName.trim().length() == 0 ) {
					fieldName = "pdx: " + field_idx;
				}
			} else {
				metric = RpUtil.getMetricFromStream(stream, field.getLoc());
			}
			if (field == null) {
				model.addRow(new Object[] { pdx, fieldName, null, null });
			} else if (metric == null) {
				model.addRow(new Object[] { pdx, fieldName + " [" + field.getLoc() + "]", null, DisplayUtil.getColorFromDrager(field.getForeground()) });
			} else {
				model.addRow(new Object[] { pdx, fieldName, metric, //
						DisplayUtil.getColorFromDrager(field.getForeground()) } //
				);
			}
		}

		signalTable.getModel().addTableModelListener( this );
		signalTable.setEnabled(true);

	}

	public void clear() {
		if (display_format != null) {
			display_format.setSelected(false);
			display_format = null;
		}

		formatTable.clearSelection(); // funny, that didn't trigger the selection listener

		formatTable.setEnabled(false);
		formatTable.setForeground(Color.LIGHT_GRAY);

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		label1 = new JLabel();
		boxName = new JLabel();
		insertBand = new JButton();
		removeBand = new JButton();
		panel2 = new JPanel();
		scrollPane2 = new JScrollPane();
		formatTable = new JTable();
		fieldSelectionPanel = new JPanel();
		demoPanel = new JPanel();
		scrollPane1 = new JScrollPane();
		signalTable = new JTable();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, default, $rgap, fill:default:grow"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default, $lcgap, default:grow, 2*($lcgap, default), default",
				"default"));

			//---- label1 ----
			label1.setText("  Editing:");
			panel1.add(label1, CC.xy(1, 1));

			//---- boxName ----
			boxName.setText("text");
			panel1.add(boxName, CC.xy(3, 1));

			//---- insertBand ----
			insertBand.setToolTipText("Insert a new row");
			insertBand.setIcon(new ImageIcon(getClass().getResource("/idea/image/process_add.png")));
			insertBand.setMaximumSize(new Dimension(32, 32));
			insertBand.setMinimumSize(new Dimension(32, 32));
			insertBand.setPreferredSize(new Dimension(32, 32));
			insertBand.addActionListener(e -> insertBandActionPerformed(e));
			panel1.add(insertBand, CC.xy(7, 1));

			//---- removeBand ----
			removeBand.setToolTipText("Delete current row");
			removeBand.setIcon(new ImageIcon(getClass().getResource("/idea/image/process_remove.png")));
			removeBand.setMaximumSize(new Dimension(32, 32));
			removeBand.setMinimumSize(new Dimension(32, 32));
			removeBand.setPreferredSize(new Dimension(32, 32));
			removeBand.addActionListener(e -> removeBandActionPerformed(e));
			panel1.add(removeBand, CC.xy(8, 1));
		}
		add(panel1, CC.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"120dlu, $lcgap, 14dlu, $lcgap, default:grow(0.6)",
				"fill:default:grow"));

			//======== scrollPane2 ========
			{
				scrollPane2.setPreferredSize(new Dimension(150, 40));

				//---- formatTable ----
				formatTable.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null, null},
						{null, null, null},
					},
					new String[] {
						"O", "Format", "Fields"
					}
				) {
					Class<?>[] columnTypes = new Class<?>[] {
						Object.class, Object.class, Integer.class
					};
					boolean[] columnEditable = new boolean[] {
						false, false, false
					};
					@Override
					public Class<?> getColumnClass(int columnIndex) {
						return columnTypes[columnIndex];
					}
					@Override
					public boolean isCellEditable(int rowIndex, int columnIndex) {
						return columnEditable[columnIndex];
					}
				});
				{
					TableColumnModel cm = formatTable.getColumnModel();
					cm.getColumn(0).setResizable(false);
					cm.getColumn(0).setMinWidth(1);
					cm.getColumn(0).setMaxWidth(1);
					cm.getColumn(0).setPreferredWidth(1);
					cm.getColumn(1).setPreferredWidth(200);
					cm.getColumn(2).setPreferredWidth(60);
				}
				formatTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
				scrollPane2.setViewportView(formatTable);
			}
			panel2.add(scrollPane2, CC.xy(1, 1));

			//======== fieldSelectionPanel ========
			{
				fieldSelectionPanel.setLayout(null);

				{ // compute preferred size
					Dimension preferredSize = new Dimension();
					for(int i = 0; i < fieldSelectionPanel.getComponentCount(); i++) {
						Rectangle bounds = fieldSelectionPanel.getComponent(i).getBounds();
						preferredSize.width = Math.max(bounds.x + bounds.width, preferredSize.width);
						preferredSize.height = Math.max(bounds.y + bounds.height, preferredSize.height);
					}
					Insets insets = fieldSelectionPanel.getInsets();
					preferredSize.width += insets.right;
					preferredSize.height += insets.bottom;
					fieldSelectionPanel.setMinimumSize(preferredSize);
					fieldSelectionPanel.setPreferredSize(preferredSize);
				}
			}
			panel2.add(fieldSelectionPanel, CC.xy(3, 1));

			//======== demoPanel ========
			{
				demoPanel.setLayout(new FormLayout(
					"default:grow",
					"fill:60dlu, $lgap, fill:default:grow"));

				//======== scrollPane1 ========
				{
					scrollPane1.setPreferredSize(new Dimension(150, 40));

					//---- signalTable ----
					signalTable.setModel(new DefaultTableModel(
						new Object[][] {
							{null, null, null, null},
						},
						new String[] {
							"O", "Field", "Sig", "Color"
						}
					) {
						boolean[] columnEditable = new boolean[] {
							false, false, true, true
						};
						@Override
						public boolean isCellEditable(int rowIndex, int columnIndex) {
							return columnEditable[columnIndex];
						}
					});
					{
						TableColumnModel cm = signalTable.getColumnModel();
						cm.getColumn(0).setResizable(false);
						cm.getColumn(0).setMinWidth(1);
						cm.getColumn(0).setMaxWidth(1);
						cm.getColumn(0).setPreferredWidth(1);
						cm.getColumn(1).setPreferredWidth(80);
						cm.getColumn(2).setPreferredWidth(140);
						cm.getColumn(3).setPreferredWidth(80);
					}
					signalTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
					scrollPane1.setViewportView(signalTable);
				}
				demoPanel.add(scrollPane1, CC.xy(1, 3));
			}
			panel2.add(demoPanel, CC.xy(5, 1));
		}
		add(panel2, CC.xy(1, 5));
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel label1;
	private JLabel boxName;
	private JButton insertBand;
	private JButton removeBand;
	private JPanel panel2;
	private JScrollPane scrollPane2;
	private JTable formatTable;
	private JPanel fieldSelectionPanel;
	private JPanel demoPanel;
	private JScrollPane scrollPane1;
	private JTable signalTable;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public static void main(String[] args) {
		JFrame f = new JFrame();
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ParamEditorPanel editor;
		f.add(editor = new ParamEditorPanel(null));
		f.pack();
		
		editor.debug = true;
		editor.formatTable.setEnabled(true);
		// editor.updateFormatTableSelection(null);
		
		f.setLocationByPlatform(true);
		f.setVisible(true);
	}
}
