package idea.tsoffline;

import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.io.File;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.ImageIcon;
import javax.swing.SwingUtilities;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Level;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;

import icuInterface.PlatformUtil;
import idea.persistmanager.hdf5.H5Util;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUncaughtExceptionHandler;
import idea.GuiUtil;
import idea.meddaq.AppSetup;
import idea.r.RUtil;
import idea.repository.RepositoryFactory;
import idea.repository.RepositoryInterface;
import idea.repository.io.LocalJAXBRepository;
import idea.tsoffline.script.ConsolePanel;

@Slf4j
public class Main {

	private static File home = new File(System.getProperty("user.home"));
	private static File tsoDir = new File(home, ".tsoffline");
	private static File defaultPrefsFile = new File(tsoDir, "setup.xml");
	private static File prefsFile;
	private static ConsolePanel console;
	
	private static String sessionFile; 

	public static void parseArgs(String[] args) {

		for (int i = 0; i < args.length; i++) {

			if ("-log".equals(args[i])) {
				i++;
				String fileName = args[i];
				if (fileName.indexOf("{Date}") > 0) {
					DateFormat df = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss");
					Date now = new Date();
					String str = df.format(now);
					fileName = fileName.replaceAll("\\{Date\\}", str);
				}
				log.info("redirecting output: {}", fileName);
				GuiUtil.redirectStdOutAndErr("tsoffline", fileName);
			} else if ("-d".equals(args[i])) {
				String loggerName = args[++i];
				Logger logger = Logger.getLogger(loggerName);
				if (logger == null) {
					log.error("NO SUCH LOGGER for DEBUG: {}", loggerName);
				} else {
					logger.setLevel(Level.ALL);
				}
			} else if ("-w".equals(args[i])) {
				String loggerName = args[++i];
				Logger logger = Logger.getLogger(loggerName);
				if (logger == null) {
					log.error("NO SUCH LOGGER for WARNING: {}", loggerName);
				} else {
					logger.setLevel(Level.WARN);
				}
			} else if ("-i".equals(args[i]) ) {
				String loggerName = args[++i];
				Logger logger = Logger.getLogger(loggerName);
				if (logger == null) {
					log.error("NO SUCH LOGGER for INFO: {}", loggerName);
				} else {
					logger.setLevel(Level.INFO);
				}
			} else if ("-ww".equals(args[i])) {
				LogManager.getRootLogger().setLevel((Level) Level.WARN);
			} else if ("-ii".equals(args[i])) {
				LogManager.getRootLogger().setLevel((Level) Level.INFO);
			} else if ("-dd".equals(args[i])) {
				LogManager.getRootLogger().setLevel((Level) Level.DEBUG);
			} else if ("-beta".equals(args[i])) {
				AppModel.setBeta(true);
			} else if ("-prefs".equals(args[i])) {
				String fileName = args[++i];
				prefsFile = new File(fileName);
				if (!prefsFile.isAbsolute()) {
					prefsFile = new File(tsoDir, fileName);
				}
			} else {
				sessionFile = args[i];
			}
		}

		Thread.setDefaultUncaughtExceptionHandler(new GuiUncaughtExceptionHandler());
	}

	private static void loadNative() {
		try {
			PlatformUtil.loadLibrary("hdf5");
			PlatformUtil.loadLibrary("hdf5_java");
			// H5.loadH5Lib();
			int[] ver = null;
			String msg = "??";
			try {
				ver = H5Util.getJNIVersion();
				msg = "";

				for (int v : ver) {
					msg += "" + v;
					msg += ".";
				}
			} catch (Throwable e) {
				msg = e.getMessage();
				e.printStackTrace();
			}
			
			System.out.println("HDF5: " + msg );

		} catch (Throwable t) {
			GuiUtil.showError("Error loading libraries", t);
		}

	}

