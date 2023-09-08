/*
 * Created by JFormDesigner on Thu Mar 02 09:30:17 CST 2017
 */

package idea.tsoffline.canvas;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.GuiUtil;
import idea.tsoffline.AppModel;
import idea.tsoffline.HPPathLayer;
import idea.tsoffline.HPSplitableLayer;

/**
 * @author User #1
 */
public class UpdatePanel extends JPanel implements Runnable {

	Thread t;
	private TsBaseCanvas canvas;

	public UpdatePanel( TsBaseCanvas canvas) {
		initComponents();

		this.canvas = canvas;
		DefaultTableModel model = (DefaultTableModel) table1.getModel();
		model.setRowCount(0);
	}

	private void exitButtonActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void updateButtonActionPerformed(ActionEvent e) {

		if (t == null) {
			updateButton.setEnabled(false);
			exitButton.setEnabled(false);
			t = new Thread(this);
			t.setName("Feature-Updater");
			t.start();
		}
	}

	@Override
	public void run() {

		String[] obsolete_keys = new String[] { "data_y", "centroid_x", "centroid_y", "moment_x", "moment_y" };

		DefaultTableModel model = (DefaultTableModel) table1.getModel();

		model.setRowCount(0);
		List<HPSplitableLayer> annos = canvas.getAnnotationModel();
		
		if (annos != null) {

			int tot_fixed = 0;
			int tot_removed = 0;
			int tot_zeros = 0;
			int tot_duplicates = 0;
			int tot_data_y = 0;
			int tot_oob = 0;
			for (HPSplitableLayer splits : annos) {
				for (Object x : splits.getChildrenReference()) {
					HPPathLayer anno = (HPPathLayer) x;
					int fixed = 0;
					int oob = 0;
					int removed = 0;
					int zeros = 0;
					int duplicates = 0;
					int data_y = 0;

					@SuppressWarnings("unchecked")
					List<PNode> childs = anno.getChildrenReference();
					if (childs == null || childs.size() == 0) {
						continue;
					}
					double prev_x = Double.NaN;
					Iterator<PNode> it = childs.iterator();
					while (it.hasNext()) {
						PNode node = it.next();
						if (node.getX() - prev_x < -0.001) {
							oob++; // out of order!
						}
					}

					if (oob > 0) {
						tot_oob += oob;
						PLayer layer = anno;
						@SuppressWarnings("unchecked")
						List<PNode> list = layer.getChildrenReference();
						Collections.sort(list, new Comparator<PNode>() {

							@Override
							public int compare(PNode o1, PNode o2) {
								return Double.compare(o1.getX(), o2.getX());
							}
						});
					}
					it = childs.iterator();
					while (it.hasNext()) {
						String prev_txt = "NONE";
						prev_x = Double.NaN;

						PNode node = it.next();
						for (String key : obsolete_keys) {
							Object o = node.getAttribute(key);
							// remove data_y attribute
							if (o != null) {
								node.addAttribute(key, null);
								data_y++;
							}
						}
						// remove nodes at 0.0
						if (node.getX() == 0.0) {
							it.remove();
							zeros++;
							continue;
						}
						String txt = (String) node.getAttribute("txt");
						if ("_Pk-Pk".equals(txt)) {
							it.remove();
							removed++;
							continue;
						}
						// cound out-of-order
						// remove duplicates
						if (Math.abs(node.getX() - prev_x) < 0.010) {
							if (txt == prev_txt || txt.equals(prev_txt)) {
								// both are null
								it.remove();
								duplicates++;
								continue;
							}
						}
						prev_txt = txt;
						prev_x = node.getX();
					}

					PNode prev = null;
					PNode curr = null;
					for (PNode last : childs) {
						if (curr != null) {
							double y0 = curr.getY();
							AppModel.updateAnnotationData(prev, curr, last);
							double y1 = curr.getY();
							if (y0 != y1) {
								fixed++;
							}
						}
						prev = curr;
						curr = last;
					}

					tot_data_y += data_y;
					tot_duplicates += duplicates;
					tot_removed += removed;
					tot_zeros += zeros;
					tot_fixed += fixed;
					model.addRow(
							new Object[] { anno, x, oob, data_y, duplicates, removed, zeros, fixed });
				}
				model.addRow(new Object[] { null, "Total Adjustments: ", tot_oob, tot_data_y, tot_duplicates,
						tot_removed, tot_zeros, tot_fixed });
				int tot = tot_oob + tot_data_y + tot_duplicates + tot_removed + tot_zeros + tot_fixed;
				if (tot > 0)
					AppModel.setDirty(true);
			}
		}

		exitButton.setEnabled(true);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		scrollPane1 = new JScrollPane();
		table1 = new JTable();
		panel1 = new JPanel();
		updateButton = new JButton();
		exitButton = new JButton();

		// ======== this ========
		setLayout(new FormLayout("default:grow", "default, $lgap, default:grow, $lgap, default"));

		// ======== scrollPane1 ========
		{
			scrollPane1.setPreferredSize(new Dimension(652, 227));

			// ---- table1 ----
			table1.setModel(new DefaultTableModel(
					new Object[][] { { null, null, null, null, null, null, null, null },
							{ null, null, null, null, null, null, null, null }, },
					new String[] { "O", "Feature", "OOB", "Obsolete Keys", "Duplicates", "Obsolete Nodes", "Zeros",
							"Value Adj" }));
			{
				TableColumnModel cm = table1.getColumnModel();
				cm.getColumn(0).setMinWidth(1);
				cm.getColumn(0).setMaxWidth(1);
				cm.getColumn(0).setPreferredWidth(1);
				cm.getColumn(1).setPreferredWidth(120);
				cm.getColumn(2).setPreferredWidth(60);
				cm.getColumn(3).setPreferredWidth(60);
				cm.getColumn(4).setPreferredWidth(60);
				cm.getColumn(5).setPreferredWidth(60);
				cm.getColumn(6).setPreferredWidth(60);
				cm.getColumn(7).setPreferredWidth(60);
			}
			scrollPane1.setViewportView(table1);
		}
		add(scrollPane1, CC.xy(1, 3));

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("default:grow, 2*($lcgap, [50dlu,default])", "default"));

			// ---- updateButton ----
			updateButton.setText("Update");
			updateButton.addActionListener(e -> updateButtonActionPerformed(e));
			panel1.add(updateButton, CC.xy(3, 1));

			// ---- exitButton ----
			exitButton.setText("Exit");
			exitButton.addActionListener(e -> exitButtonActionPerformed(e));
			panel1.add(exitButton, CC.xy(5, 1));
		}
		add(panel1, CC.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JScrollPane scrollPane1;
	private JTable table1;
	private JPanel panel1;
	private JButton updateButton;
	private JButton exitButton;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
