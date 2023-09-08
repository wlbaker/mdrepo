/*
 * Created by JFormDesigner on Tue Sep 28 07:22:27 CDT 2010
 */

package idea.tsoffline.vizwiz;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ContainerEvent;
import java.awt.event.ContainerListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.text.DecimalFormat;
import java.util.Vector;

import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;

import org.rosuda.javaGD.JGDBufferedPanel;
import org.rosuda.javaGD.JGDPanel;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.display.ImageSelection;
import idea.gui.WizardPanelInterface;
import idea.r.RCue;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class RPlotterPanel extends JPanel implements WizardPanelInterface {

	DecimalFormat df1 = new DecimalFormat("0.00");
	JGDPanel gdp;

	public RPlotterPanel() {
		initComponents();

		RCue.parent = p;

		p.addContainerListener(new ContainerListener() {

			@Override
			public void componentAdded(ContainerEvent e) {
				Component cc = e.getChild();
				if (cc instanceof JGDBufferedPanel) {

					// the internal mouse handling of JGDPanel is brain dead

					gdp = (JGDPanel) cc;
					cc.removeMouseListener(gdp);
				}
				initPopupMenu(cc);
			}

			@Override
			public void componentRemoved(ContainerEvent e) {
				Container parent = RPlotterPanel.this.getParent();
				System.err.println("FIXME: close the parent: " + parent);
				parent.remove(RPlotterPanel.this);
				// public void windowClosing(WindowEvent e) {
				RCue cue = (RCue) p.getClientProperty("rcue");

				if (cue != null) {
					cue.executeDevOff();
				}
			}

		});

		initPopupMenu(p);

	}

	private void initPopupMenu(Component pp) {

		System.out.println("adding popup listener to: " + pp.getClass());
		pp.addMouseListener(new MouseAdapter() {

			private void showPopup(MouseEvent evt) {
				popupMenu.show(evt.getComponent(), evt.getX(), evt.getY());
			}

			/*
			 * Different L&F environments and OS may trigger popup on either
			 * pressed or released...either way, isPopupTrigger() is set
			 * correctly to the OS and L&F...so rely on it to determine when to
			 * show the popup.
			 */
			@Override
			public void mousePressed(MouseEvent evt) {
				if (evt.isShiftDown())
					return;
				if (evt.isControlDown())
					return;
				if (evt.isPopupTrigger()) {
					showPopup(evt);
				}
			}

			@Override
			public void mouseReleased(MouseEvent evt) {
				if (evt.isShiftDown())
					return;
				if (evt.isControlDown())
					return;
				if (evt.isPopupTrigger()) {
					showPopup(evt);
				}
			}

		});

	}

	private void copyImageActionPerformed(ActionEvent e) {
		// Work around a Sun bug that causes a hang in
		// "sun.awt.image.ImageRepresentation.reconstruct".
		// loadImage(in); // wait for image to load
		int w = p.getWidth();
		int h = p.getHeight();
		int type = BufferedImage.TYPE_INT_RGB;
		BufferedImage out = new BufferedImage(w, h, type);
		Graphics2D g2 = out.createGraphics();
		// g2.translate(0, w);
		// g2.rotate(-Math.PI / 2.0);
		p.paint(g2);
		// g2.drawImage(in, 0, 0, null);
		g2.dispose();

		ImageSelection.copyImageToClipboard(out);

	}

	private void copyDataActionPerformed(ActionEvent e) {

		JGDBufferedPanel bp;

		for (Component cc : p.getComponents()) {
			if (cc instanceof JGDBufferedPanel) {
				bp = (JGDBufferedPanel) cc;
				Vector gdo = bp.getGDOList();

				for (Object v : gdo) {
					System.out.println("v=" + v);
				}
				// ArrayList<double[]> d = getLayerLineDataObsolete(cam, cols,
				// startX, endX);
				// copyListToClipboard(cols, d);
			}
		}
	}

	private void saveAsImageActionPerformed(ActionEvent e) {

		// REngine engine = RUtil.getREngine();
		// dev.set(which=plotter.getDeviceNumber()+1)
		// dev.copy(png,"outputfile.png");
		// dev.off()
	}

	private void saveAsPDFActionPerformed(ActionEvent e) {
		// TODO add your code here
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		p = new JPanel();
		popupMenu = new JPopupMenu();
		copyImage = new JMenuItem();
		copyData = new JMenuItem();
		saveAsImage = new JMenuItem();
		saveAsPDF = new JMenuItem();

		//======== this ========
		setLayout(new FormLayout(
			"[50dlu,default]:grow",
			"default, $lgap, fill:default:grow"));

		//======== p ========
		{
			p.setLayout(new BorderLayout());
		}
		add(p, CC.xy(1, 3));

		//======== popupMenu ========
		{

			//---- copyImage ----
			copyImage.setText("Copy Image");
			copyImage.addActionListener(e -> copyImageActionPerformed(e));
			popupMenu.add(copyImage);

			//---- copyData ----
			copyData.setText("Copy Data");
			copyData.addActionListener(e -> copyDataActionPerformed(e));
			popupMenu.add(copyData);
			popupMenu.addSeparator();

			//---- saveAsImage ----
			saveAsImage.setText("Save as Image...");
			saveAsImage.setEnabled(false);
			saveAsImage.addActionListener(e -> saveAsImageActionPerformed(e));
			popupMenu.add(saveAsImage);

			//---- saveAsPDF ----
			saveAsPDF.setText("Save as PDF...");
			saveAsPDF.setEnabled(false);
			saveAsPDF.addActionListener(e -> saveAsPDFActionPerformed(e));
			popupMenu.add(saveAsPDF);
		}
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel p;
	private JPopupMenu popupMenu;
	private JMenuItem copyImage;
	private JMenuItem copyData;
	private JMenuItem saveAsImage;
	private JMenuItem saveAsPDF;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	@Override
	public void refresh() {
		// TODO Auto-generated method stub

	}

	public RCue getRCue() {
		RCue cue = null;
		
		if( gdp != null ) {
			cue = (RCue) gdp.getClientProperty("rcue");
		}
		if( cue == null ) {
			cue =  (RCue)p.getClientProperty("rcue");
		}
		
		return cue;
	}
	
	@Override
	public void previous() {
		RCue cue = getRCue();
		
		if( cue != null ) {
			cue.executeDevOff();
		}

	}

	@Override
	public boolean next() {
		return true;
	}

	@Override
	public boolean finish() {
		return true;
	}

	public int getDeviceNumber() {
		return gdp.getDeviceNumber();
	}
	
	public JPopupMenu getPopupMenu() {
		return popupMenu;
	}

}
