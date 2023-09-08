package opt.sigmapad.canvas;

import org.eclipse.swt.widgets.Composite;
import org.piccolo2d.extras.swt.PSWTCanvas;

import idea.tsoffline.canvas.TsBaseCanvas;

public class TsSWTCanvas extends PSWTCanvas {

	TsBaseCanvas base;
	
	public TsSWTCanvas(Composite parent, int style) {
		super(parent, style);
		base = new TsBaseCanvas() {
			
		} ;
	}

}
