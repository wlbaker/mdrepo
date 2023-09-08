package idea.meddaq.entry;

import gnu.io.CommPortIdentifier;

import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Image;
import java.awt.Toolkit;
import java.io.PrintStream;
import java.net.URL;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Enumeration;

import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import idea.GuiUtil;
import idea.PrefUtil;
import idea.gui.vm.ConfigurableStreamHandlerFactory;

public class StudyEntryLauncher {

	private static String loadFile = null;
	public static String designatedStudy = null;

	// there are actually three modes:
	// server
	// client
	// stand-alone
	private static String keyName = "C3E-IDEA-ENTRY";
	private static MedDAQEntryFrame frame;
	private static Date startDate;

	/**
	 * @param args
	 */
	public static void showPorts(PrintStream out) {
		Enumeration<?> portList = CommPortIdentifier.getPortIdentifiers();

		while (portList.hasMoreElements()) {
			CommPortIdentifier portID = (CommPortIdentifier) portList.nextElement();

			if (portID.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				out.println("serial: " + portID.getName());
			} else if (portID.getPortType() == CommPortIdentifier.PORT_PARALLEL) {
				out.println("parallel: " + portID.getName());
			}
		}
	}

	protected static void createGUI() {

		PrefUtil.setAppName("C3E-DATA_ENT");
		GraphicsEnvironment env = GraphicsEnvironment.getLocalGraphicsEnvironment();
		GraphicsDevice[] devices = env.getScreenDevices();

		GraphicsDevice d = devices[0];
		if (devices.length > 1) {
			d = devices[1];
		}

		String title = "C3E-DATAENTRY";

		frame = new MedDAQEntryFrame(title);

		Image image = Toolkit.getDefaultToolkit().getImage("/idea/meddaq/idea.png");
		frame.setIconImage(image);

		frame.pack();
		frame.setLocation(100, 100);
		frame.setSize(900, 600);
		frame.setVisible(true);


	}

	public static void main(final String[] args) throws UnsupportedLookAndFeelException, ParseException {

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
				GuiUtil.redirectStdOutAndErr("mgClient", fileName);
			} else if ("-key".equals(args[i])) {
				i++;
				keyName = args[i];
			} else if ("-load".equals(args[i])) {
				i++;
				loadFile = args[i];
			} else if ("-date".equals(args[i])) {
				i++;
				DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm");
				startDate = df.parse(args[i]);
			} else {
				designatedStudy = args[i];
			}
		}

		ConfigurableStreamHandlerFactory factory = //
		new ConfigurableStreamHandlerFactory("classpath", //
				new idea.gui.vm.Handler(ClassLoader.getSystemClassLoader()));

		URL.setURLStreamHandlerFactory(factory);

		// this sets the ENTER hotkey, which we don't want
		// GuiUtil.initApplication(keyName, args, false);
		PrefUtil.setAppName(keyName);
		setLookAndFeel();

		SwingUtilities.invokeLater(new Runnable() {

			public void run() {

				createGUI();
				if (loadFile != null) {
					frame.refresh(startDate, loadFile);
				}
				if (designatedStudy != null) {
					System.err.println( "DESIGNATED STUDY REQUESTED BUT NO READY");
					// frame.beginStudyActionPerformed(null, designatedStudy);
				}

			}
		});

	}

	private static void setLookAndFeel() {
		try {
			// Set System L&F
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (UnsupportedLookAndFeelException e) {
			// handle exception
		} catch (ClassNotFoundException e) {
			// handle exception
		} catch (InstantiationException e) {
			// handle exception
		} catch (IllegalAccessException e) {
			// handle exception
		}

	}

}
