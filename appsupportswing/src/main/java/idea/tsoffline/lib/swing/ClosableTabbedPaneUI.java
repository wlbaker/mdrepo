package idea.tsoffline.lib.swing;

import java.awt.Color;
import java.awt.Container;
import java.awt.Graphics;
import java.awt.LayoutManager;

import javax.swing.JButton;
import javax.swing.SwingConstants;
import javax.swing.plaf.UIResource;
import javax.swing.plaf.basic.BasicTabbedPaneUI;

/**
 * @author BBaker
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class ClosableTabbedPaneUI extends BasicTabbedPaneUI {

	
	int size=15;
	JButton	btnCloseBox = new CloseBoxButton( ); // "X");
	
	@SuppressWarnings("serial")
	protected class CloseBoxButton extends JButton implements UIResource { 
		// paint methods go here	
		public void paint(Graphics g) {
//			super.paint(g);
			
			paintCloseBox(g);
		}
		public void paintCrossHairs(Graphics g, int x, int y, int size ) {
			Color oldColor = g.getColor();
			// int mid, i, j;

			// j = 0;
			size = Math.max(size, 6);
	
			g.translate(x, y);

			g.setColor( tabPane.getForeground() );
			g.drawLine( 2, 2, size - 4, size-4);
			g.drawLine( 2, size - 4, size-4, 2);
		
			g.translate(-x, -y);	
			g.setColor(oldColor);
		}

		public void paintCloseBox( Graphics g ) {

			if( tabPane.getTabCount() == 0 ) return;
			if( !isVisible() ) return;
		
			Color origColor;
			// boolean isPressed, isEnabled;
			int w, h;
			w = size;
			h = size;
			origColor = g.getColor();

				g.setColor( highlight ); // tabPane.getBackground());
				g.fillRect(1, 1, w-2, h-2);

				if ( true ) { // bMouseInside) {
					g.drawLine(0, 0, 0, h-1);
					g.drawLine(1, 0, w-2, 0);

					g.setColor(highlight);    // inner 3D border
					g.drawLine(1, 1, 1, h-3);
					g.drawLine(2, 1, w-3, 1);

					g.setColor(shadow);       // inner 3D border
					g.drawLine(1, h-2, w-2, h-2);
					g.drawLine(w-2, 1, w-2, h-3);

					g.setColor(darkShadow);     // black drop shadow  __|
					g.drawLine(0, h-1, w-1, h-1);
					g.drawLine(w-1, h-1, w-1, 0);
				}

				boolean bIsClosePressed = getModel().isPressed();
				if (bIsClosePressed) g.translate(1, 1);

				// Draw the crosshairs
				paintCrossHairs( g, 2, 2, 12 );

				// Reset the Graphics back to it's original settings
				if (bIsClosePressed) g.translate(-1, -1);

				g.setColor(origColor);
	
		} 
	}
	
//	protected class CloseBoxButton extends JButton implements UIResource {
//		
//		public CloseBoxButton( String s ){
//			super(s);
//		}
//	}
	/**
	 * 
	 */
	public ClosableTabbedPaneUI( ) {
		super();
		// TODO Auto-generated constructor stub
		
		btnCloseBox.setFocusable( false );
		
	}
	
	public JButton getUIButton() {
		return btnCloseBox;
	}
	
	protected void installComponents() {      // create and add the close box
		super.installComponents();
//		btnCloseBox = new JButton("X");


//		button = new JButton(createImageIcon("buttons/b1.gif", description)); 
//		button.setPressedIcon(createImageIcon("buttons/b1p.gif", description)); 
//		button.setRolloverIcon(createImageIcon("buttons/b1r.gif", description)); 
//		button.setDisabledIcon(createImageIcon("buttons/b1d.gif", description));

		tabPane.add( btnCloseBox );
	}
	
	protected void uninstallComponents() {    // remove the close box
		super.uninstallComponents();
		System.err.println( "WARNING: lifecycle ignored in remove");
		tabPane.remove( btnCloseBox );
		btnCloseBox = null;		
	}
	
	protected void installDefaults() {      // creates the space to put the closebox
		super.installDefaults();
		tabAreaInsets.right += 40;
	}

	
	public class PostModeTabbedPaneLayout extends TabbedPaneLayout {
		public void layoutContainer(Container parent ) {
			super.layoutContainer( parent );
			
			int x = btnCloseBox.getX();
			int w = btnCloseBox.getWidth();
			int y = 4;

			int placement = tabPane.getTabPlacement();
			if( placement == SwingConstants.BOTTOM) {
				y = tabPane.getHeight() - size - 4;
			}

			btnCloseBox.setBounds( x+w-20, y, 15, 15);
		}
	}
	protected LayoutManager createLayoutManager() {
		return new PostModeTabbedPaneLayout();
	}

}
