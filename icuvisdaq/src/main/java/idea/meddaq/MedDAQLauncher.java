package idea.meddaq;

import icuInterface.PlatformUtil;

import java.io.File;
import java.net.URL;

import javax.swing.ImageIcon;

import javax.swing.SwingUtilities;
import javax.swing.UnsupportedLookAndFeelException;

import lombok.extern.slf4j.Slf4j;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Level;
import org.apache.log4j.LogManager;

import idea.GuiUtil;
import idea.PrefUtil;
import idea.analysis.AnalysisFactory;

import idea.process.BannerProcess;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;
import idea.repository.io.LocalJAXBRepository;

@Slf4j
public class MedDAQLauncher {

	public static String designatedStudy = null;

	// there are actually three modes:
	// server
	// client
	// stand-alone
	private static boolean server = false;
	private static boolean client = false;

	public static void initRepositoryInterface() {
		RepositoryInterface local = RepositoryFactory.getLocalRepository();
		if (local instanceof LocalJAXBRepository) {
			LocalJAXBRepository r = (LocalJAXBRepository) local;
			r.setRepositoryDir(new File(AppSetup.getLocalRepositoryDir()) );
		}

	}

	public static void loadNative() {
		PlatformUtil.loadLibrary("hdf5");
		PlatformUtil.loadLibrary("hdf5_java");

		try {
			PlatformUtil.loadLibrary("jDAQmx");
		} catch (UnsatisfiedLinkError e) {
			log.error("Unable to load NI-DAQmx support: " + e.getMessage());
		}

		try {
			// First, load the mingw exception handling dll.  I really don't have a good
			// way to figure out what method was used, except to make a note of it when
			// pista is compiled.
			String osName = System.getProperty("os.name");
			String arch = System.getProperty("os.arch");
			if( osName.startsWith("Win") ) {  // Windows 7
				
				// try to determin which method was used, based on arch
				if( "amd64".equals(arch) ) {
					// exception handling with SEH.  For gcc, this currently implies 64-bit.
					PlatformUtil.loadLibrary("libgcc_s_seh-1");
				} else {
					// 32bit & 64bit
					// exception handling with setjump-longjump
					PlatformUtil.loadLibrary("libgcc_s_sjlj-1");
				}
				// there is a third method, dwarf-2.  appears to be 32bit only and gcc specific.

				// for mingw, load libstdc++-6
				PlatformUtil.loadLibrary("libstdc++-6");
				
				// required for one driver...jpistax.dll may have dependency 
				//	PlatformUtil.loadLibrary("cbw64");
			}
			// websockets is pulled in automatically if in LD_LIBRARY_PATH
			// PlatformUtil.loadLibrary("websockets");
		} catch (UnsatisfiedLinkError e) {
			log.error("Could not load PISTAX dependencies: {}", e.getMessage());
		}
		try {
			PlatformUtil.loadLibrary("jpistax");
		} catch (UnsatisfiedLinkError e) {
			log.error("Could not load PISTAX directly: {}", e.getMessage());
		}

		/*
		 * Omitting rxtx
		try {
			String os = System.getProperty("os.name");
			if ("Linux".equals(os)) {
				// auto-loading
				log.info("no autoload of rxtx, but you may need: -Djava.library.path=/usr/lib64/rxtx");
			} else {
				PlatformUtil.loadLibrary("rxtxSerial");
			}
			log.info("---serial library loaded.");
			// loadLibrary("rxtxParallel");
			// loadLibrary("rxtxRaw");
			// loadLibrary("rxtxI2C");
			// loadLibrary("rxtxRS485");
		} catch (UnsatisfiedLinkError e) {
			log.error("Could not load rxtx module", e);
		}
		 */

	}

	public static void parseArgs(String[] args) {
		AppSetup.setClient(false);

		args = GuiUtil.parseArgs(args);
		for (int i = 0; i < args.length; i++) {

			if ("-log".equals(args[i]) || "--log".equals(args[i])) {
				i++;
			} else if ("-key".equals(args[i])) {
				i++;
				PrefUtil.setAppName(args[i]);
			} else if ("-server".equals(args[i])) {
				server = true;
			} else if ("-client".equals(args[i])) {
				client = true;
				AppSetup.setClient(true);
			} else if ("-dd".equals(args[i])) {
				// ignore
			} else if ("-ww".equals(args[i])) {
				// ignore
			} else if ("-ii".equals(args[i])) {
				// ignore
			} else if ("-d".equals(args[i])) {
				++i;
			} else if ("-w".equals(args[i])) {
				++i;
			} else if ("-i".equals(args[i])) {
				++i;
			} else {
				designatedStudy = args[i];
			}
		}

	}

	public static void createGUI() {

		PrefUtil.setAppName("MEDDAQ");

		String title = "MedDAQ";
		if (server) {
			title += " [SERVER]";
		} else if (client) {
			title += " [CLIENT]";
		}
		boolean debugging = java.lang.management.ManagementFactory.getRuntimeMXBean().getInputArguments().toString()
				.indexOf("-agentlib:jdwp") > 0;
		if (debugging) {
			title += "[DEBUG]";
		}

		MedDAQFrame frame = new MedDAQFrame(title);

		frame.pack();
		
		frame.setSize(900, 600);
		frame.setLocationByPlatform( true );

		ImageIcon image = new ImageIcon(frame.getClass().getResource("/idea/meddaq/meddaq.png"));
		frame.setIconImage( image.getImage() );

		GuiUtil.setRootWindow(frame);
		frame.setVisible(true);
		
		if (designatedStudy != null) {
			System.out.println("study?");
			frame.beginStudyActionPerformed(null, designatedStudy);
		}

	}

	public static void main(final String[] args) throws UnsupportedLookAndFeelException {

		BasicConfigurator.configure();  // log4j configuration
		// set the default logging level to warn
		LogManager.getRootLogger().setLevel((Level) Level.WARN);
		  
		ClassLoader cl0 = MedDAQLauncher.class.getClassLoader();
		ClassLoader cl1 = GuiUtil.class.getClassLoader();
		
		System.out.println("cl0=" + cl0);
		System.out.println("cl1=" + cl1);
		
		URL r0 = cl0.getResource("/idea/image/MicrophoneDisabled.png");
		URL r1 = cl1.getResource("idea/image/MicrophoneDisabled.png");
		
		System.out.println("r0=" + r0);
		System.out.println("r1=" + r1);
		
		// System.exit(0);
		/*
		 * some unknown library (?) is interefering with log4j's ability to configure through the log4j.properties file
		 */
		LogManager.getRootLogger().setLevel((Level) Level.WARN);
		parseArgs(args);
		initRepositoryInterface();

		PlatformUtil.init();
		loadNative();
		
		try {
			AnalysisFactory.registerAnalysis( BannerProcess.getAnalysisInfo() );
		} catch( Throwable t ) {
			GuiUtil.showError("FIXME: cannot load analysis engine", t);
		}
		
		SwingUtilities.invokeLater(new Runnable() {

			public void run() {

				try {
					/*
					 * using nimrod
					 */
					GuiUtil.initApplication(
							MedDAQFrame.APP_NAME,  // key name used for saving prefs in registry 
							MedDAQFrame.APP_NAME + " " + MedDAQFrame.APP_VERSION + " " + MedDAQFrame.APP_RELEASE,  // error message app id 
							args);

				} catch (UnsupportedLookAndFeelException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					System.exit(3);
				}

				//JFrame.setDefaultLookAndFeelDecorated(true);
				//JDialog.setDefaultLookAndFeelDecorated(true);

				createGUI();

			}
		});

	}

}
