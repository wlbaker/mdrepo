/*
 * Created by JFormDesigner on Tue Sep 15 17:24:24 CDT 2009
 */

package idea.display;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class ViewableSignalMenu extends JPopupMenu {
	ViewableSignalInterface cs;
	private String loc;
	
	public ViewableSignalMenu( ViewableSignalInterface cs, String loc ) {
		initComponents();
		
		this.cs = cs;
		this.loc = loc;
	}

	private void copyImageActionPerformed(ActionEvent e) {
		cs.copyImageToClipboard();
	}

	private void colorWhiteActionPerformed(ActionEvent e) {
		cs.setPenColor( loc, Color.WHITE );
	}

	private void colorYellowActionPerformed(ActionEvent e) {
		cs.setPenColor( loc, Color.YELLOW );
	}

	private void colorGreenActionPerformed(ActionEvent e) {
		cs.setPenColor( loc, Color.GREEN);
	}

	private void colorRedActionPerformed(ActionEvent e) {
		cs.setPenColor( loc, Color.RED );
	}

	private void zoomInActionPerformed(ActionEvent e) {
		cs.autoScale( loc );
	}

	private void zoomToFitActionPerformed(ActionEvent e) {
		cs.autoScale( loc );
	}

	private void colorBlueActionPerformed(ActionEvent e) {
		cs.setPenColor( loc, new Color(0x66FFCC) );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		copyImage = new JMenuItem();
		zoomIn = new JMenuItem();
		zoomOut = new JMenuItem();
		zoomToFit = new JMenuItem();
		menu1 = new JMenu();
		exportFile = new JMenuItem();
		exportClipboard = new JMenuItem();
		menu2 = new JMenu();
		colorWhite = new JMenuItem();
		colorYellow = new JMenuItem();
		colorGreen = new JMenuItem();
		colorRed = new JMenuItem();
		colorBlue = new JMenuItem();

		//======== this ========

		//---- copyImage ----
		copyImage.setText("Copy");
		copyImage.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				copyImageActionPerformed(e);
			}
		});
		add(copyImage);
		addSeparator();

		//---- zoomIn ----
		zoomIn.setText("Zoom In");
		zoomIn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				zoomInActionPerformed(e);
			}
		});
		add(zoomIn);

		//---- zoomOut ----
		zoomOut.setText("Zoom Out");
		add(zoomOut);

		//---- zoomToFit ----
		zoomToFit.setText("Zoom to Fit");
		zoomToFit.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				zoomToFitActionPerformed(e);
			}
		});
		add(zoomToFit);
		addSeparator();

		//======== menu1 ========
		{
			menu1.setText("Export");

			//---- exportFile ----
			exportFile.setText("Export File");
			menu1.add(exportFile);

			//---- exportClipboard ----
			exportClipboard.setText("Export Clipboard");
			menu1.add(exportClipboard);
		}
		add(menu1);
		addSeparator();

		//======== menu2 ========
		{
			menu2.setText("Color");

			//---- colorWhite ----
			colorWhite.setText("White");
			colorWhite.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					colorWhiteActionPerformed(e);
				}
			});
			menu2.add(colorWhite);

			//---- colorYellow ----
			colorYellow.setText("Yellow");
			colorYellow.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					colorYellowActionPerformed(e);
				}
			});
			menu2.add(colorYellow);

			//---- colorGreen ----
			colorGreen.setText("Green");
			colorGreen.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					colorGreenActionPerformed(e);
				}
			});
			menu2.add(colorGreen);

			//---- colorRed ----
			colorRed.setText("Red");
			colorRed.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					colorRedActionPerformed(e);
				}
			});
			menu2.add(colorRed);

			//---- colorBlue ----
			colorBlue.setText("Blue");
			colorBlue.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					colorBlueActionPerformed(e);
				}
			});
			menu2.add(colorBlue);
		}
		add(menu2);
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JMenuItem copyImage;
	private JMenuItem zoomIn;
	private JMenuItem zoomOut;
	private JMenuItem zoomToFit;
	private JMenu menu1;
	private JMenuItem exportFile;
	private JMenuItem exportClipboard;
	private JMenu menu2;
	private JMenuItem colorWhite;
	private JMenuItem colorYellow;
	private JMenuItem colorGreen;
	private JMenuItem colorRed;
	private JMenuItem colorBlue;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
