package opt.sigmapad;

import java.awt.Color;

import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.piccolo2d.PLayer;
import org.piccolo2d.extras.swt.PSWTCanvas;
import org.piccolo2d.extras.swt.PSWTPath;
import org.piccolo2d.extras.swt.PSWTText;

public class SigmaPadSWT {

    /**
     * Create and open a new shell on the specified display.
     *
     * @param display display
     * @return a new shell on the specified display
     */
    public static Shell open(final Display display) {
        final Shell shell = new Shell(display);
        shell.setLayout(new FillLayout());

        // create a new SWT canvas
        final PSWTCanvas canvas = new PSWTCanvas(shell, 0);
        
        // canvas.getDragDetect();
        // canvas.removeDragDetectListener(null);
        canvas.setDragDetect(false);
        PLayer layer = canvas.getLayer();
        
        layer.setPickable(false);

        // create some SWT nodes
        //    and add them as child nodes to the canvas' camera's first layer
        PSWTPath rect = PSWTPath.createRectangle(25, 25, 50, 50);
        rect.setPaint(Color.RED);
        canvas.getLayer().addChild(rect);

        rect = PSWTPath.createRectangle(300, 25, 100, 50);
        rect.setPaint(Color.BLUE);
        canvas.getLayer().addChild(rect);

        PSWTPath circle = PSWTPath.createEllipse(100, 200, 50, 50);
        circle.setPaint(Color.GREEN);
        canvas.getLayer().addChild(circle);

        circle = PSWTPath.createEllipse(120, 220, 40, 40);
        circle.setPaint(Color.GRAY);
        circle.setTransparency(0.2f);
        canvas.getLayer().addChild(circle);

        circle = PSWTPath.createEllipse(400, 400, 75, 150);
        circle.setPaint(Color.YELLOW);
        canvas.getLayer().addChild(circle);


        PSWTText text = new PSWTText("Hello World\nMultiline");        
        text.translate(350, 150);
        text.setPenColor(Color.GRAY);
        text.setBackgroundColor(Color.BLACK);
        canvas.getLayer().addChild(text);

        text = new PSWTText("Goodbye World");
        text.translate(50, 400);
        text.setPenColor(Color.MAGENTA);
        canvas.getLayer().addChild(text);

        shell.open();
        return shell;
    }
    
	public static void main2(String[] args) {
		final Display display = new Display();
		Shell shell = new Shell(display);
		shell.setLayout(new FillLayout());
		Composite comp = new Composite(shell, SWT.NONE);
		comp.setLayout(new FillLayout());

		shell.setText("SigmaPAD Canvas and piccolo");
		shell.setSize(640, 480);
		shell.open();

		while (!shell.isDisposed()) {
			if (!display.readAndDispatch())
				display.sleep();
		}
		display.dispose();
	}
	
    public static void main(final String[] args) {
        final Display display = new Display();
        final Shell shell = open(display);
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch()) {
                display.sleep();
            }
        }
        display.dispose();
    }


}
