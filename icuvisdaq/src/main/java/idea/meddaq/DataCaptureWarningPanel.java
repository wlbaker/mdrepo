/*
 * Created by JFormDesigner on Wed Apr 13 15:35:42 CDT 2016
 */

package idea.meddaq;

import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

import javax.swing.*;
import com.jgoodies.forms.factories.*;
import com.jgoodies.forms.layout.*;

import idea.GuiUtil;

/**
 * @author User #1
 */

class CompositeIcons implements Icon {

	private ArrayList<Icon> icons = new ArrayList();
	private ArrayList<Integer> listX = new ArrayList();
	private ArrayList<Integer> listY = new ArrayList();

	public void addIcon(Icon icon, int x, int y) {
		icons.add(icon);
		listX.add(x);
		listY.add(y);
	}

	@Override
	public void paintIcon(Component c, Graphics g, int i, int i1) {
		for (int j = 0; j < icons.size(); j++) {
			icons.get(j).paintIcon(c, g, listX.get(j), listY.get(j));
		}
	}

	@Override
	public int getIconWidth() {
		return 40;
	}

	@Override
	public int getIconHeight() {
		return 40;
	}

}

public class DataCaptureWarningPanel extends JPanel {
	int dismiss_count = 0;
	CompositeIcons icon;
	Icon warningIcon;
	
	public DataCaptureWarningPanel() {
		initComponents();

		icon = new CompositeIcons();
		
		icon.addIcon( warningIcon = UIManager.getIcon("OptionPane.warningIcon"), 0, 0);
		warning.setIcon(icon);
		warning.setText("");
		
		confirmMessage.setVisible(false);
	}

	private void sleepActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog(this);
	}

	private void dismissActionPerformed(ActionEvent e) {
		if( dismiss_count == 0 ) {
			confirmMessage.setBackground(Color.RED);
			confirmMessage.setOpaque(true);
			confirmMessage.setVisible(true);
			
			icon.addIcon( warningIcon, 10, 10);
			warning.repaint();
			
			dismiss_count++;
		} else {
			MedDAQFrame.getInstance().setNotCapturingTimeout( -1 );
			GuiUtil.closeDialog(this);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY //GEN-BEGIN:initComponents
		panel1 = new JPanel();
		warning = new JLabel();
		label1 = new JLabel();
		confirmMessage = new JLabel();
		buttonPanel = new JPanel();
		dismiss = new JButton();
		sleep = new JButton();

		//======== this ========
		setLayout(new FormLayout(
			"240dlu",
			"fill:160dlu, $rgap, default"));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"30dlu, $lcgap, default:grow, $lcgap, 30dlu",
				"default, $lgap, default:grow, $lgap, default, $lgap, [50dlu,default], $lgap, default:grow"));

			//---- warning ----
			warning.setText("WARNING");
			panel1.add(warning, CC.xy(1, 3));

			//---- label1 ----
			label1.setText("<html>Data capture not active.  Options are to warn again in 10 minutes or dismiss the alarm.");
			label1.setBorder(Borders.DLU7);
			panel1.add(label1, CC.xy(3, 5));

			//---- confirmMessage ----
			confirmMessage.setText("<html><center>Press Dismiss a second time to confirm dismissal and disabling of the alarm.");
			confirmMessage.setBorder(Borders.DLU14);
			panel1.add(confirmMessage, CC.xy(3, 7));
		}
		add(panel1, CC.xy(1, 1));

		//======== buttonPanel ========
		{
			buttonPanel.setLayout(new FormLayout(
				"[50dlu,default], $lcgap, default:grow, $lcgap, [50dlu,default]",
				"default"));

			//---- dismiss ----
			dismiss.setText("Dismiss");
			dismiss.addActionListener(e -> dismissActionPerformed(e));
			buttonPanel.add(dismiss, CC.xy(1, 1));

			//---- sleep ----
			sleep.setText("Sleep");
			sleep.addActionListener(e -> sleepActionPerformed(e));
			buttonPanel.add(sleep, CC.xy(5, 1));
		}
		add(buttonPanel, CC.xy(1, 3));
		// JFormDesigner - End of component initialization //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY //GEN-BEGIN:variables
	private JPanel panel1;
	private JLabel warning;
	private JLabel label1;
	private JLabel confirmMessage;
	private JPanel buttonPanel;
	private JButton dismiss;
	private JButton sleep;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
