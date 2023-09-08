package idea.display.gl;

import java.awt.Dimension;

import com.jogamp.opengl.awt.GLCanvas;

@SuppressWarnings("serial")
public class GLParameterBox extends GLCanvas {

	final static Dimension MINSIZE = new Dimension(10, 10);

	
	private GLParameterPainter painter;

	public GLParameterBox( String name, int styl ) {
		painter = null; // new GLParameterPainter( styl );
		setMinimumSize(MINSIZE);
		setShallUseOffscreenLayer(true);
		
		if( name != null ) {
			setName(name);
		}
		addGLEventListener(painter);
	}

}
