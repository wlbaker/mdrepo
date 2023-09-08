package idea.display.elegant;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class DTest
{
	public static void main(String[] args) 
	{
	    JFrame win = new JFrame("DTest!");
	    win.getContentPane().setLayout(new BorderLayout());
	    win.setSize(400,140);

	    JPanel panel = new JPanel(new FlowLayout());
	    panel.setBackground(new Color(200,200,255));
	    win.getContentPane().add(panel, BorderLayout.CENTER);

	    DisplayKnob ts0;
	    DisplayKnob ts1;
	    final JLabel jla = new JLabel("Volume: 0");
	    panel.add(ts0 = new DisplayKnob());
	    panel.add(ts1 = new DisplayKnob());
	    panel.add(jla );
	    ts0.setValue((float)1.0);
	    ts0.addChangeListener(new ChangeListener() {
		    public void stateChanged(ChangeEvent e) {
			DisplayKnob t = (DisplayKnob) e.getSource();
			int vol;
			jla.setText("Volume: " + (vol = (int)(15 * t.getValue())));
		    }
		});
	    win.setVisible( true );
	}
}


