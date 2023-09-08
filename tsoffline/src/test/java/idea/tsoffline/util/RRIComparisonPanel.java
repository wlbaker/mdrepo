/*
 * Created by JFormDesigner on Mon Jan 09 14:43:28 CST 2012
 */

package idea.tsoffline.util;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Iterator;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

import org.piccolo2d.PNode;

import com.jgoodies.forms.factories.Borders;
import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.ExcelAdapter;
import idea.tsoffline.model.OfflineSignal;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class RRIComparisonPanel extends JPanel {

	int tm;

	Object q = "?";
	String dcode = "?PT:CAT:FB?";

	public RRIComparisonPanel() {
		initComponents();

		toleranceField.setFormatterFactory(GuiUtil.getIntegerFormatterFactory());

		populateSignals();

		new ExcelAdapter(table1);
		
		fnLabel.setText("?");
		fpLabel.setText("?");
		beatsLabel.setText("?");
	}

	private void populateSignals() {
		GuiUtil.showMessage("FIXME: populateSignals");
//		OfflineSignal [] sigs = SignalUtil.getDerivedSignals();
//		DefaultComboBoxModel model = new DefaultComboBoxModel( sigs );
//		aesopSignal.setModel( model );
//		
//		model = new DefaultComboBoxModel( sigs );
//		manualSignal.setModel( model );
	}

	private void startActionPerformed(ActionEvent e) {
		try {
			_startActionPerformed();
			System.out.println("done!");
		} catch (Exception e1) {
			GuiUtil.showError("RRI Comparison", e1);
		}

	}

	private void _startActionPerformed() throws IOException {
		Integer tol = (Integer) toleranceField.getValue();
		if (tol == null) {
			GuiUtil.showMessage("Invalid tolerance");
			return;
		}

		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);

		OfflineSignal aesop = (OfflineSignal) aesopSignal.getSelectedItem();
		OfflineSignal manual = (OfflineSignal)manualSignal.getSelectedItem();
		
		compareFiles(tol, model, aesop, manual);

	}

	private void compareFiles(int tol, DefaultTableModel model, OfflineSignal aesop_sig, OfflineSignal manual_sig) throws IOException {

		int false_positive = 0;
		int false_negative = 0;
		int manual_beats = 0;

		Iterator<PNode> aesop = aesop_sig.getNodes().iterator();
		Iterator<PNode> manual = manual_sig.getNodes().iterator();
		int m_rri = read_next_rri(manual);
		long m_tot = tm;
		int a_rri = read_next_rri(aesop);
		long a_tot = tm;

		if (m_rri < 0 || a_rri < 0) {
			return;
		}

		
		if( a_rri == 0 ) {
			a_rri = (int) a_tot;
		}
		if( m_rri == 0 ) {
			m_rri = (int) a_tot;
		}
		

		q = "?";
		dcode = "?PT:CAT:FB?";

		while (m_rri > 0 && a_rri > 0) {

			long diff = m_tot - a_tot;
			if (Math.abs(diff) < tol) {
				addRow(model, m_tot, m_rri, a_rri, q, dcode, diff, "");
				m_rri = read_next_rri(manual);
				a_rri = read_next_rri(aesop);
				m_tot += m_rri;
				a_tot += a_rri;
				manual_beats++;
			} else if (a_tot < m_tot) {
				addRow(model, a_tot, null, a_rri, q, dcode, diff, "FP");
				a_rri = read_next_rri(aesop);
				a_tot += a_rri;
				false_positive++;
			} else {
				assert (m_tot < a_tot) : "PROGRAMMER ERROR UNDEFINED STATE";

				addRow(model, m_tot, m_rri, null, null, null, diff, "FN");
				m_rri = read_next_rri(manual);
				m_tot += m_rri;
				false_negative++;
				manual_beats++;
			}
			if (m_rri == 0 || a_rri == 0) {
				return;
			}
			fnLabel.setText("" + false_negative);
			fpLabel.setText("" + false_positive);
			beatsLabel.setText("" + manual_beats);
		}

	}

	private void addRow(DefaultTableModel model, long tm, Integer m_rri, Integer a_rri, Object q, String dcode, long diff, String s) {
		model.addRow(new Object[] { tm, m_rri, a_rri, q, dcode, diff, s });
	}

	private int read_next_rri(Iterator<PNode> ii) throws IOException, NumberFormatException {
		if( ii.hasNext() == false ) {
			return 0;
		}
		PNode node = ii.next();
		
		q = node.getAttribute("q");
		dcode = "" + node.getAttribute("dctor");
		tm = (int) (1000* node.getX());
		int ms = (int) (node.getY() + 0.5);
		
		return ms;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel1 = new JPanel();
		label1 = new JLabel();
		manualSignal = new JComboBox();
		label2 = new JLabel();
		aesopSignal = new JComboBox();
		tabbedPane1 = new JTabbedPane();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel3 = new JPanel();
		label5 = new JLabel();
		panel4 = new JPanel();
		scrollPane2 = new JScrollPane();
		detectorRateTable = new JTable();
		panel2 = new JPanel();
		label3 = new JLabel();
		toleranceField = new JFormattedTextField();
		label4 = new JLabel();
		fnLabel = new JLabel();
		label6 = new JLabel();
		fpLabel = new JLabel();
		label7 = new JLabel();
		beatsLabel = new JLabel();
		start = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setBorder(Borders.DLU4);
		setLayout(new FormLayout(
			"default:grow",
			"default, $lgap, fill:default:grow, $lgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"right:[100dlu,default], $lcgap, default:grow, $lcgap, default",
				"2*(default, $lgap), default"));

			//---- label1 ----
			label1.setText("Manually Verified:");
			panel1.add(label1, cc.xy(1, 1));
			panel1.add(manualSignal, cc.xy(3, 1));

			//---- label2 ----
			label2.setText("AESOP Input File:");
			panel1.add(label2, cc.xy(1, 3));
			panel1.add(aesopSignal, cc.xy(3, 3));
		}
		add(panel1, cc.xy(1, 1));

		//======== tabbedPane1 ========
		{

			//======== scrollPane1 ========
			{
				scrollPane1.setPreferredSize(new Dimension(654, 423));

				//---- table1 ----
				table1.setModel(new DefaultTableModel(
					new Object[][] {
						{null, null, null, null, null, null, null},
						{null, null, null, null, null, null, null},
					},
					new String[] {
						"TM", "Manual", "AESOP", "Quality", "Dctor Code", "Diff", "Result"
					}
				) {
					Class<?>[] columnTypes = new Class<?>[] {
						Integer.class, Object.class, Object.class, Object.class, Object.class, Object.class, Object.class
					};
					boolean[] columnEditable = new boolean[] {
						false, false, false, false, false, false, false
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
				scrollPane1.setViewportView(table1);
			}
			tabbedPane1.addTab("Comparison", scrollPane1);


			//======== panel3 ========
			{
				panel3.setLayout(new BorderLayout());

				//---- label5 ----
				label5.setText("jfreechart histogram");
				panel3.add(label5, BorderLayout.NORTH);
			}
			tabbedPane1.addTab("Quality Histogram", panel3);


			//======== panel4 ========
			{
				panel4.setLayout(new BorderLayout());

				//======== scrollPane2 ========
				{

					//---- detectorRateTable ----
					detectorRateTable.setModel(new DefaultTableModel(
						new Object[][] {
							{null, null, null, null},
							{null, null, null, null},
						},
						new String[] {
							"Detector", "FP", "FN", "Success"
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
					scrollPane2.setViewportView(detectorRateTable);
				}
				panel4.add(scrollPane2, BorderLayout.CENTER);
			}
			tabbedPane1.addTab("Detector Rates", panel4);

		}
		add(tabbedPane1, cc.xy(1, 3));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default, $lcgap, [50dlu,default], $lcgap, right:[30dlu,default], $lcgap, [20dlu,default], $lcgap, right:[30dlu,default], $lcgap, [20dlu,default], $lcgap, default, $lcgap, [30dlu,default], $lcgap, default:grow, $lcgap, default",
				"default"));

			//---- label3 ----
			label3.setText("Tolerance (ms):");
			panel2.add(label3, cc.xy(1, 1));
			panel2.add(toleranceField, cc.xy(3, 1));

			//---- label4 ----
			label4.setText("FN:");
			panel2.add(label4, cc.xy(5, 1));

			//---- fnLabel ----
			fnLabel.setText("text");
			panel2.add(fnLabel, cc.xy(7, 1));

			//---- label6 ----
			label6.setText("FP:");
			panel2.add(label6, cc.xy(9, 1));

			//---- fpLabel ----
			fpLabel.setText("text");
			panel2.add(fpLabel, cc.xy(11, 1));

			//---- label7 ----
			label7.setText("Manually Verified Beats:");
			panel2.add(label7, cc.xy(13, 1));

			//---- beatsLabel ----
			beatsLabel.setText("text");
			panel2.add(beatsLabel, cc.xy(15, 1));

			//---- start ----
			start.setText("Start");
			start.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					startActionPerformed(e);
				}
			});
			panel2.add(start, cc.xy(19, 1));
		}
		add(panel2, cc.xy(1, 5));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel1;
	private JLabel label1;
	private JComboBox manualSignal;
	private JLabel label2;
	private JComboBox aesopSignal;
	private JTabbedPane tabbedPane1;
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel3;
	private JLabel label5;
	private JPanel panel4;
	private JScrollPane scrollPane2;
	private JTable detectorRateTable;
	private JPanel panel2;
	private JLabel label3;
	private JFormattedTextField toleranceField;
	private JLabel label4;
	private JLabel fnLabel;
	private JLabel label6;
	private JLabel fpLabel;
	private JLabel label7;
	private JLabel beatsLabel;
	private JButton start;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
