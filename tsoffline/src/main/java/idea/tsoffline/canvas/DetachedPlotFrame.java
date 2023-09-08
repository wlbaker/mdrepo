/*
 * Created by JFormDesigner on Sat Apr 22 22:24:14 CDT 2017
 */

package idea.tsoffline.canvas;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
public class DetachedPlotFrame extends JDialog {
	private JComponent plot;

	public DetachedPlotFrame(JFrame owner, String title, JComponent comp) {
		super(owner, title);
		initComponents();

		this.plot = comp;
		this.setModal(false);
	}

	private void button1024ActionPerformed(ActionEvent e) {
		setPlotSize(new Dimension(1024, 768));
	}

	private void setPlotSize(Dimension d) {
		this.setMaximumSize(d);
		this.setMinimumSize(d);
		this.setPreferredSize(d);
		if( d == null ) {
			this.setSize(400,300);
		} else {
			this.setSize(d);
		}
		doLayout();
	}

	private void button800ActionPerformed(ActionEvent e) {
		setPlotSize(new Dimension(800, 600));
	}

	private void button600ActionPerformed(ActionEvent e) {
		setPlotSize(new Dimension(600, 480));
	}

	private void buttonVariableActionPerformed(ActionEvent e) {
		setPlotSize(null);
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		button1024 = new JButton();
		button800 = new JButton();
		button600 = new JButton();
		buttonVariable = new JButton();

		// ======== this ========
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		// ======== panel1 ========
		{
			panel1.setLayout(new FormLayout("3*(default, $lcgap), default", "default"));

			// ---- button1024 ----
			button1024.setText("1024x768");
			button1024.addActionListener(e -> button1024ActionPerformed(e));
			panel1.add(button1024, CC.xy(1, 1));

			// ---- button800 ----
			button800.setText("800x600");
			button800.addActionListener(e -> button800ActionPerformed(e));
			panel1.add(button800, CC.xy(3, 1));

			// ---- button600 ----
			button600.setText("600x480");
			button600.addActionListener(e -> button600ActionPerformed(e));
			panel1.add(button600, CC.xy(5, 1));

			// ---- buttonVariable ----
			buttonVariable.setText("Variable");
			buttonVariable.addActionListener(e -> buttonVariableActionPerformed(e));
			panel1.add(buttonVariable, CC.xy(7, 1));
		}
		contentPane.add(panel1, BorderLayout.SOUTH);
		pack();
		setLocationRelativeTo(getOwner());
		// JFormDesigner - End of component initialization
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel1;
	private JButton button1024;
	private JButton button800;
	private JButton button600;
	private JButton buttonVariable;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
