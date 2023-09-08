package idea.analysis.ventilator;

import java.awt.Component;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.JFrame;

import org.rosuda.javaGD.GDInterface;
import org.rosuda.javaGD.JGDBufferedPanel;

public class AnalRGuiConsole extends GDInterface implements WindowListener {

    JFrame f;
    
    @Override
	public void gdOpen(double w, double h) {
        if (f!=null) gdClose();
        f = new JFrame("JavaGD Example");
        f.addWindowListener(this);      
        c = new JGDBufferedPanel(w, h);
        f.getContentPane().add((Component) c);
        f.pack();
        f.setVisible(true);
    }
    
    @Override
	public void gdClose() {
        super.gdClose();
        if (f!=null) {
            c=null;
            f.removeAll();
            f.dispose();
            f=null;
        }
    }

    /** listener response to "Close" - effectively invokes <code>dev.off()</code> on the device */
    @Override
	public void windowClosing(WindowEvent e) {
        if (c!=null) executeDevOff();
    }
    @Override
	public void windowClosed(WindowEvent e) {}
    @Override
	public void windowOpened(WindowEvent e) {}
    @Override
	public void windowIconified(WindowEvent e) {}
    @Override
	public void windowDeiconified(WindowEvent e) {}
    @Override
	public void windowActivated(WindowEvent e) {}
    @Override
	public void windowDeactivated(WindowEvent e) {}
}