/*
 * Created by JFormDesigner on Sat Jan 29 19:09:21 CST 2011
 */

package idea.tsoffline.prefs;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;

import javax.swing.ComboBoxModel;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.gui.ColorListCellRenderer;
import idea.ts.TsoPrefs;
import idea.tsoffline.AppUtil;
import idea.tsoffline.ColorManager;
import idea.tsoffline.codes_editor.CodesPanel;
import idea.tsoffline.codes_editor.SubstitutionsPanel;

/**
 * @author User #1
 */
public class PreferencesPanel extends JPanel {
	private CodesPanel codesPanel;
	private boolean do_ok;
	private TsoPrefs prefs;
	private SubstitutionsPanel subsPanel;

	public PreferencesPanel(TsoPrefs prefs) {
		initComponents();

		this.prefs = prefs;
		subsPanel = new SubstitutionsPanel();
		tabber.insertTab("Substitutions", null, subsPanel, null, 0);
		
		codesPanel = new CodesPanel();
		tabber.insertTab("Codes", null, codesPanel, null, 0);

		tabber.setSelectedIndex(0); // floats with inserts, set back to first tab

		indicatorColor.setRenderer(new ColorListCellRenderer());
		ComboBoxModel<Color> model = new DefaultComboBoxModel<Color>(ColorManager.getColors());
		indicatorColor.setModel(model);

		refresh();
	}

	private void refresh() {
		Color[] colors = ColorManager.getColors();
		String s = prefs.getAttribute("indicatorColorIndex");
		if (s != null) {
			int indicatorColorIndex = Integer.parseInt(s);
			indicatorColor.setSelectedIndex(indicatorColorIndex);
		}
		s = prefs.getAttribute("showStudyPhase");
		boolean b = AppUtil.stringAsBoolean(s, false);
		this.displayStudyPhase.setSelected(b);
	}

	private void okActionPerformed(ActionEvent e) {
		do_ok = true;
		prefs.putAttribute("indicatorColorIndex", "" + indicatorColor.getSelectedIndex());
		prefs.putAttribute("showStudyPhase", "" + displayStudyPhase.isSelected());

		codesPanel.panelToModel(e);
		cancelActionPerformed(e);
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	public boolean isOk() {
		return do_ok;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		tabber = new JTabbedPane();
		panel1 = new JPanel();
		label3 = new JLabel();
		indicatorColor = new JComboBox<>();
		label4 = new JLabel();
		displayStudyPhase = new JCheckBox();
		label6 = new JLabel();
		label5 = new JLabel();
		panel3 = new JPanel();
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel4 = new JPanel();
		ok = new JButton();
		cancel = new JButton();

		// ======== this ========
		setLayout(new FormLayout("default:grow", "fill:default:grow, $lgap, default"));

		// ======== tabber ========
		{

			// ======== panel1 ========
			{
				panel1.setLayout(new FormLayout("default, $lcgap, [50dlu,default], $lcgap, default",
						"3*(default, $lgap), default"));

				// ---- label3 ----
				label3.setText("Cursor/indicator Color:");
				panel1.add(label3, CC.xy(1, 1));
				panel1.add(indicatorColor, CC.xy(3, 1));

				// ---- label4 ----
				label4.setText("Study Phase Display in Canvas:");
				panel1.add(label4, CC.xy(1, 3));

				// ---- displayStudyPhase ----
				displayStudyPhase.setText("Yes");
				panel1.add(displayStudyPhase, CC.xy(3, 3));

				// ---- label6 ----
				label6.setText("Cursor/editor width:");
				panel1.add(label6, CC.xy(1, 5));

				// ---- label5 ----
				label5.setText("How narrow can domain be before R-indicators disappear:");
				panel1.add(label5, CC.xy(1, 7));
			}
			tabber.addTab("Editor", panel1);

			// ======== panel3 ========
			{
				panel3.setLayout(new BorderLayout());

				// ======== scrollPane1 ========
				{

					// ---- table1 ----
					table1.setModel(
							new DefaultTableModel(
									new Object[][] { { null, "Editor: zoom in", null },
											{ null, "Editor: zoom out", null }, { null, null, null }, },
									new String[] { null, "Function", "Shortcut" }) {
								boolean[] columnEditable = new boolean[] { false, false, true };

								@Override
								public boolean isCellEditable(int rowIndex, int columnIndex) {
									return columnEditable[columnIndex];
								}
							});
					{
						TableColumnModel cm = table1.getColumnModel();
						cm.getColumn(0).setResizable(false);
						cm.getColumn(1).setPreferredWidth(200);
						cm.getColumn(2).setPreferredWidth(50);
					}
					scrollPane1.setViewportView(table1);
				}
				panel3.add(scrollPane1, BorderLayout.CENTER);
			}
			tabber.addTab("Shortcuts", panel3);
		}
		add(tabber, CC.xy(1, 1));

		// ======== panel4 ========
		{
			panel4.setLayout(new FormLayout("default:grow, 2*($lcgap, [50dlu,default])", "default"));

			// ---- ok ----
			ok.setText("Ok");
			ok.addActionListener(e -> okActionPerformed(e));
			panel4.add(ok, CC.xy(3, 1));

			// ---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(e -> cancelActionPerformed(e));
			panel4.add(cancel, CC.xy(5, 1));
		}
		add(panel4, CC.xy(1, 3));
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	private JTabbedPane tabber;
	private JPanel panel1;
	private JLabel label3;
	private JComboBox<Color> indicatorColor;
	private JLabel label4;
	private JCheckBox displayStudyPhase;
	private JLabel label6;
	private JLabel label5;
	private JPanel panel3;
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel4;
	private JButton ok;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
