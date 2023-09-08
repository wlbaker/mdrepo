package idea.tsoffline.export;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.net.URL;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.UIManager;

import org.apache.log4j.Level;
import org.apache.log4j.LogManager;

import icuInterface.PlatformUtil;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;

@Slf4j
public class StandaloneExporter implements PropertyChangeListener {

	private static String title = "tsOffline Exporter";
	private static JFrame f;
	
	private static boolean loadNative() {
		// DataSource.loadNatives();
		boolean success = false;
		try {
			PlatformUtil.loadLibrary("jhdf5");
			// H5.loadH5Lib();

			success = true;
		} catch (UnsatisfiedLinkError t) {
			GuiUtil.showError("Could not load HDF5 library", t);
		} catch (Throwable t) {
			GuiUtil.showError("Error loading libraries", t);
		}

		return success;
	}


	private static void initLookAndFeel() {
		String lookAndFeel = null;

		lookAndFeel = UIManager.getSystemLookAndFeelClassName();

		try {

			UIManager.setLookAndFeel(lookAndFeel);

		}

		catch (ClassNotFoundException e) {
			System.err
					.println("Couldn't find class for specified look and feel:"
							+ lookAndFeel);
			System.err
					.println("Did you include the L&F library in the class path?");
			System.err.println("Using the default look and feel.");
		}

		catch (Exception e) {
			GuiUtil.showError("Look and feel error", e);
		}
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) {
		String prop = evt.getPropertyName();
		if( ExportWizard.SOURCE_NAME.equals(prop ) ) {
			String val = (String) evt.getNewValue();
			if( val == null ) {
				f.setTitle( title );
			} else {
				int l = val.length();
				if( l > 100 ) {
					String sub = val.substring(l - 100);
					int slash = sub.indexOf('/');
					if( slash < 0 ) {
						slash = sub.indexOf('\\');
					}
					if( slash > 0 ) {
						val = "..." + sub.substring(slash);
					}
				}
				f.setTitle( title + ":  " + val );
			}
		}
		
	}

	private static void loadIcons(JFrame f) {
		String path = "/idea/tsoffline/images/export_bolt.gif";
		URL url = StandaloneExporter.class.getResource(path);
		if (url == null) {
			log.error("No image for path: {}" + path);
			return;
		}
		ImageIcon icon = new ImageIcon(url);
		// BufferedImage image = ImageIO.read(url);
		// ImageIcon icon = new ImageIcon(image);
		f.setIconImage(icon.getImage());
	}


	/**
	 * @param args
	 */
	public void createAndShowGUI() {

		initLookAndFeel();
		
		f = new JFrame( title );
		loadIcons(f);

		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		ExportWizard wizard = new ExportWizard(null, true);
		wizard.addPropertyChangeListener(ExportWizard.SOURCE_NAME, this);
		f.getContentPane().add(wizard);
		f.pack();

		f.setSize(1000, 500);

		GuiUtil.setRootWindow( f );
		loadNative();

		f.setVisible(true);
	}

	public static void main(String[] args) {

		LogManager.getRootLogger().setLevel((Level) Level.WARN);
		GuiUtil.parseArgs(args);
		
		// Schedule a job for the event dispatch thread:
		// creating and showing this application's GUI.
		StandaloneExporter sexp = new StandaloneExporter();
		
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				sexp.createAndShowGUI();
			}
		});
	}



}