	/*
	 * protected static void initToolWindowManager(JFrame mw) {
	 * 
	 * // Create a new instance of MyDoggyToolWindowManager passing the frame:
	 * MyDoggyToolWindowManager myDoggyToolWindowManager = new
	 * MyDoggyToolWindowManager();
	 * 
	 * // Register the TopComponent providing the bean tree view:
	 * myDoggyToolWindowManager.registerToolWindow("BeanTreeView", // Id
	 * "Bean Tree View", // Title null, // Icon new TsControlPanel(),
	 * //Component ToolWindowAnchor.LEFT); // Anchor
	 * 
	 * // Register the TopComponent providing the icon view:
	 * myDoggyToolWindowManager.registerToolWindow("IconView", // Id
	 * "Icon View", // Title null, // Icon new TsDevicePanel(), //Component
	 * ToolWindowAnchor.TOP); // Anchor
	 * 
	 * // Make all the windows available: for (ToolWindow window :
	 * myDoggyToolWindowManager.getToolWindows()) { window.setAvailable(true); }
	 * 
	 * // Add myDoggyToolWindowManager to the main window (a JFrame). //
	 * MyDoggyToolWindowManager is an extension of a JPanel:
	 * mw.add(myDoggyToolWindowManager, TableLayout.CENTER);
	 * 
	 * }
	 */

	protected static AppFrame initScreen() {
		GraphicsEnvironment env = GraphicsEnvironment.getLocalGraphicsEnvironment();
		GraphicsDevice[] devices = env.getScreenDevices();

		GraphicsDevice d = devices[0];
		if (devices.length > 1) {
			d = devices[1];
		}

		AppFrame frame = new AppFrame();

		// initToolWindowManager(frame);

		ImageIcon image = new ImageIcon(frame.getClass().getResource("/idea/tsoffline/images/sigmaPAD.png"));
		frame.setIconImage(image.getImage());

		boolean debugging = java.lang.management.ManagementFactory.getRuntimeMXBean().getInputArguments().toString()
				.indexOf("-agentlib:jdwp") > 0;
		if (debugging) {
			frame.setTitle(frame.getTitle() + " [DEBUG]");
		}

		frame.setPrefsFile(prefsFile);
		frame.pack();

		frame.setSize(1000, 700);
		// frame.setLocation( 100, 100);
		initPlugins();

		frame.setVisible(true);

		return frame;
	}
	
	protected static void initPlugins() {
		idea.tsoffline.r.PluginController.initPlugin();
		idea.tsoffline.py.PluginController.initPlugin();
		
		try {
			TsPluginAPI plugin = new idea.tsoffline.jog.PluginController();
			plugin.initPlugin( AppModel.getInstance() );
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}


	public static void initRepositoryInterface() {
		RepositoryInterface local = RepositoryFactory.getLocalRepository();
		if (local instanceof LocalJAXBRepository) {
			LocalJAXBRepository r = (LocalJAXBRepository) local;
			r.setRepositoryDir(new File(AppSetup.getLocalRepositoryDir()));
		}

	}

	private static void explain(REXP ok) throws REXPMismatchException {
		REXP cl = ok.getAttribute("class");
		if (cl != null && cl.asString() != null && cl.asString().equals("try-error")) {
			System.err.println("R error: " + ok.asString());
			throw new RuntimeException(ok.asString());
		}
	}

	/**
	 * @param args
	 */
	public static void main(final String[] args) {

		BasicConfigurator.configure();  // log4j configuration
		// set the default logging level to warn
		LogManager.getRootLogger().setLevel((Level) Level.WARN);  

		prefsFile = null;

		parseArgs(args);
		if (prefsFile == null) {
			prefsFile = defaultPrefsFile;
		}

		loadNative();

		try {

			// RMainLoopCallbacks cb;

			console = new ConsolePanel();
			RUtil.init(console);
			REngine re = RUtil.getREngine();
			re.parseAndEval(".setenv <- if (exists(\"Sys.setenv\")) Sys.setenv else Sys.putenv");
			re.parseAndEval(".setenv(\"JAVAGD_CLASS_NAME\"=\"idea/r/RCue\")");

			REXP ok = re.parseAndEval("library(JavaGD)");
			explain(ok);

		} catch (Throwable t) {
			log.error("FIXME: could not start R.  Possible problem creating temp files.", t);
		}

		initRepositoryInterface();

		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {

				try {
					GuiUtil.initApplication("TsOffline", AppFrame.APP_NAME + " " + AppFrame.APP_VERSION + " " + AppFrame.APP_RELEASE, args, true);

					// UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
					// UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.NimbusLookAndFeel");

					AppFrame frame = initScreen();
					frame.setConsole(console);
					frame.setSize(1024, 768);

					REngine re = RUtil.getREngine();
					if (re != null) {
						AppUtil.runR( "idea/tsoffline/r/init.r", true);
						AppUtil.runR( "idea/tsoffline/r/B2B-init.r", true);
					}
					
					if( sessionFile != null ) {
						AppUtil.open( sessionFile );
					}
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});

	}

}
