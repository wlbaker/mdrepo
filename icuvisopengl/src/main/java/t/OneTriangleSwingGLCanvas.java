package t;

import java.awt.BorderLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLCapabilities;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.GLProfile;
import com.jogamp.opengl.awt.GLCanvas;
import javax.swing.JFrame;

/**
 * A minimal program that draws with JOGL in a Swing JFrame using the AWT
 * GLCanvas.
 *
 * @author Wade Walker
 */
public class OneTriangleSwingGLCanvas {

	public static List<File> getFiles(String paths) {
		List<File> filesList = new ArrayList<File>();
		for (final String path : paths.split(File.pathSeparator)) {
			final File file = new File(path);
			if (file.isDirectory()) {
				recurse(filesList, file);
			} else {
				filesList.add(file);
			}
		}
		return filesList;
	}

	private static void recurse(List<File> filesList, File f) {
		File list[] = f.listFiles();
		for (File file : list) {
			if (file.isDirectory()) {
				recurse(filesList, file);
			} else {
				filesList.add(file);
			}
		}
	}

	public static void main(String[] args) {
		List<File> list = getFiles(System.getProperty("java.class.path"));
		for (File file : list) {
			String p = file.getPath();
			if (p.endsWith("jar")) {
				System.out.println(p);
			}
		}

		GLProfile glprofile = GLProfile.getDefault();
		GLCapabilities glcapabilities = new GLCapabilities(glprofile);
		final GLCanvas glcanvas = new GLCanvas(glcapabilities);

		glcanvas.addGLEventListener(new GLEventListener() {

			@Override
			public void reshape(GLAutoDrawable glautodrawable, int x, int y, int width, int height) {
				OneTriangle.setup(glautodrawable.getGL().getGL2(), width, height);
			}

			@Override
			public void init(GLAutoDrawable glautodrawable) {
			}

			@Override
			public void dispose(GLAutoDrawable glautodrawable) {
			}

			@Override
			public void display(GLAutoDrawable glautodrawable) {
				OneTriangle.render(glautodrawable.getGL().getGL2(), glautodrawable.getSurfaceWidth(),
						glautodrawable.getSurfaceHeight());
			}
		});

		final JFrame jframe = new JFrame("One Triangle Swing GLCanvas");
		jframe.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent windowevent) {
				jframe.dispose();
				System.exit(0);
			}
		});

		jframe.getContentPane().add(glcanvas, BorderLayout.CENTER);
		jframe.setSize(640, 480);
		jframe.setVisible(true);
	}
}
